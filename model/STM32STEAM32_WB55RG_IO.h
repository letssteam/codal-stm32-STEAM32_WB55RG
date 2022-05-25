#ifndef STM32_IOT_NODE_IO_H
#define STM32_IOT_NODE_IO_H

#include "STM32Pin.h"
//
// Component IDs for each pin.
// The can be user defined, but uniquely identify a pin when using the eventing APIs/
//

#define ID_PIN_PA0  (DEVICE_ID_IO_P0 + 0)
#define ID_PIN_PA1  (DEVICE_ID_IO_P0 + 1)
#define ID_PIN_PA2  (DEVICE_ID_IO_P0 + 2)
#define ID_PIN_PA3  (DEVICE_ID_IO_P0 + 3)
#define ID_PIN_PA4  (DEVICE_ID_IO_P0 + 4)
#define ID_PIN_PA5  (DEVICE_ID_IO_P0 + 5)
#define ID_PIN_PA6  (DEVICE_ID_IO_P0 + 6)
#define ID_PIN_PA7  (DEVICE_ID_IO_P0 + 7)
#define ID_PIN_PA8  (DEVICE_ID_IO_P0 + 8)
#define ID_PIN_PA9  (DEVICE_ID_IO_P0 + 9)
#define ID_PIN_PA10 (DEVICE_ID_IO_P0 + 10)
#define ID_PIN_PA11 (DEVICE_ID_IO_P0 + 11)
#define ID_PIN_PA12 (DEVICE_ID_IO_P0 + 12)
#define ID_PIN_PA15 (DEVICE_ID_IO_P0 + 13)

#define ID_PIN_PB0  (DEVICE_ID_IO_P0 + 14)
#define ID_PIN_PB1  (DEVICE_ID_IO_P0 + 15)
#define ID_PIN_PB2  (DEVICE_ID_IO_P0 + 16)
#define ID_PIN_PB4  (DEVICE_ID_IO_P0 + 17)
#define ID_PIN_PB5  (DEVICE_ID_IO_P0 + 18)
#define ID_PIN_PB6  (DEVICE_ID_IO_P0 + 19)
#define ID_PIN_PB7  (DEVICE_ID_IO_P0 + 20)
#define ID_PIN_PB8  (DEVICE_ID_IO_P0 + 21)
#define ID_PIN_PB9  (DEVICE_ID_IO_P0 + 22)
#define ID_PIN_PB10 (DEVICE_ID_IO_P0 + 23)
#define ID_PIN_PB11 (DEVICE_ID_IO_P0 + 24)
#define ID_PIN_PB12 (DEVICE_ID_IO_P0 + 25)
#define ID_PIN_PB13 (DEVICE_ID_IO_P0 + 26)
#define ID_PIN_PB14 (DEVICE_ID_IO_P0 + 27)
#define ID_PIN_PB15 (DEVICE_ID_IO_P0 + 28)

#define ID_PIN_PC0  (DEVICE_ID_IO_P0 + 29)
#define ID_PIN_PC1  (DEVICE_ID_IO_P0 + 30)
#define ID_PIN_PC2  (DEVICE_ID_IO_P0 + 31)
#define ID_PIN_PC3  (DEVICE_ID_IO_P0 + 32)
#define ID_PIN_PC4  (DEVICE_ID_IO_P0 + 33)
#define ID_PIN_PC5  (DEVICE_ID_IO_P0 + 34)
#define ID_PIN_PC6  (DEVICE_ID_IO_P0 + 35)
#define ID_PIN_PC10 (DEVICE_ID_IO_P0 + 36)
#define ID_PIN_PC11 (DEVICE_ID_IO_P0 + 37)
#define ID_PIN_PC12 (DEVICE_ID_IO_P0 + 38)
#define ID_PIN_PC13 (DEVICE_ID_IO_P0 + 39)

#define ID_PIN_PD0 (DEVICE_ID_IO_P0 + 40)
#define ID_PIN_PD1 (DEVICE_ID_IO_P0 + 41)

#define ID_PIN_PE4 (DEVICE_ID_IO_P0 + 42)

//#define ID_PIN_PH3 (DEVICE_ID_IO_P0 + 43)

// #define ID_PIN_SDA      (DEVICE_ID_IO_P0 + 32)
// #define ID_PIN_SCL      (DEVICE_ID_IO_P0 + 33)
// #define ID_PIN_MISO     (DEVICE_ID_IO_P0 + 34)
// #define ID_PIN_MOSI     (DEVICE_ID_IO_P0 + 35)
// #define ID_PIN_SCLK     (DEVICE_ID_IO_P0 + 36)
// #define ID_PIN_CS       (DEVICE_ID_IO_P0 + 37)
// #define ID_PIN_BLE_MISO (DEVICE_ID_IO_P0 + 38)
// #define ID_PIN_BLE_MOSI (DEVICE_ID_IO_P0 + 39)
// #define ID_PIN_BLE_SCLK (DEVICE_ID_IO_P0 + 40)
// #define ID_PIN_BLE_CS   (DEVICE_ID_IO_P0 + 41)
// #define ID_PIN_BLE_RST  (DEVICE_ID_IO_P0 + 42)
// #define ID_PIN_BLE_IRQ  (DEVICE_ID_IO_P0 + 43)
// #define ID_PIN_RX       (DEVICE_ID_IO_P0 + 44)
// #define ID_PIN_TX       (DEVICE_ID_IO_P0 + 45)

namespace codal {
/**
 * Represents a collection of all I/O pins exposed by the device.
 */
class STM32STEAM32_WB55RG_IO {
  public:
    /**
     * Constructor.
     */
    STM32STEAM32_WB55RG_IO();

    STM32Pin PA_0;
    STM32Pin PA_1;
    STM32Pin PA_2;
    STM32Pin PA_3;
    STM32Pin PA_4;
    STM32Pin PA_5;
    STM32Pin PA_6;
    STM32Pin PA_7;
    STM32Pin PA_8;
    STM32Pin PA_9;
    STM32Pin PA_10;
    STM32Pin PA_11;
    STM32Pin PA_12;
    STM32Pin PA_15;
    STM32Pin PB_0;
    STM32Pin PB_1;
    STM32Pin PB_2;
    STM32Pin PB_4;
    STM32Pin PB_5;
    STM32Pin PB_6;
    STM32Pin PB_7;
    STM32Pin PB_8;
    STM32Pin PB_9;
    STM32Pin PB_10;
    STM32Pin PB_11;
    STM32Pin PB_12;
    STM32Pin PB_13;
    STM32Pin PB_14;
    STM32Pin PB_15;
    STM32Pin PC_0;
    STM32Pin PC_1;
    STM32Pin PC_2;
    STM32Pin PC_3;
    STM32Pin PC_4;
    STM32Pin PC_5;
    STM32Pin PC_6;
    STM32Pin PC_10;
    STM32Pin PC_11;
    STM32Pin PC_12;
    STM32Pin PC_13;
    STM32Pin PD_0;
    STM32Pin PD_1;
    STM32Pin PE_4;
    // STM32Pin PH_3;
    STM32Pin NC;
};
}  // namespace codal

#endif
