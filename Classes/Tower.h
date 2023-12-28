// ��̨�ඨ��
#ifndef __Tower_H__
#define __Tower_H__

#include "cocos2d.h"
#include"DataClass.h"
#include"ConfigMgr.h"
#include"Enemy.h"
#include"Bullet.h"
using namespace std;
USING_NS_CC;

// ��̨״̬ö��
enum {
    E_STATE_NORMAL, // ����״̬
    E_STATE_FIRE    // ����״̬
};

// CTower ��̳��� Node �࣬���ڴ�����Ϸ����̨����Ϊ
class CTower :public Node
{
public:
    CTower(); // ���캯��
    ~CTower(); // ��������
    bool initWithData(int nTowerID); // ʹ�����ݳ�ʼ����̨
    void upgrade(); // ������̨
    static CTower* createWithData(int nTowerID); // ������̨ʵ��
    CC_SYNTHESIZE(int, m_nCurGrade, CurGrade); // ��ǰ�ȼ�
    CC_SYNTHESIZE(int, m_nSaleCoin, SaleCoin); // ���۽��
    CC_SYNTHESIZE(int, m_nUpGradeCoin, UpGradeCoin); // �������

private:
    void search(float delta); // ��������
    void fire(float Dt); // ��̨����
private:
    int i; // ��������
    int m_nCurTowerID; // ��ǰ��̨ID
    int m_nEnemyIndex; // ��������
    float m_fDisSq; // ���˾���ƽ��
    Vec2 m_nDir; // ����
    int nCurState; // ��ǰ״̬
    Sprite* m_pImage; // ��̨����
    STowerDt* m_pTowerDt; // ��̨����
};

#endif