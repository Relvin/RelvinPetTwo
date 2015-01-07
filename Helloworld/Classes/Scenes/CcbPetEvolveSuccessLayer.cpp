#include "CcbPetEvolveSuccessLayer.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "ConfigGet.h"
#include "SequencePet.h"
#include "SequenceAction.h"
#include "BackCtrl.h"
#include "MusicCtrl.h"
#include "EffectLayer.h"
#include "EnumDefines.h"

CCScene* PetEvolveSuccessScene::scene()
{
    CCScene* pScene = CCScene::create();
    PetEvolveSuccessScene* pLayer = PetEvolveSuccessScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool PetEvolveSuccessScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbPetEvolveSuccessLayer(this));
    return true;
}

void PetEvolveSuccessScene::onEnter()
{
    CCLayer::onEnter();
    //    m_pLabelTTFName->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFName->setString("宠物进化");
}

void PetEvolveSuccessScene::onExit()
{
    CCLayer::onExit();
}

void PetEvolveSuccessScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void PetEvolveSuccessScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}


CcbPetEvolveSuccessLayer::~CcbPetEvolveSuccessLayer()
{
    CC_SAFE_RELEASE_NULL(m_pSpritePet);
    CC_SAFE_RELEASE_NULL(m_pSpriteCenter);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPetName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurUp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurHp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAtt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurCover);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextUp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextHp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAtt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextCover);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurSpeDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextSpeDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillDes);
    CC_SAFE_RELEASE_NULL(m_pLayerInfoBg);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetEvolveSuccessLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetEvolveSuccessLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetEvolveSuccessLayer", CcbPetEvolveSuccessLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/arrowright.ccb]", [ccb/arrowright.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_evo_result.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

bool CcbPetEvolveSuccessLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void CcbPetEvolveSuccessLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (bTouchEnable) {
        bTouchEnable = false;
        CPet *pet = CPetCtrl::Get()->GetPetByObjId(CPetCtrl::Get()->GetEvolvePet());
        EvolveConfig::STC_EVOLVE_CONFIG *cfg = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv()));
        
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
        
        if (!cfg || cfg->wNextId == 0) {
            BackCtrl::BacktoUpperScene(kNormalTrans);
        }
        BackCtrl::BacktoUpperScene(kNormalTrans);
    }
}
void CcbPetEvolveSuccessLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool CcbPetEvolveSuccessLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbPetEvolveSuccessLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbPetEvolveSuccessLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetEvolveSuccessLayer::onExit()
{
	CCLayer::onExit();
}

void CcbPetEvolveSuccessLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetEvolveSuccessLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet", CCSprite*, this->m_pSpritePet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCenter", CCSprite*, this->m_pSpriteCenter);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetName", CCLabelTTF*, this->m_pLabelTTFPetName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurUp", CCLabelTTF*, this->m_pLabelTTFCurUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurHp", CCLabelTTF*, this->m_pLabelTTFCurHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAtt", CCLabelTTF*, this->m_pLabelTTFCurAtt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurCover", CCLabelTTF*, this->m_pLabelTTFCurCover);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurDef", CCLabelTTF*, this->m_pLabelTTFCurDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextUp", CCLabelTTF*, this->m_pLabelTTFNextUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextHp", CCLabelTTF*, this->m_pLabelTTFNextHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAtt", CCLabelTTF*, this->m_pLabelTTFNextAtt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextDef", CCLabelTTF*, this->m_pLabelTTFNextDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextCover", CCLabelTTF*, this->m_pLabelTTFNextCover);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurSpeDef", CCLabelTTF*, this->m_pLabelTTFCurSpeDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextSpeDef", CCLabelTTF*, this->m_pLabelTTFNextSpeDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillDes", CCLabelTTF*, this->m_pLabelTTFPassiveSkillDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInfoBg", CCLayer*, this->m_pLayerInfoBg);

	return false;
}

bool CcbPetEvolveSuccessLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetEvolveSuccessLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetEvolveSuccessLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetEvolveSuccessLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetEvolveSuccessLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pLayerInfoBg->setVisible(false);
    m_pSpritePet->setVisible(false);
    bTouchEnable = false;
    m_pSpriteCenter->setZOrder(2);
    ///Users/sky_zmy/Documents/pet2/resource/ccbresources/12monthdate/pet.evo.enhance/slash1.plist
}

void CcbPetEvolveSuccessLayer::loadData()
{
    uint32 dwPetObjId = CPetCtrl::Get()->GetEvolvePet();
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(dwPetObjId);
    if (!pet) {
        return;
    }
    
    PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    m_pLabelTTFPetName->setString(pCfg->strName.c_str());
    
    //进化后}
    CCString *str = CCString::createWithFormat("+%d", pet->GetbyEvolveLv());
    m_pLabelTTFNextUp->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwHpValue());
    m_pLabelTTFNextHp->setString(str->getCString());
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* norCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->GetwNormaleAttId());
    if (norCfg && norCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
        str->initWithFormat("%d", pet->GetdwSAttackValue());
    }
    else{
        str->initWithFormat("%d", pet->GetdwAttackValue());
    }
    m_pLabelTTFNextAtt->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwDefenseValue());
    m_pLabelTTFNextDef->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwSDefenseValue());
    m_pLabelTTFNextSpeDef->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwRecoverValue());
    m_pLabelTTFNextCover->setString(str->getCString());
    
    //解锁技能
    EvolveConfig::STC_EVOLVE_CONFIG* cfgPer = NULL;
    cfgPer = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv()));
    if (cfgPer && cfgPer->dwAddSkillId1) {
        m_pLabelTTFPassiveSkillName->getParent()->setVisible(true);
        std::string name = "";
        std::string des = "";
        if (cfgPer->dwAddSkillId1 / E_UNITE_BASE_FABIO == E_SKILL_TYPE_PASSIVE) {
            PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *cfg = GET_CONFIG_STC(PassiveSkillConfig, cfgPer->dwAddSkillId1);
            if (cfg) {
                name = cfg->strName;
                des = cfg->strDes;
            }
        }
        else
        {
            TalentConfig::STC_TALENT_CONFIG *cfg = GET_CONFIG_STC(TalentConfig, cfgPer->dwAddSkillId1);
            if (cfg) {
                name = cfg->strName;
                des = cfg->strDes;
            }
        }
        m_pLabelTTFPassiveSkillName->setString(name.c_str());
        m_pLabelTTFPassiveSkillDes->setString(des.c_str());
    }
    else{
        m_pLabelTTFPassiveSkillName->getParent()->setVisible(false);
    }
    //进化前}
    cfgPer = NULL;
    cfgPer = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv() - 1)); //同index前一阶的情况}
    if (!cfgPer) {
        uint16 evoId = GET_EVOLVE_ID((pet->GetwIndex() - 1), (pet->GetbyEvolveLv() - 1));
        cfgPer = GET_CONFIG_STC(EvolveConfig, evoId); //低一index，前一阶的情况}
    }
    
    if (cfgPer) {
        SequencePet* mc = SequencePet::create(cfgPer->wNextPetId);
        mc->setPosition(CPetCtrl::Get()->ConvertFlccPos(cfgPer->wNextPetId, getWidth(mc), m_pSpritePet->getPosition()));
        mc->setTag(11);
        mc->setAnchorPoint(ccp(0.5, 0));
        mc->runAction(CCRepeatForever::create(SequenceAction::create(mc, SEQ_ACT_STAND)));
        m_pSpriteCenter->addChild(mc);
    }
    
    STC_PET_BASE_INFO perInfo = CPetCtrl::Get()->getEvoPerData();

    str->initWithFormat("+%d", pet->GetbyEvolveLv() - 1);
    m_pLabelTTFCurUp->setString(str->getCString());
    
    str->initWithFormat("%d", perInfo.dwHp);
    m_pLabelTTFCurHp->setString(str->getCString());
    
    if (norCfg && norCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
        str->initWithFormat("%d", perInfo.dwSAtk);
    }
    else{
        str->initWithFormat("%d", perInfo.dwCAtk);
    }
    m_pLabelTTFCurAtt->setString(str->getCString());
    
    str->initWithFormat("%d", perInfo.dwCDef);
    m_pLabelTTFCurDef->setString(str->getCString());
    
    str->initWithFormat("%d", perInfo.dwSDef);
    m_pLabelTTFCurSpeDef->setString(str->getCString());
    
    str->initWithFormat("%d", perInfo.dwRev);
    m_pLabelTTFCurCover->setString(str->getCString());

    
    
    
    CCParticleSystemQuad *eff4 = CCParticleSystemQuad::create("ccbresources/12monthdate/pet.evo.enhance/slash4.plist");
    eff4->setPosition(ccp(160, 240));
    addChild(eff4);
    
    this->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetEvolveSuccessLayer::showEff1)),
                                       NULL));
    
}

void CcbPetEvolveSuccessLayer::showEff1()
{
    CCParticleSystemQuad *eff = CCParticleSystemQuad::create("ccbresources/12monthdate/pet.evo.enhance/slash3.plist");
    m_pSpriteCenter->addChild(eff);
    eff->setPosition(m_pSpritePet->getPosition());
    
    CCParticleSystemQuad *eff5 = CCParticleSystemQuad::create("ccbresources/12monthdate/pet.evo.enhance/slash5.plist");
    m_pSpriteCenter->addChild(eff5);
    eff5->setPosition(ccp(m_pSpritePet->getPosition().x, -m_pSpriteCenter->getPositionY() - 20));
    
    this->runAction(CCSequence::create(CCDelayTime::create(eff->getDuration() - 0.1),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetEvolveSuccessLayer::showEff2)),
                                       NULL));
    
    m_pSpriteCenter->runAction(CCSequence::create(CCDelayTime::create(eff->getDuration()*0.25),
                                                  CCMoveBy::create(eff->getDuration() * 0.5, ccp(0, 180)),
                                                  NULL));
}

void CcbPetEvolveSuccessLayer::showEff2()
{
    CCParticleSystemQuad *eff = CCParticleSystemQuad::create("ccbresources/12monthdate/pet.evo.enhance/slash2.plist");
    m_pSpriteCenter->addChild(eff, 2);
    eff->setPosition(m_pSpritePet->getPosition() + ccp(0, getHeight(m_pSpritePet) * 0.5));
    this->runAction(CCSequence::create(CCDelayTime::create(eff->getDuration() - 0.3),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetEvolveSuccessLayer::showEff3)),
                                       NULL));
    
}

void CcbPetEvolveSuccessLayer::showEff3()
{
    CCParticleSystemQuad *eff = CCParticleSystemQuad::create("ccbresources/12monthdate/pet.evo.enhance/slash1.plist");
    m_pSpriteCenter->addChild(eff, 3);
    eff->setPosition(m_pSpritePet->getPosition() + ccp(0, getHeight(m_pSpritePet) * 0.5));
    
    
    if (m_pSpriteCenter->getChildByTag(11))
    {
        m_pSpriteCenter->removeChildByTag(11);
        
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_pet_evolve));
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(CPetCtrl::Get()->GetEvolvePet());
    
    if (pet->GetbyEvolveLv() >= 6) {
        EffectLayer* effL2 = EffectLayer::create(E_ANI_EFFECT_PET_BG_ORANGE, -1, 1.0 / 10);
        effL2->setPosition(m_pSpritePet->getPosition() - ccp(0, 20));
        effL2->setAnchorPoint(ccp(0.5, 0));
        effL2->ignoreAnchorPointForPosition(false);
        m_pSpriteCenter->addChild(effL2, 1, 112);
        effL2->onRun();
    }
    
    SequencePet* mc = SequencePet::create(pet->GetwIndex());
    mc->setPosition(CPetCtrl::Get()->ConvertFlccPos(pet->GetwIndex(), getWidth(mc), m_pSpritePet->getPosition()));
    mc->setTag(11);
    mc->setAnchorPoint(ccp(0.5, 0));
    mc->runAction(CCRepeatForever::create(SequenceAction::create(mc, SEQ_ACT_STAND)));
    m_pSpriteCenter->addChild(mc, 1);
    
    CCParticleSystemQuad *eff6 = CCParticleSystemQuad::create("ccbresources/12monthdate/pet.evo.enhance/slash6.plist");
    m_pSpriteCenter->addChild(eff6, 0);
    eff6->setPosition(m_pSpritePet->getPosition() + ccp(0, getHeight(m_pSpritePet) * 0.5));
    
    
    m_pLayerInfoBg->setScale(0.1);
    m_pLayerInfoBg->setVisible(true);
    m_pLayerInfoBg->runAction(CCSequence::create(CCScaleTo::create(0.2, 1.1),
                                                  CCScaleTo::create(0.05, 0.9),
                                                  CCScaleTo::create(0.05, 1),
                                                  CCDelayTime::create(0.2),
                                                  CCCallFunc::create(this, callfunc_selector(CcbPetEvolveSuccessLayer::openTouch)),
                                                  NULL));
}

void CcbPetEvolveSuccessLayer::openTouch()
{
    bTouchEnable = true;
}



