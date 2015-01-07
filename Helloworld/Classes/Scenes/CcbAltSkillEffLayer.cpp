#include "CcbAltSkillEffLayer.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "ConfigGet.h"
#include "EffectLayer.h"
#include "EnumDefines.h"
#include "GuideData.h"
#include "CcbPetBattleLayer.h"
#include "UISupport.h"
#include "MusicCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;


CCScene *AltSkillEffScene::scene()
{
    CCScene *scene = CCScene::create();
    
    AltSkillEffScene* layer = AltSkillEffScene::create();
    layer->setPosition(ccp(0, 210));
    scene->addChild(layer);
    return scene;
}

bool AltSkillEffScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbAltSkillEffLayer());
    
    return true;
}

CcbAltSkillEffLayer::~CcbAltSkillEffLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpritePet);
    CC_SAFE_RELEASE_NULL(m_pSpritePet_1);
    CC_SAFE_RELEASE_NULL(m_pSpritePet_2);
    CC_SAFE_RELEASE_NULL(m_pSpriteGuangZhu);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSkillName);
//    CC_SAFE_RELEASE_NULL(pauseActions);
//    CC_SAFE_RELEASE_NULL(pauseTargets);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbAltSkillEffLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbAltSkillEffLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbAltSkillEffLayer", CcbAltSkillEffLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight_scene.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/
void CcbAltSkillEffLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority * 2, true);
}
bool CcbAltSkillEffLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    CCRect rect;
    rect.origin = ccp(0, 0); //getWorldPos(this);
    rect.size = getContentSize();
    CCPoint p = convertToNodeSpace(pTouch->getLocation());
    if (rect.containsPoint(p)) {
        return true;
    }
    
    return false;
}
bool CcbAltSkillEffLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    setTouchEnabled(true);
	// code here
	return true;
}

void CcbAltSkillEffLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
    
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);

    runStart();
//        this->runAction(CCSequence::create(CCDelayTime::create(0.1),
//                                           CCCallFunc::create(this, callfunc_selector(CcbAltSkillEffLayer::runStart)),
//                                           NULL));
}

void CcbAltSkillEffLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbAltSkillEffLayer::onExit()
{
	CCLayer::onExit();
}

void CcbAltSkillEffLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbAltSkillEffLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet", CCSprite*, this->m_pSpritePet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet_1", CCSprite*, this->m_pSpritePet_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet_2", CCSprite*, this->m_pSpritePet_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteGuangZhu", CCSprite*, this->m_pSpriteGuangZhu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSkillName", CCLabelTTF*, this->m_pLabelTTFSkillName);
	return false;
}

bool CcbAltSkillEffLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbAltSkillEffLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onLight_1", CcbAltSkillEffLayer::onLight_1);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onLight_2", CcbAltSkillEffLayer::onLight_2);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onRemoveSalf", CcbAltSkillEffLayer::onRemoveSalf);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onLblLight", CcbAltSkillEffLayer::onLblLight);
	return NULL;
}

SEL_MenuHandler CcbAltSkillEffLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbAltSkillEffLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbAltSkillEffLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_petId = 0;
    counter = 0;
    m_pLabelTTFSkillName->setZOrder(101);
}

void CcbAltSkillEffLayer::loadData()
{
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_petId);
    if (!petCfg) {            
        CCString *str = CCString::createWithFormat("petId : %d not found~~", m_petId);
        CCMessageBox(str->getCString(), "ERROR");
        return;
    }
//    CCTexture2D* texture = CPetCtrl::GetPetBodyTexture(m_petId);
    m_pSpritePet->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(m_petId));
    m_pSpritePet_1->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(m_petId));
    m_pSpritePet_2->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(m_petId));
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *ultCfg = GET_CONFIG_STC(UltimateSkillConfig, m_skillId);
    if (!ultCfg) {
        CCString *str = CCString::createWithFormat("petId : %d ultimateskill（id：%d） not found~~", m_petId, petCfg->wInitialSkillId);
        CCMessageBox(str->getCString(), "ERROR");
        return;
    }
    m_pLabelTTFSkillName->setDimensions(CCSizeMake(25, 0));
    m_pLabelTTFSkillName->setString(ultCfg->strName.c_str());//convertStr(ultCfg->strName).c_str());
    m_pLabelTTFSkillName->setEnableStroke(ccBLACK, 1.5);
}

void CcbAltSkillEffLayer::runStart()
{
    if (m_delegate) {
        m_delegate->pauseAll();
    }
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_petId);
    if (petCfg) {
        CMusicCtrl::PlayEffect(GET_PET_SOUND(petCfg->wSoundAlt));
    }
    mAnimationManager->runAnimationsForSequenceNamed("act_start");
}
void CcbAltSkillEffLayer::runBg()
{
    m_pSpriteGuangZhu->runAction(CCRepeatForever::create(
                                                         CCSequence::create(CCMoveBy::create(2.0 / 60.0, ccp(550, 0)),
                                                                            CCMoveBy::create(2.0 / 60.0, ccp(-550, 0)),
                                                                            NULL)));
}
void CcbAltSkillEffLayer::runPet()
{
    mAnimationManager->runAnimationsForSequenceNamed("act_pet");
}

void CcbAltSkillEffLayer::onLight_1(cocos2d::CCNode* pNode)
{
    //开始闪电}
    EffectLayer* eff1 = EffectLayer::create(E_ANI_EFFECT_BATTLE_LIGHT, 1, 1.0/30);
    eff1->setPosition(ccp(120, 135) + ccp(-5, 0));
    eff1->ignoreAnchorPointForPosition(false);
    addChild(eff1, 100);
    eff1->onRun();
    
}
void CcbAltSkillEffLayer::onLight_2(cocos2d::CCNode* pNode)
{
    EffectLayer* eff1 = EffectLayer::create(E_ANI_EFFECT_BATTLE_LIGHT, 1, 1.0/30);
    eff1->setPosition(ccp(120, 135));
    eff1->ignoreAnchorPointForPosition(false);
    addChild(eff1, 100);
    eff1->onRun();
    
    EffectLayer* eff2 = EffectLayer::create(E_ANI_EFFECT_BATTLE_LIGHT, 1, 1.0/30);
    eff2->setPosition(ccp(200, 135));
    eff2->ignoreAnchorPointForPosition(false);
    eff2->setRotationY(180);
    addChild(eff2, 100);
    eff2->onRun();
    
}
void CcbAltSkillEffLayer::onLblLight(cocos2d::CCNode* pNode)
{
    //文字闪电}
    EffectLayer* effLbl = EffectLayer::create(E_ANI_EFFECT_BATTLE_LBL_LIGHT, 1, 1.0/30);
    effLbl->setPosition(m_pLabelTTFSkillName->getPosition() + ccp(-10, 0));
    effLbl->ignoreAnchorPointForPosition(false);
    effLbl->setAnchorPoint(ccp(0.5, 0.5));
    addChild(effLbl, 100);
    effLbl->onRun();
    
    runBg();
}
void CcbAltSkillEffLayer::onRemoveSalf(cocos2d::CCNode* pNode)
{
    if (m_delegate) {
        m_delegate->remuseAll();
    }
    this->removeFromParentAndCleanup(true);
}




