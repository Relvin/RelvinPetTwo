#include "CcbChatTalkBoardLayer.h"
//#include "CcbManager.h"
#include "ReRichText.h"
#include "CcbPetIcon.h"
#include "ResourceDefine.h"
#include "GameSession.h"
#include "Role.h"
#include "CcbChatLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define R_Text_Tag 373

CcbChatTalkBoardLayer::~CcbChatTalkBoardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerHead);
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteTalkBoard);
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteVipTalkBoard);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFWords);
    CC_SAFE_RELEASE_NULL(m_pControlButtonHead);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbChatTalkBoardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbChatTalkBoardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbChatTalkBoardLayer", CcbChatTalkBoardLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/pet_icon.ccb]", [ccb/pet_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChatTalkBoardLayer.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbChatTalkBoardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbChatTalkBoardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbChatTalkBoardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbChatTalkBoardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbChatTalkBoardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbChatTalkBoardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHead", CcbPetIcon*, this->m_pLayerHead);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteTalkBoard", CCScale9Sprite*, this->m_pScale9SpriteTalkBoard);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteVipTalkBoard", CCScale9Sprite*, this->m_pScale9SpriteVipTalkBoard);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWords", CCLabelTTF*, this->m_pLabelTTFWords);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonHead", CCControlButton*, this->m_pControlButtonHead);
	return false;
}

bool CcbChatTalkBoardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbChatTalkBoardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChatTalkBoardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChatTalkBoardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonHead", CcbChatTalkBoardLayer::onPressControlButtonHead);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbChatTalkBoardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pControlButtonHead->setTouchPriority(kCCMenuHandlerPriority - 21);
}


void CcbChatTalkBoardLayer::setNodeData(const ChatDataMgr::STC_CHAT_MSG &chatMsg) {
    if (chatMsg.wVipLv > 0) {
        m_pScale9SpriteTalkBoard->setVisible(false);
        m_pScale9SpriteVipTalkBoard->setVisible(true);
        m_pLayerHead->showVip();
    } else {
        m_pScale9SpriteTalkBoard->setVisible(true);
        m_pScale9SpriteVipTalkBoard->setVisible(false);
        m_pLayerHead->hideVip();
    }
    
    m_pControlButtonHead->setTag(chatMsg.dwAccountId);
    
    m_pLayerHead->setPetId(chatMsg.wLeaderPetId);
    m_pLayerHead->setName(chatMsg.strAccountName.c_str());
    
    if (getChildByTag(R_Text_Tag)) {
        removeChildByTag(R_Text_Tag);
    }
    
    ReRichText* richText = ReRichText::create();
    
    richText->addChatMsg(
                         ccc4(255, 0, 0, 255),
                         NULL,
                         ccc4(0xF7, 0xE4, 0x02, 255),
                         NULL,
                         chatMsg.dwAccountId,
                         ccc4(255, 255, 255, 255),
                         chatMsg.strContent.c_str(),
                         richTextFontName(FONT_HEL, FONT_HEL, FONT_HEL),
                         richTextFontSize(12,12,10)
                         );
    
    CCSize _textSize = m_pLabelTTFWords->getContentSize();
    CCPoint _textPos = m_pLabelTTFWords->getPosition();
    
    richText->setSize(_textSize);
    richText->ignoreContentAdaptWithSize(false);
    
    m_pLabelTTFWords->removeFromParent();
    addChild(richText, 1, R_Text_Tag);
    
    richText->setAnchorPoint(ccp(0.5, 1));
    richText->setPosition(_textPos);
}

void CcbChatTalkBoardLayer::onPressControlButtonHead(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    uint32 dwTag = dynamic_cast<CCControlButton*>(pSender)->getTag();
    if (dwTag == CGameSession::GetRole()->GetdwAccountId()) {
        return;
    } else {
        if (CcbChatLayer::getInstance()) {
            CcbChatLayer::getInstance()->touchToPrivate(dwTag);
        }
    }
}




