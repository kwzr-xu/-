#include"GameOver.h"
#include"DynamicDt.h"
#include"GameScene.h"

// ��Ϸ������Ĺ��캯��
CGameOver::CGameOver()
{
}

// ��Ϸ���������������
CGameOver::~CGameOver()
{
}

// ��ʼ������
bool CGameOver::init()
{
    // ��ʼ������
    if (!Node::init()) {
        return false;
    }
    // ������Ϸ���������Ӧ�Ľ�������
    if (CGameScene::getInstance()->getOverOrEnd() == "Over") {
        this->createGameOver();
    }
    else if (CGameScene::getInstance()->getOverOrEnd() == "End") {
        this->createGameSuccess();
    }
    return true;
}

// ������Ϸ�ɹ�����
void CGameOver::createGameSuccess()
{
    // ��ӱ���ͼƬ
    Sprite* pBg = Sprite::createWithSpriteFrameName("ui_GameWinNew.png");
    this->addChild(pBg);

    // ��Ӽ���ͼƬ
    Sprite* pJitui = Sprite::createWithSpriteFrameName("JiTui.png");
    pJitui->setPosition(this->getPositionX() - pJitui->getContentSize().width - 15, 23);
    this->addChild(pJitui);

    // ��Ӳ��α�ǩ
    Label* m_pWaveLabel = Label::createWithTTF(StringUtils::format("0 %d", CDynamicDt::getInstance()->getWaveIndex()), "fonts/comicbd.ttf", 30);
    m_pWaveLabel->setPosition(this->getPositionX() - 5, 23);
    m_pWaveLabel->setColor(Color3B(255, 255, 224));
    this->addChild(m_pWaveLabel);

    // ��ӹ���ͼƬ
    Sprite* pGuaiWu = Sprite::createWithSpriteFrameName("GuaiWu.png");
    pGuaiWu->setPosition(this->getPositionX() + pGuaiWu->getContentSize().width + 10, 23);
    this->addChild(pGuaiWu);

    // ��ӵ�ǰ�ؿ���ǩ
    Label* m_pCurLevel = Label::createWithTTF(StringUtils::format("%s:0%d", this->G2U("�ؿ�"), CDynamicDt::getInstance()->getLevelID() - 1000), "fonts/msyhbd.ttc", 15);
    m_pCurLevel->setPosition(this->getPositionX() - 75, -17);
    this->addChild(m_pCurLevel);

    // ���ð��ͼƬ
    Sprite* pMaoXian = Sprite::createWithSpriteFrameName("DangQian.png");
    pMaoXian->setPosition(this->getPositionX() + 25, -17);
    this->addChild(pMaoXian);

    // ��ӹؿ�ѡ��ť
    m_pLevelSel = Button::create("2.png", "0.png", "", Widget::TextureResType::PLIST);
    m_pLevelSel->setPosition(Vec2(this->getPositionX() - m_pLevelSel->getContentSize().width / 2 - 20, this->getPositionY() - 65));
    m_pLevelSel->addClickEventListener(CC_CALLBACK_1(CGameOver::click, this));
    this->addChild(m_pLevelSel);

    // �������һ�ΰ�ť
    m_pTryAgain = Button::create("5.png", "3.png", "", Widget::TextureResType::PLIST);
    m_pTryAgain->setPosition(Vec2(this->getPositionX() + m_pLevelSel->getContentSize().width / 2 - 10, this->getPositionY() - 65));
    m_pTryAgain->addClickEventListener(CC_CALLBACK_1(CGameOver::click, this));
    this->addChild(m_pTryAgain);

    // �����ܲ��Ľ���״����ʾ��ͬ���ܲ�ͼƬ
    if (CDynamicDt::getInstance()->getRadishHp() == 10) {
        Sprite* pRadish = Sprite::createWithSpriteFrameName("Gold.png");
        pRadish->setPosition(this->getPositionX() - 5, 100);
        this->addChild(pRadish);
    }
    else if (CDynamicDt::getInstance()->getRadishHp() <= 9 && CDynamicDt::getInstance()->getRadishHp() >= 5) {
        Sprite* pRadish = Sprite::createWithSpriteFrameName("Sliver.png");
        pRadish->setPosition(this->getPositionX() - 5, 100);
        this->addChild(pRadish);
    }
    else if (CDynamicDt::getInstance()->getRadishHp() <= 4) {
        Sprite* pRadish = Sprite::createWithSpriteFrameName("Normal.png");
        pRadish->setPosition(this->getPositionX() - 5, 100);
        this->addChild(pRadish);
    }
}

// ������Ϸ��������
void CGameOver::createGameOver()
{
    // ��ӱ���ͼƬ
    Sprite* pBg = Sprite::createWithSpriteFrameName("ui_GameOverNew.png");
    this->addChild(pBg);

    // ��Ӽ���ͼƬ
    Sprite* pJitui = Sprite::createWithSpriteFrameName("JiTui.png");
    pJitui->setPosition(this->getPositionX() - pJitui->getContentSize().width - 15, 17);
    this->addChild(pJitui);

    // ��Ӳ��α�ǩ
    Label* m_pWaveLabel = Label::createWithTTF(StringUtils::format("0 %d", CDynamicDt::getInstance()->getWaveIndex()), "fonts/comicbd.ttf", 30);
    m_pWaveLabel->setPosition(this->getPositionX() - 15, 17);
    m_pWaveLabel->setColor(Color3B(255, 255, 224));
    this->addChild(m_pWaveLabel);

    // ��ӹ���ͼƬ
    Sprite* pGuaiWu = Sprite::createWithSpriteFrameName("GuaiWu.png");
    pGuaiWu->setPosition(this->getPositionX() + pGuaiWu->getContentSize().width, 17);
    this->addChild(pGuaiWu);

    // ��ӵ�ǰ�ؿ���ǩ
    Label* m_pCurLevel = Label::createWithTTF(StringUtils::format("%s:0%d", this->G2U("�ؿ�"), CDynamicDt::getInstance()->getLevelID() - 1000), "fonts/msyhbd.ttc", 15);
    m_pCurLevel->setPosition(this->getPositionX() - 75, -20);
    this->addChild(m_pCurLevel);

    // ���ð��ͼƬ
    Sprite* pMaoXian = Sprite::createWithSpriteFrameName("DangQian.png");
    pMaoXian->setPosition(this->getPositionX() + 25, -20);
    this->addChild(pMaoXian);

    // ��ӹؿ�ѡ��ť
    m_pLevelSel = Button::create("2.png", "0.png", "", Widget::TextureResType::PLIST);
    m_pLevelSel->setPosition(Vec2(this->getPositionX() - m_pLevelSel->getContentSize().width / 2 - 20, this->getPositionY() - 65));
    m_pLevelSel->addClickEventListener(CC_CALLBACK_1(CGameOver::click, this));
    this->addChild(m_pLevelSel);

    // �������һ�ΰ�ť
    m_pTryAgain = Button::create("5.png", "3.png", "", Widget::TextureResType::PLIST);
    m_pTryAgain->setPosition(Vec2(this->getPositionX() + m_pLevelSel->getContentSize().width / 2 - 10, this->getPositionY() - 65));
    m_pTryAgain->addClickEventListener(CC_CALLBACK_1(CGameOver::click, this));
    this->addChild(m_pTryAgain);
}

// ��GB2312����ת��ΪUTF-8����
char* CGameOver::G2U(const char* gb2312)
{
    int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);
    len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return str;
}

// ����ť����¼�
void CGameOver::click(Ref* pSender)
{
    // ��ť��������߼�
}