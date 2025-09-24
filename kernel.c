#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "function.h"
#include "kirbo.h"

/******************
 * mode 13
 * res 320 x 200
 * pixle depth 8bit RRRGGGBB???
 */

void kernel_main(void)  {

	uint8_t* p = (uint8_t*)0xA0000;
		/* Initialize terminal interface */
		terminal_initialize();

			/* Newline support is left as an exercise. */
			//terminal_writestring("Hello, kernel Worldz :D!\n");
			writeStringColor("Hello,\nkernel WORLDZ!\n", 0b00001010);
			hPrintWord(0xB00F);
			setVideoMode13();
			for( int i = 0; i < 0xFFFF; i++ )  p[i] = 0b01011110;
/*
			for( int x = 0; x < 48; x++ )  {

				for( int y = 0; y < 48; y++ )  {

					if ( kirbo_48[ ((y)*48) + x ] != 0xff )
					p[ ((y)*320) + x ] = kirbo_48[ ((y)*48) + x ];
				}
			}
			*/
			putSprite(kirbo_48, 48, 48, 160, 100, 0xFF);
}
