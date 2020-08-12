#pragma once
#include <string>
#include <fstream>


class ConfigConvert {

public:
	static bool addConfig(const char* configPath, const char* configKey, const char* configValue, const char* configComment);

	static std::string getConfig(const char* configPath, const char* configKey);

};