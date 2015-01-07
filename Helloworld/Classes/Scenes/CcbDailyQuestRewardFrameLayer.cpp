#include "CcbDailyQuestRewardFrameLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "ConfigData.h"
#include "TaskDataMgr.h"
#include "ResourcePic.h"
#include "Defines.h"
#include "PacketDataMgr.h"
#include "ResourceStringClient.h"
#include "PetLoadingLayer.h"
#include "BackCtrl.h"
#include "UISupport.h"
#include "CCFlowFire.h"

CcbDailyQuestRewardFrameLayer::~CcbDailyQuestRewardFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReward);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFReward);
    CC_SAFE_RELEASE_NULL(m_pSpriteFinish);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSchedule);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRewardNum);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFScheduleValue);
    
    
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbDailyQuestRewardFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbDailyQuestRewardFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbDailyQuestRewardFrameLayer", CcbDailyQuestRewardFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/dailyquest_reward_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbDailyQuestRewardFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbDailyQuestRewardFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbDailyQuestRewardFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->updateRewardButtonStatus();
}

void CcbDailyQuestRewardFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbDailyQuestRewardFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbDailyQuestRewardFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReward", CCControlButton*, this->m_pControlButtonReward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFReward", CCLabelTTF*, this->m_pLabelTTFReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFinish", CCSprite*, this->m_pSpriteFinish);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSchedule", CCLabelTTF* , this->m_pLabelTTFSchedule);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRewardNum", CCLabelTTF*, this->m_pLabelTTFRewardNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFScheduleValue", CCLabelTTF*, this->m_pLabelTTFScheduleValue);
	return false;
}

bool CcbDailyQuestRewardFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbDailyQuestRewardFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbDailyQuestRewardFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbDailyQuestRewardFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReward", CcbDailyQuestRewardFrameLayer::onPressControlButtonReward);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbDailyQuestRewardFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbDailyQuestRewardFrameLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool CcbDailyQuestRewardFrameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_StartTouchPos = CCPoint(0, 0);
    m_StartTouchPos = pTouch->getLocation();
    return true;
}

void CcbDailyQuestRewardFrameLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_EndTouchPos = CCPoint(0, 0);
    m_EndTouchPos = pTouch->getLocation();
}

void CcbDailyQuestRewardFrameLayer::onPressControlButtonReward(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    if( fabs(m_StartTouchPos.x - m_EndTouchPos.x) > 20 || fabs(m_StartTouchPos.y - m_EndTouchPos.y) > 10)
    {
        return;
    }
    CCControlButton* pButton = (CCControlButton *)pSender;
    if (!pButton) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (m_byRewardType == ENUM_DAILYREWARD) {
        if (pButton->getTag() == 1) {
            CGameSession::SendDailyQuestRewardRequest(ENUM_DAILYREWARD, m_dwIndex);
        }
        else
        {
            BackCtrl::changeNextSceneWithSafety(m_strNextSceneTag.c_str());
        }
        
    }
    else
    {
        if (pButton->getTag() == 1) {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendAchieveRewardRequest(m_nShowType, m_dwIndex);
        }
        else
        {
             BackCtrl::changeNextSceneWithSafety(m_strNextSceneTag.c_str());
        }
    }
    
}

void CcbDailyQuestRewardFrameLayer::CreateData(uint32 dwIndex)
{
    m_dwIndex = dwIndex;
    
    m_pSpriteFinish->setVisible(false);
    m_pLabelTTFRewardNum->getParent()->setVisible(false);
    m_pControlButtonReward->setVisible(true);
    AchieveRewardConfig::STC_ACHIEVE_REWARD_CONFIG* pConfig = GET_CONFIG_STC(AchieveRewardConfig, dwIndex);
    if (pConfig)
    {
        if (getChildByTag(715)) {
            getChildByTag(715)->removeFromParent();
        }
        m_pControlButtonReward->setEnabled(true);
        ACHIEVE_REWARD_INFO showInfo = g_TaskData->GetAchieveInfoByIndex(dwIndex);
        if (showInfo.dwScore >= pConfig->dwParam[0])
        {
            m_pControlButtonReward->setTag(1);
           m_pControlButtonReward->setTitleForState(ccs(GET_STR(Str_Get)), 1 << 0);
            this->setSchedulerLabelState(ccGREEN);
            this->setRewardButtonStatus(1);
        }
        else
        {
            this->setRewardButtonStatus(0);
            m_pControlButtonReward->setTag(0);
            m_pControlButtonReward->setTitleForState(ccs(GET_STR(Str_Goto)), 1 << 0);
            this->setSchedulerLabelState(ccYELLOW);
        }
        this->setNextSeneTag(pConfig->strNextScene);
        m_nShowType = showInfo.dwType;
        
        
        m_pLabelTTFReward->setString(pConfig->strTitle.c_str());
        m_pLabelTTFName->setString(pConfig->strDesc.c_str());
        m_pLabelTTFScheduleValue->setString(CCString::createWithFormat("(%d/%d)",showInfo.dwScore,pConfig->dwParam[0])->getCString());
        CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetObjectIconByIndex(pConfig->dwRewardID[0]).c_str());
        if (pTexture)
        {
            m_pSpriteIcon->setTexture(pTexture);
        }
    }
    m_pSpriteFinish->setVisible(false);
}


void CcbDailyQuestRewardFrameLayer::setSchedulerLabelState(ccColor3B color)
{
    m_pLabelTTFSchedule->setColor(color);
    m_pLabelTTFScheduleValue->setColor(color);
}

void CcbDailyQuestRewardFrameLayer::setRewardButtonStatus(int status)
{
    m_byStatus = status;
}

void CcbDailyQuestRewardFrameLayer::updateRewardButtonStatus()
{
    CCNode* pParticleNode = NULL;
    pParticleNode = this->getChildByTag(101);
    switch (m_byStatus) {
        case E_GOT:
        case E_NONE:
        {
            if (pParticleNode) {
                pParticleNode->setVisible(false);
            }
            break;
        }
        case E_CANGET:
        {
            
            if (pParticleNode)
            {
                pParticleNode->removeAllChildren();
            }
            else
            {
                pParticleNode = CCNode::create();
                this->addChild(pParticleNode,3);
                pParticleNode->setTag(101);
                pParticleNode->setPosition(CCPointZero);
                m_vecPot.push_back(ccp(getLeft(m_pControlButtonReward),getBottom(m_pControlButtonReward)));
                m_vecPot.push_back(ccp(getLeft(m_pControlButtonReward),getTop(m_pControlButtonReward)));
                m_vecPot.push_back(ccp(getRight(m_pControlButtonReward),getTop(m_pControlButtonReward)));
                m_vecPot.push_back(ccp(getRight(m_pControlButtonReward),getBottom(m_pControlButtonReward)));
            }
            pParticleNode->setVisible(true);
            CCFlowFire *pFlowFire = CCFlowFire::createPolygon(m_vecPot);
            pParticleNode->addChild(pFlowFire);
            
            
            break;
        }
        default:
            break;
    }
}

