// ��Դ���ݹ����ඨ��
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

// ��Դ���ݽṹ
struct SResDt
{
    vector<string> m_VecPng;    // PNGͼƬ��Դ
    vector<string> m_VecPlist;  // plist�������Դ
    vector<string> m_VecAudio;  // ��Ƶ��Դ
};

// ��Դ���ݹ�����
class CResDtMgr
{
public:
    static CResDtMgr* getInstance(); // ��ȡ����ʵ��
    void loadFile(const string& strPath); // ������Դ�ļ�
    SResDt* getData(string strKey); // ��ȡ�ض�������Դ����

private:
    CResDtMgr(); // ���캯��
    ~CResDtMgr(); // ��������
    map<string, SResDt*> m_MapData; // �洢��Դ���ݵ�ӳ���
    static CResDtMgr* m_pInstance; // ����ʵ��
};

#endif