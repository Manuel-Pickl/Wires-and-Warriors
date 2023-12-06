#ifndef LIGHTS_H
#define LIGHTS_H

#include "../gameConstants/gameConstants.h"
#include "../pins/pins.h"
#include "../touch/touch.h"

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel pixels;
extern uint32_t green;
extern uint32_t red;
extern uint32_t white;

void showGameNotStarted();
void showHearts(int playerHeartCount);
void showError(int lastError);
void showFinishLighting(bool success);
void showRingLights();

#endif // LIGHTS_H