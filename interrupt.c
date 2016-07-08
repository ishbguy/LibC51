/*
 * Interrupt initialization function definition
 *
 */

#include "config.h"
#include "interrupt.h"

bool InterruptInit(unsigned char intnum, unsigned char mode)
{
        IE      |= intnum;
        TCON    |= mode;
        return OK;
}
