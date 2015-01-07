#include "CcbTextLianXieLayer.h"
//#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbTextLianXieLayer::~CcbTextLianXieLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontAdd);
    CC_SAFE_RELEASE_NULL(m_pLabelBMFontAdd2);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTextLianXieLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTextLianXieLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTextLianXieLayer", CcbTextLianXieLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/crit.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbTextLianXieLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbTextLianXieLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
}

void CcbTextLianXieLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbTextLianXieLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTextLianXieLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTextLianXieLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontAdd", CCLabelBMFont*, this->m_pLabelBMFontAdd);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontAdd2", CCLabelBMFont*, this->m_pLabelBMFontAdd2);

	return false;
}

bool CcbTextLianXieLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTextLianXieLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTextLianXieLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTextLianXieLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTextLianXieLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}


void CcbTextLianXieLayer::show()
{
    mAnimationManager->runAnimationsForSequenceNamed("splash");
}

void CcbTextLianXieLayer::setAdd(uint16 add)
{
    CCString* str = CCString::createWithFormat("x %1.1f", (float)add / 10000);
    m_pLabelBMFontAdd->setString(str->getCString());
    m_pLabelBMFontAdd2->setString(str->getCString());
}




