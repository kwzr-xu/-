#include"DataClass.h"
#include"json/document.h"
#include"json/rapidjson.h"
using namespace rapidjson;

CselLevelDtMgr::CselLevelDtMgr()
{
}

CselLevelDtMgr::~CselLevelDtMgr()
{
}

void CselLevelDtMgr::parse(Document & doc)
{
	for (int i = 0; i < doc.Size();i++) {
		SselLevelDt* pData = new SselLevelDt();
		rapidjson::Value& vSelLevelDt = doc[i];
		pData->nID = vSelLevelDt["mapid"].GetInt();
		pData->strMapName = vSelLevelDt["mapName"].GetString();
		pData->strDisMapName = vSelLevelDt["disMapName"].GetString();
		rapidjson::Value& vBattertImgs = vSelLevelDt["batteryImg"];
		for (int j = 0; j < vBattertImgs.Size();j++) {
			string str = vBattertImgs[j].GetString();
			pData->VecBatteryImg.push_back(str);
		}
		m_VecData.push_back(pData);
	}
	doc.Clear();
}

CLevelDtMgr::CLevelDtMgr()
{
}

CLevelDtMgr::~CLevelDtMgr()
{
}

void CLevelDtMgr::parse(Document & doc)
{
	for (int i = 0; i < doc.Size(); i++)
	{
		SLevelDt* pData = new SLevelDt();
		rapidjson::Value& vLevelDt = doc[i];
		pData->nID = vLevelDt["id"].GetInt();
		pData->nInitGold = vLevelDt["initGold"].GetInt();
		pData->nRadishRow = vLevelDt["radishRow"].GetInt();
		pData->nRadishCol = vLevelDt["radishCol"].GetInt();
		pData->strMapName = vLevelDt["mapName"].GetString();
		rapidjson::Value& vWaves = vLevelDt["Wave"];
		for (int j = 0; j < vWaves.Size();j++) {
			rapidjson::Value& vWave = vWaves[j];
			SWaves* pWave = new SWaves();
			pWave->nEnemyCount = vWave["EnemyCount"].GetInt();
			pWave->nEnemyID = vWave["EnemyId"].GetInt();
			pWave->npathID = vWave["pathId"].GetInt();
			pWave->fCurInterval = vWave["CurInterval"].GetFloat();
			pWave->fNextInterval = vWave["NextInterval"].GetFloat();
			pData->m_VecWaves.push_back(pWave);
		}
		rapidjson::Value& vCardID = vLevelDt["cardId"];
		for (int j = 0; j < vCardID.Size();j++) {
			int nCardID = vCardID[j].GetInt();
			pData->VecCard.push_back(nCardID);
		}
		m_VecData.push_back(pData);
	}
	doc.Clear();
}

CEnemyDtMgr::CEnemyDtMgr()
{
}

CEnemyDtMgr::~CEnemyDtMgr()
{
}

void CEnemyDtMgr::parse(Document & doc)
{
	for (int i = 0; i < doc.Size();i++) {
		rapidjson::Value& vEnemyDt = doc[i];
		SEnemyDt* pData = new SEnemyDt();

		pData->nID = vEnemyDt["id"].GetInt();
		pData->nAck = vEnemyDt["ack"].GetInt();
		pData->nSpeed = vEnemyDt["speed"].GetInt();
		pData->nHp = vEnemyDt["hp"].GetInt();
		pData->nCoin = vEnemyDt["coins"].GetInt();
		pData->strImg = vEnemyDt["image"].GetString();
		pData->strAnim = vEnemyDt["anim"].GetString();

		m_VecData.push_back(pData);
	}
	doc.Clear();
}


CObstaclesDtMgr::CObstaclesDtMgr()
{
}

CObstaclesDtMgr::~CObstaclesDtMgr()
{
}

void CObstaclesDtMgr::parse(Document & doc)
{
	for (int i = 0; i < doc.Size();i++) {
		rapidjson::Value& vObstaclesDt = doc[i];
		SObstaclesDt* pData = new SObstaclesDt();
		pData->nID = vObstaclesDt["id"].GetInt();
		pData->nCoins = vObstaclesDt["Coins"].GetInt();
		pData->nHp = vObstaclesDt["hp"].GetInt();
		pData->strImg = vObstaclesDt["img"].GetString();
		m_VecData.push_back(pData);
	}
	doc.Clear();
}



CCardDtMgr::CCardDtMgr()
{
}

CCardDtMgr::~CCardDtMgr()
{
}

void CCardDtMgr::parse(Document & doc)
{
	for (int i = 0; i < doc.Size(); i++) {
		rapidjson::Value& vCardDt = doc[i];
		SCardDt* pData = new SCardDt();
		pData->nID = vCardDt["id"].GetInt();
		pData->nCoins = vCardDt["Coins"].GetInt();
		pData->nTowerID = vCardDt["towerID"].GetInt();
		pData->strImg = vCardDt["img"].GetString();
		pData->strDisImg = vCardDt["disImg"].GetString();
		m_VecData.push_back(pData);
	}
	doc.Clear();

}


CTowerDtMgr::CTowerDtMgr()
{
}

CTowerDtMgr::~CTowerDtMgr()
{
}

void CTowerDtMgr::parse(Document & doc)
{
	for (int i = 0; i < doc.Size();i++) 
	{
		rapidjson::Value& vTowerDt = doc[i];
		STowerDt* pData = new STowerDt();

		pData->nID = vTowerDt["id"].GetInt();

		rapidjson::Value& vLevels = vTowerDt["level"];
		for (int j = 0; j < vLevels.Size();j++) {
			rapidjson::Value& vLevel = vLevels[j];
			SLevels* pLevel = new SLevels();
			pLevel->nBulletID = vLevel["BulletId"].GetInt();
			pLevel->nAck = vLevel["ack"].GetInt();
			pLevel->fAckInterval = vLevel["ackInterval"].GetFloat();
			pLevel->nWorth = vLevel["worth"].GetInt();
			pLevel->nUpgradeCoin = vLevel["upgradeCoin"].GetInt();
			pLevel->nScope = vLevel["scope"].GetInt();
			rapidjson::Value& vImgs = vLevel["imgs"];
			for (int m = 0; m < vImgs.Size();m++) {
				string str = vImgs[m].GetString();
				pLevel->VecImg.push_back(str);
			}
			pData->m_VecLevel.push_back(pLevel);
		}
		m_VecData.push_back(pData);
	}
	doc.Clear();
}


CBulletDtMgr::CBulletDtMgr()
{
}

CBulletDtMgr::~CBulletDtMgr()
{
}

void CBulletDtMgr::parse(Document & doc)
{
	for (int i = 0; i < doc.Size();i++) {
		rapidjson::Value& vBulletDt = doc[i];
		SBulletDt* pData = new SBulletDt();
		pData->nID = vBulletDt["id"].GetInt();
		pData->nSpeed = vBulletDt["speed"].GetInt();
		rapidjson::Value& vImgs = vBulletDt["img"];
		for (int j = 0; j < vImgs.Size();j++) {
			string str = vImgs[j].GetString();
			pData->VecImgs.push_back(str);
		}
		m_VecData.push_back(pData);
	}
	doc.Clear();
}

CEffectDtMgr::CEffectDtMgr()
{
}

CEffectDtMgr::~CEffectDtMgr()
{
}

void CEffectDtMgr::parse(Document & doc)
{
	for (int i = 0; i < doc.Size();i++) {
		rapidjson::Value& vEffectDt = doc[i];
		SEffectDt* pData = new SEffectDt();
		pData->nID = vEffectDt["id"].GetInt();
		pData->objectID = vEffectDt["objectid"].GetInt();
		rapidjson::Value& vImgs = vEffectDt["boomImg"];
		for (int j = 0; j < vImgs.Size();j++) {
			string str = vImgs[j].GetString();
			pData->VecImgs.push_back(str);
		}
		m_VecData.push_back(pData);
	}
	doc.Clear();
}

SEffectDt * CEffectDtMgr::getDataByObjectID(int nObjectID)
{
	for (SDataBase* pSData:m_VecData) {
		SEffectDt* pData = static_cast<SEffectDt*>(pSData);
		if (pData->objectID == nObjectID) {
			return pData;
		}
	}
	return nullptr;
}
