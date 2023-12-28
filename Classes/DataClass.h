#ifndef __DataClass_H__
#define __DataClass_H__

#include"DataBase.h"
using namespace std;


struct SselLevelDt :public SDataBase
{
	string strMapName;
	string strDisMapName;
	vector<string> VecBatteryImg;
};


class CselLevelDtMgr:public CDataBaseMgr
{
public:
	CselLevelDtMgr();
	~CselLevelDtMgr();
	virtual void parse(Document& doc);
private:

};

struct SWaves
{
	int nEnemyID;
	int	npathID;
	int nEnemyCount;
	float fCurInterval;
	float fNextInterval;
};
struct SLevelDt:public SDataBase
{
	int nInitGold;
	int nRadishRow;
	int nRadishCol;
	string strMapName;
	vector<SWaves*> m_VecWaves;
	vector<int> VecCard;
};
class CLevelDtMgr:public CDataBaseMgr
{
public:
	CLevelDtMgr();
	~CLevelDtMgr();
	virtual void parse(Document& doc);
private:

};
struct SEnemyDt:public SDataBase
{
	int nAck;
	int nSpeed;
	int nHp;
	int nCoin;
	string strImg;
	string strAnim;
};
class CEnemyDtMgr:public CDataBaseMgr
{
public:
	CEnemyDtMgr();
	~CEnemyDtMgr();
	virtual void parse(Document& doc);
private:

};

struct SObstaclesDt:public SDataBase
{

	int nCoins;
	int nHp;
	string strImg;
};

class CObstaclesDtMgr:public CDataBaseMgr
{
public:
	CObstaclesDtMgr();
	~CObstaclesDtMgr();
	virtual void parse(Document& doc);
private:

};


struct SCardDt:public SDataBase
{
	int nTowerID;
	int nCoins;
	string strImg;
	string strDisImg;
};
class CCardDtMgr:public CDataBaseMgr
{
public:
	CCardDtMgr();
	~CCardDtMgr();
	virtual void parse(Document& doc);
private:

};

struct SLevels 
{
	int nBulletID;
	int nAck;
	float fAckInterval;
	int nWorth;
	int nUpgradeCoin;
	int nScope;
	vector<string> VecImg;
};
struct STowerDt:public SDataBase
{
	vector<SLevels*> m_VecLevel;
};
class CTowerDtMgr:public CDataBaseMgr
{
public:
	CTowerDtMgr();
	~CTowerDtMgr();
	virtual void parse(Document& doc);
private:

};

struct SBulletDt:public SDataBase
{
	int nSpeed;
	vector<string> VecImgs;
};

class CBulletDtMgr:public CDataBaseMgr
{
public:
	CBulletDtMgr();
	~CBulletDtMgr();
	virtual void parse(Document& doc);
private:

};


struct SEffectDt :public SDataBase
{
	int objectID;
	vector<string> VecImgs;
};
class CEffectDtMgr:public CDataBaseMgr
{
public:
	CEffectDtMgr();
	~CEffectDtMgr();
	virtual void parse(Document& doc);
	SEffectDt* getDataByObjectID(int nObjectID);
private:

};
#endif
