#include "SerialSample.h"

#include <string>

#include "STM32Serial.h"

void SerialSample_main(codal::STEAM32_WB55RG& steam32)
{
    steam32.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("* Demonstration de la communication serie *\r\n");
    printf("*******************************************\r\n");
    std::string str;
    bool state = false;

    while (true) {
        steam32.io.PC_11.setDigitalValue(state ? 1 : 0);

        if (steam32.serial.isReadable() != 0) {
            char c = static_cast<char>(steam32.serial.getChar(codal::ASYNC));
            str += c;
            printf("< %c \r\n", c);
            printf("> %s \r\n", str.c_str());
        }

        steam32.sleep(250);
        state = !state;
    }
}
