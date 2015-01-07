#include "CcbBegin1Layer.h"
#include "CcbManager.h"
#include "CCExTransition.h"
#include "CcbBegin20Layer.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

#include "ResourceMusic.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

#include "GuideData.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SCENE_NAME "Begin10Scene"

CcbBegin1Layer::~CcbBegin1Layer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonSkip);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBegin1Layer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBegin1Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBegin1Layer", CcbBegin1LayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_01.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


CCScene* CcbBegin1Layer::scene() {
    CCScene* pScene = CCScene::create();
    CcbBegin1Layer* pLayer = dynamic_cast<CcbBegin1Layer*>(CcbManager::sharedManager()->LoadCcbBegin1Layer(NULL));
    pScene->addChild(pLayer);
    
    return pScene;
}

bool CcbBegin1Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBegin1Layer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CMusicCtrl::StopBackgroundMusic();
    CMusicCtrl::PlayEffect(GET_MUSIC(Bgm_new_begin));
    
    AnalysicsManager::sharedAnalyticsMgr()->SendBeginPageView(SCENE_NAME);
}

void CcbBegin1Layer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(3.0f),
                                       CCCallFunc::create(this, callfunc_selector(CcbBegin1Layer::delayTouchEnable)),
                                       NULL
                                       )
                    );
}

void CcbBegin1Layer::delayTouchEnable()
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("begin1_over");
#endif
    
    CCScene* nextScene = CcbBegin20Layer::scene();
    CCDirector::sharedDirector()->replaceScene(nextScene);
}

void CcbBegin1Layer::onExit()
{
	CCLayer::onExit();
    AnalysicsManager::sharedAnalyticsMgr()->SendEngPageView(SCENE_NAME);
}

void CcbBegin1Layer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBegin1Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSkip", CCControlButton*, this->m_pControlButtonSkip);
	return false;
}

bool CcbBegin1Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbBegin1Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbBegin1Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBegin1Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSkip", CcbBegin1Layer::onPressControlButtonSkip);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbBegin1Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
#ifdef NDEBUG
    m_pControlButtonSkip->setVisible(false);
#endif
}

#pragma mark TouchDelegate
void CcbBegin1Layer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool CcbBegin1Layer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("begin1_over");
#endif
    
    CCScene* nextScene = CcbBegin20Layer::scene();
    CCDirector::sharedDirector()->replaceScene(nextScene);
    setTouchEnabled(false);
    return true;
}


void CcbBegin1Layer::onPressControlButtonSkip(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    m_pControlButtonSkip->setEnabled(false);
    
    GuideData* pData = GuideData::GetInstance();
    pData->setStepId(GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_1);
    pData->connectToServer();       // 发送后服务器返回战斗包}
}




