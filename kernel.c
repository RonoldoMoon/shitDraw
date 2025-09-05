#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "function.h"

void kernel_main(void)  {

		/* Initialize terminal interface */
		terminal_initialize();

			/* Newline support is left as an exercise. */
			terminal_writestring("Hello, kernel Worldz :D!\n");
			writeStringColor("booballyboop\njoyoop\nwhaloop", 0b00001010);
			hPrintWord(0xB00F);
}
