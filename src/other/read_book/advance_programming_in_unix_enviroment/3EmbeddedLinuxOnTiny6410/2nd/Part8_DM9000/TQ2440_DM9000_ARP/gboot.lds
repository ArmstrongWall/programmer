OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS {
	. = 0x30000000;
	
	. = ALIGN(4);
	.text :
	{
	start.o (.text)
	*(.text)
	}

	. = ALIGN(4);
	.data : 
	{
	*(.data)
	}
	
	. = ALIGN(4);
	bss_start = .;
	.bss : 
	{
	*(.bss) 
	}
	bss_end = .;
}
