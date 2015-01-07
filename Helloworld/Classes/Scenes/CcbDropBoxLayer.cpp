#include "CcbDropBoxLayer.h"
//#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbDropBoxLayer::~CcbDropBoxLayer()
{
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    CC_SAFE_RELEASE_NULL(m_pSpriteBoxClose);
	CC_SAFE_RELEASE_NULL(m_pSpriteBoxOpen_1);
	CC_SAFE_RELEASE_NULL(m_pSpriteBoxOpen_2);
	CC_SAFE_RELEASE_NULL(m_pControlButtonOpen);
    CC_SAFE_RELEASE_NULL(m_pLayerFinger);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbDropBoxLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbDropBoxLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbDropBoxLayer", CcbDropBoxLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/box.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/
//void CcbDropBoxLayer::registerWithTouchDispatcher(void)
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 25, true);
//}

bool CcbDropBoxLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbDropBoxLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
}

void CcbDropBoxLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbDropBoxLayer::onExit()
{
	CCLayer::onExit();
}

void CcbDropBoxLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbDropBoxLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBoxClose", CCSprite*, this->m_pSpriteBoxClose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBoxOpen_1", CCSprite*, this->m_pSpriteBoxOpen_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBoxOpen_2", CCSprite*, this->m_pSpriteBoxOpen_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOpen", CCControlButton*, this->m_pControlButtonOpen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerFinger", CCLayer*, this->m_pLayerFinger);
	return false;
}

bool CcbDropBoxLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbDropBoxLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbDropBoxLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbDropBoxLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOpen", CcbDropBoxLayer::onPressControlButtonOpen);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbDropBoxLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonOpen->setTouchPriority(kCCMenuHandlerPriority - 26);
    m_pLayerFinger->setVisible(false);
}

void CcbDropBoxLayer::onPressControlButtonOpen(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    if (!isOpen) {
//        runOpen();
        if (m_delegate) {
            m_delegate->openBox(this);
        }
    }
}

void CcbDropBoxLayer::runDrop()
{
    float x = CCRANDOM_MINUS1_1();
    if (x < 0) {
        x = -1;
    }
    else
    {
        x = 1;
    }
    
    int w = 5 + CCRANDOM_MINUS1_1()*20;
    
    CCActionInterval *act =  CCSequence::create(
                                                CCSequence::create(
                                                                   CCEaseOut::create(CCMoveBy::create(0.2, ccp(w*x, 30)), 0.5),
                                                                   CCDelayTime::create(0.2),
                                                                   CCEaseIn::create(CCMoveBy::create(0.2, ccp(5*x, -30)),0.5),
                                                                   NULL),
                                                
                                                CCSequence::create(
                                                                   CCMoveBy::create(0.1, ccp(4*x+CCRANDOM_MINUS1_1(), 5)),
                                                                   CCMoveBy::create(0.2, ccp(2*x+CCRANDOM_0_1()*5*x, CCRANDOM_MINUS1_1()*10 + -10)),
                                                                   NULL),
                                                NULL);
    this->runAction(act);
    
    mAnimationManager->runAnimationsForSequenceNamed("drop_box");
}

void CcbDropBoxLayer::runOpen()
{
    isOpen = true;
    this->stopAllActions();
    m_pLayerFinger->setVisible(false);
    mAnimationManager->runAnimationsForSequenceNamed("open_box");
    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbDropBoxLayer::hideSalf));
}
void CcbDropBoxLayer::runCheck()
{
    if (isOpen) {
        return;
    }
    m_pLayerFinger->setVisible(true);
    mAnimationManager->runAnimationsForSequenceNamed("check_box");
    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbDropBoxLayer::runCheck));
}
void CcbDropBoxLayer::hideSalf()
{
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->removeFromParentAndCleanup(true);
}





