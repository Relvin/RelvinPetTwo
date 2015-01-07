#include "CcbAchieveRewardFrameLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "ConfigGet.h"
#include "TaskDataMgr.h"
#include "PacketDataMgr.h"
#include "PetLoadingLayer.h"
#include "ResourcePic.h"
#include "UISupport.h"

CcbAchieveRewardFrameLayer::~CcbAchieveRewardFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReward);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFReward);
    CC_SAFE_RELEASE_NULL(m_pSpriteFinish);
}

bool CcbAchieveRewardFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbAchieveRewardFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbAchieveRewardFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbAchieveRewardFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbAchieveRewardFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbAchieveRewardFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReward", CCControlButton*, this->m_pControlButtonReward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFReward", CCLabelTTF*, this->m_pLabelTTFReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFinish", CCSprite*, this->m_pSpriteFinish);
    
	return false;
}

bool CcbAchieveRewardFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbAchieveRewardFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbAchieveRewardFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbAchieveRewardFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReward", CcbAchieveRewardFrameLayer::onPressControlButtonReward);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbAchieveRewardFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbAchieveRewardFrameLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool CcbAchieveRewardFrameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_StartTouchPos = CCPoint(0, 0);
    m_StartTouchPos = pTouch->getLocation();
    return true;
}

void CcbAchieveRewardFrameLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_EndTouchPos = CCPoint(0, 0);
    m_EndTouchPos = pTouch->getLocation();
}

void CcbAchieveRewardFrameLayer::onPressControlButtonReward(CCObject* pSender, CCControlEvent event)
{
    if( fabs(m_StartTouchPos.x - m_EndTouchPos.x) > 20 || fabs(m_StartTouchPos.y - m_EndTouchPos.y) > 10)
    {
        return;
    }
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendAchieveRewardRequest(m_nShowType, m_dwIndex);
}

void CcbAchieveRewardFrameLayer::CreateData(uint32 dwIndex)
{
    AchieveRewardConfig::STC_ACHIEVE_REWARD_CONFIG* pConfig = GET_CONFIG_STC(AchieveRewardConfig, dwIndex);
    if (pConfig)
    {
        if (getChildByTag(715)) {
            getChildByTag(715)->removeFromParent();
        }
        ACHIEVE_REWARD_INFO showInfo = g_TaskData->GetAchieveInfoByIndex(dwIndex);
        if (showInfo.dwScore >= pConfig->dwParam[0])
        {
            m_pControlButtonReward->setEnabled(true);
            CCSprite* pTips = CCSprite::create(GET_PIC(Pic_red_tip));
            pTips->setAnchorPoint(ccp(1.0f, 1.0f));
            pTips->setPosition(ccp(getRight(m_pControlButtonReward), getTop(m_pControlButtonReward)));
            addChild(pTips, 10, 715);
        }
        else
        {
            m_pControlButtonReward->setEnabled(false);
        }
        m_nShowType = showInfo.dwType;
        m_dwIndex = dwIndex;
        
        m_pLabelTTFName->setString(pConfig->strTitle.c_str());
        m_pLabelTTFReward->setString(PARSE_STRING1(pConfig->strDesc.c_str(), showInfo.dwScore));
        CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetObjectIconByIndex(pConfig->dwRewardID[0]).c_str());
        if (pTexture)
        {
            m_pSpriteIcon->setTexture(pTexture);
        }
    }
    m_pSpriteFinish->setVisible(false);
}
