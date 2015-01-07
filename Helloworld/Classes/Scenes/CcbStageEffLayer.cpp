#include "CcbStageEffLayer.h"
//#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbStageEffLayer::~CcbStageEffLayer()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbStageEffLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbStageEffLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbStageEffLayer", CcbStageEffLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/missionframelight.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbStageEffLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbStageEffLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbStageEffLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbStageEffLayer::onExit()
{
	CCLayer::onExit();
}

void CcbStageEffLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

