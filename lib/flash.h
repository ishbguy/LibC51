/* 
 * Name: flash.h
 * Desc: Function declarations for flash(EEPROM).
 * Auth: ishbguy@hotmail.com
 * Date: 2016-07-14 23:05:17 
 *
 *       +----------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       |  Name    |   7    |    6   |    5   |    4   |    3   |    2   |    1   |    0   |
 *       +----------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       | ISP_CONTR| ISPEN  |  SWBS  |  SWRST |        |        |   WT2  |   WT1  |   WT0  |
 *       +----------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       | ISP_CMD  |        |        |        |        |        |        |    MS1 |    MS0 |
 *       +----------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       | ISP_TRIG |        |        |        |        |        |        |        |        |
 *       +----------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       | ISP_DATA |        |        |        |        |        |        |        |        |
 *       +----------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       | ISP_ADDRH|        |        |        |        |        |        |        |        |
 *       +----------+--------+--------+--------+--------+--------+--------+--------+--------+
 *       | ISP_ADDRL|        |        |        |        |        |        |        |        |
 *       +----------+--------+--------+--------+--------+--------+--------+--------+--------+
 *
 *       When ISPEN = 1, write ISP_TRIG with 46H, B9H in order, ISP_CMD will be effective.
 *       When finished ISP_CMD, the content of ISP_CMD, ISP_ADDRH, ISP_ADDRL will not be
 *       changed.
 *
 *       ISP commands:
 *
 *       MS1    MS0     Operation
 *       0      0       Standby, no operation
 *       0      1       Read a byte
 *       1      0       Write a byte
 *       1      1       Erase a sector
 *
 *       WT2    WT1     WT0     Read    Write   Erase   Clock
 *       0      1       1       6T      30T     5471T   5Mhz
 *       0      1       0       11T     60T     10942T  10Mhz
 *       0      0       1       22T     120T    21885T  20Mhz
 *       0      0       0       43T     240T    43769T  40MHz
 *
 *       STC89C52RC has 4k flash rom, which contains 8 sectors, from 2000H to 2FFFH.
 *
 *       Sector0        2000H~21FFH
 *       Sector1        2200H~23FFH
 *       Sector2        2400H~25FFH
 *       Sector3        2600H~27FFH
 *       Sector4        2800H~29FFH
 *       Sector5        2A00H~2BFFH
 *       Sector6        2C00H~2DFFH
 *       Sector7        2E00H~2FFFH
 *             
 *       PS: 1 could be changed to 1 and 0, 0 could only changed to 0, if we want to change
 *           0 to 1, we must erase 0 to become 1 then change it.
 */                                                                                                  
#ifndef __FLASH_H__
#define __FLASH_H__

#include "config.h"

/* Register bit */
#define WT0                     (1 << 0)
#define WT1                     (1 << 1)
#define WT2                     (1 << 2)
#define SWRST                   (1 << 5)
#define SWBS                    (1 << 6)
#define ISPEN                   (1 << 7)

#define MS0                     (1 << 0)
#define MS1                     (1 << 1)

/* CMD */
#define CMD_Standby             (0 << 1 | 0 << 0)
#define CMD_Read                (0 << 1 | 1 << 0)
#define CMD_Write               (1 << 1 | 0 << 0)
#define CMD_Erase               (1 << 1 | 1 << 1)

#define EN_ISP5                 (ISPEN | WT1 | WT0)
#define EN_ISP10                (ISPEN | WT1)
#define EN_ISP20                (ISPEN | WT0)
#define EN_ISP40                (ISPEN)

/* Flash address range */
#define FlashStartAddr          (0x2000)
#define FlashEndAddr            (0x2FFF)
#define SectorSize              (0x200)
#define Sector0                 (0x2000)
#define Sector1                 (0x2200)
#define Sector2                 (0x2400)
#define Sector3                 (0x2600)
#define Sector4                 (0x2800)
#define Sector5                 (0x2A00)
#define Sector6                 (0x2C00)
#define Sector7                 (0x2E00)

/* Macro functions */
#define FlashInit(time)         do {    \
        ISP_CONTR |= time;              \
} while(0)

#define FlashReady()            do {    \
        ISP_TRIG = 0x46;                \
        ISP_TRIG = 0xB9;                \
} while(0)

#define FlashCMD(cmd)           do {    \
        ISP_CMD |= cmd;                 \
} while(0)

#define FlashStandby()          do {    \
        ISP_CONTR = 0;                  \
        ISP_CMD   = 0;                  \
        ISP_TRIG  = 0;                  \
        ISP_ADDRH = 0x80;               \
        ISP_ADDRL = 0;                  \
} while (0)

#define FlashReadByte(addr,data)    do {\
        FlashInit(STC_WT);              \
        FlashCMD(CMD_Read);             \
        ISP_ADDRL = addr;               \
        ISP_ADDRH = (addr >> 8);        \
        FlashReady();                   \
        NOP();                          \
        data = ISP_DATA;                \
        FlashStandby();                 \
} while(0)

#define FlashWriteByte(addr,data)   do {\
        FlashInit(STC_WT);              \
        FlashCMD(CMD_Write);            \
        ISP_ADDRL = addr;               \
        ISP_ADDRH = (addr >> 8);        \
        ISP_DATA  = data;               \
        FlashReady();                   \
        NOP();                          \
        FlashStandby();                 \
} while(0)

#define FlashEraseSector(sector)    do {\
        FlashInit(STC_WT);              \
        FlashCMD(CMD_Erase);            \
        ISP_ADDRL = addr;               \
        ISP_ADDRH = (addr >> 8);        \
        FlashReady();                   \
        NOP();                          \
        FlashStandby();                 \
} while(0)

#endif /* End of include guard: __FLASH_H__ */
