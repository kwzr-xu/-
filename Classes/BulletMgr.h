#ifndef __BulletMgr_H__
#define __BulletMgr_H__

#include "cocos2d.h"
#include"DataClass.h"
#include"ConfigMgr.h"
#include"Bullet.h"
using namespace std;
USING_NS_CC;
class CBulletMgr:public Node
{
public:
	CBulletMgr();
	~CBulletMgr();
	virtual bool init();

	void addBullet(EventCustom* pEvent);
	CREATE_FUNC(CBulletMgr);
private:

};

#endif
