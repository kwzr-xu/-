// ������Ҫ��ͷ�ļ�
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "LoadingScene.h"
#include "LoadData.h"

// ����ѡ�����Ƶ���棬������Ӧ��ͷ�ļ���ʹ����Ӧ�������ռ�
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

// ʹ�� cocos2d �����ռ�
USING_NS_CC;

// ������Ʒֱ��ʺͲ�ͬ��С����Ļ�ֱ���
static cocos2d::Size designResolutionSize = cocos2d::Size(960, 640);
static cocos2d::Size smallResolutionSize = cocos2d::Size(960, 640);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(960, 640);
static cocos2d::Size largeResolutionSize = cocos2d::Size(960, 640);

// AppDelegate �Ĺ��캯������������
AppDelegate::AppDelegate() { }
AppDelegate::~AppDelegate() {
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// ��ʼ�� OpenGL ����������
void AppDelegate::initGLContextAttrs() {
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
    GLView::setGLContextAttrs(glContextAttrs);
}

// ע�����е��������Ŀǰ�������Ϊ��
static int register_all_packages() {
    return 0;
}

// Ӧ�ó�����������õĺ���
bool AppDelegate::applicationDidFinishLaunching() {
    CLoadData* pData = new CLoadData();
    delete(pData);
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    // ��ʼ�� OpenGL ��ͼ
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("CarrotFantasy", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("CarrotFantasy");
#endif
        director->setOpenGLView(glview);
    }

    // ������ʾ֡�ʺͶ������
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60);

    // ������Ʒֱ��ʺ�������������
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    if (frameSize.height > mediumResolutionSize.height) {
        director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
    }
    else if (frameSize.height > smallResolutionSize.height) {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
    }
    else {
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
    }

    register_all_packages();

    // ���������г���
    auto scene = CLoadingScene::createWithData("Menu");
    director->runWithScene(scene);

    return true;
}

// ��Ӧ�ó�������̨ʱ����
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// ��Ӧ�ó������ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}