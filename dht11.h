/*
 * DHT11 is the tempareture and humidity sensor, it can detect the
 * temperature range from 0 ~ 50 degrees centigrate, and it also 
 * detect the humidity range from 20 ~ 90 %RH(25'C). The pins and 
 * its typical circuit is as below:
 *                      +-------+--5V
 *      -------------  |-|5k    |   ---------
 *      |           |  |_|  15V +---|       |
 *      |           |   |   2DATA   |       |
 *      |   MCU     |---+-----------| DHT11 |
 *      |           |       3NC ----|       |
 *      |           |       4   +---|       |
 *      -------------       GND |   ---------
 *      typical circuit
 *
 * Pin 2 is a serial data port, it can comunicate with microchip 
 * by pin 2, one communication last for abot 40ms, and it can trans-
 * fer 40 bits to MCU for one time. The data format of the 40 bits
 * is: 40 bits = 8bits humidity integer part
 *            + 8bits humidity fraction part
 *            + 8bits temperature ineger part
 *            + 8bits temperature fraction part
 *            + 8bits CRC (the last 8bits about the sum of before 
 *              32bits).
 *
 * Communication procedure:
 *
 *|----MCU signal----||-----DHT11 signal---|-data->- 0 ---|------- 1 ----------|

 * --+          +-----+          +---------+        +-----+        +-----------+
 *   |          |     |          |         |        |     |        |           |
 *   +----------+     +----------+         +--------+     +--------+           +--
 *
 *   |-   >18  -|20-40|-   80   -|-   80  -|-  50  -|26-28|-  50  -|-    70   -|
 *   |    ms    | us  |    us    |    us   |   us   | us  |   us   |     us    |
 *
 *   |   MCU start    |    DHT11 answer    |   0 signal   |      1 signal      |
 */

#ifndef __DHT11_H__
#define __DHT11_H__

#include <stdbool.h>

/**
 * @brief dht11 data type.
 */
typedef struct dht11 {
        unsigned char hum;
        unsigned char tem;
        unsigned char CRC;
} DHT11;

/**
 * @brief       Interface to get temperature and humidity data from DHT11.
 *
 * @param data  Pointer of dht11 data type.
 *
 * @return      SUCCESS:        hum + tem == CRC
 *              ERROR:          hum + tem != CRC
 */
extern bool Dht11GetData(DHT11 * data);

#endif
