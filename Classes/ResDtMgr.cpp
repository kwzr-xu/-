#include"ResDtMgr.h"

// 静态实例初始化
CResDtMgr* CResDtMgr::m_pInstance = nullptr;

// 构造函数
CResDtMgr::CResDtMgr()
{
}

// 析构函数
CResDtMgr::~CResDtMgr()
{
    // 删除并清除所有资源数据
    for (map<string, SResDt*>::iterator iter = m_MapData.begin(); iter != m_MapData.end(); ++iter) {
        SResDt* pData = iter->second;
        CC_SAFE_DELETE(pData);
    }
    m_MapData.clear();
}

// 获取单例实例
CResDtMgr* CResDtMgr::getInstance()
{
    // 如果实例不存在，创建新实例并加载配置文件
    if (!m_pInstance) {
        m_pInstance = new CResDtMgr();
        m_pInstance->loadFile("Config/ResData.json");
    }
    return m_pInstance;
}

// 加载资源文件
void CResDtMgr::loadFile(const string& strPath)
{
    // 获取文件完整路径并读取文件内容
    string strFullPath = FileUtils::getInstance()->fullPathForFilename(strPath);
    string strData = FileUtils::getInstance()->getStringFromFile(strFullPath);

    // 解析JSON数据
    Document doc;
    doc.Parse(strData.c_str());

    // 资源类型名称
    string SceneResName[3] = { "Common","Menu","Game" };
    string ResType[3] = { "png","plist","audio" };
    for (int i = 0; i < 3; i++) {
        SResDt* pData = new SResDt();
        rapidjson::Value& vCurSceneRes = doc[SceneResName[i].c_str()];
        for (int j = 0; j < 3; j++) {
            rapidjson::Value& vResType = vCurSceneRes[ResType[j].c_str()];
            for (int m = 0; m < vResType.Size(); m++) {
                string str = vResType[m].GetString();
                // 根据资源类型添加到相应的向量中
                if ("png" == ResType[j]) {
                    pData->m_VecPng.push_back(str);
                }
                else if ("plist" == ResType[j]) {
                    pData->m_VecPlist.push_back(str);
                }
                else if ("audio" == ResType[j]) {
                    pData->m_VecAudio.push_back(str);
                }
            }
        }
        // 将解析出的资源数据添加到映射表中
        m_MapData.insert(pair<string, SResDt*>(SceneResName[i], pData));
    }
}

// 获取特定键的资源数据
SResDt* CResDtMgr::getData(string strKey)
{
    map<string, SResDt*>::iterator iter = m_MapData.find(strKey);
    if (iter == m_MapData.end())
    {
        return nullptr;
    }
    return iter->second;
}