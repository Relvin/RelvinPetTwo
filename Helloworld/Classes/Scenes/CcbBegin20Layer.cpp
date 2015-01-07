#include "CcbBegin20Layer.h"
#include "CcbManager.h"
#include "AnalysicsManager.h"
#include "CcbBegin200Layer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SCENE_NAME "Begin20Scene"

CcbBegin20Layer::~CcbBegin20Layer()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBegin20Layer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBegin20Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBegin20Layer", CcbBegin20LayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_2.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CCScene* CcbBegin20Layer::scene() {
    CCScene* pScene = CCScene::create();
    CcbBegin20Layer* pLayer = dynamic_cast<CcbBegin20Layer*>(CcbManager::sharedManager()->LoadCcbBegin20Layer(NULL));
    pScene->addChild(pLayer);
    
    return pScene;
}

bool CcbBegin20Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBegin20Layer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    AnalysicsManager::sharedAnalyticsMgr()->SendBeginPageView(SCENE_NAME);
}

void CcbBegin20Layer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(6.5f),
                                       CCCallFunc::create(this, callfunc_selector(CcbBegin20Layer::delayTouchEnable)),
                                       NULL
                                       )
                    );
}

void CcbBegin20Layer::delayTouchEnable()
{
//    setTouchEnabled(true);
    CCScene* nextScene = CcbBegin200Layer::scene();
    CCDirector::sharedDirector()->replaceScene(nextScene);
}

void CcbBegin20Layer::onExit()
{
	CCLayer::onExit();
    AnalysicsManager::sharedAnalyticsMgr()->SendEngPageView(SCENE_NAME);
}

void CcbBegin20Layer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBegin20Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

	return false;
}

bool CcbBegin20Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbBegin20Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbBegin20Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBegin20Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbBegin20Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}


#pragma mark TouchDelegate
void CcbBegin20Layer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool CcbBegin20Layer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
    CCScene* nextScene = CcbBegin200Layer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, nextScene));
    setTouchEnabled(false);
    return true;
}






