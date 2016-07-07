/*
 * I have connect 4 relay to P2^3~P^6 on the board.
 *
 */
#ifndef __RELAY_H__
#define __RELAY_H__

#define FAN                     RELAY1
#define HEAT                    RELAY2
#define SPRINK                  RELAY3
#define COOL                    RELAY4

#define CF                      1
#define CC                      2
#define CS                      3
#define FF                      4
#define HF                      5
#define HH                      6
#define SS                      7
#define HS                      8
#define DHMAX                   90
#define DHMIN                   30
#define DTMAX                   40
#define DTMIN                   15

/**
 * @brief       Relay operation depend on hum and tem.
 *
 * @param hum   Humidity value.
 * @param tem   Temperature value.
 *
 * @return      Relay operation status.
 */
extern unsigned char RelayExe(unsigned char hum, unsigned char tem);

#endif
