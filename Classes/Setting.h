#ifndef __Setting_H__
#define __Setting_H__


#include "cocos2d.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace std;


class CSetting:public Scene
{
public:
	CSetting();
	~CSetting();
	virtual bool init();

	CREATE_FUNC(CSetting);
private:

};

#endif
