#include "kmem/kmem.h"
#include <logging/logging.h>


static fpg_set_t fpgset = {0};
extern uint32_t __heap_begin;
extern uint32_t __heap_end;

int kmem_init(uint8_t *start, uint8_t *end, uint32_t pgsz) {



  list_head_t *curr = (list_head_t *) start;
  uint8_t *next = start + pgsz;
  int ret = 0;
  list_head_t *prev = 0x0;
  // check if we have at least 1 free page
  if (next > end) {
    // no free pages
    return ret;
  }

  // have at at least 1 free page
  fpgset.pages.next = curr;


  while (next <= end) {
    // current page is usable
    curr->next = (list_head_t *) next;
    curr->prev = prev;
    ++ret;

    // increment for next round
    prev = curr;
    curr = curr->next;
    next = (uint8_t *) curr + pgsz;
  }

  // prev is last page
  prev->next = 0x0;
  fpgset.pages.prev = prev;
  fpgset.n_pages = ret;

  // debug
  // list_head_t *head = fpgset.pages.next;
  // printk("free 1KB pages in heap: %d\r\n", fpgset.n_pages);
  // while (head) {
  //   printk("(%x)->next: %x\r\n",
  //       head,
  //       head->next);
  //   printk("(%x)->prev: %x\r\n",
  //       head,
  //       head->prev);
  //   printk("\r\n");
  //   head = head->next;
  // }

  return ret;
}


void kfree(uint8_t *pg) {
  

  // check alignment, and heap stuff
  if ((uint32_t) pg % PGSZ ||
      (uint32_t) pg < __heap_begin ||
      (uint32_t) pg > __heap_end) {
    // misaligned!
    printk("emerg: %s received bad address 0x%x\r\n",
        __func__,
        pg);

    // spin
    while (1);
  }

  // valid, we add to the free list
  // first we make sure memory is voided out
  uint32_t count = PGSZ / 4;
  uint32_t *s = (uint32_t *) pg;
  while (count--) {
    *s++ = FREEPGFILL;
  }

  // now add
  ((list_head_t *) pg)->next = fpgset.pages.next;
  ((list_head_t *) pg)->prev = 0x0;
  fpgset.pages.prev = (list_head_t *) pg;
  fpgset.pages.next = (list_head_t *) pg;
  ++fpgset.n_pages;

}

void *kzalloc() {
  // return a zeroed out page

  if (fpgset.n_pages == 0) {
    printk("error: %s out of pages\r\n",
        __func__);
    return 0x0;
  }

  // claim a page
  void *ret = (void *) fpgset.pages.next;
  fpgset.pages.next = fpgset.pages.next->next;
  fpgset.pages.next->prev = 0x0;
  fpgset.n_pages--;

  // zero it out
  uint32_t count = PGSZ / 4;
  uint32_t *s = (uint32_t *) ret;
  while (count--) {
    *s++ = 0x0;
  }

  // done
  return ret;
}


