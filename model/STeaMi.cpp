#include "STeaMi.h"

using namespace codal;

STeaMi* codal::default_device_instance = nullptr;

/**
 * Constructor.
 *
 * Create a representation of a device, which includes member variables
 * that represent various device drivers used to control aspects of the STM32 IOT node.
 */
STeaMi::STeaMi()
    : lowLevelTimer(TIM2, TIM2_IRQn),
      timer(lowLevelTimer),
      io(),
      serial(io.serialTx, io.serialRx),
      i2cInt(io.intSda, io.intScl),
      i2cExt(io.extsda, io.extScl),
      spiExt(io.miso, io.mosi, io.sck),
      spiInt(io.misoDisplay, io.mosiDisplay, io.sckDisplay)
{
    // Clear our status
    status                  = 0;
    default_device_instance = this;
    default_serial_debug    = &serial;
    // this->init();
}

/**
 * Post constructor initialisation method.
 *
 * This call will initialised the scheduler, memory allocator and Bluetooth stack.
 *
 * This is required as the Bluetooth stack can't be brought up in a
 * static context i.e. in a constructor.
 *
 * @code
 * STeaMi.init();
 * @endcode
 *
 * @note This method must be called before user code utilises any functionality
 *       contained within the STeaMi class.
 */
int STeaMi::init()
{
    if ((status & DEVICE_INITIALIZED) != 0) {
        return DEVICE_NOT_SUPPORTED;
    }
    status |= DEVICE_INITIALIZED;

    // codal_dmesg_set_flush_fn(STEAM32_WB55RG_dmesg_flush);

    // Bring up fiber scheduler.
    scheduler_init(messageBus);

    for (int i = 0; i < DEVICE_COMPONENT_COUNT; i++) {
        if (CodalComponent::components[i] != nullptr) {
            CodalComponent::components[i]->init();
        }
    }

    status |= DEVICE_COMPONENT_STATUS_IDLE_TICK;

    return DEVICE_OK;
}

/**
 * Return the serial number of this device.
 *
 * @return A ManagedString representing the serial number of this device.
 *
 * @code
 * ManagedString serialNumber = uBit.getSerial();
 * @endcode
 */
ManagedString STeaMi::getSerial()
{
    uint64_t n = target_get_serial();
    int d      = 1'000'000'000;
    int n1     = n % d;
    n /= d;
    int n2 = n % d;
    n /= d;
    int n3 = n % d;
    n /= d;
    ManagedString s1(n1);
    ManagedString s2(n2);
    ManagedString s3(n3);
    ManagedString s = s3 + s2 + s1;
    return s;
}

/**
 * Delay execution for the given amount of time.
 *
 * If the scheduler is running, this will deschedule the current fiber and perform
 * a power efficient, concurrent sleep operation.
 *
 * If the scheduler is disabled or we're running in an interrupt context, this
 * will revert to a busy wait.
 *
 * Alternatively: wait, wait_ms, wait_us can be used which will perform a blocking sleep
 * operation.
 *
 * @param milliseconds the amount of time, in ms, to wait for. This number cannot be negative.
 *
 * @code
 * steami.sleep(20); //sleep for 20ms
 * @endcode
 *
 * @note This operation is currently limited by the rate of the system timer, therefore
 *       the granularity of the sleep operation is limited to 4 ms, unless the rate of
 *       the system timer is modified.
 */
void STeaMi::sleep(uint32_t milliseconds)
{
    fiber_sleep(milliseconds);
}

/**
 * Determine the time since this STeaMi was last reset.
 *
 * @return The time since the last reset, in milliseconds.
 *
 * @note This will value overflow after 1.6 months.
 */
unsigned long STeaMi::systemTime()
{
    return system_timer_current_time();
}

extern "C" int __io_putchar(int ch);

void STeaMi_dmesg_flush()
{
#if CONFIG_ENABLED(DMESG_SERIAL_DEBUG)
    #if DEVICE_DMESG_BUFFER_SIZE > 0
    if (codalLogStore.ptr > 0 && (default_device_instance != nullptr)) {
        for (uint32_t i = 0; i < codalLogStore.ptr; i++) {
            __io_putchar(codalLogStore.buffer[i]);
        }
        codalLogStore.ptr = 0;
    }
    #endif
#endif
}
