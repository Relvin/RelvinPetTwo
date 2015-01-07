#include "MainBottomLayer.h"

USING_NS_CC;

MainBottomLayer::~MainBottomLayer()
{
    
}

bool MainBottomLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	return true;
}

void MainBottomLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void MainBottomLayer::onExit()
{
	CCLayer::onExit();
}

void MainBottomLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void MainBottomLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}


