OUTPUT_FORMAT(binary)

MEMORY{
	LOAD_AREA (rx) : ORIGIN = 0x401FF000, LENGTH = 1024
	RAM (rwx) : ORIGIN = 0x40001000, LENGTH = 16K
	}

REGION_ALIAS("REGION_TEXT", LOAD_AREA);
REGION_ALIAS("REGION_RODATA", LOAD_AREA);
REGION_ALIAS("REGION_DATA", LOAD_AREA);
REGION_ALIAS("REGION_BSS", RAM);

SEARCH_DIR(/home/jack/opt/cross/lib/gcc/m68k-elf/5.3.0/m68000);

SECTIONS{
	
	
	
	.text : {
		*(.text.init)
		*(.text)
	} > REGION_TEXT
	
	.rodata : {
		*(.rodata)
		*(.rodata.*)
	} > REGION_RODATA

	
	.data : {
		*(.data)
	} > REGION_DATA
	
	
	.bss : {
		*(.bss)
	} > REGION_BSS
	
	.filler : AT(0x401FF000+1023){
			BYTE(0);
		}
	
		
	
}
