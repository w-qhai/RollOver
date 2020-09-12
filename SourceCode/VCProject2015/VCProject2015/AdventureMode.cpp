#include "AdventureMode.h"

bool		Adventure::left_pressed;	// 鼠标左键是否按下;
Card* Adventure::card;			// 植物卡d;
Plant* Adventure::seed;			// 植物种子
Shovel* Adventure::shovel;			// 选中了小铲子
CSprite		Adventure::background("background");
CSprite     Adventure::game_over("GameOver");
CSprite     Adventure::game_close("GameClose");
CSprite     Adventure::play_again("PlayAgain");

CSprite     Adventure::game_win("GameWin");
CSprite     Adventure::game_close2("GameClose2");
CSprite     Adventure::next("Next");

// 游戏中的菜单
CSprite     Adventure::game_menu_btn("GameMenuBtn");
CSprite     Adventure::game_menu("GameMenu");
CSprite     Adventure::continue_("Continue");
CSprite     Adventure::main_menu("MainMenu");
CSprite     Adventure::rebegin("ReBegin");

// 用时
CTextSprite Adventure::score("score");


void Adventure::OnMouseMove(const float fMouseX, const float fMouseY) {
	if (left_pressed && shovel) {
		shovel->SetSpritePosition(fMouseX, fMouseY);
	}
	else if (left_pressed && seed) {
		seed->SetSpritePosition(fMouseX, fMouseY);
	}
}
void Adventure::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {


	if (iMouseType == MOUSE_LEFT) {
		left_pressed = true;
		card = nullptr;
		seed = nullptr;
		shovel = nullptr;

		/*------------------游戏菜单部分-------------------*/
		if (game_menu.IsSpriteVisible()) {
			// 继续游戏
			if (continue_.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
				SuperSound::sendASoundCommand("open-day");
				SuperSound::sendASoundCommand("play-day");
				game_menu.SetSpriteVisible(false);
				continue_.SetSpriteVisible(false);
				rebegin.SetSpriteVisible(false);
				main_menu.SetSpriteVisible(false);
			}

			// 重新开始
			if (rebegin.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
				SuperSound::sendASoundCommand("open-day");
				SuperSound::sendASoundCommand("play-day");
				std::string s = "adventure_level";
				g_GameMain.reload();
				CSystem::LoadMap(std::string(s + std::to_string(g_GameMain.adventure_level_id) + ".t2d").c_str());
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
				SuperSound::sendASoundCommand("open-day");
				SuperSound::sendASoundCommand("play-day");

				game_over.SetSpriteVisible(false);
				game_close.SetSpriteVisible(false);
				play_again.SetSpriteVisible(false);
				std::string s = "adventure_level";
				g_GameMain.reload();
				CSystem::LoadMap(std::string(s + std::to_string(g_GameMain.adventure_level_id) + ".t2d").c_str());
			}
		}

		if (game_win.IsSpriteVisible()) {
			if (game_close2.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::sendASoundCommand("open-day");
				SuperSound::sendASoundCommand("play-day");
				CSystem::LoadMap("menu.t2d");
				g_GameMain.reload();
				g_GameMain.map_id = CGameMain::MapType::MenuType;
			}

			if (next.IsPointInSprite(fMouseX, fMouseY)) {
				SuperSound::sendASoundCommand("open-day");
				SuperSound::sendASoundCommand("play-day");

				game_over.SetSpriteVisible(false);
				game_close.SetSpriteVisible(false);
				play_again.SetSpriteVisible(false);

				g_GameMain.adventure_level_id++;
				if (g_GameMain.adventure_level_id > 5) {
					std::cout << "完成全部关卡" << std::endl;
					CSystem::LoadMap("menu.t2d");
					g_GameMain.reload();
					g_GameMain.map_id = CGameMain::MapType::MenuType;
					return;
				}

				std::string s = "adventure_level";
				g_GameMain.reload();
				CSystem::LoadMap(std::string(s + std::to_string(g_GameMain.adventure_level_id) + ".t2d").c_str());
			}
		}

		// 游戏中
		std::vector<PvZSprite*> sprites = g_GameMain.get_sprites_by_position(fMouseX, fMouseY);
		for (const auto& sprite : sprites) {
			// 选中的位置有太阳
			if (sprite->get_type() == "Sun") {
				Sun* sun = reinterpret_cast<Sun*>(sprite);
				SuperSound::closeAndPlay("open-sun-hit", "play-sun-hit", "close-sun-hit");
				sun->SpriteMoveTo(-43.275, -33.275, 100, true);
				sun->SetSpriteLifeTime(1);
				g_GameMain.add_sun(sun->get_num());
				sun->set_exist(false);
				left_pressed = false;
				break;
			}

			// 选中的位置有小车，不做任何事情
			if (sprite->get_type() == "Car") {
				continue;
			}

			// 选中铲子
			if (sprite->get_type() == "Shovel") {
				shovel = reinterpret_cast<Shovel*>(sprite);
				break;
			}

			// 选中卡片
			std::string type = sprite->get_type();
			// 后四位Card表示 植物卡
			if (type.substr(type.size() - 4, 4) == "Card") {
				// 鼠标按下 选中植物卡
				card = reinterpret_cast<Card*>(sprite);
				// 如果选中的卡 冷却完毕
				if (card->ready(fTimeDelta)) {
					if (sprite->get_type() == "PeaShooterCard") {
						seed = g_GameMain.create_pea_shooter(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "SunflowerCard") {
						seed = g_GameMain.create_sunflower(fMouseX, fMouseY, fTimeDelta);
					}
					else if (sprite->get_type() == "CherryBombCard") {
						// 种下的时间 用来判断是否自动爆炸
						seed = g_GameMain.create_cherry_bomb(fMouseX, fMouseY, fTimeDelta);
					}
					else if (sprite->get_type() == "PotatoMineCard") {
						// 种下的时间 用来判断是否出头
						seed = g_GameMain.create_potato_mine(fMouseX, fMouseY, fTimeDelta);
					}
					else if (sprite->get_type() == "WallNutCard") {
						seed = g_GameMain.create_wall_nut(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "JalapenoCard") {
						// 种下的时间 用来判断是否自动爆炸
						seed = g_GameMain.create_jalapeno(fMouseX, fMouseY, fTimeDelta);
					}
					else if (sprite->get_type() == "ThreePeaterCard") {
						std::cout << "Three" << std::endl;
						seed = g_GameMain.create_three_peater(fMouseX, fMouseY);
					}
					seed->SetSpriteColorAlpha(100);
				}
				else {
					card = nullptr;
				}
				break;
			}
		}
	}
}

void Adventure::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY) {
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

			for (const auto& sprite : sprites) {
				// 下面有植物 不能种
				if (sprite->get_type() == "Plant") {
					planting = false;
					break;
				}

				// 有僵尸 分情况
				if (sprite->get_type() == "Zombie") {
					if (card->get_type() == "CherryBombCard") {
						planting = true;
					}
					else {
						planting = false;
					}
					break;
				}
			}
			if (g_GameMain.adventure_level_id == 1 && (y == 0 || y == 4)) {
				planting = false;
			}

			// 地形许可 & 阳光充足
			if (planting && g_GameMain.planting(seed) && card) {
				SuperSound::closeAndPlay("open-plant", "play-plant", "close-plant");
				seed->SetSpritePosition(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
				seed->set_exist(true);
				card->plant_time(fTimeDelta);
			}
			else {
				seed->DeleteSprite();
			}
		}
		else if (left_pressed && shovel) {
			std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(fMouseX, fMouseY);
			// 位置上有植物 挖走
			for (const auto& sprite : sprites) {
				SuperSound::closeAndPlay("open-plant", "play-plant", "close-plant");
				if (sprite->get_type() == "Plant") {
					Plant* p = reinterpret_cast<Plant*>(sprite);
					p->die();
					break;
				}
			}
			shovel->SetSpritePosition(12.093, -32.500);
		}
		left_pressed = false;
		seed = nullptr;
		shovel = nullptr;
	}
}

void Adventure::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress) {

}

void Adventure::OnKeyUp(const int iKey) {

}

static void is_victory(int total_zombie) {
	if (total_zombie == 0) {
		SuperSound::sendASoundCommand("close-all");
		SuperSound::closeAndPlay("open-victory", "play-victory", "close-victory", 4);
		// 游戏胜利 
		if (!Adventure::game_win.IsSpriteVisible()) {
			Adventure::game_win.SetSpriteVisible(true);
			Adventure::game_close2.SetSpriteVisible(true);
			Adventure::next.SetSpriteVisible(true);
			Adventure::score.SetSpriteVisible(true);

			// 持久化
			long double game_cost = fTimeDelta - game_start;
			std::cout << __LINE__ << ": " << game_cost << std::endl;
			WritePrivateProfileString("level_score", std::string("level_" + std::to_string(g_GameMain.adventure_level_id)).c_str(), "1", "./score.ini");
			WritePrivateProfileString("level_time", std::string("level_time_" + std::to_string(g_GameMain.adventure_level_id)).c_str(),
				std::to_string(int(game_cost)).c_str(), "./score.ini");


			int min = int(game_cost) / 60;
			int s = int(game_cost) % 60;
			std::cout << __LINE__ << std::string(std::to_string(min) + ":" + std::to_string(s)).c_str() << std::endl;
			Adventure::score.SetTextString(std::string(std::to_string(min) + ":" + std::to_string(s)).c_str());
			return;
		}
	}
}

void Adventure::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {
	if (std::string(szSrcName) == "ZombieHead" && std::string(szTarName) == "Flag") {
		g_GameMain.zombie_wave();
		SuperSound::closeAndPlay("open-zombie-howl", "play-zombie-howl", "close-zombie-howl");
	}

	PvZSprite* src = g_GameMain.get_sprite_by_name(szSrcName);
	PvZSprite* tar = g_GameMain.get_sprite_by_name(szTarName);

	if (!game_over.IsSpriteVisible() && std::string(szTarName) == "background" && src->get_type() == "Zombie") {
		SuperSound::sendASoundCommand("close-all");
		SuperSound::closeAndPlay("open-defeat", "play-defeat", "close-defeat");
		WritePrivateProfileString("level_score", std::string("level_" + std::to_string(g_GameMain.adventure_level_id)).c_str(), "0", "./score.ini");
		game_over.SetSpriteVisible(true);
		game_close.SetSpriteVisible(true);
		play_again.SetSpriteVisible(true);
		return;
	}


	if (src && tar) {

		// 小车启动
		if (src->get_type() == "Car" && tar->get_type() == "Zombie") {
			SuperSound::closeAndPlay("open-car", "play-car", "close-car");
			Zombie* z = reinterpret_cast<Zombie*>(tar);
			Car* c = reinterpret_cast<Car*>(src);
			c->SetSpriteLinearVelocityX(25.0);
			z->die(0);
			total_zombie--;
			std::cout << total_zombie << std::endl;
			is_victory(total_zombie);
		}

		// 僵尸进入攻击范围
		if (src->get_type() == "Range" && tar->get_type() == "Zombie") {
			// 转换成其父精灵的指针
			PvZSprite* pvz = g_GameMain.get_sprite_by_name(src->GetSpriteMountedParent());
			Plant* p = reinterpret_cast<Plant*>(pvz);
			p->attack(fTimeDelta);
		}

		// 僵尸吃植物
		if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
			Zombie* z = reinterpret_cast<Zombie*>(src);
			Plant* p = reinterpret_cast<Plant*>(tar);
			z->eat_plant(p, fTimeDelta);
		}

		// 子弹打僵尸
		if (src->get_type() == "Arms" && tar->get_type() == "Zombie") {
			Arms* a = reinterpret_cast<Arms*>(src);
			Zombie* z = reinterpret_cast<Zombie*>(tar);
			// 如果有僵尸死亡，判断是否胜利
			if (z->attacked_by(a)) {
				total_zombie--;
				std::cout << total_zombie << std::endl;
				is_victory(total_zombie);
			}
		}
	}
}

void Adventure::OnSpriteColWorldLimit(const char* szName, const int iColSide) {

}
