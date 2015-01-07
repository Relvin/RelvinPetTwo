#include "CcbShopItemFrameLayer.h"
#include "CcbManager.h"
#include "ShopDataMgr.h"
#include "GameSession.h"
#include "CcbShopSelectNumLayer.h"
#include "FlyTextLayer.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"
#include "ResourcePic.h"
#include "CcbItemInfoLayer.h"
#include "CcbShopGiftView.h"
#include "CcbJumpTipLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbShopItemFrameLayer::~CcbShopItemFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonBuy);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFText);
	CC_SAFE_RELEASE_NULL(m_pSpriteState);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCanBuyCnt);
    CC_SAFE_RELEASE_NULL(m_pNodeName1);
    CC_SAFE_RELEASE_NULL(m_pNodeName2);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbShopItemFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbShopItemFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbShopItemFrameLayer", CcbShopItemFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbShopItemFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbShopItemFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbShopItemFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbShopItemFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbShopItemFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbShopItemFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBuy", CCScrollButton*, this->m_pControlButtonBuy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText", CCLabelTTF*, this->m_pLabelTTFText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteState", CCSprite*, this->m_pSpriteState);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCanBuyCnt", CCLabelTTF*, this->m_pLabelTTFCanBuyCnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeName1", CCNode *, this->m_pNodeName1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeName2", CCNode*, this->m_pNodeName2);
	return false;
}

bool CcbShopItemFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbShopItemFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbShopItemFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbShopItemFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBuy", CcbShopItemFrameLayer::onPressControlButtonBuy);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbShopItemFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbShopItemFrameLayer::onPressControlButtonBuy(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (g_ShopData->GetCurShopShowType() == E_SHOP_TYPE_RECHARGE ) //购买钻石}
    {
        
    }
    else//购买普通物品}
    {
        g_ShopData->SetCurChosenGoodsId(m_showInfo.dwGoodsId);
        g_ShopData->SetCurBuyContentId(m_showInfo.dwBuyContentId);
        g_ShopData->SetCurGoodsCostCount(m_showInfo.dwCostCount);
        
        //vip礼包只能买一个
        if (m_showInfo.byShopType == E_SHOP_TYPE_REDUCED) {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendShopBuyItem(g_ShopData->GetCurChosenGoodsId(), 1);
            return;
        }
        
        CcbShopSelectNumLayer* pLayer = (CcbShopSelectNumLayer*)CcbManager::sharedManager()->LoadCcbShopSelecNumLayer();
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        pLayer->ignoreAnchorPointForPosition(false);
        pLayer->setAnchorPoint(ccp(0.5, 0.5));
        pLayer->setPosition(ccp(winSize.width*0.5 , winSize.height *0.5));
        pLayer->setMaxCnt(m_showInfo.dwMaxCnt - m_showInfo.dwBuyCnt);
        CCDirector::sharedDirector()->getRunningScene()->addChild(pLayer, 999);
    }

}

void CcbShopItemFrameLayer::loadData(SHOP_ITEM_INFO showInfo)
{
    m_showInfo = showInfo;
    CCString* str = CCString::create("");
    //名字}
    if (m_showInfo.dwBuyCount > 1)
    {
        str->initWithFormat("%s*%d", m_showInfo.strName.c_str(), m_showInfo.dwBuyCount);
    }
    else
    {
        str->initWithFormat("%s", m_showInfo.strName.c_str());
    }
    m_pLabelTTFName->setString(str->getCString());
    m_pLabelTTFCanBuyCnt->setPositionX(getRight(m_pLabelTTFName));
    //icon
    m_pLayerIcon->loadIndexData(m_showInfo.dwBuyContentId);
    m_pLayerIcon->showIconOnly();
    
    //描述}
    m_pLabelTTFText->setString(m_showInfo.strDescription.c_str());
    
    

    CCNode *pNodeName[2];
    pNodeName[0] = m_pNodeName1;
    pNodeName[1] = m_pNodeName2;
    
    CCLabelTTF* pLabelPriceName[2] ;
    CCLabelTTF* pLabelPrice[2] ;
    CCSprite* pSpritePriceIcon[2];
    for (int i = 0; i < 2; i++) {
        pLabelPriceName[i] = (CCLabelTTF*)pNodeName[i]->getChildByTag(0);
        pSpritePriceIcon[i] = (CCSprite*)pNodeName[i]->getChildByTag(1);
        pLabelPrice[i] = (CCLabelTTF*)pNodeName[i]->getChildByTag(2);
        
    }
    
    CCTexture2D *texture2D = NULL ;
    std::string picPath = "";
    if (m_showInfo.dwCostContentId == E_UNITE_ID_COIN) {
        picPath = GET_PIC(Pic_Money);
    }
    else
    {
        picPath = GET_PIC(Pic_Diamond);
    }
    for (int i = 0; i < 2; i++) {
        texture2D = CCTextureCache::sharedTextureCache()->addImage(picPath.c_str());
        pSpritePriceIcon[i]->setTexture(texture2D);
    }
    
    
    //打折花费}
    str->initWithFormat("%d", m_showInfo.dwCostDiscount);
    pLabelPrice[0]->setString(str->getCString());
    
    //花费}
    str->initWithFormat("%d", m_showInfo.dwCostCount);
    pLabelPrice[1]->setString(str->getCString());
    
    //出售状态}
    if (m_showInfo.byStatus == 1)//1、在售}
    {
        m_pSpriteState->setVisible(false);
    }
    
    //剩余购买次数}
    m_pControlButtonBuy->setEnabled(true);
    if (m_showInfo.dwMaxCnt >= m_showInfo.dwBuyCnt)
    {
        //设置按钮}
        if (m_showInfo.dwMaxCnt <= m_showInfo.dwBuyCnt)
        {
            m_pControlButtonBuy->setEnabled(false);
        }
        else
        {
            m_pControlButtonBuy->setEnabled(true);
        }
        
        //购买次数显示}
        if (m_showInfo.byShopType == E_SHOP_TYPE_REDUCED)
        {
            m_pLabelTTFCanBuyCnt->setVisible(false);
            m_pLayerIcon->setDelegate(this);
            
        }
        else
        {
            m_pLayerIcon->setDelegate(NULL);
            str->initWithFormat(GET_STR(Str_shengyujici), m_showInfo.dwMaxCnt - m_showInfo.dwBuyCnt);
            m_pLabelTTFCanBuyCnt->setVisible(true);
            m_pLabelTTFCanBuyCnt->setString(str->getCString());
        }
        
        if (m_showInfo.dwCostDiscount < m_showInfo.dwCostCount) {
            pNodeName[0]->setVisible(true);
            pNodeName[1]->getChildByTag(3)->setVisible(true);
            pLabelPriceName[1]->setString(GET_STR(Str_Shop_Old_Price));
        }
        else
        {
            pNodeName[0]->setVisible(false);
            pNodeName[1]->getChildByTag(3)->setVisible(false);
            pLabelPriceName[1]->setString(GET_STR(Str_Shop_Now_Price));
        }
    }
    else
    {
        CCLOG("Server Error.");
    }
    
    if (CShowJumpTip::Get()->getJumpType() == E_ITEM_NOT_ENOUGH) {
        uint32 itemId = CShowJumpTip::Get()->getNeedItemId();
        if (!itemId) {
            return;
        }
        if (itemId == showInfo.dwBuyContentId) {
            CCNode* pEffectNode = CcbManager::sharedManager()->LoadCcbStageEffLayer();
            pEffectNode->setPosition(this->getContentSize() * 0.5);
            pEffectNode->ignoreAnchorPointForPosition(false);
            pEffectNode->setAnchorPoint(ccp(0.5, 0.5));
            
            pEffectNode->setScaleX((this->getContentSize().width) / pEffectNode->getContentSize().width);
            pEffectNode->setScaleY((this->getContentSize().height) / pEffectNode->getContentSize().height);
            this->addChild(pEffectNode, 60, 111);
        } else if (getChildByTag(111)) {
            getChildByTag(111)->removeFromParent();
        }
    }
}

void CcbShopItemFrameLayer::setClipRect(CCRect rect)
{
    m_pControlButtonBuy->setClipRect(rect);
    m_pLayerIcon->setClipRect(rect);
}

void CcbShopItemFrameLayer::itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId)
{
    CShopDataMgr::Get()->setCellIndex(m_nCellIndex);
    CShopDataMgr::Get()->setItemId(dwItemId);
    CcbShopGiftView* pShopGiftView = (CcbShopGiftView *)CcbManager::sharedManager()->LoadCcbShopGiftViewLayer();
    if (pShopGiftView && dwItemId != 0) {
        CCDirector::sharedDirector()->getNowScene()->addChild(pShopGiftView);
        pShopGiftView->setItemsByChestId(dwItemId);
    }
    
}

