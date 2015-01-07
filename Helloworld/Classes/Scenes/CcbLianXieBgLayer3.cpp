#include "CcbLianXieBgLayer3.h"
//#include "CcbManager.h"
#include "UISupport.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbLianXieBgLayer3::~CcbLianXieBgLayer3()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbLianXieBgLayer3( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbLianXieBgLayer3( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbLianXieBgLayer3", CcbLianXieBgLayer3Loader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_flash_3.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbLianXieBgLayer3::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbLianXieBgLayer3::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CCParticleSystemQuad* par = CCParticleSystemQuad::create("ccbresources/12monthdate/battle/pet_battle_flash_3.plist");
    par->setPosition(ccp(getWidth(this)*0.5, getHeight(this)*0.5));
    par->setAnchorPoint(ccp(0.5, 0.5));
    addChild(par);
}

void CcbLianXieBgLayer3::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbLianXieBgLayer3::onExit()
{
	CCLayer::onExit();
}

void CcbLianXieBgLayer3::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbLianXieBgLayer3::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

	return false;
}

bool CcbLianXieBgLayer3::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbLianXieBgLayer3::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onRemoveSelf", CcbLianXieBgLayer3::onRemoveSelf);
	return NULL;
}

SEL_MenuHandler CcbLianXieBgLayer3::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbLianXieBgLayer3::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbLianXieBgLayer3::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}


void CcbLianXieBgLayer3::onRemoveSelf(cocos2d::CCNode *pNode)
{
    removeFromParentAndCleanup(true);
}







