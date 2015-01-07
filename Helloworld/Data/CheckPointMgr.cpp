//
//  CheckPointMgr.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14/10/28.
//
//

#include "CheckPointMgr.h"
#include "CcbPadLayer.h"
#include "CcbManager.h"
#include "PadDefine.h"
#include "CcbPetBattleLayer.h"
#include "StageLayer.h"
#include "GuideData.h"
#include "GuideBtnPos.h"

CheckPointMgr::CheckPointMgr() {
}

void CheckPointMgr::loadTalkData(uint16 _wMapId, uint16 _wStageId, bool _bStageTalk) {
    m_vecEpitasis.clear();
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    MAP_EPITASIS m_mapEpitasis = GET_CONFIG_MAP(EpitasisConfig);
    MAP_EPITASIS::iterator m_pIter;
    
    for (m_pIter = m_mapEpitasis.begin(); m_pIter != m_mapEpitasis.end(); m_pIter++) {
        EpitasisConfig::STC_EPITASIS_CONFIG pCfg = m_pIter->second;
        if (_wMapId && pCfg.wMapId == _wMapId && pCfg.wStageId == 0) {
            // 地图点说话
            m_vecEpitasis.push_back(pCfg);
        } else if (_wStageId && _bStageTalk && pCfg.wStageId == _wStageId && pCfg.byInsertBefore == kStageTalk) {
            // 关卡点说话
            m_vecEpitasis.push_back(pCfg);
        } else if (_wStageId && !_bStageTalk && pCfg.wStageId == _wStageId) {
            // Boss前说话
            if (pCfg.byInsertBefore == kBossTalk) {
                m_vecEpitasis.push_back(pCfg);
            } else if (pCfg.byInsertBefore == kFightEndTalk) {
                m_vecFightEndTalk.push_back(pCfg);
            }
        }
    }
    return;
}

void CheckPointMgr::clrTalkData() {
    m_vecEpitasis.clear();
    m_vecFightEndTalk.clear();
}

void CheckPointMgr::addMapTalk(int _idx, StageLayer* _parent) {
    EpitasisConfig::STC_EPITASIS_CONFIG cfg;
    if (m_vecEpitasis.size() > _idx) {
        cfg = m_vecEpitasis[_idx];
    } else {
        CCAssert(1, "error config map talk");
    }
    
    CcbPadLayer* _padLayer = dynamic_cast<CcbPadLayer*>(CcbManager::sharedManager()->LoadCcbPadLayer(NULL));
    _padLayer->setPadStyle(1);
    _padLayer->setFromKind(CcbPadLayer::E_GUIDE);
    _padLayer->setTouchErase(true);
    _padLayer->setPosition(ccp(winSize.width*0.5, 150));
    _padLayer->setLadyInfo(cfg.wPicIndex, cfg.byPicPos, cfg.wScale);
    _padLayer->setDelegate(_parent);
    _padLayer->setScrollMsg(cfg.strName.c_str(), padColorArr[cfg.byNameColor], cfg.strContent.c_str(), padColorArr[cfg.byContentColor]);

    _parent->addChild(_padLayer, 199);
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(_padLayer, GuideBtnPos::E_TALK_150);
    }
}

void CheckPointMgr::addStageTalk(int _idx, StageLayer *_parent) {
    EpitasisConfig::STC_EPITASIS_CONFIG cfg;
    if (m_vecEpitasis.size() > _idx) {
        cfg = m_vecEpitasis[_idx];
    } else {
        CCAssert(1, "error config stage Talk");
    }
    
    CcbPadLayer* _padLayer = dynamic_cast<CcbPadLayer*>(CcbManager::sharedManager()->LoadCcbPadLayer(NULL));
    _padLayer->setPadStyle(1);
    _padLayer->setFromKind(CcbPadLayer::E_GUIDE);
    _padLayer->setTouchErase(true);
    _padLayer->setPosition(ccp(winSize.width*0.5, 150));
    _padLayer->setLadyInfo(cfg.wPicIndex, cfg.byPicPos, cfg.wScale);
    _padLayer->setDelegate(_parent);
    _padLayer->setScrollMsg(cfg.strName.c_str(), padColorArr[cfg.byNameColor], cfg.strContent.c_str(), padColorArr[cfg.byContentColor]);
    
    _parent->addChild(_padLayer, 199);
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(_padLayer, GuideBtnPos::E_TALK_150);
    }
}

void CheckPointMgr::addBossTalk(int _idx, CcbPetBattleLayer *_parent) {
    EpitasisConfig::STC_EPITASIS_CONFIG cfg;
    if (m_vecEpitasis.size() > _idx) {
        cfg = m_vecEpitasis[_idx];
    } else {
        CCAssert(1, "error config stage Talk");
    }
    
    CcbPadLayer* _padLayer = dynamic_cast<CcbPadLayer*>(CcbManager::sharedManager()->LoadCcbPadLayer(NULL));
    _padLayer->setPadStyle(1);
    _padLayer->setFromKind(CcbPadLayer::E_GUIDE);
    _padLayer->setTouchErase(true);
    _padLayer->setPosition(ccp(winSize.width*0.5, 150));
    _padLayer->setLadyInfo(cfg.wPicIndex, cfg.byPicPos, cfg.wScale);
    _padLayer->setDelegate(_parent);
    _padLayer->setScrollMsg(cfg.strName.c_str(), padColorArr[cfg.byNameColor], cfg.strContent.c_str(), padColorArr[cfg.byContentColor]);
    
    _parent->addChild(_padLayer, 199);
}

void CheckPointMgr::addFightEndTalk(int _idx, CcbPetBattleLayer *_parent) {
    EpitasisConfig::STC_EPITASIS_CONFIG cfg;
    if (m_vecFightEndTalk.size() > _idx) {
        cfg = m_vecFightEndTalk[_idx];
    } else {
        CCAssert(1, "error config stage Talk");
    }
    
    CcbPadLayer* _padLayer = dynamic_cast<CcbPadLayer*>(CcbManager::sharedManager()->LoadCcbPadLayer(NULL));
    _padLayer->setPadStyle(1);
    _padLayer->setFromKind(CcbPadLayer::E_GUIDE);
    _padLayer->setTouchErase(true);
    _padLayer->setPosition(ccp(winSize.width*0.5, 150));
    _padLayer->setLadyInfo(cfg.wPicIndex, cfg.byPicPos, cfg.wScale);
    _padLayer->setDelegate(_parent);
    _padLayer->setScrollMsg(cfg.strName.c_str(), padColorArr[cfg.byNameColor], cfg.strContent.c_str(), padColorArr[cfg.byContentColor]);
    
    _parent->addChild(_padLayer, 199);
}

int CheckPointMgr::talkPadCnt() {
    return m_vecEpitasis.size();
}

int CheckPointMgr::FightEndCnt()
{
    return m_vecFightEndTalk.size();
}
