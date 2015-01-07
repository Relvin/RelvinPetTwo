#include "CcbChallengeMapLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "ChallengeDataMgr.h"
#include "UISupport.h"
#include "ConfigGet.h"
#include "Instruments.h"
#include "SystemMessage.h"
#include "ResourceStringClient.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "FlyTextLayer.h"
#include "EnumDefines.h"
#include "WorldInfoDataMgr.h"
#include "PacketDataMgr.h"
#include "GuideData.h"
#include "GuideBtnPos.h"

CcbChallengeMapLayer::~CcbChallengeMapLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonReset);
    CC_SAFE_RELEASE_NULL(m_pControlButton_Go);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
    CC_SAFE_RELEASE_NULL(m_pControlButtonReward);
    CC_SAFE_RELEASE_NULL(m_pNodeRule);
    CC_SAFE_RELEASE_NULL(m_pControlButtonRule);
    CC_SAFE_RELEASE_NULL(m_pControlButtonWeather);
    CC_SAFE_RELEASE_NULL(m_pSpriteTip);
    CC_SAFE_RELEASE_NULL(m_pNodeWeather);
    CC_SAFE_RELEASE_NULL(m_pSpriteWeather);
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteWeather);
    
    CC_SAFE_RELEASE_NULL(m_pLabelTTFW_1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFW_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFW_3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFW_4);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFW_5);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFW_6);
    m_curScene = NULL;
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbChallengeMapLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbChallengeMapLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbChallengeMapLayer", CcbChallengeMapLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pavilion_map.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CcbChallengeMapLayer* CcbChallengeMapLayer::m_curScene = NULL;

CCScene* CcbChallengeMapLayer::scene()
{
    CCScene* scene = CCScene::create();
    CCNode* layer = CcbManager::sharedManager()->LoadCcbChallengeMapLayer(scene);
    scene->addChild(layer);
    return scene;
}

bool CcbChallengeMapLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
    m_curScene = this;
	return true;
}

void CcbChallengeMapLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    
    CGameSession::SendReqChallengeInfo();
}

void CcbChallengeMapLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbChallengeMapLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbChallengeMapLayer::addGuideLayer() {
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonWeather, GuideBtnPos::E_WEATHER);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonBack, GuideBtnPos::E_YIJI_BACK);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButton_Go, GuideBtnPos::E_YIJI_POINT);
        
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_2_BADGE,
                                                 GuideData::E_SYS_GUIDE_5_BADGE,
                                                 NULL
                                                 );
    }
}

void CcbChallengeMapLayer::onExit()
{
	CCLayer::onExit();
}

void CcbChallengeMapLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbChallengeMapLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReset", CCControlButton*, this->m_pControlButtonReset);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButton_Go", CCControlButton*, this->m_pControlButton_Go);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReward", CCControlButton*, this->m_pControlButtonReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeRule", CCNode*, this->m_pNodeRule);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRule", CCControlButton*, this->m_pControlButtonRule);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonWeather", CCControlButton*, this->m_pControlButtonWeather);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTip", CCSprite*, this->m_pSpriteTip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeWeather", CCNode*, this->m_pNodeWeather);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteWeather", CCSprite*, this->m_pSpriteWeather);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteWeather", CCScale9Sprite*, this->m_pScale9SpriteWeather);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFW_1", CCLabelTTF*, this->m_pLabelTTFW_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFW_2", CCLabelTTF*, this->m_pLabelTTFW_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFW_3", CCLabelTTF*, this->m_pLabelTTFW_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFW_4", CCLabelTTF*, this->m_pLabelTTFW_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFW_5", CCLabelTTF*, this->m_pLabelTTFW_5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFW_6", CCLabelTTF*, this->m_pLabelTTFW_6);
	return false;
}

bool CcbChallengeMapLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbChallengeMapLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeMapLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeMapLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReset", CcbChallengeMapLayer::onPressControlButtonReset);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLevel", CcbChallengeMapLayer::onPressControlButtonLevel);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbChallengeMapLayer::onPressControlButtonBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReward", CcbChallengeMapLayer::onPressControlButtonReward);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRule", CcbChallengeMapLayer::onPressControlButtonRule);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonWeather", CcbChallengeMapLayer::onPressControlButtonWeather);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbChallengeMapLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pSpriteTip->setVisible(false);
    m_pControlButton_Go->getParent()->setVisible(false);
    m_pControlButtonReset->setVisible(false);
    
    m_pNodeRule->setScale(0);
    if (CGameSession::GetRole()->GetwGuideTrigger() != GuideData::E_SYS_GUIDE_2_BADGE) {
        m_pNodeWeather->setScale(0);
    }
    
    m_pSpriteWeather->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(1.5, 0.95),
                                                                           CCScaleTo::create(1.5, 1.0),
                                                                           NULL)));
    
    arrPoint.push_back(ccp(45, 400));
    arrPoint.push_back(ccp(155, 350));
    arrPoint.push_back(ccp(195, 220));
    arrPoint.push_back(ccp(280, 160));
    arrPoint.push_back(ccp(50, 150));
    arrPoint.push_back(ccp(110, 30));
    
    arrWdes.push_back(m_pLabelTTFW_1);
    arrWdes.push_back(m_pLabelTTFW_2);
    arrWdes.push_back(m_pLabelTTFW_3);
    arrWdes.push_back(m_pLabelTTFW_4);
    arrWdes.push_back(m_pLabelTTFW_5);
    arrWdes.push_back(m_pLabelTTFW_6);
}



void CcbChallengeMapLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    BackCtrl::BacktoUpperScene();
}

void CcbChallengeMapLayer::onPressControlButtonReward(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    m_pNodeRule->setScale(0);
    m_pNodeWeather->setScale(0);
    
    if (m_rewardLayer) {
        m_rewardLayer->setVisible(true);
    }
    else{
        m_rewardLayer = dynamic_cast<CcbChallengeOverRewardLayer*>(CcbManager::sharedManager()->LoadCcbChallengeOverRewardLayer(this));
        m_rewardLayer->setPosition(CCPointZero);
        m_rewardLayer->setAnchorPoint(CCPointZero);
        addChild(m_rewardLayer, 10);
    }
}

void CcbChallengeMapLayer::onPressControlButtonLevel(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    m_pNodeRule->setScale(0);
    m_pNodeWeather->setScale(0);
    
    showChalLayer();
}

void CcbChallengeMapLayer::onPressControlButtonReset(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_pNodeRule->setScale(0);
    m_pNodeWeather->setScale(0);
    
    STC_CHA_LEVEL_INFO chaInfo = g_ChallengeDataMgr->getCurStageInfo();
    if (chaInfo.wIndexId == 0) {
        return;
    }
    if (chaInfo.wIndexId == 1) {
        FlyTextLayer::showTips("当前进度是第1关，无须重置~");
    }
    else{
        SystemMessage::showSystemMessage(1, this, CCString::createWithFormat("当前进度第%d关，重置回到第1关重新挑战，确定重置吗？", chaInfo.wIndexId)->getCString(), this);
    }
    
}

void CcbChallengeMapLayer::onPressControlButtonRule(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    m_pNodeWeather->setScale(0);
    if (m_pNodeRule->getScale() == 0) {
//        m_pNodeRule->setScale(0);
        m_pNodeRule->runAction(CCSequence::create(CCScaleTo::create(0.2, 1.0),
//                                                  CCScaleTo::create(0.05, 0.95),
//                                                  CCScaleTo::create(0.05, 1.0),
                                                  NULL));
    }
    else{
        m_pNodeRule->setScale(0);
    }
}

void CcbChallengeMapLayer::onPressControlButtonWeather(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    m_pNodeRule->setScale(0);
    if (m_pNodeWeather->getScale() == 0) {
//        m_pNodeWeather->setScale(0);
        m_pNodeWeather->runAction(
                                  CCSequence::create(
                                                     CCScaleTo::create(0.2, 1.0),
//                                                  CCScaleTo::create(0.05, 0.95),
//                                                  CCScaleTo::create(0.05, 1.0),
                                                  NULL
                                                     )
                                  );
    }
    else{
        m_pNodeWeather->setScale(0);
        if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
            GuideData::GetInstance()->addGuideofEnum(
                                                     GuideData::E_SYS_GUIDE_3_BADGE,
                                                     NULL
                                                     );
        }
    }
}

void CcbChallengeMapLayer::showChalLayer()
{
    if (m_chalLayer) {
        m_chalLayer->setVisible(true);
    }
    else
    {
        m_chalLayer = dynamic_cast<CcbChallengeLayer*>(CcbManager::sharedManager()->LoadCcbChallengeLayer(this));
        m_chalLayer->setPosition(CCPointZero);
        m_chalLayer->setAnchorPoint(CCPointZero);
        addChild(m_chalLayer, 10);
    }
    
}

void CcbChallengeMapLayer::reflash()
{
    PetLoadingLayer::sharedLayer()->End();
    loadData();
    if (m_rewardLayer) {
        m_rewardLayer->loadData();
    }
    if (m_chalLayer) {
        m_chalLayer->loadData();
    }
}

void CcbChallengeMapLayer::loadData()
{
    STC_CHA_LEVEL_INFO info = g_ChallengeDataMgr->getCurStageInfo();
    if (info.wIndexId == 0) {
        return;
    }
    m_pControlButton_Go->getParent()->setVisible(false);
    m_pSpriteTip->setVisible(false);
    
    //天气
    uint8 weather = WorldInfoDataMgr::Get()->getWeather();
    m_pSpriteWeather->setDisplayFrame(g_PacketDataMgr->getWeatherSF(weather));
    setWeatherLbl(weather);
    
    //重置
    if (info.byResetCnt > 0) {
        m_pControlButtonReset->setVisible(true);
    }
    else{
        m_pControlButtonReset->setVisible(false);
    }
    
    if (info.byRewStatus != E_REW_STATUS_NEW) {
        if (info.byRewStatus == E_REW_STATUS_CAN) {
            m_pSpriteTip->setVisible(true);
            showEff();
        }
        else if (info.byRewStatus == E_REW_STATUS_DONE){
            if (m_pControlButtonReward->getParent()->getChildByTag(111)) {
                m_pControlButtonReward->getParent()->removeChildByTag(111);
            }
            
            if (m_pControlButtonReward->getParent()->getChildByTag(112)) {
                m_pControlButtonReward->getParent()->removeChildByTag(112);
            }
        }
        return;
    }
    
    ChallengeConfig::STC_CHALLENGE_CONFIG* chCfg = GET_CONFIG_STC(ChallengeConfig, info.wIndexId);
    if (!chCfg) {
        return;
    }
    m_pLabelTTFName->setString(chCfg->strName.c_str());
    int p = rand() % arrPoint.size();
    m_pControlButton_Go->getParent()->setPosition(arrPoint[p]);
    m_pControlButton_Go->getParent()->setVisible(true);
    
}

void CcbChallengeMapLayer::handlerUpdateBuff()
{
    uint8 weather = WorldInfoDataMgr::Get()->getWeather();
    m_pSpriteWeather->setDisplayFrame(g_PacketDataMgr->getWeatherSF(weather));
    setWeatherLbl(weather);
}

void CcbChallengeMapLayer::showEff()
{
    CCParticleSystemQuad* eff1 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/eff_jiangli_1.plist");
    CCParticleSystemQuad* eff2 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/eff_jiangli_2.plist");
    
    eff1->setPosition(m_pControlButtonReward->getPosition() - ccp(0, getHeight(m_pControlButtonReward)*0.5));
    eff1->setTag(111);
    m_pControlButtonReward->getParent()->addChild(eff1);
    
    eff2->setTag(112);
    eff2->setPosition(getCenter(m_pControlButtonReward));
    m_pControlButtonReward->getParent()->addChild(eff2);
}

void CcbChallengeMapLayer::setWeatherLbl(uint8 weather)
{
    for (int i = 0; i < arrWdes.size(); i++) {
        arrWdes[i]->setColor(ccWHITE);
    }
    
    arrWdes[weather - 1]->setColor(ccGREEN);
}

bool CcbChallengeMapLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_pNodeWeather) {
        m_pNodeWeather->setScale(0);
    }
    
    if (m_pNodeRule) {
        m_pNodeRule->setScale(0);
    }

    return isVisible();
}

void CcbChallengeMapLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

void CcbChallengeMapLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendResetChallengeBless();
}