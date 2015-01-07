//
//  TaskDataMgr.cpp
//  HelloWorld
//
//  Created by jun on 14-4-3.
//
//

#include "TaskDataMgr.h"
#include "cocos2d.h"
#include "ConfigGet.h"
#include "GameSession.h"
#include "Role.h"

USING_NS_CC;

void CTaskDataMgr::SetAchieveInfo(const ACHIEVE_REWARD_INFO &info)
{
    vector<ACHIEVE_REWARD_INFO>::iterator iter;

    for (iter = m_vecAchieveInfo.begin(); iter != m_vecAchieveInfo.end(); iter++)
    {
        if (iter->dwType == info.dwType)
        {
            iter->dwScore = info.dwScore;
            iter->dwIndex = info.dwIndex;
            if (iter->dwIndex == 0)
            {
                m_vecAchieveInfo.erase(iter);
            }
            return;
        }
    }
    
    if (info.dwIndex != 0)
    {
        m_vecAchieveInfo.push_back(info);
    }
    
}

const ACHIEVE_REWARD_INFO CTaskDataMgr::GetAchieveInfoByIndex(uint32 dwIndex)
{
    vector<ACHIEVE_REWARD_INFO>::iterator iter;
    
    for (iter = m_vecAchieveInfo.begin(); iter != m_vecAchieveInfo.end(); iter++)
    {
        if (iter->dwIndex == dwIndex)
        {
            return *iter;
        }
    }
    //CCLOG("服务器上无此数据");
    return ACHIEVE_REWARD_INFO();
}

void CTaskDataMgr::SetDailyQuestInfo(const DAILY_QUEST_INFO &info)
{
    vector<DAILY_QUEST_INFO>::iterator iter;
    
    for (iter = m_vecDailyQuestInfo.begin(); iter != m_vecDailyQuestInfo.end(); iter++)
    {
        if (iter->dwIndex == info.dwIndex)
        {
            iter->byStatus = info.byStatus;
            iter->dwCondition = info.dwCondition;
            
            return;
        }
    }
    m_vecDailyQuestInfo.push_back(info);
}

const DAILY_QUEST_INFO CTaskDataMgr::GetDailyQuestInfoByIndex(uint32 dwIndex)
{
    vector<DAILY_QUEST_INFO>::iterator iter;
    
    for (iter = m_vecDailyQuestInfo.begin(); iter != m_vecDailyQuestInfo.end(); iter++)
    {
        if (iter->dwIndex == dwIndex)
        {
            return *iter;
        }
    }
    //CCLOG("服务器上无此数据");
    return DAILY_QUEST_INFO();
}

void CTaskDataMgr::ComputeAchieveAwardCount()
{
    m_nAchieveAwardCount = 0;
    vector<ACHIEVE_REWARD_INFO>::iterator iter;
    for (iter = m_vecAchieveInfo.begin(); iter != m_vecAchieveInfo.end(); iter++)
    {
        AchieveRewardConfig::STC_ACHIEVE_REWARD_CONFIG* pConfig = GET_CONFIG_STC(AchieveRewardConfig, iter->dwIndex);
        if (pConfig && iter->dwScore >= pConfig->dwParam[0])
        {
            CGameSession::GetRole()->SetbyNotiAward(true);
            m_nAchieveAwardCount++;
        }
    }
}

int CTaskDataMgr::GetAchieveAwardCount()
{
    return m_nAchieveAwardCount;
}

void CTaskDataMgr::ComputeDailyAwardCount()
{
    m_nDailyAwardCount = 0;
    vector<DAILY_QUEST_INFO>::iterator iter;    
    for (iter = m_vecDailyQuestInfo.begin(); iter != m_vecDailyQuestInfo.end(); iter++)
    {
        if (iter->byStatus == 1)
        {
            CGameSession::GetRole()->SetbyNotiAward(true);
            m_nDailyAwardCount++;
        }
    }
}

int CTaskDataMgr::GetDailyAwardCount()
{
    return m_nDailyAwardCount;
}

vector<uint32>& CTaskDataMgr::getHadRewardId()
{
    return m_vecGetRewardId;
}
