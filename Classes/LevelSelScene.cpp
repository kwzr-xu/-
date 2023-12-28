#include "LevelSelScene.h"
#include "DynamicDt.h"
#include "GameScene.h"
//#include "LoadingScene.h"
#include "ConfigMgr.h"
#include "GameMenu.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

// 关卡选择场景的构造函数
CLevelSelScene::CLevelSelScene()
    :levelID(0) // 初始化关卡ID
{
}

// 关卡选择场景的析构函数
CLevelSelScene::~CLevelSelScene()
{
}

// 初始化函数
bool CLevelSelScene::init()
{
    // 初始化父类
    if (!Scene::init()) {
        return false;
    }

    // 获取可视区域大小和原点
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 添加背景图片
    Sprite* pBg = Sprite::createWithSpriteFrameName("ui_S_Bg.png");
    pBg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(pBg);

    // 创建和配置页面视图
    m_pPage = PageView::create();
    this->addChild(m_pPage);
    m_pPage->setDirection(ScrollView::Direction::HORIZONTAL);
    m_pPage->setPosition(Vec2(200, 200));
    m_pPage->setContentSize(Size(500, 350));

    // 添加页面到页面视图
    for (int i = 0; i < 4; i++) {
        Layout* pLayout = Layout::create();
        pLayout->setContentSize(Size(500, 350));
        ImageView* pImage = ImageView::create(StringUtils::format("ui_map_%02d.png", i + 1), Widget::TextureResType::PLIST);
        pLayout->addChild(pImage);
        pImage->setAnchorPoint(Vec2(0, 0));

        // 获取配置数据并可能添加额外的元素到布局

        m_pPage->addChild(pLayout);
    }

    // 创建和配置开始按钮
    m_pStartButton = Button::create("Menu/startNor.png", "Menu/startSel.png", "", Widget::TextureResType::LOCAL);
    m_pStartButton->addTouchEventListener(CC_CALLBACK_1(CLevelSelScene::onButtonClick, this));
    this->addChild(m_pStartButton);
    m_pStartButton->setPosition(Vec2(origin.x + visibleSize.width / 2, 120));

    // 创建和配置返回按钮
    m_pBackButton = Button::create("Menu/BackButtonNor.png", "Menu/BackButtonSel.png", "", Widget::TextureResType::LOCAL);
    m_pBackButton->addTouchEventListener(CC_CALLBACK_1(CLevelSelScene::onButtonClick, this));
    this->addChild(m_pBackButton);
    m_pBackButton->setPosition(Vec2(origin.x + m_pBackButton->getContentSize().width / 2, origin.y + visibleSize.height - m_pBackButton->getContentSize().height / 2));

    return true;
}

// 按钮点击事件处理函数
void CLevelSelScene::onButtonClick(Ref* pSender)
{
    // 播放点击音效
    //AudioEngine::play2d("Menu/click.mp3", false);

    // 开始按钮逻辑
    if (pSender == m_pStartButton) {
        CDynamicDt::getInstance()->setLevelID(m_pPage->getCurrentPageIndex() + 1001);
        CGameScene::destroy();
        Director::getInstance()->replaceScene(TransitionFade::create(1, CGameScene::getInstance()));
    }
    // 返回按钮逻辑
    else if (pSender == m_pBackButton) {
        // 返回菜单场景
        Director::getInstance()->replaceScene(TransitionFade::create(1, CGameMenu::create()));
    }
}
