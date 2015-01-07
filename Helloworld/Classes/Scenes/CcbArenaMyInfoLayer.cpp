#include "CcbArenaMyInfoLayer.h"
//#include "CcbManager.h"
#include "ArenaDataMgr.h"
#include "TeamCtrl.h"
#include "ConfigGet.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "Role.h"
#include "PetLoadingLayer.h"
#include "ResourceStringClient.h"
#include "GlobalData.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbArenaMyInfoLayer::~CcbArenaMyInfoLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerLeaderIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDoubleWinValue);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDoubleWin);
	CC_SAFE_RELEASE_NULL(m_pLabelTTF2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTF3);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRecords);
	CC_SAFE_RELEASE_NULL(m_pLabelTTF1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPlayerName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFGroupName);
    CC_SAFE_RELEASE_NULL(m_pSpriteRankBadge);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRank);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFArenaCnt);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaMyInfoLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaMyInfoLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaMyInfoLayer", CcbArenaMyInfoLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_myinform.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaMyInfoLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbArenaMyInfoLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
    CArenaDataMgr::Get()->SaveArenaMyInfoLayerPt(this);
}

void CcbArenaMyInfoLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaMyInfoLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
    CArenaDataMgr::Get()->SaveArenaMyInfoLayerPt(NULL);
}

void CcbArenaMyInfoLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaMyInfoLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerLeaderIcon", CcbPetIcon*, this->m_pLayerLeaderIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDoubleWinValue", CCLabelTTF*, this->m_pLabelTTFDoubleWinValue);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDoubleWin", CCLabelTTF*, this->m_pLabelTTFDoubleWin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF2", CCLabelTTF*, this->m_pLabelTTF2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF3", CCLabelTTF*, this->m_pLabelTTF3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRecords", CCLabelTTF*, this->m_pLabelTTFRecords);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF1", CCLabelTTF*, this->m_pLabelTTF1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPlayerName", CCLabelTTF*, this->m_pLabelTTFPlayerName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGroupName", CCLabelTTF*, this->m_pLabelTTFGroupName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRankBadge", CCSprite*, this->m_pSpriteRankBadge);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRank", CCLabelTTF*, this->m_pLabelTTFRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFArenaCnt", CCLabelTTF*, this->m_pLabelTTFArenaCnt);

	return false;
}

bool CcbArenaMyInfoLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaMyInfoLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaMyInfoLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaMyInfoLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaMyInfoLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CreateDlgData();
}

void CcbArenaMyInfoLayer::RefeashLayer()
{
    CreateDlgData();
}

void CcbArenaMyInfoLayer::CreateDlgData()
{
    char szTemp[256] = "";
    uint16 wIndex = (uint16)CArenaDataMgr::Get()->GetPlayerInfo().byGroupId;
    RankRewardConfig::STC_RANKREWARD_CONFIG* pConfig = GET_CONFIG_STC(RankRewardConfig, wIndex);
    //组名}
    if (pConfig)
    {
        m_pLabelTTFGroupName->setString(pConfig->strGroupName.c_str());
        ccColor3B ccc3NameColor;
        ccc3NameColor.r = (0xff << 16 & pConfig->dwcolor) >> 16;
        ccc3NameColor.g = (0xff << 8 & pConfig->dwcolor) >> 8;
        ccc3NameColor.b = 0xff & pConfig->dwcolor;
        m_pLabelTTFGroupName->setColor(ccc3NameColor);
    }
    else
    {
        m_pLabelTTFGroupName->setString(GET_STR(Str_no_arena_group));
        CCLOG("rankreward.csv error!");
        return;
    }
    
    //排行}
    sprintf(szTemp, "%d", CArenaDataMgr::Get()->GetPlayerInfo().dwRank);
    m_pLabelTTF1->setString(szTemp);
    
    //胜利失败场数}
    sprintf(szTemp, GET_STR(Str_xwin_xlose), CArenaDataMgr::Get()->GetPlayerInfo().dwWinCnt, CArenaDataMgr::Get()->GetPlayerInfo().dwLostCnt);
    m_pLabelTTF2->setString(szTemp);
    
    //声望}
    CRole* pRole = CGameSession::GetRole();
    sprintf(szTemp, "%d", pRole->GetdwReputation());
    m_pLabelTTF3->setString(szTemp);
    
    //玩家名字}
    m_pLabelTTFPlayerName->setString(pRole->GetstrUserName().c_str());
    
    m_pLabelTTFRank->setString(CCString::createWithFormat("%d",CArenaDataMgr::Get()->GetPlayerInfo().dwMaxRank)->getCString());
    
    //连胜}
    sprintf(szTemp, "%d", CArenaDataMgr::Get()->GetPlayerInfo().dwDoubleWin);
    m_pLabelTTFDoubleWinValue->setString(szTemp);
    
    //队长头像}
    m_pLayerLeaderIcon->setPetId(CTeamCtrl::GetCurTeamLeaderPetIndex());
    m_pLayerLeaderIcon->setBtnEnable(false);

    //徽章}
    CCTexture2D* pBadgeTexture = CCTextureCache::sharedTextureCache()->addImage(GET_ARENA_BADGE_PIC(pConfig->wBadge));
    m_pSpriteRankBadge->setTexture(pBadgeTexture);
    
    // 设置竞技点}
    int iArenaUseCnt = pRole->GetbyArenaUseCnt();
    if (m_pLabelTTFArenaCnt) {
        snprintf(szTemp, BUFFER_SIZE_64,  "%d/10", iArenaUseCnt);
        m_pLabelTTFArenaCnt->setString(szTemp);
    }
}

