#ifndef LOGGING_H
#define LOGGING_H

#include "../gameConstants/gameConstants.h"

#include <Arduino.h>

void log(String message);
void logHeartsWithMessage(String message, int playerHeartCount);

#endif // LOGGING_H