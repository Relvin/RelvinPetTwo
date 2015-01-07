
#include "NativeModule.h"
#include "MusicCtrl.h"
#include "SimpleAudioEngine.h"
#include "Modules.h"
#include "Support.h"
#include "GameSession.h"
#include "StartGameLayer.h"
#include "MailDataMgr.h"

static void pauseMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CMusicCtrl::PauseAllEffect();
}

static void resumeMusic()
{
	if(CMusicCtrl::GetIsMusicOn())
	{
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
    CMusicCtrl::ResumeAllEffect();
}

static void doNativeLogin(std::string uid)
{
    StartGameLayer::GetCurLayer()->login("", "", uid.c_str());
}

static void doNativeLogout()
{
    CGameSession::BackToLogin();
}

static void onShareSuccess()
{
    CCLog("NativeModule onShareSuccess");
    CGameSession::SendFriendShareRequest();
    CMailDataMgr::Get()->CloseShareFrameLayer();
}

NativeModule::NativeModule()
{
    pthread_mutex_init (&mutex,NULL);
    cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector((cocos2d::SEL_SCHEDULE)&NativeModule::processCalls, this, 0.1f, kCCRepeatForever, 0.0f, false);
}

void NativeModule::processCalls(float dt)
{
	Request result;
    while(popResult(result))
    {
        std::string action = result.getString(KEY_ACTION);
	    CCLog("NativeModule::processCalls action=%s", action.c_str());
    	if(action == ACT_LOGIN_RESULT)
    	{
    		doNativeLogin(result.getString(KEY_UID));
    	}else if(action == ACT_LOGOUT_RESULT)
    	{
    		doNativeLogout();
    	}else if(action == ACT_EXIT_RESULT)
    	{
    		cocos2d::CCDirector::sharedDirector()->end();
    	}else if(action == ACT_NATIVE_SHARE_SUCCESS)
        {
            onShareSuccess();
        }else if (action == "NetworkDisconnected")
        {
            Support::sharedInstance()->networkDis();
        }
    }
}

void NativeModule::pushResult(Request request)
{
    pthread_mutex_lock (&mutex);
    mResults.push_back(request);
    pthread_mutex_unlock (&mutex);
}

bool NativeModule::popResult(Request &request)
{
    if(mResults.size() <= 0)
    {
        return false;
    }
    pthread_mutex_lock (&mutex);
    if(mResults.size() <= 0)
    {
        pthread_mutex_unlock (&mutex);
        return false;
    }
    // fifo
    request = mResults.front();
    mResults.erase(mResults.begin());
    pthread_mutex_unlock (&mutex);
    return true;
}

std::string NativeModule::onCall(std::string action, std::string params)
{
	if(action == ACT_NATIVE_PAUSE_MUSIC)
    {
    	pauseMusic();
		return "";
    }else if(action == ACT_NATIVE_RESUME_MUSIC)
    {
    	resumeMusic();
		return "";
    }
	CCLog("NativeModule::onCall queued action:%s, params:%s", action.c_str(), params.c_str());
	Request result = Request(params.c_str());
    result.insert(KEY_ACTION, action);
    pushResult(result);
    return "";
}

