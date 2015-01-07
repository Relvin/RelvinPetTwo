#include "CcbFindFriendLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "Role.h"
#include "PetLoadingLayer.h"
#include "FlyTextLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFindFriendLayer::~CcbFindFriendLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFWord);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMyId);
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteInput);
	CC_SAFE_RELEASE_NULL(m_pControlButtonFind);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFindFriendLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFindFriendLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFindFriendLayer", CcbFindFriendLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/find_friend.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFindFriendLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFindFriendLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbFindFriendLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFindFriendLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFindFriendLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFindFriendLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWord", CCLabelTTF*, this->m_pLabelTTFWord);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMyId", CCLabelTTF*, this->m_pLabelTTFMyId);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteInput", CCScale9Sprite*, this->m_pScale9SpriteInput);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFind", CCControlButton*, this->m_pControlButtonFind);

	return false;
}

bool CcbFindFriendLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbFindFriendLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFindFriendLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFindFriendLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFind", CcbFindFriendLayer::onPressControlButtonFind);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFindFriendLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pLabelTTFWord->noStroke();
    CCString* pString = CCString::createWithFormat("%d", CGameSession::GetRole()->GetdwAccountId());
    m_pLabelTTFMyId->setString(pString->getCString());
    m_pLabelTTFMyId->noStroke();
    
    CCSize sizeInput = m_pScale9SpriteInput->getContentSize();
    CCPoint pointInput = m_pScale9SpriteInput->getPosition();
    
    m_pScale9SpriteInput->removeFromParent();
    
    m_pEditBoxInput = CCEditBox::create(sizeInput, m_pScale9SpriteInput);
    m_pEditBoxInput->setAnchorPoint(ccp(0.5, 0.5));
    m_pEditBoxInput->setPosition(pointInput);
    
    m_pEditBoxInput->setFontName(T_Font);
    m_pEditBoxInput->setFontSize(14.0f);
    m_pEditBoxInput->setPlaceHolder("请输入查询账号");
    m_pEditBoxInput->setDelegate(this);
    m_pEditBoxInput->setMaxLength(10);
    m_pEditBoxInput->setInputMode(kEditBoxInputModeNumeric);
    
    addChild(m_pEditBoxInput, 1);
}

void CcbFindFriendLayer::onPressControlButtonFind(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_pEditBoxInput->getText() == NULL || strlen(m_pEditBoxInput->getText()) == 0) {
        FlyTextLayer::showTips("请输入需要查询的账号");
        return;
    }
    
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    uint32 dwUserId = atoi(m_pEditBoxInput->getText());
    CGameSession::SendReqFindFriend(dwUserId);
}

#pragma mark -- EditBox Delegate --
void CcbFindFriendLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox) {
    
}

void CcbFindFriendLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox) {
    
}

void CcbFindFriendLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, const std::string &text) {
    
}

void CcbFindFriendLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox) {
    
}





