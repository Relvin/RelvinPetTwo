#include "CcbShowGetLayer.h"
#include "CcbManager.h"
#include "CcbItemIconLayer.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "GlobalData.h"
#include "SystemMessage.h"
#include "StageLayer.h"
#include "GuideBtnPos.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbShowGetLayer::~CcbShowGetLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIconList);
	CC_SAFE_RELEASE_NULL(m_pControlButtonConfirm);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLabelTitle);
    m_vecIndex.clear();
    m_vecCnt.clear();
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbShowGetLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbShowGetLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbShowGetLayer", CcbShowGetLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/reward_tip.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbShowGetLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbShowGetLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    if (!m_bJustShow) {
        CMusicCtrl::PlayEffect( GET_MUSIC(Eff_get_reward) );
    }
}

void CcbShowGetLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    m_pTableViewIcons->reloadData();
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbShowGetLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbShowGetLayer::addGuideLayer() {
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {

        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonConfirm, GuideBtnPos::E_JUMP_NEXT);
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_GUIDE_TRIGGER_1_GET_STAR,
                                                 GuideData::E_SYS_GUIDE_1_MYSTERY,
                                                 GuideData::E_SYS_GUIDE_7_MYSTERY,
                                                 NULL
                                                 );
    }
}

void CcbShowGetLayer::onExit()
{
	CCLayer::onExit();
}

void CcbShowGetLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbShowGetLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIconList", CCLayer*, this->m_pLayerIconList);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonConfirm", CCControlButton*, this->m_pControlButtonConfirm);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTitle", CCLabelTTF*, this->m_pLabelTitle);
	return false;
}

bool CcbShowGetLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbShowGetLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbShowGetLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbShowGetLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonConfirm", CcbShowGetLayer::onPressControlButtonConfirm);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbShowGetLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pTableViewIcons = CCTableView::create(this, m_pLayerIconList->getContentSize());
    m_pTableViewIcons->setPosition(CCPointZero);
    m_pTableViewIcons->setAnchorPoint(CCPointZero);
    m_pTableViewIcons->setDirection(kCCScrollViewDirectionVertical);
    m_pTableViewIcons->setVerticalFillOrder( kCCTableViewFillTopDown );
    m_pLayerIconList->addChild(m_pTableViewIcons);
    m_pTableViewIcons->setTouchPriority(kCCMenuHandlerPriority*2-1);
    
    m_pControlButtonConfirm->setTouchPriority(kCCMenuHandlerPriority*2 - 2);
}



void CcbShowGetLayer::onPressControlButtonConfirm(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));

    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideData::GetInstance()->onlyRmGuideLayer();
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_GUIDE_TRIGGER_JUMP_NEXT,
                                                 GuideData::E_SYS_GUIDE_2_MYSTERY,
                                                 GuideData::E_SYS_GUIDE_8_MYSTERY,
                                                 NULL
                                                 );
    }
    
    removeFromParentAndCleanup(true);
    
    if (GlobalData::bJumpToTwo && StageLayer::getCurLayer()) {
        SystemMessage::showSystemMessage(0, NULL, GET_STR(Str_jump_next), StageLayer::getCurLayer(), true, 0, GET_STR(Str_tishi), true);
    }
}

void CcbShowGetLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*2, true);
}

bool CcbShowGetLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCPoint pos = this->getPosition();
    CCSize size = this->getContentSize();
    CCPoint origin = ccp(pos.x - size.width*0.5, pos.y - size.height*0.5);
    
    point = ccpSub(point, origin);
    
    CCRect tableRec = CCRectMake(m_pLayerIconList->getPositionX(), m_pLayerIconList->getPositionY(), m_pLayerIconList->getContentSize().width, m_pLayerIconList->getContentSize().height);
    if (tableRec.containsPoint(point)) {

    } else {
        if (!m_bShowItemInfo) {
            onPressControlButtonConfirm(NULL, CCControlEventTouchUpInside);
        }
    }
    return true;
}

void CcbShowGetLayer::addGetItem(uint32 dwIndex, int nCnt)
{
    for (int i = 0; i < m_vecIndex.size(); i++) {
        if (m_vecIndex[i] == dwIndex) {
            // already have
            m_vecCnt[i] += nCnt;
            return;
        }
    }
    m_vecIndex.push_back(dwIndex);
    m_vecCnt.push_back(nCnt);
    return;
}

void CcbShowGetLayer::reloadItems()
{
    m_pTableViewIcons->reloadData();

    if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_1_GET_STAR) {
        GuideData::GetInstance()->connectToServer();
    }
}

#pragma mark CCTableViewDelegate
void CcbShowGetLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    
}

CCTableViewCell* CcbShowGetLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell* pCell = table->dequeueCell();
    
    int curIdx = idx*4;
    float offWidth = 58.0f;
    int j = 0;
    
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();

        if (curIdx >= m_vecIndex.size()) {
            CCAssert(1, "What's Wrong?");
        }
        
        for (curIdx = idx*4, j = 0; curIdx < MIN(m_vecIndex.size(), idx*4+4) && j < 4; curIdx++, j++) {
            CcbItemIconLayer* pNode = dynamic_cast<CcbItemIconLayer*>(CcbManager::sharedManager()->LoadCcbItemIconLayer(this));
            if (!pNode) {
                CCAssert(1, "Init Get Icon Error");
            }
            
            pNode->loadIndexData(m_vecIndex[curIdx]);// setIconContent(m_vecIndex[curIdx], m_vecCnt[curIdx]);
            pNode->showCnt(m_vecCnt[curIdx]);
            pNode->setAnchorPoint(CCPointZero);
            pNode->setPosition(ccp(3.0 + (curIdx-idx*4) * offWidth, 0));
            pNode->setTag(j);
            pCell->addChild(pNode);
        }

    } else {
        if (curIdx >= m_vecIndex.size()) {
            CCAssert(1, "What's Wrong?");
        }
        
        for (curIdx = idx*4, j = 0; curIdx < MIN(m_vecIndex.size(), idx*4+4) && j < 4; curIdx++, j++) {
            CcbItemIconLayer* pNode = dynamic_cast<CcbItemIconLayer*>(pCell->getChildByTag(j));
            if (!pNode) {
                CCAssert(1, "Get Icon From pCell Error, Check your Tag!");
            }
            
            pNode->loadIndexData(m_vecIndex[curIdx]);// setIconContent(m_vecIndex[curIdx], m_vecCnt[curIdx]);
            pNode->showCnt(m_vecCnt[curIdx]);
            pNode->setTouchPriority(m_nPriority);
        }

    }
    return pCell;
}

unsigned int CcbShowGetLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    int cellNum = m_vecIndex.size();
    if (cellNum) {
        cellNum = (cellNum-1)/4 + 1;
    }
    CCLOG("cell Num:%d", cellNum);
    return cellNum;
}

CCSize CcbShowGetLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCSize viewSize = m_pLayerIconList->getContentSize();
    return CCSizeMake(viewSize.width - 20.0f, 64.0f);
}

void CcbShowGetLayer::setShowGetLayerTitle(const char *title)
{
    m_bJustShow = true;
    m_pLabelTitle->setString(title);
}

void CcbShowGetLayer::setNeedShowItemInfo(bool isShow)
{
    m_bShowItemInfo = isShow;
    if (isShow) {
        m_nPriority = kCCMenuHandlerPriority * 2 - 1;
    }
    else
    {
        m_nPriority = 0;
    }
}
