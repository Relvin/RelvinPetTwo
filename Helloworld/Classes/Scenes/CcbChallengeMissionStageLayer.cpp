#include "CcbChallengeMissionStageLayer.h"
#include "CcbChallengeNodeLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
//#include "CcbManager.h"

#define ANIMATIONTIME 0.08f

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark - Constructor -
CcbChallengeMissionStageLayer::CcbChallengeMissionStageLayer()
: m_pLayerStage(NULL)
, m_pNodeType1(NULL)
, m_pDelegate(NULL)
, m_bTouchMoved(false)
, m_vecStageInfo(NULL)
, m_pCurNode(NULL)
, m_BeginPoint(0,0)
, m_layerRect(0,0,0,0)
, m_fDistance(0.0f)
, m_nCurIndex(0)
{
    
}

CcbChallengeMissionStageLayer::~CcbChallengeMissionStageLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerStage);
    CC_SAFE_RELEASE_NULL(m_pNodeType1);
}

#pragma mark - initialization -
bool CcbChallengeMissionStageLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    
    this->setTouchEnabled(true);
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengeMissionStageLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerStage", CCLayer*, this->m_pLayerStage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeType1", CCNode*, this->m_pNodeType1);
	return false;
}

bool CcbChallengeMissionStageLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeMissionStageLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeMissionStageLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeMissionStageLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLeft", CcbChallengeMissionStageLayer::onPressControlButtonLeft);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRight", CcbChallengeMissionStageLayer::onPressControlButtonRight);
	return NULL;
}

#pragma mark - Visit Function -
void CcbChallengeMissionStageLayer::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!m_bVisible)
    {
        return;
    }
    kmGLPushMatrix();
    
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
    }
    
    this->transform();
    
    CCNode* pNode = NULL;
    unsigned int i = 0;
    
    if(m_pChildren && m_pChildren->count() > 0)
    {
        sortAllChildren();
        // draw children zOrder < 0
        ccArray *arrayData = m_pChildren->data;
        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];
            
            if ( pNode && pNode->getZOrder() < 0 )
            {
                if (pNode->getTag() == 101) {
                    //     kmGLPushMatrix();
                    glEnable(GL_SCISSOR_TEST);
                    CCEGLView::sharedOpenGLView()->setScissorInPoints(m_layerRect.origin.x, m_layerRect.origin.y, m_layerRect.size.width, m_layerRect.size.height);
                    pNode->visit();
                    glDisable(GL_SCISSOR_TEST);
                    //    kmGLPopMatrix();
                }else
                    pNode->visit();
                    }
            else
            {
                break;
            }
        }
        // self draw
        this->draw();
        
        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];
            if (pNode)
            {
                if (pNode->getTag() == 101)
                {
                    kmGLPushMatrix();
                    glEnable(GL_SCISSOR_TEST);
                    CCEGLView::sharedOpenGLView()->setScissorInPoints(m_layerRect.origin.x, m_layerRect.origin.y, m_layerRect.size.width, m_layerRect.size.height);
                    pNode->visit();
                    glDisable(GL_SCISSOR_TEST);
                    kmGLPopMatrix();
                }else
                    pNode->visit();
                    }
        }
    }
    else
    {
        this->draw();
    }
    
    // reset for next frame
    m_uOrderOfArrival = 0;
    
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->afterDraw(this);
    }
    
    kmGLPopMatrix();
}

#pragma mark - onNodeLoaded -
void CcbChallengeMissionStageLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
    CcbChallengeNodeLayer* pStageNode = NULL;
    for (int i = 0; i < 4; i++) {
        pStageNode = (CcbChallengeNodeLayer*)m_pLayerStage->getChildByTag(i);
        pStageNode->setZOrder(i == 2 ? 1 : 0);
        m_StagePoint[i] = pStageNode->getPosition();
        m_fStageScale[i] = pStageNode->getScale();
        pStageNode->setAttackCntVisible(false);
        pStageNode->setDropItemIconVisible(false);
        
    }
    m_fDistance = m_StagePoint[2].x - m_StagePoint[1].x;
    m_StagePoint[4] = ccp(m_StagePoint[3].x + m_fDistance,m_StagePoint[3].y);
    m_fStageScale[4] = m_fStageScale[0];
}

#pragma mark - onEnter & onExit -
void CcbChallengeMissionStageLayer::onEnter()
{
    CCLayer::onEnter();
    CCPoint layerPos = m_pLayerStage->convertToWorldSpace(CCPointZero);
    m_layerRect = CCRectMake(layerPos.x, layerPos.y, m_pLayerStage->getContentSize().width * this->getScale(), m_pLayerStage->getContentSize().height * this->getScale());
    this->loadMissionStageInfobyIndex(0);
}

void CcbChallengeMissionStageLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbChallengeMissionStageLayer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengeMissionStageLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Touch Functions -
bool CcbChallengeMissionStageLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_BeginPoint = pTouch->getLocation();
    m_bTouchMoved = false;
    if (m_layerRect.containsPoint(m_BeginPoint)) {
//        CCLOG("StartPoint = %f,%f",m_BeginPoint.x,m_BeginPoint.y);
        return true;
    }
    return false;
}

void CcbChallengeMissionStageLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPoint = pTouch->getLocation();
//    CCLOG("moveDis = %f",curPoint.x - m_BeginPoint.x);
    float fOffset = curPoint.x - m_BeginPoint.x;
    if (fabs(fOffset) > 10) {
        m_bTouchMoved = true;
    }
    
    if (fOffset < 0 ) {
        CcbChallengeNodeLayer* pStageNode = (CcbChallengeNodeLayer *)m_pLayerStage->getChildByTag(0);
        if (pStageNode) {
            pStageNode->setPosition(ccp(m_StagePoint[4].x + fOffset,m_StagePoint[4].y));
            pStageNode->setTag(4);
            pStageNode->setVisible(true);
            pStageNode->setChallengeNodeInfoByIndex((*m_vecStageInfo)[(m_nCurIndex + 2) % m_vecStageInfo->size()]);
        }
        
    }
    else if (fOffset > 0)
    {
        CcbChallengeNodeLayer* pStageNode = (CcbChallengeNodeLayer *)m_pLayerStage->getChildByTag(4);
        if (pStageNode) {
            pStageNode->setPosition(ccp(m_StagePoint[0].x + fOffset,m_StagePoint[0].y));
            pStageNode->setTag(0);
            pStageNode->setVisible(true);
            int index = m_nCurIndex - 2;
            if (index < 0) {
                index += 2 * m_vecStageInfo->size();
            }
            pStageNode->setChallengeNodeInfoByIndex((*m_vecStageInfo)[index % m_vecStageInfo->size()]);
        }
    }
    if (fabs(fOffset) > m_fDistance) {
        fOffset = fOffset > 0 ? m_fDistance : - m_fDistance;
    }
    
    this->updateStageNodePosByOffset(fOffset);
}

void CcbChallengeMissionStageLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPoint = pTouch->getLocation();
    float fOffset = curPoint.x - m_BeginPoint.x;
    if (fabs(fOffset) > 10) {
        m_bTouchMoved = true;
        this->changeStageNodeTagByDir(fOffset > 0 ? 1 : -1);
    }
    else
    {
        
        m_bTouchMoved = false;
    }
    
}

void CcbChallengeMissionStageLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void CcbChallengeMissionStageLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

#pragma mark - Button Functions -
void CcbChallengeMissionStageLayer::onPressControlButtonLeft(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CcbChallengeNodeLayer* pStageNode = (CcbChallengeNodeLayer *)m_pLayerStage->getChildByTag(4);
    if (pStageNode) {
        pStageNode->setTag(0);
        pStageNode->setVisible(true);
        int index = m_nCurIndex - 2;
        if (index < 0) {
            index += 2 * m_vecStageInfo->size();
        }
        pStageNode->setChallengeNodeInfoByIndex((*m_vecStageInfo)[index % m_vecStageInfo->size()]);
    }
    this->changeStageNodeTagByDir(1);
}

void CcbChallengeMissionStageLayer::onPressControlButtonRight(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CcbChallengeNodeLayer* pStageNode = (CcbChallengeNodeLayer *)m_pLayerStage->getChildByTag(0);
    if (pStageNode) {
        pStageNode->setTag(4);
        pStageNode->setVisible(true);
        pStageNode->setChallengeNodeInfoByIndex((*m_vecStageInfo)[(m_nCurIndex + 2) % m_vecStageInfo->size()]);
    }
        
    
    this->changeStageNodeTagByDir(-1);
}

#pragma mark - Self Functions -
void CcbChallengeMissionStageLayer::updateStageNodePosByOffset(float offset)
{
    CCNode* pStageNode = NULL;
    float fScale = 0.0f;
    float fPosy = 0.0f;
    for (int i = 0; i < 5; i++) {
        pStageNode = m_pLayerStage->getChildByTag(i);
        if (!pStageNode) {
            continue;
        }
        
        switch (i) {
            case 0:
            case 4:
            {
                fScale = m_fStageScale[i] + fabs(offset) / m_fDistance * fabs(m_fStageScale[i] - m_fStageScale[i + (offset > 0 ? 1 : -1)]);
                fPosy = m_StagePoint[i].y + fabs(offset) / m_fDistance * fabs(m_StagePoint[i].y - m_StagePoint[i + (offset > 0 ? 1 : -1)].y);
                break;
            }
            case 1:
            {
                fScale = m_fStageScale[i] + (offset) / m_fDistance * fabs(m_fStageScale[i] - m_fStageScale[i + (offset > 0 ? 1 : -1)]);
                fPosy = m_StagePoint[i].y + (offset) / m_fDistance * fabs(m_StagePoint[i].y - m_StagePoint[i + (offset > 0 ? 1 : -1)].y);
                break;
            }
            case 2:
            {
                fScale = m_fStageScale[i] - fabs(offset) / m_fDistance * fabs(m_fStageScale[i] - m_fStageScale[i + (offset > 0 ? 1 : -1)]);
                fPosy = m_StagePoint[i].y - fabs(offset) / m_fDistance * fabs(m_StagePoint[i].y - m_StagePoint[i + (offset > 0 ? 1 : -1)].y);
                break;
            }
            case 3:
            {
                fScale = m_fStageScale[i] - offset / m_fDistance * fabs(m_fStageScale[i] - m_fStageScale[i + (offset > 0 ? 1 : -1)]);
                fPosy = m_StagePoint[i].y - (offset) / m_fDistance * fabs(m_StagePoint[i].y - m_StagePoint[i + (offset > 0 ? 1 : -1)].y);
                break;
            }
            default:
                break;
        }
        pStageNode->setScale(fScale);
        pStageNode->setPosition( ccp(m_StagePoint[i].x + offset,fPosy));
    }
}

void CcbChallengeMissionStageLayer::changeStageNodeTagByDir(int nDir)
{
    m_nCurIndex -= nDir;
    if (nDir > 0 ){
        CCNode* pStageNode = NULL;
        for (int i = 4; i >= 0; i--) {
            pStageNode = m_pLayerStage->getChildByTag(i);
            if (!pStageNode) {
                continue;
            }
            pStageNode->setTag(i + 1 );
        }
        
        if (m_nCurIndex < 0) {
            m_nCurIndex += m_vecStageInfo->size();
        }
    }
    else
    {
        CCNode* pStageNode = NULL;
        for (int i = 0; i <= 4; i++) {
            pStageNode = m_pLayerStage->getChildByTag(i);
            if (!pStageNode) {
                continue;
            }
            pStageNode->setTag( i - 1);
        }
        m_nCurIndex = m_nCurIndex % m_vecStageInfo->size();
    }
    this->autoAdjustStageNodePos();
}

void CcbChallengeMissionStageLayer::autoAdjustStageNodePos()
{
    CcbChallengeNodeLayer* pStageNode = NULL;
    for (int i = 0; i < 5; i++) {
        pStageNode = (CcbChallengeNodeLayer*)m_pLayerStage->getChildByTag(i);
        if (!pStageNode) {
            continue;
        }
        pStageNode->runAction(CCSequence::create(CCSpawn::create(CCMoveTo::create(ANIMATIONTIME, m_StagePoint[i]),CCScaleTo::create(ANIMATIONTIME, m_fStageScale[i]) ,NULL),CCCallFunc::create(this, callfunc_selector(CcbChallengeMissionStageLayer::afterAnimationFinishCallBack)),NULL));
    }
    if (m_pCurNode) {
        m_pCurNode->setSelectSpriteVisible(false);
    }
    pStageNode = (CcbChallengeNodeLayer*)m_pLayerStage->getChildByTag(2);
    if (pStageNode) {
        if (m_pDelegate) {
            m_pDelegate->updateCurrentLayerInfoByIndex(pStageNode->getChallengeStageIndex());
        }
    }
    m_pCurNode = pStageNode;
    if (m_pCurNode) {
        m_pCurNode->setSelectSpriteVisible(true);
    }
}

void CcbChallengeMissionStageLayer::afterAnimationFinishCallBack()
{
    CCNode* pStageNode = NULL;
    for (int i = 0; i < 5; i++) {
        pStageNode = (CcbChallengeNodeLayer*)m_pLayerStage->getChildByTag(i);
        if (!pStageNode) {
            continue;
        }
        if (i == 0 || i == 4) {
            pStageNode->setVisible(false);
        }
        else{
            pStageNode->setVisible(true);
        }
    }
}

void CcbChallengeMissionStageLayer::loadMissionStageInfobyIndex(int nIndex)
{
    m_vecStageInfo = ChallengeCtrl::Get()->getChallengeStageInfoByMapId(ChallengeCtrl::Get()->getChallengeType());
    if (!m_vecStageInfo && m_vecStageInfo->size() == 0) {
        return;
    }
    CcbChallengeNodeLayer* pStageNode = NULL;
    for (int i = 0; i < 4 && i <= m_vecStageInfo->size(); i++) {
        pStageNode = (CcbChallengeNodeLayer*)m_pLayerStage->getChildByTag(i);
        if (!pStageNode) {
            continue;
        }
        int index = i - 2 + nIndex;
        if (index < 0) {
            index += m_vecStageInfo->size();
        }
        pStageNode->setChallengeNodeInfoByIndex((*m_vecStageInfo)[index]);
        pStageNode->setSelectSpriteVisible(false);
    }
    m_nCurIndex = nIndex ;
    
    pStageNode = (CcbChallengeNodeLayer*)m_pLayerStage->getChildByTag(2);
    if (pStageNode) {
        if (m_pDelegate) {
            m_pDelegate->updateCurrentLayerInfoByIndex(pStageNode->getChallengeStageIndex());
        }
    }
    m_pCurNode = pStageNode;
    if (m_pCurNode) {
        m_pCurNode->setSelectSpriteVisible(true);
    }
    
}

void CcbChallengeMissionStageLayer::setButtonVisible(bool bVisible)
{
    m_pNodeType1->setVisible(bVisible);
}


