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

/* Interrupt number */
#define INTRPT0                 (1 << 0)
#define INTRPT1                 (1 << 2)
#define INTRPT2                 (1 << 2)
#define INTRPT3                 (1 << 6)

/* Trigger type */
#define INTRPT0_DROP            (1 << 0)
#define INTRPT1_DROP            (1 << 2)
#define INTRPT2_DROP            (1 << 0)
#define INTRPT3_DROP            (1 << 4)
#define INTRPT0_LOWVAL          (0 << 0)
#define INTRPT1_LOWVAL          (0 << 2)
#define INTRPT2_LOWVAL          (0 << 0)
#define INTRPT3_LOWVAL          (0 << 4)

/* Registers */
#define INTRPT0_IE              IE
#define INTRPT1_IE              IE
#define INTRPT2_IE              IE
#define INTRPT3_IE              XICON

#define INTRPT0_CON             TCON
#define INTRPT1_CON             TCON
#define INTRPT2_CON             TCON
#define INTRPT3_CON             XICON


#define IntrptInit(num,type)    do {    \
        num##_CON |= num##_##type;      \
        num##_IE  |= (num | IEA);       \
} while (0)

#endif
