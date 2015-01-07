#include "CcbMainTeamLayer.h"
#include "CcbManager.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "UISupport.h"
#include "GuideBtnPos.h"
#include "GuideData.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbMainTeamLayer::~CcbMainTeamLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerMember_1);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_2);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_3);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_4);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_5);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_6);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbMainTeamLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbMainTeamLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbMainTeamLayer", CcbMainTeamLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/main_petcard.ccb]", [ccb/main_petcard.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/mainteam.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbMainTeamLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbMainTeamLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerMember_3, GuideBtnPos::E_MAIN_TEAM_TWO);
        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerMember_5, GuideBtnPos::E_MAIN_TEAM_THREE);
    }
}

void CcbMainTeamLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbMainTeamLayer::onExit()
{
	CCLayer::onExit();
}

void CcbMainTeamLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbMainTeamLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_1", CcbMainPetCardLayer*, this->m_pLayerMember_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_2", CcbMainPetCardLayer*, this->m_pLayerMember_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_3", CcbMainPetCardLayer*, this->m_pLayerMember_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_4", CcbMainPetCardLayer*, this->m_pLayerMember_4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_5", CcbMainPetCardLayer*, this->m_pLayerMember_5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_6", CcbMainPetCardLayer*, this->m_pLayerMember_6);

	return false;
}

bool CcbMainTeamLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbMainTeamLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbMainTeamLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbMainTeamLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbMainTeamLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_mapMember.clear();
    m_wTeamId = -1;
    m_mapMember[1] = m_pLayerMember_1;
    m_mapMember[2] = m_pLayerMember_2;
    m_mapMember[3] = m_pLayerMember_3;
    m_mapMember[4] = m_pLayerMember_4;
    m_mapMember[5] = m_pLayerMember_5;
    m_mapMember[6] = m_pLayerMember_6;
}

void CcbMainTeamLayer::setTeamId(uint16 wTeamId)
{
    m_wTeamId = wTeamId;
    loadData();
}

void CcbMainTeamLayer::loadData()
{
    CTeam *team = CTeamCtrl::GetTeamByObjId(m_wTeamId);
    if (!team) {
        return;
    }
    int cnt = team->getarrPetObId().size();
    int count = 0;
    
    for (int i = 1; i < cnt; i++) {
        if (team->getarrPetObId()[i]) {
            m_mapMember[i]->setPetObjIdAndSite(team->getarrPetObId()[i], i);
            if (i == team->getbyLeaderSite()) {
                m_mapMember[i]->setIsLeader(true);
            }
            count++;
        }
    }
    
    std::vector<uint8> arrLockMemSite;
    
    //当前站位上限（按1-3-5-2-4-6来解锁）}
    int teamSize = CTeamCtrl::getTeamMemberSize();
    //1-3-5
    for (int i = 0; i < 3; i++) {
        uint8 site = i*2 + 1;
        if (team->getarrPetObId()[site]) {
            continue;
        }
        count++;
        m_mapMember[site]->setPetObjIdAndSite(team->getarrPetObId()[site], site);
        if (!team->getarrPetObId()[site] && count > teamSize){
            m_mapMember[site]->setIsLock(true);
            arrLockMemSite.push_back(site);
            continue;
        }
    }
    //2-4-6
    for (int i = 0; i < 3; i++) {
        uint8 site = i*2 + 2;
        if (team->getarrPetObId()[site]) {
            continue;
        }
        count++;
        m_mapMember[site]->setPetObjIdAndSite(team->getarrPetObId()[site], site);
        if (!team->getarrPetObId()[site] && count > teamSize){
            m_mapMember[site]->setIsLock(true);
            arrLockMemSite.push_back(site);
            continue;
        }
    }
    
    if (arrLockMemSite.size() == 0) {
        return;
    }
    
    int lockCnt = 2;
    std::string arrLockPath[3];
    arrLockPath[0] = "ccbresources/12monthdate/home/pet_card_lock_10.png";
    arrLockPath[1] = "ccbresources/12monthdate/home/pet_card_lock_18.png";
    arrLockPath[2] = "ccbresources/12monthdate/home/pet_card_lock_22.png";
    for (int i = arrLockMemSite.size() - 1; i >= 0; i--) {
        CcbMainPetCardLayer* mem = m_mapMember[arrLockMemSite[i]];
        if (!mem) {
            continue;
        }
        CCSprite* sprite = CCSprite::create(arrLockPath[lockCnt].c_str());
        sprite->setPosition(ccp(getWidth(mem)*0.5, getHeight(mem)*0.5));
        sprite->setAnchorPoint(ccp(0.5, 0.5));
        mem->addChild(sprite, 10);
        mem->hideAll();
        lockCnt--;
        if (lockCnt < 0) {
            break;
        }
    }

}







