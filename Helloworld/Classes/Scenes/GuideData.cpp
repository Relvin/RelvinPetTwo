//
//  GuideData.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-3-13.}
//
//

#include "GuideData.h"
#include "ConfigGet.h"
#include "ConfigData.h"
#include "GameSession.h"
#include "Role.h"
#include "GuideLayer.h"
#ifdef GUIDE_OFF
#include "CcbPetBattleLayer.h"
#endif
#include "PadDefine.h"
#include "GlobalData.h"
#include "FightAI.h"
#include "StageScene.h"

#define kGuideTag 60143


static GuideData* m_pShared = NULL;

GuideData* GuideData::GetInstance()
{
    if (m_pShared == NULL) {
        m_pShared = new GuideData();
    }
    return m_pShared;
}

void GuideData::DestoryInstace()
{
    if (m_pShared) {
        delete m_pShared;
        m_pShared = NULL;
    }
}

GuideData::GuideData() {
    m_mapGuide.clear();
    m_mapData.clear();
    m_nStepId = 0;
    m_nGroupId = 0;
    m_dwSysLockId = 0;
}

void GuideData::Initialize() {
    if (m_mapGuide.size() > 0) {
        return;
    }
    
    std::map<uint16, GuideConfig::STC_GUIDE_CONFIG> guideMap = GET_CONFIG_MAP(GuideConfig);
    int idx = 0;
    std::map<uint16, GuideConfig::STC_GUIDE_CONFIG>::iterator iter;
    for (iter = guideMap.begin(); iter != guideMap.end(); iter++) {
        if (idx >= iter->first) {
            CCAssert(1, "may caused by following situation 1. Didn't read sequencely, 2. csv idx repeat.");
        }
        idx = iter->first;
        GuideConfig::STC_GUIDE_CONFIG stcGuide = iter->second;
        
        STC_DIALOG stcDialog;
        stcDialog.wRefButtonId = stcGuide.wButtonId;
        stcDialog.strName = stcGuide.strName;
        stcDialog.strText = stcGuide.strText;
        stcDialog.colorName = padColorArr[stcGuide.wNameColor];
        stcDialog.colorText = padColorArr[stcGuide.wTextColor];
        stcDialog.nPosY = stcGuide.nPosY;
        stcDialog.wLadyPath = stcGuide.wLadyPath;
        stcDialog.byLadyOffset = stcGuide.byLadyOffset;
        stcDialog.wOpenLv = stcGuide.wOpenLv;
        
        MAP_GUIDE::iterator m_it = m_mapGuide.find(stcGuide.wGroupId);
        if (m_it != m_mapGuide.end()) {
            if (m_it->second.find(stcGuide.wDialogId) == m_it->second.end()) {
                m_it->second.insert(make_pair(stcGuide.wDialogId, stcDialog));
            } else {
                CCMessageBox("guide csv error", "error");
            }
        } else {
            MAP_DIALOG mapData;
            mapData.insert(make_pair(stcGuide.wDialogId, stcDialog));
            m_mapGuide.insert(make_pair(stcGuide.wGroupId, mapData));
        }
        
    }
    
    std::map<uint16, SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG> mapSysLock = GET_CONFIG_MAP(SystemDebLockingConfig);
    std::map<uint16, SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG>::iterator iterL;
    for (iterL = mapSysLock.begin(); iterL != mapSysLock.end(); iterL++) {
        STC_LOCK stc = iterL->second;
        
        std::vector<int > arrKeyFrame;
        arrKeyFrame.clear();
        ResourceStringConverter::StrSplit(stc.strUnLock, "_", arrKeyFrame);
        
        for (int i = 0; i < arrKeyFrame.size(); i++) {
            if(arrKeyFrame[i] && mapLock.find(arrKeyFrame[i]) == mapLock.end())
            {
                mapLock[arrKeyFrame[i]] = stc;
            }
        }
    }
}

bool GuideData::triggerOn()
{
    CRole* pRole = CGameSession::GetRole();
    m_nGroupId = pRole->GetwGuideTrigger() / 100;
    m_nStepId = pRole->GetwGuideTrigger();
    int subStep = pRole->GetwGuideTrigger() % 100;
    int nLv = pRole->GetwRoleLv();
    
    MAP_GUIDE::iterator itGuide = m_mapGuide.find(m_nGroupId);
    if (itGuide != m_mapGuide.end()) {
        m_mapData = itGuide->second;
        MAP_DIALOG::iterator itDialog = m_mapData.find(subStep);
        if (itDialog != m_mapData.end()) {
            m_stcData = itDialog->second;
            if (m_stcData.wOpenLv <= nLv) {
                return true;
            }
        }
    }
    return false;
}

void GuideData::setStepId(int step)
{
    m_nStepId = step;
    CGameSession::GetRole()->SetwGuideTrigger(m_nStepId);
}

void GuideData::stepOver()
{
    
    CRole* pRole = CGameSession::GetRole();
    
    switch (m_nStepId) {
        case E_GUIDE_TRIGGER_START:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_1;
            break;
        case E_GUIDE_TRIGGER_INTRO:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_1;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_1:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_2;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_2:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_3;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_3:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_4;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_4:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_5;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_5:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_6;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_6:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_7;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_7:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_8;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_8:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_9;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_9:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_10;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_10:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_1;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_1:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_2;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_2:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_3;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_3:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_4;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_4:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_5;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_5:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_6;
            break;
        case E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_6:
            m_nStepId = E_GUIDE_TRIGGER_END_FAKE_ATTACK;
            break;
        case E_GUIDE_TRIGGER_END_FAKE_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_BOSS_1_TALK;
            break;
            
        case E_GUIDE_TRIGGER_BOSS_1_TALK:
            m_nStepId = E_GUIDE_TRIGGER_BOSS_2_TALK;
            break;
        case E_GUIDE_TRIGGER_BOSS_2_TALK:
            m_nStepId = E_GUIDE_TRIGGER_BOSS_3_TALK;
            break;
        case E_GUIDE_TRIGGER_BOSS_3_TALK:
            m_nStepId = E_GUIDE_TRIGGER_BOSS_4_TALK;
            break;
        case E_GUIDE_TRIGGER_BOSS_4_TALK:
            m_nStepId = E_GUIDE_TRIGGER_BOSS_5_TALK;
            break;
        case E_GUIDE_TRIGGER_BOSS_5_TALK:
            m_nStepId = E_GUIDE_TRIGGER_BOSS_6_TALK;
            break;
        case E_GUIDE_TRIGGER_BOSS_6_TALK:
            m_nStepId = E_GUIDE_TRIGGER_BOSS_7_TALK;
            break;
        case E_GUIDE_TRIGGER_BOSS_7_TALK:
            m_nStepId = E_GUIDE_TRIGGER_FAKE_ATTACK_END_1_TALK;
            break;
            
            
        case E_GUIDE_TRIGGER_FAKE_ATTACK_END_1_TALK:
            m_nStepId = E_GUIDE_TRIGGER_WAKE_1_TALK;
            break;
            
            
        case E_GUIDE_TRIGGER_WAKE_1_TALK:
            m_nStepId = E_GUIDE_TRIGGER_WAKE_2_TALK;
            break;
        case E_GUIDE_TRIGGER_WAKE_2_TALK:
            m_nStepId = E_GUIDE_TRIGGER_WAKE_3_TALK;
            break;
        case E_GUIDE_TRIGGER_WAKE_3_TALK:
            m_nStepId = E_GUIDE_TRIGGER_NAME;
            break;
            
            
        case E_GUIDE_TRIGGER_NAME:
            m_nStepId = E_GUIDE_TRIGGER_CHOOSE_TALK_1;
            break;
        case E_GUIDE_TRIGGER_CHOOSE_TALK_1:
            m_nStepId = E_GUIDE_TRIGGER_CHOOSE_TALK_2;
            break;
        case E_GUIDE_TRIGGER_CHOOSE_TALK_2:
            m_nStepId = E_GUIDE_TRIGGER_FIR_ATTACK;
            break;
            
            // 第一次战斗
        case E_GUIDE_TRIGGER_FIR_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_FIR_1_ATTACK;
            break;
        case E_GUIDE_TRIGGER_FIR_1_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_FIR_2_ATTACK;
            break;
        case E_GUIDE_TRIGGER_FIR_2_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_FIR_3_ATTACK;
            break;
        case E_GUIDE_TRIGGER_FIR_3_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_FRI_4_ATTACK;
            break;
        case E_GUIDE_TRIGGER_FRI_4_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_FIR_END_ATTACK;
            break;
        case E_GUIDE_TRIGGER_FIR_END_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_TEAM;
            break;
            
            // 第一次上阵
        case E_GUIDE_TRIGGER_TEAM:
            m_nStepId = E_GUIDE_TRIGGER_1_TEAM;
            break;
        case E_GUIDE_TRIGGER_1_TEAM:
            m_nStepId = E_GUIDE_TRIGGER_2_TEAM;
            break;
        case E_GUIDE_TRIGGER_2_TEAM:
            m_nStepId = E_GUIDE_TRIGGER_3_TEAM;
            break;
        case E_GUIDE_TRIGGER_3_TEAM:
            m_nStepId = E_GUIDE_TRIGGER_4_TEAM;
            break;
        case E_GUIDE_TRIGGER_4_TEAM:
            m_nStepId = E_GUIDE_TRIGGER_5_TEAM;
            break;
        case E_GUIDE_TRIGGER_5_TEAM:
            m_nStepId = E_GUIDE_TRIGGER_END_TEAM;
            break;
        case E_GUIDE_TRIGGER_END_TEAM:
            m_nStepId = E_GUIDE_TRIGGER_SEC_ATTACK;
            break;
            
            // 第二次战斗
        case E_GUIDE_TRIGGER_SEC_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_SEC_1_ATTACK;
            break;
        case E_GUIDE_TRIGGER_SEC_1_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_SEC_2_ATTACK;
            break;
        case E_GUIDE_TRIGGER_SEC_2_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_SEC_END_ATTACK;
            break;
        case E_GUIDE_TRIGGER_SEC_END_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_GACHA;
            break;
            
            // 召唤
        case E_GUIDE_TRIGGER_GACHA:
            m_nStepId = E_GUIDE_TRIGGER_1_GACHA;
            break;
        case E_GUIDE_TRIGGER_1_GACHA:
            m_nStepId = E_GUIDE_TRIGGER_ONCE_GACHA;
            break;
        case E_GUIDE_TRIGGER_ONCE_GACHA:
            m_nStepId = E_GUIDE_TRIGGER_3_GACHA;
            break;
        case E_GUIDE_TRIGGER_3_GACHA:
            m_nStepId = E_GUIDE_TRIGGER_4_GACHA;
            break;
        case E_GUIDE_TRIGGER_4_GACHA:
            m_nStepId = E_GUIDE_TRIGGER_5_GACHA;
            break;
        case E_GUIDE_TRIGGER_5_GACHA:
//            m_nStepId = E_GUIDE_TRIGGER_6_GACHA;
//            break;
//        case E_GUIDE_TRIGGER_6_GACHA:
            m_nStepId = E_GUIDE_TRIGGER_END_GACHA;
            break;
        case E_GUIDE_TRIGGER_END_GACHA:
            m_nStepId = E_GUIDE_TRIGGER_MAIN_TEAM;
            break;
            
            // 精灵上阵
        case E_GUIDE_TRIGGER_MAIN_TEAM:
            m_nStepId = E_GUIDE_TRIGGER_1_MAIN_TEAM;
            break;
        case E_GUIDE_TRIGGER_1_MAIN_TEAM:
            m_nStepId = E_GUIDE_TRIGGER_THI_TALK_1;
            break;
            
            // 第三次战斗
        case E_GUIDE_TRIGGER_THI_TALK_1:
            m_nStepId = E_GUIDE_TRIGGER_THI_TALK_2;
            break;
        case E_GUIDE_TRIGGER_THI_TALK_2:
            m_nStepId = E_GUIDE_TRIGGER_THI_ATTACK;
            break;
        case E_GUIDE_TRIGGER_THI_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_THI_1_ATTACK;
            break;
        case E_GUIDE_TRIGGER_THI_1_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_THI_2_ATTACK;
            break;
        case E_GUIDE_TRIGGER_THI_2_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_THI_3_ATTACK;
            break;
        case E_GUIDE_TRIGGER_THI_3_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_THI_END_ATTACK;
            break;
        case E_GUIDE_TRIGGER_THI_END_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_1_PRESS_MAIN;
            break;
        case E_GUIDE_TRIGGER_1_PRESS_MAIN:
            m_nStepId = E_GUIDE_TRIGGER_PET_ENHANCE;
            break;
            
            // 宠物强化
        case E_GUIDE_TRIGGER_PET_ENHANCE:
            m_nStepId = E_GUIDE_TRIGGER_1_PET_ENHANCE;
            break;
        case E_GUIDE_TRIGGER_1_PET_ENHANCE:
            m_nStepId = E_GUIDE_TRIGGER_2_PET_ENHANCE;
            break;
        case E_GUIDE_TRIGGER_2_PET_ENHANCE:
            m_nStepId = E_GUIDE_TRIGGER_3_PET_ENHANCE;
            break;
        case E_GUIDE_TRIGGER_3_PET_ENHANCE:
            m_nStepId = E_GUIDE_TRIGGER_PET_ENHANCE_1_TALK;
            break;
        case E_GUIDE_TRIGGER_PET_ENHANCE_1_TALK:
            m_nStepId = E_GUIDE_TRIGGER_PET_ENHANCE_2_TALK;
            break;
        case E_GUIDE_TRIGGER_PET_ENHANCE_2_TALK:
            m_nStepId = E_GUIDE_TRIGGER_END_PET_ENHANCE;
            break;
        case E_GUIDE_TRIGGER_END_PET_ENHANCE:
            m_nStepId = E_GUIDE_TRIGGER_FOUR_ATTACK;
            break;
            
            // 第四次战斗
        case E_GUIDE_TRIGGER_FOUR_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_1_FOUR_ATTACK;
            break;
        case E_GUIDE_TRIGGER_1_FOUR_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_2_FOUR_ATTACK;
            break;
        case E_GUIDE_TRIGGER_2_FOUR_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_FOUR_END_ATTACK;
            break;
        case E_GUIDE_TRIGGER_FOUR_END_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_2_PRESS_MAIN;
            break;
        case E_GUIDE_TRIGGER_2_PRESS_MAIN:
            m_nStepId = E_GUIDE_TRIGGER_PET_EVOLVE;
            break;
            
            // 宠物进阶
        case E_GUIDE_TRIGGER_PET_EVOLVE:
            m_nStepId = E_GUIDE_TRIGGER_0_PET_EVOLVE;
            break;
        case E_GUIDE_TRIGGER_0_PET_EVOLVE:
            m_nStepId = E_GUIDE_TRIGGER_1_PET_EVOLVE;
            break;
        case E_GUIDE_TRIGGER_1_PET_EVOLVE:
            m_nStepId = E_GUIDE_TRIGGER_PET_EVOLVE_1_TALK;
            break;
        case E_GUIDE_TRIGGER_PET_EVOLVE_1_TALK:
            m_nStepId = E_GUIDE_TRIGGER_PET_EVOLVE_2_TALK;
            break;
        case E_GUIDE_TRIGGER_PET_EVOLVE_2_TALK:
            m_nStepId = E_GUIDE_TRIGGER_PET_EVOLVE_3_TALK;
            break;
        case E_GUIDE_TRIGGER_PET_EVOLVE_3_TALK:
            m_nStepId = E_GUIDE_TRIGGER_END_PET_EVOLVE;
            break;
        case E_GUIDE_TRIGGER_END_PET_EVOLVE:
            m_nStepId = E_GUIDE_TRIGGER_FIVE_ATTACK;
            break;
            
            // 第五次战斗
        case E_GUIDE_TRIGGER_FIVE_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_1_FIVE_ATTACK;
            break;
        case E_GUIDE_TRIGGER_1_FIVE_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_2_FIVE_ATTACK;
            break;
        case E_GUIDE_TRIGGER_2_FIVE_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_FIVE_END_ATTACK;
            break;
        case E_GUIDE_TRIGGER_FIVE_END_ATTACK:
            m_nStepId = E_GUIDE_TRIGGER_GET_STAR;
            break;
        case E_GUIDE_TRIGGER_GET_STAR:
            m_nStepId = E_GUIDE_TRIGGER_1_GET_STAR;
            break;
        case E_GUIDE_TRIGGER_1_GET_STAR:
            m_nStepId = E_GUIDE_TRIGGER_JUMP_NEXT;
            break;
        case E_GUIDE_TRIGGER_JUMP_NEXT:
//            m_nStepId = E_GUIDE_TRIGGER_MAP_2;
//            break;
//        case E_GUIDE_TRIGGER_MAP_2:
            m_nStepId = E_GUIDE_TRIGGER_MAP_2_TALK;
            break;
        case E_GUIDE_TRIGGER_MAP_2_TALK:
            m_nStepId = E_GUIDE_END_TRIGGER;
            break;
        
        //------------SYSTEM_GUIDE---------------------------
            // 装备}
        case E_SYS_GUIDE_EQUIP:
            m_nStepId = E_SYS_GUIDE_1_EQUIP;
            break;
        case E_SYS_GUIDE_1_EQUIP:
            m_nStepId = E_SYS_GUIDE_2_EQUIP;
            break;
        case E_SYS_GUIDE_2_EQUIP:
            m_nStepId = E_SYS_GUIDE_3_EQUIP;
            break;
        case E_SYS_GUIDE_3_EQUIP:
            m_nStepId = E_SYS_GUIDE_4_EQUIP;
            break;
        case E_SYS_GUIDE_4_EQUIP:
            m_nStepId = E_SYS_GUIDE_END_EQUIP;
            break;
            
            
            // 招财猫引导
        case E_SYS_GUIDE_CAT:
            m_nStepId = E_SYS_GUIDE_0_CAT;
            break;
        case E_SYS_GUIDE_0_CAT:
            m_nStepId = E_SYS_GUIDE_1_CAT;
            break;
        case E_SYS_GUIDE_1_CAT:
            m_nStepId = E_SYS_GUIDE_2_CAT;
            break;
        case E_SYS_GUIDE_2_CAT:
            m_nStepId = E_SYS_GUIDE_END_CAT;
            break;
            
            
            // JJC引导}
        case E_SYS_GUIDE_1_JJC:
            m_nStepId = E_SYS_GUIDE_2_JJC;
            break;
        case E_SYS_GUIDE_2_JJC:
            m_nStepId = E_SYS_GUIDE_3_JJC;
            break;
        case E_SYS_GUIDE_3_JJC:
            m_nStepId = E_SYS_GUIDE_4_JJC;
            break;
        case E_SYS_GUIDE_4_JJC:
            m_nStepId = E_SYS_GUIDE_5_JJC;
            break;
        case E_SYS_GUIDE_5_JJC:
            m_nStepId = E_SYS_GUIDE_6_JJC;
            break;
        case E_SYS_GUIDE_6_JJC:
            m_nStepId = E_SYS_GUIDE_END_JJC;
            break;
            
            
            // 精英关卡}
        case E_SYS_GUIDE_HERO:
            m_nStepId = E_SYS_GUIDE_1_HERO;
            break;
        case E_SYS_GUIDE_1_HERO:
            m_nStepId = E_SYS_GUIDE_2_HERO;
            break;
        case E_SYS_GUIDE_2_HERO:
            m_nStepId = E_SYS_GUIDE_3_HERO;
            break;
        case E_SYS_GUIDE_3_HERO:
            m_nStepId = E_SYS_GUIDE_4_HERO;
            break;
        case E_SYS_GUIDE_4_HERO:
            m_nStepId = E_SYS_GUIDE_5_HERO;
            break;
        case E_SYS_GUIDE_5_HERO:
            m_nStepId = E_SYS_GUIDE_6_HERO;
            break;
        case E_SYS_GUIDE_6_HERO:
            m_nStepId = E_SYS_GUIDE_7_HERO;
            break;
        case E_SYS_GUIDE_7_HERO:
            m_nStepId = E_SYS_GUIDE_END_HERO;
            break;
        

            // 爬塔引导}
        case E_SYS_GUIDE_1_TOWER:
            m_nStepId = E_SYS_GUIDE_2_TOWER;
            break;
        case E_SYS_GUIDE_2_TOWER:
            m_nStepId = E_SYS_GUIDE_3_TOWER;
            break;
        case E_SYS_GUIDE_3_TOWER:
            m_nStepId = E_SYS_GUIDE_4_TOWER;
            break;
        case E_SYS_GUIDE_4_TOWER:
            m_nStepId = E_SYS_GUIDE_5_TOWER;
            break;
        case E_SYS_GUIDE_5_TOWER:
            m_nStepId = E_SYS_GUIDE_END_TOWER;
            break;
            /*
            m_nStepId = E_SYS_GUIDE_6_TOWER;
            break;
        case E_SYS_GUIDE_6_TOWER:
            m_nStepId = E_SYS_GUIDE_7_TOWER;
            break;
        case E_SYS_GUIDE_7_TOWER:
            m_nStepId = E_SYS_GUIDE_END_TOWER;
            break;
             */
            
            // 徽章引导}
        case E_SYS_GUIDE_BADGE:
            m_nStepId = E_SYS_GUIDE_1_BADGE;
            break;
        case E_SYS_GUIDE_1_BADGE:
            m_nStepId = E_SYS_GUIDE_2_BADGE;
            break;
        case E_SYS_GUIDE_2_BADGE:
            m_nStepId = E_SYS_GUIDE_3_BADGE;
            break;
        case E_SYS_GUIDE_3_BADGE:
            m_nStepId = E_SYS_GUIDE_4_BADGE;
            break;
        case E_SYS_GUIDE_4_BADGE:
            m_nStepId = E_SYS_GUIDE_5_BADGE;
            break;
        case E_SYS_GUIDE_5_BADGE:
            m_nStepId = E_SYS_GUIDE_5_1_BADGE;
            break;
        case E_SYS_GUIDE_5_1_BADGE:
            m_nStepId = E_SYS_GUIDE_6_BADGE;
            break;
        case E_SYS_GUIDE_6_BADGE:
            m_nStepId = E_SYS_GUIDE_7_BADGE;
            break;
        case E_SYS_GUIDE_7_BADGE:
            m_nStepId = E_SYS_GUIDE_8_BADGE;
            break;
        case E_SYS_GUIDE_8_BADGE:
            m_nStepId = E_SYS_GUIDE_9_BADGE;
            break;
        case E_SYS_GUIDE_9_BADGE:
            m_nStepId = E_SYS_GUIDE_10_BADGE;
            break;
        case E_SYS_GUIDE_10_BADGE:
            m_nStepId = E_SYS_GUIDE_11_BADGE;
            break;
        case E_SYS_GUIDE_11_BADGE:
            m_nStepId = E_SYS_GUIDE_12_BADGE;
            break;
        case E_SYS_GUIDE_12_BADGE:
            m_nStepId = E_SYS_GUIDE_END_BADGE;
            break;
            
            // 神秘商店引导
        case E_SYS_GUIDE_MYSTERY:
            m_nStepId = E_SYS_GUIDE_1_MYSTERY;
            break;
        case E_SYS_GUIDE_1_MYSTERY:
            m_nStepId = E_SYS_GUIDE_2_MYSTERY;
            break;
        case E_SYS_GUIDE_2_MYSTERY:
            m_nStepId = E_SYS_GUIDE_3_MYSTERY;
            break;
        case E_SYS_GUIDE_3_MYSTERY:
            m_nStepId = E_SYS_GUIDE_4_MYSTERY;
            break;
        case E_SYS_GUIDE_4_MYSTERY:
            m_nStepId = E_SYS_GUIDE_5_MYSTERY;
            break;
        case E_SYS_GUIDE_5_MYSTERY:
            m_nStepId = E_SYS_GUIDE_6_MYSTERY;
            break;
        case E_SYS_GUIDE_6_MYSTERY:
            m_nStepId = E_SYS_GUIDE_7_MYSTERY;
            break;
        case E_SYS_GUIDE_7_MYSTERY:
            m_nStepId = E_SYS_GUIDE_8_MYSTERY;
            break;
        case E_SYS_GUIDE_8_MYSTERY:
            m_nStepId = E_SYS_GUIDE_END_MYSTERY;
            break;
            
        case E_SYS_GUIDE_END_MYSTERY:
            m_nStepId = E_GUIDE_TRIGGER_END;
        default:
            break;
    }
    CCLog(">>>> step Id:%d", m_nStepId);
    pRole->SetwGuideTrigger(m_nStepId);
}

void GuideData::addGuideofEnum(GuideData::kStepEnum kenum, ...) {
    va_list args;
    va_start(args, kenum);
    
    bool bShowGuide = false;
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    
    GuideData::kStepEnum tmpEnum = kenum;
    
    while (tmpEnum) {
        if (wTrigger == tmpEnum) {
            bShowGuide = true;
            break;
        }
        tmpEnum = (GuideData::kStepEnum)va_arg(args, int);
    }
    
    va_end(args);
    if (bShowGuide) {
        addGuideLayer();
    }
    return;
}

void GuideData::addGuideLayer(bool connect /*=false*/, bool step /*=true*/)
{
    if (m_nStepId == E_GUIDE_TRIGGER_END) {
        return;
    }
    
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene->getChildByTag(kGuideTag)) {
        pScene->removeChildByTag(kGuideTag);
    }
    
    if (triggerOn()) {
        CCLog(">>>> cur step:%d", m_nStepId);

        GuideLayer* pGuideLayer = GuideLayer::create();
        pGuideLayer->playGuide(m_stcData);
#ifndef GUIDE_OFF
        pScene->addChild(pGuideLayer, 9999, kGuideTag);
#endif
        
        if (step) {
            stepOver();
        }
        
        if (connect) {
            connectToServer();
        }
        
#ifdef GUIDE_OFF
        if (m_nStepId == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_2 || m_nStepId == GuideData::E_GUIDE_TRIGGER_ATTR_1_TALK || m_nStepId == GuideData::E_GUIDE_TRIGGER_ATTR_2_TALK || m_nStepId == GuideData::E_GUIDE_TRIGGER_REWARD) {
            if (CcbPetBattleLayer::GetCurrScene()) {
                CcbPetBattleLayer::GetCurrScene()->remuseAll();
            }
        }
#endif
    }
}

void GuideData::onlyRmGuideLayer()
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene->getChildByTag(kGuideTag)) {
        pScene->removeChildByTag(kGuideTag);
    }
}

void GuideData::connectToServer()
{
    CGameSession::SendTriggerNum(m_nStepId);
}

void GuideData::skipCurGroup()
{
    int nCurGroup = m_nStepId / 100;
    nCurGroup++;
    m_nStepId = nCurGroup * 100;
    onlyRmGuideLayer();
    connectToServer();
}

void GuideData::skipCurStep()
{
    stepOver();
    onlyRmGuideLayer();
}

#pragma mark System Lock
/*!
 * 格式化保存用 guideId
 */
void GuideData::formateLockGuideId()
{
    
}

uint16 GuideData::checkSystemLock(uint8 type)
{
    uint16 wIndex = 0;
    
    CRole* role = CGameSession::GetRole();
    
    std::map<uint16, SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG> mapSysLock = GET_CONFIG_MAP(SystemDebLockingConfig);
    std::map<uint16, SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG>::iterator iterL;
    for (iterL = mapSysLock.begin(); iterL != mapSysLock.end(); iterL++) {
        STC_LOCK stc = iterL->second;
        if (stc.byType != type) {
            continue;
        }
        if (stc.byType == E_GUIDE_UNLOCK_TYPE_LV) {
            if (role->GetwRoleLv() == stc.wPara) {
                wIndex = stc.dwIndex;
                return wIndex;
            }
        }
        else if (stc.byType == E_GUIDE_UNLOCK_TYPE_STAGE)
        {
            //通关要求的关卡}
            STC_BATTLE_PRE_DATA preData = FightAI::Get()->getPerData();
            if (preData.dwPrePassStage > 0) {
                StageCtrl::STC_STAGE stcStage = StageCtrl::Get()->selectedStage();
                if(stcStage.wStageId > preData.dwPrePassStage && stcStage.wStageId == stc.wPara){
                    wIndex = stc.dwIndex;
                    return wIndex;;
                }
            }
//            else{
//                if (role->GetwPassStageId() == stc.wPara && GlobalData::bFirst2003) {
//                    wIndex = stc.dwIndex;
//                    return wIndex;;
//                }
//            }
        }
    }

    return wIndex;
}

//未解锁的返回 系统引导表的Id，已解锁的返回 0}
uint16 GuideData::checkBtnLock(uint16 wBtn)
{
    if (mapLock.find(wBtn) != mapLock.end()) {
        STC_LOCK stc = mapLock[wBtn];
        
        CRole* role = CGameSession::GetRole();
        if (stc.byType == E_GUIDE_UNLOCK_TYPE_LV) {
            if (role->GetwRoleLv() >= stc.wPara) {
                return 0;
            }
            else
            {
                return stc.dwIndex;
            }
        }
        else if (stc.byType == E_GUIDE_UNLOCK_TYPE_STAGE)
        {
            //当前关卡为下一关卡时，认为刚刚通关要求的关卡}
            if (role->GetwPassStageId() >= stc.wPara) {
                return 0;
            }
            else
            {
                return stc.dwIndex;
            }
        }
    }
    
    return 0;
}

void GuideData::setGroupId(uint16 groupId)
{
    m_nGroupId = groupId;
}

void GuideData::setSysLockId(uint32 dwSysLockId)
{
    //为了防止两个条件同时满足的情况，因为关卡优先判断，所以当此值已被赋值时，后面的不对其进行影响，当引导结束时，此值设置为0}
    if (!dwSysLockId) {
        m_dwSysLockId = dwSysLockId;
    }
    else if (!m_dwSysLockId) {
        m_dwSysLockId = dwSysLockId;
    }
}

void GuideData::runSystemGuide(uint16 wGroupId)
{
#if 0
    char szBuf[64];
    sprintf(szBuf, "In Group Id:%d", wGroupId);
    CCMessageBox(szBuf, "test");
#endif
    m_nStepId = wGroupId * 100;

    CCLog("cur Step Id:%d", m_nStepId);
    CGameSession::GetRole()->SetwGuideTrigger(m_nStepId);
}

