/*
 * There are some function  definition about UART.
 *
 */
#include <stdarg.h>
#include "config.h"
#include "uart.h"

void UartInit(unsigned char mode, unsigned char rate)
{
        PCON = 0X00;
        SCON |= (mode | 1 << 4);
        TH1 = rate;
        TL1 = rate;
        TMOD |= (T1M2 | GTC1 | TMR1);
        EA = OPEN;
        ES = OPEN;
        TR1 = RUN;
}

unsigned char UartSendChar(unsigned char ch)
{
        /* In case come accross an interrupt, close EA */
        EA = 0;         
        SBUF = ch;
        while(!TI);
        TI = 0;
        /* After send char, reopen EA. */
        EA = 1;
        return OK;
}

unsigned char UartSendStr(unsigned char *str)
{
        unsigned char len = 0;
        while(*str) 
                len += UartSendChar(*str++);
        return len;   //Return string length.
}

//Convert the integer value to char value and print it.
unsigned char UartIntToAscii(unsigned long num) REENTRANT
{
        unsigned long temp;
        unsigned char len = 1;

        temp = num / 10;
        if(temp != 0)
                len += UartIntToAscii(temp);
        UartSendChar(num % 10 + '0');
        return len;
}

//UartPrintf is a similar function like the STDlib function
//printf, but it implements the simple abilities like print
//char, decimal, string, float, and some control characters.
unsigned char UartPrintf(unsigned char *fmt, ...)
{
        va_list ap;
        char flag;
        unsigned char len = 0;
        EA = 0;
        
        //initialize the ap
        va_start(ap, fmt);
        //handle the control characters 
        while(*fmt) {
                //check whether the character is '%'
                if((flag = *fmt++) != '%') {
                        if (flag == '\t')
                                len += 1;
                        else if (flag == '\b')
                                len--;
                        else if (flag == '\n' || flag == '\r');
                        else
                                len++;
                        //print it and continue.
                        UartSendChar(flag);
                        continue;
                }
                //get format characterr then handle them.
                flag = *fmt++;
                switch(flag) {
                        case 's':
                                len += UartSendStr(va_arg(ap, unsigned char *));
                                break;
                        case 'd':
                                len += UartIntToAscii(va_arg(ap, unsigned short));
                                break;
                        case 'f':
                                len += UartSendChar(va_arg(ap, float));
                                break;
                        case 'c':
                                len +=UartSendChar(va_arg(ap, unsigned char));
                                break;
                        default:
                                len += UartSendChar(flag);
                                break;
                }
        }
        va_end(ap);
        EA = 1;
        return len;
}
