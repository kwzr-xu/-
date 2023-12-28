#ifndef __Radish_H__
#define __Radish_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class CRadish:public Node
{
public:
	CRadish();
	~CRadish();
	virtual bool init();
	
	CREATE_FUNC(CRadish);
	CC_SYNTHESIZE(int,m_nHp,Hp);
	CC_SYNTHESIZE(int,m_nHpState,HpState);
public:
	Sprite* m_pHpBar;
	Sprite* m_pImage;
private:
};


#endif

