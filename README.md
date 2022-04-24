# Codal target for the PNUCLEO_WB55RG Board [![codal-stm32-PNUCLEO_WB55RG](https://img.shields.io/github/workflow/status/letssteam/codal-stm32-PNUCLEO_WB55RG/codal-buildtarget?label=codal-stm32-PNUCLEO_WB55RG)](https://github.com/letssteam/codal-stm32-PNUCLEO_WB55RG/actions)

Codal target for the [P-NUCLEO-WB55](https://www.st.com/en/evaluation-tools/p-nucleo-wb55.html). Codal is the core set of drivers, mechanisms and types that make up the runtime for a board in Makecode.

## Overview

The codal runtime provides an easy to use environment for programming the board in the C/C++ language, written by Lancaster University. It contains device drivers for all the hardware capabilities, and also a suite of runtime mechanisms to make programming the easier and more flexible. These range from control of the LED matrix display to peer-to-peer radio communication and secure Bluetooth Low Energy services.

In addition to supporting development in C/C++, the runtime is also designed specifically to support higher level languages provided by our partners that target physical computing and computer science education. It is currently used as a support library for Microsoft MakeCode

Codal-core must be implemented by third party developper to support new hardware target.

## Board Information  

The the [P-NUCLEO-WB55](https://www.st.com/en/evaluation-tools/p-nucleo-wb55.html) allows users to develop applications of BLE 5 device.

The P-NUCLEO-WB55 pack is a multi-protocol wireless and ultra-low-power device embedding a powerful and ultra-low-power radio compliant with the Bluetooth® Low Energy (BLE) SIG specification v5.0 and with IEEE 802.15.4-2011.

The support for Arduino Uno V3 connectivity provides unlimited expansion capabilities with a large choice of specialized add-on boards.

<img src="https://www.st.com/bin/ecommerce/api/image.PF265562.en.feature-description-include-personalized-no-cpn-large.jpg" width="600px" />

## Feature List (and if implemented in codal)

- [ ] Flash memory
- [ ] Bluetooth® V5 module
- [ ] USB OTG FS
- [ ] 2 push-buttons (user and reset)
- [ ] GPIO
- [ ] ADC 12 bits
- [ ] FAT Storage over the flash memory
- [ ] Expansion connectors:
  - [ ] Arduino™ Uno V3

## Installation

Before using this target you need to configure your platforms with some software.
Codal is also a build system to simplify as much as possible the experience of novice users.  

1. Install `git`, ensure it is available on your platforms path.
2. Install the `arm-none-eabi-*` command line utilities for ARM based devices, ensure they are available on your platforms path.
3. Install [CMake](https://cmake.org)(Cross platform make), this is the entirety of the build system.
4. Install `Python 2.7` (if you are unfamiliar with CMake), python scripts are used to simplify the build process.
5. Clone the repository <https://github.com/lancaster-university/codal>

## Building

- Create a `codal.json` file :
  ```json
  {
    "target": {
        "name": "codal-stm32-PNUCLEO_WB55RG", 
        "url": "https://github.com/letssteam/codal-stm32-PNUCLEO_WB55RG", 
        "branch": "master", 
        "type": "git", 
        "test_ignore": true
    }
  }
  ```
- In the root of this repository type `python build.py` the `-c` option cleans before building.
- The bin file `PNUCLEO_WB55RG.bin` will be placed at the location specified by `codal.json`, by default this is the root.
- To test the sample program, you just copy the bin file in the mass storage of the board.

### Advanced use

If you would like to override or define any additional configuration options (`#define's`) that are used by the supporting libraries, the codal build system allows the addition of a config field in `codal.json`:

```json
{
    "target": {
        "name": "codal-stm32-PNUCLEO_WB55RG", 
        "url": "https://github.com/letssteam/codal-stm32-PNUCLEO_WB55RG", 
        "branch": "master", 
        "type": "git", 
        "test_ignore": true
    },
    "config":{
        "NUMBER_ONE":1
    },
    "application":"source",
    "output_folder":"."
}
```

The above example will be translate `"NUMBER_ONE":1` into: `#define NUMBER_ONE     1` and force include it during compilation. You can also specify alternate application or output folders.

#### Execute a specific sample application

By default, the application present in the `source` directory is the content of the `samples` directory of this repository. Since you can just execute one example at the time, you need to configure your target to specify the one you want.

For example, if you want to test the `BLE_TEMPERATURE_ALARM_SAMPLE`, you need to configure the corresponding `#define` with the following `codal.json`:

```json
{
    "target": {
        "name": "codal-stm32-PNUCLEO_WB55RG", 
        "url": "https://github.com/letssteam/codal-stm32-PNUCLEO_WB55RG", 
        "branch": "master", 
        "type": "git", 
        "test_ignore": true
    },
    "config":{
        "BLE_TEMPERATURE_ALARM_SAMPLE":1
    },
    "application":"source",
    "output_folder":"."
}
```
