//
//  ChanllengeDataMgr.h
//  MyGame
//
//  Created by long on 14-7-29.
//
//

#ifndef __MyGame__ChallengeDataMgr__
#define __MyGame__ChallengeDataMgr__

#include <iostream>
#include "Singleton.h"
#include "Defines.h"
#include "cocos2d.h"
#include "WorldPacket.h"

#define g_ChallengeDataMgr ChallengeDataMgr::Get()

/** 道观信息
 *		[uint32] dwCurStageId
 *		[uint8]	 byRewStatus
 *		[string] strName
 *		[uint16] wRoleLv
 *		[uint8]	 byTeamSize
 *				[uint16]	wPetId
 *		[uint8]	 byRewardSize
 *				[uint32]    dwUniteId
 *				[uint32]    dwUniteCnt
 **/
struct STC_CHA_LEVEL_INFO
{
    uint16 wIndexId;                    //关卡Id
    uint8 byRewStatus;                  //通关领奖状态
    uint8 byResetCnt;                   //剩余重置次数
    std::string strDefName;             //挑战对手名字
    uint16 wRoleLv;                     //挑战对手等级
    std::vector<uint16> arrPetId;       //对手阵容
    std::vector<uint32> arrRewItemId;   //关卡掉落Id
    std::vector<uint32> arrRewItemCnt;  //关卡掉落数量
    
    STC_CHA_LEVEL_INFO(){
        wIndexId = 0;
    };
};

class ChallengeDataMgr :  public Singleton<ChallengeDataMgr>
{
public:
    ChallengeDataMgr();
    ~ChallengeDataMgr();
    
    void handlerCurStageInfo(WorldPacket &packet);
    STC_CHA_LEVEL_INFO getCurStageInfo(){
        return m_curStageInfo;
    };
    
    void setCurFightStage(uint16 stageId){m_wCurFightStage = stageId;};
    uint16 getCurFightStage(){return m_wCurFightStage;};
private:
    STC_CHA_LEVEL_INFO m_curStageInfo;
    uint16 m_wCurFightStage;
};

#endif /* defined(__MyGame__ChanllengeDataMgr__) */
