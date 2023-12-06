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
extern int lastError;
extern int lastSoundLevelStartSingle;
extern int level;
extern int playerHeartCount;
extern bool heartsChanged;
extern bool gameStarted;

void initializeGame();
void showHeartsWithMessage(String message);
void setError();
bool playersHaveErrorCooldown();
void finishGame(bool success);
void removePlayerHeart();
void startLevel();
void finishLevel();
bool isFinishAllowed();
void tick();
void playGame();

bool checkStartTouch();
bool checkEndTouch();
bool checkWireTouch();

void showHeartLights();
void showHeartLights();
void showRingLights();

#endif // GAME_H