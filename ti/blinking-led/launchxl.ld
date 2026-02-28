/* Linker Script for TMS570LC4357 */

MEMORY
{
    VECTORS (X)  : ORIGIN = 0x00000000, LENGTH = 0x00000020
    FLASH   (RX) : ORIGIN = 0x00000020, LENGTH = 0x003FFFE0
    SRAM    (RW) : ORIGIN = 0x08000000, LENGTH = 0x00080000
}

SECTIONS
{
    .intvecs : 
    { 
        KEEP(*(.intvecs)) 
    } > VECTORS

    .text : 
    { 
        *(.text*) 
        *(.rodata*) 
    } > FLASH

    .data : 
    { 
        _sdata = .;
        *(.data*)
        _edata = .;
    } > SRAM AT > FLASH

    .bss : 
    { 
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM

    /* Provide a symbol for the stack top */
    _stack_top = ORIGIN(SRAM) + LENGTH(SRAM);
}
