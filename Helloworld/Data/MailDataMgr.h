//
//  MailDataMgr.h
//  HelloWorld
//
//  Created by jun on 13-11-18.
//
//

#ifndef __HelloWorld__MailDataMgr__
#define __HelloWorld__MailDataMgr__

#include <iostream>
#include "Singleton.h"
#include "Defines.h"
#include <vector>
#include <map>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

const int MAIL_RETENTION_PERIOD = 30;   //保留天数}

enum MAIL_FLAG  //邮件标志}
{
    E_MAIL_FLAG_NEW = 0,    //新邮件}
    E_MAIL_FLAG_READ = 1,   //已读取}
    E_MAIL_FLAG_REWARD = 2, //已领取}
};

enum MAIL_TYPE  //邮件类型}
{
    E_MAIL_TYPE_SYSTEM  = 1,    //系统邮件}
    E_MAIL_TYPE_MESSAGE = 2,    //玩家留言}
};

enum MAIL_FUNC
{
    E_MAIL_FUNC_UPDATE = 0,  //更新邮件状态}
    E_MAIL_FUNC_ADD = 1,     //增加新邮件}
    E_MAIL_FUNC_DEL = 2,     //删除邮件}
    E_MAIL_FUNC_REWARD = 3,  //查看系统奖励}
};

struct MAIL_REWARD_INFO
{
    uint32 dwRewId;     //奖励物品ID}
    uint32 dwRewCnt;    //奖励物品数量}
    
    MAIL_REWARD_INFO()
    {
        dwRewId = 0;
        dwRewCnt = 0;
    };
};

struct MAIL_INFO
{
    uint32	dwMailId;       //邮件ID}
    string	strTitle;       //邮件标题}
    string	strContent;     //邮件内容}
    uint32	dwRecvTime;     //邮件时间，单位：秒}
//    uint32	dwRewId;        //奖励物品Index}
//    uint32	dwRewCnt;       //奖励物品数量}
    
    vector<MAIL_REWARD_INFO> vecRewareInfo;//奖励物品列表}
   
    MAIL_INFO()
    {
        dwMailId = 0;
        strTitle = "";
        strContent = "";
        dwRecvTime = 0;
//        dwRewId = 0;
//        dwRewCnt = 0;
    };
};

typedef vector<MAIL_INFO> VEC_MAIL_INFO;
typedef vector<MAIL_INFO>::iterator VEC_ITER_MAIL_INFO;

class CMailDataMgr :public Singleton<CMailDataMgr>
{
public:
    CMailDataMgr();
	//普通信件}
	void AddNorMail(const MAIL_INFO &mailInfo);
	bool DelNorMailbyID(uint32 dwMailID);
	VEC_MAIL_INFO GetNorMailList();
	void ClearNorMailList();
	//系统邮件}
	void AddSysMail(const MAIL_INFO &mailInfo);
	bool DelSysMailbyID(uint32 dwMailID);
	VEC_MAIL_INFO GetSysMailList();
	void ClearSysMailList();

	void SetCurMailType(int type);//当前打开界面的类型 1、系统邮件 2、普通邮件}
	int GetCurMailType();

	void UpdateNorMailFlagbyID(uint32 dwMailID, uint8 byMailFlag);
	void UpdateSysMailFlagbyID(uint32 dwMailID, uint8 byMailFlag);

	void SetCurOpenMailID(uint32 dwMailID);
	uint32 GetCurOpenMailID();

	void SetCurNotifyFunc(int func);
	int GetCurNotifyFunc();

	void SetMailNum(uint32 num) { m_dwMailNum = num; };
	uint32 GetMailNum() { return m_dwMailNum; };

	uint32 GetSysRewardNum() { return m_vecSysMailList.size(); };
public:
	VEC_MAIL_INFO m_vecNorMailList;  //普通信件列表}
	VEC_MAIL_INFO m_vecSysMailList;  //系统邮件列表}

	uint32 m_dwCurOpenMailID;   //邮件ID}
	int m_nCurMailType;         //当前打开的邮件类型，1系统邮件，2普通邮件}
	int m_nCurNotifyFunc;       //当前等待通知的功能，用来更新显示内容，0是更新flag状态 1是增加新邮件 2是删除邮件 3是查看系统奖励}

	uint32 m_dwMailNum;
	//分享界面的Node指针}
	void SetShareFrameLayerPt(CCNode* node);
	void CloseShareFrameLayer();
	CCNode* m_pShareFrameLayerPt;

	//主界面的的Node指针}
	void SetMainLayerPt(CCNode* node) { m_pMainLayerPt = node; };
	CCNode* GetMainLayerPt() { return m_pMainLayerPt; };
	CCNode* m_pMainLayerPt;
    //设置界面的Node指针}
    void SetSettingLayerPt(CCNode* node) { m_pSettingLayerPt = node; };
    CCNode* GetSettingLayerPt() { return m_pSettingLayerPt; };
    CCNode* m_pSettingLayerPt;
    
    //绑定界面的Node指针}
    void SetBindingLayerPt(CCNode* node) { m_pBindingLayerPt = node; };
    CCNode* GetBindingLayerPt() { return m_pBindingLayerPt; };
    CCNode* m_pBindingLayerPt;
    
    //账号是否绑定过}
    void SetAccountBindingState(bool isBinding) { m_isAccountBinding = isBinding; };
    bool GetAccountBindingState() { return m_isAccountBinding; };
    bool m_isAccountBinding;
    
    void SetAccountBindingMail( string strMail) { m_strBindingMail = strMail; };
    string GetBindingMail() { return m_strBindingMail; };
    string m_strBindingMail;
    
};

#endif /* defined(__HelloWorld__MailDataMgr__) */
