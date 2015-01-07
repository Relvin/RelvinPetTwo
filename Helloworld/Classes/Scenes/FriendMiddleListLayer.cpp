//
//  FriendMiddleListLayer.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/21.
//
//

#include "FriendMiddleListLayer.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "CcbFriendListFrameLayer.h"
#include "CcbFriendCntLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

FriendMiddleListLayer* FriendMiddleListLayer::create(cocos2d::CCSize size) {
    FriendMiddleListLayer* pRet = new FriendMiddleListLayer();
    if (pRet && pRet->init(size)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool FriendMiddleListLayer::init(cocos2d::CCSize size) {
    if (!FriendMiddleBaseLayer::init(size)) {
        return false;
    }
    m_pLayerFriendCnt = dynamic_cast<CcbFriendCntLayer*>( CcbManager::sharedManager()->LoadCcbFriendCntLayer(this) );
    m_pLayerFriendCnt->setPosition(ccp(m_size.width * 0.5, 0));
    addChild(m_pLayerFriendCnt, 2);
    //TODO:Junie get max friend cnt from vip csv
    m_pLayerFriendCnt->setFriendCnt(FriendUnitDataMgr::Get()->friendNum(), 100);
    
    m_tableViewSize = CCSizeMake(m_size.width, m_size.height - getHeight(m_pLayerFriendCnt));
    m_tablePosition = ccp(0, getHeight(m_pLayerFriendCnt));
    
    return true;
}

void FriendMiddleListLayer::onEnter() {
    FriendMiddleBaseLayer::onEnter();
    reloadTableData();
}

void FriendMiddleListLayer::onEnterTransitionDidFinish() {
    FriendMiddleBaseLayer::onEnterTransitionDidFinish();
}

void FriendMiddleListLayer::onExit() {
    FriendMiddleBaseLayer::onExit();
}

void FriendMiddleListLayer::onExitTransitionDidStart() {
    FriendMiddleBaseLayer::onExitTransitionDidStart();
}

void FriendMiddleListLayer::reloadTableData() {
    FriendMiddleBaseLayer::reloadTableData();
    m_pLayerFriendCnt->setFriendCnt(FriendUnitDataMgr::Get()->friendNum(), 100);
}

#pragma mark -- Table Delegate --

CCTableViewCell* FriendMiddleListLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    CCTableViewCell* pCell = table->dequeueCell();
    
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbFriendListFrameLayer* pFrame = dynamic_cast<CcbFriendListFrameLayer*>(CcbManager::sharedManager()->LoadCcbFriendListFrameLayer(this));
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
        CcbFriendListFrameLayer* pFrame = dynamic_cast<CcbFriendListFrameLayer*>(pCell->getChildByTag(123));
        pFrame->setFrameData(FriendUnitDataMgr::Get()->frameInfoAtIdx(idx));
    }
    return pCell;
}


