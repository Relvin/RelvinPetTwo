//
//  CaptureScene.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-8.}
//
//

#include "CaptureScene.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "CcbCaptureLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

USING_NS_CC;

#pragma mark CaptureCtrl

CaptureCtrl::STC_MASTER CaptureCtrl::masterInfo;
uint8 CaptureCtrl::byCurType = 0;

uint8 CaptureCtrl::bIsNew = 0;
CaptureCtrl::VEC_MINE CaptureCtrl::m_vecMine;
CaptureCtrl::VEC_MSG CaptureCtrl::m_vecMsg;
uint8 CaptureCtrl::byCurFarmId = 0;

void CaptureCtrl::HandlerCaptureInfo(WorldPacket &packet)
{
    m_vecMine.clear();
    m_vecMsg.clear();
    packet >> masterInfo.dwMasterId >> masterInfo.strMasterName >> masterInfo.dwCaptureTime;
    packet >> masterInfo.byMasterType >> masterInfo.byMasterFarmId >> masterInfo.wLeaderId;
    packet >> masterInfo.byGroupId >> masterInfo.dwLeftTime;
    
    packet >> byCurType;
    
    uint8 bySlaveSize;
    packet >> bySlaveSize;
    for (int i = 0; i < bySlaveSize; ++i) {
        STC_MINE_INFO stcMine;
        packet >> stcMine.dwSlaveId >> stcMine.strName >> stcMine.byRobLv >> stcMine.dwRewCnt;
        packet >> stcMine.wPetLeaderId >> stcMine.dwLeftTime;
        m_vecMine.push_back(stcMine);
    }
    packet >> bIsNew;

    uint8 byMsgSize;
    packet >> byMsgSize;
    for (int i = 0; i < byMsgSize; ++i) {
        std::string strMsg;
        packet >> strMsg;
        m_vecMsg.push_back(strMsg);
    }
    
    // 如果自身为奴隶，倒计时时间到之后，服务器会发送全包来更新自身！}
    
    if (CcbCaptureLayer::GetCurLayer()) {
        CcbCaptureLayer::GetCurLayer()->setCaptureInfo();
    } else {
        BackCtrl::InsertNextScene(kCaptureScene);
    }
}

void CaptureCtrl::HandlerRobRewardUpdate(WorldPacket &packet)
{
    uint8 byFarmId;
    packet >> byCurType >> byFarmId;
    packet >> m_vecMine[byFarmId].dwSlaveId >> m_vecMine[byFarmId].strName;
    packet >> m_vecMine[byFarmId].byRobLv >> m_vecMine[byFarmId].dwRewCnt;
    packet >> m_vecMine[byFarmId].wPetLeaderId >> m_vecMine[byFarmId].dwLeftTime;
    
    CGameSession::NotifyRefeashLayer();
}

#pragma mark CaptureScene

CCScene* CaptureScene::scene()
{
    CCScene* pScene = CCScene::create();
    CaptureScene* pLayer = CaptureScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool CaptureScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbCaptureLayer(this));
    return true;
}

bool CaptureScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    return false;
}

void CaptureScene::onEnter()
{
    CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_capture_title));
}

void CaptureScene::onExit()
{
    CCLayer::onExit();
}

void CaptureScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CaptureScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

