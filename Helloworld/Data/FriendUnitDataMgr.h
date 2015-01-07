//
//  FriendUnitDataMgr.h
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/21.
//
//

#ifndef __MyGame__FriendUnitDataMgr__
#define __MyGame__FriendUnitDataMgr__

#include "Singleton.h"
#include <iostream>
#include <vector>
#include "WorldPacket.h"

using namespace std;

// 使用Friend_list_stc的有三个，剩余一个使用mail stc
#define Friend_Type 3
// 总共有5个标签
#define Type_Cnt 5

class FriendMiddleBaseLayer;
class FriendUnitDataMgr : public Singleton<FriendUnitDataMgr> {
    
public:
    FriendUnitDataMgr();
    
    virtual ~FriendUnitDataMgr();
    
    enum {
        kFriendListType = 0,
        kFriendSuggestType,
        kEnergyGetType,
        kFriendMailType,
        kFriendInvite,
    };
    
    enum {
        kMailTypeMsg = 1,
        kMailTypeApply = 2,
    };
    
    typedef struct _STC_LIST_INFO
    {
        uint32 dwRoleId;
        uint16 wLeaderId;
        std::string strName;
        uint16 wRoleLv;
        uint32 dwFightPower;
        uint8 byHaveSendEnergy;
        
        _STC_LIST_INFO() {
            dwRoleId = 0;
            wLeaderId = 0;
            strName = "";
            wRoleLv = 0;
            dwFightPower = 0;
            byHaveSendEnergy = 0;
        }
    }STC_LIST_INFO;
    
    typedef struct _STC_FRIEND_MAIL {
        uint8 byType;
        uint32 dwIndex;
        string strTitle;
        uint8 byMailFlag;       // 邮件flag，已读，未读}
        string strSendName;
        uint16 wRoleLv;
        uint16 wLeaderPetId;
        uint32 dwFightPower;
        _STC_FRIEND_MAIL() {
            byType = 0;
            dwIndex = 0;
            strTitle = "";
            byMailFlag = 0;
            strSendName = "";
            wRoleLv = 0;
            wLeaderPetId = 0;
            dwFightPower = 0;
        }
    }STC_FRIEND_MAIL;
    
    typedef struct _STC_MAIL_CONTENT {
        uint32 dwMailId;
        uint8 byMailFlag;
        string strContent;
        uint32 dwSendId;
        uint32 dwSendTime;
        _STC_MAIL_CONTENT() {
            dwMailId = 0;
            byMailFlag = 0;
            strContent = "";
            dwSendId = 0;
            dwSendTime = 0;
        }
    }STC_MAIL_CONTENT;
    
    /*!
     用于好友列表，好友推荐(好友查找)，领取体力
     */
    typedef std::vector<STC_LIST_INFO> VEC_FRIEND_LIST;     //好友个人信息Vector
    typedef std::vector<STC_FRIEND_MAIL> VEC_FRIEND_MAIL;   // 好友邮件Vecotr
    
    /*!
     好友列表(上线发)
     */
    void handlerFriendList(WorldPacket& packet);
    
    /*!
     好友推荐(请求才发)
     */
    void handlerFriendSuggest(WorldPacket& packet);
    
    /*!
     查找好友的结果(请求才发)
     */
    void handlerFindFriend(WorldPacket& packet);
    
    /*!
     领取体力(上线发)
     */
    void handlerGetEnergy(WorldPacket& packet);
    void handlerGetEnergyUpdate(WorldPacket& packet);
    /*!
     领取单个体力 和 领取全部体力 后返回的协议
     */
    void handlerAchieveEnergyResult(WorldPacket& packet);
    
    /*!
     邮件列表(上线发)
     */
    void handlerFriendMailList(WorldPacket& packet);
    void handlerNewFriendMail(WorldPacket& packet);
    
    /*!
     设置类型，获得类型
     */
    void setFriendType(int _type) {
        m_nCurType = _type;
    }
    int friendType() {
        return m_nCurType;
    }
    
    /*!
     获得table数量(四种均支持)
     */
    int frameCnt();
    
    /*!
     好友数量
     */
    int friendNum();
    
    /*!
     获得table的第n个数据(仅限于前三种类型)
     */
    STC_LIST_INFO frameInfoAtIdx(int _idx);
    
    /*!
     第N个邮件
     */
    STC_FRIEND_MAIL friendMailAtIdx(int _idx);
    
    void resetMiddles();
    /*!
     设置Middle的显示
     */
    void setMiddleNode(
                       int _type,
                       cocos2d::CCSize _size,
                       cocos2d::CCPoint _pos,
                       cocos2d::CCLayer* _pLayer
                       );
    
    /*!
     剩余体力领取数量
     */
    uint32 leftEnergyCnt() {
        return dwLeftEnergyCnt;
    }
    
    /*!
     赠送体力之后的回调
     */
    void handlerFriendEnergyGiveResult(WorldPacket& packet);
    
    /*!
     申请好友之后的回包，成功或者错误码
     */
    void handlerApplyFriendResult(WorldPacket& packet);
    
    /*!
     同意好友请求之后的回包（会给双方都发该协议，因此包含两个处理）
     */
    void handlerAgreeFriendReqResult(WorldPacket& packet);
    
    /*!
     @brief 删除对应_type的cell的数据值(有则删除并刷新，无则不报错不刷新)
     @param _type
            _dwTargetId
     */
    void delTargetIdInType(uint32 _dwTargetId, int _type);
    
    /*!
     mailTarget setter & getter
     */
    void setMailTarget(uint32 _dwMailTarget, std::string _strName) {
        m_dwMailTarget = _dwMailTarget;
        m_strMailTargetName = _strName;
    }
    uint32 mailTarget() {
        return  m_dwMailTarget;
    }
    std::string mailTargetName() {
        return m_strMailTargetName;
    }
    
    /*!
     删除好友后的结果
     */
    void handlerDelFriendResult(WorldPacket& packet);
    
    /*!
     删除邮件后的结果
     */
    void handlerDelMailResult(WorldPacket& packet);
    
    /*!
     邮件详情
     */
    void handlerMailDetailResult(WorldPacket& packet);
    
    /*!
     设置对应邮件的Flag值
     */
    void setMailFlagAtIdx(uint32 _dwTargetId, uint8 _byFlag);
    
    /*!
     读取邮件的时候传入的发件人姓名和邮件标题
     */
    void openMailWithNameAndTitle(std::string _strName, std::string _strTitle) {
        m_strMailSenderName = _strName;
        m_strMailInTitle = _strTitle;
    }
private:
    VEC_FRIEND_LIST m_vecFriendList[Friend_Type];   // 前三个Tab的数据
    VEC_FRIEND_MAIL m_vecFriendMail;    // 邮件只有一个Tab
    int m_nCurType;     // 当前的Type，enum中的类型
    uint32 dwLeftEnergyCnt;     // 剩余领取体力次数
    uint32 m_dwMailTarget;      // 邮件的收信人ID
    std::string m_strMailTargetName;    // 邮件的收信人姓名
    FriendMiddleBaseLayer* m_pLayerMiddles[Type_Cnt];   // 四个Tab的中间Layer

    std::string m_strMailSenderName;    // 邮件的发件人姓名
    std::string m_strMailInTitle;       // 邮件的标题
};

#endif /* defined(__MyGame__FriendUnitDataMgr__) */
