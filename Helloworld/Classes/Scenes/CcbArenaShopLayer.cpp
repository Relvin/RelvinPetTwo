#include "CcbArenaShopLayer.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "CcbArenaShopFrameLayer.h"
#include "CCScrollViewWithBar.h"
#include "ArenaDataMgr.h"
#include "Role.h"
#include "EnumDefines.h"
#include "ConfigGet.h"
#include "GuideData.h"
#include "CcbItemInfoButtonLayer.h"
#include "ResourceStringClient.h"
#include "PacketDataMgr.h"
#include "UISupport.h"

CcbArenaShopLayer::~CcbArenaShopLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerViewSize);
	CC_SAFE_RELEASE_NULL(m_pLabelTTF1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFReputation);
    CC_SAFE_RELEASE_NULL(m_pLayerReputation);
    CC_SAFE_RELEASE_NULL(m_pLayerTop);
    CC_SAFE_RELEASE_NULL(m_pLayerBottom);
    CC_SAFE_RELEASE_NULL(m_tableView);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaShopLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaShopLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaShopLayer", CcbArenaShopLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_shop.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaShopLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbArenaShopLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
}

void CcbArenaShopLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    m_tableView->reloadData();
    
//    this->runAction( CCSequence::create(CCDelayTime::create(TRANS_DUR*0.5), CCCallFunc::create(this, callfunc_selector(CcbArenaShopLayer::addGuideLayer)), NULL) );
}

void CcbArenaShopLayer::addGuideLayer()
{
//    GuideData::GetInstance()->addGuideofEnum(GuideData::E_SYS_GUIDE_JJC_5, NULL);
//    GuideData::GetInstance()->connectToServer();
}

void CcbArenaShopLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
}

void CcbArenaShopLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaShopLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerViewSize", CCLayer*, this->m_pLayerViewSize);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF1", CCLabelTTF*, this->m_pLabelTTF1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFReputation", CCLabelTTF*, this->m_pLabelTTFReputation);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerReputation", CCLayer*, this->m_pLayerReputation);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTop", CCLayer*, this->m_pLayerTop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, this->m_pLayerBottom);
    
	return false;
}

bool CcbArenaShopLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaShopLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaShopLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaShopLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaShopLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    char szTemp[16] = "";
    CRole* pRole = CGameSession::GetRole();
    sprintf(szTemp, "%d", pRole->GetdwReputation());
    m_pLabelTTFReputation->setString(szTemp);
    
    m_clipRect.origin = getWorldPos(m_pLayerViewSize);
    m_pLayerViewSize->setContentSize(CCSizeMake(getWidth(m_pLayerViewSize),getBottom(m_pLayerTop) - m_clipRect.origin.y + 5));
    m_clipRect.size = m_pLayerViewSize->getContentSize();
    
    m_tableView = CCTableView::create(this, m_pLayerViewSize->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->retain();
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    
    m_pLayerViewSize->addChild(m_tableView);

}


CCSize CcbArenaShopLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerViewSize), 91 + 5);
}

CCTableViewCell* CcbArenaShopLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbArenaShopFrameLayer(this);
        pNode->setPosition(ccp(getWidth(m_pLayerViewSize)*0.5, 0));
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbArenaShopFrameLayer* pNode = (CcbArenaShopFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->loadData(idx);
        pNode->setClipRect(m_clipRect);
    }

    return pCell;
}

unsigned int CcbArenaShopLayer::numberOfCellsInTableView(CCTableView *table)
{
    return CArenaDataMgr::Get()->GetShopList().size();
}

void CcbArenaShopLayer::RefeashLayer()
{
    char szTemp[16] = "";
    CRole* pRole = CGameSession::GetRole();
    sprintf(szTemp, "%d", pRole->GetdwReputation());
    m_pLabelTTFReputation->setString(szTemp);
    CCPoint offPos = m_tableView->getContentOffset();
    m_tableView->reloadData();
    m_tableView->setContentOffset(offPos);
}
