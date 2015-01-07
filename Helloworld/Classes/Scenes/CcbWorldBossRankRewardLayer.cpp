#include "CcbWorldBossRankRewardLayer.h"
#include "CcbManager.h"
#include "CcbWorldBossRankRewardFrame.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "MusicCtrl.h"


CcbWorldBossRankRewardLayer::~CcbWorldBossRankRewardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerBg);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbWorldBossRankRewardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbWorldBossRankRewardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbWorldBossRankRewardLayer", CcbWorldBossRankRewardLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/world_boss_reward.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbWorldBossRankRewardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbWorldBossRankRewardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbWorldBossRankRewardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbWorldBossRankRewardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbWorldBossRankRewardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbWorldBossRankRewardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBg", CCLayer*, this->m_pLayerBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);

	return false;
}

bool CcbWorldBossRankRewardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbWorldBossRankRewardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbWorldBossRankRewardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbWorldBossRankRewardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbWorldBossRankRewardLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbWorldBossRankRewardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_clipRect.origin = getWorldPos(m_pLayerBg);
    m_clipRect.size = m_pLayerBg->getContentSize();
    
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 16);
    
    m_table = CCTableView::create(this, m_pLayerBg->getContentSize());
    m_table->ignoreAnchorPointForPosition(false);
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setTouchPriority(kCCMenuHandlerPriority - 16);
    m_table->setPosition(getWidth(m_pLayerBg)*0.5, 0);
    m_table->setAnchorPoint(ccp(0.5, 0));
    m_pLayerBg->addChild(m_table);
    
    loadData();
}


bool CcbWorldBossRankRewardLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return isVisible();
}

void CcbWorldBossRankRewardLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 15, true);
}

void CcbWorldBossRankRewardLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    this->setVisible(false);
}

void CcbWorldBossRankRewardLayer::loadData()
{
    arrRewardIndex.clear();
    
    std::map<uint16, WorldBossRewardConfig::STC_WORLD_BOSS_REWARD_CONFIG> mapRe = GET_CONFIG_MAP(WorldBossRewardConfig);
    std::map<uint16, WorldBossRewardConfig::STC_WORLD_BOSS_REWARD_CONFIG>::iterator it = mapRe.begin();
    for (; it != mapRe.end(); it ++) {
        if (!it->first) {
            continue;
        }
        arrRewardIndex.push_back(it->first);
    }
    
    m_table->reloadData();
}

CCSize CcbWorldBossRankRewardLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(getWidth(m_pLayerBg), 95+3);
}

CCTableViewCell* CcbWorldBossRankRewardLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell* cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbWorldBossRankRewardFrame();
        pNode->setPosition(getWidth(m_pLayerBg)*0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        cell->addChild(pNode, 1, 1);
    }
    
    CcbWorldBossRankRewardFrame* reF = dynamic_cast<CcbWorldBossRankRewardFrame*>(cell->getChildByTag(1));
    if (reF) {
        reF->loadData(arrRewardIndex[idx]);
        reF->setClipRect(m_clipRect);
    }
    
    return cell;
}

unsigned int CcbWorldBossRankRewardLayer::numberOfCellsInTableView(CCTableView *table)
{
    return arrRewardIndex.size();
}







