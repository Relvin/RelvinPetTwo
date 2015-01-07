#include "CcbCaptureFrameLayer.h"
//#include "CcbManager.h"
#include "CaptureScene.h"
#include "GameSession.h"
#include "Instruments.h"
#include "FlccMovieClip.h"
#include "FlccMovieFPSAction.h"
#include "FlccMovieAction.h"
#include "SequenceAction.h"
#include "SequencePet.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbCaptureFrameLayer::~CcbCaptureFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTimeL);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTimeR);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNameL);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNameR);
	CC_SAFE_RELEASE_NULL(m_pControlButtonL);
	CC_SAFE_RELEASE_NULL(m_pControlButtonR);
    CGameSession::Detach(this);
}

//-- copy this to CcbManager
/*
//CcbManager.h


//CcbManager.cpp

*/


bool CcbCaptureFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CGameSession::Attach(this);
	return true;
}

void CcbCaptureFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbCaptureFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbCaptureFrameLayer::onExit()
{
	CCLayer::onExit();
    unschedule(schedule_selector(CcbCaptureFrameLayer::update));
}

void CcbCaptureFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbCaptureFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTimeL", CCLabelTTF*, this->m_pLabelTTFTimeL);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTimeR", CCLabelTTF*, this->m_pLabelTTFTimeR);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNameL", CCLabelTTF*, this->m_pLabelTTFNameL);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNameR", CCLabelTTF*, this->m_pLabelTTFNameR);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonL", CCControlButton*, this->m_pControlButtonL);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonR", CCControlButton*, this->m_pControlButtonR);

	return false;
}

bool CcbCaptureFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbCaptureFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbCaptureFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbCaptureFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLeft", CcbCaptureFrameLayer::onPressControlButtonLeft);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRight", CcbCaptureFrameLayer::onPressControlButtonRight);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbCaptureFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
//    m_pLabelTTFTimeL->setStrokeForLabelTTF(ccBLACK, 0.1);
//    m_pLabelTTFTimeR->setStrokeForLabelTTF(ccBLACK, 0.1);
//    m_pLabelTTFNameL->setStrokeForLabelTTF(ccBLACK, 0.1);
//    m_pLabelTTFNameR->setStrokeForLabelTTF(ccBLACK, 0.1);
    SetSlaveInfo();
   
}



void CcbCaptureFrameLayer::onPressControlButtonLeft(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CaptureCtrl::byCurFarmId = 0;
    if (m_bLSlaveEmpty) {
        CGameSession::SendCaptureList();
    } else {
        CGameSession::SendRobRewardClick(CaptureCtrl::byCurType, 0);
    }
}

void CcbCaptureFrameLayer::onPressControlButtonRight(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CaptureCtrl::byCurFarmId = 1;
    if (m_bRSlaveEmpty) {
        CGameSession::SendCaptureList();
    } else {
        CGameSession::SendRobRewardClick(CaptureCtrl::byCurType, 1);
    }
}

#pragma mark Private Method
void CcbCaptureFrameLayer::updateTime(float dt)
{
    //更新时间即可，是否可领奖利用通知机制}
    if (m_dwLLeftTime) {
        m_dwLLeftTime--;
        m_pLabelTTFTimeL->setString(getLeftTimeFromInt(m_dwLLeftTime)->getCString());
    }
    if (m_dwRLeftTime) {
        m_dwRLeftTime--;
        m_pLabelTTFTimeR->setString(getLeftTimeFromInt(m_dwRLeftTime)->getCString());
    }
}

void CcbCaptureFrameLayer::SetSlaveInfo()
{
    unschedule(schedule_selector(CcbCaptureFrameLayer::updateTime));
    
    CaptureCtrl::STC_MINE_INFO leftMine = CaptureCtrl::m_vecMine[0];
    CaptureCtrl::STC_MINE_INFO rightMine = CaptureCtrl::m_vecMine[1];
    
    m_dwLLeftTime = m_dwRLeftTime = 0;
    
    if (leftMine.dwSlaveId) {
        m_bLSlaveEmpty = false;
        m_pLabelTTFNameL->setString(leftMine.strName.c_str());

        m_pLabelTTFTimeL->setString(getLeftTimeFromInt(leftMine.dwLeftTime)->getCString());
        
        SequencePet* mc = SequencePet::create(leftMine.wPetLeaderId);
        mc->setAnchorPoint(ccp(0.5, 0));
        mc->setPosition(ccp(m_pControlButtonL->getPositionX(), m_pControlButtonL->getPositionY()+8));
        mc->runAction( CCRepeatForever::create( SequenceAction::create(mc, SEQ_ACT_STAND) ) );
        if (getChildByTag(100)) {
            getChildByTag(100)->removeFromParentAndCleanup(true);
        }
        addChild(mc, 100);
        if (leftMine.dwRewCnt <= 0) {
            m_pControlButtonL->setEnabled(false);
        }
        m_dwLLeftTime = leftMine.dwLeftTime;
    } else {
        m_pLabelTTFNameL->setString(GET_STR(Str_capture_loli));
        m_pLabelTTFTimeL->setString(GET_STR(Str_time_zero));
        m_bLSlaveEmpty = true;
    }
    
    
    if (rightMine.dwSlaveId) {
        m_bRSlaveEmpty = false;
        m_pLabelTTFNameR->setString(rightMine.strName.c_str());

        m_pLabelTTFTimeR->setString(getLeftTimeFromInt(rightMine.dwLeftTime)->getCString());
        
        SequencePet* mc = SequencePet::create(rightMine.wPetLeaderId);
        mc->setAnchorPoint(ccp(0.5, 0));
        mc->setPosition(ccp(m_pControlButtonR->getPositionX(), m_pControlButtonR->getPositionY()+8));
        mc->runAction( CCRepeatForever::create( SequenceAction::create(mc, SEQ_ACT_STAND) ) );
        if (getChildByTag(101)) {
            getChildByTag(101)->removeFromParentAndCleanup(true);
        }
        addChild(mc, 101);
        if (rightMine.dwRewCnt <= 0) {
            m_pControlButtonR->setEnabled(false);
        }
        m_dwRLeftTime = rightMine.dwLeftTime;
    } else {
        m_pLabelTTFNameR->setString(GET_STR(Str_capture_ol));
        m_pLabelTTFTimeR->setString(GET_STR(Str_time_zero));
        m_bRSlaveEmpty = true;
    }
    
    schedule(schedule_selector(CcbCaptureFrameLayer::updateTime), 1.0f);
}

#pragma mark ObserverMSG
void CcbCaptureFrameLayer::RefeashLayer()
{
    SetSlaveInfo();
}




