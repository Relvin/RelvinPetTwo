#include "CcbExcPetFrameLayer.h"
//#include "CcbManager.h"
#include "CcbPetIcon.h"
#include "ConfigGet.h"
#include "PacketDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbExcPetFrameLayer::~CcbExcPetFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPetName2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFSkillName2);
	CC_SAFE_RELEASE_NULL(m_pLayerPet);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbExcPetFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbExcPetFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbExcPetFrameLayer", CcbExcPetFrameLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/pet_icon.ccb]", [ccb/pet_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_excpet_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbExcPetFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbExcPetFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbExcPetFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbExcPetFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbExcPetFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbExcPetFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetName2", CCLabelTTF*, this->m_pLabelTTFPetName2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSkillName2", CCLabelTTF*, this->m_pLabelTTFSkillName2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPet", CCLayer*, this->m_pLayerPet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr", CCLabelTTF*, this->m_pLabelTTFAttr);

	return false;
}

bool CcbExcPetFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbExcPetFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbExcPetFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbExcPetFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbExcPetFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbExcPetFrameLayer::loadData(STC_EXC_PET excPet)
{
    CcbPetIcon* icon = dynamic_cast<CcbPetIcon*>(m_pLayerPet);
    if (icon) {
        icon->setPetId(excPet.petIndex);
        icon->loadData();
    }
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, excPet.petIndex);
    //宠物名}
    if (petCfg) {
        m_pLabelTTFPetName2->setString(petCfg->strName.c_str());
    }
    
    //专属属性}
    CCString* str = CCString::createWithFormat("+%.1f%%", (float)excPet.dwEmbValue / 100);
    m_pLabelTTFSkillName2->setString(str->getCString());
    
    m_pLabelTTFAttr->setString(g_PacketDataMgr->getAttrText(excPet.byEmbType).c_str());
}







