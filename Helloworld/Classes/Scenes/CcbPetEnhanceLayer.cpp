#include "CcbPetEnhanceLayer.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "CcbTeamMemberLayer.h"
#include "BackCtrl.h"
#include "SystemMessage.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "CPetMgr.h"
#include "SequenceAction.h"
#include "SequencePet.h"
#include "UISupport.h"
#include "CcbItemIconLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "FlyTextLayer.h"
#include "ArmatureManager.h"
#include "EffectLayer.h"
#include "EnumDefines.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;

PetEnhanceScene::~PetEnhanceScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* PetEnhanceScene::scene()
{
    CCScene* pScene = CCScene::create();
    PetEnhanceScene* pLayer = PetEnhanceScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool PetEnhanceScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName );
    
	return false;
}

bool PetEnhanceScene::init()
{
    if ( !CCLayer::init() ) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbPetEnhanceLayer(this));
    return true;
}

void PetEnhanceScene::onEnter()
{
    CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_layer_pet_enhance));
}

void PetEnhanceScene::onExit()
{
    CCLayer::onExit();
}

void PetEnhanceScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

void PetEnhanceScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

#pragma mark CcbPetEnhanceLayer

static CcbPetEnhanceLayer* m_shared = NULL;

CcbPetEnhanceLayer::~CcbPetEnhanceLayer()
{
    m_shared = NULL;
	CC_SAFE_RELEASE_NULL(m_pControlButtonEnhance);
	CC_SAFE_RELEASE_NULL(m_pLayerElem1);
	CC_SAFE_RELEASE_NULL(m_pControlButtonElem1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFElemLv1);
	CC_SAFE_RELEASE_NULL(m_pLayerElem2);
	CC_SAFE_RELEASE_NULL(m_pControlButtonElem2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFElemLv2);
	CC_SAFE_RELEASE_NULL(m_pLayerElem3);
	CC_SAFE_RELEASE_NULL(m_pControlButtonElem3);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFElemLv3);
	CC_SAFE_RELEASE_NULL(m_pLayerElem4);
	CC_SAFE_RELEASE_NULL(m_pControlButtonElem4);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFElemLv4);
	CC_SAFE_RELEASE_NULL(m_pLayerElem5);
	CC_SAFE_RELEASE_NULL(m_pControlButtonElem5);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFElemLv5);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFHp);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAtt);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRev);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDef);
	CC_SAFE_RELEASE_NULL(m_pSpriteBase);
	CC_SAFE_RELEASE_NULL(m_pSpritePet);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMoney);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFGetExp);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNeedExp);
	CC_SAFE_RELEASE_NULL(m_pSpriteExpBar2);
	CC_SAFE_RELEASE_NULL(m_pSpriteExpBar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNoMoney);
    CC_SAFE_RELEASE_NULL(m_pSpriteExpBar2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNoMoney);
    
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_1);
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_2);
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_3);
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_4);
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_5);
    
    CC_SAFE_RELEASE_NULL(m_pNodeFood1);
    CC_SAFE_RELEASE_NULL(m_pNodeFood2);
    CC_SAFE_RELEASE_NULL(m_pNodeFood3);
    CC_SAFE_RELEASE_NULL(m_pNodeFood4);
    CC_SAFE_RELEASE_NULL(m_pNodeFood5);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoLv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSpeDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPetName);
    CC_SAFE_RELEASE_NULL(m_pControlButtonAutoAdd);
    
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAddHp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAddAtt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAddRev);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAddDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAddSpeDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAddLv);
}

CcbPetEnhanceLayer* CcbPetEnhanceLayer::GetSharedLayer()
{
    return m_shared;
}

bool CcbPetEnhanceLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_shared = this;
	return true;
}

void CcbPetEnhanceLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonAutoAdd, GuideBtnPos::E_ENHANCE_AUTO);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonEnhance, GuideBtnPos::E_COMFIRM_ENHANCE);
    }
}

void CcbPetEnhanceLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_PRIMARY);
    CCLog("SetPetBagType %d", CPetCtrl::Get()->GetPetBagType());
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetEnhanceLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbPetEnhanceLayer::addGuideLayer()
{
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_2_PET_ENHANCE,
                                             NULL);
}

void CcbPetEnhanceLayer::onExit()
{
	CCLayer::onExit();

    if (CPetCtrl::Get()->GetPetBagType() != CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_SUB) {
        CPetCtrl::Get()->ClearSelectedPet();
    }
}

void CcbPetEnhanceLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetEnhanceLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEnhance", CCControlButton*, this->m_pControlButtonEnhance);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem1", CCLayer*, this->m_pLayerElem1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem1", CCControlButton*, this->m_pControlButtonElem1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFElemLv1", CCLabelTTF*, this->m_pLabelTTFElemLv1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem2", CCLayer*, this->m_pLayerElem2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem2", CCControlButton*, this->m_pControlButtonElem2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFElemLv2", CCLabelTTF*, this->m_pLabelTTFElemLv2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem3", CCLayer*, this->m_pLayerElem3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem3", CCControlButton*, this->m_pControlButtonElem3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFElemLv3", CCLabelTTF*, this->m_pLabelTTFElemLv3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem4", CCLayer*, this->m_pLayerElem4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem4", CCControlButton*, this->m_pControlButtonElem4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFElemLv4", CCLabelTTF*, this->m_pLabelTTFElemLv4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem5", CCLayer*, this->m_pLayerElem5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem5", CCControlButton*, this->m_pControlButtonElem5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFElemLv5", CCLabelTTF*, this->m_pLabelTTFElemLv5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFHp", CCLabelTTF*, this->m_pLabelTTFHp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAtt", CCLabelTTF*, this->m_pLabelTTFAtt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRev", CCLabelTTF*, this->m_pLabelTTFRev);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDef", CCLabelTTF*, this->m_pLabelTTFDef);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBase", CCSprite*, this->m_pSpriteBase);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet", CCSprite*, this->m_pSpritePet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMoney", CCLabelTTF*, this->m_pLabelTTFMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGetExp", CCLabelTTF*, this->m_pLabelTTFGetExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNeedExp", CCLabelTTF*, this->m_pLabelTTFNeedExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteExpBar2", CCSprite*, this->m_pSpriteExpBar2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteExpBar", CCSprite*, this->m_pSpriteExpBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNoMoney", CCLabelTTF*, this->m_pLabelTTFNoMoney);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_1", CCSprite*, this->m_pSprite_plus_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_2", CCSprite*, this->m_pSprite_plus_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_3", CCSprite*, this->m_pSprite_plus_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_4", CCSprite*, this->m_pSprite_plus_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_5", CCSprite*, this->m_pSprite_plus_5);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFood1", CCNode*, this->m_pNodeFood1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFood2", CCNode*, this->m_pNodeFood2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFood3", CCNode*, this->m_pNodeFood3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFood4", CCNode*, this->m_pNodeFood4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFood5", CCNode*, this->m_pNodeFood5);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoLv", CCLabelTTF*, this->m_pLabelTTFEvoLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSpeDef", CCLabelTTF*, this->m_pLabelTTFSpeDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetName", CCLabelTTF*, this->m_pLabelTTFPetName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAutoAdd", CCControlButton*, this->m_pControlButtonAutoAdd);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAddHp", CCLabelTTF*, this->m_pLabelTTFAddHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAddAtt", CCLabelTTF*, this->m_pLabelTTFAddAtt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAddRev", CCLabelTTF*, this->m_pLabelTTFAddRev);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAddDef", CCLabelTTF*, this->m_pLabelTTFAddDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAddSpeDef", CCLabelTTF*, this->m_pLabelTTFAddSpeDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAddLv", CCLabelTTF*, this->m_pLabelTTFAddLv);
	return false;
}

bool CcbPetEnhanceLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetEnhanceLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetEnhanceLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetEnhanceLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAutoAdd", CcbPetEnhanceLayer::onPressControlButtonAutoAdd);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEnhance", CcbPetEnhanceLayer::onPressControlButtonEnhance);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonElem", CcbPetEnhanceLayer::onPressControlButtonElem);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetEnhanceLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_bAutoSelect = false;
    
    arrElems.clear();
    arrElems.push_back(m_pLayerElem1);
    arrElems.push_back(m_pLayerElem2);
    arrElems.push_back(m_pLayerElem3);
    arrElems.push_back(m_pLayerElem4);
    arrElems.push_back(m_pLayerElem5);
    
    arrElemButtons.clear();
    arrElemButtons.push_back(m_pControlButtonElem1);
    arrElemButtons.push_back(m_pControlButtonElem2);
    arrElemButtons.push_back(m_pControlButtonElem3);
    arrElemButtons.push_back(m_pControlButtonElem4);
    arrElemButtons.push_back(m_pControlButtonElem5);
    
    arrElemsPlus.clear();
    arrElemsPlus.push_back(m_pSprite_plus_1);
    arrElemsPlus.push_back(m_pSprite_plus_2);
    arrElemsPlus.push_back(m_pSprite_plus_3);
    arrElemsPlus.push_back(m_pSprite_plus_4);
    arrElemsPlus.push_back(m_pSprite_plus_5);
    
    m_vecNode.clear();
    m_vecNode.push_back(m_pNodeFood1);
    m_vecNode.push_back(m_pNodeFood2);
    m_vecNode.push_back(m_pNodeFood3);
    m_vecNode.push_back(m_pNodeFood4);
    m_vecNode.push_back(m_pNodeFood5);
    
    for (int i = 0; i < arrElemsPlus.size(); i++) {
        arrElemsPlus[i]->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.5),
                                                                              CCFadeIn::create(1.5),
                                                                              NULL)));
    }
    
    m_pSpritePet->setVisible(false);
    
    expBarWidth = getWidth(m_pSpriteExpBar);
    
    m_pSpriteExpBar2->setVisible(false);
    m_pLabelTTFNoMoney->setVisible(false);
    
    m_pLabelTTFAddHp->setVisible(false);
    m_pLabelTTFAddAtt->setVisible(false);
    m_pLabelTTFAddRev->setVisible(false);
    m_pLabelTTFAddDef->setVisible(false);
    m_pLabelTTFAddSpeDef->setVisible(false);
    
}

void CcbPetEnhanceLayer::onPressControlButtonEnhance(CCObject* pSender, CCControlEvent event)
{
    //TODO: 【GuideData】 如果强化动画不跳转界面，那么在此处增加GuideLayer，而不是在addGuideLayer方法中}
    // E_GUIDE_TRIGGER_EDIT_TEAM，或者在动画结束后增加该指引的ID}
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    checkIntensify();
}
void CcbPetEnhanceLayer::onPressControlButtonAutoAdd(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if(CPetCtrl::Get()->selectEnhanceElemAuto() == 0)
    {
        FlyTextLayer::showTips(GET_STR(Str_no_eat_pet));
        return;
    }
    m_bAutoSelect = true;
    loadElem();
    m_bAutoSelect = false;
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_3_PET_ENHANCE,
                                             NULL
                                             );
}

void CcbPetEnhanceLayer::onPressControlButtonElem(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_SUB);
    BackCtrl::InsertNextScene(kPetBagSaleScene);
}


void CcbPetEnhanceLayer::loadData()
{
    //强化宠物信息}
    m_dwPetObjId = CPetCtrl::Get()->GetIntensifyPet();
    CPet * pet = CPetCtrl::Get()->GetPetByObjId(m_dwPetObjId);
    if (!pet) {
        return;
    }
    
    if (pet->GetbyEvolveLv() >= 6) {
        EffectLayer* effL = EffectLayer::create(E_ANI_EFFECT_PET_BG_ORANGE, -1, 1.0 / 10);
        effL->setPosition(m_pSpritePet->getPosition() - ccp(0, 20));
        effL->setAnchorPoint(ccp(0.5, 0));
        effL->ignoreAnchorPointForPosition(false);
        m_pSpritePet->getParent()->addChild(effL, 1, 112);
        effL->onRun();
    }
    
    SequencePet *mc= dynamic_cast<SequencePet*>(m_pSpritePet->getParent()->getChildByTag(1));
    if (mc) {
        mc->removeFromParentAndCleanup(true);
        mc = NULL;
    }

    mc = SequencePet::create(pet->GetwIndex());
    if (mc) {
        mc->setPosition(CPetCtrl::Get()->ConvertFlccPos(pet->GetwIndex(), getWidth(mc), m_pSpritePet->getPosition()));
        mc->setAnchorPoint(ccp(0.5, 0));
        m_pSpritePet->getParent()->addChild(mc, 2, 1);
        mc->runAction(CCRepeatForever::create(SequenceAction::create(mc, SEQ_ACT_STAND)));
    }
    m_pSpriteBase->setTexture(CPetCtrl::Get()->GetBaseTextureByPet(pet->GetwIndex()));
    //基础数据}
    CCString *str = CCString::create("");
    
    str->initWithFormat("%s%d", SB_Lv, pet->GetbyLv());
    m_pLabelTTFLv->setString(str->getCString());
    m_pLabelTTFLv->setZOrder(3);
    m_pLabelTTFLv->setVisible(true);
    
    //name
    PetConfig::STC_PET_CONFIG* petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    m_pLabelTTFPetName->setString(petCfg->strName.c_str());
    
    str->initWithFormat("%d", pet->GetdwHpValue());
    m_pLabelTTFHp->setString(str->getCString());
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* norCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->GetwNormaleAttId());
    if (norCfg && norCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
        str->initWithFormat("%d", pet->GetdwSAttackValue());
    }
    else{
        str->initWithFormat("%d", pet->GetdwAttackValue());
    }
    m_pLabelTTFAtt->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwDefenseValue());
    m_pLabelTTFDef->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwSDefenseValue());
    m_pLabelTTFSpeDef->setString(str->getCString());
    
    str->initWithFormat("%d", pet->GetdwRecoverValue());
    m_pLabelTTFRev->setString(str->getCString());
    
    str->initWithFormat("+%d", pet->GetbyEvolveLv());
    m_pLabelTTFEvoLv->setString(str->getCString());
    
    loadElem();
}

void CcbPetEnhanceLayer::loadElem()
{
    m_costCoin = 0;
    uint32 getExp = 0;
    int cnt = 0;
    CPet * pet = CPetCtrl::Get()->GetPetByObjId(m_dwPetObjId);
    CCString* str = CCString::create("");
    std::vector<uint32> arrMemberObjId =  CPetCtrl::Get()->GetSelectedPet();
    for (int i = 0; i < arrMemberObjId.size(); i++) {
        if (!arrMemberObjId[i]) {
            continue;
        }
        CPet *p = CPetCtrl::Get()->GetPetByObjId(arrMemberObjId[i]);
        if (!p) {
            continue;
        }
        PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, p->GetwIndex());
        
        
        CcbItemIconLayer* icon = dynamic_cast<CcbItemIconLayer*>(arrElems[cnt]);//->loadIndexData(p->GetwIndex());
        icon->loadIndexData(p->GetwIndex());
        icon->showIconOnly();
        icon->showLv(p->GetbyLv());
        icon->showName();
        icon->setBtnEnable(false);

        arrElemsPlus[cnt]->setVisible(false);
        
        cnt++;
        
        //经验}
        //        bool same = false;
        //        if (p->GetbyNature1() == pet->GetbyNature1()) {
        //            same = true;
        //        }
        uint32 exp = ENHANCE_EXP(pCfg->dwMergeExpFatio, p->GetbyLv());
        getExp += exp;
        //钱}
        CCLog("exp fatio:%d, money fatio:%d", pCfg->dwMergeExpFatio, pCfg->dwMergeCoinFatio);
        m_costCoin += ENHANCE_MONEY(pCfg->dwMergeExpFatio, p->GetbyLv(), pCfg->dwMergeCoinFatio);
        
        if (m_bAutoSelect && checkExpFull(exp + getExp)) {
            break;
        }

    }
    
    if (m_bAutoSelect) {
        uint8 tempS = arrMemberObjId.size();
        for (int k = cnt; k < tempS; k++) {
            CPetCtrl::Get()->UnSelectedPet(arrMemberObjId[k]);
        }
    }
    
    
    for (int j = cnt; j < 5; j++) {
        CcbItemIconLayer* icon = dynamic_cast<CcbItemIconLayer*>(arrElems[j]);//->loadIndexData(p->GetwIndex());
        icon->loadIndexData(0);
        icon->showIconOnly();
        icon->setBtnEnable(false);
        arrElemsPlus[j]->setVisible(true);
    }
    
    //金币}
    str->initWithFormat("%d", m_costCoin);
    m_pLabelTTFMoney->setString(str->getCString());
    //获得经验}
    str->initWithFormat("%d", getExp);
    m_pLabelTTFGetExp->setString(str->getCString());
    //升级剩余经验}
    ExpConfig::STC_EXP_CONFIG *expCfg = GET_CONFIG_STC(ExpConfig, pet->GetbyLv());
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    uint32 maxExp = expCfg->dwPetExp * petCfg->dwExpFatio / 100;
    
    str->initWithFormat("%d",  maxExp - pet->GetcurExp());
    m_pLabelTTFNeedExp->setString(str->getCString());
    
    m_pSpriteExpBar->setTextureRect(CCRectMake(0, 0, expBarWidth * pet->GetcurExp() / maxExp, getHeight(m_pSpriteExpBar)));
    
    if (getExp > 0) {
        m_pSpriteExpBar2->setVisible(true);
        m_pSpriteExpBar2->setOpacity(0);
        uint32 temp = getExp + pet->GetcurExp();
        temp = MIN(temp, maxExp);
        m_pSpriteExpBar2->setTextureRect(CCRectMake(0, 0, expBarWidth * temp / maxExp, getHeight(m_pSpriteExpBar2)));
        m_pSpriteExpBar2->runAction(
                                    CCRepeatForever::create(
                                                            CCSequence::create(
                                                                               CCFadeIn::create(1.0),
                                                                               CCFadeOut::create(1.0),
                                                                               NULL
                                                                               )
                                                            )
                                    );
    }
    else
    {
        m_pSpriteExpBar2->stopAllActions();
        m_pSpriteExpBar2->setVisible(false);
    }
    
    if (m_costCoin > CGameSession::GetRole()->GetdwCoin()) {
        m_pLabelTTFMoney->setColor(ccRED);
        m_pControlButtonEnhance->setEnabled(false);
        m_pLabelTTFNoMoney->setVisible(true);
        m_pLabelTTFNoMoney->runAction(CCRepeatForever::create(CCBlink::create(1.5, 1)));
        m_pLabelTTFMoney->runAction(CCRepeatForever::create(CCBlink::create(1.5, 1)));
    }
    else
    {
        m_pLabelTTFMoney->stopAllActions();
        m_pLabelTTFMoney->setColor(ccWHITE);
        m_pControlButtonEnhance->setEnabled(true);
        m_pLabelTTFNoMoney->stopAllActions();
        m_pLabelTTFNoMoney->setVisible(false);
    }
    
    showNextLvValue(getExp);
}

void CcbPetEnhanceLayer::checkIntensify()
{
    //3星以上被吃、满级的被吃}
    bool flagStar = false;
    bool flagFiveStar = false;
    bool flagLv = false;
    
    
    std::vector<uint32> arrMemberObjId =  CPetCtrl::Get()->GetSelectedPet();
    for (int i = 0; i < arrMemberObjId.size(); i++) {
        if (!arrMemberObjId[i]) {
            continue;
        }
        CPet *p = CPetCtrl::Get()->GetPetByObjId(arrMemberObjId[i]);
        if (!p) {
            continue;
        }
        PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, p->GetwIndex());
        if (!pCfg) {
            continue;
        }
        //学过技能的}
        
        if (p->GetbyStarLv() >= 3) {
            flagStar = true;
            if (p->GetbyStarLv() == 5 && p->GetwIndex() != 165 && p->GetwIndex() != 166) {
                flagFiveStar = true;
            }
            continue;
        }
        
        if (p->GetbyLv() == pCfg->byLvMax) {
            flagLv = true;
            continue;
        }
    }
    
    if (flagStar)
    {
        CCString *str = CCString::create("");
        if (flagFiveStar) {
            str->initWithFormat("%s\n%s\n%s", GET_STR(Str_sure_eat_pet_star), GET_STR(Str_five_star_pet_notice), GET_STR(Str_sure_enh));
        }
        else{
            str->initWithFormat("%s\n%s", GET_STR(Str_sure_eat_pet_star), GET_STR(Str_sure_enh));
        }
        
        SystemMessage::showSystemMessage(1, this, str->getCString(), this, false, 1, GET_STR(Str_tishi));
        return;
    }
    else if (flagLv)
    {
        SystemMessage::showSystemMessage(1, this, GET_STR(Str_sure_eat_pet_lv), this, false, 1, GET_STR(Str_tishi));
        return;
    }
    
    if (arrMemberObjId.size()) {
        CPetMgr::Get()->setPetOrgInfo(CPetCtrl::Get()->GetIntensifyPet());
        CPetCtrl::Get()->DoIntensifyPet();
    } else {
        FlyTextLayer::showTips(GET_STR(Str_choose_eat_pet));
        return;
    }
    
}

void CcbPetEnhanceLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    CPetMgr::Get()->setPetOrgInfo(CPetCtrl::Get()->GetIntensifyPet());
    CPetCtrl::Get()->DoIntensifyPet();
}

const int Star_Tag = 2727;
const int Enhance_Tag = 5722;
const float Delay_Time = 0.5f;

void CcbPetEnhanceLayer::playEnhanceEffect()
{
    int k = 0;
    std::vector<uint32> arrMemberObjId = CPetCtrl::Get()->GetSelectedPet();
    for (int i = 0; i < arrMemberObjId.size(); i++) {
//    for (int i = 0; i < 2; i++) {
        if (!arrMemberObjId[i]) {
            continue;
        }
    
        CcbItemIconLayer* icon = dynamic_cast<CcbItemIconLayer*>(arrElems[k]);//->loadIndexData(p->GetwIndex());
        icon->loadIndexData(0);
        icon->showIconOnly();
        icon->setBtnEnable(false);
        
        arrElemsPlus[k]->setVisible(true);

        //add particles
        CCParticleSystemQuad* pStar = CCParticleSystemQuad::create("effect/effect_1103.plist");
        CCPoint pos = getWorldPos(m_vecNode[k]);//->getPosition();
//        pos = ccpAdd(pos, m_vecNode[k]->getParent()->getPosition());
//        pos = ccpAdd(pos, m_vecNode[k]->getParent()->getParent()->getPosition());
        
        pStar->setPosition(pos);
        
        if (this->getChildByTag(Star_Tag + k)) {
            this->getChildByTag(Star_Tag + k)->removeFromParent();
        }
        this->addChild(pStar, 90, Star_Tag + k);
        
        pos = getWorldPos(m_pSpritePet) + ccp(getWidth(m_pSpritePet)*0.5, getHeight(m_pSpritePet)*0.5);
        
        pStar->runAction(
                         CCMoveTo::create(Delay_Time, pos)//->getParent()->getPosition(), ccp(0.0f, -40.0f)))
                         );
        
        k++;
    }
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(Delay_Time),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetEnhanceLayer::addPetEnhanceEff)),
                                       NULL
                                       )
                    );
}

void CcbPetEnhanceLayer::addPetEnhanceEff() {
    
    if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_PET_ENHANCE_1_TALK) {
        GuideData::GetInstance()->connectToServer();
    }
    
    for (int i = 0; i < 5; i++) {
        if (this->getChildByTag(Star_Tag + i)) {
            this->getChildByTag(Star_Tag + i)->removeFromParent();
        }
    }
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_pet_upgrade));
    
    //cocosstudio动画只要动画本身中心点对，程序里不需要设置任何锚点什么的，游戏里的位置就是动画的中心点
    CCNode* pPetEnhance = ArmatureManager::sharedManager()->LoadArmature(GET_ARM_PATH(Arm_ef_pet_enhance), GET_ARM_NAME(Arm_ef_pet_enhance));
//    pPetEnhance->ignoreAnchorPointForPosition(false);
//    pPetEnhance->setAnchorPoint(ccp(0.5, 0.5));
//    pPetEnhance->setPosition(m_pSpritePet->getParent()->getPosition());
//    SequencePet *mc= dynamic_cast<SequencePet*>(m_pSpritePet->getParent()->getChildByTag(1));
    CCPoint pos = getWorldPos(m_pSpritePet) + ccp(getWidth(m_pSpritePet)*0.5, getHeight(m_pSpritePet)*0.5);
    pPetEnhance->setPosition(pos);
    
    if (this->getChildByTag(Enhance_Tag)) {
        this->getChildByTag(Enhance_Tag)->removeFromParent();
    }
    this->addChild(pPetEnhance, 99, Enhance_Tag);
    
    //TODO: 赶时间简单粗暴做法，直接刷新数据，后续需要每次升级增加特效}
    
    if (m_pLabelTTFAddLv->isVisible()) {
        //等级
        hideAddTextEff(m_pLabelTTFAddLv);
        showEnhTextEff(m_pLabelTTFLv);
        //生命
        hideAddTextEff(m_pLabelTTFAddHp);
        showEnhTextEff(m_pLabelTTFHp);
        //攻击
        hideAddTextEff(m_pLabelTTFAddAtt);
        showEnhTextEff(m_pLabelTTFAtt);
        //普防
        hideAddTextEff(m_pLabelTTFAddDef);
        showEnhTextEff(m_pLabelTTFDef);
        //特防
        hideAddTextEff(m_pLabelTTFAddSpeDef);
        showEnhTextEff(m_pLabelTTFSpeDef);
        //回复
        hideAddTextEff(m_pLabelTTFAddRev);
        showEnhTextEff(m_pLabelTTFRev);
    }
    
    loadData();
    CPetCtrl::Get()->ClearSelectedPet();
    
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_PET_ENHANCE_1_TALK,
                                             NULL
                                             );
}


bool CcbPetEnhanceLayer::checkExpFull(uint32 addexp)
{
    bool ret = false;
    CRole* role = CGameSession::GetRole();
    CPet * pet = CPetCtrl::Get()->GetPetByObjId(m_dwPetObjId);
    uint16 petLv = pet->GetbyLv();
    
    uint32 allExp = addexp + pet->GetcurExp();
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    ExpConfig::STC_EXP_CONFIG *expCfg = GET_CONFIG_STC(ExpConfig, pet->GetbyLv());
    
    uint32 maxExp = expCfg->dwPetExp * petCfg->dwExpFatio / 100;
    while (allExp >= maxExp) {
        allExp -= maxExp;
        petLv++;
        //达到限制等级
        if (petLv > role->GetwRoleLv()) {
            ret = true;
            break;
        }
        ExpConfig::STC_EXP_CONFIG *expCfg = GET_CONFIG_STC(ExpConfig, petLv);
        maxExp = expCfg->dwPetExp * petCfg->dwExpFatio / 100;
    }
    
    return ret;
}

void CcbPetEnhanceLayer::showNextLvValue(uint32 addExp)
{
    CRole* role = CGameSession::GetRole();
    CPet * pet = CPetCtrl::Get()->GetPetByObjId(m_dwPetObjId);
    uint16 petLv = pet->GetbyLv();
    
    uint32 allExp = addExp + pet->GetcurExp();
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    ExpConfig::STC_EXP_CONFIG *expCfg = GET_CONFIG_STC(ExpConfig, pet->GetbyLv());
    
    uint32 maxExp = expCfg->dwPetExp * petCfg->dwExpFatio / 100;
    while (allExp >= maxExp) {
        allExp -= maxExp;
        petLv++;
        //达到限制等级
        if (petLv >= role->GetwRoleLv()) {
            petLv = role->GetwRoleLv();
            break;
        }
        ExpConfig::STC_EXP_CONFIG *expCfg = GET_CONFIG_STC(ExpConfig, petLv);
        maxExp = expCfg->dwPetExp * petCfg->dwExpFatio / 100;
    }
    
    
    m_pLabelTTFAddHp->setVisible(false);
    m_pLabelTTFAddAtt->setVisible(false);
    m_pLabelTTFAddRev->setVisible(false);
    m_pLabelTTFAddDef->setVisible(false);
    m_pLabelTTFAddSpeDef->setVisible(false);
    m_pLabelTTFAddLv->setVisible(false);
    if (petLv == pet->GetbyLv()) {
        return;
    }
    
    
    
    STC_PET_BASE_INFO baseInfo = CPetCtrl::Get()->getPetBaseValueByObjId(m_dwPetObjId);
    
    STC_PET_BASE_INFO baseEmbAdd = CPetCtrl::Get()->getEmblemAddValue(m_dwPetObjId, baseInfo);
    
    STC_PET_BASE_INFO baseAdd;
    baseAdd.dwHp = petCfg->dwHpChg * (petLv - pet->GetbyLv()) / 1000;
    baseAdd.dwCAtk = petCfg->dwAttackChg * (petLv - pet->GetbyLv()) / 1000;
    baseAdd.dwCDef = petCfg->dwDeffenseChg * (petLv - pet->GetbyLv()) / 1000;
    baseAdd.dwSAtk = petCfg->dwSAttackChg * (petLv - pet->GetbyLv()) / 1000;
    baseAdd.dwSDef = petCfg->dwSDeffenseChg * (petLv - pet->GetbyLv()) / 1000;
    baseAdd.dwRev = petCfg->dwRecoverChg * (petLv - pet->GetbyLv()) / 1000;
    
    baseInfo.dwHp += baseAdd.dwHp;
    baseInfo.dwCAtk += baseAdd.dwCAtk;
    baseInfo.dwCDef += baseAdd.dwCDef;
    baseInfo.dwSAtk += baseAdd.dwSAtk;
    baseInfo.dwSDef += baseAdd.dwSDef;
    baseInfo.dwRev += baseAdd.dwRev;
    
    STC_PET_BASE_INFO nowEmbAdd = CPetCtrl::Get()->getEmblemAddValue(m_dwPetObjId, baseInfo);
    
    CCString* str = CCString::create("");
    
    str->initWithFormat("+%d", petLv - pet->GetbyLv());
    m_pLabelTTFAddLv->setVisible(true);
    m_pLabelTTFAddLv->setString(str->getCString());
    showAddTextEff(m_pLabelTTFAddLv);
    
    
    if (nowEmbAdd.dwHp + baseAdd.dwHp > baseEmbAdd.dwHp) {
        m_pLabelTTFAddHp->setVisible(true);
        str->initWithFormat("+%d", nowEmbAdd.dwHp + baseAdd.dwHp - baseEmbAdd.dwHp);
        m_pLabelTTFAddHp->setString(str->getCString());
        showAddTextEff(m_pLabelTTFAddHp);
    }
    
    uint32 atk = 0;
    uint32 nowAtk = 0;
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* norCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->GetwNormaleAttId());
    if (norCfg && norCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
        atk = baseEmbAdd.dwSAtk;
        nowAtk = nowEmbAdd.dwSAtk + baseAdd.dwSAtk;
    }
    else{
        atk = baseEmbAdd.dwCAtk;
        nowAtk = nowEmbAdd.dwCAtk + baseAdd.dwCAtk;
    }
    
    if (nowAtk > atk) {
        m_pLabelTTFAddAtt->setVisible(true);
        str->initWithFormat("+%d", nowAtk - atk);
        m_pLabelTTFAddAtt->setString(str->getCString());
        showAddTextEff(m_pLabelTTFAddAtt);
    }
    
    if (nowEmbAdd.dwCDef + baseAdd.dwCDef > baseEmbAdd.dwCDef) {
        m_pLabelTTFAddDef->setVisible(true);
        str->initWithFormat("+%d", nowEmbAdd.dwCDef + baseAdd.dwCDef - baseEmbAdd.dwCDef);
        m_pLabelTTFAddDef->setString(str->getCString());
        showAddTextEff(m_pLabelTTFAddDef);
    }
    
    if (nowEmbAdd.dwSDef + baseAdd.dwSDef > baseEmbAdd.dwSDef) {
        m_pLabelTTFAddSpeDef->setVisible(true);
        str->initWithFormat("+%d", nowEmbAdd.dwSDef + baseAdd.dwSDef - baseEmbAdd.dwSDef);
        m_pLabelTTFAddSpeDef->setString(str->getCString());
        showAddTextEff(m_pLabelTTFAddSpeDef);
    }
    
    if (nowEmbAdd.dwRev + baseAdd.dwRev > baseEmbAdd.dwRev) {
        m_pLabelTTFAddRev->setVisible(true);
        str->initWithFormat("+%d", nowEmbAdd.dwRev + baseAdd.dwRev - baseEmbAdd.dwRev);
        m_pLabelTTFAddRev->setString(str->getCString());
        showAddTextEff(m_pLabelTTFAddRev);
    }
    
}

void CcbPetEnhanceLayer::showAddTextEff(CCLabelTTF* lbl)
{
    if (!lbl->isVisible()) {
        return;
    }
    lbl->stopAllActions();
    lbl->setOpacity(255);
    lbl->runAction(CCRepeatForever::create(
                                           CCSequence::create(
                                                              CCFadeOut::create(1.0),
                                                              CCFadeIn::create(1.0),
                                                              CCDelayTime::create(0.5),
                                                              NULL)));
}

void CcbPetEnhanceLayer::hideAddTextEff(CCLabelTTF* lbl)
{
    if (!lbl->isVisible()) {
        return;
    }
    lbl->stopAllActions();
    lbl->setOpacity(255);
    lbl->runAction(CCSequence::create(
                                      CCFadeOut::create(0.1),
                                      CCFadeIn::create(0.1),
                                      CCHide::create(),
                                      NULL));
}

void CcbPetEnhanceLayer::showEnhTextEff(CCLabelTTF* lbl)
{
    lbl->stopAllActions();
    lbl->runAction(CCSequence::create(
                                      CCScaleTo::create(0.1, 1.2),
                                      CCScaleTo::create(0.1, 1.0),
                                      NULL));
}