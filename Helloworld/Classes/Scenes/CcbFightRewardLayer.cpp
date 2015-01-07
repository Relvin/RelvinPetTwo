#include "CcbFightRewardLayer.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "FightAI.h"
#include "BackCtrl.h"
#include "PetBattleData.h"
#include "StageScene.h"
#include "MapScene.h"
#include "Role.h"
#include "GuideData.h"
#include "TowerDataMgr.h"
#include "ResourceStringClient.h"
#include "ChallengeDataMgr.h"
#include "UISupport.h"
#include "CCScrollViewWithBar.h"
#include "CcbItemIconLayer.h"
#include "ResourceDefine.h"
#include "CcbUserLvUpLayer.h"
#include "CcbShareFrameLayer.h"
#include "MusicCtrl.h"
#include "CcbSystemBootInfoLayer.h"
#include "GlobalData.h"
#include "PetLoadingLayer.h"
#include "CcbWorldLootLayer.h"
#include "CcbMJShopFindLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;


FightRewardScene::FightRewardScene()
{
    
}
FightRewardScene::~FightRewardScene()
{
    
}
CCScene *FightRewardScene::scene()
{
    CCScene *scene = CCScene::create();
    FightRewardScene *layer = FightRewardScene::create();
    layer->setTag(1);
    scene->addChild(layer);
    return scene;
}
bool FightRewardScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CcbFightRewardLayer *layer = dynamic_cast<CcbFightRewardLayer*>(CcbManager::sharedManager()->LoadCcbFightRewardLayer(this));
    layer->setTag(1);
    addChild(layer);
    return true;
}

void CcbFightRewardLayer::showReward()
{
    CcbFightRewardLayer *layer = dynamic_cast<CcbFightRewardLayer*>(CcbManager::sharedManager()->LoadCcbFightRewardLayer(NULL));
    layer->ignoreAnchorPointForPosition(false);
    layer->setAnchorPoint(ccp(0.5, 0.5));
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    layer->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
}

CcbFightRewardLayer::~CcbFightRewardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteStar_1);
	CC_SAFE_RELEASE_NULL(m_pSpriteStar_2);
	CC_SAFE_RELEASE_NULL(m_pSpriteStar_3);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFGetMoney);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFGetExp);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
	CC_SAFE_RELEASE_NULL(m_pSpriteExpBar);
	CC_SAFE_RELEASE_NULL(m_pSpriteItemIcon);
	CC_SAFE_RELEASE_NULL(m_pLayerRward);
	CC_SAFE_RELEASE_NULL(m_pControlButtonContinue);
	CC_SAFE_RELEASE_NULL(m_pControlButtonShare);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFStageName);
    CC_SAFE_RELEASE_NULL(m_pSpriteZhuanlun);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDropDes);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDropType);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFightRewardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFightRewardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFightRewardLayer", CcbFightRewardLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/fight_exp_reward.ccb]", [ccb/fight_exp_reward.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/fight_item_reward.ccb]", [ccb/fight_item_reward.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/fight_pet_reward.ccb]", [ccb/fight_pet_reward.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight_reward.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFightRewardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    setTouchEnabled(true);
	return true;
}

void CcbFightRewardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
    
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Bgm_main_scene));
    
    if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_TOWER
        || FightAI::Get()->getFightType() == E_BATTLE_TYPE_WRESTLE
        || FightAI::Get()->getFightType() == E_BATTLE_TYPE_BOSS)
    {
        loadData();
        return;
    }
    //判断关卡通关解锁}
    StageCtrl::STC_STAGE stc = StageCtrl::Get()->selectedStage();
    STC_BATTLE_PRE_DATA preData = FightAI::Get()->getPerData();
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage
        && preData.dwPrePassStage < stc.wStageId) {
        uint16 sysLockId = GuideData::GetInstance()->checkSystemLock(GuideData::E_GUIDE_UNLOCK_TYPE_STAGE);
        SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, sysLockId);
        if (cfg) {
            GuideData::GetInstance()->setSysLockId(sysLockId);
        }
    }
    
    loadData();
}

void CcbFightRewardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFightRewardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFightRewardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

bool CcbFightRewardLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}
void CcbFightRewardLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!isExpUpStop) {
        onEndExpUp();
    }
    else if(!m_bIsShowEnd)
    {
        onFastShow();
    }
        
}
void CcbFightRewardLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 18, true);
}

// Inhert MemberVariableAssigner
bool CcbFightRewardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar_1", CCSprite*, this->m_pSpriteStar_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar_2", CCSprite*, this->m_pSpriteStar_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar_3", CCSprite*, this->m_pSpriteStar_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGetMoney", CCLabelTTF*, this->m_pLabelTTFGetMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGetExp", CCLabelTTF*, this->m_pLabelTTFGetExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteExpBar", CCSprite*, this->m_pSpriteExpBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteItemIcon", CCSprite*, this->m_pSpriteItemIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRward", CCLayer*, this->m_pLayerRward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonContinue", CCControlButton*, this->m_pControlButtonContinue);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShare", CCControlButton*, this->m_pControlButtonShare);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFStageName", CCLabelTTF*, this->m_pLabelTTFStageName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteZhuanlun", CCSprite*, this->m_pSpriteZhuanlun);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDropDes", CCLabelTTF*, this->m_pLabelTTFDropDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDropType", CCLabelTTF*, this->m_pLabelTTFDropType);
	return false;
}

bool CcbFightRewardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFightRewardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onStartExp1", CcbFightRewardLayer::onStartExp1);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onStartExp2", CcbFightRewardLayer::onStartExp2);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onStartExp3", CcbFightRewardLayer::onStartExp3);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onShowWorldLoot", CcbFightRewardLayer::onShowWorldLoot);
	return NULL;
}

SEL_MenuHandler CcbFightRewardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFightRewardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonContinue", CcbFightRewardLayer::onPressControlButtonContinue);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShare", CcbFightRewardLayer::onPressControlButtonShare);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFightRewardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}

    m_byStar = 0;
    m_wUserLv = 0;
    m_dwUserExp = 0;
    isLvUpRunning = false;
    isExpUpStop = false;
    curFrame = 0;
    perExp = 0;
    moleExp = 0;
    perMoney = 0;
    moleMoney = 0;
    m_dwCurLvExp = 0;
    m_dwGetExp = 0;
    m_dwCurGetExp = 0;
    m_dwGetCoin = 0;
    m_dwCurGetCoin = 0;
    isLvMax = 0;
    m_curItemCnt = -1;
    m_bIsShowEnd = 0;
    m_bIsFast = false;
    m_backFlag = false;
    m_dwCurLvGetExp = 0;
    
    expBarW = getWidth(m_pSpriteExpBar);
    m_pSpriteItemIcon->setVisible(false);
    m_pLabelTTFGetExp->setString("0");
    m_pLabelTTFGetMoney->setString("0");
    
    m_pControlButtonContinue->setTouchPriority(kCCMenuHandlerPriority - 20);
    m_pControlButtonShare->setTouchPriority(kCCMenuHandlerPriority - 20);
    
    m_pSpriteZhuanlun->runAction(CCRepeatForever::create(CCRotateBy::create(4.0, 360)));
    
    if (GlobalData::shared()->getShareSwitch()) {
        m_pControlButtonShare->setVisible(false);
        m_pControlButtonContinue->setPosition((m_pControlButtonShare->getPosition() + m_pControlButtonContinue->getPosition()) / 2);
    }

}

void CcbFightRewardLayer::onPressControlButtonContinue(CCObject* pSender, CCControlEvent event)
{
    if (!m_bIsFast) {
        m_bIsFast = true;
    }
    
    if (!isExpUpStop || !m_bIsShowEnd) {
        return;
    }
    if (isLvUpRunning) {
        return;
    }
    if (m_backFlag) {
        return;
    }
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));

    m_backFlag = true;
    
    uint8 fightType = FightAI::Get()->getFightType();
    uint16 lv = FightAI::Get()->getPerData().wUserLv;
    FightAI::Get()->uninit();
//    PetLoadingLayer::sharedLayer()->WaitForPacket();
    
    if (fightType == E_BATTLE_TYPE_TOWER) {
        BackCtrl::JumpToScene(kTowerMainScene);
        return;
    }
    
    if (fightType == E_BATTLE_TYPE_WRESTLE)
    {
        BackCtrl::JumpToScene(kChallengeMapScene);
        return;
    }
    
    if (fightType == E_BATTLE_TYPE_BOSS){
        CGameSession::SendWorldBossInfo();
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        return;
    }
    
    //升级后做解锁判断
    CRole* role = CGameSession::GetRole();
    if (role->GetwRoleLv() > lv) {
        uint16 sysLockId = GuideData::GetInstance()->checkSystemLock(GuideData::E_GUIDE_UNLOCK_TYPE_LV);
        SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, sysLockId);
        if (cfg) {
            GuideData::GetInstance()->setSysLockId(sysLockId);
        }
    }
    
    if (fightType == E_BATTLE_TYPE_SWEEP) {
        removeFromParent();
        CcbSystemBootInfoLayer::showSystemBootInfo(GuideData::GetInstance()->getSysLockId(), NULL);
    } else if (fightType == E_BATTLE_TYPE_ACTIVE_MAP)
    {
        BackCtrl::BacktoUpperScene();
    }
    else
    {
        BackCtrl::JumpToScene(kStageScene);
        return;
    }
    
    return;
}

void CcbFightRewardLayer::onPressControlButtonShare(CCObject* pSender, CCControlEvent event)
{
    if (!isExpUpStop || !m_bIsShowEnd) {
        return;
    }
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	// TODO:
    m_pControlButtonShare->setVisible(false);
    m_pControlButtonContinue->setVisible(false);
    CCLayer* pLayer = (CCLayer*)CCDirector::sharedDirector()->getRunningScene();//->getChildren()->objectAtIndex(0);
    
    CcbShareFrameLayer::showShare(pLayer, Str_share_text_pve_win);
    m_pControlButtonShare->setVisible(true);
    m_pControlButtonContinue->setVisible(true);
}

void CcbFightRewardLayer::loadData()
{
    STC_BATTLE_PRE_DATA preData = FightAI::Get()->getPerData();
    CCString *str = CCString::create("");
    
    bool flagNewEquip = false;
    bool flagPetEvoElem = false;
    bool flagEquipEvoElem = false;
    
    std::vector<STC_FIGHT_REWARD_ITEM> arrReward = FightAI::Get()->getPveReward();
    for (int i  = 0; i < arrReward.size(); i++) {
        STC_FIGHT_REWARD_ITEM item = arrReward[i];
        
        //金币和经验单独处理，宠物最后显示，首次通关优先显示，其他的都算是item}
        if (item.byType >= 1) {
            arrFirst.push_back(item);
            continue;
        }
        
        switch (item.dwItemId / E_UNITE_BASE_FABIO) {
            case E_UNITE_TYPE_SPECIAL:
                switch (item.dwItemId % E_UNITE_BASE_FABIO) {
                    case E_SPECIAL_ID_COIN:
                        m_dwGetCoin = item.dwCount;
                        continue;
                        break;
                    case E_SPECIAL_ID_EXP:
                        m_dwGetExp = item.dwCount;
                        continue;
                        break;
                        
                    default:
                        break;
                }
                arrItem.push_back(item);
                break;
            case E_UNITE_TYPE_PET:
                arrPet.push_back(item);
                break;
            case E_UNITE_TYPE_EQUIP:
                flagNewEquip = true;
                arrItem.push_back(item);
                break;
            case E_UNITE_TYPE_ITEM:
            {
                int head = item.dwItemId / 100000;
                if (head == 110) {
                    flagEquipEvoElem = true;
                }
                else if (head == 111 && item.dwItemId != 11100002){ //进阶印章不提示
                    flagPetEvoElem = true;
                }
                arrItem.push_back(item);
            }
                break;
            default:
                arrItem.push_back(item);
                break;
        }
    }
    arrReward.clear();
    for (int i = 0; i < arrFirst.size(); i++) {
        STC_FIGHT_REWARD_ITEM item = arrFirst[i];
        arrReward.push_back(item);
    }
    
    for (int i = 0; i < arrItem.size(); i++) {
        STC_FIGHT_REWARD_ITEM item = arrItem[i];
        arrReward.push_back(item);
    }
    
    for (int i = 0; i < arrPet.size(); i++) {
        STC_FIGHT_REWARD_ITEM item = arrPet[i];
        arrReward.push_back(item);
    }
    
    if (flagNewEquip) {
		str->initWithFormat("%s%s%s", GET_STR(Str_chinese_left), GET_STR(Str_new_equip), GET_STR(Str_chinese_right));
        m_pLabelTTFDropType->setString(str->getCString());
        m_pLabelTTFDropDes->setString(GET_STR(Str_go_wear_equip));
        m_pLabelTTFDropDes->setPositionX(getRight(m_pLabelTTFDropType) - 3);
    }
    else if (flagPetEvoElem){
        str->initWithFormat("%s%s%s", GET_STR(Str_chinese_left), GET_STR(Str_new_pet_evo_elem), GET_STR(Str_chinese_right));
        m_pLabelTTFDropType->setString(str->getCString());
        m_pLabelTTFDropDes->setString(GET_STR(Str_go_pet_evo));
        m_pLabelTTFDropDes->setPositionX(getRight(m_pLabelTTFDropType) - 3);
    }
    else if (flagEquipEvoElem){
        str->initWithFormat("%s%s%s", GET_STR(Str_chinese_left), GET_STR(Str_new_equip_evo_elem), GET_STR(Str_chinese_right));
        m_pLabelTTFDropType->setString(str->getCString());
        m_pLabelTTFDropDes->setString(GET_STR(Str_go_equip_evo));
        m_pLabelTTFDropDes->setPositionX(getRight(m_pLabelTTFDropType) - 3);
    }
    else{
        m_pLabelTTFDropDes->getParent()->setVisible(false);
    }
    
    
    //星级}
    m_byStar = FightAI::Get()->getFightStar();
    if (m_byStar < 3) {
        m_pSpriteStar_3->setVisible(false);
    }
    if (m_byStar < 2) {
        m_pSpriteStar_2->setVisible(false);
    }
    //关卡名}
    if (g_TowerDataMgr->isEnterTower())
    {
        //关卡名称}
        m_pLabelTTFStageName->setString(CCString::createWithFormat(GET_STR(Str_dijiceng), g_TowerDataMgr->GetCurBattleFloor())->getCString());
        
    }
    else if(FightAI::Get()->getFightType() == E_BATTLE_TYPE_WRESTLE)
    {
        uint16 stageId = g_ChallengeDataMgr->getCurFightStage();
        ChallengeConfig::STC_CHALLENGE_CONFIG* cfg = GET_CONFIG_STC(ChallengeConfig, stageId);
        if (cfg) {
            m_pLabelTTFStageName->setString(cfg->strName.c_str());
        }
    }
    else if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_BOSS)
    {
        m_pLabelTTFStageName->setString("世界BOSS");
    }
    else if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_ACTIVE_MAP)
    {
        StageCtrl::STC_STAGE *stc = StageCtrl::Get()->getStageByStageId(StageCtrl::Get()->getSelectStageId());
        //关卡名称}
        if (stc) {
            m_pLabelTTFStageName->setString(stc->strName.c_str());
        }
        else
        {
            m_pLabelTTFStageName->setString("");
        }
        
    }
    else
    {
        StageCtrl::STC_STAGE stc = StageCtrl::Get()->selectedStage();
        //关卡名称}
        m_pLabelTTFStageName->setString(stc.strName.c_str());
    }
    
    //等级}
    m_wUserLv = preData.wUserLv;
    str->initWithFormat("%s%d", SB_Lv, m_wUserLv);
    m_pLabelTTFLv->setString(str->getCString());
    //当前经验}
    m_dwUserExp = preData.dwCurExp;
    //升级需要经验}
    ExpConfig::STC_EXP_CONFIG *lvCfg = GET_CONFIG_STC(ExpConfig, m_wUserLv);
    if (lvCfg) {
        m_dwCurLvExp = lvCfg->dwUserExp;
        
        if (m_dwCurLvExp == 0) {
            isLvMax = true;
            m_pLabelTTFLv->setString(SB_LvMax);
        }
        else {
            m_pSpriteExpBar->setTextureRect(CCRectMake(0, 0, (float)m_dwUserExp * expBarW / m_dwCurLvExp, getHeight(m_pSpriteExpBar)));
        }
    }
    else
    {
        isLvMax = true;
        m_pLabelTTFLv->setString(SB_LvMax);
    }
    
    perExp = m_dwGetExp / 45;
    moleExp = m_dwGetExp % 45;
    
    perMoney = m_dwGetCoin / 45;
    moleMoney = m_dwGetCoin % 45;
    
    //物品}
    CCScrollView *scroll = CCScrollView::create(m_pLayerRward->getContentSize());
    scroll->setPosition(CCPointZero);
    scroll->setAnchorPoint(CCPointZero);
    scroll->setBounceable(true);
    scroll->setDirection(kCCScrollViewDirectionVertical);
    scroll->setTouchPriority(kCCMenuHandlerPriority - 21);
    
    CCScrollViewWithBar* bar = CCScrollViewWithBar::create(scroll);
    bar->setPosition(CCPointZero);
    bar->setAnchorPoint(CCPointZero);
    m_pLayerRward->addChild(bar);
    
    float h = arrReward.size() / 4 * 65;
    if (arrReward.size() % 4 > 0) {
        h += 65;
    }
    scroll->setContentSize(CCSizeMake(getWidth(scroll), h));
    scroll->setContentOffset(ccp(0, scroll->getViewSize().height - h));
    for (int i = 0; i < arrReward.size(); i++) {
        STC_FIGHT_REWARD_ITEM item = arrReward[i];
        
        CCPoint pos = ccp( 15 + (i % 4) * 65,  h - (i / 4 * 60) - 60);

        //获取item图标}
        CCSprite *img = CCSprite::create("ccbresources/12monthdate/universal/item_nothing.png");
        img->setPosition(pos);
        img->setAnchorPoint(ccp(0.5, 0.5));
        scroll->addChild(img, 3);
        m_arrItemNothing.push_back(img);
        
        CcbItemIconLayer* itemIcon = dynamic_cast<CcbItemIconLayer*>(CcbManager::sharedManager()->LoadCcbItemIconLayer(this));
        itemIcon->ignoreAnchorPointForPosition(false);
        itemIcon->loadIndexData(item.dwItemId);
        itemIcon->setAnchorPoint(ccp(0.5, 0.5));
        itemIcon->setBtnEnable(false);

        if (item.byType >= 1) {
            //加“首次通关”文字}
            CCLabelTTF *lbl = CCLabelTTF::create(GET_STR(Str_shouci_tongguan), FONT_FZCQJW, 10);
            lbl->setPosition(ccp(getWidth(itemIcon)*0.5 - 1, getHeight(itemIcon)));
            itemIcon->addChild(lbl, 10);
        }
        
        itemIcon->showCnt(item.dwCount);

        itemIcon->setPosition(pos);
        scroll->addChild(itemIcon, 2);
        itemIcon->setVisible(false);
        m_arrItem.push_back(itemIcon);
        
        CCSprite* imgLight = CCSprite::create("ccbresources/12monthdate/temp/white.png");
        imgLight->setScale(getWidth(itemIcon) / getWidth(imgLight));
        imgLight->setPosition(pos - ccp(1, 0));
        imgLight->setAnchorPoint(ccp(0.5, 0.5));
        scroll->addChild(imgLight, 4);
        imgLight->setOpacity(0);
        m_arrLight.push_back(imgLight);
    }
    bar->checkIsShow();
}

void CcbFightRewardLayer::onStartExp1(CCNode *pNode)
{
    if (m_byStar > 1) {
        return;
    }
    schedule(schedule_selector(CcbFightRewardLayer::updateForExp));
}

void CcbFightRewardLayer::onStartExp2(CCNode *pNode)
{
    if (m_byStar > 2) {
        return;
    }
    schedule(schedule_selector(CcbFightRewardLayer::updateForExp));
}

void CcbFightRewardLayer::onStartExp3(CCNode *pNode)
{
    schedule(schedule_selector(CcbFightRewardLayer::updateForExp));
}

void CcbFightRewardLayer::onShowWorldLoot(CCNode* pNode)
{
    CcbWorldLootLayer::showWorldLoot();
    CcbMJShopFindLayer::showMJShop();
}

void CcbFightRewardLayer::onEndExpUp()
{
    if (isExpUpStop || isLvMax) {
        return;
    }
    unschedule(schedule_selector(CcbFightRewardLayer::updateForExp));
    isExpUpStop = true;
    
    //升级需要经验}
    CRole *role = CGameSession::GetRole();
    m_dwUserExp = role->GetdwRoleExp();
    
    if (m_wUserLv < role->GetwRoleLv()) {
        m_wUserLv = role->GetwRoleLv();
        onLvUp();
    }
    
    ExpConfig::STC_EXP_CONFIG *lvCfg = GET_CONFIG_STC(ExpConfig, m_wUserLv);
    m_pSpriteExpBar->setTextureRect(CCRectMake(0, 0, expBarW * m_dwUserExp / lvCfg->dwUserExp, getHeight(m_pSpriteExpBar)));
    
    m_pLabelTTFGetExp->setString(CCString::createWithFormat("%d", m_dwGetExp)->getCString());
    m_pLabelTTFGetMoney->setString(CCString::createWithFormat("%d", m_dwGetCoin)->getCString());
    
    onShowItem();
}

void CcbFightRewardLayer::updateForExp(float time)
{
    if (isLvUpRunning || isExpUpStop) {
        return;
    }
    
    if (m_dwGetCoin > 0 && m_dwGetCoin > m_dwCurGetCoin) {
        m_dwCurGetCoin += perMoney;
        curFrame++;
        if (curFrame <= moleMoney) {
            m_dwCurGetCoin++;
        }
        
        if (m_dwCurGetCoin >= m_dwGetCoin) {
            m_dwCurGetCoin = m_dwGetCoin;
            curFrame = 0;
        }
        m_pLabelTTFGetMoney->setString(CCString::createWithFormat("%d", m_dwCurGetCoin)->getCString());
        return;
    }

    //先判断是否读取完全部经验}
    if (m_dwGetExp > 0 && m_dwGetExp > m_dwCurGetExp) {
        m_dwCurGetExp += perExp;
        m_dwCurLvGetExp += perExp;
        curFrame++;
        
        if (curFrame <= moleExp) {
            m_dwCurGetExp++;
            m_dwCurLvGetExp++;
        }
        
        //升级了}
        if (!isLvMax && m_dwCurLvExp < m_dwCurLvGetExp + m_dwUserExp) {
            uint32 off = m_dwCurLvExp - m_dwUserExp;
            m_dwCurGetExp -= m_dwCurLvGetExp - off;
            if (curFrame > 0) {
                curFrame--;
            }
            m_dwCurLvGetExp = 0;
            m_dwUserExp = 0;
            m_wUserLv++;
            onLvUp();
        }
        
        if (m_dwCurGetExp >= m_dwGetExp) {
            m_dwCurGetExp = m_dwGetExp;
            curFrame = 0;
            unschedule(schedule_selector(CcbFightRewardLayer::updateForExp));
            onEndExpUp();
            
            return;
        }
        m_pLabelTTFGetExp->setString(CCString::createWithFormat("%d", m_dwCurGetExp)->getCString());
        if (!isLvMax) {
            m_pSpriteExpBar->setTextureRect(CCRectMake(0, 0, expBarW * (m_dwCurLvGetExp + m_dwUserExp) / m_dwCurLvExp, getHeight(m_pSpriteExpBar)));
        }
    }
    else{
        onEndExpUp();
    }
}

void CcbFightRewardLayer::onLvUp()
{
    isLvUpRunning = true;
    
//    uint16 sysLockId = GuideData::GetInstance()->checkSystemLock(GuideData::E_GUIDE_UNLOCK_TYPE_LV);
//    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, sysLockId);
//    if (cfg) {
//        GuideData::GetInstance()->setSysLockId(sysLockId);
//    }
    
    m_pLabelTTFLv->setString(CCString::createWithFormat("%s%d", SB_Lv, m_wUserLv)->getCString());
    ExpConfig::STC_EXP_CONFIG *lvCfg = GET_CONFIG_STC(ExpConfig, m_wUserLv);
    // [2014-03-12] added by Juniechu, crash caused by lvCfg equals NULL
    if (!lvCfg || lvCfg->dwUserExp == 0) {
        isLvMax = true;
        return;
    }
    m_dwCurLvExp = lvCfg->dwUserExp;
    
    m_pSpriteExpBar->setTextureRect(CCRectMake(0, 0, m_dwUserExp*expBarW / m_dwCurLvExp, getHeight(m_pSpriteExpBar)));
    //弹出升级面板}
    CcbUserLvUpLayer* node = dynamic_cast<CcbUserLvUpLayer*>(CcbManager::sharedManager()->LoadCcbUserLvUpLayer(this));
    if (node) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        node->setPosition(ccp(winSize.width* 0.5, winSize.height * 0.5));
        node->ignoreAnchorPointForPosition(false);
        node->setDelegate(this);
        CCDirector::sharedDirector()->getRunningScene()->addChild(node, 999);
        return;
    }
    onLvUpEnd();
}

void CcbFightRewardLayer::onLvUpEnd()
{
    isLvUpRunning = false;
}

void CcbFightRewardLayer::onShowItem()
{
    int size = m_arrItemNothing.size() - 1;
    if (m_curItemCnt >= size) {
        m_bIsShowEnd = true;
        return;
    }
    m_curItemCnt++;
    CCSprite* nothing = m_arrItemNothing[m_curItemCnt];
    CCNode* item = m_arrItem[m_curItemCnt];
    CCSprite* light = m_arrLight[m_curItemCnt];
    if (!item) {
        onShowItem();
    }
    float time = 0.5;
    float time2 = 0.1;
    if (m_bIsFast) {
        time = 0.1;
        time2 = 0.0;
    }
    nothing->runAction(CCSequence::create(CCFadeOut::create(time),
                                          CCHide::create(),
                                          NULL));
    item->setVisible(true);
    light->runAction(CCSequence::create(CCFadeIn::create(time),
                                        CCHide::create(),
                                        CCDelayTime::create(time2),
                                        CCCallFunc::create(this, callfunc_selector(CcbFightRewardLayer::onShowItem)),
                                        NULL));
}

void CcbFightRewardLayer::onFastShow()
{
    if (m_bIsFast) {
        return;
    }
    m_bIsFast = true;
    if (m_curItemCnt >= m_arrItemNothing.size() - 1) {
        m_bIsShowEnd = true;
        return;
    }
    CCSprite* nothing = m_arrItemNothing[m_curItemCnt];
    CCNode* item = m_arrItem[m_curItemCnt];
    CCSprite* light = m_arrLight[m_curItemCnt];
    if (item) {
        nothing->setVisible(false);
        item->setVisible(true);
        light->setVisible(false);
        onShowItem();
    }
}

