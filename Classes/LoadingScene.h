#ifndef __LoadingScene_H__
#define __LoadingScene_H__


#include "cocos2d.h"
#include "ResDtMgr.h"

USING_NS_CC;
class CLoadingScene:public Scene
{
public:
	CLoadingScene();
	~CLoadingScene();
	bool initWithData(string strSceneName);
	
	static CLoadingScene* createWithData(string strSceneName);
private:
	void update(float delta);
	void loadRes(SResDt* pDt);
private:
	string strNextSceneName;
	bool isCommonFinish;
	bool isMenuFinish;
	SResDt* m_pComDt;
	SResDt* m_pSceneDt;
	int m_nState;
	int m_nCurIndex;
	int m_nCount;
	int m_nResTotalCount;
	ProgressTimer* m_pProgress;
};

#endif
