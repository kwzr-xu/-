#include "LoadData.h"
#include "ConfigMgr.h"
#include "DataClass.h"
CLoadData::CLoadData()
{
	this->initConfigs();
}


CLoadData::~CLoadData()
{
}

void CLoadData::initConfigs()
{

	//加载选择关卡数据
	CselLevelDtMgr* pSelLevelDtMgr = new CselLevelDtMgr();
	pSelLevelDtMgr->loadFile("Config/SelLevel.json");
	//存储到配置管理者里面
	CConfigMgr::getInstance()->setData("SelLevelDtMgr", pSelLevelDtMgr);


	//加载关卡数据
	CLevelDtMgr* pLevelDtMgr = new CLevelDtMgr();
	pLevelDtMgr->loadFile("Config/LevelDt.json");
	//存储到配置管理者里面
	CConfigMgr::getInstance()->setData("LevelDtMgr", pLevelDtMgr);


	//加载敌人数据
	CEnemyDtMgr* pEnemyDtMgr = new CEnemyDtMgr();
	pEnemyDtMgr->loadFile("Config/EnemyDt.json");
	//存储到配置管理者里面
	CConfigMgr::getInstance()->setData("EnemyDtMgr", pEnemyDtMgr);


	//加载障碍物数据
	CObstaclesDtMgr* pObstaclesDtMgr = new CObstaclesDtMgr();
	pObstaclesDtMgr->loadFile("Config/obstaclesDt.json");
	//存储到配置管理者里面
	CConfigMgr::getInstance()->setData("ObstaclesDtMgr", pObstaclesDtMgr);

	//加载卡片数据
	CCardDtMgr* pCardDtMgr = new CCardDtMgr();
	pCardDtMgr->loadFile("Config/CardDt.json");
	//存储到配置管理者里面
	CConfigMgr::getInstance()->setData("CardDtMgr", pCardDtMgr);


	//加载塔台数据
	CTowerDtMgr* pTowerDtMgr = new CTowerDtMgr();
	pTowerDtMgr->loadFile("Config/TowerDt.json");
	//存储到配置管理者里面
	CConfigMgr::getInstance()->setData("TowerDtMgr", pTowerDtMgr);

	//加载子弹数据
	CBulletDtMgr* pBulletDtMgr = new CBulletDtMgr();
	pBulletDtMgr->loadFile("Config/BulletDt.json");
	//存储到配置管理者里面
	CConfigMgr::getInstance()->setData("BulletDtMgr", pBulletDtMgr);

	//加载子弹爆炸数据
	CEffectDtMgr* pEffectDtMgr = new CEffectDtMgr();
	pEffectDtMgr->loadFile("Config/EffectDt.json");
	//存储到配置管理者里面
	CConfigMgr::getInstance()->setData("EffectDtMgr", pEffectDtMgr);

}
