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

#define TIMER0                  0
#define TIMER1                  1
#define TIMER2                  2
#define COUNTRE0                3
#define COUNTER1                4
#define COUNTRE2                5

#define ENABLE                  1
#define DISABLE                 0
#define RUN                     1
#define STOP                    0
#define OPEN                    1
#define CLOSE                   0
#define PHIGH                   1
#define PLOW                    0

#define T0M0                    0
#define T0M1                    1
#define T0M2                    2
#define T0M3                    3
#define T1M0                    (0 << 4)
#define T1M1                    (1 << 4)
#define T1M2                    (2 << 4)
#define T1M3                    (3 << 4)

#define COUT0                   (1 << 2)
#define TMR0                    (0 << 2)
#define COUT1                   (1 << 6)
#define TMR1                    (0 << 6)
#define GTO0                    (1 << 3)
#define GTC0                    (0 << 3)
#define GTO1                    (1 << 7)
#define GTC1                    (0 << 7)
#define T0R                     (1 << 4)
#define T0S                     (0 << 4)
#define T1R                     (1 << 6)
#define T1S                     (0 << 6)

#define MSTIMES                 (46)
#define TIMES                   (65536 - (MSTIMES * 1000))
#define SEC                     0
#define MIN                     1
#define HOUR                    2

extern bool TimerInit(unsigned char timer, unsigned long times);
extern unsigned char TimeConvert(unsigned int sec, unsigned char fmt);
extern unsigned char AsciiToInt(unsigned char ch);
extern unsigned int  TimeSet(unsigned char *time);

#endif
