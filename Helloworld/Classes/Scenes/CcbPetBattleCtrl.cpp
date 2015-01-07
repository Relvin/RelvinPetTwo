#include "CcbPetBattleCtrl.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "ShowPetBattleWord.h"
#include "ResourcePic.h"
#include "ConfigGet.h"
#include "ConfigUtil.h"
#include "ResourceDefine.h"
#include "FightAI.h"
#include "FightTeam.h"
#include "FightPet.h"
#include "PetBattleControlDelegate.h"
#include "PetCtrl.h"
#include "CcbAltSkillEffLayer.h"
#include "GuideData.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "Pet.h"
#include "EffectLayer.h"
#include "MusicCtrl.h"
#include "ArmatureManager.h"
#include "GameSession.h"
#include "Role.h"
#include "PacketDataMgr.h"
#include "CcbPetBattleLayer.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

USING_NS_CC;
USING_NS_CC_EXT;

CcbPetBattleCtrl::~CcbPetBattleCtrl()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteHpBar2);
	CC_SAFE_RELEASE_NULL(m_pSpriteHpBar);
	CC_SAFE_RELEASE_NULL(m_pSpritePowerBar);
	CC_SAFE_RELEASE_NULL(m_pSpriteNature);
	CC_SAFE_RELEASE_NULL(m_pSpriteBgNormal);
	CC_SAFE_RELEASE_NULL(m_pSpriteBgDead);
	CC_SAFE_RELEASE_NULL(m_pSpriteBgNothing);
    CC_SAFE_RELEASE_NULL(m_pLayerSkillFull);
    CC_SAFE_RELEASE_NULL(m_pLayerEffBg);
    CC_SAFE_RELEASE_NULL(m_pSpriteFace);
    CC_SAFE_RELEASE_NULL(m_pSpriteLvStar);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetBattleCtrl( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetBattleCtrl( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetBattleCtrl", CcbPetBattleCtrlLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_ctrl.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/
void CcbPetBattleCtrl::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 10, false);
}

bool CcbPetBattleCtrl::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbPetBattleCtrl::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    
}

void CcbPetBattleCtrl::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetBattleCtrl::onExit()
{
	CCLayer::onExit();
}

void CcbPetBattleCtrl::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetBattleCtrl::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteHpBar2", CCSprite*, this->m_pSpriteHpBar2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteHpBar", CCSprite*, this->m_pSpriteHpBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePowerBar", CCSprite*, this->m_pSpritePowerBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNature", CCSprite*, this->m_pSpriteNature);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBgNormal", CCSprite*, this->m_pSpriteBgNormal);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBgDead", CCSprite*, this->m_pSpriteBgDead);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBgNothing", CCSprite*, this->m_pSpriteBgNothing);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerSkillFull", CCLayer*, this->m_pLayerSkillFull);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEffBg", CCLayer*, this->m_pLayerEffBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFace", CCSprite*, this->m_pSpriteFace);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLvStar", CCSprite*, this->m_pSpriteLvStar);
	return false;
}

bool CcbPetBattleCtrl::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetBattleCtrl::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetBattleCtrl::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetBattleCtrl::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetBattleCtrl::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}

    barHpWidth = getWidth(m_pSpriteHpBar2);
    barPowerWidth = getWidth(m_pSpritePowerBar);
    m_pLayerSkillFull->setVisible(false);
    m_bIsEnable = true;
    m_isPalsy = false;
    m_isSeal = false;
    m_isBingDong = false;
    m_isZhongDu = false;
    m_isZhuoShao = false;
    m_isConfused = false;
    isFirstFull = false;
    m_regulate = 0;
    m_battleIndex = 0;
    m_pSpriteBg->setZOrder(-2);
    m_bLockDelay = true;
    m_pSpriteFace->getParent()->setVisible(false);
}

void CcbPetBattleCtrl::setBattleIndex(uint16 bIndex, PetBattleControlDelegate *delegate)
{
    m_battleIndex = bIndex;
    _delegate = delegate;
    loadData();
}

void CcbPetBattleCtrl::loadData()
{
    FightPet *fPet = FightAI::Get()->getMyTeam()->GetTeam()[m_battleIndex];
    if (!fPet || fPet->getPetInfo().wPetIndexId == 0) {
//        m_pLayerNormal->setVisible(false);
        m_battleIndex = 0;
        m_pSpriteBgDead->setVisible(false);
        m_pSpriteBgNothing->setVisible(true);
        return;
    }
    STC_PET_CTRL_INFO pet;
    pet.petBattleIndex = fPet->getPetInfo().wBattleIndex;
    pet.petIndex = fPet->getPetInfo().wPetIndexId;
    pet.petNature = fPet->getPetInfo().petNature;
    
    pet.curHP = fPet->getPetInfo().wHP;
    pet.maxHP = fPet->getCurHP();

    pet.petState = 0;
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, pet.petIndex);
    pet.name = petCfg->strName;
    pet.maxSkillValue = fPet->getPetInfo().wAllPower;
    pet.curSkillValue = 0;//fPet->getCurPower();
    pet.regulateState = 0;

    petInfo = pet;
    
    //头像}
    m_pSpriteIcon->setTexture(CPetCtrl::Get()->GetPetBattleHeadTexture(petInfo.petIndex));
    //属性}
    CCSpriteFrame *sf = CPetCtrl::Get()->GetPetNaturePicSF(petInfo.petIndex);
    m_pSpriteNature->setDisplayFrame(sf);
    
    //框
    m_pSpriteBgNormal->setDisplayFrame(g_PacketDataMgr->getBattleFrame(petInfo.petIndex));
    
    //星级
    m_pSpriteLvStar->setScale(1.0);
    m_pSpriteLvStar->removeAllChildren();
    m_pSpriteLvStar->setContentSize(CCSizeMake(m_pSpriteLvStar->getTexture()->getContentSize().width, getHeight(m_pSpriteLvStar)));
    for (int i = 1; i < petCfg->byStarLv; i++) {
        CCSprite *star = CCSprite::createWithTexture(m_pSpriteLvStar->getTexture());// ("ccbresources/12monthdate/pet/pic_lvstar.png");
        m_pSpriteLvStar->setContentSize(star->getContentSize());
        star->setAnchorPoint(ccp(0, 0));
        star->setPosition(ccp(i*getWidth(star)*0.75, 0));
        m_pSpriteLvStar->addChild(star);
    }
    m_pSpriteLvStar->setContentSize(CCSizeMake((getWidth(m_pSpriteLvStar)*0.75)*(petCfg->byStarLv-1)+ getWidth(m_pSpriteLvStar)*0.75, getHeight(m_pSpriteLvStar)));
    m_pSpriteLvStar->setScale(0.75);
    
    CTeam* team = CTeamCtrl::GetCurTeam();
    m_ObjId = team->getarrPetObId()[m_battleIndex % 100];
    
    //初始化血条、气条}
    Reflash(petInfo);
}


void CcbPetBattleCtrl::Reflash(STC_PET_CTRL_INFO pet )
{
    petInfo = pet;
    
    loseHP(petInfo.curHP);
    
    setPower(petInfo.curSkillValue);
    
    setCtrlState(petInfo.petState);
    
    setRegulateState(petInfo.regulateState);
}

void CcbPetBattleCtrl::loseHP(int curHp)
{
    petInfo.curHP = curHp;
    
    float f = curHp * 100.0 /petInfo.maxHP;

    if (f < 100) {
        m_pSpriteHpBar->setVisible(false);
        m_pSpriteHpBar2->setVisible(true);
    }
    else
    {
        m_pSpriteHpBar->setVisible(true);
        m_pSpriteHpBar2->setVisible(false);
    }
    
    m_pSpriteHpBar2->setTextureRect(CCRectMake(0, 0, f / 100 * barHpWidth, getHeight(m_pSpriteHpBar)));
    
    if (petInfo.curHP == 0) {
        setCtrlState(E_PET_STATE_DEAD);
    }
}

void CcbPetBattleCtrl::setPower(uint32 curPower)
{
    FightPet* fPet = FightAI::Get()->getFightPetByBIndex(m_battleIndex);
    if (!fPet || fPet->getIsWaitSkill()) {
        return;
    }
    
    int add = curPower - petInfo.curSkillValue;
    
    if (add != 0 && add != -petInfo.maxSkillValue) {
        showSPAdd(add);
    }
    
    if (curPower >= petInfo.maxSkillValue) {
        curPower = petInfo.maxSkillValue;
    }
    
    float f = curPower * 100.0 / petInfo.maxSkillValue;
    f = f > 100? 100 : f;

    m_pSpritePowerBar->setTextureRect(CCRectMake(0, 0, f / 100 * barPowerWidth, getHeight(m_pSpritePowerBar)));
    //如果技能条满了，显示闪电特效}
    
    petInfo.curSkillValue = curPower;
    if (petInfo.curSkillValue >= petInfo.maxSkillValue) {
        if (!isFirstFull) {
            isFirstFull = true;
            
            if (petInfo.maxSkillValue > 0
                && petInfo.curHP > 0 ) {
                showSkillFull();
            }
        }
        else{
            showFlowFire();
        }
    }
    else
    {
        isFirstFull = false;
        hideFlowFire(NULL);
    }
}


void CcbPetBattleCtrl::setCtrlState(uint8 ctrlState)
{
    if (petInfo.petState == E_PET_STATE_DEAD) {
        return;
    }
    
    if (m_isPalsy && petInfo.petState != E_PET_STATE_DEAD) {
    }
    petInfo.petState = ctrlState;
    
    m_pSpriteBgDead->setVisible(false);
    m_pSpriteBgNothing->setVisible(false);
    
    switch (ctrlState) {
        case E_PET_STATE_NORMAL:
            
            break;
        case E_PET_STATE_SKILL_FULL:
            break;
        case E_PET_STATE_DEAD:
            m_pSpriteBgDead->setVisible(true);
//            this->runAction(CCMoveBy::create(0.1, ccp(0, -8)));
            m_pLayerEffBg->removeAllChildren();
            
            
            hideFlowFire(NULL);
            break;
        case E_PET_STATE_NOTHING:
            m_pSpriteBgNothing->setVisible(true);
        default:
            break;
    }
}

void CcbPetBattleCtrl::setRegulateState(uint8 regulateState)
{
    petInfo.regulateState = regulateState;

    //显示属性克制}
    switch (regulateState) {
        case E_ATTRIBUTE_REGULATE_NON:
            
            break;
        case E_ATTRIBUTE_REGULATE_DOWN:
            break;
        case E_ATTRIBUTE_REGULATE_UP:
            break;
        default:
            break;
    }
    
}

void CcbPetBattleCtrl::setIsPalsy(bool isPalsy)
{
    if (m_isPalsy == isPalsy) {
        return;
    }
    m_isPalsy = isPalsy;
    showBuffEff();
}

void CcbPetBattleCtrl::setIsSeal(bool isSeal)
{
    if (m_isSeal == isSeal) {
        return;
    }
    m_isSeal = isSeal;
    showBuffEff();
}

void CcbPetBattleCtrl::setIsConfused(bool isConfused)
{
    if (m_isConfused == isConfused) {
        return;
    }
    m_isConfused = isConfused;
    showBuffEff();
}

void CcbPetBattleCtrl::setIsBingDong(bool isBingDong)
{
    if (m_isBingDong == isBingDong) {
        return;
    }
    m_isBingDong = isBingDong;
    showBuffEff();
}


void CcbPetBattleCtrl::setIsZhongdu(bool isZhongdu)
{
    if (m_isZhongDu == isZhongdu) {
        return;
    }
    m_isZhongDu = isZhongdu;
    showBuffEff();
}

void CcbPetBattleCtrl::setIsZhuoShao(bool isZhuoShao)
{
    if (m_isZhuoShao == isZhuoShao) {
        return;
    }
    m_isZhuoShao = isZhuoShao;
    showBuffEff();
}

void CcbPetBattleCtrl::showBuffEff()
{
    /*
     麻痹
     混乱
     封印
     冰冻
     中毒
     灼烧*/
    uint8 eType = 0;
    if (m_isPalsy) {
        if (m_pLayerEffBg->getChildByTag(Arm_ef_mabi)) {
            return;
        }
        eType = Arm_ef_mabi;
    }
    else if (m_isConfused){
        if (m_pLayerEffBg->getChildByTag(Arm_ef_hunluan)) {
            return;
        }
        eType = Arm_ef_hunluan;
    }
    else if (m_isSeal){
        if (m_pLayerEffBg->getChildByTag(Arm_ef_fengyin)) {
            return;
        }
        eType = Arm_ef_fengyin;
    }
    else if (m_isBingDong){
        if (m_pLayerEffBg->getChildByTag(Arm_ef_bingdong)) {
            return;
        }
        eType = Arm_ef_bingdong;
    }
    else if (m_isZhongDu){
        if (m_pLayerEffBg->getChildByTag(Arm_ef_zhongdu)) {
            return;
        }
        eType = Arm_ef_zhongdu;
    }
    else if (m_isZhuoShao){
        if (m_pLayerEffBg->getChildByTag(Arm_ef_zhuoshao)) {
            return;
        }
        eType = Arm_ef_zhuoshao;
    }
    
    m_pLayerEffBg->removeAllChildren();
    if (eType == 0) {
        return;
    }
    
    CCArmature* arm = ArmatureManager::sharedManager()->LoadArmature(GET_ARM_PATH(eType), GET_ARM_NAME(eType));
    arm->setPosition(getWidth(m_pLayerEffBg)*0.5, getHeight(m_pLayerEffBg)*0.5);
    arm->ignoreAnchorPointForPosition(false);
    arm->setAnchorPoint(ccp(0.5, 0.5));
    m_pLayerEffBg->addChild(arm, eType);
}

void CcbPetBattleCtrl::setAttributeRegulate(int rate)
{
    uint8 regulate = E_ATTRIBUTE_REGULATE_NON;
    if (rate > 100) {
        regulate = E_ATTRIBUTE_REGULATE_UP;
    }
    else if(rate < 100)
    {
        regulate = E_ATTRIBUTE_REGULATE_DOWN;
    }
    if (regulate == petInfo.regulateState) {
        return;
    }
    setRegulateState(regulate);
}

void CcbPetBattleCtrl::onUpMove()
{
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    // 在Attack_touch_1,2,3,4,5,6的时候暂停界面，加上手指指引，引导点击}
    char szBuf[64];
    snprintf(szBuf, 64, "fake_battle_touch_%d", wTrigger - GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_1 + 1);
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent(szBuf);
#endif

    if (wTrigger == GuideData::E_GUIDE_TRIGGER_END_FAKE_ATTACK) {
        if (_delegate) {
            _delegate->remuseAll();
        }
        GuideData::GetInstance()->onlyRmGuideLayer();
        GuideData::GetInstance()->stepOver();
    }
    
    if (m_isSeal || m_isPalsy || m_isConfused) {
        return;
    }
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(m_battleIndex);
    if (!pet || pet->getIsWaitSkill()) {
        return;
    }
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->getPetInfo().wSkillId);
    if (!ultCfg) {
        return;
    }
    
    if (petInfo.curSkillValue == petInfo.maxSkillValue) {
        doSomeThing(pet->getPetInfo().wSkillId);
    }
    
    if (wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_2 ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_3 ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_4 ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_5 ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_6
        ) {
        GuideData::GetInstance()->addGuideLayer();
    }
}


//释放攻击}
void CcbPetBattleCtrl::doSomeThing(uint32 skillId)
{
    if (_delegate) {
//        hideFlowFire(NULL);
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_battle_push_uskill));
        _delegate->doSomething(petInfo.petBattleIndex, skillId);
    }
}


bool CcbPetBattleCtrl::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_battleIndex == 0) {
        return true;
    }
    
    CCPoint point = m_pSpriteBgNormal->convertToNodeSpace(pTouch->getLocation());
    if (!m_pSpriteBgNormal->boundingBox().containsPoint(point)) {
        return true;
    }
    
    if (rand() % 5 == 3) {

        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/face/face.plist");
        int ra = rand() % 30 + 1;
        CCSpriteFrame* sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%d.png", ra)->getCString());
        if (sf) {
            m_pSpriteFace->setDisplayFrame(sf);
            m_pSpriteFace->getParent()->stopAllActions();
            m_pSpriteFace->getParent()->setVisible(false);
            m_pSpriteFace->getParent()->setScale(0.1);
            m_pSpriteFace->getParent()->runAction(CCSequence::create(CCShow::create(),
                                                                     CCScaleTo::create(0.2, 1.0),
                                                                     CCDelayTime::create(1.0),
                                                                     CCHide::create(),
                                                                     NULL));
        }
    }
    
    this->runAction(CCScaleTo::create(0.1, 0.97));
    
    if (!m_bIsEnable) {
        return true;
    }
    
    if (petInfo.curHP <= 0 || petInfo.curSkillValue < petInfo.maxSkillValue) {
        return true;
    }
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_1) {
        if (m_bLockDelay) {
            return true;
        }
    }
    
    onUpMove();
    
    return true;
}

void CcbPetBattleCtrl::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    this->runAction(CCScaleTo::create(0.1, 1.0));
}
void CcbPetBattleCtrl::showSkillFull()
{
    showFlowFire();
}

void CcbPetBattleCtrl::showFlowFire()
{
    if (petInfo.petState == E_PET_STATE_DEAD) {
        hideFlowFire(NULL);
        return;
    }
    if (m_pLayerSkillFull) {
        m_pLayerSkillFull->setVisible(true);
    }
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (m_battleIndex == 6 && wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_1) {
        CcbPetBattleLayer::GetCurrScene()->pauseAll();
        GuideData::GetInstance()->addGuideLayer();
        
        m_bLockDelay = false;
        return;
    }
}

void CcbPetBattleCtrl::hideFlowFire(CCObject* object)
{
    if (m_pLayerSkillFull) {
        m_pLayerSkillFull->setVisible(false);
    }
}

void CcbPetBattleCtrl::showSPAdd(int add)
{
    string s = "+";
    if (add < 0) {
        s = "-";
    }
    CCString* str = CCString::createWithFormat("SP%s%d", s.c_str(), abs(add));
    CCLabelBMFont* lbl = CCLabelBMFont::create(str->getCString(), "ccbresources/font/font_sp.fnt");
    lbl->setPosition(getWidth(this)*0.5, m_pSpritePowerBar->getPositionY());
    lbl->setAnchorPoint(ccp(0.5, 0.5));
    lbl->ignoreAnchorPointForPosition(false);
    lbl->setScale(0.4);
    this->addChild(lbl, 100);
    lbl->setOpacity(0);
    lbl->runAction(
                   CCSequence::create(
                                      CCSpawn::create(
                                                      CCFadeIn::create(0.25),
                                                      CCMoveBy::create(0.25, ccp(0, 5)),
                                                      NULL
                                                      ),
                                      CCMoveBy::create(0.5, ccp(0, 10)),
                                      CCDelayTime::create(1.0),
                                      CCFadeOut::create(0.25),
                                      CCCallFuncN::create(this, callfuncN_selector(CcbPetBattleCtrl::removeSPAdd)),
                                      NULL
                                      )
                   );
}
void CcbPetBattleCtrl::removeSPAdd(CCNode* object)
{
    if (!object) {
        return;
    }
    object->removeFromParentAndCleanup(true);
}

