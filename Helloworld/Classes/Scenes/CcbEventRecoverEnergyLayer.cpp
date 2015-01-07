#include "CcbEventRecoverEnergyLayer.h"
//#include "CcbManager.h"
#include "Role.h"
#include "GameSession.h"
#include "FlyTextLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "UISupport.h"

CcbEventRecoverEnergyLayer::~CcbEventRecoverEnergyLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonRecover);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRewardDesc);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventRecoverEnergyLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventRecoverEnergyLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventRecoverEnergyLayer", CcbEventRecoverEnergyLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_recover_energy.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventRecoverEnergyLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEventRecoverEnergyLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::GetRole()->Attach(this);
}

void CcbEventRecoverEnergyLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEventRecoverEnergyLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::GetRole()->Detach(this);
}

void CcbEventRecoverEnergyLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventRecoverEnergyLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRecover", CCControlButton*, this->m_pControlButtonRecover);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRewardDesc", CCLabelTTF*, this->m_pLabelTTFRewardDesc);

	return false;
}

bool CcbEventRecoverEnergyLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEventRecoverEnergyLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventRecoverEnergyLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventRecoverEnergyLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRecover", CcbEventRecoverEnergyLayer::onPressControlButtonRecover);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventRecoverEnergyLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonRecover->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(1.5, 0.95),
                                                                                  CCScaleTo::create(1.5, 1.0),
                                                                                  NULL)));
    
    m_curEnergy = CGameSession::GetRole()->GetdwEnergy();
    dwEnergyChanged(m_curEnergy);
}

void CcbEventRecoverEnergyLayer::onPressControlButtonRecover(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	
    CRole* pRole = CGameSession::GetRole();
    if (pRole && pRole->GetbyEnergyRewStatus() == 1)
    {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        CGameSession::SendEarnEnergyReward();
        CCParticleSystemQuad* eff = CCParticleSystemQuad::create("ccbresources/12monthdate/event/effect_tili_03.plist");
        CCPoint pos = m_pControlButtonRecover->getPosition();
        eff->setPosition(pos);
        eff->setTag(111);
        m_pControlButtonRecover->getParent()->addChild(eff);
    }
    else
    {
        FlyTextLayer::showTips(GET_STR(Str_cannot_get));
    }
}

void CcbEventRecoverEnergyLayer::dwEnergyChanged(uint32 dwEnergy)
{
    PetLoadingLayer::sharedLayer()->End();

    if (dwEnergy != m_curEnergy) {
        CCString* str = CCString::createWithFormat(GET_STR(Str_Get_Energy), dwEnergy - m_curEnergy);
        m_curEnergy = dwEnergy;
        FlyTextLayer::showTips(str->getCString());
        m_pControlButtonRecover->setVisible(false);
        hideEff();
        return;
    }
    
    CRole* pRole = CGameSession::GetRole();
    if (pRole && pRole->GetbyEnergyRewStatus() == 1)
    {
        m_pControlButtonRecover->setVisible(true);
        showEff();
    }
    else
    {
        m_pControlButtonRecover->setVisible(false);
        hideEff();
    }
}

void CcbEventRecoverEnergyLayer::showEff()
{
    CCParticleSystemQuad* eff1 = CCParticleSystemQuad::create("ccbresources/12monthdate/event/effect_tili_01.plist");
    CCParticleSystemQuad* eff2 = CCParticleSystemQuad::create("ccbresources/12monthdate/event/effect_tili_02.plist");
    
    CCPoint pos = ccp(getCenterX(m_pControlButtonRecover), getBottom(m_pControlButtonRecover));
    
    eff1->setPosition(pos);
    eff1->setTag(111);
    m_pControlButtonRecover->getParent()->addChild(eff1);
    
    eff2->setPosition(getCenter(m_pControlButtonRecover));
    eff2->setTag(112);
    m_pControlButtonRecover->getParent()->addChild(eff2);
}

void CcbEventRecoverEnergyLayer::hideEff()
{
    if (m_pControlButtonRecover->getParent()->getChildByTag(111)) {
        m_pControlButtonRecover->getParent()->removeChildByTag(111);
    }
    
    if (m_pControlButtonRecover->getParent()->getChildByTag(112)) {
        m_pControlButtonRecover->getParent()->removeChildByTag(112);
    }
}



