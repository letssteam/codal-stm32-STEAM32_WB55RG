#include "DapLink_Flash_sample.h"

#include <cctype>
#include <cstdio>

constexpr uint8_t ADDRESS = 0x76;

bool state_led = false;

void DAPLINK_FLASH_Sample(codal::STM32STEAM32_WB55RG& steam32)
{
    steam32.init();
    steam32.serial.init(115200);

    steam32.io.PA_11.setDigitalValue(0);  // Force HP low state...

    auto i2c = steam32.i2c1;

    printf("Ready !\r\n");
    codal::fiber_sleep(1000);

    char c;
    while (1) {
        steam32.sleep(100);

        c = static_cast<char>(steam32.serial.getChar(codal::ASYNC));

        if ((steam32.serial.getChar(codal::ASYNC) != DEVICE_NO_DATA)) {
            // flush rx buffer
            target_wait(10);
            while (steam32.serial.getChar(codal::ASYNC) != DEVICE_NO_DATA) target_wait(10);

            if (c < 0x20) continue;

            printf("--- Recv '%c'\n", toupper(c));

            switch ((char)toupper(c)) {
                case 'A': {
                    printf("Data to append (max 256 char): \n");
                    codal::ManagedString str = steam32.serial.readUntil('\n', codal::SYNC_SPINWAIT);

                    i2c.beginTransmission(ADDRESS);
                    i2c.write(0x11);
                    for (int16_t i = 0; i < str.length() && i < 256; ++i) {
                        i2c.write(uint8_t(str.charAt(i)));
                    }
                    i2c.endTransmission();
                    break;
                }

                    // Read a sector (256 bytes) seems to break the I2C bus. This is not an issue, because there is no
                    // reason to read a secto for the moment.
                    // case 'R': {
                    //     i2c.beginTransmission(ADDRESS);
                    //     i2c.write(0x20);
                    //     i2c.write(0x00);
                    //     i2c.endTransmission();

                    //     auto result = i2c.read(0x77, 256);
                    //     printf("Sector 0 data (%d):\n'%.256s'\n", result.size(), result.data());

                    //     break;
                    // }

                case 'W': {
                    i2c.beginTransmission(ADDRESS);
                    i2c.write(0x01);
                    i2c.endTransmission();

                    auto result = i2c.read(0x77, 1);
                    printf("Who Am I = 0x%02X\n", result[0]);
                    break;
                }

                case 'C':
                    i2c.beginTransmission(ADDRESS);
                    i2c.write(0x10);
                    i2c.endTransmission();
                    break;

                case 'F': {
                    printf(
                        "Set the filename (format: FFFFFFFFEEE (F: filename, E: ext) use ' ' (space) to fill unsused \
                        characters)): \n");
                    codal::ManagedString str = steam32.serial.readUntil('\n', codal::SYNC_SPINWAIT);

                    printf("--- filename: (size: %d) '%s' ", str.length(), str.toCharArray());

                    for (int i = 0; i < str.length(); ++i) {
                        printf("0x%02X ", unsigned(str.charAt(i)));
                    }
                    printf("\n");

                    i2c.beginTransmission(ADDRESS);
                    i2c.write(0x03);
                    for (uint16_t i = 0; i < str.length(); ++i) {
                        i2c.write(uint8_t(str.charAt(i)));
                    }
                    i2c.endTransmission();
                    break;
                }

                case 'G': {
                    i2c.beginTransmission(ADDRESS);
                    i2c.write(0x04);
                    i2c.endTransmission();

                    auto result = i2c.read(0x77, 11);
                    printf("filename = '%.11s'\n", result.data());
                    break;
                }

                case 'S': {
                    i2c.beginTransmission(ADDRESS);
                    i2c.write(0x80);
                    i2c.endTransmission();

                    auto status_1 = i2c.read(0x77, 1);
                    printf("Status = 0x%02X\n", status_1[0]);

                    i2c.beginTransmission(ADDRESS);
                    i2c.write(0x81);
                    i2c.endTransmission();

                    auto status_err = i2c.read(0x77, 1);
                    printf("Error status = 0x%02X\n", status_err[0]);
                    break;
                }

                case 'L': {
                    uint16_t total   = 200;
                    uint16_t success = 0;
                    uint16_t failure = 0;

                    for (uint16_t i = 0; i < total; i++) {
                        i2c.beginTransmission(ADDRESS);
                        i2c.write(0x04);
                        i2c.endTransmission();

                        auto result = i2c.read(0x77, 11);

                        if (result[0] == 0x00) {
                            failure++;
                        }
                        else {
                            success++;
                        }

                        steam32.sleep(10);
                    }

                    printf("Test done (success: %d/%d (%d %%) -- failure: %d/%d (%d %%)\n", success, total,
                           success * 100 / total, failure, total, failure * 100 / total);
                }

                default:
                    break;
            }
        }
    }
}