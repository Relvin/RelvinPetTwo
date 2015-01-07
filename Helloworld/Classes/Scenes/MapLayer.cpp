//
//  MapLayer.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-17.}
//
//

#include "MapLayer.h"
#include "StageScene.h"
#include "MapScene.h"
#include "MainScene.h"
#include "GameSession.h"
#include "BackCtrl.h"
#include "GlobalData.h"
#include "Role.h"
#include "EnumDefines.h"
#include "EffectLayer.h"
#include "GuideData.h"
#include "CcbManager.h"
#include "SystemMessage.h"
#include "Instruments.h"
#include "ResourcePic.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "FlyTextLayer.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "CcbMapPointLayer.h"
#include "CheckPointMgr.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;

MapLayer::~MapLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonActivity);
    CC_SAFE_RELEASE_NULL(m_pControlButtonNormal);
	CC_SAFE_RELEASE_NULL(m_pSpriteMap1);
	CC_SAFE_RELEASE_NULL(m_pSpriteMap2);
	CC_SAFE_RELEASE_NULL(m_pSpriteMap3);
    CC_SAFE_RELEASE_NULL(m_pSpriteMap4);
    CC_SAFE_RELEASE_NULL(m_pSpriteBg);
    CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
    CC_SAFE_RELEASE_NULL(m_pLayerActivity);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDiffcult);
    CC_SAFE_RELEASE_NULL(m_pNodeMap1);
    CC_SAFE_RELEASE_NULL(m_pNodeMap2);
    CC_SAFE_RELEASE_NULL(m_pNodeMap3);
    CC_SAFE_RELEASE_NULL(m_pNodeMap4);
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 
 
 //CcbManager.cpp

 */


bool MapLayer::init()
{
	// First be called.
	if (!CCLayer::init())
    {
		return false;
	}
	// code here
    
    CRole* pRole = CGameSession::GetRole();
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
        wMapId = pRole->GetwPassMapId();
        wStageId = pRole->GetwPassStageId();
        if (GlobalData::nCurNormalAreaIdx == -1)
        {
            int mapId = wStageId / 1000;
            if (mapId == 0)
            {
                m_nAreaIdx = 0;
            }
            else
            {
                MapConfig::STC_MAP_CONFIG* stcMap = GET_CONFIG_STC(MapConfig, mapId);
                if (stcMap)
                {
                    m_nAreaIdx = stcMap->byAreaId-1;
                } else {
                    // 此时应该是超出最大地图点，减一得到最大地图点}
                    stcMap = GET_CONFIG_STC(MapConfig, mapId-1);
                    m_nAreaIdx = stcMap->byAreaId-1;
                }
            }
        }
        else
        {
            m_nAreaIdx = GlobalData::nCurNormalAreaIdx;
        }

    } else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
        wMapId = pRole->GetwHeroMap();
        wStageId = pRole->GetwHeroStage();
        if (GlobalData::nCurHeroAreaIdx == -1)
        {
            int mapId = wStageId / 1000;
            if (mapId == 0)
            {
                m_nAreaIdx = 0;
            }
            else
            {
                MapConfig::STC_MAP_CONFIG* stcMap = GET_CONFIG_STC(MapConfig, mapId);
                if (stcMap)
                {
                    m_nAreaIdx = stcMap->byAreaId-1;
                } else {
                    // 此时应该是超出最大地图点，减一得到最大地图点}
                    stcMap = GET_CONFIG_STC(MapConfig, mapId-1);
                    m_nAreaIdx = stcMap->byAreaId-1;
                }
            }
            
        }
        else
        {
            m_nAreaIdx = GlobalData::nCurHeroAreaIdx;
        }

    }
    CCLog("cur area id:%d", m_nAreaIdx);
    
	return true;
}

void MapLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    setTouchEnabled(true);
    
    if ( CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV ) {
        if (m_pMapPoint1) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pMapPoint1, GuideBtnPos::E_MAP_ONE);
        }
        if (m_pMapPoint2) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pMapPoint2, GuideBtnPos::E_MAP_TWO);
        }
        if (m_pControlButtonActivity->isVisible()) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonActivity, GuideBtnPos::E_HERO_MAP);
        }
    }
}

void MapLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

    int nPassArea = CCUserDefault::sharedUserDefault()->getIntegerForKey(strBuf64);
    int nPassMapId = wMapId + 1;
    int nPassStageId = wStageId;
    
    CCLog("pass area:%d, pass map:%d, pass stage:%d", nPassArea, nPassMapId, nPassStageId);
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(MapLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void MapLayer::addGuideLayer()
{
    // GuideData::E_GUIDE_TRIGGER_FIR_ATTACK_1由于解锁面板去除，加入到这里。否则加到roundActionOver}
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_FIR_1_ATTACK,
                                             GuideData::E_GUIDE_TRIGGER_SEC_1_ATTACK,
                                             GuideData::E_GUIDE_TRIGGER_THI_1_ATTACK,
                                             GuideData::E_GUIDE_TRIGGER_1_FOUR_ATTACK,
                                             GuideData::E_GUIDE_TRIGGER_1_FIVE_ATTACK,
//                                             GuideData::E_GUIDE_TRIGGER_MAP_2,
                                             
                                             GuideData::E_SYS_GUIDE_1_HERO,
                                             GuideData::E_SYS_GUIDE_2_HERO,
                                             NULL
                                             );
}

void MapLayer::onExit()
{
	CCLayer::onExit();
}

void MapLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool MapLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonActivity", CCControlButton*, this->m_pControlButtonActivity);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonNormal", CCControlButton*, this->m_pControlButtonNormal);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMap1", CCSprite*, this->m_pSpriteMap1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMap2", CCSprite*, this->m_pSpriteMap2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMap3", CCSprite*, this->m_pSpriteMap3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMap4", CCSprite*, this->m_pSpriteMap4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerActivity", CCLayer*, this->m_pLayerActivity);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDiffcult", CCLabelTTF*, this->m_pLabelTTFDiffcult);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeMap1", CCNode*, this->m_pNodeMap1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeMap2", CCNode*, this->m_pNodeMap2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeMap3", CCNode*, this->m_pNodeMap3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeMap4", CCNode*, this->m_pNodeMap4);
    
	return false;
}

bool MapLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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

// Inhert CCBSelectorResolver
SEL_CallFuncN MapLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler MapLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_CCControlHandler MapLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", MapLayer::onPressControlButtonBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonActivity", MapLayer::onPressControlButtonActivity);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonStage", MapLayer::onPressControlButtonStage);
	return NULL;
}

// Inhert CCNodeLoaderListener
void MapLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}

    winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* dEff1 = CCSprite::create("ccbresources/12monthdate/universal/xuan_wo.png");
    dEff1->ignoreAnchorPointForPosition(false);
    CCParticleSystemQuad* dEff2 = CCParticleSystemQuad::create("ccbresources/12monthdate/universal/tdoor_2.plist");
    dEff1->setPosition(m_pControlButtonActivity->getPosition() - ccp(0, 4));
    dEff2->setPosition(m_pControlButtonActivity->getPosition() - ccp(-1, 4));
    dEff1->setScale(0.8);
    dEff1->runAction(CCRepeatForever::create(CCSpawn::create(CCRotateBy::create(3.0, -360),
                                                             CCScaleTo::create(1.5, 0.6),
                                                             CCScaleTo::create(1.5, 0.8),
                                                             NULL)));
    dEff2->setScale(0.7);
    m_pLayerActivity->addChild(dEff1, 3);
    m_pLayerActivity->addChild(dEff2, 3);
    m_pControlButtonActivity->setZOrder(1);
    m_pLabelTTFDiffcult->setZOrder(2);
    
    std::string strName = CGameSession::GetRole()->GetstrUserName();
    
    if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
        CCTexture2D* pTex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_mytown_base1));
        m_pSpriteBg->setTexture(pTex);
        snprintf(strBuf64, BUFFER_SIZE_64, "%s%s", D9_LOCAL_SPECIAL_MAP, strName.c_str());
        snprintf(mapFirstIdx, 64, "%s%s", D9_UNLOCK_SPECIAL_MAP, strName.c_str());
        //修改按钮文字}
        m_pControlButtonActivity->setVisible(false);
        m_pControlButtonNormal->setVisible(true);
    } else {
        snprintf(strBuf64, BUFFER_SIZE_64, "%s%s", D9_LOCAL_NORMAL_MAP, strName.c_str());
        snprintf(mapFirstIdx, 64, "%s%s", D9_UNLOCK_NORMAL_MAP, strName.c_str());
        m_pControlButtonActivity->setVisible(true);
        m_pControlButtonNormal->setVisible(false);
        dEff1->setColor(ccRED);
    }
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger == GuideData::E_GUIDE_TRIGGER_FIR_1_ATTACK ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_SEC_1_ATTACK ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_THI_TALK_1 ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_1_FOUR_ATTACK ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_1_FIVE_ATTACK
        ) {
        m_pLayerActivity->setVisible(false);
        m_pControlButtonBack->setVisible(false);
    }
    
    bCanMoveLeft = bCanMoveRight = false;
    
    bCanTouch = true;
    bFromBegin = false;
    bMoved = false;
    
    
    int nUnlckFlag = CCUserDefault::sharedUserDefault()->getIntegerForKey(mapFirstIdx);
    // 判断是否是新开大地图}
    if (nUnlckFlag == 0 && wMapId == 8 && wStageId == 8008) {
        // 第一章地图8个地图点，第8个地图点8个stage}
        m_nAreaIdx = 1;
        nUnlckFlag = 1;
        CCUserDefault::sharedUserDefault()->setIntegerForKey(mapFirstIdx, nUnlckFlag);
    } else if (nUnlckFlag == 1 && wMapId == 15 && wStageId == 15010) {
        // 第二章地图}
        m_nAreaIdx = 2;
        nUnlckFlag = 2;
        CCUserDefault::sharedUserDefault()->setIntegerForKey(mapFirstIdx, nUnlckFlag);
    }
//TODO:    else if (nUnlckFlag == 2 && )
    // 第三章地图通关后没有第四章地图}
    
    m_pSpriteMap1->setZOrder(1);
    m_pSpriteMap2->setZOrder(2);
    m_pSpriteMap3->setZOrder(3);
    m_pSpriteMap4->setZOrder(4);
    
    m_pSpriteMap1->setPositionX(winSize.width*0.5);
    m_pSpriteMap2->setPositionX(winSize.width*0.5);
    m_pSpriteMap3->setPositionX(winSize.width*0.5);
    m_pSpriteMap4->setPositionX(winSize.width*0.5);
    
    m_nViewIdx = m_nAreaIdx % 4; //TODO: 1. 超出4个Map，更新扇形背景图 2. 初始定位到View Idx，现在默认还是第一个扇形地图}
    //[2013-12-04] Update: 现只支持最大4张地图，超过部分需要替换背景图}
    
    m_pMaps[0] = m_pSpriteMap1;
    m_pMaps[1] = m_pSpriteMap2;
    m_pMaps[2] = m_pSpriteMap3;
    m_pMaps[3] = m_pSpriteMap4;
    
    m_pNodeMaps[0] = m_pNodeMap1;
    m_pNodeMaps[1] = m_pNodeMap2;
    m_pNodeMaps[2] = m_pNodeMap3;
    m_pNodeMaps[3] = m_pNodeMap4;
    
    for (int i = 0; i < 4; i++) {
        m_fMapRotation[i] = m_pMaps[i]->getRotationX() - 90.0f*m_nViewIdx;
        m_pMaps[i]->setRotation(m_fMapRotation[i]);
    }
    
    placeMapPoint();
}

void MapLayer::upLeftRightStatus()
{
    bCanMoveLeft = bCanMoveRight = true;
    if (m_nAreaIdx == MapCtrl::nOpenArea - 1) {
        bCanMoveLeft = false;
    }
    if (m_nAreaIdx == 0) {
        bCanMoveRight = false;
    }
}

void MapLayer::addMapPointsToArea(int nDataIdx, int nViewIdx)
{
    upLeftRightStatus();
    if (nDataIdx >= MapCtrl::nOpenArea) {
        // 如果Area数据Idx比已经开放的Area还要大，则返回。OpenArea从1开始，DataIdx从0开始}
        bCanMoveLeft = false;
        return;
    }
    if (nDataIdx < 0) {
        bCanMoveRight = false;
        return;
    }
    
    //TODO: change cur map bg sprite!!, 如果当前的AreaId > 4}
    
    if (MapCtrl::m_vecArea.size() == 0) {
        CCMessageBox("null map data!", "error");
        return;
    }
    
    MapCtrl::VECTOR_POINT_TYPE curArea = MapCtrl::m_vecArea[nDataIdx];
    int nSize = curArea.size();
    int nStatus = 1; //默认为新地图，未通关 //0 通关; 1 未通关}

    
    for (int i = 0; i < nSize; i++) {
        MapConfig::STC_MAP_CONFIG pConfig = curArea[i].map_config;
        
//        // 最后一个Area的最后一个地图点为新地图，未通关地图}
//            if (wStageId == 0) {    // 此时wStageId == 0为新手刚进入}
//                // 判断是否超出最大地图点，如果超出最大地图点，此时wStageId=23001, 23超出最大地图点}

        CcbMapPointLayer* point = dynamic_cast<CcbMapPointLayer*>(CcbManager::sharedManager()->LoadCcbMapPointLayer(this));
        point->setMapPoint(nStatus, pConfig.strName, curArea[i].strDes, curArea[i].strTime, pConfig.wMapId);

        
        point->ignoreAnchorPointForPosition(false);
        point->setAnchorPoint(ccp(0.5, 0.5));
        point->setPosition(ccp((float)pConfig.posX, (float)pConfig.posY));

        // clear
        if (pConfig.wMapId <= wMapId) {
            point->setMapClear();
        }
        else{
            point->setMapNew();
        }
        
        m_pNodeMaps[nViewIdx]->addChild(point);
        
        uint8 byClicked = 1;
        
        if (i == nSize-1 && nDataIdx == MapCtrl::nOpenArea-1) {
            if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
                MapCtrl::setMapPointClicked(MapCtrl::kMapStarNormal, pConfig.wMapId);
            } else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
                MapCtrl::setMapPointClicked(MapCtrl::kMapStarHero, pConfig.wMapId);
            }
            byClicked = MapCtrl::bMapPointClicked;
            
            if (!byClicked) {
                point->setMapNotOpen();
            }
        }

        if (byClicked) {
            int bonusId = 100*StageCtrl::Get()->kind() + pConfig.wMapId;
            StageBonusConfig::STC_CONFIG_BONUS* pStageBonus = GET_CONFIG_STC(StageBonusConfig, bonusId);
            
            uint32 dwAllStarGet;
            if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
                dwAllStarGet = MapCtrl::starCntInMap(MapCtrl::kMapStarNormal, pConfig.wMapId);
            } else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
                dwAllStarGet = MapCtrl::starCntInMap(MapCtrl::kMapStarHero, pConfig.wMapId);
            }
            
            uint32 dwMaxStar = 0;
            int k = 2;
            while (dwMaxStar == 0 && k >= 0) {
                dwMaxStar = pStageBonus->wRewardNeed[k];
                k--;
            }
            if (dwAllStarGet == 0) {
                point->setMapStarCnt(0);
            } else if (dwAllStarGet < (dwMaxStar + 1) / 2) {
                point->setMapStarCnt(1);
            } else if (dwAllStarGet < dwMaxStar) {
                point->setMapStarCnt(2);
            } else {
                point->setMapStarCnt(3);
            }
        }
        
        if (i == 0) {
            m_pMapPoint1 = point;
        } else if (i == 1) {
            m_pMapPoint2 = point;
        }
    }
}


// 放置stage点到当前map，以及之前之后的map上。}
void MapLayer::placeMapPoint()
{
    addMapPointsToArea(m_nAreaIdx, m_nViewIdx);
    addMapPointsToArea(m_nAreaIdx + 1, getCycleSpriteIdx(m_nViewIdx + 1));
    addMapPointsToArea(m_nAreaIdx - 1, getCycleSpriteIdx(m_nViewIdx - 1));
}

void MapLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    BackCtrl::BacktoUpperScene(kFadeTrans);
}

void MapLayer::onPressControlButtonActivity(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_SPECIAL);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
        StageCtrl::Get()->setKind(StageCtrl::kSpecialStage);
    } else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
        StageCtrl::Get()->setKind(StageCtrl::kNormalStage);
    } else {
        CCAssert(1, "Stage Kind Error");
    }
    CGameSession::SendNormalMap();
}

#pragma mark ccTouch Delegate

void MapLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool MapLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!bCanTouch) {
        return true;
    }
    bFromBegin = true;
    bMoved = false;
    
    m_pointStart = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());

    for (int i = 0; i < 4; i++) {
        m_fMapRotation[i] = m_pMaps[i]->getRotationX();
    }
    
    return true;
}

void MapLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!bCanTouch || !bFromBegin) {
        return;
    }
    CCPoint pointMove = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    float distance = (pointMove.x - m_pointStart.x);
    
    if ( !bCanMoveLeft && distance < 0 ) {
        return;
    }
    if ( !bCanMoveRight && distance > 0) {
        return;
    }
    bMoved = true;
    updateRotationWithDistance(distance);
    return;
}

void MapLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!bCanTouch || !bFromBegin || !bMoved) {
        return;
    }
    CCPoint pointEnd = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    float distance = pointEnd.x - m_pointStart.x;
    
    if ( !bCanMoveLeft && distance < -15.0 ) {
        adjustMapPosition(0.0);
        return;
    }
    if ( !bCanMoveRight && distance > 15.0) {
        adjustMapPosition(0.0);
        return;
    }
    
    if (fabsf(distance) > 30.0) {
        adjustMapPosition(distance);
    } else {
        adjustMapPosition(0.0);
    }
    bFromBegin = false;
}

void MapLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("cancel!!!");
}

#pragma mark Private Method


void MapLayer::updateRotationWithDistance(float distance)
{
    float fMapRotation[Map_Circle];
    
    for (int i = 0; i < Map_Circle; i++) {
        fMapRotation[i] = m_fMapRotation[i] + (distance * 0.25);
        m_pMaps[i]->setRotation(fMapRotation[i]);
    }
}

int MapLayer::getCycleSpriteIdx(int curIdx) {
    if (curIdx >= Map_Circle) {
        curIdx -= Map_Circle;
    }
    if (curIdx <= -1) {
        curIdx += Map_Circle;
    }
    return curIdx;
}

void MapLayer::setControlTouchEnable()
{
    bCanTouch = true;
    
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
        GlobalData::nCurNormalAreaIdx = m_nAreaIdx;
    } else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
        GlobalData::nCurHeroAreaIdx = m_nAreaIdx;
    }
}

void MapLayer::mapRunAction(float offset)
{
    for (int i = 0; i < Map_Circle-1; i++) {
        m_pMaps[i]->runAction( CCRotateTo::create(0.5f, m_fMapRotation[i] + offset) );
    }
    m_pMaps[Map_Circle-1]->runAction( CCSequence::create(CCRotateTo::create(0.5f, m_fMapRotation[Map_Circle-1]+offset), CCCallFunc::create(this, callfunc_selector(MapLayer::setControlTouchEnable)), NULL) );
}

void MapLayer::adjustMapPosition(float dis)
{
    bCanTouch = false;
    
    if (dis == 0) {
        // do nothing
    } else if (dis < -1.0) {
        bIsMoveLeft = true;
        m_nAreaIdx++;
        m_nViewIdx++;
        if (m_nAreaIdx == MapCtrl::nOpenArea) {
            bCanMoveLeft = false;
            CCMessageBox("rotation left error", "error");
        }
        
        m_nViewIdx = getCycleSpriteIdx(m_nViewIdx);
    } else if (dis > 1.0){
        bIsMoveLeft = false;
        m_nAreaIdx--;
        m_nViewIdx--;
        if (m_nAreaIdx < 0) {
            bCanMoveRight = false;
            CCMessageBox("rotation right error", "error");
        }
        m_nViewIdx = getCycleSpriteIdx(m_nViewIdx);
    }
    
    if (dis == 0) {
        // back to origin!!!
        mapRunAction(0.0);
    } else {
        if (bIsMoveLeft) {
            mapRunAction(-90.0);
            m_pNodeMaps[getCycleSpriteIdx(m_nViewIdx-2)]->removeAllChildrenWithCleanup(true);
            addMapPointsToArea(m_nAreaIdx+1, getCycleSpriteIdx(m_nViewIdx + 1));
        } else {
            mapRunAction(90.0);
            m_pNodeMaps[getCycleSpriteIdx(m_nViewIdx+2)]->removeAllChildrenWithCleanup(true);
            addMapPointsToArea(m_nAreaIdx-1, getCycleSpriteIdx(m_nViewIdx - 1));
        }
        
        // 将超出|1|的Area上的地图点点去除，新加入的Area增加地图点}
    }
}

#pragma mark - Stage Enter -
void MapLayer::onPressControlButtonStage(CCObject *pSender, CCControlEvent controlEvent)
{
    if (!bCanTouch) {
        return;
    }
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    CCLog("MapLayer::touch stage button.");
    CCNode* pNode = dynamic_cast<CCNode*>(pSender);
    
    if (!pNode) {
        CCMessageBox("Node Null", "map point");
        return;
    }
    
    int mapId = pNode->getTag();
    CCLOG("send Map Id:%d request stage list......", mapId);
    MapCtrl::nSelectedMapId = mapId;
    
    CheckPointMgr::Get()->clrTalkData();
    
    kalilil();
}

void MapLayer::kalilil()
{
    int mapId = MapCtrl::nSelectedMapId;
    MapConfig::STC_MAP_CONFIG* pMapConfig = GET_CONFIG_STC(MapConfig, mapId);
    if ( pMapConfig ) {
        uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
        if (
            wTrigger == GuideData::E_GUIDE_TRIGGER_FIR_3_ATTACK ||
            wTrigger == GuideData::E_GUIDE_END_TRIGGER
            ) {
            GuideData::GetInstance()->onlyRmGuideLayer();
        }
        
        StageCtrl::Get()->setCurMapPointName(pMapConfig->strName);
        
        // 将所有的关卡点都禁掉}
        bCanTouch = false;
        
        this->runAction(
                        CCSequence::create(
                                           CCDelayTime::create(0.3f),
                                           CCCallFunc::create(this, callfunc_selector(MapLayer::setControlTouchEnable)),
                                           NULL
                                           )
                        );
        
        StageCtrl::Get()->setFromJump(false);
        PetLoadingLayer::sharedLayer()->WaitForPacket(true);
        CGameSession::SendReqStageInfo(StageCtrl::Get()->kind(), mapId);
    } else {
        CCMessageBox("Get Name From Map Error", "Error");
    }
}

void MapLayer::onActionOver()
{
    int nCurMap = wMapId + 1;
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(strBuf64, nCurMap);
    bCanTouch = true;
}


void MapLayer::setOpacity(GLubyte opacity)
{
    if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>( pObject );
			if (pRGBAProtocol)
			{
				pRGBAProtocol->setOpacity(opacity);
			}
		}
	}
}

//void MapLayer::showStep()
//{
//    m_nVecIdx++;
//    if (m_nVecIdx >= CheckPointMgr::Get()->talkPadCnt()) {
//        kalilil();
//        return;
//    }
//    
//    CheckPointMgr::Get()->addMapTalk(m_nVecIdx, this);
//}

