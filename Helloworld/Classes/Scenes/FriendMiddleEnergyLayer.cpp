//
//  FriendMiddleEnergyLayer.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/22.
//
//

#include "FriendMiddleEnergyLayer.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "FriendUnitDataMgr.h"
#include "CcbFriendGetAllEnergyLayer.h"
#include "CcbFriendGetEnergyFrameLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

FriendMiddleEnergyLayer* FriendMiddleEnergyLayer::create(cocos2d::CCSize size) {
    FriendMiddleEnergyLayer* pRet = new FriendMiddleEnergyLayer();
    if (pRet && pRet->init(size)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool FriendMiddleEnergyLayer::init(cocos2d::CCSize size) {
    if (!FriendMiddleBaseLayer::init(size)) {
        return false;
    }
    
    m_pLayerGetAllEnergy = dynamic_cast<CcbFriendGetAllEnergyLayer*>(CcbManager::sharedManager()->LoadCcbFriendGetAllEnergyLayer(this));
    m_pLayerGetAllEnergy->setPosition(ccp(m_size.width * 0.5, 0.0f));
    addChild(m_pLayerGetAllEnergy, 2);
    
    m_tablePosition = ccp(0, getHeight(m_pLayerGetAllEnergy));
    m_tableViewSize = CCSizeMake(m_size.width, m_size.height - getHeight(m_pLayerGetAllEnergy));
    
    return true;
}

void FriendMiddleEnergyLayer::onEnter() {
    FriendMiddleBaseLayer::onEnter();
    reloadTableData();
}

void FriendMiddleEnergyLayer::onEnterTransitionDidFinish() {
    FriendMiddleBaseLayer::onEnterTransitionDidFinish();
}

void FriendMiddleEnergyLayer::onExit() {
    FriendMiddleBaseLayer::onExit();
}

void FriendMiddleEnergyLayer::onExitTransitionDidStart() {
    FriendMiddleBaseLayer::onExitTransitionDidStart();
}

void FriendMiddleEnergyLayer::reloadTableData()
{
    FriendMiddleBaseLayer::reloadTableData();
    m_pLayerGetAllEnergy->leftEnergyCntUpdate();
}

#pragma mark -- Table Delegate --

CCTableViewCell* FriendMiddleEnergyLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    CCTableViewCell* pCell = table->dequeueCell();
    
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbFriendGetEnergyFrameLayer* pFrame = dynamic_cast<CcbFriendGetEnergyFrameLayer*>(CcbManager::sharedManager()->LoadCcbFriendGetEnergyFrameLayer(this));
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
        CcbFriendGetEnergyFrameLayer* pFrame = dynamic_cast<CcbFriendGetEnergyFrameLayer*>(pCell->getChildByTag(123));
        pFrame->setFrameData(FriendUnitDataMgr::Get()->frameInfoAtIdx(idx));
    }
    
    return pCell;
}


