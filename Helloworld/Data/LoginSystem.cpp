//
//  LoginSystem.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-1-17.}
//
//

#include "LoginSystem.h"
#include "StartGameLayer.h"
#include "MainScene.h"
#include "MainLayer.h"
#include "NetClient.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "GlobalData.h"
#include "EnumDefines.h"
#include "CcbManager.h"
#include "CcbAccountLayer.h"
#include "Role.h"
#include "Version.h"

#include "CcbChoosePetLayer.h"
#include "Instruments.h"
#include "CcbNoServiceLayer.h"
#include "Support.h"
#include "BackCtrl.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "BackCtrl.h"

//#include "CcbBegin1Layer.h"
#include "CcbBegin20Layer.h"

#include "GuideData.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform_android.h"
#endif

bool LoginSystem::ConnectToServer(std::string& strIp, int nPort) {
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->End();
    return pNetClient->Connect(strIp.c_str(), nPort);
}

bool LoginSystem::ConnectToLoginServer(std::string strIp, int nPort)
{
    m_byConnectStatus = E_UNCONNECTED;
    m_strLoginIp = strIp;
    m_nLoginPort = nPort;
    
    if (m_byConnectStatus != E_LOGIN_CONNECTED) {
        if (!ConnectToServer(m_strLoginIp, m_nLoginPort)) {
            m_byConnectStatus = E_UNCONNECTED;
            
            ShowNoServiceLayer();
            
            PetLoadingLayer::sharedLayer()->End();
            return false;
        }
    }
    m_byConnectStatus = E_LOGIN_CONNECTED;
    PetLoadingLayer::sharedLayer()->End();
    return true;
}

std::string LoginSystem::getUid()
{
    std::string strUid = "invalid";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    strUid = Support::sharedInstance()->readUdidFromKeyChain();
    
    CCLog("StartGameLayer || get udid from keychain:%s", strUid.c_str());
    
    if ( strUid.empty() || strUid == "" || strUid.length() < 10 ) {
        Support::sharedInstance()->saveUdidToKeyChain();
        strUid = Support::sharedInstance()->readUdidFromKeyChain();
    }
    
    if ( strUid.empty() || strUid == "" || strUid.length() < 10 ) {
        strUid = CCUserDefault::sharedUserDefault()->getStringForKey(D9_UDID);
    }
    
    if ( strUid.empty() || strUid == "" || strUid.length() < 10 ) {
        strUid = Support::sharedInstance()->uniqueId();
        CCUserDefault::sharedUserDefault()->setStringForKey(D9_UDID, strUid);
    }
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    strUid = PlatformGetDeviceId();
#endif
    return strUid;
}

void LoginSystem::StartLogin(std::string strIp, int nPort, uint8 authFlag, std::string strUname, std::string strPwd)
{
    m_byShowServerList = E_FROM_LOGIN;
    
    m_dwCurTimeStamp = 0;
    
    m_strLoginIp = strIp;
    m_nLoginPort = nPort;
    m_byAuthFlag = authFlag;
    m_strUname = strUname;
    m_strPwd = strPwd;

    PetLoadingLayer::sharedLayer()->WaitForPacket();
    ConnectToLoginServer(m_strLoginIp, m_nLoginPort);
    
    /**
     下面这段代码必须加，}
     */
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    
    CGameSession::SendRequestServerList(m_strUname, getUid(), cvtInt2String((int)CUR_GAME_VERSION), Support::sharedInstance()->appChannel());
}

void LoginSystem::SetServerCallback()
{
    if (m_byShowServerList == E_FROM_LOGIN) {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        Support* pApp = Support::sharedInstance();
        switch (m_byAuthFlag) {
            case E_AUTH_FAST: {
                CGameSession::SendGameFastLogin(getUid(), CUR_GAME_VERSION, m_strUname, m_strPwd, m_wAreaId, pApp->deviceType(), pApp->deviceOS(), pApp->appChannel());
                break;
            }
            case E_AUTH_ACCOUNT: {
                CGameSession::SendGameLogin(getUid(), CUR_GAME_VERSION, m_strUname, m_strPwd, m_wAreaId);
                break;
            }
            case E_AUTH_THIRD: {
                CGameSession::SendGameOtherLogin(getUid(), CUR_GAME_VERSION, m_strUname, m_strPwd, m_wAreaId, pApp->deviceType(), pApp->deviceOS(), pApp->appChannel());
                break;
            }
            case E_AUTH_USER: {
                CGameSession::SendUserLoginServer(m_dwUserId, m_wAreaId);
                break;
            }
            default:
                break;
        }
    } else if (m_byShowServerList == E_FROM_SERVER) {
        CCNode* pServerLayer = CcbManager::sharedManager()->LoadCcbServerListLayer();
        StartGameLayer::GetCurLayer()->addChild(pServerLayer, 90, StartGameLayer::E_SERVER_TAG);
    } else {
        return;
    }
}

void LoginSystem::SetGameServerInfo(WorldPacket &packet) {
    uint8 byState;
    
    packet >> byState;
    packet >> m_strGameIp;
    packet >> m_nGamePort;
    
    std::string strDevice;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    strDevice = "iOS";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    strDevice = "Android";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    strDevice = "win32";
#endif
    
    if (byState == E_ERRNO_AUTH_SUCCESS) {
        if (m_byConnectStatus != E_GAME_CONNECTED) {
            if (!ConnectToServer(m_strGameIp, m_nGamePort)) {
                m_byConnectStatus = E_UNCONNECTED;
                PetLoadingLayer::sharedLayer()->End();
                //TODO: 重连}
                return;
            }
        }
        m_byConnectStatus = E_GAME_CONNECTED;
        
        switch (m_byAuthFlag) {
            case E_AUTH_FAST: {
                CGameSession::SendFastAuth(getUid(), CUR_GAME_VERSION, "", "", m_wAreaId, strDevice);
                break;
            }
            case E_AUTH_ACCOUNT: {
                // [2014-01-26] modified by Juniechu, 账号登陆修改为登陆成功后显示账号名在原先登陆按钮上，稍后点击登陆游戏利用账号登陆}
//                CGameSession::SendAccountAuth(getUid(), 20, m_strUname, m_strPwd, m_wAreaId);
                // 已经在得到服务器列表时 RefeashLayer 刷新过账号名}
                if (m_byMode == E_FUCKING_UPPER) {
                    d9_encode_save(D9_ACCOUNT, m_strUname);
                    CCUserDefault::sharedUserDefault()->setStringForKey(D9_PASSWORD, m_strPwd);
                    CcbAccountLayer::GetCurLayer()->HideAccountLayer();
                } else if (m_byMode == E_FUCKING_LOWER) {
                    CGameSession::SendAccountAuth(getUid(), CUR_GAME_VERSION, m_strUname, m_strPwd, m_wAreaId, strDevice);
                }
                break;
            }
            case E_AUTH_THIRD: {
//                CGameSession::SendThirdAuth(getUid(), 20, m_strUname, m_strPwd, m_wAreaId);
                
                // 已经在得到服务器列表时 RefeashLayer 刷新过账号名}
                if (m_byMode == E_FUCKING_LOWER) {
                    CGameSession::SendThirdAuth(getUid(), CUR_GAME_VERSION, m_strUname, m_strPwd, m_wAreaId, strDevice);
                }
                break;
            }
            case E_AUTH_USER: {
                CGameSession::SendUserGameServer(m_dwUserId, m_wAreaId);
                break;
            }
            default:
                break;
        }
        return;
    }
    
    PetLoadingLayer::sharedLayer()->End();
    if (byState == E_ERRNO_AUTH_ACCOUNT_HAVE) {
		CCMessageBox("alread get account", "ERROR");
    } else if (byState == E_ERRNO_AUTH_WRONG_VERSION) {
		CCMessageBox("version error", "ERROR");
    } else if (byState == E_ERRNO_AUTH_NO_SERVER) {
		CCMessageBox("server mantaining", "ERROR");
    } else if (byState == E_ERRNO_AUTH_NO_ACCOUNT) {
		CCMessageBox("account not exist", "ERROR");
    } else if (byState == E_ERRNO_AUTH_WRONG_PWD) {
		CCMessageBox("password error", "ERROR");
    } else if (byState == E_ERRNO_AUTH_NAME_LEN) {
		CCMessageBox("account length error", "ERROR");
    }
    else {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d", byState);
        CCMessageBox(strBuf64, "Error");
    }
    
    m_byConnectStatus = E_UNCONNECTED;
}

void LoginSystem::SetAuthResult(WorldPacket &packet)
{
    uint8 byResult;
    packet >> byResult;
    if (byResult == 0) {
        // 当在登陆界面网络就断掉的情况下，应该仍然跳转到主界面，其余情况则直接断线重连，刷新当前界面}
        if (GlobalData::bReConnectFlag && !StartGameLayer::GetCurLayer()) {
            //从后台切回前台需要将 置回}
            GlobalData::bReConnectFlag = false;
            //刷新当前界面，去除断线重连界面}
            PetLoadingLayer::sharedLayer()->End();
            if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(RECONNECT_TAG)) {
                CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(RECONNECT_TAG);
            }
        } else {
            int curTrigger = CGameSession::GetRole()->GetwGuideTrigger();
            CCLog("trigger is:%d", curTrigger);
            
            if (curTrigger == 1306) {
                GuideData::GetInstance()->setStepId(GuideData::E_GUIDE_END_TRIGGER);
                GuideData::GetInstance()->connectToServer();
            }
            
            CCScene* pScene;
            if (curTrigger == 0) {
                // 新号 未走完新手流程}
//                pScene = CcbBegin1Layer::scene();
                pScene = CcbBegin20Layer::scene();
            } else if (curTrigger == 300 || curTrigger == 400) {
//            } else if (curTrigger == 300) {
//                // 新建名字}
//                pScene = CreateNameScene::scene();
//            } else if (curTrigger == 400) {
                // 选宠物}
                pScene = ChoosePetScene::scene();
            }
            else {
                if (
                    BackCtrl::GetCurSceneIdx() != kPveBattleScene &&    // 战斗界面的重连直接跳转到主界面
                    BackCtrl::GetCurSceneIdx() != 0
                    ) {
                    return;
                } else if (MainLayer::GetCurLayer()) {     // 如果此时在主界面重连，那么不需要replace当前的scene}
                    return;
                }
                CTeam* pTeam = CTeamCtrl::GetCurTeam();
                if (pTeam->getbyLeaderSite() == 0) {
                    pScene = ChoosePetScene::scene();
                    CCDirector::sharedDirector()->replaceScene(pScene);
                    return;
                }
                pScene = MainScene::scene();
                BackCtrl::ClearSceneStack();
            }
            GlobalData::nReconnetCnt = 0;
            GuideData::GetInstance()->Initialize();
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
    } else {
        PetLoadingLayer::sharedLayer()->End();
        if (byResult == E_ERRNO_AUTH_NO_ACCOUNT) {
			CCMessageBox("Account not exist.", "ERROR");
            return;
        }
        snprintf(strBuf64, BUFFER_SIZE_64, "Login Auth Result Error:%d", byResult);
        CCMessageBox(strBuf64, "Error");
    }
}

void LoginSystem::ReConnect()
{
    m_byShowServerList = E_FROM_LOGIN;

    // 时间戳判断}
    CRole* pRole = CGameSession::GetRole();
    m_dwCurTimeStamp = pRole->GetdwWorldInitTime();
    
    // 注意m_dwUserId为0的情况}
    if (ConnectToLoginServer(m_strLoginIp, m_nLoginPort) && m_dwUserId) {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        CGameSession::SendUserLoginServer(m_dwUserId, m_wAreaId);
    }
    
}

void LoginSystem::EnterBackGround()
{
    if (!StartGameLayer::GetCurLayer()) {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
    }
    
    GlobalData::bReConnectFlag = true;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->End();

    pNetClient->setConnectStage(CNetClient::CONN_STATE_DISCONNECT);
}

void LoginSystem::ShowNoServiceLayer()
{
//    if (!GlobalData::bReConnectFlag) {
//        return;
//    }
    if (CCDirector::sharedDirector()->getRunningScene() && CCDirector::sharedDirector()->getRunningScene()->getChildByTag(RECONNECT_TAG)) {
        CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(RECONNECT_TAG);
    }
    PetLoadingLayer::sharedLayer()->End();
    // 如果输错Ip，则会一直在断线重连界面。debug版中在startgame界面去除该layer}
    
    if (!GlobalData::bCloseForce) {
        CcbNoServiceLayer* serviceLayer = CcbNoServiceLayer::create();
        CCDirector::sharedDirector()->getRunningScene()->addChild(serviceLayer, 10001, RECONNECT_TAG);
    }
}

