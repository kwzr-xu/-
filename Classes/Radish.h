#ifndef __RADISH_H__ // ��ֹͷ�ļ��ظ�����
#define __RADISH_H__

#include "cocos2d.h" // ���� Cocos2d-x ��ܵĺ���ͷ�ļ�
USING_NS_CC; // ʹ�� Cocos2d-x �����ռ�
using namespace std; // ʹ�ñ�׼�������ռ�

// ����һ�� CRadish �࣬�̳��� Cocos2d-x �� Node ��
class CRadish : public Node
{
public:
    CRadish();  // ���캯��
    ~CRadish(); // ��������

    virtual bool init(); // ��ʼ���������������ö���ĳ�ʼ״̬

    CREATE_FUNC(CRadish); // �꣬�ṩ��һ����̬�Ĵ�������ķ���

    // �������ɻ�ȡ�������ܲ�����ֵ��״̬�ķ����ĺ�
    CC_SYNTHESIZE(int, m_nHp, Hp);         // ����ֵ
    CC_SYNTHESIZE(int, m_nHpState, HpState); // ����״̬

public:
    Sprite* m_pHpBar; // ��ʾѪ���ľ���
    Sprite* m_pImage; // ��ʾ�ܲ�ͼ��ľ���
};

#endif // __RADISH_H__
