#include "$classname.h"
//#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

$classname::~$classname()
{
$releaseAssigner
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* Load$classname( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::Load$classname( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "$classname", $classLoader::loader() );
	$bindCcbFileSelector
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("$ccbifilename", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool $classname::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void $classname::onEnter()
{
	$inheritclass::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void $classname::onEnterTransitionDidFinish()
{
	$inheritclass::onEnterTransitionDidFinish();
}

void $classname::onExit()
{
	$inheritclass::onExit();
}

void $classname::onExitTransitionDidStart()
{
	$inheritclass::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool $classname::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
$bindMemberVariable
	return false;
}

bool $classname::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN $classname::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
$bindCallfuncSelector
	return NULL;
}

SEL_MenuHandler $classname::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
$bindMenuSelector
	return NULL;
}

SEL_CCControlHandler $classname::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
$bindControlSelector
	return NULL;
}

// Inhert CCNodeLoaderListener
void $classname::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
}

$menuSelectorCallback

$controlSelectorCallback

$callfuncSelectorCallback

$androidMenuReturnCallback

$inheritByCCTableViewVirtualFunctionImplement