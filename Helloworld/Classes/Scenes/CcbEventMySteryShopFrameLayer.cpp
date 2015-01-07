#include "CcbEventMySteryShopFrameLayer.h"
//#include "CcbManager.h"
#include "PetCtrl.h"
#include "ConfigGet.h"
#include "ItemDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "EnumDefines.h"
#include "SystemMessage.h"
#include "CcbItemInfoButtonLayer.h"
#include "PacketDataMgr.h"
#include "ResourceStringClient.h"
#include "CCScrollButton.h"
#include "MusicCtrl.h"
#include "Role.h"
#include "CcbJumpTipLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbEventMySteryShopFrameLayer::~CcbEventMySteryShopFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pControlButtonExchange);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFExchange);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFExchangeCount);
    CC_SAFE_RELEASE_NULL(m_pSpriteCostType);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventMySteryShopFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventMySteryShopFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventMySteryShopFrameLayer", CcbEventMySteryShopFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_mysteryshop_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventMySteryShopFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
//    setTouchEnabled(true);
	return true;
}

void CcbEventMySteryShopFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEventMySteryShopFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEventMySteryShopFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEventMySteryShopFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventMySteryShopFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExchange", CCScrollButton*, this->m_pControlButtonExchange);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFExchange", CCLabelTTF*, this->m_pLabelTTFExchange);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFExchangeCount", CCLabelTTF*, this->m_pLabelTTFExchangeCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCostType", CCSprite*, this->m_pSpriteCostType);
	return false;
}

bool CcbEventMySteryShopFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEventMySteryShopFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventMySteryShopFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventMySteryShopFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExchange", CcbEventMySteryShopFrameLayer::onPressControlButtonExchange);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventMySteryShopFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}



void CcbEventMySteryShopFrameLayer::onPressControlButtonExchange(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    if(m_stcGoods.byType == E_MY_SHOP_MJ)
    {
        CRole* role = CGameSession::GetRole();
        if (role->GetdwDollar() < m_stcGoods.dwCostCnt) {
            CShowJumpTip::Get()->Show(E_DOLLAR_NOT_ENOUGH);
            return;
        }
        CGameSession::SendMJShopBuy(m_stcGoods.dwGoodsId);
    }
    else{
        CGameSession::SendMySteryShopBy(m_stcGoods.dwGoodsId);
    }
    PetLoadingLayer::sharedLayer()->WaitForPacket();
}

void CcbEventMySteryShopFrameLayer::loadData(STC_STERY_GOODS stcGoods)
{
    m_stcGoods = stcGoods;
    
    //icon
    m_pLayerIcon->loadIndexData(m_stcGoods.dwBuyContentId);
    m_pLayerIcon->showIconOnly();
    m_pLayerIcon->showStarLv();
    m_pLayerIcon->showCnt( m_stcGoods.dwBuyCount);
    //名}
    CCString* str = CCString::createWithFormat("%s",m_stcGoods.strName.c_str());
    m_pLabelTTFName->setString(str->getCString());
    //描述}
    str->initWithFormat("%d", stcGoods.dwCostCnt);
    m_pLabelTTFExchange->setString(str->getCString());
    
    //花费的物品icon
    std::string iconP = g_PacketDataMgr->GetItemIconByIndex(m_stcGoods.dwCostItemId);
    CCTexture2D* t2d = CCTextureCache::sharedTextureCache()->addImage(iconP.c_str());
    if (t2d) {
        m_pSpriteCostType->setTexture(t2d);
    }
    
    //兑换次数}
    m_pControlButtonExchange->setEnabled(true);
    if (m_stcGoods.dwLimitCnt == 0) {
        m_pLabelTTFExchangeCount->setVisible(false);
    }
    else
    {
        int cnt = m_stcGoods.dwLimitCnt - m_stcGoods.dwBuyCnt;
        cnt = MAX(cnt, 0);
//        m_pLabelTTFExchangeCount->setVisible(true);
        str->initWithFormat("%s%d", GET_STR(Str_exchange_cnt), cnt);
        m_pLabelTTFExchangeCount->setString(str->getCString());
        
        if (cnt == 0) {
            m_pControlButtonExchange->setEnabled(false);
        }
    }
}

void CcbEventMySteryShopFrameLayer::setClipRect(CCRect rect)
{
    m_pLayerIcon->setClipRect(rect);
    m_pControlButtonExchange->setClipRect(rect);
}
