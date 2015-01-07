#include "CcbFightFinishLayer.h"
//#include "CcbManager.h"
#include "MusicCtrl.h"
#include "CheckPointMgr.h"
#include "CcbPetBattleLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFightFinishLayer::~CcbFightFinishLayer()
{

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFightFinishLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFightFinishLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFightFinishLayer", CcbFightFinishLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight_finish.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFightFinishLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFightFinishLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbFightFinishLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFightFinishLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFightFinishLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFightFinishLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

	return false;
}

bool CcbFightFinishLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFightFinishLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "stopBgm", CcbFightFinishLayer::stopBgm);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "endCallBack", CcbFightFinishLayer::endCallBack);
	return NULL;
}

SEL_MenuHandler CcbFightFinishLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFightFinishLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFightFinishLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}


float CcbFightFinishLayer::getDuring()
{
    return 3.2;
}

void CcbFightFinishLayer::stopBgm(cocos2d::CCNode *pNode)
{
    CMusicCtrl::StopBackgroundMusic();
}

void CcbFightFinishLayer::endCallBack(cocos2d::CCNode *pNode) {
    if ( CheckPointMgr::Get()->FightEndCnt() > 0 ) {
        CheckPointMgr::Get()->addFightEndTalk(0, CcbPetBattleLayer::GetCurrScene());
    }
}



