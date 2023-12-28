#include"ConfigMgr.h"

// ��̬��Ա���������ڴ洢���Ψһʵ��
CConfigMgr* CConfigMgr::m_pInstance = nullptr;

// ���캯��
CConfigMgr::CConfigMgr()
{
}

// ��������
CConfigMgr::~CConfigMgr()
{
}

// ��ȡ���Ψһʵ���ľ�̬����
CConfigMgr* CConfigMgr::getInstance()
{
    if (!m_pInstance) // ���ʵ�������ڣ�����һ����ʵ��
    {
        m_pInstance = new CConfigMgr();
    }
    return m_pInstance; // ����ʵ��
}

// �������ƻ�ȡ����
CDataBaseMgr* CConfigMgr::getData(string strName)
{
    if (strName.empty()) { // �������Ϊ�գ����ؿ�ָ��
        return nullptr;
    }
    map<string, CDataBaseMgr*>::iterator itor = m_MapDatas.find(strName);
    return itor->second; // �����ҵ�������
}

// ��������
void CConfigMgr::setData(string strName, CDataBaseMgr* pDataBaseMgr)
{
    if (strName.empty() || !pDataBaseMgr) { // �������Ϊ�ջ�����Ϊ�գ��򲻽��в���
        return;
    }
    m_MapDatas.insert(pair<string, CDataBaseMgr*>(strName, pDataBaseMgr)); // ��������
}