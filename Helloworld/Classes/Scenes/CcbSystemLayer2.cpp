#include "CcbSystemLayer2.h"
#include "CcbManager.h"
#include "Role.h"
#include "GameSession.h"
#include "EnumDefines.h"
#include "ShopDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "UISupport.h"
#include "MusicCtrl.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

void CSystemMessage2::Show(SHOW_MSG_TYPE emType, uint32 dwCount1, uint32 dwCount2)
{
    Create();
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene->getChildByTag(2123))
    {
        pScene->removeChildByTag(2123);
    }
    CcbSystemLayer2* pLayer = (CcbSystemLayer2*)CcbManager::sharedManager()->LoadSystemMessage2();
    pLayer->retain();
    pScene->addChild(pLayer, 1, 2123);
    pLayer->SetShowMsg(emType, dwCount1, dwCount2);
    pLayer->autorelease();
}


void CSystemMessage2::Refeash(uint32 dwCount1, uint32 dwCount2)
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene->getChildByTag(2123))
    {
        CCLayer* pLayer = (CCLayer*)pScene->getChildByTag(2123);
        if (pLayer)
        {
            ((CcbSystemLayer2*)pLayer)->SetShowMsg(m_emType, dwCount1, dwCount2);
        }
    }
}

void CSystemMessage2::Close()
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene->getChildByTag(2123))
    {
        pScene->removeChildByTag(2123);
    }
    Destory();
}

CcbSystemLayer2::~CcbSystemLayer2()
{
	CC_SAFE_RELEASE_NULL(m_pLayerColor);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTipTitle);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFContentTitle);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFText1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFText2);
	CC_SAFE_RELEASE_NULL(m_pSpriteArrowRight);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFText3);
	CC_SAFE_RELEASE_NULL(m_pSpriteArrowUp);
	CC_SAFE_RELEASE_NULL(m_pLayerTextParent);
	CC_SAFE_RELEASE_NULL(m_pControlButtonOk);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbSystemLayer2( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbSystemLayer2( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbSystemLayer2", CcbSystemLayer2Loader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/message2.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbSystemLayer2::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbSystemLayer2::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbSystemLayer2::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbSystemLayer2::onExit()
{
	CCLayer::onExit();
}

void CcbSystemLayer2::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbSystemLayer2::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerColor", CCLayer*, this->m_pLayerColor);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTipTitle", CCLabelTTF*, this->m_pLabelTTFTipTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFContentTitle", CCLabelTTF*, this->m_pLabelTTFContentTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText1", CCLabelTTF*, this->m_pLabelTTFText1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText2", CCLabelTTF*, this->m_pLabelTTFText2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteArrowRight", CCSprite*, this->m_pSpriteArrowRight);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText3", CCLabelTTF*, this->m_pLabelTTFText3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteArrowUp", CCSprite*, this->m_pSpriteArrowUp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTextParent", CCLayer*, this->m_pLayerTextParent);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOk", CCControlButton*, this->m_pControlButtonOk);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);

	return false;
}

bool CcbSystemLayer2::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbSystemLayer2::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbSystemLayer2::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbSystemLayer2::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOk", CcbSystemLayer2::onPressControlButtonOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbSystemLayer2::onPressControlButtonCancel);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbSystemLayer2::onPressControlButtonClose);

	return NULL;
}

void CcbSystemLayer2::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*2 - 21, true);
    
}

bool CcbSystemLayer2::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

// Inhert CCNodeLoaderListener
void CcbSystemLayer2::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonOk->setTouchPriority(kCCMenuHandlerPriority*2-22);
    m_pControlButtonCancel->setTouchPriority(kCCMenuHandlerPriority*2-22);
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority*2-22);

}

void CcbSystemLayer2::SetShowMsg(SHOW_MSG_TYPE emType, uint32 dwCount1, uint32 dwCount2)
{
    m_emMsgType = emType;
    char szTemp[256] = "";
    CRole* pRole = CGameSession::GetRole();
    switch (emType)
    {
        case E_TYPE_POWER:
        {
            m_pLabelTTFTipTitle->setString(GET_STR(Str_power_revert));
            
            sprintf(szTemp, GET_STR(Str_cost_for_add_energy), dwCount1, dwCount2);
            m_pLabelTTFContentTitle->setString(szTemp);
            
            m_pLabelTTFText1->setString(GET_STR(Str_cur_power));
            sprintf(szTemp, "%d", pRole->GetdwEnergy());
            m_pLabelTTFText2->setString(szTemp);
            sprintf(szTemp, "%d", pRole->GetdwEnergy() + dwCount2);
            m_pLabelTTFText3->setString(szTemp);
        }
            break;
        case E_TYPE_ITEM_BAG_FULL:
        case E_TYPE_ITEM_BAG:
        {
            m_pLabelTTFTipTitle->setString(GET_STR(Str_buy_item_packet));
            
            if (emType == E_TYPE_ITEM_BAG_FULL) {
                sprintf(szTemp, GET_STR(Str_cost_for_add_item_bag), dwCount1, dwCount2);
            }
            else
            {
                sprintf(szTemp, GET_STR(Str_ItemBagLayer_Expand), dwCount1, dwCount2);
            }
            
            m_pLabelTTFContentTitle->setString(szTemp);
            
            m_pLabelTTFText1->setString(GET_STR(Str_cur_bag));
            sprintf(szTemp, GET_STR(Str_jige), pRole->GetdwItemBagCnt());
            m_pLabelTTFText2->setString(szTemp);
            sprintf(szTemp, GET_STR(Str_jige), pRole->GetdwItemBagCnt() + dwCount2);
            m_pLabelTTFText3->setString(szTemp);
        }
            break;
        case E_TYPE_PET_BAG_FULL:
        case E_TYPE_PET_BAG:
        {
            m_pLabelTTFTipTitle->setString(GET_STR(Str_buy_pet_packet));
            if (emType == E_TYPE_PET_BAG_FULL) {
                sprintf(szTemp, GET_STR(Str_cost_for_add_pet_bag), dwCount1, dwCount2);
            }
            else
            {
                sprintf(szTemp, GET_STR(Str_PetLayer_Expand), dwCount1, dwCount2);
            }
            
            m_pLabelTTFContentTitle->setString(szTemp);

            m_pLabelTTFText1->setString(GET_STR(Str_cur_pet_packet));
            sprintf(szTemp, GET_STR(Str_jige), pRole->GetdwPetBagCnt());
            m_pLabelTTFText2->setString(szTemp);
            sprintf(szTemp, GET_STR(Str_jige), pRole->GetdwPetBagCnt() + dwCount2);
            m_pLabelTTFText3->setString(szTemp);
        }
            break;
        case E_TYPE_GET_COIN:
            m_pLabelTTFTipTitle->setString(GET_STR(Str_buy_coin));
            
            sprintf(szTemp, GET_STR(Str_cost_for_add_money), dwCount1, dwCount2);
            m_pLabelTTFContentTitle->setString(szTemp);
            m_pLabelTTFText1->setString("");
            m_pLabelTTFText2->setString("");
            m_pLabelTTFText3->setString("");
            m_pSpriteArrowRight->setVisible(false);
            m_pSpriteArrowUp->setVisible(false);
            CShopDataMgr::Get()->setAddMoney(dwCount2);
            break;
        default:
            break;
    }
    
    CSystemMessage2::Get()->SetMsgType(emType);
    if (emType != E_TYPE_GET_COIN)
    {
        m_pSpriteArrowRight->setVisible(true);
        m_pSpriteArrowUp->setVisible(true);
        
        m_pSpriteArrowRight->setPositionX(getRight(m_pLabelTTFText2));
        m_pLabelTTFText3->setPositionX(getRight(m_pSpriteArrowRight));
        m_pSpriteArrowUp->setPositionX(getRight(m_pLabelTTFText3));
    }
    if (dwCount1 > CGameSession::GetRole()->GetdwDollar())
    {
        CShopDataMgr::Get()->setAddMoney(0);
    }
}

void CcbSystemLayer2::onPressControlButtonOk(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    switch (m_emMsgType)
    {
        case E_TYPE_POWER:
        {
            CGameSession::SendItemBagEnlager(E_ROLE_OPERATE_TYPE_ENERGY);
            AnalysicsManager::sharedAnalyticsMgr()->SendEvent("buy_energy");
        }
            break;
        case E_TYPE_ITEM_BAG_FULL:
        case E_TYPE_ITEM_BAG:
        {
            CGameSession::SendItemBagEnlager(E_ROLE_OPERATE_TYPE_ITEM_BAG);
            AnalysicsManager::sharedAnalyticsMgr()->SendEvent("expand_bag");
        }
            break;
        case E_TYPE_PET_BAG_FULL:
        case E_TYPE_PET_BAG:
        {
            CGameSession::SendItemBagEnlager(E_ROLE_OPERATE_TYPE_PET_BAG);
            AnalysicsManager::sharedAnalyticsMgr()->SendEvent("expand_pet");
        }
            break;
        case E_TYPE_GET_COIN:
        {
            CGameSession::SendItemBagEnlager(E_ROLE_OPERATE_TYPE_GET_COIN);
            AnalysicsManager::sharedAnalyticsMgr()->SendEvent("buy_coin");
        }
            break;
        default:
            break;
    }
}

void CcbSystemLayer2::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	// TODO:
    CSystemMessage2::Get()->Close();
    CShopDataMgr::Get()->setAddMoney(0);
}

void CcbSystemLayer2::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
	// TODO:
    CSystemMessage2::Get()->Close();
    CShopDataMgr::Get()->setAddMoney(0);
}





