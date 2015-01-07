#include "CcbMapPointJumpLayer.h"
//#include "CcbManager.h"
#include "StageScene.h"
#include "MapScene.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "ResourceMusic.h"
#include "PetLoadingLayer.h"
#include "GameSession.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbMapPointJumpLayer::~CcbMapPointJumpLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerColor);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFContent);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGoto1);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGoto2);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbMapPointJumpLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbMapPointJumpLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbMapPointJumpLayer", CcbMapPointJumpLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/jump.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbMapPointJumpLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbMapPointJumpLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    setTouchEnabled(true);
}

void CcbMapPointJumpLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbMapPointJumpLayer::onExit()
{
	CCLayer::onExit();
}

void CcbMapPointJumpLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbMapPointJumpLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerColor", CCLayer*, this->m_pLayerColor);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFContent", CCLabelTTF*, this->m_pLabelTTFContent);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGoto1", CCControlButton*, this->m_pControlButtonGoto1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGoto2", CCControlButton*, this->m_pControlButtonGoto2);

	return false;
}

bool CcbMapPointJumpLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbMapPointJumpLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbMapPointJumpLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbMapPointJumpLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbMapPointJumpLayer::onPressControlButtonCancel);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGoto1", CcbMapPointJumpLayer::onPressControlButtonGoto1);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGoto2", CcbMapPointJumpLayer::onPressControlButtonGoto2);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbMapPointJumpLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pControlButtonCancel->setTouchPriority(kCCMenuHandlerPriority * 2 - 1);
    m_pControlButtonGoto1->setTouchPriority(kCCMenuHandlerPriority * 2 - 1);
    m_pControlButtonGoto2->setTouchPriority(kCCMenuHandlerPriority * 2 - 1);
}



void CcbMapPointJumpLayer::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    removeFromParent();
}

void CcbMapPointJumpLayer::onPressControlButtonGoto1(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
	removeFromParent();
}

void CcbMapPointJumpLayer::onPressControlButtonGoto2(CCObject* pSender, CCControlEvent event)
{
	CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    StageCtrl::Get()->setKind(StageCtrl::Get()->kind());
    
    if (MapCtrl::nSelectedMapId < 22) {
        MapCtrl::nSelectedMapId++;
    }
    
    MapConfig::STC_MAP_CONFIG* pMapConfig = GET_CONFIG_STC(MapConfig, MapCtrl::nSelectedMapId);
    if (pMapConfig) {
        StageCtrl::Get()->setCurMapPointName(pMapConfig->strName);
        StageCtrl::Get()->setFromJump(false);
        CGameSession::SendReqStageInfo(StageCtrl::Get()->kind(), MapCtrl::nSelectedMapId);
    }
}

#pragma mark -- Touch Delegate --
void CcbMapPointJumpLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority * 2, true);
}

bool CcbMapPointJumpLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    return true;
}


