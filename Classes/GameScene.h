#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include"DataClass.h"
#include"ConfigMgr.h"
#include"ui/CocosGUI.h"
#include"TiledMapCtrl.h"
#include"EnemyMgr.h"
#include"Radish.h"
#include"TowerMgr.h"
#include"BulletMgr.h"
#include"GameOver.h"


USING_NS_CC;
using namespace ui;


class CGameScene:public Scene
{
public:
	CGameScene();
	~CGameScene();
	static CGameScene* getInstance();
	static CGameScene* destory();
	virtual bool init();
	CREATE_FUNC(CGameScene);
	CC_SYNTHESIZE_READONLY(CRadish*, m_pRadish, Radish);
	CC_SYNTHESIZE_READONLY(CTiledMapCtrl*, m_pTiledMapCtrl, TiledMapCtrl);
	CC_SYNTHESIZE_READONLY(CEnemyMgr*, m_pEnemyMgr, EnemyMgr);
	CC_SYNTHESIZE_READONLY(CTowerMgr*, m_pTowerMgr, TowerMgr);
	CC_SYNTHESIZE_READONLY(CBulletMgr*,m_pBulletMgr,BulletMgr);
	CC_SYNTHESIZE_READONLY(CGameOver*,m_pGameOver, GameOver);
	CC_SYNTHESIZE_READONLY(string,m_StrOverOrEnd, OverOrEnd);
public:
	Label* m_pCoinLabel;
	Label* m_pWaveLabel;
	Label* m_pTotalWaveLabel;
private:
	virtual void update(float delta);
	void createMenu();
	void stop(Ref* pSender);
	void addMenu(Ref* pSender);
	void click(Ref* pSender);
	char* G2U(const char* gb2312);
	void Speed_Up(Ref* pSender);
	//void createOb();//¥¥Ω®’œ∞≠ŒÔ
private:
	Node* m_pMenuNode;
	Sprite* m_pWaveNum;
	Button* m_pNormalSpeed;
	Button* m_pMenu;
	Button* m_pStop;
	Button* m_pContinue;
	Button* m_pResume;
	Button* m_pLevelSel;
	Animation* m_pEnemyBoom;
	int m_nTimer;
	Label* m_pLabel;
	SLevelDt* m_pCurLevelDt;
	static CGameScene* m_pInstance;
};
#endif
