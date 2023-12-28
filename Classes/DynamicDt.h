#ifndef __DynamicDt_H__
#define __DynamicDt_H__

#include "cocos2d.h"

// CDynamicDt 类：用于管理动态游戏数据
class CDynamicDt {
public:
    // 获取单例实例
    static CDynamicDt* getInstance();

    // 使用宏 CC_SYNTHESIZE 实现 getter 和 setter 方法
    CC_SYNTHESIZE(int, m_nLevelID, LevelID);      // 当前关卡ID
    CC_SYNTHESIZE(int, m_nMapGold, MapGold);      // 地图上的金币数
    CC_SYNTHESIZE(int, m_nWaveIndex, WaveIndex);  // 波次索引
    CC_SYNTHESIZE(int, m_nRadishHp, RadishHp);    // 萝卜的生命值

private:
    CDynamicDt();                                // 构造函数
    ~CDynamicDt();                               // 析构函数
    static CDynamicDt* pInstance;              // 静态实例
};

#endif