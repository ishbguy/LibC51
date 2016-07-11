/*
 * This is the definition of the timer initialization and timer interrupt
 * service program.
 *
 * Timer setting involves some relate registers: IE, TCON, TMOD, TL, TH IP
 * T2CON
 *
 * +---+---+---+---+---+---+---+---+---+
 * |BIT 7   6   5   4   3   2   1   0  |
 * +---+---+---+---+---+---+---+---+---+
 * |IE  EA  -   ET2 ES  ET1 EX1 ET0 EX0|
 * +---+---+---+---+---+---+---+---+---+
 * TCON TF1 TR1 TF0 TR0 IE1 IT1 IE0 IT0|
 * +---+---+---+---+---+---+---+---+---+
 * TMOD GAT C/T M1  M0  GAT C/T M1  M0 |
 * +---+---+---+---+---+---+---+---+---+
 * |IP  -   -   PT2 PS  PT1 PX1 PT0 PX0|
 * +---+---+---+---+---+---+---+---+---+
 * SCON SM0 SM1 SM2 REN TB8 RB8 TI  RI |
 * +---+---+---+---+---+---+---+---+---+
 * PCON SMOD -  -   -   GF1 GF0 PD  IDL|
 * +---+---+---+---+---+---+---+---+---+
 * |PSW CY  AC  F0  RS1 RS0 OV  -   P  |
 * +---+---+---+---+---+---+---+---+---+
 * T2CON TF2 EXF2 RCLK TCLK EXEN2 TR2 C/T2 CP/RL2
 * +---+---+---+---+---+---+---+---+---+
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdbool.h>

/* Usages */
#define TMR0                    (0 << 2)
#define CNT0                    (1 << 2)
#define TMR1                    (0 << 6)
#define CNT1                    (1 << 6)
#define TMR2                    (0 << 1)
#define CNT2                    (1 << 1)

/* Modes */
#define TMR0_Mode0              (0)
#define TMR0_Mode1              (1)
#define TMR0_Mode2              (2)
#define TMR0_Mode3              (3)
#define TMR1_Mode0              (0 << 4)
#define TMR1_Mode1              (1 << 4)
#define TMR1_Mode2              (2 << 4)
#define TMR1_Mode3              (3 << 4)
#define TMR2_Mode0              (1 << 0 | 0 << 4 | 0 << 5)
#define TMR2_Mode1              (0 << 0 | 0 << 4 | 0 << 5)
#define TMR2_Mode2              (1 << 4 | 1 << 5)
#define TMR2_Mode3              (0)

#define CNT0_Mode0              (0)
#define CNT0_Mode1              (1)
#define CNT0_Mode2              (2)
#define CNT0_Mode3              (3)
#define CNT1_Mode0              (0 << 4)
#define CNT1_Mode1              (1 << 4)
#define CNT1_Mode2              (2 << 4)
#define CNT1_Mode3              (3 << 4)
#define CNT2_Mode0              (1 << 0 | 0 << 4 | 0 << 5)
#define CNT2_Mode1              (0 << 0 | 0 << 4 | 0 << 5)
#define CNT2_Mode2              (1 << 4 | 1 << 5)
#define CNT2_Mode3              (0)

/* Countting Base */
#define TMR0_Mode0_Base              (32)
#define TMR0_Mode1_Base              (256)
#define TMR0_Mode2_Base              (1)
#define TMR0_Mode3_Base              (1)
#define TMR1_Mode0_Base              (32)
#define TMR1_Mode1_Base              (256)
#define TMR1_Mode2_Base              (1)
#define TMR1_Mode3_Base              (1)
#define TMR2_Mode0_Base              (256)
#define TMR2_Mode1_Base              (256)
#define TMR2_Mode2_Base              (256)
#define TMR2_Mode3_Base              (1)

#define CNT0_Mode0_Base              (32)
#define CNT0_Mode1_Base              (256)
#define CNT0_Mode2_Base              (1)
#define CNT0_Mode3_Base              (1)
#define CNT1_Mode0_Base              (32)
#define CNT1_Mode1_Base              (256)
#define CNT1_Mode2_Base              (1)
#define CNT1_Mode3_Base              (1)
#define CNT2_Mode0_Base              (256)
#define CNT2_Mode1_Base              (256)
#define CNT2_Mode2_Base              (256)
#define CNT2_Mode3_Base              (1)

/* Interrupt */
#define TMR0_IE                 (1 << 1)
#define CNT0_IE                 (1 << 1)
#define TMR1_IE                 (1 << 3)
#define CNT1_IE                 (1 << 3)
#define TMR2_IE                 (1 << 5)
#define CNT2_IE                 (1 << 5)
#define IEA                     (1 << 7)

/* Operations */
#define TMR0_TR                 (1 << 4)
#define CNT0_TR                 (1 << 4)
#define TMR1_TR                 (1 << 6)
#define CNT1_TR                 (1 << 6)
#define TMR2_TR                 (1 << 2)
#define CNT2_TR                 (1 << 2)

/* Setting Registers */
#define TMR0_MOD                TMOD
#define CNT0_MOD                TMOD
#define TMR1_MOD                TMOD
#define CNT1_MOD                TMOD
#define TMR2_MOD                T2CON
#define CNT2_MOD                T2CON

#define TMR0_CON                TCON
#define CNT0_CON                TCON
#define TMR1_CON                TCON
#define CNT1_CON                TCON
#define TMR2_CON                T2CON
#define CNT2_CON                T2CON

/* Counting Registers */
#define TMR0_TH                 TH0
#define TMR0_TL                 TL0
#define CNT0_TH                 TH0
#define CNT0_TL                 TL0
#define TMR1_TH                 TH1
#define TMR1_TL                 TL1
#define CNT1_TH                 TH1
#define CNT1_TL                 TL1
#define TMR2_TH                 TH2
#define TMR2_TL                 TL2
#define CNT2_TH                 TH2
#define CNT2_TL                 TL2

#define TimerInit(timer,mode,time)      do {\
        timer##_TH   = time / timer##_##mode##_Base; \
        timer##_TL   = time % timer##_##mode##_Base; \
        timer##_MOD |= (timer | timer##_##mode); \
        timer##_CON |= timer##_TR; \
        IE          |= (timer##_IE | IEA); \
} while (0)


#define MSTIMES                 (46)
#define TIMES                   (65536 - (MSTIMES * 1000))
#define SEC                     (0)
#define MIN                     (1)
#define HOUR                    (2)

extern unsigned char TimeConvert(unsigned int sec, unsigned char fmt);
extern unsigned char AsciiToInt(unsigned char ch);
extern unsigned int  TimeSet(unsigned char *time);

#endif
