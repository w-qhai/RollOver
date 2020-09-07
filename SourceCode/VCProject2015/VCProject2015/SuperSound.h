#pragma once
#include <iostream>
#include <thread>
#include <Windows.h>
#include <mmsystem.h>
#include "ConfigConvert.h"
#pragma comment(lib, "winmm.lib")


class SuperSound {

private:
	static const char* configPath;
	static const int maxMusicLength;
	
public:

	static void sendASoundCommand(const char* key);
	static void closeAndPlay(const char* openkey, const char* playkey, const char* closekey, int maxMusicLength = 2);
	
};