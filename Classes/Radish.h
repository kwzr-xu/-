#ifndef __RADISH_H__ // 防止头文件重复包含
#define __RADISH_H__

#include "cocos2d.h" // 引入 Cocos2d-x 框架的核心头文件
USING_NS_CC; // 使用 Cocos2d-x 命名空间
using namespace std; // 使用标准库命名空间

// 定义一个 CRadish 类，继承自 Cocos2d-x 的 Node 类
class CRadish : public Node
{
public:
    CRadish();  // 构造函数
    ~CRadish(); // 析构函数

    virtual bool init(); // 初始化方法，用于设置对象的初始状态

    CREATE_FUNC(CRadish); // 宏，提供了一个静态的创建对象的方法

    // 用于生成获取和设置萝卜生命值和状态的方法的宏
    CC_SYNTHESIZE(int, m_nHp, Hp);         // 生命值
    CC_SYNTHESIZE(int, m_nHpState, HpState); // 生命状态

public:
    Sprite* m_pHpBar; // 表示血条的精灵
    Sprite* m_pImage; // 表示萝卜图像的精灵
};

#endif // __RADISH_H__
