/* 
 * Name: flash.c
 * Desc: Definition of flash memory functions.
 * Auth: ishbguy@hotmail.com
 * Date: 2016-07-20 23:23:08 
 */
#include "config.h"
#include "flash.h"

void MemInit(memory * mem)
{
        mem->start = FlashStartAddr;
        mem->end   = FlashEndAddr;
        mem->pos   = (MemReadByte(mem, FlashEndAddr-1) << 8) \
                     + MemReadByte(mem, FlashEndAddr);
        if (mem->pos > mem->end || mem->pos < mem->start)
                mem->pos = FlashStartAddr;
        mem->total = mem->end - mem->start + 1;
        mem->free  = mem->end - mem->pos + 1;
}

unsigned char MemReadByte(memory * mem, unsigned short addr)
{
        unsigned char data = '\0';

        if (addr > mem->pos || addr < mem->start)
                return data;
        FlashReadByte(addr, data);
        return data;
}

bool MemWriteByte(memory * mem, unsigned char data)
{
        if (mem->pos >= mem->end - 1)
                return FALSE;
        FlashWriteByte(mem->pos, data);
        mem->pos++;
        mem->free  = mem->end - mem->pos + 1;
        return TRUE;
}

bool MemEraseSector(memory * mem, unsigned short secaddr)
{
        unsigned char posH, posL;

        posH = MemReadByte(mem, FlashEndAddr-1);
        posL = MemReadByte(mem, FlashEndAddr);
        if (secaddr < Sector0 || secaddr > Sector7)
               return FALSE;

        FlashEraseSector(secaddr);
        if (mem->pos >= secaddr) {
                mem->pos = secaddr;
                mem->free  = mem->end - mem->pos + 1;
        }
        FlashWriteByte(FlashEndAddr-1, posH);
        FlashWriteByte(FlashEndAddr, posL);

        return TRUE;
}
