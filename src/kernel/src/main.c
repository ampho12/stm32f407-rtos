#include <gpio/gpio.h>
#include <rcc/rcc.h>
#include <usart/usart.h>
#include <logging/logging.h>
#include <kmem/kmem.h>
#include <proc/proc.h>
#include <debug_utils/debug_utils.h>

// 10 found experimentally for stack adjustment

int putc(char c) {
  usart_write_byte(USART1, c);
  return 0;
}

int write_buf(const char *buf, uint32_t len) {
  return usart_write_buf(USART1, buf, len);
}


void delay(volatile uint32_t num) {
  while (num--) {
    asm volatile("nop");
  }
}

extern uint32_t _bss;
extern uint32_t _ebss;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _sidata;
extern void __heap_begin(void);
extern void __heap_end(void);

int this_in_bss = 0;


void 
memdump(uint32_t* start, uint32_t *end, int inc) {
  while (start != end) {
    printk("0x%x: 0x%x\r\n",
        start,
        *start);
    start += inc;
  }
}



// typedef struct proc_ctl_blk {
//   uint32_t *psp;
// } pcb_t;
// 
// pcb_t pcb_array[2];
// pcb_t *last_pcb;
// pcb_t *curr_pcb;
// int curr_pid;



struct systick {
  volatile uint32_t CTRL, LOAD, VAL, CALIB;
};
#define SYSTICK ((struct systick *) 0xe000e010)  // 2.2.2

static inline void systick_init(uint32_t ticks) {
  if ((ticks - 1) > 0xffffff) return;  // Systick timer is 24 bit
  SYSTICK->LOAD = ticks - 1;
  SYSTICK->VAL = 0;
  SYSTICK->CTRL = 0x7;  // Enable systick
  rcc_enable_clock(RCC_SYSCFG);
  // RCC->APB2ENR |= BIT(14);                   // Enable SYSCFG
}

static volatile uint32_t s_ticks = 0;
void SysTick_Handler(void) { 
  s_ticks++; 

  if (s_ticks % 5000 == 0) {
    // printk("register dump from systick handler\r\n");
    // register_dump();
    // printk("stack dump from systick handler\r\n");
    // stack_dump(10);

    
    // print out psp
    printk("psp dump from systick handler\r\n");
    uint32_t *psp;
    // uint32_t *psp;
    __asm__ volatile(
        "mrs %0, PSP"
        : "=r" (psp)
        :
        :);
    memdump(psp, psp + 12, 1);
    // printk("\r\n\n");

    // save a decremented psp to account for register
    // pcb_array[curr_pid].psp = psp - 8;

    // switch tasks
    pend_task_switch((curr_pid + 1) % 2);
  }
}



int timer_expired(uint32_t *t, uint32_t prd, uint32_t now) {
  if (now + prd < *t) *t = 0;                    // Time wrapped? Reset timer
  if (*t == 0) *t = now + prd;                   // Firt poll? Set expiration
  if (*t > now) return 0;                    // Not expired yet, return
  *t = (now - *t) > prd ? now + prd : *t + prd;  // Next expiration time
  return 1;                                   // Expired, return true
}


__attribute__ ((naked))
void task_idle(void) {

  while (1) {
    printk("task idle\r\n");
    __asm__ volatile(
        "mov r0, #0xca70;"
        "mov r1, #0xca71;"
        "mov r2, #0xca72;"
        "mov r3, #0xca73;"
        "mov r4, #0xca74;"
        "mov r5, #0xca75;"
        "mov r6, #0xca76;"
        "mov r8, #0xca78;"
        "mov r9, #0xca79;"
        "mov r10, #0xca7a;"
        :
        :
        : "r0", "r1", "r2", "r3", "r4",
          "r5", "r6", "r8", "r9", "r10"
        );
    // register_dump();
    // printk("\r\n\n");
    delay(5000000);
  }
}

__attribute__ ((naked))
void task1(void) {

  while (1) {
    printk("task one\r\n");
  __asm__ volatile(
      "mov r0, #0xfed0;"
      "mov r1, #0xfed1;"
      "mov r2, #0xfed2;"
      "mov r3, #0xfed3;"
      "mov r4, #0xfed4;"
      "mov r5, #0xfed5;"
      "mov r6, #0xfed6;"
      "mov r8, #0xfed8;"
      "mov r9, #0xfed9;"
      "mov r10, #0xfeda;"
      :
      :
      : "r0", "r1", "r2", "r3", "r4",
        "r5", "r6", "r8", "r9", "r10"
      );
    // register_dump();
    // printk("\r\n\n");
    delay(5000000);
  }
}





// void stack_dump(uint32_t n_words) {
//   uint32_t *__stack_dump_sp;                        
//   uint32_t *__estack_dump_sp;
//   __asm__ volatile(
//       "mov %0, sp"
//       : "=r" (__stack_dump_sp)
//       :
//       :);
//   __estack_dump_sp = __stack_dump_sp + (n_words);
//   while (__stack_dump_sp != __estack_dump_sp) {
//     printk("0x%x: 0x%x\r\n", 
//         __stack_dump_sp, 
//         *__stack_dump_sp++) ;
//   }
// }




int main(void) {

  usart_init(USART1, 115200, USART_8N1);


  // printk("STARTING PROGRAM\r\n");

  // register_dump();
  // // regdump();
  // printk("DONE DUMP\r\n");

  int ret;
  ret = kmem_init((uint8_t *) __heap_begin,
      (uint8_t *) __heap_end,
      PGSZ);

  printk("free 1KB pages in heap: %d\r\n", ret);

  create_and_add_task(task_idle);
  create_and_add_task(task1);

  // PRAY AND HOPE THAT WE DO NOT CALL SysTick_Handler 
  // BEFORE SWAPPING INTO IDLE TASK
  systick_init(16000000 / 1000);
  start_tasks();


  while (1);



  gpio_set_mode(PIN('A', 6), GPIO_MODE_GPOUTPUT);
  gpio_set_mode(PIN('A', 7), GPIO_MODE_GPOUTPUT);
  uint32_t timer = 0, period = 500;      // Declare timer and 500ms period



}





__attribute__((naked, noreturn))
void _reset(void) {

  // clear the bss, its just a bunch of zeros in sram
  uint8_t *byte = (uint8_t *) &_bss;
  while (byte < (uint8_t *) &_ebss) {
    *byte++ = 0;
  }

  // fill the heap with garbage
  for (uint32_t *hp = (uint32_t *) &__heap_begin;
       hp != (uint32_t *) &__heap_end;) {
    *hp++ = FREEPGFILL;
  }

  // copy data from flash to sram
  for (uint8_t *src = (uint8_t *) &_sidata,
       *dst = (uint8_t *) &_data;
       dst < (uint8_t *) &_edata;) {
    *dst++ = *src++;
  }


  main();
  while (1);
}



extern void _estack(void);

__attribute__((section(".vectors")))
void (*vectors[16 + 91])(void) = {
  [0] = _estack,
  [1] = _reset,
  [14] = PendSV_Handler,
  [15] = SysTick_Handler,
  
};
