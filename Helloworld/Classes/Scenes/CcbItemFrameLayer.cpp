#include "CcbItemFrameLayer.h"
#include "CcbManager.h"
#include "ItemDataMgr.h"
#include "PacketDataMgr.h"
#include "GameSession.h"
#include "EnumDefines.h"
#include "ResourceDefine.h"
#include "ResourceStringClient.h"
#include "CcbItemIconLayer.h"
#include "CCScrollButton.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "CcbJumpTipLayer.h"


CcbItemFrameLayer::~CcbItemFrameLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemDesc);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemCount);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon);
    //	CC_SAFE_RELEASE_NULL(m_pSpriteIconFrame);
    //	CC_SAFE_RELEASE_NULL(m_pSpriteLvStar);
    //	CC_SAFE_RELEASE_NULL(m_pControlButtonSale);
    //	CC_SAFE_RELEASE_NULL(m_pControlButtonCompound);
    CC_SAFE_RELEASE_NULL(m_pControlButtonUse);
    
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 CCNode* LoadCcbItemFrameLayer( CCObject* owner );
 
 //CcbManager.cpp
 CCNode* CcbManager::LoadCcbItemFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbItemFrameLayer", CcbItemFrameLayerLoader::loader() );
	
 
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_frame.ccbi", owner);
	pCCBReader->release();
 
	return pNode;
 }
 */


bool CcbItemFrameLayer::init()
{
    // First be called.
    if (!CCLayer::init()) {
        return false;
    }
    // code here
    setTouchEnabled(true);
    return true;
}

void CcbItemFrameLayer::onEnter()
{
    CCLayer::onEnter();
    //在scene()之后被调用}
    //这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbItemFrameLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
    
}

void CcbItemFrameLayer::onExit()
{
    CCLayer::onExit();
}

void CcbItemFrameLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbItemFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemName", CCLabelTTF*, this->m_pLabelTTFItemName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemDesc", CCLabelTTF*, this->m_pLabelTTFItemDesc);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemCount", CCLabelTTF*, this->m_pLabelTTFItemCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
    //	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIconFrame", CCSprite*, this->m_pSpriteIconFrame);
    //	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLvStar", CCSprite*, this->m_pSpriteLvStar);
    //	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSale", CCControlButton*, this->m_pControlButtonSale);
    //	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCompound", CCControlButton*, this->m_pControlButtonCompound);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonUse", CCScrollButton*, this->m_pControlButtonUse);
    
    return false;
}

bool CcbItemFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbItemFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
    return NULL;
}

SEL_MenuHandler CcbItemFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
    return NULL;
}

SEL_CCControlHandler CcbItemFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUse", CcbItemFrameLayer::onPressControlButtonUse);
    
    return NULL;
}

// Inhert CCNodeLoaderListener
void CcbItemFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    // 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
    // 可以删除，如果不需要}
    //CreateShowData();
    m_pControlButtonUse->setTouchPriority(kCCMenuHandlerPriority - 20);
}

void CcbItemFrameLayer::CreateShowData()
{
    const CItem* pItem = g_PacketDataMgr->GetItemInfoByIndex(m_dwItemShowIndex);
    if (!pItem)
    {
        return;
    }
    m_pLayerIcon->loadIndexData(pItem->GetIndex());
    m_pLayerIcon->showIconOnly();
    m_pLayerIcon->setBtnEnable(false);
    //        m_pLayerIcon->showCnt(pItem->GetCount());
    //        m_pLayerIcon->showStarLv(pItem->GetConfigData().byQuality);
    //设置物品名字}
    m_pLabelTTFItemName->setString(pItem->GetConfigData().strName.c_str());
    uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(m_dwItemShowIndex);
    m_pLabelTTFItemName->setColor(g_PacketDataMgr->getQualityColor(quality));
    //物品描述}
    m_pLabelTTFItemDesc->setString(pItem->GetConfigData().strDesc.c_str());
    
    //物品数量}
    CCString* str = CCString::createWithFormat("%s: %d", GET_STR(Str_shuliang), pItem->GetCount());
    m_pLabelTTFItemCount->setString(str->getCString());
    
    //显示“使用”和“合成”按钮}
    m_pControlButtonUse->setVisible(false);
    m_pControlButtonUse->setEnabled(true);
    switch (pItem->GetConfigData().byType)
    {
        case E_ITEM_USE_BOX:
        case E_ITEM_USE_ENERGY:
            //可以使用}
            m_pControlButtonUse->setVisible(true);
            break;
        default:
            break;
    }
    
    if (CShowJumpTip::Get()->getJumpType() == E_ITEM_NOT_ENOUGH) {
        uint32 itemId = CShowJumpTip::Get()->getNeedItemId();
        if (!itemId) {
            return;
        }
        if (itemId == m_dwItemShowIndex) {
            CCNode* pEffectNode = CcbManager::sharedManager()->LoadCcbStageEffLayer();
            pEffectNode->setPosition(this->getContentSize() * 0.5);
            pEffectNode->ignoreAnchorPointForPosition(false);
            pEffectNode->setAnchorPoint(ccp(0.5, 0.5));
            
            pEffectNode->setScaleX((this->getContentSize().width) / pEffectNode->getContentSize().width);
            pEffectNode->setScaleY((this->getContentSize().height) / pEffectNode->getContentSize().height);
            this->addChild(pEffectNode, 60, 111);
        } else if (getChildByTag(111)) {
            getChildByTag(111)->removeFromParent();
        }
    }
    
}

void CcbItemFrameLayer::onPressControlButtonUse(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    const CItem* pItem = g_PacketDataMgr->GetItemInfoByIndex(m_dwItemShowIndex);
    if (pItem)
    {
        switch (pItem->GetConfigData().byType)
        {
            case E_ITEM_USE_BOX:
            {
                if (checkBoxAndKey()) {
                    CGameSession::SendItemUse(pItem->GetIndex(), pItem->GetCount());//物品ObjID，物品数量}
                }
                else{
                    return;
                }
            }
                break;
            case E_ITEM_USE_ENERGY:
            {
                //碎片,合成}
                CGameSession::SendItemUse(pItem->GetIndex(), pItem->GetCount());//物品ObjID，物品数量}
            }
                break;
            default:
                break;
        }
        if (pItem->GetIndex() != E_ITEM_ENERGY) {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
        }
    }
}

bool CcbItemFrameLayer::checkBoxAndKey()
{
    bool ret = true;
    
    const CItem* pItem = g_PacketDataMgr->GetItemInfoByIndex(m_dwItemShowIndex);
    ItemConfig::STC_ITEM_CONFIG *itemCfg = GET_CONFIG_STC(ItemConfig, pItem->GetIndex());
    
    if(!itemCfg->wParas[1]){
        return ret;
    }
    
    int cnt = g_PacketDataMgr->GetItemCountByIndex(itemCfg->wParas[1]);
    if (cnt == 0) {
        CShowJumpTip::Get()->Show(E_ITEM_NOT_ENOUGH, itemCfg->wParas[1]);
        ret = false;
    }
    
    return ret;
}

void CcbItemFrameLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    const CItem* pItem = g_PacketDataMgr->GetItemInfoByIndex(m_dwItemShowIndex);
    if (pItem)
    {
        CGameSession::SendSellItem(pItem->GetIndex(), pItem->GetCount());
    }
}

void CcbItemFrameLayer::setClipRect(CCRect rect)
{
    m_pControlButtonUse->setClipRect(rect);
}


