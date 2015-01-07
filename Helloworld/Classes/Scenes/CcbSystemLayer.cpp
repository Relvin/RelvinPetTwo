#include "CcbSystemLayer.h"
#include "CcbManager.h"
#include "CcbSysFriendFrameLayer.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "UISupport.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark SystemScene
CCScene* SystemScene::scene() {
    CCScene* pScene = CCScene::create();
    SystemScene* pLayer = SystemScene::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

bool SystemScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbSystemLayer(this));
    return true;
}

void SystemScene::onEnter()
{
    CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_friend));
}

void SystemScene::onExit()
{
    CCLayer::onExit();
}

bool SystemScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}


#pragma mark SystemLayer

CcbSystemLayer::~CcbSystemLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerViewSize);
    CC_SAFE_RELEASE_NULL(m_pLayerHeadBack);
    m_vecCell.clear();
}

//-- copy this to CcbManager 
/*
//CcbManager.h


//CcbManager.cpp

*/


bool CcbSystemLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    STC_SYS sFriendReq;
    sFriendReq.strName = GET_STR(Str_friend_invite);
    sFriendReq.nTag = CcbSysFriendFrameLayer::kFriendRequst;
    m_vecSystem.push_back(sFriendReq);
    
    STC_SYS sFriendMail;
    sFriendMail.strName = GET_STR(Str_email_search);
    sFriendMail.nTag = CcbSysFriendFrameLayer::kFriendMailTag;
    m_vecSystem.push_back(sFriendMail);
    
    STC_SYS sFriendList;
    sFriendList.strName = GET_STR(Str_friend_list);
    sFriendList.nTag = CcbSysFriendFrameLayer::kFriendListTag;
    m_vecSystem.push_back(sFriendList);
    
    STC_SYS sFriendApply;
    sFriendApply.strName = GET_STR(Str_friend_add);
    sFriendApply.nTag = CcbSysFriendFrameLayer::kFriendAddTag;
    m_vecSystem.push_back(sFriendApply);
    
	return true;
}

void CcbSystemLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbSystemLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    m_bRestored = false;
    bool bFirst = true;
    m_fDelay = (m_vecCell.size()-1) * m_fDelta;
    CCLog("cell size:%lu", m_vecCell.size());

    int nCnt = m_vecCell.size();
    for (int i = 0; i < nCnt; i++) {
        if (m_vecCell[i]->getParent()->getParent()) {
            if (m_fDelay == 0.0f) {
                m_vecCell[i]->runAction(
                                        CCMoveBy::create(TRANS_DUR*0.5, ccp(-winSize.width, 0))
                                        );
            } else {
                m_vecCell[i]->runAction(
                                        CCSequence::create(
                                                           CCDelayTime::create(m_fDelay),
                                                           CCMoveBy::create(TRANS_DUR*0.5, ccp(-winSize.width, 0)),
                                                           NULL
                                                           )
                                        );
                if (bFirst) {
                    bFirst = false;
                    this->runAction(
                                    CCSequence::create(
                                                       CCDelayTime::create(TRANS_DUR*0.5+0.2f),
                                                       CCCallFunc::create(this, callfunc_selector(CcbSystemLayer::setTouchRestore)),
                                                       NULL
                                                       )
                                    );
                }
            }
        }
        m_fDelay -= m_fDelta;
    }
}

void CcbSystemLayer::setTouchRestore() {
    for (int i = 0; i < m_vecCell.size(); i++) {
        if (m_vecCell[i]->getPositionX() != 160.0f) {
            m_vecCell[i]->setPositionX(160.0f);
        }
    }
    m_bRestored = true;
}

void CcbSystemLayer::onExit()
{
	CCLayer::onExit();
}

void CcbSystemLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
    m_fDelay = 0;
    int nCnt = m_vecCell.size();
    for (int i = 0; i < nCnt; i++) {
        if (m_vecCell[i]->getParent()->getParent()) {
            m_vecCell[i]->runAction(
                                    CCSequence::create(CCDelayTime::create(m_fDelay),
                                                       CCMoveBy::create(TRANS_DUR*0.5, ccp(winSize.width, 0)),
                                                       NULL
                                                       )
                                    );
            m_fDelay += m_fDelta;
        }
    }
}

// Inhert MemberVariableAssigner
bool CcbSystemLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHeadBack", CCLayer*, this->m_pLayerHeadBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerViewSize", CCLayer*, this->m_pLayerViewSize);
	return false;
}

bool CcbSystemLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
void CcbSystemLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    winSize = CCDirector::sharedDirector()->getWinSize();
    m_nTableCnt = m_vecSystem.size();
    
    m_pLayerViewSize->setContentSize(CCSizeMake(getWidth(m_pLayerViewSize), getBottom(m_pLayerHeadBack) - getWorldPos(m_pLayerViewSize).y + 5 ));
    
    CCLog("content size:[%f, %f]", m_pLayerViewSize->getContentSize().width, m_pLayerViewSize->getContentSize().height);
    
    m_pTableList = CCTableView::create(this, m_pLayerViewSize->getContentSize());
    m_pTableList->setDirection(kCCScrollViewDirectionVertical);
    m_pTableList->setPosition(CCPointZero);
    m_pLayerViewSize->addChild(m_pTableList);
    
    m_pTableList->reloadData();
}

#pragma mark CCTableView Delegate
void CcbSystemLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    if (cell) {
        CCLog("cell touch at index:%d", cell->getIdx());
    }
}

CCTableViewCell* CcbSystemLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCLOG("table cell at index");
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();

        CcbSysFriendFrameLayer* pNode = dynamic_cast<CcbSysFriendFrameLayer*>(CcbManager::sharedManager()->LoadCcbSysFriendFrameLayer(this));
        if (!pNode) {
            return NULL;
        }
        // setNodeData
        pNode->setNodeData(m_vecSystem[idx].strName, m_vecSystem[idx].nTag);
        
        if (m_bRestored) {
            pNode->setPosition(ccp(160.0f, 0));
        } else {
            pNode->setPosition(ccp(winSize.width + 160.0f, 0));
        }
        
        m_vecCell.push_back(pNode);
        
        pCell->addChild(pNode);
        pNode->setTag(123);
    } else {
        CcbSysFriendFrameLayer* pNode = dynamic_cast<CcbSysFriendFrameLayer*>(pCell->getChildByTag(123));
        if (!pNode) {
            return NULL;
        }
        // setNodeData
        pNode->setNodeData(m_vecSystem[idx].strName, m_vecSystem[idx].nTag);
    }
    return pCell;
}

unsigned int CcbSystemLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return m_nTableCnt;
}

CCSize CcbSystemLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(245.0f, 62.0f);
}


