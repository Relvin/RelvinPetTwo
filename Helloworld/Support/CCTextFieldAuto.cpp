#include "CCTextFieldAuto.h"
#include "UIMacro.h"
#include "HelloWorldScene.h"
#include "KeyboardDelegate.h"
#include "UISupport.h"
static CCRect getRect(CCNode * pNode)
{
	CCRect rc;
	rc.origin = pNode->getPosition();
	rc.size = pNode->getContentSize();
	rc.origin.x -= rc.size.width / 2;
	rc.origin.y -= rc.size.height / 2;
	return rc;
}

//////////////////////////////////////////////////////////////////////////
// implement KeyboardNotificationLayer
//////////////////////////////////////////////////////////////////////////

KeyboardNotificationLayer::KeyboardNotificationLayer()
: m_pTrackNode(0)
{
	setTouchEnabled(true);
	touchPriority = 0;
}

void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, touchPriority, false);
}

void KeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
//	CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
//		info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);

	if (! m_pTrackNode)
	{
		return;
	}

	CCRect rectTracked = getRect(m_pTrackNode);
//	CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
//		rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);

	// if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
	{
		return;
	}
    // [2013-12-25] Juniechu added.只需要继承IMEDelegate即可，整个页面setPostion(ccp(0,100));上移即可，不需要移动输入框的位置}
	return;
	// assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = info.end.getMaxY() - info.end.getMinY();
//	CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);

	// move all the children node of KeyboardNotificationLayer
	CCArray * children = getChildren();
	CCNode * node = 0;
	int count = children->count();
	CCPoint pos;
	for (int i = 0; i < count; ++i)
	{
		node = (CCNode*)children->objectAtIndex(i);
		pos = node->getPosition();
		pos.y += adjustVert;
		node->setPosition(pos);
	}
}
void KeyboardNotificationLayer::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
{
	
}
// CCLayer function

bool KeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!m_bVisible) {
		return false;
	}
	m_beginPos = pTouch->getLocationInView();
	m_beginPos = CCDirector::sharedDirector()->convertToGL(m_beginPos);
	return true;
}

void KeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (! m_pTrackNode)
	{
		return;
	}

	CCPoint endPos = pTouch->getLocationInView();
	endPos = CCDirector::sharedDirector()->convertToGL(endPos);

	float delta = 5.0f;
	if (::abs(endPos.x - m_beginPos.x) > delta
		|| ::abs(endPos.y - m_beginPos.y) > delta)
	{
		// not click
		m_beginPos.x = m_beginPos.y = -1;
		return;
	}

	// decide the trackNode is clicked.
	CCRect rect;
	CCPoint point = convertTouchToNodeSpaceAR(pTouch);
//	CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);

	rect = getRect(m_pTrackNode);
//	CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
//		rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

	rect = nodeRectInParentSpace(m_pTrackNode);
	point = convertTouchToNodeSpace(pTouch);
    this->onClickTrackNode(rect.containsPoint(point));

	// decide the TextField is clicked.

}


CCTextFieldAuto * CCTextFieldAuto::create(CCTextFieldTTF* textField)
{
	CCTextFieldAuto *pRet = new CCTextFieldAuto();
	if (pRet && pRet->initWithTextField(textField))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

// KeyboardNotificationLayer
std::string CCTextFieldAuto::subtitle()
{
	return "";
}
void CCTextFieldAuto::onClickTrackNode(bool bClicked)
{
	CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
	if (bClicked)
	{
		// TextFieldTTFTest be clicked
//		CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF attachWithIME");
		pTextField->attachWithIME();
	}
	else
	{
		// TextFieldTTFTest not be clicked
//		CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF detachWithIME");
		pTextField->detachWithIME();
	}
}

void CCTextFieldAuto::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
	KeyboardNotificationLayer::keyboardWillShow(info);

//	if (m_pLoginScene)
//	{
//		m_pLoginScene->keyboardWillShow();
//	}
	if (m_pKeyboardDelegate)
		m_pKeyboardDelegate->keyboardWillShow(this);//
}
void CCTextFieldAuto::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
{
	KeyboardNotificationLayer::keyboardWillHide(info);
//	if (m_pLoginScene)
//	{
//		m_pLoginScene->keyboardWillHide();
//	}
	if (m_pKeyboardDelegate)
		m_pKeyboardDelegate->keyboardWillHide(this);
}

//void CCTextFieldAuto::SetLoginScene(HelloWorld *pLoginScene)
//{
//	m_pLoginScene = pLoginScene;
//}

// CCTextFieldDelegate protocol
bool CCTextFieldAuto::onTextFieldAttachWithIME(CCTextFieldTTF * pSender)
{
	if (! m_bAction)
	{
		m_textField->runAction(m_pTextFieldAction);
		m_bAction = true;
	}
	return false;
}

bool CCTextFieldAuto::onTextFieldDetachWithIME(CCTextFieldTTF * pSender)
{
	if (m_bAction)
	{
		m_textField->stopAction(m_pTextFieldAction);
		m_textField->setOpacity(255);
		m_bAction = false;
	}
	return false;
}

void CCTextFieldAuto::onEnter()
{
	KeyboardNotificationLayer::onEnter();

	m_nCharLimit = 12;

    m_pTextFieldAction = CCRepeatForever::create(
                                                 CCSequence::create(
                                                                    CCFadeOut::create(0.25),
                                                                    CCFadeIn::create(0.25),
                                                                    0
                                                                    ));
	m_pTextFieldAction->retain();
	m_bAction = false;
}
void CCTextFieldAuto::onExit()
{
	KeyboardNotificationLayer::onExit();
//    m_pTextFieldAction->retain();
	m_pTextFieldAction->release();
}
