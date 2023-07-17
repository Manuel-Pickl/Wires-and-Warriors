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
    }
}

void turnMotor(int level) {
    // turn motor one step
    digitalWrite(stepPinWire,HIGH);
    delayMicroseconds(getMotorDelay(level));
    digitalWrite(stepPinWire,LOW);
}