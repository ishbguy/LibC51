/* 
 * Name: config.h
 * Desc: A configuration header file which you can define what pin you use
 *       and some common useful error code.
 * Auth: ishbguy@hotmail.com
 * Date: 2016-07-03 16:11:34 
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "stc89c52rc.h"
#include <stdbool.h>

#define REENTRANT               __reentrant
#define INTERRUPT               __interrupt
#define NOP()                   __asm \
                                nop \
                                __endasm
/* Pin configurations. */
/* For DHT11 */
#define DATA                    P2_7

/* For external interrupts. */
#define INT0KEY                 P3_2
#define INT1KEY                 P3_3

/* For LCD1602 */
#define RS                      P2_2
#define RW                      P2_1
#define LCDEN                   P2_0
#define LEDEN                   P1_2
#define BUSYFLAG                P0_7
#define LCDPORT                 P0

/* For 4 relays */
#define RELAY1                  P2_3
#define RELAY2                  P2_4
#define RELAY3                  P2_5
#define RELAY4                  P2_6

/* Errors Code definitions */
#define TRUE                    1
#define FALSE                   0
#define SUCCESS                 1
#define FAILED                  0
#define OK                      1
#define ERROR                   0
#define BUSY                    1
#define FREE                    0
#define DISABLE                 0
#define ENABLE                  1
#define RUN                     1
#define STOP                    0
#define OPEN                    1
#define CLOSE                   0
#define PHIGH                   1
#define PLOW                    0


#define BUFSIZE                 11

#endif /* End of include guard: __CONFIG_H__ */
