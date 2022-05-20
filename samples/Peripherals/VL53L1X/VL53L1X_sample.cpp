
#include "VL53L1X_sample.h"

#include <cstdio>
#include <string>

void vlx53l1xSample(codal::STM32STEAM32_WB55RG& steam32)
{
    steam32.serial.init(115200);

    steam32.sleep(1000);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*                 VL53L1X                 *\r\n");
    printf("*******************************************\r\n");

    steam32.io.PB_12.setDigitalValue(0);
    codal::VL53L1X vl53l1x(&steam32.i2c1);

    vl53l1x.init();

    steam32.sleep(2000);

    std::string distance;

    while (true) {
        distance = "Distance : " + std::to_string(vl53l1x.getDistance()) + " mm";

        printf("%s \r\n", distance.c_str());

        steam32.sleep(1000);
    }
}
