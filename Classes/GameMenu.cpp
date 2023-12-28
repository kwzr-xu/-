#include "GameMenu.h"
#include "LevelSelScene.h"
#include "audio/include/AudioEngine.h"  // 使用新的 AudioEngine 头文件
#include "Setting.h"

using namespace cocos2d; // AudioEngine 命名空间

CGameMenu::CGameMenu()
	//: m_nMDir(0, 1)
	//, m_nCDir(1, 0)
{
}

CGameMenu::~CGameMenu()
{
	AudioEngine::end(); // 当不再需要音频时释放资源
}

bool CGameMenu::init()
{
	if (!Scene::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 使用 AudioEngine 播放背景音乐
	AudioEngine::play2d("Menu/MainAudio.mp3", true);

	Sprite* pBg = Sprite::createWithSpriteFrameName("MainBg.png");
	pBg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(pBg);

	this->createButton();
	this->createObject();
	this->scheduleUpdate();
	return true;
}


//void CGameMenu::leafShake(float Dt)
//{

//}

/*
void CGameMenu::update(float delta)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Vec2 MonsterPos = m_pDyMonster->getPosition();
	MonsterPos.y += m_nMDir.y*delta * 20;
	if (MonsterPos.y>=470) {
		m_nMDir = Vec2(0,-1);
	}
	else if (MonsterPos.y<=430) {
		m_nMDir = Vec2(0, 1);
	}
	m_pDyMonster->setPosition(MonsterPos);


	Vec2 CloudPos = m_pDyCloud->getPosition();
	CloudPos.x += m_nCDir.x*delta * 30;
	if (CloudPos.x>(visibleSize.width+m_pDyCloud->getContentSize().width/2)) {
		CloudPos.x = origin.x - m_pDyCloud->getContentSize().width / 2;
	}

	m_pDyCloud->setPosition(CloudPos);
}
*/

void CGameMenu::click(Ref* pSender)
{
	// 使用 AudioEngine 播放点击音效
	AudioEngine::play2d("Menu/click.mp3", false);

	if (pSender == m_pAdvent) {
		Director::getInstance()->replaceScene(TransitionFade::create(1, CLevelSelScene::create()));
	}
	//if (pSender == m_pSetup) {
	//	Director::getInstance()->replaceScene(TransitionFade::create(1, CSetting::create()));
	//}
}

void CGameMenu::createButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	m_pAdvent = Button::create("AdventNor.png","AdventSel.png","",Widget::TextureResType::PLIST);
	m_pAdvent->setScale(1.3);
	m_pAdvent->setPosition(Vec2(visibleSize.width/2, visibleSize.height/6));
	m_pAdvent->addClickEventListener(CC_CALLBACK_1(CGameMenu::click,this));
	this->addChild(m_pAdvent);


	//m_pBoos = Button::create("BoosNor.png", "BoosSel.png", "", Widget::TextureResType::PLIST);
	//m_pBoos->setPosition(Vec2((visibleSize.width - m_pAdvent->getContentSize().width * 3) / 2 + m_pAdvent->getContentSize().width*1.5, 50 + m_pAdvent->getContentSize().height / 2));
	//m_pBoos->addClickEventListener(CC_CALLBACK_1(CGameMenu::click, this));
	//this->addChild(m_pBoos);


	//m_pMonster = Button::create("MonsterNor.png", "MonsterSel.png", "", Widget::TextureResType::PLIST);
	//m_pMonster->setPosition(Vec2(visibleSize.width- (visibleSize.width - m_pAdvent->getContentSize().width * 3) / 4- m_pAdvent->getContentSize().width/2, 50 + m_pAdvent->getContentSize().height / 2));
	//m_pMonster->addClickEventListener(CC_CALLBACK_1(CGameMenu::click, this));
	//this->addChild(m_pMonster);

	//设置按钮

	//m_pSetup = Button::create("setupNor.png", "setupSel.png", "", Widget::TextureResType::PLIST);
	//m_pSetup->setPosition(Vec2(200,230));
	//m_pSetup->addClickEventListener(CC_CALLBACK_1(CGameMenu::click, this));
	//this->addChild(m_pSetup);


	//m_pDoubt = Button::create("doubtNor.png", "doubtSel.png", "", Widget::TextureResType::PLIST);
	//m_pDoubt->setPosition(Vec2(760, 230));
	//m_pDoubt->addClickEventListener(CC_CALLBACK_1(CGameMenu::click, this));
	//this->addChild(m_pDoubt);
}

void CGameMenu::createObject()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_pDyMonster = Sprite::createWithSpriteFrameName("DyMonst.png");
	m_pDyMonster->setPosition(200,450);
	this->addChild(m_pDyMonster);

	m_pDyCloud = Sprite::createWithSpriteFrameName("cloud.png");
	m_pDyCloud->setPosition(origin.x-m_pDyCloud->getContentSize().width/2, 550);
	this->addChild(m_pDyCloud);

	m_pleaf1 = Sprite::createWithSpriteFrameName("leaf1.png");
	m_pleaf1->setPosition(400,430);
	this->addChild(m_pleaf1);


	m_pleaf2 = Sprite::createWithSpriteFrameName("leaf3.png");
	m_pleaf2->setPosition(500, 430);
	this->addChild(m_pleaf2);


	m_pleaf3 = Sprite::createWithSpriteFrameName("leaf2.png");
	m_pleaf3->setPosition(450, 440);
	this->addChild(m_pleaf3);

	Sprite* pRadish = Sprite::createWithSpriteFrameName("radish.png");
	pRadish->setPosition(origin.x + visibleSize.width / 2 - 40, origin.y + visibleSize.height / 2 + 50);
	this->addChild(pRadish);

	Sprite* pFont = Sprite::createWithSpriteFrameName("font.png");
	pFont->setPosition(origin.x + visibleSize.width / 2 - 20, origin.y + visibleSize.height / 2);
	this->addChild(pFont);

}