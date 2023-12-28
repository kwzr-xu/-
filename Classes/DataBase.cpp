#include "DataBase.h"

// ���캯��
CDataBaseMgr::CDataBaseMgr() {
}

// ��������
CDataBaseMgr::~CDataBaseMgr() {
}

// �Ӹ���·�������ļ�
void CDataBaseMgr::loadFile(const string& strPath) {
    // ��ȡȫ·��
    string strFullPath = FileUtils::getInstance()->fullPathForFilename(strPath);
    // ��ȡ�ļ���Ϣ
    string strData = FileUtils::getInstance()->getStringFromFile(strFullPath);

    Document doc;
    doc.Parse(strData.c_str());

    this->parse(doc);

    doc.Clear();
}

// ͨ�� ID ��ȡ����
SDataBase* CDataBaseMgr::getDataByID(int nID) {
    for (SDataBase* pData : m_VecData) {
        if (pData->nID == nID) {
            return pData;
        }
    }
    return nullptr;
}

// ͨ��������ȡ����
SDataBase* CDataBaseMgr::getDataByIndex(int nIndex) {
    if (nIndex < 0 || nIndex >= m_VecData.size()) {
        return nullptr;
    }
    return m_VecData[nIndex];
}

// ��ȡ��������
vector<SDataBase*> CDataBaseMgr::getAllData() {
    return m_VecData;
}

// ��ȡ���ݵ�����
int CDataBaseMgr::getSize() {
    return m_VecData.size();
}
