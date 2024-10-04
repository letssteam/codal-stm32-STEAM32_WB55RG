#include "BlinkSample.h"

using namespace std;
using namespace codal;

void BlinkSample_main(codal::STEAM32_WB55RG& steam32)
{
    bool state = false;

    while (true) {
        steam32.io.PC_10.setDigitalValue((int)state);
        steam32.io.PC_12.setDigitalValue((int)!state);

        steam32.sleep(500);
        state = !state;
    }
}
