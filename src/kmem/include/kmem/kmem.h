#ifndef INCLUDE_KMEM_h_
#define INCLUDE_KMEM_h_

#include <utils/types.h>

// 1 KB pages
#define PGSZ (1 << 10) 
#define FREEPGFILL 0x0badbeef

typedef struct list_head {
  struct list_head *next;
  struct list_head *prev;
} list_head_t;


typedef struct free_page_set {
  list_head_t pages;
  int n_pages;
} fpg_set_t;



int kmem_init(uint8_t *curr, uint8_t *end, uint32_t pgsz);
void *kzalloc();
void kfree(uint8_t *pg);


#endif // INCLUDE_KMEM_h_
