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

    // ����������ݵ���Ա����
    m_pEnemyDt = pData;
    m_nHp = pData->nHp;
    m_nSpeed = pData->nSpeed;

    // ��������� Sprite
    m_pImage = Sprite::createWithSpriteFrameName(pData->strImg);
    this->setPosition(CGameScene::getInstance()->getTiledMapCtrl()->m_MapPathPos[0]);
    this->addChild(m_pImage);

    // ��ʼ��Ѫ��
    m_pHpBar = Sprite::create("xuetiao.png");
    m_pHpBar->setAnchorPoint(Vec2(0.0f, 0.5f));
    m_pHpBar->setPosition(Vec2(-m_pImage->getContentSize().width / 2, m_pImage->getContentSize().height - 5));
    this->addChild(m_pHpBar);

    // ��������
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
    //��ȡ��ǰ��Ϸ�����ĵ�ͼ��·������
    m_MapPath = CGameScene::getInstance()->getTiledMapCtrl()->m_MapPathPos;

    if (i < m_MapPath.size()) {
        //��ȡ��ǰ·�������һ��·�������Ƭ����
        Vec2 tile = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(m_MapPath[i]);
        Vec2 tileNex = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(m_MapPath[i + 1]);

        //���������X��Y�ϵ��ƶ�����������ʾ��
        if (tileNex.x - tile.x == 0) {
            m_nDir = Vec2((tileNex.x - tile.x), (tile.y - tileNex.y) / abs(tileNex.y - tile.y));
        }
        if (tileNex.y - tile.y == 0) {
            m_nDir = Vec2((tileNex.x - tile.x) / abs(tileNex.x - tile.x), (tileNex.y - tile.y));
        }

        //�л��ƶ���������Ҷ���
        if (m_nDir == Vec2(1, 0)) {
            this->changeAnim(E_STATE_RIGHT);
        }
        else if (m_nDir == Vec2(-1, 0)) {
            this->changeAnim(E_STATE_LEFT);
        }

        //��������ڵ�ǰ֡Ӧ���ƶ��ľ���
        float dis = abs(m_MapPath[i + 1].x - m_MapPath[i].x) + abs(m_MapPath[i + 1].y - m_MapPath[i].y);
        Vec2 pos = this->getPosition();

        //�����ƶ�������ٶȸ��¹����λ��
        pos.x += m_nSpeed * m_nDir.x * delta;
        pos.y += m_nSpeed * m_nDir.y * delta;
        fDis += abs(m_nSpeed * m_nDir.x * delta) + abs(m_nSpeed * m_nDir.y * delta);
        this->setPosition(pos);

        //��������ƶ����볬���˵�ǰ·�εĳ��ȣ����л�����һ��·����
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
    //����ӵ���ID��ָ����Χ�ڣ����ٷ��������ӵ���
    if (pBullet->m_nBulletID >= 5010 && pBullet->m_nBulletID <= 5012) {
        //60%�ĸ���ʹ���˱���ס
        int Num = random() % 10;
        if (Num < 6) {
            m_nSpeed = 0;
        }
        this->scheduleOnce(CC_CALLBACK_1(CEnemy::resumeAction, this), 2, "resumeAction"); //�����ָ�
    }

    m_nHp -= pBullet->getDamage(); //Ѫ������

    // ����Ѫ��
    float hpPercentage = static_cast<float>(m_nHp) / static_cast<float>(m_pEnemyDt->nHp);
    m_pHpBar->setScaleX(hpPercentage); // ����Ѫ��

    //Ѫ����Ϊ0
    if (m_nHp <= 0) {
        int nCoin = CDynamicDt::getInstance()->getMapGold(); //����coin
        nCoin += m_pEnemyDt->nCoin;
        CDynamicDt::getInstance()->setMapGold(nCoin);
        this->removeFromParent(); //�Ƴ��ù������ʾ

        // ���½����ʾ
        CGameScene::getInstance()->m_pCoinLabel->setString(StringUtils::format("%d", CDynamicDt::getInstance()->getMapGold()));
    }
    pBullet->removeFromParent();
}

void CEnemy::resumeAction(float delta) {
    m_nSpeed = m_pEnemyDt->nSpeed;
}

void CEnemy::changeAnim(int nState) {
    //�ж��Ƿ��Ѿ�change
    if (m_nState == nState) {
        return;
    }

    m_nState = nState; //����Ŀ��״̬
    m_pImage->stopAllActions(); //ֹͣ����

    //����״̬ѡ�񶯻�
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