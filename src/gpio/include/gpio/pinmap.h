#ifndef INCLUDE_PINMAP_h_
#define INCLUDE_PINMAP_h_

#include <utils/types.h>

#define PIN(port_letter, pin_idx) \
  ((pin_t) (((port_letter) - 'A') << 8) | ((pin_idx) & 0xff))

#define PORT_IDX(pin) ((pin) >> 8)
#define PIN_IDX(pin) ((pin) & 0xff)




#endif // INCLUDE_PINMAP_h_
