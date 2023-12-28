#ifndef __DataBase_H__
#define __DataBase_H__

#include<string>
#include<vector>
#include"cocos2d.h"
#include"json/document.h"
#include"json/rapidjson.h"

using namespace std;
using namespace rapidjson;
USING_NS_CC;

// SDataBase �ṹ�壺���ڱ�ʾ�������ݿ���Ŀ��
struct SDataBase
{
public:
    SDataBase() : nID(0) {}  // ���캯������ʼ�� ID Ϊ 0��
    int nID;  // ���ݵ�Ψһ��ʶ����
};

// CDataBaseMgr �ࣺ���ڹ������ݿ����ݡ�
class CDataBaseMgr
{
public:
    CDataBaseMgr();  // ���캯����
    ~CDataBaseMgr(); // ����������

    // �Ӹ���·�������ļ���
    virtual void loadFile(const string& strPath);

    // ͨ�� ID ��ȡ���ݡ�
    SDataBase* getDataByID(int nID);

    // ���麯�������ڽ����ĵ�����������������ʵ�֡�
    virtual void parse(Document& doc) = 0;

    // ͨ��������ȡ���ݡ�
    SDataBase* getDataByIndex(int nIndex);

    // ��ȡ�������ݡ�
    vector<SDataBase*> getAllData();

    // ��ȡ���ݵ�������
    int getSize();

protected:
    vector<SDataBase*> m_VecData; // �洢���ݵ�����
};

#endif
