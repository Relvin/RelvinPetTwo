#include "CcbFriendMailLayer.h"
#include "GameSession.h"
#include "BackCtrl.h"
#include "SystemMessage.h"
#include "ResourceDefine.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "FriendUnitDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFriendMailLayer::~CcbFriendMailLayer()
{
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteTitle);
    CC_SAFE_RELEASE_NULL(m_pNodeContent);
    CC_SAFE_RELEASE_NULL(m_pControlButtonSend);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFId);
    CC_SAFE_RELEASE_NULL(m_pLayerContent);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFriendMailLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFriendMailLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFriendMailLayer", CcbFriendMailLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_mail.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFriendMailLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbFriendMailLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbFriendMailLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

    uint32 dwUserId = FriendUnitDataMgr::Get()->mailTarget();
    CCString* strId = CCString::createWithFormat("%s(%d)", FriendUnitDataMgr::Get()->mailTargetName().c_str(), dwUserId);
    m_pLabelTTFId->setString(strId->getCString());
    
    CCPoint orgPos = m_pLayerContent->getPosition();
    CCSize orgSize = m_pLayerContent->getContentSize();
    orgPos = ccpSub(orgPos, ccp(orgSize.width*0.5, orgSize.height*0.5));
    
    CCSize titleSize, contentSize;
    CCPoint titlePos, contentPos;
    
    titleSize = m_pScale9SpriteTitle->getContentSize();
    contentSize = m_pNodeContent->getContentSize();
    titlePos = m_pScale9SpriteTitle->getPosition();
    titlePos = ccpAdd(titlePos, orgPos);
    contentPos = m_pNodeContent->getPosition();
    contentPos = ccpAdd(contentPos, orgPos);
    
    m_pScale9SpriteTitle->removeFromParent();
    
    //Title
    m_pEditTitle = CCEditBox::create(titleSize, m_pScale9SpriteTitle);
    m_pEditTitle->setAnchorPoint(CCPointZero);
    m_pEditTitle->setPosition(titlePos);
    
    m_pEditTitle->setFont(FONT_HEL, 12);
    m_pEditTitle->setFontColor(ccWHITE);
    m_pEditTitle->setPlaceHolder("Title");
    m_pEditTitle->setMaxLength(16);
    m_pEditTitle->setDelegate(this);
    addChild(m_pEditTitle);
    
    //Content
    m_pTTFContent = CCTextFieldTTF::textFieldWithPlaceHolder("Content", contentSize, kCCTextAlignmentLeft, FONT_HEL, 12);
    m_pTTFContent->setAnchorPoint(CCPointZero);
    m_pTTFContent->setPosition(contentPos);
    m_pTTFContent->setColor(ccWHITE);
    m_pTTAContent = CCTextFieldAuto::create(m_pTTFContent);
    
    m_pTTFContent->setDelegate(m_pTTAContent);
    addChild(m_pTTAContent, 1);
}

void CcbFriendMailLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendMailLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendMailLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteTitle", CCScale9Sprite*, this->m_pScale9SpriteTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeContent", CCNode*, this->m_pNodeContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSend", CCControlButton*, this->m_pControlButtonSend);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFId", CCLabelTTF*, this->m_pLabelTTFId);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerContent", CCLayer*, this->m_pLayerContent);
	return false;
}

bool CcbFriendMailLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFriendMailLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFriendMailLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFriendMailLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSend", CcbFriendMailLayer::onPressControlButtonSend);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFriendMailLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbFriendMailLayer::onPressControlButtonSend(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_strTile = m_pEditTitle->getText();

    m_strContent = m_pTTAContent->getTextField()->getString();
    
    if (m_strTile == "" || m_strTile.empty()) {
        SystemMessage::showSystemMessage(0, NULL, GET_STR(Str_email_title_cannot_empty));
        return;
    }
    if (m_strContent == "" || m_strContent.empty()) {
        SystemMessage::showSystemMessage(0, NULL, GET_STR(Str_eamil_cannot_empty));
        return;
    }
    
    CGameSession::SendFriendMsg(FriendUnitDataMgr::Get()->mailTarget(), m_strTile, m_strContent);
	SystemMessage::showSystemMessage(0, this, GET_STR(Str_email_send_suc), this, false, 1);
}

void CcbFriendMailLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    BackCtrl::BacktoUpperScene();
}

#pragma mark EditBox
void CcbFriendMailLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
}

void CcbFriendMailLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
}

void CcbFriendMailLayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
}

void CcbFriendMailLayer::editBoxReturn(CCEditBox* editBox)
{
}

#pragma mark ccTouchDelegate
void CcbFriendMailLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
}

bool CcbFriendMailLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_posBegin = pTouch->getLocationInView();
    m_posBegin = CCDirector::sharedDirector()->convertToGL(m_posBegin);
    return false;
}

#pragma mark IMEDelegate
static CCRect getRect(CCNode * pNode)
{
	CCSize contentSize = pNode->getContentSize();
	CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
	return CCRectApplyAffineTransform(rect, pNode->nodeToWorldTransform());
}

void CcbFriendMailLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo &info)
{
    // CCLOG("CCEditBox::keyboardWillShow");
    CCRect rectTracked = getRect(m_pTTFContent);
	// some adjustment for margin between the keyboard and the edit box.
//	rectTracked.origin.y -= 4;
    
    // if the keyboard area doesn't intersect with the tracking node area, nothing needs to be done.
    if (!rectTracked.intersectsRect(info.end) || !rectTracked.containsPoint(m_posBegin))
    {
        CCLOG("needn't to adjust view layout.");
        return;
    }
    float m_fAdjustHeight;
    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    m_fAdjustHeight = info.end.getMaxY() - rectTracked.getMinY();
    this->setPosition(ccp(0, m_fAdjustHeight));
}

void CcbFriendMailLayer::keyboardWillHide(CCIMEKeyboardNotificationInfo &info)
{
    setPosition(ccp(0, 0));
}




