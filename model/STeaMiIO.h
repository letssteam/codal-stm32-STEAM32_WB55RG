#pragma once

#include "CodalComponent.h"
#include "CodalConfig.h"
#include "STM32Pin.h"

namespace {
enum class PinIndex : int {
    PC_4   = 0,
    PA_5   = 1,
    PC_5   = 2,
    PA_2   = 3,
    PA_4   = 4,
    PA_7   = 5,
    PC_3   = 6,
    PA_9   = 7,
    PA_15  = 8,
    PC_2   = 9,
    PA_6   = 10,
    PA_8   = 11,
    PC_6   = 12,
    PB_13  = 13,
    PB_14  = 14,
    PB_15  = 15,
    PE_4   = 16,
    PC_0   = 17,
    PC_1   = 18,
    PB_2   = 19,
    PD_0   = 20,
    PB_8   = 21,
    PB_9   = 22,
    PC_13  = 23,
    PB_12  = 24,
    PB_0   = 25,
    PD_1   = 26,
    PB_6   = 27,
    PB_7   = 28,
    PC_10  = 29,
    PH_3   = 30,
    PC_11  = 31,
    PC_12  = 32,
    PA_0   = 33,
    PA_3   = 34,
    PA_10  = 35,
    PA_12  = 36,
    PB_1   = 37,
    PB_10  = 38,
    PB_11  = 39,
    PA_11  = 40,
    PB_4   = 41,
    PB_5   = 42,
    PA_1   = 43,
    GPIO_1 = 44,
    GPIO_2 = 45,
    GPIO_3 = 46,
    GPIO_4 = 47,
    GPIO_5 = 48,
    GPIO_6 = 49,
    GPIO_7 = 50,
    GPIO_8 = 51,
};

#define PIN_ID(X) (DEVICE_ID_IO_P0 + (int)::PinIndex::X)

#define ID_PIN_PC4   PIN_ID(PC_4)
#define ID_PIN_PA5   PIN_ID(PA_5)
#define ID_PIN_PC5   PIN_ID(PC_5)
#define ID_PIN_PA2   PIN_ID(PA_2)
#define ID_PIN_PA4   PIN_ID(PA_4)
#define ID_PIN_PA7   PIN_ID(PA_7)
#define ID_PIN_PC3   PIN_ID(PC_3)
#define ID_PIN_PA9   PIN_ID(PA_9)
#define ID_PIN_PA15  PIN_ID(PA_15)
#define ID_PIN_PC2   PIN_ID(PC_2)
#define ID_PIN_PA6   PIN_ID(PA_6)
#define ID_PIN_PA8   PIN_ID(PA_8)
#define ID_PIN_PC6   PIN_ID(PC_6)
#define ID_PIN_PB13  PIN_ID(PB_13)
#define ID_PIN_PB14  PIN_ID(PB_14)
#define ID_PIN_PB15  PIN_ID(PB_15)
#define ID_PIN_PE4   PIN_ID(PE_4)
#define ID_PIN_PC0   PIN_ID(PC_0)
#define ID_PIN_PC1   PIN_ID(PC_1)
#define ID_PIN_PB2   PIN_ID(PB_2)
#define ID_PIN_PD0   PIN_ID(PD_0)
#define ID_PIN_PB8   PIN_ID(PB_8)
#define ID_PIN_PB9   PIN_ID(PB_9)
#define ID_PIN_PC13  PIN_ID(PC_13)
#define ID_PIN_PB12  PIN_ID(PB_12)
#define ID_PIN_PB0   PIN_ID(PB_0)
#define ID_PIN_PD1   PIN_ID(PD_1)
#define ID_PIN_PB6   PIN_ID(PB_6)
#define ID_PIN_PB7   PIN_ID(PB_7)
#define ID_PIN_PC10  PIN_ID(PC_10)
#define ID_PIN_PH3   PIN_ID(PH_3)
#define ID_PIN_PC11  PIN_ID(PC_11)
#define ID_PIN_PC12  PIN_ID(PC_12)
#define ID_PIN_PA0   PIN_ID(PA_0)
#define ID_PIN_PA3   PIN_ID(PA_3)
#define ID_PIN_PA10  PIN_ID(PA_10)
#define ID_PIN_PA12  PIN_ID(PA_12)
#define ID_PIN_PB1   PIN_ID(PB_1)
#define ID_PIN_PB10  PIN_ID(PB_10)
#define ID_PIN_PB11  PIN_ID(PB_11)
#define ID_PIN_PA11  PIN_ID(PA_11)
#define ID_PIN_PB4   PIN_ID(PB_4)
#define ID_PIN_PB5   PIN_ID(PB_5)
#define ID_PIN_PA1   PIN_ID(PA_1)
#define ID_PIN_GPIO1 PIN_ID(GPIO_1)
#define ID_PIN_GPIO2 PIN_ID(GPIO_2)
#define ID_PIN_GPIO3 PIN_ID(GPIO_3)
#define ID_PIN_GPIO4 PIN_ID(GPIO_4)
#define ID_PIN_GPIO5 PIN_ID(GPIO_5)
#define ID_PIN_GPIO6 PIN_ID(GPIO_6)
#define ID_PIN_GPIO7 PIN_ID(GPIO_7)
#define ID_PIN_GPIO8 PIN_ID(GPIO_8)

}  // namespace

//
// Component IDs for each pin.
// The can be user defined, but uniquely identify a pin when using the eventing APIs/
//

#define ID_PIN_P0  ID_PIN_PC4
#define ID_PIN_P1  ID_PIN_PA5
#define ID_PIN_P2  ID_PIN_PC5
#define ID_PIN_P3  ID_PIN_PA2
#define ID_PIN_P4  ID_PIN_PA4
#define ID_PIN_P5  ID_PIN_PA7
#define ID_PIN_P6  ID_PIN_PC3
#define ID_PIN_P7  ID_PIN_PA9
#define ID_PIN_P8  ID_PIN_PA15
#define ID_PIN_P9  ID_PIN_PC2
#define ID_PIN_P10 ID_PIN_PA6
#define ID_PIN_P11 ID_PIN_PA8
#define ID_PIN_P12 ID_PIN_PC6
#define ID_PIN_P13 ID_PIN_PB13
#define ID_PIN_P14 ID_PIN_PB14
#define ID_PIN_P15 ID_PIN_PB15
#define ID_PIN_P16 ID_PIN_PE4
#define ID_PIN_P19 ID_PIN_PC1
#define ID_PIN_P20 ID_PIN_PC0
#define ID_PIN_P24 ID_PIN_GPIO3
#define ID_PIN_P25 ID_PIN_GPIO4
#define ID_PIN_P28 ID_PIN_GPIO1
#define ID_PIN_P29 ID_PIN_GPIO2

#define ID_PIN_ACTIVATE_3V3_STLINK ID_PIN_PB2
#define ID_PIN_CS_DISPLAY          ID_PIN_PD0
#define ID_PIN_RST_DISPLAY         ID_PIN_PA12
#define ID_PIN_SPI_INT_MOSI        ID_PIN_PB5
#define ID_PIN_SPI_INT_MISO        ID_PIN_PB4
#define ID_PIN_SPI_INT_SCK         ID_PIN_PA1
#define ID_PIN_I2C_EXT_SCL         ID_PIN_PC0
#define ID_PIN_I2C_EXT_SDA         ID_PIN_PC1
#define ID_PIN_I2C_INT_SCL         ID_PIN_PB8
#define ID_PIN_I2C_INT_SDA         ID_PIN_PB9
#define ID_PIN_INT_ACC             ID_PIN_PC13
#define ID_PIN_INT_DIST            ID_PIN_PB12
#define ID_PIN_INT_MAG             ID_PIN_PD1
#define ID_PIN_INT_EXPANDER        ID_PIN_PB0
#define ID_PIN_JACDAC_DATA_TX      ID_PIN_PB6
#define ID_PIN_JACDAC_DATA_RX      ID_PIN_PB7
#define ID_PIN_RST_EXPANDER        ID_PIN_PB1
#define ID_PIN_SERIAL_RX           ID_PIN_PB10
#define ID_PIN_SERIAL_TX           ID_PIN_PB11
#define ID_PIN_SPI_EXT_MOSI        ID_PIN_PB15
#define ID_PIN_SPI_EXT_MISO        ID_PIN_PB14
#define ID_PIN_SPI_EXT_SCK         ID_PIN_PB13
#define ID_PIN_SPI_EXT_CS          ID_PIN_PE4
#define ID_PIN_LED_BLUE            ID_PIN_PC10
#define ID_PIN_LED_GREEN           ID_PIN_PC11
#define ID_PIN_LED_RED             ID_PIN_PC12
#define ID_PIN_LED_BLE             ID_PIN_PH3
#define ID_PIN_A_BUTTON            ID_PIN_PA7
#define ID_PIN_B_BUTTON            ID_PIN_PA8
#define ID_PIN_MENU_BUTTON         ID_PIN_PA0
#define ID_PIN_UP_BUTTON           ID_PIN_GPIO8
#define ID_PIN_DOWN_BUTTON         ID_PIN_GPIO6
#define ID_PIN_LEFT_BUTTON         ID_PIN_GPIO7
#define ID_PIN_RIGHT_BUTTON        ID_PIN_GPIO5
#define ID_PIN_SPEAKER             ID_PIN_PA11
#define ID_PIN_MIC_CLK             ID_PIN_PA3
#define ID_PIN_MIC_IN              ID_PIN_PA10

namespace codal {

using STeaMiPin = STM32Pin;  // Todo : Define a STeaMiPin class to handle IOExpander pins
/**
 * Represents a collection of all I/O pins exposed by the device.
 */
class STeaMiIO {
  public:
    /**
     * Constructor.
     */
    STeaMiIO();

    STM32Pin p0;
    STM32Pin p1;
    STM32Pin p2;
    STM32Pin p3;
    STM32Pin p4;
    STM32Pin p5;
    STM32Pin p6;
    STM32Pin p7;
    STM32Pin p8;
    STM32Pin p9;
    STM32Pin p10;
    STM32Pin p11;
    STM32Pin p12;
    STM32Pin p13;
    STM32Pin p14;
    STM32Pin p15;
    STM32Pin p16;
    STM32Pin p19;
    STM32Pin p20;

    STeaMiPin p24;
    STeaMiPin p25;
    STeaMiPin p28;
    STeaMiPin p29;

    STM32Pin activate3V3StLink;

    STM32Pin csDisplay;
    STM32Pin resetDisplay;
    STM32Pin mosiDisplay;
    STM32Pin misoDisplay;
    STM32Pin sckDisplay;

    STM32Pin extScl;
    STM32Pin extsda;

    STM32Pin intScl;
    STM32Pin intSda;

    STM32Pin irqAcc;
    STM32Pin irqDist;
    STM32Pin irqMag;
    STM32Pin irqExpander;

    STM32Pin jacdacTx;
    STM32Pin jacdacRx;

    STM32Pin resetExpander;
    STM32Pin serialRx;
    STM32Pin serialTx;

    STM32Pin mosi;
    STM32Pin miso;
    STM32Pin sck;
    STM32Pin cs;

    STM32Pin ledGreen;
    STM32Pin ledBlue;
    STM32Pin ledRed;

    STM32Pin ledBLE;

    STM32Pin buttonA;
    STM32Pin buttonB;
    STM32Pin buttonMenu;

    STeaMiPin buttonUp;
    STeaMiPin buttonDown;
    STeaMiPin buttonLeft;
    STeaMiPin buttonRight;

    STM32Pin speaker;
    STM32Pin runmic;
    STM32Pin microphone;
};
}  // namespace codal