//
//  EffectLayer.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-2-25.}
//
//

#include "EffectLayer.h"
#include "ConfigData.h"
#include "ConfigGet.h"

#pragma mark EffectLayerProtocol
void EffectLayerProtocol::onActionOver()
{
    
}


#pragma mark EffectLayer
EffectLayer::EffectLayer() {
    delegate = NULL;
}

EffectLayer::~EffectLayer() {
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(strPlist.c_str());
}

EffectLayer* EffectLayer::create(uint16 effectId)
{
    return EffectLayer::create(effectId, 1, 0.2);
}

EffectLayer* EffectLayer::create(uint16 effectId, float fps)
{
    return EffectLayer::create(effectId, 1, fps);
}

EffectLayer* EffectLayer::create(uint16 effectId, int loop, float fps)
{
    EffectLayer* pRet = new EffectLayer();
    if (pRet && pRet->init(effectId, loop, fps)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool EffectLayer::init(uint16 effectId, int loop, float fps)
{
    if (!CCLayer::init()) {
        return false;
    }
    m_wEffectId = effectId;
    m_loop = loop;
    m_fps = fps;
    m_interval = 0;
    return true;
}

void EffectLayer::onEnter()
{
    CCLayer::onEnter();
    
    AnimationEffectConfig::STC_ANIMATION_EFFECT_CONFIG* pConfig = GET_CONFIG_STC(AnimationEffectConfig, m_wEffectId);
    if (!pConfig) {
        return;
    }
    
    CCString* plist = CCString::createWithFormat("%s.plist", pConfig->strPath.c_str());
    CCLog("Plist Path is:%s", plist->getCString());
    CCSpriteFrameCache* pSf = CCSpriteFrameCache::sharedSpriteFrameCache();
    pSf->addSpriteFramesWithFile(plist->getCString());
    strPlist = plist->getCString();
    
    CCSprite* pSprite = CCSprite::create();
    CCArray* pArray = CCArray::createWithCapacity(pConfig->wCnt);
    for (int i = 0; i < pConfig->wCnt; i++) {
        CCString* pStrName = CCString::createWithFormat("%s%d.png", pConfig->strName.c_str(), i+1);
        CCLog("Pic Path Name:%s", pStrName->getCString());
        CCSpriteFrame* pFrame = pSf->spriteFrameByName(pStrName->getCString());
        if (!pFrame) {
            CCLog("not found pic!!!");
            continue;
        }
        pArray->addObject(pFrame);
        if (i == 0) {
            pSprite->setDisplayFrame(pFrame);
        }
    }
    
    pSprite->setAnchorPoint(CCPointZero);
    pSprite->setPosition(CCPointZero);
    pSprite->setTag(11);
    addChild(pSprite);
    
    setContentSize(pSprite->getContentSize());
    
    CCAnimation* pAnimation = CCAnimation::createWithSpriteFrames(pArray, m_fps);
    CCAnimate* pAnimate = CCAnimate::create(pAnimation);
    
    m_pSeq = CCSequence::create(pAnimate, NULL);

    if (m_loop < 0) {
        m_fDuring = 0;
    }
    else
    {
        m_fDuring = m_loop * m_fps * pConfig->wCnt;
    }
}

void EffectLayer::setDelegate(EffectLayerProtocol *_delegate)
{
    delegate = _delegate;
}

void EffectLayer::onRun()
{
    CCSprite* pSprite = dynamic_cast<CCSprite*>(getChildByTag(11));
    if (!pSprite) {
        return;
    }
    if (m_loop < 0) {
        pSprite->runAction(CCRepeatForever::create(CCSequence::create(CCShow::create(),
                                                                      m_pSeq,
                                                                      CCHide::create(),
                                                                      CCDelayTime::create(m_interval),
                                                                      NULL)));
    }
    else
    {
        pSprite->runAction(CCSequence::create(CCRepeat::create(CCSequence::create(CCShow::create(),
                                                               m_pSeq,
                                                               CCHide::create(),
                                                               CCDelayTime::create(m_interval),
                                                               NULL),
                                                               m_loop),
                                              CCCallFunc::create(this, callfunc_selector(EffectLayer::onOver)),
                                              NULL));
    }
}
void EffectLayer::onOver()
{
    this->removeFromParentAndCleanup(true);
    if (delegate) {
        delegate->onActionOver();
    }
}

//设置图片为additive模式}
void EffectLayer::setSpriteAdd()
{
    CCSprite* pSprite = dynamic_cast<CCSprite*>(getChildByTag(11));
    if (!pSprite) {
        return;
    }
    ccBlendFunc bf = pSprite->getBlendFunc();
    bf.dst = GL_SRC_ALPHA;
    bf.src = GL_ONE;
    pSprite->setBlendFunc(bf);
}