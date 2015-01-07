#include "CcbGachaOpenEgg.h"
//#include "CcbManager.h"
#include "CcbGachaResultLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbGachaOpenEgg::~CcbGachaOpenEgg()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteEgg1);
	CC_SAFE_RELEASE_NULL(m_pSpriteEgg2);
	CC_SAFE_RELEASE_NULL(m_pControlButtonOpen);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbGachaOpenEgg( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbGachaOpenEgg( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGachaOpenEgg", CcbGachaOpenEggLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_result_2.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbGachaOpenEgg::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbGachaOpenEgg::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbGachaOpenEgg::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbGachaOpenEgg::onExit()
{
	CCLayer::onExit();
}

void CcbGachaOpenEgg::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbGachaOpenEgg::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEgg1", CCSprite*, this->m_pSpriteEgg1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEgg2", CCSprite*, this->m_pSpriteEgg2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOpen", CCControlButton*, this->m_pControlButtonOpen);

	return false;
}

bool CcbGachaOpenEgg::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbGachaOpenEgg::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbGachaOpenEgg::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbGachaOpenEgg::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOpen", CcbGachaOpenEgg::onPressControlButtonOpen);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGachaOpenEgg::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}



void CcbGachaOpenEgg::onPressControlButtonOpen(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_delegate) {        
        m_delegate->showEgg();
        hideEgg();
    }
}

void CcbGachaOpenEgg::loadData(uint8 quality){

    CCString* path = CCString::createWithFormat("ccbresources/12monthdate/gacha/dan%d.png", quality);
    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(path->getCString());
    if (tex) {
        m_pSpriteEgg1->setTexture(tex);
        m_pSpriteEgg2->setTexture(tex);
    }
}

void CcbGachaOpenEgg::hideEgg()
{
    stopAllActions();
    m_pControlButtonOpen->setEnabled(false);
    m_pSpriteEgg1->setVisible(false);
    m_pSpriteEgg2->setVisible(false);
}



