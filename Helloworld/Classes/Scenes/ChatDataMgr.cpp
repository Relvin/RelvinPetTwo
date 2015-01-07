//
//  ChatDataMgr.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14-6-19.}
//
//

#include "ChatDataMgr.h"
#include "GameSession.h"
#include "CcbChatLayer.h"
#include "ScrollNoticeLayer.h"
#include "EnumDefines.h"

ChatDataMgr::ChatDataMgr()
{
    for (int i = 0; i < CHANNEL_CNT; i++) {
        m_vecChatMsg[i].clear();
    }
    
    m_vecChannelName.clear();
}

ChatDataMgr::~ChatDataMgr()
{
    for (int i = 0; i < CHANNEL_CNT; i++) {
        m_vecChatMsg[i].clear();
    }
    m_vecChannelName.clear();
}

void ChatDataMgr::handlerChatMsgList(WorldPacket &packet) {
    for (int i = 0; i < CHANNEL_CNT; i++) {
        m_vecChatMsg[i].clear();
    }
//    initData();
    
    uint8 bySize = 0;
    bool bPrivate = false;
    bool bGuider = false;
    
    packet >> bySize;
    for (int i = 0; i < bySize; i++) {
        STC_CHAT_MSG sMsg;
        
        packet >> sMsg.byChannel >> bPrivate >> sMsg.dwAccountId >> sMsg.wVipLv >> sMsg.wLeaderPetId >> sMsg.strAccountName >> sMsg.strContent >> bGuider;
        m_vecChatMsg[sMsg.byChannel].push_back(sMsg);
    }
}

void ChatDataMgr::handlerAddChatMsg(WorldPacket& packet) {
    STC_CHAT_MSG sAddMsg;
    
    bool bPrivate = false;
    bool bGuider = false;
    
    packet >> sAddMsg.byChannel >> bPrivate >> sAddMsg.dwAccountId >> sAddMsg.wVipLv >> sAddMsg.wLeaderPetId >> sAddMsg.strAccountName >> sAddMsg.strContent >> bGuider;
    m_vecChatMsg[sAddMsg.byChannel].push_back(sAddMsg);
    
    if (sAddMsg.byChannel == CHAT_CHANNEL_WOLRD) {
        VEC_CHAT_MSG::iterator ii = m_vecChatMsg[CHAT_CHANNEL_WOLRD].begin();
        int count = 0;
        for (; ii != m_vecChatMsg[CHAT_CHANNEL_WOLRD].end(); ++ii) {
            if (!ii->bIsSysNotice) {
                if (m_vecChatMsg[CHAT_CHANNEL_WOLRD].size() - count > 8) {
                    m_vecChatMsg[CHAT_CHANNEL_WOLRD].erase(ii);
                }
                break;
            }
            count++;
        }
    }
    
    if (CcbChatLayer::getInstance()) {
//        CcbChatLayer::getInstance()->addNewMsg(sAddMsg);
        CcbChatLayer::getInstance()->reloadData();
    }
}

void ChatDataMgr::handlerRecNoticeMassage(WorldPacket &packet)
{
    STC_CHAT_MSG sAddMsg;
    packet >> sAddMsg.strContent;
    
    sAddMsg.bIsSysNotice = true;
    
    if (m_vecChatMsg[CHAT_CHANNEL_WOLRD].size() == 0) {
        m_vecChatMsg[CHAT_CHANNEL_WOLRD].push_back(sAddMsg);
    }
    else
    {
        VEC_CHAT_MSG::iterator ii = m_vecChatMsg[CHAT_CHANNEL_WOLRD].begin();
        for (int count = 0; ii != m_vecChatMsg[CHAT_CHANNEL_WOLRD].end(); ++ii,count++) {
            if (!ii->bIsSysNotice) {
                m_vecChatMsg[CHAT_CHANNEL_WOLRD].insert(ii, sAddMsg);
                if (count > 5) {
                    m_vecChatMsg[CHAT_CHANNEL_WOLRD].erase(m_vecChatMsg[CHAT_CHANNEL_WOLRD].begin());
                }
                break;
            }
        }
    }
    
    if (CcbChatLayer::getInstance()) {
//        CcbChatLayer::getInstance()->addNewMsg(sAddMsg);
        CcbChatLayer::getInstance()->reloadData();
    }
    ScrollNoticeLayer::shareInstance()->showScrollNotice(sAddMsg.strContent.c_str());
}


ChatDataMgr::STC_CHAT_MSG ChatDataMgr::msgAtIdx(int idx, int _type) {
    STC_CHAT_MSG sTmp;
    if (idx < m_vecChatMsg[_type].size()) {
        sTmp = m_vecChatMsg[_type][idx];
    }
    return sTmp;
}

const char* ChatDataMgr::playerName(uint32 _account)
{
//    ITR_CHAT_MSG pIt;
//    for (pIt = m_vecChatMsg.begin(); pIt != m_vecChatMsg.end(); pIt++) {
//        if (pIt->dwAccountId == _account) {
//            return pIt->strAccountName.c_str();
//        }
//    }
    return NULL;
}

void ChatDataMgr::initData() {
    STC_CHAT_MSG s1;
    s1.byChannel = 0;
    s1.dwAccountId = 2000044444;
    s1.strAccountName = "SB";
    s1.strContent = "=.=.==.=.=.=.=.=.=.[/1]=.=.=.=.==.=.=.=.=.=.=.==.=.=.=.=.=.=.=.=,,-,-,--,--,-,--,-,-,-,-,-,-";
    m_vecChatMsg[CHAT_CHANNEL_WOLRD].push_back(s1);
    
    STC_CHAT_MSG s2;
    s2.byChannel = 0;
    s2.dwAccountId = 2000044445;
	s2.strAccountName = "{qqqqqqqqqqqqq矫情}";
	s2.strContent = "{首先我导入的第三方框架的时候，只是[/9]从一个工程把类拖到另一个工程里面，这样的话只是显示在工程的表面而已，不是真正的在目录里面。}";
    m_vecChatMsg[CHAT_CHANNEL_PERSONAL].push_back(s2);
}

