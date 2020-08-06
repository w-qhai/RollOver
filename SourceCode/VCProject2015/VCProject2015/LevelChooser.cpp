#include "LevelChooser.h"

CStaticSprite LevelChooser::level_1("level1");

void LevelChooser::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	// 点击不同按钮 加载不同地图
	if (level_1.IsPointInSprite(fMouseX, fMouseY)) {
		CSystem::LoadMap("level.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
	}
}

void LevelChooser::OnMouseMove(const float fMouseX, const float fMouseY) {}
void LevelChooser::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY) {}
void LevelChooser::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress) {}
void LevelChooser::OnKeyUp(const int iKey) {}
void LevelChooser::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {}
void LevelChooser::OnSpriteColWorldLimit(const char* szName, const int iColSide) {}