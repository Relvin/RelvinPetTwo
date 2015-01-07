#include "CcbEquipInlayLayer.h"
#include "MusicCtrl.h"
#include "Defines.h"
#include "ConfigData.h"
#include "StageScene.h"
#include "ConfigGet.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "EquipDataMgr.h"
#include "UISupport.h"
#include "Rune.h"
#include "PacketDataMgr.h"
#include "CcbManager.h"
#include "PetLoadingLayer.h"
#include "BackCtrl.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "CcbEquipCompoundInfoLayer.h"
#include "ErrorMsg.h"
#include "EnumDefines.h"
#include "ChallengeCtrl.h"
#include "CcbJumpTipLayer.h"
#include <algorithm>

USING_NS_CC;
USING_NS_CC_EXT;

#define clmCnt 5

using namespace std;

CcbEquipInlayLayer::CcbEquipInlayLayer()
: m_pLabelTTFEquipName (NULL)
, m_pSpriteEquipIcon (NULL)
, m_pLabelTTFProText_2 (NULL)
, m_pLabelTTFPro_2 (NULL)
, m_pLabelTTFProText_1 (NULL)
, m_pLabelTTFPro_1 (NULL)
, m_pLabelTTFRuneName2 (NULL)
, m_pLabelTTFRuneAttr2 (NULL)
, m_pSpriteRuneIcon2 (NULL)
, m_pSpriteLock (NULL)
, m_pControlButtonRuneIcon2 (NULL)
, m_pLabelTTFRuneAttr1 (NULL)
, m_pLabelTTFRuneName1 (NULL)
, m_pSpriteRuneIcon1 (NULL)
, m_pControlButtonRuneIcon1 (NULL)
, m_pSpriteStarlv (NULL)
, m_pLayerEquipBg (NULL)
, m_pSpriteShowNothing (NULL)
, m_pLabelTTFNeedNum (NULL)
, m_pControlButtonYiji (NULL)
, m_pControlButtonShop (NULL)
, m_pLayerRuneListParent (NULL)
, m_pControlButtonEquip (NULL)
, m_pNodeEquip(NULL)
, m_pNodeNothingtips(NULL)
, m_pTableView(NULL)
, m_clipRect(0,0,0,0)
, m_dwRuneID1(0)
, m_dwRuneID2(0)
, m_pLabelRuneName1(NULL)
, m_pLabelRuneName2(NULL)
{
    
}

CcbEquipInlayLayer::~CcbEquipInlayLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEquipName);
	CC_SAFE_RELEASE_NULL(m_pSpriteEquipIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFProText_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPro_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFProText_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPro_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRuneName2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRuneAttr2);
	CC_SAFE_RELEASE_NULL(m_pSpriteRuneIcon2);
	CC_SAFE_RELEASE_NULL(m_pSpriteLock);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRuneIcon2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRuneAttr1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRuneName1);
	CC_SAFE_RELEASE_NULL(m_pSpriteRuneIcon1);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRuneIcon1);
	CC_SAFE_RELEASE_NULL(m_pSpriteStarlv);
	CC_SAFE_RELEASE_NULL(m_pLayerEquipBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteShowNothing);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNeedNum);
	CC_SAFE_RELEASE_NULL(m_pControlButtonYiji);
	CC_SAFE_RELEASE_NULL(m_pControlButtonShop);
	CC_SAFE_RELEASE_NULL(m_pLayerRuneListParent);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEquip);
    CC_SAFE_RELEASE_NULL(m_pNodeEquip);
    CC_SAFE_RELEASE_NULL(m_pNodeNothingtips);
    CC_SAFE_RELEASE_NULL(m_pLabelRuneName1);
    CC_SAFE_RELEASE_NULL(m_pLabelRuneName2);

}

bool CcbEquipInlayLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEquipInlayLayer::onEnter()
{
	CCLayer::onEnter();
    CGameSession::Attach(this);
}

void CcbEquipInlayLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->loadLayerDataInfo();
}

void CcbEquipInlayLayer::onExit()
{
    CGameSession::Detach(this);
	CCLayer::onExit();
}

void CcbEquipInlayLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEquipInlayLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEquipName", CCLabelTTF*, this->m_pLabelTTFEquipName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEquipIcon", CCSprite*, this->m_pSpriteEquipIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFProText_2", CCLabelTTF*, this->m_pLabelTTFProText_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPro_2", CCLabelTTF*, this->m_pLabelTTFPro_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFProText_1", CCLabelTTF*, this->m_pLabelTTFProText_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPro_1", CCLabelTTF*, this->m_pLabelTTFPro_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRuneName2", CCLabelTTF*, this->m_pLabelTTFRuneName2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRuneAttr2", CCLabelTTF*, this->m_pLabelTTFRuneAttr2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRuneIcon2", CCSprite*, this->m_pSpriteRuneIcon2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLock", CCSprite*, this->m_pSpriteLock);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRuneIcon2", CCControlButton*, this->m_pControlButtonRuneIcon2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRuneAttr1", CCLabelTTF*, this->m_pLabelTTFRuneAttr1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRuneName1", CCLabelTTF*, this->m_pLabelTTFRuneName1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRuneIcon1", CCSprite*, this->m_pSpriteRuneIcon1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRuneIcon1", CCControlButton*, this->m_pControlButtonRuneIcon1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStarlv", CCSprite*, this->m_pSpriteStarlv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquipBg", CCLayer*, this->m_pLayerEquipBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteShowNothing", CCSprite*, this->m_pSpriteShowNothing);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNeedNum", CCLabelTTF*, this->m_pLabelTTFNeedNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonYiji", CCControlButton*, this->m_pControlButtonYiji);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShop", CCControlButton*, this->m_pControlButtonShop);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRuneListParent", CCLayer*, this->m_pLayerRuneListParent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquip", CCControlButton*, this->m_pControlButtonEquip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquip", CCNode*, this->m_pNodeEquip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pNodeNothingtips", CCNode*, this->m_pNodeNothingtips);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelRuneName1", CCLabelTTF*, this->m_pLabelRuneName1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelRuneName2", CCLabelTTF*, this->m_pLabelRuneName2);
	return false;
}

bool CcbEquipInlayLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbEquipInlayLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEquipInlayLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEquipInlayLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRuneIcon2", CcbEquipInlayLayer::onPressControlButtonRuneIcon2);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRuneIcon1", CcbEquipInlayLayer::onPressControlButtonRuneIcon1);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonYiji", CcbEquipInlayLayer::onPressControlButtonYiji);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShop", CcbEquipInlayLayer::onPressControlButtonShop);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEquip", CcbEquipInlayLayer::onPressControlButtonEquip);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipInlayLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pTableView = CCTableView::create(this, m_pLayerEquipBg->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setPosition(CCPointZero);
    m_pTableView->setAnchorPoint(CCPointZero);
    m_pLayerEquipBg->addChild(m_pTableView);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    
    m_pSpriteLock->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.5),
                                                                        CCFadeIn::create(1.5),
                                                                        NULL)));
    m_clipRect.origin = getWorldPos(m_pLayerEquipBg);
    m_clipRect.size = m_pLayerEquipBg->getContentSize();
    
    m_pControlButtonYiji->getParent()->setVisible(false);
    m_pSpriteRuneIcon1->getParent()->setVisible(false);
    m_pSpriteRuneIcon2->getParent()->setVisible(false);
    m_pControlButtonRuneIcon1->setEnabled(false);
    m_pControlButtonRuneIcon2->setEnabled(false);
    m_pNodeEquip->setVisible(false);
    m_pSpriteLock->setVisible(false);
}

#pragma mark - Self Functions -
void CcbEquipInlayLayer::loadLayerDataInfo()
{
    this->createShowList();
    this->createLayerData();
}

void CcbEquipInlayLayer::createShowList()
{
    m_vecRuneList.clear();
    vector<uint32> arrId = g_EquipData->GetVecShowRuneKeyID();
    for (int i = 0; i < arrId.size(); i++)
    {
        const CRune* pRune = g_PacketDataMgr->GetRuneInfoByKeyID(arrId[i]);
        if (pRune && pRune->GetCnt() != 0)
        {
            SHOW_RUNE_INFO tempInfo;
            tempInfo.dwKeyID = arrId[i];
            tempInfo.sort = pRune->GetIndex();
            m_vecRuneList.push_back(tempInfo);
        }
    }
    sort(m_vecRuneList.begin(), m_vecRuneList.end(), less<SHOW_RUNE_INFO>());
    if (m_vecRuneList.size() == 0)
    {
        m_pControlButtonYiji->getParent()->setVisible(true);
    }
    else
    {
        m_pControlButtonYiji->getParent()->setVisible(false);
    }
    m_pTableView->reloadData();
}

void CcbEquipInlayLayer::createLayerData()
{
    
    const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(g_EquipData->GetChosenEquipKeyID());
    if (pEquip)
    {
        m_pNodeNothingtips->setVisible(false);
        m_pNodeEquip->setVisible(true);
        m_pLabelTTFEquipName->setString(pEquip->GetConfigData().strName.c_str());
        
        uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(pEquip->GetIndex());
        m_pLabelTTFEquipName->setColor(g_PacketDataMgr->getQualityColor(quality));
        
        CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(GET_EQUIP_ICON(pEquip->GetConfigData().dwIcon));
        m_pSpriteEquipIcon->setTexture(pTexture);
        
        //是否解锁了第二个符文镶嵌位}
        if (pEquip->GetRunesCnt() == 2)
        {
            m_pSpriteLock->setVisible(false);
        }
        else
        {
            m_pSpriteLock->setVisible(true);
            m_pControlButtonRuneIcon2->setEnabled(true);
        }
        
        //符文1}
        m_dwRuneID1 = pEquip->GetRune1();
        if (pEquip->GetRune1() > 0)
        {
            LP_RUNE_CONFIG pConfig = GET_CONFIG_STC(RuneConfig, pEquip->GetRune1());
            if (pConfig)
            {
                m_pSpriteRuneIcon1->getParent()->setVisible(true);
                m_pControlButtonRuneIcon1->setEnabled(true);
                
                m_pSpriteRuneIcon1->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetRuneIconByIndex(pEquip->GetRune1()).c_str()));
                m_pLabelTTFRuneName1->setString(pConfig->strName.c_str());
                m_pLabelTTFRuneAttr1->setString(CCString::createWithFormat("+%d", pConfig->wEffectValue1)->getCString());
                m_pLabelRuneName1->setString(g_PacketDataMgr->getAttrText(pConfig->byEffectType1).c_str());
//                m_pSpriteRuneAttr1->setDisplayFrame(g_PacketDataMgr->getAttrTexture(pConfig->byEffectType1));
            }
        }
        else
        {
            m_pSpriteRuneIcon1->getParent()->setVisible(false);
            m_pControlButtonRuneIcon1->setEnabled(false);
        }
        //符文2}
        m_dwRuneID2 = pEquip->GetRune2();
        if (m_dwRuneID2 > 0)
        {
            LP_RUNE_CONFIG pConfig = GET_CONFIG_STC(RuneConfig, m_dwRuneID2);
            if (pConfig)
            {
                m_pSpriteRuneIcon2->getParent()->setVisible(true);
                m_pControlButtonRuneIcon2->setEnabled(true);
                
                m_pSpriteRuneIcon2->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetRuneIconByIndex(m_dwRuneID2).c_str()));
                m_pLabelTTFRuneName2->setString(pConfig->strName.c_str());
                m_pLabelTTFRuneAttr2->setString(CCString::createWithFormat("+%d", pConfig->wEffectValue1)->getCString());
                m_pLabelRuneName2->setString(g_PacketDataMgr->getAttrText(pConfig->byEffectType1).c_str());
//                m_pSpriteRuneAttr2->setDisplayFrame(g_PacketDataMgr->getAttrTexture(pConfig->byEffectType1));
            }
        }
        else
        {
            m_pSpriteRuneIcon2->getParent()->setVisible(false);
        }
        
        //add by Relvin need modify
        float evoAdd = 1;//1 + (float)pEquip->GetConfigData().wEvoCoef / 10000;
        //属性类型}
        uint8 byProType[2];
        byProType[0] = pEquip->GetConfigData().byEffectType1;
        byProType[1] = pEquip->GetConfigData().byEffectType2;
        //当前属性值}
        uint32 dwProCurValue[2];
        dwProCurValue[0] = (pEquip->GetConfigData().wEffectValue1 + (pEquip->GetLevel() - 1) * pEquip->GetConfigData().wGrowthRate1) * evoAdd;
        dwProCurValue[1] = (pEquip->GetConfigData().wEffectValue2 + (pEquip->GetLevel() - 1) * pEquip->GetConfigData().wGrowthRate2) * evoAdd;
        CCLabelTTF* arrProName[2];
        CCLabelTTF* arrProLblCur[2];
        arrProName[0] = m_pLabelTTFProText_1;
        arrProName[1] = m_pLabelTTFProText_2;
        arrProLblCur[0] = m_pLabelTTFPro_1;
        arrProLblCur[1] = m_pLabelTTFPro_2;
        int cnt = 0;
        CCString* str = CCString::create("");
        for (int i = 0; i < 2; i++) {
            if (byProType[i] == 0) {
                continue;
            }
            arrProName[cnt]->setVisible(true);
            arrProLblCur[cnt]->setVisible(true);
            arrProName[cnt]->setString(g_PacketDataMgr->getAttrText(byProType[i]).c_str());
            str->initWithFormat("+%d", dwProCurValue[i]);
            arrProLblCur[cnt]->setString(str->getCString());
            
            cnt++;
        }
        for (; cnt < 2; cnt++) {
            arrProLblCur[cnt]->setVisible(false);
            arrProName[cnt]->setVisible(false);
        }
        
        //星级}
        m_pSpriteStarlv->removeAllChildren();
        CCTexture2D *td = m_pSpriteStarlv->getTexture();
        uint8 starLv = pEquip->GetConfigData().byStar;
        for (int s = 1; s < starLv; s++) {
            CCSprite *st = CCSprite::createWithTexture(td);
            st->setAnchorPoint(ccp(0, 0));
            st->setPosition(ccp(s*getWidth(st), 0));
            m_pSpriteStarlv->addChild(st);
        }
        m_pSpriteStarlv->setContentSize(CCSizeMake(starLv*td->getContentSize().width, getHeight(m_pSpriteStarlv)));
    }
    else
    {
        m_pNodeEquip->setVisible(false);
        m_pNodeNothingtips->setVisible(true);
    }
}

#pragma mark - Button Functions -
void CcbEquipInlayLayer::onPressControlButtonRuneIcon2(CCObject* pSender, CCControlEvent event)
{
    if (m_dwRuneID2 > 0)
    {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_rune_put_down));
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        CGameSession::SendRuneUnload(g_EquipData->GetChosenEquipKeyID(), 1, m_dwRuneID2);
    }
    else
    {
        const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(g_EquipData->GetChosenEquipKeyID());
        if (pEquip && pEquip->GetRunesCnt() == 1)
        {
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_rune_open));
            
            int cnt = g_PacketDataMgr->GetItemCountByIndex(E_RUNES_CNT_OPEN_ITEM);
            if (cnt == 0) {
                CShowJumpTip::Get()->Show(E_ITEM_NOT_ENOUGH, E_RUNES_CNT_OPEN_ITEM);
                return;
            }
            
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendEquipEnlageRune(pEquip->GetKeyID());
        }
    }
}

void CcbEquipInlayLayer::onPressControlButtonRuneIcon1(CCObject* pSender, CCControlEvent event)
{
    if (m_dwRuneID1 > 0)
    {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_rune_put_down));
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        CGameSession::SendRuneUnload(g_EquipData->GetChosenEquipKeyID(), 0, m_dwRuneID1);
    }
}

void CcbEquipInlayLayer::onPressControlButtonYiji(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));

    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ACTIVITY);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    StageCtrl::Get()->setFromJump(false);
    ChallengeCtrl::Get()->setChallengeStage(ChallengeCtrl::E_CHALLENGE_NONE);
    CGameSession::SendSpecialMapList();
}

void CcbEquipInlayLayer::onPressControlButtonShop(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CGameSession::SendReqShopCnt();
}

void CcbEquipInlayLayer::onPressControlButtonEquip(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::InsertNextScene(kEquipListScene);
}

#pragma mark - TableView Functions -
void CcbEquipInlayLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    
}

CCTableViewCell* CcbEquipInlayLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    int cnt = m_vecRuneList.size() - idx * clmCnt;
    if (cnt > clmCnt) {
        cnt  = clmCnt;
    }
    
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCNode *node = CCNode::create();
        node->setContentSize(CCSizeMake(table->getContentSize().width, 64));
        node->setTag(1);
        cell->addChild(node);
    }
    CCNode *node = dynamic_cast<CCNode*>(cell->getChildByTag(1));
    
    for (int i = 0; i < cnt; i++)
    {
        CcbItemIconLayer *icon = dynamic_cast<CcbItemIconLayer*>(node->getChildByTag(i+1));
        if (!icon) {
            icon =  dynamic_cast<CcbItemIconLayer*>(CcbManager::sharedManager()->LoadCcbItemIconLayer(this));
            icon->setTag(i+1);
            node->addChild(icon);
        }
        
        const CRune *rune = g_PacketDataMgr->GetRuneInfoByKeyID(m_vecRuneList[idx * clmCnt + i].dwKeyID);
        if (!rune)
        {
            icon->removeFromParent();
            
            continue;
        }
        icon->setVisible(true);
        icon->loadObjData(rune->GetIndex(), E_UNITE_TYPE_RUNES);
        icon->setDelegate(this);
        
        icon->setPosition(ccp(18 + i*(getWidth(icon)+8), 10));
        icon->setAnchorPoint(ccp(0, 0));
        icon->setClipRect(m_clipRect);
        icon->setTag(i+1);
    }
    for (int i = cnt; i < clmCnt; i++) {
        CcbItemIconLayer *icon = dynamic_cast<CcbItemIconLayer*>(node->getChildByTag(i+1));
        if (icon) {
            icon->setVisible(false);
        }
    }
    
    return cell;
}

unsigned int CcbEquipInlayLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return ceil(m_vecRuneList.size() / 5.0f);
}

CCSize CcbEquipInlayLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerEquipBg), 64);
}

#pragma mark - ItemTouch Function -
void CcbEquipInlayLayer::itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId)
{
   CcbEquipCompoundInfoLayer* pEquipCompoundLayer = (CcbEquipCompoundInfoLayer *)CcbManager::sharedManager()->LoadCcbEquipCompoundInfoLayer(this);
    this->addChild(pEquipCompoundLayer,2);
    pEquipCompoundLayer->setEquipInfoByItemIndex(dwItemId);
}

void CcbEquipInlayLayer::RefeashLayer()
{
    this->showEquipInfoChanged();
    this->createShowList();
    this->createLayerData();
    m_pTableView->reloadData();
}

bool CcbEquipInlayLayer::NotifyErrorMsg(uint16 wErrorNo)
{
    if (wErrorNo == ERROR_MSG_ITEM_NOT_ENOUGH) {
        LP_ITEM_CONFIG pItemConfig = GET_CONFIG_STC(ItemConfig, E_RUNES_CNT_OPEN_ITEM);
        SystemMessage::showSystemMessage(1, this, CCString::createWithFormat(GET_STR(Str_Item_Not_Enough),pItemConfig->strName.c_str())->getCString(),this);
        return true;
    }
    return false;
    
}

void CcbEquipInlayLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CGameSession::SendOpenShopRequest();
}

void CcbEquipInlayLayer::showEquipInfoChanged()
{
    const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(g_EquipData->GetChosenEquipKeyID());
    if (pEquip)
    {
        if (pEquip->GetRune1()  != m_dwRuneID1)
        {
            uint32 dwRuneId = m_dwRuneID1 ? m_dwRuneID1 : pEquip->GetRune1();
            
            LP_RUNE_CONFIG pConfig = GET_CONFIG_STC(RuneConfig, dwRuneId);
            if (pConfig)
            {
                int EffectValue = m_dwRuneID1 ? pConfig->wEffectValue1 * -1 : pConfig->wEffectValue1;
                FlyTextLayer::showText(pConfig->byEffectType1, EffectValue);
            }
        }
        if (pEquip->GetRune2()  != m_dwRuneID2) {
            uint32 dwRuneId = m_dwRuneID2 ? m_dwRuneID2 : pEquip->GetRune2();
            
            LP_RUNE_CONFIG pConfig = GET_CONFIG_STC(RuneConfig, dwRuneId);
            if (pConfig)
            {
                int EffectValue = m_dwRuneID2 ? pConfig->wEffectValue1 * -1 : pConfig->wEffectValue1;
                FlyTextLayer::showText(pConfig->byEffectType1, EffectValue);
            }
        }
    }
    

}
