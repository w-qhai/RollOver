
#include "LianliankanMode.h"

float                   LianLianKan::x_slot[9] = { -35, -24.5, -14, -3.5, 7, 17.5, 28, 38.5, 49 };
float                   LianLianKan::y_slot[5] = { -20, -8, 4, 15, 27 };
int                     LianLianKan::gameData[ROW + 2][COL + 2];
int                     LianLianKan::clicked_pos_x = -1;
int                     LianLianKan::clicked_pos_y = -1;
bool                    LianLianKan::is_clicked = false;
CStaticSprite           LianLianKan::Lian("LianLianKanBase");
CStaticSprite* LianLianKan::first_choose;
CStaticSprite* LianLianKan::second_choose;
CSprite                 LianLianKan::menu("LianMenu");
CSprite                 LianLianKan::back_button("LianBack");
CSprite                 LianLianKan::continue_button("LianRe");
int                     LianLianKan::total;
std::map<char*, CStaticSprite*> LianLianKan::one_map;

/// <summary>
/// 初始化连连看配置
/// </summary>

void LianLianKan::init()
{
        // 初始化连连看配置

        total = ROW * COL;

        memset(gameData, 0, sizeof(gameData));
        for (int i = 1; i <= ROW; i++) {
            for (int j = 1; j <= COL; j++) {
                Lian.SetStaticSpriteImage("llkmapImageMap", gameData[i][j] - 1);
                char* map_name = CSystem::MakeSpriteName("llkmapImageMap", i * COL + j);
                CStaticSprite* temp = new CStaticSprite(map_name);
                temp->DeleteSprite();
                one_map[map_name] = 0;

            }
        }
        one_map.clear();
        srand(time(NULL));

        int card[8] = { 0 };
        int card_index = 0;
        int current_card_num = 0;

        for (int i = 0; i < 8; i++) {
        exists:
                int temp = (rand() % MAX_CARD_NUM) + 1;
                for (int j = 0; j < i; j++) {
                        if (card[j] == temp) {
                                goto exists;
                        }
                }
                card[i] = temp;
        }

        for (int i = 1; i <= ROW; i++) {
                for (int j = 1; j <= COL; j++) {
                        // card_index = 0 时， (card_index %4 + 1) * 2 = 2
                        // card_index = 1 时， (card_index %4 + 1) * 2 = 4

                        if (current_card_num < (card_index % 4 + 1) * 2) {
                                gameData[i][j] = card[card_index];
                                current_card_num++;
                        }
                        else {
                                current_card_num = 1;
                                gameData[i][j] = card[++card_index];
                        }

                }

        }
        // 自动生成连连看图标

        //打乱顺序 
        for (int i = 1; i <= ROW * COL; ++i)
        {
                //随机得到两个数的坐标
                int x1 = rand() % COL + 1;
                int y1 = rand() % ROW + 1;
                int x2 = rand() % COL + 1;
                int y2 = rand() % ROW + 1;

                int temp = gameData[y1][x1];
                gameData[y1][x1] = gameData[y2][x2];
                gameData[y2][x2] = temp;
        }

        for (int i = 1; i <= ROW; i++) {
                for (int j = 1; j <= COL; j++) {
                        Lian.SetStaticSpriteImage("llkmapImageMap", gameData[i][j] - 1);
                        char* map_name = CSystem::MakeSpriteName("llkmapImageMap", i * COL + j);
                        CStaticSprite* temp = new CStaticSprite(map_name);
                        temp->CloneSprite("LianLianKanBase");
                        temp->SetSpritePosition(x_slot[j - 1], y_slot[i - 1]);
                        one_map[map_name] = temp;

                }
        }
}


int LianLianKan::clicked(int x, int y, CStaticSprite* sprite)
{
        if (!is_clicked)
        {
                clicked_pos_x = x;
                clicked_pos_y = y;
                is_clicked = true;
                first_choose = sprite;
                first_choose->SetSpriteColorAlpha(185);
        }
        else
        {

                second_choose = sprite;
                first_choose->SetSpriteColorAlpha(255);
                if (clicked_pos_x == x && clicked_pos_y == y) {
                        return 0;
                }
                else {

                        if (judge(clicked_pos_x, clicked_pos_y, x, y))
                        {
                                first_choose->DeleteSprite();
                                second_choose->DeleteSprite();
                                // 消除两个，并且量两个置0
                                gameData[clicked_pos_x][clicked_pos_y] = 0;
                                gameData[x][y] = 0;
                                total = total - 2;
                        }

                        first_choose = nullptr;
                        second_choose = nullptr;
                        clicked_pos_x = x;
                        clicked_pos_y = y;
                        if (total == 0) {
                                game_finish();
                        }
                }
                is_clicked = false;
        }
        return 1;
}

int LianLianKan::judge(int fromx, int fromy, int tox, int toy)
{
        if (fromx == tox && fromy == toy)
                return 0;

        if (gameData[fromx][fromy] != gameData[tox][toy])
                return 0;

        if (zero_corner(fromx, fromy, tox, toy) || one_corner(fromx, fromy, tox, toy) || two_corner(fromx, fromy, tox, toy))
                return 1;
        return 0;
}



bool LianLianKan::zero_corner(int x1, int y1, int x2, int y2)
{
        if (x1 == x2 || y1 == y2) {
                // 找出相对左上的点
                int s_x = x1, s_y = y1, e_x = x2, e_y = y2;
                if (x1 > x2) {
                        s_x = x2, s_y = y2;
                        e_x = x1, e_y = y1;
                }
                if (y1 > y2) {
                        s_x = x2, s_y = y2;
                        e_x = x1, e_y = y1;
                }

                for (int i = s_x + 1; i < e_x; i++) {
                        if (gameData[i][y1]) {
                                return false;
                        }
                }

                for (int i = s_y + 1; i < e_y; i++) {
                        if (gameData[x1][i]) {
                                return false;
                        }
                }
                return true;
        }
        return false;
}

bool LianLianKan::one_corner(int x1, int y1, int x2, int y2)
{

        int corner_one_x = x1, corner_one_y = y2;
        int corner_two_x = x2, corner_two_y = y1;

        if (gameData[corner_one_x][corner_one_y] == 0 && zero_corner(x1, y1, corner_one_x, corner_one_y) && zero_corner(x2, y2, corner_one_x, corner_one_y)) {
                return true;
        }
        if (gameData[corner_two_x][corner_two_y] == 0 && zero_corner(x1, y1, corner_two_x, corner_two_y) && zero_corner(x2, y2, corner_two_x, corner_two_y)) {
                return true;
        }
        return false;
}

bool LianLianKan::two_corner(int x1, int y1, int x2, int y2)
{
        bool tag1 = false;
        bool tag2 = false;
        // 向下走
        if (!tag1) {
                for (int i = x1 + 1; i < ROW + 2; i++) {
                        int temp_x = i, temp_y = y1;
                        if (gameData[temp_x][temp_y])
                                break;
                        tag1 = one_corner(temp_x, temp_y, x2, y2);
                        if (tag1)
                                break;
                }
        }
        // 向上走
        if (!tag1) {
                for (int i = x1 - 1; i >= 0; i--) {
                        int temp_x = i, temp_y = y1;
                        if (gameData[temp_x][temp_y])
                                break;
                        tag1 = one_corner(temp_x, temp_y, x2, y2);
                        if (tag1)
                                break;
                }
        }
        // 向右走
        if (!tag2) {
                for (int i = y1 + 1; i < COL + 2; i++) {
                        int temp_x = x1, temp_y = i;
                        if (gameData[temp_x][temp_y])
                                break;
                        tag2 = one_corner(temp_x, temp_y, x2, y2);
                        if (tag2)
                                break;
                }
        }
        // 向上走
        if (!tag2) {
                for (int i = y1 - 1; i >= 0; i--) {
                        int temp_x = x1, temp_y = i;
                        if (gameData[temp_x][temp_y])
                                break;
                        tag2 = one_corner(temp_x, temp_y, x2, y2);
                        if (tag2)
                                break;
                }
        }

        if (tag1 || tag2) {
                return true;
        }
        else {
                return false;
        }

}


/// <summary>
/// 游戏结束调用
/// </summary>
void LianLianKan::game_finish()
{
        is_clicked = false;
        menu.SetSpriteVisible(true);
        continue_button.SetSpriteVisible(true);
        back_button.SetSpriteVisible(true);
}



/// <summary>
/// 鼠标抬起事件
/// </summary>
/// <param name="iMouseType"></param>
/// <param name="fMouseX"></param>
/// <param name="fMouseY"></param>
void LianLianKan::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{
        if (iMouseType == MOUSE_LEFT)
        {
                if (continue_button.IsPointInSprite(fMouseX, fMouseY) && continue_button.IsSpriteVisible()) {
                        menu.SetSpriteVisible(false);
                        continue_button.SetSpriteVisible(false);
                        back_button.SetSpriteVisible(false);
                        g_GameMain.reload(); 
                }
                else if (back_button.IsPointInSprite(fMouseX, fMouseY) && back_button.IsSpriteVisible()) {
                        SuperSound::closeAndPlay("open-click2", "play-click2", "close-click2");
                        CSystem::LoadMap("menu.t2d");
                        g_GameMain.reload();
                        CGameMain::SetLianLianKan(false);
                        g_GameMain.map_id = CGameMain::MapType::MenuType;
                }
                else {
                        int current_x = 1, current_y = 1;
                        for (std::map<char*, CStaticSprite*>::iterator iter = one_map.begin(); iter != one_map.end(); iter++)
                        {
                                if (iter->second->IsPointInSprite(fMouseX, fMouseY))
                                        clicked(current_x, current_y, iter->second);

                                if (current_y != COL)
                                        current_y++;
                                else
                                        current_y = 1, current_x++;

                        }
                }



        }
}

void	 LianLianKan::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {
    if (std::string(szSrcName) == "ZombieHead" && std::string(szTarName) == "Flag") {
        CStaticSprite flag("Flag");
        flag.SetSpriteEnable(false);
        SuperSound::closeAndPlay("open-zombie-howl", "play-zombie-howl", "close-zombie-howl");
        game_finish();
    }
}