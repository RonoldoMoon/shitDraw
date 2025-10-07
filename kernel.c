#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "function.h"
#include "kirbo.h"
#include "memory.h"

/******************
 * mode 13
 * res 320 x 200
 * pixle depth 8bit RRRGGGBB???
 */
#define COLOR 0b00001111

gdt_entry_t gdt[3];
gdt_ptr_t   gdtPointer;


void kernel_main(void)  {

	uint8_t* p = (uint8_t*)0xA0000;

		/* Initialize terminal interface */
		terminal_initialize();

			writeStringColor("Hello, welcome to shitDraw v0.01!\n\n", 0b00001011);
			writeStringColor("let us peek at the CR0 register\n", 0b00001111);
			printCR0(getCR0());
			idt_t myThing;
			store_idt(&myThing);
			hPrint32(GDT_Descriptor);
			hPrintWord(myThing.length);

			//writeStringColor("\n", COLOR);
			//writeStringColor("IDT reg\n", COLOR);
			//hPrint32(getIDTreg());
                        //writeStringColor("\n", COLOR);
                        //writeStringColor("GDT reg\n", COLOR);
			//hPrint32(getGDTreg());

//			setVideoMode13();
//			for( int i = 0; i < 0xFFFF; i++ )  p[i] = 0b01011110;
//			putSprite(kirbo_48, 48, 48, 160, 100, 0xFF);
}
