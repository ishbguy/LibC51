/*
 * Interrput function protype. The interrupt affact the IE, IP, TCON,
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
 *
 */
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include <stdbool.h>

#define INT0                    (1 << 7 | 1 << 0)
#define INT1                    (1 << 7 | 1 << 2)
#define DW0                     (1 << 0)
#define DW1                     (1 << 2)
#define LV0                     (0 << 0)
#define LV1                     (0 << 2)

#define INTV0                   0
#define INTV1                   2
#define UIV                     4
#define TIV0                    1
#define TIV1                    3
#define TIV2                    5

extern bool apm, lcdtoggle, starttoggle, uarttoggle;
extern unsigned char *cmd, buf[], ms50;
extern unsigned long tick, second;

extern unsigned char InterruptInit(unsigned char intnum, unsigned char mode);
extern void UartIsr(void) INTERRUPT UIV;
extern void Timer0Isr(void) INTERRUPT TIV0;
extern void InteruptIsr(void) INTERRUPT INTV0;

#endif
