#include "DynamicDt.h"

// 初始化静态实例指针为 nullptr
CDynamicDt* CDynamicDt::pInstance = nullptr;

// 构造函数
CDynamicDt::CDynamicDt()
    : m_nLevelID(0), m_nMapGold(0), m_nWaveIndex(1), m_nRadishHp(0) {
}

// 析构函数
CDynamicDt::~CDynamicDt() {
}

// 获取单例实例
CDynamicDt* CDynamicDt::getInstance() {
    if (!pInstance) {
        pInstance = new CDynamicDt(); // 若实例不存在，创建新实例
    }
    return pInstance; // 返回实例
}