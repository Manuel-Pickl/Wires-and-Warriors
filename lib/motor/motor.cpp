#include "motor.h"

unsigned long lastMotorStepTime = 0;
unsigned long lastBridgeStepTime = 0;

int getMotorSteps(int level) {
    switch (level) {
        case 1:
            return 0;
        case 2:
            return 500;
        case 3:
            return 500;
    }
}

int getMotorDelay(int level) {
    switch (level) {
        case 1:
            return 0;
        case 2:
            return 10000;
        case 3:
            return 2000;

        default:
            return 0;
    }
}

void turnMotor(int level) {
    unsigned long currentTime = millis();

    // if (currentTime - lastMotorStepTime >= getMotorDelay(level)) {
    //     // turn side motors one step
    //     digitalWrite(stepPinWire, HIGH);
    //     digitalWrite(stepPinWire, LOW);

    //     // Update the last execution time
    //     lastMotorStepTime = currentTime;
    // }
}

int tickCounter = 0;

void turnBridge() {
    unsigned long currentTime = millis();

    if (currentTime - lastBridgeStepTime >= 3000) {
        tickCounter++;

        const int pulsesForFullRotation = 6400;
        if (tickCounter >= pulsesForFullRotation) {
            // Toggle the direction of the motor
            digitalWrite(directionPinBridge, !digitalRead(directionPinBridge));

            // Reset the tick counter
            tickCounter = 0;
        }

        // turn bridge motor one step
        digitalWrite(stepPinBridge, HIGH);
        digitalWrite(stepPinBridge, LOW);

        // Update the last execution time
        lastBridgeStepTime = currentTime;
    }
}