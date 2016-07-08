/* 
 * Name: interrupt_service.c
 * Desc: Definitions of interrupt services.
 * Auth: ishbguy@hotmail.com
 * Date: 2016-07-08 16:18:27 
 */
#include "config.h"
#include "interrupt.h"
#include "uart.h"
#include "timer.h"
#include "delay.h"
#include "lcd1602.h"
#include "interrupt_service.h"

void UartIsr(void) INTERRUPT SI0_VECTOR
{
        if(RI) {
                if(cmd < buf + BUFSIZE - 1 &&\
                                SBUF != '\n' &&\
                                SBUF != '\r' &&\
                                SBUF != '\b' &&\
                                SBUF != 127) {
                        *cmd++ = SBUF;
                        UartSendChar(SBUF);
                        RI = 0;
                }
                else if(SBUF == '\r' || SBUF == '\n') {
                        *cmd = '\0';
                        cmd = buf;
                        UartSendChar('\n');
                        UartSendChar('\r');
                        uarttoggle = 1;
                        RI = 0;
                }
                else if(SBUF == '\b' || SBUF == 127) {
                        if(cmd > buf) {
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

void Timer0Isr(void) INTERRUPT TF0_VECTOR
{
        TH0 = TIMES / 256;
        TL0 = TIMES % 256;
        tick++;
        ms50++;
        if(ms50 >= 20) {
                ms50 = 0;
                second++;
                if(second >= 43200) {
                        second  = 0;
                        apm = !apm;
                }
        }

        if(lcdtoggle == 1 && tick == 400) {
                LEDEN = 1;
                LcdSendCmd(NDIS_NCRS_NBLK);
                lcdtoggle = 0;
        }
        if(tick >= 1200) {
                tick = 0;
                starttoggle = 1;
        }
}
//Exception interrupt service program
void Interrupt0Isr(void) INTERRUPT IE0_VECTOR
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
