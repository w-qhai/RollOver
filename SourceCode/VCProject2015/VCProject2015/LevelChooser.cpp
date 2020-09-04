#include "LevelChooser.h"
//==============================================================================
//
// 冒险模式关卡选择器
//
//==============================================================================

CStaticSprite LevelChooser::level_1("level1");
CStaticSprite LevelChooser::level_2("level2");
CStaticSprite LevelChooser::level_3("level3");
CStaticSprite LevelChooser::level_4("level4");
CStaticSprite LevelChooser::level_5("level5");

void LevelChooser::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	

	// 点击不同按钮 加载不同地图
	if (level_1.IsPointInSprite(fMouseX, fMouseY)) {
		SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
		CSystem::LoadMap("adventure_level1.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
		g_GameMain.adventure_level_id = 1;
	}
	else if (level_2.IsPointInSprite(fMouseX, fMouseY)) {
		SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
		CSystem::LoadMap("adventure_level2.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
		g_GameMain.adventure_level_id = 2;
	}
	else if (level_3.IsPointInSprite(fMouseX, fMouseY)) {
		SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
		CSystem::LoadMap("adventure_level3.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
		g_GameMain.adventure_level_id = 3;
	}
	else if (level_4.IsPointInSprite(fMouseX, fMouseY)) {
		SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
		CSystem::LoadMap("adventure_level4.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
		g_GameMain.adventure_level_id = 4;
	}
	else if (level_5.IsPointInSprite(fMouseX, fMouseY)) {
		SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
		CSystem::LoadMap("adventure_level5.t2d");
		g_GameMain.map_id = CGameMain::MapType::AdventureType;
		g_GameMain.adventure_level_id = 5;
	}
}

void LevelChooser::OnMouseMove(const float fMouseX, const float fMouseY) {}
void LevelChooser::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY) {}
void LevelChooser::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress) {}
void LevelChooser::OnKeyUp(const int iKey) {}
void LevelChooser::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {}
void LevelChooser::OnSpriteColWorldLimit(const char* szName, const int iColSide) {}