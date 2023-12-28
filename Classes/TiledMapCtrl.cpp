#include"TiledMapCtrl.h"
using namespace std;

// 构造函数
CTiledMapCtrl::CTiledMapCtrl()
{
}

// 析构函数
CTiledMapCtrl::~CTiledMapCtrl()
{
}

// 初始化地图数据
bool CTiledMapCtrl::initWithData(SLevelDt* pData)
{
    if (!Node::init()) {
        return false;
    }
    this->initMap(pData);  // 初始化地图
    this->initObjGroup();  // 初始化对象组
    return true;
}

// 创建地图控制器实例
CTiledMapCtrl* CTiledMapCtrl::createWithData(SLevelDt* pData)
{
    CTiledMapCtrl* pMap = new CTiledMapCtrl();
    if (pMap && pMap->initWithData(pData)) {
        pMap->autorelease();
        return pMap;
    }
    CC_SAFE_DELETE(pMap);
    return nullptr;
}

// 判断指定的瓦片是否是障碍物
bool CTiledMapCtrl::isObstacles(const Vec2& tile)
{
    for (int i = 0; i < m_MapObPos.size(); i++) {
        Vec2 obPos = this->getTiledByPos(m_MapObPos[i]);
        if (tile == obPos) {
            return false;
        }
    }
}

// 初始化地图
void CTiledMapCtrl::initMap(SLevelDt* pData)
{
    m_pTiledMap = TMXTiledMap::create(pData->strMapName); // 加载瓦片地图
    this->addChild(m_pTiledMap); // 将地图添加为子节点

    m_pPath = m_pTiledMap->getLayer("path"); // 获取路径层
}

// 初始化对象组
void CTiledMapCtrl::initObjGroup()
{
    m_pPathObjGroup = m_pTiledMap->getObjectGroup("pathObject1"); // 获取路径对象组
    ValueVector PathObjs = m_pPathObjGroup->getObjects(); // 获取路径对象
    for (cocos2d::Value& PathObj : PathObjs) {
        ValueMap valueMap = PathObj.asValueMap();
        Vec2 pos;
        pos.x = valueMap["x"].asFloat();
        pos.y = valueMap["y"].asFloat();
        m_MapPathPos.insert(pair<int, Vec2>(valueMap["name"].asInt(), pos)); // 存储路径点信息
    }

    // 获取并处理障碍物对象组
    m_pObstacles = m_pTiledMap->getObjectGroup("obstacles");
    ValueVector obstaclesObjs = m_pObstacles->getObjects();
    for (cocos2d::Value& obstaclesObj : obstaclesObjs) {
        ValueMap valueMap = obstaclesObj.asValueMap();
        Vec2 pos;
        pos.x = valueMap["x"].asFloat();
        pos.y = valueMap["y"].asFloat();
        m_MapObPos.insert(pair<int, Vec2>(valueMap["name"].asInt(), pos)); // 存储障碍物信息
    }
}

// 判断指定的瓦片是否为空
bool CTiledMapCtrl::isNullTile(const Vec2& tile)
{
    unsigned int GID = m_pPath->getTileGIDAt(tile); // 获取瓦片ID
    if (GID == 0) {
        return true;
    }
    return false;
}

// 根据位置获取瓦片坐标
Vec2 CTiledMapCtrl::getTiledByPos(const Vec2& pos)
{
    Size TileSize = m_pTiledMap->getTileSize();
    Size MapSize = m_pTiledMap->getMapSize();
    int TiledX = pos.x / TileSize.width;
    int TiledY = (MapSize.height * TileSize.height - pos.y) / TileSize.height;
    return Vec2(TiledX, TiledY);
}

// 根据瓦片坐标获取位置
Vec2 CTiledMapCtrl::getPosByTiled(const Vec2& tiled)
{
    Size sizeTiled = m_pTiledMap->getTileSize();
    Size sizeMap = m_pTiledMap->getMapSize();
    Vec2 pos;
    pos.x = tiled.x * sizeTiled.width + sizeTiled.width / 2;
    pos.y = (sizeMap.height - tiled.y) * sizeTiled.height - sizeTiled.height / 2;
    return pos;
}
