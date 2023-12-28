// 塔台类定义
#ifndef __Tower_H__
#define __Tower_H__

#include "cocos2d.h"
#include"DataClass.h"
#include"ConfigMgr.h"
#include"Enemy.h"
#include"Bullet.h"
using namespace std;
USING_NS_CC;

// 塔台状态枚举
enum {
    E_STATE_NORMAL, // 正常状态
    E_STATE_FIRE    // 开火状态
};

// CTower 类继承自 Node 类，用于处理游戏中塔台的行为
class CTower :public Node
{
public:
    CTower(); // 构造函数
    ~CTower(); // 析构函数
    bool initWithData(int nTowerID); // 使用数据初始化塔台
    void upgrade(); // 升级塔台
    static CTower* createWithData(int nTowerID); // 创建塔台实例
    CC_SYNTHESIZE(int, m_nCurGrade, CurGrade); // 当前等级
    CC_SYNTHESIZE(int, m_nSaleCoin, SaleCoin); // 出售金币
    CC_SYNTHESIZE(int, m_nUpGradeCoin, UpGradeCoin); // 升级金币

private:
    void search(float delta); // 搜索敌人
    void fire(float Dt); // 塔台开火
private:
    int i; // 辅助变量
    int m_nCurTowerID; // 当前塔台ID
    int m_nEnemyIndex; // 敌人索引
    float m_fDisSq; // 敌人距离平方
    Vec2 m_nDir; // 方向
    int nCurState; // 当前状态
    Sprite* m_pImage; // 塔台精灵
    STowerDt* m_pTowerDt; // 塔台数据
};

#endif