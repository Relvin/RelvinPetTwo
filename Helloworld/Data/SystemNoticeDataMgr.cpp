//
//  SystemNoticeDataMgr.cpp
//  MyGame
//
//  Created by jun on 14-8-13.
//
//

#include "SystemNoticeDataMgr.h"

void CSystemNoticeDataMgr::AddSystemNotice(const SYSTEM_NOTICE_INFO& temp)
{
    map<uint8, SYSTEM_NOTICE_INFO>::iterator iter = m_mapSystemNotice.find(temp.byIndex);
    if (iter == m_mapSystemNotice.end())
    {
        m_mapSystemNotice.insert(make_pair(temp.byIndex, temp));
    }
}

map<uint8, SYSTEM_NOTICE_INFO> CSystemNoticeDataMgr::GetSystemNoticeMap()
{
    return m_mapSystemNotice;
}

SYSTEM_NOTICE_INFO CSystemNoticeDataMgr::GetNoticeInfoFromMap(uint8 index)
{
    map<uint8, SYSTEM_NOTICE_INFO>::iterator iter = m_mapSystemNotice.find(index);
    if (iter != m_mapSystemNotice.end())
    {
        return iter->second;
    }
    return SYSTEM_NOTICE_INFO();
}

void CSystemNoticeDataMgr::ClearSystemNotice()
{
    m_mapSystemNotice.clear();
}