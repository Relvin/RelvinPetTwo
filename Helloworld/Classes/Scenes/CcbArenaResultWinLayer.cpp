#include "CcbArenaResultWinLayer.h"
#include "CcbManager.h"
#include "ArenaDataMgr.h"
#include "PacketDataMgr.h"
#include "CcbItemIconLayer.h"
#include "GameSession.h"
#include "GuideData.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "CcbShareFrameLayer.h"
#include "ResourceStringClient.h"
#include "BackCtrl.h"
#include <algorithm>
#include "GlobalData.h"
#include "GuideBtnPos.h"
#include "CcbArenaResultHighestLayer.h"
#include "ItemDataMgr.h"
#include "ConfigData.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

#define SCROLL1TIME     1.0f
#define SCROLL2TIME     0.5f
#define SCROLL3TIME     0.5f
#define SCROLLTOUCHDELAY    1.f

CcbArenaResultWinLayer::~CcbArenaResultWinLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRank);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFReputation);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCoin);
	CC_SAFE_RELEASE_NULL(m_pControlButtonExtraReward);
	CC_SAFE_RELEASE_NULL(m_pLayerScroll_1);
	CC_SAFE_RELEASE_NULL(m_pLayerScroll_2);
	CC_SAFE_RELEASE_NULL(m_pLayerScroll_3);
    CC_SAFE_RELEASE_NULL(m_pLayerRewardParent);
    CC_SAFE_RELEASE_NULL(m_pControlButtonShare);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFMaxRank);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNums);
    CC_SAFE_RELEASE_NULL(m_pNodeShareReward);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaResultWinLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaResultWinLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaResultWinLayer", CcbArenaResultWinLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/header_back2.ccb]", [ccb/header_back2.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/item_icon.ccb]", [ccb/item_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_result_win.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaResultWinLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
    for (int i = 0; i < 3; i++)
    {
        m_isStartRoll[i] = false;
    }
    m_isEndRoll = false;
	return true;
}

void CcbArenaResultWinLayer::onEnter()
{
	CCLayer::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CcbArenaResultWinLayer::listenToBackFromNotification), "SHARE_SUCCESS", NULL);
    CGameSession::GetRole()->Attach(this);
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
//    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_arena_win));
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Bgm_arena));
    uint32 dwMaxRankRole = CArenaDataMgr::Get()->GetResultInfo().dwMaxRankDollar;
    if (dwMaxRankRole != 0) {
        CcbArenaResultHighestLayer* node = dynamic_cast<CcbArenaResultHighestLayer*>(CcbManager::sharedManager()->LoadCcbArenaResultHighestLayer());
        node->setDelegate(this);
        addChild(node, 99);
    }
    else
    {
        this->StopRoll();
    }
    this->listenToBackFromNotification(NULL);
}

void CcbArenaResultWinLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    RESULT_INFO_ALL showInfo = CArenaDataMgr::Get()->GetResultInfo();
    if (showInfo.dwItemId[0] != 0)
    {
        StartRoll();
    }
//    this->runAction(
//                    CCSequence::create(
//                                        CCDelayTime::create(0.1f),
//                                        CCCallFunc::create(this, callfunc_selector(CcbArenaResultWinLayer::addGuideLayer)),
//                                        NULL
//                                        )
//                    );
    
}

void CcbArenaResultWinLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonExtraReward, GuideBtnPos::E_JJC_EXTERN_REWARD);
        
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_5_JJC,
                                                 NULL
                                                 );
    }
    this->StopRoll();
}

void CcbArenaResultWinLayer::onExit()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "SHARE_SUCCESS");
    CGameSession::GetRole()->Detach(this);
	CCLayer::onExit();
}

void CcbArenaResultWinLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaResultWinLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRank", CCLabelTTF*, this->m_pLabelTTFRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFReputation", CCLabelTTF*, this->m_pLabelTTFReputation);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoin", CCLabelTTF*, this->m_pLabelTTFCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExtraReward", CCControlButton*, this->m_pControlButtonExtraReward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerScroll_1", CCLayer*, this->m_pLayerScroll_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerScroll_2", CCLayer*, this->m_pLayerScroll_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerScroll_3", CCLayer*, this->m_pLayerScroll_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRewardParent", CCLayer*, this->m_pLayerRewardParent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShare", CCControlButton*, this->m_pControlButtonShare);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMaxRank", CCLabelTTF*, this->m_pLabelTTFMaxRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNums", CCLabelTTF*, this->m_pLabelTTFNums);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeShareReward", CCNode*, this->m_pNodeShareReward);
	return false;
}

bool CcbArenaResultWinLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaResultWinLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaResultWinLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaResultWinLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExtraReward", CcbArenaResultWinLayer::onPressControlButtonExtraReward);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShare", CcbArenaResultWinLayer::onPressControlButtonShare);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaResultWinLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    schedule(schedule_selector(CcbArenaResultWinLayer::onUpdate));
    
    RESULT_INFO_ALL showInfo = CArenaDataMgr::Get()->GetResultInfo();
    m_pLayerIcon->loadIndexData(showInfo.infoPersonal[0].wLeaderId);
    m_pLayerIcon->showIconOnly();
    m_pLayerIcon->setBtnEnable(false);
    
    m_pLabelTTFName->setString(showInfo.infoPersonal[0].strName.c_str());
    
    m_pControlButtonExtraReward->setVisible(false);
    
    m_pControlButtonShare->setTouchPriority(-1);
    
    char szTemp[256] = "\0";

    //排行}
    sprintf(szTemp, "%d", CArenaDataMgr::Get()->GetResultInfo().infoPersonal[0].dwRank);
    m_pLabelTTFRank->setString(szTemp);
    //声望}
    sprintf(szTemp, "%d", CArenaDataMgr::Get()->GetResultInfo().dwReputation);
    m_pLabelTTFReputation->setString(szTemp);
    //金币}
    sprintf(szTemp, "%d", CArenaDataMgr::Get()->GetResultInfo().dwCoin);
    m_pLabelTTFCoin->setString(szTemp);
    
    memset(szTemp, '\0', sizeof(szTemp));
    sprintf(szTemp, "%d", g_ArenaData->getMyPreRank() - showInfo.infoPersonal[0].dwRank);
    m_pLabelTTFNums->setString(szTemp);
    
//        m_pLabelTTFMaxRank->getParent()->setVisible(true);
//        m_pLabelTTFMaxRank->setString(CCString::createWithFormat("%d",dwMaxRankRole)->getCString());
//    }
//    else
//    {
//        m_pLabelTTFMaxRank->getParent()->setVisible(false);
//    }
    
    m_pControlButtonExtraReward->setEnabled(false);
    if (showInfo.dwItemId[0] == 0)
    {
        m_pLayerRewardParent->setVisible(false);
    }
    else
    {
        m_pLayerRewardParent->setVisible(true);
    }
    
    if (GlobalData::shared()->getShareSwitch()) {
        m_pControlButtonShare->setVisible(false);
    }
}

void CcbArenaResultWinLayer::onPressControlButtonExtraReward(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_pControlButtonExtraReward->setEnabled(false);
    StopRoll();
}

void CcbArenaResultWinLayer::onPressControlButtonShare(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    CCLayer* pLayer = (CCLayer*)CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0);
    CcbShareFrameLayer::showShare(pLayer, Str_share_text_pvp_win);
    
    if (
        CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV &&
        CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_SYS_GUIDE_END_JJC
        ) {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("arena_guide_end");
#endif
    }
}

void CcbArenaResultWinLayer::onUpdate(float delta)
{
    if (m_pScrollView[0] && m_isStartRoll[0])
    {
        static float offY1 = 0;
        offY1 -= 11;
        if (offY1 < -540)
        {
            offY1 = 0;
        }
        m_pScrollView[0]->setContentOffset(ccp(0, offY1));
    }
    
    if (m_pScrollView[1] && m_isStartRoll[1])
    {
        static float offY2 = 0;
        offY2 -= 14;
        if (offY2 < -540)
        {
            offY2 = 0;
        }
        m_pScrollView[1]->setContentOffset(ccp(0, offY2));
    }
    
    if (m_pScrollView[2] && m_isStartRoll[2])
    {
        static float offY3 = 0;
        offY3 -= 18;
        if (offY3 < -540)
        {
            offY3 = 0;
        }
        m_pScrollView[2]->setContentOffset(ccp(0, offY3));
    }
}

void CcbArenaResultWinLayer::StartRoll()
{
    m_pControlButtonExtraReward->setEnabled(true);
    RandShowItem();
    
    for (int i = 0; i < 3; i++)
    {
        m_pNodeRewardItem[i] = CCNode::create();
        m_pScrollView[i] = CCScrollView::create();
        m_isStartRoll[i] = true;
    }
    m_pLayerScroll_1->addChild(m_pScrollView[0]);
    m_pLayerScroll_2->addChild(m_pScrollView[1]);
    m_pLayerScroll_3->addChild(m_pScrollView[2]);
    
    
    for ( int i = 0; i < 3; i++)
    {
        m_pNodeRewardItem[i]->setContentSize(CCSizeMake(m_pLayerScroll_1->getContentSize().width, 60 * 10));
        for (int k = 0; k < 10; k++)
        {
            CcbItemIconLayer* pItemIcon = (CcbItemIconLayer*)CcbManager::sharedManager()->LoadCcbItemIconLayer(this);
            pItemIcon->loadIndexData(m_ShowItem[i][k].dwIndex);
            pItemIcon->setPositionX(m_pLayerScroll_1->getContentSize().width * 0.5);
            pItemIcon->setPositionY(m_pLayerScroll_1->getContentSize().height * 0.5 + 60 * k);
            pItemIcon->showIconOnly();
            pItemIcon->setBtnEnable(false);
            m_pNodeRewardItem[i]->addChild(pItemIcon, 1, 100 + i * 10 + k);
        }
        
        m_pScrollView[i]->setPosition(0, 0);
        m_pScrollView[i]->setViewSize(m_pLayerScroll_1->getContentSize());
        m_pScrollView[i]->setBounceable(false);
        m_pScrollView[i]->setTouchEnabled(false);
        m_pScrollView[i]->setContainer(m_pNodeRewardItem[i]);
    }
}

void CcbArenaResultWinLayer::scheduleStopRoll(float cTime)
{
    this->StopRoll();
}

void CcbArenaResultWinLayer::StopRoll()
{
    this->runAction(CCSequence::create(CCDelayTime::create(SCROLL1TIME),
                                       CCCallFunc::create(this, callfunc_selector(CcbArenaResultWinLayer::StopScrollView1)),
                                       CCDelayTime::create(SCROLL2TIME),
                                       CCCallFunc::create(this, callfunc_selector(CcbArenaResultWinLayer::StopScrollView2)),
                                       CCDelayTime::create(SCROLL3TIME),
                                       CCCallFunc::create(this, callfunc_selector(CcbArenaResultWinLayer::StopScrollView3)),
                                       CCDelayTime::create(SCROLLTOUCHDELAY),
                                       CCCallFunc::create(this, callfunc_selector(CcbArenaResultWinLayer::EndRoll)),
                                       NULL));
}

void CcbArenaResultWinLayer::EndRoll()
{
    m_isEndRoll = true;
}

void CcbArenaResultWinLayer::StopScrollView1()
{
    m_isStartRoll[0] = false;
    m_pScrollView[0]->setContentOffsetInDuration(ccp(0,-540), 1);
    CcbItemIconLayer* pItemIcon = (CcbItemIconLayer*)m_pNodeRewardItem[0]->getChildByTag(109);
    if (pItemIcon)
    {
        RESULT_INFO_ALL showInfo = CArenaDataMgr::Get()->GetResultInfo();
        pItemIcon->showCnt(showInfo.dwItemCnt[0]);
    }
}

void CcbArenaResultWinLayer::StopScrollView2()
{
    m_isStartRoll[1] = false;
    m_pScrollView[1]->setContentOffsetInDuration(ccp(0,-540), 1);
    CcbItemIconLayer* pItemIcon = (CcbItemIconLayer*)m_pNodeRewardItem[1]->getChildByTag(119);
    if (pItemIcon)
    {
        RESULT_INFO_ALL showInfo = CArenaDataMgr::Get()->GetResultInfo();
        pItemIcon->showCnt(showInfo.dwItemCnt[1]);
    }
}

void CcbArenaResultWinLayer::StopScrollView3()
{
    m_isStartRoll[2] = false;
    m_pScrollView[2]->setContentOffsetInDuration(ccp(0,-540), 1);
    CcbItemIconLayer* pItemIcon = (CcbItemIconLayer*)m_pNodeRewardItem[2]->getChildByTag(129);
    if (pItemIcon)
    {
        RESULT_INFO_ALL showInfo = CArenaDataMgr::Get()->GetResultInfo();
        pItemIcon->showCnt(showInfo.dwItemCnt[2]);
    }
}

void CcbArenaResultWinLayer::RandShowItem()
{
    RankRewardConfig::STC_RANKREWARD_CONFIG* pConfig = GET_CONFIG_STC(RankRewardConfig, 1);
    if (pConfig)
    {
        RESULT_INFO_ALL showInfo = CArenaDataMgr::Get()->GetResultInfo();
        srand((unsigned)time(NULL));
        SHOW_ITEM_INFO tempInfo;
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 9; k++)
            {
                int index = rand() % 100;
                tempInfo.dwIndex = pConfig->dwShowItems[k];
                tempInfo.sort = index;
                
                m_ShowItem[i].push_back(tempInfo);
            }
            tempInfo.dwIndex = showInfo.dwItemId[i];
            tempInfo.sort = 999;
            m_ShowItem[i].push_back(tempInfo);
            sort(m_ShowItem[i].begin(), m_ShowItem[i].end(), less<SHOW_ITEM_INFO>());
        }
    }
}

void CcbArenaResultWinLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool CcbArenaResultWinLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbArenaResultWinLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_isEndRoll )
    {
        m_isEndRoll = false;
        BackCtrl::BacktoUpperScene();
    }
}

void CcbArenaResultWinLayer::dwShareCntChanged(uint32 dwShareCnt)
{
    this->listenToBackFromNotification(NULL);
}

void CcbArenaResultWinLayer::listenToBackFromNotification(cocos2d::CCObject *pObject)
{
    CRole* pRole = CGameSession::GetRole();
    if (!pRole || pRole->GetdwShareCnt() >= 3) {
        m_pNodeShareReward->setVisible(false);
        return;
    }
    
    ShareConfig::STC_SHARE_CONFIG* pShareConfig = GET_CONFIG_STC(ShareConfig, pRole->GetdwShareCnt() + 1);
    if (!pShareConfig) {
        m_pNodeShareReward->setVisible(false);
        return;
    }
    m_pNodeShareReward->setVisible(true);
    ((CCSprite *)m_pNodeShareReward->getChildByTag(0))->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetItemIconByIndex(pShareConfig->dwItemIndex).c_str()));
    ((CCLabelTTF*)m_pNodeShareReward->getChildByTag(1))->setString(CCString::createWithFormat("+%d",pShareConfig->dwItemCount)->getCString());
}
