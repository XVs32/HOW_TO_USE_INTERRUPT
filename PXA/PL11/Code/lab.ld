OUTPUT_ARCH(arm)
ENTRY(_reset_entry)

SECTIONS
{
	.text 0xa0000000 : {		/* Real text segment		*/
		_text = .;		/* Text and read-only data	*/
		*(.vector)					
		*(.stext)    
		*(.mmulib)
		*(.text)
		*(.rodata)
		. = ALIGN(4);
		_etext = .;		/* End of text section		*/
	}

	.data : {
		_sdata = .;
		*(.data)
        *(.dtors)		
        *(.ctors)			
		. = ALIGN(4);
		_edata = .;
	}

	.bss : {
		_sbss = .;		/* BSS				*/
		*(.bss)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	}
	
	_end = .;
	
	.stack 0xa4000000 : {
		_USR_STACK = .;                  /* STACK			*/		
		_IRQ_STACK = . - 0x1000;	
		_FIQ_STACK = . - 0x2000;
		__stack_limit = . - 0x1000;
	}
}
