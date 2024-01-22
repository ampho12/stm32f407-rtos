#include "usart/usart.h"

#include <utils/types.h>
#include <rcc/rcc.h>
#include <gpio/gpio.h>

// int usart_setup(usart_t *usart_port,
//     uint32_t baud_rate,
//     usart_config_t usart_config) {
// 
//   
//   // enable gpio, needed to make tx and rx work!!
//   rcc_enable_clock(RCC_GPIOA);
//   rcc_enable_clock(RCC_USART2);
//   // RCC->apb1enR |= 1 << 17;
//   // gpio_port_t *gpioA = (gpio_port_t *) GPIO_FROM_IDX(0);
//   // gpio_set_mode2(gpioA, 2, GPIO_MODE_AF);
//   // gpio_set_af2(gpioA, 2, GPIO_AF_USART1_3);
//   // gpio_set_mode2(gpioA, 3, GPIO_MODE_AF);
//   // gpio_set_af2(gpioA, 3, GPIO_AF_USART1_3);
// 
//   gpio_set_mode(PIN('A', 2), GPIO_MODE_AF);
//   gpio_set_af(PIN('A', 2), GPIO_AF_USART1_3);
//   gpio_set_mode(PIN('A', 3), GPIO_MODE_AF);
//   gpio_set_af(PIN('A', 3), GPIO_AF_USART1_3);
// 
//   usart_port->cR1 = 0;
//   usart_port->brR = USART_CLK / baud_rate;
//   usart_port->cR1 |= (1 << USART_UE) 
//     | (1 << USART_TE)
//     | (1 << USART_RE);
// 
//   return 0;
// }
// 

usart_dev_t usart_dev1 = {
  .rcc_gpio = RCC_GPIOA,
  .rcc_usart = RCC_USART1,
  .regs = (usart_regs_t *) USART1_ADDR,
  .tx_config = {
    .pin = PIN('A', 9),
    .gpio_mode = GPIO_MODE_AF,
    .gpio_af = GPIO_AF_USART1_3,
  },
  .rx_config = {
    .pin = PIN('A', 10),
    .gpio_mode = GPIO_MODE_AF,
    .gpio_af = GPIO_AF_USART1_3,
  },
};

usart_dev_t usart_dev2 = {
  .rcc_gpio = RCC_GPIOA,
  .rcc_usart = RCC_USART2,
  .regs = (usart_regs_t *) USART2_ADDR,
  .tx_config = {
    .pin = PIN('A', 2),
    .gpio_mode = GPIO_MODE_AF,
    .gpio_af = GPIO_AF_USART1_3,
  },
  .rx_config = {
    .pin = PIN('A', 3),
    .gpio_mode = GPIO_MODE_AF,
    .gpio_af = GPIO_AF_USART1_3,
  },
};



int usart_init(usart_dev_t *usart,
    uint32_t baud_rate,
    usart_config_t usart_config) {
  
  // enable gpio, needed to make tx and rx work!!
  rcc_enable_clock(usart->rcc_usart);
  rcc_enable_clock(usart->rcc_gpio);

  // configure rx and tx gpio
  gpio_pin_init(&usart->rx_config);
  gpio_pin_init(&usart->tx_config);

  // setup registers
  usart->regs->cR1 = 0;
  usart->regs->brR = USART_CLK / baud_rate;
  usart->regs->cR1 |= (1 << USART_UE) 
    | (1 << USART_TE)
    | (1 << USART_RE);

  return 0;
}

void usart_write_byte(usart_dev_t *usart, uint8_t byte) {
  usart->regs->dR = byte;
  // wait for value to move into shift register
  while ((usart->regs->sR & (1 << USART_TXE)) == 0) ;
}

int usart_write_buf(usart_dev_t *usart, 
    const char *buf, 
    uint32_t len) {

  int ret = 0;
  while (*buf && len--) {
    usart_write_byte(usart, *buf++);
    ++ret;
  }
  return ret;
}


// int usart_write(usart_t *usart_port, uint8_t byte) {
//   usart_port->dR = byte;
// 
//   // wait for data to be moved to shift register
//   while ((usart_port->sR & (1 << USART_TXE)) == 0) {
//     // gpio_set_od(gpioA, 6, GPIO_OD_HIGH);
//     // delay(1);
//   }
// 
//   // gpio_set_od(gpioA, 6, GPIO_OD_LOW);
//   // we could wait for data to be transmitted, but we will
//   // trust the hardware to do that successfully!
//   return 0;
// }
