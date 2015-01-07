/**
 * vCcbVipListLayer.cpp
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Relvin
 * Date: 2014-10-23 16:16:30
 */


#include "CcbVipListLayer.h"
#include "CcbManager.h"
#include "CcbVipFrameLayer.h"
#include "ConfigGet.h"
#include "GameSession.h"
#include "MusicCtrl.h"
#include "Role.h"


USING_NS_CC;
USING_NS_CC_EXT;

CcbVipListLayer::CcbVipListLayer()
: m_pSpriteTitle (NULL)
, m_pNodeTable (NULL)
, m_pControlButtonLeft (NULL)
, m_pControlButtonRight (NULL)
, m_pTableView(NULL)
, m_TouchBeginPos(0,0)
, m_nCurPage(0)
, m_nTotalPage(0)
, m_bTouchMoved(false)
{
    
}

CcbVipListLayer::~CcbVipListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteTitle);
	CC_SAFE_RELEASE_NULL(m_pNodeTable);
	CC_SAFE_RELEASE_NULL(m_pControlButtonLeft);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRight);

}

#pragma mark - Initialize -

bool CcbVipListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    
    this->setTouchEnabled(true);
    
	return true;
}

// Inhert MemberVariableAssigner
bool CcbVipListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTitle", CCSprite*, this->m_pSpriteTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTable", CCNode*, this->m_pNodeTable);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonLeft", CCControlButton*, this->m_pControlButtonLeft);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRight", CCControlButton*, this->m_pControlButtonRight);

	return false;
}

bool CcbVipListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbVipListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbVipListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbVipListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLeft", CcbVipListLayer::onPressControlButtonLeft);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRight", CcbVipListLayer::onPressControlButtonRight);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbVipListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_nTotalPage = GET_CONFIG_MAP(VipShowConfig).size();
    m_pTableView = CCTableView::create(this, m_pNodeTable->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionHorizontal);
    m_pTableView->setAnchorPoint(CCPointZero);
    m_pTableView->setDelegate(this);
    m_pTableView->setBounceable(false);
    m_pNodeTable->addChild(m_pTableView);
}

#pragma mark - onEnter -
void CcbVipListLayer::onEnter()
{
    CCLayer::onEnter();
}

void CcbVipListLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    m_pTableView->reloadData();
    CRole* pRole = CGameSession::GetRole();
    if (pRole)
    {
        if (pRole->GetbyVipLv() >= 0 && pRole->GetbyVipLv() < m_nTotalPage)
        {
            m_pTableView->scrollToIndex(pRole->GetbyVipLv());
            m_nCurPage = pRole->GetbyVipLv();
            this->setTitleShowInfo(pRole->GetbyVipLv());
        }
    }
}

#pragma mark - onExit -
void CcbVipListLayer::onExit()
{
    CCLayer::onExit();
}

void CcbVipListLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}


#pragma mark - TableView Functions -
void CcbVipListLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    
}

CCTableViewCell* CcbVipListLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbVipFrameLayer(this,m_pNodeTable->getContentSize());
        pNode->setPosition(ccp(0, 0));
        pCell->addChild(pNode, 1, 1);
    }
    
    CcbVipFrameLayer *pNode = (CcbVipFrameLayer*)pCell->getChildByTag(1);
    if (pNode)
    {
        pNode->setFrameInfoByIndex(idx);
    }
    return pCell;
}

unsigned int CcbVipListLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return m_nTotalPage;
}

CCSize CcbVipListLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return table->getViewSize();
}

#pragma mark - Button Functions -
void CcbVipListLayer::onPressControlButtonLeft(cocos2d::CCObject *pObject, cocos2d::extension::CCControlEvent event)
{
    if (!m_bTouchMoved) {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
        m_pTableView->scrollToIndex(m_nCurPage);
        this->updateTableViewPos(-1);
    }
    
}

void CcbVipListLayer::onPressControlButtonRight(cocos2d::CCObject *pObject, cocos2d::extension::CCControlEvent event)
{
    
    if (!m_bTouchMoved) {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
        m_pTableView->scrollToIndex(m_nCurPage);
        this->updateTableViewPos(1);
    }
}

#pragma mark - Touch Functions -
bool CcbVipListLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!this->isVisible()) {
        return false;
    }
    m_bTouchMoved = false;
    m_TouchBeginPos = pTouch->getLocation();
    CCPoint validPos = m_pNodeTable->convertToWorldSpaceAR(CCPointZero);
    if (!CCRectMake(validPos.x, validPos.y, m_pNodeTable->getContentSize().width, m_pNodeTable->getContentSize().height).containsPoint(m_TouchBeginPos)) {
        return false;
    }
    return true;
}

void CcbVipListLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchMoved = true;
}

void CcbVipListLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!m_bTouchMoved) {
        return;
    }
    CCPoint endPos = pTouch->getLocation();
    CCPoint validPos = m_pNodeTable->convertToWorldSpaceAR(CCPointZero);
    if (endPos.x < validPos.x) {
        endPos.x = validPos.x;
    }
    int movDir = 0;
    if (fabs(endPos.x - m_TouchBeginPos.x) > 50) {
        movDir = (m_TouchBeginPos.x - endPos.x) > 0 ? 1 : -1;
    }
    this->updateTableViewPos(movDir);
}

void CcbVipListLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void CcbVipListLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

#pragma mark - Self Functions -
void CcbVipListLayer::updateTableViewPos(int moveDir)
{
    if (m_nCurPage + moveDir < 0 || m_nCurPage + moveDir >= m_nTotalPage) {
        return;
    }
    m_pTableView->unscheduleAllSelectors();
    m_pTableView->getContainer()->stopAllActions();
    m_nCurPage += moveDir;
    
    float offset = - this->tableCellSizeForIndex(m_pTableView, 0).width * m_nCurPage;
    float during = fabsf((offset - m_pTableView->getContentOffset().x) / 800.0f);
    
    m_pTableView->setContentOffsetInDuration(ccp(offset, 0), during);
    this->setTitleShowInfo(m_nCurPage);
}

void CcbVipListLayer::setTitleShowInfo(int index )
{
    char szTemp[1024] = "\0";
    sprintf(szTemp, "ccbresources/12monthdate/vip/text_title%d.png",index);
    CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(szTemp);
    this->m_pSpriteTitle->setTexture(pTexture);

}

void CcbVipListLayer::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    m_pTableView->setTouchEnabled(visible);
    if (visible) {
        CRole* pRole = CGameSession::GetRole();
        if (pRole)
        {
            if (pRole->GetbyVipLv() > 0 && pRole->GetbyVipLv() < m_nTotalPage)
            {
                m_pTableView->scrollToIndex(pRole->GetbyVipLv());
                m_nCurPage = pRole->GetbyVipLv();
                this->setTitleShowInfo(pRole->GetbyVipLv());
                
            }
        }
    }
}

