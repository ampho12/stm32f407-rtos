#include "rcc/rcc.h"

#include <utils/types.h>

void rcc_enable_clock(rcc_peripheral_t num) {

  uint8_t reg = num / 32;
  uint8_t shift = num % 32;

  switch (reg) {
    case 0:
      RCC->ahb1enR |= 1 << (shift);
    break;

    case 1:
      RCC->ahb2enR |= 1 << (shift);
    break;

    case 2:
      RCC->ahb3enR |= 1 << (shift);
    break;

    case 3:
      RCC->apb1enR |= 1 << (shift);
    break;

    case 4:
      RCC->apb2enR |= 1 << (shift);
    break;
  }
}


