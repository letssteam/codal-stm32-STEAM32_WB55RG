
#include "HTS221_sample.h"

#include <string>

void hts221Sample(codal::STM32STEAM32_WB55RG& steam32)
{
    steam32.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*          Demonstration du HTS221        *\r\n");
    printf("*******************************************\r\n");

    codal::HTS221 hts221(&steam32.i2c1, 0xBE);
    hts221.init();

    hts221.setOutputRate(codal::HTS221_OUTPUT_RATE::RATE_7HZ);

    steam32.sleep(2000);

    std::string temperature;
    std::string humidity;

    bool state = false;

    while (true) {
        state = !state;
        steam32.io.PC_10.setDigitalValue(state ? 1 : 0);

        if (!hts221.isTemperatureDataAvailable() || !hts221.isHumidityDataAvailable()) {
            steam32.sleep(100);
            printf("Sensor is not ready\r\n");
            continue;
        }

        temperature = "Temperature : " + std::to_string(hts221.getTemperature()) + " C";
        humidity    = "Humidity : " + std::to_string(hts221.getHumidity()) + " %RH";

        printf("%s \r\n", temperature.c_str());
        printf("%s \r\n", humidity.c_str());
        printf("\r\n");

        steam32.sleep(1000);
    }
}
