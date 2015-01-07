//
//  Role.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-18.}
//
//

#include "Role.h"

CRole::CRole()
{
    m_dwAccountId = 0;          // 账号ID}}
    m_strAccount = "";          // 账号}
    m_strUserName = "Chinese";    // 用户名}
    m_wRoleLv = 0;              // 人物等级}
    m_dwRoleExp = 0;            // 人物经验（稍后服务器增加经验最大值）}
    m_dwEnergy = 0;             // 人物活力，用来推图}
    m_dwEnergyMax = 0;          // 活力最大值}
    m_dwCoin = 0;               // 金币}
    m_dwDollar = 0;             // 钻石}
    m_byVipLv = 0;              // VIP 等级}
    m_dwVipExp = 0;             // VIP 经验（经验累积，每个等级Max读配表）}
    m_wPhoto = 0;               // 人物头像}
    m_dwResFarmNum = 0;          // 魂(蓝色的那个球)}
    m_byArenaUseCnt = 0;        // 竞技点}
    
    m_dwReputation = 0;         // 声望}
    m_wPassMapId = 0;           // 已经过的地图Id}
    m_wPassStageId = 0;         // 已经过的关卡Id}
    
    m_dwItemBagCnt = 0;         // 背包数量}
    m_dwRoleMaxExp = 0;         // 当前等级的最大经验值}
    
    m_dwEnergyRecTime = 0;      // 体力恢复倒计时}
    m_dwPetBagCnt = 0;          // 宠物背包}
    m_byArenaGroup = 0;         // 竞技点}
    
    m_byEnergyRewStatus = 0;    //回复体力}
    m_dwSevenRewDay = 0;        //7天登陆奖励}
    m_bySevenRewStatus = 0;
    m_dwThirtyRewDay = 0;       //30天登陆奖励}
    m_byThirtyRewStatus = 0;
    
    m_dwBattleBagCnt = 0;       //开放的战斗位个数}
    m_dwWorldInitTime = 0;      // 服务器重启时间，断线重连时候判断。}
    m_dwScore = 0;     //// 祭炼} 改为 每日人物 积分}
    
    m_wGuideTrigger = 0;       //新手引导触发器}
    m_wHeroStage = 0;   // 精英关卡已过关卡点}
    m_wHeroMap = 0;     // 精英关卡已过地图点}
    m_byIsAutoFight = 0;
    m_dwSweepUseTime = 0;
    m_dwSweepCDTime = 0;
    m_dwRoleFightValue = 0;
    m_dwShareCnt = 0;
    /* the properties below are used by client ONLY!
     IF you want add any property of Role in the following time,
     add BEFORE this.
     */
    m_byNotiUnit = 0;   // 精灵通知}
    m_byNotiGacha = 0;  // 抽奖通知}
    m_byNotiShop = 0;   // 商城通知}
    m_byNotiActive = 0; // 活动通知}
    m_byNotiFriend = 0; // 好友通知}
    m_byNoti30Day = 0;  // 30天通知}
    m_byNotiReward = 0; // 奖励通知}
    m_byNotiMystery = 0;    // 神秘商店}
    m_byNotiNewPet = 0; // 新宠物}
    m_byNotiNewEquip = 0;   // 新装备}
    m_byNotiNewEmblem = 0;  // 新徽章}
    m_byNotiAward = 0;  // top的奖励通知}
    m_byNotiBox = 0;    // 箱子
    m_byNotiChips = 0;  // 碎片
    
    arrUnitChildren.clear();
    arrUnitChildren.push_back(&m_byNotiNewPet);
    arrUnitChildren.push_back(&m_byNotiNewEquip);
    arrUnitChildren.push_back(&m_byNotiNewEmblem);
    arrUnitChildren.push_back(&m_byNotiBox);
    arrUnitChildren.push_back(&m_byNotiChips);
}

CRole::~CRole()
{
    
}

void CRole::SetbyNotiUnit()
{
    uint8 byUnit = 0;
    for (int i = 0; i < arrUnitChildren.size(); i++) {
        byUnit = byUnit | *arrUnitChildren[i];
    }
    SetbyNotiUnit(byUnit);
}