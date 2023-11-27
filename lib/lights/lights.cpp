#include "lights.h"

Adafruit_NeoPixel pixels(lifeLEDsCount, lifeLEDsPin, NEO_GRB + NEO_KHZ800);
uint32_t green = pixels.Color(150, 0, 0);
uint32_t red = pixels.Color(0, 150, 0);
uint32_t white = pixels.Color(150, 150, 150);

void showHeartLights(int playerHeartCount) {
    pixels.clear(); // Set all pixel colors to 'off'
    for(int i = 0; i < playerHeartCount; i++) 
    {
        pixels.setPixelColor(i, red);
    }
    pixels.show();  // Send the updated pixel colors to the hardware.
}

void showErrorLights(int lastError) {
    int elapsedTime = millis() - lastError;
    int intervalTime = errorCooldown / (flashsPerError * 2);
    int currentInterval = elapsedTime / intervalTime;

    // set every single led to white every flash interval
    pixels.clear();
    if (currentInterval % 2) {
        for(int i = 0; i < lifeLEDsCount; i++) 
        {
            pixels.setPixelColor(i, white);
        }
    }
    pixels.show();
}

void showFinishLighting(bool success) {
    uint32_t color = success ? green : red;
    const int cycles = 5;
    for(int i = 0; i < lifeLEDsCount * cycles; i++) 
    {
        int ledIndex = i % lifeLEDsCount;
        pixels.clear();
        pixels.setPixelColor(ledIndex, color);
        pixels.show();
        delay(100);
    }
}

void showDefaultLights() {
    for(int i = 0; i < lifeLEDsCount; i++) 
    {
        pixels.setPixelColor(i, white);
    }
    pixels.show();
}