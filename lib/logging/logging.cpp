#include "logging.h"

void log(String message) {
    if (!showLogs) {
        return;
    } 
    
    Serial.println(message);
}

void logHeartsWithMessage(String message, int playerHeartCount) {
    String messageWithHearts = message + " (" + playerHeartCount + "/" + playerStartingHearts + ")";
    log(messageWithHearts);
}