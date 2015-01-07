#include "CcbActivityLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "CcbActivityNodeLayer.h"
#include "StageScene.h"
#include "ConfigGet.h"
#include "GuideData.h"
#include "UISupport.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbActivityLayer::~CcbActivityLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerUp);
    CC_SAFE_RELEASE_NULL(m_pLayerBg);
}


bool CcbActivityLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbActivityLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbActivityLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    //已开放活动在前，未开放活动在后}
    StageCtrl::VEC_SPE_MAP arrMap = StageCtrl::Get()->activityMapAll();
    m_nTableCnt = arrMap.size();
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_pTableList->reloadData();
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbActivityLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbActivityLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_1_CAT,
                                                 GuideData::E_SYS_GUIDE_2_TOWER,
                                                 GuideData::E_SYS_GUIDE_1_BADGE,
                                                 GuideData::E_SYS_GUIDE_5_1_BADGE,
                                                 NULL
                                                 );
    }
}

void CcbActivityLayer::onExit()
{
	CCLayer::onExit();
}

void CcbActivityLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbActivityLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerUp", CCLayer*, this->m_pLayerUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBg", CCLayer*, this->m_pLayerBg);

	return false;
}

bool CcbActivityLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


// Inhert CCNodeLoaderListener
void CcbActivityLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_clipRect.origin = getWorldPos(m_pLayerBg);
    m_pLayerBg->setContentSize(CCSizeMake(getWidth(m_pLayerBg), getBottom(m_pLayerUp) - m_clipRect.origin.y + 2));
    m_clipRect.size = m_pLayerBg->getContentSize();
    
    m_pTableList = CCTableView::create(this, m_pLayerBg->getContentSize());
    m_pTableList->setPosition(CCPointZero);
    
    m_pTableList->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableList->setDirection(kCCScrollViewDirectionVertical);
    m_pLayerBg->addChild(m_pTableList);
}

#pragma mark CCTableView Delegate
void CcbActivityLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    if (cell) {
        CCLog("Activity Touch Cell:%d", cell->getIdx());
    }
}

CCTableViewCell* CcbActivityLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CcbActivityNodeLayer* pNode = dynamic_cast<CcbActivityNodeLayer*>(CcbManager::sharedManager()->LoadCcbActivityNodeLayer(this));
        m_fCellWidth = pNode->getContentSize().width;
        m_fCellHeight = pNode->getContentSize().height;
        
        pNode->setNode(idx);
        pNode->setClipRect(m_clipRect);
        pNode->setPosition(getWidth(m_pLayerBg)*0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pCell->addChild(pNode);
        pNode->setTag(123);
    } else {
        CcbActivityNodeLayer* pNode = dynamic_cast<CcbActivityNodeLayer*>(pCell->getChildByTag(123));
        pNode->setNode(idx);
    }
    return pCell;
}

unsigned int CcbActivityLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return m_nTableCnt;
}

CCSize CcbActivityLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
//    CCLog("height: %f", m_fCellHeight);
    return CCSizeMake(m_fCellWidth, 80);
}




