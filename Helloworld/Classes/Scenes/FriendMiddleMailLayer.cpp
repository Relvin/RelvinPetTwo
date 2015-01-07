//
//  FriendMiddleMailLayer.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/22.
//
//

#include "FriendMiddleMailLayer.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "FriendUnitDataMgr.h"
#include "CcbFriendMailFrameLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

FriendMiddleMailLayer* FriendMiddleMailLayer::create(cocos2d::CCSize size) {
    FriendMiddleMailLayer* pRet = new FriendMiddleMailLayer();
    if (pRet && pRet->init(size)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool FriendMiddleMailLayer::init(cocos2d::CCSize size) {
    if (!FriendMiddleBaseLayer::init(size)) {
        return false;
    }
    return true;
}

void FriendMiddleMailLayer::onEnter() {
    FriendMiddleBaseLayer::onEnter();
    reloadTableData();
}

void FriendMiddleMailLayer::onEnterTransitionDidFinish() {
    FriendMiddleBaseLayer::onEnterTransitionDidFinish();
}

void FriendMiddleMailLayer::onExit() {
    FriendMiddleBaseLayer::onExit();
}

void FriendMiddleMailLayer::onExitTransitionDidStart() {
    FriendMiddleBaseLayer::onExitTransitionDidStart();
}

void FriendMiddleMailLayer::reloadTableData() {
    FriendMiddleBaseLayer::reloadTableData();
}

#pragma mark -- Table Delegate --

CCTableViewCell* FriendMiddleMailLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    CCTableViewCell* pCell = table->dequeueCell();
    
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbFriendMailFrameLayer* pFrame = dynamic_cast<CcbFriendMailFrameLayer*>(CcbManager::sharedManager()->LoadCcbFriendMailFrameLayer(this));
        if (!pFrame) {
            return NULL;
        }
        
        pFrame->setFrameData(FriendUnitDataMgr::Get()->friendMailAtIdx(idx));
        pFrame->ignoreAnchorPointForPosition(false);
        pFrame->setAnchorPoint(ccp(0.5, 0));
        pFrame->setPosition(ccp(m_tableViewSize.width * 0.5, 0.0f));
        pCell->addChild(pFrame);
        pFrame->setTag(123);
    } else {
        CcbFriendMailFrameLayer* pFrame = dynamic_cast<CcbFriendMailFrameLayer*>(pCell->getChildByTag(123));
        pFrame->setFrameData(FriendUnitDataMgr::Get()->friendMailAtIdx(idx));
    }
    return pCell;
}



