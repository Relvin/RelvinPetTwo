#include "CcbHeaderBackLayer2.h"
//#include "CcbManager.h"
#include "BackCtrl.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbHeaderBackLayer2::~CcbHeaderBackLayer2()
{
//	CC_SAFE_RELEASE_NULL(m_pSpriteAttribute);
//	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
	CC_SAFE_RELEASE_NULL(m_pNodeBg);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbHeaderBackLayer2( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbHeaderBackLayer2( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbHeaderBackLayer2", CcbHeaderBackLayer2Loader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/header_back2.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbHeaderBackLayer2::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbHeaderBackLayer2::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbHeaderBackLayer2::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbHeaderBackLayer2::onExit()
{
	CCLayer::onExit();
}

void CcbHeaderBackLayer2::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbHeaderBackLayer2::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute", CCSprite*, this->m_pSpriteAttribute);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeBg", CCNode*, this->m_pNodeBg);

	return false;
}

bool CcbHeaderBackLayer2::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbHeaderBackLayer2::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbHeaderBackLayer2::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbHeaderBackLayer2::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbHeaderBackLayer2::onPressControlButtonBack);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbHeaderBackLayer2::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonBack->setTouchPriority(kCCMenuHandlerPriority+30);
    m_backFlag = false;
    
}



void CcbHeaderBackLayer2::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    if (m_backFlag) {
        return;
    }
    m_backFlag = true;
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    BackCtrl::BacktoUpperScene(kNormalTrans);
}







