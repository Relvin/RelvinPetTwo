#include "CcbActivityTipLayer.h"
//#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbActivityTipLayer::~CcbActivityTipLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbActivityTipLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbActivityTipLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbActivityTipLayer", CcbActivityTipLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/activity_tip.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbActivityTipLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbActivityTipLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
//    this->setScale(0.1);
//    this->runAction(CCSequence::create(CCScaleTo::create(0.2, 1.2),
//                                       CCScaleTo::create(0.1, 0.9),
//                                       CCScaleTo::create(0.1, 1.0),
//                                       NULL));
}

void CcbActivityTipLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbActivityTipLayer::onExit()
{
	CCLayer::onExit();
}

void CcbActivityTipLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbActivityTipLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);

	return false;
}

bool CcbActivityTipLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbActivityTipLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbActivityTipLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbActivityTipLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbActivityTipLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbActivityTipLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
}



void CcbActivityTipLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    removeFromParentAndCleanup(true);
}

void CcbActivityTipLayer::loadData(std::string time)
{
    m_pLabelTTFTime->setString(time.c_str());
}

bool CcbActivityTipLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void CcbActivityTipLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*2, true);
}



