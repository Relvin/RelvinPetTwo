#include "CcbBattleAnimationLayer.h"
//#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbBattleAnimationLayer::~CcbBattleAnimationLayer()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBattleAnimationLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBattleAnimationLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBattleAnimationLayer", CcbBattleAnimationLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_ctrl_ani.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbBattleAnimationLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBattleAnimationLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbBattleAnimationLayer::onExit()
{
	CCLayer::onExit();
}

