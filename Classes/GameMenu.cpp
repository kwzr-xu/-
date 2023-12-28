#include "GameMenu.h"
#include "LevelSelScene.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

CGameMenu::CGameMenu()
{
}

CGameMenu::~CGameMenu()
{
}

Scene* CGameMenu::scene()
{
	Scene* scene = Scene::create();
	CGameMenu* layer = CGameMenu::create();

	scene->addChild(layer);

	return scene;
}

bool CGameMenu::init()
{
	if (!Scene::init()) {
		return false;
	}

	AudioEngine::pauseAll();
	AudioEngine::play2d("Menu/BGM.mp3", true);

	auto director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();
	auto origin = director->getVisibleOrigin();

	auto background = Sprite::create("Menu/main.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Point(0, 0));

	float x = visibleSize.width / background->getContentSize().width;
	float y = visibleSize.height / background->getContentSize().height;
	background->setScale(x, y);

	this->addChild(background);

	Sprite* AdventNormal = Sprite::create("Menu/newGameButton.png", Rect(0, 0, 300, 88));
	Sprite* AdventSelected = Sprite::create("Menu/newGameButton.png", Rect(0, 88, 300, 88));
	Sprite* AdventDisabled = Sprite::create("Menu/newGameButton.png", Rect(0, 88 * 2, 300, 88));

	MenuItemSprite* m_pAdvent = MenuItemSprite::create(AdventNormal, AdventSelected, AdventDisabled,
		CC_CALLBACK_1(CGameMenu::click, this));
	m_pAdvent->setPosition(Point(visibleSize.width / 2, 100));

	Menu* menu = Menu::create(m_pAdvent, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2, 2);

	return true;
}


void CGameMenu::click(Ref* pSender)
{

	Scene* scene = Scene::create();
	scene->addChild(CLevelSelScene::create());
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));

	//Director::getInstance()->replaceScene(TransitionFade::create(1, CLevelSelScene::create()));
}
