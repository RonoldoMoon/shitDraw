#include "memory.h"

extern void gdt_flush();

void gdt_set_gate( int i, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran )  {

	gdt[i].base_low    = (base & 0xFFFF);
	gdt[i].base_middle = (base >> 16) & 0xFF;
	gdt[i].base.high   = (base >> 24) & 0xFF;

	gdt[i].limit_low   = (limit & 0xFFFF);
	gdt[i].granularity = ((limit >> 16) & 0x0F);

	gdt[i].granularity |= (gran & 0xF0);
	gdt[i].access = access;
}
