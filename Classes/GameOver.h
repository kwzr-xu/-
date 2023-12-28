// 游戏结束类定义
#ifndef __GameOver_H__
#define __GameOver_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace ui;

class CGameOver :public Node
{
public:
    CGameOver();
    ~CGameOver();
    virtual bool init();
    CREATE_FUNC(CGameOver);
public:
    void createGameSuccess(); // 创建游戏成功界面的函数
    void createGameOver();    // 创建游戏失败界面的函数
private:
    char* G2U(const char* gb2312); // GB2312到UTF-8的编码转换函数
    void click(Ref* pSender);      // 按钮点击事件处理函数
private:
    bool isWin;                    // 游戏是否胜利标志
    bool isFail;                   // 游戏是否失败标志
    Button* m_pLevelSel;           // 关卡选择按钮
    Button* m_pTryAgain;           // 再试一次按钮
};

#endif