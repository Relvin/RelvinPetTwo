#include "CcbExchangeCodeLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "FlyTextLayer.h"
#include "MusicCtrl.h"

CcbExchangeCodeLayer::~CcbExchangeCodeLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonExchangeCode);
    CC_SAFE_RELEASE_NULL(m_pSpriteEditParent);
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteEnterCode);
    CC_SAFE_RELEASE_NULL(m_pEditBoxEnterCode);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbExchangeCodeLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbExchangeCodeLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbExchangeCodeLayer", CcbExchangeCodeLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/exchange_code.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbExchangeCodeLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbExchangeCodeLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
}

void CcbExchangeCodeLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbExchangeCodeLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
}

void CcbExchangeCodeLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbExchangeCodeLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExchangeCode", CCControlButton*, this->m_pControlButtonExchangeCode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEditParent", CCSprite*, this->m_pSpriteEditParent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteEnterCode", CCScale9Sprite*, this->m_pScale9SpriteEnterCode);
	return false;
}

bool CcbExchangeCodeLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbExchangeCodeLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbExchangeCodeLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbExchangeCodeLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExchangeCode", CcbExchangeCodeLayer::onPressControlButtonExchangeCode);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbExchangeCodeLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CCSize EditBoxSize = m_pScale9SpriteEnterCode->getOriginalSize();
    CCPoint EditBoxPos = m_pScale9SpriteEnterCode->getPosition();
    m_pScale9SpriteEnterCode->removeFromParent();
    m_pEditBoxEnterCode = CCEditBox::create(EditBoxSize, m_pScale9SpriteEnterCode);
    m_pEditBoxEnterCode->setInputMode(kEditBoxInputModeNumeric);
    m_pEditBoxEnterCode->setPosition(EditBoxPos);
    m_pEditBoxEnterCode->setMaxLength(32);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pEditBoxEnterCode->setFontName("Paint Boy");
#else
	m_pEditBoxEnterCode->setFontName("fonts/Paint Boy.ttf");
#endif
    
    m_pEditBoxEnterCode->setFontSize(14);
    m_pEditBoxEnterCode->setPlaceHolder(GET_STR(Str_input_exchange));
    m_pEditBoxEnterCode->setText("");

    m_pEditBoxEnterCode->retain();
    m_pSpriteEditParent->addChild(m_pEditBoxEnterCode);
    m_pEditBoxEnterCode->setDelegate(this);

}


void CcbExchangeCodeLayer::onPressControlButtonExchangeCode(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	// TODO:
    char szTempNum[32] = "";
    strncpy(szTempNum, m_pEditBoxEnterCode->getText(), 32);

    if (strcmp(szTempNum, "") == 0)
    {
//        CCMessageBox("qqqqqqqqqqqqq请输入有效的兑换码", "提示");
        FlyTextLayer::showTips(GET_STR(Str_input_right_exchange));
        return;
    }
    
    CGameSession::SendInviteCode(szTempNum);
    
    //成功返回调清空}
    m_pEditBoxEnterCode->setText("");
}

void CcbExchangeCodeLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox * editbox)
{
    //
}

void CcbExchangeCodeLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox * editbox)
{
    //
}

void CcbExchangeCodeLayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    //
}

void CcbExchangeCodeLayer::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
    
}

void CcbExchangeCodeLayer::RefeashLayer()
{
    //m_pEditBoxEnterCode->setText("");
}


