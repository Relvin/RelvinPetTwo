#include "CcbShopGemListLayer.h"
#include "CcbManager.h"
#include "CcbGemListFrameLayer.h"
#include "ConfigGet.h"
#include "BackCtrl.h"
#include "Role.h"
#include "GameSession.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "CcbVipListLayer.h"
#include "ResourceStringClient.h"
#include "GlobalData.h"
#include "UserInfoDataMgr.h"

static CcbShopGemListLayer *m_pShare = NULL;

CcbShopGemListLayer* CcbShopGemListLayer::shareInstance()
{
    return m_pShare;
}

CcbShopGemListLayer::CcbShopGemListLayer()
: m_pLayerGemList(NULL)
, m_pLayerParent(NULL)
, m_pControlButtonGotoVIP(NULL)
, m_pControlButtonBackShopgem(NULL)
, m_pLabelTTFCurVip(NULL)
, m_pLabelTTFNextVip(NULL)
, m_pLabelTTFText1(NULL)
, m_pLabelTTFDollarToNext(NULL)
, m_pLabelTTFText2(NULL)
, m_pSpriteVipProcess(NULL)
, m_pTableViewTabGem(NULL)
, m_pVipListLayer(NULL)
, m_pTiplessVip2(NULL)
, m_pScale9VipBg(NULL)
, m_fVipProcessWidth(0.0f)
{
    
}

CcbShopGemListLayer::~CcbShopGemListLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerGemList);
    CC_SAFE_RELEASE_NULL(m_pLayerParent);
    CC_SAFE_RELEASE_NULL(m_pControlButtonGotoVIP);
    CC_SAFE_RELEASE_NULL(m_pControlButtonBackShopgem);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurVip);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextVip);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFText1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDollarToNext);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFText2);
    CC_SAFE_RELEASE_NULL(m_pSpriteVipProcess);
    CC_SAFE_RELEASE_NULL(m_pTableViewTabGem);
    CC_SAFE_RELEASE_NULL(m_pTiplessVip2);
    CC_SAFE_RELEASE_NULL(m_pScale9VipBg);
    m_pShare = NULL;
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 CCNode* LoadCcbShopGemListLayer( CCObject* owner );
 
 //CcbManager.cpp
 CCNode* CcbManager::LoadCcbShopGemListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbShopGemListLayer", CcbShopGemListLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
 pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
 
 
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_gem_list.ccbi", owner);
	pCCBReader->release();
 
	return pNode;
 }
 */


bool CcbShopGemListLayer::init()
{
    // First be called.
    if (!CCLayer::init()) {
        return false;
    }
    m_pShare = this;
    // code here
    return true;
}

void CcbShopGemListLayer::onEnter()
{
    CCLayer::onEnter();
    CGameSession::Attach(this);
    CGameSession::GetRole()->Attach(this);
    if (UserInfoDataMgr::Get()->getGotoVipFlag()) {
        this->onPressControlButtonGotoVIP(NULL, CCControlEventTouchUpInside);
        UserInfoDataMgr::Get()->setGotoVipFlag(false);
    }
}

void CcbShopGemListLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
    m_pTableViewTabGem->reloadData();
}

void CcbShopGemListLayer::onExit()
{
    CGameSession::GetRole()->Detach(this);
    CGameSession::Detach(this);
    CCLayer::onExit();
}

void CcbShopGemListLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbShopGemListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerGemList", CCLayer*, this->m_pLayerGemList);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent", CCLayer*, this->m_pLayerParent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGotoVIP", CCControlButton*, this->m_pControlButtonGotoVIP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBackShopgem", CCControlButton*, this->m_pControlButtonBackShopgem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurVip", CCLabelTTF*, this->m_pLabelTTFCurVip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextVip", CCLabelTTF*, this->m_pLabelTTFNextVip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText1", CCLabelTTF*, this->m_pLabelTTFText1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDollarToNext", CCLabelTTF*, this->m_pLabelTTFDollarToNext);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText2", CCLabelTTF*, this->m_pLabelTTFText2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteVipProcess", CCSprite*, this->m_pSpriteVipProcess);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pTiplessVip2", CCNode*, this->m_pTiplessVip2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9VipBg", CCScale9Sprite*, this->m_pScale9VipBg);
    
    return false;
}

bool CcbShopGemListLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbShopGemListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
    return NULL;
}

SEL_MenuHandler CcbShopGemListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
    return NULL;
}

SEL_CCControlHandler CcbShopGemListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGotoVIP", CcbShopGemListLayer::onPressControlButtonGotoVIP);
    return NULL;
}

// Inhert CCNodeLoaderListener
void CcbShopGemListLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    // 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
    // 可以删除，如果不需要}
    float addVipLayerHeight = 0.0f;
    if (GlobalData::shared()->getVipSwitch()) {
        m_pScale9VipBg->getParent()->setVisible(false);
        addVipLayerHeight = m_pScale9VipBg->getPreferredSize().height;
    }
    
    m_pLayerGemList->setContentSize(CCSizeMake(getWidth(m_pLayerGemList), addVipLayerHeight + getBottom(getChildByTag(333)) - m_pLayerGemList->getPosition().y + 5));
    m_clipRect = m_pLayerGemList->boundingBox();
    
    CShopDataMgr::Get()->SetCurShopShowType(E_SHOP_TYPE_RECHARGE);
    
    m_vecShowList = CShopDataMgr::Get()->GetStorePayList();
    
    m_pTableViewTabGem = CCTableView::create(this, m_pLayerGemList->getContentSize());
    m_pTableViewTabGem->setDirection(kCCScrollViewDirectionVertical);
    m_pTableViewTabGem->setPosition(CCPointZero);
    m_pTableViewTabGem->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableViewTabGem->retain();
    m_pTableViewTabGem->setAnchorPoint(CCPointZero);
    m_pTableViewTabGem->setTouchPriority(kCCMenuHandlerPriority);
    m_pLayerGemList->addChild(m_pTableViewTabGem, 1);
    
    m_fVipProcessWidth = m_pSpriteVipProcess->getContentSize().width;
    
    this->SetVipData();
    
}

void CcbShopGemListLayer::SetVipData()
{
    CRole *pRole = CGameSession::GetRole();
    if (pRole)
    {
        uint8 byCurVip = pRole->GetbyVipLv();
        char szTemp[32] = "\0";
        sprintf(szTemp, "VIP%d", byCurVip);
        m_pLabelTTFCurVip->setString(szTemp);
        VipShowConfig::STC_VIP_SHOW_CONFIG* pConfig = NULL;GET_CONFIG_STC(VipShowConfig, byCurVip+1);
        
        int nextVip = 3;
        if (byCurVip < nextVip) {
            pConfig = GET_CONFIG_STC(VipShowConfig, nextVip);
            m_pTiplessVip2->setVisible(true);
            m_pLabelTTFDollarToNext->getParent()->setVisible(false);
            ((CCLabelTTF *)m_pTiplessVip2->getChildByTag(1))->setString(CCString::createWithFormat("VIP%d",nextVip)->getCString());
            if (pConfig) {
                ((CCLabelTTF *)m_pTiplessVip2->getChildByTag(0))->setString(CCString::createWithFormat("%d", pConfig->dwRechargeVal - pRole->GetdwVipExp())->getCString());
                float pre = (float)pRole->GetdwVipExp() / (float)pConfig->dwRechargeVal;
                float width = m_fVipProcessWidth * pre;
                m_pSpriteVipProcess->setTextureRect(CCRectMake(0, 0, width, m_pSpriteVipProcess->getContentSize().height));
            }
            ((CCLabelTTF *)m_pTiplessVip2->getChildByTag(2))->setString(GET_STR(Str_LowVip2_notice_text));
        }
        else
        {
            m_pTiplessVip2->setVisible(false);
            m_pLabelTTFDollarToNext->getParent()->setVisible(true);
            
            sprintf(szTemp, "VIP%d", byCurVip + 1);
            m_pLabelTTFNextVip->setString(szTemp);
            
            pConfig = GET_CONFIG_STC(VipShowConfig, byCurVip+1);
            if (pConfig)
            {
                float pre = (float)pRole->GetdwVipExp() / (float)pConfig->dwRechargeVal;
                float width = m_fVipProcessWidth * pre;
                m_pSpriteVipProcess->setTextureRect(CCRectMake(0, 0, width, m_pSpriteVipProcess->getContentSize().height));
                sprintf(szTemp, "%d", pConfig->dwRechargeVal - pRole->GetdwVipExp());
                m_pLabelTTFDollarToNext->setString(szTemp);
                m_pLabelTTFText1->setPositionX(getLeft(m_pLabelTTFDollarToNext));
            }

        }
    }
}

CCSize CcbShopGemListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerGemList), 68 + 5);
}

CCTableViewCell* CcbShopGemListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CCNode* pLayer = CcbManager::sharedManager()->LoadCcbGemListFrameLayer(this);
        pLayer->setPosition(getWidth(m_pLayerGemList) - 3, 0);
        pLayer->setAnchorPoint(ccp(1, 0));
        pLayer->ignoreAnchorPointForPosition(false);
        pCell->addChild(pLayer, 1, 123);
    }
    
    CcbGemListFrameLayer* pNode = (CcbGemListFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->setClipRect(m_clipRect);
        pNode->setChargeInfo(m_vecShowList[idx].dwGoodsId);
    }
    
    return pCell;
}

unsigned int CcbShopGemListLayer::numberOfCellsInTableView(CCTableView *table)
{
    //return 1;
    return m_vecShowList.size();
}

void CcbShopGemListLayer::onPressControlButtonGotoVIP(CCObject* pSender, CCControlEvent event)
{
    if (pSender) {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    }
    
    if (!m_pVipListLayer) {
        m_pVipListLayer = (CcbVipListLayer*)CcbManager::sharedManager()->LoadCcbVipListLayer(this,m_pLayerGemList->getContentSize());
        m_pLayerGemList->addChild(m_pVipListLayer,1);
        m_pVipListLayer->setPosition(ccp(0,6));
        m_pVipListLayer->setVisible(false);
    }
    if (!pSender && m_pVipListLayer->isVisible()) {
        return;
    }
    m_pTableViewTabGem->setVisible(!m_pTableViewTabGem->isVisible());
    m_pVipListLayer->setVisible(!m_pTableViewTabGem->isVisible());
    
    m_pControlButtonGotoVIP->setVisible(m_pTableViewTabGem->isVisible());
    m_pControlButtonBackShopgem->setVisible(m_pVipListLayer->isVisible());
    
}

void CcbShopGemListLayer::refreshLayer()
{
    m_pTableViewTabGem->reloadData();
    this->SetVipData();
    if (UserInfoDataMgr::Get()->getGotoVipFlag()) {
        this->onPressControlButtonGotoVIP(NULL, CCControlEventTouchUpInside);
        UserInfoDataMgr::Get()->setGotoVipFlag(false);
    }
}


void CcbShopGemListLayer::byVipLvChanged(uint8 byVipLv)
{
    this->SetVipData();
}

void CcbShopGemListLayer::dwVipExpChanged(uint32 dwVipExp)
{
    this->SetVipData();
}