#include <stdio.h>

#include "stm32f407xx.h"

#define DELAY_NUM 500000

// semihosting init function
extern void initialise_monitor_handles(void);

void delay(uint32_t div) {
  for (uint32_t i = 0; i < DELAY_NUM / div; i++)
    ;
}

int main(void) {
  initialise_monitor_handles();

  // Enable peripheral clock for GPIOA
  RCC->AHB1ENR |= (1 << 0x0u);

  // Set PIN 1 as output mode, each pin uses 2 bit fields, so multiply by 2
  GPIOA->MODER &= ~(0x3 << 2 * 1);
  GPIOA->MODER |= (1 << (2 * 1));

  printf("Application is running...\n");

  // Toggle LED
  GPIOA->ODR ^= (1 << 1);

  int toggle_count = 0;
  for (;;) {
    // Toggle LED
    GPIOA->ODR ^= (1 << 1);
    toggle_count++;
    printf("Toggle count: %d\n", toggle_count);
    delay(1);
  }
}
