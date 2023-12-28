#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "DataClass.h"
#include "ConfigMgr.h"
#include "Bullet.h"
using namespace std;
USING_NS_CC;

enum {
    E_STATE_LEFT,
    E_STATE_RIGHT,
    E_STATE_DEATH
};

class CEnemy : public Node {
public:
    CEnemy();
    ~CEnemy();
    bool initWithData(SEnemyDt* pData);
    static CEnemy* createWithData(SEnemyDt* pData);

    CC_SYNTHESIZE_READONLY(int, m_nCoin, Coin);
    CC_SYNTHESIZE_READONLY(SEnemyDt*, m_pEnemyDt, Enemy);
    CC_SYNTHESIZE(int, m_nHp, Hp);

    void onCollision(CBullet* pBullet);
    void update(float delta);

private:
    void resumeAction(float delta);
    void changeAnim(int nState);
    Animation* createAnimation(const std::string& frameNamePattern, int numFrames, float delay);

private:
    Sprite* m_pHpBar;
    Sprite* m_pBoom;
    int m_nSpeed;
    Scheduler* m_pScheduler;
    map<int, Vec2> m_MapPath;
    int i;
    float dis;
    Vec2 m_nDir;
    int m_nState;
    float fDis;
    Animation* m_pAnimationL;
    Animation* m_pAnimationR;
    Animation* m_pAnimationBoom;
    Sprite* m_pImage;
};

#endif // __ENEMY_H__