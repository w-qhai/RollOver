#pragma once
#include <windows.h>
#include <Mmsystem.h>
#pragma comment ( lib, "winmm.lib" ) 
////////////////////////////////////////////////////////////////////////////////
//
// 类：Sound
// 游戏声音播放工具类. 类中均为静态函数. 函数调用方法 CSystem::函数名();
//
class Sound
{
public:
	// 播放音乐函数
	// 参数 src：声音的路径及名称，具体值请在编辑器的资源 -> 添加声音那里查看本项目里的声音资源，完整按照那个路径值填写即可，路径使用\\
	// 参数 isLoop：是否循环播放。如果是循环播放的声音，需要手动调用API停止播放
	//
	static void Play(const char* src, const bool isLoop);
private:

};