// 关卡选择场景类定义
#ifndef __LevelSelScene_H__
#define __LevelSelScene_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"ConfigMgr.h"
#include"DataClass.h"
USING_NS_CC;
using namespace ui;

class CLevelSelScene :public Scene
{
public:
    CLevelSelScene();
    ~CLevelSelScene();

    virtual bool init();
    CREATE_FUNC(CLevelSelScene);

private:
    void onButtonClick(Ref* pSender); // 按钮点击事件处理函数

private:
    int levelID;                      // 当前选中的关卡ID
    Button* m_pStartButton;           // 开始游戏按钮
    Button* m_pBackButton;            // 返回按钮
    PageView* m_pPage;                // 页面视图，用于关卡选择
};
#endif
