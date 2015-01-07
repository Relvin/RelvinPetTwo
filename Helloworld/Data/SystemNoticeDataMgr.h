//
//  SystemNoticeDataMgr.h
//  MyGame
//
//  Created by jun on 14-8-13.
//
//

#ifndef __MyGame__SystemNoticeDataMgr__
#define __MyGame__SystemNoticeDataMgr__

#include "Singleton.h"
#include "Defines.h"
#include <map>
using namespace std;

struct SYSTEM_NOTICE_INFO
{
    uint8 byIndex;
    string title;
    string content;
    
    SYSTEM_NOTICE_INFO()
    {
        byIndex = 0;
    }
};

class CSystemNoticeDataMgr : public Singleton<CSystemNoticeDataMgr>
{
public:
    void AddSystemNotice(const SYSTEM_NOTICE_INFO& temp);
    map<uint8, SYSTEM_NOTICE_INFO> GetSystemNoticeMap();
    SYSTEM_NOTICE_INFO GetNoticeInfoFromMap(uint8 index);
    void ClearSystemNotice();
private:
    map<uint8, SYSTEM_NOTICE_INFO> m_mapSystemNotice;
};

#define g_SystemNoticeDataMgr CSystemNoticeDataMgr::Get()

#endif /* defined(__MyGame__SystemNoticeDataMgr__) */
