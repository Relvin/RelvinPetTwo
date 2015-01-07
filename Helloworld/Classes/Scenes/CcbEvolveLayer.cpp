#include "CcbEvolveLayer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "FlccMovieClip.h"
#include "FlccMovieAction.h"
#include "Role.h"
#include "GameSession.h"
#include "ItemDataMgr.h"
#include "UISupport.h"
#include "SequencePet.h"
#include "SequenceAction.h"
#include "PetLoadingLayer.h"
#include "CcbPetIcon.h"
#include "CcbItemIconLayer.h"
#include "BackCtrl.h"
#include "GuideData.h"
#include "CcbDropTipLayer.h"
#include "MusicCtrl.h"
#include "PacketDataMgr.h"
#include "ResourceStringClient.h"
#include "EffectLayer.h"
#include "Emblem.h"
#include "EmblemDataMgr.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark CcbEvolve  Scene
EvolveScene::~EvolveScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* EvolveScene::scene()
{
    CCScene* pScene = CCScene::create();
    EvolveScene* pLayer = EvolveScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool EvolveScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbEvolveLayer(this));
    return true;
}

void EvolveScene::onEnter()
{
    CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_unit_2));
}

void EvolveScene::onExit()
{
    CCLayer::onExit();
}

void EvolveScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void EvolveScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

bool EvolveScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName );
	return false;
}

bool EvolveScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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

#pragma mark CcbEvolve Layer
CcbEvolveLayer::~CcbEvolveLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonEvo);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMoney);
	CC_SAFE_RELEASE_NULL(m_pSprite_no_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNum01);
	CC_SAFE_RELEASE_NULL(m_pSprite_no_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNum02);
	CC_SAFE_RELEASE_NULL(m_pSprite_no_3);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNum03);
	CC_SAFE_RELEASE_NULL(m_pSprite_no_4);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNum04);
	CC_SAFE_RELEASE_NULL(m_pSprite_no_5);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNum05);
	CC_SAFE_RELEASE_NULL(m_pSpriteBase_2);
	CC_SAFE_RELEASE_NULL(m_pSpritePet_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAdd2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDef_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRev_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAtt_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFHp_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv_2);
	CC_SAFE_RELEASE_NULL(m_pSpriteBase_1);
	CC_SAFE_RELEASE_NULL(m_pSpritePet_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAdd1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDef_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRev_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAtt_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFHp_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMsg);
    CC_SAFE_RELEASE_NULL(m_pLyaerPet1Bg);
	CC_SAFE_RELEASE_NULL(m_pLyaerPet2Bg);
    
    CC_SAFE_RELEASE_NULL(m_pLayerElem1);
    CC_SAFE_RELEASE_NULL(m_pLayerElem2);
    CC_SAFE_RELEASE_NULL(m_pLayerElem3);
    CC_SAFE_RELEASE_NULL(m_pLayerElem4);
    CC_SAFE_RELEASE_NULL(m_pLayerElem5);
    
    CC_SAFE_RELEASE_NULL(m_pControlButtonEvoSearch);
    
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSpeDef_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSpeDef_1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName);
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 CCNode* LoadCcbEvolveLayer( CCObject* owner );
 
 //CcbManager.cpp
 CCNode* CcbManager::LoadCcbEvolveLayer( CCObject* owner ) {
 CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
 pLoaderLib->registerCCNodeLoader( "CcbEvolveLayer", CcbEvolveLayerLoader::loader() );
 pLoaderLib->registerCCNodeLoader( "[ccb/arrowright.ccb]", [ccb/arrowright.ccb]Loader::loader() );
 
 
 CCBReader* pCCBReader = new CCBReader(pLoaderLib);
 CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_evo.ccbi", owner);
 pCCBReader->release();
 
 return pNode;
 }
 */


bool CcbEvolveLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_dwPetObId = 0;
	return true;
}

void CcbEvolveLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    //    m_pLyaerBg->setPositionX(m_pLyaerBg->getPositionX() + CCDirector::sharedDirector()->getWinSize().width);
    
    loadData();
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonEvo, GuideBtnPos::E_COMFIRM_EVOLVE);
    }
}

void CcbEvolveLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbEvolveLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbEvolveLayer::addGuideLayer()
{
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_1_PET_EVOLVE,
                                             GuideData::E_GUIDE_TRIGGER_PET_EVOLVE_1_TALK,
                                             NULL
                                             );
}

void CcbEvolveLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEvolveLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEvolveLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEvo", CCControlButton*, this->m_pControlButtonEvo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMoney", CCLabelTTF*, this->m_pLabelTTFMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_no_1", CCSprite*, this->m_pSprite_no_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNum01", CCLabelTTF*, this->m_pLabelTTFNum01);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_no_2", CCSprite*, this->m_pSprite_no_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNum02", CCLabelTTF*, this->m_pLabelTTFNum02);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_no_3", CCSprite*, this->m_pSprite_no_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNum03", CCLabelTTF*, this->m_pLabelTTFNum03);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_no_4", CCSprite*, this->m_pSprite_no_4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNum04", CCLabelTTF*, this->m_pLabelTTFNum04);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_no_5", CCSprite*, this->m_pSprite_no_5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNum05", CCLabelTTF*, this->m_pLabelTTFNum05);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBase_2", CCSprite*, this->m_pSpriteBase_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet_2", CCSprite*, this->m_pSpritePet_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAdd2", CCLabelTTF*, this->m_pLabelTTFAdd2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDef_2", CCLabelTTF*, this->m_pLabelTTFDef_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRev_2", CCLabelTTF*, this->m_pLabelTTFRev_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAtt_2", CCLabelTTF*, this->m_pLabelTTFAtt_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFHp_2", CCLabelTTF*, this->m_pLabelTTFHp_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv_2", CCLabelTTF*, this->m_pLabelTTFLv_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBase_1", CCSprite*, this->m_pSpriteBase_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet_1", CCSprite*, this->m_pSpritePet_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAdd1", CCLabelTTF*, this->m_pLabelTTFAdd1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDef_1", CCLabelTTF*, this->m_pLabelTTFDef_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRev_1", CCLabelTTF*, this->m_pLabelTTFRev_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAtt_1", CCLabelTTF*, this->m_pLabelTTFAtt_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFHp_1", CCLabelTTF*, this->m_pLabelTTFHp_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv_1", CCLabelTTF*, this->m_pLabelTTFLv_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMsg", CCLabelTTF*, this->m_pLabelTTFMsg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLyaerPet1Bg", CCLayer*, this->m_pLyaerPet1Bg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLyaerPet2Bg", CCLayer*, this->m_pLyaerPet2Bg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem1", CcbItemIconLayer*, this->m_pLayerElem1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem2", CcbItemIconLayer*, this->m_pLayerElem2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem3", CcbItemIconLayer*, this->m_pLayerElem3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem4", CcbItemIconLayer*, this->m_pLayerElem4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem5", CcbItemIconLayer*, this->m_pLayerElem5);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEvoSearch", CCControlButton*, this->m_pControlButtonEvoSearch);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSpeDef_2", CCLabelTTF*, this->m_pLabelTTFSpeDef_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSpeDef_1", CCLabelTTF*, this->m_pLabelTTFSpeDef_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurName", CCLabelTTF*, this->m_pLabelTTFCurName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextName", CCLabelTTF*, this->m_pLabelTTFNextName);
	return false;
}

bool CcbEvolveLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEvolveLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler CcbEvolveLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_CCControlHandler CcbEvolveLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEvo", CcbEvolveLayer::onPressControlButtonEvo);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonElem", CcbEvolveLayer::onPressControlButtonElem);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEvoSearch", CcbEvolveLayer::onPressControlButtonEvoSearch);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEvolveLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    
}

void CcbEvolveLayer::onPressControlButtonElem(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    int tag = ((CCNode*)pSender)->getTag();
    tag--;
    if (tag >= 0 && tag < arrElemId.size()) {
        uint32 itemId = arrElemId[tag];
        EvolveInfoConfig::STC_EVOLVE_INFO_CONFIG* cfg = GET_CONFIG_STC(EvolveInfoConfig, itemId);
        if (cfg) {
//            CcbDropTipLayer::showDropTip(itemId);
        }
    }
}

void CcbEvolveLayer::onPressControlButtonEvo(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CPetCtrl::Get()->DoEvolvePet();
    if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_PET_EVOLVE_1_TALK) {
        GuideData::GetInstance()->connectToServer();    // send 1303 to server
    }
}

void CcbEvolveLayer::onPressControlButtonEvoSearch(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    showEvoInfo();
}


void CcbEvolveLayer::setPetObjectId(uint32 dwObId)
{
    if (dwObId && m_dwPetObId != dwObId) {
        m_dwPetObId = dwObId;
        loadData();
    }
}

void CcbEvolveLayer::loadData()
{
    m_dwPetObId = CPetCtrl::Get()->GetEvolvePet();
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(m_dwPetObId);
    if (!pet) {
        return;
    }
    
    //一、进化前信息}
    //flcc
    EffectLayer* effL = dynamic_cast<EffectLayer*>(m_pLyaerPet1Bg->getChildByTag(112));
    if (effL) {
        effL->removeFromParentAndCleanup(true);
    }
    if (pet->GetbyEvolveLv() >= 6) {
        effL = EffectLayer::create(E_ANI_EFFECT_PET_BG_ORANGE, -1, 1.0 / 10);
        effL->setPosition(m_pSpritePet_1->getPosition() - ccp(0, 20));
        effL->setAnchorPoint(ccp(0.5, 0));
        effL->ignoreAnchorPointForPosition(false);
        m_pLyaerPet1Bg->addChild(effL, 1, 112);
        effL->onRun();
    }
    
    SequencePet *mc1 = SequencePet::create(pet->GetwIndex());
    if (mc1) {
        //        mc1->setScale(0.5);
        mc1->setPosition(CPetCtrl::Get()->ConvertFlccPos(pet->GetwIndex(), getWidth(mc1), m_pSpritePet_1->getPosition()));
        mc1->setAnchorPoint(ccp(0.5, 0));
        mc1->runAction(CCRepeatForever::create(SequenceAction::create(mc1, SEQ_ACT_STAND)));
        m_pLyaerPet1Bg->addChild(mc1, 2);
    }
    //基本信息}
    PetConfig::STC_PET_CONFIG *pConfig1 = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    
    CCString *str = CCString::create("");
    m_pLabelTTFCurName->setString(pConfig1->strName.c_str());
    
    str->initWithFormat("%s%d", SB_Lv, pet->GetbyLv());
    m_pLabelTTFLv_1->setString(str->getCString());
    m_pLabelTTFLv_2->setString(str->getCString());
    
    str->initWithFormat("+%d", pet->GetbyEvolveLv());
    m_pLabelTTFAdd1->setString(str->getCString());
    m_pLabelTTFAdd1->setPositionX(getRight(m_pLabelTTFCurName) + 8);
    
    str->initWithFormat("%d", pet->GetdwHpValue());
    m_pLabelTTFHp_1->setString(str->getCString());
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* norCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->GetwNormaleAttId());
    if (norCfg && norCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
        str->initWithFormat("%d", pet->GetdwSAttackValue());
    }
    else{
        str->initWithFormat("%d", pet->GetdwAttackValue());
    }
    m_pLabelTTFAtt_1->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwDefenseValue());
    m_pLabelTTFDef_1->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwSDefenseValue());
    m_pLabelTTFSpeDef_1->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwRecoverValue());
    m_pLabelTTFRev_1->setString(str->getCString());
    
    m_pSpriteBase_1->setTexture(CPetCtrl::Get()->GetBaseTextureByPet(pet->GetwIndex()));
    m_pSpriteBase_2->setTexture(CPetCtrl::Get()->GetBaseTextureByPet(pet->GetwIndex()));
    
    
    STC_PET_BASE_INFO baseInfo;
    baseInfo.dwHp = pet->GetdwHpValue();
    baseInfo.dwCAtk = pet->GetdwAttackValue();
    baseInfo.dwCDef = pet->GetdwDefenseValue();
    baseInfo.dwSAtk = pet->GetdwSAttackValue();
    baseInfo.dwSDef = pet->GetdwSDefenseValue();
    baseInfo.dwRev = pet->GetdwRecoverValue();
    CPetCtrl::Get()->setEvoPerData(baseInfo);
    //二、取进化后petConfig}
    //    uint32 nextEvoId = GET_EVOLVE_ID(pet->GetwIndex(), 1);
    //    if (pet->GetbyEvolveLv() > 0) {
    EvolveConfig::STC_EVOLVE_CONFIG *eConfig = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv()));
    uint32 nextEvoId = eConfig->wNextId;
    //    }
    
    EvolveConfig::STC_EVOLVE_CONFIG *evoConfig = GET_CONFIG_STC(EvolveConfig, nextEvoId);
    
    uint16 nextId = evoConfig->wNextPetId;
    
    
    //三、进化后信息}
    
    EffectLayer* effL2 = dynamic_cast<EffectLayer*>(m_pLyaerPet2Bg->getChildByTag(112));
    if (effL2) {
        effL2->removeFromParentAndCleanup(true);
    }

    if (evoConfig->byLv >= 6) {
        effL2 = EffectLayer::create(E_ANI_EFFECT_PET_BG_ORANGE, -1, 1.0 / 10);
        effL2->setPosition(m_pSpritePet_2->getPosition() - ccp(0, 20));
        effL2->setAnchorPoint(ccp(0.5, 0));
        effL2->ignoreAnchorPointForPosition(false);
        m_pLyaerPet2Bg->addChild(effL2, 1, 112);
        effL2->onRun();
    }
    
    SequencePet *mc2 = SequencePet::create(nextId);
    mc2->setAnchorPoint(ccp(0.5, 0));
    mc2->setPosition(CPetCtrl::Get()->ConvertFlccPos(nextId, getWidth(mc2), m_pSpritePet_2->getPosition()));
    mc2->runAction(CCRepeatForever::create(SequenceAction::create(mc2, SEQ_ACT_STAND)));
    
    m_pLyaerPet2Bg->addChild(mc2, 2);
    
    //    m_pLyaerPet2Bg->addChild(clipper);
    //基本信息}
    STC_PET_BASE_INFO embBAdd;
    STC_PET_BASE_INFO embAdd;
    STC_PET_BASE_INFO baseAdd;
    baseInfo = CPetCtrl::Get()->getPetBaseValueByObjId(m_dwPetObId);
    embBAdd = CPetCtrl::Get()->getEmblemAddValue(m_dwPetObId, baseInfo);
    
    baseAdd.dwHp = baseInfo.dwHp + evoConfig->dwAddHP;
    baseAdd.dwCAtk = baseInfo.dwCAtk + evoConfig->dwAddCATK;
    baseAdd.dwCDef = baseInfo.dwCDef + evoConfig->dwAddCDEF;
    baseAdd.dwSAtk = baseInfo.dwSAtk + evoConfig->dwAddSATK;
    baseAdd.dwSDef = baseInfo.dwSDef + evoConfig->dwAddSDEF;
    baseAdd.dwRev = baseInfo.dwRev + evoConfig->dwAddREV;
    embAdd = CPetCtrl::Get()->getEmblemAddValue(m_dwPetObId, baseAdd);
    
    PetConfig::STC_PET_CONFIG * pCfg_2 = GET_CONFIG_STC(PetConfig, nextId);
    m_pLabelTTFNextName->setString(pCfg_2->strName.c_str());
    
    str->initWithFormat("+%d", evoConfig->byLv);
    m_pLabelTTFAdd2->setString(str->getCString());
    m_pLabelTTFAdd2->setPositionX(getRight(m_pLabelTTFNextName) + 8);

    str->initWithFormat("%d", evoConfig->dwAddHP + pet->GetdwHpValue() + embAdd.dwHp - embBAdd.dwHp);
    m_pLabelTTFHp_2->setString(str->getCString());
    
    if (norCfg && norCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
        str->initWithFormat("%d", evoConfig->dwAddSATK + pet->GetdwSAttackValue() + embAdd.dwSAtk - embBAdd.dwSAtk);
    }
    else{
        str->initWithFormat("%d", evoConfig->dwAddCATK + pet->GetdwAttackValue() + embAdd.dwCAtk - embBAdd.dwCAtk);
    }
    m_pLabelTTFAtt_2->setString(str->getCString());
    
    str->initWithFormat("%d", evoConfig->dwAddCDEF + pet->GetdwDefenseValue() + embAdd.dwCDef- embBAdd.dwCDef);
    m_pLabelTTFDef_2->setString(str->getCString());
    
    str->initWithFormat("%d", evoConfig->dwAddSDEF + pet->GetdwSDefenseValue() + embAdd.dwSDef - embBAdd.dwSDef);
    m_pLabelTTFSpeDef_2->setString(str->getCString());
    
    str->initWithFormat("%d", evoConfig->dwAddREV + pet->GetdwRecoverValue() + embAdd.dwRev - embBAdd.dwRev);
    m_pLabelTTFRev_2->setString(str->getCString());
    
    
    //解锁技能
    if (evoConfig && evoConfig->dwAddSkillId1) {
        m_pLabelTTFPassiveSkillName->getParent()->setVisible(true);
        std::string name = "";
        if (evoConfig->dwAddSkillId1 / E_UNITE_BASE_FABIO == E_SKILL_TYPE_PASSIVE) {
            PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *cfg = GET_CONFIG_STC(PassiveSkillConfig, evoConfig->dwAddSkillId1);
            if (cfg) {
                name = cfg->strName;
            }
        }
        else
        {
            TalentConfig::STC_TALENT_CONFIG *cfg = GET_CONFIG_STC(TalentConfig, evoConfig->dwAddSkillId1);
            if (cfg) {
                name = cfg->strName;
            }
        }
        m_pLabelTTFPassiveSkillName->setString(name.c_str());
    }
    else{
        m_pLabelTTFPassiveSkillName->getParent()->setVisible(false);
    }
    
    //四、取进化信息}
    
    //进化材料}
    int len = 0;
    GET_ARRAY_LEN(evoConfig->wEvoItemId, len);
    std::vector<CcbItemIconLayer *> arrElem;
    arrElem.push_back(m_pLayerElem1);
    arrElem.push_back(m_pLayerElem2);
    arrElem.push_back(m_pLayerElem3);
    arrElem.push_back(m_pLayerElem4);
    arrElem.push_back(m_pLayerElem5);
    
    std::vector<CCLabelTTF *> arrElemNo;
    arrElemNo.push_back(m_pLabelTTFNum01);
    arrElemNo.push_back(m_pLabelTTFNum02);
    arrElemNo.push_back(m_pLabelTTFNum03);
    arrElemNo.push_back(m_pLabelTTFNum04);
    arrElemNo.push_back(m_pLabelTTFNum05);
    
    std::vector<CCSprite *> arrSpritNo;
    arrSpritNo.push_back(m_pSprite_no_1);
    arrSpritNo.push_back(m_pSprite_no_2);
    arrSpritNo.push_back(m_pSprite_no_3);
    arrSpritNo.push_back(m_pSprite_no_4);
    arrSpritNo.push_back(m_pSprite_no_5);
    
    arrElemId.clear();
    int c = -1;
    std::map<uint16, std::vector<CcbItemIconLayer*> > mapPet;
    mapPet.clear();
    bool emFlag = true;
    for (int i = 0; i < len; i++) {
        arrElem[i]->getParent()->setVisible(false);
        
        uint32 itemId = evoConfig->wEvoItemId[i];
        if (!itemId) {
            continue;
        }
        arrElemId.push_back(itemId);
        c++;
        CcbItemIconLayer* eiem = arrElem[c];
        eiem->getParent()->setVisible(true);
        eiem->loadIndexData(itemId);
        eiem->showIconOnly();
        eiem->setBtnEnable(true);
        eiem->setIsShowDropInfo(true);
        
        arrSpritNo[c]->setZOrder(3);
        arrSpritNo[c]->setVisible(false);
        
        uint32 dwCurCount = 0;
        PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, itemId);
        if (pCfg) {
            dwCurCount = CPetCtrl::Get()->getPetNumByIndex(pCfg->wIndex);
            if (pet->GetwIndex() == pCfg->wIndex) {
                dwCurCount--;
            }
            if (mapPet.find(pCfg->wIndex) != mapPet.end()) {
                mapPet[pCfg->wIndex].push_back(eiem);
            }
            else
            {
                std::vector<CcbItemIconLayer*> vecPet;
                vecPet.push_back(eiem);
                mapPet[pCfg->wIndex] = vecPet;
            }
        }
        
        ItemConfig::STC_ITEM_CONFIG *iConfig = GET_CONFIG_STC(ItemConfig, itemId);
        if (iConfig) {
            
            dwCurCount = g_PacketDataMgr->GetItemCountByIndex(itemId);//changed by lixiaojun 2014/1/27
            //物品不足时加遮罩}
            if (dwCurCount < evoConfig->byEvoItemCnt[i]) {
                CCLayerColor *cLayer = CCLayerColor::create(ccc4(0, 0, 0, 255));
                cLayer->setContentSize(eiem->getContentSize());
                cLayer->setOpacity(150);
                cLayer->setPosition(CCPointZero - ccp(0.5, 0.5));
                cLayer->ignoreAnchorPointForPosition(false);
                eiem->getParent()->addChild(cLayer);
                emFlag = false;
                
                arrSpritNo[c]->setVisible(true);
                arrSpritNo[c]->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.5),
                                                                                    CCFadeIn::create(1.5),
                                                                                    NULL)));
            }
        }
        
        CCString *str = CCString::createWithFormat("%d / %d", dwCurCount, evoConfig->byEvoItemCnt[i]);
        arrElemNo[c]->setVisible(true);
        arrElemNo[c]->setString(str->getCString());
        arrElemNo[c]->setZOrder(3);
    }
    
    //宠物不足时加遮罩}
    std::map<uint16, std::vector<CcbItemIconLayer*> >::iterator it = mapPet.begin();
    for (; it != mapPet.end(); it++) {
        std::vector<CcbItemIconLayer*> vctPet = it->second;
        if (vctPet.size() == 0) {
            continue;
        }
        int num = CPetCtrl::Get()->getPetNumByIndex(it->first);
        
        if (pet->GetwIndex() == it->first) {
            num--;
        }
        
        for (int i = 0; i < vctPet.size(); i++) {
            CcbItemIconLayer *eiem = vctPet[i];
            if (num > 0) {
                num--;
                continue;
            }
            CCLayerColor *cLayer = CCLayerColor::create(ccc4(0, 0, 0, 255));
            cLayer->setContentSize(eiem->getContentSize());
            cLayer->setOpacity(150);
            cLayer->setPosition(CCPointZero - ccp(0.5, 0.5));
            cLayer->ignoreAnchorPointForPosition(false);
            eiem->getParent()->addChild(cLayer);
            emFlag = false;
            
            for (int i = 0; i < arrElem.size(); i++) {
                if (arrElem[i] == eiem) {
                    arrSpritNo[i]->setVisible(true);
                    arrSpritNo[i]->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.5),
                                                                                        CCFadeIn::create(1.5),
                                                                                        NULL)));
                    break;
                }
            }
            
            
        }
    }
    
    //进化金钱}
    uint32 cost = evoConfig->dwNeedMoney;//pConfig1->byStarLv * 50000;
    str->initWithFormat("%d", cost);
    m_pLabelTTFMoney->setString(str->getCString());
    if (CGameSession::GetRole()->GetdwCoin() < cost)
    {
        m_pLabelTTFMoney->setColor(ccRED);
        //        m_pLabelTTFMsg->setString("金币不足");
    }
    //判断可否进化，给出提示信息}
    m_pLabelTTFMsg->setVisible(true);
    m_pControlButtonEvo->setEnabled(false);
    
    m_pLabelTTFMsg->runAction(CCRepeatForever::create(CCBlink::create(1.5, 1)));
    
    if (pet->GetbyLv() < evoConfig->wPetLv) {
        str->initWithFormat(GET_STR(Str_can_evo), evoConfig->wPetLv);
        m_pLabelTTFMsg->setString(str->getCString());
    }
    else if (CGameSession::GetRole()->GetdwCoin() < cost)
    {
        m_pLabelTTFMsg->setString(GET_STR(Str_no_money));
    }
    else if (!emFlag)         //材料不足}
    {
        m_pLabelTTFMsg->setString(GET_STR(Str_no_evo_emlm));
    }
    else
    {
        m_pLabelTTFMsg->stopAllActions();
        m_pLabelTTFMsg->setVisible(false);
        m_pControlButtonEvo->setEnabled(true);
    }
    
    m_pSpritePet_1->setVisible(false);
    m_pSpritePet_2->setVisible(false);
}

void CcbEvolveLayer::showEvoInfo()
{
    if (!m_evoInfoLayer) {
        m_evoInfoLayer = CcbManager::sharedManager()->LoadCcbEvoInfoListLayer();
        m_evoInfoLayer->ignoreAnchorPointForPosition(false);
        m_evoInfoLayer->setAnchorPoint(ccp(0.5, 0.5));
        m_evoInfoLayer->setPosition(CCDirector::sharedDirector()->getWinSize() * 0.5);
        addChild(m_evoInfoLayer, 10);
    }
    m_evoInfoLayer->setVisible(true);
}

