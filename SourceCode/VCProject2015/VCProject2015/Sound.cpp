#include "Sound.h"
#include <iostream>
#include <sstream>
void Sound::Play(const char* location, const bool isLoop) {
	if (isLoop) {
		PlaySound(location, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
	else {
		PlaySound(location, NULL, SND_FILENAME | SND_ASYNC);
	}
	//PlaySound("game\\data\\audio\\Faster.wav", NULL, SND_FILENAME | SND_LOOP |  SND_ASYNC);
}