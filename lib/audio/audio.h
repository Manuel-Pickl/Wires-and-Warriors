#ifndef AUDIO_H
#define AUDIO_H

#include "../gameConstants/gameConstants.h"
#include "../logging/logging.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

enum class Sound {
    VoiceStart,
    HeartsReplenished,
    HeartLost,
    GameOver,
    VoiceFinish,
    Code
};

extern SoftwareSerial mySoftwareSerial;
extern DFRobotDFPlayerMini myDFPlayer;

void initializeAudio();
int getSoundIndex(Sound sound);
void playSound(int soundIndex);
void playSound(Sound sound);
void playFinishSound(bool success);

#endif // AUDIO_H