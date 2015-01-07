#include "CcbMJShopFindLayer.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "BackCtrl.h"
#include "FightAI.h"
#include "MusicCtrl.h"
#include "GameSession.h"
#include "ConfigGet.h"
#include "PetLoadingLayer.h"
#include "EventDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbMJShopFindLayer::~CcbMJShopFindLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonGo);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbMJShopFindLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbMJShopFindLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbMJShopFindLayer", CcbMJShopFindLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_MJShop.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbMJShopFindLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbMJShopFindLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    setTouchEnabled(true);
}

void CcbMJShopFindLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbMJShopFindLayer::onExit()
{
	CCLayer::onExit();
}

void CcbMJShopFindLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbMJShopFindLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGo", CCControlButton*, this->m_pControlButtonGo);

	return false;
}

bool CcbMJShopFindLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbMJShopFindLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbMJShopFindLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbMJShopFindLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGo", CcbMJShopFindLayer::onPressControlButtonGo);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbMJShopFindLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pControlButtonGo->setTouchPriority(kCCMenuHandlerPriority - 21);
}



void CcbMJShopFindLayer::onPressControlButtonGo(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    g_EventData->setMyShopType(E_MY_SHOP_MJ);
    CGameSession::SendReqMJShopList();
    CGameSession::SendReqMySteryShopList();
}

void CcbMJShopFindLayer::showMJShop()
{
    if(FightAI::Get()->getIsMJShopOpen())
    {
        CCNode* node = CcbManager::sharedManager()->LoadCcbMJShopFindLayer();
        if (node) {
            CCDirector::sharedDirector()->getRunningScene()->addChild(node, 998);
        }
    }
}

bool CcbMJShopFindLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCRect rect;
    CCPoint p = this->convertToWorldSpace(pTouch->getLocation());
    rect.origin = this->convertToWorldSpace(getOrigin(m_pControlButtonGo));
    rect.size = m_pControlButtonGo->getContentSize();
    if (rect.containsPoint(p)) {
        return false;
    }
    
    return true;
}

void CcbMJShopFindLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    removeFromParent();
}

void CcbMJShopFindLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 20, true);
}




