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

// SDataBase 结构体：用于表示基本数据库条目。
struct SDataBase
{
public:
    SDataBase() : nID(0) {}  // 构造函数，初始化 ID 为 0。
    int nID;  // 数据的唯一标识符。
};

// CDataBaseMgr 类：用于管理数据库数据。
class CDataBaseMgr
{
public:
    CDataBaseMgr();  // 构造函数。
    ~CDataBaseMgr(); // 析构函数。

    // 从给定路径加载文件。
    virtual void loadFile(const string& strPath);

    // 通过 ID 获取数据。
    SDataBase* getDataByID(int nID);

    // 纯虚函数，用于解析文档，必须在派生类中实现。
    virtual void parse(Document& doc) = 0;

    // 通过索引获取数据。
    SDataBase* getDataByIndex(int nIndex);

    // 获取所有数据。
    vector<SDataBase*> getAllData();

    // 获取数据的数量。
    int getSize();

protected:
    vector<SDataBase*> m_VecData; // 存储数据的容器
};

#endif
