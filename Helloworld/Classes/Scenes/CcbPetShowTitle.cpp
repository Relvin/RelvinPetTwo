#include "CcbPetShowTitle.h"
#include "PetCtrl.h"

//#include "PetIconCtrl.h"
#include "ConfigGet.h"
#include "UISupport.h"
//#include "CcbPetIconCtrl.h"
#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPetShowTitle::~CcbPetShowTitle()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFHp);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRec);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDef);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAtt);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFSpeed);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCrit);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
	CC_SAFE_RELEASE_NULL(m_pLayerPetIcon);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetShowTitle( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetShowTitle( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetShowTitle", CcbPetShowTitleLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshowtitle.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetShowTitle::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbPetShowTitle::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbPetShowTitle::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetShowTitle::onExit()
{
	CCLayer::onExit();
}

void CcbPetShowTitle::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetShowTitle::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFHp", CCLabelTTF*, this->m_pLabelTTFHp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRec", CCLabelTTF*, this->m_pLabelTTFRec);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDef", CCLabelTTF*, this->m_pLabelTTFDef);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAtt", CCLabelTTF*, this->m_pLabelTTFAtt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSpeed", CCLabelTTF*, this->m_pLabelTTFSpeed);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCrit", CCLabelTTF*, this->m_pLabelTTFCrit);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetIcon", CcbPetIcon*, this->m_pLayerPetIcon);
	return false;
}

bool CcbPetShowTitle::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetShowTitle::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetShowTitle::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetShowTitle::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetShowTitle::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
//    m_pLayerPetIcon->setTouchEnable(false);
    
//    expBarWidth = getWidth(m_pSpriteExpBar);
}

void CcbPetShowTitle::loadData(CPet *pPet)
{
//    CPet *pPet = CPetCtrl::GetPetByObjId(wObId);
    if (!pPet) {
        return;
    }
    m_pLayerPetIcon->setPetId(pPet->GetwIndex());
    m_pLayerPetIcon->setBtnEnable(false);
    CCString *str = CCString::create("");
    
    //HP
    str->initWithFormat("%d", pPet->GetdwHpValue());
    m_pLabelTTFHp->setString(str->getCString());
    //Att
    str->initWithFormat("%d", pPet->GetdwAttackValue());
    m_pLabelTTFAtt->setString(str->getCString());
    //Def
    str->initWithFormat("%d", pPet->GetdwDefenseValue());
    m_pLabelTTFDef->setString(str->getCString());
    //Rec
    str->initWithFormat("%d", pPet->GetdwRecoverValue());
    m_pLabelTTFRec->setString(str->getCString());
    
    PetConfig::STC_PET_CONFIG *pConfig = GET_CONFIG_STC(PetConfig, pPet->GetwIndex());
    //MaxLv
    if (pPet->GetbyMaxLv() == 0) {
        str->initWithFormat("%s%d / %d", SB_Lv, pPet->GetbyLv(), pConfig->byLvMax);
    }
    else{
        str->initWithFormat("%s%d / %d", SB_Lv, pPet->GetbyLv(), pPet->GetbyMaxLv());
    }
    m_pLabelTTFLv->setString(str->getCString());
    
    //速度}
    str->initWithFormat("%d", pPet->GetdwSpeedValue());
    m_pLabelTTFSpeed->setString(str->getCString());
    //暴击}
    str->initWithFormat("%.1f%%", (float)pPet->GetdwCritRateValue() / 100);
    m_pLabelTTFCrit->setString(str->getCString());
    
}

void CcbPetShowTitle::loadTujianData(uint16 petId)
{
//    m_pLayerPetIcon->setPetId(petId);
//    m_pLayerPetIcon->loadData();

    
    CCString *str = CCString::create("");
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, petId);
    if (!petCfg) {
        
        return;
    }
    m_pLayerPetIcon->setPetId(petId);
    m_pLayerPetIcon->setBtnEnable(false);
    //HP
    str->initWithFormat("%d", petCfg->dwHpValue);
    m_pLabelTTFHp->setString(str->getCString());
    //Att
    str->initWithFormat("%d", petCfg->dwAttackValue);
    m_pLabelTTFAtt->setString(str->getCString());
    //Def
    str->initWithFormat("%d", petCfg->dwDeffenseValue);
    m_pLabelTTFDef->setString(str->getCString());
    //Rec
    str->initWithFormat("%d", petCfg->dwRecoverValue);
    m_pLabelTTFRec->setString(str->getCString());
    
    uint8 byCurLv = 1;
    
    //MaxLv
    str->initWithFormat("%s%d / %d", SB_Lv, byCurLv, petCfg->byLvMax);
    m_pLabelTTFLv->setString(str->getCString());
    
    //速度}
    str->initWithFormat("%d", petCfg->dwSpeedValue);
    m_pLabelTTFSpeed->setString(str->getCString());
    //暴击}
    str->initWithFormat("%.1f%%", (float)petCfg->dwLuckValue / 100);
    m_pLabelTTFCrit->setString(str->getCString());

}





