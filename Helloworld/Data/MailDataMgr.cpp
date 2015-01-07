//
//  MailDataMgr.cpp
//  HelloWorld
//
//  Created by jun on 13-11-18.
//
//

#include "MailDataMgr.h"
#include "GameSession.h"
#include "Role.h"
CMailDataMgr::CMailDataMgr()
: m_nCurMailType(0)
, m_nCurNotifyFunc(0)
, m_dwMailNum(0)
, m_pShareFrameLayerPt (NULL)
, m_pMainLayerPt(NULL)
, m_pSettingLayerPt(NULL)
, m_pBindingLayerPt(NULL)
, m_isAccountBinding(false)
, m_strBindingMail("")
{
    m_vecNorMailList.clear();
    m_vecSysMailList.clear();
}

void CMailDataMgr::AddNorMail(const MAIL_INFO &mailInfo)
{
    m_vecNorMailList.push_back(mailInfo);
}

bool CMailDataMgr::DelNorMailbyID(uint32 dwMailID)
{
    if (m_vecNorMailList.size() == 0)
    {
        return false;
    }
    
    VEC_ITER_MAIL_INFO iter;
    for ( iter = m_vecNorMailList.begin(); iter != m_vecNorMailList.end(); iter++ )
    {
        if (iter->dwMailId == dwMailID)
        {
            m_vecNorMailList.erase(iter);
            return true;
        }
    }
    return false;
}

VEC_MAIL_INFO CMailDataMgr::GetNorMailList()
{
    return m_vecNorMailList;
}

void CMailDataMgr::ClearNorMailList()
{
    m_vecNorMailList.clear();
}

void CMailDataMgr::AddSysMail(const MAIL_INFO &mailInfo)
{
    CGameSession::GetRole()->SetbyNotiAward(true);
    m_vecSysMailList.push_back(mailInfo);
}

bool CMailDataMgr::DelSysMailbyID(uint32 dwMailID)
{
    if (m_vecSysMailList.size() == 0)
    {
        return false;
    }
    
    VEC_ITER_MAIL_INFO iter;
    for ( iter = m_vecSysMailList.begin(); iter != m_vecSysMailList.end(); iter++ )
    {
        if (iter->dwMailId == dwMailID)
        {
            m_vecSysMailList.erase(iter);
            return true;
        }
    }
    return false;
}

VEC_MAIL_INFO CMailDataMgr::GetSysMailList()
{
    return m_vecSysMailList;
}

void CMailDataMgr::ClearSysMailList()
{
    m_vecSysMailList.clear();
}

void CMailDataMgr::SetCurMailType(int type)
{
    m_nCurMailType = type;
}

int CMailDataMgr::GetCurMailType()
{
    return m_nCurMailType;
}

void CMailDataMgr::UpdateNorMailFlagbyID(uint32 dwMailID, uint8 byMailFlag)
{
    if (m_vecNorMailList.size() == 0)
    {
        return;
    }
    
    VEC_ITER_MAIL_INFO iter;
    for ( iter = m_vecNorMailList.begin(); iter != m_vecNorMailList.end(); iter++ )
    {
        if (iter->dwMailId == dwMailID)
        {
            //iter->byMailFlag = byMailFlag;
            return;
        }
    }
}

void CMailDataMgr::UpdateSysMailFlagbyID(uint32 dwMailID, uint8 byMailFlag)
{
    if (m_vecSysMailList.size() == 0)
    {
        return;
    }
    
    VEC_ITER_MAIL_INFO iter;
    for ( iter = m_vecSysMailList.begin(); iter != m_vecSysMailList.end(); iter++ )
    {
        if (iter->dwMailId == dwMailID)
        {
            //iter->byMailFlag = byMailFlag;
            return;
        }
    }
}

void CMailDataMgr::SetCurOpenMailID(uint32 dwMailID)
{
    m_dwCurOpenMailID = dwMailID;
}

uint32 CMailDataMgr::GetCurOpenMailID()
{
    return m_dwCurOpenMailID;
}

void CMailDataMgr::SetCurNotifyFunc(int func)
{
    m_nCurNotifyFunc = func;
}

int CMailDataMgr::GetCurNotifyFunc()
{
    return m_nCurNotifyFunc;
}

void CMailDataMgr::SetShareFrameLayerPt(CCNode* node)
{
    m_pShareFrameLayerPt = node;
}

void CMailDataMgr::CloseShareFrameLayer()
{
    if (m_pShareFrameLayerPt)
    {
        m_pShareFrameLayerPt->removeFromParent();
        m_pShareFrameLayerPt = NULL;
    }
}
