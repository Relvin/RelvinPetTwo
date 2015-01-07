#include "CcbEquipCompoundFrame1Layer.h"
//#include "CcbManager.h"
#include "BackCtrl.h"
#include "EquipDataMgr.h"
#include "CcbEquipCompoundListLayer.h"
#include "PacketDataMgr.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

CcbEquipCompoundFrame1Layer::~CcbEquipCompoundFrame1Layer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pControlButtonShowInfo);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
//	CC_SAFE_RELEASE_NULL(m_pLabelTTFEquipAttri1);
//	CC_SAFE_RELEASE_NULL(m_pLabelTTFEquipAttri2);
//	CC_SAFE_RELEASE_NULL(m_pSpriteStar);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDesc);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEquipCompoundFrame1Layer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEquipCompoundFrame1Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEquipCompoundFrame1Layer", CcbEquipCompoundFrame1LayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_compound_frame1.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEquipCompoundFrame1Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    registerWithTouchDispatcher();
	return true;
}

void CcbEquipCompoundFrame1Layer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEquipCompoundFrame1Layer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipCompoundFrame1Layer::onExit()
{
	CCLayer::onExit();
}

void CcbEquipCompoundFrame1Layer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEquipCompoundFrame1Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShowInfo", CCScrollButton*, this->m_pControlButtonShowInfo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEquipAttri1", CCLabelTTF*, this->m_pLabelTTFEquipAttri1);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEquipAttri2", CCLabelTTF*, this->m_pLabelTTFEquipAttri2);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar", CCSprite*, this->m_pSpriteStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDesc", CCLabelTTF*, this->m_pLabelTTFDesc);
	return false;
}

bool CcbEquipCompoundFrame1Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEquipCompoundFrame1Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEquipCompoundFrame1Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEquipCompoundFrame1Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShowInfo", CcbEquipCompoundFrame1Layer::onPressControlButtonShowInfo);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipCompoundFrame1Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_touchFlag = false;
    m_index = 0;
}

void CcbEquipCompoundFrame1Layer::onPressControlButtonShowInfo(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    //CCLOG("%d", getLocalTag());
    if (m_touchFlag) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    g_EquipData->SetCompoundIndex(m_index);
    BackCtrl::InsertNextScene(kEquipCompoundInfoScene);
}

void CcbEquipCompoundFrame1Layer::loadData(uint32 index)
{
    m_index = index;
    RuneConfig::STC_RUNE_CONFIG* pRuneConfig = GET_CONFIG_STC(RuneConfig, index);
    if (!pRuneConfig)
    {
        return;
    }
    //计算可合成的符文个数，取前一个符文的IndexID}
    char szTemp[32] = "";
    int count = g_PacketDataMgr->GetRunesCountWithoutInlayByIndex(index-1);
    sprintf(szTemp, "%s (%d)", pRuneConfig->strName.c_str(), count / 3);
    m_pLabelTTFName->setString(szTemp);
    
    uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(m_index);
    m_pLabelTTFName->setColor(g_PacketDataMgr->getQualityColor(quality));
    
    m_pLayerIcon->loadIndexData(index);
    m_pLayerIcon->showIconOnly();
    m_pLayerIcon->setBtnEnable(false);
    
    m_pLabelTTFDesc->setString(pRuneConfig->strDesc.c_str());
}

void CcbEquipCompoundFrame1Layer::setClipRect(CCRect rect)
{
    m_pControlButtonShowInfo->setClipRect(rect);
}

void CcbEquipCompoundFrame1Layer::setBtnEnable(bool enable)
{
    m_pControlButtonShowInfo->setEnabled(enable);
}


