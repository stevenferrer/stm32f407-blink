# stm32f407-blink

STM32F407 blink example using [STM32F4XX M](https://stm32-base.org/boards/STM32F407VGT6-STM32F4XX-M.html) board. Special thanks to [FastBit Embedded Brain Academy](https://fastbitlab.com/).

## How to flash

Build:

```console
$ make
```

Start OpenOCD:

```console
$ make flash
```

Run GDB in another terminal:

```console
$ arm-none-eabi-gdb
```

Connect to OpenOCD and flash the `blink.elf` file to the board:

```console
(gdb) target remote :3333
(gdb) monitor flash write_image erase blink.elf
```
