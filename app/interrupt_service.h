/* 
 * Name: interrupt_service.h
 * Desc: Declaration of interrupt services.
 * Auth: ishbguy@hotmail.com
 * Date: 2016-07-08 16:16:05 
 */
#ifndef __INTERRUPT_SERVICE_H__
#define __INTERRUPT_SERVICE_H__

#include <stdbool.h>

extern bool apm, lcdtoggle, starttoggle, uarttoggle;
extern unsigned char *cmd, buf[], ms50;
extern unsigned long tick, second;

extern void UartIsr(void) INTERRUPT SI0_VECTOR;
extern void Timer0Isr(void) INTERRUPT TF0_VECTOR;
extern void Interrupt0Isr(void) INTERRUPT IE0_VECTOR;

#endif /* End of include guard: __INTERRUPT_SERVICE_H__ */
