#ifndef INCLUDE_LOGGING_h_
#define INCLUDE_LOGGING_h_

#include <utils/types.h>


__attribute__ ((format(printf, 1, 2)))
int printk(const char *fmt, ...);

int putc(char c);
int write_buf(const char *str, uint32_t len);



#endif // INCLUDE_LOGGING_h_
