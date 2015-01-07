#include "CcbChallengeLayer.h"
#include "CcbManager.h"
#include "ChallengeDataMgr.h"
#include "UISupport.h"
#include "ConfigGet.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "CcbPetIcon.h"
#include "CcbItemIconLayer.h"
#include "GuideBtnPos.h"
#include "GuideData.h"
#include "ConfigGet.h"

CcbChallengeLayer::~CcbChallengeLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDeffenceLv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDeffenceName);
    CC_SAFE_RELEASE_NULL(m_pLayerDefIcon_1);
    CC_SAFE_RELEASE_NULL(m_pLayerDefIcon_2);
    CC_SAFE_RELEASE_NULL(m_pLayerDefIcon_3);
    CC_SAFE_RELEASE_NULL(m_pLayerDefIcon_4);
    CC_SAFE_RELEASE_NULL(m_pLayerDefIcon_5);
    CC_SAFE_RELEASE_NULL(m_pLayerDefIcon_6);
    CC_SAFE_RELEASE_NULL(m_pNodeDeffencePet);
    CC_SAFE_RELEASE_NULL(m_pLayerGetCoin);
    CC_SAFE_RELEASE_NULL(m_pLayerGetEmblem);
    CC_SAFE_RELEASE_NULL(m_pNodeChallengeReward);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFChallengeNum);
    CC_SAFE_RELEASE_NULL(m_pControlButtonGochallenge);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbChallengeLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbChallengeLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbChallengeLayer", CcbChallengeLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/pavilion_over_reward_frame.ccb]", [ccb/pavilion_over_reward_frame.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pavilion_vielist.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbChallengeLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbChallengeLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbChallengeLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbChallengeLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbChallengeLayer::addGuideLayer() {
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonGochallenge, GuideBtnPos::E_WANT_YIJI);
        
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_4_BADGE,
                                                 NULL
                                                 );
    }
}

void CcbChallengeLayer::onExit()
{
	CCLayer::onExit();
}

void CcbChallengeLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbChallengeLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDeffenceLv", CCLabelTTF*, this->m_pLabelTTFDeffenceLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDeffenceName", CCLabelTTF*, this->m_pLabelTTFDeffenceName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDefIcon_1", CCLayer*, this->m_pLayerDefIcon_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDefIcon_2", CCLayer*, this->m_pLayerDefIcon_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDefIcon_3", CCLayer*, this->m_pLayerDefIcon_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDefIcon_4", CCLayer*, this->m_pLayerDefIcon_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDefIcon_5", CCLayer*, this->m_pLayerDefIcon_5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDefIcon_6", CCLayer*, this->m_pLayerDefIcon_6);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeDeffencePet", CCNode*, this->m_pNodeDeffencePet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerGetCoin", CCLayer*, this->m_pLayerGetCoin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerGetEmblem", CCLayer*, this->m_pLayerGetEmblem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeChallengeReward", CCNode*, this->m_pNodeChallengeReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFChallengeNum", CCLabelTTF*, this->m_pLabelTTFChallengeNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGochallenge", CCControlButton*, this->m_pControlButtonGochallenge);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);

	return false;
}

bool CcbChallengeLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbChallengeLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGochallenge", CcbChallengeLayer::onPressControlButtonGochallenge);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbChallengeLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbChallengeLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonGochallenge->setTouchPriority(kCCMenuHandlerPriority - 6);
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 6);
}



void CcbChallengeLayer::onPressControlButtonGochallenge(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    STC_CHA_LEVEL_INFO chaInfo = g_ChallengeDataMgr->getCurStageInfo();
    g_ChallengeDataMgr->setCurFightStage(chaInfo.wIndexId);
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendReqChallengeFight();
}

void CcbChallengeLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    setVisible(false);
}

void CcbChallengeLayer::loadData()
{
    STC_CHA_LEVEL_INFO chaInfo = g_ChallengeDataMgr->getCurStageInfo();
    if (chaInfo.wIndexId == 0) {
        return;
    }
    //敌人名字
    m_pLabelTTFDeffenceName->setString(chaInfo.strDefName.c_str());
    //敌人等级
    CCString *str = CCString::createWithFormat("%s%d", SB_Lv, chaInfo.wRoleLv);
    m_pLabelTTFDeffenceLv->setString(str->getCString());
    
    //关卡
    str->initWithFormat("%d", chaInfo.wIndexId);
    m_pLabelTTFChallengeNum->setString(str->getCString());
    
    
    std::vector<CCLayer*> arrPetIcon;
    arrPetIcon.push_back(m_pLayerDefIcon_1);
    arrPetIcon.push_back(m_pLayerDefIcon_2);
    arrPetIcon.push_back(m_pLayerDefIcon_3);
    arrPetIcon.push_back(m_pLayerDefIcon_4);
    arrPetIcon.push_back(m_pLayerDefIcon_5);
    arrPetIcon.push_back(m_pLayerDefIcon_6);
    //敌方阵营
    int cnt = 0;
    for (int i = 0; i < chaInfo.arrPetId.size(); i++) {
        if (chaInfo.arrPetId[i] == 0) {
            continue;
        }
        PetConfig::STC_PET_CONFIG *pConfigPet = GET_CONFIG_STC(PetConfig, chaInfo.arrPetId[i]);
        if (!pConfigPet)
        {
            continue;
        }
        CcbItemIconLayer* icon = dynamic_cast<CcbItemIconLayer*>(arrPetIcon[cnt]);
        icon->loadIndexData(chaInfo.arrPetId[i]);
        icon->showStarLv(pConfigPet->byStarLv);
        icon->setBtnEnable(false);
        icon->setVisible(true);
        cnt++;
    }
    
    for (; cnt < 6; cnt++) {
        arrPetIcon[cnt]->setVisible(false);
    }
    
    //获得奖励
    for (int i = 0; i < chaInfo.arrRewItemId.size(); i++) {
        if (!chaInfo.arrRewItemId[i]) {
            continue;
        }
        if (chaInfo.arrRewItemId[i] == E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_COIN) {
            CcbItemIconLayer* item = dynamic_cast<CcbItemIconLayer*>(m_pLayerGetCoin);
            item->loadIndexData(chaInfo.arrRewItemId[i]);
            item->showIconOnly();
            item->showCnt(chaInfo.arrRewItemCnt[i]);
            item->showName();
            continue;
        }
        
        CcbItemIconLayer* item = dynamic_cast<CcbItemIconLayer*>(m_pLayerGetEmblem);
        item->loadIndexData(chaInfo.arrRewItemId[i]);
        item->showIconOnly();
        item->showName();
        break;
    }
}


bool CcbChallengeLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return isVisible();
}

void CcbChallengeLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);
}

