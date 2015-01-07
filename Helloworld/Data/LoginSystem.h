//
//  LoginSystem.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-1-17.}
//
//

#ifndef __HelloWorld__LoginSystem__
#define __HelloWorld__LoginSystem__

#include "Singleton.h"
#include "Defines.h"
#include "WorldPacket.h"
#include <iostream>

class LoginSystem : public Singleton<LoginSystem> {
    
public:
    enum {
		E_UNCONNECTED,
		E_LOGIN_CONNECTED,
		E_GAME_CONNECTED,
	};
    
    enum {
        E_AUTH_FAST,            // 快速登陆验证}
        E_AUTH_ACCOUNT,         // 账号登陆验证}
        E_AUTH_THIRD,           // 第三方登陆验证}
        E_AUTH_USER,            // 变态登陆}
    };
    
    enum {
        E_FROM_STARTING = 0,    // 启动}
        E_FROM_LOGIN,           // 登陆}
        E_FROM_SERVER,
    };
    
    enum {
        E_FUCKING_UPPER = 0,    // 只是登陆}
        E_FUCKING_LOWER = 1,    // 登陆加进入游戏}
    };
    
    LoginSystem() {
        m_strLoginIp = "";
        m_nLoginPort = 0;
        m_strGameIp = "";
        m_nGamePort = 0;
        m_strUname = "";
        m_strPwd = "";
        m_dwUserId = 0;
        m_wAreaId = 0;
        
        m_byAuthFlag = E_AUTH_FAST;
        m_byConnectStatus = E_UNCONNECTED;
        m_byShowServerList = E_FROM_STARTING;
        
        m_dwCurTimeStamp = 0;
    };
    
    ~LoginSystem() {
        m_strLoginIp = "";
        m_nLoginPort = 0;
        m_strGameIp = "";
        m_nGamePort = 0;
        m_strUname = "";
        m_strPwd = "";
        m_dwUserId = 0;
        m_wAreaId = 0;
        
        m_byAuthFlag = E_AUTH_FAST;
        m_byConnectStatus = E_UNCONNECTED;
        m_byShowServerList = E_FROM_STARTING;
    };
    
    bool ConnectToLoginServer(std::string strIp, int nPort);
    void StartLogin(std::string strIp, int nPort, uint8 authFlag, std::string strUname, std::string strPwd);
    void SetGameServerInfo(WorldPacket &packet);
    void SetAuthResult(WorldPacket &packet);
    
    void EnterBackGround();
    void ReConnect();
    /*!
     * show No service layer
     */
    void ShowNoServiceLayer();
    
    void SetServerCallback();
    
    uint16 getAreaId() {
        return m_wAreaId;
    }
    void setAreaId(uint16 wArea) {
        m_wAreaId = wArea;
    }
    uint32 getUserId() {
        return m_dwUserId;
    }
    void setUserId(uint32 dwUser) {
        m_dwUserId = dwUser;
    }
    
    uint8 connectStatus() {
        return m_byConnectStatus;
    }
    void setConnectStatus(uint8 byStatus) {
        m_byConnectStatus = byStatus;
    }
    
    void setShowServerList(uint8 byFrom) {
        m_byShowServerList = byFrom;
    }
    uint8 showServerList() {
        return m_byShowServerList;
    }
    
    void setMode(uint8 byMode) {
        m_byMode = byMode;
    }
    
    uint8 getMode() {
        return m_byMode;
    }
    
    uint8 getAuthFlag() {
        return m_byAuthFlag;
    }
    std::string getUid();
    
    uint32 dwCurTimeStamp() {
        return m_dwCurTimeStamp;
    }
private:
    std::string m_strLoginIp;
    int m_nLoginPort;
    std::string m_strGameIp;
    int m_nGamePort;
    std::string m_strUname, m_strPwd;
    
    uint16 m_wAreaId;   // 当前的AreaId}
    uint32 m_dwUserId;
    
    uint8 m_byAuthFlag;
    uint8 m_byConnectStatus;
    
    uint8 m_byMode;
    uint32 m_dwCurTimeStamp;
    
    bool ConnectToServer(std::string &strIp, int nPort);    // LoginServer和GameServer均使用该连接方式}
    
    uint8 m_byShowServerList;       // 是否显示server list layer，第一次拉数据时不需要显示，登陆游戏再次拉服务器列表不需要显示。其余情况需要显示}
};

#endif /* defined(__HelloWorld__LoginSystem__) */
