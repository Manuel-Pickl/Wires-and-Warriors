#include "game.h"

#pragma region Variables

int cycle;
unsigned int gameStart;

unsigned int lastError;
unsigned int lastSoundLevelStartSingle = 0;

int level;

int playerHearts;
bool heartsChanged;

bool gameStarted;

Adafruit_NeoPixel pixels(lifeLEDsCount, lifeLEDsPin, NEO_GRB + NEO_KHZ800);
uint32_t green = pixels.Color(150, 0, 0);
uint32_t red = pixels.Color(0, 150, 0);
uint32_t white = pixels.Color(150, 150, 150);

#pragma endregion Variables

void initializeGame() {
    cycle = 0;
    lastError = -1 * errorCooldown;
    gameStart = 0;

    level = startingLevel;

    playerHearts = playerStartingHearts;
    heartsChanged = false;

    gameStarted = false;

    // initializeAudio();
}

void showHeartsWithMessage(String message) {
    String messageWithHearts = message + " (" + playerHearts + "/" + playerStartingHearts + ")";
    log(messageWithHearts);
}

#pragma region Errors 

void setError() {
    // update last error cycle
    lastError = millis();
}

bool playersHaveErrorCooldown() {
    unsigned int elapsedTimeSinceError = millis() - lastError;
    return elapsedTimeSinceError < errorCooldown;
}

#pragma endregion Errors

#pragma region Player Hearts

void finishGame(bool success) {
    Sound sound = success ? Sound::VoiceFinish : Sound::GameOver;
    playSound(sound);

    uint32_t color = success ? green : red;
    for(int i = 0; i < lifeLEDsCount * 3; i++) 
    {
        int ledIndex = i % lifeLEDsCount;
        pixels.clear();
        pixels.setPixelColor(ledIndex, color);
        pixels.show();
        delay(50);
    }

    initializeGame();
}

void removePlayerHeart() {
    playerHearts--;
    if (playerHearts <= 0) {
        log("You lost!");
        finishGame(false);
    }
    else {
        heartsChanged = true;
        showHeartsWithMessage("Heart lost!");
    }
}

void flashLEDsForError() {
    int elapsedTime = millis() - lastError;
    int intervalTime = errorCooldown / (flashsPerError * 2);
    unsigned int currentInterval = elapsedTime / intervalTime;

    // set every single led to red every flash interval
    pixels.clear();
    if (currentInterval % 2) {
        for(int i = 0; i < lifeLEDsCount; i++) 
        {
            pixels.setPixelColor(i, white);
        }
    }
    pixels.show();
}

void setHeartLEDs() {
    pixels.clear(); // Set all pixel colors to 'off'
    for(int i = 0; i < playerHearts; i++) 
    {
        pixels.setPixelColor(i, red);
    }
    pixels.show();  // Send the updated pixel colors to the hardware.
}

void toggleHeartLEDs() {
    if (!heartsChanged) {
        return;
    }

    if (playersHaveErrorCooldown()) {
        flashLEDsForError();
    }
    else {
        setHeartLEDs();
        heartsChanged = false;
    }
}

#pragma endregion Player Hearts

#pragma region Levels

void startLevel() {
    log("Level " + String(level) + " started");

    playerHearts = playerStartingHearts;
    heartsChanged = true;
    showHeartsWithMessage("Hearts replenished!");
    
    playSound(Sound::HeartsReplenished);
    delay(2000); // delay for definite audio finish

    gameStarted = true;
    gameStart = millis();
}

void finishLevel() {
    log("Level " + String(level) + " finished");
    
    if (level == 3) {
        log("You made it!");
        finishGame(true);
    }
    else {
        level++;
        startLevel();
    }
}

#pragma endregion Levels

#pragma region Touch

bool isFinishAllowed() {
    int elapsedGameTime = millis() - gameStart;
    bool isGameLongEnough = elapsedGameTime > earliestFinishTime; 
    
    return gameStarted && isGameLongEnough;
}

bool playerTouchesPin(int pin) {
    return !digitalRead(pin);
}

void checkStartTouch() {
    if (!gameStarted
        && playerTouchesPin(currentButtonLeftPin)
        // && playerTouchesPin(currentButtonRightPin)) {
        && true)
    {
        playSound(Sound::VoiceStart);
        delay(1800);
        startLevel();
    }
}

void checkEndTouch() {
    if (isFinishAllowed()
        && playerTouchesPin(currentButtonLeftPin)
        // && playerTouchesPin(currentButtonRightPin)) {
        && true) {
        finishLevel();
    }
}

void checkWireTouch() {
    if (gameStarted
        && playerTouchesPin(wirePin)
        && !playersHaveErrorCooldown()) {
        setError();
        removePlayerHeart();
        playSound(Sound::HeartLost);
    }
}

void toggleStartLEDs() {
    if (gameStarted) {
        return;
    }

    pixels.clear();
    
    if (playerTouchesPin(currentButtonLeftPin)) {
        // first half of life leds
        for(int i = 0; i < (lifeLEDsCount / 2); i++) 
        {
            pixels.setPixelColor(i, green);
        }

        // if (millis() - lastSoundLevelStartSingle > 5000) {
            // lastSoundLevelStartSingle = millis();
            // playSound(Sound::LevelStartSingle);
        // }
    }

    if (playerTouchesPin(currentButtonRightPin)) {
        // second half of life leds
        for(int i = (lifeLEDsCount / 2) - 1; i < lifeLEDsCount; i++) 
        {
            pixels.setPixelColor(i, green);
        }
    }
    
    pixels.show();
}

void checkSystemTouch() {
    cycle++;

    checkStartTouch();
    checkWireTouch();
    checkEndTouch();

    toggleHeartLEDs();
    toggleStartLEDs();
}

#pragma endregion Touch

#pragma region Play

void playGame() {
    // turn motor and check for system touches while turning
    for(int step = 0; step < getMotorSteps(level); step++) {
        checkSystemTouch();
        turnMotor(level);
    }

    checkSystemTouch();
}

#pragma endregion Play