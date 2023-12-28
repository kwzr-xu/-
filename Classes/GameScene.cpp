// ���������ͷ�ļ�
#include "GameScene.h"
#include "DynamicDt.h"
#include "LoadingScene.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

// ��̬��Ա����������ʵ�ֵ���ģʽ
CGameScene* CGameScene::m_pInstance = nullptr;

// ���캯������ʼ����ʱ��
CGameScene::CGameScene() : m_nTimer(3) { }

// ��������
CGameScene::~CGameScene() { }

// ��ʼ������
bool CGameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	// ��ȡ��Ļ��С��ԭ������
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���ص�ǰ��������ݺ͵�ͼ������
	m_pCurLevelDt = static_cast<SLevelDt*>(CConfigMgr::getInstance()->getData("LevelDtMgr")->getDataByID(CDynamicDt::getInstance()->getLevelID()));
	m_pTiledMapCtrl = CTiledMapCtrl::createWithData(m_pCurLevelDt);
	this->addChild(m_pTiledMapCtrl);

	// ���������ӱ�������
	Sprite* pCbg = Sprite::createWithSpriteFrameName("ui_Item_01.png");
	pCbg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - pCbg->getContentSize().height / 2);
	m_pTiledMapCtrl->addChild(pCbg);

	// ���ó�ʼ��Һͽ����ʾ��ǩ
	CDynamicDt::getInstance()->setMapGold(m_pCurLevelDt->nInitGold);
	m_pCoinLabel = Label::createWithTTF(StringUtils::format("%d", CDynamicDt::getInstance()->getMapGold()), "fonts/comicbd.ttf", 30);
	m_pCoinLabel->setPosition(100 + m_pCoinLabel->getContentSize().width / 2, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2);
	this->addChild(m_pCoinLabel);

	// �������˹�����������
	m_pEnemyMgr = CEnemyMgr::create();
	m_pTiledMapCtrl->addChild(m_pEnemyMgr);

	// �������ư�ť�������¼�������
	// �����ٶȰ�ť
	m_pNormalSpeed = Button::create("Game/Normal_Speed.png", "Game/Accel_Speed.png", "", Widget::TextureResType::LOCAL);
	m_pNormalSpeed->setPosition(Vec2(origin.x + visibleSize.width - 180, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2 - 5));
	m_pNormalSpeed->addClickEventListener(CC_CALLBACK_1(CGameScene::Speed_Up, this));
	this->addChild(m_pNormalSpeed);

	// ��ͣ��ť
	m_pStop = Button::create("Game/StopNor.png", "Game/StopSel.png", "", Widget::TextureResType::LOCAL);
	m_pStop->setPosition(Vec2(origin.x + visibleSize.width - 110, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2 - 5));
	m_pStop->addClickEventListener(CC_CALLBACK_1(CGameScene::stop, this));
	this->addChild(m_pStop);

	// �˵���ť
	m_pMenu = Button::create("Game/MenuNor.png", "Game/MenuSel.png", "", Widget::TextureResType::LOCAL);
	m_pMenu->setPosition(Vec2(origin.x + visibleSize.width - 50, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2 - 5));
	m_pMenu->addClickEventListener(CC_CALLBACK_1(CGameScene::addMenu, this));
	this->addChild(m_pMenu);

	// ���������Ӳ�����ʾ
	m_pWaveNum = Sprite::create("Game/Wave.png");
	m_pWaveNum->setPosition(origin.x + visibleSize.width / 2 - m_pWaveNum->getContentSize().width / 2, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2);
	this->addChild(m_pWaveNum);

	m_pWaveLabel = Label::createWithTTF(StringUtils::format("0 %d", m_pEnemyMgr->getWaveIndex() + 1), "fonts/comicbd.ttf", 30);
	m_pWaveLabel->setPosition(origin.x + visibleSize.width / 2 - m_pWaveNum->getContentSize().width / 2, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2);
	this->addChild(m_pWaveLabel);

	m_pTotalWaveLabel = Label::createWithTTF(StringUtils::format(" / %d%s", m_pCurLevelDt->m_VecWaves.size(), this->G2U("������")), "fonts/msyhbd.ttc", 30);
	m_pTotalWaveLabel->setPosition(origin.x + visibleSize.width / 2 + m_pTotalWaveLabel->getContentSize().width / 2, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2);
	this->addChild(m_pTotalWaveLabel);

	// �����������ܲ�����Ϸ�е�һ��Ԫ�أ�
	m_pRadish = CRadish::create();
	Vec2 RadishPos = m_pTiledMapCtrl->getPosByTiled(Vec2(m_pCurLevelDt->nRadishRow, m_pCurLevelDt->nRadishCol));
	m_pRadish->setPosition(RadishPos);
	m_pTiledMapCtrl->addChild(m_pRadish);

	// ������������������
	m_pTowerMgr = CTowerMgr::create();
	this->addChild(m_pTowerMgr, 100);

	// �����ӵ�������������
	m_pBulletMgr = CBulletMgr::create();
	this->addChild(m_pBulletMgr);

	// �����ϰ���
	//this->createOb();

	// ���ų�������
	this->scheduleUpdate();
	return true;
}

// ����ģʽ��ʵ�֣�ȷ��ֻ��һ������ʵ��
CGameScene* CGameScene::getInstance() {
	if (!m_pInstance) {
		m_pInstance = CGameScene::create();
	}
	return m_pInstance;
}

// ���ٳ���ʵ��
CGameScene* CGameScene::destory() {
	Director::getInstance()->getScheduler()->setTimeScale(1);
	m_pInstance = nullptr;
	return m_pInstance;
}


// ������Ϸ�еĲ˵�����
void CGameScene::createMenu() {
	// ����һ���µĽڵ���Ϊ�˵�������
	m_pMenuNode = Node::create();
	m_pMenuNode->setPosition(Vec2::ZERO);
	this->addChild(m_pMenuNode, 200);

	// ��ȡ��Ļ��С��ԭ��λ��
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���������ò˵�����
	Sprite* pMenuBg = Sprite::createWithSpriteFrameName("ui_MenuBg.png");
	pMenuBg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	m_pMenuNode->addChild(pMenuBg);

	// ����������Ϸ��ť
	m_pContinue = Button::create("ui_btn_Continue.png", "ui_btn_Continue.png", "", Widget::TextureResType::PLIST);
	m_pContinue->setPosition(Vec2(origin.x + visibleSize.width / 2 - 9, origin.y + visibleSize.height / 2 + m_pContinue->getContentSize().height * 1.5 + 8));
	m_pContinue->addClickEventListener(CC_CALLBACK_1(CGameScene::click, this));
	m_pMenuNode->addChild(m_pContinue);

	// �������¿�ʼ��Ϸ��ť
	m_pResume = Button::create("ui_btn_again.png", "ui_btn_again.png", "", Widget::TextureResType::PLIST);
	m_pResume->setPosition(Vec2(origin.x + visibleSize.width / 2 - 9, origin.y + visibleSize.height / 2 + 12));
	m_pResume->addClickEventListener(CC_CALLBACK_1(CGameScene::click, this));
	m_pMenuNode->addChild(m_pResume);

	// �����ؿ�ѡ��ť
	m_pLevelSel = Button::create("ui_btn_Sel.png", "ui_btn_Sel.png", "", Widget::TextureResType::PLIST);
	m_pLevelSel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 9, origin.y + visibleSize.height / 2 - m_pContinue->getContentSize().height - 17));
	m_pLevelSel->addClickEventListener(CC_CALLBACK_1(CGameScene::click, this));
	m_pMenuNode->addChild(m_pLevelSel);
}

// ��Ӧ��ͣ��ť���¼�
void CGameScene::stop(Ref* pSender) {
	AudioEngine::play2d("Menu/click.mp3", false); // ���ŵ����Ч
	if (Director::getInstance()->isPaused()) {
		Director::getInstance()->resume(); // �����ǰ����ͣ״̬����ָ���Ϸ
		m_pStop->loadTextureNormal("Game/StopNor.png"); // ���°�ť����
	}
	else {
		m_pStop->loadTextureNormal("Game/StopSel.png"); // ���°�ť����
		Director::getInstance()->pause(); // ��ͣ��Ϸ
	}
}

// ���Ӳ˵����¼���Ӧ
void CGameScene::addMenu(Ref* pSender) {
	AudioEngine::play2d("Menu/click.mp3", false); // ���ŵ����Ч
	Director::getInstance()->pause(); // ��ͣ��Ϸ
	this->createMenu(); // �����˵�
}

// �˵��а�ť������¼���Ӧ
void CGameScene::click(Ref* pSender) {
	AudioEngine::play2d("Menu/click.mp3", false); // ���ŵ����Ч
	if (pSender == m_pContinue) {
		Director::getInstance()->resume(); // �ָ���Ϸ
		this->removeChild(m_pMenuNode); // �Ƴ��˵��ڵ�
	}
	else if (pSender == m_pResume) {
		Director::getInstance()->resume(); // �ָ���Ϸ
		this->removeChild(m_pMenuNode); // �Ƴ��˵��ڵ�
		auto scene = CLoadingScene::createWithData("Game"); // �����µ���Ϸ����
		Director::getInstance()->replaceScene(scene); // �л�����
	}
	else if (pSender == m_pLevelSel) {
		Director::getInstance()->resume(); // �ָ���Ϸ
		this->removeChild(m_pMenuNode); // �Ƴ��˵��ڵ�
		auto scene = CLoadingScene::createWithData("Menu"); // �����˵�����
		Director::getInstance()->replaceScene(scene); // �л�����
	}
}


// GB2312 �� UTF-8 ���ַ�����ת������
char* CGameScene::G2U(const char* gb2312) {
	// ������Ҫ�Ŀ��ַ�����
	int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);

	// ת�����ַ��� UTF-8
	len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);

	if (wstr) delete[] wstr;
	return str;
}

// ���ٰ�ť���¼���Ӧ����
void CGameScene::Speed_Up(Ref* pSender) {
	// ���ŵ����Ч
	AudioEngine::play2d("Menu/click.mp3", false);

	// �л���Ϸ���ٶȱ���
	if (Director::getInstance()->getScheduler()->getTimeScale() == 1) {
		m_pNormalSpeed->loadTextureNormal("Game/Accel_Speed.png");
		Director::getInstance()->getScheduler()->setTimeScale(2); // ������Ϸ
	}
	else {
		m_pNormalSpeed->loadTextureNormal("Game/Normal_Speed.png");
		Director::getInstance()->getScheduler()->setTimeScale(1); // �ָ������ٶ�
	}
}

/*
// �����ϰ���ķ���
void CGameScene::createOb() {
	// ������ͼ�ϵ��ϰ���λ��
	for (auto iter = m_pTiledMapCtrl->m_MapObPos.begin(); iter != m_pTiledMapCtrl->m_MapObPos.end(); ++iter) {
		// ��������ѡ���ϰ��������
		int nObID = (iter->first == 0) ? 7001 : random() % 4 + 7002;

		// ��ȡ�ϰ������ݲ���������
		SObstaclesDt* pOb = static_cast<SObstaclesDt*>(CConfigMgr::getInstance()->getData("ObstaclesDtMgr")->getDataByID(nObID));
		Sprite* pObstacles = Sprite::createWithSpriteFrameName(pOb->strImg);
		pObstacles->setPosition(iter->second);

		// ���ϰ������ӵ�������
		this->addChild(pObstacles);
	}
}
*/

// �������·���
void CGameScene::update(float delta) {
	// ��ȡ���е��˽ڵ�
	Vector<Node*> VecEnemy = m_pEnemyMgr->getChildren();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ����ܲ���λ�ú�״̬
	Vec2 tilePos = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(m_pRadish->getPosition());
	CEnemy* pEnemy = CGameScene::getInstance()->getEnemyMgr()->getEnemyByTilePos(tilePos);

	if (pEnemy && m_pRadish->getHp() > 3 && m_pRadish->getHpState() < 10) {
		// �ܲ�����������������ֵ��״̬
		int Hp = m_pRadish->getHp() - 1;
		m_pRadish->setHp(Hp);
		int HpState = m_pRadish->getHpState() + 1;
		m_pRadish->setHpState(HpState);

		// �Ƴ����˲������ܲ�����ʾ
		pEnemy->removeFromParent();
		m_pRadish->m_pHpBar->setSpriteFrame(StringUtils::format("hp_%d.png", m_pRadish->getHp()));
		m_pRadish->m_pImage->setSpriteFrame(StringUtils::format("ui_luobo_%02d.png", m_pRadish->getHpState()));
	}
	else if (m_pRadish->getHp() <= 3 && !VecEnemy.empty()) {
		// ��Ϸ�����߼�
		m_StrOverOrEnd = "Over";
		this->unscheduleUpdate();
		m_pEnemyMgr->removeAllChildren();
		m_pEnemyMgr->unschedule("addEnemy");
		this->removeChild(m_pTowerMgr);

		// ��������ʾ��Ϸ��������
		m_pGameOver = CGameOver::create();
		this->addChild(m_pGameOver, 100);
		m_pGameOver->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	}
	else if (CDynamicDt::getInstance()->getWaveIndex() == m_pCurLevelDt->m_VecWaves.size() && VecEnemy.empty()) {
		// ��Ϸʤ���߼�
		CDynamicDt::getInstance()->setRadishHp(m_pRadish->getHp());
		m_StrOverOrEnd = "End";
		this->unscheduleUpdate();
		m_pEnemyMgr->removeAllChildren();
		m_pEnemyMgr->unschedule("addEnemy");
		this->removeChild(m_pTowerMgr);

		// ��������ʾ��Ϸʤ������
		m_pGameOver = CGameOver::create();
		this->addChild(m_pGameOver, 100);
		m_pGameOver->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	}
}