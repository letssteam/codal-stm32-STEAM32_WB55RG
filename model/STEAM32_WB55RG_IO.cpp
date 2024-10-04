/**
 * Class definition for STM32 IOT node IO.
 * Represents a collection of all I/O pins on the device.
 */

#include "STEAM32_WB55RG_IO.h"

namespace codal {

/**
 * Constructor.
 *
 * Create a representation of all given I/O pins on the edge connector
 *
 * Accepts a sequence of unique ID's used to distinguish events raised
 * by Pin instances on the default EventModel.
 */
STEAM32_WB55RG_IO::STEAM32_WB55RG_IO()
    : PA_0(ID_PIN_PA0, PinNumber::PA_0, PIN_CAPABILITY_DIGITAL),
      PA_1(ID_PIN_PA1, PinNumber::PA_1, PIN_CAPABILITY_DIGITAL),
      PA_2(ID_PIN_PA2, PinNumber::PA_2, PIN_CAPABILITY_DIGITAL),  // Enable ANALOG = bug with TIM2 (due to PWM)
      PA_3(ID_PIN_PA3, PinNumber::PA_3, PIN_CAPABILITY_DIGITAL),
      PA_4(ID_PIN_PA4, PinNumber::PA_4, PIN_CAPABILITY_ALL),
      PA_5(ID_PIN_PA5, PinNumber::PA_5, PIN_CAPABILITY_DIGITAL),  // Enable ANALOG = bug with TIM2 (due to PWM)
      PA_6(ID_PIN_PA6, PinNumber::PA_6, PIN_CAPABILITY_ALL),
      PA_7(ID_PIN_PA7, PinNumber::PA_7, PIN_CAPABILITY_ALL),
      PA_8(ID_PIN_PA8, PinNumber::PA_8, PIN_CAPABILITY_ALL),
      PA_9(ID_PIN_PA9, PinNumber::PA_9, PIN_CAPABILITY_ALL),
      PA_10(ID_PIN_PA10, PinNumber::PA_10, PIN_CAPABILITY_DIGITAL),
      PA_11(ID_PIN_PA11, PinNumber::PA_11, PIN_CAPABILITY_AD),
      PA_12(ID_PIN_PA12, PinNumber::PA_12, PIN_CAPABILITY_DIGITAL),
      PA_15(ID_PIN_PA15, PinNumber::PA_15, PIN_CAPABILITY_DIGITAL),
      PB_0(ID_PIN_PB0, PinNumber::PB_0, PIN_CAPABILITY_DIGITAL),
      PB_1(ID_PIN_PB1, PinNumber::PB_1, PIN_CAPABILITY_DIGITAL),
      PB_2(ID_PIN_PB2, PinNumber::PB_2, PIN_CAPABILITY_DIGITAL),
      PB_4(ID_PIN_PB4, PinNumber::PB_4, PIN_CAPABILITY_DIGITAL),
      PB_5(ID_PIN_PB5, PinNumber::PB_5, PIN_CAPABILITY_DIGITAL),
      PB_6(ID_PIN_PB6, PinNumber::PB_6, PIN_CAPABILITY_DIGITAL),
      PB_7(ID_PIN_PB7, PinNumber::PB_7, PIN_CAPABILITY_DIGITAL),
      PB_8(ID_PIN_PB8, PinNumber::PB_8, PIN_CAPABILITY_DIGITAL),
      PB_9(ID_PIN_PB9, PinNumber::PB_9, PIN_CAPABILITY_DIGITAL),
      PB_10(ID_PIN_PB10, PinNumber::PB_10, PIN_CAPABILITY_DIGITAL),
      PB_11(ID_PIN_PB11, PinNumber::PB_11, PIN_CAPABILITY_DIGITAL),
      PB_12(ID_PIN_PB12, PinNumber::PB_12, PIN_CAPABILITY_DIGITAL),
      PB_13(ID_PIN_PB13, PinNumber::PB_13, PIN_CAPABILITY_ALL),
      PB_14(ID_PIN_PB14, PinNumber::PB_14, PIN_CAPABILITY_ALL),
      PB_15(ID_PIN_PB15, PinNumber::PB_15, PIN_CAPABILITY_ALL),
      PC_0(ID_PIN_PC0, PinNumber::PC_0, PIN_CAPABILITY_DIGITAL),
      PC_1(ID_PIN_PC1, PinNumber::PC_1, PIN_CAPABILITY_DIGITAL),
      PC_2(ID_PIN_PC2, PinNumber::PC_2, PIN_CAPABILITY_DIGITAL),
      PC_3(ID_PIN_PC3, PinNumber::PC_3, PIN_CAPABILITY_DIGITAL),
      PC_4(ID_PIN_PC4, PinNumber::PC_4, PIN_CAPABILITY_ALL),
      PC_5(ID_PIN_PC5, PinNumber::PC_5, PIN_CAPABILITY_ALL),
      PC_6(ID_PIN_PC6, PinNumber::PC_6, PIN_CAPABILITY_DIGITAL),
      PC_10(ID_PIN_PC10, PinNumber::PC_10, PIN_CAPABILITY_DIGITAL),
      PC_11(ID_PIN_PC11, PinNumber::PC_11, PIN_CAPABILITY_DIGITAL),
      PC_12(ID_PIN_PC12, PinNumber::PC_12, PIN_CAPABILITY_DIGITAL),
      PC_13(ID_PIN_PC13, PinNumber::PC_13, PIN_CAPABILITY_DIGITAL),
      PD_0(ID_PIN_PD0, PinNumber::PD_0, PIN_CAPABILITY_DIGITAL),
      PD_1(ID_PIN_PD1, PinNumber::PD_1, PIN_CAPABILITY_DIGITAL),
      PE_4(ID_PIN_PE4, PinNumber::PE_4, PIN_CAPABILITY_DIGITAL),
      // PH_3(ID_PIN_PH3, PinNumber::PH_3, PIN_CAPABILITY_DIGITAL)
      NC(0, PinNumber::NC, PIN_CAPABILITY_AD)
{
}

}  // namespace codal
