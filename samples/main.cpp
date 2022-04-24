#include "CodalFiber.h"
#include "STM32STEAM32_WB55RG.h"

#if defined(GPIO_SAMPLE)
#include "GPIOSample.h"
#elif defined(PIN_SAMPLE)
#include "PinSample.h"
#elif defined(ADC_SAMPLE)
#include "ADCSample.h"
#elif defined(SERIAL_SAMPLE)
#include "SerialSample.h"
#else
#include "BlinkSample.h"
#endif

codal::STM32STEAM32_WB55RG steam32;

auto main() -> int
{
    steam32.init();
    SAMPLE_MAIN(steam32);
    codal::release_fiber();
    return 0;
}
