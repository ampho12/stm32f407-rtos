#ifndef INCLUDE_I2C_h_
#define INCLUDE_I2C_h_


















typedef struct i2c_regs {

  volatile uint32_t cR1;
  volatile uint32_t cR2;
  volatile uint32_t oaR1;
  volatile uint32_t oaR2;

  volatile uint32_t dR;
  volatile uint32_t sR1;
  volatile uint32_t sR2;
  volatile uint32_t ccR;

  volatile uint32_t trise;
  volatile uint32_t fltr;

} i2c_regs_t;

typedef struct i2c_device {
  rcc_peripheral_t rcc_gpio;
  rcc_peripheral_t rcc_i2c;
  i2c_regs *regs;
  pin_config_t sda_config;
  pin_config_t scl_config;

} i2c_dev_t;









#endif // INCLUDE_I2C_h_
