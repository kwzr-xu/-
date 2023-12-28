#include"Tower.h"
#include"GameScene.h"

// ���캯������ʼ�����ֲ���
CTower::CTower()
    :m_nCurGrade(0) // ��ǰ�ȼ�
    , nCurState(E_STATE_NORMAL) // ��ǰ״̬�������򿪻�
    , m_nSaleCoin(0) // ���۽��
    , m_nDir(0, -1) // ����
    , m_nEnemyIndex(0) // ��������
    , m_nCurTowerID(0) // ��ǰ��̨ID
    , i(0) // ��������
{
}

// ��������
CTower::~CTower()
{
}

// ʹ�����ݳ�ʼ����̨
bool CTower::initWithData(int nTowerID)
{
    if (!Node::init()) {
        return false;
    }
    m_nCurTowerID = nTowerID; // ������̨ID
    m_pTowerDt = static_cast<STowerDt*>(CConfigMgr::getInstance()->getData("TowerDtMgr")->getDataByID(nTowerID)); // ��ȡ��̨����
    m_pImage = Sprite::createWithSpriteFrameName(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]); // ������̨����
    m_nSaleCoin = m_pTowerDt->m_VecLevel[m_nCurGrade]->nWorth; // ���ó��۽��
    m_nUpGradeCoin = m_pTowerDt->m_VecLevel[m_nCurGrade]->nUpgradeCoin; // �����������
    this->addChild(m_pImage); // �����̨����Ϊ�ӽڵ�
    this->schedule(CC_CALLBACK_1(CTower::search, this), "search"); // ��ʱִ����������
    this->schedule(CC_CALLBACK_1(CTower::fire, this), m_pTowerDt->m_VecLevel[m_nCurGrade]->fAckInterval, "fire"); // ��ʱִ�п�����
    return true;
}

// ������̨
void CTower::upgrade()
{
    m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[++m_nCurGrade]->VecImg[nCurState]); // ������̨����ͼ��
    setSaleCoin(m_pTowerDt->m_VecLevel[m_nCurGrade]->nWorth); // ���³��۽��
    setUpGradeCoin(m_pTowerDt->m_VecLevel[m_nCurGrade]->nUpgradeCoin); // �����������
    setCurGrade(m_nCurGrade); // ���µ�ǰ�ȼ�
}

// ������̨ʵ��
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

// ��������
void CTower::search(float delta)
{
    // ����Ϸ������ȡ���˹���������������̨������Χ�ڵĵ���
    CEnemy* pTarget = CGameScene::getInstance()->getEnemyMgr()->getEnemyByRadius(m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope, this->getPosition());
    // ����ҵ����ˣ����ݵ���λ�õ�����̨���򣬲�����ִ�п������
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
            m_pImage->setRotation(angleDegrees); // ��ת��̨�������
        }
    }
}

// ��̨����
void CTower::fire(float Dt)
{
    // ��ȡ�ڹ�����Χ�ڵĵ���
    CEnemy* pTarget = CGameScene::getInstance()->getEnemyMgr()->getEnemyByRadius(m_pTowerDt->m_VecLevel[m_nCurGrade]->nScope, this->getPosition());
    if (pTarget) {
        // ������̨ID����̨�ȼ�ȷ�������߼�
        if (m_nCurTowerID == 4001 || m_nCurTowerID == 4002 || m_nCurTowerID == 4004) {
            nCurState = E_STATE_FIRE; // ������̨Ϊ����״̬
            m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]); // ������̨ͼ��Ϊ����״̬
            SBulletDt* pBulletDt = static_cast<SBulletDt*>(CConfigMgr::getInstance()->getData("BulletDtMgr")->getDataByID(m_pTowerDt->m_VecLevel[m_nCurGrade]->nBulletID)); // ��ȡ�ӵ�����
            CBullet* pBullet = CBullet::createWithData(pBulletDt); // �����ӵ�
            pBullet->setPosition(this->getPosition()); // �����ӵ�λ��
            _eventDispatcher->dispatchCustomEvent("addBullet", pBullet); // ����ӵ�����Ϸ����
            pBullet->setTarget(pTarget); // �����ӵ���Ŀ��
            pBullet->setDamage(m_pTowerDt->m_VecLevel[m_nCurGrade]->nAck); // �����ӵ����˺�
            pBullet->addCollsionCb(CC_CALLBACK_1(CEnemy::onCollision, pTarget)); // �����ӵ�����ײ�ص�
            Vec2 dir = (pTarget->getPosition() - this->getPosition()).getNormalized();
            Vec2 downVector(0, -1);
            float angleRadians = dir.getAngle(downVector);
            float angleDegrees = angleRadians * 180 / M_PI;  // M_PI ��һ���꣬�����˦е�ֵ
            pBullet->setRotation(angleDegrees); // �����ӵ��ķ���
        }
        // ������̨�Ŀ����߼��������������
        else {
            nCurState = E_STATE_NORMAL; // ������̨Ϊ����״̬
            m_pImage->setSpriteFrame(m_pTowerDt->m_VecLevel[m_nCurGrade]->VecImg[nCurState]); // ������̨ͼ��Ϊ����״̬
        }
    }
}
