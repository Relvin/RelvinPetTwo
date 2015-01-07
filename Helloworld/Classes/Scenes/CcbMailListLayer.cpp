#include "CcbMailListLayer.h"
#include "CcbManager.h"
//#include "CcbMailFrameLayer.h"
#include "CcbBoxRewardFrame.h"
//#include "CcbMailDetailLayer.h"
#include "MailDataMgr.h"
#include "PetCtrl.h"
#include "EnumDefines.h"
#include "PacketDataMgr.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"

CcbMailListLayer::~CcbMailListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerForView);
    CC_SAFE_RELEASE_NULL(m_pLayerParent);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbMailListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbMailListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbMailListLayer", CcbMailListLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/mail_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

bool CcbMailListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    return true;
}

bool CcbMailListLayer::CreateTableView()
{
    m_tableView = CCTableView::create(this, m_pLayerForView->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setAnchorPoint(CCPointZero);
    m_tableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pLayerForView->addChild(m_tableView, 1, 1000);
    
    
    return true;
}

void CcbMailListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
}

void CcbMailListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    m_tableView->reloadData();
}

void CcbMailListLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
    
}

void CcbMailListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
    
}

// Inhert MemberVariableAssigner
bool CcbMailListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerForView", CCLayer*, this->m_pLayerForView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent", CCLayer*, this->m_pLayerParent);
    
	return false;
}

bool CcbMailListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbMailListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbMailListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbMailListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGet", CcbMailListLayer::onPressControlButtonGet);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbMailListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_clipRect.origin = getWorldPos(m_pLayerForView);
    m_pLayerForView->setContentSize(CCSizeMake(getWidth(m_pLayerForView), getBottom(getChildByTag(333)) - m_clipRect.origin.y + 5));
    m_clipRect.size  = m_pLayerForView->getContentSize();
    CreateTableView();
    
}

CCSize CcbMailListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerForView), 79 + 5);
}

CCTableViewCell* CcbMailListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbBoxRewardFrame* pCcbNode = dynamic_cast<CcbBoxRewardFrame* >(CcbManager::sharedManager()->LoadCcbBoxRewardFrame(this));
        if (pCcbNode)
        {
            pCcbNode->setPosition(getWidth(m_pLayerForView)*0.5, 0);
            pCcbNode->setAnchorPoint(ccp(0.5, 0));
            pCcbNode->ignoreAnchorPointForPosition(false);
            pCcbNode->setClipRect(m_clipRect);
            pCell->addChild(pCcbNode, 1, 123);
        }
    }
    CcbBoxRewardFrame *pNode = (CcbBoxRewardFrame*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->loadData(idx);
    }

    
    return pCell;
}

unsigned int CcbMailListLayer::numberOfCellsInTableView(CCTableView *table)
{
    return CMailDataMgr::Get()->GetSysMailList().size();
}

void CcbMailListLayer::RefeashLayer()
{
    CCPoint offPos = m_tableView->getContentOffset();
    m_tableView->reloadData();
    if (offPos.y < m_tableView->getViewSize().height - m_tableView->getContentSize().height) {
        offPos.y = m_tableView->getViewSize().height - m_tableView->getContentSize().height;
    }
    m_tableView->setContentOffset(offPos);
    
}

#pragma mark - Button Function -
void CcbMailListLayer::onPressControlButtonGet(CCObject*pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendMailReward(1);
}