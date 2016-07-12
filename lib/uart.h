/*
 * UART is the most common use in MCU, this file contain some prototype
 * about the UART, which involves some registers like:PCON, SCON, TMOD,
 * TH1, TL1, IE, TCON
 *
 * +---+---+---+---+---+---+---+---+---+
 * |BIT  7   6   5   4   3   2   1   0 |
 * +---+---+---+---+---+---+---+---+---+
 * |IE   EA  -  ET2 ES  ET1 EX1 ET0 EX0|
 * +---+---+---+---+---+---+---+---+---+
 * TCON TF1 TR1 TF0 TR0 IE1 IT1 IE0 IT0|
 * +---+---+---+---+---+---+---+---+---+
 * TMOD GAT C/T  M1  M0 GAT C/T  M1 M0 |
 * +---+---+---+---+---+---+---+---+---+
 * |IP   -   -  PT2  PS PT1 PX1 PT0 PX0|
 * +---+---+---+---+---+---+---+---+---+
 * SCON SM0 SM1 SM2 REN TB8 RB8  TI RI |
 * +---+---+---+---+---+---+---+---+---+
 * PCON SMOD SMOD0 -POF GF1 GF0  PD IDL|
 * +---+---+---+---+---+---+---+---+---+
 * |PSW  CY  AC  F0 RS1 RS0 OV   -   P |
 * +---+---+---+---+---+---+---+---+---+
 * T2CON TF2 EXF2 RCLK TCLK EXEN2 TR2 C/T2 CP/RL2
 * +---+---+---+---+---+---+---+---+---+
 */
#ifndef __UART_H__
#define __UART_H__

/* UART MODE */
#define UMode0                  (0 << 6)
#define UMode1                  (1 << 6)
#define UMode2                  (2 << 6)
#define UMode3                  (3 << 6)

/* TIMER1 MODE */
#define T1M0                    (0 << 4)
#define T1M1                    (1 << 4)
#define T1M2                    (2 << 4)
#define T1M3                    (3 << 4)

#define COUT1                   (1 << 6)
#define TMR1                    (0 << 6)
#define GTO1                    (1 << 7)
#define GTC1                    (0 << 7)
#define T1R                     (1 << 6)
#define T1S                     (0 << 6)

/* Bit rate */
#define R300                    (0XA0)
#define R600                    (0XD0)
#define R1200                   (0XE8)
#define R2400                   (0XF4)
#define R4800                   (0XFA)
#define R9600                   (0XFD)
#define R19200                  (0XFD)

/**
 * @brief       UART initialize function.
 *
 * @param mode  Mode of UART.
 * @param rate  Bit rate of UART.
 */
extern void UartInit(unsigned char mode, unsigned char rate);

/**
 * @brief       Send a character by UART.
 *
 * @param ch    Character ready to send.
 *
 * @return      OK if character sent.
 */
extern unsigned char UartSendChar(unsigned char ch);

/**
 * @brief       Send a string by UART.
 *
 * @param str   String to be sent.
 *
 * @return      Length of string.
 */
extern unsigned char UartSendStr(unsigned char *str);

/**
 * @brief       Convert the integer value to char value and
 *              print it by UART.
 *
 * @param num   The integer number.
 *
 * @return      Length of the integer number.
 */
extern unsigned char UartIntToAscii(unsigned long num) REENTRANT;

/**
 * @brief       A function like printf(), can a simple format
 *              string.
 *
 * @param fmt   Format of the string, it support %c, %d, %f, %s.
 * @param ...
 *
 * @return      Length of the printed string.
 */
extern unsigned char UartPrintf(unsigned char *fmt, ...);

#endif
