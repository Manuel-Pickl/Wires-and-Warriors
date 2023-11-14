#ifndef MOTOR_H
#define MOTOR_H

#include "../pins/pins.h"
#include <Arduino.h>

int getMotorSteps(int level);
int getMotorDelay(int level);
void turnMotor(int level);
void turnBridge();

#endif // MOTOR_H