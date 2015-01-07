//
//  ChatDataMgr.h
//  MyGame
//
//  Created by 朱 俊杰 on 14-6-19.}
//
//

#ifndef __MyGame__ChatDataMgr__
#define __MyGame__ChatDataMgr__

#include <iostream>
#include "Singleton.h"
#include "Defines.h"
#include <vector>
#include "WorldPacket.h"

const int CHANNEL_CNT = 4;

class ChatDataMgr : public Singleton<ChatDataMgr> {
    
public:
    
    ChatDataMgr();
    virtual ~ChatDataMgr();
    typedef struct _STC_CHAT_MSG {
        uint8 byChannel;
        uint32 dwAccountId;
        uint16 wVipLv;
        uint16 wLeaderPetId;
        std::string strAccountName;
        std::string strContent;
        bool bIsSysNotice;
        _STC_CHAT_MSG()
        {
            byChannel = 0;
            dwAccountId = 0;
            wVipLv = 0;
            wLeaderPetId = 0;
            strAccountName = "";
            strContent = "";
            bIsSysNotice = false;
        }
    }STC_CHAT_MSG;
    
    /*
    enum ChatChannel
    {
        CHAT_CHANNEL_SYSTEM		= 0,		// 系统消息}
        CHAT_CHANNEL_WOLRD		= 1,		// 世界聊天}
        CHAT_CHANNEL_PERSONAL	= 2,		// 个人聊天}
        CHAT_CHANNEL_GUILD		= 3,		// 公会聊天}
    };
     */
    
    void handlerChatMsgList(WorldPacket& packet);
    void handlerAddChatMsg(WorldPacket& packet);
    void handlerRecNoticeMassage(WorldPacket &packet);
    STC_CHAT_MSG msgAtIdx(int idx, int _type);
    int msgCnt(int _type) { return m_vecChatMsg[_type].size(); }
    const char* playerName(uint32 _account);
    
private:
    typedef std::vector<STC_CHAT_MSG> VEC_CHAT_MSG;
    typedef std::vector<STC_CHAT_MSG>::iterator ITR_CHAT_MSG;
    VEC_CHAT_MSG m_vecChatMsg[CHANNEL_CNT];
    
    std::vector<std::string> m_vecChannelName;
    void initData();
};

#endif /* defined(__MyGame__ChatDataMgr__) */
