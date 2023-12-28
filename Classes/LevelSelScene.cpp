#include "LevelSelScene.h"
#include "DynamicDt.h"
#include "GameScene.h"
//#include "LoadingScene.h"
#include "ConfigMgr.h"
#include "GameMenu.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

// �ؿ�ѡ�񳡾��Ĺ��캯��
CLevelSelScene::CLevelSelScene()
    :levelID(0) // ��ʼ���ؿ�ID
{
}

// �ؿ�ѡ�񳡾�����������
CLevelSelScene::~CLevelSelScene()
{
}

// ��ʼ������
bool CLevelSelScene::init()
{
    // ��ʼ������
    if (!Scene::init()) {
        return false;
    }

    // ��ȡ���������С��ԭ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ��ӱ���ͼƬ
    Sprite* pBg = Sprite::createWithSpriteFrameName("ui_S_Bg.png");
    pBg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(pBg);

    // ����������ҳ����ͼ
    m_pPage = PageView::create();
    this->addChild(m_pPage);
    m_pPage->setDirection(ScrollView::Direction::HORIZONTAL);
    m_pPage->setPosition(Vec2(200, 200));
    m_pPage->setContentSize(Size(500, 350));

    // ���ҳ�浽ҳ����ͼ
    for (int i = 0; i < 4; i++) {
        Layout* pLayout = Layout::create();
        pLayout->setContentSize(Size(500, 350));
        ImageView* pImage = ImageView::create(StringUtils::format("ui_map_%02d.png", i + 1), Widget::TextureResType::PLIST);
        pLayout->addChild(pImage);
        pImage->setAnchorPoint(Vec2(0, 0));

        // ��ȡ�������ݲ�������Ӷ����Ԫ�ص�����

        m_pPage->addChild(pLayout);
    }

    // ���������ÿ�ʼ��ť
    m_pStartButton = Button::create("Menu/startNor.png", "Menu/startSel.png", "", Widget::TextureResType::LOCAL);
    m_pStartButton->addTouchEventListener(CC_CALLBACK_1(CLevelSelScene::onButtonClick, this));
    this->addChild(m_pStartButton);
    m_pStartButton->setPosition(Vec2(origin.x + visibleSize.width / 2, 120));

    // ���������÷��ذ�ť
    m_pBackButton = Button::create("Menu/BackButtonNor.png", "Menu/BackButtonSel.png", "", Widget::TextureResType::LOCAL);
    m_pBackButton->addTouchEventListener(CC_CALLBACK_1(CLevelSelScene::onButtonClick, this));
    this->addChild(m_pBackButton);
    m_pBackButton->setPosition(Vec2(origin.x + m_pBackButton->getContentSize().width / 2, origin.y + visibleSize.height - m_pBackButton->getContentSize().height / 2));

    return true;
}

// ��ť����¼�������
void CLevelSelScene::onButtonClick(Ref* pSender)
{
    // ���ŵ����Ч
    //AudioEngine::play2d("Menu/click.mp3", false);

    // ��ʼ��ť�߼�
    if (pSender == m_pStartButton) {
        CDynamicDt::getInstance()->setLevelID(m_pPage->getCurrentPageIndex() + 1001);
        CGameScene::destroy();
        Director::getInstance()->replaceScene(TransitionFade::create(1, CGameScene::getInstance()));
    }
    // ���ذ�ť�߼�
    else if (pSender == m_pBackButton) {
        // ���ز˵�����
        Director::getInstance()->replaceScene(TransitionFade::create(1, CGameMenu::create()));
    }
}
