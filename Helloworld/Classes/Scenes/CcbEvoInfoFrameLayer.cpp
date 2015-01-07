#include "CcbEvoInfoFrameLayer.h"
//#include "CcbManager.h"
#include "ConfigGet.h"
#include "EnumDefines.h"
#include "Pet.h"
#include "PetCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbEvoInfoFrameLayer::~CcbEvoInfoFrameLayer()
{
//	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPetLv);
	CC_SAFE_RELEASE_NULL(m_pSpriteNext);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFSkillName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFHp);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRev);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAtt);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDef);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoLv);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEvoInfoFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEvoInfoFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEvoInfoFrameLayer", CcbEvoInfoFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/evo_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEvoInfoFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEvoInfoFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEvoInfoFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEvoInfoFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEvoInfoFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEvoInfoFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetLv", CCLabelTTF*, this->m_pLabelTTFPetLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNext", CCSprite*, this->m_pSpriteNext);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSkillName", CCLabelTTF*, this->m_pLabelTTFSkillName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFHp", CCLabelTTF*, this->m_pLabelTTFHp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRev", CCLabelTTF*, this->m_pLabelTTFRev);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAtt", CCLabelTTF*, this->m_pLabelTTFAtt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDef", CCLabelTTF*, this->m_pLabelTTFDef);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoLv", CCLabelTTF*, this->m_pLabelTTFEvoLv);

	return false;
}

bool CcbEvoInfoFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEvoInfoFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEvoInfoFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEvoInfoFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEvoInfoFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbEvoInfoFrameLayer::loadData(uint32 evoId)
{
    EvolveConfig::STC_EVOLVE_CONFIG* cfg = GET_CONFIG_STC(EvolveConfig, evoId);
    if (!cfg) {
        return;
    }
    //阶级}
    CCString* str = CCString::createWithFormat("进阶 +%d", cfg->byLv);
    m_pLabelTTFEvoLv->setString(str->getCString());
    //需要等级}
    str->initWithFormat("%d", cfg->wPetLv);
    m_pLabelTTFPetLv->setString(str->getCString());
    //icon
//    str->initWithFormat("ccbresources/12monthdate/pet.evo.enhance/pic_enhance_icon_%d.png", cfg->byIcon);
//    CCTexture2D* icon = CCTextureCache::sharedTextureCache()->addImage(str->getCString());
//    if (icon) {
//        m_pSpriteIcon->setTexture(icon);
//    }
    //技能名}
    uint32 passSkillId = cfg->dwAddSkillId1;// + cfg->dwAddSkillId2;
    std::string name = "";
    if (passSkillId / E_UNITE_BASE_FABIO == E_SKILL_TYPE_PASSIVE) {
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *pCfg = GET_CONFIG_STC(PassiveSkillConfig, passSkillId);
        if (pCfg) {
            name = pCfg->strName;//ConfigGet::GetSkillIconByIndexID(pCfg->wIcon);
        }
    }
    else if(passSkillId / E_UNITE_BASE_FABIO == E_SKILL_TYPE_TALENT)
    {
        TalentConfig::STC_TALENT_CONFIG *pCfg = GET_CONFIG_STC(TalentConfig, passSkillId);
        if (pCfg) {
            name = pCfg->strName;//ConfigGet::GetSkillIconByIndexID(pCfg->dwIcon);
        }
    }
    m_pLabelTTFSkillName->setString(name.c_str());
    
    //下次进阶}
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(CPetCtrl::Get()->GetEvolvePet());
    if (evoId % 100 == pet->GetbyEvolveLv() + 1) {
        m_pSpriteNext->setVisible(true);
    }
    else
    {
        m_pSpriteNext->setVisible(false);
    }
    
    //HP
    str->initWithFormat("+ %d", cfg->dwAddHP);
    m_pLabelTTFHp->setString(str->getCString());
    //DEF
    str->initWithFormat("+ %d", cfg->dwAddCDEF);
    m_pLabelTTFDef->setString(str->getCString());
    //ATT
    str->initWithFormat("+ %d", cfg->dwAddCATK);
    m_pLabelTTFAtt->setString(str->getCString());
    //REV
    str->initWithFormat("+ %d", cfg->dwAddREV);
    m_pLabelTTFRev->setString(str->getCString());
}







