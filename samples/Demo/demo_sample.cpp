#include "demo_sample.h"

using namespace codal;
using namespace std;

#include <algorithm>
#include <cmath>
#include <functional>
#include <string>
#include <vector>

#include "APDS9960.h"
#include "HTS221.h"
#include "STM32Pin.h"
#include "STM32SAI.h"
#include "VL53L1X.h"
#include "WSEN-PADS.h"
#include "ism330dl.h"
#include "lis2mdl.h"
#include "mcp23009-e.h"
#include "menu.h"
#include "pcm_utils.h"
#include "pdm2pcm.h"
#include "ssd1327.h"
// #include "STM32SingleWireSerial.h"

constexpr uint16_t AUDIO_BUFFER = 256;

constexpr uint8_t MCP_GPIO_1    = 0;
constexpr uint8_t MCP_GPIO_2    = 1;
constexpr uint8_t MCP_GPIO_3    = 2;
constexpr uint8_t MCP_GPIO_4    = 3;
constexpr uint8_t MCP_GP_RIGHT  = 4;
constexpr uint8_t MCP_GP_BOTTOM = 5;
constexpr uint8_t MCP_GP_LEFT   = 6;
constexpr uint8_t MCP_GP_UP     = 7;

STM32SPI* spi       = nullptr;
STM32Pin* cs        = nullptr;
STM32Pin* dc        = nullptr;
STM32Pin* rst       = nullptr;
STM32Pin* led_red   = nullptr;
STM32Pin* led_green = nullptr;
STM32Pin* led_blue  = nullptr;
SSD1327_SPI* ssd    = nullptr;

STM32Pin* btnMenu = nullptr;
STM32Pin* btnA    = nullptr;
STM32Pin* btnB    = nullptr;
STM32Pin* buzzer  = nullptr;

MCP23009E* mcp  = nullptr;
HTS221* hts     = nullptr;
WSEN_PADS* pres = nullptr;
VL53L1X* tof    = nullptr;
STM32SAI* sai   = nullptr;
PDM2PCM pdm2pcm(16, 8, 0, 1);

APDS9960* apds = nullptr;
ISM330DL* ism  = nullptr;
LIS2MDL* lis   = nullptr;
// STM32SingleWireSerial* jacdac;

ScreenMenu* mainMenu = nullptr;

uint16_t rawMicData[AUDIO_BUFFER];
bool processedMicData = true;

enum SnakeDir { UP, RIGHT, DOWN, LEFT };

string fToStr(float value, unsigned pres)
{
    int ent = (int)value;
    int dec = (int)((value - ent) * pow(10, pres));

    return to_string(ent) + "." + to_string(abs(dec));
}

bool click_button(STM32Pin* btn)
{
    if (btn->getDigitalValue() == 0) {
        while (btn->getDigitalValue() == 0)
            ;

        return true;
    }

    return false;
}

void show_main_menu()
{
    mcp->interruptOnFalling(MCP_GP_BOTTOM, []() { mainMenu->moveDown(); });
    mcp->interruptOnFalling(MCP_GP_UP, []() { mainMenu->moveUp(); });

    mainMenu->show();

    while (1) {
        if (btnA->getDigitalValue() == 0) {
            while (btnA->getDigitalValue() == 0)
                ;
            break;
        }

        fiber_sleep(1);
    }

    mcp->disableInterrupt(MCP_GP_BOTTOM);
    mcp->disableInterrupt(MCP_GP_UP);
    mainMenu->execute();
}

void show_temp_hum()
{
    while (1) {
        fiber_sleep(125);

        if (click_button(btnMenu)) {
            break;
        }

        if (!hts->isTemperatureDataAvailable() || !hts->isHumidityDataAvailable()) {
            printf("HTS221 not ready\r\n");
            continue;
        }

        ssd->fill(0x00);
        ssd->drawText("Temperature: " + fToStr(hts->getTemperature(), 2) + " C", 5, 55, 0xFF);
        ssd->drawText("Humidite: " + fToStr(hts->getHumidity(), 2) + " %HR", 5, 65, 0xFF);

        ssd->show();
    }
}

void show_pressure()
{
    while (1) {
        fiber_sleep(125);

        if (click_button(btnMenu)) {
            break;
        }

        ssd->fill(0x00);
        ssd->drawText("Pression: " + fToStr(pres->getPressure(), 2) + " kPa", 5, 55, 0xFF);
        ssd->drawText("Temperature: " + fToStr(pres->getTemperature(), 2) + " C", 5, 65, 0xFF);

        ssd->show();
    }
}

void show_tof()
{
    while (1) {
        fiber_sleep(100);

        if (click_button(btnMenu)) {
            break;
        }

        ssd->fill(0x00);
        ssd->drawText("Distance: " + fToStr(tof->getDistance(), 2) + " mm", 5, 60, 0xFF);
        ssd->show();
    }
}

void show_acc_gyro_magn()
{
    int8_t selection = 0;

    while (1) {
        if (click_button(btnMenu)) {
            break;
        }

        if (mcp->getLevel(MCP_GP_LEFT) == MCP_LOGIC_LEVEL::LOW) {
            while (mcp->getLevel(MCP_GP_LEFT) == MCP_LOGIC_LEVEL::LOW)
                ;

            selection--;
        }

        if (mcp->getLevel(MCP_GP_RIGHT) == MCP_LOGIC_LEVEL::LOW) {
            while (mcp->getLevel(MCP_GP_RIGHT) == MCP_LOGIC_LEVEL::LOW)
                ;

            selection++;
        }

        ssd->fill(0x00);

        if (selection == 0) {
            ssd->drawText("Accelerometer", 25, 20, 0xFF);
            auto accel = ism->readAccelerometerData();

            ssd->drawText("X: " + fToStr(accel.x, 2), 20, 49, 0xFF);
            ssd->drawText("Y: " + fToStr(accel.y, 2), 20, 58, 0xFF);
            ssd->drawText("Z: " + fToStr(accel.z, 2), 20, 67, 0xFF);

            ssd->drawText("<- Magneto", 20, 87, 0xFF);
            ssd->drawText("-> Gyro", 20, 96, 0xFF);
        }
        else if (selection == 1) {
            ssd->drawText("Gyroscope", 30, 20, 0xFF);
            auto gyro = ism->readGyroscopeData();

            ssd->drawText("X: " + fToStr(gyro.x, 2), 20, 49, 0xFF);
            ssd->drawText("Y: " + fToStr(gyro.y, 2), 20, 58, 0xFF);
            ssd->drawText("Z: " + fToStr(gyro.z, 2), 20, 67, 0xFF);

            ssd->drawText("<- Accelero", 20, 87, 0xFF);
            ssd->drawText("-> Magneto", 20, 96, 0xFF);
        }
        else if (selection == 2) {
            ssd->drawText("Magnetometer", 25, 20, 0xFF);

            auto magn = lis->readData();

            ssd->drawText("X: " + fToStr(magn.x, 2), 20, 49, 0xFF);
            ssd->drawText("Y: " + fToStr(magn.y, 2), 20, 58, 0xFF);
            ssd->drawText("Z: " + fToStr(magn.z, 2), 20, 67, 0xFF);

            ssd->drawText("<- Gyro", 20, 87, 0xFF);
            ssd->drawText("-> Accelero", 20, 96, 0xFF);
        }
        else {
            selection = selection < 0 ? 2 : 0;
            continue;
        }

        ssd->show();
        fiber_sleep(125);
    }
}

void show_optical_sensor()
{
    while (1) {
        fiber_sleep(100);

        if (click_button(btnMenu)) {
            break;
        }

        std::array<uint16_t, 4> color_data = apds->getColors();

        ssd->fill(0x00);
        ssd->drawText("Color Sensor", 25, 20, 0xFF);
        ssd->drawText("(untested)", 25, 28, 0xFF);
        ssd->drawText("Red  : " + to_string(color_data[0]), 20, 49, 0xFF);
        ssd->drawText("Green: " + to_string(color_data[1]), 20, 58, 0xFF);
        ssd->drawText("Blue : " + to_string(color_data[2]), 20, 67, 0xFF);
        ssd->drawText("Clear: " + to_string(color_data[3]), 20, 76, 0xFF);
        ssd->show();
    }
}

void show_microphone()
{
    sai->startListening();

    while (1) {
        fiber_sleep(100);

        if (click_button(btnMenu)) {
            break;
        }

        if (!processedMicData) {
            auto conv = pdm2pcm.convert(rawMicData, AUDIO_BUFFER);

            float avg = 0;
            for (auto v : conv) {
                avg += float(v) / float(conv.size());
            }

            ssd->fill(0x00);
            ssd->drawText("Decibel: " + fToStr(PCMUtils::toDecibel(conv), 1) + "dB", 5, 60, 0xFF);
            ssd->show();

            processedMicData = true;
        }
    }

    sai->stopListening();
}

void micro_on_data(const int32_t* data)
{
    if (processedMicData) {
        for (uint16_t i = 0; i < AUDIO_BUFFER; ++i) {
            rawMicData[i] = uint16_t(data[i] & 0x0000FFFF);
        }

        processedMicData = false;
    }
}

void show_buzzer()
{
    uint8_t* cursor = new uint8_t(2);
    int* freq       = new int(440);

    mcp->interruptOnFalling(MCP_GP_BOTTOM, [=]() {
        int p     = pow(10, *cursor);
        int digit = int(*freq / p) % 10;
        if (digit == 0) {
            return;
        }

        *freq -= p;
        buzzer->setAnalogPeriodUs(1000000 / *freq);
        buzzer->setAnalogValue(255);
    });

    mcp->interruptOnFalling(MCP_GP_UP, [=]() {
        int p     = pow(10, *cursor);
        int digit = int(*freq / p) % 10;
        if (digit == 9) {
            return;
        }

        *freq += p;
        buzzer->setAnalogPeriodUs(1000000 / *freq);
        buzzer->setAnalogValue(255);
    });

    mcp->interruptOnFalling(MCP_GP_LEFT, [=]() {
        if (*cursor < 5) {
            (*cursor)++;
        }
    });

    mcp->interruptOnFalling(MCP_GP_RIGHT, [=]() {
        if (*cursor > 0) {
            (*cursor)--;
        }
    });

    buzzer->setAnalogPeriodUs(1000000 / *freq);
    buzzer->setAnalogValue(255);

    while (1) {
        if (click_button(btnMenu)) {
            break;
        }

        auto freqStr     = std::to_string(*freq);
        string cursorStr = "      ";

        while (freqStr.size() < 5) {
            freqStr = "0" + freqStr;
        }

        for (int8_t i = 4; i >= 0; --i) {
            if (i == *cursor) {
                cursorStr.push_back('^');
            }
            else {
                cursorStr.push_back(' ');
            }
        }

        ssd->fill(0x00);
        ssd->drawText("Freq: " + freqStr + "Hz", 15, 40, 0xFF);
        ssd->drawText(cursorStr, 15, 48, 0xFF);
        ssd->drawText("< / >: change digit", 5, 66, 0xFF);
        ssd->drawText("^ / v: de/increase", 5, 75, 0xFF);
        ssd->show();

        fiber_sleep(100);
    }

    buzzer->setAnalogValue(0);
    mcp->disableInterrupt(MCP_GP_BOTTOM);
    mcp->disableInterrupt(MCP_GP_UP);
    delete cursor;
    delete freq;
}

void show_button()
{
    while (1) {
        if (click_button(btnMenu)) {
            break;
        }

        bool up_state    = mcp->getLevel(MCP_GP_UP) == MCP_LOGIC_LEVEL::HIGH;
        bool down_state  = mcp->getLevel(MCP_GP_BOTTOM) == MCP_LOGIC_LEVEL::HIGH;
        bool left_state  = mcp->getLevel(MCP_GP_LEFT) == MCP_LOGIC_LEVEL::HIGH;
        bool right_state = mcp->getLevel(MCP_GP_RIGHT) == MCP_LOGIC_LEVEL::HIGH;
        bool a_state     = btnA->getDigitalValue() == 1;
        bool b_state     = btnB->getDigitalValue() == 1;

        ssd->fill(0x00);
        ssd->drawText("Up: " + string(up_state ? "HIGH" : "LOW"), 12, 33, 0xFF);
        ssd->drawText("Down: " + string(down_state ? "HIGH" : "LOW"), 7, 45, 0xFF);
        ssd->drawText("Left: " + string(left_state ? "HIGH" : "LOW"), 2, 56, 0xFF);
        ssd->drawText("Right: " + string(right_state ? "HIGH" : "LOW"), 2, 69, 0xFF);
        ssd->drawText("A: " + string(a_state ? "HIGH" : "LOW"), 7, 81, 0xFF);
        ssd->drawText("B: " + string(b_state ? "HIGH" : "LOW"), 12, 93, 0xFF);
        ssd->show();

        fiber_sleep(1);
    }
}

void show_rgb()
{
    uint8_t* select_line = new uint8_t(0);

    mcp->interruptOnFalling(MCP_GP_BOTTOM, [=]() {
        if (*select_line < 2) {
            (*select_line)++;
        }
    });

    mcp->interruptOnFalling(MCP_GP_UP, [=]() {
        if (*select_line > 0) {
            (*select_line)--;
        }
    });

    while (1) {
        if (click_button(btnMenu)) {
            break;
        }

        if (click_button(btnA)) {
            switch (*select_line) {
                case 0:
                    led_red->setDigitalValue(!led_red->getDigitalValue());
                    break;

                case 1:
                    led_green->setDigitalValue(!led_green->getDigitalValue());
                    break;

                case 2:
                    led_blue->setDigitalValue(!led_blue->getDigitalValue());
                    break;
            }
        }

        ssd->fill(0x00);
        ssd->drawText("Toggle Red LED", 15, 51, 0xFF);
        ssd->drawText("Toggle Blue LED", 15, 60, 0xFF);
        ssd->drawText("Toggle Green LED", 15, 69, 0xFF);
        ssd->drawText(">", 5, (*select_line) * 9 + 51, 0xFF);
        ssd->show();

        fiber_sleep(1);
    }

    mcp->disableInterrupt(MCP_GP_BOTTOM);
    mcp->disableInterrupt(MCP_GP_UP);
    led_red->setDigitalValue(0);
    led_green->setDigitalValue(0);
    led_blue->setDigitalValue(0);
    delete select_line;
}

void show_screen()
{
    ssd->fill(0x00);

    uint16_t color = 0xFF;
    uint8_t shape  = 4;

    while (1) {
        for (unsigned i = 0; i < 35; ++i) {
            if (click_button(btnMenu)) {
                return;
            }

            if (shape == 0)
                ssd->drawCircle(64, 64, i, true, color);
            else if (shape == 1)
                ssd->drawRectangle(64 - i * 2, 64 - i * 2, 64 + i * 2, 64 + i * 2, true, color);
            else if (shape == 2)
                ssd->drawPolygon(64, 64, 5, i * 2, 3, color);
            else if (shape == 3)
                ssd->drawPolygon(64, 64, 3, i * 2, 3, color);
            else if (shape == 4)
                for (float deg = 0; deg < 360; deg += 0.5) {
                    float theta = deg * 0.0174533;
                    float r     = 10 * theta;  // pow(5, theta);

                    ssd->drawPixel(r * cos(r) + 64, r * sin(r) + 64, color);
                }

            ssd->show();
        }

        color = ~color;
        shape++;
        if (shape >= 5) shape = 0;
    }
}

void show_battery()
{
    while (1) {
        if (click_button(btnMenu)) {
            break;
        }

        ssd->fill(0x00);
        ssd->drawText("  Not available...", 5, 60, 0xFF);
        ssd->show();

        fiber_sleep(100);
    }
}

void show_pads()
{
    int r = 3;

    while (1) {
        if (click_button(btnMenu)) {
            break;
        }

        bool gp1 = mcp->getLevel(MCP_GPIO_1) == MCP_LOGIC_LEVEL::HIGH;
        bool gp2 = mcp->getLevel(MCP_GPIO_2) == MCP_LOGIC_LEVEL::HIGH;
        bool gp3 = mcp->getLevel(MCP_GPIO_3) == MCP_LOGIC_LEVEL::HIGH;
        bool gp4 = mcp->getLevel(MCP_GPIO_4) == MCP_LOGIC_LEVEL::HIGH;

        ssd->fill(0x00);
        ssd->drawCircle(8, 41, r, true, 0xFF);
        ssd->drawCircle(14, 30, r, gp3, 0xFF);
        ssd->drawCircle(22, 20, r, gp4, 0xFF);
        ssd->drawCircle(32, 13, r, false, 0xFF);
        ssd->drawChar('G', 30, 10, 0xFF);
        ssd->drawChar('V ', 6, 38, 0x00);

        ssd->drawCircle(119, 41, r, true, 0xFF);
        ssd->drawCircle(113, 30, r, gp2, 0xFF);
        ssd->drawCircle(105, 20, r, gp1, 0xFF);
        ssd->drawCircle(95, 13, r, false, 0xFF);
        ssd->drawChar('G', 93, 10, 0xFF);
        ssd->drawChar('V', 117, 38, 0x00);

        ssd->drawChar(gp3 ? '1' : '0', 12, 27, gp3 ? 0x00 : 0xFF);
        ssd->drawChar(gp4 ? '1' : '0', 20, 17, gp4 ? 0x00 : 0xFF);
        ssd->drawChar(gp2 ? '1' : '0', 111, 27, gp2 ? 0x00 : 0xFF);
        ssd->drawChar(gp1 ? '1' : '0', 103, 17, gp1 ? 0x00 : 0xFF);

        ssd->show();

        fiber_sleep(10);
    }
}

void show_jacdac()
{
    // ssd->fill(0x00);
    // ssd->drawText("  Serial output...", 5, 60, 0xFF);
    // ssd->show();

    ssd->fill(0x00);
    ssd->drawText("  Not available...", 5, 60, 0xFF);
    ssd->show();

    while (1) {
        if (click_button(btnMenu)) {
            break;
        }

        // int rec = jacdac->getc();
        // while (rec > 0) {
        //     printf("%c", char(rec));
        //     rec = jacdac->getc();
        // }

        fiber_sleep(1);
    }
}
void show_qwic()
{
    ssd->fill(0x00);
    ssd->drawText("  Not available...", 5, 60, 0xFF);
    ssd->show();

    while (1) {
        if (click_button(btnMenu)) {
            break;
        }

        fiber_sleep(1);
    }
}

void Demo_main(codal::STM32STEAM32_WB55RG& steam32)
{
    spi     = &steam32.spi1;
    cs      = &steam32.io.PD_0;
    dc      = &steam32.io.PB_4;
    rst     = &steam32.io.PA_12;
    ssd     = new SSD1327_SPI(*spi, *cs, *dc, *rst, 128, 128);
    btnMenu = &steam32.io.PA_0;
    btnA    = &steam32.io.PA_7;
    btnB    = &steam32.io.PA_8;
    buzzer  = &steam32.io.PA_11;

    led_red   = &steam32.io.PC_12;
    led_green = &steam32.io.PC_11;
    led_blue  = &steam32.io.PC_10;

    buzzer->setAnalogValue(0);

    steam32.serial.init(115200);
    steam32.sleep(500);

    printf("Init peripherals !\r\n");

    ssd->init();
    ssd->fill(0x00);
    ssd->drawText("Initialization...", 20, 60, 0xFF);
    ssd->show();

    mcp  = new MCP23009E(steam32.i2c1, 0x40, steam32.io.PB_1, steam32.io.PB_0);
    hts  = new HTS221(&steam32.i2c1, 0xBE);
    pres = new WSEN_PADS(steam32.i2c1, 0xBA);
    apds = new APDS9960(steam32.i2c1, 0x72);
    tof  = new VL53L1X(&steam32.i2c1);
    ism  = new ISM330DL(&steam32.i2c1);
    lis  = new LIS2MDL(&steam32.i2c1);
    sai  = new STM32SAI(&steam32.io.PA_10, &steam32.io.PA_3, GPIO_AF3_SAI1, AUDIO_BUFFER);
    // jacdac = new STM32SingleWireSerial(steam32.io.PB_6);

    mcp->setup(MCP_GPIO_1, MCP_DIR::INPUT, MCP_PULLUP::PULLUP);
    mcp->setup(MCP_GPIO_2, MCP_DIR::INPUT, MCP_PULLUP::PULLUP);
    mcp->setup(MCP_GPIO_3, MCP_DIR::INPUT, MCP_PULLUP::PULLUP);
    mcp->setup(MCP_GPIO_4, MCP_DIR::INPUT, MCP_PULLUP::PULLUP);
    mcp->setup(MCP_GP_RIGHT, MCP_DIR::INPUT);
    mcp->setup(MCP_GP_BOTTOM, MCP_DIR::INPUT);
    mcp->setup(MCP_GP_LEFT, MCP_DIR::INPUT);
    mcp->setup(MCP_GP_UP, MCP_DIR::INPUT);

    hts->init();
    hts->setOutputRate(codal::HTS221_OUTPUT_RATE::RATE_7HZ);

    pres->init();

    tof->init();

    ism->init();
    ism->setAccelerometerODR(ISM_ODR::F_1_66_KHZ);
    ism->setGyroscopeODR(ISM_ODR::F_208_HZ);

    lis->init();
    lis->setODR(LIS2_ODR::F_50_HZ);
    lis->setLowPassFilter(true);

    apds->init();

    if (!sai->init()) {
        printf("Failed to init SAI\r\n");
    }
    sai->onReceiveData(micro_on_data);

    // jacdac->init(1000000);

    steam32.sleep(500);

    ssd->fill(0x00);
    ssd->drawText("Hello STeamy !", 20, 60, 0xFF);
    ssd->show();
    printf("Hello STeamy !\r\n");
    steam32.sleep(1500);

    vector<MenuEntry> mainMenuEntries = {{"Temp & Hum", []() -> void { show_temp_hum(); }},
                                         {"Pressure", []() -> void { show_pressure(); }},
                                         {"Time Of Flight", []() -> void { show_tof(); }},
                                         {"Acc / Gyro / Magn", []() -> void { show_acc_gyro_magn(); }},
                                         {"Color Sensor", []() -> void { show_optical_sensor(); }},
                                         {"Microphone", []() -> void { show_microphone(); }},
                                         {"Buzzer", []() -> void { show_buzzer(); }},
                                         {"Buttons", []() -> void { show_button(); }},
                                         {"LEDs", []() -> void { show_rgb(); }},
                                         {"Screen", []() -> void { show_screen(); }},
                                         {"Battery", []() -> void { show_battery(); }},
                                         {"Pads \"tete\"", []() -> void { show_pads(); }},
                                         {"(QWIC)", []() -> void { show_qwic(); }},
                                         {"(jacdac)", []() -> void { show_jacdac(); }}};
    mainMenu                          = new ScreenMenu(*ssd, mainMenuEntries);

    while (1) {
        show_main_menu();
    }
}