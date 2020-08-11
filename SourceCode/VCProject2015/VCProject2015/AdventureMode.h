#pragma once
#include "LessonX.h"

extern long double fTimeDelta;

namespace Adventure {
    extern bool			left_pressed;   // 鼠标左键是否按下
    extern Card*        card;		    // 植物卡
    extern Plant*       seed;		    // 植物种子
    extern Shovel*      shovel;         // 选中了小铲子
    extern CSprite      background;
    extern CSprite      game_over;
    extern CSprite      game_close;
    extern CSprite      play_again;

    void		OnMouseMove(const float fMouseX, const float fMouseY);
    void		OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
    void		OnKeyUp(const int iKey);
    void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
    void		OnSpriteColWorldLimit(const char* szName, const int iColSide);
};