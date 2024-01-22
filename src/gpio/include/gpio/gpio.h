#ifndef INCLUDE_GPIO_h_
#define INCLUDE_GPIO_h_


#include <utils/types.h>
// #include <rcc/rcc.h>

#include "gpio/pinmap.h"


/// structure to represent a single GPIO port (GPIOA, GPIOB, etc)
typedef struct gpio_port {
  volatile uint32_t modeR;
  volatile uint32_t otypeR;
  volatile uint32_t ospeedR;
  volatile uint32_t pupdR;
  volatile uint32_t idR;
  volatile uint32_t odR;
  volatile uint32_t bsrR;
  volatile uint32_t lckR;
  volatile uint32_t afR[2];
} gpio_port_t;


/// enum to represent modes gpio modes
typedef enum gpio_mode_type {
  GPIO_MODE_INPUT = 0x0,
  GPIO_MODE_GPOUTPUT= 0x1,
  GPIO_MODE_AF = 0x2,
  GPIO_MODE_ANALOG = 0x3,
} gpio_mode_t;

typedef enum gpio_output_type {
  GPIO_OTYPE_PP = 0x0,
  GPIO_OTYPE_OD,
} gpio_otype_t;

typedef enum gpio_pupd_type {
  GPIO_PUPD_NONE = 0x0,
  GPIO_PUPD_PULLUP,
  GPIO_PUPD_PULLDOWN,
  GPIO_PUPD_RESERVED,
} gpio_pupd_t;

typedef enum gpio_output_data_type {
  GPIO_OD_LOW = 0x0,
  GPIO_OD_HIGH = 0x1,
} gpio_od_t;

typedef enum gpio_bsrr_type {
  GPIO_BSRR_LOW = 0x0,
  GPIO_BSRR_HIGH = 0x1,
} gpio_bsrr_t;

typedef enum gpio_af_type {
  GPIO_AF_SYSTEM = 0,
  GPIO_AF_TIM1_2,
  GPIO_AF_TIM3_5,
  GPIO_AF_TIM8_11,
  GPIO_AF_I2C1_3,
  GPIO_AF_SPI1_2,
  GPIO_AF_SPI3,
  GPIO_AF_USART1_3,
  GPIO_AF_USART4_6,
  GPIO_AF_CAN1_2TIM12_14,
  GPIO_AF_OTGHS_FS,
  GPIO_AF_ETH,
  GPIO_AF_DCMI,
  GPIO_AF_NONE,
  GPIO_AF_EVENTOUT,
} gpio_af_t;

// void gpio_set_mode2(
//     gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_mode_t mode);
// 
// void gpio_set_af2(
//     gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_af_t af);
// 
// void gpio_set_otype(
//     gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_otype_t otype);
// 
// void gpio_set_pupd(
//     gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_pupd_t pupd);
// 
// void gpio_set_od(
//     gpio_port_t *gpio,
//     uint32_t pin,
//     gpio_od_t od);
// 
// void gpio_set_bsrr(
//     gpio_port_t *gpio,
//     uint32_t pin,
//     uint32_t val);

// all the peripherals need the gpio in some configuration
// thus we define a common structure that contains this
// config that can be embedded / used
// assume single port

typedef struct pin_config {
  pin_t pin;
  gpio_mode_t gpio_mode;
  gpio_af_t gpio_af;
} pin_config_t;








void gpio_set_mode(
    pin_t pin,
    gpio_mode_t mode);

void gpio_set_af(
    pin_t pin,
    gpio_af_t af);

void gpio_set_otype(
    pin_t pin,
    gpio_otype_t otype);

void gpio_set_pupd(
    pin_t pin,
    gpio_pupd_t pupd);

void gpio_set_od(
    pin_t pin,
    gpio_od_t od);

void gpio_set_bsrr(
    pin_t pin,
    uint32_t val);


void gpio_pin_init(pin_config_t *pin_config);















#define GPIO_BASE 0x40020000
#define GPIO_FROM_IDX(port_idx) \
  ((gpio_port_t *) (GPIO_BASE + (port_idx) * 0x400))
#define GPIO_FROM_LETTER(port_letter) \
  GPIO_FROM_IDX((port_letter) - 'A')





#endif // INCLUDE_GPIO_h_
