#include "CcbLeftArrow.h"
//#include "CcbManager.h"


USING_NS_CC;
USING_NS_CC_EXT;

CcbLeftArrow::~CcbLeftArrow()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbLeftArrow( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbLeftArrow( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader("CcbLeftArrow", CcbLeftArrowLoader::loader());
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arrowleft.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbLeftArrow::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbLeftArrow::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbLeftArrow::onExit()
{
	CCLayer::onExit();
}










