/*
 * Thare are some function definition of timer
 */

#include "config.h"
#include "timer.h"

unsigned char TimeConvert(unsigned int sec, unsigned char fmt)
{
        extern bool apm;
        if(fmt == HOUR) {
                if((sec / 3600) == 0 && apm == 1)
                        return 12;
                else
                        return (sec / 3600);
        }
        else if(fmt == MIN)
                return ((sec % 3600) / 60);
        else
                return ((sec % 3600) % 60);
}

unsigned char AsciiToInt(unsigned char ch)
{
        return (unsigned char)(ch - '0');
}

unsigned int TimeSet(unsigned char *time)
{
        extern bool apm;
        unsigned char hour, min, sec;

        hour = (time[4] - '0') * 10 + (time[5] - '0');
        if(hour >= 12) {
                hour -= 12;
                apm   = 1;
        }
        else
                apm = 0;

        min = (time[6] - '0') * 10 + (time[7] - '0');
        if(min > 60)
                min -= 60;
        sec = (time[8] - '0') * 10 + (time[9] - '0');
        if(sec > 60)
                sec -= 60;
        return (hour * 3600 + min * 60 + sec);
}
