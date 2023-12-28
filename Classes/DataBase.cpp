#include "DataBase.h"

// 构造函数
CDataBaseMgr::CDataBaseMgr() {
}

// 析构函数
CDataBaseMgr::~CDataBaseMgr() {
}

// 从给定路径加载文件
void CDataBaseMgr::loadFile(const string& strPath) {
    // 获取全路径
    string strFullPath = FileUtils::getInstance()->fullPathForFilename(strPath);
    // 获取文件信息
    string strData = FileUtils::getInstance()->getStringFromFile(strFullPath);

    Document doc;
    doc.Parse(strData.c_str());

    this->parse(doc);

    doc.Clear();
}

// 通过 ID 获取数据
SDataBase* CDataBaseMgr::getDataByID(int nID) {
    for (SDataBase* pData : m_VecData) {
        if (pData->nID == nID) {
            return pData;
        }
    }
    return nullptr;
}

// 通过索引获取数据
SDataBase* CDataBaseMgr::getDataByIndex(int nIndex) {
    if (nIndex < 0 || nIndex >= m_VecData.size()) {
        return nullptr;
    }
    return m_VecData[nIndex];
}

// 获取所有数据
vector<SDataBase*> CDataBaseMgr::getAllData() {
    return m_VecData;
}

// 获取数据的数量
int CDataBaseMgr::getSize() {
    return m_VecData.size();
}
