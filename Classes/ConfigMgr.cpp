#include"ConfigMgr.h"
CConfigMgr * CConfigMgr::m_pInstance = nullptr;
CConfigMgr::CConfigMgr()
{
}

CConfigMgr::~CConfigMgr()
{
}

CConfigMgr * CConfigMgr::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CConfigMgr();
	}
	return m_pInstance;
}

CDataBaseMgr * CConfigMgr::getData(string strName)
{
	if (strName.empty()) {
		return nullptr;
	}
	map<string, CDataBaseMgr*>::iterator itor = m_MapDatas.find(strName);
	return itor->second;
}

void CConfigMgr::setData(string strName, CDataBaseMgr * pDataBaseMgr)
{
	if (strName.empty()||!pDataBaseMgr) {
		return;
	}
	m_MapDatas.insert(pair<string,CDataBaseMgr*>(strName,pDataBaseMgr));
}
