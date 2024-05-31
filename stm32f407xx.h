/*
 * stm32f407xx.h
 *
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define _reg volatile uint32_t

/*
 * Memory base addresses
 */
#define FLASH_BASE_ADDR 0x08000000u // main memory base address
#define SRAM1_BASE_ADDR 0x20000000u // sram1 base address
#define SRAM2_BASE_ADDR 0x2001C000u // sram2 base address
#define ROM_BASE_ADDR 0x1fff0000u   // system memory base address
#define SRAM SRAM1_BASE_ADDR

/*
 * AHBx and APBx base addresses
 */
#define PERI_BASE_ADDR 0x40000000u
#define APB1_BASE_ADDR PERI_BASE_ADDR
#define APB2_BASE_ADDR 0x40010000u
#define AHB1_BASE_ADDR 0x40020000u
#define AHB2_BASE_ADDR 0x50000000u

#define GPIOA_BASE_ADDR (AHB1_BASE_ADDR + 0x0000u)

#define RCC_BASE_ADDR (AHB1_BASE_ADDR + 0x3800u)

// See GPIO register map
typedef struct GPIO_RegDef_t {
  _reg MODER;   // mode register
  _reg OTYPER;  // output type register
  _reg OSPEEDR; // output speed register
  _reg PUPDR;   // pull-up/pull-down register
  _reg IDR;     // input data register
  _reg ODR;     // output data register
  _reg BSRR;    // bit set/reset register
  _reg LCKR;    // configuration lock register
  _reg AFR[2];  // alternate function register
} GPIO_RegDef_t;

// See RCC register map
typedef struct RCC_RegDef_t {
  _reg CR;
  _reg PLLCFGR;
  _reg CFGR;
  _reg CIR;
  _reg AHB1RSTR;
  _reg AHB2RSTR;
  _reg AHB3RSTR;
  uint32_t _res1; // reserved
  _reg APB1RSTR;
  _reg APB2RSTR;
  uint32_t _res2[2]; // reserved
  _reg AHB1ENR;
  _reg AHB2ENR;
  _reg AHB3ENR;
  uint32_t __res3; // reserved
  _reg APB1ENR;
  _reg APB2ENR;
  uint32_t __res4[2]; // reserved
  _reg AHB1LPENR;
  _reg AHB2LPENR;
  _reg AHB3LPENR;
  uint32_t __res5; // reserved
  _reg APB1LPENR;
  _reg APB2LPENR;
  uint32_t __res6[2]; // reserved
  _reg BCDR;
  _reg CSR;
  uint32_t __res7[2];
  _reg SSCGR;
  _reg PLLI2CFGR;
} RCC_RegDef_t;

/*
 * Peripheral definitions
 */

#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASE_ADDR)
#define RCC ((RCC_RegDef_t *)RCC_BASE_ADDR)

/*
 * Clock enable macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1 << 0x0u))

/*
 * Clock disable macros for GPIOx peripherals
 */
#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 0x0u))

/*
 * Register reset macros. Works by setting the reset register to 1 and then back
 * to zero. Use "do while condition zero" to execute multiple statements.
 */
#define GPIOA_REG_RESET()                                                      \
  do {                                                                         \
    (RCC->AHB1RSTR |= (1 << 0));                                               \
    (RCC->AHB1RSTR &= ~(1 << 0));                                              \
  } while (0)

#endif /* INC_STM32F407XX_H_ */
