#include "CcbGachaResultEgg.h"
#include "EnumDefines.h"
#include "EffectLayer.h"
#include "CcbGachaResultLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbGachaResultEgg::~CcbGachaResultEgg()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteEgg1);
	CC_SAFE_RELEASE_NULL(m_pSpriteEgg2);
    CC_SAFE_RELEASE_NULL(m_pSpriteEgg3);
	CC_SAFE_RELEASE_NULL(m_pSpriteEgg4);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbGachaResultEgg( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbGachaResultEgg( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGachaResultEgg", CcbGachaResultEggLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_result_egg.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbGachaResultEgg::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbGachaResultEgg::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbGachaResultEgg::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbGachaResultEgg::onExit()
{
	CCLayer::onExit();
}

void CcbGachaResultEgg::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbGachaResultEgg::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEgg1", CCSprite*, this->m_pSpriteEgg1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEgg2", CCSprite*, this->m_pSpriteEgg2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEgg3", CCSprite*, this->m_pSpriteEgg3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEgg4", CCSprite*, this->m_pSpriteEgg4);

	return false;
}

bool CcbGachaResultEgg::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。}
    bool bRet = false;
    if (pTarget == this)
    {
        if (0 == strcmp(pMemberVariableName, "mCustomPropertyInt"))
        {
            this->mCustomPropertyInt = pCCBValue->getIntValue();
            CCLog("mCustomPropertyInt = %d", mCustomPropertyInt);
            bRet = true;
        }
        else if ( 0 == strcmp(pMemberVariableName, "mCustomPropertyFloat"))
        {
            this->mCustomPropertyFloat = pCCBValue->getFloatValue();
            CCLog("mCustomPropertyFloat = %f", mCustomPropertyFloat);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyBoolean"))
        {
            this->mCustomPropertyBoolean = pCCBValue->getBoolValue();
            CCLog("mCustomPropertyBoolean = %d", mCustomPropertyBoolean);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyString"))
        {
            this->mCustomPropertyString = pCCBValue->getStringValue();
            CCLog("mCustomPropertyString = %s", mCustomPropertyString.c_str());
            bRet = true;
        }
        
    }
    
    return bRet;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbGachaResultEgg::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "showBall", CcbGachaResultEgg::showBall);
    
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "removeSelf", CcbGachaResultEgg::removeSelf);
	return NULL;
}

SEL_MenuHandler CcbGachaResultEgg::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbGachaResultEgg::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGachaResultEgg::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbGachaResultEgg::loadData(uint8 type)
{
    quality = type;
    CCString* path = CCString::createWithFormat("ccbresources/12monthdate/gacha/dan%d.png", type);
    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(path->getCString());
    if (tex) {
        m_pSpriteEgg1->setTexture(tex);
        m_pSpriteEgg2->setTexture(tex);
        m_pSpriteEgg3->setTexture(tex);
        m_pSpriteEgg4->setTexture(tex);
    }
}

void CcbGachaResultEgg::showBall(CCNode* pNode)
{
    CCParticleSystemQuad* huashu = CCParticleSystemQuad::create("ccbresources/12monthdate/gacha/hanasu.plist");
    if (huashu) {
        huashu->setPosition(m_pSpriteEgg1->getPosition());
        m_pSpriteEgg1->getParent()->addChild(huashu);
    }
    
    CCParticleSystemQuad* ball = CCParticleSystemQuad::create("ccbresources/12monthdate/gacha/ball.plist");
    float time = 0;
    if (ball) {
        //        light->setPosition(CCPointZero);
        ball->setPosition(m_pSpriteEgg1->getPosition());
        time = MAX(time, ball->getDuration());
        m_pSpriteEgg1->getParent()->addChild(ball);
    }
    
    CCParticleSystemQuad* ball1 = CCParticleSystemQuad::create("ccbresources/12monthdate/gacha/ball1.plist");

    if (ball1) {
        ball1->setPosition(m_pSpriteEgg1->getPosition());
        m_pSpriteEgg1->getParent()->addChild(ball1);
    }
    
    
    
    this->runAction(CCSequence::create(CCDelayTime::create(time - 0.4),
                                       CCCallFunc::create(this, callfunc_selector(CcbGachaResultEgg::showEggLight)),
                                       NULL));
}

void CcbGachaResultEgg::showEggLight()
{
    float time = 0.2;
    CCString* path = CCString::createWithFormat("ccbresources/12monthdate/gacha/effectfly%d.plist", quality);
    CCParticleSystemQuad* eff = CCParticleSystemQuad::create(path->getCString());
    if (eff) {
        eff->setPosition(m_pSpriteEgg1->getPosition());
        time = MAX(time, eff->getDuration());
        m_pSpriteEgg1->getParent()->addChild(eff);
    }
    
//    EffectLayer *eff = EffectLayer::create(E_ANI_EFFECT_GACHA_EGGLIGHT, 1, 0.08);
//    m_pSpriteLight->setVisible(false);
//    eff->ignoreAnchorPointForPosition(false);
//    eff->setPosition(m_pSpriteLight->getPosition());
//    eff->setAnchorPoint(m_pSpriteLight->getAnchorPoint());
//    addChild(eff);
//    eff->onRun();
    
    this->runAction(CCSequence::create(CCDelayTime::create(time - 0.1),
                                       CCCallFunc::create(this, callfunc_selector(CcbGachaResultEgg::showFlashLight)),
                                       NULL));
}

void CcbGachaResultEgg::showFlashLight()
{
    float time = 0.2;
    
    CCString* path = CCString::createWithFormat("ccbresources/12monthdate/gacha/flashlight%d.plist", quality);
    CCParticleSystemQuad* flashLight = CCParticleSystemQuad::create(path->getCString());
    if (flashLight) {
        time = MAX(time, flashLight->getDuration());
    }
    flashLight->setPosition(m_pSpriteEgg1->getPosition());
    m_pSpriteEgg1->getParent()->addChild(flashLight);

    this->runAction(CCSequence::create(CCDelayTime::create(time - 0.1),
                                       CCCallFunc::create(this, callfunc_selector(CcbGachaResultEgg::showPet)),
                                       NULL));
}

void CcbGachaResultEgg::removeSelf(CCNode *pNode)
{
    
}

void CcbGachaResultEgg::showPet(){
    if (m_delegate) {
        m_delegate->showLight();
    }
}



