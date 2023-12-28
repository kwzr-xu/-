//���ؽ���
#include"LoadingScene.h"
#include"ResDtMgr.h"
#include"GameMenu.h"
#include "audio/include/AudioEngine.h"
#include"LevelSelScene.h"
#include"GameScene.h"
#include"DynamicDt.h"
#include"ConfigMgr.h"

using namespace cocos2d;

// ���캯��
CLoadingScene::CLoadingScene()
    :m_nState(0), m_nCurIndex(0), m_nCount(0), m_nResTotalCount(0),
    isCommonFinish(false), isMenuFinish(false) {
}

// ��������
CLoadingScene::~CLoadingScene() {
}

// ��ʼ���������������ü��س���
bool CLoadingScene::initWithData(string strSceneName) {
    // ��鳡����ʼ���Ƿ�ɹ�
    if (!Scene::init()) {
        return false;
    }

    // ������һ������������
    strNextSceneName = strSceneName;

    // ��ȡ��Ļ�ߴ��ԭ������
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ����ͨ����Դ��ָ����������Դ
    m_pComDt = CResDtMgr::getInstance()->getData("Common");
    m_pSceneDt = CResDtMgr::getInstance()->getData(strSceneName);

    // ��������Դ����
    m_nResTotalCount += (m_pComDt->m_VecPng.size() + m_pComDt->m_VecPlist.size() + m_pComDt->m_VecAudio.size());
    m_nResTotalCount += (m_pSceneDt->m_VecPng.size() + m_pSceneDt->m_VecPlist.size() + m_pSceneDt->m_VecAudio.size());

    // ���ñ���ͼ��
    //Sprite* pBg = Sprite::create("Default-Landscape_ipad.png");
    //pBg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    //this->addChild(pBg);

    // ���ý���������
    //Sprite* pProgressBg = Sprite::create("Common/ui_ProgressBar_01.png");
    //pProgressBg->setPosition(origin.x + visibleSize.width / 2, origin.y + pProgressBg->getContentSize().height / 2 + 50);
    //this->addChild(pProgressBg);

    // ���ý�����
    //m_pProgress = ProgressTimer::create(Sprite::create("Common/ui_ProgressBar_02.png"));
    //m_pProgress->setPosition(origin.x + visibleSize.width / 2, origin.y + pProgressBg->getContentSize().height / 2 + 50);
    //this->addChild(m_pProgress);
    //m_pProgress->setType(ProgressTimer::Type::BAR);
    //m_pProgress->setMidpoint(Vec2(0, 0.5));
    //m_pProgress->setBarChangeRate(Vec2(1, 0));

    // �������º���
    this->scheduleUpdate();
    return true;
}

// �����������ݵļ��س���
CLoadingScene* CLoadingScene::createWithData(string strSceneName) {
    CLoadingScene* pLoadingScene = new CLoadingScene();
    if (pLoadingScene && pLoadingScene->initWithData(strSceneName)) {
        pLoadingScene->autorelease();
        return pLoadingScene;
    }
    CC_SAFE_DELETE(pLoadingScene);
    return nullptr;
}

// ���º��������ڼ�����Դ
void CLoadingScene::update(float delta) {
    if (m_nCount < m_nResTotalCount) {
        // ����ͨ����Դ
        if (!isCommonFinish) {
            this->loadRes(m_pComDt);
        }
        // ���س����ض���Դ
        else {
            this->loadRes(m_pSceneDt);
        }

        // ���½�����
        //float fPercent = (float)m_nCount * 100 / m_nResTotalCount;
        //m_pProgress->setPercentage(fPercent);
    }
    else {
        // ��Դ������ϣ�ȡ�����£��л�����һ������
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
			m_nState = 1;//����plist��״̬
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
			m_nState = 2;//����Audio��״̬
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
			m_nState = 0;//����Audio��״̬
			isCommonFinish = true;
			return;
		}
		AudioEngine::preload(pDt->m_VecAudio[m_nCurIndex].c_str());
		m_nCurIndex++;
		m_nCount++;

	}
}
