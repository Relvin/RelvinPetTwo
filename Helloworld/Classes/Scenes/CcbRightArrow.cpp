#include "CcbRightArrow.h"
//#include "CcbManager.h"


USING_NS_CC;
USING_NS_CC_EXT;

CcbRightArrow::~CcbRightArrow()
{

}


bool CcbRightArrow::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbRightArrow::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbRightArrow::onExit()
{
	CCLayer::onExit();
}




