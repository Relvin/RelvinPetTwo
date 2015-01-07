//
//  ServerListCtrl.h
//  HelloWorld
//
//  Created by junjie zhu on 13-9-27.
//
//

#ifndef __HelloWorld__ServerListCtrl__
#define __HelloWorld__ServerListCtrl__

#include <iostream>
#include "Defines.h"
#include "WorldPacket.h"
#include "Singleton.h"
#include "Version.h"

enum
{
    E_SERVER_STATUS_NORMAL		= 0,    // **
	E_SERVER_STATUS_NEW			= 1,    // 新区}
	E_SERVER_STATUS_HOT			= 2,    // 火爆}
	E_SERVER_STATUS_MAINTAIN	= 3,    // 维护}
};

typedef struct _STC_AREA
{
    uint16	wAreaId;
    std::string strAreaName;
    uint8	byStatus;
    uint32  dwResourceVersion;
    _STC_AREA() {
        wAreaId = 0;
        strAreaName = "server";
        dwResourceVersion = CUR_RESOURCE_VERSION;
    }
}STC_AREA;

class ServerListCtrl : public Singleton<ServerListCtrl> {

    
public:
    ServerListCtrl() {
        m_nSelected = 999;
        m_strNotice = "";
    }
    
    // 得到服务器列表}
    void setServerList(WorldPacket &packet);
    // setter & getter
    int getAreaNum() {
        return m_wAreaNum;
    }
    int getSelected() {
        return m_nSelected;
    }
    void setSelected(uint8 uIdx) {
        m_nSelected = uIdx;
    }
    uint32 resourceVersion();
    const char* getAreaName(int idx);
    uint8 getAreaStatus(int idx);
    uint16 getAreaId(int idx);
    
    const char* selectedServerName();
private:
    int m_nSelected;     // 选中的服务器的idx，非areaId！}
    uint16 m_wAreaNum;
    std::vector<STC_AREA> m_vecArea;
    std::string m_strNotice;
    uint32 m_dwVersion;
};

#endif /* defined(__HelloWorld__ServerListCtrl__) */
