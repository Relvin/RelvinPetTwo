//
//  SystemMessage.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-26.}
//
//

#include "SystemMessage.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "GuideBtnPos.h"
#include "GuideData.h"
#include "ReRichText.h"
#include "UISupport.h"

std::vector<SystemMessage::STC_MSG> SystemMessage::m_vecPending;

#pragma mark CCB Methods
bool SystemMessage::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void SystemMessage::onEnter()
{
	CCLayer::onEnter();
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
}

void SystemMessage::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
//    this->runAction(
//                    CCSequence::create(
//                                       CCDelayTime::create(0.4f),
//                                       CCCallFunc::create(this, callfunc_selector(SystemMessage::addGuideLayer)),
//                                       NULL
//                                       )
//                    );
}

void SystemMessage::addGuideLayer() {

}

void SystemMessage::onExit()
{
	CCLayer::onExit();
}

void SystemMessage::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool SystemMessage::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOk", CCControlButton*, this->m_pControlButtonOk);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFContent", CCLabelTTF*, this->m_pLabelTTFContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerColor", CCLayer*, this->m_pLayerColor);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTitle", CCLabelTTF*, this->m_pLabelTTFTitle);
	return false;
}

bool SystemMessage::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{

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
SEL_CallFuncN SystemMessage::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler SystemMessage::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_CCControlHandler SystemMessage::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOk", SystemMessage::onPressControlButtonOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", SystemMessage::onPressControlButtonCancel);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", SystemMessage::onPressControlButtonClose);
	return NULL;
}

// Inhert CCNodeLoaderListener
void SystemMessage::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pControlButtonOk->setTouchPriority(kCCMenuHandlerPriority*5-1);
    m_pControlButtonCancel->setTouchPriority(kCCMenuHandlerPriority*5-1);
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority*5-1);
    
    m_pLabelTTFTitle->noStroke();
    m_pLabelTTFContent->noStroke();
    m_pLabelTTFContent->setString("");
    
    m_pRichText = ReRichText::create();
    m_pRichText->setFontName(m_pLabelTTFContent->getFontName());
    m_pRichText->setFontSize(m_pLabelTTFContent->getFontSize());
    m_pRichText->setSize(m_pLabelTTFContent->getDimensions());
    m_pRichText->ignoreContentAdaptWithSize(false);
    m_pLabelTTFContent->getParent()->addChild(m_pRichText);
    m_pRichText->ignoreAnchorPointForPosition(false);
    m_pRichText->setAnchorPoint(ccp(0.5f, 1.0f));
    m_pRichText->setPosition(m_pLabelTTFContent->getPosition());
}

void SystemMessage::onPressControlButtonOk(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	if (delegate) {
		delegate->systemMessageOKTapped(this);
	}
//    if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_SYS_GUIDE_7_MYSTERY) {
//        GuideData::GetInstance()->onlyRmGuideLayer();
//    }
    
    removeFromParentAndCleanup(false);
}

void SystemMessage::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
	if (delegate) {
		delegate->systemMessageCancelTapped(this);
	}
	removeFromParentAndCleanup(false);
}

void SystemMessage::onPressControlButtonClose(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    removeFromParent();
}

#pragma mark Public Method
void SystemMessage::showSystemMessage(int type, CCNode *parent, const char *text, SystemMessageProtocol *_delegate, bool bForceShow, int _param, const char *title, bool bHideClose)
{
	if (!CheckCanDo() && !bForceShow)
	{
		STC_MSG stcMsg;
		stcMsg.strMsg = text;
        stcMsg.strTitle = title;
		m_vecPending.push_back(stcMsg);
		return;
	}
	SystemMessage *sys = dynamic_cast<SystemMessage*>(CcbManager::sharedManager()->LoadSystemMessage());
	sys->showMessage(type, parent, text, _delegate, _param, title, bHideClose);
}

void SystemMessage::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*5, true);
}

bool SystemMessage::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

#pragma mark Private Method

bool SystemMessage::CheckCanDo()
{
    return true;
}

void SystemMessage::ProcessPending(CCNode *pNode)
{
	for(int i = 0; i < (int)(m_vecPending.size()); ++i)
	{
		SystemMessage::showSystemMessage(0, pNode, m_vecPending[i].strMsg.c_str());
	}
	m_vecPending.clear();
}

void SystemMessage::setDelegate(SystemMessageProtocol *_delegate)
{
	delegate = _delegate;
}

void SystemMessage::showMessage(int type, CCNode *parent, const char *text, SystemMessageProtocol *_delegate, int _param, const char* title, bool bHideClose)
{
	param = _param;
	
	if (!parent) {
		CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
		if (scene->getChildByTag(1000)) {
            return;
		}
		scene->addChild(this, 1000, 1000);
	}
	else {
		if (parent->getChildByTag(1000)) {
            return;
		}
		parent->addChild(this, 1000, 1000);
        

        CCPoint m_posParent = parent->getPosition();
        if (parent->getParent()) {
            m_posParent.x += parent->getParent()->getPositionX();
        }
        CCLOG("[%f, %f]", m_posParent.x, m_posParent.y);
        
		setPosition(ccp(getPosition().x - m_posParent.x, getPosition().y - m_posParent.y));
	}
	
//	m_pLabelTTFContent->setString(text);
    m_pRichText->setString(text);
    if (title) {
        m_pLabelTTFTitle->setString(title);
    }

    mAnimationManager->runAnimationsForSequenceNamed("show");
    
	delegate = _delegate;
    
    // ccb制作者使用的是320.0固定宽度}
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float xPos = 320.0f * 0.5f;
    if (type == 0) {
        m_pControlButtonCancel->setVisible(false);
	}
	if (type == 1) {
        m_pControlButtonCancel->setEnabled(true);
        xPos = 320.0f * 0.65f;
	}
    setCenterX(m_pControlButtonOk, xPos);
    
    if (bHideClose) {
        m_pControlButtonClose->setVisible(false);
    }
}

void SystemMessage::UnInit()
{
	m_vecPending.clear();
}

