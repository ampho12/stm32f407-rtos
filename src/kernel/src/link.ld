ENTRY(_reset)

MEMORY {
  flash(rx) : ORIGIN = 0x08000000, LENGTH = 2048k
  sram(rwx) : ORIGIN = 0x20000000, LENGTH = 64k
}

/* main stack is 4k */
__main_stack_sz = 0x1000 ;

_estack = ORIGIN(sram) + LENGTH(sram) ;
__heap_end = _estack - __main_stack_sz ;

SECTIONS {


  .vectors : {
    * ( .vectors )
  } > flash

  .text : {
    * ( .text* )
  } > flash

  .rodata : {
    * ( .rodata* )
  } > flash

  .data : {
    _data = . ;
    /* (.data) */
    *(.first_data)
    *(.data SORT(.data.*))
    _edata = . ;
  } > sram AT > flash
  _sidata = LOADADDR(.data) ;

  .bss : {
    _bss = . ;
    *(.bss SORT(.bss.*) COMMON)
    /* ( .bss ) */
    _ebss = . ;
  } > sram

  /* align to 4Kb for heap*/
  . = ALIGN(4096) ;
  __heap_begin = . ;

}


