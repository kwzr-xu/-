#ifndef __TowerMgr_H__
#define __TowerMgr_H__

#include "cocos2d.h"
#include"DataClass.h"
#include"ConfigMgr.h"
#include"ui/CocosGUI.h"
#include"Tower.h"
using namespace std;
USING_NS_CC;
using namespace ui;
class CTowerMgr:public Node
{
public:
	CTowerMgr();
	~CTowerMgr();
	virtual bool init();


	CREATE_FUNC(CTowerMgr);
	CC_SYNTHESIZE_READONLY(Vec2,m_nTouchPos,TouchPos);
	CC_SYNTHESIZE_READONLY(CTower*,m_nTower,Tower);
private:
	void upGradeTips(int nCoin);
	CTower* getTowerByPos(const Vec2& pos);
	bool isTower(const Vec2& pos);
	void upGradeAndDeleta(CTower* pTower);
	void createCurCard();
	void creatAnims();
	void addTowerClick(Ref* pRender,int nTowerID);
	void UpGradeClick(Ref* pRender);
	void DeleteClick(Ref* pRender);
private:
	Button* m_pUpGrade1;
	Sprite* m_pOK;
	Sprite* m_pUpGradeAnims;
	Node* pNode;
	SLevelDt* m_pCurLevelDt;
	Animation* m_pAnimationSel;
	Animation* m_pAnimationPaint;
	Animation* m_pAnimationUpGrade;
	Animation* m_pAnimationUpTips;
	void addTouchEvent();
	bool onTouchBegan(Touch* pTouch,Event* pEvent);

};

#endif
