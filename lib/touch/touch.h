#ifndef TOUCH_H
#define TOUCH_H

#include "../pins/pins.h"

#include <Arduino.h>

bool playerTouchesPin(int pin);
bool bothPlayersTouchRing();

#endif // TOUCH_H