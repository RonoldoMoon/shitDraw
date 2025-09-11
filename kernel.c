#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "function.h"

void kernel_main(void)  {

	uint8_t* p = (uint8_t*)0xA0000;
		/* Initialize terminal interface */
		terminal_initialize();

			/* Newline support is left as an exercise. */
			//terminal_writestring("Hello, kernel Worldz :D!\n");
			writeStringColor("Hello,\nkernel WORLDZ!\n", 0b00001010);
			hPrintWord(0xB00F);
			setVideoMode13();
			for( int i = 0; i < 0xFF; i++ )  p[i] = 0b01011010;
}
