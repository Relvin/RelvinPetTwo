//
//  TaskDataMgr.h
//  HelloWorld
//
//  Created by jun on 14-4-3.
//
//

#ifndef __HelloWorld__TaskDataMgr__
#define __HelloWorld__TaskDataMgr__

#include <iostream>
#include "Singleton.h"
#include "Defines.h"
#include "ConfigData.h"
#include <vector>

using namespace std;

struct ACHIEVE_REWARD_INFO
{
    uint32	dwType;
    uint32	dwScore;
    uint32	dwIndex;
    
    ACHIEVE_REWARD_INFO()
    {
        dwType = 0;
        dwScore = 0;
        dwIndex = 0;
    }
};

struct DAILY_QUEST_INFO
{
    uint32 dwIndex;
    uint8 byStatus;
    uint32 dwCondition;
    
    DAILY_QUEST_INFO()
    {
        dwIndex = 0;
        byStatus = 0;
        dwCondition = 0;
    }
};

class CTaskDataMgr : public Singleton<CTaskDataMgr>
{
public:
    CTaskDataMgr() {
        m_nAchieveAwardCount = 0;
    }
    
    //存放成就状态}
    void SetAchieveInfo(const ACHIEVE_REWARD_INFO &info);
    const ACHIEVE_REWARD_INFO GetAchieveInfoByIndex(uint32 dwIndex);
    vector<ACHIEVE_REWARD_INFO> GetAchieveVector() { return m_vecAchieveInfo; };
    vector<ACHIEVE_REWARD_INFO> m_vecAchieveInfo;
    
    //存放每日任务状态}
    void SetDailyQuestInfo(const DAILY_QUEST_INFO &info);
    const DAILY_QUEST_INFO GetDailyQuestInfoByIndex(uint32 dwIndex);
    vector<DAILY_QUEST_INFO> m_vecDailyQuestInfo;
    
    void ComputeAchieveAwardCount();
    int GetAchieveAwardCount();
    int m_nAchieveAwardCount;
    
    void ComputeDailyAwardCount();
    int GetDailyAwardCount();
    int m_nDailyAwardCount;
    
    vector<uint32>& getHadRewardId();
    
private:
    vector<uint32>  m_vecGetRewardId;
};

#define g_TaskData CTaskDataMgr::Get()

#endif /* defined(__HelloWorld__TaskDataMgr__) */
