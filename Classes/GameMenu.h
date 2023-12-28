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
	static cocos2d::Scene* scene();

	CREATE_FUNC(CGameMenu);
	void click(Ref* pSender);
};


#endif