CC=arm-none-eabi-gcc
MPU=cortex-m4
CFLAGS=-c -mcpu=$(MPU) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS=-mcpu=$(MPU) -mthumb -mfloat-abi=soft -T stm32f407xx.ld -Wl,-Map=blink.map
LDFLAGS_NANO=$(LDFLAGS) --specs=nano.specs
LDFLAGS_SEMI=$(LDFLAGS) --specs=rdimon.specs

all: blink.o startup.o syscalls.o blink.elf

semi: blink.o startup.o syscalls.o blink_semi.elf

clean:
	rm -Rf *.o *.elf *.map

startup.o: startup.c
	$(CC) $(CFLAGS) -o $@ $^

blink.o: blink.c stm32f407xx.h stm32f407xx_gpio_driver.h
	$(CC) $(CFLAGS) blink.c stm32f407xx_gpio_driver.c

syscalls.o: syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

blink.elf: blink.o stm32f407xx_gpio_driver.o startup.o syscalls.o
	$(CC) $(LDFLAGS_NANO) -o $@ $^

blink_semi.elf: blink.o stm32f407xx_gpio_driver.o startup.o
	$(CC) $(LDFLAGS_SEMI) -o $@ $^

dump: blink.elf
	arm-none-eabi-objdump -h $^

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program blink.elf verify reset exit"

debug:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
