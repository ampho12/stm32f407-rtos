#ifndef INCLUDE_RCC_h_
#define INCLUDE_RCC_h_


#include <utils/types.h>


/// since STM32F4 is based on ARM cortex M, it uses 
/// ARM Advanced Microntroller Bus Architecture
/// AMBA1: Advanced System Bus (ASB) and Advanced Peripheral Bus (APB)
/// AMBA2: Added AMBA High-performance Bus (AHB)
/// AMBA3: Added Advanced eXtensible Interface (AXI) and Advaned Trace Bus (ATB)
/// AMBA4: AMBA-4 AXI4 and AMBA-4 AXI Coherence Extension (ACE)
/// AMBA5: Coherent Hub Interface (CHI)

typedef struct reset_clk_cntl {
  uint32_t cR; // clock control register
  uint32_t pllcfgR; // PLL config register 
  uint32_t cfgR; // clock config register
  uint32_t ciR; // clock interrupt register 

  // peripheral reset registers
  uint32_t ahb1rstR; // GPIO A through I, DMA1, DMA2, Ethernet MAC, USB OTG HS
  uint32_t ahb2rstR; // DCMI (Camera), Crypto module, hash module, random num (rng) module, USB OTG FS
  uint32_t ahb3rstR; // Flexible Static Memory Controller (FSMC) module
  uint32_t reserved1;
  uint32_t apb1rstR; // Timers 2 through 7, Timers 12 through 14, window watchdog, spi2, spi3, usart 2 through 5, i2c 1 through 3, CAN1, CAN2, power interface, dac
  uint32_t apb2rstR; // Timer1, TIM8, USART1, USART6, ADC, SDIO, SPI1, system configuration controller, TIM 9 through 11)
  uint32_t reserved2;
  uint32_t reserved3;

  // peripheral clock enable registers - enables clock for that particular peripheral
  uint32_t ahb1enR; 
  uint32_t ahb2enR;
  uint32_t ahb3enR;
  uint32_t reserved4;
  uint32_t apb1enR;
  uint32_t apb2enR;
  uint32_t reserved5;
  uint32_t reserved6;

  // peripheral clock enable, in low pwer mode register
  uint32_t ahb1lpenR;
  uint32_t ahb2lpenR;
  uint32_t ahb3lpenR;
  uint32_t reserved7;
  uint32_t apb1lpenR;
  uint32_t apb2lpenR;
  uint32_t reserved8;
  uint32_t reserved9;

  /// backup domain control register: 
  uint32_t bdcR;
  /// clock control and status register
  uint32_t csR;
  
  uint32_t reserved10;
  uint32_t reserved11;
  /// spread specturl clock generator register 
  uint32_t sscgR;
  /// PLLI2S configuration register
  uint32_t plli2scfgR;

} rcc_t;

typedef enum rcc_peripheral_offsets {
  // ahb1
  RCC_GPIOA = 0x0,
  RCC_GPIOB,
  RCC_GPIOC,
  RCC_GPIOD,
  RCC_GPIOE,
  RCC_GPIOF,
  RCC_GPIOG,
  RCC_GPIOH,
  RCC_GPIOI,
  RCC_DMA1 = 21,
  RCC_DMA2,
  RCC_ETHMAC = 25,
  RCC_OTGHS = 29,

  // ahb2
  RCC_DCMI = 32 + 0,
  RCC_CRYP = 32 + 4,
  RCC_HASH,
  RCC_RNG,
  RCC_OTG_FS,

  // ahb3
  RCC_FSMC = 64,

  // apb1
  RCC_TIM2 = 96,
  RCC_TIM3,
  RCC_TIM4,
  RCC_TIM5,
  RCC_TIM6,
  RCC_TIM7,
  RCC_TIM12,
  RCC_TIM13,
  RCC_TIM14,
  RCC_WWDG = 96 + 11, // window watchdog
  RCC_SPI2 = 96 + 14,
  RCC_SPI3,
  RCC_USART2 = 96 + 17,
  RCC_USART3,
  RCC_USART4,
  RCC_USART5,
  RCC_I2C1,
  RCC_I2C2,
  RCC_I2C3,
  RCC_CAN1 = 96 + 25,
  RCC_CAN2,
  RCC_PWR = 96 + 28,
  RCC_DAC = 96 + 29,

  // apb2 
  RCC_TIM1 = 128 + 0,
  RCC_TIM8,
  RCC_USART1 = 128 + 4,
  RCC_USART6,
  RCC_ADC = 128 + 8,
  RCC_SDIO = 128 + 11,
  RCC_SPI1,
  RCC_SYSCFG = 128 + 14,
  RCC_TIM9 = 128 + 16,
  RCC_TIM10,
  RCC_TIM11,
} rcc_peripheral_t;


#define RCC_BASE 0x40023800
#define RCC ((rcc_t *) RCC_BASE)





void rcc_enable_clock(rcc_peripheral_t num);


// typedef enum rcc_ahb1 {
//   RCC_GPIOA = 0x0,
//   RCC_GPIOB,
//   RCC_GPIOC,
//   RCC_GPIOD,
//   RCC_GPIOE,
//   RCC_GPIOF,
//   RCC_GPIOG,
//   RCC_GPIOH,
//   RCC_GPIOI,
//   RCC_DMA1 = 21,
//   RCC_DMA2,
//   RCC_ETHMAC = 25,
//   RCC_OTGHS = 29,
// } rcc_ahb1_offset;
// 
// typedef enum rcc_ahb2 {
//   RCC_DCMI = 0,
//   RCC_CRYP = 4,
//   RCC_HASH,
//   RCC_RNG,
//   RCC_OTG_FS,
// } rcc_ahb2_offset;
// 
// 
// 
// typedef enum rcc_ahb3 {
//   RCC_FSMC,
// } rcc_ahb3_offset;
// 
// typedef enum rcc_apb1 {
//   RCC_TIM2 = 0,
//   RCC_TIM3,
//   RCC_TIM4,
//   RCC_TIM5,
//   RCC_TIM6,
//   RCC_TIM7,
//   RCC_TIM12,
//   RCC_TIM13,
//   RCC_TIM14,
//   RCC_WWDG = 11, // window watchdog
//   RCC_SPI2 = 14,
//   RCC_SPI3,
//   RCC_USART2 = 17,
//   RCC_USART3,
//   RCC_USART4,
//   RCC_USART5,
//   RCC_I2C1,
//   RCC_I2C2,
//   RCC_I2C3,
//   RCC_CAN1 = 25,
//   RCC_CAN2,
//   RCC_PWR = 28,
//   RCC_DAC = 29,
// } rcc_apb1_offset;
// 
// 
// typedef enum rcc_apb2 {
//   RCC_TIM1 = 0,
//   RCC_TIM8,
//   RCC_USART1 = 4,
//   RCC_USART6,
//   RCC_ADC = 8,
//   RCC_SDIO = 11,
//   RCC_SPI1,
//   RCC_SYSCFG = 14,
//   RCC_TIM9 = 16,
//   RCC_TIM10,
//   RCC_TIM11,
// } rcc_apb2_offset;

#endif // INCLUDE_RCC_h_
