#include"BulletMgr.h"

CBulletMgr::CBulletMgr()
{
}

CBulletMgr::~CBulletMgr()
{
	_eventDispatcher->removeCustomEventListeners("addBullet");
}

bool CBulletMgr::init()
{
	if (!Node::init()) {
		return false;
	}
	_eventDispatcher->addCustomEventListener("addBullet",CC_CALLBACK_1(CBulletMgr::addBullet,this));
	return true;
}

void CBulletMgr::addBullet(EventCustom * pEvent)
{
	CBullet* pBullet = static_cast<CBullet*>(pEvent->getUserData());
	this->addChild(pBullet);
}
