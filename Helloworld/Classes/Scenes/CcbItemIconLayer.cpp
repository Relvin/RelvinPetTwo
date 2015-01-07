#include "CcbItemIconLayer.h"
//#include "CcbManager.h"
#include "UISupport.h"
#include "ItemDataMgr.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "GameSession.h"
#include "BackCtrl.h"
#include "PacketDataMgr.h"
#include "Equip.h"
#include "Emblem.h"
#include "EmblemDataMgr.h"
#include "CcbDropTipLayer.h"
#include "CcbItemInfoLayer.h"
#include "CcbEmblemInfoLayer.h"
#include "Instruments.h"
#include "Rune.h"
#include "EquipDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "GuideData.h"
#include "ResourceDefine.h"
#include "ResourceStringClient.h"
#include "FlyTextLayer.h"
#include "MusicCtrl.h"
#include "StageScene.h"
#include "GlobalData.h"
#include "ResourcePic.h"
#include "ChallengeCtrl.h"
#include "GuideData.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

USING_NS_CC;
USING_NS_CC_EXT;

CcbItemIconLayer::~CcbItemIconLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemNum);
    CC_SAFE_RELEASE_NULL(m_pSpriteBg);
    CC_SAFE_RELEASE_NULL(m_pSpriteIconFrame);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemLv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemEvoLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemStarLv);
	CC_SAFE_RELEASE_NULL(m_pSpriteStar);
    CC_SAFE_RELEASE_NULL(m_pSpriteAttribute);
    CC_SAFE_RELEASE_NULL(m_pSpriteNumBg);
    CC_SAFE_RELEASE_NULL(m_pSpriteChip);
    CC_SAFE_RELEASE_NULL(m_pNodeStar);
    
}

//-- copy this to CcbManager
/*
//CcbManager.h
CCNode* LoadCcbItemIconLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbItemIconLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbItemIconLayer", CcbItemIconLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_icon.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbItemIconLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbItemIconLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
	CCLayer::onEnterTransitionDidFinish();
}

void CcbItemIconLayer::onEnterTransitionDidFinish()
{

}

void CcbItemIconLayer::onExit()
{
	CCLayer::onExit();
}

void CcbItemIconLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbItemIconLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemName", CCLabelTTF*, this->m_pLabelTTFItemName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemNum", CCLabelTTF*, this->m_pLabelTTFItemNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemLv", CCLabelTTF*, this->m_pLabelTTFItemLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIconFrame", CCSprite*, this->m_pSpriteIconFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemEvoLv", CCLabelTTF*, this->m_pLabelTTFItemEvoLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemStarLv", CCLabelTTF*, this->m_pLabelTTFItemStarLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar", CCSprite*, this->m_pSpriteStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute", CCSprite*, this->m_pSpriteAttribute);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNumBg", CCSprite*, this->m_pSpriteNumBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteChip", CCSprite*, this->m_pSpriteChip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeStar", CCNode*, this->m_pNodeStar);
    
	return false;
}

bool CcbItemIconLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbItemIconLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbItemIconLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbItemIconLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSelect", CcbItemIconLayer::onPressControlButtonSelect);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbItemIconLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_byStar = 0;
    m_itemObjId = 0;
    m_itemIndexId = 0;
    m_byType = E_UNITE_TYPE_PET;
    m_isShowDropInfo = false;
    m_pLabelTTFItemName->setZOrder(4);
    m_pLabelTTFItemNum->getParent()->setZOrder(3);
    m_pLabelTTFItemLv->getParent()->setZOrder(3);
    m_pSpriteIconFrame->setZOrder(2);
    m_pSpriteStar->setZOrder(3);
    m_pSpriteAttribute->setZOrder(3);
    m_pLabelTTFItemEvoLv->setZOrder(3);
    m_pNodeStar->setZOrder(3);
    
    m_pLabelTTFItemNum->setEnableStroke(ccBLACK, 0.5);
    m_NumBgW = getWidth(m_pSpriteNumBg);
    
    m_btnShow = CCScrollButton::createTransWithHightLight();
    m_btnShow->setZoomOnTouchDown(false);
    m_btnShow->setPreferredSize(m_pSpriteIcon->getContentSize() - CCSizeMake(2, 2));
    m_btnShow->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbItemIconLayer::onPressControlButtonSelect), CCControlEventTouchUpInside);
    m_btnShow->setPosition(m_pSpriteIcon->getPosition());
    m_btnShow->ignoreAnchorPointForPosition(false);
    addChild(m_btnShow, 1);
    m_btnShow->setTouchPriority(kCCMenuHandlerPriority - 20);
    m_pSpriteChip->setVisible(false);
    
}

void CcbItemIconLayer::onPressControlButtonSelect(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    if (m_isShowDropInfo) {
        if (CGameSession::GetRole()->GetwGuideTrigger() < GuideData::E_GUIDE_END_TRIGGER) {
            FlyTextLayer::showTips("引导未结束");
            return;
        }
        
        if (m_itemIndexId / E_UNITE_BASE_FABIO == E_UNITE_TYPE_PET) {
            m_itemIndexId = 12100000 + m_itemIndexId;
        }
        CcbDropTipLayer::showDropTip(m_itemIndexId);
        return;
    }
   
    if (m_itemObjId == 0) {
        if (m_pDelegate) {
            m_pDelegate->itemIconTouchedCallBack(this, m_itemIndexId);
            return;
        }
        if (m_itemIndexId == 0) {
            return;
        }
        
        if (m_itemIndexId / E_UNITE_BASE_FABIO == E_UNITE_TYPE_PET) {
            CPetCtrl::Get()->setPetTujianShowId(m_itemIndexId);
            BackCtrl::InsertNextScene(kShowPetTujian, kNormalTrans);
            return;
        }
        if (m_itemIndexId)
        {
            CShowItemInfo::Get()->Show(m_itemIndexId);
            return;
        }
    }
    else
    {
        switch (m_byType) {
            case E_UNITE_TYPE_PET:
                if (m_pDelegate) {
                    m_pDelegate->itemIconTouchedCallBack(this, m_itemObjId);
                    return;
                }
                CPetCtrl::Get()->SetShowPetObjId(m_itemObjId); //暂时没用到，跳转到宠物详情}
                BackCtrl::InsertNextScene(kPetShowScene, kNormalTrans);
                return;
                break;
            case E_UNITE_TYPE_EMBLEM:   //用在徽章界面，显示徽章详情}
                CcbEmblemInfoLayer::showEmblemInfo(m_itemObjId);
                return;
                break;
            case E_UNITE_TYPE_EQUIP:    //没什么用}
//                CShowItemInfo::Get()->Show(m_itemIndexId);
                return;
                break;
            case E_UNITE_TYPE_RUNES:    //符文镶嵌时，用于镶嵌}
                if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_SYS_GUIDE_END_TOWER) {
                    GuideData::GetInstance()->onlyRmGuideLayer();
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
                    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("tower_guide_end");
#endif
                }
//                onRuneInplay();
                if (m_pDelegate) {
                    m_pDelegate->itemIconTouchedCallBack(this, m_itemObjId);
                }
                return;
            default:
                break;
        }
    }
}


void CcbItemIconLayer::loadObjData(uint32 itemObjId, E_UNITE_TYPE byType)
{
    m_pSpriteAttribute->setVisible(false);
    m_pSpriteChip->setVisible(false);
    m_itemObjId = itemObjId;
    m_byType = byType;
    m_byStar = 0;
    switch (m_byType) {
        case E_UNITE_TYPE_PET:
        {
            CPet* pet = CPetCtrl::Get()->GetPetByObjId(m_itemObjId);
            if (pet) {
                loadIndexData(pet->GetwIndex());
                showLv(pet->GetbyLv());
                showEvoLv(pet->GetbyEvolveLv());
                m_byStar = pet->GetbyStarLv();
            }
            else
            {
                loadIndexData(0);
            }
        }
            break;
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_SPECIAL:
        {
            
        }
            break;
        case E_UNITE_TYPE_EQUIP:
        {
            const CEquip* equip = g_PacketDataMgr->GetEquipInfoByKeyID(m_itemObjId);
            if (equip) {
                loadIndexData(equip->GetIndex());
                showLv(equip->GetLevel());
                showEvoLv(equip->getEvoLv());
                m_byStar = equip->GetConfigData().byStar;
            }
        }
            break;
        case E_UNITE_TYPE_RUNES:
        {
            const CRune *rune = g_PacketDataMgr->GetRuneInfoByKeyID(m_itemObjId);
            if (rune) {
                this->loadIndexData(rune->GetIndex());
                this->showCnt(rune->GetCnt());
            }
        }
            break;
        case E_UNITE_TYPE_CHEST:
        case E_UNITE_TYPE_GEM:
            
            break;
        case E_UNITE_TYPE_EMBLEM:
        {
            CEmblem* emblem = g_EmblemData->getEmblemByObjId(m_itemObjId);
            if (emblem) {
                loadIndexData(emblem->getdwIndexId());
                showLv(emblem->getbyLv());
            }
            else{
                m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage("ccbresources/12monthdate/pet.evo.enhance/emblem_bg.png"));
                m_pSpriteIconFrame->setDisplayFrame(g_PacketDataMgr->getQualityFrameSF(0));
                m_pSpriteBg->setDisplayFrame(g_PacketDataMgr->getQualityBgSF(0));
                showIconOnly();
            }
        }
            break;
            
        default:
            break;
    }
    
    showStarLv();
}

void CcbItemIconLayer::loadIndexData(uint32 itemIndexId)
{
    m_pSpriteAttribute->setVisible(false);
    m_pSpriteChip->setVisible(false);
    if (!itemIndexId) {
        m_pSpriteIcon->setVisible(false);
//        m_pSpriteAttribute->setVisible(false);
        showIconOnly();
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/quality.plist");
        m_pSpriteIconFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pet_nothing.png"));
//        m_pSpriteIconFrame->setDisplayFrame(g_PacketDataMgr->getQualityBgSF(0));
        return;
    }
    m_pSpriteIcon->setVisible(true);
    
    m_itemIndexId = itemIndexId;
    
    m_byStar = g_PacketDataMgr->getObjectStarByIndex(m_itemIndexId);
    
    m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetObjectIconByIndex(m_itemIndexId).c_str()));
    m_pLabelTTFItemName->setString(g_PacketDataMgr->GetObjectNameByIndex(m_itemIndexId).c_str());
    
    uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(m_itemIndexId);
    
    if (m_itemIndexId / E_UNITE_BASE_FABIO == E_UNITE_TYPE_PET) {
        m_pSpriteAttribute->setVisible(true);
        m_pSpriteAttribute->setDisplayFrame(CPetCtrl::Get()->GetPetNaturePicSF(m_itemIndexId));
    }
    
    if (!m_bSetNameColor) {
        m_pLabelTTFItemName->setColor(g_PacketDataMgr->getQualityColor(quality));
    }
    
    
    m_pSpriteIconFrame->setDisplayFrame(g_PacketDataMgr->getQualityFrameSF(quality));
    m_pSpriteBg->setDisplayFrame(g_PacketDataMgr->getQualityBgSF(quality));
    
    if (itemIndexId / E_UNITE_BASE_FABIO == E_UNITE_TYPE_ITEM) {
        ItemConfig::STC_ITEM_CONFIG* itemCfg = GET_CONFIG_STC(ItemConfig, itemIndexId);
        if (itemCfg &&
            (itemCfg->byType == E_ITEM_USE_EMBLEM_PATCH ||
            itemCfg->byType == E_ITEM_USE_PET_PATCH ||
            itemCfg->byType == E_ITEM_USE_EQUIP_PATCH)) {
                m_pSpriteChip->setVisible(true);
        }
    }
    
    showIconOnly();
    showName();
    
}

void CcbItemIconLayer::showIconOnly()
{
    
    hideLv();
    hideName();
    hideCnt();
    hideStarLv();
    hideEvoLv();
}

void CcbItemIconLayer::hideLv()
{
    if (m_pLabelTTFItemLv) {
        m_pLabelTTFItemLv->getParent()->setVisible(false);
    }
}

void CcbItemIconLayer::showLv(uint16 lv)
{
    if (m_pLabelTTFItemLv) {
        m_pLabelTTFItemLv->setString(CCString::createWithFormat("%s%d", SB_Lv,lv)->getCString());
        m_pLabelTTFItemLv->getParent()->setVisible(true);
    }
}


void CcbItemIconLayer::hideName()
{
    if (m_pLabelTTFItemName) {
        m_pLabelTTFItemName->setVisible(false);
    }
}


void CcbItemIconLayer::showName()
{
    if (m_pLabelTTFItemName) {
        m_pLabelTTFItemName->setVisible(true);
    }
}


void CcbItemIconLayer::hideCnt()
{
    if (m_pLabelTTFItemNum) {
        m_pLabelTTFItemNum->setVisible(false);
        
        if(m_pLabelTTFItemEvoLv && !m_pLabelTTFItemEvoLv->isVisible())
        {
            m_pSpriteNumBg->setVisible(false);
        }
    }
}

void CcbItemIconLayer::setCntFont(float fontSize)
{
    if (m_pLabelTTFItemNum) {
        m_pLabelTTFItemNum->setFontSize(fontSize);
        
        if (getWidth(m_pLabelTTFItemNum) > m_NumBgW) {
            m_pSpriteNumBg->setScaleX(getWidth(m_pLabelTTFItemNum) / m_NumBgW);
        }
        else{
            m_pSpriteNumBg->setScaleX(getWidth(m_pLabelTTFItemNum) / m_NumBgW * 1.2);
        }
        m_pSpriteNumBg->setVisible(true);
    }
}

void CcbItemIconLayer::showCnt(uint32 cnt)
{
    if (m_pLabelTTFItemNum) {
        m_pLabelTTFItemNum->setString(CCString::createWithFormat("%d", cnt)->getCString());
        m_pLabelTTFItemNum->setVisible(true);
        
        if (getWidth(m_pLabelTTFItemNum) > m_NumBgW) {
            m_pSpriteNumBg->setScaleX(getWidth(m_pLabelTTFItemNum) / m_NumBgW);
        }
        else{
            m_pSpriteNumBg->setScaleX(getWidth(m_pLabelTTFItemNum) / m_NumBgW * 1.2);
        }
        m_pSpriteNumBg->setVisible(true);
    }
}
void CcbItemIconLayer::showCntFromTo(uint32 cntF, uint32 cntTo)
{
    m_pLabelTTFItemNum->setVisible(true);
    if (cntF == cntTo) {
        m_pLabelTTFItemNum->setString(getMoneyStrFormat(cntF)->getCString());
    }
    else
    {
        m_pLabelTTFItemNum->setString(CCString::createWithFormat("%s~%s", getMoneyStrFormat(cntF)->getCString(), getMoneyStrFormat(cntTo)->getCString())->getCString());
    }
    
    if (getWidth(m_pLabelTTFItemNum) > m_NumBgW) {
        m_pSpriteNumBg->setScaleX(getWidth(m_pLabelTTFItemNum) / m_NumBgW);
    }
    else{
        m_pSpriteNumBg->setScaleX(getWidth(m_pLabelTTFItemNum) / m_NumBgW * 1.2);
    }
    m_pSpriteNumBg->setVisible(true);
}
//显示星级}
void CcbItemIconLayer::showStarLv(uint8 lv)
{
    if (lv == 0) {
        lv = m_byStar;
    }
    
    if (m_byStar <= 0) {
        hideStarLv();
        return;
    }
    m_pSpriteStar->setVisible(false);
#if 0
    if (m_pSpriteStar) {
        m_pSpriteStar->setVisible(true);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/star.plist");
        
        string framePath = CCString::createWithFormat("star_%d.png", lv)->getCString();
        m_pSpriteStar->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framePath.c_str()));
//        m_pLabelTTFItemStarLv->setString(CCString::createWithFormat("%d", lv)->getCString());
    }
#endif
    m_pNodeStar->removeAllChildren();
    CCSprite* pSpriteStar = NULL;
    float fWidth = 0.0f;
    m_pNodeStar->setVisible(true);
    for (int i = 0; i < lv; i++) {
        pSpriteStar = CCSprite::create(GET_PIC(Pic_Pet_Star_Level));
        m_pNodeStar->addChild(pSpriteStar);
        pSpriteStar->setAnchorPoint(CCPointZero);
        pSpriteStar->setPosition(ccp(fWidth, 0));
        
        float fSub = 4.0f;
        if (i == lv - 1) {
            fSub = 0.0f;
        }
        fWidth += pSpriteStar->getContentSize().width - fSub;
    }
    if (pSpriteStar) {
        m_pNodeStar->setContentSize(CCSizeMake(fWidth, pSpriteStar->getContentSize().height));
    }
}
//隐藏星级}
void CcbItemIconLayer::hideStarLv()
{
    if (m_pSpriteStar) {
        m_pSpriteStar->setVisible(false);
    }
    if (m_pNodeStar) {
        m_pNodeStar->setVisible(false);
    }
}

//显示阶级等级}
void CcbItemIconLayer::showEvoLv(uint16 lv)
{
    if (lv == 0) {
        hideEvoLv();
        return;
    }
    if (m_pLabelTTFItemEvoLv) {
        m_pLabelTTFItemEvoLv->setVisible(true);
        m_pLabelTTFItemEvoLv->setString(CCString::createWithFormat("+%d", lv)->getCString());
        
        if (getWidth(m_pLabelTTFItemEvoLv) > m_NumBgW) {
            m_pSpriteNumBg->setScaleX(getWidth(m_pLabelTTFItemEvoLv) / m_NumBgW);
        }
        else{
            m_pSpriteNumBg->setScaleX(getWidth(m_pLabelTTFItemNum) / m_NumBgW * 1.2);
        }
        m_pSpriteNumBg->setVisible(true);
    }
}

//隐藏进阶等级}
void CcbItemIconLayer::hideEvoLv()
{
    if (m_pLabelTTFItemEvoLv) {
        m_pLabelTTFItemEvoLv->setVisible(false);
        
        if(m_pLabelTTFItemNum && !m_pLabelTTFItemNum->isVisible())
        {
            m_pSpriteNumBg->setVisible(false);
        }
    }
}

/*!
 * 设置名字的描边
 */
void CcbItemIconLayer::setNameStroke(ccColor3B color)
{
    m_pLabelTTFItemName->setEnableStroke(color);
}
/*!
 * 取消名字的描边
 */
void CcbItemIconLayer::hideNameStroke()
{
    m_pLabelTTFItemName->noStroke();
}

void CcbItemIconLayer::setLabelNameColor(ccColor3B color)
{
    m_bSetNameColor = true;
    m_pLabelTTFItemName->setColor(color);
}

void CcbItemIconLayer::setBtnEnable(bool enable)
{
    if (m_btnShow) {
        m_btnShow->setEnabled(enable);
    }
}

void CcbItemIconLayer::setClipRect(CCRect rect)
{
    if (m_btnShow) {
        m_btnShow->setClipRect(rect);
    }
}

CCLabelTTF* CcbItemIconLayer::getItemCntLabel()
{
    return m_pLabelTTFItemNum;
}

void CcbItemIconLayer::setTouchPriority(int priority)
{
    m_btnShow->setTouchPriority(priority);
}

