#ifndef __EnemyMgr_H__
#define __EnemyMgr_H__

#include "cocos2d.h"
#include"DataClass.h"
#include"ConfigMgr.h"
#include"Enemy.h"
using namespace std;
USING_NS_CC;
class CEnemyMgr:public Node
{
public:
	CEnemyMgr();
	~CEnemyMgr();
	virtual bool init();

	CREATE_FUNC(CEnemyMgr);
	CC_SYNTHESIZE_READONLY(int,m_nCount,Count);
	CC_SYNTHESIZE_READONLY(int, m_nWaveIndex, WaveIndex);
public:
	CEnemy* getEnemyByTilePos(const Vec2& Tilepos);
	vector<CEnemy*> iceFlowerCollic(const Vec2& pos, int nScope);
	CEnemy* getEnemyByRadius(float fRadius,const Vec2& center);
private:
	void addEnemy(float delta);
private:
	vector<CEnemy*> m_VecEnemy;
	SLevelDt* m_pCurLevelDt;//µ±Ç°¹Ø¿¨
	SWaves* m_pWave;
};

#endif
