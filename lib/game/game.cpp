#include "game.h"

int cycle;
int gameStart;

int lastError;
int lastSoundLevelStartSingle = 0;

int level;

int playerHeartCount;
bool heartsChanged;

bool gameStarted;

void initializeGame() {
    cycle = 0;
    lastError = -1 * errorCooldown;
    gameStart = 0;

    level = startingLevel;

    playerHeartCount = playerStartingHearts;
    heartsChanged = false;

    gameStarted = false;
    
    showDefaultLights();
}


void playGame() {
    // turn motor and check for system touches while turning
    for(int step = 0; step < getMotorSteps(level); step++) {
        tick();

        if (gameStarted) {
            // turnBridge();
            turnMotor(level);
        }
    }

    tick();

    if (gameStarted) {
        turnBridge();
    }
}

void showHeartsWithMessage(String message) {
    String messageWithHearts = message + " (" + playerHeartCount + "/" + playerStartingHearts + ")";
    log(messageWithHearts);
}

void setError() {
    // update last error cycle
    lastError = millis();
}

bool playersHaveErrorCooldown() {
    int elapsedTimeSinceError = millis() - lastError;
    return elapsedTimeSinceError < errorCooldown;
}

void finishGame(bool success) {
    playFinishSound(success);
    showFinishLighting(success);
    if (success) {
        playSound(Sound::Code);
    }

    initializeGame();
}

void removePlayerHeart() {
    playerHeartCount--;
    if (playerHeartCount <= 0) {
        log("You lost!");
        finishGame(false);
    }
    else {
        heartsChanged = true;
        showHeartsWithMessage("Heart lost!");
    }
}

void startLevel() {
    log("Level " + String(level) + " started");

    playerHeartCount = playerStartingHearts;
    heartsChanged = true;
    showHeartsWithMessage("Hearts replenished!");
    
    playSound(Sound::HeartsReplenished);
    delay(2000); // delay for definite audio finish

    gameStarted = true;
    gameStart = millis();
}

void finishLevel() {
    log("Level " + String(level) + " finished");
    
    if (level == endLevel) {
        log("You made it!");
        finishGame(true);
    }
    else {
        level++;
        startLevel();
    }
}

bool isFinishAllowed() {
    int elapsedGameTime = millis() - gameStart;
    bool isGameLongEnough = elapsedGameTime > earliestFinishTime; 
    
    return gameStarted && isGameLongEnough;
}

void tick() {
    cycle++;

    toggleLights();

    if (checkStartTouch()) {
        toggleLights();
        playSound(Sound::VoiceStart);
        delay(1800);
        startLevel();
    }

    if (checkWireTouch()) {
        playSound(Sound::HeartLost);
        setError();
        removePlayerHeart();
    }
    
    if (checkEndTouch()) {
        finishLevel();
    }
}

#pragma region touch

bool checkStartTouch() {
    if (gameStarted) {
        return false;
    }

    if (!bothPlayersTouchRing()) {
        return false;
    }
        
    return true;
}

bool checkEndTouch() {
    if (!isFinishAllowed()) {
        return false;
    }
    
    if (!bothPlayersTouchRing()) {
        return false;
    }

    return true;
}

bool checkWireTouch() {
    if (!gameStarted) {
        return false;
    }

    if (playersHaveErrorCooldown()) {
        return false;
    }

    if (!playerTouchesPin(wirePin)) {
        return false;
    }

    return true;
}

#pragma endregion touch

#pragma region lights


void toggleLights() {
    toggleHeartLights();
    toggleStartingLights();
}

void toggleHeartLights() {
    if (!heartsChanged) {
        return;
    }

    if (playersHaveErrorCooldown()) {
        showErrorLights(lastError);
    }
    else {
        showHeartLights(playerHeartCount);
        heartsChanged = false;
    }
}

void toggleStartingLights() {
    digitalWrite(leftLEDPin, LOW);
    digitalWrite(rightLEDPin, LOW);
 
    if (playerTouchesPin(currentButtonLeftPin)) {
        digitalWrite(leftLEDPin, HIGH);
    }

    if (playerTouchesPin(currentButtonRightPin)) {
        digitalWrite(rightLEDPin, HIGH);
    }
}

#pragma endregion lights
