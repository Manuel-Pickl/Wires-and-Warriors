#include "gameConstants.h"

// game
const int startingLevel = 1;
const int endLevel = 3;

const int playerStartingHearts = 6;
const int lifeLEDsCount = 6;

// error
const int errorCooldown = 1000; // milliseconds
const int flashsPerError = 3;
// error flash color:
// -> game.cpp > flashLEDsForError() > pixels.setPixelColor(i, white);

const int earliestFinishTime = 15000; // milliseconds
const int volume = 25; // 0-30
const int pulsesForFullRotation = 6400; // motor specific value
const int motorDelay = 10;

// debug
const bool showLogs = true;