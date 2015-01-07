//
//  SequenceAction.cpp
//  HelloWorld
//
//  Created by long on 14-1-19.
//
//

#include "SequenceAction.h"
#include "SequencePet.h"
#include "ConfigGet.h"
#include "ConfigUtil.h"
#include "ResourceDefine.h"

SequenceAction::SequenceAction()
{
    m_frameCT = 0;
    m_frameTT = 0;
}
SequenceAction::~SequenceAction()
{
    
}

SequenceAction* SequenceAction::create(SequencePet* delegate, std::string actName)
{
    SequenceAction *pRet = new SequenceAction();
    if (pRet && pRet->init(delegate, actName))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool SequenceAction::init(SequencePet* delegate, std::string actName)
{
    
    m_delegate = delegate;
    curActName = actName;
    
    if (!m_delegate) {
        return false;
    }
    uint16 petId = m_delegate->getPetId();
    m_frameTT = 1.0 / m_delegate->getFPS();
    
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, petId);
    if (!petCfg) {
        return false;
    }
    uint16 maxFrame = 0;
    if (curActName == SEQ_ACT_STAND) {
        maxFrame = petCfg->wStandFrame;
    }
    else if(curActName == SEQ_ACT_ATTACK)
    {
        maxFrame = petCfg->wAtkFrame;
    }
    
    CCString *plistName = CCString::createWithFormat(PET_SEQUENCE_PLIST, petCfg->dwModelIndex, curActName.c_str());

    //加载序列帧plist}
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( plistName->getCString() );
    
    cocos2d::CCArray *pFrames = new CCArray();
    for (int i = 1; i <= maxFrame; i++) {
        CCString *name = CCString::createWithFormat(PET_SEQUENCE_SPRITE_FRAME, petCfg->dwModelIndex, curActName.c_str(), i);
        CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        
        if (sf) {
            pFrames->addObject(sf);
        }
        else
        {
            CCLog(" SequenceAction, %s, not found~~~", name->getCString());
        }
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(pFrames, 1.0 / m_delegate->getFPS());
    if (!CCAnimate::initWithAnimation(animation))
    {
        return false;
    }

    return true;
}


SequenceFPSAction::SequenceFPSAction()
{
    
}

SequenceFPSAction::~SequenceFPSAction()
{
    
}

SequenceFPSAction* SequenceFPSAction::create(SequencePet *pTarget, const std::string actionName)
{
    SequenceFPSAction* pAction = new SequenceFPSAction();
    if ( pAction && pAction->initWithActionName( pTarget, actionName) ) {
        pAction->autorelease();
        return pAction;
    }
    CC_SAFE_DELETE(pAction);
    return NULL;
}


bool SequenceFPSAction::initWithActionName( SequencePet* pTarget, const std::string actionName)
{
    if (!CCNode::init()) {
        return false;
    }
    m_myTarget      = pTarget;
    m_strActionName = actionName;
    m_fLastUpdate   = -1;
    
    uint16 petId = pTarget->getPetId();
//    m_frameTT = 1.0 / pTarget->getFPS();
    
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, petId);
    if (!petCfg) {
        return false;
    }
    uint16 maxFrame = 0;
    if (actionName == SEQ_ACT_STAND) {
        maxFrame = petCfg->wStandFrame;
    }
    else if(actionName == SEQ_ACT_ATTACK)
    {
        maxFrame = petCfg->wAtkFrame;
    }
    
    CCString *plistName = CCString::createWithFormat(PET_SEQUENCE_PLIST, petCfg->dwModelIndex, actionName.c_str());
    //加载序列帧plist}
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( plistName->getCString() );
    
//    m_bRestart      = bRestart;
    m_wFrameLast    = maxFrame;
    m_wCurFrame     = 1;
    this->schedule(schedule_selector(SequenceFPSAction::update), 1.0 / pTarget->getFPS());
    return true;
}

void SequenceFPSAction::update(float time)
{

//    CCLog("     SequenceFPSAction  :  %d", m_wCurFrame);
    if (m_wCurFrame > m_wFrameLast) {
        if (m_myTarget) {
//            m_myTarget->callBackFPSAction();
        }
        stop();
        
        return;
    }
    
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_myTarget->getPetId());
    if (!petCfg) {
        return;
    }
    CCString *name = CCString::createWithFormat(PET_SEQUENCE_SPRITE_FRAME, petCfg->dwModelIndex, m_strActionName.c_str(), m_wCurFrame);
    
    CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
    
    if (sf) {
        m_myTarget->setDisplayFrame(sf);
    }
    else
    {
        CCLOG(" SequenceAction, %s, not found~~~", name->getCString());
    }
    
    m_wCurFrame++;
}


void SequenceFPSAction::stop()
{
    unschedule(schedule_selector(SequenceFPSAction::update));
    this->removeFromParent();
}

