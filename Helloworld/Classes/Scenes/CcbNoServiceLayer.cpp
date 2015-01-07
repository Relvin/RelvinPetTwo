#include "CcbNoServiceLayer.h"
//#include "CcbManager.h"
#include "LoginSystem.h"
#include "GlobalData.h"
#include "SystemMessage.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "UISupport.h"
#include "GameSession.h"
#include "StartGameLayer.h"
#include "Account.h"

#define REC_CNT 3

CcbNoServiceLayer::~CcbNoServiceLayer()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbNoServiceLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbNoServiceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbNoServiceLayer", CcbNoServiceLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/noservice.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbNoServiceLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbNoServiceLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    
    std::string strText;
    
    if (GlobalData::nReconnetCnt >= REC_CNT) {
        if (StartGameLayer::GetCurLayer()) {
            strText = GET_STR(Str_server_list_error_exit);
        } else {
            strText = GET_STR(Str_plz_back_to_login);
        }
    } else {
        if (StartGameLayer::GetCurLayer()) {
            strText = GET_STR(Str_get_server_list_error);
        } else {
            strText = GET_STR(Str_no_network);
        }
    }
    SystemMessage::showSystemMessage(0, this, strText.c_str(), this, true, 0, GET_STR(Str_warning), true);
    
#ifdef DEBUG
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* pForceClose = CCLabelTTF::create("求爷爷就不弹", "Arial", 18);
    CCMenuItemLabel* pForceItem = CCMenuItemLabel::create(pForceClose, this, menu_selector(CcbNoServiceLayer::forceClose));
    pForceItem->setAnchorPoint(ccp(0.5, 1));
    pForceItem->setPosition(ccp(winSize.width * 0.5, getTop(this)));
    CCMenu* pMenu = CCMenu::createWithItem(pForceItem);
    pMenu->setAnchorPoint(CCPointZero);
    pMenu->setPosition(CCPointZero);
    pMenu->setTouchPriority(kCCMenuHandlerPriority*5-1);
    addChild(pMenu, 5);
#endif
}

void CcbNoServiceLayer::onExit()
{
	CCLayer::onExit();
}

bool CcbNoServiceLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbNoServiceLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2*kCCMenuHandlerPriority, true);
}

void CcbNoServiceLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    if (GlobalData::nReconnetCnt >= REC_CNT) {
        if (StartGameLayer::GetCurLayer()) {
            exit(0);
        } else {
#if defined VERSION_D9||VERSION_91
            Account::shareInstance()->switchAccount();
#else
            CGameSession::BackToLogin();
#endif
            return;
        }
    }
    GlobalData::nReconnetCnt++;
    LoginSystem::Get()->ReConnect();
    removeFromParentAndCleanup(true);
}

void CcbNoServiceLayer::forceClose(CCObject *pObject)
{
    GlobalData::bCloseForce = true;
    removeFromParentAndCleanup(true);
}

