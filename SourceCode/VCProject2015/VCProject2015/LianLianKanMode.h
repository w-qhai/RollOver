#pragma once
#include "LessonX.h"

extern long double fTimeDelta;
extern long double game_start;

const int ROW = 5;      //游戏界面总行数 
const int COL = 8;      //游戏界面总列数 

#define MAX_CARD_NUM 52

namespace LianLianKan {


	extern float x_slot[9];
	extern float y_slot[5];
	extern int gameData[ROW + 2][COL + 2];
	extern int clicked_pos_x;
	extern int clicked_pos_y;
	extern int total;
	extern bool is_clicked;
	extern CStaticSprite Lian;
	extern std::map<char*, CStaticSprite*> one_map;
	extern CSprite base_map;
	extern CSprite menu;
	extern CSprite back_button;
	extern CSprite continue_button;
	extern CStaticSprite* first_choose;
	extern CStaticSprite* second_choose;


	void		init();
	int			clicked(const int x, const int y, CStaticSprite* sprite);
	int			judge(const int x1, const int y1, const int x2, const int y2);
	bool		zero_corner(const int x1, const int y1, const int x2, const int y2);
	bool		one_corner(const int x1, const int y1, const int x2, const int y2);
	bool		two_corner(const int x1, const int y1, const int x2, const int y2);
	void		game_finish();

	void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
	void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
};