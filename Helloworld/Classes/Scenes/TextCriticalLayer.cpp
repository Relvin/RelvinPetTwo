#include "TextCriticalLayer.h"
#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

TextCriticalLayer::~TextCriticalLayer()
{
    CCLog("delloc Text Critical");
}

bool TextCriticalLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    this->setAnchorPoint(ccp(0.5, 0));
    this->setPosition(ccp(0, 0));
	return true;
}

void TextCriticalLayer::onEnter()
{
	CCLayer::onEnter();
}

void TextCriticalLayer::onExit()
{
	CCLayer::onExit();
}


