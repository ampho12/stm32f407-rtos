#ifndef INCLUDE_PROC_h_
#define INCLUDE_PROC_h_

#include <utils/types.h>

typedef struct proc_ctl_blk {
  uint32_t *psp;
} pcb_t;


#define NUM_MAX_PROC 10
#define DEFAULT_CPSR 0x01000000


extern int curr_pid;


void start_tasks(void);
void PendSV_Handler(void);
void create_and_add_task(void (*task)(void));
void pend_task_switch(int next_pid);



#endif // INCLUDE_PROC_h_
