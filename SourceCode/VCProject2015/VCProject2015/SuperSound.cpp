#include "SuperSound.h"
/// <summary>
/// 配置文件位置(相对路径或绝对路径)
/// </summary>

const char* SuperSound::configPath = "pvzConfig.ini";

/// <summary>
/// 特效音乐最长时间值(秒)
/// 用于延迟多长时间后关闭音频流
/// </summary>

const int SuperSound::maxMusicLength = 2;

/// <summary>
/// 背景音乐播放
/// </summary>
/// <param name="key">配置KEY</param>
/// <returns></returns>

void SuperSound::sendASoundCommand(const char* key) {

	std::string szSoundContent = ConfigConvert::getConfig(configPath, key);

	if (szSoundContent != "") {

		int i = mciSendString(szSoundContent.c_str(), NULL, 0, NULL);

		std::cout << szSoundContent << "--->" << i << std::endl;

	}

}

/// <summary>
/// 特效音乐播放
/// 开辟线程，不会阻塞UI，推荐特效音乐用此函数播放
/// </summary>
/// <param name="openkey">配置打开KEY</param>
/// <param name="playkey">配置播放KEY</param>
/// <param name="closekey">配置关闭KEY</param>
/// <returns></returns>

void SuperSound::closeAndPlay(const char* openkey, const char* playkey, const char* closekey) {

	std::thread t([=] {

		SuperSound::sendASoundCommand(openkey);

		SuperSound::sendASoundCommand(playkey);

		Sleep(maxMusicLength * 1000);
		
		SuperSound::sendASoundCommand(closekey);	

	});

	t.detach();

}






