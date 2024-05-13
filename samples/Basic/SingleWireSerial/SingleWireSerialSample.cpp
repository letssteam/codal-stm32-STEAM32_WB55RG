#include "SingleWireSerialSample.h"

#include <cstdio>

#include "STM32SingleWireSerial.h"

void set_serial_mode(codal::STM32SingleWireSerial& sws, bool is_tx)
{
    if (is_tx) {
        sws.setMode(codal::SingleWireMode::SingleWireTx);
    }
    else {
        sws.setMode(codal::SingleWireMode::SingleWireRx);
    }
}

void SingleSerialSerialSample_main(codal::STM32STEAM32_WB55RG& steam32)
{
    bool is_sserial_tx = false;
    codal::STM32SingleWireSerial sserial(steam32.io.PB_6);
    unsigned tx_counter = 0;

    steam32.serial.init(115200);
    sserial.init(115200);

    printf("\r\n");
    printf("********************************************************\r\n");
    printf("* Demonstration de la communication Single Wire serial *\r\n");
    printf("********************************************************\r\n");

    set_serial_mode(sserial, is_sserial_tx);

    while (true) {
        if (steam32.serial.isReadable() != 0) {
            switch (char(steam32.serial.getChar(codal::ASYNC))) {
                case 'T':
                case 't':
                    is_sserial_tx = true;
                    set_serial_mode(sserial, is_sserial_tx);
                    break;

                case 'R':
                case 'r':
                    is_sserial_tx = false;
                    set_serial_mode(sserial, is_sserial_tx);
                    break;

                default:
                    printf("Help\n\tr/R: Set single wire serial Rx mode\n\tt/T: Set single wire serial Tx mode\n\n");
                    break;
            }
        }

        if (is_sserial_tx) {
            if (tx_counter >= 10) {
                tx_counter = 0;
            }

            int res = sserial.putc(char(0x30 + tx_counter));
            printf("Send data: '%c' (byte send: %d)\n", char(0x30 + tx_counter), res);
            steam32.sleep(1000);
            tx_counter++;
        }
        else {
            int read = sserial.getc();
            if (read != DEVICE_NO_DATA) {
                printf("Received data: '%c'\n", char(read));
            }
        }
    }
}
