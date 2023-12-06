#ifndef GAME_H
#define GAME_H

#include "../gameConstants/gameConstants.h"
#include "../lights/lights.h"
#include "../pins/pins.h"
#include "../motor/motor.h"
#include "../audio/audio.h"
#include "../logging/logging.h"
#include "../touch/touch.h"

#include <Arduino.h>

extern int cycle;
extern int gameStart;
extern long long lastError;
extern int lastSoundLevelStartSingle;
extern int level;
extern int playerHeartCount;
extern bool heartsChanged;
extern bool gameStarted;

void tick();
void initializeGame();
void finishGame(bool success);
void startLevel();
void finishLevel();

void setError();
bool playersHaveErrorCooldown();
bool isFinishAllowed();
void removePlayerHeart();

void logHeartsWithMessage(String message);

bool checkStartTouch();
bool checkEndTouch();
bool checkWireTouch();

void showHeartLights();

#endif // GAME_H