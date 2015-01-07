#include "CcbBattleDead.h"
//#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbBattleDead::~CcbBattleDead()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBattleDead( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBattleDead( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBattleDead", CcbBattleDeadLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/battle_dead.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbBattleDead::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBattleDead::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbBattleDead::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbBattleDead::onExit()
{
	CCLayer::onExit();
}

void CcbBattleDead::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBattleDead::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

	return false;
}

bool CcbBattleDead::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbBattleDead::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "addPlist", CcbBattleDead::addPlist);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "removeSelf", CcbBattleDead::removeSelf);
	return NULL;
}

SEL_MenuHandler CcbBattleDead::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBattleDead::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbBattleDead::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}


void CcbBattleDead::addPlist(cocos2d::CCNode* pNode)
{
    ///Users/sky_zmy/Documents/pet2/resource/ccbresources/12monthdate/battle/battle_dead.plist
    CCParticleSystemQuad* eff = CCParticleSystemQuad::create("ccbresources/12monthdate/battle/battle_dead.plist");
    eff->setPosition(CCPointZero);
    addChild(eff);
}

void CcbBattleDead::removeSelf(cocos2d::CCNode* pNode)
{
    removeFromParent();
}




