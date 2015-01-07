//
//  FriendCtrl.h
//  HelloWorld
//
//  Created by jun on 14-4-23.
//
//

#ifndef __HelloWorld__FriendCtrl__
#define __HelloWorld__FriendCtrl__

#include "Singleton.h"
#include "Defines.h"
#include "WorldPacket.h"
#include <vector>
#include <map>
#include "ConfigData.h"

using namespace std;

struct INVITE_USER_INFO
{
    uint32 dwInviteID;
    string strName;
    uint32 dwInviteCount;
    
    INVITE_USER_INFO()
    {
        dwInviteID = 0;
        strName = "";
        dwInviteCount = 0;
    }
};

struct INVITE_LIST_INFO
{
    uint32 dwRewardIndex;
    uint8 byStatus;
    
    INVITE_LIST_INFO()
    {
        dwRewardIndex = 0;
        byStatus = 0;
    }
};

struct INVITEE_LIST_INFO
{
    uint32 dwRewardIndex;
    uint8 byStatus;
    
    INVITEE_LIST_INFO()
    {
        dwRewardIndex = 0;
        byStatus = 0;
    }
};

struct INVITE_LIST_SHOW_INFO
{
    INVITE_LIST_INFO info;
    INVITE_CONFIG config;
};

class FriendCtrl : public Singleton<FriendCtrl> {
    
public:
    enum {
        kFromFriendList = 0,    // 0:好友列表界面}
        kFromCapture = 1,       // 1:抓捕奴隶界面}
        kFromRescue = 2,        // 2:解救好友界面}
        kFromTotalMail = 3,     // 3.包括好友邮件和好友申请}
        kFromFindFriend = 4,    // 4:查找好友列表}
    };
    
    enum {
        kFriendMsg = 1,
        kFriendApply = 2,
    };
    
    typedef struct _STC_USER_INFO
    {
        uint32 dwRoleId;
        std::string strName;
        uint16 wRoleLv;
        uint16 wPhoto;
        uint16 wLeaderId;
        uint8   byGroupId;
        _STC_USER_INFO() {
            dwRoleId = 0;
            strName = "";
            wRoleLv = 0;
            wPhoto = 0;
            wLeaderId = 0;
            byGroupId = 0;
        }
    }STC_USER_INFO;
    
    typedef struct _STC_FRIEND_MAIL {
        uint32 dwIndex;
        string strTitle;
        uint8 byMailFlag;       // 邮件flag，已读，未读}
        string strSendName;
        uint16 wRoleLv;
        uint16 wLeaderPetId;
        uint8 byArenaGroupId;
        _STC_FRIEND_MAIL() {
            dwIndex = 0;
            strTitle = "";
            byMailFlag = 0;
            strSendName = "";
            wRoleLv = 0;
            wLeaderPetId = 0;
            byArenaGroupId = 0;
        }
    }STC_FRIEND_MAIL;
    
    typedef struct _STC_MAIL_CONTENT {
        uint32 dwMailId;
        uint8 byMailFlag;
        string strContent;
        uint32 dwSendId;
        uint32 dwSendTime;
    }STC_MAIL_CONTENT;
    
    typedef std::vector<STC_USER_INFO> VEC_USER;
    
    typedef vector<STC_FRIEND_MAIL> VEC_FRIEND_MSG;
    
    void handlerFindFriendResult(WorldPacket& packet);
    // 抓捕列表}
    void handlerCaptureList(WorldPacket& packet);
    // 请求好友列表}
    void handlerFriendList(WorldPacket& packet);
    // 请求解救列表}
    void handlerRescueList(WorldPacket& packet);
    // 同意好友请求后的回调，该回调会发给双方}
    void handlerAddResult(WorldPacket& packet);
    // 删除好友后的回调}
    void handlerDelResult(WorldPacket& packet);
    // 新的好友请求到达}
//    void handlerNewApply(WorldPacket& packet);
    // 申请好友后的回包}
    void handlerApplyFriendResult(WorldPacket& packet);
    
    // 接入好友邮件和好友申请列表}
    void handlerFriendMsg(WorldPacket& packet);
    // 有新的好友邮件和好友申请到达}
    void handlerNewFriendMsg(WorldPacket& packet);
    
    /*!
     * 接收邮件内容}
     */
    void handlerFriendMailContent(WorldPacket& packet);
    
    STC_FRIEND_MAIL friendMailAtIdx(int idx) {
        if (idx >= m_vecMsg.size()) {
            CCMessageBox("Friend Mail Error", "Error");
            STC_FRIEND_MAIL tmp;
            return tmp;
        }
        return m_vecMsg[idx];
    }
    
    
    STC_FRIEND_MAIL friendApplyAtIdx(int idx) {
        if (idx >= m_vecApply.size()) {
            CCMessageBox("Friend Apply Error", "Error");
            STC_FRIEND_MAIL tmp;
            return tmp;
        }
        return m_vecApply[idx];
    }
    
    int msgCnt() {
        return m_vecMsg.size();
    }
    
    int applyCnt() {
        return m_vecApply.size();
    }
    
    int msgTotalCnt() {
        int nApply = m_vecApply.size();
        int nMsg = m_vecMsg.size();
        return nApply+nMsg;
    }
    
    /*!
     * 删除好友列表中的用户}
     */
    void removeUserWithRoleId(uint32 dwRoleId);
    
    /*!
     删除邮件和申请好友请求
     */
    void removeDzhWithId(uint32 dwId);
    
    /*! 
     * 增加好友列表中的用户}
     */
    void addUserWithRoleId(STC_USER_INFO newFriend);
    
    /*!
     * 删除申请列表中的用户}
     */
    void delApplyWithIdxId(uint32 dwIdxId);
    
    /*!
     * 删除好友邮件}
     */
    void delMsgWithIdxId(uint32 dwIdxId);
    
    uint8 getFromType() {
        return kFrom;
    }
    void setFromType(uint8 kType) {
        kFrom = kType;
    }
    
    int resCapUserCnt() {
        return m_vecResCapList.size();
    }
    
    STC_USER_INFO resCapUserAtIdx(int idx) {
        if (m_vecResCapList.empty() || idx >= m_vecResCapList.size()) {
            CCMessageBox("Get Error Friend Msg", "Error");
            STC_USER_INFO tmp;
            return tmp;
        }
        return m_vecResCapList[idx];
    }
    
    STC_USER_INFO friendListAtIdx(int idx) {
        if (m_vecFriendList.empty() || idx >= m_vecFriendList.size()) {
            CCMessageBox("get friend list error", "Fuck");
            STC_USER_INFO tmp;
            return tmp;
        }
        return m_vecFriendList[idx];
    }
    
    STC_USER_INFO userFinded() {
        CCLog("leader Id:%d, group Id:%d", findUser.wLeaderId, findUser.byGroupId);
        return findUser;
    }
    
    int friendListCnt() {
        return m_vecFriendList.size();
    }
    

    
    void setUserId(uint32 dwId) {
        m_dwUserId = dwId;
    }
    uint32 dwUserId() {
        return m_dwUserId;
    }
    
    std::string userName(uint32 dwId);
    
    STC_MAIL_CONTENT mailContent() {
        return sMailContent;
    }
    
    std::string senderNameByIdx(uint32 dwIdxId);
    std::string friendMailTitleByIdx(uint32 dwIdxId);
    void setMailFlagByIdx(uint32 dwIdxId);
    
    /*!
     * 删除好友邮件后的结果
     */
    void delMailResult(WorldPacket& packet);
    
    void handlerFriendPet(WorldPacket& packet);
    
    WorldPacket* getFriendPet(){return &m_friendPetPacket;};
private:
    uint8 kFrom;
    VEC_USER m_vecResCapList;           // 抓捕，解救}
    VEC_USER m_vecFriendList;       // 好友列表，上线即发}
    STC_USER_INFO findUser;
    uint32 m_dwUserId;              // 发送邮件给m_dwUserId这位好友}
    
    VEC_FRIEND_MSG m_vecMsg;        // 好友消息}
    VEC_FRIEND_MSG m_vecApply;      // 好友申请}
    
    STC_MAIL_CONTENT sMailContent;  // 好友邮件内容}
    
    WorldPacket m_friendPetPacket;
public:
    //邀请人信息}
    void SetInviteUserInfo(const INVITE_USER_INFO &info);
    const INVITE_USER_INFO GetInviteUserInfo();
    INVITE_USER_INFO m_InviteUserInfo;
    
    //邀请列表}
    void SetMapInviteList(const INVITE_LIST_INFO &info);
    INVITE_LIST_INFO GetInviteListInfobyIndex(uint32 dwIndex);
    map<uint32, INVITE_LIST_INFO> GetMapInviteList();
    map<uint32, INVITE_LIST_INFO> m_mapInviteList;

    //被邀请列表}
    void SetMapInviteeList(const INVITEE_LIST_INFO &info);
    INVITEE_LIST_INFO GetInviteeListInfobyIndex(uint32 dwIndex);
    map<uint32, INVITEE_LIST_INFO> GetMapInviteeList();
    map<uint32, INVITEE_LIST_INFO> m_mapInviteeList;
    
    
};


#endif /* defined(__HelloWorld__FriendCtrl__) */
