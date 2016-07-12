/*
 * This is the relay function to test the temperature and humidity ro make
 * a reaction.
 *
 */

#include "config.h"
#include "relay.h"

unsigned char RelayExe(unsigned char hum, unsigned char tem)
{
        if(tem > DTMAX) {
                if(hum > DHMAX) {
                        COOL    = 0;
                        HEAT    = 1;
                        SPRINK  = 1;
                        FAN     = 0;
                        return CF;
                }
                else if(hum < DHMIN) {
                        COOL    = 0;
                        HEAT    = 1;
                        SPRINK  = 0;
                        FAN     = 1;
                        return CS;
                }
                else {
                        COOL    = 0;
                        HEAT    = 1;
                        SPRINK  = 1;
                        FAN     = 1;
                        return CC;
                }
        }
        else if(tem < DTMIN) {
                if(hum > DHMAX) {
                        COOL    = 1;
                        HEAT    = 0;
                        SPRINK  = 1;
                        FAN     = 0;
                        return HF;
                }
                else if(hum < DHMIN) {
                        COOL    = 1;
                        HEAT    = 0;
                        SPRINK  = 0;
                        FAN     = 1;
                        return HS;
                }
                else {
                        COOL    = 1;
                        HEAT    = 0;
                        SPRINK  = 1;
                        FAN     = 1;
                        return HH;
                }
        }
        else {
                if(hum > DHMAX) {
                        COOL    = 1;
                        HEAT    = 1;
                        SPRINK  = 1;
                        FAN     = 0;
                        return FF;
                }
                else if(hum < DHMIN) {
                        COOL    = 1;
                        HEAT    = 1;
                        SPRINK  = 0;
                        FAN     = 1;
                        return SS;
                }
                else {
                        COOL    = 1;
                        HEAT    = 1;
                        SPRINK  = 1;
                        FAN     = 1;
                        return 0;
                }
        }
}
