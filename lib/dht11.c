/*
 * DHT11 temperature and humidity sensor function definitions
 *
 */

#include "config.h"
#include "dht11.h"
#include "delay.h"

/* Initialize DHT11 then ready to read data. */
static bool Dht11Init(void)
{
        bool flag;
        unsigned char time;

        /* A start signal, >18ms low level, then 20-40us high level. */
        DATA = 0;
        Delay1ms(19);                    // >18ms
        DATA = 1;
        for(time = 0; time < 10; time++);// 20-40us    34.7us
        for(time = 0; time < 12; time++);

        /* A response signal */
        flag = DATA;
        for(time = 0; time < 11; time++);//DHT11 response for 80us in low level.
        for(time = 0; time < 24; time++);//DHT11 response for 80us in high level.
        return flag;
}

/* Read a byte of data. */
static unsigned char Dht11GetChar()
{
        unsigned char byte = 0;
        unsigned char time;
        unsigned char time1;

        while(DATA == 1);                 //Wait the end of response signal.
        for(time1=0;time1<8;time1++) {
                while(DATA == 0);         //Ready for about 50us. 
                byte <<= 1;               //Ready to get next bit.

                /* Count the high level stay time.
                 * if it more than 28us, it is 1 signal
                 * or it is 0
                 */
                for(time = 0; DATA == 1; time++);
                if(time < 10)
                        byte |= 0x00;
                else
                        byte |= 0x01;
        }
        return byte;
}

/* Get 40bits data from DHT11. */
bool Dht11GetData(DHT11 * data)
{
        unsigned char time;
        unsigned char tem, hum, CRC;

        tem = hum = CRC = 0;

        EA = 0;

        /* 40 bits = 8bits humidity integer part
         *         + 8bits humidity fraction part
         *         + 8bits temperature ineger part
         *         + 8bits temperature fraction part
         *         + 8bits CRC (the last 8bits about 
         *           the sum of before 32bits). 
         */
        if(Dht11Init() == 0) {
                hum = Dht11GetChar();
                Dht11GetChar();
                tem = Dht11GetChar();
                Dht11GetChar();
                CRC = Dht11GetChar();

                /* Last the pin will be low level for
                 * about 50us.
                 */
                for(time = 0; time < 17; time++);
                DATA = 1;
        }
        EA = 1;
        
        if ((tem + hum) != CRC && CRC == 0)
                return ERROR;

        data->hum = hum;
        data->tem = tem;
        data->CRC = CRC;

        return SUCCESS;

}
