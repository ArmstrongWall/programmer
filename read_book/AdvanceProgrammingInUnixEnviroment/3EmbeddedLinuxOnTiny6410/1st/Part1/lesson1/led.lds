

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x50008000;

	. = ALIGN(4);
	.text :
	{
		led.o	(.text)
		*(.text)
	}

	. = ALIGN(4);
	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

	. = ALIGN(4);
	.data : { *(.data) }


	. = ALIGN(4);
	__bss_start = .;
	.bss (NOLOAD) : { *(.bss) . = ALIGN(4); }
	_end = .;
}
