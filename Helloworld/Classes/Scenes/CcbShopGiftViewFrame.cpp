#include "CcbShopGiftViewFrame.h"
#include "CcbItemIconLayer.h"
#include "PacketDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbShopGiftViewFrame::CcbShopGiftViewFrame()
: m_pNodeGiftIcon (NULL)
, m_pLabelTTFGiftName (NULL)
, m_pLabelTTFGiftIntroduce (NULL)
{
}

CcbShopGiftViewFrame::~CcbShopGiftViewFrame()
{
	CC_SAFE_RELEASE_NULL(m_pNodeGiftIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFGiftName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFGiftIntroduce);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* Loadshop_giftbag_prerviewframe( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::Loadshop_giftbag_prerviewframe( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "shop_giftbag_prerviewframe", shop_giftbag_prerviewframeLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/item_icon.ccb]", [ccb/item_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_giftbag_prerviewframe.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbShopGiftViewFrame::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbShopGiftViewFrame::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbShopGiftViewFrame::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbShopGiftViewFrame::onExit()
{
	CCLayer::onExit();
}

void CcbShopGiftViewFrame::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbShopGiftViewFrame::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeGiftIcon", CcbItemIconLayer*, this->m_pNodeGiftIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGiftName", CCLabelTTF*, this->m_pLabelTTFGiftName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGiftIntroduce", CCLabelTTF*, this->m_pLabelTTFGiftIntroduce);

	return false;
}

bool CcbShopGiftViewFrame::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbShopGiftViewFrame::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbShopGiftViewFrame::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbShopGiftViewFrame::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbShopGiftViewFrame::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
}


void CcbShopGiftViewFrame::setFrameInfoByItemIndex(ChestConfig::STC_UNITE_RESOURCE &cellItem)
{
    m_cellItem = cellItem;
    m_pNodeGiftIcon->loadIndexData(m_cellItem.dwUniteId);
    m_pNodeGiftIcon->showIconOnly();
    m_pNodeGiftIcon->showCnt(m_cellItem.dwUniteCnt);
    m_pNodeGiftIcon->setTouchPriority(kCCMenuHandlerPriority - 22);
 
    m_pLabelTTFGiftName->setString(g_PacketDataMgr->GetObjectNameByIndex(cellItem.dwUniteId).c_str());
    m_pLabelTTFGiftIntroduce->setString(g_PacketDataMgr->GetObjectDescByIndex(cellItem.dwUniteId).c_str());
    
}








