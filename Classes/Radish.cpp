#include "Radish.h" // ���� CRadish �������

// ���캯��
CRadish::CRadish()
    : m_nHp(10),        // ��ʼ������ֵΪ 10
    m_nHpState(1)     // ��ʼ������״̬Ϊ 1
{
    // ���캯��������
}

// ��������
CRadish::~CRadish()
{
    // �������������壬������Դ����
}

// ��ʼ������
bool CRadish::init()
{
    // ���ȵ��û���� init ����
    if (!Node::init()) {
        return false; // ��������ʼ��ʧ�ܣ����� false
    }

    // ��������״̬�����ܲ���ͼ����
    m_pImage = Sprite::createWithSpriteFrameName(StringUtils::format("ui_luobo_%02d.png", m_nHpState));
    m_pImage->setAnchorPoint(Vec2(0.5, 0)); // ����ê��
    this->addChild(m_pImage); // ��ͼ�������Ϊ�ӽڵ�

    // ������ʾ����ֵ��Ѫ������
    m_pHpBar = Sprite::createWithSpriteFrameName(StringUtils::format("hp_%d.png", m_nHp));
    m_pHpBar->setPosition(m_pImage->getPositionX() + 50, m_pImage->getPositionY() + 50); // ����Ѫ��λ��
    this->addChild(m_pHpBar); // ��Ѫ���������Ϊ�ӽڵ�

    return true; // ��ʼ���ɹ�
}