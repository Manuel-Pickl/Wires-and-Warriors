#include "logging.h"

void log(String message) {
    if (!showLogs) {
        return;
    } 
    
    Serial.println(message);
}