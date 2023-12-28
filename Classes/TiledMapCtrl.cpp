#include"TiledMapCtrl.h"
using namespace std;

// ���캯��
CTiledMapCtrl::CTiledMapCtrl()
{
}

// ��������
CTiledMapCtrl::~CTiledMapCtrl()
{
}

// ��ʼ����ͼ����
bool CTiledMapCtrl::initWithData(SLevelDt* pData)
{
    if (!Node::init()) {
        return false;
    }
    this->initMap(pData);  // ��ʼ����ͼ
    this->initObjGroup();  // ��ʼ��������
    return true;
}

// ������ͼ������ʵ��
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

// �ж�ָ������Ƭ�Ƿ����ϰ���
bool CTiledMapCtrl::isObstacles(const Vec2& tile)
{
    for (int i = 0; i < m_MapObPos.size(); i++) {
        Vec2 obPos = this->getTiledByPos(m_MapObPos[i]);
        if (tile == obPos) {
            return false;
        }
    }
}

// ��ʼ����ͼ
void CTiledMapCtrl::initMap(SLevelDt* pData)
{
    m_pTiledMap = TMXTiledMap::create(pData->strMapName); // ������Ƭ��ͼ
    this->addChild(m_pTiledMap); // ����ͼ���Ϊ�ӽڵ�

    m_pPath = m_pTiledMap->getLayer("path"); // ��ȡ·����
}

// ��ʼ��������
void CTiledMapCtrl::initObjGroup()
{
    m_pPathObjGroup = m_pTiledMap->getObjectGroup("pathObject1"); // ��ȡ·��������
    ValueVector PathObjs = m_pPathObjGroup->getObjects(); // ��ȡ·������
    for (cocos2d::Value& PathObj : PathObjs) {
        ValueMap valueMap = PathObj.asValueMap();
        Vec2 pos;
        pos.x = valueMap["x"].asFloat();
        pos.y = valueMap["y"].asFloat();
        m_MapPathPos.insert(pair<int, Vec2>(valueMap["name"].asInt(), pos)); // �洢·������Ϣ
    }

    // ��ȡ�������ϰ��������
    m_pObstacles = m_pTiledMap->getObjectGroup("obstacles");
    ValueVector obstaclesObjs = m_pObstacles->getObjects();
    for (cocos2d::Value& obstaclesObj : obstaclesObjs) {
        ValueMap valueMap = obstaclesObj.asValueMap();
        Vec2 pos;
        pos.x = valueMap["x"].asFloat();
        pos.y = valueMap["y"].asFloat();
        m_MapObPos.insert(pair<int, Vec2>(valueMap["name"].asInt(), pos)); // �洢�ϰ�����Ϣ
    }
}

// �ж�ָ������Ƭ�Ƿ�Ϊ��
bool CTiledMapCtrl::isNullTile(const Vec2& tile)
{
    unsigned int GID = m_pPath->getTileGIDAt(tile); // ��ȡ��ƬID
    if (GID == 0) {
        return true;
    }
    return false;
}

// ����λ�û�ȡ��Ƭ����
Vec2 CTiledMapCtrl::getTiledByPos(const Vec2& pos)
{
    Size TileSize = m_pTiledMap->getTileSize();
    Size MapSize = m_pTiledMap->getMapSize();
    int TiledX = pos.x / TileSize.width;
    int TiledY = (MapSize.height * TileSize.height - pos.y) / TileSize.height;
    return Vec2(TiledX, TiledY);
}

// ������Ƭ�����ȡλ��
Vec2 CTiledMapCtrl::getPosByTiled(const Vec2& tiled)
{
    Size sizeTiled = m_pTiledMap->getTileSize();
    Size sizeMap = m_pTiledMap->getMapSize();
    Vec2 pos;
    pos.x = tiled.x * sizeTiled.width + sizeTiled.width / 2;
    pos.y = (sizeMap.height - tiled.y) * sizeTiled.height - sizeTiled.height / 2;
    return pos;
}
