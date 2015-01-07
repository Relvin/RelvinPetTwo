#include "CcbBegin200Layer.h"
#include "CcbManager.h"
#include "CcbBegin21Layer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbBegin200Layer::~CcbBegin200Layer()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBegin200Layer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBegin200Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBegin200Layer", CcbBegin200LayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_2_0.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


CCScene* CcbBegin200Layer::scene() {
    CCScene* pScene = CCScene::create();
    CcbBegin200Layer* pLayer = dynamic_cast<CcbBegin200Layer*>(CcbManager::sharedManager()->LoadCcbBegin200Layer(NULL));
    pScene->addChild(pLayer);
    
    return pScene;
}


bool CcbBegin200Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBegin200Layer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbBegin200Layer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(1.0f),
                                       CCCallFunc::create(this, callfunc_selector(CcbBegin200Layer::delayTouchEnable)),
                                       NULL
                                       )
                    );
}

void CcbBegin200Layer::delayTouchEnable() {
    CCScene* nextScene = CcbBegin21Layer::scene();
    CCDirector::sharedDirector()->replaceScene(nextScene);
}

void CcbBegin200Layer::onExit()
{
	CCLayer::onExit();
}

void CcbBegin200Layer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBegin200Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

	return false;
}

bool CcbBegin200Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbBegin200Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbBegin200Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBegin200Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbBegin200Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
}









