#include "CcbArenaShopFrameLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "ArenaDataMgr.h"
#include "PetCtrl.h"
#include "ResourceStringClient.h"
#include "ResourceStringConverter.h"
#include "ConfigGet.h"
#include "GameSession.h"
#include "Role.h"
#include "PetLoadingLayer.h"
#include "GuideData.h"
#include "UISupport.h"
#include "MusicCtrl.h"

CcbArenaShopFrameLayer::~CcbArenaShopFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDesc);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFExchangeCount);
	CC_SAFE_RELEASE_NULL(m_pControlButtonExchange);
    CC_SAFE_RELEASE_NULL(m_pControlButtonExchange1);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaShopFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaShopFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaShopFrameLayer", CcbArenaShopFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_shop_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaShopFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
//    setTouchEnabled(true);
	return true;
}

void CcbArenaShopFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbArenaShopFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaShopFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbArenaShopFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaShopFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDesc", CCLabelTTF*, this->m_pLabelTTFDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFExchangeCount", CCLabelTTF*, this->m_pLabelTTFExchangeCount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExchange", CCScrollButton*, this->m_pControlButtonExchange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExchange1", CCScrollButton*, this->m_pControlButtonExchange1);
    
	return false;
}

bool CcbArenaShopFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaShopFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaShopFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaShopFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExchange", CcbArenaShopFrameLayer::onPressControlButtonExchange);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaShopFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbArenaShopFrameLayer::onPressControlButtonExchange(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	// TODO:
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    ARENA_SHOP_INFO tempInfo = CArenaDataMgr::Get()->GetShopList()[m_dwIndex];
    CGameSession::SendArenaShopExchange(tempInfo.dwGoodsId);
}

void CcbArenaShopFrameLayer::loadData(uint32 index)
{
    m_dwIndex = index;
    
    ARENA_SHOP_INFO tempInfo = CArenaDataMgr::Get()->GetShopList()[m_dwIndex];
    CCString* str = CCString::create("");
    //名字}
    m_pLabelTTFName->setString(tempInfo.strName.c_str());
    //icon
    m_pLayerIcon->loadIndexData(tempInfo.dwBuyContentId);
    m_pLayerIcon->showIconOnly();
//    m_pLayerIcon->setBtnEnable(false);
    //说明}
    str->initWithFormat(GET_STR(Str_reputation_can_exchange), tempInfo.dwCostReputition);
    m_pLabelTTFDesc->setString(str->getCString());
    //次数}
    int cnt = tempInfo.dwLimitCnt - tempInfo.dwExchangeCnt;
    if (cnt <= 0) {
        cnt = 0;
        m_pControlButtonExchange->setEnabled(false);
    }
    else{
        m_pControlButtonExchange->setEnabled(true);
    }
    str->initWithFormat("%d", cnt);
    m_pLabelTTFExchangeCount->setString(str->getCString());
    
}

void CcbArenaShopFrameLayer::setClipRect(CCRect rect)
{
    m_pControlButtonExchange->setClipRect(rect);
    m_pControlButtonExchange1->setClipRect(rect);
}
