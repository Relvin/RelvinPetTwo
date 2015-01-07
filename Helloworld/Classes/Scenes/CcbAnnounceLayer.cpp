#include "CcbAnnounceLayer.h"
//#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbAnnounceLayer::~CcbAnnounceLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerScrolText);
	CC_SAFE_RELEASE_NULL(m_pControlButtonOk);

}

//-- copy this to CcbManager 
/*
//CcbManager.h


//CcbManager.cpp

*/


bool CcbAnnounceLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbAnnounceLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbAnnounceLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbAnnounceLayer::onExit()
{
	CCLayer::onExit();
}

void CcbAnnounceLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbAnnounceLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerScrolText", CCLayer*, this->m_pLayerScrolText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOk", CCControlButton*, this->m_pControlButtonOk);

	return false;
}

bool CcbAnnounceLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbAnnounceLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbAnnounceLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbAnnounceLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOk", CcbAnnounceLayer::onPressControlButtonOk);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbAnnounceLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CCSize viewSize = m_pLayerScrolText->getContentSize();
    CCPoint scrollPos = m_pLayerScrolText->getPosition();
    
    CCScrollView* pScroll = CCScrollView::create(viewSize);
    pScroll->setPosition(scrollPos);
    pScroll->setDirection(kCCScrollViewDirectionVertical);
    
    addChild(pScroll);
}

void CcbAnnounceLayer::onPressControlButtonOk(CCObject* pSender, CCControlEvent event)
{
    removeFromParentAndCleanup(true);
}







