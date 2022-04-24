#!/bin/sh
arm-none-eabi-gdb --eval "target remote | openocd -s /usr/share/openocd/scripts/ -s libraries/codal-stm32-PNUCLEO_WB55RG/scripts/ -f openocd.cfg -f debug.cfg" build/PNUCLEO_WB55RG
