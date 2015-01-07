//
//  FriendMiddleBaseLayer.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/21.
//
//

#include "FriendMiddleBaseLayer.h"
#include "FriendUnitDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool FriendMiddleBaseLayer::init(cocos2d::CCSize size) {
    if (!CCLayer::init()) {
        return false;
    }
    m_size = size;
    setContentSize(m_size);
    
    m_nFriendCnt = FriendUnitDataMgr::Get()->frameCnt();
    
    m_tablePosition = ccp(0, 0);
    m_tableViewSize = m_size;
    
    return true;
}

void FriendMiddleBaseLayer::onEnter() {
    CCLayer::onEnter();
    m_frameSize = CCSizeMake(281.0, 79.0);
    
    m_pTableView = CCTableView::create(this, m_tableViewSize);
    m_pTableView->setPosition(m_tablePosition);
    addChild(m_pTableView, 1);
    
    // reload should be called by derived class
//    reloadTableData();
}

void FriendMiddleBaseLayer::onEnterTransitionDidFinish() {
    CCLayer::onEnterTransitionDidFinish();
}

void FriendMiddleBaseLayer::onExit() {
    CCLayer::onExit();
}

void FriendMiddleBaseLayer::onExitTransitionDidStart() {
    CCLayer::onExitTransitionDidStart();
}

void FriendMiddleBaseLayer::reloadTableData() {
    m_nFriendCnt = FriendUnitDataMgr::Get()->frameCnt();
    m_pTableView->reloadData();
}

void FriendMiddleBaseLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell) {
    if ( cell ) {
        CCLog("cell touched at %s index:%i", __FILE__, cell->getIdx());
    }
}

unsigned int FriendMiddleBaseLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table) {
    return m_nFriendCnt;
}

CCSize FriendMiddleBaseLayer::cellSizeForTable(cocos2d::extension::CCTableView *table) {
    return m_frameSize;
}

