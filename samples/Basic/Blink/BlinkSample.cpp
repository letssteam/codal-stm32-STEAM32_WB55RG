#include "BlinkSample.h"

void BlinkSample_main(codal::STM32STEAM32_WB55RG& steam32)
{
    bool state = false;
    while (true) {
        steam32.io.PC_10.setDigitalValue((int)state);
        // steam32.io.led2.setDigitalValue((int)!state);
        steam32.sleep(1000);
        state = !state;
    }
}
