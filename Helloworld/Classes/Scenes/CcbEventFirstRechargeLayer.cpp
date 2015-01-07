#include "CcbEventFirstRechargeLayer.h"
//#include "CcbManager.h"
#include "ShopDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "EventDataMgr.h"
#include "ConfigGet.h"
#include "CcbItemInfoButtonLayer.h"
#include "EnumDefines.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"

CcbEventFirstRechargeLayer::~CcbEventFirstRechargeLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon1);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon2);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon3);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon4);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGet);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGoRecharge);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventFirstRechargeLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventFirstRechargeLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventFirstRechargeLayer", CcbEventFirstRechargeLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_first_recharge.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventFirstRechargeLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEventFirstRechargeLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbEventFirstRechargeLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
}

void CcbEventFirstRechargeLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEventFirstRechargeLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventFirstRechargeLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon1", CcbItemIconLayer*, this->m_pLayerIcon1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon2", CcbItemIconLayer*, this->m_pLayerIcon2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon3", CcbItemIconLayer*, this->m_pLayerIcon3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon4", CcbItemIconLayer*, this->m_pLayerIcon4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGet", CCControlButton*, this->m_pControlButtonGet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGoRecharge", CCControlButton*, this->m_pControlButtonGoRecharge);

	return false;
}

bool CcbEventFirstRechargeLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEventFirstRechargeLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventFirstRechargeLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventFirstRechargeLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGet", CcbEventFirstRechargeLayer::onPressControlButtonGet);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGoCharge", CcbEventFirstRechargeLayer::onPressControlButtonGoCharge);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventFirstRechargeLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    if (g_EventData->GetFirstRechargeState() == 1)
    {
        m_pControlButtonGet->setVisible(true);
        m_pControlButtonGoRecharge->setVisible(false);
    }
    else if (g_EventData->GetFirstRechargeState() == 2)
    {
        m_pControlButtonGet->setVisible(false);
        m_pControlButtonGoRecharge->setVisible(false);
    }
    else
    {
        m_pControlButtonGet->setVisible(false);
        m_pControlButtonGoRecharge->setVisible(true);
    }
}


void CcbEventFirstRechargeLayer::onPressControlButtonGet(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CGameSession::SendFirstPayReward();
}

void CcbEventFirstRechargeLayer::onPressControlButtonGoCharge(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    g_ShopData->SetCurShopShowType(1);
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendRequestStorePayList();
}

void CcbEventFirstRechargeLayer::loadData()
{
    std::vector<CcbItemIconLayer*> arrIcon;
    arrIcon.push_back(m_pLayerIcon1);
    arrIcon.push_back(m_pLayerIcon2);
    arrIcon.push_back(m_pLayerIcon3);
    arrIcon.push_back(m_pLayerIcon4);
    
    int count = 0;
    FirstRechargeConfig::STC_FIRST_RECHARGE_CONFIG* pConfig = GET_CONFIG_STC(FirstRechargeConfig, 1);
    if (pConfig)
    {
        for (int i = 0; i < 4; i++)
        {
            if (pConfig->dwItemID[i] == 0)
            {
                continue;
            }
            arrIcon[count]->setVisible(true);
            arrIcon[count]->loadIndexData(pConfig->dwItemID[i]);
            arrIcon[count]->showCnt(pConfig->dwItemCount[i]);
            count++;
        }
    }
    
    for (; count < arrIcon.size(); count++) {
        arrIcon[count]->setVisible(false);
    }
}





