#include "CcbPetInfoLayer.h"
#include "CcbManager.h"
#include "EffectLayer.h"
#include "EnumDefines.h"
#include "SequencePet.h"
#include "SequenceAction.h"
#include "PetCtrl.h"
#include "UISupport.h"
#include "CcbPetShowBackLayer.h"
#include "CcbPetSkillLayer.h"
#include "EquipDataMgr.h"
#include "MusicCtrl.h"
#include "TeamCtrl.h"
#include "ConfigGet.h"
#include "Team.h"
#include "BackCtrl.h"
#include "GachaDataMgr.h"
#include "GuideData.h"
#include "AltEffArmature.h"
#include "ResourceDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPetInfoScene::~CcbPetInfoScene()
{
    
    
}

CCScene *CcbPetInfoScene::scene()
{
    CCScene* scene = CCScene::create();
    CcbPetInfoScene *layer = CcbPetInfoScene::create();
    scene->addChild(layer, 1, 1);
    return scene;
}

bool CcbPetInfoScene::init()
{
    // First be called.
    if (!CCLayer::init()) {
        return false;
    }
    // code here
    CCNode* layer = CcbManager::sharedManager()->LoadCcbPetInfoLayer();
    this->addChild(layer);
    layer->setTag(1);
    return true;
}

void CcbPetInfoScene::onEnter()
{
    CCLayer::onEnter();
    //在scene()之后被调用}
    //这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    
}

void CcbPetInfoScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbPetInfoScene::onExit()
{
    CCLayer::onExit();
    
}

void CcbPetInfoScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
    CCAction* pAction = CCFadeOut::create(1.0f);
    this->runAction(pAction);
}

CcbPetInfoLayer::~CcbPetInfoLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerBack);
	CC_SAFE_RELEASE_NULL(m_pLayerSkill);
	CC_SAFE_RELEASE_NULL(m_pSpriteBase);
	CC_SAFE_RELEASE_NULL(m_pSpritePetMc);
	CC_SAFE_RELEASE_NULL(m_pSprite6Wei);
	CC_SAFE_RELEASE_NULL(m_pControlButtonStrong);
	CC_SAFE_RELEASE_NULL(m_pControlButtonUp);
	CC_SAFE_RELEASE_NULL(m_pControlButtonChange);
    CC_SAFE_RELEASE_NULL(m_pControlButtonAlt);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetInfoLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetInfoLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetInfoLayer", CcbPetInfoLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/petshow_back.ccb]", [ccb/petshow_back.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_information.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetInfoLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbPetInfoLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    if (CPetCtrl::Get()->GetShowPetObjId()) {
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(CPetCtrl::Get()->GetShowPetObjId());
        loadPetData(pet);
    }
    else if (CPetCtrl::Get()->getPetTujianShowId())
    {
        loadTujianData(CPetCtrl::Get()->getPetTujianShowId());
    }
}

void CcbPetInfoLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetInfoLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbPetInfoLayer::addGuideLayer()
{
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_4_GACHA,
                                             NULL
                                             );
}

void CcbPetInfoLayer::onExit()
{
	CCLayer::onExit();
    //如果是单抽，显示抽宠动画
    if (g_GachaData->m_vecGachaPetIdx.size() == 1) {
        g_GachaData->m_vecGachaPetIdx.clear();
        return;
    }
}

void CcbPetInfoLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetInfoLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBack", CcbPetShowBackLayer*, this->m_pLayerBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerSkill", CCLayer*, this->m_pLayerSkill);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBase", CCSprite*, this->m_pSpriteBase);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetMc", CCSprite*, this->m_pSpritePetMc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite6Wei", CCSprite*, this->m_pSprite6Wei);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStrong", CCControlButton*, this->m_pControlButtonStrong);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonUp", CCControlButton*, this->m_pControlButtonUp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonChange", CCControlButton*, this->m_pControlButtonChange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAlt", CCControlButton*, this->m_pControlButtonAlt);

	return false;
}

bool CcbPetInfoLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbPetInfoLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetInfoLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetInfoLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonStrong", CcbPetInfoLayer::onPressControlButtonStrong);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUp", CcbPetInfoLayer::onPressControlButtonUp);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonChange", CcbPetInfoLayer::onPressControlButtonChange);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAlt", CcbPetInfoLayer::onPressControlButtonAlt);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetInfoLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    
    m_pSpritePetMc->setVisible(false);
    
    m_pLayerSkill->getParent()->getParent()->setZOrder(-1);
    
//    arrPoint[0] = ccp(getWidth(m_pSprite6Wei) * 0.25, getHeight(m_pSprite6Wei));// + ccp(10, 10);
//    arrPoint[1] = ccp(getWidth(m_pSprite6Wei) * 0.75, getHeight(m_pSprite6Wei));// - ccp(10, 10);
//    arrPoint[2] = ccp(getWidth(m_pSprite6Wei) * 1, getHeight(m_pSprite6Wei) * 0.5);// - ccp(10, 10);
//    arrPoint[3] = ccp(getWidth(m_pSprite6Wei) * 0.75, getHeight(m_pSprite6Wei) * 0);// - ccp(10, 10);
//    arrPoint[4] = ccp(getWidth(m_pSprite6Wei) * 0.25, getHeight(m_pSprite6Wei) * 0);// + ccp(10, 10);
//    arrPoint[5] = ccp(getWidth(m_pSprite6Wei) * 0, getHeight(m_pSprite6Wei) * 0.5);// + ccp(10, 10);
    arrPoint[0] = ccp(0, 15);
    arrPoint[1] = ccp(13, 7.5);
    arrPoint[2] = ccp(13, -7.5);
    arrPoint[3] = ccp(0, -15);
    arrPoint[4] = ccp(-13, -7.5);
    arrPoint[5] = ccp(-13, 7.5);
                      
    
    m_scrollView = CCScrollView::create(m_pLayerSkill->getContentSize());
    m_scrollView->setDirection(kCCScrollViewDirectionVertical);
    m_scrollView->setPosition(CCPointZero);
    m_scrollView->setAnchorPoint(CCPointZero);
    m_scrollView->setTouchPriority(2*kCCMenuHandlerPriority - 6);
    m_pLayerSkill->addChild(m_scrollView);
    
    m_skillLayer = dynamic_cast<CcbPetSkillLayer*>(CcbManager::sharedManager()->LoadCcbPetSkillLayer(this));
    m_skillLayer->setPosition(CCPointZero);
    m_skillLayer->setAnchorPoint(CCPointZero);
    m_skillLayer->ignoreAnchorPointForPosition(false);
    m_scrollView->addChild(m_skillLayer);
    
    m_pControlButtonStrong->setTouchPriority(2*kCCMenuHandlerPriority - 6);
    m_pControlButtonUp->setTouchPriority(2*kCCMenuHandlerPriority - 6);
    m_pControlButtonChange->setTouchPriority(2*kCCMenuHandlerPriority - 6);
    
    m_pLayerBack->setBackTouchPr(2*kCCMenuHandlerPriority - 6);
    
    m_pControlButtonAlt->setVisible(false);
#ifdef DEBUG
    m_pControlButtonAlt->setTouchPriority(2*kCCMenuHandlerPriority - 6);
    m_pControlButtonAlt->setVisible(true);
#endif
    
}
void CcbPetInfoLayer::onPressControlButtonAlt(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (!isParitleStop) {
        return;
    }
    showAlk();
}


void CcbPetInfoLayer::onPressControlButtonStrong(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CPetCtrl::Get()->SetIntensifyPet(CPetCtrl::Get()->GetShowPetObjId());
    BackCtrl::InsertNextScene(kEnhanceScene);
}

void CcbPetInfoLayer::onPressControlButtonUp(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CPetCtrl::Get()->SetEvolvePet(CPetCtrl::Get()->GetShowPetObjId());
    BackCtrl::InsertNextScene(kEvolveScene);
}

void CcbPetInfoLayer::onPressControlButtonChange(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CTeam* team = CTeamCtrl::GetCurTeam();
    uint8 site = CTeamCtrl::getSiteByPetId(CPetCtrl::Get()->GetShowPetObjId());
    if (!site) {
        retain();
    }
    //组队界面进入宠物背包}
    if (team->getbyLeaderSite() == site) {
        CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_PARTY_LEADER);
    }
    else
    {
        CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_PARTY_NORMAL);
    }
    CTeamCtrl::SetSelectedMemberSite(site);
    BackCtrl::InsertNextScene(kPetBagScene, kNormalTrans);
}


void CcbPetInfoLayer::loadTujianData(uint16 wPetIndexId)
{
    loadData(wPetIndexId, 0);
    
    m_pLayerBack->loadData(wPetIndexId);
    m_skillLayer->loadTujianData(wPetIndexId);
    m_scrollView->setContentSize(m_skillLayer->getContentSize());
    m_scrollView->setContentOffset(m_scrollView->getViewSize() - m_scrollView->getContentSize());
    m_pControlButtonStrong->setVisible(false);
    m_pControlButtonUp->setVisible(false);
    m_pControlButtonChange->setVisible(false);
}
void CcbPetInfoLayer::loadPetData(CPet* pet)
{
    loadData(pet->GetwIndex(), pet->GetbyEvolveLv());
    m_skillLayer->loadDataPet(pet);
    
    m_scrollView->setContentSize(m_skillLayer->getContentSize());
    m_scrollView->setContentOffset(m_scrollView->getViewSize() - m_scrollView->getContentSize());
    if (CPetCtrl::Get()->getIsFirendLook()) {
        m_pLayerBack->loadObjData(pet, true);
        m_pLayerBack->setDelegate(this);
        m_pControlButtonStrong->setVisible(false);
        m_pControlButtonUp->setVisible(false);
        m_pControlButtonChange->setVisible(false);
    }
    else
    {
        m_pLayerBack->loadObjData(pet);
        m_pControlButtonChange->setVisible(true);
        m_pControlButtonUp->setVisible(true);
        
        //强化}
        if (CPetCtrl::Get()->IsCanIntensify(pet->GetObjId())) {
            m_pControlButtonStrong->setEnabled(true);
        }
        else
        {
            m_pControlButtonStrong->setEnabled(false);
        }
        
        //进化}
        if (CPetCtrl::Get()->IsCanEvolve(pet->GetObjId())) {
            m_pControlButtonUp->setEnabled(true);
        }
        else
        {
            m_pControlButtonUp->setEnabled(false);
        }
        
        m_pControlButtonChange->setVisible(g_EquipData->getIsEquipShow());
    }
}


void CcbPetInfoLayer::loadData(uint16 wPetIndexId, uint8 evoLv)
{
    m_wPetIndexId = wPetIndexId;
    initFrame();
    //宠物动画}
    EffectLayer* effL = dynamic_cast<EffectLayer*>(m_pSpritePetMc->getParent()->getChildByTag(112));
    if (effL) {
        effL->removeFromParentAndCleanup(true);
    }
    if (evoLv >= 6) {
        effL = EffectLayer::create(E_ANI_EFFECT_PET_BG_ORANGE, -1, 1.0 / 10);
        effL->setPosition(m_pSpritePetMc->getPosition() - ccp(0, 20));
        effL->setAnchorPoint(ccp(0.5, 0));
        effL->ignoreAnchorPointForPosition(false);
        m_pSpritePetMc->getParent()->addChild(effL, 1, 112);
        
        effL->onRun();
    }
    
    SequencePet* mc = dynamic_cast<SequencePet*>(m_pSpritePetMc->getParent()->getChildByTag(11));
    if (mc) {
        //        mc->stopAllActions();
        mc->removeFromParentAndCleanup(true);
    }
    
    mc = SequencePet::create(wPetIndexId);
    mc->setPosition(CPetCtrl::Get()->ConvertFlccPos(wPetIndexId, getWidth(mc), m_pSpritePetMc->getPosition(), true));
    mc->setAnchorPoint(ccp(0.5, 0));
    //    mc->setTag(11);
    mc->setRotationY(180);
    m_pSpritePetMc->getParent()->addChild(mc, 2, 11);
    mc->runAction(CCRepeatForever::create(CCSequence::create(
                                                             SequenceAction::create(mc, SEQ_ACT_STAND),
                                                             SequenceAction::create(mc, SEQ_ACT_STAND),
                                                             SequenceAction::create(mc, SEQ_ACT_STAND),
                                                             CCCallFunc::create(this, callfunc_selector(CcbPetInfoLayer::hidePetBgEff)),
                                                             CCCallFunc::create(this, callfunc_selector(CcbPetInfoLayer::showNor)),
                                                             SequenceAction::create(mc, SEQ_ACT_ATTACK),
                                                             //                                                             CCDelayTime::create(0.5),
                                                             CCCallFunc::create(this, callfunc_selector(CcbPetInfoLayer::showPetBgEff)),
                                                             NULL)));
    //站台}
    m_pSpriteBase->setTexture(CPetCtrl::Get()->GetBaseTextureByPet(wPetIndexId));
    
    //六维图
    PetLiuWeiConfig::STC_CONFIG_PET_LIUWEI* liuweiCfg = GET_CONFIG_STC(PetLiuWeiConfig, wPetIndexId);
    if (liuweiCfg) {
        float base = 100.0f;
        float offX = 30.0f * 0.85;
        float offY = 35.0f * 0.85;
        CCPoint pos = getWorldPos(m_pSprite6Wei) + m_pSprite6Wei->getContentSize() * 0.5 * m_pSprite6Wei->getScale();

        arrPoint[0] = arrPoint[0] + ccp(0, offY) * (liuweiCfg->wAtk / base) + pos;
        arrPoint[1] = arrPoint[1] + ccp(offX, 0.5*offY) * (liuweiCfg->wHp / base) + pos;
        arrPoint[2] = arrPoint[2] + ccp(offX, -0.5*offY) * (liuweiCfg->wSDef / base) + pos;
        arrPoint[3] = arrPoint[3] + ccp(0, -offY) * (liuweiCfg->wControl / base) + pos;
        arrPoint[4] = arrPoint[4] + ccp(-offX, -0.5*offY) * (liuweiCfg->wSupp / base) + pos;
        arrPoint[5] = arrPoint[5] + ccp(-offX, 0.5*offY) * liuweiCfg->wCDef / base + pos;
    }
}
void CcbPetInfoLayer::draw()
{
    CCLayer::draw();
    CHECK_GL_ERROR_DEBUG();
    //启用混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    
    glLineWidth(1);
    ccDrawSolidPoly(arrPoint, 6, ccc4f(253, 163, 0, 0.5f));

}
void CcbPetInfoLayer::showPetBgEff()
{
    EffectLayer* effL = dynamic_cast<EffectLayer*>(m_pSpritePetMc->getParent()->getChildByTag(112));
    if (effL) {
        effL->runAction(CCSequence::create(CCDelayTime::create(0.3),
                                           CCShow::create(),
                                           NULL));
        //        effL->getSprite()->setVisible(true);
    }
}


void CcbPetInfoLayer::hidePetBgEff()
{
    EffectLayer* effL = dynamic_cast<EffectLayer*>(m_pSpritePetMc->getParent()->getChildByTag(112));
    if (effL) {
        effL->setVisible(false);
    }
}


bool CcbPetInfoLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isVisible()) {
        return false;
    }
    return true;
}

void CcbPetInfoLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2*kCCMenuHandlerPriority - 5, true);
}

void CcbPetInfoLayer::initFrame()
{
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_wPetIndexId);
    
    if (!petCfg) {
        // create a new role, use config here first.
        return;
    }
    isParitleStop = true;
    curFrame = 0;
    allFrame = 0;
    allNorFrame = 0;
    allAltFrame = 0;
    std::string keyFrame = petCfg->strKeyFrames;
    std::vector<int> arrKeyFrame;
    ResourceStringConverter::StrSplit(keyFrame, "_", arrKeyFrame);
    
    for (int i = 0; i < arrKeyFrame.size(); i++) {
        if (arrKeyFrame[i]) {
            m_mapKeyFrame[arrKeyFrame[i]] = arrKeyFrame[i];
        }
    }
    
    ComboIdConfig::STC_COMBOID_CONFIG *combo;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *ult = GET_CONFIG_STC(UltimateSkillConfig, petCfg->wInitialSkillId);
    if (ult) {
        combo = GET_CONFIG_STC(ComboIdConfig, ult->wComboid);
        
        if (combo) {
            int len = 0;
            GET_ARRAY_LEN(combo->dwComboTime, len);
            for (int i = 0; i < len; i++) {
                if (combo->dwComboTime[i] == 0) {
                    break;
                }
                allAltFrame = combo->dwComboTime[i];
            }
        }
    }
    
    combo = GET_CONFIG_STC(ComboIdConfig, petCfg->wComboId);
    if (combo) {
        int len = 0;
        GET_ARRAY_LEN(combo->dwComboTime, len);
        for (int i = 0; i < len; i++) {
            if (combo->dwComboTime[i] == 0) {
                break;
            }
            allNorFrame = combo->dwComboTime[i];
        }
    }
    
    arrKeyFrame.clear();
    ResourceStringConverter::StrSplit(petCfg->strAltKeyFrames, "_", arrKeyFrame);
    for (int i = 0; i < arrKeyFrame.size(); i++) {
        if (arrKeyFrame[i]) {
            m_mapAltKeyFrame[arrKeyFrame[i]] = arrKeyFrame[i];
        }
    }
}

void CcbPetInfoLayer::showNor()
{
    isParitleStop = false;
    isRealSkill = false;
    curFrame = 0;
    allFrame = allNorFrame;
    arrCurParticle.clear();
    unschedule(schedule_selector(CcbPetInfoLayer::updateForEff));
    schedule(schedule_selector(CcbPetInfoLayer::updateForEff), 1.0 / 24);
}

void CcbPetInfoLayer::showAlk()
{
    isParitleStop = false;
    isRealSkill = true;
    curFrame = 0;
    allFrame = allAltFrame;
    arrCurParticle.clear();
    
    SequencePet* mc = dynamic_cast<SequencePet*>(m_pSpritePetMc->getParent()->getChildByTag(11));
    if (!mc) {
        return;
    }
    hidePetBgEff();
    mc->stopAllActions();
    mc->runAction(SequenceAction::create(mc, SEQ_ACT_STAND));
    mc->stopAllActions();
    mc->runAction(SequenceAction::create(mc, SEQ_ACT_ATTACK));
    
    unschedule(schedule_selector(CcbPetInfoLayer::updateForEff));
    schedule(schedule_selector(CcbPetInfoLayer::updateForEff), 1.0 / 24);
}

void CcbPetInfoLayer::stopEff()
{
    isParitleStop = true;
    curFrame = 0;
    unschedule(schedule_selector(CcbPetInfoLayer::updateForEff));
    //清除特效}
    for (int i = 0; i < arrCurParticle.size(); i++) {
        if (arrCurParticle[i]) {
            arrCurParticle[i]->stopSystem();
            arrCurParticle[i]->removeFromParentAndCleanup(true);
            arrCurParticle[i] = NULL;
        }
    }
    arrCurParticle.clear();
    
    if (isRealSkill) {
        SequencePet* mc = dynamic_cast<SequencePet*>(m_pSpritePetMc->getParent()->getChildByTag(11));
        if (!mc) {
            return;
        }
        mc->stopAllActions();
        showPetBgEff();
        mc->runAction(CCRepeatForever::create(CCSequence::create(
                                                                 SequenceAction::create(mc, SEQ_ACT_STAND),
                                                                 SequenceAction::create(mc, SEQ_ACT_STAND),
                                                                 SequenceAction::create(mc, SEQ_ACT_STAND),
                                                                 CCCallFunc::create(this, callfunc_selector(CcbPetInfoLayer::hidePetBgEff)),
                                                                 CCCallFunc::create(this, callfunc_selector(CcbPetInfoLayer::showNor)),
                                                                 SequenceAction::create(mc, SEQ_ACT_ATTACK),
                                                                 CCCallFunc::create(this, callfunc_selector(CcbPetInfoLayer::showPetBgEff)),
                                                                 NULL)));
    }
    
}

void CcbPetInfoLayer::updateForEff(float time)
{
    curFrame++;
    if (curFrame > allFrame) {
        unschedule(schedule_selector(CcbPetInfoLayer::updateForEff));
        stopEff();
        return;
    }
    
    if ((isRealSkill && m_mapAltKeyFrame.find(curFrame) == m_mapAltKeyFrame.begin())
        ||(!isRealSkill && m_mapKeyFrame.find(curFrame) == m_mapKeyFrame.begin())) {
        showArmEff();
    }
    
    
    if ((isRealSkill && m_mapAltKeyFrame.find(curFrame) != m_mapAltKeyFrame.end())
        ||(!isRealSkill && m_mapKeyFrame.find(curFrame) != m_mapKeyFrame.end())) {
        
        PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_wPetIndexId);
        if (!petCfg) {
            return;
        }
        if (isRealSkill) {
            CMusicCtrl::PlayEffect(petCfg->wAltEffSound);
        }
        else{
            CMusicCtrl::PlayEffect(petCfg->wMusicId);
        }
        showHitEff();
    }
}

//显示序列帧特效}
void CcbPetInfoLayer::showArmEff()
{
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_wPetIndexId);
    if (!petCfg) {
        return;
    }
    uint32 effId = 0;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *cfg = NULL;
    if(isRealSkill){
        cfg = GET_CONFIG_STC(UltimateSkillConfig, petCfg->wInitialSkillId);
    }
    else{
        cfg = GET_CONFIG_STC(UltimateSkillConfig, petCfg->dwNomaleAttId);
    }
    if (cfg) {
        effId = cfg->wShowEffectId;
    }
    if(!effId){
        return;
    }
    EffectGroupConfig::STC_EFFECT_GROUP_CONFIG *effGroup = GET_CONFIG_STC(EffectGroupConfig, effId);
    if (!effGroup || effGroup->strArmEff == "" || strcmp(effGroup->strArmEff.c_str(), "0") == 0) {
        return;
    }

    CCPoint pos = ccp(115, 68);
    CCString* str = CCString::createWithFormat(ALT_ARMATURE_PATH, effGroup->strArmEff.c_str(), effGroup->strArmEff.c_str());
    AltEffArmature* arm = AltEffArmature::create(str->getCString(), effGroup->strArmEff.c_str());
    if (arm) {
        arm->setPosition(pos);
        arm->setRotationY(180);
        m_pSpritePetMc->getParent()->addChild(arm, 6);
    }
    
}

void CcbPetInfoLayer::showHitEff()
{
    if (isParitleStop) {
        return;
    }
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_wPetIndexId);
    if (!petCfg) {
        return;
    }
    //显示特效}
    uint32 effId = 0;
    if (isRealSkill) {
        UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *cfg = GET_CONFIG_STC(UltimateSkillConfig, petCfg->wInitialSkillId);
        if (cfg) {
            effId = cfg->wShowEffectId;
        }
    }
    else
    {
        effId = petCfg->wEffectId;
    }
    
    EffectGroupConfig::STC_EFFECT_GROUP_CONFIG *effGroup = GET_CONFIG_STC(EffectGroupConfig, effId);
    if (!effGroup) {
        return;
    }

    showHitEff(effId);

}

void CcbPetInfoLayer::showHitEff(uint32 effGroupId)
{
    CCArray *arrAct = CCArray::create();
    EffectGroupConfig::STC_EFFECT_GROUP_CONFIG *effGroup = GET_CONFIG_STC(EffectGroupConfig, effGroupId);
    float time=0;
    CCPoint pos = ccp(115, 68);
    for (int i = 0; i < effGroup->effParts.size(); i++) {
        if (effGroup->effParts[i] == "0" || effGroup->effParts[i] == "") {
            continue;
        }
        CCParticleSystemQuad *particle = CCParticleSystemQuad::create(GET_BATTLE_LIST_EFF(effGroup->effParts[i]));
        if (!particle) {
            continue;
        }

        particle->setRotationY(180);
        particle->setPosition(pos);

        arrAct->addObject(CCCallFuncO::create(this, callfuncO_selector(CcbPetInfoLayer::onParticle), particle));
        if (effGroup->byType == 1) {    //一起}
            time = time > particle->getDuration()? time : particle->getDuration();
        }
        else if (effGroup->byType == 2) {   //顺序}
            time += particle->getDuration();
            arrAct->addObject(CCDelayTime::create(particle->getDuration()));
        }
        
    }
    if (arrAct->count() > 0) {
        CCActionInterval *act = NULL;
        if (effGroup->byType == 1) {    //一起}
            act = CCSpawn::create(arrAct);
        }
        else if (effGroup->byType == 2)   //顺序}
        {
            act = CCSequence::create(arrAct);
        }
        if (act) {
            this->runAction(act);
        }
    }
    
}

void CcbPetInfoLayer::onParticle(CCObject *pObject)
{
    CCParticleSystemQuad *particle = (CCParticleSystemQuad *)pObject;
    if (isParitleStop) {
        return;
    }
    if (!particle->getParent()) {
        
        arrCurParticle.push_back(particle);
        
        m_pSpritePetMc->getParent()->addChild(particle, 5);
    }
    //    }
}