#include "function.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
		return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
		return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
		size_t len = 0;
			while (str[len])
						len++;
				return len;
}

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
				
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
          for (size_t x = 0; x < VGA_WIDTH; x++) {
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
																	}
									}
}

void terminal_setcolor(uint8_t color) 
{
		terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
		const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
		for (size_t i = 0; i < size; i++)
			terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
		terminal_write(data, strlen(data));
}

void setVideoMode13()  {

	asm ( "nop\n"
	      "call set_mode_0x13\n"
	      "nop"       );
}

int test()  {

	asm ( "mov $0x5A, %eax" );
}

int test1(int balls)  {

	asm ( "movl %%ebx, %%eax\n"
	      "inc  %%eax"
	      :
	      : "b" (balls)
	    );
}

void hPrintWord(uint16_t x)  {

	uint16_t i, y;

	for ( i = 0; i < 4; i++ )  {

		y = x << (4*i);
		y = y >> 12;

		if ( y < 10 ) terminal_putchar( y + 48 );
		else          terminal_putchar( y + 55 );
	}
}

void hPrintByte(uint8_t x)  {

	uint8_t i, y;

	for ( i = 0; i < 2; i++ )  {

		y = x << (4*i);
		y = y >> 4; //yeah, shut up...

		if ( y < 10 ) terminal_putchar( y + 48 );
		else          terminal_putchar( y + 55 );
	}
}

void terminal_putcharCOLOR(char c, uint8_t color) 
{
	terminal_putentryat(c, color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void writeStringColor(const char* data, uint8_t color )  {

		size_t size =  strlen(data);

		for (size_t i = 0; i < size; i++)  {
			if ( data[i] == 0x0A ) { terminal_row++; terminal_column = 0; i++; }
			terminal_putcharCOLOR(data[i], color);
		}

}
