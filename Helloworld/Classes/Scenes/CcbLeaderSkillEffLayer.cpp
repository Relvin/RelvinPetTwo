#include "CcbLeaderSkillEffLayer.h"
//#include "CcbManager.h"
#include "MusicCtrl.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "ConfigGet.h"
#include "TeamCtrl.h"
#include "Team.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbLeaderSkillEffLayer::~CcbLeaderSkillEffLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpritePet);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFSkillName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSkillDes);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbLeaderSkillEffLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbLeaderSkillEffLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbLeaderSkillEffLayer", CcbLeaderSkillEffLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_ani.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbLeaderSkillEffLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbLeaderSkillEffLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbLeaderSkillEffLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbLeaderSkillEffLayer::onExit()
{
	CCLayer::onExit();
}

void CcbLeaderSkillEffLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbLeaderSkillEffLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet", CCSprite*, this->m_pSpritePet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSkillName", CCLabelTTF*, this->m_pLabelTTFSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSkillDes", CCLabelTTF*, this->m_pLabelTTFSkillDes);
	return false;
}

bool CcbLeaderSkillEffLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbLeaderSkillEffLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "removeSelf", CcbLeaderSkillEffLayer::removeSelf);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "playVoice", CcbLeaderSkillEffLayer::playVoice);
	return NULL;
}

SEL_MenuHandler CcbLeaderSkillEffLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbLeaderSkillEffLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbLeaderSkillEffLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}


void CcbLeaderSkillEffLayer::loadData()
{
    uint32 dwLeaderObjId = CTeamCtrl::GetCurTeam()->getarrPetObId()[CTeamCtrl::GetCurTeam()->getbyLeaderSite()];
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(dwLeaderObjId);
    if (!pet) {
        return;
    }
    //原画}
    m_pSpritePet->setTexture(CPetCtrl::Get()->GetPetBattleLeaderIconTexture(pet->GetwIndex()));
    
    //技能名}
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG *leaderCfg = GET_CONFIG_STC(LeaderSkillConfig, pet->GetwLeaderSkillId());
    if (!leaderCfg) {
        m_pLabelTTFSkillName->setString("");
        return;
    }
//    m_pLabelTTFSkillName->setDimensions(CCSizeMake(25, 0));
    m_pLabelTTFSkillName->setString(leaderCfg->strName.c_str());
    m_pLabelTTFSkillName->setEnableStroke(ccBLACK, 1.5);
    
    m_pLabelTTFSkillDes->setString(leaderCfg->strDes.c_str());
    
}

void CcbLeaderSkillEffLayer::removeSelf(cocos2d::CCNode* pNode)
{
    this->setVisible(false);
    removeFromParentAndCleanup(true);
}

void CcbLeaderSkillEffLayer::playVoice(cocos2d::CCNode* pNode)
{
    uint32 dwLeaderObjId = CTeamCtrl::GetCurTeam()->getarrPetObId()[CTeamCtrl::GetCurTeam()->getbyLeaderSite()];
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(dwLeaderObjId);
    if (pet) {
        PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
        if (petCfg) {
            CMusicCtrl::PlayEffect(GET_PET_SOUND(petCfg->wSoundLeader));
        }
    }
}



