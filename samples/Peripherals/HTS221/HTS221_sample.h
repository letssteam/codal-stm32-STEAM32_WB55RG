#pragma once

#include "HTS221.h"
#include "STM32STEAM32_WB55RG.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN hts221Sample
#endif

void hts221Sample(codal::STM32STEAM32_WB55RG& steam32);
