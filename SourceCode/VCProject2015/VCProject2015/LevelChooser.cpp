#include "LevelChooser.h"
//==============================================================================
//
// 冒险模式关卡选择器
//
//==============================================================================

CStaticSprite LevelChooser::level_1("level1");
CStaticSprite LevelChooser::level_2("level2");
CStaticSprite LevelChooser::level_3("level3");

void LevelChooser::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	// 点击不同按钮 加载不同地图
	if (level_1.IsPointInSprite(fMouseX, fMouseY)) {
		CSystem::LoadMap("adventure_level1.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
		g_GameMain.adventure_level_id = 1;
	}
	else if (level_2.IsPointInSprite(fMouseX, fMouseY)) {
		CSystem::LoadMap("adventure_level2.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
		g_GameMain.adventure_level_id = 2;
	}
	else if (level_3.IsPointInSprite(fMouseX, fMouseY)) {
		CSystem::LoadMap("adventure_level3.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
		g_GameMain.adventure_level_id = 3;
	}
}

void LevelChooser::OnMouseMove(const float fMouseX, const float fMouseY) {}
void LevelChooser::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY) {}
void LevelChooser::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress) {}
void LevelChooser::OnKeyUp(const int iKey) {}
void LevelChooser::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {}
void LevelChooser::OnSpriteColWorldLimit(const char* szName, const int iColSide) {}