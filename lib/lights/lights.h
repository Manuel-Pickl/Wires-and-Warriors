#ifndef LIGHTS_H
#define LIGHTS_H

#include "../gameConstants/gameConstants.h"
#include "../pins/pins.h"

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel pixels;
extern uint32_t green;
extern uint32_t red;
extern uint32_t white;

void showHeartLights(int playerHeartCount);
void showErrorLights(int lastError);
void showFinishLighting(bool success);

#endif // LIGHTS_H