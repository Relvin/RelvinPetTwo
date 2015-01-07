#include "CcbPetBattleLayer.h"
#include "CcbManager.h"
#include "FightPetSprite.h"
#include "FightTeam.h"
#include "FightAI.h"
#include "CcbPetBattleCtrl.h"
#include "UISupport.h"
#include "ShowPetBattleWord.h"
#include "ConfigGet.h"
#include "DropItemSprite.h"
#include "ResourcePic.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "CcbFightRewardLayer.h"
#include "StageScene.h"
#include "MapScene.h"
#include "ConfigUtil.h"
#include "ResourceDefine.h"
#include "PetCtrl.h"
#include "CcbAltSkillEffLayer.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"
#include "Role.h"

#include "TeamCtrl.h"
#include "Team.h"
#include "Pet.h"
#include "CcbLeaderSkillEffLayer.h"
#include "EffectLayer.h"
#include "GuideData.h"
#include "CcbPetBattleHpBarLayer.h"

#include "CcbSystemBootLose.h"
#include "TowerDataMgr.h"
#include "ChallengeDataMgr.h"
#include "Support.h"
#include "ArmatureManager.h"
#include "CcbPetBattleBossLayer.h"

//#include "CcbPetBattleLoading.h"
#include "PadDefine.h"
#include <algorithm>
#include "AppDelegate.h"

#include "AnalysicsManager.h"
#include "GlobalData.h"
#include "CheckPointMgr.h"
#include "FlyTextLayer.h"
#include "GuideBtnPos.h"
#include "ResourceStringClient.h"

PetBattleScene::PetBattleScene()
{
    
}
PetBattleScene::~PetBattleScene()
{
    
}
CCScene* PetBattleScene::scene()
{
    CCScene *scene = CCScene::create();
    
    PetBattleScene *layer = PetBattleScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool PetBattleScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbPetBattleLayer(this));
    
    return true;
}

CcbPetBattleLayer::~CcbPetBattleLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteFarMap);
	CC_SAFE_RELEASE_NULL(m_pSpriteNearMap);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_6);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_3);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_5);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_2);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_4);
	CC_SAFE_RELEASE_NULL(m_pLayerPetBattleCtrl_1);
	CC_SAFE_RELEASE_NULL(m_pLayerPetCtrlBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteMyHpBar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMyMaxHP);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMyCurHP);
	CC_SAFE_RELEASE_NULL(m_pSpriteMyHpBg);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAutoFight);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAutoFightOff);
	CC_SAFE_RELEASE_NULL(m_pSpriteEggBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEgg);
	CC_SAFE_RELEASE_NULL(m_pSpriteSoulBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFSoul);
	CC_SAFE_RELEASE_NULL(m_pSpriteCoinBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCoin);
	CC_SAFE_RELEASE_NULL(m_pNodeNormalReward);
	CC_SAFE_RELEASE_NULL(m_pSpriteBossIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteBossNature);
	CC_SAFE_RELEASE_NULL(m_pSpriteBossHpBar);
	CC_SAFE_RELEASE_NULL(m_pLayerBossHpBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCurWave);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMaxWave);
	CC_SAFE_RELEASE_NULL(m_pLayerWaveBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCurRound);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRoundGang);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMaxRound);
	CC_SAFE_RELEASE_NULL(m_pSpriteCoinCat_RoundBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCoinCat_CurRound);
	CC_SAFE_RELEASE_NULL(m_pSpriteCoinCat_CoinBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCoinCat_Coin);
	CC_SAFE_RELEASE_NULL(m_pSpriteCoinCat_DamBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCoinCat_Damage);
	CC_SAFE_RELEASE_NULL(m_pNodeCoinCatReward);
    CC_SAFE_RELEASE_NULL(m_pLayerAllBg);
    CC_SAFE_RELEASE_NULL(m_pLayerWave);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEnemyAltName);
    CC_SAFE_RELEASE_NULL(m_pSpriteEnemyAltBg);
    CC_SAFE_RELEASE_NULL(m_pSpritePetCtrlBg);
    CC_SAFE_RELEASE_NULL(pauseActions);
    CC_SAFE_RELEASE_NULL(pauseTargets);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetBattleLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetBattleLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetBattleLayer", CcbPetBattleLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/pet_battle_ctrl.ccb]", [ccb/pet_battle_ctrl.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_scene.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CcbPetBattleLayer* CcbPetBattleLayer::m_currentScene = NULL;

bool CcbPetBattleLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_currentScene = this;
    setTouchEnabled(true);
    
	return true;
}

void CcbPetBattleLayer::menuCloseCallback(cocos2d::CCObject *pObject)
{
    failVerified();
}
void CcbPetBattleLayer::menuJiaSu(cocos2d::CCObject *pObject)
{
    if (CCDirector::sharedDirector()->getScheduler()->getTimeScale() > 1.0) {
        CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0);
        return;
    }
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(5.0);
}
void CcbPetBattleLayer::onLoseBattle() {
    FightAI::Get()->uninit();
    // 跳弹版}
    CcbSystemBootLose::showLose();
}

void CcbPetBattleLayer::failVerified()
{
    BackCtrl::JumpToScene(kStageScene);
}

void CcbPetBattleLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    Support::sharedInstance()->makeScreenAlwaysOn();
    CMusicCtrl::StopBackgroundMusic();
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Bgm_stage_normal));
    loadData();
}

void CcbPetBattleLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger < GuideData::E_GUIDE_END_TRIGGER) {

        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerPetBattleCtrl_1, GuideBtnPos::E_BIG_ONE);

        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerPetBattleCtrl_3, GuideBtnPos::E_BIG_TWO);

        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerPetBattleCtrl_5, GuideBtnPos::E_BIG_THREE);
        
        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerPetBattleCtrl_2, GuideBtnPos::E_BIG_FOUR);

        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerPetBattleCtrl_4, GuideBtnPos::E_BIG_FIVE);

        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerPetBattleCtrl_6, GuideBtnPos::E_BIG_SIX);
    }
}

void CcbPetBattleLayer::onExit()
{
    Support::sharedInstance()->makeScreenDefault();
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0);
	CCLayer::onExit();
}

void CcbPetBattleLayer::onExitTransitionDidStart()
{
    CMusicCtrl::StopBackgroundMusic();
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Bgm_main_scene));
	CCLayer::onExitTransitionDidStart();
    CCDirector::sharedDirector()->purgeCachedData();
    CCArmatureDataManager::sharedArmatureDataManager()->removeAllArmatureFileInfo();
}

// Inhert MemberVariableAssigner
bool CcbPetBattleLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFarMap", CCSprite*, this->m_pSpriteFarMap);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNearMap", CCSprite*, this->m_pSpriteNearMap);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_6", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_6);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_3", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_5", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_2", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_4", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBattleCtrl_1", CcbPetBattleCtrl*, this->m_pLayerPetBattleCtrl_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetCtrlBg", CCLayer*, this->m_pLayerPetCtrlBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMyHpBar", CCSprite*, this->m_pSpriteMyHpBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMyMaxHP", CCLabelTTF*, this->m_pLabelTTFMyMaxHP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMyCurHP", CCLabelTTF*, this->m_pLabelTTFMyCurHP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAutoFight", CCControlButton*, this->m_pControlButtonAutoFight);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAutoFightOff", CCControlButton*, this->m_pControlButtonAutoFightOff);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEggBg", CCSprite*, this->m_pSpriteEggBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEgg", CCLabelTTF*, this->m_pLabelTTFEgg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSoulBg", CCSprite*, this->m_pSpriteSoulBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSoul", CCLabelTTF*, this->m_pLabelTTFSoul);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCoinBg", CCSprite*, this->m_pSpriteCoinBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoin", CCLabelTTF*, this->m_pLabelTTFCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNormalReward", CCNode*, this->m_pNodeNormalReward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBossIcon", CCSprite*, this->m_pSpriteBossIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBossNature", CCSprite*, this->m_pSpriteBossNature);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBossHpBar", CCSprite*, this->m_pSpriteBossHpBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBossHpBg", CCLayer*, this->m_pLayerBossHpBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurWave", CCLabelTTF*, this->m_pLabelTTFCurWave);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMaxWave", CCLabelTTF*, this->m_pLabelTTFMaxWave);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerWaveBg", CCLayer*, this->m_pLayerWaveBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurRound", CCLabelTTF*, this->m_pLabelTTFCurRound);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRoundGang", CCLabelTTF*, this->m_pLabelTTFRoundGang);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMaxRound", CCLabelTTF*, this->m_pLabelTTFMaxRound);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCoinCat_RoundBg", CCSprite*, this->m_pSpriteCoinCat_RoundBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoinCat_CurRound", CCLabelTTF*, this->m_pLabelTTFCoinCat_CurRound);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCoinCat_CoinBg", CCSprite*, this->m_pSpriteCoinCat_CoinBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoinCat_Coin", CCLabelTTF*, this->m_pLabelTTFCoinCat_Coin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCoinCat_DamBg", CCSprite*, this->m_pSpriteCoinCat_DamBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoinCat_Damage", CCLabelTTF*, this->m_pLabelTTFCoinCat_Damage);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeCoinCatReward", CCNode*, this->m_pNodeCoinCatReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerAllBg", CCLayer*, this->m_pLayerAllBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerWave", CcbFightWaveLayer*, this->m_pLayerWave);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEnemyAltBg", CCSprite*, this->m_pSpriteEnemyAltBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnemyAltName", CCLabelTTF*, this->m_pLabelTTFEnemyAltName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetCtrlBg", CCSprite*, this->m_pSpritePetCtrlBg);
	return false;
}

bool CcbPetBattleLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetBattleLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_MenuHandler CcbPetBattleLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler CcbPetBattleLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAutoFight", CcbPetBattleLayer::onPressControlButtonAutoFight);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAutoFightOff", CcbPetBattleLayer::onPressControlButtonAutoFightOff);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetBattleLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "ccbresources/12monthdate/battle/CloseNormal.png",
                                                          "ccbresources/12monthdate/battle/CloseSelected.png",
                                                          this,
                                                          menu_selector(CcbPetBattleLayer::menuCloseCallback)
                                                          );
    
    pCloseItem->setPosition( ccp(winSize.width - 20, 20) );
    pCloseItem->setScale(2);
    
    
    CCMenuItemLabel* btnJiaSu = CCMenuItemLabel::create(CCLabelTTF::create("加速", "", 20), this, menu_selector(CcbPetBattleLayer::menuJiaSu));
    btnJiaSu->setPosition(pCloseItem->getPosition() + ccp(0, 40) );
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, btnJiaSu, NULL);
    pMenu->setPosition( CCPointZero );
    pMenu->setTouchPriority(kCCMenuHandlerPriority - 30);
#ifdef DEBUG
    this->addChild(pMenu, 1000);
#endif
    
    fRealHeight = winSize.height - getTop(m_pLayerPetCtrlBg);
    initPos();
    imgTrans = CCSprite::create("ccbresources/12monthdate/battle/battle_wipe.png");
    
    imgTrans->setPosition(ccp(-10, getTop(m_pLayerPetCtrlBg)));
    imgTrans->setAnchorPoint(CCPointZero);
    this->addChild(imgTrans, E_ZORDER_TRANS);
    imgTrans->setRotationY(180);
    CCSprite *img2 = CCSprite::create("ccbresources/12monthdate/battle/battle_wipe.png");
    img2->setTextureRect(CCRectMake(113, 0, 10, getHeight(img2)));
    img2->setScaleX(100);
    img2->setAnchorPoint(CCPointZero);
    img2->setPosition(ccp(getWidth(imgTrans), 0));
    imgTrans->addChild(img2);
    imgTrans->setScaleY((winSize.height - getTop(m_pLayerPetCtrlBg) + 10)/getHeight(imgTrans));
    
    //被动技能特效}
    arrBattleCtrl.clear();
    arrBattleCtrl.push_back(m_pLayerPetBattleCtrl_1);
    arrBattleCtrl.push_back(m_pLayerPetBattleCtrl_2);
    arrBattleCtrl.push_back(m_pLayerPetBattleCtrl_3);
    arrBattleCtrl.push_back(m_pLayerPetBattleCtrl_4);
    arrBattleCtrl.push_back(m_pLayerPetBattleCtrl_5);
    arrBattleCtrl.push_back(m_pLayerPetBattleCtrl_6);

    bosshpBarWidth = getWidth(m_pSpriteBossHpBar);
    myhpBarWidth = getWidth(m_pSpriteMyHpBar);
    m_isAutoFight = false;
    m_isFighting = false;
    isStop = false;

    m_bIsRoundEnd = false;
    isEatBox = false;
    m_WaitAttCnt = 0;
    m_AttCnt = 0;

    m_curCoin = 0;
    m_curSoul = 0;
    m_curEgg = 0;

    m_pControlButtonAutoFightOff->setVisible(false);
    m_pControlButtonAutoFightOff->setTouchPriority(kCCMenuHandlerPriority - 20);
    m_pControlButtonAutoFight->setTouchPriority(kCCMenuHandlerPriority - 20);
    m_pLayerBossHpBg->setVisible(false);
    m_wBossIndex = 0;

    m_pLayerBossHpBg->setZOrder(E_ZORDER_BOSS_HP_BG);
    
    m_pNodeNormalReward->setZOrder(1);
    m_pNodeCoinCatReward->setZOrder(1);
    
    m_pSpriteEnemyAltBg->setVisible(false);
    m_pSpriteEnemyAltBg->setZOrder(E_ZORDER_ALT_SKILL_EFF);
    
    arrCurFightPet.clear();

    
    m_isAutoFight = GlobalData::bIsAutoFight;
    if (m_isAutoFight) {
        m_pControlButtonAutoFight->setVisible(false);
        m_pControlButtonAutoFightOff->setVisible(true);
    }
    else{
        m_pControlButtonAutoFight->setVisible(true);
        m_pControlButtonAutoFightOff->setVisible(false);
    }
    
    CRole* role = CGameSession::GetRole();
    if (role->GetwGuideTrigger() < GuideData::E_GUIDE_TRIGGER_FIR_ATTACK) {
        m_pControlButtonAutoFight->setVisible(false);
        m_pControlButtonAutoFightOff->setVisible(false);
    }
}

bool CcbPetBattleLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (isStop || m_isAutoFight) {
        return true;
    }
    return false;
}

void CcbPetBattleLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 15, true);
}

void CcbPetBattleLayer::onPressControlButtonAutoFight(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CRole* role = CGameSession::GetRole();
    if (!role->GetbyIsAutoFight()) {
        FlyTextLayer::showTips(GET_STR(Str_no_open_auto_fight));
        return;
    }
    
    //自动战斗后，直到点击关闭为止一直自动战斗，关闭后，从下一回合开始手动战斗}
//    m_pControlButtonAutoFight->setEnabled(false);
    m_pControlButtonAutoFight->setVisible(false);
    m_pControlButtonAutoFightOff->setVisible(true);

    m_isAutoFight = true;
    GlobalData::bIsAutoFight = m_isAutoFight;
    
    if (!m_isFighting || m_bIsRoundEnd) {
        for (int i = 0; i < arrBattleCtrl.size(); i++) {
            CcbPetBattleCtrl *ctrl = arrBattleCtrl[i];
            STC_PET_CTRL_INFO info = ctrl->getPetCrtlInfo();
            if (!info.petIndex) {
                continue;
            }
            ctrl->setIsEnable(false);
            
        }
        return;
    }
    
    bool flag = false;
    if (arrCurFightPet.size() > 0 && *arrCurFightPet.begin() > PetCnt) {
        flag = true;
    }
    int cnt = 0;
    for (int i = 0; i < arrBattleCtrl.size(); i++) {
        CcbPetBattleCtrl *ctrl = arrBattleCtrl[i];
        STC_PET_CTRL_INFO info = ctrl->getPetCrtlInfo();
        if (!info.petIndex) {
            continue;
        }
        ctrl->setIsEnable(false);
        
        FightPet* pet = FightAI::Get()->getFightPetByBIndex(info.petBattleIndex);
        if (!pet || pet->getCurHP() == 0
            || pet->getCurPower() < pet->getPetInfo().wAllPower) {
            continue;
        }
        pet->setIsWaitSkill(true);
        
        //这么做是为了，在点击自动战斗时，多个技能同时释放时，加上延迟}
        //当前是敌方攻击时，之前的机制能够满足}
        //当前是我方时，正在攻击的宠物不动，其他的加入延迟，开始走计时器}
        if (flag) {
            addSkillWait(pet->getPetInfo().wBattleIndex, pet->getPetInfo().wSkillId);
        }
        else{
            for (int i = 0; i < arrSkillWait.size(); i++) {
                if (arrSkillWait[i].key ==  pet->getPetInfo().wBattleIndex) {
                    continue;
                }
            }
            
            
            STC_WAIT_BATTLE_DATA wData;
            wData.key = pet->getPetInfo().wBattleIndex;
            wData.skillId = pet->getPetInfo().wSkillId;
            //在攻击中}
            if (arrCurFightPet.find(pet->getPetInfo().wBattleIndex) != arrCurFightPet.end()) {
                wData.frame = 0; //本来，frame==0表示已经开始攻击，但因为我方时，并且此宠正在攻击时，释放技能不走计时器而是在宠物回来后自动完成，故设为0并不影响。设0是为了在计时器中不再对此条数据处理}
            }
            else{   //可立即攻击}
                wData.frame = cnt* 10 + 5;
                cnt++;
            }
            arrSkillWait.push_back(wData);
        }
    }
    
    if (cnt > 0) {
        schedule(schedule_selector(CcbPetBattleLayer::updateForSkillWaitBattle));
    }
    
}

void CcbPetBattleLayer::onPressControlButtonAutoFightOff(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    //关闭自动战斗，从下一波开始手动战斗}
    m_isAutoFight = false;
    m_pControlButtonAutoFight->setVisible(true);
    m_pControlButtonAutoFightOff->setVisible(false);
    GlobalData::bIsAutoFight = m_isAutoFight;
    for (int i = 0; i < arrBattleCtrl.size(); i++) {
        CcbPetBattleCtrl *ctrl = arrBattleCtrl[i];
        STC_PET_CTRL_INFO info = ctrl->getPetCrtlInfo();
        if (!info.petIndex) {
            continue;
        }
        ctrl->setIsEnable(true);
    }
}

//初始化站位}
void CcbPetBattleLayer::initPos()
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
CCPoint CcbPetBattleLayer::getMyMiddlePos()
{
    return arrPetPos[2];
}

//获取敌方宠物中间位置}
CCPoint CcbPetBattleLayer::getEnemyMiddlePos()
{
    return arrEnemyPos[2];
}
void CcbPetBattleLayer::loadData()
{
    allDamage = 0;
    //判断是否是招财猫}
    if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE) {
        m_pLabelTTFCoinCat_Coin->setString("0");
        m_pLabelTTFCoinCat_Damage->setString("0");
        m_pLabelTTFCoinCat_CurRound->setString(CCString::createWithFormat("%d / %d",FightAI::Get()->getAllRound(), FightAI::Get()->getAllRound())->getCString());
        m_pNodeNormalReward->setVisible(false);
    }
    else
    {
        m_pLabelTTFCoin->setString("0");
        m_pLabelTTFEgg->setString("0");
        m_pNodeCoinCatReward->setVisible(false);
    }
    //音效}
    switch (FightAI::Get()->getFightType()) {
        case E_BATTLE_TYPE_MAP:
        case E_BATTLE_TYPE_HERO_MAP:
        case E_BATTLE_TYPE_COIN_TREE:
        {
            StageCtrl::STC_STAGE stage = StageCtrl::Get()->selectedStage();
            int m = stage.vectNormalBgm.size();
            if (m == 0) {
                break;
            }
            m = rand() % m;
            CMusicCtrl::PlayBackgroundMusic(GET_BATTLE_NOR_MUSIC(stage.vectNormalBgm[m]));
        }
            break;
        case E_BATTLE_TYPE_ACTIVE_MAP:
        {
            StageCtrl::STC_STAGE *stage = StageCtrl::Get()->getStageByStageId(StageCtrl::Get()->getSelectStageId());
            
            if (!stage) {
                break;
            }
            int m = stage->vectNormalBgm.size();
            m = rand() % m;
            if (m < stage->vectNormalBgm.size()) {
                CMusicCtrl::PlayBackgroundMusic(GET_BATTLE_NOR_MUSIC(stage->vectNormalBgm[m]));
            }
            
            break;
        }
        default:
            break;
    }
    //地图}
    int mapId = 1;
    
    switch (FightAI::Get()->getFightType()) {
        case E_BATTLE_TYPE_MAP:
        case E_BATTLE_TYPE_HERO_MAP:
        {
            StageCtrl::STC_STAGE stage = StageCtrl::Get()->selectedStage();
            mapId = stage.wShowMapId;
        }
            break;
            
        case E_BATTLE_TYPE_ACTIVE_MAP:
        {
            ActiveStageConfig::STC_ACTIVE_STAGE_CONFIG * cfg = GET_CONFIG_STC(ActiveStageConfig, StageCtrl::Get()->getSelectStageId());
            if (cfg) {
                mapId = cfg->wBattleMapId;
            }
            break;
        }
        case E_BATTLE_TYPE_COIN_TREE:
        {
            ActiveStageConfig::STC_ACTIVE_STAGE_CONFIG * cfg = GET_CONFIG_STC(ActiveStageConfig, StageCtrl::Get()->selectedStage().wStageId);
            if (cfg) {
                mapId = cfg->wBattleMapId;
            }
        }
            break;
        case E_BATTLE_TYPE_TOWER:
        {
            TowerConfig::STC_TOWER_CONFIG * cfg = GET_CONFIG_STC(TowerConfig, g_TowerDataMgr->GetCurBattleFloor());
            mapId = cfg->wBattleMapId;
        }
            break;
        case E_BATTLE_TYPE_WRESTLE:
            mapId = rand() % 10 + 1;
            break;
            
        default:
            break;
    }
    
    CRole* role = CGameSession::GetRole();
    if (role->GetwGuideTrigger() < GuideData::E_GUIDE_TRIGGER_FIR_1_ATTACK) {
        mapId = 4;
    }
    
    std::string pathMap = CUtil::StrFormat( FIGHT_MAP , mapId, FORMAT_PARAM_END ).c_str();
//    std::string pathScene = CUtil::StrFormat( FIGHT_MAP_SCENE , mapId, FORMAT_PARAM_END ).c_str();

    
    CCTexture2D* t2xScene = CCTextureCache::sharedTextureCache()->addImage(pathMap.c_str());
//    CCTexture2D* t2xScene = CCTextureCache::sharedTextureCache()->addImage(pathScene.c_str());
    
    if (t2xScene) {
        m_pSpriteNearMap->initWithTexture(t2xScene);
    }
    else
    {
        t2xScene = CCTextureCache::sharedTextureCache()->addImage("map/battle_map_12.png");
        if (t2xScene) {
            m_pSpriteNearMap->initWithTexture(t2xScene);
        }
    }
//
//    if (t2xScene) {
//        m_pSpriteNearMap->initWithTexture(t2xScene);
//    }
//    else
//    {
//        t2xScene = CCTextureCache::sharedTextureCache()->addImage("map/battle_scene_12.png");
//        if (t2xScene) {
//            m_pSpriteNearMap->initWithTexture(t2xScene);
//        }
//    }

//    m_pSpriteFarMap->setAnchorPoint(ccp(0.5, 1));
    m_pSpriteNearMap->setAnchorPoint(ccp(0.5, 1));
    FightTeam *myTeam = FightAI::Get()->getMyTeam();
    
    //我方总血量}
    CCString *str = CCString::create("");
    str->initWithFormat("%d", myTeam->GetTeamHpMax());
    m_pLabelTTFMyCurHP->setString(str->getCString());
    m_pLabelTTFMyMaxHP->setString(str->getCString());
    m_dwMyTeamCurHP = myTeam->GetTeamHpMax();
    //敌方血量、名称}
    
    //回合}
    curRound = FightAI::Get()->getAllRound();
    str->initWithFormat("%d", curRound);
    str->initWithFormat("%d", FightAI::Get()->getAllWaveCnt());

    //flcc和petCtrl}
    FightTeam::MapFightTeam myTeamMember = myTeam->GetTeam();
    FightTeam::MapFightTeam::iterator it = myTeamMember.begin();
    
    for (; it != myTeamMember.end(); it++) {
        if (!it->second) {
            continue;
        }
        //生成flcc}
        FightPetSprite *mc = FightPetSprite::create(it->first, this);
        mc->setPosition(arrPetPos[it->first%100 - 1]);
        mc->setAnchorPoint(ccp(0, 0));
        mc->setMyPos(arrPetPos[it->first%100 - 1]);
//        mc->setScale(0.9);
        mc->setRotationY(180);
        mc->setIsCanDead(true);
        m_pLayerAllBg->addChild(mc);
        mc->setOpacity(0);
        it->second->setIsCanDead(true);
        
        
        CcbPetBattleHpBarLayer* hpBar = mc->getHpBar();
        if (hpBar) {
            m_pLayerAllBg->addChild(hpBar, E_ZORDER_ENEMY_HP_BG);
        }
        
        mc->setZOrder(E_ZORDER_PET_MC - mc->getMyPos().y);
        m_mapPet[it->first] = mc;

    }
    
    for (int i = 0; i < PetCnt; i++) {
        if (m_mapPet.find(i+1) == m_mapPet.end()) {
            m_mapPet[i+1] = NULL;
        }
        
        arrBattleCtrl[i]->setBattleIndex(i+1, this);
        arrBattleCtrl[i]->setZOrder(E_ZORDER_PET_CTRL);
    }
//    m_pSpriteMyHpBg->setZOrder(E_ZORDER_MY_HP_BG);
    
    FightAI::Get()->waveStart();
    waveStart();
}

void CcbPetBattleLayer::loadEnemyTeam()
{
    std::map<uint16, FightPetSprite*>::iterator it = m_mapPet.begin();
    for (; it != m_mapPet.end(); it++) {
        if(it->first <= PetCnt || !it->second)
        {
           continue;
        }
        it->second->removeFromParentAndCleanup(true);
        it->second = NULL;
    }
        
    FightTeam *enemyTeam = FightAI::Get()->getEnemyTeam();
    FightTeam::MapFightTeam enemyTeamMember = enemyTeam->GetTeam();
    FightTeam::MapFightTeam::iterator itE = enemyTeamMember.begin();
    
    if (enemyTeamMember.size() == 0) {
//        CCMessageBox("qqqqqqqqqqqqq敌方宠物没有~~~", "Error");
        return;
    }
    
    
    bool flag = true;
    
    for (; itE != enemyTeamMember.end(); itE++) {
        if (!itE->second) {
            continue;
        }
        
        FightPetSprite *mc = FightPetSprite::create(itE->first, this);
        mc->setAnchorPoint(ccp(0, 0));
        mc->setPosition(arrEnemyPos[itE->first%100 - 1]);
        mc->setMyPos(arrEnemyPos[itE->first%100 - 1]);
//        mc->setRotationY(180);
        mc->setIsCanDead(true);
        itE->second->setIsCanDead(true);
//        mc->setScale(0.9);
        m_pLayerAllBg->addChild(mc);
        
        CcbPetBattleHpBarLayer* hpBar = mc->getHpBar();
        if (itE->second->getPetInfo().isBoss) {
            m_wBossIndex = itE->first;
            mc->setScale(1.1);
            hpBar = NULL;
        }
        
        if (hpBar) {
            m_pLayerAllBg->addChild(hpBar, E_ZORDER_ENEMY_HP_BG);
        }
        
        mc->setZOrder(E_ZORDER_PET_MC - mc->getMyPos().y);
        m_mapPet[itE->first] = mc;
        
        mc->setVisible(false);
        
        if (flag) {
            flag = false;
            FightAI::Get()->setSelectedEnemy(itE->first);
        }
    }
    for (int i = 1; i <= PetCnt; i++) {
        if (m_mapPet.find(i+100) == m_mapPet.end()) {
            m_mapPet[i+100] = NULL;
        }
    }
}
//怪进入场景}
void CcbPetBattleLayer::enemyRunIn()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    for (int i = 101; i <= 100 + PetCnt; i++) {
        if (m_mapPet.find(i) == m_mapPet.end()) {
            continue;
        }
        FightPetSprite *mc = m_mapPet[i];
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

void CcbPetBattleLayer::doSomething(uint16 wBattleIndex, uint32 skillId)
{
    if (m_bIsRoundEnd || !wBattleIndex || !skillId) {
        return;
    }
    FightPet* pet = FightAI::Get()->getFightPetByBIndex(wBattleIndex);
    if (!pet || pet->getIsWaitSkill()) {
        return;
    }
    
    if (wBattleIndex <= PetCnt && !m_isAutoFight) {
        arrBattleCtrl[wBattleIndex - 1]->hideFlowFire(NULL);
        showBattleCtrlTouchEff(wBattleIndex);
        pet->setIsWaitSkill(true);
        FightPetSprite* sPet = m_mapPet[wBattleIndex];
        sPet->showAltEff();
    }
    CCLog("点击释放~~~~~~~~~~ %d", wBattleIndex);
    addSkillWait(wBattleIndex, skillId);
}

void CcbPetBattleLayer::addSkillWait(uint16 wBattleIndex, uint32 skillId)
{
    if (!wBattleIndex || !skillId) {
        return;
    }
    FightPet* pet = FightAI::Get()->getFightPetByBIndex(wBattleIndex);
    if (!pet) {
        return;
    }
    
    for (int i = 0; i < arrSkillWait.size(); i++) {
        if (arrSkillWait[i].key == wBattleIndex) {
            return;
        }
    }
    
    STC_WAIT_BATTLE_DATA wData;
    wData.key = wBattleIndex;
    wData.skillId = pet->getPetInfo().wSkillId;
    wData.frame = 0;
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger < GuideData::E_GUIDE_TRIGGER_BOSS_1_TALK) {
        wData.frame = 1;
        schedule(schedule_selector(CcbPetBattleLayer::updateForSkillWaitBattle));
    }
    
    //根据不同的情况，选择不同攻击方式}
    //当自身正在攻击，或者敌方正在攻击时，加入等待序列，等待攻击}
    if (arrCurFightPet.size() > 0) {
        if (arrCurFightPet.find(wBattleIndex) != arrCurFightPet.end()
            || abs(*arrCurFightPet.begin() - wBattleIndex) > PetCnt) {
            wData.frame = 100000;
            CCLog("延迟攻击~~~~~~~~~~ %d", wBattleIndex);
        }
    }
    arrSkillWait.push_back(wData);
    //可以立刻攻击}
    if (wData.frame == 0) {
        startBattle(wBattleIndex, pet->getPetInfo().wSkillId);
        CCLog("立即攻击~~~~~~~~~~ %d", wBattleIndex);
    }
}

//判断连携加成}
bool CcbPetBattleLayer::checkLianXie(uint16 wBattleIndex)
{
    arrLianxieWait.clear();

    m_WaitAttCnt = 0;
    uint8 cnt = m_AttCnt;//arrEnemyBattleWait.size();
    for (int i = cnt; i < arrEnemyBattleWait.size(); i++) {
        STC_WAIT_BATTLE_DATA data = arrEnemyBattleWait[i];
        if (wBattleIndex == data.key) {
            arrLianxieWait.push_back(data);
            continue;
        }
        if (abs(data.key - wBattleIndex) <= PetCnt) {
            FightPet * pet = FightAI::Get()->getFightPetByBIndex(data.key);
            if (pet->getCurHP() <= 0 || pet->HasPalsyBuff(FightAI::Get()->getCurRound())
                || pet->HasConfusedBuff(FightAI::Get()->getCurRound())) {
                m_AttCnt++;
                continue;
            }
            arrLianxieWait.push_back(data);
        }
        else
        {
            break;
        }
    }
    
    if (arrLianxieWait.size() <= 1) {
        arrLianxieWait.clear();
        return false;
    }

    uint16 rand = FightAI::Get()->getDamFloat().arrLianXieRate[arrLianxieWait.size() - 1];
    uint16 add = FightAI::Get()->getDamFloat().arrLianXieValue[arrLianxieWait.size() - 1];
    bool flag = std::rand() % 10000 <= rand > 0;
    //关闭连携
//    if (wBattleIndex > PetCnt) {
        flag = false;
//    }
    
    for (int i = 0; i < arrLianxieWait.size(); i++) {
        STC_WAIT_BATTLE_DATA data = arrLianxieWait[i];
        uint16 frame = delayFrame * i + 1;
        
        FightPet * pet = FightAI::Get()->getFightPetByBIndex(data.key);
        if (flag) {
            pet->setLianXieState(E_LIANXIE_STATE_OK);
            pet->setLianXieAdd(add - 10000);
            FightPetSprite* pSprite = m_mapPet[data.key];
            if (pSprite) {
                pSprite->showLianXie(add);
            }
            
            frame += delayFrame*3;
        }
        else{
            pet->setLianXieAdd(0);
            pet->setLianXieState(E_LIANXIE_STATE_LOSE);
        }
        if (i == arrLianxieWait.size()-1) {
            pet->setLianXieState(E_LIANXIE_STATE_LAST);
        }
        data.frame = frame;
        arrLianxieWait[i] = data;
    }
    
    if (flag) {
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
    schedule(schedule_selector(CcbPetBattleLayer::updateForWaitBattle));
    
    return true;
}

void CcbPetBattleLayer::startBattle(uint16 wBattleIndex, uint32 skillId)
{
    bool isRealSkill = false;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, skillId);
    if (ultCfg && ultCfg->byType == 1) {
        isRealSkill = true;
    }
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_1 && wBattleIndex > 100) {
        return;
    }
    
    //不能攻击，相当于这个人已经攻击结束了}
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(wBattleIndex);
    if (!pet || pet->getCurHP() <= 0) {
        endBattle(wBattleIndex, skillId);
        return;
    }
    
    //判断能否攻击}
    if (pet->HasPalsyBuff(FightAI::Get()->getCurRound()) ||
        pet->HasConfusedBuff(FightAI::Get()->getCurRound())) {
        endBattle(wBattleIndex, skillId);
        return;
    }
    //判断能否技能(普通情况不可能走技能攻击了，所以封印时，并且用技能，直接返回就可以)}
    if (isRealSkill && pet->HasSealBuff(FightAI::Get()->getCurRound())) {
        endBattle(wBattleIndex, skillId);
        return;
    }
    
    //判断连携(技能不走连携)}
    if (!isRealSkill && pet->getLianXieState() == E_LIANXIE_STATE_NON) {
        if (checkLianXie(wBattleIndex)) {
            return;
        }
        if (pet->getLianXieState() == E_LIANXIE_STATE_LAST) {
            
            unschedule(schedule_selector(CcbPetBattleLayer::updateForWaitBattle));
        }
    }
    
    STC_START_BATTLE_DATA startData = FightAI::Get()->getStartBattleData(wBattleIndex,  skillId);
    if (wBattleIndex <= PetCnt && startData.arrEnemyIndexs.size() == 0) {
        for (int i = 1; i <= PetCnt; i++) {
            uint16 fightId = i+100;
            if(m_mapPet.find(fightId) != m_mapPet.end() &&
               m_mapPet[fightId]){
                if (m_mapPet[fightId]->getDeadTime() > 18) {
                    m_mapPet[fightId]->setDeadTime(DEADTIME);
                    startData.arrEnemyIndexs.push_back(fightId);
                    startData.wAttIndex = fightId % 100;
                    break;
                }
                
            }
        }
    }
    
    //加这段，是为了过滤已经死的怪}
    int count = 0;
    for (int i = 0; i < startData.arrEnemyIndexs.size(); i++) {
        uint16 fightId = startData.arrEnemyIndexs[i];
        if(m_mapPet.find(fightId) != m_mapPet.end() &&
           m_mapPet[fightId]){
            if (m_mapPet[fightId]->getDeadTime() > 18) {
                m_mapPet[fightId]->setDeadTime(DEADTIME);
                count++;
            }
           
        }
    }
    
    if (count == 0) {
        endBattle(wBattleIndex, skillId);
        return;
    }
    arrCurFightPet.insert(wBattleIndex);
    
    
    //生成战斗包，并取得战斗包的Key，加入等待序列}
    FightAI::Get()->setWaitFrame(arrWaitBattleData);
    uint16 key = FightAI::Get()->getBattleData(startData);
    STC_WAIT_BATTLE_DATA wait;
    wait.key = key;
    wait.frame = 0;
    arrWaitBattleData.push_back(wait);
    
    FightPetSprite *mc = m_mapPet[wBattleIndex];
    if (mc) {
        CCPoint pos = CCPointZero;
        uint16 enemyIndex = startData.wAttIndex;
        FightPetSprite *mcE = NULL;
        int x = 1;
        if (wBattleIndex <= PetCnt) {
            x = -1;
            pos = arrEnemyPos[enemyIndex - 1];
            mcE  = m_mapPet[enemyIndex+100];
        }
        else
        {
            
            pos = arrPetPos[enemyIndex - 1];
            mcE  = m_mapPet[enemyIndex];
        }
        float offX = 0;
        if (mcE) {
            offX = (float)mcE->getStandSize().width * 0.5*mcE->getScaleX() - getWidth(mcE)*(1-mcE->getScaleX())*0.5;
        }
        if (isRealSkill) {
            showSkillLayer(wBattleIndex, skillId);
            pet->setIsWaitSkill(false);
            if (wBattleIndex <= PetCnt) {
                mc->hideAltEff();
                CcbPetBattleCtrl* ctrl = arrBattleCtrl[wBattleIndex - 1];
                ctrl->setPower(0);
                ctrl->setCtrlState(E_PET_STATE_NORMAL);
            }
        }
        
        STC_BATTLE_DATA data = FightAI::Get()->getBattleDataByKey(key);
        mc->startBattle(CCPoint(pos.x + x*((float)mc->getAtkSize().width*0.5*mc->getScaleX() + offX - getWidth(mc)*(1-mc->getScaleX())*0.5), pos.y), data);
    }
    
    
}

void CcbPetBattleLayer::updateForWaitBattle(float time)
{
    if (m_isPauseAll) {
        return;
    }
    //循环所有战斗包，更新等待时间}
    if (arrSkillWait.size() > 0){
        return;
    }
    for (int i = 0; i < arrLianxieWait.size(); i++) {
        STC_WAIT_BATTLE_DATA wait = arrLianxieWait[i];
        if (wait.frame == 0) {
            continue;
        }
        wait.frame--;
        arrLianxieWait[i] = wait;
        
        if (wait.frame == 0) {
            //如果是自动战斗，判断是否释放技能}
            uint32 skillId = wait.skillId;

            startBattle(wait.key, skillId);
        }
    }
}

//技能等待中的战斗包计时}
void CcbPetBattleLayer::updateForSkillWaitBattle(float time)
{
    if ( m_bBossFlag && CheckPointMgr::Get()->talkPadCnt() > 0) {
        return;
    }
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger < GuideData::E_GUIDE_TRIGGER_BOSS_1_TALK) {
        return;
    }
    
    for (int i = 0; i < arrSkillWait.size(); i++) {
        STC_WAIT_BATTLE_DATA wait = arrSkillWait[i];
        if (wait.frame <= 0) {
            continue;
        }
        wait.frame--;
        arrSkillWait[i] = wait;
        
        if (wait.frame == 0) {
            //如果是自动战斗，判断是否释放技能}
            uint32 skillId = wait.skillId;
            CCLog("敌阵营 延迟攻击~~~~~~~~~~ %d", wait.key);
            startBattle(wait.key, skillId);
        }
    }
}

bool CcbPetBattleLayer::cmpSpeed(const int &p, const int &q)
{
    FightPet* pet1 = FightAI::Get()->getFightPetByBIndex(p);
    FightPet* pet2 = FightAI::Get()->getFightPetByBIndex(q);
    
    uint32 speed1 = pet1->getCurSpeed(FightAI::Get()->getCurRound());
    uint32 speed2 = pet2->getCurSpeed(FightAI::Get()->getCurRound());
    
    return speed1 > speed2;
}

//自动攻击}
void CcbPetBattleLayer::autoAttack()
{
    m_isFighting = true;

    FightTeam::MapFightTeam teamMy = FightAI::Get()->getMyTeam()->GetTeam();
    FightTeam::MapFightTeam teamEn = FightAI::Get()->getEnemyTeam()->GetTeam();
    
    std::vector<uint16> arrFightId;
    FightTeam::MapFightTeam::iterator it = teamMy.begin();
    for (; it != teamMy.end(); it++) {
        if (!it->second
            || (it->second->getCurHP() == 0 && it->second->getIsCanDead())) {
            continue;
        }
        it->second->setLianXieState(E_LIANXIE_STATE_NON);
        arrFightId.push_back(it->first);
    }
    
    it = teamEn.begin();
    for (; it != teamEn.end(); it++) {
        if (!it->second
            || (it->second->getCurHP() == 0 && it->second->getIsCanDead())) {
            continue;
        }
        it->second->setLianXieState(E_LIANXIE_STATE_NON);
        arrFightId.push_back(it->first);
    }
    
    std::sort(arrFightId.begin(), arrFightId.end(), cmpSpeed);
    
    int cnt = 0;
    for (int i = 0; i < arrFightId.size(); i++) {
        STC_WAIT_BATTLE_DATA wait;
        wait.key = arrFightId[i];
        
        uint16 frame = delayFrame + 1;
        if (arrEnemyBattleWait.size() > 0) {
            frame += arrEnemyBattleWait[arrEnemyBattleWait.size() - 1].frame;
        }
        
        FightPet *pet = FightAI::Get()->getFightPetByBIndex(wait.key);
        
        wait.frame = frame;//CCRANDOM_0_1() * 5 + delayFrame *i + delayFrame + 5;// + count * 10;
        wait.skillId = pet->getPetInfo().wNormalAttId;
        arrEnemyBattleWait.push_back(wait);
        
        if (!pet->getPetInfo().wSkillId) {
            continue;
        }
        
        if ( (pet->getCurPower() >= pet->getPetInfo().wAllPower)
            || pet->getIsWaitSkill()) {
        
            
            if (wait.key > PetCnt || m_isAutoFight) {
                
                STC_WAIT_BATTLE_DATA wData;
                wData.key = pet->getPetInfo().wBattleIndex;
                wData.skillId = pet->getPetInfo().wSkillId;
                
                if (arrSkillWait.size() == 0) {
                    wData.frame = 5;
                }
                else if (abs(arrSkillWait[0].key - wait.key) > PetCnt){
                    wData.frame = 100000;
                }
                else{
                    wData.frame = cnt* 10 + 5;
                }
                cnt++;
                arrSkillWait.push_back(wData);
            }
        }
    }
    
    if (cnt > 0) {
        schedule(schedule_selector(CcbPetBattleLayer::updateForSkillWaitBattle));
        return;
    }
    
    if (arrEnemyBattleWait.size() == 0) {
        roundEnd();
        return;
    }
//    isStop = false;
    startBattle(arrEnemyBattleWait[0].key, arrEnemyBattleWait[0].skillId);
}

void CcbPetBattleLayer::doBattle(uint8 key)
{
    
}


//显示掉血}
void CcbPetBattleLayer::loseHp(uint16 wBattleIndex, int hp)
{
    FightPetSprite *pSprite = m_mapPet[wBattleIndex];
    //掉血的是我方}
    if (wBattleIndex <= PetCnt) {
        m_dwMyTeamCurHP = m_dwMyTeamCurHP < hp ? 0 : m_dwMyTeamCurHP-hp;
        
        CCString *str = CCString::createWithFormat("%d", m_dwMyTeamCurHP);
        m_pLabelTTFMyCurHP->setString(str->getCString());
        
        m_pSpriteMyHpBar->setTextureRect(CCRectMake(0, 0, (float)m_dwMyTeamCurHP / FightAI::Get()->getMyTeam()->GetTeamHpMax() * myhpBarWidth / m_pSpriteMyHpBar->getScaleX(), getHeight(m_pSpriteMyHpBar) / m_pSpriteMyHpBar->getScaleY()));
        
        arrBattleCtrl[wBattleIndex - 1]->loseHP(pSprite->getCurHP());
    }
    else
    {
        curRoundDamage += hp;
        allDamage += hp;
        m_pLabelTTFCoinCat_Damage->setString(CCString::createWithFormat("%d", allDamage)->getCString());
        //如果是boss掉血}
        if (wBattleIndex == m_wBossIndex) {
            m_pSpriteBossHpBar->setTextureRect(CCRectMake(0, 0, (float)pSprite->getCurHP() / pSprite->getMaxHp() * bosshpBarWidth / m_pSpriteBossHpBar->getScaleX(), getHeight(m_pSpriteBossHpBar) / m_pSpriteBossHpBar->getScaleY()));
        }
    }
}

//加血}
void CcbPetBattleLayer::addHp(uint16 wBattleIndex, int hp)
{
    FightPetSprite *pSprite = m_mapPet[wBattleIndex];
    
    hp = pSprite->addHP(hp);
    //加血的是我方}
    if (wBattleIndex <= PetCnt) {
        m_dwMyTeamCurHP = m_dwMyTeamCurHP + hp;
        if (m_dwMyTeamCurHP > FightAI::Get()->getMyTeam()->GetTeamHpMax())
        {
            m_dwMyTeamCurHP = FightAI::Get()->getMyTeam()->GetTeamHpMax();
        }
        
        CCString *str = CCString::createWithFormat("%d", m_dwMyTeamCurHP);
        m_pLabelTTFMyCurHP->setString(str->getCString());
        
        m_pSpriteMyHpBar->setTextureRect(CCRectMake(0, 0, (float)m_dwMyTeamCurHP / FightAI::Get()->getMyTeam()->GetTeamHpMax() * myhpBarWidth / m_pSpriteMyHpBar->getScaleX(), getHeight(m_pSpriteMyHpBar) / m_pSpriteMyHpBar->getScaleY()));
        
        arrBattleCtrl[wBattleIndex - 1]->loseHP(pSprite->getCurHP());
    }
    else
    {
        
        //如果是boss加血}
        if (wBattleIndex == m_wBossIndex) {
            m_pSpriteBossHpBar->setTextureRect(CCRectMake(0, 0, (float)pSprite->getCurHP() / pSprite->getMaxHp() * bosshpBarWidth / m_pSpriteBossHpBar->getScaleX(), getHeight(m_pSpriteBossHpBar) / m_pSpriteBossHpBar->getScaleY()));
        }
    }
}
//调整主动技能冷却}
void CcbPetBattleLayer::setPower(uint16 wBattleId, int wValue)
{
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(wBattleId);
    if (!pet) {
        return;
    }
    int curPower = MIN(MAX(wValue, 0), pet->getPetInfo().wAllPower);
    
    if (wBattleId <= PetCnt) {
        CcbPetBattleCtrl * ctrl = arrBattleCtrl[wBattleId - 1];
        ctrl->setPower(curPower);
    }
    
    //怒气满就释放技能}
    if (wBattleId > PetCnt ||
        m_isAutoFight) {
        if (!pet->getIsWaitSkill() &&
            pet->getCurPower() >= pet->getPetInfo().wAllPower) {
            pet->setIsWaitSkill(true);
            addSkillWait(wBattleId, pet->getPetInfo().wSkillId);
        }
    }
}
//用于判断死亡}
void CcbPetBattleLayer::updateForChkDead(float time)
{
    if (m_isPauseAll) {
        return;
    }
    
    for (int i = 1; i <= PetCnt; i++) {
        FightPetSprite *pSprite = m_mapPet[i];
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
            arrBattleCtrl[i-1]->setCtrlState(E_PET_STATE_DEAD);
        }
    }
    
    for (int i = 1; i <= PetCnt; i++) {
        FightPetSprite *pSprite = m_mapPet[i + 100];
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
            if (pSprite->getBattleIndex() == m_wBossIndex) {
                m_pLayerBossHpBg->setVisible(false);
            }
            
            FightPet* fPet = FightAI::Get()->getFightPetByBIndex(pSprite->getBattleIndex());
            if (fPet && fPet->getCurHP() > 0) {
                CCLog("fight id: %d is dead,but curHp :%d",pSprite->getBattleIndex(), fPet->getCurHP());
            }
            pSprite->setIsDead(true);
            enemyDead(pSprite->getBattleIndex());
        }
    }
}

//敌人死亡}
void CcbPetBattleLayer::enemyDead(uint16 wEnemyIndex)
{
    
    //死后掉落最后的所有物品}
    FightPet* pet = FightAI::Get()->getFightPetByBIndex(wEnemyIndex);
    if (!pet) {
        return;
    }
    if (wEnemyIndex > PetCnt && pet->getMyTeam()->GetTeamHp() == 0 && !pet->getMyTeam()->getLastDeadFlag()) {
        pet->getMyTeam()->setLastDeadFlag(true);
        std::vector<STC_ITEM_DROP> arrDrop = FightAI::Get()->getDropItemByDamage(10000, pet);
        
        int n = pet->getMaxDropHeart() - pet->getCurHeart();
        for (int i = 0; i < n; i++) {
            STC_ITEM_DROP item;
            item.wCount = 1;
            item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_HEART;
            arrDrop.push_back(item);
        }
        for (int i = 0; i < arrDrop.size(); i++) {
            dropItem(wEnemyIndex, arrDrop[i]);
        }

    }
    
}

//显示boss血条}
void CcbPetBattleLayer::showBossHp()
{
    FightPet *pet = FightAI::Get()->getBoss();
    if (!pet || FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE) {
        return;
    }
    
    m_pLayerBossHpBg->setVisible(true);
    m_wBossIndex = pet->getPetInfo().wBattleIndex;

    //头像}
    m_pSpriteBossIcon->setTexture(CPetCtrl::Get()->GetPetHeadTexture(pet->getPetInfo().wPetIndexId));

    CCSpriteFrame* sf = CPetCtrl::Get()->GetPetNaturePicSF(pet->getPetInfo().wPetIndexId);
    m_pSpriteBossNature->setDisplayFrame(sf);
}

//一次攻击结束}
void CcbPetBattleLayer::endBattle(uint16 wBattleIndex, uint32 skillId)
{
    //判断有没有连击，如果有，继续攻击，如果没有判断是不是所有人都攻击结束}
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(wBattleIndex);
    if (!pet) {
        return;
    }
    
    CCLOG("战后归位~~~~~~~~~~%d", wBattleIndex);

    bool isEnd = FightAI::Get()->getMyTeam()->getLivePetCount() == 0 || FightAI::Get()->getEnemyTeam()->getLivePetCount() == 0;
    
    //移除正在攻击者}
    if (arrCurFightPet.find(wBattleIndex) != arrCurFightPet.end()) {
        arrCurFightPet.erase(wBattleIndex);
    }
    bool isRealSkill = false;
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, skillId);
    if (ultCfg && ultCfg->byType == 1) {
        isRealSkill = true;
    }
    //技能不占攻击次数}
    if (isRealSkill) {
        int cnt = 0;
        for (int i = 0; i < arrSkillWait.size(); i++) {
            STC_WAIT_BATTLE_DATA wData = arrSkillWait[i];
            if (wData.key == wBattleIndex) {
                wData.frame = -1;
                arrSkillWait[i] = wData;
            }
            
            if (wData.frame == -1) {
                cnt ++;
            }
        }
        if (cnt == arrSkillWait.size()) {
            unschedule(schedule_selector(CcbPetBattleLayer::updateForSkillWaitBattle));
            arrSkillWait.clear();
        }
    }
    else{
        //已攻击人数+1}
        m_AttCnt++;
        pet->updateBuff(FightAI::Get()->getCurRound());
        pet->setLianXieState(E_LIANXIE_STATE_NON);
        if (m_WaitAttCnt > 0) {
            m_WaitAttCnt --;
        }
    }
    
    //判断技能攻击}
    if (arrSkillWait.size() > 0){
        int cnt = 0;

        for (int i = 0; i < arrSkillWait.size(); i++) {
            STC_WAIT_BATTLE_DATA wData = arrSkillWait[i];
            if (wData.frame < 0) {
                continue;
            }
            //同阵营}
            if (abs(wData.key - wBattleIndex) < PetCnt) {
                if (wData.key == wBattleIndex) {
                    wData.frame = 0;
                    arrSkillWait[i] = wData;
                    CCLog("同阵营 延迟攻击~~~~~~~~~~ %d", wData.key);
                    startBattle(wData.key, wData.skillId);
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
            STC_WAIT_BATTLE_DATA wData = arrSkillWait[i];
            if (wData.frame < 0) {
                continue;
            }
            //敌阵营}
            if (abs(wData.key - wBattleIndex) > PetCnt) {
                
                if (arrCurFightPet.size() == 0) {
                    wData.frame = cnt * 10 + 5;
                    arrSkillWait[i] = wData;
                    cnt++;
                }
            }
            
        }
        if (cnt > 0) {
            schedule(schedule_selector(CcbPetBattleLayer::updateForSkillWaitBattle));
            return;
        }
    }
    else{
        if (m_skillBgLayer) {
            m_skillBgLayer->removeFromParentAndCleanup(true);
            m_skillBgLayer = NULL;
        }
    }
    
    if (isStop || m_bIsRoundEnd) {
        pet->setLianXieState(E_LIANXIE_STATE_NON);
        return;
    }
    
    //如果全部攻击结束，回合结束,开始吃掉落物品}
    if (m_AttCnt >= arrEnemyBattleWait.size() || (m_WaitAttCnt == 0 && isEnd)) {
        if (m_pLayerAllBg->getChildByTag(555)) { //连携}
            m_pLayerAllBg->getChildByTag(555)->setVisible(true);
            m_pLayerAllBg->getChildByTag(555)->removeFromParentAndCleanup(true);
        }
        
        if (m_skillBgLayer) {
            m_skillBgLayer->removeFromParentAndCleanup(true);
            m_skillBgLayer = NULL;
        }
        
        isStop = isEnd;
        m_bIsRoundEnd = true;
        this->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                           CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::eatDropThing)),
                                           NULL));
    }
    else if(m_WaitAttCnt == 0)
    {
        if (m_pLayerAllBg->getChildByTag(555)) {//连携}
            m_pLayerAllBg->getChildByTag(555)->setVisible(true);
            m_pLayerAllBg->getChildByTag(555)->removeFromParentAndCleanup(true);
        }
        startBattle(arrEnemyBattleWait[m_AttCnt].key, arrEnemyBattleWait[m_AttCnt].skillId);
    }
}

#pragma mark Round Start
void CcbPetBattleLayer::pauseAll()
{
    CCDirector *director = CCDirector::sharedDirector();
    
    CC_SAFE_RELEASE(pauseActions);
    pauseActions = director->getActionManager()->pauseAllRunningActions();
    CC_SAFE_RETAIN(pauseActions);
    
    CC_SAFE_RELEASE(pauseTargets);
    pauseTargets = director->getScheduler()->pauseAllTargets();
    CC_SAFE_RETAIN(pauseTargets);
    
    director->getScheduler()->resumeTarget(director->getActionManager());
    
    
    for (int i = 1; i <= PetCnt; i++) {
        CCNode* node = m_pLayerPetBattleCtrl_1->getParent()->getChildByTag(i);
        if (!node) {
            continue;
        }
        node->getChildByTag(11)->resumeSchedulerAndActions();
    }
    m_isPauseAll = true;
    this->getScheduler()->resumeTarget(this);
    
    CCDirector::sharedDirector()->getScheduler()->resumeTarget((CCObject*)AppDelegate::sharedAppDelegate()->netClient());
}

void CcbPetBattleLayer::remuseAll()
{
    if (m_skillLayer) {
        m_skillLayer = NULL;
    }
    m_bBossFlag = false;
    
    CCDirector::sharedDirector()->getScheduler()->resumeTargets(pauseTargets);
    CCDirector::sharedDirector()->getActionManager()->resumeTargets(pauseActions);
    m_isPauseAll = false;
    
}

//显示波次动画}
void CcbPetBattleLayer::showWaveAction()
{

}
//波次开始}
void CcbPetBattleLayer::waveStart()
{
    unschedule(schedule_selector(CcbPetBattleLayer::updateForChkDead));
    schedule(schedule_selector(CcbPetBattleLayer::updateForChkDead), 1.0 / 60);

    isStop = true;
    //1、开场动画}
    //2、我方进场动画}
    //3、队长动画 + 队长语音}
    //4、敌方进场}
    
    float time = 0.7;
    float time2 = 0.2;
    if (FightAI::Get()->getCurWave() == 1) {
        //第一会场在在此加载敌方，后面的在过场动画过程中加载}

        loadEnemyTeam();
        //战斗开始，}
        //1、开场动画}
        //2、我方进场动画}
        //3、队长动画 + 队长语音}
        time = showFightStartEff();
        time2 = 1.6;
    }
    if (FightAI::Get()->getCurWave() == FightAI::Get()->getAllWaveCnt()) {
        FightPet *pet = FightAI::Get()->getBoss();
        if (pet) {
            m_bBossFlag = true;
            
            if (FightAI::Get()->getCurWave() != 1) {
                this->runAction(CCSequence::create(CCDelayTime::create(time),
                                                   CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::showBossEff)),
                                                   NULL));
                time += 3.0;
                time2 += 2.5;
            }
            
        }
    }
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(time2),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::showBossHp)),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::enemyRunIn)),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::showPassive)),
                                       NULL
                                       )
                    );
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(time),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::openTouch)),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::roundStart)),
                                       NULL
                                       )
                    );
    m_bWaveFlag = true;
    bSecond = false;
}

//波次结束}
void CcbPetBattleLayer::waveEnd()
{
    FightAI::Get()->waveEnd();
    m_pLayerBossHpBg->setVisible(false);
//    isSkillFight = false;
    
    showPassive();
    refreshBuff();
    
    for (int i = 1; i <= PetCnt; i++) {
        FightPet* pet = FightAI::Get()->getFightPetByBIndex(i);
        if (pet) {
            pet->setIsWaitSkill(false);
            FightPetSprite* sPet = m_mapPet[i];
            sPet->hideAltEff();
            arrBattleCtrl[i-1]->setPower(pet->getCurPower());
        }
    }
    updatePetCtrl();
    
    schedule(schedule_selector(CcbPetBattleLayer::updateForWaveChange));
}

//等待所有怪消失后，切换波次}
void CcbPetBattleLayer::updateForWaveChange(float time)
{
    if (m_isPauseAll) {
        return;
    }
    
    //1、不管我方敌方，只要有已死亡但未消失的，则false，否则true结束}
    bool myHide = true;
    bool enemyHide = true;
    for (int i = 1; i <= PetCnt; i++) {
        FightPetSprite *pSprite = m_mapPet[i];
        if (pSprite && pSprite->getCurHP() <= 0) {
            if (!pSprite->isHide()) {
                myHide = false;
            }
        }

        FightPetSprite *pSpriteE = m_mapPet[i + 100];
        if (pSpriteE && pSpriteE->getCurHP() <= 0) {
            if (!pSpriteE->isHide()) {
                enemyHide = false;
            }
        }

    }
    
    if (myHide && enemyHide) {
        unschedule(schedule_selector(CcbPetBattleLayer::updateForWaveChange));
        
        if (!isStop) {
            roundStart();
        }
        else
        {
            //判断有没有箱子}
            if (mapDropBox.size() > 0 && FightAI::Get()->getMyTeam()->getLivePetCount() > 0) {
                openBox();
                return;
            }
            
            //播放波次动画}
            waveEndAction();
        }
    }
}

//波次结束动画}
void CcbPetBattleLayer::waveEndAction()
{
    //判断有没有箱子}
    if (mapDropBox.size() > 0 && FightAI::Get()->getMyTeam()->getLivePetCount() > 0) {
        openBox();
        return;
    }
    CRole *role = CGameSession::GetRole();
    if (FightAI::Get()->isGameOver() || curRound <= 0) {
        //战斗结束}
//        int res = 0;
        if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE
            || FightAI::Get()->getMyTeam()->getLivePetCount() > 0) {
            m_nRes = 1;
            ShowPetBattleWord::showTextWord(E_WORD_TYPE_FIGHT_FINISH, ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) -fRealHeight*0.5), m_pLayerAllBg);
            
            if ( CheckPointMgr::Get()->FightEndCnt() > 0 ) {
                m_nTalkIdx = 0;
                fRewardWait = 0.2;
//                CheckPointMgr::Get()->addFightEndTalk(m_nTalkIdx, this);
                return;
            }
        }
        else
        {
            //输了}
            m_nRes = 0;
            
            CMusicCtrl::StopBackgroundMusic();
            
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_pve_lose));
            
            ShowPetBattleWord::showTextWord(E_WORD_TYPE_LOSE, ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) -fRealHeight*0.5), m_pLayerAllBg);
            
            
        }
        
        //这地方为什么以这样一大坨东西}
        //因为要判断战斗结束后的跳转啊！！！进入战斗的渠道很多啊！！！}
        // 新手假战斗跳转
        if (role->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_END_1_TALK) {
            GuideData::GetInstance()->addGuideLayer();  // 增加战斗结束的说话版}
            pauseAll();
            return;
        }
        fRewardWait = 2.0;
        fightVerify();
    }
    else
    {
        FightAI::Get()->waveStart();
        //大魔王出现
        if (role->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_BOSS_1_TALK) {
            pauseAll();
            GuideData::GetInstance()->addGuideLayer();
            
            return;
        }
        
        //播放波次动画}
        this->runAction(CCSequence::create(
                                           CCDelayTime::create(0.8),
                                           CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::loadEnemyTeam)),
                                           NULL));
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        imgTrans->runAction(CCSequence::create(
                                               CCDelayTime::create(0.3),
                                               CCMoveBy::create(0.5, ccp(winSize.width + 150, 0)),
                                               CCDelayTime::create(0.5),
                                               CCMoveBy::create(0.5, ccp(-(winSize.width + 150), 0)),
                                               CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::waveStart)),
                                               NULL
                                               )
                            );
    }
}

void CcbPetBattleLayer::fightVerify() {
    CRole* role = CGameSession::GetRole();
    
    STC_BATTLE_PRE_DATA perData;
    perData.wUserLv = role->GetwRoleLv();
    perData.dwCurExp = role->GetdwRoleExp();
    perData.dwCurEnergy = role->GetdwEnergy();
    perData.byCurFightCnt = role->GetdwBattleBagCnt();
    
    uint16 mapId = 0;
    uint16 stageId = 0;
    
    switch (FightAI::Get()->getFightType()) {
        case E_BATTLE_TYPE_TOWER:
            mapId = g_TowerDataMgr->GetCurBattleFloor();
            stageId = g_TowerDataMgr->GetCurBattleFloor();
            break;
        case E_BATTLE_TYPE_WRESTLE:
        {
            stageId = g_ChallengeDataMgr->getCurFightStage();
        }
            break;
        case E_BATTLE_TYPE_MAP:
        {
            perData.dwPrePassStage = role->GetwPassStageId();
        }
        case E_BATTLE_TYPE_COIN_TREE:
        case E_BATTLE_TYPE_HERO_MAP:
        {
            StageCtrl::STC_STAGE stc = StageCtrl::Get()->selectedStage();
            mapId = MapCtrl::nSelectedMapId;
            stageId = stc.wStageId;
            
            perData.dwCurEnergy -= stc.byCostEnergy;
        }
            break;
        case E_BATTLE_TYPE_ACTIVE_MAP:
        {
            StageCtrl::STC_STAGE *stage = StageCtrl::Get()->getStageByStageId(StageCtrl::Get()->getSelectStageId());
            if (stage) {
                stageId = stage->wStageId;
                
                perData.dwCurEnergy -= stage->byCostEnergy;
            }
            mapId = MapCtrl::nSelectedMapId;
            
            break;
        }
        default:
            break;
    }
    
    FightAI::Get()->setPerData(perData);
    
    FightAI::Get()->setCoinCatDamage(allDamage);
    FightAI::Get()->setCoinCatMoney(allDamage* ((float)FightAI::Get()->getDamFloat().dwCoinCatFloat / 10000));
    CGameSession::SendPveFightResult(FightAI::Get()->getFightType(), mapId, stageId, FightAI::Get()->getMyTeam()->getDeadPetCount(), m_nRes, allDamage, FightAI::Get()->getCoinCatMoney());
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    return;
}

void CcbPetBattleLayer::bossTransform() {
    loadEnemyTeam();
    //显示大魔王
    CcbPetBattleBossLayer* bossLayer = dynamic_cast<CcbPetBattleBossLayer*>(CcbManager::sharedManager()->LoadCcbPetBattleBossLayer());
    if (bossLayer) {
        bossLayer->setDelagate(this);
        FightPet* pet = FightAI::Get()->getFightPetByBIndex(103);
        bossLayer->setBossId(pet->getPetInfo().wPetIndexId);
        
        CCDirector::sharedDirector()->getRunningScene()->addChild(bossLayer, 9999);
    }
    
    enemyRunIn();
    openTouch();
}

//回合开始}
void CcbPetBattleLayer::roundStart()
{
    FightAI::Get()->roundStart();
    showPassive();
    //加载buff}
    refreshBuff();
    m_bIsRoundEnd = false;
    curRoundDamage = 0;
    arrEnemyBattleWait.clear();
    arrSkillWait.clear();
    arrCurFightPet.clear();
    autoAttack();
    
    // 加入说话弹版}
    // 普通攻击结束，大招点亮，此时加入大招指示手势}
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();

    if ( wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_1) {
        if (bSecond) {
            if (m_bWaveFlag) {
                pauseAll();
                GuideData::GetInstance()->addGuideLayer();
                m_bWaveFlag = false;
            }
        } else {
            bSecond = true;
        }
    }
    
    // add talk pad
    if ( m_bBossFlag && CheckPointMgr::Get()->talkPadCnt() > 0 ) {
        pauseAll();
        m_nTalkIdx = 0;
        CheckPointMgr::Get()->addBossTalk(m_nTalkIdx, this);
    }
}

//回合结束}
void CcbPetBattleLayer::roundEnd()
{
    m_isFighting = false;
    
    arrWaitBattleData.clear();
    
    m_WaitAttCnt = 0;
    m_AttCnt = 0;
    
    curRound--;
    
    m_pLabelTTFCoinCat_CurRound->setString(CCString::createWithFormat("%d / %d",curRound, FightAI::Get()->getAllRound())->getCString());
    
    if (!isStop) {
        //buff结算}
        FightAI::Get()->roundEnd();
        showPassive();
        FightAI::Get()->buffActive();
        buffActive();
        
        refreshBuff();
        updatePetCtrl();
        //到达限制回合数，强制判输}
        if (curRound <= 0) {
            FightAI::Get()->getMyTeam()->SetTeamHp(0);
            waveEndAction();
            return;
        }
        
        schedule(schedule_selector(CcbPetBattleLayer::updateForWaveChange));
        
    }
    else {
        waveEnd();
    }
}

//buff结算}
void CcbPetBattleLayer::buffActive()
{
    for (int i = 1; i <= PetCnt; i++) {
        FightPet *petM = FightAI::Get()->getFightPetByBIndex(i);
        if (petM) {
            if (petM->getCurHP() <= 0 && petM->getIsCanDead()) {
                continue;
            }
            FightPetSprite *pSprite = m_mapPet[i];
            pSprite->buffActive(petM->getArrBuffValue());
        }
        
        FightPet *petE = FightAI::Get()->getFightPetByBIndex(i + 100);
        if (petE) {
            if (petE->getCurHP() <= 0 && petE->getIsCanDead()) {
                continue;
            }
            FightPetSprite *pSprite = m_mapPet[i + 100];
            pSprite->buffActive(petE->getArrBuffValue());
        }
    }
}

//刷新队伍buff}
void CcbPetBattleLayer::refreshBuff()
{
    for (int i = 1; i <= PetCnt; i++) {
        FightPet *petMy = FightAI::Get()->getFightPetByBIndex(i);
        if (petMy) {
            FightPetSprite *pSprite = m_mapPet[i];
            if (pSprite) {
                pSprite->setMapBuff(petMy->getMapBuff());
                pSprite->setArrEff(petMy->getArrEff());
                pSprite->reflashBuff();
                pSprite->showEff();
                
                setPetCtrlSpecial(petMy->getPetInfo().wBattleIndex);
            }
            
        }
        
        FightPet *petEnemy = FightAI::Get()->getFightPetByBIndex(i+100);
        if (petEnemy) {
            if (petEnemy->getIsCanDead()&&petEnemy->getCurHP()<=0) {
                continue;
            }
            FightPetSprite *pSprite = m_mapPet[i+100];
            if (!pSprite) {
                continue;
            }
            pSprite->setMapBuff(petEnemy->getMapBuff());
            pSprite->setArrEff(petEnemy->getArrEff());
            pSprite->reflashBuff();
            pSprite->showEff();
        }
    }
}
#pragma mark Action
//显示boss动画}
void CcbPetBattleLayer::showBossEff()
{
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    ShowPetBattleWord::showTextWord(E_WORD_TYPE_BOSS_WARNING, ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) - fRealHeight*0.5), m_pLayerAllBg);
}

//我方进场动画}
void CcbPetBattleLayer::petInEff()
{
    float time = 0.1;
    
    std::map<uint16, FightPetSprite*>::iterator it = m_mapPet.begin();
    for (; it != m_mapPet.end(); it++) {
        if (it->second && it->first <= PetCnt) {
            it->second->showRunIn();
            time = 1.2;
        }
    }
}
//显示队长技能动画}
void CcbPetBattleLayer::showLeaderSkillLayer()
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
            m_mapPet[i]->showLeaderEff();
        }
    }
}

//显示战斗开始动画}
float  CcbPetBattleLayer::showFightStartEff()
{
    ShowPetBattleWord::showTextWord(E_WORD_TYPE_FIGHT_START, ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) - fRealHeight*0.5), m_pLayerAllBg);
    
    float time = 1.0;
    this->runAction(CCSequence::create(CCDelayTime::create(time),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::petInEff)),
                                       CCDelayTime::create(1.2),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::showLeaderSkillLayer)),
                                       NULL));
    
    return time + 1.2 + 1.0;
}
//显示大招点击时特效}
void CcbPetBattleLayer::showBattleCtrlTouchEff(uint16 wBattleId)
{
    if (wBattleId > PetCnt) {
        return;
    }
    EffectLayer* eff = EffectLayer::create(E_ANI_EFFECT_BATTLE_CTRL_TOUCH, 0.1);
    eff->ignoreAnchorPointForPosition(false);
    eff->setAnchorPoint(ccp(0, 0));
    eff->setSpriteAdd();
    eff->setPosition(arrBattleCtrl[wBattleId - 1]->getPosition() + ccp(28, 80 + 7));
    eff->setAnchorPoint(arrBattleCtrl[wBattleId - 1]->getAnchorPoint());
    m_pLayerPetBattleCtrl_1->getParent()->addChild(eff, E_ZORDER_PET_CTRL + 1, wBattleId);
    
    eff->onRun();
}
//显示主动技能动画}
void CcbPetBattleLayer::showSkillLayer(uint16 wBattleId, uint32 dwSkillId)
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
        uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
        if (!m_skillLayer && wTrigger >= GuideData::E_GUIDE_TRIGGER_BOSS_1_TALK) {
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
void CcbPetBattleLayer::showEnemyUltSkill(std::string strName)
{
    m_pLabelTTFEnemyAltName->setString(strName.c_str());
    m_pSpriteEnemyAltBg->runAction(CCSequence::create(CCShow::create(),
                                                      CCDelayTime::create(2),
                                                      CCHide::create(),
                                                      NULL));
}

//显示自动触发被动技能}
void CcbPetBattleLayer::showPassive()
{
    //波次开始和结束时，刷新两队被动技能，普通时只刷当前攻击队伍的}
    //改成了按速度攻击，所以每回合开始、结束的时候也都刷全部队伍的被动技能}
    int k = 1;

    for (int i = 1; i <= PetCnt; i++) {
        FightPet *petM = FightAI::Get()->getFightPetByBIndex(i);
        if (petM) {
            if (petM->getCurHP() <= 0 && petM->getIsCanDead()) {
                continue;
            }
            FightPetSprite *pSprite = m_mapPet[i];
            pSprite->showPassive(petM->arrTriggerPassiveSkill, true);
        }
        
        FightPet *pet = FightAI::Get()->getFightPetByBIndex(i + k*100);
        if (pet) {
            if (pet->getCurHP() <= 0 && pet->getIsCanDead()) {
                continue;
            }
            FightPetSprite *pSprite = m_mapPet[i + k*100];
            pSprite->showPassive(pet->arrTriggerPassiveSkill, true);
        }
    }
}

#pragma mark Eat Drop Item
//精灵死亡}
void CcbPetBattleLayer::showDeadEff(uint16 wBattleId){
    
    FightPetSprite* mc = getFightPetSprite(wBattleId);
    
    CCParticleSystemQuad* eff = CCParticleSystemQuad::create("effect/eff_526.plist");
    eff->setScale(0.5);
    eff->setPosition(mc->getMyPos() + ccp(0, mc->getStandSize().height*0.5));
    m_pLayerAllBg->addChild(eff, mc->getZOrder() + 1);
    
    FightPet*pet = FightAI::Get()->getFightPetByBIndex(wBattleId);
    if (pet && pet->getPetInfo().isEgg) {
        eff->runAction(CCSequence::create(CCDelayTime::create(1.5),
                                          CCEaseIn::create(CCMoveTo::create(0.5, ccp(getCenterX(m_pSpriteEggBg) + getLeft(m_pNodeNormalReward), getCenterY(m_pSpriteEggBg)+getBottom(m_pNodeNormalReward))), 2),
                                          CCHide::create(),
                                          CCCallFuncN::create(this, callfuncN_selector(CcbPetBattleLayer::removeDeadEff)),
                                          CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::addEgg)), NULL));
    }
    else{
        eff->runAction(CCSequence::create(CCDelayTime::create(1.5),
                                          CCHide::create(),
                                          CCCallFuncN::create(this, callfuncN_selector(CcbPetBattleLayer::removeDeadEff)),
                                          NULL));
    }
    
}

void CcbPetBattleLayer::removeDeadEff(CCNode* node)
{
    if (node) {
        node->removeFromParentAndCleanup(true);
    }
}

void CcbPetBattleLayer::addEgg()
{
    CMusicCtrl::PlayEffect( GET_MUSIC(Eff_gacha_pet) );
    CCActionInterval *actP = CCSequence::create(CCScaleTo::create(0.1, 1.1), CCScaleTo::create(0.1, 1), NULL);
    CCString *str = NULL;
    m_curEgg += 1;
    str = CCString::createWithFormat("%d", m_curEgg);
    m_pLabelTTFEgg->setString(str->getCString());
    
    m_pSpriteEggBg->runAction(actP);
}


//掉落箱子}
void CcbPetBattleLayer::dropBox(uint16 wEnemyIndxe)
{
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(wEnemyIndxe);
    if (!pet) {
        return;
    }
    
    if (pet->getPetInfo().boxItem.size() == 0) {
        return;
    }
    
    for (int i = 0; i < pet->getPetInfo().boxItem.size() ; i++) {
        STC_ITEM_DROP item = pet->getPetInfo().boxItem[i];
        
        CcbDropBoxLayer *box = dynamic_cast<CcbDropBoxLayer*>(CcbManager::sharedManager()->LoadCcbDropBoxLayer(this));
        CCPoint pos;
        if (wEnemyIndxe > PetCnt) {
            pos = arrEnemyPos[wEnemyIndxe % 100 - 1] + ccp(0, 20);
        }
        else
        {
            pos = arrPetPos[wEnemyIndxe % 100 - 1] + ccp(0, 20);
        }
        box->setPosition(pos);
        m_pLayerAllBg->addChild(box, E_ZORDER_PET_MC - pos.y);
        
        box->runDrop();
        mapDropBox[box] =  item;
    }
    
};

//开箱子}
void CcbPetBattleLayer::openBox(CCLayer *box)
{
    isEatBox = true;
    CcbDropBoxLayer *dBox = dynamic_cast<CcbDropBoxLayer*>(box);
    if (!dBox) {
        return;
    }
    if (mapDropBox.find(dBox) != mapDropBox.end()) {
        dBox->runOpen();
        STC_ITEM_DROP item = mapDropBox[dBox];
        mapDropBox.erase(dBox);
        int n = item.wCount;
        
        if (item.wItemType / E_UNITE_BASE_FABIO == E_UNITE_TYPE_SPECIAL
            &&
            ( item.wItemType % E_UNITE_BASE_FABIO == E_SPECIAL_ID_COIN
             || item.wItemType % E_UNITE_BASE_FABIO == E_SPECIAL_ID_FARM_RES )) {
                n = rand() % (10 - 3) + 7;
            }
        
        for (int i = 0; i < n; i++) {
            STC_ITEM_DROP dItem;
            dItem.wItemType = item.wItemType;
            dItem.wValue = item.wCount / n;
            if (i == 0) {
                dItem.wValue += item.wCount % n;
            }
            
            DropItemSprite *itemSprite = DropItemSprite::create(item.wItemType);

            itemSprite->setPosition(dBox->getPosition());
            m_pLayerAllBg->addChild(itemSprite, dBox->getZOrder() + 1);
            itemSprite->setItem(dItem);
            itemSprite->runAct();
            dropItemFly(itemSprite);
        }
    }
}

void CcbPetBattleLayer::openBox()
{
    isEatBox = true;
    std::map<CcbDropBoxLayer*, STC_ITEM_DROP>::iterator it = mapDropBox.begin();
    
    while (it != mapDropBox.end()) {
        if (!it->first) {
            it++;
            continue;
        }
        openBox(it->first);
        it = mapDropBox.begin();
    }
    mapDropBox.clear();
    
    waitTime = 120;

    schedule(schedule_selector(CcbPetBattleLayer::waitToEatDrop));
    
    
}

//掉物品}
void CcbPetBattleLayer::dropItem(uint16 wEnemyIndex, STC_ITEM_DROP item)
{    
    DropItemSprite *itemSprite = DropItemSprite::create(item.wItemType);

    itemSprite->setPosition(ccpAdd(arrEnemyPos[wEnemyIndex % 100 -1] , ccp(0, 20)));
    m_pLayerAllBg->addChild(itemSprite, E_ZORDER_PET_MC - arrEnemyPos[wEnemyIndex % 100 -1].y + 1);
    if (item.wItemType == E_UNITE_BASE_FABIO * E_UNITE_TYPE_SPECIAL + E_SPECIAL_ID_HEART) {
        itemSprite->setZOrder(E_ZORDER_PET_MC - arrEnemyPos[wEnemyIndex % 100 -1].y + 2);
    }
    itemSprite->runAct();
    itemSprite->setItem(item);
    arrHeartSprite.push_back(itemSprite);
}

void CcbPetBattleLayer::eatDropThing()
{
    arrWaitBattleData.clear();
    
    for (int i = 0; i < arrHeartSprite.size(); i++) {
        dropItemFly(arrHeartSprite[i], true);
    }
    
    waitTime = 60;

    if (arrHeartSprite.size() == 0) {
        waitTime = 10;
    }
    schedule(schedule_selector(CcbPetBattleLayer::waitToEatDrop));
}

void CcbPetBattleLayer::dropItemFly(DropItemSprite* imgItem, bool isHeart)
{
    float time1 = 0.01;
    float time2 = 0.5;
    float time3 = 1.5;
    if (isHeart) {
        time3 = 0.1;
    }
    uint8 r = rand() % 20 + 1;
    CCActionInterval *act = NULL;
    
    STC_ITEM_DROP item = imgItem->getItem();
    //根据item的类型判断应该飞往何处}
    //如果材料，直接消失；如果是金币或者蛋，飞往对应图标处；如果是心珠，飞到血条处}
    switch (item.wItemType / E_UNITE_BASE_FABIO) {
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_EQUIP:
        case E_UNITE_TYPE_GEM:
            act = CCSequence::create(CCDelayTime::create(time3),
                                     CCFadeOut::create(time2),
                                     NULL);
            break;
        case E_UNITE_TYPE_PET:
            act = CCSequence::create(CCDelayTime::create(time3 + 1),
                                     CCDelayTime::create(r*time1),
                                     CCEaseIn::create(CCMoveTo::create(time2, ccp(getCenterX(m_pSpriteEggBg) + getLeft(m_pNodeNormalReward), getCenterY(m_pSpriteEggBg)+getBottom(m_pNodeNormalReward))), 2),
                                     CCHide::create(),
                                     CCCallFuncN::create(this, callfuncN_selector(CcbPetBattleLayer::callBackItemFly)), NULL);
            
            break;
        case E_UNITE_TYPE_SPECIAL:
            switch (item.wItemType % E_UNITE_BASE_FABIO) {
                case E_SPECIAL_ID_COIN:
                    if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE) {
                        act = CCSequence::create(CCDelayTime::create(time3),
                                                 CCDelayTime::create(r*time1),
                                                 CCEaseIn::create(CCMoveTo::create(time2, getCenter(m_pSpriteCoinCat_CoinBg) + ccp(getLeft(m_pNodeCoinCatReward), getBottom(m_pNodeCoinCatReward))), 2),
                                                 CCHide::create(),
                                                 CCCallFuncN::create(this, callfuncN_selector(CcbPetBattleLayer::callBackItemFly)),NULL);
                    }
                    else
                    {
                        act = CCSequence::create(CCDelayTime::create(time3),
                                                 CCDelayTime::create(r*time1),
                                                 CCEaseIn::create(CCMoveTo::create(time2, getCenter(m_pSpriteCoinBg) + ccp(getLeft(m_pNodeNormalReward), getBottom(m_pNodeNormalReward))), 2),
                                                 CCHide::create(),
                                                 CCCallFuncN::create(this, callfuncN_selector(CcbPetBattleLayer::callBackItemFly)),NULL);
                    }
                    break;
                case E_SPECIAL_ID_FARM_RES:
                    act = CCSequence::create(CCDelayTime::create(time3),
                                             CCDelayTime::create(r*time1),
                                             CCEaseIn::create(CCMoveTo::create(time2, ccp(getCenterX(m_pSpriteSoulBg) + getLeft(m_pNodeNormalReward), getBottom(m_pSpriteSoulBg)+getCenterY(m_pNodeNormalReward))), 2),
                                             CCHide::create(),
                                             CCCallFuncN::create(this, callfuncN_selector(CcbPetBattleLayer::callBackItemFly)),NULL);
                    break;
                case E_SPECIAL_ID_HEART:
                {
                    //吃该心珠的宠物fightId}
                    item.wHasCount = FightAI::Get()->getMyTeam()->eatHeart(FightAI::Get()->getCurRound());
                    
                    FightPet* pet = FightAI::Get()->getFightPetByBIndex(item.wHasCount);
                    
                    if (!pet) {
                        return;
                    }
                    //存回复的血量}
                    item.wCount = pet->eatHeart(1, FightAI::Get()->getCurRound());
                    
                    FightPetSprite *petSp = getFightPetSprite(item.wHasCount);
                    
                    act = CCSequence::create(CCDelayTime::create(time3),
                                             CCDelayTime::create(r*time1),
                                             CCEaseIn::create(CCMoveTo::create(time2, ccpAdd(petSp->getMyPos(), ccp(0, petSp->getStandSize().height*0.5))), 2),
                                             CCHide::create(),
                                             CCCallFuncN::create(this, callfuncN_selector(CcbPetBattleLayer::callBackItemFly)),NULL);
                }
                    
                    break;
                default:
                    break;
            }
            break;
        default:
            act = (CCActionInterval*)CCFadeOut::create(time2);
            
            break;
    }
    imgItem->setItem(item);
    imgItem->runAction(act);
}

void CcbPetBattleLayer::callBackItemFly(CCNode *node)
{
    waitTime = 20;

    STC_ITEM_DROP item = ((DropItemSprite*)node)->getItem();
    node->removeFromParentAndCleanup(true);
    //    node->release();
    CCActionInterval *actP = CCSequence::create(CCScaleTo::create(0.1, 1.1), CCScaleTo::create(0.1, 1), NULL);
    CCString *str = NULL;
    int hp = 0;
    
    switch (item.wItemType / E_UNITE_BASE_FABIO) {
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_EQUIP:
        case E_UNITE_TYPE_GEM:
            break;
        case E_UNITE_TYPE_PET:
            m_curEgg += 1;
            str = CCString::createWithFormat("%d", m_curEgg);
            m_pLabelTTFEgg->setString(str->getCString());
            
            m_pSpriteEggBg->runAction(actP);
            break;
        case E_UNITE_TYPE_SPECIAL:
            switch (item.wItemType % E_UNITE_BASE_FABIO) {
                case E_SPECIAL_ID_COIN:
                    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_buy_good));
                    m_curCoin += item.wValue;
                    str = CCString::createWithFormat("%d", m_curCoin);
                    if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE) {
                        m_pLabelTTFCoinCat_Coin->setString(str->getCString());
                        
                        m_pSpriteCoinCat_CoinBg->runAction(actP);
                    }
                    else
                    {
                        m_pLabelTTFCoin->setString(str->getCString());
                        
                        m_pSpriteCoinBg->runAction(actP);
                    }
                    break;
                case E_SPECIAL_ID_FARM_RES:
                    m_curSoul += item.wValue;
                    str = CCString::createWithFormat("%d", m_curSoul);
                    m_pLabelTTFSoul->setString(str->getCString());
                    
                    m_pSpriteSoulBg->runAction(actP);
                    break;
                case E_SPECIAL_ID_HEART:
                    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_heart_heal));
                    hp =  item.wCount;
                    str = CCString::createWithFormat("%d", hp);
                    addHp(item.wHasCount, hp);
                    //心珠计算}
                {
                    FightPetSprite *petSp = getFightPetSprite(item.wHasCount);
                    ShowPetBattleWord::showWord(str->getCString(), E_WORD_TYPE_HP, ccpAdd(petSp->getMyPos(), ccp(0, petSp->getStandSize().height*0.5)), m_pLayerAllBg);
                }
                    break;
                default:
                    break;
            }
        default:

            break;
    }
    
}

void CcbPetBattleLayer::waitToEatDrop(float item)
{
    if (waitTime > 0) {
        waitTime--;
        return;
    }
    unschedule(schedule_selector(CcbPetBattleLayer::waitToEatDrop));
    arrHeartSprite.clear();
    doAfterEat();
}

void CcbPetBattleLayer::doAfterEat()
{
    if (isEatBox) {
        //播放波次动画}
        isEatBox = false;
        waveEndAction();
    }
    else
    {
        roundEnd();
    }
}

//更新精灵ctrl}
void CcbPetBattleLayer::updatePetCtrl()
{
    //更新精灵icon状态}
    for (int i = 0; i < PetCnt; i++) {
        CcbPetBattleCtrl *ctrl = arrBattleCtrl[i];
        STC_PET_CTRL_INFO info = ctrl->getPetCrtlInfo();
        if (!info.petIndex) {
            continue;
        }
        
        FightPet *pet = FightAI::Get()->getMyTeam()->GetTeam()[info.petBattleIndex];
        if (!pet) {
            continue;
        }
        info.curSkillValue = pet->getIsWaitSkill() ? 0 : pet->getCurPower();

        ctrl->setPower(info.curSkillValue);
    }
}

void CcbPetBattleLayer::setPetCtrlSpecial(uint16 wBattleIndex)
{
    if (wBattleIndex > PetCnt) {
        return;
    }
    CcbPetBattleCtrl *ctrl = arrBattleCtrl[wBattleIndex - 1];
    if (!ctrl) {
        return;
    }
    
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(wBattleIndex);
    if (!pet || pet->getCurHP() == 0) {
        return;
    }
    //麻痹}
    ctrl->setIsPalsy(pet->HasPalsyBuff(FightAI::Get()->getCurRound()));
    //混乱}
    ctrl->setIsConfused(pet->HasConfusedBuff(FightAI::Get()->getCurRound()));
    //封锁}
    ctrl->setIsSeal(pet->HasSealBuff(FightAI::Get()->getCurRound()));
    //冰冻
    ctrl->setIsBingDong(pet->HasFrozenBuff(FightAI::Get()->getCurRound()));
    //中毒
    ctrl->setIsZhongdu(pet->HasPoisonBuff(FightAI::Get()->getCurRound()));
    //灼烧
    ctrl->setIsZhuoShao(pet->HasFiringBuff(FightAI::Get()->getCurRound()));
}

//战斗结果 1验证成功，0验证失败}
void CcbPetBattleLayer::handlerPVEResult(WorldPacket& packet)
{
    /*
             -- 如果是最后一关，跳到大地图界面
     战斗胜利<
             -- 如果不是最后一关，跳回关卡界面
     
     战斗失败 -- 跳出失败弹版，点击跳回开战界面
     验证失败 -- 跳回开战界面
     */

    
    PetLoadingLayer::sharedLayer()->End();
    uint8 res = 0;
    packet >> res;
    if (res) {
         if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE) {
             this->runAction(
                             CCSequence::create(
                                                CCDelayTime::create(fRewardWait),
                                                CCFadeOut::create(0.5),
                                                CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::gotoReward)),
                                                NULL
                                                )
                             );
             return;
         }

        if (FightAI::Get()->getMyTeam()->getLivePetCount() == 0) {
            // 战斗失败}
            
            if (
                FightAI::Get()->getFightType() == E_BATTLE_TYPE_MAP ||
                FightAI::Get()->getFightType() == E_BATTLE_TYPE_HERO_MAP ||
                FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE ||
                FightAI::Get()->getFightType() == E_BATTLE_TYPE_ACTIVE_MAP
                ) {
                int _type = StageCtrl::Get()->kind();
                int _MapId = MapCtrl::nSelectedMapId;
                int _stageId = StageCtrl::Get()->selectedStage().wStageId;
                if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_ACTIVE_MAP) {
                    _stageId = StageCtrl::Get()->getSelectStageId();
                }
                
                snprintf(strBuf64, BUFFER_SIZE_64, "type:%d_%d_%d", _type, _MapId, _stageId);
                AnalysicsManager::sharedAnalyticsMgr()->failMission(strBuf64, "lose_battle");
            }
            
            this->runAction(CCSequence::create(CCDelayTime::create(2.5),
                                               CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::onLoseBattle)),
                                               NULL));
        }
        else
        {
            this->runAction(CCSequence::create(CCDelayTime::create(fRewardWait),
                                               CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::gotoReward)),
                                               NULL));
        }
    }
    else
    {
        ShowPetBattleWord::showTextWord(E_WORD_TYPE_LOSE, ccp(getWidth(m_pLayerAllBg) * 0.5, getHeight(m_pLayerAllBg) - fRealHeight*0.5), m_pLayerAllBg);

        if (
            FightAI::Get()->getFightType() == E_BATTLE_TYPE_MAP ||
            FightAI::Get()->getFightType() == E_BATTLE_TYPE_HERO_MAP ||
            FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE ||
            FightAI::Get()->getFightType() == E_BATTLE_TYPE_ACTIVE_MAP
            ) {
            int _type = StageCtrl::Get()->kind();
            int _MapId = MapCtrl::nSelectedMapId;
            int _stageId = StageCtrl::Get()->selectedStage().wStageId;
            if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_ACTIVE_MAP) {
                _stageId = StageCtrl::Get()->getSelectStageId();
            }
            snprintf(strBuf64, BUFFER_SIZE_64, "type:%d_%d_%d", _type, _MapId, _stageId);
            AnalysicsManager::sharedAnalyticsMgr()->failMission(strBuf64, "fail_verified");
        }
        
        this->runAction(CCSequence::create(CCDelayTime::create(3.0),
                                           CCFadeOut::create(0.5),
                                           CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::failVerified)),
                                           NULL));
    }
    
}

//跳转到结算面板}
void CcbPetBattleLayer::gotoReward()
{
    if (
        FightAI::Get()->getFightType() == E_BATTLE_TYPE_MAP ||
        FightAI::Get()->getFightType() == E_BATTLE_TYPE_HERO_MAP
        ) {
        int _type = StageCtrl::Get()->kind();
        int _MapId = MapCtrl::nSelectedMapId;
        int _stageId = StageCtrl::Get()->selectedStage().wStageId;
        snprintf(strBuf64, BUFFER_SIZE_64, "type:%d_%d_%d", _type, _MapId, _stageId);
        AnalysicsManager::sharedAnalyticsMgr()->completeMission(strBuf64);
    } else if (
               FightAI::Get()->getFightType() == E_BATTLE_TYPE_COIN_TREE ||
               FightAI::Get()->getFightType() == E_BATTLE_TYPE_ACTIVE_MAP
               ) {
        int _MapId = MapCtrl::nSelectedMapId;
        int _stageId = StageCtrl::Get()->selectedStage().wStageId;
        if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_ACTIVE_MAP) {
            _stageId = StageCtrl::Get()->getSelectStageId();
        }
        snprintf(strBuf64, BUFFER_SIZE_64, "active:%d_%d", _MapId, _stageId);
        AnalysicsManager::sharedAnalyticsMgr()->completeMission(strBuf64);
    }
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (
        wTrigger == GuideData::E_GUIDE_TRIGGER_FIR_END_ATTACK ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_SEC_END_ATTACK ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_THI_END_ATTACK ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_FOUR_END_ATTACK ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_FIVE_END_ATTACK
        ) {
        GuideData::GetInstance()->stepOver();
        GuideData::GetInstance()->connectToServer();
    }
    
    // 判断是否通关当前地图点
    MapCtrl::hasNewMapPointOpen();
    
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
        if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_TOWER) {
            BackCtrl::JumpToScene(kTowerMainScene);
            return;
        }
        else if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_WRESTLE)
        {
            BackCtrl::JumpToScene(kChallengeMapScene);
            return;
        }
    }
    CcbFightRewardLayer::showReward();
}

void CcbPetBattleLayer::showStep()
{
    m_nTalkIdx++;
    if (m_bBossFlag) {
        if (m_nTalkIdx >= CheckPointMgr::Get()->talkPadCnt() ) {
            remuseAll();
            return;
        }
        
        CheckPointMgr::Get()->addBossTalk(m_nTalkIdx, this);
    } else {
        if (m_nTalkIdx >= CheckPointMgr::Get()->FightEndCnt()) {
            fightVerify();
            return;
        }
        
        CheckPointMgr::Get()->addFightEndTalk(m_nTalkIdx, this);
    }
}


//屏幕抖动}
void CcbPetBattleLayer::doShake()
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
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBattleLayer::callBackShake)),
                                       NULL));
}

//屏幕抖动回调}
void CcbPetBattleLayer::callBackShake()
{
    m_actShake = NULL;
    m_isShake = false;
}

