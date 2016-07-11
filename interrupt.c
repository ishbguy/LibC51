/*
 * Interrupt initialization function definition
 *
 */

#include "config.h"
#include "interrupt.h"

bool InterruptInit(INTNO intno, unsigned char type)
{
        unsigned char IntSet[4] = {
                INTRPT0,
                INTRPT1,
                INTRPT2,
                INTRPT3
        };

        if (intno < intrpt0 || intno > intrpt3) {
                return FAILED;
        }

        if (intno <= intrpt2) {
                IE    |= IntSet[intno];
                TCON  |= type;
        }
        else {
                XICON |= (IntSet[intno] | type);
        }

        EA = 1;
        return OK;
}
