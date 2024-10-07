#pragma once

#include "CodalCompat.h"
#include "CodalComponent.h"
#include "CodalDevice.h"
#include "CodalDmesg.h"
#include "CodalFiber.h"
#include "CodalHeapAllocator.h"
#include "ErrorNo.h"
#include "ManagedString.h"
#include "ManagedType.h"
#include "MessageBus.h"
#include "STM32I2C.h"
#include "STM32LowLevelTimer.h"
#include "STM32SPI.h"
#include "STM32Serial.h"
#include "STeaMiIO.h"
#include "Timer.h"

// Status flag values
#define DEVICE_INITIALIZED 0x01

/**
 * Class definition for a STeaMi device.
 *
 * Represents the device as a whole, and includes member variables that represent various device drivers
 * used to control aspects of the STeaMi.
 */
namespace codal {
class STeaMi : public CodalComponent {
  public:
    STM32LowLevelTimer lowLevelTimer;
    Timer timer;
    MessageBus messageBus;
    STeaMiIO io;

    STM32Serial serial;
    STM32I2C i2cInt;
    STM32I2C i2cExt;
    STM32SPI spiExt;
    STM32SPI spiInt;

  private:
    /**
     * A listener to perform actions as a result of Message Bus reflection.
     *
     * In some cases we want to perform lazy instantiation of components, such as
     * the compass and the accelerometer, where we only want to add them to the idle
     * fiber when someone has the intention of using these components.
     */
    void onListenerRegisteredEvent(Event evt);

  public:
    /**
     * Constructor.
     *
     * Create a representation of a Genuino Zero device, which includes member variables
     * that represent various device drivers used to control aspects of the board.
     */
    STeaMi();

    /**
     * Post constructor initialisation method.
     */
    int init() override final;

    /**
     * Return the serial number of this device.
     *
     * @return A ManagedString representing the serial number of this device.
     *
     * @code
     * ManagedString serialNumber = uBit.getSerial();
     * @endcode
     */
    static ManagedString getSerial();

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
     * uBit.sleep(20); //sleep for 20ms
     * @endcode
     *
     * @note This operation is currently limited by the rate of the system timer, therefore
     *       the granularity of the sleep operation is limited to 4 ms, unless the rate of
     *       the system timer is modified.
     */
    void sleep(uint32_t milliseconds);

    /**
     * A periodic callback invoked by the fiber scheduler idle thread.
     * We use this for any low priority, background housekeeping.
     */
    virtual void idleCallback() override { codal_dmesg_flush(); }

    /**
     * Periodic callback from Device system timer.
     *
     */
    virtual void periodicCallback() override {}

    /**
     * Determine the time since this STeaMi was last reset.
     *
     * @return The time since the last reset, in milliseconds.
     *
     * @note This will value overflow after 1.6 months.
     */
    // TODO: handle overflow case.
    unsigned long systemTime();

    /**
     * Determines if any persistent storage needs to be erased following the reprogramming
     * of the micro:bit.
     *
     * @param forceErase Force an erase of user data, even if we have not detected a reflash event.
     */
    void eraseUserStorage(bool forceErase = false);
};

extern STeaMi* default_device_instance;
}  // namespace codal