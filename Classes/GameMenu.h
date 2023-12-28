#ifndef __GameMenu_H__
#define __GameMenu_H__


#include "cocos2d.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace std;
class CGameMenu:public Scene
{
public:
	CGameMenu();
	~CGameMenu();

	virtual bool init();

	CREATE_FUNC(CGameMenu);
private:
	//void leafShake(float Dt);//一段时间叶子抖动一下
	//void update(float delta);
	void click(Ref* pSender);
	void createButton();
	void createObject();
private:
	//Vec2 m_nMDir;
	//Vec2 m_nCDir;
	Sprite* m_pDyMonster;
	Sprite* m_pDyCloud;
	Sprite* m_pleaf1;
	Sprite* m_pleaf2;
	Sprite* m_pleaf3;
	Button* m_pAdvent;
	//Button* m_pBoos;
	//Button* m_pMonster;
	//Button* m_pSetup;//设置
	//Button* m_pDoubt;//疑问
	Button* m_pStart;
};


#endif