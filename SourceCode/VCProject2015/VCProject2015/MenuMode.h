#pragma once
#include "LessonX.h"

namespace Menu {
    extern CStaticSprite adventure;	    // 冒险模式
    extern CStaticSprite mini;			// 迷你游戏
    extern CStaticSprite edu;			// 益智模式

    extern CStaticSprite help_btn;		// 帮助按钮
    extern CStaticSprite help_msg;		// 帮助消息面板
    extern CStaticSprite help_close;	// 帮助关闭按钮

    void		OnMouseMove(const float fMouseX, const float fMouseY);
    void		OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
    void		OnKeyUp(const int iKey);
    void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
    void		OnSpriteColWorldLimit(const char* szName, const int iColSide);
};
