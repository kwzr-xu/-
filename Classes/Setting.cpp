#include"Setting.h"


CSetting::CSetting()
{
}

CSetting::~CSetting()
{
}

bool CSetting::init()
{
	if (!Scene::init()) {
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*Sprite* pFirst = Sprite::createWithSpriteFrameName("option.png");
	pFirst->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
	this->addChild(pFirst);*/
	return true;
}
