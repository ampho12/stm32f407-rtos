#include "proc/proc.h"
#include <kmem/kmem.h>

static pcb_t pcb_array[NUM_MAX_PROC];

int curr_pid = 0;


__attribute__ ((used))
static pcb_t *curr_pcb = 0;

// compiler may omit this variable from symbol table
// if it thinks its not being used or can be optimized away
// the __attribute__((used)) tells compiler to keep it in 
// symbol table
__attribute__ ((used))
static pcb_t *last_pcb = 0;


/// creates a task and adds it
void create_and_add_task(void (*task)(void)) {
  static uint32_t pid = 0;
  // create psp 
  pcb_array[pid].psp = (uint32_t *) 
    ((char *) kzalloc() + PGSZ);
  // setup psp stack frame
  // cpsr
  // pc
  // lr
  // r12
  // r3
  // r2
  // r1
  // r0

  *(--pcb_array[pid].psp) = (uint32_t) DEFAULT_CPSR;
  *(--pcb_array[pid].psp) = (uint32_t) task;
  // skip over rest of stack frame
  pcb_array[pid].psp -= 6;

  // stack frame has r0, r1, r2, r3, r12, r14 (lr)
  // we also restore r13 (sp) and r15 (pc)
  // thus, r4 through r11 are not saved
  // we save them as 0 to begin with
  pcb_array[pid].psp -= 8;
  ++pid;

}


// starts task 0 from main mode
// NOTE naked attribute used with extended inline assembly
// may not always work!! check generated assembly
__attribute__ ((naked))
void start_tasks(void) {

  curr_pid = 0;
  curr_pcb = &pcb_array[curr_pid];
  uint32_t *psp = pcb_array[curr_pid].psp;
  
  // skip over r4 through r11
  psp += 8;
  // skip over stack frame, right at pc
  psp += 6;
  __asm__ volatile(
      // switch to psp
      "msr PSP, %0;"
      "mov  r2, $0x2;"
      "msr  CONTROL, r2;"
      // get pc
      "pop {r1};"
      // get cpsr, throw it away
      "pop {r2};"
      // switch to non privileged mode
      "mov  r2, $0x3;"
      "msr  CONTROL, r2;"
      // we now have psp in non privilege mode
      // and we have new msp insalled for this task
      // push pc and return to it (i.e return to task)
      "push {r1};"
      "pop {pc};"
      :
      : "r" (psp)
      : "r1", "r2"
      );
}


void pend_task_switch(int next_pid) {

  curr_pid = next_pid;
  last_pcb = curr_pcb;
  curr_pcb = &pcb_array[curr_pid];

  // pend the PendSV exception
  // At reset, all priorities are 0 (except, reset, NMI, and 
  // Hardfault). A pending interrupt with same priority
  // level stays pending and does not preempt
  volatile uint32_t *icsr = (void *)0xE000ED04;
  // Pend a PendSV exception using by writing 1 to PENDSVSET at bit 28
  *icsr = 0x1 << 28;
  // the PendSV_Handler will do the process switch
}


/// actual task switch
__attribute__ ((naked, noinline))
void PendSV_Handler(void) {
  __asm__ volatile(
      "push {lr};"

      // first we save r4-r11 on current psp
      // 1. get psp
      "mrs r0, PSP;"
      // 2. store registers
      "stmdb r0!, {r4-r11};"

      // now we save the current psp on last_pcb
      "ldr r1, =last_pcb;"
      "ldr r1, [r1, #0];"
      "str r0, [r1, #0];"

      // get the psp from the curr_pcb
      "ldr r1, =curr_pcb;"
      "ldr r1, [r1, #0];"
      "ldr r0, [r1, #0];"

      // reload registers
      "ldmia r0!, {r4-r11};"
      // change psp
      "msr PSP, r0;"
      // return
      "pop {pc};"
      );
}

