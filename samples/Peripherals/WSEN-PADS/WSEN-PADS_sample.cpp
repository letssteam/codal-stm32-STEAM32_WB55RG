#include "WSEN-PADS_sample.h"

#include <string>

void Wsen_PadsSample(codal::STM32STEAM32_WB55RG& steam32)
{
    steam32.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*        Demonstration du WSEN_PADS       *\r\n");
    printf("*******************************************\r\n");

    codal::WSEN_PADS press(steam32.i2c1, 0xBA);
    press.init();

    steam32.sleep(2000);

    printf("Device ID : %X\r\n", press.whoAmI());

    steam32.sleep(2000);

    std::string pressure;
    std::string temperature;

    bool state = false;

    while (true) {
        state = !state;
        steam32.io.PC_10.setDigitalValue(state ? 1 : 0);

        pressure    = "Pressure : " + std::to_string(press.getPressure()) + " kPa";
        temperature = "Temperature : " + std::to_string(press.getTemperature()) + " C";

        printf("%s \r\n", pressure.c_str());
        printf("%s \r\n", temperature.c_str());
        printf("\r\n");

        steam32.sleep(1000);
    }
}
