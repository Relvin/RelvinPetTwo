#include "CcbArenaBattleListLayer.h"
#include "CcbManager.h"
#include "ArenaDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "CcbPetIcon.h"
#include "GameSession.h"
#include "Role.h"
#include "CCScrollButton.h"
#include "GuideData.h"
#include "SystemMessage.h"
#include "ConfigGet.h"
#include "FlyTextLayer.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "GuideBtnPos.h"
#include "CcbItemIconLayer.h"
#include "CcbJumpTipLayer.h"

CcbArenaBattleListLayer::CcbArenaBattleListLayer():
m_pSpriteCrown (NULL),
m_pLabelTTFName (NULL),
m_pLabelTTFRank (NULL),
m_pControlButtonBattle (NULL),
//m_pLabelTTFRankWin (NULL),
//m_pLabelTTFRankLose (NULL),
//m_pLabelTTFMoney (NULL),
//m_pLabelTTFReputation (NULL),
//m_pLabelTTFDayReputation (NULL),
m_pLabelFightScore (NULL),
m_pNodeUserteam(NULL),
m_pLabelTTFUserLv(NULL),
m_ClipRect(0,0,0,0)
{
    
}

CcbArenaBattleListLayer::~CcbArenaBattleListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteCrown);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRank);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBattle);
//	CC_SAFE_RELEASE_NULL(m_pLabelTTFRankWin);
//	CC_SAFE_RELEASE_NULL(m_pLabelTTFRankLose);
//	CC_SAFE_RELEASE_NULL(m_pLabelTTFMoney);
//	CC_SAFE_RELEASE_NULL(m_pLabelTTFReputation);
//	CC_SAFE_RELEASE_NULL(m_pLabelTTFDayReputation);
    CC_SAFE_RELEASE_NULL(m_pLabelFightScore);
    CC_SAFE_RELEASE_NULL(m_pNodeUserteam);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFUserLv);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaBattleListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaBattleListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaBattleListLayer", CcbArenaBattleListLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_fight_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaBattleListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    
	return true;
}

void CcbArenaBattleListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等.}
    setTouchEnabled(true);
    this->updateLayerInfo();
}

void CcbArenaBattleListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        if (m_localTag == CArenaDataMgr::Get()->GetBattleList().size() - 1) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonBattle, GuideBtnPos::E_JJC_LAST);
        }
    }
//    this->runAction(
//                    CCSequence::create(
//                                        CCDelayTime::create(0.1f),
//                                        CCCallFunc::create(this, callfunc_selector(CcbArenaBattleListLayer::addGuideLayer)),
//                                        NULL
//                                        )
//                    );
    
    
}

void CcbArenaBattleListLayer::addGuideLayer() {

}

void CcbArenaBattleListLayer::onExit()
{
	CCLayer::onExit();
}

void CcbArenaBattleListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaBattleListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCrown", CCSprite*, this->m_pSpriteCrown);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRank", CCLabelTTF*, this->m_pLabelTTFRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBattle", CCScrollButton*, this->m_pControlButtonBattle);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRankWin", CCLabelTTF*, this->m_pLabelTTFRankWin);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRankLose", CCLabelTTF*, this->m_pLabelTTFRankLose);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMoney", CCLabelTTF*, this->m_pLabelTTFMoney);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFReputation", CCLabelTTF*, this->m_pLabelTTFReputation);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDayReputation", CCLabelTTF*, this->m_pLabelTTFDayReputation);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelFightScore", CCLabelTTF*, this->m_pLabelFightScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeUserteam", CCNode*, this->m_pNodeUserteam);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFUserLv", CCLabelTTF*, this->m_pLabelTTFUserLv);
    
	return false;
}

bool CcbArenaBattleListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaBattleListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaBattleListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaBattleListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBattle", CcbArenaBattleListLayer::onPressControlButtonBattle);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaBattleListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbArenaBattleListLayer::onPressControlButtonBattle(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    ARENA_BATTLE_LIST_INFO tempInfo;
    if (m_byType == E_ARENA_NOMALE)
    {
        CRole* role = CGameSession::GetRole();
        if(role->GetbyArenaUseCnt() == 0){
            onBuyUse();
            return;
        }
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        g_ArenaData->setMyPreRank(CArenaDataMgr::Get()->GetPlayerInfo().dwMaxRank);
        tempInfo = CArenaDataMgr::Get()->GetBattleList()[m_localTag];
        CGameSession::SendArenaBattle(tempInfo.dwUserId, tempInfo.dwRank);
        //CCLOG("挑战");`

    }
    else if(m_byType == E_ARENA_RANK)
    {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        tempInfo = CArenaDataMgr::Get()->GetRankList()[m_localTag];
        CGameSession::SendArenaLearn(tempInfo.dwUserId, tempInfo.dwRank);
        //CCLog("切磋");
    }
    else
    {
        PetLoadingLayer::sharedLayer()->End();
    }
}

void CcbArenaBattleListLayer::loadData(int localTag, uint8 byType)
{
    m_localTag = localTag;
    m_byType = byType;
}

void CcbArenaBattleListLayer::updateLayerInfo()
{
    ARENA_BATTLE_LIST_INFO tempInfo;
    CCString *str = CCString::create("");
    if (m_byType == E_ARENA_NOMALE) {
        tempInfo = CArenaDataMgr::Get()->GetBattleList()[m_localTag];
        
        //        m_pLabelTTFRankWin->getParent()->setVisible(false);
        //        m_pLabelTTFReputation->getParent()->setVisible(true);
        
        //声望}
        //        str->initWithFormat("%d", tempInfo.dwGetReputation);
        //        m_pLabelTTFReputation->setString(str->getCString());
        //金币}
        //        str->initWithFormat("%d", tempInfo.dwGetMoney);
        //        m_pLabelTTFMoney->setString(str->getCString());
        //每日声望}
        //        ArenaRewardConfig::STC_ARENA_REWARD_CONFIG* cfg = GET_CONFIG_STC(ArenaRewardConfig, tempInfo.byGroupId);
        //        if (cfg) {
        //            str->initWithFormat("%d", cfg->dwReputationMax);
        //            m_pLabelTTFDayReputation->setString(str->getCString());
        //        }
        
        CRole* role = CGameSession::GetRole();
        if (role->GetdwAccountId() == tempInfo.dwUserId)
        {
            m_pControlButtonBattle->setEnabled(false);
        }
        else
        {
            m_pControlButtonBattle->setEnabled(true);
        }
        if (role->GetbyArenaUseCnt() == 0) {
            m_pControlButtonBattle->setTitleForState(CCString::create(GET_STR(Str_buy_cnt)), CCControlStateNormal);
        }
        else{
            m_pControlButtonBattle->setTitleForState(CCString::create(GET_STR(Str_tiaozhan)), CCControlStateNormal);
        }
    }
    else if(m_byType == E_ARENA_RANK){
        tempInfo = CArenaDataMgr::Get()->GetRankList()[m_localTag];
        //胜}
        //        str->initWithFormat("%d", tempInfo.dwWinCnt);
        //        m_pLabelTTFRankWin->setString(str->getCString());
        //负}
        //        str->initWithFormat("%d", tempInfo.dwLostCnt);
        //        m_pLabelTTFRankLose->setString(str->getCString());
        
        //        m_pLabelTTFRankWin->getParent()->setVisible(true);
        //        m_pLabelTTFReputation->getParent()->setVisible(false);
    }
    
    
    //名字}
    m_pLabelTTFName->setString(tempInfo.strName.c_str());
    //排名}
    str->initWithFormat("%d %s", tempInfo.dwRank,GET_STR(Str_Place));
    m_pLabelTTFRank->setString(str->getCString());
    
    str->initWithFormat("%d",tempInfo.dwFightScore);
    m_pLabelFightScore->setString(str->getCString());
    
    str->initWithFormat("%s%d",SB_Lv,tempInfo.wRoleLv);
    m_pLabelTTFUserLv->setString(str->getCString());
    
    CcbItemIconLayer *pItemIcon = NULL;
    for (int i = 0; i < 6; i++) {
        pItemIcon = (CcbItemIconLayer *)m_pNodeUserteam->getChildByTag(i);
        if (i >= tempInfo.m_VecTeam.size()) {
            if (pItemIcon) {
                pItemIcon->setVisible(false);
            }
            continue;
        }
        if (!pItemIcon) {
            pItemIcon = (CcbItemIconLayer *)CcbManager::sharedManager()->LoadCcbItemIconLayer(this);
            if (i == 0) {
                pItemIcon->setScale(0.9f);
            }
            else
            {
                pItemIcon->setScale(0.7f);
            }
            m_pNodeUserteam->addChild(pItemIcon);
            pItemIcon->setClipRect(m_ClipRect);
            pItemIcon->setTag(i);
            pItemIcon->setAnchorPoint(ccp(0, 0));
            if (i > 0) {
                pItemIcon->setPosition(ccp((pItemIcon->getContentSize().width + 2) * (0.9 + 0.7 * (i - 1)), 0));
            }
            else
            {
                pItemIcon->setPosition(CCPointZero);
            }
            
        }
        pItemIcon->setVisible(true);
        pItemIcon->loadIndexData(tempInfo.m_VecTeam[i].dwPetIndex);
        pItemIcon->hideName();
        pItemIcon->showLv(tempInfo.m_VecTeam[i].byPetLv);
        pItemIcon->showStarLv();
    }
    
    //icon
    //    m_pLayerPetIcon->setPetId(tempInfo.wPhoto);
    //皇冠}
    if (tempInfo.dwRank > 3) {
        m_pSpriteCrown->setVisible(false);
    } else {
        str->initWithFormat("ccbresources/12monthdate/arena/pic_crown%d.png", tempInfo.dwRank);
        CCTexture2D* t2d = CCTextureCache::sharedTextureCache()->addImage(str->getCString());
        if (t2d) {
            m_pSpriteCrown->setTexture(t2d);
            m_pSpriteCrown->setVisible(true);
        }
    }
}

void CcbArenaBattleListLayer::setClipRect(CCRect rect)
{
    m_ClipRect = rect;
    m_pControlButtonBattle->setClipRect(rect);
    
}


void CcbArenaBattleListLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendBuyAreanPoint();
}

void CcbArenaBattleListLayer::onBuyUse()
{
    uint8 buyCnt = g_ArenaData->getBuyUseCnt();
    VipShowConfig::STC_VIP_SHOW_CONFIG* vipCfg = GET_CONFIG_STC(VipShowConfig, CGameSession::GetRole()->GetbyVipLv());
    if (!vipCfg || vipCfg->wArenaBuyMax <= buyCnt) {
        //购买次数已用完
//        FlyTextLayer::showTips(GET_STR(Str_vip_need_up));
        CShowJumpTip::Get()->Show(E_VIP_NOT_ENOUGH);
        return;
    }
//    ArenaTimeConfig::STC_CONFIG_ARENA_TIME* cfg = GET_CONFIG_STC(ArenaTimeConfig, buyCnt+1);
    VipBuyConfig::STC_CONFIG_VIP_BUY* pVipBuyCfg = GET_CONFIG_STC(VipBuyConfig, buyCnt+1);
    if (pVipBuyCfg) {
        CCString* str = CCString::createWithFormat(GET_STR(Str_sure_buy_arena_point), pVipBuyCfg->wArena);
        SystemMessage::showSystemMessage(1, CCDirector::sharedDirector()->getRunningScene(), str->getCString(), this);
    }
}

