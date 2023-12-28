// �ؿ�ѡ�񳡾��ඨ��
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
    void onButtonClick(Ref* pSender); // ��ť����¼�������

private:
    int levelID;                      // ��ǰѡ�еĹؿ�ID
    Button* m_pStartButton;           // ��ʼ��Ϸ��ť
    Button* m_pBackButton;            // ���ذ�ť
    PageView* m_pPage;                // ҳ����ͼ�����ڹؿ�ѡ��
};
#endif
