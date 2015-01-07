#include "CcbFriendLayer.h"
#include "CcbManager.h"
#include "FriendScene.h"
#include "CcbRescueFrameLayer.h"
#include "CcbFriendNodeLayer.h"
#include "UISupport.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFriendLayer::~CcbFriendLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerBottom);
    CC_SAFE_RELEASE_NULL(m_pLayerHeadBack);
    CC_SAFE_RELEASE_NULL(m_pLayerViewBg);
    m_shared = NULL;
}

//-- copy this to CcbManager 
/*
//CcbManager.h


//CcbManager.cpp

*/
CcbFriendLayer* CcbFriendLayer::m_shared = NULL;

bool CcbFriendLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_shared = this;
	return true;
}

CcbFriendLayer* CcbFriendLayer::GetCurLayer()
{
    return m_shared;
}

// Inhert CCNodeLoaderListener
void CcbFriendLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

void CcbFriendLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_clipRect.origin = getWorldPos(m_pLayerViewBg);
    m_pLayerViewBg->setContentSize(CCSizeMake(getWidth(m_pLayerViewBg), getBottom(m_pLayerHeadBack) - m_clipRect.origin.y + 5));
    m_clipRect.size = m_pLayerViewBg->getContentSize();
    m_pTableFriend = CCTableView::create(this, m_clipRect.size);
    m_pTableFriend->setPosition(CCPointZero);
    
    m_pTableFriend->setDirection(kCCScrollViewDirectionVertical);
    m_pTableFriend->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pLayerViewBg->addChild(m_pTableFriend);
    
    m_pTableFriend->reloadData();
}

void CcbFriendLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFriendLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHeadBack", CCLayer*, this->m_pLayerHeadBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, this->m_pLayerBottom);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerViewBg", CCLayer*, this->m_pLayerViewBg);
	return false;
}

bool CcbFriendLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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

#pragma mark TableView Delegate
void CcbFriendLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    return;
}

CCTableViewCell* CcbFriendLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)

{
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCNode* pNode;
        if ( FriendCtrl::Get()->getFromType() == FriendCtrl::kFromCapture || FriendCtrl::Get()->getFromType() == FriendCtrl::kFromRescue ) {    // 抓捕，解救界面}
            pNode = CcbManager::sharedManager()->LoadCcbRescueFrameLayer(this);
            dynamic_cast<CcbRescueFrameLayer*>(pNode)->SetData(idx);
        }
        else if ( FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendList) {    // 好友列表界面}
            pNode = CcbManager::sharedManager()->LoadCcbFriendNodeLayer(this);
            dynamic_cast<CcbFriendNodeLayer*>(pNode)->setNode(FriendCtrl::Get()->friendListAtIdx(idx));
        }
        else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromTotalMail) {      // 好友申请+好友邮件界面}
            pNode = CcbManager::sharedManager()->LoadCcbFriendNodeLayer(this);
            // set mail&apply data to pnode
            int nApplyCnt = FriendCtrl::Get()->applyCnt();
            if (idx < nApplyCnt) {
                dynamic_cast<CcbFriendNodeLayer*>(pNode)->setMsgInfo(FriendCtrl::Get()->friendApplyAtIdx(idx), FriendCtrl::kFriendApply);
            } else {
                dynamic_cast<CcbFriendNodeLayer*>(pNode)->setMsgInfo(FriendCtrl::Get()->friendMailAtIdx(idx-nApplyCnt), FriendCtrl::kFriendMsg);
            }
            
        }
        m_fCellWidth = pNode->getContentSize().width;
        m_fCellHeight = pNode->getContentSize().height;
        pNode->setPosition(ccp(getWidth(m_pLayerViewBg)*0.5, 4));
        pCell->addChild(pNode);
        pNode->setTag(123);
    } else {
        if ( FriendCtrl::Get()->getFromType() == FriendCtrl::kFromCapture || FriendCtrl::Get()->getFromType() == FriendCtrl::kFromRescue ) {
            CcbRescueFrameLayer* pNode = dynamic_cast<CcbRescueFrameLayer*>(pCell->getChildByTag(123));
            pNode->SetData(idx);
        }
        else if ( FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendList ) {
            CcbFriendNodeLayer* pNode = dynamic_cast<CcbFriendNodeLayer*>(pCell->getChildByTag(123));
            pNode->setNode(FriendCtrl::Get()->friendListAtIdx(idx));
        }
        else if ( FriendCtrl::Get()->getFromType() == FriendCtrl::kFromTotalMail ) {
            CcbFriendNodeLayer* pNode = dynamic_cast<CcbFriendNodeLayer*>(pCell->getChildByTag(123));
            // set mail&apply data to pnode
            int nApplyCnt = FriendCtrl::Get()->applyCnt();
            if (idx < nApplyCnt) {
                pNode->setMsgInfo(FriendCtrl::Get()->friendApplyAtIdx(idx), FriendCtrl::kFriendApply);
            } else {
                pNode->setMsgInfo(FriendCtrl::Get()->friendMailAtIdx(idx-nApplyCnt), FriendCtrl::kFriendMsg);
            }
        }
    }
    return pCell;
}

unsigned int CcbFriendLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromTotalMail) {
        m_nTableCnt = FriendCtrl::Get()->msgTotalCnt();
    } else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendList) {
        m_nTableCnt = FriendCtrl::Get()->friendListCnt();
    } else {
        m_nTableCnt = FriendCtrl::Get()->resCapUserCnt();
    }
    return m_nTableCnt;
}

CCSize CcbFriendLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(m_fCellWidth, 86);
}

#pragma mark Public Method
void CcbFriendLayer::ReloadList()
{
    m_pTableFriend->reloadData();
}

void CcbFriendLayer::addMailContent()
{
    CCNode* pCotent = CcbManager::sharedManager()->LoadCcbMailDetailLayer();
    pCotent->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
    this->addChild(pCotent, 20);
}


