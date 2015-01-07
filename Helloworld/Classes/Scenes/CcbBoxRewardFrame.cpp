#include "CcbBoxRewardFrame.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "MailDataMgr.h"
#include "Instruments.h"
#include "MusicCtrl.h"
#include "Instruments.h"
#include "CcbSystemMailBoardLayer.h"

CcbBoxRewardFrame::~CcbBoxRewardFrame()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTitle);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFContent);
    CC_SAFE_RELEASE_NULL(m_pControlbuttonReward);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBoxRewardFrame( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBoxRewardFrame( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBoxRewardFrame", CcbBoxRewardFrameLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/box_reward_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbBoxRewardFrame::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBoxRewardFrame::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbBoxRewardFrame::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbBoxRewardFrame::onExit()
{
	CCLayer::onExit();
}

void CcbBoxRewardFrame::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBoxRewardFrame::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTitle", CCLabelTTF*, this->m_pLabelTTFTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFContent", CCLabelTTF*, this->m_pLabelTTFContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlbuttonReward", CCScrollButton*, this->m_pControlbuttonReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
    
	return false;
}

bool CcbBoxRewardFrame::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbBoxRewardFrame::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbBoxRewardFrame::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBoxRewardFrame::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReward", CcbBoxRewardFrame::onPressControlButtonReward);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbBoxRewardFrame::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_indexId = 0;
}

void CcbBoxRewardFrame::onPressControlButtonReward(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CcbSystemMailBoardLayer::showMail(m_indexId);
}

void CcbBoxRewardFrame::loadData(int wIndex)
{
    m_indexId = wIndex;
    MAIL_INFO tempInfo;
    VEC_MAIL_INFO tempList = CMailDataMgr::Get()->GetSysMailList();
    tempInfo = tempList[tempList.size()-wIndex-1];
    m_pLabelTTFTitle->setString(tempInfo.strTitle.c_str());

    CCString* str = getDayTimeFromInt(tempInfo.dwRecvTime);
    m_pLabelTTFTime->setString(str->getCString());
}

void CcbBoxRewardFrame::setClipRect(CCRect rect)
{
    m_pControlbuttonReward->setClipRect(rect);
}



