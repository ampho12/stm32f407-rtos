
  .section ".text.regdump", "x"
  .global "regdump"
  .extern printk
regdump:
  ldr r4, =regdump_strings
  mov r5, sp
  push {lr}
  // we have 16 registers
  mov r6, #16
1:
  sub r6, #1
  mov r0, r4
  ldr r1, [r5]
  // print, also overwrites lr
  bl printk
  // prep for next iteration
  // increment address on stack
  add r5, #4
  // increment address of string
  add r4, #12
  cmp r6, #0
  bne 1b

  // print out status registers
  mov r6, #2
2:
  sub r6, #1
  mov r0, r4
  ldr r1, [r5]
  // print, also overwrites lr
  bl printk
  // prep for next iteration
  // increment address on stack
  add r5, #4
  // increment address of string
  add r4, #13
  cmp r6, #0
  bne 2b
  pop {pc}

regdump_strings:
// all strings are same length for simplicity
// length of each string: 12 bytes
  .asciz "r00: 0x%x\r\n"
  .asciz "r01: 0x%x\r\n"
  .asciz "r02: 0x%x\r\n"
  .asciz "r03: 0x%x\r\n"
  .asciz "r04: 0x%x\r\n"
  .asciz "r05: 0x%x\r\n"
  .asciz "r06: 0x%x\r\n"
  .asciz "r07: 0x%x\r\n"
  .asciz "r08: 0x%x\r\n"
  .asciz "r09: 0x%x\r\n"
  .asciz "r10: 0x%x\r\n"
  .asciz "r11: 0x%x\r\n"
  .asciz "r12: 0x%x\r\n"
  .asciz "r14: 0x%x\r\n"
  .asciz "_pc: 0x%x\r\n"
  .asciz "_sp: 0x%x\r\n"
// length of each string: 13 bytes
  .asciz "apsr: 0x%x\r\n"
  .asciz "epsr: 0x%x\r\n"
  
  
