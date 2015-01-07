//
//  FriendCtrl.cpp
//  HelloWorld
//
//  Created by jun on 14-4-23.
//
//

#include "FriendCtrl.h"
#include "BackCtrl.h"
#include "PetLoadingLayer.h"

#include "CcbFriendLayer.h"
#include "SystemMessage.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "GameSession.h"
#include "Role.h"
#include "FlyTextLayer.h"

void FriendCtrl::handlerCaptureList(WorldPacket &packet)
{
    // 我也想把所有的friend list接收写在一起啊！！！！天杀的服务器同一个结构体发过来的数据顺序不一样怎么办。}
    kFrom = kFromCapture;
    m_vecResCapList.clear();
    uint8 bySize;
    packet >> bySize;
    for (int i = 0; i < bySize; i++) {
        STC_USER_INFO stcUser;
        packet >> stcUser.dwRoleId;
        packet >> stcUser.strName;
        packet >> stcUser.wRoleLv;
        packet >> stcUser.wPhoto;
        packet >> stcUser.wLeaderId;
        packet >> stcUser.byGroupId;
        m_vecResCapList.push_back(stcUser);
    }
    BackCtrl::InsertNextScene(kFriendScene);
}

void FriendCtrl::handlerRescueList(WorldPacket &packet)
{
    kFrom = kFromRescue;
    m_vecResCapList.clear();
    uint8 bySize;
    packet >> bySize;
    for (int i = 0; i < bySize; i++) {
        STC_USER_INFO stcUser;
        packet >> stcUser.dwRoleId;
        packet >> stcUser.wLeaderId;
        packet >> stcUser.strName;
        packet >> stcUser.wRoleLv;
        packet >> stcUser.wPhoto;
        packet >> stcUser.byGroupId;
        m_vecResCapList.push_back(stcUser);
    }
    BackCtrl::InsertNextScene(kFriendScene);
}

// 发送好友列表　{}
/* uint8 bySize +
 {      uint32 dwFriendId +
 uint16 wLeaderId +
 std::string strName +
 uint16 wRoleLv +
 uint16 wPhoto}}*/
void FriendCtrl::handlerFriendList(WorldPacket &packet)
{
    // 好友申请和好友列表均走该接口，所以kFrom在之前设置}
    m_vecFriendList.clear();
    uint8 bySize;
    packet >> bySize;
    for (int i = 0; i < bySize; i++) {
        STC_USER_INFO stcUser;
        packet >> stcUser.dwRoleId; // dwFriendId
        packet >> stcUser.wLeaderId;
        packet >> stcUser.strName;
        packet >> stcUser.wRoleLv;
        packet >> stcUser.wPhoto;
        packet >> stcUser.byGroupId;
        m_vecFriendList.push_back(stcUser);
    }
//    BackCtrl::InsertNextScene(kFriendScene);
}



void FriendCtrl::handlerFindFriendResult(WorldPacket &packet)
{
    kFrom = kFromFindFriend;
    uint16 wError;
    packet >> wError;
    PetLoadingLayer::sharedLayer()->End();
    if (wError == 0) {
        packet >> findUser.dwRoleId >> findUser.wLeaderId >> findUser.strName >> findUser.wRoleLv >> findUser.wPhoto >> findUser.byGroupId;
        
//        if (CcbFindFriendLayer::GetCurLayer()) {
//            if (findUser.dwRoleId != 0) {
//                CcbFindFriendLayer::GetCurLayer()->showFindResult();
//            }
//        }
        
        return;
    } else {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
    }
}

void FriendCtrl::handlerApplyFriendResult(WorldPacket &packet)
{
    uint16 wError;
    packet >> wError;
    
    PetLoadingLayer::sharedLayer()->End();
    if (wError == 0) {
        FlyTextLayer::showTips(GET_STR(Str_apply_success));
//        if (CcbFindFriendLayer::GetCurLayer()) {
//            CcbFindFriendLayer::GetCurLayer()->hideFindResult();
//        }
    } else {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
    }
}

void FriendCtrl::handlerAddResult(WorldPacket &packet)
{
    STC_USER_INFO userInfo;
    packet >> userInfo.dwRoleId >> userInfo.wLeaderId >> userInfo.strName >> userInfo.wRoleLv >> userInfo.wPhoto >> userInfo.byGroupId;

    if (kFrom == kFromTotalMail) {
        delApplyWithIdxId(userInfo.dwRoleId);
    }
    addUserWithRoleId(userInfo);
}


void FriendCtrl::handlerFriendMsg(WorldPacket &packet)
{
    m_vecMsg.clear();
    m_vecApply.clear();
    
    uint8 bySize;
    packet >> bySize;
    for (int i = 0; i < bySize; i++) {
        uint8 byType;
        STC_FRIEND_MAIL sMail;
        
        packet >> byType;
        packet >> sMail.dwIndex >> sMail.strTitle >> sMail.byMailFlag >> sMail.strSendName >> sMail.wRoleLv >> sMail.wLeaderPetId >> sMail.byArenaGroupId;
        if (byType == kFriendMsg) {
            m_vecMsg.push_back(sMail);
        } else if (byType == kFriendApply) {
            m_vecApply.push_back(sMail);
        }
    }
}

void FriendCtrl::handlerNewFriendMsg(WorldPacket &packet)
{
    uint8 byType;
    STC_FRIEND_MAIL sMail;
    
    packet >> byType;
    packet >> sMail.dwIndex >> sMail.strTitle >> sMail.byMailFlag >> sMail.strSendName >> sMail.wRoleLv >> sMail.wLeaderPetId >> sMail.byArenaGroupId;
    if (byType == kFriendMsg) {
        m_vecMsg.push_back(sMail);
    } else if (byType == kFriendApply) {
        m_vecApply.push_back(sMail);
    }
    
    if (CcbFriendLayer::GetCurLayer()) {
        CcbFriendLayer::GetCurLayer()->ReloadList();
    } else {
        CGameSession::GetRole()->SetbyNotiFriend(true);
    }
}

void FriendCtrl::handlerDelResult(WorldPacket &packet)
{
    uint32 dwFriendId;
    packet >> dwFriendId;
    
    removeUserWithRoleId(dwFriendId);
}

//void FriendCtrl::handlerNewApply(WorldPacket &packet)
//{
//    STC_USER_INFO userInfo;
//    packet >> userInfo.dwRoleId >> userInfo.wLeaderId >> userInfo.strName >> userInfo.wRoleLv >> userInfo.wPhoto >> userInfo.byGroupId;
//    
//    // 如果在申请界面，则增加一个申请名单}
////    if (kFrom == kFromFriendApply) {
//    if (kFrom == kFromTotalMail) {
//        addUserWithRoleId(userInfo);
//    }
//}

void FriendCtrl::delApplyWithIdxId(uint32 dwIdxId)
{
    bool bRemove = false;
    VEC_FRIEND_MSG::iterator iter;
    for (iter = m_vecApply.begin(); iter != m_vecApply.end(); iter++) {
        if (iter->dwIndex == dwIdxId) {
            m_vecApply.erase(iter);
            bRemove = true;
            break;
        }
    }
}

void FriendCtrl::delMsgWithIdxId(uint32 dwIdxId)
{
    bool bRemove = false;
    VEC_FRIEND_MSG::iterator iter;
    for (iter = m_vecMsg.begin(); iter != m_vecMsg.end()&&!bRemove; iter++) {
        if (iter->dwIndex == dwIdxId) {
            m_vecMsg.erase(iter);
            bRemove = true;
            break;
        }
    }
    
    if (bRemove && CcbFriendLayer::GetCurLayer()) {
        CcbFriendLayer::GetCurLayer()->ReloadList();
    }
}

std::string FriendCtrl::userName(uint32 dwId)
{
    VEC_USER::iterator iter;
    for (iter = m_vecFriendList.begin(); iter != m_vecFriendList.end(); iter++) {
        if (iter->dwRoleId == dwId) {
            return iter->strName;
        }
    }
    return NULL;
}

void FriendCtrl::removeUserWithRoleId(uint32 dwRoleId)
{
    bool bRemove = false;
    VEC_USER::iterator iter;
    for (iter = m_vecFriendList.begin(); iter != m_vecFriendList.end(); iter++) {
        if (iter->dwRoleId == dwRoleId) {
            m_vecFriendList.erase(iter);
            bRemove = true;
            break;
        }
    }
    
    if (bRemove && CcbFriendLayer::GetCurLayer()) {
        CcbFriendLayer::GetCurLayer()->ReloadList();
    }
}

void FriendCtrl::removeDzhWithId(uint32 dwId)
{
    bool bRemove = false;
    VEC_FRIEND_MSG::iterator iter;
    for (iter = m_vecMsg.begin(); iter != m_vecMsg.end(); iter++) {
        if (iter->dwIndex == dwId) {
            m_vecMsg.erase(iter);
            bRemove = true;
            break;
        }
    }
    
    for (iter = m_vecApply.begin(); !bRemove && iter != m_vecApply.end(); iter++) {
        if (iter->dwIndex == dwId) {
            m_vecApply.erase(iter);
            bRemove = true;
            break;
        }
    }
    
    if (bRemove && CcbFriendLayer::GetCurLayer()) {
        CcbFriendLayer::GetCurLayer()->ReloadList();
    }
}

void FriendCtrl::addUserWithRoleId(STC_USER_INFO newFriend)
{
    bool bRepeat = false;
    VEC_USER::iterator iter;
    for (iter = m_vecFriendList.begin(); iter != m_vecFriendList.end(); ++iter) {
        if (iter->dwRoleId == newFriend.dwRoleId) {
            bRepeat = true;
            break;
        }
    }
    
    if (!bRepeat) {
        m_vecFriendList.push_back(newFriend);
        if (CcbFriendLayer::GetCurLayer()) {
            CcbFriendLayer::GetCurLayer()->ReloadList();
        }
    }
}

void FriendCtrl::SetInviteUserInfo(const INVITE_USER_INFO &info)
{
    m_InviteUserInfo.dwInviteID = info.dwInviteID;
    m_InviteUserInfo.strName = info.strName;
    m_InviteUserInfo.dwInviteCount = info.dwInviteCount;
}

const INVITE_USER_INFO FriendCtrl::GetInviteUserInfo()
{
    return m_InviteUserInfo;
}

//邀请列表}
void FriendCtrl::SetMapInviteList(const INVITE_LIST_INFO &info)
{
    map<uint32, INVITE_LIST_INFO>::iterator iter;
    iter = m_mapInviteList.find(info.dwRewardIndex);
    if (iter == m_mapInviteList.end())
    {
        m_mapInviteList.insert(make_pair(info.dwRewardIndex, info));
    }
    else
    {
        iter->second.byStatus = info.byStatus;
    }
}

INVITE_LIST_INFO FriendCtrl::GetInviteListInfobyIndex(uint32 dwIndex)
{
    map<uint32, INVITE_LIST_INFO>::iterator iter;
    iter = m_mapInviteList.find(dwIndex);
    if (iter != m_mapInviteList.end())
    {
        return iter->second;
    }
    return INVITE_LIST_INFO();
}

map<uint32, INVITE_LIST_INFO> FriendCtrl::GetMapInviteList()
{
    return m_mapInviteList;
}

//被邀请列表}
void FriendCtrl::SetMapInviteeList(const INVITEE_LIST_INFO &info)
{
    map<uint32, INVITEE_LIST_INFO>::iterator iter;
    iter = m_mapInviteeList.find(info.dwRewardIndex);
    if (iter == m_mapInviteeList.end())
    {
        m_mapInviteeList.insert(make_pair(info.dwRewardIndex, info));
    }
    else
    {
        iter->second.byStatus = info.byStatus;
    }
}

INVITEE_LIST_INFO FriendCtrl::GetInviteeListInfobyIndex(uint32 dwIndex)
{
    map<uint32, INVITEE_LIST_INFO>::iterator iter;
    iter = m_mapInviteeList.find(dwIndex);
    if (iter != m_mapInviteeList.end())
    {
        return iter->second;
    }
    return INVITEE_LIST_INFO();
}

map<uint32, INVITEE_LIST_INFO> FriendCtrl::GetMapInviteeList()
{
    return m_mapInviteeList;
}

void FriendCtrl::handlerFriendMailContent(WorldPacket &packet)
{
    packet >> sMailContent.dwMailId >> sMailContent.byMailFlag >> sMailContent.strContent >> sMailContent.dwSendId >> sMailContent.dwSendTime;
    // set mail flag
    setMailFlagByIdx(sMailContent.dwMailId);
    // load mail content layer
    if (CcbFriendLayer::GetCurLayer()) {
        CcbFriendLayer::GetCurLayer()->addMailContent();
    }
}

void FriendCtrl::setMailFlagByIdx(uint32 dwIdxId)
{
    VEC_FRIEND_MSG::iterator pIter;
    for (pIter = m_vecMsg.begin(); pIter != m_vecMsg.end(); pIter++) {
        if (pIter->dwIndex == dwIdxId) {
            pIter->byMailFlag = sMailContent.byMailFlag;
            break;
        }
    }
}

std::string FriendCtrl::senderNameByIdx(uint32 dwIdxId)
{
    VEC_FRIEND_MSG::iterator iter;
    for (iter = m_vecMsg.begin(); iter != m_vecMsg.end(); iter++) {
        if (iter->dwIndex == dwIdxId) {
            return iter->strSendName;
        }
    }
    return "NULL";
}

std::string FriendCtrl::friendMailTitleByIdx(uint32 dwIdxId)
{
    VEC_FRIEND_MSG::iterator iter;
    for (iter = m_vecMsg.begin(); iter != m_vecMsg.end(); iter++) {
        if (iter->dwIndex == dwIdxId) {
            return iter->strTitle;
        }
    }
    return "";
}

void FriendCtrl::delMailResult(WorldPacket &packet)
{
    PetLoadingLayer::sharedLayer()->End();
    uint32 dwMailId = 0;
    packet >> dwMailId;
    
    delMsgWithIdxId(dwMailId);
}

void FriendCtrl::handlerFriendPet(WorldPacket& packet)
{
    m_friendPetPacket = packet;
}