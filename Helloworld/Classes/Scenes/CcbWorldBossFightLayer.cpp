#include "CcbWorldBossFightLayer.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "FightTeam.h"
#include "FightAI.h"
#include "FightPetSprite.h"
#include "ShowPetBattleWord.h"
#include "UISupport.h"
#include "BackCtrl.h"
#include "CcbAltSkillEffLayer.h"
#include "MusicCtrl.h"
#include "CcbSystemBootLose.h"
#include "GameSession.h"
#include "Support.h"
#include "CcbPetBattleCtrl.h"
#include "CcbFightRewardLayer.h"
#include "Role.h"
#include "PetLoadingLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

 WorldBossFightScene:: WorldBossFightScene()
{
    
}
 WorldBossFightScene::~ WorldBossFightScene()
{
    
}
CCScene*  WorldBossFightScene::scene()
{
    CCScene *scene = CCScene::create();
    
     WorldBossFightScene *layer =  WorldBossFightScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool  WorldBossFightScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbWorldBossFightLayer(this));
    
    return true;
}

CcbWorldBossFightLayer::~CcbWorldBossFightLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteFarMap);
	CC_SAFE_RELEASE_NULL(m_pSpriteNearMap);
	CC_SAFE_RELEASE_NULL(m_pSpriteBossIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteBossHpBar);
	CC_SAFE_RELEASE_NULL(m_pSpriteBossNature);
	CC_SAFE_RELEASE_NULL(m_pLayerBossHpBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEnemyAltName);
	CC_SAFE_RELEASE_NULL(m_pSpriteEnemyAltBg);
	CC_SAFE_RELEASE_NULL(m_pLayerAllBg);
	CC_SAFE_RELEASE_NULL(m_pSpritePetCtrlBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteMyHpBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteMyHpBar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMyMaxHP);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMyCurHP);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_6);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_4);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_2);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_5);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_3);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_1);
	CC_SAFE_RELEASE_NULL(m_pLayerPetCtrlBg);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbWorldBossFightLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbWorldBossFightLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbWorldBossFightLayer", CcbWorldBossFightLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/pet_battle_ctrl.ccb]", [ccb/pet_battle_ctrl.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_boss_scene.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbWorldBossFightLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbWorldBossFightLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Eff_arean_battle));
    loadData();
}

void CcbWorldBossFightLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                       CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::fightStart)),
                                       NULL));
}

void CcbWorldBossFightLayer::onExit()
{
	CCLayer::onExit();
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0);
}

void CcbWorldBossFightLayer::onExitTransitionDidStart()
{
    CMusicCtrl::StopBackgroundMusic();
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Bgm_main_scene));
    CCLayer::onExitTransitionDidStart();
    CCDirector::sharedDirector()->purgeCachedData();
    CCArmatureDataManager::sharedArmatureDataManager()->removeAllArmatureFileInfo();
}

// Inhert MemberVariableAssigner
bool CcbWorldBossFightLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFarMap", CCSprite*, this->m_pSpriteFarMap);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNearMap", CCSprite*, this->m_pSpriteNearMap);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBossIcon", CCSprite*, this->m_pSpriteBossIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBossHpBar", CCSprite*, this->m_pSpriteBossHpBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBossNature", CCSprite*, this->m_pSpriteBossNature);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBossHpBg", CCLayer*, this->m_pLayerBossHpBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnemyAltName", CCLabelTTF*, this->m_pLabelTTFEnemyAltName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEnemyAltBg", CCSprite*, this->m_pSpriteEnemyAltBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerAllBg", CCLayer*, this->m_pLayerAllBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetCtrlBg", CCSprite*, this->m_pSpritePetCtrlBg);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMyHpBg", CCSprite*, this->m_pSpriteMyHpBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMyHpBar", CCSprite*, this->m_pSpriteMyHpBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMyMaxHP", CCLabelTTF*, this->m_pLabelTTFMyMaxHP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMyCurHP", CCLabelTTF*, this->m_pLabelTTFMyCurHP);
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_6", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_6);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_4", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_2", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_5", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_3", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_1", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetCtrlBg", CCLayer*, this->m_pLayerPetCtrlBg);

	return false;
}

bool CcbWorldBossFightLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbWorldBossFightLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbWorldBossFightLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbWorldBossFightLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbWorldBossFightLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    
    m_pSpriteEnemyAltBg->setVisible(false);
    
    mapPetCtrl[1] = m_pLayerPetBattleCtrl_1;
    mapPetCtrl[2] = m_pLayerPetBattleCtrl_2;
    mapPetCtrl[3] = m_pLayerPetBattleCtrl_3;
    mapPetCtrl[4] = m_pLayerPetBattleCtrl_4;
    mapPetCtrl[5] = m_pLayerPetBattleCtrl_5;
    mapPetCtrl[6] = m_pLayerPetBattleCtrl_6;
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "ccbresources/12monthdate/battle/CloseNormal.png",
                                                          "ccbresources/12monthdate/battle/CloseSelected.png",
                                                          this,
                                                          menu_selector(CcbWorldBossFightLayer::menuCloseCallback)
                                                          );
    
    pCloseItem->setPosition( ccp(winSize.width - 20, 20) );
    pCloseItem->setScale(2);
    
    
    CCMenuItemLabel* btnJiaSu = CCMenuItemLabel::create(CCLabelTTF::create("加速", "", 20), this, menu_selector(CcbWorldBossFightLayer::menuJiaSu));
    btnJiaSu->setPosition(pCloseItem->getPosition() + ccp(0, 40) );

    CCMenu* pMenu = CCMenu::create(pCloseItem, btnJiaSu, NULL);
    pMenu->setPosition( CCPointZero );
    pMenu->setTouchPriority(kCCMenuHandlerPriority - 30);
#ifdef DEBUG
    this->addChild(pMenu, 1000);
#endif
    
    
    myhpBarWidth = getWidth(m_pSpriteMyHpBar);
    bosshpBarWidth = getWidth(m_pSpriteBossHpBar);
    fRealHeight = winSize.height - getTop(m_pLayerPetCtrlBg);
    initPos();
}

bool CcbWorldBossFightLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbWorldBossFightLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 15, true);
}

void CcbWorldBossFightLayer::menuCloseCallback(cocos2d::CCObject *pObject)
{
    failVerified();
}
void CcbWorldBossFightLayer::menuJiaSu(cocos2d::CCObject *pObject)
{
    if (CCDirector::sharedDirector()->getScheduler()->getTimeScale() > 1.0) {
        CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0);
        return;
    }
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(5.0);
}
void CcbWorldBossFightLayer::failVerified()
{
    BackCtrl::BacktoUpperScene();
}

//初始化站位}
void CcbWorldBossFightLayer::initPos()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    float rowH = 0;//(fRealHeight - 145 - 25) / 2;
    if (winSize.height <= 480) {
        rowH = (fRealHeight - 125 - 25) / 2;
    }
    else{
        rowH = (fRealHeight - 165 - 25) / 2;
    }
    float offY = getHeight(m_pLayerAllBg) - fRealHeight + 25;
    arrPetPos[0] = ccp(100 + 0,offY + rowH*2);
    arrPetPos[2] = ccp(100 + 0,offY + rowH);
    arrPetPos[4] = ccp(100 + 0,offY);
    arrPetPos[1] = ccp(30 + 0,offY + rowH * 2);
    arrPetPos[3] = ccp(30 + 0,offY + rowH);
    arrPetPos[5] = ccp(30 + 0,offY);
    
    
    arrEnemyPos[0] = ccp(320 - 110 + 0, offY + rowH*2);
    if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE) {
        arrEnemyPos[2] = ccp(320 - 100 + 40 + 0, offY + rowH);
    }
    else
    {
        arrEnemyPos[2] = ccp(320 - 100 + 0,offY + rowH);
    }
    arrEnemyPos[4] = ccp(320 - 100 + 0, offY);
    arrEnemyPos[1] = ccp(320 - 30 + 0, offY + rowH*2);
    arrEnemyPos[3] = ccp(320 - 30 + 0, offY + rowH);
    arrEnemyPos[5] = ccp(320 - 30 + 0, offY);
}

//获取我方宠物中间位置}
CCPoint CcbWorldBossFightLayer::getMyMiddlePos()
{
    return arrPetPos[2];
}
//获取敌方宠物中间位置}
CCPoint CcbWorldBossFightLayer::getEnemyMiddlePos()
{
    return arrEnemyPos[2];
}

void CcbWorldBossFightLayer::loadData()
{
    handlerPVPInfo(*FightAI::Get()->getPVPData());
    
    mapPetSprite.clear();
    FightTeam *myTeam = FightAI::Get()->Get()->getMyTeam();
    FightTeam *enemyTeam = FightAI::Get()->getEnemyTeam();
    
    //我方队伍}
    std::map<uint16, FightPet*>::iterator itM = myTeam->GetTeam().begin();
    for (; itM != myTeam->GetTeam().end(); itM++) {
        if (!itM->second) {
            continue;
        }
        FightPet *pet = itM->second;
        //flcc
        FightPetSprite *pSprite = FightPetSprite::create(pet->getPetInfo().wBattleIndex, this);
        mapPetSprite[itM->first] = pSprite;
        CCPoint pos = arrPetPos[itM->first % 100 - 1];
        pSprite->setPosition(pos);
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setMyPos(pos);
//        pSprite->setScale(0.9);
        pSprite->setRotationY(180);
        pSprite->setIsCanDead(true);
        
        m_pLayerAllBg->addChild(pSprite, 480 - pos.y);
        pSprite->setOpacity(0);
    }
    
    m_dwCurMyTeamHP = myTeam->GetTeamHp();
    m_dwMyTeamHP = myTeam->GetTeamHpMax();
    
    m_pLabelTTFMyCurHP->setString(CCString::createWithFormat("%d", m_dwCurMyTeamHP)->getCString());
    m_pLabelTTFMyMaxHP->setString(CCString::createWithFormat("%d", m_dwMyTeamHP)->getCString());
    
    //敌方队伍}
    std::map<uint16, FightPet*>::iterator itE = enemyTeam->GetTeam().begin();
    for (; itE != enemyTeam->GetTeam().end(); itE++) {
        if (!itE->second) {
            continue;
        }
        FightPet *pet = itE->second;
        //flcc
        FightPetSprite *pSprite = FightPetSprite::create(pet->getPetInfo().wBattleIndex, this);
        mapPetSprite[itE->first] = pSprite;
        CCPoint pos = arrEnemyPos[itE->first % 100 - 1];
        pSprite->setPosition(pos);
        //        pSprite->setRotationY(180);
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setMyPos(pos);
//        pSprite->setScale(0.9);
        
        if (itE->second->getPetInfo().isBoss) {
            m_wBossIndex = itE->first;
            showBossHp();
            pSprite->setScale(1.1);
//            hpBar = NULL;
        }
        pSprite->setVisible(false);
        pSprite->setIsCanDead(true);
        
        m_pLayerAllBg->addChild(pSprite, 480 - pos.y);
//        pSprite->setOpacity(0);
        
    }
    
    //icon
    for (int i = 1; i <= PetCnt; i++) {
        CcbPetBattleCtrl *pCtrl = mapPetCtrl[i];
        pCtrl->setBattleIndex(i, this);
    }
}

//显示boss血条}
void CcbWorldBossFightLayer::showBossHp()
{
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(m_wBossIndex);
    if (!pet) {
        return;
    }
    
    m_pLayerBossHpBg->setVisible(true);
//    m_wBossIndex = pet->getPetInfo().wBattleIndex;
    //如果是boss掉血}
    m_pSpriteBossHpBar->setTextureRect(CCRectMake(0, 0, (float)pet->getCurHP() / pet->getPetInfo().wHP * bosshpBarWidth / m_pSpriteBossHpBar->getScaleX(), getHeight(m_pSpriteBossHpBar) / m_pSpriteBossHpBar->getScaleY()));
    
    //头像}
    m_pSpriteBossIcon->setTexture(CPetCtrl::Get()->GetPetHeadTexture(pet->getPetInfo().wPetIndexId));
    
    CCSpriteFrame* sf = CPetCtrl::Get()->GetPetNaturePicSF(pet->getPetInfo().wPetIndexId);
    m_pSpriteBossNature->setDisplayFrame(sf);
}

int CcbWorldBossFightLayer::getEnemyIndex(STC_BATTLE_DATA bData)
{
    uint16 enemyIndex = 3;
    
    uint8 eEffObj = bData.eEffObj;
    uint8 scope = E_ATTACK_SCOPE_BF_SINLGE;
    if (bData.wSkillId) {
        UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, bData.wSkillId);
        if (ultCfg) {
            scope = ultCfg->byAttackScope;
        }
    }
    
    if (bData.arrAttData.size() == 1)  //只有一个目标时，攻击位置就是那个目标}
    {
        enemyIndex = bData.arrAttData.begin()->first;
    }
    else    //多个目标时，默认是中间位置}
    {
        enemyIndex = 3;
    }
    
    switch (scope) {
        case E_ATTACK_SCOPE_BF_SINLGE:
            
        case E_ATTACK_SCOPE_AF_SINGLE:
            
        case E_ATTACK_SCOPE_ATK_MAX:
            
        case E_ATTACK_SCOPE_HP_MIN:
            
        case E_ATTACK_SCOPE_DEF_MIN:
            
        case E_ATTACK_SCOPE_NATURE_SELECT:
            
        case E_ATTACK_SCOPE_COLUMN:
            
        case E_ATTACK_SCOPE_RAND_TWO:
            
        case E_ATTACK_SCOPE_RAND_THREE:
            
        case E_ATTACK_SCOPE_ATK_MAX_2:
            
        case E_ATTACK_SCOPE_HP_MIN_2:
            
        case E_ATTACK_SCOPE_DEF_MIN_2:
            
        case E_ATTACK_SCOPE_NATURE_SELECT_2:
            //已经由默认方式 获取到了正确的攻击位置}
            break;
        case E_ATTACK_SCOPE_AF_ALL:
        case E_ATTACK_SCOPE_BF_ALL:
            if (bData.arrAttData.size() > 0 && bData.arrAttData.begin()->first % 2 > 0) {
                //因为是后排全体，如果选择的有前排，说明后排没有目标了(要买全部前排，要买全部后排)}
                enemyIndex = 3;
                break;
            }
            else{
                enemyIndex = 4;
            }
            break;
        case E_ATTACK_SCOPE_ALL:
            enemyIndex = 3;
            break;
            
        default:
            break;
    }
    
    if (eEffObj == E_EFFECT_OBJECT_MY) {
        enemyIndex = 3;
    }
    
    return enemyIndex;
}

void CcbWorldBossFightLayer::pauseAll()
{
    CCDirector *director = CCDirector::sharedDirector();
    
    //    pauseActions = NULL;
    //    pauseTargets = NULL;
    
    CC_SAFE_RELEASE(pauseActions);
    pauseActions = director->getActionManager()->pauseAllRunningActions();
    CC_SAFE_RETAIN(pauseActions);
    
    CC_SAFE_RELEASE(pauseTargets);
    pauseTargets = CCDirector::sharedDirector()->getScheduler()->pauseAllTargets();
    CC_SAFE_RETAIN(pauseTargets);
    m_isPauseAll = true;
    director->getScheduler()->resumeTarget(director->getActionManager());
    this->getScheduler()->resumeTarget(this);
}

void CcbWorldBossFightLayer::remuseAll()
{
    
    CCDirector::sharedDirector()->getScheduler()->resumeTargets(pauseTargets);
    CCDirector::sharedDirector()->getActionManager()->resumeTargets(pauseActions);
    m_isPauseAll = false;
    //    pauseActions = NULL;
    //    pauseTargets = NULL;
}

void CcbWorldBossFightLayer::fightStart()
{
    m_CurRound = 0;
    
    //1、开场动画}
    //2、我方进场动画}
    //3、队长动画 + 队长语音}
    //4、敌方进场}
    
    float time = 0.7;
    float time2 = 0.2;

    time = showFightStartEff();
    time2 = 1.6;

    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(time2),
//                                       CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::showBossHp)),
                                       CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::enemyRunIn)),
                                       NULL
                                       )
                    );
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(time),
                                       CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::roundStart)),
                                       NULL
                                       )
                    );
}

void CcbWorldBossFightLayer::afterInEff()
{
    //播完回调，开始战斗}
    roundStart();
}

void CcbWorldBossFightLayer::fightEnd()
{
    //播战斗结束动画，弹出结算面板}
    CMusicCtrl::StopBackgroundMusic();
    if (m_ArenaData.isWin) {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_pve_win));
        ShowPetBattleWord::showTextWord(E_WORD_TYPE_FIGHT_FINISH, ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) -fRealHeight*0.5), m_pLayerAllBg);
    }
    else{
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_pve_lose));
        ShowPetBattleWord::showTextWord(E_WORD_TYPE_LOSE, ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) -fRealHeight*0.5), m_pLayerAllBg);
    }
    this->runAction(CCSequence::create(CCDelayTime::create(2.8),
                                       CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::gotoReward)),
                                       NULL));
//    }
//    else
//    {
//        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_arena_lose));
//        CcbSystemBootLose::showLose();
//    }
}

void CcbWorldBossFightLayer::gotoReward()
{
    uint8 itemCnt = 0;
    uint8 petCnt = 0;
    std::vector<STC_FIGHT_REWARD_ITEM>arrReward = FightAI::Get()->getPveReward();
    for (int i = 0; i < arrReward.size(); i++) {
        STC_FIGHT_REWARD_ITEM item = arrReward[i];
        if (!item.dwItemId && item.dwCount > 0) {
            continue;
        }
        itemCnt++;
    }
    if (!petCnt && !itemCnt) {
        if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_BOSS) {
            CGameSession::SendWorldBossInfo();
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            return;
        }
    }
    
    CRole* role = CGameSession::GetRole();
    
    STC_BATTLE_PRE_DATA perData;
    perData.wUserLv = role->GetwRoleLv();
    perData.dwCurExp = role->GetdwRoleExp();
    perData.dwCurEnergy = role->GetdwEnergy();
    perData.byCurFightCnt = role->GetdwBattleBagCnt();
    FightAI::Get()->setPerData(perData);
    
    CcbFightRewardLayer::showReward();
}

void CcbWorldBossFightLayer::roundStart()
{
    if (m_ArenaData.arrRound.empty()) {
        CCMessageBox("byTeamSize is 0", "Eeeeeeerrrrror");
        return;
    }
    m_curBattleRound = m_ArenaData.arrRound[m_CurRound];
    arrSkillWait.clear();
    m_AttCnt = 0;// m_curBattleRound.arrWaitBattle.size();
    m_CurAttCnt = 0;
    
    //显示技能预备效果}
    for (int i = 0; i < m_curBattleRound.arrWaitBattle.size(); i++) {
        STC_WAIT_BATTLE data = m_curBattleRound.arrWaitBattle[i];
        
        bool isRealSkill = false;
        UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, data.bData.wSkillId);
        if (ultCfg && ultCfg->byType == 1) {
            isRealSkill = true;
        }
        
        if (isRealSkill) {
            FightPetSprite* sPet = mapPetSprite[data.bData.wBattleIndex];
            if (sPet) {
                sPet->showAltEff();
            }
        }
    }
    
    //刷新Buff}
    std::map<uint16, std::vector<STC_BUFF> >::iterator it = m_curBattleRound.mapBeforeBuff.begin();
    for (; it != m_curBattleRound.mapBeforeBuff.end(); it++) {
        std::vector<STC_BUFF> arrBuff = it->second;
        FightPetSprite *pet = NULL;
        pet = mapPetSprite[it->first];
        
        FightPet* fPet = FightAI::Get()->getFightPetByBIndex(it->first);
        
        if (pet && fPet) {
            std::map<uint8, std::vector<STC_BUFF> > mapBuff;
            mapBuff[1] = arrBuff;
            fPet->setMapBuff(mapBuff);
            
            pet->setMapBuff(mapBuff);
            pet->reflashBuff();
            
            
        }
    }
    
    //显示被动技能}
    std::map<uint16, std::vector<STC_TRIGGERED_PSKILL> >::iterator itP = m_curBattleRound.mapBeforePass.begin();
    for (; itP != m_curBattleRound.mapBeforePass.end(); itP++) {
        
        FightPetSprite *pet = NULL;
        pet = mapPetSprite[it->first];
        
        if (!pet) {
            continue;
        }
        pet->showPassive(itP->second);
    }
    
    if (m_curBattleRound.arrWaitBattle.size() == 0) {
        this->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                           CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::roundEnd)),
                                           NULL));
        return;
    }
    //    schedule(schedule_selector(CcbWorldBossFightLayer::updateWaitForFight));
    schedule(schedule_selector(CcbWorldBossFightLayer::updateForChkDead));
    
    bool isRealSkill = false;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, m_curBattleRound.arrWaitBattle[0].bData.wSkillId);
    if (ultCfg && ultCfg->byType == 1) {
        isRealSkill = true;
    }
    
    if (isRealSkill) {
        STC_WAIT_BATTLE data = m_curBattleRound.arrWaitBattle[0];
        data.wcurFrame = 0;
        arrSkillWait.push_back(data);
    }
    
    startBattle(m_curBattleRound.arrWaitBattle[0]);
    
}

void CcbWorldBossFightLayer::roundEnd()
{
    unschedule(schedule_selector(CcbWorldBossFightLayer::updateForChkDead));
    m_CurRound++;
    if(m_CurRound >= m_ArenaData.arrRound.size())
    {
        this->runAction(CCSequence::create(CCDelayTime::create(1.5),
                                           CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::fightEnd)),
                                           NULL));
    }
    else
    {
        //buff生效}
        std::map<uint16, std::vector<STC_BUFF_VALUE> >::iterator it = m_curBattleRound.mapAfterBuffValue.begin();
        for (; it != m_curBattleRound.mapAfterBuffValue.end(); it++) {
            std::vector<STC_BUFF_VALUE> arrBuff = it->second;
            FightPetSprite *pet = NULL;
            pet = mapPetSprite[it->first];
            
            if (pet) {
                pet->buffActive(arrBuff);
            }
        }
        //刷新Buff}
        std::map<uint16, std::vector<STC_BUFF> >::iterator itA = m_curBattleRound.mapAfterBuff.begin();
        for (; itA != m_curBattleRound.mapAfterBuff.end(); itA++) {
            std::vector<STC_BUFF> arrBuff = itA->second;
            FightPetSprite *pet = NULL;
            pet = mapPetSprite[itA->first];
            FightPet* fPet = FightAI::Get()->getFightPetByBIndex(it->first);
            
            if (pet && fPet) {
                std::map<uint8, std::vector<STC_BUFF> > mapBuff;
                mapBuff[1] = arrBuff;
                
                fPet->setMapBuff(mapBuff);
                
                pet->setMapBuff(mapBuff);
                pet->reflashBuff();
            }
        }
        
        //刷新必杀值}
        std::map<uint16, uint16>::iterator itP = m_curBattleRound.mapAfterPower.begin();
        for (; itP != m_curBattleRound.mapAfterPower.end(); itP++) {
            CcbPetBattleCtrl *petCtrl = NULL;
            petCtrl = mapPetCtrl[itP->first];
            if (petCtrl) {
                petCtrl->setPower(itP->second);
            }
        }
        
        //刷新血量}
        std::map<uint16, uint32>::iterator itHp = m_curBattleRound.mapAfterHp.begin();
        for (; itHp != m_curBattleRound.mapAfterHp.end(); itHp++) {
            CcbPetBattleCtrl *petCtrl = NULL;
            petCtrl = mapPetCtrl[itHp->first];
            if (petCtrl) {
                petCtrl->loseHP(itHp->second);
            }
            FightPetSprite *pet = NULL;
            pet = mapPetSprite[itHp->first];
            if (pet) {
                pet->setCurHP(itHp->second);
                if (itHp->second == 0) {
                    pet->setIsDead(true);
                }
            }
        }
        
        m_dwCurMyTeamHP = m_curBattleRound.dwMyAllHp;
//        m_dwCurEnemyTeamHP = m_curBattleRound.dwEnemyAllHp;
        
        //开始下一回合}
        schedule(schedule_selector(CcbWorldBossFightLayer::updateForChange));
    }
}

//验证连携}
bool CcbWorldBossFightLayer::checkLianXie(STC_WAIT_BATTLE wdata)
{
    m_WaitAttCnt = 0;
    if (wdata.arrLianxieId.size() == 0) {
        return false;
    }
    arrLianxieWait.clear();
    int cnt = 0;
    for (int i = m_CurAttCnt; i < m_curBattleRound.arrWaitBattle.size(); i++) {
        
        STC_WAIT_BATTLE w = m_curBattleRound.arrWaitBattle[i];
        bool isRealSkill = false;
        UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, w.bData.wSkillId);
        if (ultCfg && ultCfg->byType == 1) {
            isRealSkill = true;
        }
        //过滤掉技能攻击的}
        if (isRealSkill) {
            continue;
        }
        
        w.wcurFrame = 0;
        w.wStartFrame = delayFrame * cnt + 1;
        arrLianxieWait.push_back(w);
        cnt++;
        if (cnt >= wdata.arrLianxieId.size()) {
            break;
        }
    }
    if (arrLianxieWait.size() == 1) {
        arrLianxieWait.clear();
        return false;
    }
    
    for (int i = 0; i < arrLianxieWait.size(); i++) {
        uint16 id = wdata.arrLianxieId[i];
        FightPet* pet = FightAI::Get()->getFightPetByBIndex(id);
        STC_WAIT_BATTLE w = arrLianxieWait[i];
        if (wdata.wLianxieAdd) {
            if (pet) {
                pet->setLianXieState(E_LIANXIE_STATE_OK);
            }
            w.wStartFrame += 3*delayFrame;
            arrLianxieWait[i] = w;
            FightPetSprite* petSp = mapPetSprite[id];
            if (petSp) {
                petSp->showLianXie(wdata.wLianxieAdd);
            }
        }
        else{
            pet->setLianXieAdd(0);
            pet->setLianXieState(E_LIANXIE_STATE_LOSE);
        }
        
        if (i - m_CurAttCnt == wdata.arrLianxieId.size() - 1) {
            pet->setLianXieState(E_LIANXIE_STATE_LAST);
        }
        
    }
    if (wdata.wLianxieAdd) {
        CCNode *lianxieBg = CcbManager::sharedManager()->LoadCcbLianXieBgLayer();
        if (lianxieBg) {
            lianxieBg->setPosition(ccp(getWidth(m_pLayerAllBg)*0.5, getHeight(m_pLayerAllBg) - fRealHeight*0.5));
            lianxieBg->setAnchorPoint(ccp(0.5, 0.5));
            lianxieBg->ignoreAnchorPointForPosition(false);
            m_pLayerAllBg->addChild(lianxieBg);
            lianxieBg->setTag(555);
        }
    }
    
    m_WaitAttCnt = arrLianxieWait.size();
    schedule(schedule_selector(CcbWorldBossFightLayer::updateWaitForFight));
    return true;
}

void CcbWorldBossFightLayer::startBattle(STC_WAIT_BATTLE wdata)
{
    FightPetSprite *mc = NULL;
    STC_BATTLE_DATA data = wdata.bData;
    mc = mapPetSprite[data.wBattleIndex];
    if (mc->getCurHP() <= 0) {
        m_CurAttCnt++;
        endBattle(data.wBattleIndex, 0);
        return;
    }
    //在此加连携判断，并且改变出击方式}
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(data.wBattleIndex);
    
    bool isRealSkill = false;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, data.wSkillId);
    if (ultCfg && ultCfg->byType == 1) {
        isRealSkill = true;
    }
    
    if (!isRealSkill) {
        //判断连携}
        if (pet->getLianXieState() == E_LIANXIE_STATE_NON) {
            if (checkLianXie(wdata)) {
                return;
            }
        }
        
        if (pet->getLianXieState() == E_LIANXIE_STATE_LAST) {
            unschedule(schedule_selector(CcbWorldBossFightLayer::updateWaitForFight));
        }
    }
    //能走到这，说明此精灵已经开始攻击了}
    m_CurAttCnt++;
    arrCurFightPet.insert(data.wBattleIndex);
    //判断下一次攻击是否是技能攻击(非最后一次攻击)}
    if (m_CurAttCnt < m_curBattleRound.arrWaitBattle.size() - 1) {
        STC_WAIT_BATTLE nda = m_curBattleRound.arrWaitBattle[m_CurAttCnt];
        ultCfg = GET_CONFIG_STC(UltimateSkillConfig, nda.bData.wSkillId);
        bool isSkill = false;
        if (ultCfg && ultCfg->byType == 1) {
            isSkill = true;
        }
        if (isSkill) {
            //根据不同的情况，选择不同攻击方式}
            //当自身正在攻击，或者敌方正在攻击时，加入等待序列，等待攻击}
            nda.wcurFrame = 0;
            if (arrCurFightPet.size() > 0) {
                if (arrCurFightPet.find(nda.bData.wBattleIndex) != arrCurFightPet.end()
                    || abs(*arrCurFightPet.begin() - nda.bData.wBattleIndex) > PetCnt) {
                    //            isSkillFight = true;
                    nda.wcurFrame = 10000;
                    CCLog("延迟攻击~~~~~~~~~~ %d", nda.bData.wBattleIndex);
                }
            }
            //可以立刻攻击}
            if (nda.wcurFrame == 0) {
                nda.wcurFrame = delayFrame * 0.5;
                CCLog("立即攻击~~~~~~~~~~ %d", nda.bData.wBattleIndex);
            }
            arrSkillWait.push_back(nda);
            schedule(schedule_selector(CcbWorldBossFightLayer::updateForSkillWaitBattle));
        }
    }
    
    
    
    if (mc) {
        CCPoint pos = CCPointZero;
        uint16 enemyIndex = getEnemyIndex(data);
        FightPetSprite *mcE = NULL;
        int x = 1;
        if (data.wBattleIndex <= PetCnt) {
            x = -1;
            pos = arrEnemyPos[enemyIndex % 100 - 1];
            mcE  = mapPetSprite[enemyIndex+100];
        }
        else
        {
            pos = arrPetPos[enemyIndex % 100 - 1];
            mcE  = mapPetSprite[enemyIndex];
        }
        
        
        float offX = 0;
        if (mcE) {
            offX = mcE->getStandSize().width * 0.5;
        }
        //        mc->setZOrder(enemyIndex + 1);
        
        //显示主动技能的eff，刷新Buff}
        std::map<uint16, STC_ATTACK_DATA>::iterator it = data.arrAttData.begin();
        for (; it != data.arrAttData.end(); it++) {
            FightPet *fpet = FightAI::Get()->getFightPetByBIndex(it->second.wEnemyIndex);
            if (!pet) {
                continue;
            }
            //刷buff
            fpet->setMapBuff(it->second.arrEnemyBuff);
            
            pet->setMapBuff(it->second.arrMyBuff);
        }
        
        
        
        mc->startBattle(CCPoint(pos.x + x*(mc->getAtkSize().width * 0.5 + offX), pos.y), data);
        
        if (isRealSkill) {
            showSkillLayer(mc->getBattleIndex(), data.wSkillId);
            //技能释放时播放技能语音}
            PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, mc->getPetIndex());
            if (petCfg) {
                CMusicCtrl::PlayEffect(GET_PET_SOUND(petCfg->wSoundAlt));
            }
            mapPetCtrl[data.wBattleIndex]->setPower(0);
        }
    }
}

void CcbWorldBossFightLayer::doBattle(STC_BATTLE_DATA data)
{
    
}
//调整主动技能冷却}
void CcbWorldBossFightLayer::setPower(uint16 wBattleId, int wValue)
{
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(wBattleId);
    if (!pet) {
        return;
    }
    int curPower = MIN(MAX(wValue, 0), pet->getPetInfo().wAllPower);
    
    CcbPetBattleCtrl * ctrl = mapPetCtrl[wBattleId];
    if (ctrl) {
        ctrl->setPower(curPower);
    }
}

void CcbWorldBossFightLayer::setPetCtrlSpecial(uint16 wBattleIndex)
{
    if (wBattleIndex > PetCnt) {
        return;
    }
    CcbPetBattleCtrl *ctrl = mapPetCtrl[wBattleIndex];
    if (!ctrl) {
        return;
    }
    
    FightPetSprite *petS = mapPetSprite[wBattleIndex];
    if (!petS || petS->getCurHP() == 0) {
        return;
    }
    FightPet* pet = FightAI::Get()->getFightPetByBIndex(wBattleIndex);
    //麻痹}
    ctrl->setIsPalsy(pet->HasPalsyBuff(0));
    //混乱}
    ctrl->setIsConfused(pet->HasConfusedBuff(0));
    //封锁}
    ctrl->setIsSeal(pet->HasSealBuff(0));
    //冰冻
    ctrl->setIsBingDong(pet->HasFrozenBuff(0));
    //中毒
    ctrl->setIsZhongdu(pet->HasPoisonBuff(0));
    //灼烧
    ctrl->setIsZhuoShao(pet->HasFiringBuff(0));
}

void CcbWorldBossFightLayer::endBattle(uint16 wBattleIndex, uint32 skillId)
{
    FightPet* pet = FightAI::Get()->getFightPetByBIndex(wBattleIndex);
    m_AttCnt++;
    //移除正在攻击者}
    if (arrCurFightPet.find(wBattleIndex) != arrCurFightPet.end()) {
        arrCurFightPet.erase(wBattleIndex);
    }
    
    bool isRealSkill = false;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, skillId);
    if (ultCfg && ultCfg->byType == 1) {
        isRealSkill = true;
    }
    
    if (isRealSkill) {
        int cnt = 0;
        for (int i = 0; i < arrSkillWait.size(); i++) {
            STC_WAIT_BATTLE wData = arrSkillWait[i];
            if (wData.bData.wBattleIndex == wBattleIndex) {
                wData.wcurFrame = -1;
                arrSkillWait[i] = wData;
            }
            
            if (wData.wcurFrame == -1) {
                cnt ++;
            }
        }
        if (cnt == arrSkillWait.size()) {
            unschedule(schedule_selector(CcbWorldBossFightLayer::updateForSkillWaitBattle));
            arrSkillWait.clear();
        }
    }
    else{
        if (m_WaitAttCnt > 0) {
            m_WaitAttCnt--;
        }
        pet->setLianXieState(E_LIANXIE_STATE_NON);
    }
    
    
    //判断技能攻击}
    if (arrSkillWait.size() > 0){
        int cnt = 0;
        
        for (int i = 0; i < arrSkillWait.size(); i++) {
            STC_WAIT_BATTLE wData = arrSkillWait[i];
            if (wData.wcurFrame < 0) {
                continue;
            }
            //同阵营}
            if (abs(wData.bData.wBattleIndex - wBattleIndex) < PetCnt) {
                if (wData.bData.wBattleIndex == wBattleIndex) {
                    wData.wcurFrame = 0;
                    arrSkillWait[i] = wData;
                    CCLog("同阵营 延迟攻击~~~~~~~~~~ %d", wData.bData.wBattleIndex);
                    startBattle(wData);
                    return;
                }
                cnt++;
            }
        }
        //优先同阵营，当cnt > 0时，说明有同阵营的未攻击结束，直接返回即可}
        if (cnt > 0) {
            return;
        }
        
        //当同阵营的全部攻击结束，再考虑敌阵营的}
        for (int i = 0; i < arrSkillWait.size(); i++) {
            STC_WAIT_BATTLE wData = arrSkillWait[i];
            if (wData.wcurFrame < 0) {
                continue;
            }
            //敌阵营}
            if (abs(wData.bData.wBattleIndex - wBattleIndex) > PetCnt) {
                
                if (arrCurFightPet.size() == 0) {
                    wData.wcurFrame = cnt * 10 + 5;
                    arrSkillWait[i] = wData;
                    CCLog("敌阵营 延迟攻击~~~~~~~~~~ %d", wData.bData.wBattleIndex);
                    cnt++;
                }
            }
            
        }
        if (cnt > 0) {
            //            isSkillFight = false;
            schedule(schedule_selector(CcbWorldBossFightLayer::updateForSkillWaitBattle));
            return;
        }
    }
    else{
        if (m_skillBgLayer) {
            m_skillBgLayer->removeFromParentAndCleanup(true);
            m_skillBgLayer = NULL;
        }
    }
    
    
    if (m_AttCnt >= m_curBattleRound.arrWaitBattle.size()) {
        m_AttCnt = 0;
        m_CurAttCnt = 0;
        if (m_pLayerAllBg->getChildByTag(555)) { //连携}
            m_pLayerAllBg->getChildByTag(555)->setVisible(true);
            m_pLayerAllBg->getChildByTag(555)->removeFromParentAndCleanup(true);
        }
        //        pet->setLianXieState(E_LIANXIE_STATE_NON);
        this->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                           CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::eatDropThing)),
                                           NULL));
        return;
    }
    else if(m_WaitAttCnt == 0)
    {
        if (m_pLayerAllBg->getChildByTag(555)) { //连携}
            m_pLayerAllBg->getChildByTag(555)->setVisible(true);
            m_pLayerAllBg->getChildByTag(555)->removeFromParentAndCleanup(true);
        }
        if (m_CurAttCnt >= m_curBattleRound.arrWaitBattle.size()) {
            return;
        }
        startBattle(m_curBattleRound.arrWaitBattle[m_CurAttCnt]);
    }
}

void CcbWorldBossFightLayer::loseHp(uint16 wBattleIndex, int hp)
{
    FightPetSprite *pSprite = mapPetSprite[wBattleIndex];
    //掉血的是我方}
    if (wBattleIndex <= PetCnt) {
        m_dwCurMyTeamHP = m_dwCurMyTeamHP < hp ? 0 : m_dwCurMyTeamHP-hp;
        
        CCString *str = CCString::createWithFormat("%d", m_dwCurMyTeamHP);
        m_pLabelTTFMyCurHP->setString(str->getCString());
        
        m_pSpriteMyHpBar->setTextureRect(CCRectMake(0, 0, (float)m_dwCurMyTeamHP / FightAI::Get()->getMyTeam()->GetTeamHpMax() * myhpBarWidth / m_pSpriteMyHpBar->getScaleX(), getHeight(m_pSpriteMyHpBar) / m_pSpriteMyHpBar->getScaleY()));
        
        mapPetCtrl[wBattleIndex]->loseHP(pSprite->getCurHP());
    }
    else
    {
        //如果是boss掉血}
        if (wBattleIndex == m_wBossIndex) {
            m_pSpriteBossHpBar->setTextureRect(CCRectMake(0, 0, (float)pSprite->getCurHP() / pSprite->getMaxHp() * bosshpBarWidth / m_pSpriteBossHpBar->getScaleX(), getHeight(m_pSpriteBossHpBar) / m_pSpriteBossHpBar->getScaleY()));
        }
    }
}

void CcbWorldBossFightLayer::addHp(uint16 wBattleIndex, int hp)
{
    FightPetSprite *pSprite = mapPetSprite[wBattleIndex];
    
    hp = pSprite->addHP(hp);
    //加血的是我方}
    if (wBattleIndex <= PetCnt) {
        m_dwCurMyTeamHP = m_dwCurMyTeamHP + hp;
        if (m_dwCurMyTeamHP > FightAI::Get()->getMyTeam()->GetTeamHpMax())
        {
            m_dwCurMyTeamHP = FightAI::Get()->getMyTeam()->GetTeamHpMax();
        }
        
        CCString *str = CCString::createWithFormat("%d", m_dwCurMyTeamHP);
        m_pLabelTTFMyCurHP->setString(str->getCString());
        
        m_pSpriteMyHpBar->setTextureRect(CCRectMake(0, 0, (float)m_dwCurMyTeamHP / FightAI::Get()->getMyTeam()->GetTeamHpMax() * myhpBarWidth / m_pSpriteMyHpBar->getScaleX(), getHeight(m_pSpriteMyHpBar) / m_pSpriteMyHpBar->getScaleY()));
        
        mapPetCtrl[wBattleIndex]->loseHP(pSprite->getCurHP());
    }
    else
    {
        
        //如果是boss加血}
        if (wBattleIndex == m_wBossIndex) {
            m_pSpriteBossHpBar->setTextureRect(CCRectMake(0, 0, (float)pSprite->getCurHP() / pSprite->getMaxHp() * bosshpBarWidth / m_pSpriteBossHpBar->getScaleX(), getHeight(m_pSpriteBossHpBar) / m_pSpriteBossHpBar->getScaleY()));
        }
    }
}

void CcbWorldBossFightLayer::showDeadEff(uint16 wBattleId){
    
    FightPetSprite* mc = getFightPetSprite(wBattleId);
    
    CCParticleSystemQuad* eff = CCParticleSystemQuad::create("effect/eff_526.plist");
    eff->setScale(0.5);
    eff->setPosition(mc->getMyPos() + ccp(0, mc->getStandSize().height*0.5));
    m_pLayerAllBg->addChild(eff, mc->getZOrder() + 1);
    
    eff->runAction(CCSequence::create(CCDelayTime::create(1.5),
                                      CCHide::create(),
                                      CCCallFuncN::create(this, callfuncN_selector(CcbWorldBossFightLayer::removeDeadEff)),
                                      NULL));
    
    
}

void CcbWorldBossFightLayer::removeDeadEff(CCNode* node)
{
    if (node) {
        node->removeFromParentAndCleanup(true);
    }
}

//用于判断死亡}
void CcbWorldBossFightLayer::updateForChkDead(float time)
{
    if (m_isPauseAll) {
        return;
    }
    
    for (int i = 1; i <= PetCnt; i++) {
        FightPetSprite *pSprite = mapPetSprite[i];
        //        FightPet* pet = FightAI::Get()->getFightPetByBIndex(i + 100);
        if (!pSprite) {
            continue;
        }
        if (pSprite->getCurHP() > 0) {
            continue;
        }
        if (pSprite->getDeadTime() <= 0) {
            continue;
        }
        pSprite->setDeadTime(pSprite->getDeadTime()-1);
        //        CCLog("@@@@@@@@ %d: ",pSprite->getDeadTime());
        if (pSprite->getDeadTime() == 0) {
            pSprite->setIsDead(true);
        }
    }
    
    for (int i = 1; i <= PetCnt; i++) {
        FightPetSprite *pSprite = mapPetSprite[i + 100];
        //        FightPet* pet = FightAI::Get()->getFightPetByBIndex(i + 100);
        if (!pSprite) {
            continue;
        }
        if (pSprite->getCurHP() > 0) {
            continue;
        }
        if (pSprite->getDeadTime() <= 0) {
            continue;
        }
        pSprite->setDeadTime(pSprite->getDeadTime()-1);
        //        CCLog("@@@@@@@@ %d: ",pSprite->getDeadTime());
        if (pSprite->getDeadTime() == 0) {
            pSprite->setIsDead(true);
        }
    }
}

void CcbWorldBossFightLayer::eatDropThing()
{
    waitTime = 20;
    schedule(schedule_selector(CcbWorldBossFightLayer::waitToEatDrop));
}

//物品飞动}
void CcbWorldBossFightLayer::callBackItemFly(cocos2d::CCNode* node)
{
    waitTime = 20;
    STC_ITEM_DROP item = ((DropItemSprite*)node)->getItem();
    CCString *str = NULL;
    //    int hp = 0;
    //    int x = 0;
    switch (item.wItemType / E_UNITE_BASE_FABIO) {
        case E_UNITE_TYPE_SPECIAL:
            switch (item.wItemType % E_UNITE_BASE_FABIO) {
                case E_SPECIAL_ID_HEART:
                    //item.wHasCount保存的是吃这个心珠的宠物fightId}
                    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_heart_heal));
                    addHp(item.wHasCount, item.wCount);
                    str = CCString::createWithFormat("%d", item.wCount);
                {
                    FightPetSprite *pet = mapPetSprite[item.wHasCount];
                    if (pet) {
                        ShowPetBattleWord::showWord(str->getCString(), E_WORD_TYPE_HP, ccp(pet->getMyPos().x, pet->getMyPos().y + pet->getStandSize().height*0.5), m_pLayerAllBg);
                    }
                    
                }
                    break;
                default:
                    break;
            }
        default:
            
            break;
    }
    node->removeFromParentAndCleanup(true);
}

//等待吃物品结束}
void CcbWorldBossFightLayer::waitToEatDrop(float time)
{
    if (m_isPauseAll) {
        return;
    }
    
    if (waitTime > 0) {
        waitTime--;
        return;
    }
    unschedule(schedule_selector(CcbWorldBossFightLayer::waitToEatDrop));
    //    if (itemCounter <= 0) {
    //清空掉落的物品图片}
    std::map<uint32, std::vector<DropItemSprite*> >::iterator it = mapDropSprite.begin();
    for (; it != mapDropSprite.end(); it++) {
        it->second.clear();
    }
    mapDropSprite.clear();
    //    }
    roundEnd();
}

void CcbWorldBossFightLayer::updateWaitForFight(float time)
{
    if (m_isPauseAll) {
        return;
    }
    
    if (arrSkillWait.size() > 0) {
        return;
    }
    
    for (int i = 0; i < arrLianxieWait.size(); i++) {
        arrLianxieWait[i].wcurFrame++;
        if (arrLianxieWait[i].wcurFrame != arrLianxieWait[i].wStartFrame) {
            continue;
        }
        startBattle(arrLianxieWait[i]);
    }
}
//技能等待中的战斗包计时}
void CcbWorldBossFightLayer::updateForSkillWaitBattle(float time)
{
    for (int i = 0; i < arrSkillWait.size(); i++) {
        STC_WAIT_BATTLE wait = arrSkillWait[i];
        if (wait.wcurFrame <= 0) {
            continue;
        }
        wait.wcurFrame--;
        arrSkillWait[i] = wait;
        
        if (wait.wcurFrame == 0) {
            //如果是自动战斗，判断是否释放技能}
            //            uint32 skillId = wait.skillId;
            CCLog("敌阵营 延迟攻击~~~~~~~~~~ %d", wait.bData.wBattleIndex);
            startBattle(wait);
        }
    }
}
/*
 uint16 错误码， 0, 表示成功，不为0是错误码}
 
 uint8 战斗类型，0，
 
 uint16 wPhoto 己方玩家头像
 uint16 wPhoto 敌方玩家头像
 
 string 我方名字
 uint8 我方队伍 ID
 uint32 我方队伍血量 最大值
 uint8 我方参加战斗宠物个数
 uint8  宠物战斗Id FightId
 uint16 宠物Id PetId
 uint8  宠物等级 PetLv
 uint32 宠物当前血量
 uint32 宠物血量最大值
 uint8  宠物属性
 uint8  宠物类型
 uint8  主动技能冷却值				// new add}
 string 敌方名字
 uint8 敌方队伍 ID
 uint32 敌方队伍血量 最大值
 uint8 敌方方参加战斗宠物个数
 uint8  宠物战斗Id FightId
 uint16 宠物Id PetId
 uint8  宠物等级 PetLv
 uint32 宠物当前血量
 uint32 宠物血量最大值
 uint8  宠物属性
 uint8  宠物类型
 uint8  主动技能冷却值				// new add}
 
 uint8 战斗结果，0，负，1，胜
 uint8 战斗回合数 RoundCnt
 uint8 队伍 size
 uint8 队伍出手 队伍  ID
 uint8 队伍中宠物总个数（按照出手先手顺序排序）
 uint8 攻击宠物战斗Id FightId
 uint8 触发战斗前被动技能 size
 uint16 技能Id
 uint8 buf标志 size
 uint16 buf标志位
 
 uint8 队伍 size
 uint8 队伍出手 队伍  ID  // TeamId}
 
 uint8 队伍中宠物总个数（按照出手先手顺序排序）
 uint16 出手帧数//Team}
 uint8 攻击宠物战斗Id FightId
 uint8 buf标志 size
 uint16 buf标志位
 uint8 bIs连击
 uint8 攻击结果（0 不能出手 ，1，命中）
 uint16 攻击宠物释放的技能 wSpellId      0 普通攻击; 非零 技能攻击
 
 uint8 bySize 对本队伍加Effect 和Buff	 // add}
 uint8 byTeamType 队伍Id				 // add}
 uint8 byFightId  战斗位置ID			//  add}
 uint8 触发 Effect标志 size			//  add}
 uint16 触发 Effect标志位		//  add}
 int32  血量更改值				//  add}
 uint32 宠物血量						//  add}
 uint32 团队血量						//  add}
 
 uint16 被动技能ID       // add}
 uint8 触发被动技能size  // delete}
 uint16 被动技能ID   // delete}
 
 uint8 防御宠物的个数 TargetCnt
 uint8 防御宠物战斗组 ID
 uint8 防御宠物战斗Id FightId
 
 uint8 触发 Effect标志 size  // add}
 uint16 触发 Effect标志位  // add}
 int32  血量更改值  // add}
 uint32 宠物血量  // add}
 uint32 团队血量  // add}
 
 int32 伤害值，大于0，扣血，小于0，加血
 uint8 是否　Spark
 uint8 标志位，是否暴击
 
 uint16 吸血EFFECT Index  // add}
 int	   吸取血量   // add}
 
 uint32 防御宠物当前血量
 uint32 防御队伍血量
 uint8 buf标志位 size
 uint16 buf标志位
 uint16 掉落心珠数量
 
 uint32 心珠数量
 uint32 血量回复
 uint32 战队血量
 
 uint8 队伍中宠物总个数（按照出手先手顺序排序）update buf
 uint8 攻击宠物战斗Id FightId
 uint8 buf标志 size
 uint16 buf type
 int32 Buf伤害
 uint32 当前血量
 uint32 战队血量
 
 uint8 buf标志 size
 uint16 buf type
 uint8 技能能量值
 
 */
void CcbWorldBossFightLayer::handlerPVPInfo(WorldPacket &packet)
{    

    uint8 byFightResult;//战斗结果，0，负，1，胜}
    uint8 byRoundCnt;
    
    packet >> byFightResult;
    packet >> byRoundCnt;
    m_ArenaData.isWin = byFightResult;
    m_ArenaData.byRoundCnt = byRoundCnt;
    
    for (int i = 0; i < byRoundCnt; i++) {
        //攻击人数
        uint8 byTeamSize;
        packet >> byTeamSize;
        STC_BATTLE_ROUND round1;
        for (int k = 0; k < byTeamSize; k++) {
            //攻击者
            uint8 wFightId;
            uint8 byPassSize;
            packet >> wFightId;
            packet >> byPassSize;
            //攻击前触发被动技能
            std::vector<STC_TRIGGERED_PSKILL> arrPass;
            for(int pS = 0; pS < byPassSize; pS++)
            {
                STC_TRIGGERED_PSKILL pass;
                uint32 wPassIndex;
                packet >> wPassIndex;
                pass.wSkillIndex = wPassIndex;
                pass.fightId = wFightId;
                uint8 effSize;
                packet >> effSize;
                STC_PET_EFF_BY_PSKILL myEff;
                for (int eS = 0; eS < effSize; ++eS) {
                    STC_EFFECT eff;
                    uint32 effId;
                    int effValue;
                    packet >> effId;
                    packet >> effValue;
                    eff.wEffId = effId;
                    eff.dwValue = effValue;
                    myEff.fightId = wFightId;
                    myEff.arrEff.push_back(eff);
                }
                pass.arrMyEffsAndBuff.push_back(myEff);
                arrPass.push_back(pass);
            }
            
            //攻击前buff
            uint8 byBuffSize;
            packet >> byBuffSize;
            std::vector<STC_BUFF> arrBuff;
            for (int bS = 0; bS < byBuffSize; bS++) {
                uint32 wBuffId;
                uint8 byIsNew;
                packet >> wBuffId;
                packet >> byIsNew;
                STC_BUFF buff;
                buff.wBuffId = wBuffId;
                buff.isNew = byIsNew;
                arrBuff.push_back(buff);
            }
            uint32 curHp;//宠物血量}
            uint32 curTeamHp;//队伍血量}
            packet >> curHp;
            packet >> curTeamHp;
            round1.mapBeforePass[wFightId] = arrPass;
            round1.mapBeforeBuff[wFightId] = arrBuff;
        }
        
        packet >> byTeamSize;
        
        //回合后各宠物的血量}
        std::map<uint16, uint32> mapAfterHp;
        mapAfterHp.clear();
        for (int k = 0; k < byTeamSize; k++) {
            
            uint8 byFightId;
            
            packet >> byFightId;
            STC_WAIT_BATTLE waitBattle;
            
            uint8 bySeqSize;// 连协个数}
            packet >> bySeqSize;
            std::vector<uint32> arrLianxieId;
            for (int seq = 0; seq < bySeqSize; seq++) {
                uint8 byLianxieId;
                packet >> byLianxieId;
                arrLianxieId.push_back(byLianxieId);
            }
            uint16 wLianxieAdd;
            packet >> wLianxieAdd;
            waitBattle.arrLianxieId = arrLianxieId;
            waitBattle.wLianxieAdd = wLianxieAdd;
            
            uint8 byBuffSize;
            packet >> byBuffSize;
            
            waitBattle.wStartFrame = 0;//1 + j * delayFrame;
            waitBattle.wcurFrame = 0;
            
            waitBattle.bData.wBattleIndex = byFightId;
            
            std::map<uint8,  std::vector<STC_BUFF> > mapMyBuff;
            std::vector<STC_BUFF> arrMyBuff;
            for (int bS = 0; bS < byBuffSize; bS++) {
                uint32 wBuffId;
                uint8 byIsNew;
                packet >> wBuffId;
                packet >> byIsNew;
                STC_BUFF buff;
                buff.wBuffId = wBuffId;
                buff.isNew = byIsNew;
                arrMyBuff.push_back(buff);
                
            }
            mapMyBuff[1] = arrMyBuff;
            uint8 bIsDouble;
            uint8 bAttResult;//（0 不能出手 ，1，命中）}
            uint32 wSpellId;//      0 普通攻击; 非零 技能攻击}
            packet >> bIsDouble;
            packet >> bAttResult;//（0 不能出手 ，1，命中）}
            if (bAttResult == 0) {
                continue;
            }
            packet >> wSpellId;//      0 普通攻击; 非零 技能攻击}
            
            waitBattle.bData.wSkillId = wSpellId;
            
            
            uint8 byToMySize;// 对本队伍加Effect 和Buff	 // add}
            packet >> byToMySize;
            for (int i = 0; i < byToMySize; i++) {
                uint8 byTeamType;// 队伍Id				 // add}
                uint8 byFightId;//  战斗位置ID			//  add}
                packet >> byTeamType;
                packet >> byFightId;
                STC_ATTACK_DATA attData;
                attData.dwAllDamage = 0;
                attData.wEnemyIndex = byFightId;
                uint8 byEffSize;//触发 Effect标志 size			//  add}
                packet >> byEffSize;
                std::vector<STC_EFFECT> arrEff;
                for (int j=0; j < byEffSize; j++) {
                    uint32 wEffId;//触发 Effect标志位		//  add}
                    int32  dwValue;//血量更改值				//  add}
                    packet >> wEffId;
                    packet >> dwValue;
                    STC_EFFECT eff;
                    eff.wEffId = wEffId;
                    eff.dwValue = dwValue;
                    arrEff.push_back(eff);
                }
                attData.arrEnemyEff = arrEff;
                
                //                    uint32 dwPetHp;//宠物血量						//  add}
                //                    uint32 dwTeamHp;//团队血量						//  add}
                //                    packet >> dwPetHp;
                //                    packet >> dwTeamHp;
                
                uint8 byBuffSize;
                packet >> byBuffSize;
                std::map<uint8, std::vector<STC_BUFF> > mapEBuff;
                std::vector<STC_BUFF> arrBuff;
                for (int j = 0; j < byBuffSize; j++) {
                    
                    STC_BUFF buff;
                    uint32 wBuffId;
                    uint8 byIsNew;
                    packet >> wBuffId;
                    packet >> byIsNew;
                    
                    buff.wBuffId = wBuffId;
                    buff.isNew = byIsNew;
                    arrBuff.push_back(buff);
                    
                }
                mapEBuff[1] = arrBuff;
                attData.arrEnemyBuff = mapEBuff;
                
                waitBattle.bData.arrAttData[attData.wEnemyIndex] = attData;
            }
            
            uint8 byEnemyCnt;
            packet >> byEnemyCnt;
            for (int enemyCnt = 0; enemyCnt < byEnemyCnt; enemyCnt++) {
                STC_ATTACK_DATA attData;
                
                uint8 byEnemyTeamId;
                uint8 wEnemyFightId;
                uint8 byIsHit;
                packet >> byEnemyTeamId;
                packet >> wEnemyFightId;
                packet >> byIsHit;
                
                attData.wEnemyIndex = wEnemyFightId;
                attData.isHit = byIsHit;
                
                //未命中}
                if (!attData.isHit) {
                    attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_BATTLE] = getTrSkillInSpecial(wEnemyFightId, packet);
                    waitBattle.bData.arrAttData[attData.wEnemyIndex] = attData;
                    waitBattle.bData.eEffObj = E_EFFECT_OBJECT_ENEMY;
                    if (abs(wEnemyFightId - waitBattle.bData.wBattleIndex) < PetCnt) {
                        waitBattle.bData.eEffObj = E_EFFECT_OBJECT_MY;
                    }
                    continue;
                }
                
                uint8 byTrSize;//被动技能触发列表}
                packet >> byTrSize;
                std::vector<STC_TRIGGERED_PSKILL> arrTrPSkill;
                for (int trS = 0; trS < byTrSize; ++trS) {
                    uint32 skillId;//被动技能 SpellId}
                    packet >> skillId;
                    
                    STC_TRIGGERED_PSKILL trSkill;
                    trSkill.wSkillIndex = skillId;
                    trSkill.fightId = byFightId;
                    
                    uint8 byMyEffS;//触发被动技能 Effect标志 size		//对自己}
                    packet >> byMyEffS;
                    std::vector<STC_EFFECT> arrMyEff;
                    for (int eS = 0; eS < byMyEffS; eS++) {
                        STC_EFFECT eff;
                        uint32 wEffId;//触发 Effect标志位}
                        int dwValue;//更改值}
                        packet >> wEffId;
                        packet >> dwValue;
                        eff.wEffId = wEffId;
                        eff.dwValue = dwValue;
                        arrMyEff.push_back(eff);
                    }
                    STC_PET_EFF_BY_PSKILL myEff;
                    myEff.fightId = byFightId;
                    myEff.arrEff = arrMyEff;
                    trSkill.arrMyEffsAndBuff.push_back(myEff);
                    
                    uint8 byEnemyEffS;//触发被动技能 Effect标志 size		//对对手}
                    packet >> byEnemyEffS;
                    std::vector<STC_EFFECT> arrEnemyEff;
                    for (int eS = 0; eS < byEnemyEffS; eS++) {
                        STC_EFFECT eff;
                        uint32 wEffId;//触发 Effect标志位}
                        int dwValue;//更改值}
                        packet >> wEffId;
                        packet >> dwValue;
                        eff.wEffId = wEffId;
                        eff.dwValue = dwValue;
                        arrEnemyEff.push_back(eff);
                    }
                    STC_PET_EFF_BY_PSKILL enymyEff;
                    enymyEff.fightId = wEnemyFightId;
                    enymyEff.arrEff = arrEnemyEff;
                    trSkill.arrEnemyEffsAndBuff.push_back(enymyEff);
                    arrTrPSkill.push_back(trSkill);
                    
                }
                attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_BIGEN] = arrTrPSkill;
                
                //主动技能对 对方的Eff}
                uint8 byEffS;
                packet >> byEffS;
                std::vector<STC_EFFECT> arrEnemyEff;
                for (int eS = 0; eS < byEffS; eS++) {
                    STC_EFFECT eff;
                    uint32 wEffId;
                    int dwValue;
                    packet >> wEffId;
                    packet >> dwValue;
                    eff.wEffId = wEffId;
                    eff.dwValue = dwValue;
                    arrEnemyEff.push_back(eff);
                }
                attData.arrEnemyEff = arrEnemyEff;
                
                int32 dwDamage;//大于0，扣血，小于0，加血}
                uint8 isSpark;
                uint8 byRegulateState;
                uint8 isCrit;
                uint32 dwEnPetHP;
                uint32 dwEnTeamHP;
                
                packet >> dwDamage;//大于0，扣血，小于0，加血}
                //                    if (dwDamage < 0) {
                //                        CCLog("");
                //                    }
                packet >> isSpark;
                packet >> byRegulateState;
                packet >> isCrit;
                
                attData.regulateState = byRegulateState;
                attData.isSpark = isSpark;
                attData.isCrit = isCrit;
                attData.dwAllDamage = dwDamage;
                
                arrTrPSkill.clear();
                if (attData.isCrit) {
                    std::vector<STC_TRIGGERED_PSKILL> arrSkill = getTrSkillInSpecial(wEnemyFightId, packet);
                    for (int s = 0; s < arrSkill.size(); ++s) {
                        if (arrSkill[s].wSkillIndex) {
                            arrTrPSkill.push_back(arrSkill[s]);
                        }
                    }
                }
                
                
                uint32 wBloodEffId;// 吸血EFFECT Index  // add}
                int	   dwBloodValue;//吸取血量   // add}
                packet >> wBloodEffId;
                packet >> dwBloodValue;
                if (wBloodEffId != 0 && dwBloodValue != 0) {
                    STC_EFFECT bloodEff;
                    bloodEff.wEffId = wBloodEffId;
                    bloodEff.dwValue = dwBloodValue;
                    attData.arrMyEff.push_back(bloodEff);
                }
                
                packet >> dwEnPetHP;
                packet >> dwEnTeamHP;
                mapAfterHp[wEnemyFightId] = dwEnPetHP;
                attData.dwEnemyAllHp = dwEnTeamHP;
                
                bool isHurt;
                bool isDead;
                packet >> isHurt;
                if (isHurt) {
                    //受伤触发}
                    std::vector<STC_TRIGGERED_PSKILL> arrSkill = getTrSkillInSpecial(wEnemyFightId, packet);
                    for (int s = 0; s < arrSkill.size(); ++s) {
                        if (arrSkill[s].wSkillIndex) {
                            arrTrPSkill.push_back(arrSkill[s]);
                        }
                    }
                }
                attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_BATTLE] = arrTrPSkill;
                
                arrTrPSkill.clear();
                packet >> isDead;
                if (isDead) {
                    //杀死触发}
                    std::vector<STC_TRIGGERED_PSKILL> arrSkill = getTrSkillInSpecial(wEnemyFightId, packet);
                    for (int s = 0; s < arrSkill.size(); ++s) {
                        if (arrSkill[s].wSkillIndex) {
                            arrTrPSkill.push_back(arrSkill[s]);
                        }
                    }
                    
                    //死亡触发}
                    std::vector<STC_TRIGGERED_PSKILL> arrKillSkill = getTrSkillInSpecial(wEnemyFightId, packet);
                    for (int s = 0; s < arrKillSkill.size(); ++s) {
                        if (arrSkill[s].wSkillIndex) {
                            arrTrPSkill.push_back(arrKillSkill[s]);
                        }
                    }
                }
                attData.mapPassiveSkill[E_PASSIVE_SHOW_TIME_DEAD] = arrTrPSkill;
                
                
                uint8 byBuffSize;
                packet >> byBuffSize;
                std::map<uint8, std::vector<STC_BUFF> > mapEnemyBuff;
                std::vector<STC_BUFF> arrEnemyBuff;
                for (int bS = 0; bS < byBuffSize; bS++) {
                    uint32 wBuffId;
                    uint8 byIsNew;
                    packet >> wBuffId;
                    packet >> byIsNew;
                    STC_BUFF buff;
                    buff.wBuffId = wBuffId;
                    buff.isNew = byIsNew;
                    
                    arrEnemyBuff.push_back(buff);
                }
                mapEnemyBuff[1] = arrEnemyBuff;
                
                attData.arrEnemyBuff = mapEnemyBuff;
                
                attData.arrDamage = makeCombo(attData.dwAllDamage, waitBattle.bData.wBattleIndex, waitBattle.bData.wSkillId);
                
                //掉落的心珠}
                uint16 wHeartCnt;
                packet >> wHeartCnt;
                for (int hS = 0; hS < wHeartCnt; hS++) {
                    STC_ITEM_DROP item ;
                    item.wItemType = E_UNITE_BASE_FABIO * E_UNITE_TYPE_SPECIAL + E_SPECIAL_ID_HEART;
                    item.wCount = 1;
                    attData.arrItems.push_back(item);
                }
                uint8 curPower;
                packet >> curPower;
                attData.curPower = curPower;
                waitBattle.bData.arrAttData[attData.wEnemyIndex] = attData;
                waitBattle.bData.eEffObj = E_EFFECT_OBJECT_ENEMY;
                if (abs(wEnemyFightId - waitBattle.bData.wBattleIndex) < PetCnt) {
                    waitBattle.bData.eEffObj = E_EFFECT_OBJECT_MY;
                }
            }
            uint8 curPower;
            packet >> curPower;
            uint32 dwCurHp;//攻击者血量}
            uint32 dwCurTeamHp;//攻击者队伍血量}
            packet >> dwCurHp;
            packet >> dwCurTeamHp;
            mapAfterHp[byFightId] = dwCurHp;
            
            
            waitBattle.dwTeamHP = dwCurTeamHp;
            //            round1.dwMyAllHp = dwCurTeamHp;
            
            waitBattle.bData.curPower = curPower;
            
            round1.arrWaitBattle.push_back(waitBattle);
        }
        
        
        //buff生效}
        std::map<uint16, std::vector<STC_BUFF_VALUE> > mapAfterBuffValue;
        //回合结束时buff}
        std::map<uint16, std::vector<STC_BUFF> > mapAfterBuff;
        //回合后吃到的心珠}
        std::map<uint16, STC_EAT_HEART> mapEatHeart;
        //回合后各宠物的必杀值}
        std::map<uint16, uint16> mapAfterPower;
        
        uint8 bySize;
        packet >> bySize;
        for (int fS = 0; fS < bySize; fS++) {
            uint8 byFightId;
            packet >> byFightId;
            
            uint8 eatHeartCnt; //吃心珠的数量}
            uint32 reValue; //回复力值}
            uint32 heartValue; //心珠回复量}
            uint32 dwPetHP;
            uint32 dwTeamHP;
            
            packet >> eatHeartCnt;
            packet >> reValue;
            packet >> heartValue;
            STC_EAT_HEART eat;
            eat.cnt = eatHeartCnt;
            eat.dwValue = heartValue;
            
            mapEatHeart[byFightId] = eat;
            
            
            packet >> dwPetHP;
            packet >> dwTeamHP;
            
            uint8 byBuffSize;
            packet >> byBuffSize;
            std::vector<STC_BUFF_VALUE> arrBuffValue;
            for (int bS = 0; bS < byBuffSize; bS++) {
                uint32 byBuffType;
                int32 dwValue;
                packet >> byBuffType;
                packet >> dwValue;
                STC_BUFF_VALUE buff;
                buff.byBuffType = byBuffType;
                buff.dwValue = dwValue;
                arrBuffValue.push_back(buff);
            }
            mapAfterBuffValue[byFightId] = arrBuffValue;
            //                uint32 dwPetHP;
            //                uint32 dwTeamHP;
            packet >> dwPetHP;
            packet >> dwTeamHP;
            mapAfterHp[byFightId] = dwPetHP;
            
            if (byFightId <= PetCnt) {
                round1.dwMyAllHp = dwTeamHP;
            }
            else {
                round1.dwEnemyAllHp = dwTeamHP;
            }
            
            
            packet >> byBuffSize;
            std::vector<STC_BUFF> arrBuff;
            for (int bS = 0; bS < byBuffSize; bS++) {
                uint32 wBuffId;
                uint8 byIsNew;
                packet >> wBuffId;
                packet >> byIsNew;
                STC_BUFF buff;
                buff.wBuffId = wBuffId;
                buff.isNew = byIsNew;
                arrBuff.push_back(buff);
            }
            mapAfterBuff[byFightId] = arrBuff;
            
            uint8 byPower;
            packet >> byPower;
            mapAfterPower[byFightId] = byPower;
        }
        round1.mapAfterBuffValue = mapAfterBuffValue;
        round1.mapAfterBuff = mapAfterBuff;
        round1.mapAfterBuff = mapAfterBuff;
        round1.mapAfterPower = mapAfterPower;
        round1.mapEatHeart = mapEatHeart;
        //            round1.byAttacker = byTeamId;
        round1.mapAfterHp = mapAfterHp;
        
        m_ArenaData.arrRound.push_back(round1);
        
    }
    
}

std::vector<STC_TRIGGERED_PSKILL> CcbWorldBossFightLayer::getTrSkillInSpecial(uint16 wBattleId, WorldPacket &packet)
{
    std::vector<STC_TRIGGERED_PSKILL> arrTrSkill;
    bool isTrig;
    packet >> isTrig;
    if (!isTrig) {
        return arrTrSkill;
    }
    STC_TRIGGERED_PSKILL trSkill;
    uint32 dwSpellId;
    uint8 bySize;// 队伍}
    packet >> dwSpellId;
    packet >> bySize;
    
    trSkill.wSkillIndex = dwSpellId;
    trSkill.fightId = wBattleId;
    
    
    for (int sS = 0; sS < bySize; ++sS) {
        
        uint8 wFightId;//攻击宠物战斗Id FightId}
        uint8 efSize;//触发 Effect标志 size}
        packet >> wFightId;
        packet >> efSize;
        STC_PET_EFF_BY_PSKILL mySkill;
        mySkill.fightId = wFightId;
        
        for (int eS = 0; eS < efSize; ++eS) {
            uint32 effId;//触发 Effect标志位}
            int32  effValue;//更改值}
            packet >> effId;
            packet >> effValue;
            
            STC_EFFECT eff;
            eff.wEffId = effId;
            eff.dwValue = effValue;
            mySkill.arrEff.push_back(eff);
        }
        
        uint8 byBuffSize;
        packet >> byBuffSize;
        std::vector<STC_BUFF> arrBuff;
        for (int bS = 0; bS < byBuffSize; bS++) {
            uint32 wBuffId;
            uint8 byIsNew;
            packet >> wBuffId;
            packet >> byIsNew;
            STC_BUFF buff;
            buff.wBuffId = wBuffId;
            buff.isNew = byIsNew;
            arrBuff.push_back(buff);
        }
        mySkill.arrBuff[1] = arrBuff;
        
        if (abs(wFightId - wBattleId) > PetCnt) {
            trSkill.arrEnemyEffsAndBuff.push_back(mySkill);
        }
        else
        {
            trSkill.arrMyEffsAndBuff.push_back(mySkill);
        }
        
        uint32 dwCurHp;//血量}
        uint32 dwCurTeamHp;//队伍血量}
        packet >> dwCurHp;
        packet >>dwCurTeamHp;
    }
    
    
    return arrTrSkill;
}

std::map<uint16, STC_FRAME_DAMAGE> CcbWorldBossFightLayer::makeCombo(int& allDamage, uint16 fightId, uint32 skillId )
{
    std::map<uint16, STC_FRAME_DAMAGE> arrDam;
    int realDamege = 0;
    
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(fightId);
    if (!pet) {
        return arrDam;
    }
    
    PetConfig::STC_PET_CONFIG *petConfig = GET_CONFIG_STC(PetConfig, pet->getPetInfo().wPetIndexId);
    if (!petConfig) {
        return arrDam;
    }
    int comboid = petConfig->wComboId;
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *skill = GET_CONFIG_STC(UltimateSkillConfig, skillId);
    if (skill && skill->byType == 1) {
        if (skill->byEffectObj == E_EFFECT_OBJECT_MY) {
            return arrDam;
        }
        comboid = skill->wComboid;
    }
    
    ComboIdConfig::STC_COMBOID_CONFIG *stcCombo = GET_CONFIG_STC(ComboIdConfig, comboid);
    
    do {
        if (!stcCombo) {
            break;
        }
        int len;
        //当攻击不破防时，只能打出1点伤害，这时总伤害是1点，计算combo时，每次combo也是1点伤害}
        //如此会导致显示的伤害比实际总伤害要大一点点，所以就要调整计算的总伤害了}
        GET_ARRAY_LEN(stcCombo->dwComboPer, len);
        int lastFrame = 0;
        int lastDamege = allDamage;
        for (int i = 0; i < len; i++) {
            if (!stcCombo->dwComboTime[i]) {
                break;
            }
            STC_FRAME_DAMAGE damage;
            damage.wFrame = stcCombo->dwComboTime[i];
            int dam = stcCombo->dwComboPer[i] * allDamage / 1000;
            
            if (dam <= 0)
            {
                dam = 1;
            }
            
            damage.dwDamege = dam;
            
            lastFrame = damage.wFrame;
            lastDamege -= damage.dwDamege;
            realDamege += damage.dwDamege;
            arrDam[damage.wFrame] = damage;
        }
        //调整误差，最后一次的伤害不按照配比计算了，用总伤害减去前面的所有伤害取得}
        if (arrDam.find(lastFrame) != arrDam.end() && lastDamege > 0 ) {
            arrDam[lastFrame].dwDamege += lastDamege;
            realDamege += lastDamege;
        }
    } while (0);
    if (allDamage != realDamege) {
        allDamage = realDamege;
    }
    return arrDam;
}

#pragma mark Action

//我方进场动画}
void CcbWorldBossFightLayer::petInEff()
{
    std::map<uint16, FightPetSprite*>::iterator it = mapPetSprite.begin();
    for (; it != mapPetSprite.end(); it++) {
        if (it->second) {
            it->second->showRunIn();
        }
        
        FightPet* fPet = FightAI::Get()->getFightPetByBIndex(it->first);
        if (!fPet) {
            continue;
        }
        if(fPet->getCurPower() > 0)
        {
            setPower(it->first, fPet->getCurPower());
            it->second->showLeaderEff();
        }
    }
}

//怪进入场景}
void CcbWorldBossFightLayer::enemyRunIn()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    for (int i = 101; i <= 100 + PetCnt; i++) {
        if (mapPetSprite.find(i) == mapPetSprite.end()) {
            continue;
        }
        FightPetSprite *mc = mapPetSprite[i];
        if (!mc) {
            continue;
        }
        float posX = mc->getPositionX();
        mc->setPositionX(winSize.width + 50);
        mc->setVisible(true);
        mc->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(posX, mc->getPositionY())),
                                         NULL));
    }
}

//显示队长技能动画}
void CcbWorldBossFightLayer::showLeaderSkillLayer()
{
    //刚开始战斗时播放队长特效}
    for (int i = 1; i <= PetCnt; i++) {
        FightPet* fPet = FightAI::Get()->getFightPetByBIndex(i);
        if (!fPet) {
            continue;
        }
        if(fPet->getCurPower() > 0)
        {
            setPower(i, fPet->getCurPower());
            mapPetSprite[i]->showLeaderEff();
        }
    }
}

//显示战斗开始动画}
float  CcbWorldBossFightLayer::showFightStartEff()
{
    ShowPetBattleWord::showTextWord(E_WORD_TYPE_FIGHT_START, ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) - fRealHeight*0.5), m_pLayerAllBg);
    
    float time = 1.0;
    this->runAction(CCSequence::create(CCDelayTime::create(time),
                                       CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::petInEff)),
                                       CCDelayTime::create(1.2),
                                       CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::showLeaderSkillLayer)),
                                       NULL));
    
    return time + 1.2 + 1.0;
}
//显示主动技能动画}
void CcbWorldBossFightLayer::showSkillLayer(uint16 wBattleId, uint32 dwSkillId)
{
    if (wBattleId <= PetCnt) {
        if (!m_skillBgLayer) {
            m_skillBgLayer = CcbManager::sharedManager()->LoadCcbBattleSkillBgLayer(this);
            m_skillBgLayer->setPosition(ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) - fRealHeight*0.5));
            m_skillBgLayer->ignoreAnchorPointForPosition(false);
            m_skillBgLayer->setAnchorPoint(ccp(0.5, 0.5));
            m_pLayerAllBg->addChild(m_skillBgLayer, 10);
        }
        
        
        FightPet* pet = FightAI::Get()->getFightPetByBIndex(wBattleId);
        if (!m_skillLayer) {
            m_skillLayer = CcbManager::sharedManager()->LoadCcbAltSkillEffLayer();
            CcbAltSkillEffLayer *layer = dynamic_cast<CcbAltSkillEffLayer*>(m_skillLayer);
            layer->setPosition(ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) - fRealHeight*0.5));
            layer->ignoreAnchorPointForPosition(false);
            layer->setAnchorPoint(ccp(0.5, 0.5));
            layer->setDelegate(this);
            layer->setPetId(pet->getPetInfo().wPetIndexId, dwSkillId);
            m_pLayerAllBg->addChild(layer, E_ZORDER_ALT_SKILL_EFF);
        }
    }
    else
    {
        UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *ultCfg = GET_CONFIG_STC(UltimateSkillConfig, dwSkillId);
        if (ultCfg) {
            showEnemyUltSkill(ultCfg->strName);
            return;
        }
    }
    
}
//显示怪的主动技能}
void CcbWorldBossFightLayer::showEnemyUltSkill(std::string strName)
{
    m_pLabelTTFEnemyAltName->setString(strName.c_str());
    m_pSpriteEnemyAltBg->runAction(CCSequence::create(CCShow::create(),
                                                      CCDelayTime::create(2),
                                                      CCHide::create(),
                                                      NULL));
}

//等待所有死亡的怪消失后，进入下一回合}
void CcbWorldBossFightLayer::updateForChange(float time)
{
    if (m_isPauseAll) {
        return;
    }
    
    //1、不管我方敌方，只要有已死亡但未消失的，则false，否则true结束}
    bool myHide = true;
    bool enemyHide = true;
    for (int i = 1; i <= PetCnt; i++) {
        FightPetSprite *pSprite = mapPetSprite[i];
        if (pSprite && pSprite->getIsDead()) {
            if (!pSprite->isHide()) {
                myHide = false;
            }
        }
        
        FightPetSprite *pSpriteE = mapPetSprite[i + 100];
        if (pSpriteE && pSpriteE->getIsDead()) {
            if (!pSpriteE->isHide()) {
                enemyHide = false;
            }
        }
        
    }
    
    if (myHide && enemyHide) {
        unschedule(schedule_selector(CcbWorldBossFightLayer::updateForChange));
        
        roundStart();
    }
}
#pragma mark show passive skill

//屏幕抖动}
void CcbWorldBossFightLayer::doShake()
{
    if (m_isShake) {
        if (m_actShake && !m_actShake->isDone()) {
            m_actShake->setDuration(0.1);
            return;
        }
    }
    m_actShake = CCShake::create(0.1, 10);
    m_isShake = true;
    m_pSpriteNearMap->runAction(CCSequence::create(m_actShake,
                                                   CCCallFunc::create(this, callfunc_selector(CcbWorldBossFightLayer::callBackShake)),
                                                   NULL));
}

//屏幕抖动回调}
void CcbWorldBossFightLayer::callBackShake()
{
    m_actShake = NULL;
    m_isShake = false;
}





