#pragma region Includes

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../gameConstants/gameConstants.h"
#include "../pins/pins.h"
#include "../motor/motor.h"
#include "../audio/audio.h"
#include "../logging/logging.h"

#pragma endregion Includes

#pragma region Variables

extern int cycle;
extern unsigned int gameStart;
extern unsigned int lastError;
extern unsigned int lastSoundLevelStartSingle;
extern int level;
extern int playerHearts;
extern bool heartsChanged;
extern bool gameStarted;

extern Adafruit_NeoPixel pixels;
extern uint32_t green;
extern uint32_t red;
extern uint32_t white;

void initializeGame();
void showHeartsWithMessage(String message);
void setError();
bool playersHaveErrorCooldown();
void finishGame(bool success);
void removePlayerHeart();
void flashLEDsForError();
void setHeartLEDs();
void toggleHeartLEDs();
void startLevel();
void finishLevel();
bool isFinishAllowed();
bool playerTouchesPin(int pin);
void checkStartTouch();
void checkEndTouch();
void checkWireTouch();
void toggleStartLEDs();
void checkSystemTouch();
void playGame();