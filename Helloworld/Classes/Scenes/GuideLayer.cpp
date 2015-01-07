//
//  GuideLayer.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-3-12.}
//
//

#include "GuideLayer.h"
#include "CcbManager.h"
#include "CcbPadLayer.h"
#include "MaskLayer.h"
#include "ConfigGet.h"
#include "CcbManager.h"
#include "Support.h"
#include "GuideData.h"
#include "ResourcePic.h"
#include "UISupport.h"
#include "GuideBtnPos.h"

USING_NS_CC;

#define Mask_Tag 3257

GuideLayer::GuideLayer() {

}

GuideLayer::~GuideLayer()
{
    CCLog("release guide layer");
}

bool GuideLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(winSize);
    return true;
}

void GuideLayer::onEnter()
{
    CCLayer::onEnter();
}

void GuideLayer::onExit()
{
    CCLayer::onExit();
}

void GuideLayer::onEnterTransitionDidFinish() {
    CCLayer::onEnterTransitionDidFinish();
}

void GuideLayer::onExitTransitionDidStart() {
    CCLayer::onExitTransitionDidStart();
}

void GuideLayer::playGuide(GuideData::STC_DIALOG dialog)
{

    CcbPadLayer* m_pPadLayer = NULL;
    if (dialog.nPosY > 0) {
        m_pPadLayer = dynamic_cast<CcbPadLayer*>(CcbManager::sharedManager()->LoadCcbPadLayer(this));
        m_pPadLayer->setPadStyle(1);
        m_pPadLayer->setFromKind(CcbPadLayer::E_GUIDE);
        addChild(m_pPadLayer, 9001);

        m_pPadLayer->setTouchErase(true);
        m_pPadLayer->setPosition(ccp(winSize.width*0.5, dialog.nPosY));
        m_pPadLayer->setLadyInfo(dialog.wLadyPath, dialog.byLadyOffset);
        
        m_pPadLayer->setScrollMsg(dialog.strName.c_str(), dialog.colorName, dialog.strText.c_str(), dialog.colorText);

    }
    
    if (dialog.wRefButtonId) {
        if (m_pPadLayer) {
            m_pPadLayer->setTouchErase(false);
            m_pPadLayer->setTouchEnabled(false);
            m_pPadLayer->removeMask();
        }
        
        uint16 wRefBtnId = dialog.wRefButtonId;
        
        GuideButtonConfig::STC_GUIDE_BUTTON_CONFIG *btnCfg = GET_CONFIG_STC(GuideButtonConfig, wRefBtnId);
        // convert pos to current screen
        if (!btnCfg) {
            CCMessageBox("Guide Button Csv", "Error");
            return;
        }

        CCRect touchRect = GuideBtnPos::Get()->worldRectWithEnum(wRefBtnId);

        std::vector<CCRect> arrRect;
        arrRect.push_back(touchRect);
        
        if (getChildByTag(Mask_Tag)) {
            removeChildByTag(Mask_Tag);
        }
        
        if (btnCfg->byLock) {
            MaskLayer* pMaskLayer;
            if (btnCfg->byDark) {
                pMaskLayer = MaskLayer::create(arrRect);
            } else {
                pMaskLayer = MaskLayer::create(arrRect, false);
            }
            
            pMaskLayer->setAnchorPoint(CCPointZero);
            pMaskLayer->setPosition(CCPointZero);
            
            
            addChild(pMaskLayer, 9000, Mask_Tag);
        }
        
        
        // 增加上下的手势}
        if (btnCfg->byDirection == 0) {
            CCNode* pHand;
            pHand = CcbManager::sharedManager()->LoadCcbFingerUpLayer(NULL);
            pHand->setAnchorPoint(ccp(0, 1));
            pHand->setPosition(ccp(touchRect.getMidX(), touchRect.getMidY()));
            addChild(pHand, 9003);
            
            CCNode* pAni = CcbManager::sharedManager()->LoadCcbBattleAnimationLayer();
            pAni->ignoreAnchorPointForPosition(false);
            pAni->setAnchorPoint(ccp(0.5, 0.5));
            pAni->setPosition(pHand->getPosition());
            addChild(pAni, 9000);
            
        } else {
            CCNode* pHand;
            if (btnCfg->byDirection == 1) { // 上手}
                pHand = CcbManager::sharedManager()->LoadCcbFingerUpLayer(NULL);
                pHand->setAnchorPoint(ccp(0, 1));
                pHand->setPosition(ccp(touchRect.getMidX(), touchRect.getMidY()));
            } else if (btnCfg->byDirection == 2) { // 下手}
                pHand = CcbManager::sharedManager()->LoadCcbFingerDownLayer(NULL);
                pHand->setAnchorPoint(ccp(0, 0));
                pHand->setPosition(ccp(touchRect.getMidX(), touchRect.getMidY()));
            }
            
            addChild(pHand, 9002);
        }
        
        CCLabelTTF* lblSkip = CCLabelTTF::create("GO", "Arial", 24);
        lblSkip->setColor(ccRED);
        CCMenuItemLabel* pMenuSkip = CCMenuItemLabel::create(lblSkip, this, menu_selector(GuideLayer::skip));
        pMenuSkip->setAnchorPoint(ccp(0.5, 1));
        pMenuSkip->setPosition(ccp(winSize.width * 0.5, winSize.height));
        
        CCMenu* pMenu = CCMenu::create(pMenuSkip, NULL);
        pMenu->setPosition(CCPointZero);
        pMenu->setTouchPriority(kCCMenuHandlerPriority  * 4 - 1);
        
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
        addChild(pMenu, 9004);
#else
        
#ifdef DEBUG
        addChild(pMenu, 9004);
#endif
        
#endif
    }
}

void GuideLayer::skip(CCObject *pObject)
{
    GuideData::GetInstance()->skipCurStep();
}

