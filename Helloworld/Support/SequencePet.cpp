//
//  Sequence.cpp
//  HelloWorld
//
//  Created by long on 14-1-19.
//
//

#include "SequencePet.h"
#include "ConfigUtil.h"
#include "ResourceDefine.h"
#include "SequenceAction.h"
#include "ConfigGet.h"
#include "FightPetSprite.h"
#include "Pet.h"
SequencePet::SequencePet()
{
    m_wFps = seq_fps;
    m_FightPetSprite = NULL;
    m_fpsAction = NULL;
}
//析构时注意清内存}
SequencePet::~SequencePet()
{
//    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_petId);
//    if (!petCfg) {
//        return;
//    }
//    int maxFrame = petCfg->wStandFrame;
//    CCTexture2D* tex = NULL;
//    //清除呼吸动作图片}
//    for (int i = 1; i <= maxFrame; i++) {
//        CCString *name = CCString::createWithFormat(PET_SEQUENCE_SPRITE_FRAME, m_petId, SEQ_ACT_STAND, i);
//        CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//        if (!sf || sf->retainCount() == 0) {
//            continue;
//        }
////        CCLOG("stand name %s", name->getCString());
//        sf->release();
//        if ( sf->retainCount() == 1 )
//        {
//            tex = sf->getTexture();
//            CCTextureCache::sharedTextureCache()->removeTexture( tex );
//            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName( name->getCString() );
//        }
//    }
//    
//    //清除攻击动作图片}
//    maxFrame = petCfg->wAtkFrame;
//    for (int i = 1; i <= maxFrame; i++) {
//        CCString *name = CCString::createWithFormat(PET_SEQUENCE_SPRITE_FRAME, m_petId, SEQ_ACT_ATTACK, i);
//        CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
//        if (!sf || sf->retainCount() == 0) {
//            continue;
//        }
//        CCLOG("atk name %s", name->getCString());
//        sf->release();
//        if ( sf->retainCount() == 1 )
//        {
//            tex = sf->getTexture();
//            CCTextureCache::sharedTextureCache()->removeTexture( tex );
//            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName( name->getCString() );
//        }
//    }
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}
//根据petId读序列帧图进内存}
SequencePet* SequencePet::create(uint32 petId)
{
    SequencePet *pRet = new SequencePet();
    if (pRet && pRet->init(petId))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        
        return create(162);
        
        return NULL;
    }
}

bool SequencePet::init(uint32 petId)
{
    if (!CCSprite::init()) {
        return false;
    }
    
    m_petId = petId;
    PetConfig::STC_PET_CONFIG* pet = GET_CONFIG_STC(PetConfig, m_petId);
    if (!pet) {
        return false;
    }
    CCString *plistName = CCString::createWithFormat(PET_SEQUENCE_PLIST, pet->dwModelIndex, SEQ_ACT_STAND);

    //加载序列帧plist}
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( plistName->getCString() );
    //取呼吸动画第一帧作为默认图}
    CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(PET_SEQUENCE_SPRITE_FRAME, pet->dwModelIndex, SEQ_ACT_STAND, 1)->getCString());
    //如果取不到，说明加载失败}
    if (!sf) {
		CCLog(" SequencePet %d呼吸动作第一帧没有找到qqqqqqqqqqqqq}~~", petId);
        return false;
    }
    return initWithSpriteFrame(sf);
}

void SequencePet::setFPS(uint16 fps)
{
    m_wFps = fps;
}
CCSprite *SequencePet::getStandPic()
{
    //取呼吸动画第一帧作为默认图}
    PetConfig::STC_PET_CONFIG* pet = GET_CONFIG_STC(PetConfig, m_petId);
    if (!pet) {
        return NULL;
    }
    CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(PET_SEQUENCE_SPRITE_FRAME, pet->dwModelIndex, SEQ_ACT_STAND, 1)->getCString());
    //如果取不到，说明加载失败}
    if (!sf) {
//        CCLog(" SequencePet %d呼吸动作第一帧没有找到}~~", m_petId);}
        return NULL;
    }
    return CCSprite::createWithSpriteFrame(sf);
}

//按帧执行的动画}
void SequencePet::runFPSAction(SequenceFPSAction *action, FightPetSprite *pet)
{
    m_fpsAction = NULL;
    if (!action) {
        return;
    }
    m_fpsAction = action;
    m_fpsAction->setPosition(ccp(-1000,-1000));
    addChild(m_fpsAction);

    m_FightPetSprite = pet;
}
void SequencePet::callBackFPSAction()
{
    if (m_FightPetSprite) {
        m_FightPetSprite->afterAttact();
    }
}

