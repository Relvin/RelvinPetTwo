#include "CcbBattleTeamShowLayer.h"
//#include "CcbManager.h"
#include "ConfigGet.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "Team.h"
#include "CcbPetIcon.h"
#include "BackCtrl.h"
#include "TeamCtrl.h"
#include "ResourceStringClient.h"
#include "CcbPetShowLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbBattleTeamShowLayer::~CcbBattleTeamShowLayer()
{
    CC_SAFE_RELEASE_NULL(m_pSpriteLeader);
    CC_SAFE_RELEASE_NULL(m_pLayerM6);
    CC_SAFE_RELEASE_NULL(m_pLayerM1);
    CC_SAFE_RELEASE_NULL(m_pLayerM2);
    CC_SAFE_RELEASE_NULL(m_pLayerM3);
    CC_SAFE_RELEASE_NULL(m_pLayerM4);
    CC_SAFE_RELEASE_NULL(m_pLayerM5);
    CC_SAFE_RELEASE_NULL(m_pControlButtonTeam);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderDes);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderName);

    CC_SAFE_RELEASE_NULL(m_pLabelTTFTeamId);
}

//-- copy this to CcbManager 
/*
//CcbManager.h


//CcbManager.cpp

*/


bool CcbBattleTeamShowLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBattleTeamShowLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbBattleTeamShowLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbBattleTeamShowLayer::onExit()
{
	CCLayer::onExit();
}

void CcbBattleTeamShowLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBattleTeamShowLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLeader", CCSprite*, this->m_pSpriteLeader);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerM6", CCLayer*, this->m_pLayerM6);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerM1", CCLayer*, this->m_pLayerM1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerM2", CCLayer*, this->m_pLayerM2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerM3", CCLayer*, this->m_pLayerM3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerM4", CCLayer*, this->m_pLayerM4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerM5", CCLayer*, this->m_pLayerM5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTeam", CCControlButton*, this->m_pControlButtonTeam);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderDes", CCLabelTTF*, this->m_pLabelTTFLeaderDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderName", CCLabelTTF*, this->m_pLabelTTFLeaderName);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTeamId", CCLabelTTF*, this->m_pLabelTTFTeamId);
	return false;
}

bool CcbBattleTeamShowLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbBattleTeamShowLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler CcbBattleTeamShowLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBattleTeamShowLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTeam", CcbBattleTeamShowLayer::onPressControlButtonTeam);
	return NULL;
}
void CcbBattleTeamShowLayer::onPressControlButtonTeam(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    BackCtrl::InsertNextScene(kTeamScene);
}


// Inhert CCNodeLoaderListener
void CcbBattleTeamShowLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pBossIcon[0] = dynamic_cast<CcbPetIcon*>(m_pLayerM1);
    m_pBossIcon[1] = dynamic_cast<CcbPetIcon*>(m_pLayerM2);
    m_pBossIcon[2] = dynamic_cast<CcbPetIcon*>(m_pLayerM3);
    m_pBossIcon[3] = dynamic_cast<CcbPetIcon*>(m_pLayerM4);
    m_pBossIcon[4] = dynamic_cast<CcbPetIcon*>(m_pLayerM5);
    m_pBossIcon[5] = dynamic_cast<CcbPetIcon*>(m_pLayerM6);

    CcbPetShowLayer::m_bIsChangePetEnable = false;
}

//static const char* teamName[] = {"qqqqqqqqqqqqq队伍一","队伍二","队伍三","队伍四","队伍五","队伍六"};

#pragma mark Public Method
void CcbBattleTeamShowLayer::SetTeamInfo(CTeam *teamInfo)
{
    m_team = teamInfo;
    int cnt = teamInfo->getarrPetObId().size();

    CCPoint leaderPos = m_pBossIcon[teamInfo->getbyLeaderSite()-1]->getPosition();
    m_pSpriteLeader->setPosition(leaderPos);
    
    int j = 0;
    for (int i = 1; i < cnt; i++) {
        if (teamInfo->getarrPetObId()[i] != 0) {
            CPet* pet = CPetCtrl::Get()->GetPetByObjId(teamInfo->getarrPetObId()[i]);

            if (pet && pet->GetObjId() != 0) {
                m_pBossIcon[j]->setPetObjId(pet->GetObjId());
                m_pBossIcon[j]->loadObjData();
                m_pBossIcon[j]->setBtnEnable(true);
            }
        }
        j++;
    }

    
//    m_pLabelTTFTeamId->setString(teamName[teamInfo->getbyTeamId()]);
    uint8 byTeamId = teamInfo->getbyTeamId();
    m_pLabelTTFTeamId->setString(CCString::createWithFormat("%s%s", GET_STR(Str_team), GET_STR(Str_one + byTeamId))->getCString());
    //队长技能}
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG* pConfig = CTeamCtrl::GetTeamLeaderSkill((uint8)teamInfo->getbyTeamId());
    if (!pConfig) {
        return;
    }
    m_pLabelTTFLeaderName->setString(pConfig->strName.c_str());
    m_pLabelTTFLeaderDes->setString(pConfig->strDes.c_str());
}







