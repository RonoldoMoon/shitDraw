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

			writeStringColor("Hello, welcome to shitDraw v0.01!\n\n", 0b00001011);
			writeStringColor("let us peek at the CR0 register\n", 0b00001111);
			printCR0(getCR0());
//			setVideoMode13();
//			for( int i = 0; i < 0xFFFF; i++ )  p[i] = 0b01011110;
//			putSprite(kirbo_48, 48, 48, 160, 100, 0xFF);
}
