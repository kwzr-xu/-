#ifndef __ConfigMgr_H__
#define __ConfigMgr_H__

#include"DataBase.h"

class CConfigMgr
{
public:
    // ��ȡʵ���ľ�̬����
    static CConfigMgr* getInstance();

    // �����ȡ���������ݵĽӿ�
    CDataBaseMgr* getData(string strName);
    void setData(string strName, CDataBaseMgr* pDataBaseMgr);

private:
    // ���캯��������������Ϊ˽�У���֧�ֵ���ģʽ
    CConfigMgr();
    ~CConfigMgr();

    // �洢��ʵ���ľ�̬��Ա����
    static CConfigMgr* m_pInstance;

    // �洢�������ݵ�ӳ��
    map<string, CDataBaseMgr*> m_MapDatas;
};

#endif // __ConfigMgr_H__