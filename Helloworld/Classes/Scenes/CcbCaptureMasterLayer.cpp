#include "CcbCaptureMasterLayer.h"
//#include "CcbManager.h"
#include "CaptureScene.h"
#include "GameSession.h"
#include "Instruments.h"
#include "PetCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbCaptureMasterLayer::~CcbCaptureMasterLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonRevolt);
	CC_SAFE_RELEASE_NULL(m_pSpriteMasterHead);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMasterName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMasterGroup);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCageTime);

}

//-- copy this to CcbManager 
/*
//CcbManager.h


//CcbManager.cpp

*/


bool CcbCaptureMasterLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbCaptureMasterLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbCaptureMasterLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbCaptureMasterLayer::onExit()
{
	CCLayer::onExit();
}

void CcbCaptureMasterLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbCaptureMasterLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRevolt", CCControlButton*, this->m_pControlButtonRevolt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMasterHead", CCSprite*, this->m_pSpriteMasterHead);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMasterName", CCLabelTTF*, this->m_pLabelTTFMasterName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMasterGroup", CCLabelTTF*, this->m_pLabelTTFMasterGroup);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCageTime", CCLabelTTF*, this->m_pLabelTTFCageTime);

	return false;
}

bool CcbCaptureMasterLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbCaptureMasterLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbCaptureMasterLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbCaptureMasterLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRevolt", CcbCaptureMasterLayer::onPressControlButtonRevolt);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbCaptureMasterLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
//    m_pLabelTTFMasterName->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFMasterGroup->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFCageTime->setStrokeForLabelTTF(ccBLACK, 1.0);
    setMasterInfo();
}



void CcbCaptureMasterLayer::onPressControlButtonRevolt(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CGameSession::SendSlaveRevolt(CaptureCtrl::masterInfo.dwMasterId, CaptureCtrl::byCurType, CaptureCtrl::masterInfo.byMasterFarmId);
}

#pragma mark Private Method
void CcbCaptureMasterLayer::updateTime(float dt)
{
    if (m_dwLeftTime) {
        m_dwLeftTime--;
        m_pLabelTTFCageTime->setString(getLeftTimeFromInt(m_dwLeftTime)->getCString());
    }
}

void CcbCaptureMasterLayer::setMasterInfo()
{
    unschedule(schedule_selector(CcbCaptureMasterLayer::updateTime));
    
    CaptureCtrl::STC_MASTER masterInfo = CaptureCtrl::masterInfo;
    
    m_dwLeftTime = masterInfo.dwLeftTime;
    
    m_pLabelTTFMasterName->setString(masterInfo.strMasterName.c_str());
    m_pLabelTTFCageTime->setString(getLeftTimeFromInt(masterInfo.dwLeftTime)->getCString());
    m_pSpriteMasterHead->setTexture(CPetCtrl::Get()->GetPetHeadTexture(masterInfo.wLeaderId));
    RankRewardConfig::STC_RANKREWARD_CONFIG* pConfig = GET_CONFIG_STC(RankRewardConfig, masterInfo.byGroupId);
    m_pLabelTTFMasterGroup->setString(pConfig->strGroupName.c_str());
    
    schedule(schedule_selector(CcbCaptureMasterLayer::updateTime), 1.0f);
}




