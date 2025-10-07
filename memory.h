

typedef struct gdt_entry_s  {

	unsigned short limit_low;
	unsigned short base_low;    //and here. 
	unsigned char  base_middle; //24 bits for base here
	unsigned char  access;
	unsigned char  granularity; //plus last nible of limit.
	unsigned char  base_high;
} gdt_entry_t __attribute__((packed));

typedef struct gdt_ptr_s  {

	unsigned short limit;
	unsigned int   base;
} gdt_ptr_t __atribute__((packed));
