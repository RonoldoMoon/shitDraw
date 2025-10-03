#include "function.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
#define VIDEO_MEM 0xA0000
#define VIDEO_RES_X 320
#define VIDEO_RES_Y 200

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

void hPrint32(uint32_t x)  {

	uint16_t i, y;

	for ( i = 0; i < 8; i++ )  {

		y = x << (4*i);
		y = y >> 28;

		if ( y < 10 ) terminal_putchar( y + 48 );
		else          terminal_putchar( y + 55 );
	}
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

//position wil be for the center of the sprite.
void putSprite(const uint8_t* p, uint8_t size_x, uint8_t size_y, uint8_t pos_x, uint8_t pos_y, uint8_t mask)  {

	for ( uint8_t y = 0; y < size_y; y++ )  {

		for ( uint8_t x = 0; x < size_x; x++ )  {

			if ( p[ (y*size_x) + x ] != mask )
				((uint8_t*)VIDEO_MEM)[ ((y+pos_y-(size_y/2))*VIDEO_RES_X) + ( x + pos_x - (size_x/2) ) ] = p[ (y*size_x) + x ];
		}
	}
}

int getCR0()  {

	asm ( "mov %cr0, %eax" );
}

void printCR0(uint32_t x)  {

	uint32_t mask = 1;

	char *p[] = { "Protected Mode Enabled\n",
		      "Monitor co-processor\n",
		      "Emulation\n",
		      "Task switched\n",
		      "Extension type\n",
		      "Numeric error\n",
		      "Write protect\n",
		      "Alignment mask\n",
		      "Not-write through\n",
		      "Cache disable\n",
		      "Paging\n"                   };

	int i = 0;

	for ( ; mask < 64; mask <<= 1 , i++ )  {

		if ( mask & x ) terminal_putchar('1');
		else terminal_putchar('0');

		terminal_putchar(0x20);


		writeStringColor(p[i], 0b00001010);
	}
}

void store_idt(idt_t *p)  {

	asm volatile ( "sidt %0" : "=m"(*p));
}

