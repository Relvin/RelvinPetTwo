#ifndef _CCTEXTFIELDAUTO_H
#define _CCTEXTFIELDAUTO_H

#include "cocos2d.h"
USING_NS_CC;


//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
	KeyboardNotificationLayer();

	virtual std::string subtitle() = 0;
	virtual void onClickTrackNode(bool bClicked) = 0;

	virtual void registerWithTouchDispatcher();
	virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);
	virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info);
	// CCLayer
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void setTouchPriority(int _touchPriority)
	{
		touchPriority = _touchPriority;
	}
protected:
	int touchPriority;
	CCNode * m_pTrackNode;
	CCPoint  m_beginPos;
};

class HelloWorld;

//////////////////////////////////////////////////////////////////////////
// CCTextFieldAuto for test TextFieldTTF default behavior.
//////////////////////////////////////////////////////////////////////////
class CKeyboardDelegate;

class CCTextFieldAuto : public KeyboardNotificationLayer, public CCTextFieldDelegate
{
public:
	bool initWithTextField(CCTextFieldTTF* textField) {
		if( !textField ) return false;
//		m_pLoginScene = NULL;
		m_pKeyboardDelegate = NULL;
		if( !KeyboardNotificationLayer::init() ) return false;
		m_textField = textField;
		m_pTrackNode = textField;
		this->addChild(textField);
		this->setContentSize(textField->getContentSize());
		setTouchEnabled(true);
		return true;
	}
	static CCTextFieldAuto * create(CCTextFieldTTF* textField);

	CCTextFieldTTF* getTextField() { return m_textField; }
	const CCTextFieldTTF* getTextField() const { return m_textField; }
	// KeyboardNotificationLayer
	virtual std::string subtitle();
	virtual void onClickTrackNode(bool bClicked);

	virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);
	virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info);

	void SetLoginScene(HelloWorld *pLoginScene);

	// CCTextFieldDelegate
	virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * pSender);
	virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);

	virtual void onEnter();
	virtual void onExit();
	
	void SetKeyboardDelegate(CKeyboardDelegate *pKeyboardDelegate) {m_pKeyboardDelegate = pKeyboardDelegate;};

	CKeyboardDelegate * GetKeyboardDelegate() {return m_pKeyboardDelegate;};
private:
	//cocos2d::CCPoint m_beginPos;
	CCTextFieldTTF* m_textField; //weak

//	HelloWorld *m_pLoginScene;
	CKeyboardDelegate *m_pKeyboardDelegate;
	CCAction *          m_pTextFieldAction;
	bool                m_bAction;
	int                 m_nCharLimit;       // the textfield max char limit
};
#endif