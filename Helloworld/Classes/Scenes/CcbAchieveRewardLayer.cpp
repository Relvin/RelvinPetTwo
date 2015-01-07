#include "CcbAchieveRewardLayer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "CcbAchieveRewardFrameLayer.h"
#include "CCScrollViewWithBar.h"
#include "GameSession.h"
#include "EnumDefines.h"
#include "PacketDataMgr.h"
#include "UISupport.h"

CcbAchieveRewardLayer::~CcbAchieveRewardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerForList);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCount1);
	CC_SAFE_RELEASE_NULL(m_pSpriteCount1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCount2);
	CC_SAFE_RELEASE_NULL(m_pSpriteCount2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCount3);
	CC_SAFE_RELEASE_NULL(m_pSpriteCount3);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCount4);
	CC_SAFE_RELEASE_NULL(m_pSpriteCount4);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCount5);
	CC_SAFE_RELEASE_NULL(m_pSpriteCount5);
    CC_SAFE_RELEASE_NULL(m_tableView);
}


bool CcbAchieveRewardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbAchieveRewardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
}

void CcbAchieveRewardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    m_tableView->reloadData();
}

void CcbAchieveRewardLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
}

void CcbAchieveRewardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbAchieveRewardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerForList", CCLayer*, this->m_pLayerForList);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCount1", CCLabelTTF*, this->m_pLabelTTFCount1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCount1", CCSprite*, this->m_pSpriteCount1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCount2", CCLabelTTF*, this->m_pLabelTTFCount2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCount2", CCSprite*, this->m_pSpriteCount2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCount3", CCLabelTTF*, this->m_pLabelTTFCount3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCount3", CCSprite*, this->m_pSpriteCount3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCount4", CCLabelTTF*, this->m_pLabelTTFCount4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCount4", CCSprite*, this->m_pSpriteCount4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCount5", CCLabelTTF*, this->m_pLabelTTFCount5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCount5", CCSprite*, this->m_pSpriteCount5);

	return false;
}

bool CcbAchieveRewardLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbAchieveRewardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbAchieveRewardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbAchieveRewardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbAchieveRewardLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pLayerForList->setContentSize(CCSizeMake(getWidth(m_pLayerForList), getBottom(getChildByTag(333)) - getWorldPos(m_pLayerForList).y + 5));
    
    
    m_tableView = CCTableView::create(this, m_pLayerForList->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->setDelegate(this);
    m_tableView->retain();
    
    m_tableView->setAnchorPoint(CCPointZero);
    m_tableView->setPosition(CCPointZero);
    m_pLayerForList->addChild(m_tableView);
    
}

CCSize CcbAchieveRewardLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerForList), 70);
}

CCTableViewCell* CcbAchieveRewardLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbAchieveRewardFrameLayer(this);
        pNode->setPosition(getWidth(m_pLayerForList)* 0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbAchieveRewardFrameLayer* pNode = (CcbAchieveRewardFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->CreateData(g_TaskData->GetAchieveVector()[idx].dwIndex);
    }
    return pCell;
}

unsigned int CcbAchieveRewardLayer::numberOfCellsInTableView(CCTableView *table)
{
    return g_TaskData->GetAchieveVector().size();
}

void CcbAchieveRewardLayer::RefeashLayer()
{
    m_tableView->reloadData();
}





