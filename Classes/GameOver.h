// ��Ϸ�����ඨ��
#ifndef __GameOver_H__
#define __GameOver_H__

#include "cocos2d.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace ui;

class CGameOver :public Node
{
public:
    CGameOver();
    ~CGameOver();
    virtual bool init();
    CREATE_FUNC(CGameOver);
public:
    void createGameSuccess(); // ������Ϸ�ɹ�����ĺ���
    void createGameOver();    // ������Ϸʧ�ܽ���ĺ���
private:
    char* G2U(const char* gb2312); // GB2312��UTF-8�ı���ת������
    void click(Ref* pSender);      // ��ť����¼�������
private:
    bool isWin;                    // ��Ϸ�Ƿ�ʤ����־
    bool isFail;                   // ��Ϸ�Ƿ�ʧ�ܱ�־
    Button* m_pLevelSel;           // �ؿ�ѡ��ť
    Button* m_pTryAgain;           // ����һ�ΰ�ť
};

#endif