#include "CcbJumpTipLayer.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "EnumDefines.h"
#include "BackCtrl.h"
#include "PetCtrl.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "GuideData.h"
#include "ShopDataMgr.h"
#include "PacketDataMgr.h"
#include "Item.h"
#include "PetLoadingLayer.h"

void CShowJumpTip::Show(SHOW_JUMP_TIP emType, uint32 itemId)
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene->getChildByTag(2121))
    {
        pScene->removeChildByTag(2121);
    }
    CShowJumpTip::Get()->setNeedItemId(itemId);
    CShowJumpTip::Get()->setJumpType(emType);
    CcbJumpTipLayer* pLayer = (CcbJumpTipLayer*)CcbManager::sharedManager()->LoadCcbJumpTipLayer(pScene);
    pLayer->retain();
    pScene->addChild(pLayer, 1, 2121);
    pLayer->SetShowJumpTip(emType, itemId);
    pLayer->autorelease();
}

void CShowJumpTip::Close()
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene->getChildByTag(2121))
    {
        pScene->removeChildByTag(2121);
    }
}

CcbJumpTipLayer::~CcbJumpTipLayer()
{

	CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFContent);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTipTitle);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGo);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbJumpTipLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbJumpTipLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbJumpTipLayer", CcbJumpTipLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbCostTipLayer.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbJumpTipLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbJumpTipLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_pLabelTTFContent->noStroke();
    m_pLabelTTFTipTitle->noStroke();
}

void CcbJumpTipLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbJumpTipLayer::onExit()
{
	CCLayer::onExit();
}

void CcbJumpTipLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbJumpTipLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFContent", CCLabelTTF*, this->m_pLabelTTFContent);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTipTitle", CCLabelTTF*, this->m_pLabelTTFTipTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGo", CCControlButton*, this->m_pControlButtonGo);

	return false;
}

bool CcbJumpTipLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbJumpTipLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbJumpTipLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbJumpTipLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbJumpTipLayer::onPressControlButtonCancel);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGo", CcbJumpTipLayer::onPressControlButtonGo);

	return NULL;
}

void CcbJumpTipLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2*kCCMenuHandlerPriority - 23, true);
}

bool CcbJumpTipLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
    
}

// Inhert CCNodeLoaderListener
void CcbJumpTipLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pLabelTTFContent->setString(GET_STR(Str_no_init));
    m_pLabelTTFTipTitle->setString("");
    m_posButton1 = m_pControlButtonGo->getPosition();
    
    m_pControlButtonCancel->setTouchPriority(2*kCCMenuHandlerPriority - 24);
    m_pControlButtonGo->setTouchPriority(2*kCCMenuHandlerPriority - 24);
}

void CcbJumpTipLayer::SetShowJumpTip(SHOW_JUMP_TIP emType, uint32 itemId)
{
    m_emShowJumpTipType = emType;
    
    //[2014-11-1] bug fixed, 当系统引导的时候，如果有错误，会走不下去。}
    GuideData::GetInstance()->onlyRmGuideLayer();
    
    switch (emType)
    {
        case E_ITEM_NOT_ENOUGH:
        {
//            const CItem* item = g_PacketDataMgr->GetItemInfoByIndex(itemId);
            ItemConfig::STC_ITEM_CONFIG* item = GET_CONFIG_STC(ItemConfig, itemId);
            if (item) {                
                m_pLabelTTFTipTitle->setString(CCString::createWithFormat("%s%s", item->strName.c_str(), GET_STR(Str_bu_gou_la))->getCString());
                m_pLabelTTFContent->setString(GET_STR(Str_go_shop));
                m_pControlButtonGo->setTitleForState( CCString::create(GET_STR(Str_mai_mai_mai)), CCControlStateNormal);
            }
            else
            {
                m_pLabelTTFContent->setString(GET_STR(Str_no_item_o));
                m_pLabelTTFTipTitle->setString(GET_STR(Str_no_item));
                m_pControlButtonGo->setTitleForState( CCString::create(GET_STR(Str_mai_mai_mai)), CCControlStateNormal);
            }

        }
            break;
        case E_POWER_NOT_ENOUGH://体力不足}
        {
            m_pLabelTTFContent->setString(GET_STR(Str_shop_no_energy));
            m_pLabelTTFTipTitle->setString(CCString::createWithFormat("%s%s", GET_STR(Str_Energy), GET_STR(Str_bu_gou_la))->getCString());
            m_pControlButtonGo->setTitleForState( CCString::create(GET_STR(Str_power_no_enough)), CCControlStateNormal);
        }
            break;
        case E_MONEY_NOT_ENOUGH://金币不足}
        {
            m_pLabelTTFContent->setString(GET_STR(Str_shop_no_money));
            m_pLabelTTFTipTitle->setString(CCString::createWithFormat("%s%s", GET_STR(Str_money), GET_STR(Str_bu_gou_la))->getCString());
            
            m_pControlButtonGo->setTitleForState( CCString::create(GET_STR(Str_coin_no_enough)), CCControlStateNormal);
        }
            break;
        case E_REPUTATION_NOT_ENOUGH://声望不足}
        {
            m_pLabelTTFContent->setString(GET_STR(Str_how_get_raputation));
            m_pLabelTTFTipTitle->setString(GET_STR(Str_shop_no_reputation));
            
            m_pControlButtonGo->setTitleForState( CCString::create(GET_STR(Str_reputation_no_enough)), CCControlStateNormal);
        }
            break;
        case E_FUSE_STONE_NOT_ENOUGH://融合石不足}
        {
            m_pLabelTTFContent->setString(GET_STR(Str_how_get_fuse));
            m_pLabelTTFTipTitle->setString(GET_STR(Str_no_fuse));
            
            m_pControlButtonGo->setTitleForState( CCString::create(GET_STR(Str_fuse_stone_no_enouth)), CCControlStateNormal);
        }
            break;
            
        case E_DOLLAR_NOT_ENOUGH: //钻石不足
        {
            m_pLabelTTFContent->setString(GET_STR(Str_how_get_dollar));
            m_pLabelTTFTipTitle->setString(GET_STR(Str_no_dollar));
            m_pControlButtonGo->setTitleForState( CCString::create(GET_STR(Str_buy_dollar_arOnce)), CCControlStateNormal);
        }
            break;
        case E_VIP_NOT_ENOUGH: //VIP不足
        {
            m_pLabelTTFContent->setString(GET_STR(Str_get_vip));
            m_pLabelTTFTipTitle->setString(GET_STR(Str_no_buy_cnt));
            m_pControlButtonGo->setTitleForState( CCString::create(GET_STR(Str_buy_dollar_arOnce)), CCControlStateNormal);
        }
            break;
        default:
            break;
    }
}

void CcbJumpTipLayer::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    CShowJumpTip::Get()->setJumpType(E_SHOW_JUMP_NULL);
    CShowJumpTip::Get()->setNeedItemId(0);
    CShowJumpTip::Get()->Close();
}

void CcbJumpTipLayer::onPressControlButtonGo(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	// TODO:
    switch (m_emShowJumpTipType)
    {
        case E_ITEM_NOT_ENOUGH:
        {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            g_ShopData->SetCurShopShowType(E_SHOP_TYPE_NORMAL);
            CGameSession::SendOpenShopRequest();
        }
            break;
        case E_PET_PACKAGE_FULL:;
        case E_ITEM_PACKAGE_FULL:
        case E_POWER_NOT_ENOUGH:
        case E_MONEY_NOT_ENOUGH:
            CGameSession::SendReqShopCnt();
            break;
        case E_REPUTATION_NOT_ENOUGH:
            CGameSession::SendArenaBattleListRequest();
            break;
        case E_FUSE_STONE_NOT_ENOUGH:
            BackCtrl::InsertNextScene(kPetFuse);
            break;
        case E_DOLLAR_NOT_ENOUGH:
        case E_VIP_NOT_ENOUGH:
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            g_ShopData->SetCurShopShowType(E_SHOP_TYPE_RECHARGE);
            CGameSession::SendRequestStorePayList();
            break;
        default:
            break;
    }
}






