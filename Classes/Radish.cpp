#include "Radish.h" // 包含 CRadish 类的声明

// 构造函数
CRadish::CRadish()
    : m_nHp(10),        // 初始化生命值为 10
    m_nHpState(1)     // 初始化生命状态为 1
{
    // 构造函数的主体
}

// 析构函数
CRadish::~CRadish()
{
    // 析构函数的主体，用于资源清理
}

// 初始化方法
bool CRadish::init()
{
    // 首先调用基类的 init 方法
    if (!Node::init()) {
        return false; // 如果基类初始化失败，返回 false
    }

    // 根据生命状态创建萝卜的图像精灵
    m_pImage = Sprite::createWithSpriteFrameName(StringUtils::format("ui_luobo_%02d.png", m_nHpState));
    m_pImage->setAnchorPoint(Vec2(0.5, 0)); // 设置锚点
    this->addChild(m_pImage); // 将图像精灵添加为子节点

    // 创建表示生命值的血条精灵
    m_pHpBar = Sprite::createWithSpriteFrameName(StringUtils::format("hp_%d.png", m_nHp));
    m_pHpBar->setPosition(m_pImage->getPositionX() + 50, m_pImage->getPositionY() + 50); // 设置血条位置
    this->addChild(m_pHpBar); // 将血条精灵添加为子节点

    return true; // 初始化成功
}