#pragma once
#include "LessonX.h"
extern long double fTimeDelta;
extern int bowling_counter;
namespace Bowling {
    extern bool			left_pressed;   // 鼠标左键是否按下
    extern Card* card;		    // 植物卡
    extern Plant* seed;		    // 植物种子
    extern WallNutBowling bowling;
    extern CSprite top_side;
    extern CSprite bottom_side;

    void		OnMouseMove(const float fMouseX, const float fMouseY);
    void		OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
    void		OnKeyUp(const int iKey);
    void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
    void		OnSpriteColWorldLimit(const char* szName, const int iColSide);
};

