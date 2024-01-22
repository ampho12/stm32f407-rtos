

#include <stdarg.h>
#include <utils/types.h>

#include "logging/logging.h"


char printk_buf[16];

__attribute__ ((format(printf, 1, 2)))
int printk(const char *fmt, ...) {

  va_list ptr;


  const char *tmp_fmt = fmt;
  uint32_t num_percs = 0;

  while (*tmp_fmt) {
    num_percs += (*tmp_fmt++) == '%';
  }

  va_start(ptr, num_percs);

  // uint32_t arg;
  uint32_t count;
  uint8_t scratch;
  

  while (*fmt) {

    if (*fmt != '%') {
      putc(*fmt++);
      continue;
    }

    fmt++;

    switch (*fmt) {
      case 'x': {
        // print hexadecimal
        uint32_t arg = va_arg(ptr, uint32_t);
        count = 8;
        while (count--) {
          scratch = arg & 0xf;
          // putc(scratch + '0');
          printk_buf[count] = (0x30 << (scratch >= 10))
            + (scratch >= 10)
            + scratch % 10;
          arg >>= 4;
        }
        write_buf(printk_buf, 8);
        break;
      }

      case 'd': {
        uint32_t arg = va_arg(ptr, int);
        if (arg >> 31) {
          putc('-');
          arg *= -1;
        }
        count = 10;
        do {
          --count;
          printk_buf[count] = '0' + arg % 10;
          arg /= 10;
        } while (arg);
        write_buf(printk_buf + count, 10 - count);
        
        break;
      }

      case 'u': {
        uint32_t arg = va_arg(ptr, int);
        count = 10;
        do {
          --count;
          printk_buf[count] = '0' + arg % 10;
          arg /= 10;
        } while (arg);
        write_buf(printk_buf + count, 10 - count);
        
        break;
      }
      case 's': {
        const char *arg = va_arg(ptr, const char *);
        while (*arg) putc(*arg++);
      }
      break;
      default:
      write_buf("__UNKNWN__", 10);
      break;
    }
    ++fmt;

  }
  va_end(ptr);

  return 0;
}
