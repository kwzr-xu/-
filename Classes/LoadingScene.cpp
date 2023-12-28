//加载界面
#include"LoadingScene.h"
#include"ResDtMgr.h"
#include"GameMenu.h"
#include "audio/include/AudioEngine.h"
#include"LevelSelScene.h"
#include"GameScene.h"
#include"DynamicDt.h"
#include"ConfigMgr.h"

using namespace cocos2d;

// 构造函数
CLoadingScene::CLoadingScene()
    :m_nState(0), m_nCurIndex(0), m_nCount(0), m_nResTotalCount(0),
    isCommonFinish(false), isMenuFinish(false) {
}

// 析构函数
CLoadingScene::~CLoadingScene() {
}

// 初始化函数，用于设置加载场景
bool CLoadingScene::initWithData(string strSceneName) {
    // 检查场景初始化是否成功
    if (!Scene::init()) {
        return false;
    }

    // 保存下一个场景的名称
    strNextSceneName = strSceneName;

    // 获取屏幕尺寸和原点坐标
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 加载通用资源和指定场景的资源
    m_pComDt = CResDtMgr::getInstance()->getData("Common");
    m_pSceneDt = CResDtMgr::getInstance()->getData(strSceneName);

    // 计算总资源数量
    m_nResTotalCount += (m_pComDt->m_VecPng.size() + m_pComDt->m_VecPlist.size() + m_pComDt->m_VecAudio.size());
    m_nResTotalCount += (m_pSceneDt->m_VecPng.size() + m_pSceneDt->m_VecPlist.size() + m_pSceneDt->m_VecAudio.size());

    // 设置背景图像
    //Sprite* pBg = Sprite::create("Default-Landscape_ipad.png");
    //pBg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    //this->addChild(pBg);

    // 设置进度条背景
    //Sprite* pProgressBg = Sprite::create("Common/ui_ProgressBar_01.png");
    //pProgressBg->setPosition(origin.x + visibleSize.width / 2, origin.y + pProgressBg->getContentSize().height / 2 + 50);
    //this->addChild(pProgressBg);

    // 设置进度条
    //m_pProgress = ProgressTimer::create(Sprite::create("Common/ui_ProgressBar_02.png"));
    //m_pProgress->setPosition(origin.x + visibleSize.width / 2, origin.y + pProgressBg->getContentSize().height / 2 + 50);
    //this->addChild(m_pProgress);
    //m_pProgress->setType(ProgressTimer::Type::BAR);
    //m_pProgress->setMidpoint(Vec2(0, 0.5));
    //m_pProgress->setBarChangeRate(Vec2(1, 0));

    // 启动更新函数
    this->scheduleUpdate();
    return true;
}

// 创建带有数据的加载场景
CLoadingScene* CLoadingScene::createWithData(string strSceneName) {
    CLoadingScene* pLoadingScene = new CLoadingScene();
    if (pLoadingScene && pLoadingScene->initWithData(strSceneName)) {
        pLoadingScene->autorelease();
        return pLoadingScene;
    }
    CC_SAFE_DELETE(pLoadingScene);
    return nullptr;
}

// 更新函数，用于加载资源
void CLoadingScene::update(float delta) {
    if (m_nCount < m_nResTotalCount) {
        // 加载通用资源
        if (!isCommonFinish) {
            this->loadRes(m_pComDt);
        }
        // 加载场景特定资源
        else {
            this->loadRes(m_pSceneDt);
        }

        // 更新进度条
        //float fPercent = (float)m_nCount * 100 / m_nResTotalCount;
        //m_pProgress->setPercentage(fPercent);
    }
    else {
        // 资源加载完毕，取消更新，切换到下一个场景
        this->unscheduleUpdate();
        if ("Menu" == strNextSceneName) {
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, CGameMenu::create()));
        }
        if ("Game" == strNextSceneName) {
            CGameScene::destory();
            Director::getInstance()->replaceScene(TransitionFade::create(1, CGameScene::getInstance()));
        }
    }
}

void CLoadingScene::loadRes(SResDt * pDt)
{
	if (0 == m_nState) {
		if (m_nCurIndex>=pDt->m_VecPng.size()) {
			m_nCurIndex = 0;
			m_nState = 1;//加载plist的状态
			return;
		}
		string strPath = pDt->m_VecPng[m_nCurIndex];
		TextureCache* pCache = Director::getInstance()->getTextureCache();
		pCache->addImage(strPath);
		m_nCurIndex++;
		m_nCount++;

	}
	if (1 == m_nState) {
		if (m_nCurIndex >= pDt->m_VecPlist.size()) {
			m_nCurIndex = 0;
			m_nState = 2;//加载Audio的状态
			return;
		}
		SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
		pCache->addSpriteFramesWithFile(pDt->m_VecPlist[m_nCurIndex]);
		m_nCurIndex++;
		m_nCount++;

	}
	if (2 == m_nState) {
		if (m_nCurIndex >= pDt->m_VecAudio.size()) {
			m_nCurIndex = 0;
			m_nState = 0;//加载Audio的状态
			isCommonFinish = true;
			return;
		}
		AudioEngine::preload(pDt->m_VecAudio[m_nCurIndex].c_str());
		m_nCurIndex++;
		m_nCount++;

	}
}
