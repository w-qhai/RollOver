#include "MenuMode.h"

CStaticSprite Menu::adventure("AdventureGame");		// 冒险模式
CStaticSprite Menu::mini("MiniGame");				// 迷你游戏
CStaticSprite Menu::edu("EduGame");					// 益智模式
CStaticSprite Menu::help_btn("helpBtn");			// 帮助按钮
CStaticSprite Menu::help_msg("helpMsg");			// 帮助消息面板
CStaticSprite Menu::help_close("helpClose");		// 关闭帮助消息
CStaticSprite Menu::exit_("exit");					// 退出游戏

CStaticSprite Menu::achievement("achievement");		// 成就按钮
CStaticSprite Menu::score_board("scoreBoard");		// 成就面板
CStaticSprite Menu::score_close("scoreBoardClose");	// 成就面板

CStaticSprite Menu::level_1("level_1");
CStaticSprite Menu::level_2("level_2");
CStaticSprite Menu::level_3("level_3");
CStaticSprite Menu::level_4("level_4");
CStaticSprite Menu::level_5("level_5");

// 保龄球用时
CTextSprite	  Menu::bowling_score("bowlingScore");
// 冒险用时
CTextSprite	  Menu::level1_score("level1Score");
CTextSprite	  Menu::level2_score("level2Score");
CTextSprite	  Menu::level3_score("level3Score");
CTextSprite	  Menu::level4_score("level4Score");
CTextSprite	  Menu::level5_score("level5Score");


void Menu::OnMouseMove(const float fMouseX, const float fMouseY) {
	// 根据鼠标位置 显示不同图片
	if (!score_board.IsSpriteVisible() && help_msg.GetSpritePositionY() < -10) {
		static CStaticSprite* last = nullptr;
		CStaticSprite* now = nullptr;

		if (adventure.IsPointInSprite(fMouseX, fMouseY)) {
			now = &adventure;
		}

		if (mini.IsPointInSprite(fMouseX, fMouseY)) {
			now = &mini;
		}

		if (edu.IsPointInSprite(fMouseX, fMouseY)) {
			now = &edu;
		}

		if (achievement.IsPointInSprite(fMouseX, fMouseY)) {
			now = &achievement;
		}

		if (adventure.IsPointInSprite(fMouseX, fMouseY) ||
			mini.IsPointInSprite(fMouseX, fMouseY) ||
			edu.IsPointInSprite(fMouseX, fMouseY) ||
			achievement.IsPointInSprite(fMouseX, fMouseY)) {
			if (last != now) {
				SuperSound::closeAndPlay("open-hover", "play-hover", "close-hover");
			}

		}


		adventure.SetStaticSpriteImage("AdventureModeImageMap", adventure.IsPointInSprite(fMouseX, fMouseY));
		mini.SetStaticSpriteImage("MiniModeImageMap", mini.IsPointInSprite(fMouseX, fMouseY));
		edu.SetStaticSpriteImage("EduModeImageMap", edu.IsPointInSprite(fMouseX, fMouseY));
		achievement.SetStaticSpriteImage("AchievementImageMap1", achievement.IsPointInSprite(fMouseX, fMouseY));

		last = now;
	}
}

void Menu::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	// 点击不同按钮 加载不同地图
	if (!score_board.IsSpriteVisible() && help_msg.GetSpritePositionY() < -10) {
		if (adventure.IsPointInSprite(fMouseX, fMouseY)) {
			SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
			CSystem::LoadMap("levelChooser.t2d");
			g_GameMain.map_id = CGameMain::MapType::LevelChooserType;
		}
		else if (mini.IsPointInSprite(fMouseX, fMouseY)) {
			SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
			CSystem::LoadMap("lianliankan.t2d");
			g_GameMain.map_id = CGameMain::MapType::LianLianKanType;
		}
		else if (edu.IsPointInSprite(fMouseX, fMouseY)) {
			SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
			SuperSound::sendASoundCommand("close-all");
			SuperSound::sendASoundCommand("open-bowling");
			SuperSound::sendASoundCommand("play-bowling");
			CSystem::LoadMap("bowling.t2d");
			g_GameMain.map_id = CGameMain::MapType::BowlingType;
		}

		if (exit_.IsPointInSprite(fMouseX, fMouseY)) {
			SuperSound::closeAndPlay("open-click1", "play-click1", "close-click1");
			exit(0);
		}
	}

	// 
	if (help_btn.IsPointInSprite(fMouseX, fMouseY)) {
		SuperSound::closeAndPlay("open-click1", "play-click1", "close-click1");
		help_msg.SpriteMoveTo(1.094, -5.124, 50, true);
	}
	if (help_close.IsPointInSprite(fMouseX, fMouseY)) {
		SuperSound::closeAndPlay("open-click1", "play-click1", "close-click1");
		help_msg.SpriteMoveTo(-0.198, -64.815, 80, true);
	}


	// 成就面板
	if (achievement.IsPointInSprite(fMouseX, fMouseY)) {
		SuperSound::closeAndPlay("open-click1", "play-click1", "close-click1");
		score_board.SetSpriteVisible(true);
		score_close.SetSpriteVisible(true);

		// 保龄球用时
		bowling_score.SetSpriteVisible(true);
		int bowling_time = GetPrivateProfileInt("other_time", "bowling_time", 0, "./score.ini");
		int min = int(bowling_time) / 60;
		int s = int(bowling_time) % 60;
		bowling_score.SetTextString(std::string(std::to_string(min) + ":" + std::to_string(s)).c_str());

		// 是否完成
		int level1 = GetPrivateProfileInt("level_score", "level_1", 0, "./score.ini");
		int level2 = GetPrivateProfileInt("level_score", "level_2", 0, "./score.ini");
		int level3 = GetPrivateProfileInt("level_score", "level_3", 0, "./score.ini");
		int level4 = GetPrivateProfileInt("level_score", "level_4", 0, "./score.ini");
		int level5 = GetPrivateProfileInt("level_score", "level_5", 0, "./score.ini");

		level_1.SetSpriteVisible(level1 == 1);
		level_2.SetSpriteVisible(level2 == 1);
		level_3.SetSpriteVisible(level3 == 1);
		level_4.SetSpriteVisible(level4 == 1);
		level_5.SetSpriteVisible(level5 == 1);

		// 用时
		int level1_time = GetPrivateProfileInt("level_time", "level_time_1", 0, "./score.ini");
		int level2_time = GetPrivateProfileInt("level_time", "level_time_2", 0, "./score.ini");
		int level3_time = GetPrivateProfileInt("level_time", "level_time_3", 0, "./score.ini");
		int level4_time = GetPrivateProfileInt("level_time", "level_time_4", 0, "./score.ini");
		int level5_time = GetPrivateProfileInt("level_time", "level_time_5", 0, "./score.ini");

		level1_score.SetTextString(std::string(std::to_string(level1_time / 60) + ":" + std::to_string(level1_time % 60)).c_str());
		level2_score.SetTextString(std::string(std::to_string(level2_time / 60) + ":" + std::to_string(level2_time % 60)).c_str());
		level3_score.SetTextString(std::string(std::to_string(level3_time / 60) + ":" + std::to_string(level3_time % 60)).c_str());
		level4_score.SetTextString(std::string(std::to_string(level4_time / 60) + ":" + std::to_string(level4_time % 60)).c_str());
		level5_score.SetTextString(std::string(std::to_string(level5_time / 60) + ":" + std::to_string(level5_time % 60)).c_str());

		level1_score.SetSpriteVisible(level1 == 1);
		level2_score.SetSpriteVisible(level2 == 1);
		level3_score.SetSpriteVisible(level3 == 1);
		level4_score.SetSpriteVisible(level4 == 1);
		level5_score.SetSpriteVisible(level5 == 1);

	}
	if (score_close.IsPointInSprite(fMouseX, fMouseY)) {
		SuperSound::closeAndPlay("open-click1", "play-click1", "close-click1");
		score_board.SetSpriteVisible(false);
		score_close.SetSpriteVisible(false);
		level_1.SetSpriteVisible(false);
		level_2.SetSpriteVisible(false);
		level_3.SetSpriteVisible(false);
		level_4.SetSpriteVisible(false);
		level_5.SetSpriteVisible(false);

		level1_score.SetSpriteVisible(false);
		level2_score.SetSpriteVisible(false);
		level3_score.SetSpriteVisible(false);
		level4_score.SetSpriteVisible(false);
		level5_score.SetSpriteVisible(false);
		bowling_score.SetSpriteVisible(false);
	}

}

void Menu::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY) {}
void Menu::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress) {}
void Menu::OnKeyUp(const int iKey) {}
void Menu::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {}
void Menu::OnSpriteColWorldLimit(const char* szName, const int iColSide) {}