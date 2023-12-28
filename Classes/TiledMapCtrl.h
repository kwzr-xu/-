// ��Ƭ��ͼ�����ඨ��
#ifndef __TiledMapCtrl_H__
#define __TiledMapCtrl_H__

#include "cocos2d.h"
#include"DataClass.h"
using namespace std;
USING_NS_CC;

// CTiledMapCtrl ��̳��� Node �࣬���ڴ�����Ƭ��ͼ�Ŀ��ƺͽ���
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
    bool isObstacles(const Vec2& tile); // �ж��Ƿ�Ϊ�ϰ���
    map<int, Vec2> m_MapObPos; // �洢�ϰ���λ��
    map<int, Vec2> m_MapPathPos; // �洢·����Ϣ
    bool isNullTile(const Vec2& tile); // �ж���Ƭ�Ƿ�Ϊ��
private:
    void initMap(SLevelDt* pData); // ��ʼ����ͼ
    void initObjGroup(); // ��ʼ��������
private:
    TMXObjectGroup* m_pPathObjGroup; // ·��������
    TMXObjectGroup* m_pObstacles; // �ϰ��������
    TMXTiledMap* m_pTiledMap; // ��Ƭ��ͼ
    TMXLayer* m_pPath; // ·����
};
#endif