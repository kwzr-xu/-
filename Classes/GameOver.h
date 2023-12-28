#ifndef __GameOver_H__
#define __GameOver_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace ui;

class CGameOver:public Node
{
public:
	CGameOver();
	~CGameOver();
	virtual bool init();
	CREATE_FUNC(CGameOver);
public:
	void createGameSuccess();
	void createGameOver();
private:
	//char* G2U(const char* gb2312);
	void click(Ref* pSender);
private:
	bool isWin;
	bool isFail;
	Button* m_pLevelSel;
	Button* m_pTryAgain;
};

#endif
