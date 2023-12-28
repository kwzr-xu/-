// 瓦片地图控制类定义
#ifndef __TiledMapCtrl_H__
#define __TiledMapCtrl_H__

#include "cocos2d.h"
#include"DataClass.h"
using namespace std;
USING_NS_CC;

// CTiledMapCtrl 类继承自 Node 类，用于处理瓦片地图的控制和交互
class CTiledMapCtrl :public Node
{
public:
    CTiledMapCtrl();
    ~CTiledMapCtrl();
    bool initWithData(SLevelDt* pData);
    Vec2 getTiledByPos(const Vec2& pos);
    Vec2 getPosByTiled(const Vec2& tiled);
    static CTiledMapCtrl* createWithData(SLevelDt* pData);
public:
    bool isObstacles(const Vec2& tile); // 判断是否为障碍物
    map<int, Vec2> m_MapObPos; // 存储障碍物位置
    map<int, Vec2> m_MapPathPos; // 存储路径信息
    bool isNullTile(const Vec2& tile); // 判断瓦片是否为空
private:
    void initMap(SLevelDt* pData); // 初始化地图
    void initObjGroup(); // 初始化对象组
private:
    TMXObjectGroup* m_pPathObjGroup; // 路径对象组
    TMXObjectGroup* m_pObstacles; // 障碍物对象组
    TMXTiledMap* m_pTiledMap; // 瓦片地图
    TMXLayer* m_pPath; // 路径层
};
#endif