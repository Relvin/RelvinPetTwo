#include "CcbLianXieBgLayer.h"
//#include "CcbManager.h"


CcbLianXieBgLayer::~CcbLianXieBgLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerMask);
    CC_SAFE_RELEASE_NULL(m_pSpriteGuangZhu);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbLianXieBgLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbLianXieBgLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbLianXieBgLayer", CcbLianXieBgLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_start_fight.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbLianXieBgLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbLianXieBgLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
    
//    m_pLayerMask->runAction(CCFadeIn::create(0.15));
}

void CcbLianXieBgLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbLianXieBgLayer::onExit()
{
	CCLayer::onExit();
}

void CcbLianXieBgLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbLianXieBgLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMask", CCLayer*, this->m_pLayerMask);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteGuangZhu", CCSprite*, this->m_pSpriteGuangZhu);
	return false;
}

bool CcbLianXieBgLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbLianXieBgLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onAddLight", CcbLianXieBgLayer::onAddLight);
	return NULL;
}

SEL_MenuHandler CcbLianXieBgLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbLianXieBgLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbLianXieBgLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbLianXieBgLayer::onAddLight(cocos2d::CCNode *pNode)
{
    m_pSpriteGuangZhu->runAction(CCFadeIn::create(0.15));
    m_pSpriteGuangZhu->runAction(CCRepeatForever::create(
                                                         CCSequence::create(CCMoveBy::create(2.0 / 60.0, ccp(900, 0)),
                                                                            CCMoveBy::create(2.0 / 60.0, ccp(-900, 0)),
                                                                            NULL)));
}







