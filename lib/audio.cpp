#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

enum class Sound {
    LevelStartSingle,
    LevelStartDouble,
    LevelFinish,
    VoiceStart,
    VoiceFinish,
    HeartLost,
    GameOver
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
    
    myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

int getSoundIndex(Sound sound) {
    switch (sound)
    {
        case Sound::LevelStartSingle:
          return 1;

        case Sound::LevelStartDouble:
           return 2;

        case Sound::VoiceStart:
          return 3;

        case Sound::LevelFinish:
            return 4;

        case Sound::VoiceFinish:
            return 5;

        case Sound::HeartLost:
            return 6;

        case Sound::GameOver:
            return 7;

        default:
            break;
    }
}

void playSound(Sound sound) {
    int soundIndex = getSoundIndex(sound);
    myDFPlayer.play(soundIndex);
}

void playSound(int soundIndex) {
    myDFPlayer.play(soundIndex);
}