#pragma once
#include "LessonX.h"



namespace Menu {
    extern CStaticSprite adventure;	    // 冒险模式
    extern CStaticSprite mini;			// 迷你游戏
    extern CStaticSprite edu;			// 益智模式

    extern CStaticSprite help_btn;		// 帮助按钮
    extern CStaticSprite help_msg;		// 帮助消息面板
    extern CStaticSprite help_close;	// 帮助关闭按钮
    extern CStaticSprite exit_;	        // 退出游戏

    extern CStaticSprite achievement;   // 成就按钮
    extern CStaticSprite score_board;   // 成就面板
    extern CStaticSprite score_close;   // 成就面板关闭

    extern CStaticSprite level_1;
    extern CStaticSprite level_2;
    extern CStaticSprite level_3;
    extern CStaticSprite level_4;
    extern CStaticSprite level_5;

    // 用时
    extern CTextSprite	 bowling_score;
    extern CTextSprite	 level1_score;
    extern CTextSprite	 level2_score;
    extern CTextSprite	 level3_score;
    extern CTextSprite	 level4_score;
    extern CTextSprite	 level5_score;

    void		OnMouseMove(const float fMouseX, const float fMouseY);
    void		OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
    void		OnKeyUp(const int iKey);
    void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
    void		OnSpriteColWorldLimit(const char* szName, const int iColSide);
};
