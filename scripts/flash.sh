#!/bin/sh
set -e
./build.py
openocd -s "/usr/share/openocd/scripts/" -s"libraries/codal-stm32-PNUCLEO_WB55RG/scripts/" -f "openocd.cfg" -c "program PNUCLEO_WB55RG.hex verify reset exit "
