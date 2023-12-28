#include"TowerMgr.h"
#include"DynamicDt.h"
#include"DataClass.h"
#include"ConfigMgr.h"
#include"GameScene.h"
using namespace ui;
CTowerMgr::CTowerMgr()
{
}

CTowerMgr::~CTowerMgr()
{
}

bool CTowerMgr::init()
{
	if (!Node::init()) {
		return false;
	}
	pNode = Node::create();
	pNode->setPosition(Vec2::ZERO);
	this->addChild(pNode,100);
	int nLevelID = CDynamicDt::getInstance()->getLevelID();

	m_pCurLevelDt = static_cast<SLevelDt*>(CConfigMgr::getInstance()->getData("LevelDtMgr")->getDataByID(nLevelID));
	this->creatAnims();
	this->addTouchEvent();
	return true;
}
void CTowerMgr::upGradeTips(int nCoin)
{
	Vector<Node*> VecTower = this->getChildren();
	for (Node*& pTNode: VecTower) {
		CTower* pTower = static_cast<CTower*>(pTNode);
		if (pTower->getUpGradeCoin()<= nCoin) {
			Sprite* pTips = Sprite::create("UpTips1.png");
			pTips->setPosition(Vec2(pTower->getPositionX(),pTower->getPositionY()+pTower->getContentSize().height/2+pTips->getContentSize().height/2+10));
			this->addChild(pTips);
			Animate* pTipsAnim = Animate::create(m_pAnimationUpTips);
			pTips->runAction(RepeatForever::create(pTipsAnim));
		}
	}
}
//判断该点的炮台
CTower * CTowerMgr::getTowerByPos(const Vec2 & pos)
{
	Vector<Node*> VecTower = this->getChildren();
	for (Node*& pTNode : VecTower) {
		CTower* pTower = static_cast<CTower*>(pTNode);
		if (pTower->getPosition() == pos) {
			return pTower;
		}
	}
	return nullptr;
}

//遍历塔台管理者所有炮台，给后面时候能
bool CTowerMgr::isTower(const Vec2 & pos)
{
	Vector<Node*> VecTower = this->getChildren();
	for (Node*& pTNode:VecTower) {
		CTower* pTower = static_cast<CTower*>(pTNode);
		if (pTower->getPosition() == pos) {
			return true;
		}
	}
	return false;
}

void CTowerMgr::upGradeAndDeleta(CTower* pTower) {
	// 创建一个面板精灵，并设置其位置
	Sprite* pPanel = Sprite::create("1.png");
	pPanel->setPosition(m_nTouchPos);
	pNode->addChild(pPanel);

	// 如果塔的升级费用小于1000，创建一个升级按钮
	if (pTower->getUpGradeCoin() < 1000) {
		m_pUpGrade1 = Button::create(StringUtils::format("%03dok.png", pTower->getUpGradeCoin()), StringUtils::format("%03dok.png", pTower->getUpGradeCoin()), "", Widget::TextureResType::PLIST);
		m_pUpGrade1->setPosition(Vec2(m_nTouchPos.x, m_nTouchPos.y + 80));
		m_pUpGrade1->addClickEventListener(CC_CALLBACK_1(CTowerMgr::UpGradeClick, this));
		pNode->addChild(m_pUpGrade1);
	}

	// 创建一个删除按钮
	Button* pDelete = Button::create("Delete.png", "Delete.png", "", Widget::TextureResType::PLIST);
	pDelete->setPosition(Vec2(m_nTouchPos.x, m_nTouchPos.y - 80));
	pDelete->addClickEventListener(CC_CALLBACK_1(CTowerMgr::DeleteClick, this));
	pNode->addChild(pDelete);
}

void CTowerMgr::createCurCard()
{
	Sprite* pSel = Sprite::createWithSpriteFrameName("TowerSet1.png");
	pSel->setPosition(m_nTouchPos);
	pNode->addChild(pSel);
	Animate* pAnimateSel = Animate::create(m_pAnimationSel);
	pSel->runAction(RepeatForever::create(pAnimateSel));
	for (int i = 0; i < m_pCurLevelDt->VecCard.size(); i++) {
		SCardDt* pData = static_cast<SCardDt*>(CConfigMgr::getInstance()->getData("CardDtMgr")->getDataByID(m_pCurLevelDt->VecCard[i]));
		if (CDynamicDt::getInstance()->getMapGold() >= pData->nCoins) {
			Button* pTower = Button::create(pData->strImg, pData->strImg, "", Widget::TextureResType::PLIST);
			float fX = m_nTouchPos.x - pSel->getContentSize().width / 2 - pTower->getContentSize().width / 2 + 10 + 100 * i;
			float fY = m_nTouchPos.y + pSel->getContentSize().height / 2 + pTower->getContentSize().height / 2 + 10;
			pTower->setPosition(Vec2(fX, fY));
			pNode->addChild(pTower);
			pTower->addClickEventListener(CC_CALLBACK_1(CTowerMgr::addTowerClick, this, pData->nTowerID));
		}
		else {
			Button* pTower = Button::create(pData->strDisImg, pData->strDisImg, "", Widget::TextureResType::PLIST);
			float fX = m_nTouchPos.x - pSel->getContentSize().width / 2 - pTower->getContentSize().width / 2 + 10 + 100 * i;
			float fY = m_nTouchPos.y + pSel->getContentSize().height / 2 + pTower->getContentSize().height / 2 + 10;
			pTower->setPosition(Vec2(fX, fY));
			pNode->addChild(pTower);
		}
	}
}


void CTowerMgr::creatAnims()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	m_pAnimationSel = Animation::create();
	for (int i = 0; i < 2;i++) {
		SpriteFrame* pFrame = pCache->getSpriteFrameByName(StringUtils::format("TowerSet%d.png",i+1));
		m_pAnimationSel->addSpriteFrame(pFrame);
	}
	m_pAnimationSel->setDelayPerUnit(0.3);
	m_pAnimationSel->retain();


	//种植塔台动画
	m_pAnimationPaint = Animation::create();
	for (int i = 0; i < 3; i++) {
		SpriteFrame* pFrame = pCache->getSpriteFrameByName(StringUtils::format("ui_Props_02_%02d.png", i + 1));
		m_pAnimationPaint->addSpriteFrame(pFrame);
	}
	m_pAnimationPaint->setDelayPerUnit(0.1);
	m_pAnimationPaint->retain();


	//塔台升级动画
	m_pAnimationUpGrade = Animation::create();
	for (int i = 0; i < 3; i++) {
		SpriteFrame* pFrame = pCache->getSpriteFrameByName(StringUtils::format("TowerUpdata%d.png", i + 1));
		m_pAnimationUpGrade->addSpriteFrame(pFrame);
	}
	m_pAnimationUpGrade->setDelayPerUnit(0.1);
	m_pAnimationUpGrade->retain();

	//提示塔台升级动画

	m_pAnimationUpTips = Animation::create();
	for (int i = 0; i < 2; i++) {
		SpriteFrame* pFrame = pCache->getSpriteFrameByName(StringUtils::format("UpTips%d.png", i + 1));
		m_pAnimationUpTips->addSpriteFrame(pFrame);
	}
	m_pAnimationUpTips->setDelayPerUnit(0.3);
	m_pAnimationUpTips->retain();
}

void CTowerMgr::addTowerClick(Ref * pRender,int nTowerID)
{
	//给安装塔台设置一个绽放动画，播放完动画之后删除该精灵
	Animate* pAnimationPaint = Animate::create(m_pAnimationPaint);
	m_pOK = Sprite::createWithSpriteFrameName("ui_Props_02_01.png");
	m_pOK->setPosition(m_nTouchPos);
	this->addChild(m_pOK);
	Sequence* pSeq = Sequence::create(pAnimationPaint, RemoveSelf::create(),NULL);
	m_pOK->runAction(pSeq);



	pNode->removeAllChildren();
	m_nTower = CTower::createWithData(nTowerID);
	STowerDt* pData = static_cast<STowerDt*>(CConfigMgr::getInstance()->getData("TowerDtMgr")->getDataByID(nTowerID));
	int nCoin = CDynamicDt::getInstance()->getMapGold();
	nCoin -= pData->m_VecLevel[0]->nWorth;
	CDynamicDt::getInstance()->setMapGold(nCoin);
	CGameScene::getInstance()->m_pCoinLabel->setString(StringUtils::format("%d", CDynamicDt::getInstance()->getMapGold()));
	m_nTower->setPosition(m_nTouchPos);
	this->addChild(m_nTower);
}

void CTowerMgr::DeleteClick(Ref * pRender)
{
	if (pNode != nullptr) {
		pNode->removeAllChildren();
	}
	CTower* pCurTower = this->getTowerByPos(m_nTouchPos);
	//pCurTower->getSaleCoin()*0.6;
	int nCoin = CDynamicDt::getInstance()->getMapGold();
	nCoin += pCurTower->getSaleCoin()*0.6;
	CDynamicDt::getInstance()->setMapGold(nCoin);
	CGameScene::getInstance()->m_pCoinLabel->setString(StringUtils::format("%d", CDynamicDt::getInstance()->getMapGold()));
	this->removeChild(pCurTower);
}

void CTowerMgr::UpGradeClick(Ref * pRender)
{
	if (pNode != nullptr) {
		pNode->removeAllChildren();
	}
	Animate* pUpGrade = Animate::create(m_pAnimationUpGrade);
	m_pUpGradeAnims = Sprite::createWithSpriteFrameName("TowerUpdata1.png");
	m_pUpGradeAnims->setPosition(m_nTouchPos);
	this->addChild(m_pUpGradeAnims);
	Sequence* pSeq = Sequence::create(pUpGrade, RemoveSelf::create(), NULL);
	m_pUpGradeAnims->runAction(pSeq);

	CTower* pCurTower = this->getTowerByPos(m_nTouchPos);
	//pCurTower->getUpGradeCoin();
	int nCoin = CDynamicDt::getInstance()->getMapGold();
	nCoin -= pCurTower->getUpGradeCoin();
	CDynamicDt::getInstance()->setMapGold(nCoin);
	CGameScene::getInstance()->m_pCoinLabel->setString(StringUtils::format("%d", CDynamicDt::getInstance()->getMapGold()));
	pCurTower->upgrade();
}

void CTowerMgr::addTouchEvent()
{
	EventListenerTouchOneByOne* pListener = EventListenerTouchOneByOne::create();
	pListener->onTouchBegan = CC_CALLBACK_2(CTowerMgr::onTouchBegan,this);
	//pListener->setSwallowTouches(true);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener,this);
}

bool CTowerMgr::onTouchBegan(Touch * pTouch, Event * pEvent)
{
	Vec2 pos = pTouch->getLocation();

	Vec2 tile = CGameScene::getInstance()->getTiledMapCtrl()->getTiledByPos(pos);

	m_nTouchPos = CGameScene::getInstance()->getTiledMapCtrl()->getPosByTiled(tile);
	if (CGameScene::getInstance()->getTiledMapCtrl()->isNullTile(tile)&&!this->isTower(m_nTouchPos)) {
		if (pNode != nullptr) {
			pNode->removeAllChildren();
		}
		//点击屏幕位置安装塔台，并给塔台设置点击回调函数
		this->createCurCard();
	}
	else if (this->isTower(m_nTouchPos)) {
		CTower* pCurTower = this->getTowerByPos(m_nTouchPos);	
		//点其他地方消除挑选框
		if (pNode != nullptr) {
			pNode->removeAllChildren();
		}
		this->upGradeAndDeleta(pCurTower);
		if (pCurTower->getCurGrade() == 2) {
			this->upGradeAndDeleta(pCurTower);
			Button* pUpGradeMax = Button::create("GradeMax.png", "GradeMax.png", "", Widget::TextureResType::PLIST);
			pUpGradeMax->setPosition(Vec2(m_nTouchPos.x, m_nTouchPos.y + 80));
			pNode->addChild(pUpGradeMax);
		}
		else if (CDynamicDt::getInstance()->getMapGold() < pCurTower->getUpGradeCoin()) {
			Button* pUpGrade = Button::create(StringUtils::format("%dno.png", pCurTower->getUpGradeCoin()), StringUtils::format("%dno.png", pCurTower->getUpGradeCoin()), "", Widget::TextureResType::PLIST);
			pUpGrade->setPosition(Vec2(m_nTouchPos.x, m_nTouchPos.y + 80));
			pNode->addChild(pUpGrade);
		}
	}
	else {
		//点其他地方消除挑选框
		if (pNode != nullptr) {
			pNode->removeAllChildren();
		}
	}
	return true;
}

