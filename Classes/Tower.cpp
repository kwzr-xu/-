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

//升级炮塔
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
		//只有几种塔台才会旋转
		//只有等前一只死了才会重新转向
		if (TowerScope*TowerScope >= m_fDisSq && (m_nCurTowerID == 4001 || m_nCurTowerID == 4002 || m_nCurTowerID == 4003 || m_nCurTowerID == 4004 || m_nCurTowerID == 4006)) {
			//进入炮台攻击范围
			//旋转炮台
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
	// 获取在炮塔攻击范围内的敌人
	CEnemy* pTarget = CGameScene::getInstance()->getEnemyMgr()->getEnemyByRadius(m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope, this->getPosition());

	// 如果有敌人在攻击范围内
	if (pTarget) {
		// 判断炮塔类型是否是指定的几种（4001、4002、4004）
		if (m_nCurTowerID == 4001 || m_nCurTowerID == 4002 || m_nCurTowerID == 4004) {
			// 切换炮塔的当前状态为“开火”
			nCurState = E_STATE_FIRE;

			// 更新炮塔显示的图片（根据炮塔等级和当前状态获取对应的图片）
			m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]);

			// 获取炮塔当前等级对应的子弹信息
			SBulletDt* pBulletDt = static_cast<SBulletDt*>(CConfigMgr::getInstance()->getData("BulletDtMgr")->getDataByID(m_pTowerDt->m_VecLevel[m_nCurGrade]->nBulletID));

			// 创建子弹对象，并设置位置为炮塔位置
			CBullet* pBullet = CBullet::createWithData(pBulletDt);
			pBullet->setPosition(this->getPosition());

			// 发送自定义事件，通知场景添加子弹
			_eventDispatcher->dispatchCustomEvent("addBullet", pBullet);
			pBullet->setTarget(pTarget);
			pBullet->setDamage(m_pTowerDt->m_VecLevel[m_nCurGrade]->nAck);

			// 添加子弹碰撞回调，即当子弹碰撞到敌人时执行敌人的 onCollision 方法
			pBullet->addCollsionCb(CC_CALLBACK_1(CEnemy::onCollision, pTarget));

			// 计算炮塔指向敌人的方向
			Vec2 dir = (pTarget->getPosition() - this->getPosition()).getNormalized();

			// 设置子弹的旋转角度，使其朝向敌人
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