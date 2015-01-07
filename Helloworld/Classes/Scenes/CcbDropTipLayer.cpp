#include "CcbDropTipLayer.h"
#include "CcbManager.h"
#include "CCScrollViewWithBar.h"
#include "EnumDefines.h"
#include "UISupport.h"
#include "ConfigGet.h"
#include "ResourceStringConverter.h"
#include "ResourceDefine.h"
#include "StageScene.h"
#include "PacketDataMgr.h"
#include "MusicCtrl.h"
#include "CcbDropTipFrameLayer.h"
#include "GameSession.h"

CcbDropTipLayer::~CcbDropTipLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerText);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDes);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCollectNum);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTextYishouji);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbDropTipLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbDropTipLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbDropTipLayer", CcbDropTipLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow_drop_tip.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbDropTipLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbDropTipLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbDropTipLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbDropTipLayer::onExit()
{
	CCLayer::onExit();
}

void CcbDropTipLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbDropTipLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerText", CCLayer*, this->m_pLayerText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDes", CCLabelTTF*, this->m_pLabelTTFDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCollectNum", CCLabelTTF*, this->m_pLabelTTFCollectNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTextYishouji", CCLabelTTF*, this->m_pLabelTTFTextYishouji);

	return false;
}

bool CcbDropTipLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbDropTipLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbDropTipLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbDropTipLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbDropTipLayer::onPressControlButtonBack);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbDropTipLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    
    arrId.clear();
    
    m_pLabelTTFName->noStroke();
    m_pLabelTTFTextYishouji->noStroke();
    
    m_table = CCTableView::create(this, m_pLayerText->getContentSize());
    m_table->setPosition(CCPointZero);
    m_table->setAnchorPoint(CCPointZero);
    m_table->setBounceable(true);
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setTouchPriority(kCCMenuHandlerPriority*2 - 1);

    CCTableViewWithBar* bar = CCTableViewWithBar::create(m_table);
    bar->setPosition(CCPointZero);
    bar->setAnchorPoint(CCPointZero);
    m_pLayerText->addChild(bar, 1, 101);
}

void CcbDropTipLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    removeFromParent();
}

void CcbDropTipLayer::showDropTip(uint32 varId)
{
    CcbDropTipLayer* layer = dynamic_cast<CcbDropTipLayer*>(CcbManager::sharedManager()->LoadCcbDropTipLayer());
    layer->ignoreAnchorPointForPosition(false);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    layer->setPosition(ccp(winSize.width* 0.5, winSize.height*0.5));
    CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 999);
    
    layer->loadData(varId);
}

void CcbDropTipLayer::loadData(uint32 varId)
{
    if (!varId) {
        return;
    }
    
    m_pLayerIcon->loadIndexData(varId);
    m_pLayerIcon->showIconOnly();
    m_pLayerIcon->setBtnEnable(false);
    
    m_pLabelTTFName->setString(g_PacketDataMgr->GetObjectNameByIndex(varId).c_str());
    
    m_pLabelTTFCollectNum->setString(CCString::createWithFormat("%d", g_PacketDataMgr->GetItemCountByIndex(varId))->getCString());
    
    EvolveInfoConfig::STC_EVOLVE_INFO_CONFIG* cfg = GET_CONFIG_STC(EvolveInfoConfig, varId);
    if (!cfg) {
        return;
    }
    m_pLabelTTFDes->setString(cfg->strDes.c_str());
    int len = 0;
    GET_ARRAY_LEN(cfg->arrStageId, len);
    if (len > 4) {
        len = 4;
    }
    for (int i = 0; i < len; i++) {
        if (cfg->arrStageId[i] == 0 && cfg->arrStageType[i] == 0) {
            continue;
        }
        arrId.push_back(cfg->arrStageId[i]);
        arrType.push_back(cfg->arrStageType[i]);
        arrDropProb.push_back(cfg->arrDropProb[i]);
    }
    m_table->reloadData();
    
    dynamic_cast<CCTableViewWithBar*>(m_pLayerText->getChildByTag(101))->checkIsShow(numberOfCellsInTableView(m_table), cellSizeForTable(m_table));
}

bool CcbDropTipLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void CcbDropTipLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*2, true);
}

CCSize CcbDropTipLayer::cellSizeForTable(CCTableView *table)
{
    return CCSize(getWidth(m_pLayerText), 50 + 5);
}

CCTableViewCell* CcbDropTipLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CcbDropTipFrameLayer* pNode = dynamic_cast<CcbDropTipFrameLayer*>(CcbManager::sharedManager()->LoadCcbDropTipFrameLayer());
//        CGameSession::Attach(pNode);
        pNode->setPosition(getWidth(m_pLayerText) *0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pNode->setClipRect(clipRect);
        pNode->loadData(arrId[idx], arrType[idx], arrDropProb[idx]);
        pCell->addChild(pNode, 1, 123);
    } else {
        CcbDropTipFrameLayer* pNode = (CcbDropTipFrameLayer*)pCell->getChildByTag(123);
        if (pNode)
        {
            pNode->loadData(arrId[idx], arrType[idx], arrDropProb[idx]);
        }
    }
    return pCell;
}

unsigned int CcbDropTipLayer::numberOfCellsInTableView(CCTableView *table)
{
    return arrId.size();
}


