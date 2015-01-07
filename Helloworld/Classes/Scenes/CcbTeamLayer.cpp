#include "CcbTeamLayer.h"
#include "CcbManager.h"
#include "Team.h"
#include "TeamCtrl.h"
#include "CcbTeamFrameLayer.h"
#include "GameSession.h"
#include "BackCtrl.h"
#include "CcbHeaderBackLayer.h"
#include "ResourceStringClient.h"
#include "PetLoadingLayer.h"
#include "UISupport.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "ChallengeCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define MOVE_INCH            7.0f/160.0f

TeamScene::~TeamScene()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    
}

CCScene *TeamScene::scene()
{
    CCScene *scene = CCScene::create();
    CCLayer *layer = TeamScene::create();
    scene->addChild(layer);
    return scene;
}

bool TeamScene::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    this->addChild(CcbManager::sharedManager()->LoadCcbTeamLayer(this));
    
	return true;
}

void TeamScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_pLabelTTFName->setString(GET_STR(Str_layer_team));
    ChallengeCtrl::Get()->setChallengePetChoose(false);
}

void TeamScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void TeamScene::onExit()
{
	CCLayer::onExit();
}

void TeamScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool TeamScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool TeamScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


CcbTeamLayer::~CcbTeamLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerBack);
	CC_SAFE_RELEASE_NULL(m_pControlButtonShowValue);
	CC_SAFE_RELEASE_NULL(m_pLayerTeam_1);
	CC_SAFE_RELEASE_NULL(m_pLayerTeamBg);
	CC_SAFE_RELEASE_NULL(m_pLayerArrowLeft);
	CC_SAFE_RELEASE_NULL(m_pControlButtonLeft);
	CC_SAFE_RELEASE_NULL(m_pLayerArrowRight);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRight);
    CC_SAFE_RELEASE_NULL(m_pControlButtonChgLeader);
    m_bLockSlide = false;
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTeamLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTeamLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTeamLayer", CcbTeamLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/arrowleft.ccb]", [ccb/arrowleft.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/arrowright.ccb]", [ccb/arrowright.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/teamview.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbTeamLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_bDragging = false;
    m_bTouchMoved = false;
    m_fTouchLength = 0;
    m_isCanTouch = true;
	return true;
}

void CcbTeamLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbTeamLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbTeamLayer::addGuide)),
                                       NULL
                                       )
                    );
    
    PetLoadingLayer::sharedLayer()->End();
}

void CcbTeamLayer::addGuide()
{
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_2_TEAM,
                                             GuideData::E_GUIDE_TRIGGER_4_TEAM,
                                             GuideData::E_SYS_GUIDE_7_BADGE,
                                             NULL
                                             );
    m_bCanTouchBtn = true;
}

void CcbTeamLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTeamLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTeamLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBack", CCLayer*, this->m_pLayerBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShowValue", CCControlButton*, this->m_pControlButtonShowValue);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTeam_1", CcbTeamFrameLayer*, this->m_pLayerTeam_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTeamBg", CCLayer*, this->m_pLayerTeamBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerArrowLeft", CCLayer*, this->m_pLayerArrowLeft);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonLeft", CCControlButton*, this->m_pControlButtonLeft);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerArrowRight", CCLayer*, this->m_pLayerArrowRight);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRight", CCControlButton*, this->m_pControlButtonRight);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonChgLeader", CCControlButton*, this->m_pControlButtonChgLeader);
	return false;
}

bool CcbTeamLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTeamLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_MenuHandler CcbTeamLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler CcbTeamLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShowValue", CcbTeamLayer::onPressControlButtonShowValue);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLeft", CcbTeamLayer::onPressControlButtonLeft);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRight", CcbTeamLayer::onPressControlButtonRight);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonChgLeader", CcbTeamLayer::onPressControlButtonChgLeader);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTeamLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pLayerArrowLeft->setVisible(false);
    m_pLayerArrowRight->setVisible(false);
    arrTeams[0] = m_pLayerTeam_1;

    m_bShowValue = true;
    m_pLayerTeam_1->setDelegate(this);

    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger == GuideData::E_GUIDE_TRIGGER_2_TEAM) {
        m_pControlButtonLeft->setVisible(false);
        m_pControlButtonRight->setVisible(false);
        m_bLockSlide = true;
    }
}


void CcbTeamLayer::onPressControlButtonChgLeader(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    m_pControlButtonRight->getParent()->setVisible(false);
    arrTeams[0]->startLeaderChg();
}

void CcbTeamLayer::onPressControlButtonShowValue(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_bShowValue = !m_bShowValue;
    arrTeams[0]->showPetBaseValue(m_bShowValue);
    if (m_bShowValue) {
        m_pControlButtonShowValue->setTitleForState(CCString::createWithFormat("%s%s", GET_STR(Str_yincang), GET_STR(Str_nature)), CCControlStateNormal);
    }
    else{
        m_pControlButtonShowValue->setTitleForState(CCString::createWithFormat("%s%s", GET_STR(Str_xianshi), GET_STR(Str_nature)), CCControlStateNormal);
    }
    
}

void CcbTeamLayer::onPressControlButtonLeft(CCObject* pSender, CCControlEvent event)
{
    if (m_isCanTouch)
    {
        changePage(1);
    }
}

void CcbTeamLayer::onPressControlButtonRight(CCObject* pSender, CCControlEvent event)
{
    if (m_isCanTouch)
    {
        changePage(-1);
    }
}


void CcbTeamLayer::loadData()
{
    std::map<uint8, CTeam*> mapAll = CTeamCtrl::GetAllTeam();
    curPage = CTeamCtrl::GetCurTeamId();
    CTeam *team = mapAll[curPage];
    
    m_pLayerTeam_1->setTeamId(team->getbyTeamId());
    m_pLayerTeam_1->showPetBaseValue(m_bShowValue);
}

bool CcbTeamLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bLockSlide) {
        return false;
    }
    
    if (!m_isCanTouch) {
        return true;
    }
    m_tTouchPoint = convertTouchToNodeSpace(pTouch);
    m_bTouchMoved = false;
    m_bDragging = true;
    m_tScrollDistance = ccp(0.0f, 0.0f);
    m_fTouchLength    = 0.0f;
    
    return true;
}

void CcbTeamLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bLockSlide) {
        return;
    }
    
    if (m_bDragging) {
        CCPoint moveDistance, newPoint, maxInset, minInset;
        CCRect  frame;
        
        frame = CCRectMake(m_pLayerTeamBg->getPosition().x - m_pLayerTeamBg->getContentSize().width * m_pLayerTeamBg->getAnchorPoint().x, m_pLayerTeamBg->getPosition().y - m_pLayerTeamBg->getContentSize().height * m_pLayerTeamBg->getAnchorPoint().y, m_pLayerTeamBg->getContentSize().width, m_pLayerTeamBg->getContentSize().height);
        
        newPoint     = this->convertTouchToNodeSpace(pTouch);
        moveDistance = ccpSub(newPoint, m_tTouchPoint);
        
        float dis = 0.0f;
        
        dis = moveDistance.x;
        
        
        if (!m_bTouchMoved && fabs(convertDistanceFromPointToInch(dis)) < MOVE_INCH )
        {
            //CCLOG("Invalid movement, distance = [%f, %f], disInch = %f", moveDistance.x, moveDistance.y);
             m_tScrollDistance = CCPointZero;
            return;
        }
        
        if (!m_bTouchMoved)
        {
            moveDistance = CCPointZero;
        }
        
        m_tTouchPoint = newPoint;
        m_bTouchMoved = true;
        
        if (frame.containsPoint(this->convertToWorldSpace(newPoint)))
        {
            m_tScrollDistance = ccp(moveDistance.x, 0.0f);
        }
    }
}

void CcbTeamLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bLockSlide) {
        return;
    }
    
    if (m_bTouchMoved) {
        relocateContainer();
    }
    m_bTouchMoved = false;
    m_bDragging = false;
}

void CcbTeamLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchMoved) {
        relocateContainer();
    }
    m_bTouchMoved = false;
    m_bDragging = false;
}

void CcbTeamLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-2, false);
}
float CcbTeamLayer::convertDistanceFromPointToInch(float pointDis)
{
    float factor = ( CCEGLView::sharedOpenGLView()->getScaleX() + CCEGLView::sharedOpenGLView()->getScaleY() ) / 2;
    return pointDis * factor / CCDevice::getDPI();
}
void CcbTeamLayer::moveTeamLayer(CCPoint moveDis)
{
    m_fTouchLength += moveDis.x;
    for (int i = 0; i < 6; i ++) {
        arrTeams[i]->setPosition(ccpAdd(arrTeams[i]->getPosition(), moveDis));
    }
}

void CcbTeamLayer::relocateContainer()
{
    int off = 0;
    if (m_tScrollDistance.x > 8.0)
    {
        off = 1;
    }
    else if (m_tScrollDistance.x < -8.0)
    {
        off = -1;
    }
    else
    {
        if (m_fTouchLength <= -160) {
            off = -1;
        }
        else if(m_fTouchLength >= 160)
        {
            off = 1;
        }
    }
    changePage(off);
}

void CcbTeamLayer::changePage(int off)
{
    if (off == 0) {
        return;
    }
    m_isCanTouch = false;
    
    uint8 nextPage = curPage+6 - off;
    
    nextPage = (nextPage)%6;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    std::map<uint8, CTeam*> mapAll = CTeamCtrl::GetAllTeam();
    arrTeams[1]->setVisible(false);
    arrTeams[1]->setTeamId(mapAll[nextPage]->getbyTeamId());
    arrTeams[1]->showPetBaseValue(m_bShowValue);
    if (off > 0) {
        arrTeams[1]->setPositionX(-winSize.width * 0.5);
    }
    else
    {
        arrTeams[1]->setPositionX(winSize.width * 1.5);
    }
    arrTeams[1]->setVisible(true);
    
    if (nextPage != CTeamCtrl::GetCurTeamId()) {
        CTeamCtrl::ChgCurTeam(nextPage);
    }
    
    for (int i = 0; i < 2; i ++) {
        CcbTeamFrameLayer *frame = arrTeams[i];
        
        if (!frame) {
            continue;
        }
        
        frame->runAction(CCSequence::create(
                                            CCMoveBy::create(0.2, ccp(off * winSize.width, 0)),
                                            CCCallFunc::create(this, callfunc_selector(CcbTeamLayer::afterChgPage)),
                                            NULL));
        
    }
    curPage = nextPage;
    CcbTeamFrameLayer *frame1 = arrTeams[0];
    CcbTeamFrameLayer *frame2 = arrTeams[1];
    arrTeams[0] = frame2;
    arrTeams[1] = frame1;
}

int CcbTeamLayer::getPageInitOff(int page)
{
    int off = page - curPage;
    if (off < -3) {
        off += 6;
    }
    else if(off > 2)
    {
        off -= 6;
    }
    return off;
}


void CcbTeamLayer::afterChgPage()
{
    m_isCanTouch = true;
}

void CcbTeamLayer::endLeaderChg()
{
    m_pControlButtonRight->getParent()->setVisible(true);
}



