#include "MenuMode.h"

CStaticSprite Menu::adventure("AdventureGame");		// 冒险模式
CStaticSprite Menu::mini("MiniGame");				// 迷你游戏
CStaticSprite Menu::edu("EduGame");					// 益智模式

void Menu::OnMouseMove(const float fMouseX, const float fMouseY) {
	// 根据鼠标位置 显示不同图片
	adventure.SetStaticSpriteImage("AdventureModeImageMap", adventure.IsPointInSprite(fMouseX, fMouseY));
	mini.SetStaticSpriteImage("MiniModeImageMap", mini.IsPointInSprite(fMouseX, fMouseY));
	edu.SetStaticSpriteImage("EduModeImageMap", edu.IsPointInSprite(fMouseX, fMouseY));
}

void Menu::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	// 点击不同按钮 加载不同地图
	if (adventure.IsPointInSprite(fMouseX, fMouseY)) {
		CSystem::LoadMap("level.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
	}
	else if (mini.IsPointInSprite(fMouseX, fMouseY)) {
		// ...
	}
	else if (edu.IsPointInSprite(fMouseX, fMouseY)){
		CSystem::LoadMap("bowling.t2d");
		g_GameMain.map_id = CGameMain::MapType::BowlingType;
	}
}

void Menu::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY) {}
void Menu::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress) {}
void Menu::OnKeyUp(const int iKey) {}
void Menu::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {}
void Menu::OnSpriteColWorldLimit(const char* szName, const int iColSide) {}