#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

enum class Sound {
    VoiceStart,
    HeartsReplenished,
    HeartLost,
    GameOver,
    VoiceFinish
};

void initializeAudio() {
    mySoftwareSerial.begin(9600);
  
    Serial.println();
    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
    
    if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while(true){
        delay(0); // Code to compatible with ESP8266 watch dog.
        }
    }
    Serial.println(F("DFPlayer Mini online."));
    
    myDFPlayer.volume(volumne);  //Set volume value. From 0 to 30
}

int getSoundIndex(Sound sound) {
    switch (sound)
    {
        case Sound::VoiceStart:
          return 1;

        case Sound::HeartsReplenished:
           return 2;

        case Sound::HeartLost:
            return 3;

        case Sound::GameOver:
            return 4;

        case Sound::VoiceFinish:
            return 5;

        default:
            return 0;
    }
}

void playSound(int soundIndex) {
    // play audio file at index
    // -> index gets assigned on copy to sd card)
    myDFPlayer.play(soundIndex);

    // delay for program stability
    delay(100);
}

void playSound(Sound sound) {
    int soundIndex = getSoundIndex(sound);
    playSound(soundIndex);
}