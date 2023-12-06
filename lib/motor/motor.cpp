#include "motor.h"

long lastBridgeTurnTime = 0;
long lastMotorTurnTime = 0;
int tickCounter = 0;

int getMotorRotations(int level) {
    switch (level) {
        case 2:
            return 1;
        case 3:
            return 3;
        default:
            return 0;
    }
}

bool timeToTurnSides() {
    long currentTime = millis();
    long elapsedTime = currentTime - lastMotorTurnTime;
    bool timeToTurn = elapsedTime >= motorDelay;

    if (timeToTurn) {
        lastMotorTurnTime = currentTime;
    }

    return timeToTurn;
}

bool timeToTurnBridge() {
    long currentTime = millis();
    long elapsedTime = currentTime - lastBridgeTurnTime;
    bool timeToTurn = elapsedTime >= motorDelay;

    if (timeToTurn) {
        lastBridgeTurnTime = currentTime;
    }

    return timeToTurn;
}

void turnSides(int level) {
    if (!timeToTurnSides()) {
        return;
    }

    for (int i = 0; i < getMotorRotations(level); i++) {
        // turn side motors one step
        digitalWrite(stepPinWire, HIGH);
        delayMicroseconds(1);
        digitalWrite(stepPinWire, LOW);
    }
}

void turnBridge() {
    if (!timeToTurnBridge()) {
        return;
    }

    // turn bridge motor one step
    digitalWrite(stepPinBridge, HIGH);
    delayMicroseconds(1);
    digitalWrite(stepPinBridge, LOW);
    
    if (tickCounter >= pulsesForFullRotation) {
        // change bridge rotation
        digitalWrite(directionPinBridge, !digitalRead(directionPinBridge));
        tickCounter = 0;
    }

    tickCounter++;
}