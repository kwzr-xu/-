#ifndef __Bullet_H__
#define __Bullet_H__

#include "cocos2d.h"
#include"DataClass.h"
#include"ConfigMgr.h"
using namespace std;
USING_NS_CC;
class CBullet:public Node
{
public:
	CBullet();
	~CBullet();
	bool initWithData(SBulletDt* pData);

	static CBullet* createWithData(SBulletDt* pData);
	CC_SYNTHESIZE(int,m_nDamage,Damage);
	CC_SYNTHESIZE_READONLY(Node*, m_pTarget, Target);
public:
	int m_nBulletID;
	Sprite* m_pImage;
	Animation* m_pAnimaBoom;
	virtual void update(float delta);
	void addCollsionCb(function<void(CBullet*)> Cb);
	void setTarget(Node* target);
	void createBoomAnims();
	Rect getBoundingBoxToWorld();
private:
	Vec2 m_vDir;
	function<void(CBullet*)> m_CollisionCb;
	int m_nSpeed;
};

#endif
