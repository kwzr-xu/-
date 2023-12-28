#include"EnemyMgr.h"
#include"DynamicDt.h"
#include"GameScene.h"
CEnemyMgr::CEnemyMgr()
	:m_nWaveIndex(0)
	,m_nCount(0)
{
}

CEnemyMgr::~CEnemyMgr()
{
}

bool CEnemyMgr::init()
{
	if (!Node::init()) {
		return false;
	}

	int nLevelID = CDynamicDt::getInstance()->getLevelID();

	m_pCurLevelDt = static_cast<SLevelDt*>(CConfigMgr::getInstance()->getData("LevelDtMgr")->getDataByID(nLevelID));

	m_pWave = m_pCurLevelDt->m_VecWaves[m_nWaveIndex];//第一波怪物的数据


	this->schedule(CC_CALLBACK_1(CEnemyMgr::addEnemy, this), m_pWave->fCurInterval, "addEnemy");
	return true;

}
CEnemy * CEnemyMgr::getEnemyByTilePos(const Vec2 & Tilepos)
{
	Vector<Node*> VecChild = this->getChildren();
	for (Node*& pNode : VecChild) {
		//CEnemy* pEnemy = static_cast<CEnemy*>(pNode);
		Vec2 pos = pNode->getPosition();
		Vec2 tilePos = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(pos);
		if (tilePos == Tilepos) {
			return static_cast<CEnemy*>(pNode);
		}
	}
	return nullptr;
}
vector<CEnemy*> CEnemyMgr::iceFlowerCollic(const Vec2 & pos,int nScope)
{
	Vector<Node*> VecEnemy = this->getChildren();
	for (Node*& pENode : VecEnemy) {
		CEnemy* pEnemy = static_cast<CEnemy*>(pENode);
		Vec2 EnemyPos = pEnemy->getPosition();
		float fDis = EnemyPos.getDistanceSq(pos);
		if (fDis <= nScope * nScope) {
			m_VecEnemy.push_back(pEnemy);
		}
	}
	return m_VecEnemy;

}

CEnemy * CEnemyMgr::getEnemyByRadius(float fRadius, const Vec2 & center)
{
	Vector<Node*> VecChild = this->getChildren();
	for (Node*& pNode:VecChild) {
		//CEnemy* pEnemy = static_cast<CEnemy*>(pNode);
		Vec2 pos = pNode->getPosition();
		float fDistSq = pos.getDistanceSq(center);
		if (fDistSq<=fRadius*fRadius) {
			return static_cast<CEnemy*>(pNode);
		}
	}
	return nullptr;
}

void CEnemyMgr::addEnemy(float delta)
{
	if (m_nCount>m_pWave->nEnemyCount) {
		m_nCount = 0;
		m_nWaveIndex++;
		this->unschedule("addEnemy");//关闭定时器
		if (m_nWaveIndex> m_pCurLevelDt->m_VecWaves.size()-1) {
			//怪物生成完毕，返回
			return;
		}

		m_pWave = m_pCurLevelDt->m_VecWaves[m_nWaveIndex];

		this->scheduleOnce([&](float)->void {
			this->schedule(CC_CALLBACK_1(CEnemyMgr::addEnemy, this), m_pWave->fCurInterval, "addEnemy");
			this->addEnemy(0);
			CGameScene::getInstance()->m_pWaveLabel->setString(StringUtils::format("0 %d", m_nWaveIndex + 1));
			CDynamicDt::getInstance()->setWaveIndex(m_nWaveIndex + 1);
		}, m_pWave->fNextInterval, "nextWave");
		//根据波数据重新开启新的定时器
		return;
	}
	m_nCount++;
	SEnemyDt* pEnemyDt = static_cast<SEnemyDt*>(CConfigMgr::getInstance()->getData("EnemyDtMgr")->getDataByID(m_pWave->nEnemyID));

	CEnemy* pEnemy = CEnemy::createWithData(pEnemyDt);

	this->addChild(pEnemy);

}
