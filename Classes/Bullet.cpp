// ���� Bullet.h ͷ�ļ�
#include "Bullet.h"

// ���캯������ʼ���ӵ��ٶ�Ϊ 0
CBullet::CBullet()
	: m_nSpeed(0)
{
}

// ��������
CBullet::~CBullet()
{
}

// ��ʼ���ӵ����ݵķ���������һ�������ӵ����ݵĽṹ�� SBulletDt ָ��
bool CBullet::initWithData(SBulletDt* pData)
{
	// ʹ�� Cocos2d-x Node �ĳ�ʼ������
	if (!Node::init()) {
		return false;
	}

	// �Ӵ�������ݽṹ���л�ȡ�ӵ� ID ���ٶ�
	m_nBulletID = pData->nID;
	m_nSpeed = pData->nSpeed;

	// ʹ�õ�һ��ͼƬ���� Sprite������ӵ���ǰ Node
	m_pImage = Sprite::createWithSpriteFrameName(pData->VecImgs[0]);
	this->addChild(m_pImage);

	// ������ը����
	this->createBoomAnims();

	// ��ʼ���ɹ�
	return true;
}

// ����һ���ӵ����󲢷��أ�����һ�������ӵ����ݵĽṹ�� SBulletDt ָ��
CBullet* CBullet::createWithData(SBulletDt* pData)
{
	// �����ӵ�����
	CBullet* pBullet = new CBullet();

	// ��������ɹ����ҳ�ʼ���ɹ����Զ��ͷŶ��󲢷���
	if (pBullet && pBullet->initWithData(pData)) {
		pBullet->autorelease();
		return pBullet;
	}

	// ����ʧ�ܻ��ʼ��ʧ��ʱ���ͷŶ��󲢷��ؿ�ָ��
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

// ÿ֡���·����������ƶ��ӵ��������ײ��
void CBullet::update(float delta)
{
	// �ж��ӵ������Ƿ�Ϊ�ض����ͣ�����ǣ���ִ����Ӧ�߼�
	if (m_nBulletID == 5001 || m_nBulletID == 5004 || (m_nBulletID >= 5010 && m_nBulletID <= 5012)) {
		// ���û��Ŀ�ֱ꣬�ӷ���
		if (!m_pTarget) {
			return;
		}

		// ��ȡĿ��λ�ú͵�ǰλ��
		Vec2 EnemyPos = m_pTarget->getPosition();
		Vec2 pos = this->getPosition();

		// �����ӵ��ƶ����򲢸���λ��
		m_vDir = (EnemyPos - pos).getNormalized();
		pos += (m_vDir * m_nSpeed * delta);
		this->setPosition(pos);

		// �����ӵ���Ŀ��֮��ľ���
		float fDisSq = EnemyPos.getDistanceSq(pos);

		// �������С�ڵ��� 5 ��ƽ��������Ϊ������ײ
		if (fDisSq <= 5 * 5) {
			// ������ײ
			// ִ����ײ�ص�����
			m_CollisionCb(this);
		}
	}
}

// �����ӵ���Ŀ��ڵ�
void CBullet::setTarget(Node* target)
{
	m_pTarget = target;
	// ����ÿ֡����
	this->scheduleUpdate();
}

// �����ײ�ص�����������һ������������Ϊ�ص�
void CBullet::addCollsionCb(std::function<void(CBullet*)> Cb)
{
	m_CollisionCb = Cb;
}

// ������ը����
void CBullet::createBoomAnims()
{
	// �����ù�������ȡ�ӵ��ı�ըЧ������
	SEffectDt* pData = static_cast<CEffectDtMgr*>(CConfigMgr::getInstance()->getData("EffectDtMgr"))->getDataByObjectID(m_nBulletID);

	// ��ȡ����֡����ʵ��
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();

	// ������ը��������
	m_pAnimaBoom = Animation::create();

	// �����ӵ���ըЧ����ͼƬ����ӵ�������
	for (int i = 0; i < pData->VecImgs.size(); i++) {
		SpriteFrame* pFrame = pCache->getSpriteFrameByName(pData->VecImgs[i]);
		m_pAnimaBoom->addSpriteFrame(pFrame);
	}

	// ���ö���ÿ֡�Ĳ��ż��
	m_pAnimaBoom->setDelayPerUnit(0.1);

	// �Զ����������ü�������ֹ���ͷ�
	m_pAnimaBoom->retain();
}

// ��ȡ�ӵ�����������ϵ�еİ�Χ��
Rect CBullet::getBoundingBoxToWorld()
{
	// ��ȡ�ӵ�ͼƬ�İ�Χ��
	Rect rcImg = m_pImage->getBoundingBox();

	// ����һ�����ζ��󣬱�ʾ�ӵ�����������ϵ�еİ�Χ��
	Rect rc;
	rc.size = rcImg.size;
	rc.origin = this->convertToWorldSpaceAR(rcImg.origin);
	return rc;
}
