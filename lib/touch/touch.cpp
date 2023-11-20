#include "touch.h"

bool playerTouchesPin(int pin) {
    return !digitalRead(pin);
}

bool bothPlayersTouchRing() {
    return (playerTouchesPin(currentButtonLeftPin) 
        && playerTouchesPin(currentButtonRightPin));
}