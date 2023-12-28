#ifndef __ConfigMgr_H__
#define __ConfigMgr_H__

#include"DataBase.h"

class CConfigMgr
{
public:
    // 获取实例的静态方法
    static CConfigMgr* getInstance();

    // 定义获取和设置数据的接口
    CDataBaseMgr* getData(string strName);
    void setData(string strName, CDataBaseMgr* pDataBaseMgr);

private:
    // 构造函数和析构函数设为私有，以支持单例模式
    CConfigMgr();
    ~CConfigMgr();

    // 存储类实例的静态成员变量
    static CConfigMgr* m_pInstance;

    // 存储配置数据的映射
    map<string, CDataBaseMgr*> m_MapDatas;
};

#endif // __ConfigMgr_H__