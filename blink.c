#include <stdio.h>

#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"

#define DELAY_NUM 500000

// semihosting init function
extern void initialise_monitor_handles(void);

void delay(uint32_t div) {
  for (uint32_t i = 0; i < DELAY_NUM / div; i++)
    ;
}

int main(void) {
  initialise_monitor_handles();

  GPIO_Handle_t gpio_led;
  int toggle_count = 0;

  gpio_led.pGPIOx = GPIOA;
  gpio_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
  gpio_led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
  gpio_led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  gpio_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  gpio_led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPD_PU;

  GPIO_Init(&gpio_led);

  printf("Application is running...\n");

  for (;;) {
    GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_1);
    toggle_count++;
    printf("Toggle count: %d\n", toggle_count);
    delay(1);
  }
}
