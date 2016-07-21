/*
 * There are some lcd1602 function definitons
 */

#include "config.h"
#include <stdarg.h>
#include <stdbool.h>
#include "lcd1602.h"
#include "delay.h"

#define NOP4                    __asm \
                                nop \
                                nop \
                                nop \
                                nop \
                                __endasm

/* Test the lcd1602 whether it is busy and return busy status by 
 * BUSYFLAG, You can sbit the BUSYFLAG for what you want to set
 */
static bool LcdIsBusy(void)
{
        bool status;
        
        P0 = 0x00;              //Clear the port fisrt
        GETSTATUS;
        LCDEN = 1;
        NOP4;
        status = BUSYFLAG;      //Read the BUSYFLAG bit
        LCDEN = 0;              //Disable operation mode
        
        return status;
}

/* Read the lcd1602 data CMD port, then return the LCD status,
 * you can change the port number by which port you use for the
 * lcd1602
 */
static unsigned char GetLcdStatus(void)
{
        unsigned char status;

        GETSTATUS;
        LCDEN = 1;
        NOP4;
        status = LCDPORT;       //Read the port status
        LCDEN = 0;              //Disable operation mode
        
        return status;
}

/* Read the lcd1602 port data in which addr display then return
 * the acii value.
 */
static unsigned char GetLcdData(void)
{
        unsigned char data;

        GETDATA;
        LCDEN = 1;
        NOP4;
        data = LCDPORT;         //Read the data(ascii value)
        LCDEN = 0;              //Disable operation mode
        
        return data;
}

/* Write the CMD to lcd to take operation. The CMD is some
 * operation code which need to check from the manual.
 */
bool LcdSendCmd(unsigned char cmd)
{
        while(LcdIsBusy());
        SENDCMD;
        LCDEN = 0;
        NOP4;
        LCDPORT = cmd;          //Write CMD to lcd port.
        NOP4;
        LCDEN = 1;              //enable operation mode.
        NOP4;
        LCDEN = 0;

        return OK;
}

void LcdInit(void)
{
        LcdSendCmd(0x38);
        Delay1ms(2);
        LcdSendCmd(0x0c);
        Delay1ms(2);
        LcdSendCmd(0x06);
        Delay1ms(2);
        LcdSendCmd(0x01);
        Delay1ms(2);
}

/* This function is to tell the lcd to move to the right addr
 * to write and dispaly the charcter.
 */
bool LcdSendAddr(unsigned char addr)
{
        /* Write character to addr: 0x80 +_addr. */
        if(LcdSendCmd(addr|STARTADDR))
                return OK;
        else
                return ERROR;
}

/* This function is to write the wdata to lcd to tell lcd what
 * character it needs to display.
 */
bool LcdSendData(unsigned char data)
{
        while(LcdIsBusy());
        SENDDATA;
        LCDEN = 0;
        NOP4;
        LCDPORT = data;        //Write data to lcd port.
        NOP4;
        LCDEN = 1;              //Enable operation mode.
        NOP4;
        LCDEN = 0;

        return OK;
}

unsigned char LcdDisplayChar(unsigned char ch)
{
        LcdSendData(ch);
        Delay1ms(1);
        return OK;
}

unsigned char LcdDisplayString(unsigned char *str)
{
        unsigned char len = 0;
        while(*str) {
                LcdSendData(*str++);
                len++;
                Delay1ms(1);
        }
        return len;
}

/* Store user specify character. */
bool LcdStoreUserCh(unsigned char *userch, unsigned char useraddr)
{
        char i;
        LcdSendCmd(useraddr);
        Delay1ms(1);
        for(i = 0; i < 8; i++) {
                LcdSendData(*userch++);
                Delay1ms(1);
        }
        return OK;
}

bool LcdShift(unsigned char type, unsigned char len, int ms)
{
        while(len--) {
                LcdSendCmd(type);
                Delay1ms(ms);
        }
        return OK;
}

//Convert the integer value to char value and print it.
unsigned char LcdIntToAscii(unsigned long num) REENTRANT
{
        unsigned long temp;
        unsigned char len = 1;
        temp = num / 10;
        if(temp != 0)
                len += LcdIntToAscii(temp);
        LcdDisplayChar(num % 10 + '0');
        return len;
}

/* LcdSet is a useful function to set the lcd working
 * status or mode.  cmd is the command code value, which 
 * has been defined in lcd1602.h.
 */
unsigned char LcdSet(unsigned char cmd, ...)
{
        va_list ap;
        va_start(ap, cmd);
        LcdSendCmd(cmd);
        Delay1ms(2);
        while(*ap) {
                LcdSendCmd(va_arg(ap, unsigned char));
                Delay1ms(2);
        }
        va_end(ap);
        return OK;
}

/* LcdPrintf is a similar function like the STDlib function
 * printf, but it implements the simple abilities like print
 * char, decimal, string, float, and some control characters.
 */
unsigned char LcdPrintf(unsigned char *fmt, ...)
{
        unsigned char len = 0;
        va_list ap;
        char flag;
        /* initialize the ap */
        va_start(ap, fmt);
        /* handle the control characters */
        while(*fmt) {
                /* check whether the character is '%' */
                if((flag = *fmt++) != '%') {
                        /* handle '\n' '\r' '\t' '\b'. */
                        if(flag == '\n' || flag == '\r') {
                                LcdSendAddr(SECONDLINE);
                                Delay1ms(1);
                                continue;
                        }
                        else if(flag == '\t') {
                                LcdDisplayString("    ");
                                len += 4;
                                continue;
                        }
                        else if(flag == '\b') {
                                LcdShift(CRSLR, 1, 1);
                                LcdDisplayChar(' ');
                                LcdShift(CRSLR, 1, 1);
                                len--;
                                continue;
                        }
                        /* if it is not '%' and not * '\n' '\r'
                         * '\t' '\b' //print it and continue.
                         */
                        LcdDisplayChar(flag);
                        len++;
                        continue;
                }
                /* get format characterr then handle them. */
                flag = *fmt++;
                switch(flag) {
                        case 's':
                                len += LcdDisplayString(va_arg(ap, unsigned char *));
                                break;
                        case 'd':
                                len += LcdIntToAscii(va_arg(ap, unsigned short));
                                break;
                        case 'f':
                                len += LcdDisplayChar(va_arg(ap, float));
                                break;
                        case 'c':
                                len += LcdDisplayChar(va_arg(ap, unsigned char));
                                break;
                        default:
                                len += LcdDisplayChar(flag);
                                break;
                }
        }
        va_end(ap);
        return len;
}
