#ifndef __LevelSelScene_H__
#define __LevelSelScene_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"ConfigMgr.h"
#include"DataClass.h"
USING_NS_CC;
using namespace ui;
class CLevelSelScene:public Scene
{
public:
	CLevelSelScene();
	~CLevelSelScene();

	virtual bool init();


	CREATE_FUNC(CLevelSelScene);

private:
	void onButtonClick(Ref* pSender);
private:
	int levelID;
	Button* m_pStartButton;
	Button* m_pBackButton;
	PageView* m_pPage;
};
#endif
