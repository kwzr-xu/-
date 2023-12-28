#include"Tower.h"
#include"GameScene.h"

// 构造函数，初始化各种参数
CTower::CTower()
    :m_nCurGrade(0) // 当前等级
    , nCurState(E_STATE_NORMAL) // 当前状态（正常或开火）
    , m_nSaleCoin(0) // 出售金币
    , m_nDir(0, -1) // 方向
    , m_nEnemyIndex(0) // 敌人索引
    , m_nCurTowerID(0) // 当前塔台ID
    , i(0) // 辅助变量
{
}

// 析构函数
CTower::~CTower()
{
}

// 使用数据初始化塔台
bool CTower::initWithData(int nTowerID)
{
    if (!Node::init()) {
        return false;
    }
    m_nCurTowerID = nTowerID; // 设置塔台ID
    m_pTowerDt = static_cast<STowerDt*>(CConfigMgr::getInstance()->getData("TowerDtMgr")->getDataByID(nTowerID)); // 获取塔台数据
    m_pImage = Sprite::createWithSpriteFrameName(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]); // 创建塔台精灵
    m_nSaleCoin = m_pTowerDt->m_VecLevel[m_nCurGrade]->nWorth; // 设置出售金币
    m_nUpGradeCoin = m_pTowerDt->m_VecLevel[m_nCurGrade]->nUpgradeCoin; // 设置升级金币
    this->addChild(m_pImage); // 添加塔台精灵为子节点
    this->schedule(CC_CALLBACK_1(CTower::search, this), "search"); // 定时执行搜索函数
    this->schedule(CC_CALLBACK_1(CTower::fire, this), m_pTowerDt->m_VecLevel[m_nCurGrade]->fAckInterval, "fire"); // 定时执行开火函数
    return true;
}

// 升级塔台
void CTower::upgrade()
{
    m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[++m_nCurGrade]->VecImg[nCurState]); // 更新塔台精灵图像
    setSaleCoin(m_pTowerDt->m_VecLevel[m_nCurGrade]->nWorth); // 更新出售金币
    setUpGradeCoin(m_pTowerDt->m_VecLevel[m_nCurGrade]->nUpgradeCoin); // 更新升级金币
    setCurGrade(m_nCurGrade); // 更新当前等级
}

// 创建塔台实例
CTower* CTower::createWithData(int nTowerID)
{
    CTower* pTower = new CTower();
    if (pTower && pTower->initWithData(nTowerID)) {
        pTower->autorelease();
        return pTower;
    }
    CC_SAFE_DELETE(pTower);
    return nullptr;
}

// 搜索敌人
void CTower::search(float delta)
{
    // 从游戏场景获取敌人管理器，查找在塔台攻击范围内的敌人
    CEnemy* pTarget = CGameScene::getInstance()->getEnemyMgr()->getEnemyByRadius(m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope, this->getPosition());
    // 如果找到敌人，根据敌人位置调整塔台方向，并可能执行开火操作
    if (pTarget) {
        Vec2 EnemyPos = pTarget->getPosition();
        Vec2 TowerPos = this->getPosition();
        m_fDisSq = EnemyPos.getDistanceSq(TowerPos);
        float TowerScope = m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope;
        if (TowerScope * TowerScope >= m_fDisSq && (m_nCurTowerID == 4001 || m_nCurTowerID == 4002 || m_nCurTowerID == 4003 || m_nCurTowerID == 4004 || m_nCurTowerID == 4006)) {
            Vec2 disPos = EnemyPos - TowerPos;
            m_nDir = disPos.getNormalized();
            Vec2 downVector(0, -1);
            float angleRadians = m_nDir.getAngle(downVector);
            float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
            m_pImage->setRotation(angleDegrees); // 旋转塔台朝向敌人
        }
    }
}

// 塔台开火
void CTower::fire(float Dt)
{
    // 获取在攻击范围内的敌人
    CEnemy* pTarget = CGameScene::getInstance()->getEnemyMgr()->getEnemyByRadius(m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope, this->getPosition());
    if (pTarget) {
        // 根据塔台ID和塔台等级确定开火逻辑
        if (m_nCurTowerID == 4001 || m_nCurTowerID == 4002 || m_nCurTowerID == 4004) {
            nCurState = E_STATE_FIRE; // 设置塔台为开火状态
            m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]); // 更新塔台图像为开火状态
            SBulletDt* pBulletDt = static_cast<SBulletDt*>(CConfigMgr::getInstance()->getData("BulletDtMgr")->getDataByID(m_pTowerDt->m_VecLevel[m_nCurGrade]->nBulletID)); // 获取子弹数据
            CBullet* pBullet = CBullet::createWithData(pBulletDt); // 创建子弹
            pBullet->setPosition(this->getPosition()); // 设置子弹位置
            _eventDispatcher->dispatchCustomEvent("addBullet", pBullet); // 添加子弹到游戏场景
            pBullet->setTarget(pTarget); // 设置子弹的目标
            pBullet->setDamage(m_pTowerDt->m_VecLevel[m_nCurGrade]->nAck); // 设置子弹的伤害
            pBullet->addCollsionCb(CC_CALLBACK_1(CEnemy::onCollision, pTarget)); // 设置子弹的碰撞回调
            Vec2 dir = (pTarget->getPosition() - this->getPosition()).getNormalized();
            Vec2 downVector(0, -1);
            float angleRadians = dir.getAngle(downVector);
            float angleDegrees = angleRadians * 180 / M_PI;  // M_PI 是一个宏，定义了π的值
            pBullet->setRotation(angleDegrees); // 设置子弹的方向
        }
        // 其他塔台的开火逻辑可以在这里添加
        else {
            nCurState = E_STATE_NORMAL; // 设置塔台为正常状态
            m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]); // 更新塔台图像为正常状态
        }
    }
}
