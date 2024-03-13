CC=arm-none-eabi-gcc
MCPU=cortex-m4
CFLAGS=-c -mcpu=$(MCPU) -mthumb -std=c99 -Wall -O0
LDFLAGS=-nostdlib -T stm32f407xx.ld -Wl,-Map=blink.map

all: blink.o startup.o blink.elf

clean:
	rm -Rf *.o *.elf *.map

startup.o: startup.c
	$(CC) $(CFLAGS) -o $@ $^

blink.o: blink.c stm32f407xx.h stm32f407xx_gpio_driver.h
	$(CC) $(CFLAGS) blink.c stm32f407xx_gpio_driver.c

blink.elf: blink.o stm32f407xx_gpio_driver.o startup.o
	$(CC) $(LDFLAGS) -o $@ $^

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
