//
//  FightPetSprite.cpp
//  HelloWorld
//
//  Created by long on 13-9-2.
//
//

#include "FightPetSprite.h"

#include "FlccMovieAction.h"
#include "FlccMovieFPSAction.h"
#include "ResourcePic.h"

#include "UISupport.h"
#include "EnumDefines.h"
#include "ShowPetBattleWord.h"
#include "DropItemSprite.h"
#include "SpccMovieClip.h"
#include "SpccMovieAction.h"
#include "SpccMovieFPSAction.h"
#include "CcbPetBattleLayer.h"
#include "FightAI.h"
#include "FightPet.h"
#include "FightTeam.h"
#include "SequenceAction.h"
#include "MusicCtrl.h"
#include "CcbManager.h"
#include "CcbArenaFightLayer.h"
#include "EffectLayer.h"
#include "ArmatureManager.h"
#include "AltEffArmature.h"
#include "FlyTextLayer.h"
#include "CcbWorldBossFightLayer.h"

#define buffWidth   16
#define flccFPS     24

FightPetSprite::FightPetSprite()
:m_isSelected(false),
m_isStand(true),
m_isDead(false),
stopFrame(0),
m_isCanDead(false),
m_isHide(false),
m_isFighting(false)
{
    altEff = NULL;
    dustEff = NULL;
    lblLXAdd = NULL;
    arrDeadTPSkill.clear();
    arrComboOffNorm.clear();
    arrComboOffSkill.clear();
}
FightPetSprite::~FightPetSprite()
{
    
    altEff = NULL;
    dustEff = NULL;
    m_delegate = NULL;
    mc = NULL;
    m_MyTeam.clear();
    m_EnemyTeam.clear();
}
FightPetSprite* FightPetSprite::create(uint16 wBattleIndex, PetBattleControlDelegate *delegate)
{
    FightPetSprite *pRet = new FightPetSprite();
    if (pRet && pRet->init(wBattleIndex, delegate))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
void FightPetSprite::onEnter()
{
    CCLayer::onEnter();
    
    hpBar = dynamic_cast<CcbPetBattleHpBarLayer*>(CcbManager::sharedManager()->LoadCcbPetBattleHpBarLayer(this));
    hpBar->loadData(m_BattleIndex);
    hpBar->setPosition(ccpAdd(getMyPos(), ccp(-getWidth(hpBar)*0.5, standSize.height)));
    hpBar->setAnchorPoint(ccp(0.5, 0));
    
    hpBar->setVisible(false);
    isHpBarShow = false;
    
    dustEff = CcbManager::sharedManager()->LoadCcbBattleDust();
    dustEff->setPosition(ccp(standSize.width*0.5, 0));
    dustEff->setVisible(false);
    if (m_BattleIndex <= PetCnt) {
        dustEff->setRotationY(180);
    }
    addChild(dustEff, -1);
    
    if (m_BattleIndex <= PetCnt) {
        altEff = CcbManager::sharedManager()->LoadCcbPetBattleAltLoad();
        altEff->setPosition(ccp(0, 5));
        altEff->setVisible(false);
        addChild(altEff, 0);
    }
    
    FightPet* pet = FightAI::Get()->getFightPetByBIndex(m_BattleIndex);
    if (pet->getPetInfo().byEvoLv >= 6) {
        EffectLayer* effL2 = EffectLayer::create(E_ANI_EFFECT_PET_BG_ORANGE, -1, 1.0 / 10);
        effL2->setPosition(ccp(0, -20));
        effL2->setAnchorPoint(ccp(0.5, 0));
        effL2->ignoreAnchorPointForPosition(false);
        addChild(effL2, -2, 112);
        effL2->onRun();
    }
}

void FightPetSprite::showRunIn()
{
    CCParticleSystemQuad* eff1 = CCParticleSystemQuad::create("ccbresources/12monthdate/battle/battle_start1.plist");
    eff1->setPosition(ccp(0, standSize.height));
    addChild(eff1, 2);
    
    CCParticleSystemQuad* eff2 = CCParticleSystemQuad::create("ccbresources/12monthdate/battle/battle_start2.plist");
    eff2->setPosition(ccp(0, standSize.height * 0.5));
    addChild(eff2, 1);
    
    this->setOpacity(0);
    this->runAction(CCSequence::create(CCDelayTime::create(eff2->getDuration() - 0.7),
                                       CCSpawn::create(CCFadeIn::create(0.7),
                                                       CCSequence::create(CCDelayTime::create(0.3),
                                                                          CCCallFunc::create(this, callfunc_selector(FightPetSprite::showRunIn3)),
                                                                          NULL),
                                                       NULL),
                                       NULL));
    
}
void FightPetSprite::showRunIn3()
{
    CCParticleSystemQuad* eff3 = CCParticleSystemQuad::create("ccbresources/12monthdate/battle/battle_start3.plist");
    eff3->setPosition(ccp(0, standSize.height * 0.5));
    addChild(eff3, 3);
}

void FightPetSprite::showLeaderEff()
{
    CCNode* node = CcbManager::sharedManager()->LoadCcbBattleLeaderPlus(this);
    node->setPosition(ccp(0, 0) );
    addChild(node, 4);
    
    CCParticleSystemQuad* eff = CCParticleSystemQuad::create("ccbresources/12monthdate/battle/battle_plus1.plist");
    eff->setPosition(ccp(0, -3));
    addChild(eff, 3);
}

void FightPetSprite::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 15, false);
}
bool FightPetSprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint p = convertToNodeSpace(pTouch->getLocation());
    CCRect rect;
    rect.origin = ccp(-standSize.width*0.5, 0);
    rect.size = standSize;
    if (m_isStand && rect.containsPoint(p)) {
        showHpBar();
    }
    
    return true;
    
}
void FightPetSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void FightPetSprite::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void FightPetSprite::showHpBar()
{
    if (isHpBarShow || (getIsDead() && getCurHP() == 0)) {
        return;
    }
    
    if (hpBar) {
        isHpBarShow = true;
        hpBar->setVisible(true);
    }
}

void FightPetSprite::hideHpBar()
{
    if (isHpBarShow && hpBar) {
        isHpBarShow = false;
        hpBar->setVisible(false);
    }
}
bool FightPetSprite::init(uint16 wBattleIndex, PetBattleControlDelegate *delegate)
{
    if (!CCLayer::init()) {
        return false;
    }
    
    setTouchEnabled(true);
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(wBattleIndex);
    
    if (!pet) {
        return false;
    }
    
    setPetIndex(pet->getPetInfo().wPetIndexId);
    setBattleIndex(wBattleIndex);
    
    setPetNature(pet->getPetInfo().petNature);
    setMaxHp(pet->getPetInfo().wHP);
    setCurHP(pet->getCurHP());
    
    if (m_CurHP == 0) {
        CCMessageBox(CCString::createWithFormat("pet init Hp~~~~~0 ~~fightId: %d,  petId: %d, CurHp %d",wBattleIndex, pet->getPetInfo().wPetIndexId, pet->getCurHP())->getCString(), "Error");
    }
    
    setDeadValue(pet->getPetInfo().wHP);
    m_mapBuff.clear();
    m_delegate = delegate;
	setDeadTime(DEADTIME);
    
    //根据petIndex生产一个flcc}
    mc = SequencePet::create(m_PetIndex);
    
    mc->setFPS(seq_fps);
    
    addChild(mc);
    
    //    mc->runAction( SequenceAction::create(mc, SEQ_ACT_ATTACK));
    //    mc->stopAllActions();
    
    float deTime = (rand() % 30) * 0.01;
    
    mc->runAction(
                  CCSequence::create(
                                     CCDelayTime::create(deTime),
                                     CCCallFunc::create(this, callfunc_selector(FightPetSprite::runStand)),
                                     NULL
                                     )
                  );
    CCSize mcSize = mc->getContentSize();
    this->setContentSize(mcSize);
    
    
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_PetIndex);
    
    if (!petCfg) {
        // create a new role, use config here first.
        CCAssert(true, "config file load error. try to add config/ suffix :-)");
    }
    
    std::string keyFrame = petCfg->strKeyFrames;
    std::vector<int> arrKeyFrame;
    ResourceStringConverter::StrSplit(keyFrame, "_", arrKeyFrame);
    
    for (int i = 0; i < arrKeyFrame.size(); i++) {
        if (arrKeyFrame[i]) {
            m_mapKeyFrame[arrKeyFrame[i]] = arrKeyFrame[i];
        }
    }
    
    arrKeyFrame.clear();
    ResourceStringConverter::StrSplit(petCfg->strAltKeyFrames, "_", arrKeyFrame);
    for (int i = 0; i < arrKeyFrame.size(); i++) {
        if (arrKeyFrame[i]) {
            m_mapAltKeyFrame[arrKeyFrame[i]] = arrKeyFrame[i];
        }
    }
    
    std::vector<int> arrStand;
    ResourceStringConverter::StrSplit(petCfg->strStandSize, "_", arrStand);
    
    standPos.x = arrStand[0] * 0.5;
    standPos.y = arrStand[1]* 0.5;
    standSize.width = arrStand[2]* 0.5;
    standSize.height = arrStand[3]* 0.5;
    
    arrStand.clear();
    ResourceStringConverter::StrSplit(petCfg->strAtkSize, "_", arrStand);
    
    atkPos.x = arrStand[0]* 0.5;
    atkPos.y = arrStand[1]* 0.5;
    atkSize.width = arrStand[2]* 0.5;
    atkSize.height = arrStand[3]* 0.5;
    
    mc->setPosition(ccp(getWidth(mc) * 0.5 - standPos.x - standSize.width * 0.5, -standPos.y));
    mc->setAnchorPoint(ccp(0.5, 0));
    
    //普通攻击combo off}
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* norCfg = GET_CONFIG_STC(UltimateSkillConfig,  pet->getPetInfo().wNormalAttId);
    int len = 0;
    if (norCfg) {
        ComboOffConfig::STC_COMBO_OFF_CONFIG* offCfg = GET_CONFIG_STC(ComboOffConfig, norCfg->wComboid);
        if (offCfg) {
            GET_ARRAY_LEN(offCfg->arrComboOffX, len);
            for (int i = 0; i < len; i++) {
                CCPoint pos = CCPointZero;
                pos.x = offCfg->arrComboOffX[i];
                pos.y = offCfg->arrComboOffY[i];
                arrComboOffNorm.push_back(pos);
            }
        }
    }
    //技能攻击combo off}
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG*ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->getPetInfo().wSkillId);
    if (ultCfg) {
        ComboIdConfig::STC_COMBOID_CONFIG* comCfg = GET_CONFIG_STC(ComboIdConfig, ultCfg->wComboid);
        if (comCfg) {
            ComboOffConfig::STC_COMBO_OFF_CONFIG* offCfg = GET_CONFIG_STC(ComboOffConfig, comCfg->wComboOffId);
            if (offCfg) {
                GET_ARRAY_LEN(offCfg->arrComboOffX, len);
                for (int i = 0; i < len; i++) {
                    CCPoint pos = CCPointZero;
                    pos.x = offCfg->arrComboOffX[i];
                    pos.y = offCfg->arrComboOffY[i];
                    arrComboOffSkill.push_back(pos);
                }
            }
        }
    }
    
    m_hpBarShowTime = 0;
    schedule(schedule_selector(FightPetSprite::updateForHpBar));
    waitForDoBattle = -1;
    schedule(schedule_selector(FightPetSprite::updateForDoBattle));
    schedule(schedule_selector(FightPetSprite::update), 1.0 / mc->getFPS());
    
    return true;
}

void FightPetSprite::runStand()
{
    mc->runAction(CCRepeatForever::create(SequenceAction::create(mc, SEQ_ACT_STAND)));
}

void FightPetSprite::chgSelected()
{
    m_isSelected = !m_isSelected;
}

void FightPetSprite::showBuff()
{
    if (m_CurHP <= 0) {
        return;
    }
    for (int i = 0; i < arrImgBuff.size(); i++) {
        if (arrImgBuff[i]) {
            arrImgBuff[i]->setVisible(true);
        }
    }
    
    //buff飘字
    FightPet* pet = FightAI::Get()->getFightPetByBIndex(m_BattleIndex);
    if (!pet) {
        return;
    }
    std::map<uint8, std::vector<STC_BUFF> >mapBuff = pet->getMapBuff();
    std::map<uint8, std::vector<STC_BUFF> >::iterator it = mapBuff.begin();
    int cnt = 0;
    CCPoint pos = getMyPos() + ccp(0, standSize.height * 0.7);
    for (; it != mapBuff.end(); it++) {
        std::vector<STC_BUFF> arrBuff = it->second;
        
        for (int i = 0; i < arrBuff.size(); i++) {
            STC_BUFF buff = arrBuff[i];
            if (!buff.wBuffId || !buff.isNew) {
                continue;
            }
            SkillBuffConfig::STC_SKILL_BUFF_CONFIG *cfg = GET_CONFIG_STC(SkillBuffConfig, arrBuff[i].wBuffId);
            if (!cfg) {
                continue;
            }
            if (cfg->buffPara[2]) { //可叠加buff不显示}
                continue;
            }
            
            FlyTextLayer::showBuffText(cfg->strFlyText.c_str(), cfg->wBuffEff != E_BUFF_EFFECT_DEBUFF, pos, cnt*0.3, 0.5, this->getParent());
            cnt++;
        }
        mapBuff[it->first] = arrBuff;
    }
    pet->newToOldBuff();
}

void FightPetSprite::reflashBuff()
{
    for (int i = 0; i < arrImgBuff.size(); i++) {
        if (arrImgBuff[i]) {
            arrImgBuff[i]->removeFromParentAndCleanup(true);
        }
    }
    arrImgBuff.clear();
    
    if (m_CurHP <= 0) {
        return;
    }
    
    std::map<uint8, std::vector<STC_BUFF> >::iterator it = m_mapBuff.begin();
    
    float w = 0;
    float w1= 0;
    for (; it != m_mapBuff.end(); it++) {
        std::vector<STC_BUFF> arrBuff = it->second;
        
        for (int i = 0; i < arrBuff.size(); i++) {
            if (!arrBuff[i].wBuffId) {
                continue;
            }
            
            SkillBuffConfig::STC_SKILL_BUFF_CONFIG *cfg = GET_CONFIG_STC(SkillBuffConfig, arrBuff[i].wBuffId);
            if (!cfg) {
                continue;
            }
            if (cfg->buffPara[2]) { //可叠加buff不显示}
                continue;
            }
            CCSprite *img = CCSprite::create(CCString::createWithFormat(GET_PIC(PIC_battle_buff_icon), cfg->wIcon)->getCString());
            if (!img) {
                continue;
            }
            addChild(img);
            w1 = getWidth(img);
            w += w1;
            img->setVisible(false);
            arrImgBuff.push_back(img);
        }
    }
    float posX = -w * 0.5 + w1 * 0.5;
    for (int i = 0; i < arrImgBuff.size(); i++) {
        if (!arrImgBuff[i]) {
            continue;
        }
        
        arrImgBuff[i]->setPosition(ccp(posX, standSize.height));
        arrImgBuff[i]->setAnchorPoint(ccp(0.5, 0));
        if (m_BattleIndex <= PetCnt) {
            arrImgBuff[i]->setRotationY(180);
        }
        posX += getWidth(arrImgBuff[i]);
    }
    
    m_delegate->setPetCtrlSpecial(m_BattleIndex);
    
    if (m_isStand) {
        showBuff();
    }
}
void FightPetSprite::hideBuff()
{
    for (int i = 0; i < arrImgBuff.size(); i++) {
        if (arrImgBuff[i]) {
            arrImgBuff[i]->setVisible(false);
        }
    }
}

void FightPetSprite::startBattle(CCPoint pos, STC_BATTLE_DATA data)
{
    m_isStand = false;
    hideBuff();
    m_CurBattleData = *new STC_CUR_ATT_DATA();
    m_CurBattleData.bData = data;
    //显示被动技能}
    std::map<uint16, STC_ATTACK_DATA>::iterator it = data.arrAttData.begin();
    for (; it != data.arrAttData.end(); it++) {
        STC_ATTACK_DATA attData = it->second;
        if (attData.mapPassiveSkill.find(E_PASSIVE_SHOW_TIME_BIGEN) != attData.mapPassiveSkill.end()) {
            //            FightPetSprite* petS = m_mapPet[it->first];
            //            if (petS) {
            showPassive(attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_BIGEN]);
            //            }
        }
    }
    float time = 0.1;
    if (arrNowShowPassTextSprite.size() > 0) {
        time = 0.5;
    }

    PetConfig::STC_PET_CONFIG *pet = GET_CONFIG_STC(PetConfig, m_PetIndex);
    //0：近战，1：远程}
    if (pet->byAttackType == E_ATTACK_TYPE_MAGIC ||
        m_CurBattleData.bData.eEffObj == E_EFFECT_OBJECT_MY) {
//        this->runAction(CCSequence::create(CCDelayTime::create(time + 0.2),
//                                           CCCallFunc::create(this, callfunc_selector(FightPetSprite::doBattle)),
//                                           NULL));
        
    }
    else
    {
        this->setZOrder(480-pos.y + 10);
        mc->pauseSchedulerAndActions();
        mc->resumeSchedulerAndActions();
        this->runAction(CCSequence::create(CCDelayTime::create(time),
                                           CCMoveTo::create((float)startFrames / 60.0, pos),
                                           NULL));
        
        dustEff->runAction(CCSequence::create(CCDelayTime::create(time),
                                              CCShow::create(),
                                              NULL));
    }
    waitForDoBattle = time * 60 + startFrames;
    
    //组个显示用包（加上combo）}
    ComboIdConfig::STC_COMBOID_CONFIG *combo;
    if (!pet) {
        return;
    }
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *ult = GET_CONFIG_STC(UltimateSkillConfig, data.wSkillId);
    if (!ult || ult->byType == 2) {
        combo = GET_CONFIG_STC(ComboIdConfig, pet->wComboId);
    }
    else
    {
        combo = GET_CONFIG_STC(ComboIdConfig, ult->wComboid);
    }
    
    if (combo) {
        int len = 0;
        GET_ARRAY_LEN(combo->dwComboTime, len);
        for (int i = 0; i < len; i++) {
            if (combo->dwComboTime[i] == 0) {
                break;
            }
            m_CurBattleData.arrComboFrame[combo->dwComboTime[i]] = combo->dwComboPer[i];
            allFrame = combo->dwComboTime[i];
        }
    }
    
    allFrame = MAX(pet->wAtkFrame, allFrame);
    //    arrCurAttData.clear();
}

void FightPetSprite::doBattle()
{
    if (!mc) {
        return;
    }
    
    mc->stopAllActions();
    mc->runAction(SequenceAction::create(mc, SEQ_ACT_STAND));
    mc->stopAllActions();
    
    float time = 0.1;//(rand() % 6 + 1) * 0.1;
    mc->runAction(CCSequence::create(
                                     CCDelayTime::create(time),
                                     CCCallFunc::create(this, callfunc_selector(FightPetSprite::beforeAttact)),
                                     NULL));
    //    beforeAttact();
}
void FightPetSprite::beforeAttact()
{
    if (dustEff) {
        dustEff->setVisible(false);
    }
    //进阶烟雾
    if (getChildByTag(112)) {
        getChildByTag(112)->setVisible(false);
    }
    isParitleStop = false;
    arrCurParticle.clear();
    itemCnt = 0;
    m_isFighting = true;
    mc->runFPSAction(SequenceFPSAction::create(mc, SEQ_ACT_ATTACK), this);
}

void FightPetSprite::showPassiveInBattle()
{
    //显示被动技能}
    std::map<uint16, STC_ATTACK_DATA>::iterator it = m_CurBattleData.bData.arrAttData.begin();
    for (; it != m_CurBattleData.bData.arrAttData.end(); it++) {
        STC_ATTACK_DATA attData = it->second;
        if (attData.mapPassiveSkill.find(E_PASSIVE_SHOW_TIME_BATTLE) != attData.mapPassiveSkill.end()) {
            showPassive(attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_BATTLE]);
        }
    }
}

//显示所有被动技能产生的eff与buff}
void FightPetSprite::showPassiveEff()
{
    std::set<uint16> setFight;
    setFight.clear();
    std::map<uint16, STC_ATTACK_DATA>::iterator itD = m_CurBattleData.bData.arrAttData.begin();
    for (; itD != m_CurBattleData.bData.arrAttData.end(); itD++) {
        STC_ATTACK_DATA attData = itD->second;
        
        std::map<uint8, std::vector<STC_TRIGGERED_PSKILL> >::iterator it = attData.mapPassiveSkill.begin();
        for (; it != attData.mapPassiveSkill.end(); it++) {
            if (it->first == E_PASSIVE_SHOW_TIME_DEAD) {
                continue;
            }
            std::vector<STC_TRIGGERED_PSKILL> arrPSkill = it->second;
            
            for (int ps = 0; ps < arrPSkill.size(); ps++) {
                STC_TRIGGERED_PSKILL pskill = arrPSkill[ps];
                
                for (int i = 0 ; i < pskill.arrMyEffsAndBuff.size(); i++) {
                    STC_PET_EFF_BY_PSKILL effbuff = pskill.arrMyEffsAndBuff[i];
                    FightPet *pet = FightAI::Get()->getFightPetByBIndex(effbuff.fightId);
                    if (!pet) {
                        continue;
                    }
                    FightPetSprite* petS = m_delegate->getFightPetSprite(effbuff.fightId);
                    if (!petS) {
                        continue;
                    }
                    petS->setMapBuff(effbuff.arrBuff);
                    petS->reflashBuff();
                    petS->setArrEff(effbuff.arrEff);
                    petS->showEff();
                }
                
                for (int i = 0 ; i < pskill.arrEnemyEffsAndBuff.size(); i++) {
                    STC_PET_EFF_BY_PSKILL effbuff = pskill.arrEnemyEffsAndBuff[i];
                    FightPet *pet = FightAI::Get()->getFightPetByBIndex(effbuff.fightId);
                    if (!pet) {
                        continue;
                    }
                    FightPetSprite* petS = m_delegate->getFightPetSprite(effbuff.fightId);
                    if (!petS) {
                        continue;
                    }
                    petS->setMapBuff(effbuff.arrBuff);
                    petS->reflashBuff();
                    petS->setArrEff(effbuff.arrEff);
                    //                    if (setFight.find(effbuff.fightId) == setFight.end()) {
                    //                        petS->setMapBuff(pet->getMapBuff());
                    //                        petS->reflashBuff();
                    //                        setFight.insert(effbuff.fightId);
                    //                    }
                    petS->showEff();
                }
                
            }
        }
    }
}
void FightPetSprite::afterAttact()
{
    //    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_PetIndex);
    //    if (petCfg->byAttackType != E_ATTACK_TYPE_MAGIC) {
    //        unschedule(schedule_selector(FightPetSprite::update));
    //        afterAtk();
    //    }
}
void FightPetSprite::afterAtk()
{
    isParitleStop = true;
    //    mc->resumeFPSAction();
    this->setZOrder(480 - m_MyPos.y);
    
    //清除特效}
    for (int i = 0; i < arrCurParticle.size(); i++) {
        if (arrCurParticle[i]) {
            arrCurParticle[i]->stopSystem();
            arrCurParticle[i]->removeFromParentAndCleanup(true);
            arrCurParticle[i] = NULL;
        }
    }
    arrCurParticle.clear();
    
    //显示主动技能的eff，刷新Buff}
    std::map<uint16, STC_ATTACK_DATA>::iterator it = m_CurBattleData.bData.arrAttData.begin();
    for (; it != m_CurBattleData.bData.arrAttData.end(); it++) {
        FightPetSprite *enemy = NULL;
        enemy =  m_delegate->getFightPetSprite(it->second.wEnemyIndex);
        if (!enemy) {
            continue;
        }
        FightPet *pet = FightAI::Get()->getFightPetByBIndex(it->second.wEnemyIndex);
        if (!pet || pet->getCurHP() <= 0) {
            continue;
        }
        //刷新怒气值}
        if (m_delegate) {
            if ((dynamic_cast<CcbArenaFightLayer*>(m_delegate) || dynamic_cast<CcbWorldBossFightLayer*>(m_delegate))
                && it->second.isHit) { //未命中时不变}
                m_delegate->setPower(it->first, it->second.curPower);
            }
            else{
                m_delegate->setPower(it->first, pet->getCurPower());
            }
        }
        
        if (m_CurBattleData.bData.eEffObj != E_EFFECT_OBJECT_MY) {
            setMapBuff(it->second.arrMyBuff);
            setArrEff(it->second.arrMyEff);
        }
        
        enemy->setMapBuff(it->second.arrEnemyBuff);
        enemy->setArrEff(it->second.arrEnemyEff);
        reflashBuff();
        showEff();
        enemy->reflashBuff();
        enemy->showEff();
    }
    
    //显示攻击敌方的同时，给自己带来的Eff
    std::map<uint16, std::vector<STC_EFFECT> > mapEffToMy = m_CurBattleData.bData.mapEffToMy;
    std::map<uint16, std::vector<STC_EFFECT> >::iterator itE = mapEffToMy.begin();
    for (; itE != mapEffToMy.end(); itE++) {
        FightPetSprite *enemy = m_delegate->getFightPetSprite(itE->first);
        if (!enemy || enemy->getCurHP() <= 0) {
            continue;
        }
        enemy->setArrEff(itE->second);
        enemy->showEff();
    }
    
    
    showPassiveEff();
    
    //显示被动技能(杀死触发) （这段处理的本意 是将死亡触发的过滤出，在死亡宠物正真死亡(即开始播死亡特效时，而不是被攻击结束)时表现死亡技能）}
    //但考虑到如果需要这样表现的话，Eff与Buff要特殊处理，这样做是否值得呢？所以暂时取消这段的特殊处理}
    it = m_CurBattleData.bData.arrAttData.begin();
    for (; it != m_CurBattleData.bData.arrAttData.end(); it++) {
        STC_ATTACK_DATA attData = it->second;
        if (attData.mapPassiveSkill.find(E_PASSIVE_SHOW_TIME_DEAD) != attData.mapPassiveSkill.end()) {
            FightPetSprite* petS = m_delegate->getFightPetSprite(it->first);
            if (petS) {
                std::vector<STC_TRIGGERED_PSKILL> arrTPSkill = attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_DEAD];
                showPassive(arrTPSkill, true);
            }
        }
    }
    
    //如果是技能攻击，刷新所有人的buff}
    if (m_CurBattleData.bData.wSkillId) {
        for (int i = 1; i <= PetCnt; i++) {
            FightPet* pet = FightAI::Get()->getFightPetByBIndex(i);
            if (pet && pet->getCurHP() > 0) {
                FightPetSprite* petSp = m_delegate->getFightPetSprite(i);
                if (petSp) {
                    petSp->setMapBuff(pet->getMapBuff());
                    petSp->reflashBuff();
                }
            }
            
            pet = FightAI::Get()->getFightPetByBIndex(i + 100);
            if (pet && pet->getCurHP() > 0) {
                FightPetSprite* petSp = m_delegate->getFightPetSprite(i + 100);
                if (petSp) {
                    petSp->setMapBuff(pet->getMapBuff());
                    petSp->reflashBuff();
                }
            }
        }
    }
    
    
    //人物返回}
    PetConfig::STC_PET_CONFIG *pet = GET_CONFIG_STC(PetConfig, m_PetIndex);
    CCActionInterval *act = NULL;
    mc->stopAllActions();
    mc->runAction( CCRepeatForever::create(SequenceAction::create(mc, SEQ_ACT_STAND)));
    
    
    float time = 0.3;
    
    if (pet->byAttackType == E_ATTACK_TYPE_MELEE &&
        m_CurBattleData.bData.eEffObj != E_EFFECT_OBJECT_MY) {
        act = CCJumpTo::create(startFrames / 60.0, m_MyPos, 10, 1);// CCMoveTo::create(startFrames / 60.0, m_MyPos);
    }
    else
    {
        act = CCDelayTime::create(0.1);
    }
    this->runAction(CCSequence::create(CCDelayTime::create(time),
                                       act,
                                       CCCallFunc::create(this, callfunc_selector(FightPetSprite::endBattle)),
                                       NULL));
    
    
}

void FightPetSprite::endBattle()
{
    //刷新怒气值}
    if (m_delegate) {
        m_delegate->setPower(m_BattleIndex, m_CurBattleData.bData.curPower);
    }
    
    mc->stopAllActions();
    mc->runAction( CCRepeatForever::create(SequenceAction::create(mc, SEQ_ACT_STAND)));
    //进阶烟雾
    if (getChildByTag(112)) {
        getChildByTag(112)->setVisible(true);
    }
    m_isStand = true;
    showBuff();
    m_delegate->endBattle(m_BattleIndex, m_CurBattleData.bData.wSkillId);
}

void FightPetSprite::update(float time)
{
    if (!m_isFighting) {
        return;
    }
    //判断combo帧}
    if (m_CurBattleData.arrComboFrame.size() == 0) {
        //        unschedule(schedule_selector(FightPetSprite::update));
        m_isFighting = false;
    }
    
    if (stopFrame > 0) {
        stopFrame--;
        return;
    }
    
    //超过combo}
    if (m_CurBattleData.wFrame > allFrame) {
        m_isFighting = false;
        afterAtk();
        return;
    }
    
    bool isRealSkill = false;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig,  m_CurBattleData.bData.wSkillId);
    
    if (ultCfg && ultCfg->byType == 1) {
        isRealSkill = true;
    }
    if ((isRealSkill && m_mapAltKeyFrame.find(m_CurBattleData.wFrame) != m_mapAltKeyFrame.end())
        || (!isRealSkill && m_mapKeyFrame.find(m_CurBattleData.wFrame) != m_mapKeyFrame.end())) {
        PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_PetIndex);
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
    
    //    CCLog("  battle id :  %d  updata frame ~~~~~~~%d , all frame : %d",m_BattleIndex, m_CurBattleData.wFrame, allFrame);
    if (m_CurBattleData.arrComboFrame.find(m_CurBattleData.wFrame) == m_CurBattleData.arrComboFrame.end()) {
        m_CurBattleData.wFrame++;
        
        return;
    }
    
    if (m_CurBattleData.arrComboFrame.find(m_CurBattleData.wFrame) == m_CurBattleData.arrComboFrame.begin()) {
        //伤害第一帧}
        showPassiveInBattle();
        showArmEff();
    }
    m_CurBattleData.wCounter++;
    //    CCLog("    #######attack frame ~~~~~~~%d : ", m_CurBattleData.wFrame);
    //    bool isEnd = false;
    std::map<uint16, STC_ATTACK_DATA>::iterator it = m_CurBattleData.bData.arrAttData.begin();
    for (; it != m_CurBattleData.bData.arrAttData.end(); it++) {
        
        STC_ATTACK_DATA attData = it->second;
        FightPetSprite *enemy = NULL;
        
        
        enemy = m_delegate->getFightPetSprite(attData.wEnemyIndex);
        if (!enemy) {
            continue;
        }
        
        //闪避}
        if (m_CurBattleData.arrComboFrame.find(m_CurBattleData.wFrame) == m_CurBattleData.arrComboFrame.begin()
            && !attData.isHit) {
            enemy->onDodge();
            //            CCLog("%d gan %d, dam : %d", m_BattleIndex, attData.wEnemyIndex, attData.dwAllDamage);
            continue;
        }
        //如果没有伤害，不显示}
        if (attData.dwAllDamage == 0) {
            continue;
        }
        std::map<uint16, STC_FRAME_DAMAGE> arrDamage = attData.arrDamage;
        if (arrDamage.size() == 0) {
            continue;
        }
        std::map<uint16, STC_FRAME_DAMAGE>::iterator itD = arrDamage.find(m_CurBattleData.wFrame);
        
        //走到这里，说明已经走到了Combo段，主攻者动作停帧，}
        PetConfig::STC_PET_CONFIG *pet = GET_CONFIG_STC(PetConfig, m_PetIndex);
        if (pet->byAttackType == E_ATTACK_TYPE_MELEE) {
            
        }
        //掉血}
        int loseHp = enemy->loseHP(itD->second.dwDamege);
        m_delegate->loseHp(attData.wEnemyIndex, loseHp);
        enemy->beHit();
        if (isRealSkill) {
            if (m_delegate) {
                m_delegate->doShake();
            }
        }
        //显示伤害}
        CCString *word = CCString::createWithFormat("%d", itD->second.dwDamege);
        CCPoint pos = enemy->getMyPos();// + ccp(0, 210);
        CCNode * node = this->getParent();//->getParent();
        
        
        CCPoint off = getPointOffByType(m_CurBattleData.bData.wSkillId, m_CurBattleData.wCounter);
        
        CCPoint textPos = ccp(pos.x + off.x, pos.y + off.y + enemy->getStandSize().height * 0.5);
        
        ShowPetBattleWord::showWord(word->getCString(), attData.regulateState, textPos, node);
        
        //显示Spark}
        
        
        //显示暴击}
        if (itD == arrDamage.begin()) {
            CCLog("%d gan %d, dam : %d", m_BattleIndex, attData.wEnemyIndex, attData.dwAllDamage);
            if (attData.isCrit) {
                ShowPetBattleWord::showTextWord(E_WORD_TYPE_CRIT_TEXT, ccp(pos.x , pos.y + enemy->getStandSize().height), node);
                if (m_delegate) {
                    m_delegate->doShake();
                }
            }
        }
        
        
        //掉物品}
        int n = attData.arrItems.size() / attData.arrDamage.size();
        if (++itD == arrDamage.end())
        {
            n = n + attData.arrItems.size() - n*(attData.arrDamage.size());
            isParitleStop = true;
        }
        for (int i = 0; i < n; i++) {
            m_delegate->dropItem(enemy->getBattleIndex(), attData.arrItems[i + attData.dwDropCnt]);
        }
        attData.dwDropCnt += n;
        it->second = attData;
        
    }
    itemCnt = m_CurBattleData.wFrame;
    
    
    m_CurBattleData.wFrame++;
}


void FightPetSprite::buffActive(std::vector<STC_BUFF_VALUE> arrBuffValue)
{
    for (int i = 0; i < arrBuffValue.size(); i++) {
        STC_BUFF_VALUE buff = arrBuffValue[i];
        CCString *str = CCString::create("");
        if (buff.byBuffType == E_BUFF_RECOVE_TYPE_ADD) {
            str->initWithFormat("%d", buff.dwValue);
            
            ShowPetBattleWord::showWord(str->getCString(), E_WORD_TYPE_HP, ccp(m_MyPos.x, m_MyPos.y + standSize.height * 0.6), getParent());
            
            m_delegate->addHp(m_BattleIndex, buff.dwValue);
        }
        else if(buff.byBuffType == E_BUFF_RECOVE_TYPE_SUB) {
            str->initWithFormat("%d", buff.dwValue);
            ShowPetBattleWord::showWord(str->getCString(), E_WORD_TYPE_NORMAL, ccp(m_MyPos.x, m_MyPos.y + standSize.height * 0.6), getParent());
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			int value = max(-buff.dwValue, buff.dwValue);
#else
			int value = std::max(-buff.dwValue, buff.dwValue);
#endif
			
            value = loseHP(value);
            m_delegate->loseHp(m_BattleIndex, value);
        }
    }
}

void FightPetSprite::showEff()
{
    for (int i = 0; i < m_arrEff.size(); i ++) {
        SkillEffectConfig::STC_SKILL_EFFECT_CONFIG *cfg = GET_CONFIG_STC(SkillEffectConfig, m_arrEff[i].wEffId);
        if (!cfg) {
            continue;
        }
        CCString *str = CCString::createWithFormat("%d", m_arrEff[i].dwValue);
        switch (cfg->byType) {
            case E_EFFECT_RECOVER_HP_CUR:   //回血（当前血量）}
                
            case E_EFFECT_RECOVER_HP_MAX:   //回血（最大血量）}
                
            case E_EFFECT_RECOVER_HP:     //回复数值}
                m_delegate->addHp(m_BattleIndex, m_arrEff[i].dwValue);
                
                ShowPetBattleWord::showWord(str->getCString(), E_WORD_TYPE_HP, m_MyPos + ccp(0, standSize.height * 0.6), getParent());
                break;
                
            case E_EFFECT_SUCK_BLOOD:     //吸血}
                
                m_delegate->addHp(m_BattleIndex, m_arrEff[i].dwValue);
                
                ShowPetBattleWord::showWord(str->getCString(), E_WORD_TYPE_HP, getPosition() + ccp(0, standSize.height * 0.6), getParent());
                break;
                
            case E_EFFECT_INITIAL_ADD:  //主技能CD+    //组包时已经加在了FightPet上，攻击结束刷新power时就刷上了，如果需要特殊表示的话再加}
                break;
            case E_EFFECT_INITIAL_DEC:  //主技能CD-}
                break;
            default:
                break;
        }
    }
    m_arrEff.clear();
}

void FightPetSprite::updateForHpBar(float time)
{
    m_hpBarShowTime--;
    if (m_hpBarShowTime <= 0) {
        m_hpBarShowTime = 0;
        hideHpBar();
    }
}
void FightPetSprite::beHit()
{
	this->setDeadTime(DEADTIME);
    
    //受到攻击时显示血条}
    if (hpBar) {
        hpBar->setHp(m_CurHP);
    }
    
    m_hpBarShowTime = 30;
    showHpBar();
    
    //受攻击时，刷新气条}
    
    //显示受击动作}
    mc->runAction(CCSequence::create(CCMoveBy::create(0.05, ccp(10, 0)),
                                     CCMoveBy::create(0.05, ccp(-10, 0)),
                                     CCMoveBy::create(0.05, ccp(10, 0)),
                                     CCMoveBy::create(0.05, ccp(-10, 0)),
                                     NULL));
    
}
//闪避}
void FightPetSprite::onDodge()
{
    
    CCNode* node = getParent();
    CCPoint pos = m_MyPos;
    
    CCPoint textPos = pos + ccp(0, getStandSize().height * 0.8);
    ShowPetBattleWord::showTextWord(E_WORD_TYPE_MISS_TEXT, textPos, node);
    
    //显示闪避动作}
    int x = -1;
    if (m_BattleIndex > PetCnt) {
        x = 1;
    }
    this->runAction(CCSequence::create(CCMoveBy::create(0.05, ccp(x*getStandSize().width*0.5 * 0.5, 0)),
                                       CCDelayTime::create(1.0),
                                       CCMoveBy::create(0.05, ccp(-x*getStandSize().width*0.5 * 0.5, 0)),
                                       NULL));
}
void FightPetSprite::setIsDead(bool isDead)
{
    if (m_isDead) {
        return;
    }
    if (m_isCanDead && isDead) {
        m_isDead = true;
        if (hpBar) {
            hpBar->setVisible(false);
            hpBar->removeFromParentAndCleanup(true);
            hpBar = NULL;
        }
        
        if(mc)
        {
            hideBuff();
            mc->stopAllActions();
            this->runAction(CCSequence::create(
                                               CCCallFunc::create(this, callfunc_selector(FightPetSprite::showDeadPassive)),
                                               CCDelayTime::create(0.9),
                                               CCFadeOut::create(0.6),
                                               CCCallFunc::create(this, callfunc_selector(FightPetSprite::dropBox)),
                                               NULL));
        }
    }
    else{m_isDead = false;}
};
void FightPetSprite::showDeadPassive()
{
    unschedule(schedule_selector(FightPetSprite::updateForHpBar));
    unschedule(schedule_selector(FightPetSprite::updateForDoBattle));
    unschedule(schedule_selector(FightPetSprite::update));
    hideAltEff();
    //死亡特效}
    m_delegate->showDeadEff(m_BattleIndex);
    
    showPassive(arrDeadTPSkill);
    
}

void FightPetSprite::showAltEff(CCObject* object)
{
    FightPet* pet = FightAI::Get()->getFightPetByBIndex(m_BattleIndex);
    if (altEff && pet->getCurPower() >= pet->getPetInfo().wAllPower) {
        altEff->setVisible(true);
    }
}

void FightPetSprite::hideAltEff()
{
    if (altEff) {
        altEff->setVisible(false);
    }
}

void FightPetSprite::showLianXie(uint16 add)
{
    
    if (!lblLXAdd) {
        lblLXAdd = dynamic_cast<CcbTextLianXieLayer*>(CcbManager::sharedManager()->LoadCcbTextLianXieLayer());
        lblLXAdd->setPosition(ccp(0, standSize.height));
        lblLXAdd->setAnchorPoint(ccp(0.5, 0));
        lblLXAdd->ignoreAnchorPointForPosition(false);
        if (m_BattleIndex <= PetCnt) {
            lblLXAdd->setRotationY(180);
        }
        addChild(lblLXAdd, 100);
    }
    lblLXAdd->setAdd(add);// m_pLabelBMFontAdd->setString(str->getCString());
    lblLXAdd->show();
}

void FightPetSprite::dropBox()
{
    m_isHide = true;
    //如果可以出蛋，在消失后掉出}
    m_delegate->dropBox(m_BattleIndex);
}
int FightPetSprite::addHP(int wValue)
{
    int ret = 0;
    if (m_CurHP <= 0) {
        return ret;
    }
    ret = MIN(m_MaxHP - m_CurHP, wValue);
    m_CurHP += wValue;
    if (m_CurHP > m_MaxHP) {
        m_CurHP = m_MaxHP;
    }
    //    CCLog("~~~~FightPetSprite~~Add~~ Id : %d, Add:%d, curHp:%d", m_BattleIndex, wValue, m_CurHP);
    return ret;
}

int FightPetSprite::loseHP(int wValue)
{
    int ret = wValue;
    if (m_isCanDead && m_CurHP < wValue) {
        ret = m_CurHP;
    }
    
    m_CurHP -= ret;
    if (m_CurHP < 0) {
        m_CurHP = 0;
    }
    
    //    CCLog("~~~~FightPetSprite~~Lose~~ Id : %d, Lose:%d, curHp:%d", m_BattleIndex, wValue, m_CurHP);
    return ret;
}
//显示序列帧特效}
void FightPetSprite::showArmEff()
{
    uint32 effId = 0;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *cfg = GET_CONFIG_STC(UltimateSkillConfig, m_CurBattleData.bData.wSkillId);
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
    
    /*
     E_ALT_EFF_SINGLE = 0,   //单体
     E_ALT_EFF_HALF = 1,     //半屏
     E_ALT_EFF_FULL = 2,     //全屏
     E_ALT_EFF_ROW = 3,      //横排
     E_ALT_EFF_RANK = 4,     //竖排
     */
    CCPoint pos = CCPointZero;
    uint16 enemyId = m_CurBattleData.bData.arrAttData.begin()->first;
    FightPetSprite* enemy = m_delegate->getFightPetSprite(enemyId);

    if (!enemy) {
        return;
    }
    switch (effGroup->byAltEffType) {
        case E_ALT_EFF_SINGLE:
        {
            //单体特效在每个攻击对象身上都显示一次}
            std::map<uint16, STC_ATTACK_DATA>::iterator it = m_CurBattleData.bData.arrAttData.begin();
            for (; it != m_CurBattleData.bData.arrAttData.end(); it++) {
                FightPetSprite *enemy = NULL;
                
                enemy = m_delegate->getFightPetSprite(it->first);
                if (!enemy || !it->second.isHit) {
                    continue;
                }
                CCString* str = CCString::createWithFormat(ALT_ARMATURE_PATH, effGroup->strArmEff.c_str(), effGroup->strArmEff.c_str());
                AltEffArmature* arm = AltEffArmature::create(str->getCString(), effGroup->strArmEff.c_str());
                
                if (getParent() && arm) {
                    if (m_BattleIndex <= PetCnt) {
                        arm->setRotationY(180);
                    }
                    arm->setPosition(enemy->getMyPos()+ ccp(0, enemy->getStandSize().height*0.5));
//                    arm->ignoreAnchorPointForPosition(false);
//                    arm->setAnchorPoint(ccp(0.5, 0.5));
                    getParent()->addChild(arm, 695);
                }
            }
            return;
        }
            break;
        case E_ALT_EFF_HALF:
        {
            if (enemyId <= PetCnt) {
                pos = m_delegate->getMyMiddlePos() + ccp(-35, 0);
            }
            else{
                pos = m_delegate->getEnemyMiddlePos() + ccp(35, 0);;
            }
            
        }
            break;
        case E_ALT_EFF_FULL:
        {
            if (enemyId <= PetCnt) {
                pos = m_delegate->getMyMiddlePos() + ccp(-35, 0);
            }
            else{
                pos = m_delegate->getEnemyMiddlePos() + ccp(35, 0);
            }
        }
            break;
        case E_ALT_EFF_ROW:
        {
            if ((enemyId % 2 > 0 && enemyId <= PetCnt) ||
                (enemyId % 2 == 0 && enemyId > PetCnt)) {
                pos = enemy->getMyPos() + ccp(-35, 0);
            }
            else{
                pos = enemy->getMyPos() + ccp(35, 0);
            }
        }
            break;
        case E_ALT_EFF_RANK:
        {
            if (enemyId <= PetCnt) {
                if (enemyId % 2 > 0) {
                    pos = m_delegate->getMyMiddlePos();
                }
                else{
                    pos = m_delegate->getMyMiddlePos() + ccp(-70, 0);
                }
            }
            else{
                if (enemyId % 2 > 0) {
                    pos = m_delegate->getEnemyMiddlePos();
                }
                else{
                    pos = m_delegate->getEnemyMiddlePos() + ccp(70, 0);
                }
            }
        }
            break;
            
        default:
            break;
    }
    
    CCString* str = CCString::createWithFormat(ALT_ARMATURE_PATH, effGroup->strArmEff.c_str(), effGroup->strArmEff.c_str());
    AltEffArmature* arm = AltEffArmature::create(str->getCString(), effGroup->strArmEff.c_str());
    if (getParent() && arm) {
        arm->setPosition(pos);
//        arm->ignoreAnchorPointForPosition(false);
//        arm->setAnchorPoint(ccp(0.5, 0.5));
        if (enemyId > PetCnt) {
            arm->setRotationY(180);
        }
        getParent()->addChild(arm, 698);
    }
    
}

void FightPetSprite::showHitEff()
{
    if (isParitleStop) {
        return;
    }
    //显示特效}
    uint32 effId = 0;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *cfg = GET_CONFIG_STC(UltimateSkillConfig, m_CurBattleData.bData.wSkillId);
    if (cfg) {
        effId = cfg->wShowEffectId;
    }
    else
    {
        PetConfig::STC_PET_CONFIG *cfg = GET_CONFIG_STC(PetConfig, m_PetIndex);
        effId = cfg->wEffectId;
    }
    
    EffectGroupConfig::STC_EFFECT_GROUP_CONFIG *effGroup = GET_CONFIG_STC(EffectGroupConfig, effId);
    if (!effGroup) {
        return;
    }
    
    //全屏特效只显示一次}
    if (effGroup->byAltEffType == E_ALT_EFF_HALF
        ||effGroup->byAltEffType == E_ALT_EFF_FULL) {
        showHitEff(effGroup, NULL);
        return;
    }
    
    //单体特效在每个攻击对象身上都显示一次}
    std::map<uint16, STC_ATTACK_DATA>::iterator it = m_CurBattleData.bData.arrAttData.begin();
    for (; it != m_CurBattleData.bData.arrAttData.end(); it++) {
        FightPetSprite *enemy = NULL;
        
        enemy = m_delegate->getFightPetSprite(it->first);
        if (!enemy || !it->second.isHit) {
            continue;
        }
        showHitEff(effGroup, enemy);
    }
}

void FightPetSprite::showHitEff(EffectGroupConfig::STC_EFFECT_GROUP_CONFIG *effGroup, FightPetSprite *pet)
{
    CCArray *arrAct = CCArray::create();
    float time=0;
    for (int i = 0; i < effGroup->effParts.size(); i++) {
        if (effGroup->effParts[i] == "0" || effGroup->effParts[i] == "") {
            continue;
        }
        CCParticleSystemQuad *particle = CCParticleSystemQuad::create(getEffPath(effGroup->effParts[i]).c_str());
        if (!particle) {
            continue;
        }
        
        particle->setTag(1);
        if (effGroup->byAltEffType == E_ALT_EFF_HALF) //有发射点的全体，需取反}
        {
            CCPoint pos = CCPointZero;
            if (m_BattleIndex <= PetCnt) {
                pos = m_delegate->getEnemyMiddlePos();
                particle->setRotationY(180);
            }
            else
            {
                pos = m_delegate->getMyMiddlePos();
                
            }
            particle->setPosition(ccp(pos.x, pos.y + 20));
        }
        else if (effGroup->byAltEffType == E_ALT_EFF_FULL) //无发射点的全体}
        {
            CCPoint pos = particle->getPosition() + ccp(0, -130);
            particle->setPosition(pos);
        }
        else //单体}
        {
            particle->setTag(2);
            CCPoint pos = pet->getMyPos();// + ccp(0, offY);
            particle->setPosition(ccp(pos.x, pos.y+pet->getStandSize().height * 0.5));
            
            if (m_BattleIndex <= PetCnt) {
                particle->setRotationY(180);
            }
        }
        
        arrAct->addObject(CCCallFuncO::create(this, callfuncO_selector(FightPetSprite::onParticle), particle));
        if (effGroup->byType == 1) {    //一起}
            time = time > particle->getDuration()? time : particle->getDuration();
        }
        else if (effGroup->byType == 2) {   //顺序}
            time += particle->getDuration();
            arrAct->addObject(CCDelayTime::create(particle->getDuration()));
        }
        
    }
    if (arrAct->count() > 0) {
        //        arrAct->addObject(NULL);
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

void FightPetSprite::onParticle(CCObject *pObject)
{
	CCParticleSystemQuad *particle = (CCParticleSystemQuad *)pObject;
    if (isParitleStop) {
        return;
    }
    arrCurParticle.push_back(particle);
    int zorder = 698; //全体，比血条(697)高}
    if (particle->getTag() == 2) { //单体，比血条(697)低}
        zorder = 695;
    }
    
    //    if (m_delegate && !dynamic_cast<CcbArenaFightLayer*>(m_delegate)) {
    //        if (getParent() && getParent()->getParent() && !particle->getParent()) {
    //            getParent()->getParent()->addChild(particle, zorder);
    //        }
    //    }
    //    else
    //    {
    if (getParent() && !particle->getParent()) {
        getParent()->addChild(particle, zorder);
    }
    //    }
}

std::string FightPetSprite::getEffPath(std::string idx)
{
    char buf[256];
    sprintf(buf, "effect/effect_%s.plist",idx.c_str());
    return buf;
}

CCPoint FightPetSprite::getPointOffByType(uint32 skillId, uint16 wNextIndex)
{
    CCPoint pos = CCPointZero;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig,  skillId);
    
    if (ultCfg && ultCfg->byType == 1) {
        if (wNextIndex < arrComboOffSkill.size())
        {
            pos = arrComboOffSkill[wNextIndex];
        }
    }
    else{
    
        if (wNextIndex < arrComboOffNorm.size()) {
            pos = arrComboOffNorm[wNextIndex];
        }
    }
    
    return pos;
}


void FightPetSprite::setOpacity(GLubyte opacity)
{
    mc->setOpacity(opacity);
    if (getChildByTag(112)) {
        dynamic_cast<EffectLayer*>(getChildByTag(112))->getSprite()->setOpacity(opacity);
    }
}


//显示被动技能 并 刷新Buff 和 Eff}
void FightPetSprite::showPassive(std::vector<STC_TRIGGERED_PSKILL> arrTPSkill, bool flag)
{
    for (int i = 0; i < arrTPSkill.size(); ++i) {
        STC_TRIGGERED_PSKILL ps = arrTPSkill[i];
        if (ps.wSkillIndex == 0) {
            continue;
        }
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *pCfg = GET_CONFIG_STC(PassiveSkillConfig, ps.wSkillIndex);
        if (!pCfg) {
            continue;
        }
        FightPetSprite* pet = m_delegate->getFightPetSprite(ps.fightId);
        if (!pet) {
            continue;
        }
        if (pCfg->byTriggerType == E_PASSIVE_TYPE_IN_FIGHT) {
            pet->showPassSkillLayer();
        }
        if (pCfg->byIsShow) {
            pet->showPassive(pCfg->strName);
        }
        
        
        for (int k = 0; k < ps.arrMyEffsAndBuff.size(); ++k) {
            STC_PET_EFF_BY_PSKILL petEff = ps.arrMyEffsAndBuff[k];
            
            FightPetSprite* petS = m_delegate->getFightPetSprite(petEff.fightId);
            if (!petS) {
                continue;
            }
            
            if (flag)
            {
                petS->setMapBuff(petEff.arrBuff);
                petS->reflashBuff();
                
                petS->setArrEff(petEff.arrEff);
                petS->showEff();
                
            }
            //            setPetCtrlSpecial(petEff.fightId);
        }
        
        for (int k = 0; k < ps.arrEnemyEffsAndBuff.size(); ++k) {
            STC_PET_EFF_BY_PSKILL petEff = ps.arrEnemyEffsAndBuff[k];
            
            FightPetSprite* petS = m_delegate->getFightPetSprite(petEff.fightId);
            if (!petS) {
                continue;
            }
            
            //            petS->setMapBuff(petEff.arrBuff);
            //            petS->reflashBuff();
            if (flag)
            {
                petS->setMapBuff(petEff.arrBuff);
                petS->reflashBuff();
                
                petS->setArrEff(petEff.arrEff);
                petS->showEff();
            }
            //            setPetCtrlSpecial(petEff.fightId);
        }
        
    }
}
//加入一个被动技能(前三个依次显示，之后的进入等待序列)}
void FightPetSprite::showPassive(std::string strPassName)
{
    for (int i = 0; i < arrNowShowPassTextSprite.size(); i++) {
        CCSprite *img = arrNowShowPassTextSprite[i];
        if (!img) {
            continue;
        }
        CCLabelTTF *lbl = dynamic_cast<CCLabelTTF *>(img->getChildByTag(1));
        if (!lbl) {
            continue;
        }
        if (strcmp(lbl->getString(), strPassName.c_str()) == 0) {
            return;
        }
    }
    
    CCSprite *img = CCSprite::create("ccbresources/12monthdate/battle/back_normal_skill.png");
    CCLabelTTF *lbl = CCLabelTTF::create(strPassName.c_str(), FONT_HEL, 13);
    lbl->setPosition(ccp(getWidth(img) * 0.5 - 8, getHeight(img)*0.5 - 2));
    lbl->setTag(1);
    img->addChild(lbl);
    img->setAnchorPoint(ccp(0.5, 0));
    if (m_BattleIndex <= PetCnt) {
        img->setRotationY(180);
    }
    img->setPosition(ccp(0, standSize.height));
    addChild(img);
    arrNowShowPassTextSprite.push_back(img);
    for (int i=0; i < arrNowShowPassTextSprite.size() - 1; i++) {
        CCSprite *sp = arrNowShowPassTextSprite[i];
        sp->setPositionY(sp->getPositionY() + getHeight(sp));
    }
    img->runAction(CCSequence::create(CCDelayTime::create(0.5),
                                      CCCallFuncN::create(this, callfuncN_selector(FightPetSprite::hidePassText)),
                                      NULL));

}

//显示下一个被动技能（三个以内，显示够1.5秒后消失，多余三个时，每个最多显示0.5秒）}
void FightPetSprite::addPassText(std::string strPassName)
{
    for (int i = 0; i < arrNowShowPassTextSprite.size(); i++) {
        CCSprite *img = arrNowShowPassTextSprite[i];
        if (!img) {
            continue;
        }
        CCLabelTTF *lbl = dynamic_cast<CCLabelTTF *>(img->getChildByTag(1));
        if (!lbl) {
            continue;
        }
        if (strcmp(lbl->getString(), strPassName.c_str()) == 0) {
            return;
        }
    }
    
    if (arrNowShowPassTextSprite.size() >= 3 ) {
        CCSprite *sp = arrNowShowPassTextSprite[0];
        sp->stopAllActions();
        hidePassText(sp);
    }
    
    CCSprite *img = CCSprite::create("ccbresources/12monthdate/battle/back_normal_skill.png");
    CCLabelTTF *lbl = CCLabelTTF::create(strPassName.c_str(), FONT_HEL, 13);
    lbl->setPosition(ccp(getWidth(img) * 0.5 - 8, getHeight(img)*0.5 - 2));
    lbl->setTag(1);
    img->addChild(lbl);
    img->setAnchorPoint(ccp(0.5, 0));

    if (m_BattleIndex <= PetCnt) {
        img->setRotationY(180);
    }
    img->setPosition(ccp(0, standSize.height));
    addChild(img);
    arrNowShowPassTextSprite.push_back(img);

    for (int i=0; i < arrNowShowPassTextSprite.size() - 1; i++) {
        CCSprite *sp = arrNowShowPassTextSprite[i];
        sp->setPositionY(sp->getPositionY() + getHeight(sp));

    }
    img->runAction(CCSequence::create(CCDelayTime::create(0.5),
                                      
                                      CCCallFuncN::create(this, callfuncN_selector(FightPetSprite::hidePassText)),
                                      NULL));
    
}
//等待计时(0.5秒)，}
void FightPetSprite::updataWaitForShowPass(float time)
{
    if (arrWaitPassiveText.size() > 0) {
        std::string text = arrWaitPassiveText[0];
        addPassText(text);
        arrWaitPassiveText.erase(arrWaitPassiveText.begin());
    }
    else
    {
        unschedule(schedule_selector(FightPetSprite::updataWaitForShowPass));
    }
}
//消失}
void FightPetSprite::hidePassText(cocos2d::CCNode *node)
{
    arrNowShowPassTextSprite.erase(arrNowShowPassTextSprite.begin());
    node->removeFromParentAndCleanup(true);
    
    node = NULL;
}

//显示被动技能动画}
void FightPetSprite::showPassSkillLayer()
{
    CCNode* node = getChildByTag(111);
    if (node) {
        node->removeFromParent();
    }
    
    EffectLayer* effLayer = EffectLayer::create(E_ANI_EFFECT_BATTLE_PSKILL_EFF, 1, 0.15);
    effLayer->setPosition(ccp(0, getStandSize().height * 0.5));
    effLayer->ignoreAnchorPointForPosition(false);
    effLayer->setAnchorPoint(ccp(0.5, 0.5));
    effLayer->setTag(111);
    addChild(effLayer, 4);
    effLayer->onRun();
}

void FightPetSprite::updateForDoBattle(float time)
{
    if (waitForDoBattle < 0) {
        return;
    }
    waitForDoBattle--;
    if (waitForDoBattle == 0) {
        doBattle();
    }
    
}
