//
//  FriendMiddleSuggestLayer.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/21.
//
//

#include "FriendMiddleSuggestLayer.h"
#include "CcbFindFriendLayer.h"
#include "CcbFriendCntLayer.h"
#include "FriendUnitDataMgr.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "CcbFriendFindFrameLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

FriendMiddleSuggestLayer* FriendMiddleSuggestLayer::create(cocos2d::CCSize size) {
    FriendMiddleSuggestLayer* pRet = new FriendMiddleSuggestLayer();
    if (pRet && pRet->init(size)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool FriendMiddleSuggestLayer::init(cocos2d::CCSize size) {
    if (!FriendMiddleBaseLayer::init(size)) {
        return false;
    }
    m_nFriendCnt = FriendUnitDataMgr::Get()->frameCnt();
    
    m_pLayerFriendCnt = dynamic_cast<CcbFriendCntLayer*>(CcbManager::sharedManager()->LoadCcbFriendCntLayer(this));
    m_pLayerFriendCnt->setPosition(ccp(m_size.width * 0.5, 0));
    addChild(m_pLayerFriendCnt, 2);
    //TODO:Junie get max friend cnt from vip csv
    m_pLayerFriendCnt->setFriendCnt(FriendUnitDataMgr::Get()->friendNum(), 100);
    
    m_tablePosition = ccp(0, getHeight(m_pLayerFriendCnt));
    
    m_pLayerFindFriend = dynamic_cast<CcbFindFriendLayer*>(CcbManager::sharedManager()->LoadCcbFindFriendLayer(this));
    m_pLayerFindFriend->setPosition(ccp(m_size.width * 0.5, m_size.height));
    addChild(m_pLayerFindFriend, 2);
    
    m_tableViewSize = CCSizeMake(m_size.width, m_size.height - getHeight(m_pLayerFriendCnt) - getHeight(m_pLayerFindFriend));
    
    return true;
}

void FriendMiddleSuggestLayer::onEnter() {
    FriendMiddleBaseLayer::onEnter();
}

void FriendMiddleSuggestLayer::onExit() {
    FriendMiddleBaseLayer::onExit();
}

void FriendMiddleSuggestLayer::onEnterTransitionDidFinish() {
    FriendMiddleBaseLayer::onEnterTransitionDidFinish();
}

void FriendMiddleSuggestLayer::onExitTransitionDidStart() {
    FriendMiddleBaseLayer::onExitTransitionDidStart();
}

void FriendMiddleSuggestLayer::reloadTableData() {
    FriendMiddleBaseLayer::reloadTableData();
    m_pLayerFriendCnt->setFriendCnt(FriendUnitDataMgr::Get()->friendNum(), 100);
}

#pragma mark -- Table Delegate --

CCTableViewCell* FriendMiddleSuggestLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    CCTableViewCell* pCell = table->dequeueCell();
    
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbFriendFindFrameLayer* pFrame = dynamic_cast<CcbFriendFindFrameLayer*>(CcbManager::sharedManager()->LoadCcbFriendFindFrameLayer(this));
        if (!pFrame) {
            return NULL;
        }
        
        pFrame->setFrameData(FriendUnitDataMgr::Get()->frameInfoAtIdx(idx));
        pFrame->ignoreAnchorPointForPosition(false);
        pFrame->setAnchorPoint(ccp(0.5, 0));
        pFrame->setPosition(ccp(m_tableViewSize.width * 0.5, 0.0f));
        pCell->addChild(pFrame);
        pFrame->setTag(123);
    } else {
        CcbFriendFindFrameLayer* pFrame = dynamic_cast<CcbFriendFindFrameLayer*>(pCell->getChildByTag(123));
        pFrame->setFrameData(FriendUnitDataMgr::Get()->frameInfoAtIdx(idx));
    }
    
    return pCell;
}

