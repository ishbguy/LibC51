/* 
 * Name: clock.h
 * Desc: Declaration of clock functions.
 * Auth: ishbguy@hotmail.com
 * Date: 2016-07-11 22:02:25 
 */
#ifndef __CLOCK_H__
#define __CLOCK_H__

#define MSTIMES                 (46)
#define TIMES                   (65536 - (MSTIMES * 1000))
#define SEC                     (0)
#define MIN                     (1)
#define HOUR                    (2)

extern unsigned char TimeConvert(unsigned int sec, unsigned char fmt);
extern unsigned char AsciiToInt(unsigned char ch);
extern unsigned int  TimeSet(unsigned char *time);

#endif /* End of include guard: __CLOCK_H__ */
