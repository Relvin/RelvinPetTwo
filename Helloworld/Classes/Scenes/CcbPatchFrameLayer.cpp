#include "CcbPatchFrameLayer.h"
#include "CcbManager.h"
#include "Item.h"
#include "ItemDataMgr.h"
#include "CcbItemIconLayer.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "PacketDataMgr.h"
#include "CCScrollButton.h"
#include "GameSession.h"
#include "CcbDropTipLayer.h"
#include "MusicCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPatchFrameLayer* CcbPatchFrameLayer::createCCNode(cocos2d::CCNode *pParent, cocos2d::extension::CCBReader *pCCBReader)
{
    CcbPatchFrameLayer *ret = new CcbPatchFrameLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        ret->setAnimationManager(pCCBReader->getAnimationManager());
        return ret;
    }
    CC_SAFE_RELEASE_NULL(ret);
    return NULL;
}

CcbPatchFrameLayer::CcbPatchFrameLayer()
: m_pLabelTTFItemName (NULL)
, m_pLabelTTFItemCount (NULL)
, m_pLayerIcon (NULL)
, m_pControlButtonCompound (NULL)
, m_pLabelTTFNotEnough (NULL)
, m_pNodeNotEnough (NULL)
, m_dwItemIndex(0)
, m_pAnimationmanager(NULL)
{
    
    
}

CcbPatchFrameLayer::~CcbPatchFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemCount);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCompound);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNotEnough);
    CC_SAFE_RELEASE_NULL(m_pNodeNotEnough);
    CC_SAFE_RELEASE_NULL(m_pAnimationmanager);

}

#pragma mark - Initialization -
bool CcbPatchFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbPatchFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemName", CCLabelTTF*, this->m_pLabelTTFItemName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemCount", CCLabelTTF*, this->m_pLabelTTFItemCount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCompound", CCScrollButton*, this->m_pControlButtonCompound);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNotEnough", CCLabelTTF*, this->m_pLabelTTFNotEnough);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNotEnough", CCNode*, this->m_pNodeNotEnough);

	return false;
}

bool CcbPatchFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbPatchFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPatchFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPatchFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCompound", CcbPatchFrameLayer::onPressControlButtonCompound);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGoto", CcbPatchFrameLayer::onPressControlButtonGoto);

	return NULL;
}

#pragma mark - NodeLoaded -
// Inhert CCNodeLoaderListener
void CcbPatchFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

#pragma mark - onEnter & onExit -
void CcbPatchFrameLayer::onEnter()
{
    CCLayer::onEnter();

}

void CcbPatchFrameLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    this->updateShowItemInfo();
}

void CcbPatchFrameLayer::onExit()
{
    CCLayer::onExit();
}

void CcbPatchFrameLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Button Functions -
void CcbPatchFrameLayer::onPressControlButtonCompound(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    const CItem* pItem = g_PacketDataMgr->GetItemInfoByIndex(m_dwItemIndex);
    if (pItem)
    {
        if (g_ItemData->GetItemShowMode() == MODE_SHOW_PET_CHIP)
        {
            CGameSession::SendItemUse(pItem->GetIndex(), pItem->GetConfigData().wParas[0]);
        }
        else
        {
            CGameSession::SendItemUse(pItem->GetIndex(), pItem->GetCount());//物品ObjID，物品数量}
        }
    }
}

void CcbPatchFrameLayer::onPressControlButtonGoto(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CcbDropTipLayer::showDropTip(m_dwItemIndex);
}

#pragma mark - Self Functions -
void CcbPatchFrameLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *animationMgr)
{
    CC_SAFE_RELEASE_NULL(m_pAnimationmanager);
    m_pAnimationmanager = animationMgr;
    CC_SAFE_RETAIN(m_pAnimationmanager);
}

void CcbPatchFrameLayer::updateShowItemInfo()
{
    const CItem* pItem = g_PacketDataMgr->GetItemInfoByIndex(m_dwItemIndex);
    if (pItem)
    {
        m_pLayerIcon->loadIndexData(pItem->GetIndex());
        m_pLayerIcon->showIconOnly();
        m_pLayerIcon->setBtnEnable(false);
        m_pLayerIcon->showStarLv();
        //设置物品名字}
        m_pLabelTTFItemName->setString(pItem->GetConfigData().strName.c_str());
        m_pLabelTTFItemName->setColor(g_PacketDataMgr->getQualityColor(g_PacketDataMgr->getObjectQualityByIndex(m_dwItemIndex)));
        
        //物品数量}
        CCString* str = CCString::createWithFormat("%s: %d/%d", GET_STR(Str_shuliang), pItem->GetCount(),pItem->GetConfigData().wParas[0]);
        m_pLabelTTFItemCount->setString(str->getCString());
        
        if (pItem->GetCount() >= pItem->GetConfigData().wParas[0]) {
            m_pNodeNotEnough->setVisible(false);
            m_pControlButtonCompound->setVisible(true);
        }
        else
        {
            m_pControlButtonCompound->setVisible(false);
            m_pNodeNotEnough->setVisible(true);
            if (m_pAnimationmanager) {
                m_pAnimationmanager->runAnimationsForSequenceNamed("Default Timeline");
            }
        }
    }
}

void CcbPatchFrameLayer::setClipRect(CCRect rect)
{
    m_pControlButtonCompound->setClipRect(rect);
}

