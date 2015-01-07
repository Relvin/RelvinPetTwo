//
//  StageScene.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-18.}
//
//

#include "StageScene.h"
#include "StageLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "ConfigGet.h"
#include "EnumDefines.h"
#include "GameSession.h"
#include "CcbDropTipLayer.h"
#include "PetLoadingLayer.h"
#include "ChallengeCtrl.h"

USING_NS_CC;


/*{ uint8 bySize +
        uint16 wStageId +
        std::string strName +
        uint8 bySectionCnt +
        uint16 wIconId +
        std::string strDes +
        uint8 byNeedEnergy +
        uint8 byIsNew +
        std::string strName
        uint8 bySize
            uint16 wPetId
        uint8 bySize
            uint32 dwItemId
 }
 */

// 总共最多掉落两件物品}
#define Drop_Cnt 6
//// 最新修改，活动关卡可以最多6个}
//#define Active_Drop_Cnt 6

StageCtrl::StageCtrl()
: m_wStageId(0)
{
    
}

void StageCtrl::handlerStageList(WorldPacket &packet)
{
    m_vecStage.clear();

    uint8 bySize;
    
    m_nCurStarCnt = 0;
    
    if (kFromType == kNormalStage || kFromType == kSpecialStage) {
        packet >> byStarGet;
    }
    
    packet >> bySize;
    for (int s = 0; s < bySize; s++) {
        STC_STAGE stc;
        
        packet >> stc.wStageId;
        if (kFromType == kActivityStage) {  // 只有活动关卡才由服务器发Stage信息，其余的普通和精英关卡均读表}
            packet >> stc.strName;
            packet >> stc.byFightCnt;
            packet >> stc.wIconId;
            packet >> stc.strDes;
        }
        packet >> stc.byCostEnergy;
        packet >> stc.byStatus;
        
        if (kFromType == kNormalStage)
        {
            packet >> stc.strFirstBlood;
            StageConfig::STC_STAGE_CONFIG *stageCfg = GET_CONFIG_STC(StageConfig, stc.wStageId);
            StageShowConfig::STC_STAGE_SHOW_CONFIG* stageShowCfg = GET_CONFIG_STC(StageShowConfig, kFromType*E_UNITE_BASE_FABIO + stc.wStageId);
            
            if (stageCfg && stageShowCfg) {
                stc.strName = stageCfg->strName;
                stc.byFightCnt = stageCfg->wWaveCnt;
                stc.wIconId = stageCfg->dwStageIcon;
                stc.strDes = stageCfg->strDesc;
                stc.byMaxAttCnt = stageCfg->wAttCnt;
                stc.vectNormalBgm = stageCfg->vectNormalBgm;
                stc.vectBossBgm = stageCfg->vectBossBgm;
                stc.byFlag = stageCfg->byFlag;
                stc.wShowMapId = stageCfg->wShowMapId;
                
                if (stageCfg->dwFirstRewItemId1) {
                    stc.m_vecFirstItemId.push_back(stageCfg->dwFirstRewItemId1);
                    stc.m_vecFirstItemCnt.push_back(stageCfg->dwFirstRewItemCnt1);
                }
                if (stageCfg->dwFirstRewItemId2) {
                    stc.m_vecFirstItemId.push_back(stageCfg->dwFirstRewItemId2);
                    stc.m_vecFirstItemCnt.push_back(stageCfg->dwFirstRewItemCnt2);
                }
                
                
                for (int i = 0; i < Drop_Cnt; ++i) {
                    if (stageShowCfg->arrPetId[i]) {
                        stc.m_vecPetId.push_back(stageShowCfg->arrPetId[i]);
                    }
                    if (stageShowCfg->arrItemId[i]) {
                        stc.m_vecItemId.push_back(stageShowCfg->arrItemId[i]);
                    }
                }
            }
        }
        else if (kFromType == kSpecialStage) {
            packet >> stc.strFirstBlood;
            StageHConfig::STC_STAGE_H_CONFIG *hstageCfg = GET_CONFIG_STC(StageHConfig, stc.wStageId);
            StageShowConfig::STC_STAGE_SHOW_CONFIG* stageShowCfg = GET_CONFIG_STC(StageShowConfig, kFromType*E_UNITE_BASE_FABIO + stc.wStageId);
            if (hstageCfg && stageShowCfg) {
                stc.strName = hstageCfg->strName;
                stc.byFightCnt = hstageCfg->wWaveCnt;
                stc.wIconId = hstageCfg->dwStageIcon;
                stc.strDes = hstageCfg->strDesc;
                stc.byMaxAttCnt = hstageCfg->wAttCnt;
                stc.vectNormalBgm = hstageCfg->vectNormalBgm;
                stc.vectBossBgm = hstageCfg->vectBossBgm;
                stc.byFlag = hstageCfg->byFlag;
                stc.wShowMapId = hstageCfg->wShowMapId;
                
                if (hstageCfg->dwFirstRewItemId1) {
                    stc.m_vecFirstItemId.push_back(hstageCfg->dwFirstRewItemId1);
                    stc.m_vecFirstItemCnt.push_back(hstageCfg->dwFirstRewItemCnt1);
                }
                if (hstageCfg->dwFirstRewItemId2) {
                    stc.m_vecFirstItemId.push_back(hstageCfg->dwFirstRewItemId2);
                    stc.m_vecFirstItemCnt.push_back(hstageCfg->dwFirstRewItemCnt2);
                }
                
                for (int i = 0; i < Drop_Cnt; ++i) {
                    if (stageShowCfg->arrPetId[i]) {
                        stc.m_vecPetId.push_back(stageShowCfg->arrPetId[i]);
                    }
                    if (stageShowCfg->arrItemId[i]) {
                        stc.m_vecItemId.push_back(stageShowCfg->arrItemId[i]);
                    }
                }
            }
        }
        
        packet >> stc.byAttackCnt;
        if (kFromType == kActivityStage) {
            packet >> stc.byMaxAttCnt;
            packet >> stc.wRoleLvLimit;
            packet >> stc.byBuyCnt;
            
            StageHConfig::STC_STAGE_H_CONFIG *activeCfg = GET_CONFIG_STC(StageHConfig, stc.wStageId);
            if (activeCfg) {
                stc.vectNormalBgm = activeCfg->vectNormalBgm;
                stc.vectBossBgm = activeCfg->vectBossBgm;
            }
            StageShowConfig::STC_STAGE_SHOW_CONFIG* stageShowCfg = GET_CONFIG_STC(StageShowConfig, stc.wStageId);
            
            for (int i = 0; i < Drop_Cnt; i++) {
                if (stageShowCfg && stageShowCfg->arrPetId[i]) {
                    stc.m_vecPetId.push_back(stageShowCfg->arrPetId[i]);
                }
                if (stageShowCfg && stageShowCfg->arrItemId[i]) {
                    stc.m_vecItemId.push_back(stageShowCfg->arrItemId[i]);
                }
            }
        } else {
            packet >> stc.byStarCnt;
            m_nCurStarCnt += stc.byStarCnt;
            packet >> stc.byBuyCnt;
        }
        
        m_vecStage.push_back(stc);
    }
    if (kFromType != kActivityStage) {
        BackCtrl::InsertNextScene(kStageScene, kFadeTrans);
    }
    else
    {
        switch (ChallengeCtrl::Get()->getChallengeType()) {
            case ChallengeCtrl::kPetRelics:
            {
                BackCtrl::InsertNextScene(kChallengeType3Scene);
                break;
            }
            case ChallengeCtrl::kGodRelics:
            {
                BackCtrl::InsertNextScene(kChallengeType2Scene);
                break;
            }
            case ChallengeCtrl::kStoneRelics:
            {
                BackCtrl::InsertNextScene(kChallengeType1Scene);
                break;
            }
            case ChallengeCtrl::kMoneyCat:
            case ChallengeCtrl::kEggTag:
            {
                BackCtrl::InsertNextScene(kStageScene, kFadeTrans);
                break;
            }
            default:
                break;
        }
    }
    
}

StageCtrl::STC_STAGE* StageCtrl::getStageByStageId(int index)
{
    for (int i = 0; i < m_vecStage.size(); i++) {
        if (m_vecStage[i].wStageId == index) {
            return &m_vecStage[i];
        }
    }
    
    return NULL;
}

void StageCtrl::handlerStageUpdate(WorldPacket &packet)
{
    uint16 _wStageId;
    uint8 _byNeedEnergy;
    uint8 _byIsNew;
    std::string _strName;
    uint8 _byAttackCnt;
    uint8 _byStarCnt;
    uint8 _byBuyCnt;
    
    packet >> _wStageId >> _byNeedEnergy >> _byIsNew >> _strName >> _byAttackCnt >> _byStarCnt;
    packet >> _byBuyCnt;
    
    VECTOR_STAGE_TYPE::iterator pIter;
    for (pIter = m_vecStage.begin(); pIter != m_vecStage.end(); pIter++) {
        if (pIter->wStageId == _wStageId) {
            
            m_nCurStarCnt -= pIter->byStarCnt;
            m_nCurStarCnt += _byStarCnt;
            
            pIter->byCostEnergy = _byNeedEnergy;
            pIter->byStatus = _byIsNew;
            pIter->strFirstBlood = _strName;
            pIter->byAttackCnt = _byAttackCnt;
            pIter->byStarCnt = _byStarCnt;
            pIter->byBuyCnt = _byBuyCnt;
            
            CGameSession::NotifyRefeashLayer();
            return;;
        }
    }
}

void StageCtrl::handlerActivityMap(WorldPacket &packet)
{
    m_vecActiviyMap.clear();
    m_mapActivityMap.clear();
    uint8 bySize;
    
    packet >> bySize;
    VEC_SPE_MAP tempVecInfo;
    tempVecInfo.clear();
    int ntype = 0;
    for (int i = 0; i < bySize; ++i) {
        
        STC_SPE_MAP stcMap;
        packet >> stcMap.wMapId >> stcMap.dwReleaseTime >> stcMap.byIsOpen;
        m_vecActiviyMap.push_back(stcMap);
        tempVecInfo.push_back(stcMap);
        if (i == 0 || i == 1 || i == 3 || i + 1 == bySize) {
            m_mapActivityMap[ntype] = tempVecInfo;
            ntype++;
            tempVecInfo.clear();
        }
        
    }
    if (m_byFromJump) {
        PetLoadingLayer::sharedLayer()->End();
        CcbDropTipLayer::showDropTip(m_itemIndexId);
    } else {
        BackCtrl::ChangeRootScene(kChallengeIndexScene);
    }
}

bool StageCtrl::isActivityOpen(int _mapId) {
    bool bFind = false;
    VEC_SPE_MAP::iterator pIter;
    for (pIter = m_vecActiviyMap.begin(); pIter != m_vecActiviyMap.end(); pIter++) {
        if (pIter->wMapId == _mapId) {
            bFind = pIter->byIsOpen;
            break;
        }
    }
    return bFind;
}

/** 发送活动关卡列表}
 uint16	wStageId		关卡Id
 uint8	byNeedEnergy	需要能量
 uint8	byIsNew			是否新关卡
 uint8	byAttackCnt		每日攻打次数
 uint8	byAttackCnt		每日攻打总次数
 */
void StageCtrl::handlerActiveStageUpdate(WorldPacket &packet)
{
    uint16	_wStageId;		//关卡Id}
    uint8	_byNeedEnergy;	//需要能量}
    uint8	_byIsNew;		//是否新关卡}
    uint8	_byAttackCnt;	//每日攻打次数}
    uint8	_byMaxAttackCnt;	//每日攻打总次数}
    uint8   _byBuyCnt;
    
    packet >> _wStageId >> _byNeedEnergy >> _byIsNew >> _byAttackCnt >> _byMaxAttackCnt;
    packet >> _byBuyCnt;
    
    VECTOR_STAGE_TYPE::iterator pIter;
    for (pIter = m_vecStage.begin(); pIter != m_vecStage.end(); pIter++) {
        if (pIter->wStageId == _wStageId) {
            pIter->byCostEnergy = _byNeedEnergy;
            pIter->byStatus = _byIsNew;
            pIter->byAttackCnt = _byAttackCnt;
            pIter->byMaxAttCnt = _byMaxAttackCnt;
            pIter->byBuyCnt = _byBuyCnt;
            
            CGameSession::NotifyRefeashLayer();
            return;
        }
    }
}

#pragma mark StageScene

StageScene::~StageScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* StageScene::scene()
{
    CCScene* pScene = CCScene::create();
    StageScene* pLayer = StageScene::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

bool StageScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadStageLayer(this));
    return true;
}

void StageScene::onEnter() {
    CCLayer::onEnter();

    this->m_pLabelTTFName->setString(StageCtrl::Get()->curMapPointName());
}

void StageScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void StageScene::onExit()
{
    CCLayer::onExit();
}

void StageScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool StageScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
 
	return false;
}

bool StageScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。}
    bool bRet = false;
    if (pTarget == this)
    {
        if (0 == strcmp(pMemberVariableName, "mCustomPropertyInt"))
        {
            this->mCustomPropertyInt = pCCBValue->getIntValue();
            CCLog("mCustomPropertyInt = %d", mCustomPropertyInt);
            bRet = true;
        }
        else if ( 0 == strcmp(pMemberVariableName, "mCustomPropertyFloat"))
        {
            this->mCustomPropertyFloat = pCCBValue->getFloatValue();
            CCLog("mCustomPropertyFloat = %f", mCustomPropertyFloat);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyBoolean"))
        {
            this->mCustomPropertyBoolean = pCCBValue->getBoolValue();
            CCLog("mCustomPropertyBoolean = %d", mCustomPropertyBoolean);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyString"))
        {
            this->mCustomPropertyString = pCCBValue->getStringValue();
            CCLog("mCustomPropertyString = %s", mCustomPropertyString.c_str());
            bRet = true;
        }
        
    }
    
    return bRet;
}


