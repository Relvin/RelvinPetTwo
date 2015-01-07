#include "CcbTujianShowLayer.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "EnumDefines.h"
#include "SequencePet.h"
#include "SequenceAction.h"
#include "UISupport.h"
#include "Pet.h"
#include "MusicCtrl.h"
#include "BackCtrl.h"
#include "GuideData.h"
#include "Instruments.h"
#include "ResourceStringClient.h"
#include "GachaDataMgr.h"
#include "PetLoadingLayer.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;


PetTujianShowScene::PetTujianShowScene()
{
    
}
PetTujianShowScene::~PetTujianShowScene()
{
    
}
CCScene * PetTujianShowScene::scene()
{
    CCScene *scene = CCScene::create();
    PetTujianShowScene *layer = PetTujianShowScene::create();
    scene->addChild(layer);
    return scene;
}
bool PetTujianShowScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbTujianShowLayer(this));
    return true;
}

void PetTujianShowScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void PetTujianShowScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void PetTujianShowScene::onExit()
{
	CCLayer::onExit();
}

void PetTujianShowScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

CcbTujianShowLayer::~CcbTujianShowLayer()
{
    CC_SAFE_RELEASE_NULL(m_pSpriteBg);
    CC_SAFE_RELEASE_NULL(m_pLayerHaloLight);
    CC_SAFE_RELEASE_NULL(m_pSpritePaint);
    CC_SAFE_RELEASE_NULL(m_pSpriteStar);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    CC_SAFE_RELEASE_NULL(m_pSpriteExp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFProperty);
    CC_SAFE_RELEASE_NULL(m_pSpritePetType);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Text_SkillInfo);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNormal_AtkName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSkill_alkName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFHp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRec);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAtt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCrit);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSDef);
    CC_SAFE_RELEASE_NULL(m_pControlButtonShowSkill);
    CC_SAFE_RELEASE_NULL(m_pLayerBottom);
    CC_SAFE_RELEASE_NULL(m_pLayerTitle);
    CC_SAFE_RELEASE_NULL(m_pLayerBack);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJiPan1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJiPan2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJiPan3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJiPan4);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBadage1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBadage2);
    
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTujianShowLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTujianShowLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTujianShowLayer", CcbTujianShowLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/petshowtitle.ccb]", [ccb/petshowtitle.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/petshow_back.ccb]", [ccb/petshow_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/petshow_skill.ccb]", [ccb/petshow_skill.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/tujian_show.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/
bool CcbTujianShowLayer::m_bTouchThenBack = false;

void CcbTujianShowLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
}

bool CcbTujianShowLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    /*
     1、十连抽，新宠进来后，点击直接返回
     2、单抽，开始不可点击；显示出宠物后，点击显示技能；显示完技能，点击返回
     3、图鉴，点击发声
     */
    if (m_bStep1End) {
        showTitleABottom();
        m_bStep1End = false;
        return false;
    }

    if (m_bLock3s) {
        return true;
    }
    
    CCRect rect = m_pControlButtonShowSkill->boundingBox();
    CCPoint p = pTouch->getLocation();
    if (rect.containsPoint(p)) {
        return false;
    }
    rect = m_pLayerBack->boundingBox();
    if (rect.containsPoint(p)) {
        return false;
    }
    rect = m_pLayerTitle->boundingBox();
    if (rect.containsPoint(p)) {
        return false;
    }
    
    return true;
}

void CcbTujianShowLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bLock3s) {
        return;
    }
    
    if (m_bStep2End && m_bTouchThenBack) {
        BackCtrl::BacktoUpperScene(kFadeTrans);
        m_bTouchThenBack = false;
        
        CCLog("back from tujianshow!!!!!!!!");
        
        return;
    }
    
        //技能释放时播放技能语音}
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_petIndex);
    if (petCfg) {
        CMusicCtrl::StopEffect(m_soundId);
        m_soundId = CMusicCtrl::PlayEffect(GET_PET_SOUND(petCfg->wSoundAlt));
    }
    return;
    
}

bool CcbTujianShowLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    this->setTouchEnabled(true);
	return true;
}

void CcbTujianShowLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
    
    //技能释放时播放技能语音}
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_petIndex);
    if (petCfg) {
        CMusicCtrl::StopEffect(m_soundId);
        m_soundId = CMusicCtrl::PlayEffect(GET_PET_SOUND(petCfg->wSoundAlt));
    }
    
    //如果是单抽，显示抽宠动画
    if (g_GachaData->m_vecGachaPetIdx.size() == 1) {
        showOnePet();
        return;
    }
    
    showGuide();
}

void CcbTujianShowLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbTujianShowLayer::showGuide()
{
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger == GuideData::E_GUIDE_TRIGGER_3_GACHA) {
        m_bLock3s = true;
        PetLoadingLayer::sharedLayer()->WaitForPacket(true);
        this->runAction(
                        CCSequence::create(
                                           CCDelayTime::create(0.1f),
                                           CCCallFunc::create(this, callfunc_selector(CcbTujianShowLayer::addGuideLayer)),
                                           NULL
                                           )
                        );
    } else if (wTrigger == GuideData::E_GUIDE_TRIGGER_5_GACHA) {
        this->runAction(
                        CCSequence::create(
                                           CCDelayTime::create(0.1f),
                                           CCCallFunc::create(this, callfunc_selector(CcbTujianShowLayer::addGuideLayer)),
                                           NULL
                                           )
                        );
    }
}

void CcbTujianShowLayer::addGuideLayer()
{
    m_bLock3s = false;
    PetLoadingLayer::sharedLayer()->End();
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonShowSkill, GuideBtnPos::E_PET_INFO);
    }
    GuideData::GetInstance()->addGuideLayer();
}

void CcbTujianShowLayer::onExit()
{
    CCTextureCache::sharedTextureCache()->removeTextureForKey(CPetCtrl::Get()->GetPetBodyPicName(m_petIndex).c_str());
    m_bTouchThenBack = false;
	CCLayer::onExit();
}

void CcbTujianShowLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
    CCDirector::sharedDirector()->purgeCachedData();
    
}

// Inhert MemberVariableAssigner
bool CcbTujianShowLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBack", CcbPetShowBackLayer*, this->m_pLayerBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHaloLight", CcbHaloLightLayer*, this->m_pLayerHaloLight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePaint", CCSprite*, this->m_pSpritePaint);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar", CCSprite*, this->m_pSpriteStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteExp", CCSprite*, this->m_pSpriteExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFProperty", CCLabelTTF*, this->m_pLabelTTFProperty);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetType", CCSprite*, this->m_pSpritePetType);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Text_SkillInfo", CCLabelTTF*, this->m_pLabelTTF_Text_SkillInfo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNormal_AtkName", CCLabelTTF*, this->m_pLabelTTFNormal_AtkName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSkill_alkName", CCLabelTTF*, this->m_pLabelTTFSkill_alkName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFHp", CCLabelTTF*, this->m_pLabelTTFHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRec", CCLabelTTF*, this->m_pLabelTTFRec);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAtt", CCLabelTTF*, this->m_pLabelTTFAtt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCrit", CCLabelTTF*, this->m_pLabelTTFCrit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCDef", CCLabelTTF*, this->m_pLabelTTFCDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSDef", CCLabelTTF*, this->m_pLabelTTFSDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShowSkill", CCControlButton*, this->m_pControlButtonShowSkill);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, this->m_pLayerBottom);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTitle", CCLayer*, this->m_pLayerTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJiPan1", CCLabelTTF*, this->m_pLabelTTFJiPan1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJiPan2", CCLabelTTF*, this->m_pLabelTTFJiPan2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJiPan3", CCLabelTTF*, this->m_pLabelTTFJiPan3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJiPan4", CCLabelTTF*, this->m_pLabelTTFJiPan4);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBadage1", CCLabelTTF*, this->m_pLabelTTFBadage1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBadage2", CCLabelTTF*, this->m_pLabelTTFBadage2);
	return false;
}

bool CcbTujianShowLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTujianShowLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTujianShowLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTujianShowLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShowSkill", CcbTujianShowLayer::onPressControlButtonShowSkill);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTujianShowLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_petIndex = 0;
    m_soundId = 0;
    m_canTouch = true;
    m_bLock3s = false;
    m_bStep1End = false;
    m_bStep2End = true;
    m_pSpriteStar->setVisible(false);
    m_pLabelTTFProperty->noStroke();
    
    arrQyName[0] = m_pLabelTTFJiPan1;
    arrQyName[1] = m_pLabelTTFJiPan2;
    arrQyName[2] = m_pLabelTTFJiPan3;
    arrQyName[3] = m_pLabelTTFJiPan4;
    
    arrQyName[4] = m_pLabelTTFBadage1;
    arrQyName[5] = m_pLabelTTFBadage2;
    
    m_pSpritePaint->setPositionY((getBottom(m_pLayerBack) + (getTop(m_pLayerBottom) - 20)) * 0.5 );
    
    m_pControlButtonShowSkill->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pSpritePaint->runAction(
                              CCRepeatForever::create(
                                                      CCSequence::create(
                                                                         CCScaleTo::create(1.5, 0.95),
                                                                         CCScaleTo::create(1.5, 1.0),
                                                                         NULL
                                                                         )
                                                      )
                              );
    
}

void CcbTujianShowLayer::onPressControlButtonShowSkill(CCObject* pSender, CCControlEvent event)
{
    if (m_bLock3s) {
        return;
    }
    
    if (getChildByTag(111)) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    GuideData::GetInstance()->onlyRmGuideLayer();
    
    BackCtrl::InsertNextScene(kPetInfoScene);
}


void CcbTujianShowLayer::loadData()
{
    uint16 petId = CPetCtrl::Get()->getPetTujianShowId();
    if (!petId) {
        CCString *str = CCString::createWithFormat("not find petIndex : %d" , petId);
        CCMessageBox(str->getCString(), "Error");
        return;
    }
//    m_pLayerHaloLight->setShowInfoByIndex(petId);
    
    m_petIndex = petId;
    //返回按钮}
    m_pLayerBack->loadData(m_petIndex);
    //原画}
    m_pSpritePaint->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(m_petIndex));
//    m_pSpritePaint->setAnchorPoint(ccp(0.5, 0));
    //背景}
//    m_pSpriteBg->setDisplayFrame(CPetCtrl::Get()->GetPetShowFramePicSF(petId));
    //头}

    
    //宠物类型}
    m_pLabelTTFProperty->setString(CPetCtrl::Get()->GetPetTypeString(m_petIndex).c_str());
    //类型图片}
    m_pSpritePetType->setDisplayFrame(CPetCtrl::Get()->GetPetTypeSF(m_petIndex));
    
    PetConfig::STC_PET_CONFIG* cfg = GET_CONFIG_STC(PetConfig, m_petIndex);
    
    //必杀技能}
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* cfgUlt = GET_CONFIG_STC(UltimateSkillConfig, cfg->wInitialSkillId);
    if (cfgUlt) {
        CCString *str = CCString::createWithFormat("%s·%s ", cfgUlt->strName.c_str(), covert2Roman(1).c_str());
        
        m_pLabelTTFSkill_alkName->setString(str->getCString());
    }
    else{
        m_pLabelTTFSkill_alkName->setString(GET_STR(Str_wu));
    }
    //普通技能
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* cfgNor = GET_CONFIG_STC(UltimateSkillConfig, cfg->dwNomaleAttId);
    if (cfgNor) {
        CCString *str = CCString::createWithFormat("%s", cfgNor->strName.c_str());
        
        m_pLabelTTFNormal_AtkName->setString(str->getCString());
    }
    
    //情缘
    int qyCnt = 0;
    for (int i = 0; i < 4; i ++) {
        uint32 qyId = cfg->arrQyIndex[i];
        if (!qyId) {
            continue;
        }
        QingYuanConfig::STC_QING_YUAN_CONFIG* qyCfg = GET_CONFIG_STC(QingYuanConfig, qyId);
        if (!qyCfg) {
            continue;
        }
        arrQyName[qyCnt]->setString(qyCfg->strName.c_str());
        arrQyName[qyCnt]->setColor(ccGRAY);
        qyCnt++;
    }
//    for (; qyCnt < 4; qyCnt++) {
//        arrQyName[qyCnt]->setString("");
//    }
    
//    int emCnt = 0;
    EmblemShowConfig::STC_EMBLEM_SHOW_CONFIG* eCfg = GET_CONFIG_STC(EmblemShowConfig, cfg->wGroupId);
    if (eCfg) {
        for (int i = 0; i < 2; i++) {
            if (!eCfg->wExcEmIndex[i]) {
                continue;
            }
            EmblemConfig::STC_EMBLEM_CONFIG *emCfg = GET_CONFIG_STC(EmblemConfig, eCfg->wExcEmIndex[i]);
            if (!emCfg) {
                continue;
            }
            arrQyName[qyCnt]->setString(emCfg->strName.c_str());
            arrQyName[qyCnt]->setColor(ccGRAY);
            qyCnt++;
        }
    }
    if (qyCnt == 0) {
        qyCnt++;
        arrQyName[0]->setString(GET_STR(Str_wu));
        arrQyName[0]->setColor(ccWHITE);
    }
    
    for (; qyCnt < 6; qyCnt++) {
        arrQyName[qyCnt]->setString("");
    }
    
    
    //六维属性
    //HP
    CCString*str = CCString::createWithFormat("%d", cfg->dwHpValue);
    m_pLabelTTFHp->setString(str->getCString());
    //Rev
    str->initWithFormat("%d", cfg->dwRecoverValue);
    m_pLabelTTFRec->setString(str->getCString());
    //Atk
    if (cfgNor&& cfgNor->byHurtType == E_SPELL_HURT_SPE_ATK) {
        str->initWithFormat("%d", cfg->dwSAttackValue);
    }
    else{
        str->initWithFormat("%d", cfg->dwAttackValue);
    }
    
    m_pLabelTTFAtt->setString(str->getCString());
    //Crit
    str->initWithFormat("%d%%", cfg->dwLuckValue / 100);
    m_pLabelTTFCrit->setString(str->getCString());
    //CDef
    str->initWithFormat("%d", cfg->dwDeffenseValue);
    m_pLabelTTFCDef->setString(str->getCString());
    //SDef
    str->initWithFormat("%d", cfg->dwSDeffenseValue);
    m_pLabelTTFSDef->setString(str->getCString());
    
}


//单个}
void CcbTujianShowLayer::showOnePet()
{

    PetConfig::STC_PET_CONFIG* petCfg = GET_CONFIG_STC(PetConfig, m_petIndex);
    if (!petCfg) {
        return;
    }
    m_bTouchThenBack = true;

    m_bStep1End = false;
    m_bStep2End = false;
    
    m_pLayerTitle->setPositionY(m_pLayerTitle->getPositionY() + 150);
    m_pLayerBack->setPositionY(m_pLayerBack->getPositionY() + 150);
    m_pLayerBottom->setPositionY(-getHeight(m_pLayerBottom));
    
    m_pLayerStarBg = CCLayer::create();
    m_pLayerStarBg->setPosition(ccp(m_pSpriteStar->getPosition().x, getBottom(m_pSpriteStar) - 10));
    m_pLayerStarBg->ignoreAnchorPointForPosition(false);
    m_pLayerStarBg->setAnchorPoint(ccp(0.5,0));
    m_pLayerStarBg->setContentSize(CCSizeMake(320, getHeight(m_pLayerStarBg)));
    m_pSpriteStar->getParent()->addChild(m_pLayerStarBg);
    
    
    uint8 quality = CPetCtrl::Get()->getPetQuality(m_petIndex);

    //名字}
    m_pLabelTTFName->setVisible(true);
    m_pLabelTTFName->setString(petCfg->strName.c_str());

    //星级}
    uint8 starLv = petCfg->byStarLv;
    float width = getWidth(m_pSpriteStar)* starLv;// + 2*(starLv - 1);

    m_pLayerStarBg->setContentSize(CCSizeMake(width, 30));
    curStarCnt = 0;
    maxStarCnt = starLv;
    
    CCString* path = CCString::createWithFormat("ccbresources/12monthdate/gacha/level%d.plist", quality);
    CCParticleSystemQuad* light = CCParticleSystemQuad::create(path->getCString());
    
    if (light) {
        light->setPosition(ccp(160, 140));
        m_pSpritePaint->getParent()->addChild(light);
    }
    
    switch (quality) {
        case E_GACHA_EGG_TYPE_XIYOU:
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_rare));
            break;
        case E_GACHA_EGG_TYPE_CHAO_XIYOU:
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_more_rare));
            break;
        case E_GACHA_EGG_TYPE_CHAOJUE_XIYOU:
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_most_rare));
            break;
        case E_GACHA_EGG_TYPE_BAST:
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_most_rare));
            break;
            
        default:
            break;
    }
    
    //最大星级}
    if (starLv == 6) {
        CMusicCtrl::PlayEffect( GET_MUSIC(Eff_get_epic_pet) );
    }
    else{
        CMusicCtrl::PlayEffect( GET_MUSIC(Eff_gacha_pet) );
    }

    schedule(schedule_selector(CcbTujianShowLayer::addStar), 0.3);

    //文字}
    showText(quality, starLv);
}
//显示星级}
void CcbTujianShowLayer::addStar(float time)
{
    if (curStarCnt >= maxStarCnt) {
        unschedule(schedule_selector(CcbTujianShowLayer::addStar));

        return;
    }
    CCNode *star = CcbManager::sharedManager()->LoadCcbGachaResultStar(this);
    star->ignoreAnchorPointForPosition(false);
    star->setAnchorPoint(ccp(0, 0));
    star->setPosition(ccp(curStarCnt*getWidth(m_pSpriteStar), 0));
    m_pLayerStarBg->addChild(star);
    
    curStarCnt++;
}

void CcbTujianShowLayer::showText(uint8 type, uint8 star)
{
    CCNode* node = NULL;
    float time = 0.1;
    switch (type) {
        case E_GACHA_EGG_TYPE_XIYOU:
            time = star * 0.5 + 1;
            break;
            
        case E_GACHA_EGG_TYPE_CHAO_XIYOU:
            node = CcbManager::sharedManager()->LoadCcbGachaResultChaoXiyou(this);
            time = 1.5;
            break;
            
        case E_GACHA_EGG_TYPE_CHAOJUE_XIYOU:
            node = CcbManager::sharedManager()->LoadCcbGachaResultChaojueXiyou(this);
            time = 1.5;
            break;
            
        case E_GACHA_EGG_TYPE_BAST:
            node = CcbManager::sharedManager()->LoadCcbGachaResultChaojueXiyou(this);
            time = 1.5;
            break;
            
        default:
            break;
    }
    if (node) {
        node->setPosition(ccp(0, 0));
        m_pSpritePaint->getParent()->addChild(node, 10);
        
    }
    this->runAction(CCSequence::create(CCDelayTime::create(time + 0.2),
                                       CCCallFunc::create(this, callfunc_selector(CcbTujianShowLayer::step1End)),
                                       NULL));
    
}
void CcbTujianShowLayer::step1End()
{
    m_bStep1End = true;
}
void CcbTujianShowLayer::step2End()
{
    m_bStep2End = true;
    
    showGuide();
    m_canTouch = true;
}
void CcbTujianShowLayer::showTitleABottom()
{
    
    m_pLayerTitle->runAction(CCMoveBy::create(0.5, ccp(0, -150)));
    m_pLayerBack->runAction(CCMoveBy::create(0.5, ccp(0, -150)));
    m_pLayerBottom->runAction(CCMoveBy::create(0.5, ccp(0, getHeight(m_pLayerBottom))));
    this->runAction(CCSequence::create(CCDelayTime::create(1.5),
                                       CCCallFunc::create(this, callfunc_selector(CcbTujianShowLayer::step2End)),
                                       NULL));
}
