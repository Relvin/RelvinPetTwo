#include "CcbGMLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "UISupport.h"

USING_NS_CC;
USING_NS_CC_EXT;


CCScene* GMScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
    
	// 'layer' is an autorelease object
	GMScene *layer = GMScene::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}
GMScene::~GMScene()
{
	
}
bool GMScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    addChild(CcbManager::sharedManager()->LoadCcbGMLayer(this));
    return true;
}



CcbGMLayer::~CcbGMLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonUser);
	CC_SAFE_RELEASE_NULL(m_pControlButtonPet);
	CC_SAFE_RELEASE_NULL(m_pControlButtonItem);
	CC_SAFE_RELEASE_NULL(m_pControlButtonVip);
	CC_SAFE_RELEASE_NULL(m_pLayerBg);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
	CC_SAFE_RELEASE_NULL(m_pControlButtonSend);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGem);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEmblem);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbGMLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbGMLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGMLayer", CcbGMLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gm.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbGMLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbGMLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbGMLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbGMLayer::onExit()
{
	CCLayer::onExit();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
    if (pGlView)
    {
        pGlView->setIMEKeyboardState(false);
    }
#endif
}

void CcbGMLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbGMLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonUser", CCControlButton*, this->m_pControlButtonUser);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPet", CCControlButton*, this->m_pControlButtonPet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonItem", CCControlButton*, this->m_pControlButtonItem);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonVip", CCControlButton*, this->m_pControlButtonVip);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBg", CCLayer*, this->m_pLayerBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSend", CCControlButton*, this->m_pControlButtonSend);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGem", CCControlButton*, this->m_pControlButtonGem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEmblem", CCControlButton*, this->m_pControlButtonEmblem);

	return false;
}

bool CcbGMLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbGMLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbGMLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbGMLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUser", CcbGMLayer::onPressControlButtonUser);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonPet", CcbGMLayer::onPressControlButtonPet);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonItem", CcbGMLayer::onPressControlButtonItem);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonVip", CcbGMLayer::onPressControlButtonVip);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbGMLayer::onPressControlButtonBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSend", CcbGMLayer::onPressControlButtonSend);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGem", CcbGMLayer::onPressControlButtonGem);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEmblem", CcbGMLayer::onPressControlButtonEmblem);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGMLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_ItemLayer = NULL;
    m_UserLayer = NULL;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCTextFieldTTF* pInfo = CCTextFieldTTF::textFieldWithPlaceHolder("Gm Cmd","Arial",24);
	pInfo->setColor( ccWHITE );
	pInfo->setPosition(ccp(size.width/2,size.height - 21));
	m_pTextFieldAutoInfo =  CCTextFieldAuto::create(pInfo);

	addChild(m_pTextFieldAutoInfo,10);
}



void CcbGMLayer::onPressControlButtonUser(CCObject* pSender, CCControlEvent event)
{
    loadUser();
}

void CcbGMLayer::onPressControlButtonPet(CCObject* pSender, CCControlEvent event)
{
    loadItem(E_GM_ITEM_PET);
}

void CcbGMLayer::onPressControlButtonItem(CCObject* pSender, CCControlEvent event)
{
    loadItem(E_GM_ITEM_ITEM);
}

void CcbGMLayer::onPressControlButtonVip(CCObject* pSender, CCControlEvent event)
{
    loadItem(E_GM_ITEM_EQUIP);
}

void CcbGMLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    CCDirector::sharedDirector()->popScene();
}

void CcbGMLayer::onPressControlButtonSend(CCObject* pSender, CCControlEvent event)
{
    onSave();
}

void CcbGMLayer::onPressControlButtonGem(CCObject* pSender, CCControlEvent event)
{
    loadItem(E_GM_ITEM_RUNE);
}

void CcbGMLayer::onPressControlButtonEmblem(CCObject* pSender, CCControlEvent event)
{
    loadItem(E_GM_ITEM_EMBLEM);
}

void CcbGMLayer::loadData()
{
    loadUser();
}

void CcbGMLayer::loadUser()
{
    if (!m_UserLayer) {
        m_UserLayer = dynamic_cast<CcbGmUserLayer*>(CcbManager::sharedManager()->LoadCcbGmUserLayer(this));
        m_UserLayer->setPosition(CCPointZero);
        m_UserLayer->setAnchorPoint(CCPointZero);
        m_pLayerBg->addChild(m_UserLayer);
    }
    m_UserLayer->setVisible(true);
    if (m_ItemLayer) {
        m_ItemLayer->setVisible(false);
    }
}

void CcbGMLayer::loadItem(uint8 type)
{
    if (!m_ItemLayer) {
        m_ItemLayer = dynamic_cast<CcbGmItemLayer*>(CcbManager::sharedManager()->LoadCcbGmItemLayer(this));
        m_ItemLayer->setPosition(CCPointZero);
        m_ItemLayer->setAnchorPoint(CCPointZero);
        m_pLayerBg->addChild(m_ItemLayer);
        
    }
    m_ItemLayer->setVisible(true);
    if (m_UserLayer) {
        m_UserLayer->setVisible(false);
    }
    m_ItemLayer->setType(type);
}

void CcbGMLayer::onSave()
{
    CCString *str = NULL;
    if (m_pTextFieldAutoInfo->getTextField()->getString() != NULL && m_pTextFieldAutoInfo->getTextField()->getString() [0] != '\0') {
        CGameSession::SendGM(m_pTextFieldAutoInfo->getTextField()->getString());
        return;
    }
    
    if (m_UserLayer->isVisible()) {
        str = m_UserLayer->getGmString();
    }
    else if (m_ItemLayer->isVisible())
    {
        str = m_ItemLayer->getGmString();
    }
    if (str) {
        CGameSession::SendGM(str->getCString());
    }
        
}
