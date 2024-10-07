
#include "VL53L1X_sample.h"

#include <cstdio>
#include <string>

void vlx53l1xSample(codal::STeaMi& steami)
{
    steami.serial.init(115200);

    steami.sleep(1000);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*                 VL53L1X                 *\r\n");
    printf("*******************************************\r\n");

    steami.io.irqDist.setDigitalValue(0);
    codal::VL53L1X vl53l1x(&steami.i2cInt);

    vl53l1x.init();

    steami.sleep(2000);

    std::string distance;

    while (true) {
        distance = "Distance : " + std::to_string(vl53l1x.getDistance()) + " mm";

        printf("%s \r\n", distance.c_str());

        steami.sleep(1000);
    }
}
