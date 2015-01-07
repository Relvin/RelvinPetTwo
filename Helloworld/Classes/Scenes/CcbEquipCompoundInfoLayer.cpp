#include "CcbEquipCompoundInfoLayer.h"
#include "CcbItemIconLayer.h"
#include "PacketDataMgr.h"
#include "EquipDataMgr.h"
#include "UISupport.h"
#include "FlyTextLayer.h"
#include "PetLoadingLayer.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "ArmatureManager.h"
#include "ErrorMsg.h"

USING_NS_CC;
USING_NS_CC_EXT;

//符文合成消耗的数量为3，是个定值}
const char* COMPOUND_COST_RUNE_COUNT = "3";

static CcbEquipCompoundInfoLayer* s_share = NULL;

CcbEquipCompoundInfoLayer* CcbEquipCompoundInfoLayer::shareInstance()
{
    return s_share;
}

CcbEquipCompoundInfoLayer::CcbEquipCompoundInfoLayer()
: m_pLabelTTFCostName (NULL)
, m_pControlButtonCompound (NULL)
, m_pControlButtonInlay (NULL)
, m_pLabelTTFCostText (NULL)
, m_pLabelTTFCostDollor (NULL)
, m_pControlButtonChooseDollor (NULL)
, m_pSpriteCross (NULL)
, m_pLabelTTFRate (NULL)
, m_pLayerIcon_Cost (NULL)
, m_pLabelAttributes_Cost (NULL)
, m_pLabelAttributes_Number1 (NULL)
, m_pLayerIcon_Result (NULL)
, m_pLabelTTFResultName (NULL)
, m_pLabelAttributes_Result (NULL)
, m_pLabelAttributes_Number2 (NULL)
, m_pLabelTTFNeedNum (NULL)
, m_pLabelTTFOwnNum (NULL)
, m_pControlButtonClose (NULL)
, m_pLabelTTFCostTitle(NULL)
, m_pLabelTTFCostMoney(NULL)
, m_dwItemId(0)
, m_dwRate(0)
, m_bIsCostDollor(false)
{
    
}

CcbEquipCompoundInfoLayer::~CcbEquipCompoundInfoLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCostName);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCompound);
	CC_SAFE_RELEASE_NULL(m_pControlButtonInlay);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCostText);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCostDollor);
	CC_SAFE_RELEASE_NULL(m_pControlButtonChooseDollor);
	CC_SAFE_RELEASE_NULL(m_pSpriteCross);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRate);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon_Cost);
	CC_SAFE_RELEASE_NULL(m_pLabelAttributes_Cost);
	CC_SAFE_RELEASE_NULL(m_pLabelAttributes_Number1);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon_Result);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFResultName);
	CC_SAFE_RELEASE_NULL(m_pLabelAttributes_Result);
	CC_SAFE_RELEASE_NULL(m_pLabelAttributes_Number2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNeedNum);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFOwnNum);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCostTitle);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCostMoney);
    s_share = NULL;
}

bool CcbEquipCompoundInfoLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    s_share = this;
    this->setTouchEnabled(true);
	return true;
}

void CcbEquipCompoundInfoLayer::onEnter()
{
	CCLayer::onEnter();
}

void CcbEquipCompoundInfoLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipCompoundInfoLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEquipCompoundInfoLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEquipCompoundInfoLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCostName", CCLabelTTF*, this->m_pLabelTTFCostName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCompound", CCControlButton*, this->m_pControlButtonCompound);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonInlay", CCControlButton*, this->m_pControlButtonInlay);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCostText", CCLabelTTF*, this->m_pLabelTTFCostText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCostDollor", CCLabelTTF*, this->m_pLabelTTFCostDollor);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonChooseDollor", CCControlButton*, this->m_pControlButtonChooseDollor);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCross", CCSprite*, this->m_pSpriteCross);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRate", CCLabelTTF*, this->m_pLabelTTFRate);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_Cost", CcbItemIconLayer*, this->m_pLayerIcon_Cost);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelAttributes_Cost", CCLabelTTF*, this->m_pLabelAttributes_Cost);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelAttributes_Number1", CCLabelTTF*, this->m_pLabelAttributes_Number1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_Result", CcbItemIconLayer*, this->m_pLayerIcon_Result);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFResultName", CCLabelTTF*, this->m_pLabelTTFResultName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelAttributes_Result", CCLabelTTF*, this->m_pLabelAttributes_Result);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelAttributes_Number2", CCLabelTTF*, this->m_pLabelAttributes_Number2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNeedNum", CCLabelTTF*, this->m_pLabelTTFNeedNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFOwnNum", CCLabelTTF*, this->m_pLabelTTFOwnNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCostTitle", CCLabelTTF*, this->m_pLabelTTFCostTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCostMoney", CCLabelTTF*, this->m_pLabelTTFCostMoney);
	return false;
}

bool CcbEquipCompoundInfoLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    bool bRet = false;
    
    
    return bRet;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbEquipCompoundInfoLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEquipCompoundInfoLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEquipCompoundInfoLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCompound", CcbEquipCompoundInfoLayer::onPressControlButtonCompound);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonInlay", CcbEquipCompoundInfoLayer::onPressControlButtonInlay);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonChooseDollor", CcbEquipCompoundInfoLayer::onPressControlButtonChooseDollor);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbEquipCompoundInfoLayer::onPressControlButtonClose);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipCompoundInfoLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pControlButtonChooseDollor->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pControlButtonCompound->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pControlButtonInlay->setTouchPriority(kCCMenuHandlerPriority - 21);
}

void CcbEquipCompoundInfoLayer::setEquipInfoByItemIndex(uint32 dwIndex)
{
    m_dwItemId = dwIndex;
    const CRune* pRune = g_PacketDataMgr->GetRuneInfoByKeyID(m_dwItemId);
    if (!pRune || pRune->GetCnt() == 0) {
        this->removeFromParent();
        return;
    }
    
    m_pLayerIcon_Cost->loadIndexData(m_dwItemId);
    m_pLayerIcon_Cost->hideName();
    m_pLayerIcon_Cost->showCnt(g_PacketDataMgr->GetRuneCountByIndex(m_dwItemId));
    
    RuneConfig::STC_RUNE_CONFIG* pRuneConfig = GET_CONFIG_STC(RuneConfig,m_dwItemId);
    if (pRuneConfig)
    {
        uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(pRuneConfig->dwIndex);
        m_pLabelTTFCostName->setColor(g_PacketDataMgr->getQualityColor(quality));
        
        m_pLabelTTFCostTitle->setString(pRuneConfig->strName.c_str());
        m_pLabelTTFCostName->setString(pRuneConfig->strName.c_str());
        m_pLabelTTFCostDollor->setString(CCString::createWithFormat("%d",pRuneConfig->dwCostDollor)->getCString());
        m_dwRate = pRuneConfig->wCompoundRate / 100;
        m_pLabelAttributes_Cost->setString(g_PacketDataMgr->getAttrText(pRuneConfig->byEffectType1).c_str());
        m_pLabelAttributes_Number1->setString(CCString::createWithFormat("+%d",pRuneConfig->wEffectValue1)->getCString());
        m_pLabelAttributes_Number1->setPosition(ccp(getRight(m_pLabelAttributes_Cost), m_pLabelAttributes_Number2->getPositionY()));
        m_pLabelTTFNeedNum->setString(COMPOUND_COST_RUNE_COUNT);
        
        m_pLabelTTFCostMoney->setString(CCString::createWithFormat("%d",pRuneConfig->dwCostMoney)->getCString());
        
        int nCount = g_PacketDataMgr->GetRuneCountByIndex(m_dwItemId);
        m_pLabelTTFOwnNum->setString(CCString::createWithFormat("%d",nCount)->getCString());
        if (nCount < 3)
        {
            m_pLabelTTFOwnNum->setColor(ccGREEN);
        }
        else
        {
            m_pLabelTTFOwnNum->setColor(ccWHITE);
        }
    }
    
    
    pRuneConfig = GET_CONFIG_STC(RuneConfig, m_dwItemId + 1);
    if (pRuneConfig)
    {
        uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(pRuneConfig->dwIndex);
        m_pLabelTTFResultName->setColor(g_PacketDataMgr->getQualityColor(quality));
        
        m_pLabelTTFResultName->setString(pRuneConfig->strName.c_str());
        m_pLabelAttributes_Result->setString(g_PacketDataMgr->getAttrText(pRuneConfig->byEffectType1).c_str());
        m_pLabelAttributes_Number2->setString(CCString::createWithFormat("+%d",pRuneConfig->wEffectValue1)->getCString());
        m_pLabelAttributes_Number2->setPosition(ccp(getRight(m_pLabelAttributes_Result), m_pLabelAttributes_Number1->getPositionY()));
        m_pLayerIcon_Result->loadIndexData(m_dwItemId + 1);
        m_pLayerIcon_Result->hideName();
        int count = g_PacketDataMgr->GetRuneCountByIndex(m_dwItemId + 1);
        if (count != 0) {
            m_pLayerIcon_Result->showCnt(count);
        }
    }
    else{
        m_pLabelTTFResultName->getParent()->setVisible(false);
        m_pLabelTTFCostDollor->getParent()->setVisible(false);
        m_pLabelTTFNeedNum->getParent()->setVisible(false);
        m_pLayerIcon_Cost->getParent()->setPosition(ccp(m_pLayerIcon_Cost->getParent()->getParent()->getContentSize().width / 2.0, m_pLayerIcon_Cost->getParent()->getPositionY()));
        m_pControlButtonCompound->setEnabled(false);
    }
    
    this->setChooseCostState();
}

void CcbEquipCompoundInfoLayer::setChooseCostState()
{
    if (m_bIsCostDollor)
    {
        m_pSpriteCross->setVisible(true);
        m_pLabelTTFRate->setString("100%");
    }
    else
    {
        m_pSpriteCross->setVisible(false);
        char szTemp[16] = "";
        sprintf(szTemp, "%d%%", m_dwRate);
        m_pLabelTTFRate->setString(szTemp);
    }
}

#pragma mark - Button Functions -
void CcbEquipCompoundInfoLayer::onPressControlButtonCompound(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    PetLoadingLayer::sharedLayer()->WaitForPacket(false);
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_bIsCostDollor)
    {
        CGameSession::SendEquipCompound(m_dwItemId, 3, 1);
    }
    else
    {
        CGameSession::SendEquipCompound(m_dwItemId, 3, 0);
    }
}

void CcbEquipCompoundInfoLayer::onPressControlButtonInlay(CCObject* pSender, CCControlEvent event)
{
    //    GuideData::GetInstance()->addGuideofEnum(GuideData::E_SYS_GUIDE_HERO_9, NULL);
    const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(g_EquipData->GetChosenEquipKeyID());
    if (pEquip)
    {
        RuneConfig::STC_RUNE_CONFIG* pRuneConfig = GET_CONFIG_STC(RuneConfig,m_dwItemId);
        
        if (pEquip->GetRune1() != 0 && pEquip->GetRune2() != 0) {
            FlyTextLayer::showTips(GET_STR(Str_put_down_rune_first));
            return;
        }
        uint8 offSet = 0;
        if (pEquip->GetRune1()) {
            offSet = 1;
        }
        
        
        if ((pEquip->GetRune1() != 0 && pRuneConfig->byEffectType1 == GET_CONFIG_STC(RuneConfig,pEquip->GetRune1())->byEffectType1) ||
            (pEquip->GetRune2() != 0 && pRuneConfig->byEffectType1 == GET_CONFIG_STC(RuneConfig,pEquip->GetRune2())->byEffectType1))
        {
            FlyTextLayer::showTips(GET_STR(Str_the_same_rune));
            return;
        }
        PetLoadingLayer::sharedLayer()->WaitForPacket(false);
        CGameSession::SendRuneToEquip(g_EquipData->GetChosenEquipKeyID(), offSet, m_dwItemId);
        this->removeFromParent();
    }
    else
    {
        FlyTextLayer::showTips(GET_STR(Str_InlayLayer_No_Equip));
    }
}

void CcbEquipCompoundInfoLayer::onPressControlButtonChooseDollor(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    m_bIsCostDollor = !m_bIsCostDollor;
    this->setChooseCostState();
}

void CcbEquipCompoundInfoLayer::onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event)
{
    this->removeFromParent();
}

#pragma mark - Touch Functions -
bool CcbEquipCompoundInfoLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbEquipCompoundInfoLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 21, true);
}

#pragma mark - Receive Functins -
void CcbEquipCompoundInfoLayer::handlerRunesUpgradeResult(WorldPacket &packet)
{
    uint16 wError = 0;
    uint8 byResult = 0;
    packet >> wError;
    packet >> byResult;

    PetLoadingLayer::sharedLayer()->End();
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_rune_beset));
    if (wError != 0)
    {
        if (wError == ERROR_MGS_RUNES_UPGRADE_NOT_ENGOUH) {
            this->playFlashAnimation(m_pLayerIcon_Cost->getItemCntLabel());
        }
        else if (wError == ERROR_MSG_RUNES_CNT_MAX)
        {
            this->playFlashAnimation(m_pLayerIcon_Result->getItemCntLabel());
        }
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
        return;
    }

    if (byResult == 1)
    {
        PetLoadingLayer::sharedLayer()->CoverCouched();
        CCArmature* pGemCompound = ArmatureManager::sharedManager()->LoadArmature(GET_ARM_PATH(Arm_ef_GemCompoundSucc), GET_ARM_NAME(Arm_ef_GemCompoundSucc));
        pGemCompound->setPosition(getCenter(m_pLayerIcon_Cost));
        m_pLayerIcon_Cost->getParent()->addChild(pGemCompound);
        pGemCompound->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CcbEquipCompoundInfoLayer::movementEventCallback));
        pGemCompound->setScale(0.5f);
        
        FlyTextLayer::showTips(GET_STR(Str_hecheng_succ));
    }
    else if (byResult == 0)
    {
        FlyTextLayer::showTips( GET_STR(Str_hecheng_failed));
        PetLoadingLayer::sharedLayer()->CoverCouched();
        CCArmature* pGemCompound = ArmatureManager::sharedManager()->LoadArmature(GET_ARM_PATH(Arm_ef_GemCompoundFail), GET_ARM_NAME(Arm_ef_GemCompoundFail));
        pGemCompound->setPosition(getCenter(m_pLayerIcon_Cost));
        m_pLayerIcon_Cost->getParent()->addChild(pGemCompound);
        pGemCompound->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CcbEquipCompoundInfoLayer::movementEventCallback));
    }
    
    
}

void CcbEquipCompoundInfoLayer::movementEventCallback(cocos2d::extension::CCArmature *pArmature, cocos2d::extension::MovementEventType moveEventType, const char *animateName)
{
    if (moveEventType == COMPLETE) {
        PetLoadingLayer::sharedLayer()->End();
        pArmature->getAnimation()->setMovementEventCallFunc(NULL, NULL);
        this->setEquipInfoByItemIndex(m_dwItemId);
    }
}

void CcbEquipCompoundInfoLayer::playFlashAnimation(CCNode *pNode)
{
    if (!pNode || dynamic_cast<CCSprite *>(pNode) == NULL) {
        return;
    }
    CCSprite* pSprite = (CCSprite *)pNode;
    ccColor3B color = pSprite->getColor();
    CCArray *pAnimateArr = CCArray::create();
    for (int i = 0; i < 3; i++) {
        pAnimateArr->addObject(CCSpawn::create(CCScaleTo::create(0.2, 3.0f),CCTintTo::create(0.2,255,0,0),NULL));
        pAnimateArr->addObject(CCDelayTime::create(0.2f));
        pAnimateArr->addObject(CCSpawn::create(CCScaleTo::create(0.2, 1.0f),CCTintTo::create(0.2,color.r,color.g,color.b),NULL));
    }
    
    pSprite->runAction(CCSequence::create(pAnimateArr));
}


