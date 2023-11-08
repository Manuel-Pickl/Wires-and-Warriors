#pragma region Includes

#include "../lib/game/game.h"
#include "../lib/pins/pins.h"

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "SoftwareSerial.h"

#pragma endregion Includes

#pragma region Setup

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
    // motor wire
    pinMode(stepPinWire, OUTPUT);
}

#pragma endregion Setup

#pragma region Arduino

void setup() {
  initializeSerialMonitor();
  initializeLEDs();

  // set PinMode
  setInputPinModes();
  setOutputPinModes();

  initializeGame();
  // initializeAudio();

  log("game initialized");
}

void loop() {
  playGame();
}

#pragma endregion Arduino