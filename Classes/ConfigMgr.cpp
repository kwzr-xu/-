#include"ConfigMgr.h"

// 静态成员变量，用于存储类的唯一实例
CConfigMgr* CConfigMgr::m_pInstance = nullptr;

// 构造函数
CConfigMgr::CConfigMgr()
{
}

// 析构函数
CConfigMgr::~CConfigMgr()
{
}

// 获取类的唯一实例的静态方法
CConfigMgr* CConfigMgr::getInstance()
{
    if (!m_pInstance) // 如果实例不存在，创建一个新实例
    {
        m_pInstance = new CConfigMgr();
    }
    return m_pInstance; // 返回实例
}

// 根据名称获取数据
CDataBaseMgr* CConfigMgr::getData(string strName)
{
    if (strName.empty()) { // 如果名称为空，返回空指针
        return nullptr;
    }
    map<string, CDataBaseMgr*>::iterator itor = m_MapDatas.find(strName);
    return itor->second; // 返回找到的数据
}

// 设置数据
void CConfigMgr::setData(string strName, CDataBaseMgr* pDataBaseMgr)
{
    if (strName.empty() || !pDataBaseMgr) { // 如果名称为空或数据为空，则不进行操作
        return;
    }
    m_MapDatas.insert(pair<string, CDataBaseMgr*>(strName, pDataBaseMgr)); // 插入数据
}