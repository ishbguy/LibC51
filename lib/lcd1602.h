/*
 * This is the delay function prototype
 */

#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <stdbool.h>

//Define the                    LCD mode
#define SENDCMD                 RS = 0; RW = 0
#define GETSTATUS               RS = 0; RW = 1
#define SENDDATA                RS = 1; RW = 0
#define GETDATA                 RS = 1; RW = 1

//Define the                    CMD code
#define CLRSCR                  0X01
#define CRSRST                  0X02 //OR 0X03

//Mode settings
#define LCRS_NR                 0X04
#define LCRS_R                  0X05
#define RCRS_NR                 0X06
#define RCRS_R                  0x07

//display, cursor and blink
#define NDIS_NCRS_NBLK          0X08
#define NDIS_NCRS_BLK           0X09
#define NDIS_CRS_NBLK           0X0A
#define NDIS_CRS_BLK            0X0B
#define DIS_NCRS_NBLK           0X0C
#define DIS_NCRS_BLK            0X0D
#define DIS_CRS_NBLK            0X0E
#define DIS_CRS_BLK             0X0F

/* cursor or screen rolling type*/
#define CRSLR                   0X10 //0X10~0X13
#define CRSRR                   0X14 //0x14~0x17
#define SCRLR                   0X18 //0X18~0X1B
#define SCRRR                   0X1C //0X1C~0X1F

//Bit width, line number, matrix
#define BIT4SL57                0X20 //0X20~0X23
#define BIT4SL510               0X24 //0X24~0X27
#define BIT4DL57                0X28 //0X28~0X2B
#define BIT4DL510               0X2C //0X2C~0X2F
#define BIT8SL57                0X30 //0X30~0X33
#define BIT8SL510               0X34 //0X34~0X37
#define BIT8DL57                0X38 //0X38~0X3B
#define BIT8DL510               0X3C //0X3C~0X3F

//User character store  addr, used by LcdSendCmd
#define USERADDR0               0X40
#define USERADDR1               0X48
#define USERADDR2               0X50
#define USERADDR3               0X58
#define USERADDR4               0X60
#define USERADDR5               0X68
#define USERADDR6               0X70
#define USERADDR7               0X78

//Display address               offset
#define STARTADDR               0X80
#define FIRSTLINE               0X00
#define SECONDLINE              0X40

//Dispaly user                  data
#define USERCHAR0               0X00
#define USERCHAR1               0X01
#define USERCHAR2               0X02
#define USERCHAR3               0X03
#define USERCHAR4               0X04
#define USERCHAR5               0X05
#define USERCHAR6               0X06
#define USERCHAR7               0X07

/**
 * @brief       Function to initialize LCD.
 */
extern void LcdInit(void);

/**
 * @brief       Send LCD operation cmd.
 *
 * @param cmd   cmd to be action.
 *
 * @return      OK will be return when finished.
 */
extern bool LcdSendCmd(unsigned char cmd);

/**
 * @brief       Send LCD operation addr, display addr
 *
 * @param addr  Address pass to LCD.
 *
 * @return      OK will be return when finished.
 */
extern bool LcdSendAddr(unsigned char addr);

/**
 * @brief       Send LCD data, such as charactere.
 *
 * @param data  8bit character value.
 *
 * @return      OK will be return when finished.
 */
extern bool LcdSendData(unsigned char data);

/**
 * @brief               Store user's character
 *
 * @param userch        Address of user character buf.
 * @param useraddr      Address need to be written.
 *
 * @return              OK will be return when finished.
 */
extern bool LcdStoreUserCh(unsigned char *userch, unsigned char useraddr);

/**
 * @brief       Setting the shift or rolling type.
 *
 * @param type  Type of shiftting or rolling.
 * @param len   Distance to be shift.
 * @param ms    How long to shift a character.
 *
 * @return      OK will be return when finished.
 */
extern bool LcdShift(unsigned char type, unsigned char len, int ms);

/**
 * @brief       Display a character in LCD.
 *
 * @param ch    The character to be displayed.
 *
 * @return      OK will be return when finished.
 */
extern unsigned char LcdDisplayChar(unsigned char ch);

/**
 * @brief       Display a string in LCD.
 *
 * @param str   String to be displayed.
 *
 * @return      Length of the string.
 */
extern unsigned char LcdDisplayString(unsigned char *str);

/**
 * @brief       Convert an integer number to ascii string a display it.
 *
 * @param num   Integer number.
 *
 * @return      Length of the string.
 */
extern unsigned char LcdIntToAscii(unsigned long num) REENTRANT;

/**
 * @brief       A bundle setting of LCD.
 *
 * @param cmd   CMD code of LCD.
 * @param ...   CMD code like cmd.
 *
 * @return      OK will be return when finished.
 */
extern unsigned char LcdSet(unsigned char cmd, ...);

/**
 * @brief       A function like printf(), which can display a simple formated
 *              string. like %d, %c, %s, %f.
 *
 * @param fmt   Formated string.
 * @param ...   Parameters in fmt.
 *
 * @return      Length of printed string.
 */
extern unsigned char LcdPrintf(unsigned char *fmt, ...);

#endif
