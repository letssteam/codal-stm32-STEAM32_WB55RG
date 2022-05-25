
#include "APDS9960_sample.h"

#include <string>

#include "ssd1327.h"

void APDS9960_SampleMain(codal::STM32STEAM32_WB55RG& steam32)
{
    steam32.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*        Demonstration du APDS9960        *\r\n");
    printf("*******************************************\r\n");

    codal::SSD1327_SPI ssd(steam32.spi1, steam32.io.PD_0, steam32.io.PB_4, steam32.io.PA_12, 128, 128);
    ssd.init();

    codal::APDS9960 apds(steam32.i2c1, 0x72);
    apds.init();

    steam32.sleep(2000);

    std::string str;
    std::array<uint16_t, 4> rgbc;

    while (true) {
        rgbc = apds.getColors();

        str = "RGBC : " + std::to_string(rgbc[0]) + ", " + std::to_string(rgbc[1]) + ", " + std::to_string(rgbc[2]) +
              ", " + std::to_string(rgbc[3]);
        printf("%s \r\n", str.c_str());

        ssd.fill(0x00);
        ssd.drawText("Red:   " + std::to_string(rgbc[0]), 20, 30, 0xff);
        ssd.drawText("Green: " + std::to_string(rgbc[1]), 20, 50, 0xff);
        ssd.drawText("Blue:  " + std::to_string(rgbc[2]), 20, 70, 0xff);
        ssd.drawText("Clear: " + std::to_string(rgbc[3]), 20, 90, 0xff);
        ssd.show();

        steam32.sleep(250);
    }
}