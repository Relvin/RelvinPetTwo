#include "StartGameScene.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "GameStateManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

StartGameScene::~StartGameScene()
{

}

CCScene* StartGameScene::scene()
{
	// scene() was called after init()
	CCScene* scene = CCScene::create();
    StartGameScene* pLayer = StartGameScene::create();
    scene->addChild(pLayer);
	return scene;
}

bool StartGameScene::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    CGameSession::Init();
    addChild(CcbManager::sharedManager()->LoadStartGameLayer(this));
	return true;
}

void StartGameScene::onEnter()
{
	CCLayer::onEnter();
}

void StartGameScene::onExit()
{
	CCLayer::onExit();
}




