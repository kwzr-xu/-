// 包含所需的头文件
#include "GameScene.h"
#include "DynamicDt.h"
#include "LoadingScene.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

// 静态成员变量，用于实现单例模式
CGameScene* CGameScene::m_pInstance = nullptr;

// 构造函数，初始化计时器
CGameScene::CGameScene() : m_nTimer(3) { }

// 析构函数
CGameScene::~CGameScene() { }

// 初始化场景
bool CGameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	// 获取屏幕大小和原点坐标
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 加载当前级别的数据和地图控制器
	m_pCurLevelDt = static_cast<SLevelDt*>(CConfigMgr::getInstance()->getData("LevelDtMgr")->getDataByID(CDynamicDt::getInstance()->getLevelID()));
	m_pTiledMapCtrl = CTiledMapCtrl::createWithData(m_pCurLevelDt);
	this->addChild(m_pTiledMapCtrl);

	// 创建并添加背景精灵
	Sprite* pCbg = Sprite::createWithSpriteFrameName("ui_Item_01.png");
	pCbg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - pCbg->getContentSize().height / 2);
	m_pTiledMapCtrl->addChild(pCbg);

	// 设置初始金币和金币显示标签
	CDynamicDt::getInstance()->setMapGold(m_pCurLevelDt->nInitGold);
	m_pCoinLabel = Label::createWithTTF(StringUtils::format("%d", CDynamicDt::getInstance()->getMapGold()), "fonts/comicbd.ttf", 30);
	m_pCoinLabel->setPosition(100 + m_pCoinLabel->getContentSize().width / 2, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2);
	this->addChild(m_pCoinLabel);

	// 创建敌人管理器并添加
	m_pEnemyMgr = CEnemyMgr::create();
	m_pTiledMapCtrl->addChild(m_pEnemyMgr);

	// 创建控制按钮并添加事件监听器
	// 正常速度按钮
	m_pNormalSpeed = Button::create("Game/Normal_Speed.png", "Game/Accel_Speed.png", "", Widget::TextureResType::LOCAL);
	m_pNormalSpeed->setPosition(Vec2(origin.x + visibleSize.width - 180, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2 - 5));
	m_pNormalSpeed->addClickEventListener(CC_CALLBACK_1(CGameScene::Speed_Up, this));
	this->addChild(m_pNormalSpeed);

	// 暂停按钮
	m_pStop = Button::create("Game/StopNor.png", "Game/StopSel.png", "", Widget::TextureResType::LOCAL);
	m_pStop->setPosition(Vec2(origin.x + visibleSize.width - 110, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2 - 5));
	m_pStop->addClickEventListener(CC_CALLBACK_1(CGameScene::stop, this));
	this->addChild(m_pStop);

	// 菜单按钮
	m_pMenu = Button::create("Game/MenuNor.png", "Game/MenuSel.png", "", Widget::TextureResType::LOCAL);
	m_pMenu->setPosition(Vec2(origin.x + visibleSize.width - 50, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2 - 5));
	m_pMenu->addClickEventListener(CC_CALLBACK_1(CGameScene::addMenu, this));
	this->addChild(m_pMenu);

	// 创建并添加波数显示
	m_pWaveNum = Sprite::create("Game/Wave.png");
	m_pWaveNum->setPosition(origin.x + visibleSize.width / 2 - m_pWaveNum->getContentSize().width / 2, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2);
	this->addChild(m_pWaveNum);

	m_pWaveLabel = Label::createWithTTF(StringUtils::format("0 %d", m_pEnemyMgr->getWaveIndex() + 1), "fonts/comicbd.ttf", 30);
	m_pWaveLabel->setPosition(origin.x + visibleSize.width / 2 - m_pWaveNum->getContentSize().width / 2, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2);
	this->addChild(m_pWaveLabel);

	m_pTotalWaveLabel = Label::createWithTTF(StringUtils::format(" / %d%s", m_pCurLevelDt->m_VecWaves.size(), this->G2U("波怪物")), "fonts/msyhbd.ttc", 30);
	m_pTotalWaveLabel->setPosition(origin.x + visibleSize.width / 2 + m_pTotalWaveLabel->getContentSize().width / 2, origin.y + visibleSize.height - 13 - m_pCoinLabel->getContentSize().height / 2);
	this->addChild(m_pTotalWaveLabel);

	// 创建并添加萝卜（游戏中的一个元素）
	m_pRadish = CRadish::create();
	Vec2 RadishPos = m_pTiledMapCtrl->getPosByTiled(Vec2(m_pCurLevelDt->nRadishRow, m_pCurLevelDt->nRadishCol));
	m_pRadish->setPosition(RadishPos);
	m_pTiledMapCtrl->addChild(m_pRadish);

	// 创建塔管理器并添加
	m_pTowerMgr = CTowerMgr::create();
	this->addChild(m_pTowerMgr, 100);

	// 创建子弹管理器并添加
	m_pBulletMgr = CBulletMgr::create();
	this->addChild(m_pBulletMgr);

	// 创建障碍物
	//this->createOb();

	// 安排场景更新
	this->scheduleUpdate();
	return true;
}

// 单例模式的实现，确保只有一个场景实例
CGameScene* CGameScene::getInstance() {
	if (!m_pInstance) {
		m_pInstance = CGameScene::create();
	}
	return m_pInstance;
}

// 销毁场景实例
CGameScene* CGameScene::destory() {
	Director::getInstance()->getScheduler()->setTimeScale(1);
	m_pInstance = nullptr;
	return m_pInstance;
}


// 创建游戏中的菜单界面
void CGameScene::createMenu() {
	// 创建一个新的节点作为菜单的容器
	m_pMenuNode = Node::create();
	m_pMenuNode->setPosition(Vec2::ZERO);
	this->addChild(m_pMenuNode, 200);

	// 获取屏幕大小和原点位置
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建并设置菜单背景
	Sprite* pMenuBg = Sprite::createWithSpriteFrameName("ui_MenuBg.png");
	pMenuBg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	m_pMenuNode->addChild(pMenuBg);

	// 创建继续游戏按钮
	m_pContinue = Button::create("ui_btn_Continue.png", "ui_btn_Continue.png", "", Widget::TextureResType::PLIST);
	m_pContinue->setPosition(Vec2(origin.x + visibleSize.width / 2 - 9, origin.y + visibleSize.height / 2 + m_pContinue->getContentSize().height * 1.5 + 8));
	m_pContinue->addClickEventListener(CC_CALLBACK_1(CGameScene::click, this));
	m_pMenuNode->addChild(m_pContinue);

	// 创建重新开始游戏按钮
	m_pResume = Button::create("ui_btn_again.png", "ui_btn_again.png", "", Widget::TextureResType::PLIST);
	m_pResume->setPosition(Vec2(origin.x + visibleSize.width / 2 - 9, origin.y + visibleSize.height / 2 + 12));
	m_pResume->addClickEventListener(CC_CALLBACK_1(CGameScene::click, this));
	m_pMenuNode->addChild(m_pResume);

	// 创建关卡选择按钮
	m_pLevelSel = Button::create("ui_btn_Sel.png", "ui_btn_Sel.png", "", Widget::TextureResType::PLIST);
	m_pLevelSel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 9, origin.y + visibleSize.height / 2 - m_pContinue->getContentSize().height - 17));
	m_pLevelSel->addClickEventListener(CC_CALLBACK_1(CGameScene::click, this));
	m_pMenuNode->addChild(m_pLevelSel);
}

// 响应暂停按钮的事件
void CGameScene::stop(Ref* pSender) {
	AudioEngine::play2d("Menu/click.mp3", false); // 播放点击音效
	if (Director::getInstance()->isPaused()) {
		Director::getInstance()->resume(); // 如果当前是暂停状态，则恢复游戏
		m_pStop->loadTextureNormal("Game/StopNor.png"); // 更新按钮纹理
	}
	else {
		m_pStop->loadTextureNormal("Game/StopSel.png"); // 更新按钮纹理
		Director::getInstance()->pause(); // 暂停游戏
	}
}

// 添加菜单的事件响应
void CGameScene::addMenu(Ref* pSender) {
	AudioEngine::play2d("Menu/click.mp3", false); // 播放点击音效
	Director::getInstance()->pause(); // 暂停游戏
	this->createMenu(); // 创建菜单
}

// 菜单中按钮点击的事件响应
void CGameScene::click(Ref* pSender) {
	AudioEngine::play2d("Menu/click.mp3", false); // 播放点击音效
	if (pSender == m_pContinue) {
		Director::getInstance()->resume(); // 恢复游戏
		this->removeChild(m_pMenuNode); // 移除菜单节点
	}
	else if (pSender == m_pResume) {
		Director::getInstance()->resume(); // 恢复游戏
		this->removeChild(m_pMenuNode); // 移除菜单节点
		auto scene = CLoadingScene::createWithData("Game"); // 创建新的游戏场景
		Director::getInstance()->replaceScene(scene); // 切换场景
	}
	else if (pSender == m_pLevelSel) {
		Director::getInstance()->resume(); // 恢复游戏
		this->removeChild(m_pMenuNode); // 移除菜单节点
		auto scene = CLoadingScene::createWithData("Menu"); // 创建菜单场景
		Director::getInstance()->replaceScene(scene); // 切换场景
	}
}


// GB2312 到 UTF-8 的字符编码转换方法
char* CGameScene::G2U(const char* gb2312) {
	// 计算需要的宽字符长度
	int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);

	// 转换宽字符到 UTF-8
	len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);

	if (wstr) delete[] wstr;
	return str;
}

// 加速按钮的事件响应方法
void CGameScene::Speed_Up(Ref* pSender) {
	// 播放点击音效
	AudioEngine::play2d("Menu/click.mp3", false);

	// 切换游戏的速度倍率
	if (Director::getInstance()->getScheduler()->getTimeScale() == 1) {
		m_pNormalSpeed->loadTextureNormal("Game/Accel_Speed.png");
		Director::getInstance()->getScheduler()->setTimeScale(2); // 加速游戏
	}
	else {
		m_pNormalSpeed->loadTextureNormal("Game/Normal_Speed.png");
		Director::getInstance()->getScheduler()->setTimeScale(1); // 恢复正常速度
	}
}

/*
// 创建障碍物的方法
void CGameScene::createOb() {
	// 遍历地图上的障碍物位置
	for (auto iter = m_pTiledMapCtrl->m_MapObPos.begin(); iter != m_pTiledMapCtrl->m_MapObPos.end(); ++iter) {
		// 根据条件选择障碍物的类型
		int nObID = (iter->first == 0) ? 7001 : random() % 4 + 7002;

		// 获取障碍物数据并创建精灵
		SObstaclesDt* pOb = static_cast<SObstaclesDt*>(CConfigMgr::getInstance()->getData("ObstaclesDtMgr")->getDataByID(nObID));
		Sprite* pObstacles = Sprite::createWithSpriteFrameName(pOb->strImg);
		pObstacles->setPosition(iter->second);

		// 将障碍物添加到场景中
		this->addChild(pObstacles);
	}
}
*/

// 场景更新方法
void CGameScene::update(float delta) {
	// 获取所有敌人节点
	Vector<Node*> VecEnemy = m_pEnemyMgr->getChildren();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 检查萝卜的位置和状态
	Vec2 tilePos = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(m_pRadish->getPosition());
	CEnemy* pEnemy = CGameScene::getInstance()->getEnemyMgr()->getEnemyByTilePos(tilePos);

	if (pEnemy && m_pRadish->getHp() > 3 && m_pRadish->getHpState() < 10) {
		// 萝卜被攻击，更新生命值和状态
		int Hp = m_pRadish->getHp() - 1;
		m_pRadish->setHp(Hp);
		int HpState = m_pRadish->getHpState() + 1;
		m_pRadish->setHpState(HpState);

		// 移除敌人并更新萝卜的显示
		pEnemy->removeFromParent();
		m_pRadish->m_pHpBar->setSpriteFrame(StringUtils::format("hp_%d.png", m_pRadish->getHp()));
		m_pRadish->m_pImage->setSpriteFrame(StringUtils::format("ui_luobo_%02d.png", m_pRadish->getHpState()));
	}
	else if (m_pRadish->getHp() <= 3 && !VecEnemy.empty()) {
		// 游戏结束逻辑
		m_StrOverOrEnd = "Over";
		this->unscheduleUpdate();
		m_pEnemyMgr->removeAllChildren();
		m_pEnemyMgr->unschedule("addEnemy");
		this->removeChild(m_pTowerMgr);

		// 创建并显示游戏结束界面
		m_pGameOver = CGameOver::create();
		this->addChild(m_pGameOver, 100);
		m_pGameOver->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	}
	else if (CDynamicDt::getInstance()->getWaveIndex() == m_pCurLevelDt->m_VecWaves.size() && VecEnemy.empty()) {
		// 游戏胜利逻辑
		CDynamicDt::getInstance()->setRadishHp(m_pRadish->getHp());
		m_StrOverOrEnd = "End";
		this->unscheduleUpdate();
		m_pEnemyMgr->removeAllChildren();
		m_pEnemyMgr->unschedule("addEnemy");
		this->removeChild(m_pTowerMgr);

		// 创建并显示游戏胜利界面
		m_pGameOver = CGameOver::create();
		this->addChild(m_pGameOver, 100);
		m_pGameOver->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	}
}