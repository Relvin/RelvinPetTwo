#include "CcbWorldBossLayer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "GameSession.h"
#include "UISupport.h"
#include "PetCtrl.h"
#include "ResourceStringClient.h"
#include "FlyTextLayer.h"
#include "Instruments.h"
#include "BackCtrl.h"
#include "PetLoadingLayer.h"
#include "CcbShowGetLayer.h"
#include "EnumDefines.h"
#include "FightAI.h"
#include "CcbWorldBossRankLayer.h"
#include "CcbWorldBossRankRewardLayer.h"
#include "Role.h"
#include "CcbJumpTipLayer.h"
#include "ResourceStringClient.h"

WorldBossScene::WorldBossScene()
{
    
}
WorldBossScene::~WorldBossScene()
{
    
}
CCScene* WorldBossScene::scene()
{
    CCScene *scene = CCScene::create();
    
    WorldBossScene *layer = WorldBossScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool WorldBossScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbWorldBossLayer(this));
    
    return true;
}

CcbWorldBossLayer::~CcbWorldBossLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonRank);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReward);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFBossName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFBossHpCur);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFBossHpMax);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftTime);
	CC_SAFE_RELEASE_NULL(m_pSpriteBossPaint);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCostMoney);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCostDiamond);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMoneyNum);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDiamondNum);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTimes);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDamageNum);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDamagePercent);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDamageBuffPercent);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRankNum);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCD);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAutoAttack);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAtack);
	CC_SAFE_RELEASE_NULL(m_pControlButtonFuhuo);
    CC_SAFE_RELEASE_NULL(m_pSpriteHpBar);
    CC_SAFE_RELEASE_NULL(m_pLayerBoss);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBlessCDTime);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBossLV);
    
    m_curScene = NULL;

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbWorldBossLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbWorldBossLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbWorldBossLayer", CcbWorldBossLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/world_boss.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CcbWorldBossLayer* CcbWorldBossLayer::m_curScene = NULL;

bool CcbWorldBossLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_curScene = this;
	return true;
}

void CcbWorldBossLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    loadData();
}

void CcbWorldBossLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbWorldBossLayer::onExit()
{
	CCLayer::onExit();
}

void CcbWorldBossLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbWorldBossLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRank", CCControlButton*, this->m_pControlButtonRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReward", CCControlButton*, this->m_pControlButtonReward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBossName", CCLabelTTF*, this->m_pLabelTTFBossName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBossHpCur", CCLabelTTF*, this->m_pLabelTTFBossHpCur);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBossHpMax", CCLabelTTF*, this->m_pLabelTTFBossHpMax);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftTime", CCLabelTTF*, this->m_pLabelTTFLeftTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBossPaint", CCSprite*, this->m_pSpriteBossPaint);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCostMoney", CCControlButton*, this->m_pControlButtonCostMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCostDiamond", CCControlButton*, this->m_pControlButtonCostDiamond);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMoneyNum", CCLabelTTF*, this->m_pLabelTTFMoneyNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDiamondNum", CCLabelTTF*, this->m_pLabelTTFDiamondNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTimes", CCLabelTTF*, this->m_pLabelTTFTimes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDamageNum", CCLabelTTF*, this->m_pLabelTTFDamageNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDamagePercent", CCLabelTTF*, this->m_pLabelTTFDamagePercent);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDamageBuffPercent", CCLabelTTF*, this->m_pLabelTTFDamageBuffPercent);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRankNum", CCLabelTTF*, this->m_pLabelTTFRankNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCD", CCLabelTTF*, this->m_pLabelTTFCD);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAutoAttack", CCControlButton*, this->m_pControlButtonAutoAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAtack", CCControlButton*, this->m_pControlButtonAtack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFuhuo", CCControlButton*, this->m_pControlButtonFuhuo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteHpBar", CCSprite*, this->m_pSpriteHpBar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBoss", CCLayer*, this->m_pLayerBoss);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBlessCDTime", CCLabelTTF*, this->m_pLabelTTFBlessCDTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBossLV", CCLabelTTF*, this->m_pLabelTTFBossLV);

	return false;
}

bool CcbWorldBossLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbWorldBossLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbWorldBossLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbWorldBossLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRank", CcbWorldBossLayer::onPressControlButtonRank);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReward", CcbWorldBossLayer::onPressControlButtonReward);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbWorldBossLayer::onPressControlButtonBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCostMoney", CcbWorldBossLayer::onPressControlButtonCostMoney);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCostDiamond", CcbWorldBossLayer::onPressControlButtonCostDiamond);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAutoAttack", CcbWorldBossLayer::onPressControlButtonAutoAttack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAtack", CcbWorldBossLayer::onPressControlButtonAtack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFuhuo", CcbWorldBossLayer::onPressControlButtonFuhuo);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbWorldBossLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_fightType = 0;
    fHpBarWidth = getWidth(m_pSpriteHpBar);
    m_randOtherDamTime = rand() % 10 + 10;
    
    m_pSpriteBossPaint->runAction(CCRepeatForever::create(
                                                          CCSequence::create(CCScaleTo::create(1.5, 0.95),
                                                                             CCScaleTo::create(1.5, 1.0),
                                                                             NULL)));
}



void CcbWorldBossLayer::onPressControlButtonRank(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    if (!m_rankLayer) {
        m_rankLayer = CcbManager::sharedManager()->LoadCcbWorldBossRankLayer();
        this->addChild(m_rankLayer, 99);
        dynamic_cast<CcbWorldBossRankLayer*>(m_rankLayer)->loadData();
        return;
    }
    m_rankLayer->setVisible(true);
    
}

void CcbWorldBossLayer::onPressControlButtonReward(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (!m_rewardLayer) {
        m_rewardLayer = CcbManager::sharedManager()->LoadCcbWorldBossRankRewardLayer();
        this->addChild(m_rewardLayer, 99);
//        dynamic_cast<CcbWorldBossRankRewardLayer*>(m_rewardLayer)->loadData();
        return;
    }
    m_rewardLayer->setVisible(true);
}

void CcbWorldBossLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    BackCtrl::BacktoUpperScene();
}

void CcbWorldBossLayer::onPressControlButtonCostMoney(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_curBossInfo.dwBuffMoneyAddMax <= m_dwBuffAdd) {
        FlyTextLayer::showTips(CCString::createWithFormat("%s%s", GET_STR(Str_money) , GET_STR(Str_bless_full))->getCString());
        return;
    }
    
    if (CGameSession::GetRole()->GetdwCoin() < m_curBossInfo.dwCostMoney) {
        CShowJumpTip::Get()->Show(E_MONEY_NOT_ENOUGH);
        return;
    }
    
    CGameSession::SendWorldBossBless(1);
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
}

void CcbWorldBossLayer::onPressControlButtonCostDiamond(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_curBossInfo.dwBuffDollorAddMax <= m_dwBuffAdd) {
        FlyTextLayer::showTips(CCString::createWithFormat("%s%s", GET_STR(Str_dollar) , GET_STR(Str_bless_full))->getCString());
        return;
    }
    
    if (CGameSession::GetRole()->GetdwDollar() < m_curBossInfo.dwCostDollor) {
        CShowJumpTip::Get()->Show(E_DOLLAR_NOT_ENOUGH);
        return;
    }
    CGameSession::SendWorldBossBless(2);
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
}

void CcbWorldBossLayer::onPressControlButtonAutoAttack(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendWorldBossFight(1);
    m_fightType = 1;
}

void CcbWorldBossLayer::onPressControlButtonAtack(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendWorldBossFight(0);
    m_fightType = 0;
    
}

void CcbWorldBossLayer::onPressControlButtonFuhuo(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CCString*str = CCString::createWithFormat(GET_STR(Str_sure_fuhuo), m_curBossInfo.dwFuhuoCost);
    SystemMessage::showSystemMessage(1, this, str->getCString(), this, false, 1);
}

void CcbWorldBossLayer::reloadRank()
{
    if (m_rankLayer) {
        dynamic_cast<CcbWorldBossRankLayer*>(m_rankLayer)->loadData();
    }
}

void CcbWorldBossLayer::loadData()
{
    m_curBossInfo = g_WorldBossData->getBossInfo();
    //boss名
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_curBossInfo.wBossIndex);
    if (!petCfg) {
        m_pLayerBoss->setVisible(false);
        return;
    }
    
    schedule(schedule_selector(CcbWorldBossLayer::updateForGetOtherDam), 1.0);
    CCString* str = CCString::create("");
    m_pLayerBoss->setVisible(true);
    m_pLabelTTFBossName->setString(petCfg->strName.c_str());
    //原画
    CCPoint anP = m_pSpriteBossPaint->getAnchorPoint();
    m_pSpriteBossPaint->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(petCfg->wIndex));
    m_pSpriteBossPaint->setAnchorPoint(anP);
    //等级
    str->initWithFormat("%s%d", SB_Lv, m_curBossInfo.wBossLv);
    m_pLabelTTFBossLV->setString(str->getCString());
    //血量
    m_dwBossCurHp = m_curBossInfo.dwBossCurHp;
    //当前
    str->initWithFormat("%d", m_dwBossCurHp);
    m_pLabelTTFBossHpCur->setString(str->getCString());
    //最大
    str->initWithFormat("%d", m_curBossInfo.dwBossMaxHp);
    m_pLabelTTFBossHpMax->setString(str->getCString());
    //血条
    m_pSpriteHpBar->setTextureRect(CCRectMake(0, 0, m_dwBossCurHp * fHpBarWidth / m_curBossInfo.dwBossMaxHp, getHeight(m_pSpriteHpBar)));
    
    //bossCD
    m_dwLeftTime = m_curBossInfo.dwLeftTime;
    if (m_dwLeftTime > 0) {
        m_pLabelTTFLeftTime->setVisible(true);
        m_pLabelTTFLeftTime->setString(getLeftTimeFromInt(m_dwLeftTime)->getCString());
        schedule(schedule_selector(CcbWorldBossLayer::updateForBossLeftTime), 1.0);
    }
    
    //祝福相关
    //金币祝福CD
    m_dwBlessCDTime = m_curBossInfo.dwBlessCDTime;
    if (m_dwBlessCDTime > 0) {
        showBlessCD();
    }
    else{
        hideBlessCD();
    }
    
    //祝福金币
    str->initWithFormat("%d", m_curBossInfo.dwCostMoney);
    m_pLabelTTFMoneyNum->setString(str->getCString());
    
    //祝福钻石
    str->initWithFormat("%d", m_curBossInfo.dwCostDollor);
    m_pLabelTTFDiamondNum->setString(str->getCString());
    //攻击相关
    //攻击次数
    str->initWithFormat("%d", m_curBossInfo.dwBattleCnt);
    m_pLabelTTFTimes->setString(str->getCString());
    //总伤害
    m_dwAllDamage = m_curBossInfo.dwAllDamage;
    str->initWithFormat("%d", m_dwAllDamage);
    m_pLabelTTFDamageNum->setString(str->getCString());
    str->initWithFormat("(%.2f%%)", (float)m_dwAllDamage*100 / m_curBossInfo.dwBossMaxHp);
    m_pLabelTTFDamagePercent->setString(str->getCString());
    m_pLabelTTFDamagePercent->setPositionX(getRight(m_pLabelTTFDamageNum) + 2);
    
    //buff加成
    m_dwBuffAdd = m_curBossInfo.dwBuffAdd;
    str->initWithFormat("%d%%", m_dwBuffAdd / 100);
    m_pLabelTTFDamageBuffPercent->setString(str->getCString());
    //当前排名
    m_dwCurRank = m_curBossInfo.dwCurRank;
    str->initWithFormat("%d%s", m_dwCurRank, "名");
    m_pLabelTTFRankNum->setString(str->getCString());
    
    //攻击CD
    m_dwCdTime = m_curBossInfo.dwCdTime;
    if (m_dwCdTime > 0) {
        showAttCD();
    }
    else{
        hideAttCD();
    }
    
}

/**  世界BOSS 鼓舞结果
 *		[uint16]  wError
 *		[uint8 ]  byType
 *		[uint32]  dwBlessEffect		鼓励效果
 *		[uint32]  dwBlessCDTime		金币CD时间
 */
void CcbWorldBossLayer::handlerBlessResult(WorldPacket& packet)
{
    PetLoadingLayer::sharedLayer()->End();
    uint16  wError;
    packet >> wError;
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
        return;
    }
    
    uint8   byType;
    uint32  dwBlessEffect;//		鼓励效果
    uint32  dwBlessCDTime;//		金币CD时间
    packet >> byType;
    packet >> dwBlessEffect;
    packet >> dwBlessCDTime;
    
    CCString* str = CCString::createWithFormat("%s+%d%%", GET_STR(Str_atk), (dwBlessEffect - m_dwBuffAdd) / 100);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    FlyTextLayer::showBuffText(str->getCString(), true, winSize*0.5);
    
    str->initWithFormat("%d%%", dwBlessEffect / 100);
    m_pLabelTTFDamageBuffPercent->setString(str->getCString());
    
    m_dwBuffAdd = dwBlessEffect;
    
    m_dwBlessCDTime = dwBlessCDTime;
    
    if (m_dwBlessCDTime > 0) {
        showBlessCD();
    }
    else{
        hideBlessCD();
    }
}

/**  世界BOSS 清CD 结果
 *		[uint16]  wError
 *		[uint32]  dwCDTime			CD时间
 */
void CcbWorldBossLayer::handlerFuhuoResult(WorldPacket& packet)
{
    uint16  wError;
    packet >> wError;
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
        return;
    }
    
    uint32 dwCDTime;
    packet >> dwCDTime;
    m_dwCdTime = dwCDTime;
    if (dwCDTime > 0) {
        showAttCD();
    }
    else{
        hideAttCD();
    }
}


/**  世界BOSS 战斗 战报
 *		[uint16]  wError
 *		[uint32]  dwCurHP
 *		[uint32]  dwCurRank
 *		[uint32]  dwSize
 *			[int]	nKillValue
 */
void CcbWorldBossLayer::handlerOtherUserDam(WorldPacket& packet)
{
    uint16  wError;
    packet >> wError;
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
        return;
    }
    
    uint32  dwCurBossHp;
    uint32  dwRank;
    
    packet >> dwCurBossHp;
    packet >> dwRank;
    
    //boss血量
    m_dwBossCurHp = dwCurBossHp;
    CCString* str = CCString::createWithFormat("%d", m_dwBossCurHp);
    m_pLabelTTFBossHpCur->setString(str->getCString());
    //血条
    m_pSpriteHpBar->setTextureRect(CCRectMake(0, 0, m_dwBossCurHp * fHpBarWidth / m_curBossInfo.dwBossMaxHp, getHeight(m_pSpriteHpBar)));

    //当前排名
    m_dwCurRank = dwRank;
    str->initWithFormat("%d", m_dwCurRank);
    m_pLabelTTFRankNum->setString(str->getCString());
    
    uint32  dwSize;
    packet >> dwSize;
    for (int i = 0; i < dwSize; i++) {
        int	nKillValue;
        packet >> nKillValue;
        
        str->initWithFormat("-%d", nKillValue);
        FlyTextLayer::showBuffText(str->getCString(), false, CCDirector::sharedDirector()->getWinSize()*0.5, 0.2 * i);
    }
    
}

/**  世界BOSS 战斗 结果及结算
 *		[uint16]  wError
 *		[uint32]  dwKillHp
 *		[uint32]  dwCoin
 *		[uint32]  dwReputation
 *		[uint32]  dwRank
 *		[uint32]  dwTotalKillNum
 *		[uint32]  dwCDTime
 *      [uint32]  dwAtkCnt
 */
void CcbWorldBossLayer::handlerAutoAttReward(WorldPacket& packet)
{
    uint16  wError;
    packet >> wError;
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
        return;
    }
    uint32  dwCurBossHp;
    uint32  dwKillHp;
    uint32  dwCoin;
    uint32  dwReputation;
    uint32  dwRank;
    uint32  dwTotalKillNum;
    uint32  dwCDTime;
    uint32  dwAtkCnt;
    
    packet >> dwCurBossHp;
    packet >> dwKillHp;
    packet >> dwCoin;
    packet >> dwReputation;
    packet >> dwRank;
    packet >> dwTotalKillNum;
    packet >> dwCDTime;
    packet >> dwAtkCnt;
    
    //伤害
    CCString* str = CCString::createWithFormat("%d", dwTotalKillNum);
    m_dwAllDamage = dwTotalKillNum;
    m_pLabelTTFDamageNum->setString(str->getCString());
    str->initWithFormat("(%.2f%%)", (float)m_dwAllDamage*100 / m_curBossInfo.dwBossMaxHp);
    m_pLabelTTFDamagePercent->setString(str->getCString());
    m_pLabelTTFDamagePercent->setPositionX(getRight(m_pLabelTTFDamageNum) + 2);
    
    m_dwCdTime = dwCDTime;
    showAttCD();
    
    //boss血量
    m_dwBossCurHp = dwCurBossHp;
    str->initWithFormat("%d", m_dwBossCurHp);
    m_pLabelTTFBossHpCur->setString(str->getCString());
    //血条
    m_pSpriteHpBar->setTextureRect(CCRectMake(0, 0, m_dwBossCurHp * fHpBarWidth / m_curBossInfo.dwBossMaxHp, getHeight(m_pSpriteHpBar)));
    
    //当前排名
    m_dwCurRank = dwRank;
    str->initWithFormat("%d", m_dwCurRank);
    m_pLabelTTFRankNum->setString(str->getCString());
    
    //攻击次数
    str->initWithFormat("%d", dwAtkCnt);
    m_pLabelTTFTimes->setString(str->getCString());
    
    std::vector<STC_FIGHT_REWARD_ITEM> arrItem;
    FightAI::Get()->setPveReward(arrItem);//先清空FightAi中的结算物品
    //获取的物品
    if (dwCoin == 0 && dwReputation == 0) {
        return;
    }
    
    CcbShowGetLayer* pGetLayer = dynamic_cast<CcbShowGetLayer*>(CcbManager::sharedManager()->LoadCcbShowGetLayer());
    pGetLayer->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*0.5));
    
    if (dwCoin > 0) {
        STC_FIGHT_REWARD_ITEM itemCoin;
        itemCoin.dwItemId = E_UNITE_TYPE_SPECIAL*E_UNITE_BASE_FABIO + E_SPECIAL_ID_COIN;
        itemCoin.dwCount = dwCoin;
        arrItem.push_back(itemCoin);
        pGetLayer->addGetItem(E_UNITE_TYPE_SPECIAL*E_UNITE_BASE_FABIO + E_SPECIAL_ID_COIN, dwCoin);
    }
    
    if (dwReputation > 0) {
        
        STC_FIGHT_REWARD_ITEM itemRep;
        itemRep.dwItemId = E_UNITE_TYPE_SPECIAL*E_UNITE_BASE_FABIO + E_SPECIAL_ID_REPUTATION;
        itemRep.dwCount = dwReputation;
        arrItem.push_back(itemRep);
        
        pGetLayer->addGetItem(E_UNITE_TYPE_SPECIAL*E_UNITE_BASE_FABIO + E_SPECIAL_ID_REPUTATION, dwReputation);
    }
    
    FightAI::Get()->setPveReward(arrItem);
    
    if (m_fightType == 0) {
        return;
    }
    
    str->initWithFormat("-%d", dwKillHp);
    FlyTextLayer::showBuffText(str->getCString(), false, CCDirector::sharedDirector()->getWinSize()*0.5, 0.3);
    
    pGetLayer->reloadItems();
    CGameSession::NotifyRefeashLayer();
    PetLoadingLayer::sharedLayer()->End();
    CCDirector::sharedDirector()->getRunningScene()->addChild(pGetLayer, 998, 637);
    
}


/**  世界BOSS 结算 回包
 *		[uint16]  wError
 *		[uint32]  dwKillHpTotal
 *		[uint32]  dwCoinNumTotal
 *		[uint32]  dwReputationTotal
 */
void CcbWorldBossLayer::handlerBossDead(WorldPacket& packet)
{
    uint16  wError;
    packet >> wError;
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
        return;
    }
    
    m_pLayerBoss->setVisible(false);
}

void CcbWorldBossLayer::updateForAttCd(float time)
{
    if (m_dwCdTime > 0) {
        m_dwCdTime--;
    }
    CCString* str = getLeftTimeFromInt(m_dwCdTime);
    m_pLabelTTFCD->setString(str->getCString());
    if (m_dwCdTime == 0) {
        hideAttCD();
    }
}

void CcbWorldBossLayer::updateForBossLeftTime(float time)
{
    if (m_dwLeftTime > 0) {
        m_dwLeftTime--;
    }
    CCString* str = getLeftTimeFromInt(m_dwLeftTime);
    m_pLabelTTFLeftTime->setString(str->getCString());
    if (m_dwLeftTime == 0) {
//        m_pLabelTTFLeftTime->setVisible(false);
        CGameSession::SendWorldBossEndReward();
        unschedule(schedule_selector(CcbWorldBossLayer::updateForBossLeftTime));
    }
}

void CcbWorldBossLayer::updateForBlessCd(float time)
{
    if (m_dwBlessCDTime > 0) {
        m_dwBlessCDTime--;
    }
    m_pLabelTTFBlessCDTime->setString(getLeftTimeFromInt(m_dwBlessCDTime)->getCString());
    if (m_dwBlessCDTime == 0) {
        hideBlessCD();
    }
}

void CcbWorldBossLayer::updateForGetOtherDam(float time)
{
    if (m_randOtherDamTime > 0) {
        m_randOtherDamTime--;
    }
    
    if (m_randOtherDamTime == 0) {
        CGameSession::SendWorldBossUpdateInfo();
        m_randOtherDamTime = rand() % 10 + 10;
    }
}

void CcbWorldBossLayer::showBlessCD()
{
    m_pLabelTTFBlessCDTime->setString(getLeftTimeFromInt(m_dwBlessCDTime)->getCString());
    schedule(schedule_selector(CcbWorldBossLayer::updateForBlessCd), 1.0);
    m_pLabelTTFBlessCDTime->setVisible(true);
    m_pLabelTTFMoneyNum->getParent()->setVisible(false);
    m_pControlButtonCostMoney->setEnabled(false);
}

void CcbWorldBossLayer::hideBlessCD()
{
    unschedule(schedule_selector(CcbWorldBossLayer::updateForBlessCd));
    m_pLabelTTFBlessCDTime->setVisible(false);
    m_pControlButtonCostMoney->setEnabled(true);
    m_pLabelTTFMoneyNum->getParent()->setVisible(true);
}


void CcbWorldBossLayer::showAttCD()
{
    m_pLabelTTFCD->setVisible(true);
    m_pLabelTTFCD->setString(getLeftTimeFromInt(m_dwCdTime)->getCString());
    schedule(schedule_selector(CcbWorldBossLayer::updateForAttCd), 1.0);
    m_pControlButtonFuhuo->setEnabled(true);
    m_pControlButtonAtack->setEnabled(false);
    m_pControlButtonAutoAttack->setEnabled(false);
}

void CcbWorldBossLayer::hideAttCD()
{
    unschedule(schedule_selector(CcbWorldBossLayer::updateForAttCd));
    
    m_pLabelTTFCD->setVisible(false);
    m_pControlButtonFuhuo->setEnabled(false);
    m_pControlButtonAtack->setEnabled(true);
    m_pControlButtonAutoAttack->setEnabled(true);
}

void CcbWorldBossLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    if (systemMessage->getParam() == 1) {
        if (CGameSession::GetRole()->GetdwDollar() < m_curBossInfo.dwFuhuoCost) {
            CShowJumpTip::Get()->Show(E_DOLLAR_NOT_ENOUGH);
            return;
        }
        
        CGameSession::SendWorldBossClearCD();
        PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    }
}