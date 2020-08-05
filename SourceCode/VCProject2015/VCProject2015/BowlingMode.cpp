#include "BowlingMode.h"

bool		Bowling::left_pressed;	// 鼠标左键是否按下;
Card*       Bowling::card;			// 植物卡d;
Plant*      Bowling::seed;			// 植物种子

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

			for (const auto& sprite : sprites) {
				if (sprite->get_type() == "Zombie") {
					planting = false;
					break;
				}
			}

			// 地形许可 & 阳光充足
			if (planting && card && x < 2) {
				seed->SetSpritePosition(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
				seed->set_exist(true);
				seed->SetSpriteImmovable(false);
				seed->SetSpriteAngularVelocity(400);
				seed->SetSpriteLinearVelocityX(20);
				g_GameMain.move_bowling_card();
				card->DeleteSprite();
				card->set_exist(false);
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

void Bowling::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {
	PvZSprite* src = g_GameMain.get_sprite_by_name(szSrcName);
	PvZSprite* tar = g_GameMain.get_sprite_by_name(szTarName);
	if (std::string(szTarName) == "ConveryBelt") {
		src->SetSpriteImmovable(true);
	}

	if (src && tar) {
		if (src->get_type() == "WallNutCard" && tar->get_type() == "WallNutCard") {
			src->SetSpriteImmovable(tar->GetSpriteImmovable());
		}

		if (src->get_type() == "Plant" && tar->get_type() == "Zombie") {
			if (src->GetSpriteLinearVelocityY()) {
				src->SetSpriteLinearVelocityY(-src->GetSpriteLinearVelocityY());
			}
			else {
				src->SetSpriteLinearVelocityY((int)src % 2 ? 20 : -20);
			}
		}

		if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
			if (tar->GetSpriteLinearVelocityY()) {
				tar->SetSpriteLinearVelocityY(-tar->GetSpriteLinearVelocityY());
			}
			else {
				tar->SetSpriteLinearVelocityY((int)tar % 2 ? 20 : -20);
			}
		}
	}

}

void Bowling::OnSpriteColWorldLimit(const char* szName, const int iColSide) {
	PvZSprite* sprite = g_GameMain.get_sprite_by_name(szName);
	
	//0 左边，1 右边，2 上边，3 下边
	if (sprite->get_type() == "Plant") {
		if (iColSide == 1 || iColSide == 3) {
			sprite->SetSpriteLinearVelocityY(-sprite->GetSpriteLinearVelocityY());
		}
	}

	if (sprite->get_type() == "Zombie" && iColSide == 0) {
		// GameOver
	}
}