//
//  ChallengeCtrl.cpp
//  MyGame
//
//  Created by Relvin on 14/11/15.
//
//

#include "ChallengeCtrl.h"
#include "ConfigData.h"
#include "ConfigGet.h"
#include "Role.h"
#include "GameSession.h"

ChallengeCtrl::ChallengeCtrl()
: m_byType(kTypeNone)
, m_wMapId(0)
, m_bChoose(false)
, m_byStage(E_CHALLENGE_NONE)
, m_nCellIndex(-1)
{
    m_stageDiffiValue.clear();
    m_vecStageInfo.clear();
}

ChallengeCtrl::~ChallengeCtrl(){
    m_stageDiffiValue.clear();
    m_vecStageInfo.clear();
}


void ChallengeCtrl::loadDataFromConfigByMapId(uint16 wMapId)
{
    std::map<uint16, ActiveStageConfig::STC_ACTIVE_STAGE_CONFIG> StageMap = GET_CONFIG_MAP(ActiveStageConfig);
    std::map<uint16, ActiveStageConfig::STC_ACTIVE_STAGE_CONFIG>::iterator iter = StageMap.begin();
    if (wMapId == kPetRelics) {
        uint8 byDiffiValue = 0;
        for (; iter != StageMap.end(); ++iter) {
            byDiffiValue = iter->second.byDiffiValue;
            if (byDiffiValue == 0) {
                continue;
            }
            if (iter->second.byLvLimit > CGameSession::GetRole()->GetwRoleLv()) {
                continue;
            }
            std::map<uint8, VECSTAGE>::iterator vecStageIter = m_stageDiffiValue.find(byDiffiValue);
            if (vecStageIter != m_stageDiffiValue.end()) {
                vecStageIter->second.push_back(iter->second.wIndex);
            }
            else
            {
                VECSTAGE vecStage;
                vecStage.clear();
                vecStage.push_back(iter->second.wIndex);
                m_stageDiffiValue[byDiffiValue] = vecStage;
            }
        }
    }
    else
    {
        for (; iter != StageMap.end(); ++iter) {
            if (iter->second.wIndex / 1000 == wMapId) {
                m_vecStageInfo.push_back(iter->second.wIndex);
            }
        }
    }
}

ChallengeCtrl::VECSTAGE* ChallengeCtrl::getChallengeStageInfoByDiffiValue(uint8 byValue)
{
    std::map<uint8, VECSTAGE>::iterator vecStageIter = m_stageDiffiValue.find(byValue);
    if (vecStageIter != m_stageDiffiValue.end()) {
        return &vecStageIter->second;
    }
    return NULL;
}

ChallengeCtrl::VECSTAGE* ChallengeCtrl::getChallengeStageInfoByMapId(uint16 wMapId)
{
    if (m_wMapId != wMapId || m_vecStageInfo.size() == 0) {
        m_vecStageInfo.clear();
        this->loadDataFromConfigByMapId(wMapId);
    }
    return &m_vecStageInfo;
}

int ChallengeCtrl::getChallengeStageInfoCountByMapId(uint16 wMapId)
{
    if (wMapId == kPetRelics) {
        this->loadDataFromConfigByMapId(wMapId);
        return m_stageDiffiValue.size();
    }
    else
    {
        if (m_wMapId != wMapId || m_vecStageInfo.size() == 0) {
            this->loadDataFromConfigByMapId(wMapId);
        }
        return m_vecStageInfo.size();
    }
    
}
