#include "motor.h"

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
    // turn side motors one step
    digitalWrite(stepPinWire, HIGH);
    delayMicroseconds(getMotorDelay(level));
    digitalWrite(stepPinWire, LOW);
}

int tickCounter = 0;
void turnBridge() {
    tickCounter++;

    if (tickCounter >= 3500) {
        // Toggle the direction of the motor
        digitalWrite(directionPinBridge, !digitalRead(directionPinBridge));

        // Reset the tick counter
        tickCounter = 0;
    }

    // turn bridge motor one step
    digitalWrite(stepPinBridge, HIGH);
    delayMicroseconds(3000);
    digitalWrite(stepPinBridge, LOW);
}