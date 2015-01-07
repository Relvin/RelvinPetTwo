//
//  AnalysicsManager.cpp
//  MyGame
//
//  Created by panhong on 14-9-12.
//
//

#include "AnalysicsManager.h"
#include "Support.h"
#include "GameSession.h"
#include "Role.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AndroidAnalytics.h"
#endif

AnalysicsManager * AnalysicsManager::ms_pSharedAnalytics = NULL;

AnalysicsManager * AnalysicsManager::sharedAnalyticsMgr()
{
    if (ms_pSharedAnalytics == NULL)
    {
        ms_pSharedAnalytics = new AnalysicsManager();
    }
    
    return ms_pSharedAnalytics;
}

AnalysicsManager::AnalysicsManager() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    umeng = new UMAnalytics();
    umeng->InitAnalyticsSDK();
    
    
    talkingData = new GameTalkingAnalytics();
    talkingData->InitAnalyticsSDK();
#endif
    m_dwUserId = 0; //CGameSession::GetRole()->GetdwAccountId();
    m_strServerName = "";
}

AnalysicsManager::~AnalysicsManager()
{
}

// 设置用户ID
void AnalysicsManager::SetUserId(uint32 _dwId) {
    m_dwUserId = _dwId;
}

void AnalysicsManager::SendEvent( const char * eventID )
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if (m_dwUserId) {
        char szBuf[128];
        snprintf(szBuf, 128, "%d", m_dwUserId);
        
        talkingData->SendEvent(eventID, szBuf);
    }

    umeng->SendEvent(eventID, "");
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AndroidAnalytics::getInstance()->SendEvent(eventID, "");
#endif
}
void 	AnalysicsManager::SendEvent( const char * eventID, const char * edata )
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if (m_dwUserId) {
        char szBuf[128];
        snprintf(szBuf, 128, "%d", m_dwUserId);
        
        talkingData->SendEvent(eventID, szBuf, edata);
    }
    
    UMAnalytics *umeng = new UMAnalytics();
    umeng->SendEvent(eventID, "", edata);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AndroidAnalytics::getInstance()->SendEvent(eventID, edata);
#endif
}

void AnalysicsManager::SendBeginPageView(const char *pageName) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    umeng->SendBeginPageView(pageName);
#endif
}

void AnalysicsManager::SendEngPageView(const char *pageName) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    umeng->SendEndPageView(pageName);
#endif
}

void AnalysicsManager::reportPlayerInfo(int roleLv, const char *serverName, const char *roleId, int _type) {
	CCLog("AnalysicsManager::reportPlayerInfo id=%s", roleId);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if (strcmp(serverName, "") != 0) {
        m_strServerName = serverName;
    }
    
    if (m_dwUserId && (!m_strServerName.empty() && m_strServerName != "")) {
        char szBuf[128];
        snprintf(szBuf, 128, "%d", m_dwUserId);
        
        talkingData->ReportPlayerInfo(szBuf, roleLv, serverName, _type);
    }
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	char extra[256]={0};
	sprintf(extra, "Type=%d|ServerName=%s", _type, serverName);
    char szBuf[128];
    snprintf(szBuf, 128, "%d", m_dwUserId);
	AndroidAnalytics::getInstance()->ReportPlayerInfo(szBuf, roleLv, extra);
#endif
}

void AnalysicsManager::beginMission(const char *_missionName) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    talkingData->ReportMission(_missionName, 0, "");
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AndroidAnalytics::getInstance()->StartLevel(_missionName);
#endif
}

void AnalysicsManager::completeMission(const char *_missionName) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    talkingData->ReportMission(_missionName, 1, "");
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AndroidAnalytics::getInstance()->FinishLevel(_missionName);
#endif
}

void AnalysicsManager::failMission(const char *_missionName, const char* reason) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    talkingData->ReportMission(_missionName, -1, reason);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	AndroidAnalytics::getInstance()->FailLevel(_missionName, reason);
#endif
}

void AnalysicsManager::onPurchase(const char *goodsName, int num, int price) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    talkingData->OnPurchase(goodsName, num, price);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	CCLog("AnalysicsManager::onPurchase todo");
#endif
}


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
UMAnalytics* AnalysicsManager::getUMAnalytics()
{
    return umeng;
}
#endif

void AnalysicsManager::updateUmengOnlineParams()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if (umeng) {
        umeng->updateUmengOnlineParams();
    }
#endif
}

