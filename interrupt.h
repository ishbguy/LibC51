/*
 * Interrput function protype. The interrupt affact the IE, IP, TCON,
 *
 * +---+---+---+---+---+---+---+---+---+
 * |BIT 7   6   5   4   3   2   1   0  |
 * +---+---+---+---+---+---+---+---+---+
 * |IE  EA   -  ET2 ES  ET1 EX1 ET0 EX0|
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

/* Interrupt number */
#define INT0                    (1 << 0)
#define INT1                    (1 << 2)
#define INT2                    (1 << 2)
#define INT3                    (1 << 6)

/* Trigger type */
#define DROP0                   (1 << 0)
#define DROP1                   (1 << 2)
#define DROP2                   (1 << 0)
#define DROP3                   (1 << 4)
#define LOWVAL0                 (0 << 0)
#define LOWVAL1                 (0 << 2)
#define LOWVAL2                 (0 << 0)
#define LOWVAL3                 (0 << 4)

extern bool InterruptInit(unsigned char intnum, unsigned char mode);

#endif
