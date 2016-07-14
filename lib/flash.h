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
 *       1      1       Erase a byte
 *
 *       WT2    WT1     WT0     Read    Write   Erase   Clock
 *       0      1       1       6T      30T     5471T   5Mhz
 *       0      1       0       11T     60T     10942T  10Mhz
 *       0      0       1       22T     120T    21885T  20Mhz
 *       0      0       0       43T     240T    43769T  40MHz
 *
 *       STC89C52RC has 4k flash rom, which contains 8 sectors, from 2000H to 2FFFH.
 *
 *       Sector1        2000H~21FFH
 *       Sector2        2200H~23FFH
 *       Sector3        2400H~25FFH
 *       Sector4        2600H~27FFH
 *       Sector5        2800H~29FFH
 *       Sector6        2A00H~2BFFH
 *       Sector7        2C00H~2DFFH
 *       Sector8        2E00H~2FFFH
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
#define CMD_IDIL                (0 << 1 | 0 << 0)
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


#endif /* End of include guard: __FLASH_H__ */
