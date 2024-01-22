#ifndef INCLUDE_DEBUG_UTILS_h_
#define INCLUDE_DEBUG_UTILS_h_

#include <logging/logging.h>



void regdump(void);
#define register_dump() \
  do {                    \
    __asm__ volatile(                               \
      "sub sp, #72;"                                \
      "stm sp, {r0-r12, r14};"                      \
      "mov r0, pc;"                                 \
      "sub r0, #10;"                                \
      "str r0, [sp, #56];"                          \
      "mov r0, sp;"                                 \
      "add r0, #72;"                                \
      "str r0, [sp, #60];"                          \
      "mrs r0, apsr;"                               \
      "str r0, [sp ,#64];"                          \
      "mrs r0, epsr;"                               \
      "str r0, [sp ,#68];"                          \
      "bl regdump;"                                 \
      "ldm sp, {r0-r12, r14};"                      \
      "add sp, #72;"                                \
      :                                             \
      :                                             \
      :                                             \
      );                                            \
    } while (0);


uint32_t *__stack_dump_sp;                        
uint32_t *__estack_dump_sp;

// print raw stack
// TODO: make sure register values are preserved after call
#define stack_dump(n_words) \
  do {                                              \
    __asm__ volatile(                                 \
        "mov %0, sp"                                  \
        : "=r" (__stack_dump_sp)                      \
        :                                             \
        :);                                            \
    __estack_dump_sp = __stack_dump_sp + (n_words);     \
    while (__stack_dump_sp != __estack_dump_sp) {      \
      printk("0x%x: 0x%x\r\n", __stack_dump_sp, *__stack_dump_sp) ; \
      ++__stack_dump_sp;                                \
    }                                                   \
  } while (0);

/*
uint32_t *__regdump_sp;
// subtracting 10 from pc, found experimentally


#define register_dump() \
  do {                                              \
  __asm__ volatile(                                 \
      "sub sp, #64;"                                \
      "stm sp, {r0-r12, r14};"                      \
      "mov r0, pc;"                                 \
      "sub r0, #10;"                                \
      "str r0, [sp, #56];"                          \
      "mov r0, sp;"                                 \
      "add r0, #64;"                                \
      "str r0, [sp, #60];"                          \
      :                                             \
      :                                             \
      : "memory", "r0");                            \
  __asm__ volatile(                                 \
      "mov %0, sp"                                  \
      : "=r" (__regdump_sp)                                   \
      :                                             \
      :);                                            \
  printk("r0: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r1: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r2: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r3: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r4: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r5: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r6: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r7: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r8: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r9: 0x%x\r\n", *__regdump_sp++);                      \
  printk("r10: 0x%x\r\n", *__regdump_sp++);                     \
  printk("r11: 0x%x\r\n", *__regdump_sp++);                     \
  printk("r12: 0x%x\r\n", *__regdump_sp++);                     \
  printk("r14: 0x%x\r\n", *__regdump_sp++);                     \
  printk("pc: 0x%x\r\n", *__regdump_sp++);                      \
  printk("sp: 0x%x\r\n", *__regdump_sp++);                      \
  __asm__ volatile(                                   \
      "ldm sp, {r0-r12, r14};"                        \
      "add sp, #64;"                                  \
      :                                               \
      :                                               \
      : "r0", "r1", "r2", "r3", "r4", "r5", "r6",          \
       "r7", "r8", "r9", "r10", "r11", "r12", "r14"   \
      );                                             \
  } while (0);
*/
#endif // DEBUG_UTILS_h_
