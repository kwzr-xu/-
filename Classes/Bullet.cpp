#include"Bullet.h"
CBullet::CBullet()
	:m_nSpeed(0)
{
}

CBullet::~CBullet()
{
}

bool CBullet::initWithData(SBulletDt * pData)
{
	if (!Node::init()) {
		return false;
	}
	m_nBulletID = pData->nID;
	m_nSpeed = pData->nSpeed;
	m_pImage = Sprite::createWithSpriteFrameName(pData->VecImgs[0]);
	this->addChild(m_pImage);
	this->createBoomAnims();
	return true;
}

CBullet * CBullet::createWithData(SBulletDt * pData)
{
	CBullet* pBullet = new CBullet();
	if (pBullet&&pBullet->initWithData(pData)) {
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}
void CBullet::update(float delta)
{

	if (m_nBulletID == 5001|| m_nBulletID == 5004|| (m_nBulletID>=5010&&m_nBulletID<=5012)) {
		if (!m_pTarget) {
			this->removeFromParent(); // 销毁子弹
			return;
		}
		Vec2 EnemyPos = m_pTarget->getPosition();
		Vec2 pos = this->getPosition();
		m_vDir = (EnemyPos - pos).getNormalized();
		pos += (m_vDir * m_nSpeed*delta);
		this->setPosition(pos);
		float fDisSq = EnemyPos.getDistanceSq(pos);
		if (fDisSq <= 5 * 5) {
			//碰撞处理
			//播放
			m_CollisionCb(this);
		}
	}
}
void CBullet::addCollsionCb(function<void(CBullet*)> Cb)
{
	m_CollisionCb = Cb;
}
void CBullet::setTarget(Node * target)
{
	m_pTarget = target;
	this->scheduleUpdate();
}
void CBullet::createBoomAnims()
{
	SEffectDt* pData = static_cast<CEffectDtMgr*>(CConfigMgr::getInstance()->getData("EffectDtMgr"))->getDataByObjectID(m_nBulletID);
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	m_pAnimaBoom = Animation::create();
	for (int i = 0; i < pData->VecImgs.size();i++) {
		SpriteFrame* pFrame = pCache->getSpriteFrameByName(pData->VecImgs[i]);
		m_pAnimaBoom->addSpriteFrame(pFrame);
	}

	m_pAnimaBoom->setDelayPerUnit(0.1);
	m_pAnimaBoom->retain();
}
Rect CBullet::getBoundingBoxToWorld()
{
	Rect rcImg = m_pImage->getBoundingBox();
	Rect rc;
	rc.size = rcImg.size;
	rc.origin = this->convertToWorldSpaceAR(rcImg.origin);
	return rc;
}