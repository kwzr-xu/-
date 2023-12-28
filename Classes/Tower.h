#ifndef __Tower_H__
#define __Tower_H__

#include "cocos2d.h"
#include"DataClass.h"
#include"ConfigMgr.h"
#include"Enemy.h"
#include"Bullet.h"
using namespace std;
USING_NS_CC;
enum {
	E_STATE_NORMAL,
	E_STATE_FIRE
};
class CTower:public Node
{
public:
	CTower();
	~CTower();
	bool initWithData(int nTowerID);
	void upgrade();
	static CTower* createWithData(int nTowerID);
	CC_SYNTHESIZE(int ,m_nCurGrade,CurGrade);
	CC_SYNTHESIZE(int ,m_nSaleCoin,SaleCoin);
	CC_SYNTHESIZE(int ,m_nUpGradeCoin, UpGradeCoin);

private:
	void search(float delta);
	void fire(float Dt);//ÅÚÌ¨¿ª»ð
private:
	int i;
	int m_nCurTowerID;
	int m_nEnemyIndex;
	float m_fDisSq;
	Vec2 m_nDir;
	int nCurState;
	Sprite* m_pImage;
	STowerDt* m_pTowerDt;
};


#endif
