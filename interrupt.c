/*
 * Interrupt initialization function definition
 *
 */

#include "config.h"
#include "interrupt.h"
#include "lcd1602.h"
#include "uart.h"
#include "timer.h"
#include "delay.h"


unsigned char InterruptInit(unsigned char intnum, unsigned char mode)
{
        IE      |= intnum;
        TCON    |= mode;
        return OK;
}

void UartIsr(void) INTERRUPT UIV
{
        if(RI)
        {
                if(cmd < buf + BUFSIZE - 1 &&\
                                SBUF != '\n' &&\
                                SBUF != '\r' &&\
                                SBUF != '\b' &&\
                                SBUF != 127)
                {
                        *cmd++ = SBUF;
                        UartSendChar(SBUF);
                        RI = 0;
                }
                else if(SBUF == '\r' || SBUF == '\n')
                {
                        *cmd = '\0';
                        cmd = buf;
                        UartSendChar('\n');
                        UartSendChar('\r');
                        uarttoggle = 1;
                        RI = 0;
                }
                else if(SBUF == '\b' || SBUF == 127)
                {
                        if(cmd > buf)
                        {
                                UartSendChar(SBUF);
                                UartSendChar(' ');
                                UartSendChar(SBUF);
                                cmd--;
                        }
                        RI = 0;
                }
                
                else
                        RI = 0;
        }
        else
                TI = 0;
}

void Timer0Isr(void) INTERRUPT TIV0
{
        TH0 = TIMES / 256;
        TL0 = TIMES % 256;
        tick++;
        ms50++;
        if(ms50 >= 20)
        {
                ms50 = 0;
                second++;
                if(second >= 43200)
                {
                        second  = 0;
                        apm = !apm;
                }
        }

        if(lcdtoggle == 1 && tick == 400)
        {
                LEDEN = 1;
                LcdSendCmd(NDIS_NCRS_NBLK);
                lcdtoggle = 0;
        }
        if(tick >= 1200)
        {
                tick = 0;
                starttoggle = 1;
        }
}
//Exception interrupt service program
void InteruptIsr(void) INTERRUPT INTV0
{
        Delay1ms(10);
        while(!INT0KEY);
        LEDEN = !LEDEN;
        lcdtoggle = !lcdtoggle;
        if(lcdtoggle)
                LcdSendCmd(DIS_NCRS_NBLK);
        else
                LcdSendCmd(NDIS_NCRS_NBLK);
}
