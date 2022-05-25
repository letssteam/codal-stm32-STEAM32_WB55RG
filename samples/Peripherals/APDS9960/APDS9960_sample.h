#pragma once

#include "APDS9960.h"
#include "STM32STEAM32_WB55RG.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN APDS9960_SampleMain
#endif

void APDS9960_SampleMain(codal::STM32STEAM32_WB55RG& steam32);
