#include"ResDtMgr.h"
CResDtMgr * CResDtMgr::m_pInstance = nullptr;
CResDtMgr::CResDtMgr()
{
}

CResDtMgr::~CResDtMgr()
{
	for (map<string, SResDt*>::iterator iter = m_MapData.begin(); iter != m_MapData.end();++iter) {
		SResDt* pData = iter->second;
		CC_SAFE_DELETE(pData);
	}
	m_MapData.clear();
}

CResDtMgr * CResDtMgr::getInstance()
{
	if (!m_pInstance) {
		m_pInstance = new CResDtMgr();
		m_pInstance->loadFile("Config/ResData.json");
	}
	return m_pInstance;
}

void CResDtMgr::loadFile(const string & strPath)
{
	string strFullPath = FileUtils::getInstance()->fullPathForFilename(strPath);
	string strData = FileUtils::getInstance()->getStringFromFile(strFullPath);

	Document doc;
	doc.Parse(strData.c_str());

	string SceneResName[3] = { "Common","Menu","Game" };
	string ResType[3] = { "png","plist","audio" };
		for (int i = 0; i < 3;i++) {
			SResDt* pData = new SResDt();
			rapidjson::Value& vCurSceneRes = doc[SceneResName[i].c_str()];
			for (int j = 0; j < 3;j++) {
				rapidjson::Value& vResType = vCurSceneRes[ResType[j].c_str()];
				for (int m = 0; m < vResType.Size();m++) {
					string str = vResType[m].GetString();
					if ("png" == ResType[j]) {
						pData->m_VecPng.push_back(str);
					}
					else if ("plist" == ResType[j]) {
						pData->m_VecPlist.push_back(str);
					}
					else if ("audio" == ResType[j]) {
						pData->m_VecAudio.push_back(str);
					}
				}
			}
			m_MapData.insert(pair<string,SResDt*>(SceneResName[i],pData));
	}
}

SResDt * CResDtMgr::getData(string strKey)
{
	map<string, SResDt*>::iterator iter = m_MapData.find(strKey);
	if (iter == m_MapData.end())
	{
		return nullptr;
	}
	return iter->second;
}
