#include "CcbBegin22Layer.h"
#include "CcbManager.h"
#include "AnalysicsManager.h"
#include "CcbChoosePetLayer.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

#include "GuideData.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SCENE_NAME "Begin22Scene"

CcbBegin22Layer::~CcbBegin22Layer()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBegin22Layer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBegin22Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBegin22Layer", CcbBegin22LayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_2_2.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CCScene* CcbBegin22Layer::scene() {
    CCScene* pScene = CCScene::create();
    CcbBegin22Layer* pLayer = dynamic_cast<CcbBegin22Layer*>(CcbManager::sharedManager()->LoadCcbBegin22Layer(NULL));
    pScene->addChild(pLayer);
    
    return pScene;
}

bool CcbBegin22Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBegin22Layer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    AnalysicsManager::sharedAnalyticsMgr()->SendBeginPageView(SCENE_NAME);
}

void CcbBegin22Layer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(6.5f),
                                       CCCallFunc::create(this, callfunc_selector(CcbBegin22Layer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbBegin22Layer::addGuideLayer() {
    CGameSession::GetRole()->SetwGuideTrigger(GuideData::E_GUIDE_TRIGGER_WAKE_1_TALK);
    GuideData::GetInstance()->addGuideLayer();
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("begin3_over");
#endif
}

//void CcbBegin22Layer::delayTouchEnable()
//{
//    setTouchEnabled(true);
//}

//void CcbBegin22Layer::replaceNextScene() {
//    CCScene* nextScene = CreateNameScene::scene();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5f, nextScene));
//}

void CcbBegin22Layer::onExit()
{
	CCLayer::onExit();
    AnalysicsManager::sharedAnalyticsMgr()->SendEngPageView(SCENE_NAME);
}

void CcbBegin22Layer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBegin22Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

	return false;
}

bool CcbBegin22Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbBegin22Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbBegin22Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBegin22Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbBegin22Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}








