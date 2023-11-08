#include "audio.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void initializeAudio() {
    mySoftwareSerial.begin(9600);
  
    log("Initializing DFPlayer ... (May take 3~5 seconds)");
    
    if (!myDFPlayer.begin(mySoftwareSerial)) {
        log("Unable to begin:");
        log("1.Please recheck the connection!");
        log("2.Please insert the SD card!");

        while(true) {
            delay(0);
        }
    }
    
    log("DFPlayer Mini online.");
    
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