#include"Radish.h"
#include"GameScene.h"
CRadish::CRadish()
	:m_nHp(10)
	,m_nHpState(1)
{
}

CRadish::~CRadish()
{
}

bool CRadish::init()
{
	if (!Node::init()) {
		return false;
	}
	m_pImage = Sprite::createWithSpriteFrameName(StringUtils::format("ui_luobo_%02d.png", m_nHpState));
	m_pImage->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(m_pImage);

	m_pHpBar = Sprite::createWithSpriteFrameName(StringUtils::format("hp_%d.png", m_nHp));
	m_pHpBar->setPosition(m_pImage->getPositionX() + 50, m_pImage->getPositionY() + 50);
	this->addChild(m_pHpBar);
	return true;
}
