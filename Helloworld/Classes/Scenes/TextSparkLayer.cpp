#include "TextSparkLayer.h"
#include "CcbManager.h"


USING_NS_CC;
USING_NS_CC_EXT;

TextSparkLayer::~TextSparkLayer()
{
//    CC_SAFE_RELEASE(mAnimationManager);
//    CC_SAFE_RELEASE(this);
    CCLog("delloc Text Spark");
}

//-- copy this to CcbManager 
/*
//CcbManager.h


//CcbManager.cpp

*/

//CCScene* TextSparkLayer::scene()
//{
//	// scene() was called after init()
//	CCScene* scene = CCScene::create();
//	//CCNode* pNode = CcbManager::sharedManager()->LoadTextSparkLayer(scene);
//    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//	pLoaderLib->registerCCNodeLoader("TextSparkLayer", TextSparkLayerLoader::loader());
//	
//    
//	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
//	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/spark.ccbi", scene);
//	
//	if (pNode != NULL)
//	{
//		scene->addChild(pNode);
//	}
//	pCCBReader->release();
//	return scene;
//}

bool TextSparkLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
//    mAnimationManager = NULL;
//    CCNode* pNode = CcbManager::sharedManager()->LoadTextSparkLayer(this);
//    pNode->setAnchorPoint(ccp(0.5, 0.0));
//    pNode->setPosition(ccp(0, 0));
//    addChild(pNode);
    this->setAnchorPoint(ccp(0.5, 0.0));
    this->setPosition(ccp(0, 0));
	return true;
}

void TextSparkLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void TextSparkLayer::onExit()
{
	CCLayer::onExit();
}

SEL_CallFuncN TextSparkLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler TextSparkLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

bool TextSparkLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);
	return false;
}

//void TextSparkLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
//{
//    CC_SAFE_RELEASE_NULL(mAnimationManager);
//    mAnimationManager = pAnimationManager;
//    CC_SAFE_RETAIN(mAnimationManager);
//}

bool TextSparkLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


SEL_CCControlHandler TextSparkLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

void TextSparkLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}









