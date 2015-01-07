#include "CcbSystemMailBoardLayer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "GameSession.h"
#include "ResourceDefine.h"
#include "UISupport.h"
#include "PetLoadingLayer.h"
#include "CcbItemIconLayer.h"


CcbSystemMailBoardLayer::~CcbSystemMailBoardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonGet);
	CC_SAFE_RELEASE_NULL(m_pLayerIconList);
	CC_SAFE_RELEASE_NULL(m_pLayerContent);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbSystemMailBoardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbSystemMailBoardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbSystemMailBoardLayer", CcbSystemMailBoardLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system_reward_board.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbSystemMailBoardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    setTouchEnabled(true);
	// code here
	return true;
}

void CcbSystemMailBoardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbSystemMailBoardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbSystemMailBoardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbSystemMailBoardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbSystemMailBoardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGet", CCControlButton*, this->m_pControlButtonGet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIconList", CCLayer*, this->m_pLayerIconList);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerContent", CCLayer*, this->m_pLayerContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);

	return false;
}

bool CcbSystemMailBoardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbSystemMailBoardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbSystemMailBoardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbSystemMailBoardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGet", CcbSystemMailBoardLayer::onPressControlButtonGet);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbSystemMailBoardLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbSystemMailBoardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pControlButtonGet->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    
    m_pTableView = CCTableView::create(this, m_pLayerIconList->getContentSize());
    m_pTableView->setDirection( kCCScrollViewDirectionHorizontal );
    m_pTableView->setAnchorPoint(CCPointZero);
    m_pTableView->setPosition(CCPointZero);
    m_pTableView->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    m_pLayerIconList->addChild(m_pTableView, 1);
}



void CcbSystemMailBoardLayer::onPressControlButtonGet(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (m_mailId > 0) {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        uint32 dwMailID = m_mailId;
        CGameSession::SendMailReward(0,dwMailID);
    }
    
    removeFromParent();
}

void CcbSystemMailBoardLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));

    removeFromParent();
}


void CcbSystemMailBoardLayer::showMail(int wIndex)
{
    CcbSystemMailBoardLayer* layer = dynamic_cast<CcbSystemMailBoardLayer*>(CcbManager::sharedManager()->LoadCcbSystemMailBoardLayer());
    if (layer) {
        layer->loadData(wIndex);
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 999);
    }
}
void CcbSystemMailBoardLayer::loadData(int wIndex)
{
    
    VEC_MAIL_INFO tempList = CMailDataMgr::Get()->GetSysMailList();
    tempInfo = tempList[tempList.size()-wIndex-1];
    
    m_mailId = tempInfo.dwMailId;
    
    
    CCScrollView* scroll = CCScrollView::create(m_pLayerContent->getContentSize());
    scroll->setContentSize(m_pLayerContent->getContentSize());
    m_pLayerContent->addChild(scroll);
    
    CCLabelTTF* lblContent = CCLabelTTF::create(tempInfo.strContent.c_str(), FONT_HEL, 12, CCSizeMake(getWidth(m_pLayerContent) - 10, 0), kCCTextAlignmentLeft );
    lblContent->ignoreAnchorPointForPosition(false);
    lblContent->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    
    lblContent->setAnchorPoint(ccp(0, 0));
    if (getHeight(lblContent) > getHeight(m_pLayerContent)) {
        scroll->setContentSize(CCSizeMake(getWidth(m_pLayerContent), getHeight(lblContent)));
        lblContent->setPosition(ccp(5, 0));
        scroll->setContentOffset(ccp(0, getHeight(m_pLayerContent) - getHeight(lblContent)));
    }
    else{
        lblContent->setPosition(ccp(5, getHeight(m_pLayerContent) - getHeight(lblContent)));
    }
    
    scroll->addChild(lblContent);
    
    scroll->setDirection(kCCScrollViewDirectionVertical);
    scroll->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    
    
    //
    
    m_pTableView->reloadData();
    m_rect.origin = getWorldPos(m_pLayerIconList);
    m_rect.size = m_pLayerIconList->getContentSize();
    
}

//tableView相关}
CCSize CcbSystemMailBoardLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(60, 65);
}

CCTableViewCell* CcbSystemMailBoardLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbItemIconLayer* pIcon = dynamic_cast<CcbItemIconLayer*>(CcbManager::sharedManager()->LoadCcbItemIconLayer(this));
        pIcon->setAnchorPoint(ccp(0.5, 0.5));
        pIcon->setPosition(ccp(30, 35));
        pCell->addChild(pIcon);
        pIcon->setTag(123);
    }
//    else {
    CcbItemIconLayer* pIcon = dynamic_cast<CcbItemIconLayer*>(pCell->getChildByTag(123));
    if (!pIcon) {
        return NULL;
    }
    pIcon->loadIndexData(tempInfo.vecRewareInfo[idx].dwRewId);
    pIcon->showIconOnly();
    pIcon->showName();
    pIcon->showCnt(tempInfo.vecRewareInfo[idx].dwRewCnt);
    pIcon->setBtnEnable(false);
    pIcon->setClipRect(m_rect);
//    }
    return pCell;
}

unsigned int CcbSystemMailBoardLayer::numberOfCellsInTableView(CCTableView *table)
{
    return tempInfo.vecRewareInfo.size();
}

bool CcbSystemMailBoardLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbSystemMailBoardLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*2, true);
}


