#include"Tower.h"
#include"GameScene.h"
CTower::CTower()
	:m_nCurGrade(0)
	, nCurState(E_STATE_NORMAL)
	,m_nSaleCoin(0)
	,m_nDir(0,-1)
	,m_nEnemyIndex(0)
	,m_nCurTowerID(0)
	,i(0)
{
}

CTower::~CTower()
{
}

bool CTower::initWithData(int nTowerID)
{
	if (!Node::init()) {
		return false;
	}
	m_nCurTowerID = nTowerID;
	m_pTowerDt = static_cast<STowerDt*>(CConfigMgr::getInstance()->getData("TowerDtMgr")->getDataByID(nTowerID));
	m_pImage = Sprite::createWithSpriteFrameName(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]);
	m_nSaleCoin = m_pTowerDt->m_VecLevel[m_nCurGrade]->nWorth;
	m_nUpGradeCoin = m_pTowerDt->m_VecLevel[m_nCurGrade]->nUpgradeCoin;
	this->addChild(m_pImage);
	this->schedule(CC_CALLBACK_1(CTower::search,this),"search");
	this->schedule(CC_CALLBACK_1(CTower::fire, this), m_pTowerDt->m_VecLevel[m_nCurGrade]->fAckInterval, "fire");
	return true;
}

//��������
void CTower::upgrade()
{
	m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[++m_nCurGrade]->VecImg[nCurState]);
	setSaleCoin(m_pTowerDt->m_VecLevel[m_nCurGrade]->nWorth);
	setUpGradeCoin(m_pTowerDt->m_VecLevel[m_nCurGrade]->nUpgradeCoin);
	setCurGrade(m_nCurGrade);
}

CTower * CTower::createWithData(int nTowerID)
{
	CTower* pTower = new CTower();
	if (pTower&&pTower->initWithData(nTowerID)) {
		pTower->autorelease();
		return pTower;
	}
	CC_SAFE_DELETE(pTower);

	return nullptr;
}

//getTarget() {}


void CTower::search(float delta)
{
	//Vector<Node*> VecEnemy = CGameScene::getInstance()->getEnemyMgr()->getChildren();
	//for (Node*& pENode : VecEnemy) {
	//	CEnemy* pEnemy = static_cast<CEnemy*>(pENode);
	CEnemy* pTarget = CGameScene::getInstance()->getEnemyMgr()->getEnemyByRadius(m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope, this->getPosition());
	if (pTarget) {
		Vec2 EnemyPos = pTarget->getPosition();
		Vec2 TowerPos = this->getPosition();
		m_fDisSq = EnemyPos.getDistanceSq(TowerPos);
		float TowerScope = m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope;
		//ֻ�м�����̨�Ż���ת
		//ֻ�е�ǰһֻ���˲Ż�����ת��
		if (TowerScope*TowerScope >= m_fDisSq && (m_nCurTowerID == 4001 || m_nCurTowerID == 4002 || m_nCurTowerID == 4003 || m_nCurTowerID == 4004 || m_nCurTowerID == 4006)) {
			//������̨������Χ
			//��ת��̨
			Vec2 disPos = EnemyPos - TowerPos;
			m_nDir = disPos.getNormalized();
			
			//float fAngle = Vec2::angle(m_nDir, Vec2(1, 0));
			//float fDegree = CC_RADIANS_TO_DEGREES(fAngle);
			//m_pImage->setRotation(fDegree - 90);
			Vec2 downVector(0, -1);
			float angleRadians = m_nDir.getAngle(downVector);
			float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
			m_pImage->setRotation(angleDegrees);
		}
	}
}

void CTower::fire(float Dt)
{
	// ��ȡ������������Χ�ڵĵ���
	CEnemy* pTarget = CGameScene::getInstance()->getEnemyMgr()->getEnemyByRadius(m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope, this->getPosition());

	// ����е����ڹ�����Χ��
	if (pTarget) {
		// �ж����������Ƿ���ָ���ļ��֣�4001��4002��4004��
		if (m_nCurTowerID == 4001 || m_nCurTowerID == 4002 || m_nCurTowerID == 4004) {
			// �л������ĵ�ǰ״̬Ϊ������
			nCurState = E_STATE_FIRE;

			// ����������ʾ��ͼƬ�����������ȼ��͵�ǰ״̬��ȡ��Ӧ��ͼƬ��
			m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]);

			// ��ȡ������ǰ�ȼ���Ӧ���ӵ���Ϣ
			SBulletDt* pBulletDt = static_cast<SBulletDt*>(CConfigMgr::getInstance()->getData("BulletDtMgr")->getDataByID(m_pTowerDt->m_VecLevel[m_nCurGrade]->nBulletID));

			// �����ӵ����󣬲�����λ��Ϊ����λ��
			CBullet* pBullet = CBullet::createWithData(pBulletDt);
			pBullet->setPosition(this->getPosition());

			// �����Զ����¼���֪ͨ��������ӵ�
			_eventDispatcher->dispatchCustomEvent("addBullet", pBullet);
			pBullet->setTarget(pTarget);
			pBullet->setDamage(m_pTowerDt->m_VecLevel[m_nCurGrade]->nAck);

			// ����ӵ���ײ�ص��������ӵ���ײ������ʱִ�е��˵� onCollision ����
			pBullet->addCollsionCb(CC_CALLBACK_1(CEnemy::onCollision, pTarget));

			// ��������ָ����˵ķ���
			Vec2 dir = (pTarget->getPosition() - this->getPosition()).getNormalized();

			// �����ӵ�����ת�Ƕȣ�ʹ�䳯�����
			Vec2 downVector(0, -1);
			float angleRadians = dir.getAngle(downVector);
			float angleDegrees = angleRadians * 180 / M_PI;
			pBullet->setRotation(angleDegrees);
		}
	}
		else {
			nCurState = E_STATE_NORMAL;
			m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]);
		}
}