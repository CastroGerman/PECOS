/* Entry Point */
ENTRY(VarianTheFirst)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM); /* end of "RAM" Ram type memory */

_Min_Heap_Size = 0x200 ; /* required amount of heap */
_Min_Stack_Size = 0x400 ; /* required amount of stack */

/* Memories Definitions */
MEMORY
{
    CCMRAM (xrw): ORIGIN = 0x10000000, LENGTH = 64K
    RAM (xrw): ORIGIN = 0x20000000, LENGTH = 2048K
    FLASH (rx): ORIGIN = 0x08000000, LENGTH = 2048K
    VARIAN (rx): ORIGIN = 0x08100000, LENGTH = 64K
    ANDUIN (rx): ORIGIN = 0x18200000, LENGTH = 64K
}

/* Section Definitions */
SECTIONS
{
    .sec_VarianTheFirst :
    {
        . = ALIGN(4);
        *(.sec_VarianTheFirst)
        . = ALIGN(4);
    } > VARIAN

    .sec_AnduinTheSecond :
    {
        . = ALIGN(4);
        *(.sec_AnduinTheSecond)
        . = ALIGN(4);
    } > ANDUIN

    /* The program code and other data into "FLASH" Rom type memory */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
        _etext = .;  
    } > FLASH

    /* Constant data into "FLASH" Rom type memory */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)         /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
        . = ALIGN(4);
    } > FLASH

    /* Uninitialized data section into "RAM" Ram type memory */
    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = .;         /* define a global symbol at bss start */
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;         /* define a global symbol at bss end */
    } > RAM

    .data :
    {
        . = ALIGN(4);
        _sdata = .;        /* create a global symbol at data start */
        *(.data)           /* .data sections */
        *(.data*)          /* .data* sections */
        *(.RamFunc)        /* .RamFunc sections */
        *(.RamFunc*)       /* .RamFunc* sections */
        . = ALIGN(4);
        _edata = .;        /* define a global symbol at data end */
    } > RAM AT > FLASH
  
    /* User_heap_stack section, used to check that there is enough "RAM" Ram  type memory left */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } > RAM

    /* stack section */
    /*.stack (NOLOAD):
    {
        . = ALIGN(8);
        . = . + STACK_SIZE;
        . = ALIGN(8);
    } > RAM*/
    
    _end = . ;
}