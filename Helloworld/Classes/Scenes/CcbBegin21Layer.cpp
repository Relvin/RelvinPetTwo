#include "CcbBegin21Layer.h"
#include "CcbManager.h"
#include "CcbBegin22Layer.h"
#include "AnalysicsManager.h"
#include "GuideData.h"
#include "PetLoadingLayer.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

USING_NS_CC;
USING_NS_CC_EXT;

#define SCENE_NAME "Begin21Scene"

CcbBegin21Layer::~CcbBegin21Layer()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBegin21Layer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBegin21Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBegin21Layer", CcbBegin21LayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_2_1.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CCScene* CcbBegin21Layer::scene() {
    CCScene* pScene = CCScene::create();
    CcbBegin21Layer* pLayer = dynamic_cast<CcbBegin21Layer*>(CcbManager::sharedManager()->LoadCcbBegin21Layer(NULL));
    pScene->addChild(pLayer);
    
    return pScene;
}

bool CcbBegin21Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBegin21Layer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    AnalysicsManager::sharedAnalyticsMgr()->SendBeginPageView(SCENE_NAME);
}

void CcbBegin21Layer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
//    this->runAction(
//                    CCSequence::create(
//                                       CCDelayTime::create(13.0f),
//                                       CCCallFunc::create(this, callfunc_selector(CcbBegin21Layer::replaceNextScene)),
//                                       NULL
//                                       )
//                    );
}

//void CcbBegin21Layer::delayTouchEnable()
//{
//    setTouchEnabled(true);
//}

//void CcbBegin21Layer::replaceNextScene() {
////    CCScene* nextScene = CcbBegin22Layer::scene();
////    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f, nextScene));
//
//    GuideData* pData = GuideData::GetInstance();
//    pData->setStepId(GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_1);
//    pData->connectToServer();       // 发送后服务器返回战斗包}
//    
//#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
//    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("begin2_over");
//#endif
//}

void CcbBegin21Layer::onExit()
{
	CCLayer::onExit();
    AnalysicsManager::sharedAnalyticsMgr()->SendEngPageView(SCENE_NAME);
}

void CcbBegin21Layer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBegin21Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

	return false;
}

bool CcbBegin21Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbBegin21Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
//    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "playCilaCila", CcbBegin21Layer::playCilaCila);
//    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "insertQiuQiu", CcbBegin21Layer::insertQiuQiu);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onSend200", CcbBegin21Layer::onSend200);
	return NULL;
}

SEL_MenuHandler CcbBegin21Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBegin21Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbBegin21Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

#pragma mark CallFunc

//void CcbBegin21Layer::insertQiuQiu(cocos2d::CCNode *pNode) {
//	CCLabelTTF* pQiuQiu = CCLabelTTF::create("这时候小智的背景QiuQiu的变了....}", "Arial", 20);
//    pQiuQiu->setColor(ccBLUE);
//    pQiuQiu->setAnchorPoint(ccp(1, 0.5));
//    pQiuQiu->setPosition(ccp(-50, 440));
//	CCLabelTTF* pLast = CCLabelTTF::create("...一直持续。。}", "Helvetica-Bold", 24);
//    pLast->setColor(ccGREEN);
//    pLast->setAnchorPoint(ccp(1, 0.5));
//    pLast->setPosition(ccp(-50, 400));
//	CCLabelTTF* pEnd = CCLabelTTF::create("很久。。很久}", "Helvetica", 18);
//    pEnd->setColor(ccGRAY);
//    pEnd->setAnchorPoint(ccp(1, 0.5));
//    pEnd->setPosition(ccp(-50, 380));
//    
//    this->addChild(pQiuQiu);
//    this->addChild(pLast);
//    this->addChild(pEnd);
//    
//    pQiuQiu->runAction(
//                       CCMoveBy::create(1.2f, ccp(700, 0))
//                       );
//    pLast->runAction(
//                     CCSequence::create(
//                                        CCDelayTime::create(0.5f),
//                                        CCMoveBy::create(1.0f, ccp(700, 0)),
//                                        NULL
//                                        )
//                     );
//    pEnd->runAction(
//                    CCSequence::create(
//                                       CCDelayTime::create(0.9f),
//                                       CCMoveBy::create(1.2f, ccp(700, 0)),
//                                       NULL
//                                       )
//                    );
//}
//
//void CcbBegin21Layer::playCilaCila(cocos2d::CCNode *pNode) {
//	CCLabelTTF* pCila = CCLabelTTF::create("{卧槽，猪脚的蛋蛋发光了，碎裂的光闪瞎你的钛金狗眼}", "Arial", 30, CCSizeMake(200, 0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
//    pCila->setColor(ccYELLOW);
//    pCila->setPosition(ccp(250, 400));
//    
//	CCLabelTTF* pEnd = CCLabelTTF::create("{可以持续很久。。很久}", "Helvetica", 18);
//    pEnd->setColor(ccGRAY);
//    pEnd->setAnchorPoint(ccp(0, 0.5));
//    pEnd->setPosition(ccp(370, 380));
//    
//    addChild(pCila);
//    addChild(pEnd);
//    
//    pCila->runAction(CCBlink::create(3.0f, 90));
//    
//    pEnd->runAction(
//                    CCSequence::create(
//                                       CCDelayTime::create(0.5f),
//                                       CCMoveBy::create(1.0f, ccp(-450, 0)),
//                                       NULL
//                                       )
//                    );
//}


void CcbBegin21Layer::onSend200(cocos2d::CCNode *pNode) {
    GuideData* pData = GuideData::GetInstance();
    pData->setStepId(GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_1);
    pData->connectToServer();       // 发送后服务器返回战斗包}
    
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("begin2_over");
#endif
}


