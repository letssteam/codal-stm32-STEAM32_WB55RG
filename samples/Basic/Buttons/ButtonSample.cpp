#include "ButtonSample.h"

using namespace std;
using namespace codal;

void ButtonSample_main(codal::STM32STEAM32_WB55RG& steam32)
{
    STM32Pin& led_red   = steam32.io.PC_12;
    STM32Pin& led_green = steam32.io.PC_11;
    STM32Pin& led_blue  = steam32.io.PC_10;

    STM32Pin& btn_A = steam32.io.PA_7;
    STM32Pin& btn_B = steam32.io.PA_8;
    STM32Pin& btn_M = steam32.io.PA_0;

    while (true) {
        led_red.setDigitalValue(btn_A.getDigitalValue() ? 0 : 1);
        led_green.setDigitalValue(btn_B.getDigitalValue() ? 0 : 1);
        led_blue.setDigitalValue(btn_M.getDigitalValue() ? 0 : 1);
        steam32.sleep(50);
    }
}
