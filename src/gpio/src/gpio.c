#include "gpio/gpio.h"

// void gpio_set_mode2(gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_mode_t mode) {
// 
//   uint32_t src = ((uint32_t) (mode)) << (2 * pin);
//   uint32_t mask = ((uint32_t) (0x3)) << (2 * pin);
// 
//   // gpio->modeR &= ~(3u << (2 * pin));
//   // gpio->modeR |= (mode & 3u) << (2 * pin);
// 
//   gpio->modeR = replace_masked(gpio->modeR, src, mask);
// }
// 
// 
// void gpio_set_af2(gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_af_t af) {
//   
//   volatile uint32_t *dst = 
//     (pin >= 8) ? &gpio->afRH : &gpio->afRL;
// 
//   uint32_t src = ((uint32_t) (af)) << ((pin & 0x7) * 4);
//   uint32_t mask = ((uint32_t) (0xf)) << ((pin & 0x7) * 4);
// 
//   // gpio->afRL = replace_masked(gpio->afRL, src, mask);
//   *dst = replace_masked(*dst, src, mask);
//   // gpio->afRL &= ~mask;
//   // gpio->afRL |= src;
// 
// }
// 
// void gpio_set_otype(gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_otype_t otype) {
//   uint32_t src = ((uint32_t) (otype)) << (pin);
//   uint32_t mask = ((uint32_t) (0x1)) << (pin);
//   gpio->otypeR = replace_masked(gpio->otypeR, src, mask);
// }
// void gpio_set_pupd(gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_pupd_t pupd) {
// 
//   uint32_t src = ((uint32_t) (pupd)) << (2 * pin);
//   uint32_t mask = ((uint32_t) (0x3)) << (2 * pin);
//   gpio->pupdR = replace_masked(gpio->pupdR, src, mask);
// }
// 
// void gpio_set_od(gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_od_t od) {
//   uint32_t src = ((uint32_t) (od)) << (pin);
//   uint32_t mask = ((uint32_t) (0x1)) << (pin);
//   // gpio->odR = (od << pin);
//   gpio->odR = replace_masked(gpio->odR, src, mask);
// }
// 
// void gpio_set_bsrr(gpio_port_t *gpio,
//     uint32_t pin,
//     uint32_t val) {
// 
//   gpio->bsrR = (1u << pin) << (val? 0: 16);
// }



void gpio_set_mode(
    pin_t pin,
    gpio_mode_t mode) {

  gpio_port_t *gpio = GPIO_FROM_IDX(PORT_IDX(pin));
  uint32_t src = ((uint32_t) (mode)) << (2 * PIN_IDX(pin));
  uint32_t mask = ((uint32_t) (0x3)) << (2 * PIN_IDX(pin));

  // gpio->modeR &= ~(3u << (2 * pin));
  // gpio->modeR |= (mode & 3u) << (2 * pin);

  gpio->modeR = replace_masked(gpio->modeR, src, mask);
}


void gpio_set_af(
    pin_t pin,
    gpio_af_t af) {
  
  gpio_port_t *gpio = GPIO_FROM_IDX(PORT_IDX(pin));

  uint32_t src = 
    ((uint32_t) (af)) << (4 * (PIN_IDX(pin) & 0x7));

  uint32_t mask = 
    ((uint32_t) (0xf)) << (4 * (PIN_IDX(pin) & 0x7));

  gpio->afR[PIN_IDX(pin) >> 3] = 
    replace_masked(gpio->afR[PIN_IDX(pin) >> 3], src, mask);

}

void gpio_set_otype(
    pin_t pin,
    gpio_otype_t otype) {
  gpio_port_t *gpio = GPIO_FROM_IDX(PORT_IDX(pin));
  uint32_t src = ((uint32_t) (otype)) << (PIN_IDX(pin));
  uint32_t mask = ((uint32_t) (0x1)) << (PIN_IDX(pin));
  gpio->otypeR = replace_masked(gpio->otypeR, src, mask);
}

void gpio_set_pupd(
    uint32_t pin,
    gpio_pupd_t pupd) {

  gpio_port_t *gpio = GPIO_FROM_IDX(PORT_IDX(pin));
  uint32_t src = ((uint32_t) (pupd)) << (2 * PIN_IDX(pin));
  uint32_t mask = ((uint32_t) (0x3)) << (2 * PIN_IDX(pin));
  gpio->pupdR = replace_masked(gpio->pupdR, src, mask);
}

void gpio_set_od(
    uint32_t pin,
    gpio_od_t od) {
  gpio_port_t *gpio = GPIO_FROM_IDX(PORT_IDX(pin));
  uint32_t src = ((uint32_t) (od)) << (PIN_IDX(pin));
  uint32_t mask = ((uint32_t) (0x1)) << (PIN_IDX(pin));
  // gpio->odR = (od << pin);
  gpio->odR = replace_masked(gpio->odR, src, mask);
}

void gpio_set_bsrr(
    uint32_t pin,
    uint32_t val) {

  gpio_port_t *gpio = GPIO_FROM_IDX(PORT_IDX(pin));
  gpio->bsrR = (1u << PIN_IDX(pin)) << (val? 0: 16);
}


void gpio_pin_init(pin_config_t *pin_config) {
  gpio_set_mode(pin_config->pin, pin_config->gpio_mode);
  gpio_set_af(pin_config->pin, pin_config->gpio_af);
}

