#include "CcbDailyQuestRewardLayer.h"
#include "CcbManager.h"
#include "CcbDailyQuestRewardFrameLayer.h"
#include "CCScrollViewWithBar.h"
#include "ConfigGet.h"
#include "GameSession.h"
#include "EnumDefines.h"
#include "PacketDataMgr.h"
#include "UISupport.h"
#include "ResourceStringClient.h"
#include "Role.h"
#include "ResourceDefine.h"
#include "GlobalData.h"
#include "CcbShowGetLayer.h"
#include "MusicCtrl.h"
#include <algorithm>

#define NODEPARTICLETAG 5

CcbDailyQuestRewardLayer::~CcbDailyQuestRewardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFExtraAward);
	CC_SAFE_RELEASE_NULL(m_pLayerList);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFProcess);
	CC_SAFE_RELEASE_NULL(m_pSpriteBar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCompleteCount);
    CC_SAFE_RELEASE_NULL(m_pLayerTop);
    CC_SAFE_RELEASE_NULL(m_pLayerTop2);
    CC_SAFE_RELEASE_NULL(m_pLayerBottom);
    CC_SAFE_RELEASE_NULL(m_tableView);
    CC_SAFE_RELEASE_NULL(m_pNodeScoreBox);
    CC_SAFE_RELEASE_NULL(m_pNodeScore);
    CC_SAFE_RELEASE_NULL(m_pConrtolButtonDailyquest);
    CC_SAFE_RELEASE_NULL(m_pConrtolButtonAchieve);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJifen);
    CC_SAFE_RELEASE_NULL(m_pSpriteAchievetip);
    CC_SAFE_RELEASE_NULL(m_pSpriteDailyquesttip);
    CC_SAFE_RELEASE_NULL(m_pSpriteSelectframe);
    
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbDailyQuestRewardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbDailyQuestRewardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbDailyQuestRewardLayer", CcbDailyQuestRewardLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/dailyquest_reward.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbDailyQuestRewardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbDailyQuestRewardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
}

void CcbDailyQuestRewardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    
    m_tableView->reloadData();
    
    //    CCTableViewWithBar* ScrollBar = CCTableViewWithBar::create(m_tableView);
    //    ScrollBar->setPosition(CCPointZero);
    //    ScrollBar->setAnchorPoint(CCPointZero);
    //    m_pLayerList->addChild(ScrollBar);
}

void CcbDailyQuestRewardLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
}

void CcbDailyQuestRewardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbDailyQuestRewardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFExtraAward", CCLabelTTF*, this->m_pLabelTTFExtraAward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerList", CCLayer*, this->m_pLayerList);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFProcess", CCLabelTTF*, this->m_pLabelTTFProcess);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBar", CCSprite*, this->m_pSpriteBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCompleteCount", CCLabelTTF*, this->m_pLabelTTFCompleteCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTop", CCLayer*, m_pLayerTop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTop2", CCLayer*, m_pLayerTop2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, m_pLayerBottom);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeScoreBox", CCNode*, this->m_pNodeScoreBox);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeScore", CCNode*, this->m_pNodeScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pConrtolButtonDailyquest", CCControlButton*, this->m_pConrtolButtonDailyquest);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pConrtolButtonAchieve", CCControlButton*, this->m_pConrtolButtonAchieve);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJifen", CCLabelTTF*, this->m_pLabelTTFJifen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDailyquesttip", CCSprite*, this->m_pSpriteDailyquesttip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAchievetip", CCSprite*, this->m_pSpriteAchievetip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSelectframe", CCSprite*, this->m_pSpriteSelectframe);
	return false;
}

bool CcbDailyQuestRewardLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbDailyQuestRewardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbDailyQuestRewardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbDailyQuestRewardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressConrtolButtonDailyCallBack", CcbDailyQuestRewardLayer::onPressConrtolButtonDailyCallBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBox", CcbDailyQuestRewardLayer::onPressControlButtonBox);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbDailyQuestRewardLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pLayerTop2->setPositionY(getBottom(m_pLayerTop));
    
    m_pLayerList->setContentSize(CCSizeMake(getWidth(m_pLayerList),
                                                     CCDirector::sharedDirector()->getWinSize().height - getHeight(m_pLayerTop) - getHeight(m_pLayerTop2) - getHeight(m_pLayerBottom) + 5));
    m_pLayerList->setPositionY(getBottom(m_pLayerTop2) - m_pLayerList->getContentSize().height * 0.5);
    
    m_clitRect.origin = getWorldPos(m_pLayerList);
    m_clitRect.size = m_pLayerList->getContentSize();
    
    m_tableView = CCTableView::create(this, m_pLayerList->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->setDelegate(this);
    m_tableView->retain();
    
    m_tableView->setAnchorPoint(CCPointZero);
    m_tableView->setPosition(CCPointZero);
    m_pLayerList->addChild(m_tableView);
    
    m_SpriteBarSize = m_pSpriteBar->getContentSize();
    
    CCSprite *pSprite = NULL;
    for (int i = 0; i < 3; i++) {
        m_pNodeParticle[i] = CCNode::create();
        CCParticleSystemQuad* eff1 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/eff_jiangli_1.plist");
        CCParticleSystemQuad* eff2 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/eff_jiangli_2.plist");
        eff1->setPosition(CCPointZero);
        eff2->setPosition(CCPointZero);
        
        
        m_pNodeParticle[i]->addChild(eff1);
        m_pNodeParticle[i]->addChild(eff2);
        
        m_pNodeParticle[i]->setVisible(false);
        pSprite = (CCSprite *)m_pNodeScoreBox->getChildByTag(i);
        pSprite->addChild(m_pNodeParticle[i]);
        m_pNodeParticle[i]->setTag(NODEPARTICLETAG);
    }
    
    this->setLayerInfoByTab(GlobalData::shared()->getDailyLayerType());
}

void CcbDailyQuestRewardLayer::setLayerInfoByTab(uint8 byType)
{
    m_byCurType = byType;
    
    if (g_TaskData->GetAchieveAwardCount()) {
        m_pSpriteAchievetip->setVisible(true);
    } else {
        m_pSpriteAchievetip->setVisible(false);
    }
    
    if (g_TaskData->GetDailyAwardCount()) {
        m_pSpriteDailyquesttip->setVisible(true);
    } else {
        m_pSpriteDailyquesttip->setVisible(false);
    }
    
    if (byType == 0) {
        m_pSpriteSelectframe->setPosition(m_pConrtolButtonDailyquest->getPosition());
        m_pConrtolButtonDailyquest->setEnabled(false);
        m_pConrtolButtonAchieve->setEnabled(true);
        m_pNodeScore->setVisible(true);
        m_pLayerList->setContentSize(CCSizeMake(getWidth(m_pLayerList),
                                                CCDirector::sharedDirector()->getWinSize().height - getHeight(m_pLayerTop) - getHeight(m_pLayerTop2) - getHeight(m_pLayerBottom) + 5));
        m_pLayerList->setPositionY(getBottom(m_pLayerTop2)  - m_pLayerList->getContentSize().height * 0.5);
        this->CreateDailyQuestList();
        
        CRole *pRole = CGameSession::GetRole();
        uint32 dwScore = pRole->GetdwScore();
        
        CCSprite* pSprite = NULL;
        CCLabelTTF* pLabelTTF = NULL;
        DailyRewardConfig::STC_CONFIG_DAILYREWARD *pDailyRewardConfig = NULL;
        
        int nConfigScore = 0;
        for (int i = 0; i < 3; i++) {
            pDailyRewardConfig = GET_CONFIG_STC(DailyRewardConfig,i + 1);
            if (!pDailyRewardConfig) {
                continue;
            }
            nConfigScore = pDailyRewardConfig->dwNeedScore;
            if (dwScore >= nConfigScore) {
                m_pNodeParticle[i]->setVisible(true);
            }
            pSprite = (CCSprite *)m_pNodeScoreBox->getChildByTag(i);
            pLabelTTF = (CCLabelTTF *)pSprite->getChildByTag(1);
            pLabelTTF->setString(CCString::createWithFormat("%d%s",pDailyRewardConfig->dwNeedScore,GET_STR(Str_Score))->getCString());
            ((CCSprite *)pSprite->getChildByTag(3))->setVisible(false);
            
        }
        
        float fWidth = m_SpriteBarSize.width;
        if (dwScore < nConfigScore) {
            fWidth = dwScore / (float) nConfigScore * fWidth;
        }
        m_pSpriteBar->setTextureRect(CCRectMake(0, 0, fWidth, m_SpriteBarSize.height));
        m_pLabelTTFJifen->setString(CCString::createWithFormat("%d",pRole->GetdwScore())->getCString());
        
        
        for (int i = 0; i < CTaskDataMgr::Get()->getHadRewardId().size(); i++) {
            m_pNodeParticle[CTaskDataMgr::Get()->getHadRewardId()[i] - 1]->setVisible(false);
            pSprite = (CCSprite *)m_pNodeScoreBox->getChildByTag(CTaskDataMgr::Get()->getHadRewardId()[i] - 1);
            ((CCSprite *)pSprite->getChildByTag(3))->setVisible(true);
        }

    }
    else
    {
        m_pSpriteSelectframe->setPosition(m_pConrtolButtonAchieve->getPosition());
        m_pConrtolButtonDailyquest->setEnabled(true);
        m_pConrtolButtonAchieve->setEnabled(false);
        m_pNodeScore->setVisible(false);
        m_pLayerList->setContentSize(CCSizeMake(getWidth(m_pLayerList),
                                                CCDirector::sharedDirector()->getWinSize().height - getHeight(m_pLayerTop) - getHeight(m_pLayerTop2) - getHeight(m_pLayerBottom) + getHeight(m_pNodeScore) + 5));
        m_pLayerList->setPositionY(getBottom(m_pLayerTop2) + getHeight(m_pNodeScore)  - m_pLayerList->getContentSize().height * 0.5 - 10);
        
    }
    
    m_tableView->setViewSize(m_pLayerList->getContentSize());
    m_clitRect.origin = getWorldPos(m_pLayerList);
    m_clitRect.size = m_pLayerList->getContentSize();
    m_tableView->reloadData();
}

bool CcbDailyQuestRewardLayer::compare(const DAILY_QUEST_SHOW_INFO &p,const DAILY_QUEST_SHOW_INFO &q)
{
    if (p.info.byStatus < q.info.byStatus) {
        return true;
    }
    return false;
}

bool CcbDailyQuestRewardLayer::compare1(const DAILY_QUEST_SHOW_INFO &p, const DAILY_QUEST_SHOW_INFO &q)
{
    if (p.info.byStatus == 1 && p.info.byStatus > q.info.byStatus) {
        return true;
    }
    return false;
}

void CcbDailyQuestRewardLayer::CreateDailyQuestList()
{
    m_vecDailyQuestShowList.clear();
    m_nCompleteCount = 0;
    
    map<uint32, DAILY_QUEST_CONFIG> mapConfig;
    map<uint32, DAILY_QUEST_CONFIG>::iterator iter;
    mapConfig = GET_CONFIG_MAP(DailyQuestConfig);
    for (iter = mapConfig.begin(); iter != mapConfig.end(); iter++)
    {
        DAILY_QUEST_SHOW_INFO temp;
        
        temp.info.dwIndex = iter->first;
        temp.info.byStatus = g_TaskData->GetDailyQuestInfoByIndex(iter->first).byStatus;
        temp.info.dwCondition = g_TaskData->GetDailyQuestInfoByIndex(iter->first).dwCondition;
        
        temp.config.dwIndex = iter->second.dwIndex;
        temp.config.byType = iter->second.byType;
        temp.config.strTitle = iter->second.strTitle;
        temp.config.strDesc = iter->second.strDesc;
        temp.config.dwScore = iter->second.dwScore;
        temp.config.strNextScene = iter->second.strNextScene;
        temp.config.dwParam[0] = iter->second.dwParam[0];
        temp.config.dwParam[1] = iter->second.dwParam[1];
        
        temp.config.dwRewardID[0] = iter->second.dwRewardID[0];
        temp.config.dwRewardCnt[0] = iter->second.dwRewardCnt[0];
        
        if (temp.info.dwCondition > temp.config.dwParam[0])
        {
            temp.info.dwCondition = temp.config.dwParam[0];
        }
        
        if (temp.config.byType != 99)//Type 99 为额外奖励}
        {
            m_vecDailyQuestShowList.push_back(temp);
        }
        
        if (temp.info.byStatus == 2)
        {
            m_nCompleteCount++;
        }
        
        if (temp.config.byType == 99)
        {
            m_pLabelTTFExtraAward->setString(temp.config.strDesc.c_str());
        }
    }

    sort(m_vecDailyQuestShowList.begin(), m_vecDailyQuestShowList.end(), CcbDailyQuestRewardLayer::compare);
    sort(m_vecDailyQuestShowList.begin(), m_vecDailyQuestShowList.end(), CcbDailyQuestRewardLayer::compare1);
    char szTemp[8] = "";
    sprintf(szTemp, "%d/%lu", m_nCompleteCount, m_vecDailyQuestShowList.size());
    m_pLabelTTFCompleteCount->setString(szTemp);
}

CCSize CcbDailyQuestRewardLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(300, 75);
}

CCTableViewCell* CcbDailyQuestRewardLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbDailyQuestRewardFrameLayer(this);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbDailyQuestRewardFrameLayer* pNode = (CcbDailyQuestRewardFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->m_pControlButtonReward->setForceRect(m_pLayerList->boundingBox());
        pNode->m_pLabelTTFSchedule->setVisible(true);
        pNode->m_pLabelTTFScheduleValue->setVisible(true);
        if (m_byCurType == 0) {
            
            pNode->m_pLabelTTFReward->setString(CCString::createWithFormat("%s%s",GET_STR(Str_DailyReward_Get),CCString::createWithFormat("%d%s",m_vecDailyQuestShowList[idx].config.dwScore,GET_STR(Str_Score))->getCString())->getCString());
            pNode->m_pLabelTTFName->setString(m_vecDailyQuestShowList[idx].config.strDesc.c_str());
            pNode->m_pLabelTTFScheduleValue->setString(CCString::createWithFormat("(%d/%d)",m_vecDailyQuestShowList[idx].info.dwCondition,m_vecDailyQuestShowList[idx].config.dwParam[0])->getCString());
            pNode->setIndex(m_vecDailyQuestShowList[idx].info.dwIndex);
            pNode->setNextSeneTag(m_vecDailyQuestShowList[idx].config.strNextScene);
            pNode->m_pLabelTTFRewardNum->setString(CCString::createWithFormat("%d",m_vecDailyQuestShowList[idx].config.dwRewardCnt[0])->getCString());
            pNode->m_pLabelTTFRewardNum->getParent()->setVisible(true);
            pNode->m_pSpriteFinish->setVisible(false);
            pNode->m_pControlButtonReward->setVisible(true);
            if (m_vecDailyQuestShowList[idx].info.byStatus == 1)
            {
                pNode->m_pControlButtonReward->setEnabled(true);
                {
                    pNode->m_pControlButtonReward->setTitleForState(ccs(GET_STR(Str_Get)), 1 << 0);
                }
                pNode->setSchedulerLabelState(ccGREEN);
            }
            else if (m_vecDailyQuestShowList[idx].info.byStatus == 2)
            {
                pNode->m_pSpriteFinish->setVisible(true);
                pNode->m_pLabelTTFSchedule->setVisible(false);
                pNode->m_pLabelTTFScheduleValue->setVisible(false);
                pNode->m_pControlButtonReward->setVisible(false);
                {
                    pNode->m_pControlButtonReward->setTitleForState(ccs(GET_STR(Str_Get)), 1 << 0);
                }
                
            }
            else if (m_vecDailyQuestShowList[idx].info.byStatus == 0)
            {
                pNode->m_pControlButtonReward->setEnabled(true);
                {
                    pNode->m_pControlButtonReward->setTitleForState(ccs(GET_STR(Str_Goto)), 1 << 0);
                }
                pNode->setSchedulerLabelState(ccYELLOW);
            }
            pNode->setRewardButtonStatus(m_vecDailyQuestShowList[idx].info.byStatus);
            pNode->m_pControlButtonReward->setTag(m_vecDailyQuestShowList[idx].info.byStatus);
            
            uint32 dwRewardID = m_vecDailyQuestShowList[idx].config.dwRewardID[0];
            CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetObjectIconByIndex(dwRewardID).c_str());
            if (pTexture)
            {
                pNode->m_pSpriteIcon->setTexture(pTexture);
            }
        }
        else
        {
            pNode->CreateData(g_TaskData->GetAchieveVector()[idx].dwIndex);
        }
        pNode->setRewardType(m_byCurType + 1);
        
    }
    
    return pCell;
}

unsigned int CcbDailyQuestRewardLayer::numberOfCellsInTableView(CCTableView *table)
{
    if (m_byCurType == 0) {
        return m_vecDailyQuestShowList.size();
    }
    else
    {
        return g_TaskData->GetAchieveVector().size();
    }
    
}

void CcbDailyQuestRewardLayer::RefeashLayer()
{
    this->setLayerInfoByTab(m_byCurType);
    CCPoint offPos = m_tableView->getContentOffset();
    m_tableView->reloadData();
    m_tableView->setContentOffset(offPos);
}

void CcbDailyQuestRewardLayer::onPressConrtolButtonDailyCallBack(cocos2d::CCObject *pObject, CCControlEvent event)
{
    CCControlButton* pButton = (CCControlButton *)pObject;
    if (!pButton) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    this->setLayerInfoByTab(pButton->getTag());
    
}

void CcbDailyQuestRewardLayer::onPressControlButtonBox(cocos2d::CCObject *pObject, CCControlEvent event)
{
    CCControlButton* pButton = (CCControlButton *)pObject;
    if (!pButton) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CCSprite *pSprite = (CCSprite *)pButton->getParent();
    if (pSprite->getChildByTag(NODEPARTICLETAG)->isVisible()) {
        CGameSession::SendDailyQuestRewardRequest(2,pSprite->getTag() + 1);
    }
    else
    {
        DailyRewardConfig::STC_CONFIG_DAILYREWARD *pConfig = GET_CONFIG_STC(DailyRewardConfig,pSprite->getTag() + 1);
        if (!pConfig) {
            return;
        }
        CcbShowGetLayer* pGetLayer = dynamic_cast<CcbShowGetLayer*>(CcbManager::sharedManager()->LoadCcbShowGetLayer());
        pGetLayer->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*0.5));
        pGetLayer->setShowGetLayerTitle(GET_STR(Str_ShowGetLayertitleCanget));
        for (int i = 0; i < CTaskDataMgr::Get()->getHadRewardId().size(); i++) {
            if (pSprite->getTag() + 1 == CTaskDataMgr::Get()->getHadRewardId()[i]) {
                pGetLayer->setShowGetLayerTitle(GET_STR(Str_ShowGetLayer_title_get));
                break;
            }
        }
        
        for (int i = 0; i < 4; i++) {
            
            if (pConfig->dwRewardItemId[i] != 0) {
                pGetLayer->addGetItem(pConfig->dwRewardItemId[i], pConfig->dwRewardItemNum[i]);
            }
        }
        pGetLayer->setNeedShowItemInfo(true);
        this->addChild(pGetLayer);
        pGetLayer->reloadItems();
    }
    
}
