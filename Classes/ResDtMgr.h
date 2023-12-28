// 资源数据管理类定义
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

// 资源数据结构
struct SResDt
{
    vector<string> m_VecPng;    // PNG图片资源
    vector<string> m_VecPlist;  // plist精灵表资源
    vector<string> m_VecAudio;  // 音频资源
};

// 资源数据管理类
class CResDtMgr
{
public:
    static CResDtMgr* getInstance(); // 获取单例实例
    void loadFile(const string& strPath); // 加载资源文件
    SResDt* getData(string strKey); // 获取特定键的资源数据

private:
    CResDtMgr(); // 构造函数
    ~CResDtMgr(); // 析构函数
    map<string, SResDt*> m_MapData; // 存储资源数据的映射表
    static CResDtMgr* m_pInstance; // 单例实例
};

#endif