#include "../lib/game/game.h"
#include "../lib/pins/pins.h"

#include <Arduino.h>

void initializeSerialMonitor() {
    // Start the serial communication
    Serial.begin(115200);
    while (!Serial) {}
}

void initializeLEDs() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();
}

void setInputPinModes() {
    // wire
    pinMode(wirePin, INPUT_PULLUP);

    // current buttons
    pinMode(currentButtonLeftPin, INPUT_PULLUP);
    pinMode(currentButtonRightPin, INPUT_PULLUP);
}

void setOutputPinModes() {
    // motor wires
    pinMode(stepPinWire, OUTPUT);
    pinMode(stepPinBridge, OUTPUT);
    pinMode(directionPinBridge, OUTPUT);
    pinMode(leftLEDPin, OUTPUT);
    pinMode(rightLEDPin, OUTPUT);
}

void setup() {
  initializeSerialMonitor();
  initializeLEDs();

  // set PinMode
  setInputPinModes();
  setOutputPinModes();

  initializeGame();
  initializeAudio();

  log("game initialized");
}

void loop() {
  playGame();
}