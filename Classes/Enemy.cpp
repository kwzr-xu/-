#include "Enemy.h"
#include "GameScene.h"
#include "DynamicDt.h"

CEnemy::CEnemy()
    : m_nState(E_STATE_LEFT), fDis(0), i(0), dis(0), m_nSpeed(0) {
}

CEnemy::~CEnemy() {
}

bool CEnemy::initWithData(SEnemyDt* pData) {
    if (!Node::init()) {
        return false;
    }

    // 保存怪物数据到成员变量
    m_pEnemyDt = pData;
    m_nHp = pData->nHp;
    m_nSpeed = pData->nSpeed;

    // 创建怪物的 Sprite
    m_pImage = Sprite::createWithSpriteFrameName(pData->strImg);
    this->setPosition(CGameScene::getInstance()->getTiledMapCtrl()->m_MapPathPos[0]);
    this->addChild(m_pImage);

    // 初始化血条
    m_pHpBar = Sprite::create("xuetiao.png");
    m_pHpBar->setAnchorPoint(Vec2(0.0f, 0.5f));
    m_pHpBar->setPosition(Vec2(-m_pImage->getContentSize().width / 2, m_pImage->getContentSize().height - 5));
    this->addChild(m_pHpBar);

    // 创建动画
    m_pAnimationL = createAnimation("ui_L_Monsters_%02d_%02d.png", 2, 0.2);
    m_pAnimationR = createAnimation("ui_R_Monsters_%02d_%02d.png", 2, 0.2);
    m_pAnimationBoom = createAnimation("Death%d.png", 5, 0.05);

    this->scheduleUpdate();
    return true;
}

CEnemy* CEnemy::createWithData(SEnemyDt* pData) {
    CEnemy* pEnemy = new CEnemy();
    if (pEnemy && pEnemy->initWithData(pData)) {
        pEnemy->autorelease();
        return pEnemy;
    }
    CC_SAFE_DELETE(pEnemy);
    return nullptr;
}

void CEnemy::update(float delta) {
    //获取当前游戏场景的地图及路径坐标
    m_MapPath = CGameScene::getInstance()->getTiledMapCtrl()->m_MapPathPos;

    if (i < m_MapPath.size()) {
        //获取当前路径点和下一个路径点的瓦片坐标
        Vec2 tile = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(m_MapPath[i]);
        Vec2 tileNex = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(m_MapPath[i + 1]);

        //计算怪物在X和Y上的移动方向（向量表示）
        if (tileNex.x - tile.x == 0) {
            m_nDir = Vec2((tileNex.x - tile.x), (tile.y - tileNex.y) / abs(tileNex.y - tile.y));
        }
        if (tileNex.y - tile.y == 0) {
            m_nDir = Vec2((tileNex.x - tile.x) / abs(tileNex.x - tile.x), (tileNex.y - tile.y));
        }

        //切换移动方向的左右动画
        if (m_nDir == Vec2(1, 0)) {
            this->changeAnim(E_STATE_RIGHT);
        }
        else if (m_nDir == Vec2(-1, 0)) {
            this->changeAnim(E_STATE_LEFT);
        }

        //计算怪物在当前帧应该移动的距离
        float dis = abs(m_MapPath[i + 1].x - m_MapPath[i].x) + abs(m_MapPath[i + 1].y - m_MapPath[i].y);
        Vec2 pos = this->getPosition();

        //根据移动方向和速度更新怪物的位置
        pos.x += m_nSpeed * m_nDir.x * delta;
        pos.y += m_nSpeed * m_nDir.y * delta;
        fDis += abs(m_nSpeed * m_nDir.x * delta) + abs(m_nSpeed * m_nDir.y * delta);
        this->setPosition(pos);

        //如果怪物移动距离超过了当前路段的长度，就切换到下一个路径段
        if (fDis > dis) {
            fDis = 0;
            dis = 0;
            m_nDir = Vec2(0, 0);
            i++;
            return;
        }
    }
}

void CEnemy::onCollision(CBullet* pBullet) {
    //如果子弹的ID在指定范围内（减速防御塔的子弹）
    if (pBullet->m_nBulletID >= 5010 && pBullet->m_nBulletID <= 5012) {
        //60%的概率使敌人被冻住
        int Num = random() % 10;
        if (Num < 6) {
            m_nSpeed = 0;
        }
        this->scheduleOnce(CC_CALLBACK_1(CEnemy::resumeAction, this), 2, "resumeAction"); //两秒后恢复
    }

    m_nHp -= pBullet->getDamage(); //血量减少

    // 更新血条
    float hpPercentage = static_cast<float>(m_nHp) / static_cast<float>(m_pEnemyDt->nHp);
    m_pHpBar->setScaleX(hpPercentage); // 缩放血条

    //血量减为0
    if (m_nHp <= 0) {
        int nCoin = CDynamicDt::getInstance()->getMapGold(); //掉落coin
        nCoin += m_pEnemyDt->nCoin;
        CDynamicDt::getInstance()->setMapGold(nCoin);
        this->removeFromParent(); //移除该怪物的显示

        // 更新金币显示
        CGameScene::getInstance()->m_pCoinLabel->setString(StringUtils::format("%d", CDynamicDt::getInstance()->getMapGold()));
    }
    pBullet->removeFromParent();
}

void CEnemy::resumeAction(float delta) {
    m_nSpeed = m_pEnemyDt->nSpeed;
}

void CEnemy::changeAnim(int nState) {
    //判定是否已经change
    if (m_nState == nState) {
        return;
    }

    m_nState = nState; //更新目标状态
    m_pImage->stopAllActions(); //停止动作

    //根据状态选择动画
    Action* pAction = nullptr;
    if (nState == E_STATE_RIGHT) {
        pAction = Animate::create(m_pAnimationR);
    }
    else if (nState == E_STATE_LEFT) {
        pAction = Animate::create(m_pAnimationL);
    }
    else if (nState == E_STATE_DEATH) {
        Animate* pAnimateDeath = Animate::create(m_pAnimationBoom);
        CallFunc* pCallFunc = CallFunc::create([&]() { this->removeFromParent(); });
        pAction = Sequence::createWithTwoActions(pAnimateDeath, pCallFunc);
    }

    if (pAction) {
        m_pImage->runAction(pAction);
    }
}

Animation* CEnemy::createAnimation(const std::string& frameNamePattern, int numFrames, float delay) {
    Animation* animation = Animation::create();
    SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
    for (int i = 0; i < numFrames; i++) {
        SpriteFrame* pSpriteFrame = pCache->getSpriteFrameByName(StringUtils::format(frameNamePattern.c_str(), m_pEnemyDt->nID - 2000, i + 1));
        animation->addSpriteFrame(pSpriteFrame);
    }
    animation->setDelayPerUnit(delay);
    animation->retain();
    return animation;
}