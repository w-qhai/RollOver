#include "BowlingMode.h"

bool				Bowling::left_pressed;	// 鼠标左键是否按下;
Card*				Bowling::card;			// 植物卡d;
Plant*				Bowling::seed;			// 植物种子
CSprite				Bowling::top_side("TopSide");
CSprite				Bowling::bottom_side("BottomSide");
WallNutBowling		Bowling::bowling("bowling");

CSprite				Bowling::background("background");
CSprite				Bowling::game_over("GameOver");
CSprite				Bowling::game_close("GameClose");
CSprite				Bowling::play_again("PlayAgain");

CSprite				Bowling::game_win("GameWin");
CSprite				Bowling::game_close2("GameClose2");
CSprite				Bowling::next("Next");

// 游戏中的菜单
CSprite				Bowling::game_menu_btn("GameMenuBtn");
CSprite				Bowling::game_menu("GameMenu");
CSprite				Bowling::continue_("Continue");
CSprite				Bowling::main_menu("MainMenu");
CSprite				Bowling::rebegin("ReBegin");
void Bowling::OnMouseMove(const float fMouseX, const float fMouseY) {
	if (left_pressed && seed) {
		seed->SetSpritePosition(fMouseX, fMouseY);
	}
}

void Bowling::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
    if (iMouseType == MOUSE_LEFT) {
		left_pressed = true;
		card = nullptr;
		seed = nullptr;

		/*------------------游戏菜单部分-------------------*/
		if (game_menu.IsSpriteVisible()) {
			// 继续游戏
			if (continue_.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
				SuperSound::sendASoundCommand("open-bowling");
				SuperSound::sendASoundCommand("play-bowling");
				continue_.SetSpriteVisible(false);
				game_menu.SetSpriteVisible(false);
				rebegin.SetSpriteVisible(false);
				main_menu.SetSpriteVisible(false);

			}

			// 重新开始
			if (rebegin.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
				SuperSound::sendASoundCommand("open-bowling");
				SuperSound::sendASoundCommand("play-bowling");
				std::string s = "bowling";
				g_GameMain.reload();
				CSystem::LoadMap(std::string(s + ".t2d").c_str());
			}

			// 主菜单
			if (main_menu.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
				SuperSound::sendASoundCommand("open-menu");
				SuperSound::sendASoundCommand("play-menu");
				CSystem::LoadMap("menu.t2d");
				g_GameMain.reload();
				g_GameMain.map_id = CGameMain::MapType::MenuType;
			}
		}

		if (game_menu_btn.IsPointInSprite(fMouseX, fMouseY)) {
			SuperSound::closeAndPlay("open-click1", "play-click1", "close-click1");
			SuperSound::sendASoundCommand("close-all");
			if (game_menu.IsSpriteVisible()) {
				game_menu.SetSpriteVisible(false);
				continue_.SetSpriteVisible(false);
				rebegin.SetSpriteVisible(false);
				main_menu.SetSpriteVisible(false);
			}
			else {
				game_menu.SetSpriteVisible(true);
				continue_.SetSpriteVisible(true);
				rebegin.SetSpriteVisible(true);
				main_menu.SetSpriteVisible(true);
			}
		}


		/*------------------游戏失败中主体部分-------------------*/
		if (game_over.IsSpriteVisible()) {
			if (game_close.IsPointInSprite(fMouseX, fMouseY)) {
				CSystem::LoadMap("menu.t2d");
				SuperSound::sendASoundCommand("open-menu");
				SuperSound::sendASoundCommand("play-menu");
				g_GameMain.reload();
				g_GameMain.map_id = CGameMain::MapType::MenuType;
			}

			if (play_again.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::sendASoundCommand("open-bowling");
				SuperSound::sendASoundCommand("play-bowling");

				game_over.SetSpriteVisible(false);
				game_close.SetSpriteVisible(false);
				play_again.SetSpriteVisible(false);
				std::string s = "bowling";
				g_GameMain.reload();
				CSystem::LoadMap(std::string(s + ".t2d").c_str());
			}
		}

		if (game_win.IsSpriteVisible()) {
			if (game_close2.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::sendASoundCommand("open-bowling");
				SuperSound::sendASoundCommand("play-bowling");
				CSystem::LoadMap("menu.t2d");
				g_GameMain.reload();
				g_GameMain.map_id = CGameMain::MapType::MenuType;
			}

			if (next.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::sendASoundCommand("open-bowling");
				SuperSound::sendASoundCommand("play-bowling");

				game_over.SetSpriteVisible(false);
				game_close.SetSpriteVisible(false);
				play_again.SetSpriteVisible(false);

				//g_GameMain.adventure_level_id++;
				if (g_GameMain.adventure_level_id > 5) {
					std::cout << "完成全部关卡" << std::endl;
					CSystem::LoadMap("menu.t2d");
					g_GameMain.reload();
					g_GameMain.map_id = CGameMain::MapType::MenuType;
					return;
				}

				std::string s = "bowling";
				g_GameMain.reload();
				CSystem::LoadMap(std::string(s + ".t2d").c_str());
			}
		}


		// 游戏中
		std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(fMouseX, fMouseY);
		for (const auto& sprite : sprites) {
			std::string type = sprite->get_type();
			if (type.substr(type.size() - 4, 4) == "Card") {
				card = reinterpret_cast<Card*>(sprite);
				if (sprite->get_type() == "WallNutCard") {
					seed = g_GameMain.create_wall_nut(fMouseX, fMouseY);
				}
				seed->SetSpriteColorAlpha(100);
				break;
			}
		}
	}
}

void Bowling::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY) {
	float x_slot[10] = { -39, -28.5, -18, -7.5, 2, 12, 22, 32, 43, 55 };
	float y_slot[5] = { -17, -5, 9, 20, 32 };

	int x = 0, y = 0;
	for (int i = 1; i < 10; i++) {
		if (abs(fMouseX - x_slot[x]) > abs(fMouseX - x_slot[i])) {
			x = i;
		}
	}
	if (iMouseType == MOUSE_LEFT) {
		if (left_pressed && seed && card) {
			for (int i = 1; i < 5; i++) {
				if (abs(fMouseY - y_slot[y] + seed->GetSpriteHeight() / 2) > abs(fMouseY - y_slot[i] + seed->GetSpriteHeight() / 2)) {
					y = i;
				}
			}
			std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
			seed->SetSpriteColorAlpha(255);
			bool planting = true;

			// 地形许可 & 阳光充足
			if (planting && card && x < 2) {
				SuperSound::closeAndPlay("open-plant", "play-plant", "close-plant");
				seed->SetSpritePosition(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
				seed->set_exist(true);
				seed->SetSpriteImmovable(false);
				seed->SetSpriteAngularVelocity(400);
				seed->SetSpriteLinearVelocityX(20);
				g_GameMain.move_bowling_card();
				card->DeleteSprite();
				card->set_exist(false);
				bowling_counter--;
			}
			else {
				seed->DeleteSprite();
			}
		}
		left_pressed = false;
		seed = nullptr;
	}
}

void Bowling::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress) {

}

void Bowling::OnKeyUp(const int iKey) {

}


static void is_victory(int total_zombie) {
	if (total_zombie == 0) {
		SuperSound::sendASoundCommand("close-all");
		SuperSound::closeAndPlay("open-victory", "play-victory", "close-victory");
		// 游戏胜利 
		if (!Bowling::game_win.IsSpriteVisible()) {
			long double game_cost = fTimeDelta - game_start;
			std::cout << __LINE__ << ": " << game_cost << std::endl;
			Bowling::game_win.SetSpriteVisible(true);
			Bowling::game_close2.SetSpriteVisible(true);
			Bowling::next.SetSpriteVisible(true);

			/*WritePrivateProfileString("level_score", std::string("level_" + std::to_string(g_GameMain.adventure_level_id)).c_str(), "1", "./score.ini");*/

			return;
		}
	}
}

void Bowling::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {
	if (std::string(szSrcName) == "ZombieHead" && std::string(szTarName) == "Flag") {
		// 一大波僵尸
		SuperSound::closeAndPlay("open-zombie-howl", "play-zombie-howl", "close-zombie-howl");
	}

	std::cout << szSrcName << " " << szTarName << std::endl;

	PvZSprite* src = g_GameMain.get_sprite_by_name(szSrcName);
	PvZSprite* tar = g_GameMain.get_sprite_by_name(szTarName);
	if (std::string(szTarName) == "ConveryBelt") {
		src->SetSpriteImmovable(true);
	}


	if (!game_over.IsSpriteVisible() && std::string(szTarName) == "background") {
		SuperSound::sendASoundCommand("close-all");
		SuperSound::closeAndPlay("open-defeat", "play-defeat", "close-defeat");
		WritePrivateProfileString("level_score", std::string("level_" + std::to_string(g_GameMain.adventure_level_id)).c_str(), "0", "./score.ini");
		game_over.SetSpriteVisible(true);
		game_close.SetSpriteVisible(true);
		play_again.SetSpriteVisible(true);
		return;
	}

	if ((std::string(szTarName) == "TopSide" || std::string(szTarName) == "BottomSide") && src->get_type() == "Plant") {
		if (src->GetSpriteLinearVelocityY()) {
			src->SetSpriteLinearVelocityY(-src->GetSpriteLinearVelocityY());
		}
		// 坚果直走，碰撞后给个Y轴速度
		else {
			src->SetSpriteLinearVelocityY((int)src % 2 ? 20 : -20);
		}
	}

	if (src && tar) {

		if (src->get_type() == "WallNutCard" && tar->get_type() == "WallNutCard") {
			src->SetSpriteImmovable(tar->GetSpriteImmovable());
		}


		// 僵尸碰坚果或者坚果碰僵尸
		if (src->get_type() == "Plant" && tar->get_type() == "Zombie") {
			SuperSound::closeAndPlay("open-bow-hit", "play-bow-hit", "close-bow-hit");

			Plant* p = reinterpret_cast<Plant*>(src);
			Zombie* z = reinterpret_cast<Zombie*>(tar);
		

			// 碰撞后更改Y轴方向
			if (src->GetSpriteLinearVelocityY()) {
				src->SetSpriteLinearVelocityY(-src->GetSpriteLinearVelocityY());
			}
			// 坚果直走，碰撞后给个Y轴速度
			else {
				src->SetSpriteLinearVelocityY((int)src % 2 ? 20 : -20);
			}
			if (z->attacked_by(&bowling)) {
				total_zombie--;
				std::cout << total_zombie << std::endl;
				is_victory(total_zombie);
			}
		}

		if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
			SuperSound::closeAndPlay("open-bow-hit", "play-bow-hit", "close-bow-hit");
			Plant* p = reinterpret_cast<Plant*>(tar);
			Zombie* z = reinterpret_cast<Zombie*>(src);

			if (tar->GetSpriteLinearVelocityY()) {
				tar->SetSpriteLinearVelocityY(-tar->GetSpriteLinearVelocityY());
			}
			else {
				tar->SetSpriteLinearVelocityY((int)tar % 2 ? 20 : -20);
			}

			if (z->attacked_by(&bowling)) {
				total_zombie--;
				std::cout << total_zombie << std::endl;
				is_victory(total_zombie);
			}
		}
	}

}

void Bowling::OnSpriteColWorldLimit(const char* szName, const int iColSide) {

}