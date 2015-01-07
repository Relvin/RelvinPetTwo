//
//  ScrollNoticeLayer.cpp
//  MyGame
//
//  Created by Relvin on 14/10/30.
//
//

#include "ScrollNoticeLayer.h"
#include "ReRichText.h"
#include "UISupport.h"
#include "BackCtrl.h"
#include "ResourcePic.h"
#include "ConfigGet.h"
#include "StartGameLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "GuideData.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define MOVESPEED    50.f

static ScrollNoticeLayer *s_pShare = NULL;

ScrollNoticeLayer* ScrollNoticeLayer::shareInstance()
{
    if (!s_pShare) {
        s_pShare = ScrollNoticeLayer::create();
        s_pShare->retain();
        CCDirector::sharedDirector()->setNotificationNode(s_pShare);
    }
    return s_pShare;
}

void ScrollNoticeLayer::purgeScrollNotice()
{
    s_pShare->release();
    s_pShare = NULL;
}

ScrollNoticeLayer::ScrollNoticeLayer()
: m_pScrollView (NULL)
, m_pLastShowText (NULL)
, scrollIndex(0)
{
    
}

ScrollNoticeLayer::~ScrollNoticeLayer()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(ScrollNoticeLayer::scheduleToHide), this);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "SCROLLNOTICE");
}

bool ScrollNoticeLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCSprite* pSprite = CCSprite::create(GET_PIC(Pic_announce));
    this->addChild(pSprite);
    pSprite->setOpacity(200);
    
    m_pScrollView = CCScrollView::create(pSprite->getContentSize());
    m_pScrollView->setPosition(CCPointZero);
    m_pScrollView->setContentOffset(ccp(0.0f, 0.0f));
    m_pScrollView->setTouchEnabled(false);
    
    m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
    pSprite->addChild(m_pScrollView,1);
    
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(ScrollNoticeLayer::scheduleToHide), this, 3.0f, false);
    this->setVisible(false);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ScrollNoticeLayer::listenNotificationCallBack), "SCROLLNOTICE", NULL);
    
    return true;
}

void ScrollNoticeLayer::onEnter()
{
    CCLayer::onEnter();

}

void ScrollNoticeLayer::onExit()
{
    CCLayer::onExit();
    
}

void ScrollNoticeLayer::showScrollNotice(const char * text)
{
    CRole* pRole = CGameSession::GetRole();
    if (pRole->GetwGuideTrigger() < GuideData::E_GUIDE_TRIGGER_FIR_ATTACK) {
        return;
    }
    scrollIndex++;
//    CCLOG("ScrollNoticeLayer::showScrollNotice::count = %d",scrollIndex);
    
    ReRichText* reRichText = ReRichText::create(text, "Arial", 12);
    m_pScrollView->addChild(reRichText,2);
    reRichText->setAnchorPoint(ccp(0,0));
    CCPoint startPos(ccp(m_pScrollView->getViewSize().width + 10,3));
    if (m_pLastShowText) {
        startPos.x = startPos.x < (getRight(m_pLastShowText) + 10) ? (getRight(m_pLastShowText) + 10) : startPos.x;
    }
    
    reRichText->setPosition(startPos);
    reRichText->setColor(ccWHITE);
    reRichText->setImageScale(0.5f);
    
    float fMoveTime = (startPos.x + getWidth(reRichText)) / MOVESPEED;
    
    reRichText->runAction(CCSequence::create(
                                             CCMoveTo::create(fMoveTime, ccp(-getWidth(reRichText), 5)),
                                             CCCallFuncO::create(this,callfuncO_selector(ScrollNoticeLayer::afterScrollOverCallBack),reRichText),
                                             NULL));
    m_pLastShowText = reRichText;
    if (BackCtrl::GetCurSceneIdx() != kPveBattleScene && BackCtrl::GetCurSceneIdx() != kArenaFightScene && StartGameLayer::GetCurLayer() == NULL) {
        this->setVisible(true);
    }
    else
    {
        this->setVisible(false);
    }
    
}

void ScrollNoticeLayer::afterScrollOverCallBack(cocos2d::CCObject *pObject)
{
    CCNode* pNode = dynamic_cast<CCNode *>(pObject);
    if (pNode) {
        if (m_pLastShowText == pNode) {
            m_pLastShowText = NULL;
        }
        pNode->removeFromParent();
        scrollIndex--;
    }
//    CCLOG("ScrollNoticeLayer::afterScrollOverCallBack::count = %d",scrollIndex);
}

void ScrollNoticeLayer::scheduleToHide(float cTime)
{
//    CCLOG("ScrollNoticeLayer::scheduleToHide");
    if (m_pLastShowText == NULL && this->isVisible()) {
        this->setVisible(false);
    }
}

void ScrollNoticeLayer::listenNotificationCallBack(cocos2d::CCObject *pObject)
{
    if (BackCtrl::GetCurSceneIdx() != kPveBattleScene && BackCtrl::GetCurSceneIdx() != kArenaFightScene &&StartGameLayer::GetCurLayer() == NULL) {
        if (m_pLastShowText) {
            this->setVisible(true);
        }
        else
        {
            this->setVisible(false);
        }
        
    }
    else
    {
        this->setVisible(false);
    }
}

