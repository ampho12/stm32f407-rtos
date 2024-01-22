#ifndef INCLUDE_USART_h_
#define INCLUDE_USART_h_

#include <utils/types.h>
#include <rcc/rcc.h>
#include <gpio/gpio.h>

typedef enum usart_sr_bits {
  // USART SR Register, offset 0x0
  /// Parity Error. only readable
  /// Set By HW when parity error occurs in receiver mode
  /// Cleared by SW with the following sequence
  /// 1. Read from status register
  /// 2. Read or write access to USART_DR register
  USART_PE = 0x0, 
  USART_FE,
  USART_NF,
  USART_ORE,
  USART_IDLE,
  USART_RXNE,
  USART_TC,
  USART_TXE,
  USART_LBD,
  USART_CTS,
} usart_sr_bit_t;


typedef enum usart_cr1_bits {
  USART_SBK,
  USART_RWU,
  USART_RE,
  USART_TE,
  USART_IDLEIE,
  USART_RXNEIE,
  USART_TCIE,
  USART_TXEIE,
  USART_PEIE,
  USART_PS,
  USART_PCE,
  USART_WAKE,
  USART_M,
  USART_UE,
  USART_OVER8 = 15,
} usart_cr1_bit_t;

typedef enum usart_cr2_bits {
  ADD_0 = 0,
  ADD_1,
  ADD_2,
  ADD_3,
  LBDL = 5,
  LBDIE,
  LBCL = 8,
  CPHA,
  CPOL,
  CLKEN,
  STOP_0,
  STOP_1,
  LINEN,
} usart_cr2_bits_t;


typedef enum usart_cr3_bits {
  EIE,
  IREN,
  IRLP,
  HDSEL,
  NACK,
  SCEN,
  DMAR,
  DMAT,
  RTSE,
  CTSE,
  CTSIE,
  ONEBIT,
} usart_cr3_bits_t;



typedef enum usart_config {
  USART_8N1,
} usart_config_t;




/// TODO add brief description for each register
typedef struct usart_regs {
  volatile uint32_t sR;
  volatile uint32_t dR;
  volatile uint32_t brR;
  volatile uint32_t cR1;
  volatile uint32_t cR2;
  volatile uint32_t cR3;
  volatile uint32_t gtpR;
} usart_regs_t;


typedef struct usart_device {
  rcc_peripheral_t rcc_gpio;
  rcc_peripheral_t rcc_usart;
  usart_regs_t *regs;
  pin_config_t rx_config;
  pin_config_t tx_config;
  uint32_t baud_rate;

} usart_dev_t;




#define USART_CLK 16000000

#define USART1_ADDR 0x40011000
#define USART6_ADDR 0x40011400

#define USART2_ADDR 0x40004400
#define USART3_ADDR 0x40004800
#define UART4_ADDR 0x40004c00
#define UART5_ADDR 0x40005000

#define UART7_ADDR 0x40007800
#define UART8_ADDR 0x40007c00


extern usart_dev_t usart_dev1;
extern usart_dev_t usart_dev2;

#define USART1 (&usart_dev1)
#define USART2 (&usart_dev2)

// int usart_setup(usart_t *usart_port,
//     uint32_t baud_rate,
//     usart_config_t usart_config);

int usart_init(usart_dev_t *usart,
    uint32_t baud_rate,
    usart_config_t usart_config);

// int usart_write(usart_t *usart_port, uint8_t byte);
void usart_write_byte(usart_dev_t *usart, uint8_t byte);
int usart_write_buf(usart_dev_t *usart,
    const char *buf,
    uint32_t len);


#endif // INCLUDE_USART_h_

