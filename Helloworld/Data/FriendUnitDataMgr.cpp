//
//  FriendUnitDataMgr.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/21.
//
//

#include "FriendUnitDataMgr.h"
#include "Defines.h"
#include "FriendMiddleBaseLayer.h"
#include "FriendMiddleListLayer.h"
#include "FriendMiddleSuggestLayer.h"
#include "PetLoadingLayer.h"
#include "FlyTextLayer.h"
#include "ConfigGet.h"
#include "FriendMiddleEnergyLayer.h"
#include "FriendMiddleMailLayer.h"
#include "ResourceStringClient.h"
#include "CcbManager.h"
#include "CcbMailDetailLayer.h"

FriendUnitDataMgr::FriendUnitDataMgr() {
    dwLeftEnergyCnt = 0;
    m_dwMailTarget = 0;
    m_strMailTargetName = "";
    m_strMailSenderName = "";
    m_strMailInTitle = "";
}

FriendUnitDataMgr::~FriendUnitDataMgr() {

}

void FriendUnitDataMgr::handlerFriendList(WorldPacket &packet) {
    m_vecFriendList[kFriendListType].clear();
    
    uint8 bySize;
    packet >> bySize;
    
    for (int i = 0; i < bySize; i++) {
        STC_LIST_INFO stcUser;
        packet >> stcUser.dwRoleId;
        packet >> stcUser.wLeaderId;
        packet >> stcUser.strName;
        packet >> stcUser.wRoleLv;
        packet >> stcUser.dwFightPower;
        packet >> stcUser.byHaveSendEnergy;
        
        m_vecFriendList[kFriendListType].push_back(stcUser);
    }
}

void FriendUnitDataMgr::handlerFriendSuggest(WorldPacket &packet) {
    PetLoadingLayer::sharedLayer()->End();
    m_vecFriendList[kFriendSuggestType].clear();
    
    uint8 bySize;
    packet >> bySize;
    
    for (int i = 0; i < bySize; ++i) {
        STC_LIST_INFO stcUser;
        packet >> stcUser.dwRoleId;
        packet >> stcUser.wLeaderId;
        packet >> stcUser.strName;
        packet >> stcUser.wRoleLv;
        packet >> stcUser.dwFightPower;
        
        m_vecFriendList[kFriendSuggestType].push_back(stcUser);
    }
    if (m_pLayerMiddles[kFriendSuggestType] && m_pLayerMiddles[kFriendSuggestType]->isVisible()) {
        m_pLayerMiddles[kFriendSuggestType]->reloadTableData();
    }
}

void FriendUnitDataMgr::handlerFindFriend(WorldPacket &packet) {
    PetLoadingLayer::sharedLayer()->End();
    
    uint16 wError;
    packet >> wError;
    
    m_vecFriendList[kFriendSuggestType].clear();
    
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
        return;
    } else {
        STC_LIST_INFO stcUser;
        packet >> stcUser.dwRoleId;
        packet >> stcUser.wLeaderId;
        packet >> stcUser.strName;
        packet >> stcUser.wRoleLv;
        packet >> stcUser.dwFightPower;
        
        m_vecFriendList[kFriendSuggestType].push_back(stcUser);
    }
    if (m_pLayerMiddles[kFriendSuggestType] && m_pLayerMiddles[kFriendSuggestType]->isVisible()) {
        m_pLayerMiddles[kFriendSuggestType]->reloadTableData();
    }
}

void FriendUnitDataMgr::handlerGetEnergy(WorldPacket &packet) {
    m_vecFriendList[kEnergyGetType].clear();
    
    packet >> dwLeftEnergyCnt;
    uint16 wSize;
    packet >> wSize;
    
    for (int i = 0; i < wSize; i++) {
        STC_LIST_INFO stcUser;
        packet >> stcUser.dwRoleId;
        packet >> stcUser.wLeaderId;
        packet >> stcUser.strName;
        packet >> stcUser.wRoleLv;
        packet >> stcUser.dwFightPower;
        
        m_vecFriendList[kEnergyGetType].push_back(stcUser);
    }
}

void FriendUnitDataMgr::handlerGetEnergyUpdate(WorldPacket &packet) {
    STC_LIST_INFO stcUser;
    packet >> stcUser.dwRoleId;
    packet >> stcUser.wLeaderId;
    packet >> stcUser.strName;
    packet >> stcUser.wRoleLv;
    packet >> stcUser.dwFightPower;
    
    m_vecFriendList[kEnergyGetType].push_back(stcUser);
    
    if (m_pLayerMiddles[kEnergyGetType] && m_pLayerMiddles[kEnergyGetType]->isVisible()) {
        m_pLayerMiddles[kEnergyGetType]->reloadTableData();
    }
}

void FriendUnitDataMgr::handlerAchieveEnergyResult(WorldPacket &packet) {
    PetLoadingLayer::sharedLayer()->End();
    uint16 wError;
    uint32 _dwEnergyGet;

    uint8 bySize;
    uint32 _dwRoleId;
    
    packet >> wError;
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
    } else {
        packet >> _dwEnergyGet;
        packet >> dwLeftEnergyCnt;
        packet >> bySize;
        
        for (int i = 0; i < bySize; i++) {
            packet >> _dwRoleId;
            VEC_FRIEND_LIST::iterator pIter;
            for (pIter = m_vecFriendList[kEnergyGetType].begin(); pIter != m_vecFriendList[kEnergyGetType].end(); pIter++) {
                if (pIter->dwRoleId == _dwRoleId) {
                    m_vecFriendList[kEnergyGetType].erase(pIter);
                    break;
                }
            }
        }
        
        if (m_pLayerMiddles[kEnergyGetType] && m_pLayerMiddles[kEnergyGetType]->isVisible()) {
            m_pLayerMiddles[kEnergyGetType]->reloadTableData();
        }
    }
}

void FriendUnitDataMgr::handlerFriendMailList(WorldPacket &packet) {
    m_vecFriendMail.clear();
    
    uint8 bySize;
    packet >> bySize;
    
    for (int i = 0; i < bySize; i++) {
        STC_FRIEND_MAIL stcMail;
        
        packet >> stcMail.byType;
        packet >> stcMail.dwIndex;
        packet >> stcMail.strTitle;
        packet >> stcMail.byMailFlag;
        packet >> stcMail.strSendName;
        packet >> stcMail.wRoleLv;
        packet >> stcMail.wLeaderPetId;
        packet >> stcMail.dwFightPower;
        
        m_vecFriendMail.push_back(stcMail);
    }
}

void FriendUnitDataMgr::handlerNewFriendMail(WorldPacket &packet) {
    STC_FRIEND_MAIL stcMail;
    
    packet >> stcMail.byType;
    packet >> stcMail.dwIndex;
    packet >> stcMail.strTitle;
    packet >> stcMail.byMailFlag;
    packet >> stcMail.strSendName;
    packet >> stcMail.wRoleLv;
    packet >> stcMail.wLeaderPetId;
    packet >> stcMail.dwFightPower;
    
    m_vecFriendMail.push_back(stcMail);
    
    if (m_pLayerMiddles[kFriendMailType] && m_pLayerMiddles[kFriendMailType]->isVisible()) {
        m_pLayerMiddles[kFriendMailType]->reloadTableData();
    } else {
        //TODO:Junie 增加小红标提示
    }
}

int FriendUnitDataMgr::frameCnt() {
    if (m_nCurType >= 0 && m_nCurType < 3) {
        return m_vecFriendList[m_nCurType].size();
    } else if (m_nCurType == 3) {
        return m_vecFriendMail.size();
    }
    return 0;
}

int FriendUnitDataMgr::friendNum() {
    if (!m_vecFriendList[kFriendListType].empty()) {
        return m_vecFriendList[kFriendListType].size();
    }
    return 0;
}

FriendUnitDataMgr::STC_LIST_INFO FriendUnitDataMgr::frameInfoAtIdx(int _idx) {
    FriendUnitDataMgr::STC_LIST_INFO _info;
    if (m_nCurType > 2) {
        CCMessageBox("Mail use another Struct", "Error");
        return _info;
    }
    _info = m_vecFriendList[m_nCurType][_idx];
    return _info;
}

FriendUnitDataMgr::STC_FRIEND_MAIL FriendUnitDataMgr::friendMailAtIdx(int _idx) {
    FriendUnitDataMgr::STC_FRIEND_MAIL _mail;
    if (m_nCurType != 3) {
        CCMessageBox("may be the wrong type", "Error");
        return _mail;
    }
    _mail = m_vecFriendMail[_idx];
    return _mail;
}

void FriendUnitDataMgr::resetMiddles() {
    for (int i = 0; i < Type_Cnt; ++i) {
        m_pLayerMiddles[i] = NULL;
    }
}

void FriendUnitDataMgr::setMiddleNode(int _type, cocos2d::CCSize _size, cocos2d::CCPoint _pos, cocos2d::CCLayer *_pLayer) {
    if (_type < 0 || _type >= Type_Cnt) {
        CCMessageBox("Friend Middle Base Type", "Error");
        return;
    }
    
    m_nCurType = _type;
    
    for (int i = 0; i < Type_Cnt; ++i) {
        if (m_pLayerMiddles[i] && i != _type) {
            m_pLayerMiddles[i]->setVisible(false);
        }
    }
    
    PetLoadingLayer::sharedLayer()->End();
    
    if (m_pLayerMiddles[_type]) {
        // 已经创建过该Layer，只需要显示并更新即可
        m_pLayerMiddles[_type]->setVisible(true);
        m_pLayerMiddles[_type]->reloadTableData();
        return;
    } else {
        switch (_type) {
            case 0: {   // 好友列表
                m_pLayerMiddles[_type] = FriendMiddleListLayer::create(_size);
                break;
            }
            case 1: {   // 好友推荐
                m_pLayerMiddles[_type] = FriendMiddleSuggestLayer::create(_size);
                break;
            }
            case 2: {   // 领取体力
                m_pLayerMiddles[_type] = FriendMiddleEnergyLayer::create(_size);
                break;
            }
            case 3: {   // 好友邮件
                m_pLayerMiddles[_type] = FriendMiddleMailLayer::create(_size);
                break;
            }
            default:
                break;
        }
        if (m_pLayerMiddles[_type]) {
            m_pLayerMiddles[_type]->setPosition(_pos);
            _pLayer->addChild(m_pLayerMiddles[_type]);
        }
    }
}

void FriendUnitDataMgr::handlerFriendEnergyGiveResult(WorldPacket &packet) {
    PetLoadingLayer::sharedLayer()->End();
    
    bool bSuccess = false;
    uint16 wError;
    uint32 dwFriendId;
    packet >> wError;
    
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
        return;
    } else {
        packet >> dwFriendId;
        VEC_FRIEND_LIST::iterator pIter;
        for (pIter = m_vecFriendList[kFriendListType].begin(); pIter != m_vecFriendList[kFriendListType].end(); pIter++) {
            if (pIter->dwRoleId == dwFriendId) {
                pIter->byHaveSendEnergy = true;
                bSuccess = true;
                break;
            }
        }
        if (bSuccess && m_pLayerMiddles[kFriendListType] && m_pLayerMiddles[kFriendListType]->isVisible()) {
            FlyTextLayer::showTips("赠送体力成功");
            m_pLayerMiddles[kFriendListType]->reloadTableData();
        }
    }
}

void FriendUnitDataMgr::handlerApplyFriendResult(WorldPacket &packet) {
    uint16 wError;
    packet >> wError;
    PetLoadingLayer::sharedLayer()->End();
    
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
    } else {
        FlyTextLayer::showTips(GET_STR(Str_apply_success));
    }
}


void FriendUnitDataMgr::handlerAgreeFriendReqResult(WorldPacket& packet) {
    PetLoadingLayer::sharedLayer()->End();
    
    STC_LIST_INFO stcUser;
    packet >> stcUser.dwRoleId;
    packet >> stcUser.wLeaderId;
    packet >> stcUser.strName;
    packet >> stcUser.wRoleLv;
    packet >> stcUser.dwFightPower;
    packet >> stcUser.byHaveSendEnergy;
    
    // 删除邮件Tab下的好友请求
    delTargetIdInType(stcUser.dwRoleId, kFriendMailType);
    
    // 好友数据增加
    m_vecFriendList[kFriendListType].push_back(stcUser);
    if (m_pLayerMiddles[kFriendListType] && m_pLayerMiddles[kFriendListType]->isVisible()) {
        m_pLayerMiddles[kFriendListType]->reloadTableData();
    }
}

void FriendUnitDataMgr::delTargetIdInType(uint32 _dwTargetId, int _type) {
    bool bRemove = false;
    
    if (_type == kFriendMailType) {
        // 邮件中删除，包括好友申请和好友邮件
        VEC_FRIEND_MAIL::iterator pIter;
        for (pIter = m_vecFriendMail.begin(); pIter != m_vecFriendMail.end(); pIter++) {
            if (pIter->dwIndex == _dwTargetId) {
                m_vecFriendMail.erase(pIter);
                bRemove = true;
                break;
            }
        }
    } else {
        // 前三个Tab，主要是好友Tab和领取Tab
        VEC_FRIEND_LIST::iterator pIter;
        for (pIter = m_vecFriendList[_type].begin(); pIter != m_vecFriendList[_type].end(); pIter++) {
            if (pIter->dwRoleId == _dwTargetId) {
                m_vecFriendList[_type].erase(pIter);
                bRemove = true;
                break;
            }
        }
    }
    
    if (bRemove && m_pLayerMiddles[_type] && m_pLayerMiddles[_type]->isVisible()) {
        m_pLayerMiddles[_type]->reloadTableData();
    }
}

void FriendUnitDataMgr::handlerDelFriendResult(WorldPacket &packet) {
    PetLoadingLayer::sharedLayer()->End();
    
    uint32 dwDelFriendId;
    packet >> dwDelFriendId;
    
    // CcbFriendListFrameLayer::167
    if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(5021)) {
        CCDirector::sharedDirector()->getRunningScene()->removeChildByTag(5021);
    }
    
    delTargetIdInType(dwDelFriendId, kFriendListType);
}

void FriendUnitDataMgr::handlerDelMailResult(WorldPacket &packet) {
    PetLoadingLayer::sharedLayer()->End();
    uint32 dwMailId = 0;
    packet >> dwMailId;
    delTargetIdInType(dwMailId, kFriendMailType);
}

void FriendUnitDataMgr::handlerMailDetailResult(WorldPacket &packet) {
    PetLoadingLayer::sharedLayer()->End();
    
    STC_MAIL_CONTENT stcMail;
    packet >> stcMail.dwMailId;
    packet >> stcMail.byMailFlag;
    packet >> stcMail.strContent;
    packet >> stcMail.dwSendId;
    packet >> stcMail.dwSendTime;
    
    setMailFlagAtIdx(stcMail.dwMailId, stcMail.byMailFlag);
    
    CcbMailDetailLayer* pMailDetail = dynamic_cast<CcbMailDetailLayer*>( CcbManager::sharedManager()->LoadCcbMailDetailLayer() );
    pMailDetail->setMailDetailContent(stcMail, m_strMailSenderName, m_strMailInTitle);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    pMailDetail->setPosition(ccp( winSize.width*0.5, winSize.height*0.5 ));
    CCDirector::sharedDirector()->getRunningScene()->addChild(pMailDetail, 20, 3211);
}

void FriendUnitDataMgr::setMailFlagAtIdx(uint32 _dwTargetId, uint8 _byFlag) {
    VEC_FRIEND_MAIL::iterator pIter;
    for (pIter = m_vecFriendMail.begin(); pIter != m_vecFriendMail.end(); pIter++) {
        if (pIter->dwIndex == _dwTargetId) {
            pIter->byMailFlag = _byFlag;
            return;
        }
    }
    return;
}

