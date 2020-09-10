//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"
#include "../VCProject2015/VCProject2015/AdventureMode.h"
#include "../VCProject2015/VCProject2015/MenuMode.h"
#include "../VCProject2015/VCProject2015/BowlingMode.h"
#include "../VCProject2015/VCProject2015/LevelChooser.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

#undef min
#undef max

long double 	fTimeDelta;
long double 	game_start;
int total_zombie;
int bowling_counter;
FILE* stream;
void init();
int PASCAL WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	init();

	if (!CSystem::InitGameEngine(hInstance, lpCmdLine)) {
		return 0;
	}
	CSystem::LoadMap("welcome.t2d");
	CSystem::SetWindowTitle("PvZ");
	CSystem::LoadMap("welcome.t2d");
	while (CSystem::EngineMainLoop()) {
		g_GameMain.GameMainLoop(fTimeDelta);
	};

	CSystem::ShutdownGameEngine();
	return 0;
}


/*------------------事件分发-------------------*/

// 引擎捕捉鼠标移动消息后，将调用到本函数
void CSystem::OnMouseMove(const float fMouseX, const float fMouseY)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnMouseMove(fMouseX, fMouseY);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnMouseMove(fMouseX, fMouseY);
	case CGameMain::MapType::BowlingType:
		Bowling::OnMouseMove(fMouseX, fMouseY);
		break;
	default:
		break;
	}
}

// 引擎捕捉鼠标点击消息后，将调用到本函数
void CSystem::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY)
{
	static CStaticSprite load_bar("LoadBar");
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		if (load_bar.IsPointInSprite(fMouseX, fMouseY)) {
			SuperSound::closeAndPlay("open-click1", "play-click1", "close-click1");
			CSystem::LoadMap("menu.t2d");
			g_GameMain.map_id = CGameMain::MapType::MenuType;
		}
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnMouseClick(iMouseType, fMouseX, fMouseY);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnMouseClick(iMouseType, fMouseX, fMouseY);
		break;
	case CGameMain::MapType::BowlingType:
		Bowling::OnMouseClick(iMouseType, fMouseX, fMouseY);
		break;
	case CGameMain::MapType::LevelChooserType:
		LevelChooser::OnMouseClick(iMouseType, fMouseX, fMouseY);
	default:
		break;
	}
}

// 引擎捕捉鼠标弹起消息后，将调用到本函数
void CSystem::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnMouseUp(iMouseType, fMouseX, fMouseY);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnMouseUp(iMouseType, fMouseX, fMouseY);
	case CGameMain::MapType::BowlingType:
		Bowling::OnMouseUp(iMouseType, fMouseX, fMouseY);
		break;
	case CGameMain::MapType::LianLianKanType:
		LianLianKan::OnMouseUp(iMouseType, fMouseX, fMouseY);
		break;
	default:
		break;
	}
}

// 引擎捕捉键盘按下消息后，将调用到本函数
void CSystem::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnKeyDown(iKey, bAltPress, bShiftPress, bCtrlPress);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnKeyDown(iKey, bAltPress, bShiftPress, bCtrlPress);
	default:
		break;
	}
}

// 引擎捕捉键盘弹起消息后，将调用到本函数
void CSystem::OnKeyUp(const int iKey)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnKeyUp(iKey);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnKeyUp(iKey);
	default:
		break;
	}
}

// 引擎捕捉到精灵与精灵碰撞之后，调用此函数
void CSystem::OnSpriteColSprite(const char* szSrcName, const char* szTarName)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnSpriteColSprite(szSrcName, szTarName);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnSpriteColSprite(szSrcName, szTarName);
		break;
	case CGameMain::MapType::BowlingType:
		Bowling::OnSpriteColSprite(szSrcName, szTarName);
		break;
	case CGameMain::MapType::LianLianKanType:
		LianLianKan::OnSpriteColSprite(szSrcName, szTarName);
		break;
	default:
		break;
	}
}

// 引擎捕捉到精灵与世界边界碰撞之后，调用此函数 iColSide : 0 左边，1 右边，2 上边，3 下边
void CSystem::OnSpriteColWorldLimit(const char* szName, const int iColSide)
{
	std::cout << szName << " " << iColSide << std::endl;
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnSpriteColWorldLimit(szName, iColSide);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnSpriteColWorldLimit(szName, iColSide);
	case CGameMain::MapType::BowlingType:
		Bowling::OnSpriteColWorldLimit(szName, iColSide);
		break;
	default:
		break;
	}
}

void init() {
	//开启控制台，方便调试信息输出
	AllocConsole();
	freopen_s(&stream, "CONOUT$", "a+", stdout);

	std::thread timer([&]() {
		while (true) {
			fTimeDelta += CSystem::GetTimeDelta();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	});
	timer.detach();
}