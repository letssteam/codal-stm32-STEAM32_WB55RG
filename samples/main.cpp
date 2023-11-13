#include "CodalFiber.h"
#include "STM32STEAM32_WB55RG.h"

#if defined(BUTTONS_SAMPLE)
#include "ButtonSample.h"
#elif defined(SERIAL_SAMPLE)
#include "SerialSample.h"
#elif defined(VL53L1X_SAMPLE)
#include "VL53L1X_sample.h"
#elif defined(HTS221_SAMPLE)
#include "HTS221_sample.h"
#elif defined(WSEN_PADS_SAMPLE)
#include "WSEN-PADS_sample.h"
#elif defined(SCANNER_I2C)
#include "ScannerI2C.h"
#elif defined(OLED_SSD1327)
#include "OLED_SSD1327.h"
#elif defined(APDS9960)
#include "APDS9960_sample.h"
#elif defined(DEMO)
#include "demo_sample.h"
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
