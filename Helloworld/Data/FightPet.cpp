//
//  FightPet.cpp
//  HelloWorld
//
//  Created by long on 13-8-26.
//
//


/*
 被动技能触发 以及 eff是战斗逻辑中最复杂的部分，所以在这里整理一遍，以便以后查看。}
 1、被动技能按照触发时机可以分为
 自动触发(条件满足时自动触发，主要是在回合开始、回合结束、战斗开始、战斗结束时触发)
 战斗中触发(攻击过程中带出的效果)。
 另外死亡触发是一个特殊条件，做特殊判断，即不管什么情况(攻击、debuff等)造成宠物死亡，在死亡的时候判断宠物身上是否有死亡触发的技能，有的话立刻触发，并显示带出的效果(eff、buff等)；
 2、按照条件来看，受伤触发、闪避触发是针对被攻击者的；暴击触发要循环判断此次攻击暴击与否；杀死敌人要的伤害全部计算之后才能判断；所以将这四个也单独拎出来，在特定的时机验证触发；
 3、被动技能造成的eff与buff可能针对多个对象，但暂时要么是单体，要么是全体，并且所有对象的效果命中与否是统一的
 4、对于战中并且概率触发的被动技能，触发情况由服务器发送的触发列表判定，对应的技能带出效果(eff、buff)，其他的技能涉及到概率的都是由客户端随机产生
 5、不同触发条件的被动技能的表现时机也不同，包括：点击操作时、伤害第一帧时、攻击结束时、死亡时、回合开始、回合结束时等，需要单独列出来处理；
 
 
 */

#include "FightPet.h"
#include "ConfigGet.h"
#include "Defines.h"
#include "FightAI.h"
#include "HttpLog.h"
#include <stdio.h>
#include "WorldInfoDataMgr.h"

FightPet::FightPet()
:skillTriggerCounter(0),
passiveSkillTriggerCounter(0),
critTriggerCounter(0),
m_wLianXieAdd(0),
m_byLianXieState(0),
m_dwCurAtk(0)
{}
FightPet::~FightPet()
{
//    arrItem.clear();}
    arrPassiveSkillTrigger.clear();
    arrSkillTrigger.clear();
    arrCritTrigger.clear();
    arrTriggerPassiveSkill.clear();
}

FightPet* FightPet::creat(STC_FIGHT_PET_INFO *info, FightTeam *myTeam)
{
    FightPet* pet = new FightPet();
    
    if (pet && pet->init(info, myTeam))
    {
        return pet;
    }
    else
    {
        delete pet;
        pet = NULL;
        return NULL;
    }
}

bool FightPet::init(STC_FIGHT_PET_INFO *info, FightTeam *myTeam)
{
    //设置我的队伍}
    setMyTeam(myTeam);
    //
    setPetInfo(info->petInfo);
    
    setCurHP(info->petInfo.wCurHP);
//    CCLog("fight Id %d,   curHp %d", getPetInfo().wBattleIndex, getCurHP());
    if (m_curHP == 0) {
        CCMessageBox("FightPet pet init hp~~~~~0 ~~~~~~~~", "Error");
    }

    setLeaderSkillId(info->petInfo.wLeaderSkillId);
    setCurPower(info->petInfo.wPowerCur);
    setIsCanDead(false);
    setIsWaitSkill(false);
    setCurHeart(0);
    m_arrEff.clear();
    m_mapBuff.clear();
    m_mapSpecBuff.clear();
    setDoubleCount(0);
    setMaxDropHeart(0);
    setIsBoss(info->petInfo.isBoss);
    

    arrPassiveSkillTrigger = info->arrPassiveSkillTrigger;
    arrSkillTrigger = info->arrSkillTrigger;
    arrCritTrigger = info->arrCritTrigger;
    
    //根据装备判断是否有初始Buff}
    m_unHitCnt = 0;
    
    return true;
}

#pragma mark Passvie

//波次开始初始化Buff及Eff}
void FightPet::waveStartPassvieSkill(uint16 wRound)
{
    m_unHitCnt = 0;
    
    std::map<uint32, STC_PASSIVE_SKILL>::iterator it = m_petInfo.arrPassiveSkill.begin();
    for (; it != m_petInfo.arrPassiveSkill.end(); it++) {
        it->second.isTrigged = false;
    }
    
    m_mapBuff.clear();
    m_mapSpecBuff.clear();
    arrTriggerPassiveSkill.clear();
    m_arrBufValue.clear();
    m_arrEff.clear();
    //自动触发被动技能（波次触发）}
    std::vector<STC_PASSIVE_SKILL> arrPassive = checkPassvie(wRound, E_BATTLE_TIME_WAVE_START, E_PASSIVE_TYPE_AUTO);
    
    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill = triggerBuffAddEff(wRound, NULL, arrPassive);
    
    arrTriggerPassiveSkill = effPSkillActive(arrTPSkill, 0);
    
}

//波次结束时检查被动技能触发}
void FightPet::waveEndPassvieSkill(uint16 wRound)
{
    //清除buff}
    //    for (int i = 0; i < E_BUFF_TYPE_END; i++) {
    //        STC_BUFF buff;
    //        m_arrBuf.push_back(buff);
    //    }
    
    m_mapBuff.clear();
    m_mapSpecBuff.clear();
    arrTriggerPassiveSkill.clear();
    m_arrBufValue.clear();
    m_arrEff.clear();
    std::vector<STC_PASSIVE_SKILL> arrPassive = checkPassvie(wRound, E_BATTLE_TIME_WAVE_END, E_PASSIVE_TYPE_AUTO);
    
    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill = triggerBuffAddEff(wRound, NULL, arrPassive);
    m_mapBuff.clear();
    m_mapSpecBuff.clear();
    arrTriggerPassiveSkill = effPSkillActive(arrTPSkill, 0);
    
//    effActive(0, NULL);
}
//回合开始，检查自动触发的被动技能}
void FightPet::beforeRoundPassvieSkill(uint16 wRound)
{
    m_arrBufValue.clear();
    m_arrEff.clear();
    arrTriggerPassiveSkill.clear();
    std::vector<STC_PASSIVE_SKILL> arrPassive = checkPassvie(wRound, E_BATTLE_TIME_ROUND_START, E_PASSIVE_TYPE_AUTO);
    
    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill = triggerBuffAddEff(wRound, NULL, arrPassive);
    
    arrTriggerPassiveSkill = effPSkillActive(arrTPSkill, 0);
//    effActive(0, NULL);
}

//回合结束，检查自动触发的被动技能}
void FightPet::afterRoundPassiveSkill(uint16 wRound)
{
    m_arrBufValue.clear();
    m_arrEff.clear();
    arrTriggerPassiveSkill.clear();
//    std::vector<STC_PASSIVE_SKILL> arrPassive = checkPassvie(wRound, E_BATTLE_TIME_ROUND_END, E_PASSIVE_TYPE_AUTO);
//    
//    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill = triggerBuffAddEff(wRound, NULL, arrPassive);
//    
//    arrTriggerPassiveSkill = effPSkillActive(arrTPSkill, 0);
    
//    effActive(0, NULL);
}

//与伤害无关的被动技能触发}
std::vector<STC_PASSIVE_SKILL> FightPet::checkPassvie(uint16 wRound, uint8 eBattleTiem, uint8 triggerType, uint32 skillId, FightPet *enemy)
{
    std::vector<STC_PASSIVE_SKILL> arrTriggerPassive;
//    STC_PASSIVE_SKILL pp;
//    pp.wIndex = 14000118;
//    pp.wLv = 1;
//    //            passive->isTrigged = true;
//    arrTriggerPassive.push_back(pp);
//    return arrTriggerPassive;
    
    std::map<uint32, STC_PASSIVE_SKILL>::iterator it = m_petInfo.arrPassiveSkill.begin();
    for (; it != m_petInfo.arrPassiveSkill.end(); it++) {
        STC_PASSIVE_SKILL *passive = &it->second;
        if (passive->wIndex == 0) {
            continue;
        }
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *cfg = GET_CONFIG_STC(PassiveSkillConfig, passive->wIndex);
        if (!cfg) {
            continue;
        }
        //触发类型（战斗中/自动）}
        if (cfg->byTriggerType != triggerType) {
            continue;
        }
        
//        if (skillId && !cfg->byIsFlollowUlimate) {
//            continue;
//        }
        
//        if (triggerType == E_PASSIVE_TYPE_IN_FIGHT) {

//        }
        
        
        switch (eBattleTiem) {
            case E_BATTLE_TIME_ROUND_START:
//            case E_BATTLE_TIME_ROUND_END:   //回合结束}
                switch (cfg->wStrikeCondition1) {
                    case E_PASSIVE_STRIPE_RATE: //概率触发}
                        passiveSkillTriggerUsedFlag = true;
                        if (arrPassiveSkillTrigger.size() <= passiveSkillTriggerCounter) {
                            continue;
                        }
                        if (arrPassiveSkillTrigger[passiveSkillTriggerCounter].size() == 0) {
                            continue;
                        }
                        else
                        {
                            std::map<uint32, STC_PASSIVE_SKILL_TRIGGER> mapTrigger = arrPassiveSkillTrigger[passiveSkillTriggerCounter];
                            if (mapTrigger.find(passive->wIndex) == mapTrigger.end()
                                || mapTrigger[passive->wIndex].wSize == 0) {
                                continue;
                            }
//                            passive->isTrigged = true;
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_Round_CNT:		 // 隔几回合触发一次}
                        if (wRound - passive->wLastTime >= cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1) {
                            arrTriggerPassive.push_back(*passive);
                            passive->wLastTime = wRound;
                            //                            return;
                        }
                        break;
                    case E_PASSIVE_STRIPE_LOWER_HP_MY:			// 我方HP低于}
                        if ( (getCurHP() * 10000 / getPetInfo().wHP) <= cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1)
                        {
//                            passive->isTrigged = true;
                            arrTriggerPassive.push_back(*passive);
                            //                            return;
                        }
                        break;
                    case E_PASSIVE_STRIPE_UP_HP_MY:			// 我方HP高于}
                        if ( (getCurHP() * 10000 / getPetInfo().wHP) >= cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1)
                        {
//                            passive->isTrigged = true;
                            arrTriggerPassive.push_back(*passive);
                            //                            return;
                        }
                        break;
                    case E_PASSIVE_STRIPE_LOWER_HP_EN:			// 敌方HP低于}
                        if ( enemy && (enemy->getCurHP() * 10000 / enemy->getPetInfo().wHP) <= cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1)
                        {
//                            passive->isTrigged = true;
                            arrTriggerPassive.push_back(*passive);
                            //                            return;
                        }
                        break;
                    case E_PASSIVE_STRIPE_UP_HP_EN:			// 敌方HP高于}
                        if ( enemy && (enemy->getCurHP() * 10000 / enemy->getPetInfo().wHP) >= cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1)
                        {
//                            passive->isTrigged = true;
                            arrTriggerPassive.push_back(*passive);
                            //                            return;
                        }
                        break;
                        
                    case E_PASSIVE_STRIPE_SLAY_UP:  //必杀高于}
                        if (getCurPower() >= cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1) {
//                            passive->isTrigged = true;
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_SLAY_LOWER:   //必杀低于}
                        if (getCurPower() <= cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1) {
//                            passive->isTrigged = true;
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                        
                    case E_PASSIVE_STRIPE_POISON: //关于中毒}
                        if (enemy && enemy->HasPalsyBuff(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_FROZEN: //关于冰冻}
                        if (enemy && enemy->HasFrozenBuff(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_FIRING: //关于灼烧}
                        if (enemy && enemy->HasFiringBuff(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_PALSY: //关于麻痹}
                        if (enemy && enemy->HasPalsyBuff(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_SEAL: //关于封印}
                        if (enemy && enemy->HasSealBuff(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_ADD_SPEED: //关于加速}
                        if (enemy && enemy->HasNumSpeedAddBuff(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_DEC_SPEED: //关于减速}
                        if (enemy && enemy->HasNumSpeedDecBuff(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_CONFUSED: //关于混乱}
                        if (enemy && enemy->HasConfusedBuff(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                        
                    case E_PASSIVE_STRIPE_LOSE_BLOOD:   //掉血触发}
                    {
                        uint32 lose = getPetInfo().wHP - getCurHP();
                        uint32 rate = getPetInfo().wHP * (cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1) / 10000;
                        if (lose > rate) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        
                    }
                        break;
                    case E_PASSIVE_STRIPE_DIE_ONE: //  我方死亡1人}
                        if (m_MyTeam->getDeadPetCount() > 0) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_SPEED_HIGH: //速度高于自身}
                        if (enemy && enemy->getCurSpeed(wRound) > getCurSpeed(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_ONLY_ONE: //我方存活1}
                        if (m_MyTeam->getLivePetCount() > 0) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_SPEED_LOWER: //速度低于自身}
                        if (enemy && enemy->getCurSpeed(wRound) < getCurSpeed(wRound)) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_HP_HIGH: //生命高于敌方}
                        if (enemy && enemy->getCurHP() < getCurHP()) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
                    case E_PASSIVE_STRIPE_HP_LOWER: //生命低于敌方}
                        if (enemy && enemy->getCurHP() > getCurHP()) {
                            arrTriggerPassive.push_back(*passive);
                        }
                        break;
//                    case E_PASSIVE_STRIPE_START:     //波次开始第几回合触发}
//                        if (wRound == cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1) {
////                            passive->isTrigged = true;
//                            arrTriggerPassive.push_back(*passive);
//                        }
//                        break;
                        /*
                         
                         E_PASSIVE_STRIPE_POISON			= 16,	//  关于中毒}
                         E_PASSIVE_STRIPE_FROZEN			= 17,	//  关于冰冻}
                         E_PASSIVE_STRIPE_FIRING			= 18,	//  关于灼烧}
                         E_PASSIVE_STRIPE_PALSY			= 19,	//  关于麻痹}
                         E_PASSIVE_STRIPE_SEAL			= 20,	//  关于封印}
                         E_PASSIVE_STRIPE_ADD_SPEED		= 21,	//  关于加速}
                         E_PASSIVE_STRIPE_DEC_SPEED		= 22,	//  关于减速}
                         E_PASSIVE_STRIPE_CONFUSED		= 23,	//  关于混乱}
                         E_PASSIVE_STRIPE_LOSE_BLOOD		= 24,	//  掉血触发}
                         E_PASSIVE_STRIPE_DIE_ONE		= 25,	//  我方死亡1人}
                         E_PASSIVE_STRIPE_SPEED_HIGH		= 26,	//  速度高于自身}
                         E_PASSIVE_STRIPE_ONLY_ONE		= 27,	//  我方存活1}
                         E_PASSIVE_STRIPE_SPEED_LOWER	= 28,	//  速度低于自身}
                         E_PASSIVE_STRIPE_HP_HIGH		= 29,	//  生命高于敌方}
                         E_PASSIVE_STRIPE_HP_LOWER		= 30,	//  生命低于敌方}
                         
                         */
                        
                    default:
                        break;
                }
                break;
            case E_BATTLE_TIME_WAVE_START:
                if (cfg->wStrikeCondition1 == E_PASSIVE_STRIPE_START //波次开始第几回合触发}
                    && wRound == cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1) {
//                            passive->isTrigged = true;
                    arrTriggerPassive.push_back(*passive);
                }
                break;
            case E_BATTLE_TIME_WAVE_END:            // 战斗结束}
                if (cfg->wStrikeCondition1 == E_PASSIVE_STRIPE_BATTLE_END) {
//                    passive->isTrigged = true;
                    arrTriggerPassive.push_back(*passive);
                }
                break;
                
            default:
                break;
        }
    }
    
    return arrTriggerPassive;
}

//受伤触发}
std::vector<STC_TRIGGERED_PSKILL> FightPet::checkPassiveHurt(FightPet* enemy)
{
    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill;
    std::map<uint32, STC_PASSIVE_SKILL>::iterator it = m_petInfo.arrPassiveSkill.begin();
    for (; it != m_petInfo.arrPassiveSkill.end(); it++) {
        STC_PASSIVE_SKILL *passive = &it->second;
        if (passive->wIndex == 0) {
            continue;
        }
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *cfg = GET_CONFIG_STC(PassiveSkillConfig, passive->wIndex);
        if (!cfg) {
            continue;
        }
        switch (cfg->wStrikeCondition1) {
            case E_PASSIVE_STRIPE_HURT:  //受伤触发}
                if (FightAI::Get()->RandEither(cfg->wStrikePara1 + (passive->wLv-1)*cfg->wStrikeChg1, 10000)) {
//                    passive->isTrigged = true;
                    //                    arrTriggerPassive.push_back(*passive);
                    {
                        STC_TRIGGERED_PSKILL tpSkill = triggerPassiveBuffAddEff(enemy, passive);
                        if (tpSkill.wSkillIndex) {
                            arrTPSkill.push_back(tpSkill);
                        }
                    }
                    //                    triggerBuffAddEff(FightAI::Get()->getCurRound(), enemy, 0);
                }
                break;
                
            default:
                
                break;
        }
    }
    
    return arrTPSkill;
}
//闪避触发}
std::vector<STC_TRIGGERED_PSKILL> FightPet::checkPassiveDodge(FightPet* enemy)
{
    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill;
    std::map<uint32, STC_PASSIVE_SKILL>::iterator it = m_petInfo.arrPassiveSkill.begin();
    for (; it != m_petInfo.arrPassiveSkill.end(); it++) {
        STC_PASSIVE_SKILL *passive = &it->second;
        if (passive->wIndex == 0) {
            continue;
        }
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *cfg = GET_CONFIG_STC(PassiveSkillConfig, passive->wIndex);
        if (!cfg) {
            continue;
        }
        switch (cfg->wStrikeCondition1) {
            case E_PASSIVE_STRIPE_DODGE:  //闪避触发}
//                passive->isTrigged = true;
                //                arrTriggerPassive.push_back(*passive);
            {
                STC_TRIGGERED_PSKILL tpSkill = triggerPassiveBuffAddEff(enemy, passive);
                if (tpSkill.wSkillIndex) {
                    arrTPSkill.push_back(tpSkill);
                }
            }
                break;
                
            default:
                
                break;
        }
    }
    return arrTPSkill;
}
//暴击触发}
std::vector<STC_TRIGGERED_PSKILL> FightPet::checkPassiveCirt(FightPet* enemy)
{
    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill;
    std::map<uint32, STC_PASSIVE_SKILL>::iterator it = m_petInfo.arrPassiveSkill.begin();
    for (; it != m_petInfo.arrPassiveSkill.end(); it++) {
        STC_PASSIVE_SKILL *passive = &it->second;
        if (passive->wIndex == 0) {
            continue;
        }
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *cfg = GET_CONFIG_STC(PassiveSkillConfig, passive->wIndex);
        if (!cfg) {
            continue;
        }
        switch (cfg->wStrikeCondition1) {
            case E_PASSIVE_STRIPE_CRIT:  //暴击触发}
//                passive->isTrigged = true;
                //                arrTriggerPassive.push_back(*passive);
            {
                STC_TRIGGERED_PSKILL tpSkill = triggerPassiveBuffAddEff(enemy, passive);
                if (tpSkill.wSkillIndex) {
                    arrTPSkill.push_back(tpSkill);
                }
            }
                break;
                
            default:
                
                break;
        }
    }
    return arrTPSkill;
}
//杀死敌人}
std::vector<STC_TRIGGERED_PSKILL> FightPet::checkPassiveKill(FightPet* enemy)
{
    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill;
    std::map<uint32, STC_PASSIVE_SKILL>::iterator it = m_petInfo.arrPassiveSkill.begin();
    for (; it != m_petInfo.arrPassiveSkill.end(); it++) {
        STC_PASSIVE_SKILL *passive = &it->second;
        if (passive->wIndex == 0) {
            continue;
        }
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *cfg = GET_CONFIG_STC(PassiveSkillConfig, passive->wIndex);
        if (!cfg) {
            continue;
        }
        switch (cfg->wStrikeCondition1) {
            case E_PASSIVE_STRIPE_KILL_ENERMY:  //杀死敌人}
//                passive->isTrigged = true;
                //                arrTriggerPassive.push_back(*passive);
            {
                STC_TRIGGERED_PSKILL tpSkill = triggerPassiveBuffAddEff(enemy, passive);
                if (tpSkill.wSkillIndex) {
                    arrTPSkill.push_back(tpSkill);
                }
            }
                break;
                
            default:
                
                break;
        }
    }
    
    return arrTPSkill;
}
//死亡触发}
std::vector<STC_TRIGGERED_PSKILL> FightPet::checkPassiveDead(FightPet* enemy)
{
    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill;
    std::map<uint32, STC_PASSIVE_SKILL>::iterator it = m_petInfo.arrPassiveSkill.begin();
    for (; it != m_petInfo.arrPassiveSkill.end(); it++) {
        STC_PASSIVE_SKILL *passive = &it->second;
        if (passive->wIndex == 0) {
            continue;
        }
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *cfg = GET_CONFIG_STC(PassiveSkillConfig, passive->wIndex);
        if (!cfg) {
            continue;
        }
        switch (cfg->wStrikeCondition1) {
            case E_PASSIVE_STRIPE_DEAD:  //死亡触发}
//                passive->isTrigged = true;
//                arrTriggerPassive.push_back(*passive);
            {
                STC_TRIGGERED_PSKILL tpSkill = triggerPassiveBuffAddEff(enemy, passive);
                if (tpSkill.wSkillIndex) {
                    arrTPSkill.push_back(tpSkill);
                }
            }
                break;
                
            default:
                
                break;
        }
    }
    arrTPSkill = effPSkillActive(arrTPSkill, 0);
    return arrTPSkill;
}

//触发被动技能带出的eff和buff}
std::vector<STC_TRIGGERED_PSKILL> FightPet::triggerBuffAddEff(uint16 wRound, FightPet *enemy, std::vector<STC_PASSIVE_SKILL> arrTriggerPassive)
{
    //    m_arrEff.clear();
    std::vector<STC_TRIGGERED_PSKILL> arrTPSkill;
    //被动技能产生的Buff和Eff}
    for (int i = 0; i < arrTriggerPassive.size(); i++) {
        STC_PASSIVE_SKILL p = arrTriggerPassive[i];
        if (p.wIndex == 0) {
            continue;
        }
        STC_TRIGGERED_PSKILL tpSkill = triggerPassiveBuffAddEff(enemy, &p);
        
        if (tpSkill.wSkillIndex) {
            arrTPSkill.push_back(tpSkill);
        }
    }
    return arrTPSkill;
}

//触发被动技能带出的eff和buff}
STC_TRIGGERED_PSKILL FightPet::triggerPassiveBuffAddEff(FightPet *enemy, STC_PASSIVE_SKILL *passive)
{
    
    STC_TRIGGERED_PSKILL tPSkill;
    if (passive->wIndex == 0) {
        return tPSkill;
    }
    PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *passConfig = GET_CONFIG_STC(PassiveSkillConfig, passive->wIndex);
    if (!passConfig) {
        return tPSkill;
    }
    
    std::vector<FightPet*> arrMy;
    std::vector<FightPet*> arrEnemy;
    
    //因为现在只有一个和全体两种情况，所以不做其他判断}
    if (passConfig->byAttackerScope == 6) {
        std::map<uint16, FightPet*>::iterator it = this->getMyTeam()->GetTeam().begin();
        for (; it != this->getMyTeam()->GetTeam().end(); ++it) {
            if (!it->second || it->second->getCurHP() <= 0) {
                continue;
            }
            arrMy.push_back(it->second);
        }
    }
    else
    {
        arrMy.push_back(this);
    }
    
    if (enemy) {
        if (passConfig->byDeffenseScope == 6) {
            std::map<uint16, FightPet*>::iterator it = enemy->getMyTeam()->GetTeam().begin();
            for (; it != enemy->getMyTeam()->GetTeam().end(); ++it) {
                if (!it->second || it->second->getCurHP() <= 0) {
                    continue;
                }
                arrEnemy.push_back(it->second);
            }
        }
        else
        {
            arrEnemy.push_back(enemy);
        }
    }
    
    
    int len = 0;
    GET_ARRAY_LEN(passConfig->wAttackBuff, len);
    
    tPSkill.wSkillIndex = passive->wIndex;
    tPSkill.fightId = getPetInfo().wBattleIndex;
    STC_PASSIVE_SKILL_TRIGGER trigger;
    if (passiveSkillTriggerCounter < arrPassiveSkillTrigger.size()) {
        std::map<uint32, STC_PASSIVE_SKILL_TRIGGER> mapTrigger = arrPassiveSkillTrigger[passiveSkillTriggerCounter];
        trigger = mapTrigger[passive->wIndex];
    }
    
    bool triggerMyBuff = false;
    bool triggerEnemyBuff = false;
    uint8 cnt = 1;
    
    
    switch (passConfig->wStrikeCondition1) {
        case E_PASSIVE_STRIPE_LOSE_BLOOD:   //掉血触发}
        {
            uint32 lose = getPetInfo().wHP - getCurHP();
            uint32 rate = getPetInfo().wHP * (passConfig->wStrikePara1 + (passive->wLv-1)*passConfig->wStrikeChg1) / 10000;
            cnt = lose / rate;
            
        }
        case E_PASSIVE_STRIPE_DIE_ONE: //  我方死亡1人}
            cnt = m_MyTeam->getDeadPetCount();
                
            break;
        case E_PASSIVE_STRIPE_ONLY_ONE: //我方存活1}
            cnt = m_MyTeam->getLivePetCount();
            break;
            
        default:
            break;
    }
    
    std::vector<STC_EFFECT> arrMyEff;
    std::vector<STC_EFFECT> arrEnemyEff;
    
    for (int i = 0; i < len; i++) {
        //三个buff 由一个buff命中决定，要触发都触发，不触发就都不触发，所以只判断一次（除概率触发技能，都由客户端判断触发）}
        if (i == 0 && (passConfig->byTriggerType == E_PASSIVE_TYPE_AUTO || passConfig->wStrikeCondition1 != E_PASSIVE_STRIPE_RATE)) {
            triggerMyBuff = FightAI::Get()->RandEither(passConfig->wAttackBuffHit, 100);// rand() % 100 < passConfig->wAttackBuffHit;
        }
        
        //可叠加buff}
        for (int j = 0; j < cnt; j++) {

            if (passConfig->wAttackBuff[i])
            {
                if(triggerMyBuff || (trigger.wSize > 0 && trigger.byMyBuffHit == 1))
                {
                    STC_BUFF buff;
                    buff.wBuffId = passConfig->wAttackBuff[i];
                    buff.wStartRound = FightAI::Get()->getCurRound();
                    buff.wLastRound = passConfig->wAttackBuffTime[i];
                    
                    SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffCfg = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
                    if (buffCfg) {
                        switch (buffCfg->wType) {
                            case E_BUFF_FIRING:
                            case E_BUFF_FROZEN:
                            case E_BUFF_BIND:
                            case E_BUFF_POISON:
                                buff.dwValuePara = m_dwCurAtk;
                                break;
                                
                            default:
                                break;
                        }
                    }
                    
                    //                if ((FightAI::Get()->isMyAttack() && getPetInfo().wBattleIndex > PetCnt)
                    //                    ||(!FightAI::Get()->isMyAttack() && getPetInfo().wBattleIndex <= PetCnt)) {
                    //                    buff.wLastRound++;
                    //                }
                    //                bool flag = true;
                    for (int k = 0; k < arrMy.size(); ++k) {
                        
                        //                    if ((FightAI::Get()->isMyAttack() && arrMy[k]->getPetInfo().wBattleIndex > PetCnt)
                        //                        ||(!FightAI::Get()->isMyAttack() && arrMy[k]->getPetInfo().wBattleIndex <= PetCnt)) {
                        //                        buff.wLastRound++;
                        //                    }
                        
                        arrMy[k]->addNewBuff(buff);
                        
                    }
                    //                if (flag) {
                    //                    tPSkill.wSkillIndex = 0;
                    //                }
                }
            }
            
            if (passConfig->wAttackEff[i])
            {
                bool triggerEff = false;
                if(passConfig->byTriggerType == E_PASSIVE_TYPE_AUTO || passConfig->wStrikeCondition1 != E_PASSIVE_STRIPE_RATE){
                    triggerEff = rand() % 100 < passConfig->wAttackEffHit[i];
                }
                
                if (triggerEff || (trigger.wSize > 0 && trigger.arrMyEffHit[i] == 1)) {
                    STC_EFFECT eff;
                    eff.wEffId = passConfig->wAttackEff[i];
                    eff.wLv = passive->wLv;
                    for (int k = 0; k < arrMy.size(); ++k) {
                        arrMy[k]->addnewEff(eff);
                    }
                    arrMyEff.push_back(eff);
                }
            }
        
        }
        if (!enemy) {
            continue;
        }
        
        //三个buff 由一个buff命中决定，要触发都触发，不触发就都不触发，所以只判断一次（除概率触发技能，都由客户端判断触发）}
        if (i == 0 && (passConfig->byTriggerType == E_PASSIVE_TYPE_AUTO || passConfig->wStrikeCondition1 != E_PASSIVE_STRIPE_RATE)) {
            triggerEnemyBuff = rand() % 100 < passConfig->wDeffenseBuffHit;
        }
        
        //可叠加buff}
        for (int j = 0; j < cnt; j++) {
            if (passConfig->wDeffenseBuff[i])
            {
                if(triggerEnemyBuff || (trigger.wSize > 0 && trigger.byEnemyBuffHit == 1))
                {
                    STC_BUFF buff;
                    buff.wBuffId = passConfig->wDeffenseBuff[i];
                    buff.wStartRound = FightAI::Get()->getCurRound();
                    buff.wLastRound = passConfig->wDeffenseBuffTime[i];
                    
                    for (int k = 0; k < arrEnemy.size(); ++k) {
                        
                        //                    if ((FightAI::Get()->isMyAttack() && arrEnemy[k]->getPetInfo().wBattleIndex > PetCnt)
                        //                        ||(!FightAI::Get()->isMyAttack() && arrEnemy[k]->getPetInfo().wBattleIndex <= PetCnt)) {
                        //                        buff.wLastRound++;
                        //                    }
                        //招财猫免疫任何buff
                        if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE
                            && arrEnemy[k]->getPetInfo().wBattleIndex > PetCnt) {
                            continue;
                        }
                        arrEnemy[k]->addNewBuff(buff);
                    }
                    //                enemy->addNewBuff(buff);
                }
            }
            
            if (passConfig->wDeffenseEff[i])
            {
                bool triggerEff = false;
                if(passConfig->byTriggerType == E_PASSIVE_TYPE_AUTO || passConfig->wStrikeCondition1 != E_PASSIVE_STRIPE_RATE){
                    triggerEff = rand() % 100 < passConfig->wDeffenseEffHit[i];
                }
                
                if (triggerEff || (trigger.wSize > 0 && trigger.arrMyEffHit[i] == 1)) {
                    STC_EFFECT eff;
                    eff.wEffId = passConfig->wDeffenseEff[i];
                    eff.wLv = passive->wLv;
                    for (int k = 0; k < arrEnemy.size(); ++k) {
                        arrEnemy[k]->addnewEff(eff);
                    }
                    arrEnemyEff.push_back(eff);
                    //                enemy->addnewEff(eff);
                }
            }
        }
    }
    
    
    for (int i = 0; i < arrMy.size(); ++i) {
        STC_PET_EFF_BY_PSKILL pskillEff;
        pskillEff.fightId = arrMy[i]->getPetInfo().wBattleIndex;
        pskillEff.arrEff = arrMyEff;
        pskillEff.arrBuff = arrMy[i]->getMapBuff();
        
        tPSkill.arrMyEffsAndBuff.push_back(pskillEff);
    }
    
    for (int i = 0; i < arrEnemy.size(); ++i) {
        STC_PET_EFF_BY_PSKILL pskillEff;
        pskillEff.fightId = arrEnemy[i]->getPetInfo().wBattleIndex;
        pskillEff.arrEff = arrEnemyEff;
        pskillEff.arrBuff = arrEnemy[i]->getMapBuff();
        
        tPSkill.arrEnemyEffsAndBuff.push_back(pskillEff);
    }
    
    return tPSkill;
}

//触发主动技能带出的eff和buff}
STC_PET_EFF_BY_USKILL FightPet::triggerUltBuffAddEff(FightPet *enemy, uint32 skillId)
{
    STC_PET_EFF_BY_USKILL stcUSkill;
    //主动技能时，所有目标对象都属于Enemy，即使是攻击者本身}
    if (!enemy) {
        return stcUSkill;
    }
//    STC_BUFF buffM;
//    switch (getPetInfo().wBattleIndex) {
//        case 1:
//            buffM.wBuffId = 2143005;//zhongdu
//            break;
//        case 2:
//            buffM.wBuffId = 1073005;//zhuoshao
//            break;
//        case 3:
//            buffM.wBuffId = 1113000;//fengying
//            break;
//        case 5:
//            buffM.wBuffId = 1103000;//mabi
//            break;
//        case 4:
//            buffM.wBuffId = 1083050;//bingdong
//            break;
//        case 6:
//            buffM.wBuffId = 1173000;//hunluan
//            break;
//            
//        default:
//            break;
//    }
//    if (buffM.wBuffId) {
//        buffM.wStartRound = FightAI::Get()->getCurRound();
//        buffM.wLastRound = 2;
//        addNewBuff(buffM);
//    }
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *ulimateConfig = GET_CONFIG_STC(UltimateSkillConfig, skillId);
    if (!ulimateConfig) {
        return stcUSkill;
    }
    bool triggerFlag = true;
    uint16 wRound = FightAI::Get()->getCurRound();
    if (ulimateConfig->wStripeCondition) {
        triggerFlag = false;
        switch (ulimateConfig->wStripeCondition) {
            case E_PASSIVE_STRIPE_POISON: //关于中毒}
                if (enemy && enemy->HasPalsyBuff(wRound)) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_FROZEN: //关于冰冻}
                if (enemy && enemy->HasFrozenBuff(wRound)) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_FIRING: //关于灼烧}
                if (enemy && enemy->HasFiringBuff(wRound)) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_PALSY: //关于麻痹}
                if (enemy && enemy->HasPalsyBuff(wRound)) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_SEAL: //关于封印}
                if (enemy && enemy->HasSealBuff(wRound)) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_ADD_SPEED: //关于加速}
                if (enemy && enemy->HasNumSpeedAddBuff(wRound)) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_DEC_SPEED: //关于减速}
                if (enemy && enemy->HasNumSpeedDecBuff(wRound)) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_CONFUSED: //关于混乱}
                if (enemy && enemy->HasConfusedBuff(wRound)) {
                    triggerFlag = true;
                }
                break;

                break;
            case E_PASSIVE_STRIPE_DIE_ONE: //  我方死亡1人}
                if (m_MyTeam->getDeadPetCount() > 0) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_SPEED_HIGH: //速度高于自身}
                if (enemy && enemy->getCurSpeed(wRound) > getCurSpeed(wRound)) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_ONLY_ONE: //我方存活1}
                if (m_MyTeam->getLivePetCount() > 0) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_SPEED_LOWER: //速度低于自身}
                if (enemy && enemy->getCurSpeed(wRound) < getCurSpeed(wRound)) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_HP_HIGH: //生命高于敌方}
                if (enemy && enemy->getCurHP() < getCurHP()) {
                    triggerFlag = true;
                }
                break;
            case E_PASSIVE_STRIPE_HP_LOWER: //生命低于敌方}
                if (enemy && enemy->getCurHP() > getCurHP()) {
                    triggerFlag = true;
                }
                break;
                
            default:
                triggerFlag = true;
                break;
        }
    }
    
    if (!triggerFlag) {
        return stcUSkill;
    }
    
    int len = 0;
    GET_ARRAY_LEN(ulimateConfig->wAttackBuff, len);
    
    
    
    //对己方}
    if (abs(getPetInfo().wBattleIndex - enemy->getPetInfo().wBattleIndex) < PetCnt) {
        bool hit = FightAI::Get()->RandEither(ulimateConfig->wAttackBuffHit, 100);
        for (int i = 0; i < len; i++) {
            if (ulimateConfig->wAttackBuff[i]
                && hit)
            {
                STC_BUFF buff;
                buff.wBuffId = ulimateConfig->wAttackBuff[i];
                buff.wStartRound = FightAI::Get()->getCurRound();
                buff.wLastRound = ulimateConfig->wAttackBuffTime[i];
                
                enemy->addNewBuff(buff);
            }
            
            if (ulimateConfig->wAttackEff[i]
                && FightAI::Get()->RandEither(ulimateConfig->wAttackEffHit[i], 100))
            {
                STC_EFFECT eff;
                eff.wEffId = ulimateConfig->wAttackEff[i];
                //                eff.dwValue
                eff.wLv = getPetInfo().wSkillLv;
                enemy->addnewEff(eff);
                stcUSkill.arrEff.push_back(eff);
            }
        }
    }
    //对敌方}
    else{
        bool hit = FightAI::Get()->RandEither(ulimateConfig->wDeffenseBuffHit, 100);
        for (int i = 0; i < len; i++) {
            int eIndex = enemy->getPetInfo().wBattleIndex;
            eIndex = eIndex%100 - 1;
            if (ulimateConfig->wDeffenseBuff[i]
                && hit)//skillTriggerCounter < arrSkillTrigger.size() && arrSkillTrigger[skillTriggerCounter].byEnemyBuffHit[eIndex] == 1)
            {
                skillTriggerUsedFlag = true;
                STC_BUFF buff;
                buff.wBuffId = ulimateConfig->wDeffenseBuff[i];
                buff.wStartRound = FightAI::Get()->getCurRound();
                buff.wLastRound = ulimateConfig->wDeffenseBuffTime[i];
                //招财猫免疫任何buff
                if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE
                    && enemy->getPetInfo().wBattleIndex > PetCnt) {
                    
                }
                else{
                    enemy->addNewBuff(buff);
                }
                
                
            }
            
            if (ulimateConfig->wDeffenseEff[i])
                //&& skillTriggerCounter < arrSkillTrigger.size() && arrSkillTrigger[skillTriggerCounter].arrEnemyEffHit[eIndex][i] == 1)
            {
                bool effHit = FightAI::Get()->RandEither(ulimateConfig->wDeffenseEffHit[i], 100);
                if (effHit) {
                    skillTriggerUsedFlag = true;
                    STC_EFFECT eff;
                    eff.wEffId = ulimateConfig->wDeffenseEff[i];
                    eff.wLv = getPetInfo().wSkillLv;
                    enemy->addnewEff(eff);
                    stcUSkill.arrEff.push_back(eff);
                }
                
            }
        }
    }
    stcUSkill.arrBuff = enemy->getMapBuff();
    
    return stcUSkill;
}

std::vector<STC_TRIGGERED_PSKILL> FightPet::effPSkillActive(std::vector<STC_TRIGGERED_PSKILL> arrTPSkill, int damage)
{
    for (int i = 0; i < arrTPSkill.size(); ++i) {
        STC_TRIGGERED_PSKILL *tpSkill = &arrTPSkill[i];
        if (tpSkill->wSkillIndex == 0) {
            continue;
        }
        for (int k = 0; k < tpSkill->arrMyEffsAndBuff.size(); ++k) {
            STC_PET_EFF_BY_PSKILL *petEff = &tpSkill->arrMyEffsAndBuff[k];
            FightPet *pet = FightAI::Get()->getFightPetByBIndex(petEff->fightId);
            if (!pet || pet->getCurHP() <= 0) {
                continue;
            }
            petEff->arrEff = pet->effActive(petEff->arrEff, damage, pet);
        }
        
        for (int k = 0; k < tpSkill->arrEnemyEffsAndBuff.size(); ++k) {
            STC_PET_EFF_BY_PSKILL *petEff = &tpSkill->arrEnemyEffsAndBuff[k];
            FightPet *pet = FightAI::Get()->getFightPetByBIndex(petEff->fightId);
            if (!pet || pet->getCurHP() <= 0) {
                continue;
            }
            petEff->arrEff = pet->effActive(petEff->arrEff, damage, pet);
        }
    }
    
    return arrTPSkill;
}

std::vector<STC_EFFECT> FightPet::effActive(std::vector<STC_EFFECT> arrEff, int damage, FightPet *pet)
{
    std::vector<STC_EFFECT> arrMyEff;
    for (int i = 0; i < arrEff.size(); i++) {
        SkillEffectConfig::STC_SKILL_EFFECT_CONFIG *cfg = GET_CONFIG_STC(SkillEffectConfig, arrEff[i].wEffId);
        if (!cfg) {
            continue;
        }
        STC_EFFECT eff;
        switch (cfg->byType) {
            case E_EFFECT_CRIT_HIT:         //暴击}
                //                effAdd += critAdd;
                //                attData.isCrit = true;
                break;
            case E_EFFECT_DOUBLE_HIT:       //连击}
                pet->setDoubleCount(pet->getDoubleCount()+cfg->szSkillPara[0]);
                break;
            case E_EFFECT_RECOVER_HP_CUR:   //回血（当前血量）}
                eff.wEffId = cfg->wIndex;
                eff.dwValue = pet->getCurHP() * cfg->szSkillPara[0] / 10000;
                arrMyEff.push_back(eff);
                pet->addHP(eff.dwValue);
                break;
            case E_EFFECT_RECOVER_HP_MAX:   //回血（最大血量）}
                eff.wEffId = cfg->wIndex;
                eff.dwValue = pet->getPetInfo().wHP * cfg->szSkillPara[0] / 10000;
                arrMyEff.push_back(eff);
                pet->addHP(eff.dwValue);
                break;
            case E_EFFECT_UNLOCK_STATE:     //解状态（解DeBuff）}
                pet->unlockBuff(cfg->wIndex);
                break;
            case E_EFFECT_SPECIAL_ITEM:     //掉心珠}
                //掉心珠}
                eff.wEffId = cfg->wIndex;
                eff.dwValue = cfg->szSkillPara[0];
                arrMyEff.push_back(eff);
                break;
            case E_EFFECT_SUCK_BLOOD:     //吸血}
                eff.wEffId = cfg->wIndex;
                //吸伤害的百分比}
                eff.dwValue = cfg->szSkillPara[0] * damage / 10000;
                arrMyEff.push_back(eff);
                pet->addHP(eff.dwValue);
                
                break;
            case E_EFFECT_RECOVER_HP:     //回复数值}
                eff.wEffId = cfg->wIndex;
                //回复相当于 配置数 个心珠回血的量}
                eff.dwValue = cfg->szSkillPara[0] * REHP(pet->getRecover(0), FightAI::Get()->getDamFloat().dwRecoverFloat);// / 3;
                arrMyEff.push_back(eff);
                pet->addHP(eff.dwValue);
                break;
            case E_EFFECT_INITIAL_ADD:  //必杀值增加}
                eff.wEffId = cfg->wIndex;
                eff.dwValue = cfg->szSkillPara[0];
                arrMyEff.push_back(eff);
                pet->addPower(FightAI::Get()->getCurRound(), eff.dwValue);
                break;
            case E_EFFECT_INITIAL_DEC: //必杀值减少}
                eff.wEffId = cfg->wIndex;
                eff.dwValue = cfg->szSkillPara[0];
                arrMyEff.push_back(eff);
                pet->addPower(FightAI::Get()->getCurRound(), -eff.dwValue);
                break;
            default:
                break;
        }
    }
    return arrMyEff;
    //    return arrMyEff;
}

void FightPet::updateHpBuff(uint16 wRound)
{
    if (getCurHP() <= 0 && getIsCanDead()) {
        return;
    }
    bool flag = true;
    //验证回血或掉血}
    buffAddorLoseHp(flag);
    
    //清除到期的Buff}
    std::map<uint8, std::vector<STC_BUFF> >::iterator it = m_mapBuff.begin();
    for (; it != m_mapBuff.end(); it++) {
        std::vector<STC_BUFF> arrbuff = it->second;
        for (int i = 0; i < arrbuff.size(); i++) {
            STC_BUFF buff = arrbuff[i];
            if (buff.wBuffId == 0)
            {
                continue;
            }
            SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffCfg = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
            if (!buffCfg) {
                continue;
            }
            /*
            E_BUFF_NUM_RECOVER	= 3,				// 数值类 回复}
            E_BUFF_RECOVERY		= 6,				// 心珠回复 6}
            E_BUFF_FIRING		= 7,				// 灼烧 7}
            E_BUFF_FROZEN		= 8,				// 冰冻 8}
            E_BUFF_BIND			= 9,				// 缠绕 9}
            E_BUFF_POISON		= 14,				// 中毒 14}
            E_BUFF_HP_MAX_RATE	= 19,				// 最大血量百分比回复 19}
            */
            switch (buffCfg->wType) {
                case E_BUFF_NUM_RECOVER:
                case E_BUFF_RECOVERY:
                case E_BUFF_FIRING:
                case E_BUFF_FROZEN:
                case E_BUFF_BIND:
                case E_BUFF_POISON:
                case E_BUFF_HP_MAX_RATE:
                {
                    if (buff.wStartRound <= wRound)
                    {
                        if (buff.wLastRound > 1) {
                            buff.wLastRound--;
                        }
                        else{
                            buff.wBuffId = 0;
                            buff.wLastRound = 0;
                            buff.dwValuePara = 0;
                        }
                        arrbuff[i] = buff;
                    }
                }
                    break;
                default:
                    break;
            }
            
            
        }
        it->second = arrbuff;
    }
    
    //叠加buff}
    it = m_mapSpecBuff.begin();
    for (; it != m_mapSpecBuff.end(); it++) {
        std::vector<STC_BUFF> arrbuff = it->second;
        std::vector<STC_BUFF> arrspecbuff;
        for (int i = 0; i < arrbuff.size(); i++) {
            STC_BUFF buff = arrbuff[i];
            if (buff.wBuffId == 0)
            {
                continue;
            }
            SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffCfg = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
            if (!buffCfg) {
                continue;
            }
            switch (buffCfg->wType) {
                case E_BUFF_NUM_RECOVER:
                case E_BUFF_RECOVERY:
                case E_BUFF_FIRING:
                case E_BUFF_FROZEN:
                case E_BUFF_BIND:
                case E_BUFF_POISON:
                case E_BUFF_HP_MAX_RATE:
                {
                    if (buff.wStartRound > wRound) {
                        arrspecbuff.push_back(buff);
                    }
                    else{
                        if (buff.wLastRound > 1) {
                            buff.wLastRound--;
                            arrspecbuff.push_back(buff);
                        }
                    }
                }
                    break;
                default:
                    break;
            }
            
        }
        m_mapSpecBuff[it->first] = arrspecbuff;
    }
}

//更新Buff}
void FightPet::updateBuff(uint16 wRound)
{
    
    if (getCurHP() <= 0 && getIsCanDead()) {
        return;
    }
    
    //清除到期的Buff}
    std::map<uint8, std::vector<STC_BUFF> >::iterator it = m_mapBuff.begin();
    for (; it != m_mapBuff.end(); it++) {
        std::vector<STC_BUFF> arrbuff = it->second;
        for (int i = 0; i < arrbuff.size(); i++) {
            STC_BUFF buff = arrbuff[i];
            if (buff.wBuffId == 0)
            {
                continue;
            }
            SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffCfg = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
            if (!buffCfg) {
                continue;
            }
            
            /*
             E_BUFF_NUM_RECOVER	= 3,				// 数值类 回复}
             E_BUFF_RECOVERY		= 6,				// 心珠回复 6}
             E_BUFF_FIRING		= 7,				// 灼烧 7}
             E_BUFF_FROZEN		= 8,				// 冰冻 8}
             E_BUFF_BIND			= 9,				// 缠绕 9}
             E_BUFF_POISON		= 14,				// 中毒 14}
             E_BUFF_HP_MAX_RATE	= 19,				// 最大血量百分比回复 19}
             */
            switch (buffCfg->wType) {
                case E_BUFF_NUM_RECOVER:
                case E_BUFF_RECOVERY:
                case E_BUFF_FIRING:
                case E_BUFF_FROZEN:
                case E_BUFF_BIND:
                case E_BUFF_POISON:
                case E_BUFF_HP_MAX_RATE:
                
                    break;
                default:
                {
                    if (buff.wStartRound <= wRound)
                    {
                        if (buff.wLastRound > 1) {
                            buff.wLastRound--;
                        }
                        else{
                            buff.wBuffId = 0;
                            buff.wLastRound = 0;
                        }
                        arrbuff[i] = buff;
                    }
                }
                    break;
            }
        }
        it->second = arrbuff;
    }
    
    //叠加buff}
    it = m_mapSpecBuff.begin();
    for (; it != m_mapSpecBuff.end(); it++) {
        std::vector<STC_BUFF> arrbuff = it->second;
        std::vector<STC_BUFF> arrspecbuff;
        for (int i = 0; i < arrbuff.size(); i++) {
            STC_BUFF buff = arrbuff[i];
            if (buff.wBuffId == 0)
            {
                continue;
            }
            SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffCfg = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
            if (!buffCfg) {
                continue;
            }
            switch (buffCfg->wType) {
                case E_BUFF_NUM_RECOVER:
                case E_BUFF_RECOVERY:
                case E_BUFF_FIRING:
                case E_BUFF_FROZEN:
                case E_BUFF_BIND:
                case E_BUFF_POISON:
                case E_BUFF_HP_MAX_RATE:
                
                    break;
                default:
                {
                    if (buff.wStartRound > wRound) {
                        arrspecbuff.push_back(buff);
                    }
                    else{
                        if (buff.wLastRound > 1) {
                            buff.wLastRound--;
                            arrspecbuff.push_back(buff);
                        }
                    }
                }
                    break;
            }
        }
        m_mapSpecBuff[it->first] = arrspecbuff;
    }
    
}
STC_BATTLE_DATA FightPet::getAttackData(STC_START_BATTLE_DATA sData , uint16 wRound)
{
    STC_BATTLE_DATA battData;
    battData.wSkillId = sData.dwSkillId;
    
    battData.wBattleIndex = getPetInfo().wBattleIndex;
    battData.eEffObj = sData.eEffObj;
    
    critTriggerUsedFlag = false;
    skillTriggerUsedFlag = false;
    
    int allDamege = 0;
    
    //如果是技能攻击，并且，攻击的同时给自己方加buff}
    bool bRealSkill = false;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, sData.dwSkillId);
    if (ultCfg) {
        
        std::map<uint16, std::vector<STC_EFFECT> > mapEffToMy = ultSkillToMyBuff(sData.dwSkillId);
        std::map<uint16, std::vector<STC_EFFECT> >::iterator it = mapEffToMy.begin();
        for (; it != mapEffToMy.end(); it++) {
            if (it->second.size() == 0) {
                continue;
            }
            FightPet* eP = FightAI::Get()->getFightPetByBIndex(it->first);
            if (!eP) {
                continue;
            }
            
            it->second = effActive(it->second, 0, eP);
        }
        
        battData.mapEffToMy = mapEffToMy;
        
        bRealSkill = ultCfg->byType == 1;
        if (bRealSkill) {
            m_curPower = 0;
        }
        
    }
    
    for (int i = 0; i < sData.arrEnemyIndexs.size(); i++) {
        FightPet* tmpIt = FightAI::Get()->getFightPetByBIndex(sData.arrEnemyIndexs[i]);
        if (!tmpIt) {
            continue;
        }
        STC_ATTACK_DATA attData;
        STC_PET_INFO enemyInfo = tmpIt->getPetInfo();
        
        attData.wEnemyIndex = enemyInfo.wBattleIndex;

        
        attData.curPower = tmpIt->getCurPower();
        //如果对己方攻击，则只可能是 技能攻击并且只会加buff和eff，不会有伤害}
        if (abs(sData.wBattleIndex - enemyInfo.wBattleIndex) < PetCnt) {
            
            STC_PET_EFF_BY_USKILL uSkillEff = triggerUltBuffAddEff(tmpIt, sData.dwSkillId);

            attData.arrEnemyBuff = tmpIt->getMapBuff();
            attData.arrEnemyEff = effActive(uSkillEff.arrEff, allDamege, tmpIt);//tmpIt->getArrEff();
//            attData.altEffAndBuff = uSkillEff;
            battData.arrAttData[attData.wEnemyIndex] = attData;
            
            continue;
        }
        
        //这个arrEff只是用在战斗计算时验证暴击 和加伤减伤的，所以每个战斗包开始时都要清空，然后在技能触发中填充}
        m_arrEff.clear();
        tmpIt->setArrEff(m_arrEff);
        
        passiveSkillTriggerUsedFlag = false;
        
        
        std::vector<STC_TRIGGERED_PSKILL> arrTPSkill;
        
        
       
        attData.isHit = false;
//        if (sData.dwSkillId) {
//            attData.isHit = true;
//        }
//        else
        if (tmpIt->HasDodgeBuff(wRound))
        {
            attData.isHit = false;
        }
        else
        {
            uint32 myhit = m_petInfo.wHit;
            uint32 enemyDodge = tmpIt->getPetInfo().wDodge;
            float hit = myhit * 100 / (myhit+enemyDodge);
            //        CCLog("hit******hit******hit******hit****** %f ", hit);
            
            //1、计算100次样本中不命中次数}
            uint8 unHitCnt = 10 * (100 - hit) / 100;
            //非重复洗牌（累计之前连续未命中次数，以降低此次未命中概率）}
            unHitCnt = unHitCnt < m_unHitCnt ? 0 : unHitCnt - m_unHitCnt;
            uint8 v = unHitCnt == 0? 10 : 10 / unHitCnt;
            
            //2、创建一个100次攻击的数组, 把所有的不命中次数平均分配到数组中}
            std::vector<uint8> arrHit;
            for (int i = 0; i < 10; i++) {
                if (i%v == 0 && unHitCnt > 0) {
                    arrHit.push_back(0);//未命中}
                    unHitCnt--;
                }
                else
                {
                    arrHit.push_back(1);//命中}
                }
            }
            //3、在该数组中随机取一个，作为此次命中情况}
            uint8 randHit = rand() % 10;
            if (arrHit[randHit]) {
                attData.isHit = true;
//                m_unHitCnt = 0; //命中后重新洗牌(改为每波次洗牌)}
            }
            else
            {
                attData.isHit = false;
            }
        }
        
        //未命中时}
        if (!attData.isHit) {
            //判断有没有闪避触发技能（敌方闪避时，敌方触发的技能）}
            
            arrTPSkill = tmpIt->checkPassiveDodge(this);
//            triggerBuffAddEff(wRound, tmpIt, sData.dwSkillId);
            arrTPSkill = effPSkillActive(arrTPSkill, allDamege);
//            effActive(allDamege, tmpIt);
            attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_BATTLE] = arrTPSkill;
            
            attData.arrMyBuff = getMapBuff();
            attData.arrEnemyBuff = tmpIt->getMapBuff();
//            attData.arrEnemyEff = tmpIt->getArrEff();
            battData.arrAttData[attData.wEnemyIndex] = attData;
            continue;
        }
        
        
        m_dwCurAtk = 0;
        
        int atk = 0;
        int def = 0;
        int damage = 0;
        
        
        if (ultCfg && ultCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
            float atkAdd = checkAtkAddByBuff(wRound, E_SPELL_HURT_SPE_ATK);
            float defAdd = tmpIt->checkDefAddByBuff(wRound, E_SPELL_HURT_SPE_ATK);
            //特攻、特防
            atk = getPetInfo().wSAttack;
            def = enemyInfo.wSDefense;
            
            atk += getPetInfo().wBaseSAttack*atkAdd / 10000;
            def += enemyInfo.wBaseSDefense*defAdd / 10000;
        }
        else{
            //查看pet的 Buff，看有没有加攻击或者降攻击力的}
            float atkAdd = checkAtkAddByBuff(wRound, E_SPELL_HURT_NOR_ATK);
            //查看enemy的buff，看有没有加防御或者降防御的}
            //        std::vector<STC_BUFF> arrBUFF = tmpIt->getArrBuff();
            float defAdd = tmpIt->checkDefAddByBuff(wRound, E_SPELL_HURT_NOR_ATK);
            
            //普攻、普防
            atk = getPetInfo().wAttack;
            def = enemyInfo.wDefense;
            atk += getPetInfo().wBaseAttack*atkAdd / 10000;
            def += enemyInfo.wBaseDefense*defAdd / 10000;
        }
        
        //被动技能触发}
        std::vector<STC_PASSIVE_SKILL> arrTriggerPassive = checkPassvie(wRound, E_BATTLE_TIME_ROUND_START, E_PASSIVE_TYPE_IN_FIGHT, sData.dwSkillId, tmpIt);
        
        //buff触发}
        //当前攻击后 自己以及对方身上的全部buff}
        arrTPSkill = triggerBuffAddEff(wRound, tmpIt, arrTriggerPassive);
//        attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_BIGEN] = arrTPSkill;
        
        if (skillTriggerUsedFlag) {
            skillTriggerCounter++;
        }
        if (passiveSkillTriggerUsedFlag) {
            passiveSkillTriggerCounter++;
        }

        STC_PET_EFF_BY_USKILL uSkillEff;
        //计算伤害}
        m_dwCurAtk = atk;
        if (sData.dwSkillId)
        {
            uSkillEff = triggerUltBuffAddEff(tmpIt, sData.dwSkillId);
            //技能攻击时打出的伤害}
            damage = getUltimateDamage(atk, def, tmpIt->getCurHP(), sData.dwSkillId);
        }
        //如果主动技能都没造成伤害，则以普通攻击计算}
        if (!damage) {
            ATK(atk, def, (float)FightAI::Get()->getDamFloat().dwDamFloat / 10000, damage);
        }
        
        //判断属性相克}
        float atbAdd = checkAttributeRegulate(getPetInfo().petNature, enemyInfo.petNature);
        
        if (atbAdd < 0) {
            attData.regulateState = E_ATTRIBUTE_REGULATE_DOWN;
        }
        else if (atbAdd > 0)
        {
            attData.regulateState = E_ATTRIBUTE_REGULATE_UP;
        }
        else
        {
            attData.regulateState = E_ATTRIBUTE_REGULATE_NON;
        }
        
        
        //查看pet的加伤害或者减伤害Buff（包括队长技能和天赋技能）}
        float buffAdd = checkDamAddByBuff(tmpIt, wRound);
        //查看enemy加受伤害或者减受伤害的Buff（包括队长技能和天赋技能）}
        float buffDown = tmpIt->checkHitDamDownByBuff(this, wRound);
        
        //特攻或普攻伤害减少（天赋影响）
        float sDamSub = 0;
        float cDamSub = 0;
        
        if (ultCfg && ultCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
            sDamSub = tmpIt->GetTalentSDamSub();
        }
        else {
            cDamSub = tmpIt->GetTalentCDamSub();
        }
        buffDown += sDamSub + cDamSub;
        
        std::vector<STC_TRIGGERED_PSKILL> arrTPSkillHurt;
        arrTPSkillHurt.clear();
        if (damage > 0 && tmpIt->getCurHP() > 0) {
            //受伤触发}
            std::vector<STC_TRIGGERED_PSKILL> arrSkill = tmpIt->checkPassiveHurt(this);
            for (int s = 0; s < arrSkill.size(); ++s) {
                if (arrSkill[s].wSkillIndex) {
                    arrTPSkillHurt.push_back(arrSkill[s]);
                }
            }
        }
        
        attData.isCrit = critTiggerInFight(tmpIt->getPetInfo().wBattleIndex);
        //暴击触发}
        if (attData.isCrit) {
            std::vector<STC_TRIGGERED_PSKILL> arrSkill = checkPassiveCirt(tmpIt);
            for (int s = 0; s < arrSkill.size(); ++s) {
                if (arrSkill[s].wSkillIndex) {
                    arrTPSkillHurt.push_back(arrSkill[s]);
                }
            }
        }
        attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_BATTLE] = effPSkillActive(arrTPSkillHurt, damage);
        arrTPSkillHurt.clear();
        
        //检查eff效果，}
        //查看eff增加的伤害}
        float effAdd = HasNumDamageAddEff();
        if (attData.isCrit) {
            effAdd += getCritAdd();//FightAI::Get()->getDamFloat().dwCritFloat + GetLeaderCritDamAddValue() + GetTalentCritDamAdd();
        }
        //eff的减伤}
        float effDown = tmpIt->HasNumDamageDecEff();
        
        float lianxieAdd = getLianXieAdd();
        float weatherAdd = checkDamAddByWeather();
        
        //等级压制
        float lvAdd = (float)(getPetInfo().petLv - tmpIt->getPetInfo().petLv)*FightAI::Get()->getDamFloat().dwLvDamAdd / 10000;
        //阶级压制
        float evolvAdd = (float)(getPetInfo().byEvoLv - tmpIt->getPetInfo().byEvoLv)*FightAI::Get()->getDamFloat().dwEvoLvDamAdd / 10000;
        //计算总伤害}
        damage = (float)damage * (10000 + buffAdd - buffDown + atbAdd + effAdd - effDown + lianxieAdd + weatherAdd + lvAdd + evolvAdd) / 10000;
        
        //无敌时,只掉一滴血}
        if (tmpIt->HasInvincibleBuff(wRound)) {
            damage = 0;
        }
        
        uint8 byHurtType = E_SPELL_HURT_NOR_ATK;
        if (ultCfg) {
            byHurtType = ultCfg->byHurtType;
        }
        
        if ((byHurtType == E_SPELL_HURT_NOR_ATK && tmpIt->HasTalentImmuneCA())
            ||(byHurtType == E_SPELL_HURT_SPE_ATK && tmpIt->HasTalentImmuneSA())) {
            damage = 0;
        }
        
        //根据伤害值生成combo}
        //最好把掉落分配到comobo中}
        if (damage < 0) {
            damage = 0;
        }
        
        if (sData.eEffObj != E_EFFECT_OBJECT_MY) {
            attData.arrDamage = makeCombo(damage, sData.dwSkillId);
            attData.dwAllDamage = damage;
            
        }
        else
        {
            attData.dwAllDamage = 0;
        }
        allDamege += damage;
        
        //受伤回怒气}
        if (attData.dwAllDamage > 0 && attData.dwAllDamage < tmpIt->getCurHP()) {
            tmpIt->addHurtPower(wRound);
        }
        attData.curPower = tmpIt->getCurPower();
        attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_BIGEN] = effPSkillActive(arrTPSkill, damage);
        arrTPSkill.clear();
        
        //杀死触发  //死亡触发}
        if (attData.dwAllDamage >= tmpIt->getCurHP() && tmpIt->getCurHP() > 0) {
            std::vector<STC_TRIGGERED_PSKILL> arrSkill = checkPassiveKill(tmpIt);
            for (int s = 0; s < arrSkill.size(); ++s) {
                if (arrSkill[s].wSkillIndex) {
                    arrTPSkill.push_back(arrSkill[s]);
                }
            }
            
            std::vector<STC_TRIGGERED_PSKILL> arrSkillD = tmpIt->checkPassiveDead(this);
            for (int s = 0; s < arrSkillD.size(); ++s) {
                if (arrSkillD[s].wSkillIndex) {
                    arrTPSkill.push_back(arrSkillD[s]);
                }
            }
            
        }
        
        //伤害结算}
        tmpIt->loseHP(attData.dwAllDamage);
        
        attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_DEAD] = effPSkillActive(arrTPSkill, damage);
        
        
        
        //eff生效}
//        effActive(damage, tmpIt);
//        attData.arrPassiveSkill = effPSkillActive(arrTPSkill, damage);
//        effActive(uSkillEff.arrEff, allDamege, tmpIt);
//        attData.arrMyEff = effActive(uSkillEff.arrEff, allDamege, tmpIt);
        
        //战斗包中只需要存主动技能产生的Eff，因为被动技能的已经在被动技能包中包含了}
        attData.arrEnemyEff = effActive(uSkillEff.arrEff, damage, tmpIt);//tmpIt->getArrEff();
        
        attData.arrMyBuff = getMapBuff();
        attData.arrEnemyBuff = tmpIt->getMapBuff();
        
//        attData.mapPassEffAndBuff = getBattleEffAndBuffFromTPSkill(attData.mapPassiveSkill);
        
        //物品掉落}
        if (sData.wBattleIndex <= PetCnt) {
            //掉心珠}
            attData.arrItems = getDropItems(attData.dwAllDamage, tmpIt);
            
            //判断被动技能有没有触发掉心珠的eff}
            uint8 heartEff = HasNumHeartEff();
            for (int i = 0; i < heartEff; i++) {
                STC_ITEM_DROP item;
                item.wCount = 1;
                item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_HEART;
                attData.arrItems.push_back(item);
            }
            
            //掉物品}
            std::vector<STC_ITEM_DROP> vctItem = FightAI::Get()->getDropItemByDamage(attData.dwAllDamage, tmpIt);
            for (int i = 0; i < vctItem.size(); i++) {
                STC_ITEM_DROP item = vctItem[i];
                attData.arrItems.push_back(item);
            }
        }
        //        CCLog(" after att !~~~~~~~  %lu", m_petInfo.arrPassiveSkill.size());
        battData.arrAttData[attData.wEnemyIndex] = attData;
    }
    
    //不是技能攻击，并且本次攻击造成了实际伤害，回复一定的怒气}
    if (allDamege > 0 && !bRealSkill) {
        addBasePower(wRound);
    }
    if (critTriggerUsedFlag) {
        critTriggerCounter++;
    }
    battData.curPower = getCurPower();
    m_dwCurAtk = 0;
    return battData;
}

std::map<uint16, std::vector<STC_EFFECT> > FightPet::ultSkillToMyBuff(uint32 skillId)
{
    std::map<uint16, std::vector<STC_EFFECT> > mapEff;
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, skillId);
    if (ultCfg && ultCfg->byEffectNature2) {
        std::vector<uint16> arrEnemy;
        
        if (ultCfg->byAttackBuffScope == 1) {
            arrEnemy.push_back(getPetInfo().wBattleIndex);
        }
        else{
            uint8 cnt = 0;
            for (int i = 1; i <= PetCnt; ++i) {
                FightPet* petE = getMyTeam()->GetTeam()[i];
                if (!petE || petE->getCurHP() == 0){
                    continue;
                    if(ultCfg->byEffectNature2 != 7 && petE->getPetInfo().petNature != ultCfg->byEffectNature2) {
                        continue;
                    }
                }
                arrEnemy.push_back(petE->getPetInfo().wBattleIndex);
                cnt++;
                if (cnt >= ultCfg->byAttackBuffScope) {
                    break;
                }
            }
        }
        bool hit = FightAI::Get()->RandEither(ultCfg->wAttackBuffHit, 100);
        
        for (int p = 0; p < arrEnemy.size(); p++) {
            FightPet* enemy = FightAI::Get()->getFightPetByBIndex(arrEnemy[p]);
            if (!enemy) {
                continue;
            }
            
            std::vector<STC_EFFECT> arrEff;
            
            for (int i = 0; i < 3; i++) {
                if (ultCfg->wAttackBuff[i]
                    && hit)
                {
                    STC_BUFF buff;
                    buff.wBuffId = ultCfg->wAttackBuff[i];
                    buff.wStartRound = FightAI::Get()->getCurRound();
                    buff.wLastRound = ultCfg->wAttackBuffTime[i];
                    
                    enemy->addNewBuff(buff);
                }
                
                if (ultCfg->wAttackEff[i]
                    && FightAI::Get()->RandEither(ultCfg->wAttackEffHit[i], 100))
                {
                    STC_EFFECT eff;
                    eff.wEffId = ultCfg->wAttackEff[i];
                    //                eff.dwValue
                    eff.wLv = getPetInfo().wSkillLv;
                    enemy->addnewEff(eff);
                    arrEff.push_back(eff);
                }
            }
            
            mapEff[enemy->getPetInfo().wBattleIndex] = arrEff;
        }
    }
    
    return mapEff;
}

int FightPet::GetTalentAddValue(uint8 byType)
{
    int ret = 0;
    
    std::map<uint32, STC_PASSIVE_SKILL>::iterator it = m_petInfo.arrPassiveSkill.begin();
    for (; it != m_petInfo.arrPassiveSkill.end(); it++) {
        STC_PASSIVE_SKILL skill = it->second;
        if (skill.wIndex == 0 || skill.wIndex / E_UNITE_BASE_FABIO != E_SKILL_TYPE_TALENT) {
            continue;
        }
        TalentConfig::STC_TALENT_CONFIG * tCfg = GET_CONFIG_STC(TalentConfig, skill.wIndex);
        if (!tCfg) {
            continue;
        }
        if (tCfg->byTalentType == byType) {
            ret += skill.dwValue;
        }
    }
    
    return ret;
}

uint16 FightPet::HasTalentImmune(uint8 talentType)
{
    uint16 ret = 0;
    
    std::map<uint32, STC_PASSIVE_SKILL>::iterator it = m_petInfo.arrPassiveSkill.begin();
    for (; it != m_petInfo.arrPassiveSkill.end(); it++) {
        STC_PASSIVE_SKILL skill = it->second;
        if (skill.wIndex == 0 || skill.wIndex / E_UNITE_BASE_FABIO != E_SKILL_TYPE_TALENT) {
            continue;
        }
        TalentConfig::STC_TALENT_CONFIG * tCfg = GET_CONFIG_STC(TalentConfig, skill.wIndex);
        if (!tCfg) {
            continue;
        }
        if (tCfg->byTalentType == talentType) {
            ret = skill.wIndex;
        }
    }
    
    return ret;
}

//获取当前速度}
uint32 FightPet::getCurSpeed(uint8 round)
{
    return m_petInfo.wSpeed + m_petInfo.wBaseSpeed * (HasNumSpeedAddBuff(round) - HasNumSpeedDecBuff(round));
}
#pragma mark Leader
//有条件触发的队长技能（普通条件的队长技能由服务器加成后发送给我）}
int FightPet::GetLeaderAddSelfValue(uint8 byAddType)
{
    int ret = 0;
    
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG *leaderConfig = GET_CONFIG_STC(LeaderSkillConfig, getLeaderSkillId());
    do {
        if (!leaderConfig) {
            break;
        }
        
        bool flag = false;
        if (leaderConfig->wStrikeCondition != 0) {
            
            //条件触发的队长技能判断}
            switch (leaderConfig->wStrikeCondition) {
                case E_PASSIVE_STRIPE_RATE:
                    if (rand() % 100 < leaderConfig->szSkillPara[5]) {
                        flag = true;
                    }
                    break;
                case E_PASSIVE_STRIPE_LOWER_HP_MY:
                    if ((float)getCurHP() * 10000 / getPetInfo().wHP <= leaderConfig->szSkillPara[5]) {
                        flag = true;
                    }
                    break;
                case E_PASSIVE_STRIPE_UP_HP_MY:
                    if ((float)getCurHP() * 10000 / getPetInfo().wHP >= leaderConfig->szSkillPara[5]) {
                        flag = true;
                    }
                    break;
                default:
                    break;
            }
        }
        if (!flag) {
            return ret;
        }
//        if (byAddType == E_LEADER_SPELL_TYPE_ATTACK
//            ||byAddType == E_LEADER_SPELL_TYPE_DEF
//            ||byAddType == E_LEADER_SPELL_TYPE_RECOVER
//            ||byAddType == E_LEADER_SPELL_TYPE_HP) {
//            return ret;
//        }
        if (!(leaderConfig->byEffectNature1 == 7
              ||leaderConfig->byEffectNature2 == 7
              ||leaderConfig->byEffectNature1 == getPetInfo().petNature
              || leaderConfig->byEffectNature2 == getPetInfo().petNature))
        {
            break;
        }
        
        int len;
        GET_ARRAY_LEN(leaderConfig->wSkillType, len);
        for (int i = 0; i < len; i++) {
            if (leaderConfig->wSkillType[i] == byAddType) {
                ret += leaderConfig->szSkillPara[i];
                break;
            }
        }
    } while (0);
    
    return ret;
}

int FightPet::GetLeaderAddOtherValue(uint8 byAddType, uint8 byOtherNature)
{
    int ret = 0;
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG *leaderConfig = GET_CONFIG_STC(LeaderSkillConfig, getLeaderSkillId());
    do {
        if (!leaderConfig) {
            break;
        }
        bool flag = true;
        if (leaderConfig->wStrikeCondition != 0) {
            switch (leaderConfig->wStrikeCondition) {
                case E_PASSIVE_STRIPE_RATE:
                    if (rand() % 100 > leaderConfig->szSkillPara[5]) {
                        flag = false;
                    }
                    break;
                case E_PASSIVE_STRIPE_LOWER_HP_MY:
                    if ((float)m_MyTeam->GetTeamHp() / m_MyTeam->GetTeamHpMax() > leaderConfig->szSkillPara[5] / 100.0) {
                        flag = false;
                    }
                    break;
                case E_PASSIVE_STRIPE_UP_HP_MY:
                    if ((float)m_MyTeam->GetTeamHp() / m_MyTeam->GetTeamHpMax() < leaderConfig->szSkillPara[5] / 100.0) {
                        flag = false;
                    }
                    break;
                default:
                    break;
            }
        }
        if (!flag) {
            return ret;
        }
        if (!(leaderConfig->byEffectNature1 == 7
              ||leaderConfig->byEffectNature2 == 7
              ||leaderConfig->byEffectNature1 == byOtherNature
              || leaderConfig->byEffectNature2 == byOtherNature))
        {
            break;
        }
        
        int len;
        GET_ARRAY_LEN(leaderConfig->wSkillType, len);
        for (int i = 0; i < len; i++) {
            if (leaderConfig->wSkillType[i] == byAddType) {
                ret += leaderConfig->szSkillPara[i];
                break;
            }
        }
    } while (0);
    
    return ret;
}

uint32 FightPet::HasBuffTypeNum(uint8 byCurRound, uint8 byType)
{
    std::vector<STC_BUFF> arrbuff;
    if(m_mapBuff.find(byType) != m_mapBuff.end())
    {
       arrbuff = m_mapBuff[byType];
    }
    
    std::vector<STC_BUFF> arrSpecBuff;
    if(m_mapSpecBuff.find(byType) != m_mapSpecBuff.end())
    {
        arrSpecBuff = m_mapSpecBuff[byType];
    }
    
    for (int i = 0; i < arrbuff.size(); i++) {
        STC_BUFF buff = arrbuff[i];
        arrSpecBuff.push_back(buff);
    }
    
    int ret = 0;
    for (int i = 0; i < arrSpecBuff.size(); i++) {
        STC_BUFF buff = arrSpecBuff[i];
        if (buff.wBuffId == 0) {
            continue;
        }
        
        if (buff.wStartRound > byCurRound &&
            buff.wLastRound == 0) {
            continue;
        }
        
        SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffConfig = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
        if (buffConfig->wType == byType) {
            ret += buffConfig->buffPara[0];
        }
    }
    
    return ret;
}

uint16 FightPet::HasBuffTypeId(uint8 byCurRound, uint8 byType)
{
    std::vector<STC_BUFF> arrbuff;
    if(m_mapBuff.find(byType) != m_mapBuff.end())
    {
        arrbuff = m_mapBuff[byType];
    }
    
    std::vector<STC_BUFF> arrSpecBuff;
    if(m_mapSpecBuff.find(byType) != m_mapSpecBuff.end())
    {
        arrSpecBuff = m_mapSpecBuff[byType];
    }
    
    for (int i = 0; i < arrbuff.size(); i++) {
        STC_BUFF buff = arrbuff[i];
        arrSpecBuff.push_back(buff);
    }
    
    uint16 ret = 0;
    for (int i = 0; i < arrSpecBuff.size(); i++) {
        STC_BUFF buff = arrSpecBuff[i];
        if (buff.wBuffId == 0) {
            continue;
        }
        
        if (byCurRound == 0) {
            
        }
        else{
            if (buff.wStartRound > byCurRound &&
                buff.wLastRound == 0) {
                continue;
            }
        }
        
        SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffConfig = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
        if (buffConfig->wType == byType) {
            ret = buff.wBuffId;
            break;
        }
    }
    
    return ret;
}


int FightPet::GetBuffTypeValue( std::vector<STC_BUFF> arrbuff)
{
	int nAddHp = 0;
    for (int i = 0; i < arrbuff.size(); i++) {
        STC_BUFF buff = arrbuff[i];
        if (!buff.wBuffId) {
            continue;
        }
        
        SkillBuffConfig::STC_SKILL_BUFF_CONFIG * pInfo = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
        if (pInfo)
        {
            int hp = 0;
            switch (pInfo->wHurtType) {
                case E_BUFF_HURT_HEART_GEM:
                    hp += (float)getRecover(1) * pInfo->buffPara[0] / 3;
                    break;
                case E_BUFF_HURT_HP_CUR:
                    hp += (float)getCurHP() * pInfo->buffPara[0] / 10000;
                    break;
                case E_BUFF_HURT_HP_MAX:
                    hp += (float)getPetInfo().wHP * pInfo->buffPara[0] / 10000;
                    break;
                case E_BUFF_HURT_ATK:
                    hp += (float)buff.dwValuePara * pInfo->buffPara[0] / 10000;
                    break;
                default:
                    break;
            }
            
            if (hp == 0) {
                hp = 1;
            }
            if (pInfo->wBuffEff == E_BUFF_EFFECT_UPBUFF) {
                nAddHp += hp;
            }
            else if(pInfo->wBuffEff == E_BUFF_EFFECT_DEBUFF)
            {
                nAddHp -= hp;
            }
        }
    }
    
	return nAddHp;
}

int FightPet::checkAtkAddByBuff(uint16 wRound, uint8 attType)
{
    //攻击力，基本上是由服务器加成了的}
    int ret = 0;
    //队长技能}
    ret += GetLeaderAttackValue();
    
    //玉技能}
    
    //buff
    ret += HasNumAttackBuff(wRound);
    ret += HasNumAllBuff(wRound);
    if (attType == E_SPELL_HURT_SPE_ATK) {
        ret += HasNumSAttBuff(wRound);
    }
    else if (attType == E_SPELL_HURT_NOR_ATK){
        ret += HasNumCAttBuff(wRound);
    }
        
    //eff
    ret += HasNumAtkAddEff();
    return ret;
}

int FightPet::checkDefAddByBuff(uint16 wRound, uint8 attType)
{
    int ret = 0;
    //防御力，基本上是由服务器加成了的}
    //队长技能}
    ret += GetLeaderDefAddValue();
    
    //玉技能}
    
    //buff
    ret += HasNumDeffenseBuff(wRound);
    ret += HasNumAllBuff(wRound);
    if (attType == E_SPELL_HURT_SPE_ATK) {
        ret += HasNumSDefBuff(wRound);
    }
    else if (attType == E_SPELL_HURT_NOR_ATK){
        ret += HasNumCDefBuff(wRound);
    }
    return ret;
}

int FightPet::checkDamAddByBuff(FightPet* pDef, uint16 wRound)
{
    
    int ret = 0;
    //队长技能}
    //1、对某属性敌人 造成额外伤害；}
    ret += GetLeaderNatureDamOtherValue(pDef->getPetInfo().petNature);
    
    //天赋技能}
    ret += GetTalentNatureDamAdd(pDef->getPetInfo().petNature);
    ret += GetTalentDamAdd();
    PetConfig::STC_PET_CONFIG* petCfg = GET_CONFIG_STC(PetConfig, getPetInfo().wPetIndexId);
    if (petCfg && petCfg->byType2 == E_PET_FORM_DRAGRON) {
        ret += pDef->GetTalentDrogeHurtDamAdd();
    }
    //buff（暂时buff没有增加伤害的）}
    
    
    return ret;
}

int FightPet::checkHitDamDownByBuff(FightPet* pAttacker, uint16 wRound)
{
    int ret = 0;
    //队长技能}
    //1、抵御某属性伤害；}
    ret += GetLeaderNatureDefOtherValue(pAttacker->getPetInfo().petNature);
    //天赋技能}
    ret += GetTalentNatureDamSub(pAttacker->getPetInfo().petNature);
    ret += GetTalentDamSub();
    //buff
    return ret;
}

//属性相克}
int FightPet::checkAttributeRegulate(uint16 attNature, uint16 defNature)
{
    int ret = 0;
    InterPlayConfig::STC_INTER_PLAY_CONFIG *interConfig = GET_CONFIG_STC(InterPlayConfig, attNature);
    
    do {
        if (!interConfig) {
            break;
        }
        ret = interConfig->arrNature[defNature - 1] - 100;
        
        
    } while (0);
    
    return ret * 100;
}

//遗迹挑战中天气加成攻击力
int FightPet::checkDamAddByWeather()
{
    int ret = 0;
    
    if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_WRESTLE) {
        if (getPetInfo().petNature == WorldInfoDataMgr::Get()->getWeather()) {
            ret = 10000;    //暂时写死，回头再说
        }
    }
    return ret;
}

uint32 FightPet::HasEffNum(uint8 type)
{
    uint32 ret = 0;
    
    for (int i = 0; i < m_arrEff.size(); i ++) {
        if (m_arrEff[i].wEffId == 0) {
            continue;
        }
        
        SkillEffectConfig::STC_SKILL_EFFECT_CONFIG *effConfig = GET_CONFIG_STC(SkillEffectConfig, m_arrEff[i].wEffId);
        if (!effConfig || effConfig->byType != type) {
            continue;
        }
        
        uint16 lv = m_arrEff[i].wLv;
        if (type == E_EFFECT_CRIT_HIT) {
            ret = effConfig->wIndex;
            return ret;
        }
        ret += (effConfig->szSkillPara[0] + (lv - 1)* effConfig->szSkillPara[1]);
        
    }
    
    return ret;
}

//int FightPet::checkDamAddByEff()
//{
//    int ret = 0;
//    for (int i = 0; i < m_arrEff.size(); i ++) {
//        if (m_arrEff[i].wEffId == 0) {
//            continue;
//        }
//        uint16 lv = m_arrEff[i].wLv;
//        SkillEffectConfig::STC_SKILL_EFFECT_CONFIG *effConfig = GET_CONFIG_STC(SkillEffectConfig, m_arrEff[i].wEffId);
//        if (effConfig->byType == E_EFFECT_ADD_DAMAGE) {
//            ret += (effConfig->szSkillPara[0] + (lv - 1)* effConfig->szSkillPara[1]);
//        }
//    }
//    
//    return ret;
//}
//
//int FightPet::checkDamDownByEff()
//{
//    int ret = 0;
//    for (int i = 0; i < m_arrEff.size(); i ++) {
//        if (m_arrEff[i].wEffId == 0) {
//            continue;
//        }
//        uint16 lv = m_arrEff[i].wLv;
//        SkillEffectConfig::STC_SKILL_EFFECT_CONFIG *effConfig = GET_CONFIG_STC(SkillEffectConfig, m_arrEff[i].wEffId);
//        if (effConfig->byType == E_EFFECT_DEC_DAMAGE) {
//            ret += (effConfig->szSkillPara[0] + (lv - 1)* effConfig->szSkillPara[1]);
//        }
//    }
//    
//    return ret;
//}
//
////effect加攻击力}
//int FightPet::checkAttAddByEff()
//{
//    int ret = 0;
//    for (int i = 0; i < m_arrEff.size(); i ++) {
//        if (m_arrEff[i].wEffId == 0) {
//            continue;
//        }
//        uint16 lv = m_arrEff[i].wLv;
//        SkillEffectConfig::STC_SKILL_EFFECT_CONFIG *effConfig = GET_CONFIG_STC(SkillEffectConfig, m_arrEff[i].wEffId);
//        if (effConfig->byType == E_EFFECT_ADD_ATK) {
//            ret += (effConfig->szSkillPara[0] + (lv - 1)* effConfig->szSkillPara[1]);
//        }
//    }
//    
//    return ret;
//}

//暴击伤害加成（基础加成 + 队长技能加成 + 天赋技能加成 + buff）}
int FightPet::getCritAdd()
{
    return FightAI::Get()->getDamFloat().dwCritFloat + GetLeaderCritDamAddValue() + GetTalentCritDamAdd() + HasNumCritDamageBuff(FightAI::Get()->getCurRound());
}

int FightPet::checkRestoreAdd(uint16 wRound)
{
    int ret = 0;
    //队长技能加的回复}
    ret += GetLeaderRecoverValue();
    //Buff加的回复}
    ret += HasNumRecoverBuff(wRound);
    
    return ret;
}

std::map<uint16, STC_FRAME_DAMAGE> FightPet::makeCombo(int& allDamage, uint32 skillId )
{
    std::map<uint16, STC_FRAME_DAMAGE> arrDam;
    int realDamege = 0;
    PetConfig::STC_PET_CONFIG *petConfig = GET_CONFIG_STC(PetConfig, getPetInfo().wPetIndexId);
    if (!petConfig) {
        return arrDam;
    }
    int comboid = petConfig->wComboId;
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *skill = GET_CONFIG_STC(UltimateSkillConfig, skillId);
    //普通攻击时虽然攻击是技能，但combo还是走pet表中的，combo要跟模型走
    if (skill && skill->byType == 1) {
        comboid = skill->wComboid;
    }
    
    ComboIdConfig::STC_COMBOID_CONFIG *stcCombo = GET_CONFIG_STC(ComboIdConfig, comboid);
    
    do {
        if (!stcCombo) {
            break;
        }
        int len;
        //当攻击不破防时，只能打出1点伤害，这时总伤害是1点，计算combo时，每次combo也是1点伤害}
        //如此会导致显示的伤害比实际总伤害要大一点点，所以就要调整计算的总伤害了}
        GET_ARRAY_LEN(stcCombo->dwComboPer, len);
        int lastFrame = 0;
        int lastDamege = allDamage;
        for (int i = 0; i < len; i++) {
            if (stcCombo->dwComboTime[i] == 0
                || stcCombo->dwComboPer[i] == 0) {
                break;
            }

            STC_FRAME_DAMAGE damage;
            damage.wFrame = stcCombo->dwComboTime[i];
            damage.dwDamege = stcCombo->dwComboPer[i] * allDamage / 1000;
            if (damage.dwDamege == 0)
            {
                damage.dwDamege = 1;
            }
            lastFrame = damage.wFrame;
            lastDamege -= damage.dwDamege;
            realDamege += damage.dwDamege;
            arrDam[damage.wFrame] = damage;
        }
        //调整误差，最后一次的伤害不按照配比计算了，用总伤害减去前面的所有伤害取得}
        if (arrDam.find(lastFrame) != arrDam.end() && lastDamege > 0 ) {
            arrDam[lastFrame].dwDamege += lastDamege;
            realDamege += lastDamege;
        }
    } while (0);
    if (allDamage != realDamege) {
        allDamage = realDamege;
    }
    return arrDam;
}

int FightPet::getUltimateDamage(int atk, int def, int curEnemyHp, uint32 skillId)
{
    int ret = 0;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *cfg = GET_CONFIG_STC(UltimateSkillConfig, skillId);
    do {
        if (!cfg) {
            break;
        }
        
        switch (cfg->byHurtType) {
            case E_SPELL_HURT_ABUSUTE:
                ret += getPetInfo().dwSkillValue;
                break;
            case E_SPELL_HURT_RATE:
                ret += (float)curEnemyHp * getPetInfo().dwSkillValue / 10000;
                break;
            case E_SPELL_HURT_NORMAL:
            case E_SPELL_HURT_SPE_ATK:
            case E_SPELL_HURT_NOR_ATK:
//                atk *= (float)getPetInfo().dwSkillValue / 10000;
                int dam;
                ATK(atk, def, (float)FightAI::Get()->getDamFloat().dwSkillFloat / 10000, dam);
                ret += dam * (float)getPetInfo().dwSkillValue / 10000;
                break;
            default:
                break;
        }
        
    } while (0);
    
    return ret;
}



bool FightPet::critTiggerInFight(uint16 wEnemyIndex)
{
    //验证Eff暴击触发}
    if (HasNumCritEff()) {
        return true;
    }
    
    //验证Buff暴击}
    int critAdd = HasNumAllBuff(FightAI::Get()->getCurRound());
    
    FightPet* enemy = FightAI::Get()->getFightPetByBIndex(wEnemyIndex);
    
    int critHit = getPetInfo().wLucky + GetLeaderCritAddValue() + critAdd - enemy->getPetInfo().wCritFree;
    
    if (FightAI::Get()->RandEither(critHit, 10000)) {
        return true;
    }

    //TODO: [2014-02-14] added by Juniechu
    
//    if (arrCritTrigger.size() <= critTriggerCounter) {
//        return false;
//    }
//    critTriggerUsedFlag = true;
//    if (arrCritTrigger[critTriggerCounter][wEnemyIndex % 100 - 1]) {
//        STC_EFFECT eff;
//        eff.wEffId = E_EFFECT_CRIT_HIT;
//        addnewEff(eff);
//        
//        return true;
//    }
    return false;
}

bool FightPet::addNewBuff(STC_BUFF buff)
{
    bool flag = false;
    SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffCfg = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
    if (!buffCfg) {
        return flag;
    }
    
    //验证免疫（天赋技能）
    switch (buffCfg->wType) {
        case E_BUFF_POISON:
            if(HasTalentImmunePoison())
            {
                return flag;
            }
            break;
        case E_BUFF_FIRING:
            if(HasTalentImmuneFiring())
            {
                return flag;
            }
            break;
        case E_BUFF_BIND:
            if(HasTalentImmuneBind())
            {
                return flag;
            }
            break;
        case E_BUFF_SEAL:
            if(HasTalentImmuneSeal())
            {
                return flag;
            }
            break;
        case E_BUFF_PALSY:
            if(HasTalentImmunePalsy())
            {
                return flag;
            }
            break;
        case E_BUFF_FROZEN:
            if(HasTalentImmuneFrozen())
            {
                return flag;
            }
            break;
            
        default:
            break;
    }
    
    if (buffCfg->byStartTime == 1) {//下回合生效
        buff.wStartRound++;
    }
    std::vector<STC_BUFF> arrbuff;
    if (buffCfg->buffPara[2]) {    //可叠加buff不做重复验证，直接添加}
//        arrbuff = m_mapSpecBuff[buffCfg->wType];

        if(m_mapSpecBuff.find(buffCfg->wType) != m_mapSpecBuff.end())
        {
            arrbuff = m_mapSpecBuff[buffCfg->wType];
        }
        
        arrbuff.push_back(buff);
        m_mapSpecBuff[buffCfg->wType] = arrbuff;
        flag = true;
    }
    else{                               //不可叠加buff，要验证同类buff，用效果最高的替换}
//        arrbuff = m_mapBuff[buffCfg->wType];

        if(m_mapBuff.find(buffCfg->wType) != m_mapBuff.end())
        {
            arrbuff = m_mapBuff[buffCfg->wType];
        }

        if (arrbuff.size() == 0) {
            arrbuff.push_back(buff);
        }
        else
        {
            int k = -1;
            for (int i = 0; i < arrbuff.size(); i++) {
                SkillBuffConfig::STC_SKILL_BUFF_CONFIG *cfg = GET_CONFIG_STC(SkillBuffConfig, arrbuff[i].wBuffId);
                if (cfg && cfg->wBuffEff == buffCfg->wBuffEff) {
                    k = i;
                    if (cfg->buffPara[0] <= buffCfg->buffPara[0]) {
                        arrbuff[i] = buff;
                        flag = true;        //flag只能代表新的buff是否替换了旧的buff，不能作为被动技能是否显示的标示}
                    }
                    break;
                }
                
            }
            if (k == -1) {
                arrbuff.push_back(buff);
            }
        }
        
        m_mapBuff[buffCfg->wType] = arrbuff;
    }
    return flag;
}

//新增buff显示飘字后
void FightPet::newToOldBuff()
{
    std::map<uint8, std::vector<STC_BUFF> >::iterator it = m_mapBuff.begin();
    for (; it != m_mapBuff.end(); it++) {
        std::vector<STC_BUFF> arrBuff = it->second;
        
        for (int i = 0; i < arrBuff.size(); i++) {
            STC_BUFF buff = arrBuff[i];
            if (!buff.wBuffId || !buff.isNew) {
                continue;
            }
            buff.isNew = false;
            arrBuff[i] = buff;
        }
        it->second = arrBuff;
    }
}

void FightPet::addnewEff(STC_EFFECT eff)
{
    SkillEffectConfig::STC_SKILL_EFFECT_CONFIG *effConfig = GET_CONFIG_STC(SkillEffectConfig, eff.wEffId);
    if (!effConfig) {
        return;
    }
    
    m_arrEff.push_back(eff);
    
}
void FightPet::unlockBuff(uint32 effId)
{
    SkillEffectConfig::STC_SKILL_EFFECT_CONFIG *effConfig = GET_CONFIG_STC(SkillEffectConfig, effId);
    if (!effConfig || effConfig->byType != E_EFFECT_UNLOCK_STATE) {
        return;
    }
    int len = 0;
    GET_ARRAY_LEN(effConfig->szSkillPara, len);
    for (int s = 0; s < len; s++) {
        if (effConfig->szSkillPara[s] == 0) {
            continue;
        }
        std::vector<STC_BUFF> arrbuff;
        if (m_mapBuff.find(effConfig->szSkillPara[s]) != m_mapBuff.end()) {
            arrbuff = m_mapBuff[effConfig->szSkillPara[s]];
        }
       
        for (int i = 0; i < arrbuff.size(); i++) {
            STC_BUFF buff = arrbuff[i];
            SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffCfg = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
            if (!buffCfg) {
                continue;
            }
            if (buffCfg->wBuffEff == E_BUFF_EFFECT_DEBUFF) {
                buff.wBuffId = 0;
                arrbuff[i] = buff;
            }
        }
        m_mapBuff[effConfig->szSkillPara[s]] = arrbuff;
        
        //可叠加buff}
        arrbuff.clear();
        if (m_mapSpecBuff.find(effConfig->szSkillPara[s]) != m_mapSpecBuff.end()) {
            arrbuff = m_mapSpecBuff[effConfig->szSkillPara[s]];
        }
        
        std::vector<STC_BUFF> arrspecbuff;
        for (int j = 0; j < arrbuff.size(); j++) {
            STC_BUFF buff = arrbuff[j];
            SkillBuffConfig::STC_SKILL_BUFF_CONFIG *buffCfg = GET_CONFIG_STC(SkillBuffConfig, buff.wBuffId);
            if (!buffCfg) {
                continue;
            }
            if (buffCfg->wBuffEff == E_BUFF_EFFECT_DEBUFF) {
                buff.wBuffId = 0;
                arrbuff[j] = buff;
            }
            else {
                arrspecbuff.push_back(buff);
            }
        }
        m_mapSpecBuff[effConfig->szSkillPara[s]] = arrspecbuff;
    }
    
}

int FightPet::eatHeart(int num, uint16 wRound)
{
    int recover = getRecover(wRound);
    int hp = num * REHP(recover, FightAI::Get()->getDamFloat().dwRecoverFloat);
    
    addHP(hp);
    
    return hp;
}

void FightPet::addBasePower(uint16 wRound)
{
    if (m_petInfo.wBattleIndex == 6) {
        CCLOG("curPower : %d", m_curPower);
    }
    if (m_IsWaitSkill || HasSealBuff(wRound)) {
        return;
    }
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *cfg = GET_CONFIG_STC(UltimateSkillConfig, getPetInfo().wSkillId);
    if (!cfg) {
        return;
    }
    m_curPower += getPetInfo().wPowerAdd;
    if (m_curPower > getPetInfo().wAllPower) {
        m_curPower = getPetInfo().wAllPower;
    }
}

void FightPet::addHurtPower(uint16 wRound)
{
    if (m_petInfo.wBattleIndex == 6) {
        CCLOG("curPower : %d", m_curPower);
    }
    if (m_IsWaitSkill || HasSealBuff(wRound)) {
        return;
    }
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *cfg = GET_CONFIG_STC(UltimateSkillConfig, getPetInfo().wSkillId);
    if (!cfg) {
        return;
    }
    m_curPower += getPetInfo().wPowerHurtAdd;
    if (m_curPower > getPetInfo().wAllPower) {
        m_curPower = getPetInfo().wAllPower;
    }
}

void FightPet::addPower(uint16 wRound, int value)
{
    if (m_petInfo.wBattleIndex == 6) {
        CCLOG("curPower : %d", m_curPower);
    }
    if (m_IsWaitSkill || HasSealBuff(wRound)) {
        return;
    }
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *cfg = GET_CONFIG_STC(UltimateSkillConfig, getPetInfo().wSkillId);
    if (!cfg) {
        return;
    }
    m_curPower += value;
    
    if (m_curPower < 0) {
        m_curPower = 0;
    }
    
    if (m_curPower > getPetInfo().wAllPower) {
        m_curPower = getPetInfo().wAllPower;
    }
}

std::vector<STC_ITEM_DROP> FightPet::getDropItems(int damage, FightPet *enemy)
{
    std::vector<STC_ITEM_DROP> items;
    if (damage <= 0) {
        return items;
    }
    //检测eff掉心珠}
    int heartCnt = 0;
    for (int i = 0; i < m_arrEff.size(); i++) {
        if (m_arrEff[i].wEffId == E_EFFECT_SPECIAL_ITEM) {
            heartCnt += m_arrEff[i].dwValue;
        }
    }
    //受到攻击时概率掉落心珠(50%概率)，掉一个}
    int n = enemy->getMaxDropHeart() - enemy->getCurHeart();
    if (n > 0 && rand() % 100 > 50) {
        if (enemy->getCurHP() > damage) {
            heartCnt++;
            enemy->setCurHeart(enemy->getCurHeart()+1);
        }
        else
        {
            heartCnt += n;
            enemy->setCurHeart(enemy->getMaxDropHeart());
        }
    }
    
    for (int i = 0; i < heartCnt; i++) {
        STC_ITEM_DROP item;
        item.wCount = 1;
        item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_HEART;
        items.push_back(item);
    }
    
    return items;
}

//Buff回血或掉血生效}
void FightPet::buffAddorLoseHp(bool flag)
{
    m_arrBufValue.clear();
    std::map<uint8, std::vector<STC_BUFF> >::iterator it = m_mapBuff.begin();
    int hp = 0;
    for (; it != m_mapBuff.end(); it++) {
        std::vector<STC_BUFF> arrbuff = it->second;
        STC_BUFF_VALUE bValue;
        switch (it->first) {
            case E_BUFF_RECOVERY:
//                if (!flag) {
//                    continue;
//                }
                bValue.dwValue = GetBuffTypeValue(arrbuff);
                bValue.byBuffType = E_BUFF_RECOVE_TYPE_ADD;
                
                break;
            case E_BUFF_FIRING:
            case E_BUFF_FROZEN:
            case E_BUFF_BIND:
            case E_BUFF_POISON:
//                if (flag) {
//                    continue;
//                }
                bValue.dwValue = GetBuffTypeValue(arrbuff);
                bValue.byBuffType = E_BUFF_RECOVE_TYPE_SUB;
                
                break;
            default:
                break;
        }
        if (bValue.dwValue == 0) {
            continue;
        }
        m_arrBufValue.push_back(bValue);
        hp += bValue.dwValue;
    }
    
    it = m_mapSpecBuff.begin();
    for (; it != m_mapSpecBuff.end(); it++) {
        std::vector<STC_BUFF> arrbuff = it->second;
        STC_BUFF_VALUE bValue;
        switch (it->first) {
            case E_BUFF_RECOVERY:
                //                if (!flag) {
                //                    continue;
                //                }
                bValue.dwValue = GetBuffTypeValue(arrbuff);
                bValue.byBuffType = E_BUFF_RECOVE_TYPE_ADD;
                
                break;
            case E_BUFF_FIRING:
            case E_BUFF_FROZEN:
            case E_BUFF_BIND:
            case E_BUFF_POISON:
                //                if (flag) {
                //                    continue;
                //                }
                bValue.dwValue = GetBuffTypeValue(arrbuff);
                bValue.byBuffType = E_BUFF_RECOVE_TYPE_SUB;
                
                break;
            default:
                break;
        }
        if (bValue.dwValue == 0) {
            continue;
        }
        m_arrBufValue.push_back(bValue);
        hp += bValue.dwValue;
    }
    
    addHP(hp);
}

void FightPet::addHP(int dwValue)
{
    if (m_curHP <= 0) {
        return;
    }
    if (dwValue < 0) {
        loseHP(-dwValue);
        return;
    }
    if (getIsCanDead() && m_curHP > 0) {
        m_curHP += dwValue;
    }
    if (m_curHP > m_petInfo.wHP) {
        m_curHP = m_petInfo.wHP;
    }
    
    CCLog("~~~~Fight~~Add~~ Id : %d, Add:%d, curHp:%d", m_petInfo.wBattleIndex, dwValue, m_curHP);
    
    m_MyTeam->AddTeamHp(dwValue);
};

void FightPet::loseHP(int dwValue)
{
    if (dwValue < 0) {
        addHP(-dwValue);
        return;
    }
    if (dwValue > m_curHP && m_isCanDead) {
        m_MyTeam->loseTeamHp(m_curHP);
        m_curHP = 0;
    }
    else
    {
        m_curHP -= dwValue;
        m_MyTeam->loseTeamHp(dwValue);
        if (m_curHP <= 0) {
            m_curHP = 0;
        }
    }
    CCLog("~~~~Fight~~Lose~~ Id : %d, Lose:%d, curHp:%d", m_petInfo.wBattleIndex, dwValue, m_curHP);
}