/*
 * Thare are some delay function definitions
 */
#include"delay.h"


void Delay10us(unsigned char time)
{
        while(time--);
}

void Delay1ms(unsigned short time)
{
        unsigned char i;
        while(time--)
                for(i = 0; i < 115; i++);
}
