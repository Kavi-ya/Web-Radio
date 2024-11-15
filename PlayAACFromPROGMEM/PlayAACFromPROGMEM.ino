#include <Arduino.h>
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "FightClub.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup()
{
  Serial.begin(115200);

  audioLogger = &Serial;
  in = new AudioFileSourcePROGMEM(FightClub, sizeof(FightClub));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out -> SetGain(1.0);   //   out -> SetGain(0.125); 

  aac->begin(in, out);
}


void loop()
{
  if (aac->isRunning()) {
    aac->loop();
  } else {
    aac -> stop();
    Serial.printf("AAC done\n");
    delay(1000);
  }
}

