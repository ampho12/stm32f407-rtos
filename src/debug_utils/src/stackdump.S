
  .section ".data.stackdump_str"
  .global "stackdump_str"
stackdump_str:
  .ascii "0x%x: 0x%x\r\n"


  .section ".text.stackdump"
  .global "stackdump"
  .extern "printk"
stackdump:
  // expect r0 to hold number of stack lines to print
  // save registers on stack
  push {r1, r2} 
  mov r1, sp
  // adjust stack since we pushed registers onto it
  add r1, #12

1:
  cmp r0, #0
  bne 2f
  ldr r2, [r1, #0]
  push {r0, r1}
  bl  printk
  pop {r0, r1}
  sub r0, #1
  add r1, #4
  b 1b
2:
  pop {



