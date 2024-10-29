#include "CodalFiber.h"
#include "STeaMi.h"

codal::STeaMi steami;

auto main() -> int
{
    bool state = false;

    steami.init();

    while (true) {
        steami.io.ledBlue.setDigitalValue((int)state);
        steami.io.ledRed.setDigitalValue((int)!state);

        steami.sleep(500);
        state = !state;
    }
    codal::release_fiber();
    return 0;
}
