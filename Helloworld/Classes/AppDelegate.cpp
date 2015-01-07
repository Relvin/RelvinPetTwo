//
//  HelloWorldAppDelegate.cpp
//  HelloWorld
//
//  Created by long on 13-7-10.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.}
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "StartGameScene.h"
#include "NetClient.h"
#include "ClientPacketHandler.h"
#include "GameStateManager.h"
#include "BackCtrl.h"
#include "support/zip_support/ZipUtils.h"
#include "VersionCtrl.h"
#include "Support.h"
#include "MusicCtrl.h"
#include "sound_system_fmod.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform_android.h"
#include "PlatformMgr.h"
#include "NativeModule.h"
#endif

#include "DirOperate.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
:m_netClient(new CNetClient)
{

}

AppDelegate::~AppDelegate()
{
    CClientPacketHandler::sharedInstance()->UnInit();
    BackCtrl::UnInit();
    //[2014-02-10] add by Juniechu, 防止SimpleAudioEngine异常crash，有没有用不知道，精灵1及其他项目会因为音乐crash，加上这个保险~}
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->end();
    } else {
        SoundSystem::SoundSystemFmod::getInstance()->end();
    }
    delete m_netClient;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    if (Support::sharedInstance()->getScreenHWRadio() >= 1.5) {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(320, 480, kResolutionFixedWidth);
    } else {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(320, 480, kResolutionFixedHeight);
    }
    
    CCLOG("winSize: [%f, %f]", CCDirector::sharedDirector()->getWinSize().width, CCDirector::sharedDirector()->getWinSize().height);
    CCLOG("ScreenSize: [%f, %f]", CCDirector::sharedDirector()->getVisibleSize().width, CCDirector::sharedDirector()->getVisibleSize().height);
    
    pDirector->setContentScaleFactor(2);
    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 45);

    CClientPacketHandler::sharedInstance();
    BackCtrl::Init();
    
    // 此处需要增加判断，更新版本后，应该使用ipa的csv资源，如果不判断，默认由于false，会使用下载的资源}
    VersionCtrl vCtrl;
    if ( vCtrl.checkUseWhichResource() ) {
        DirOperate::DelFile(CCFileUtils::sharedFileUtils()->getWritablePath().c_str());
    }
    
    CCFileUtils::sharedFileUtils()->addSearchPath( CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), true );
    
    GameStateManager::sharedManager()->Initialize();
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") != 0) {
        SoundSystem::SoundSystemFmod::getInstance()->start();
    }
    
    // create a scene. it's an autorelease object
    // 128b72ec55cd18355758c471ba1e6e75
    ZipUtils::ccSetPvrEncryptionKeyPart(0, 0x128b72ec);
    ZipUtils::ccSetPvrEncryptionKeyPart(1, 0x55cd1835);
    ZipUtils::ccSetPvrEncryptionKeyPart(2, 0x5758c471);
    ZipUtils::ccSetPvrEncryptionKeyPart(3, 0xba1e6e75);
    
    CCScene* pScene = StartGameScene::scene();

    Support::sharedInstance()->setSplashGone();
    // run
    pDirector->runWithScene(pScene);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    CCLog("AppDelegate::doGameInit addModule");
    static NativeModule nativeModule;
    platform::PlatformMgr::getInstance()->addModule(&nativeModule);
#endif

    Support::sharedInstance()->setUmengDataAfterUmengUpdateCallBack();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    } else {
        SoundSystem::SoundSystemFmod::getInstance()->onDidEnterBackground();
    }
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") == 0) {
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    } else {
        SoundSystem::SoundSystemFmod::getInstance()->onWillEnterForeground();
    }
}
