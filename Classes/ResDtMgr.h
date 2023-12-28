#ifndef __ResDtMgr_H__
#define __ResDtMgr_H__

#include<string>
#include<vector>
#include<map>
#include"cocos2d.h"
#include"json/document.h"
#include"json/rapidjson.h"
using namespace std;
using namespace rapidjson;
USING_NS_CC;
struct SResDt
{
	vector<string> m_VecPng;
	vector<string> m_VecPlist;
	vector<string> m_VecAudio;
};

class CResDtMgr
{
public:
	static CResDtMgr* getInstance();
	void loadFile(const string& strPath);
	SResDt* getData(string strKey);
private:
	CResDtMgr();
	~CResDtMgr();
	map<string, SResDt*> m_MapData;
	static CResDtMgr* m_pInstance;
};

#endif

