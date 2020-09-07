#pragma once
#include "LessonX.h"
extern long double fTimeDelta;
extern long double game_start;
extern int bowling_counter;
extern int total_zombie;
namespace Bowling {
    extern bool			    left_pressed;   // 鼠标左键是否按下
    extern Card*            card;		    // 植物卡
    extern Plant*           seed;		    // 植物种子
    extern WallNutBowling   bowling;        // 
    extern CSprite          top_side;       // 上方空气墙
    extern CSprite          bottom_side;    // 下方空气墙
    extern CSprite          background;

    extern CSprite          game_over;      // 游戏失败图片
    extern CSprite          game_close;     // 返回主菜单按钮
    extern CSprite          play_again;     // 重新开始按钮

    extern CSprite          game_win;        // 游戏胜利图片
    extern CSprite          game_close2;    // 返回主菜单按钮
    extern CSprite          next;           // 下一关按钮 

    // 游戏中的菜单
    extern CSprite          game_menu_btn;
    extern CSprite          game_menu;
    extern CSprite          main_menu;
    extern CSprite          rebegin;
    extern CSprite          continue_;

    void		OnMouseMove(const float fMouseX, const float fMouseY);
    void		OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
    void		OnKeyUp(const int iKey);
    void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
    void		OnSpriteColWorldLimit(const char* szName, const int iColSide);
};

