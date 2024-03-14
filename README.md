# stm32f407-blink

STM32F407 blink example using [STM32F4XX M](https://stm32-base.org/boards/STM32F407VGT6-STM32F4XX-M.html) board. Special thanks to [FastBit Embedded Brain Academy](https://fastbitlab.com/).

## How to flash

Build the binary.

```console
$ make
```

Flash.

```console
$ make flash
```

Enjoy watching the LED blink!

## Semihosting

Build semihosting binary.

```console
$ make semi
```

Run OpenOCD.

```console
$ make debug
```

Flash, enable semihosting and reset.

```console
$ arm-none-eabi-gcc

(gcc) target extended-remote :3333
(gcc) monitor flash write_image erase blink_semi.elf
(gcc) monitor arm semihosting enable
(gcc) monitor reset
```

Watch OpenOCD console print.

```console
Application is running...
Toggle count: 1
Toggle count: 2
Toggle count: 3
...
```
