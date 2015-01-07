#include "CcbFightWaveLayer.h"
//#include "CcbManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFightWaveLayer::~CcbFightWaveLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteCurWave_1);
    CC_SAFE_RELEASE_NULL(m_pSpriteCurWave_2);
	CC_SAFE_RELEASE_NULL(m_pSpriteMaxWave);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFightWaveLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFightWaveLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFightWaveLayer", CcbFightWaveLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight_count.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFightWaveLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFightWaveLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
}

void CcbFightWaveLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFightWaveLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFightWaveLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFightWaveLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCurWave_1", CCSprite*, this->m_pSpriteCurWave_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCurWave_2", CCSprite*, this->m_pSpriteCurWave_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMaxWave", CCSprite*, this->m_pSpriteMaxWave);

	return false;
}

bool CcbFightWaveLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFightWaveLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler CcbFightWaveLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFightWaveLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFightWaveLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbFightWaveLayer::onStart()
{
    mAnimationManager->runAnimationsForSequenceNamed("onStart");
}

float CcbFightWaveLayer::getDuring()
{
    return 2.8;
}

void CcbFightWaveLayer::setCurWave(int cnt)
{
    CCString* str = CCString::createWithFormat("ccbresources/12monthdate/cartoon/pic_num_%d.png", cnt);
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(str->getCString());
    if (texture) {
        m_pSpriteCurWave_1->setContentSize(texture->getContentSize());
        m_pSpriteCurWave_2->setContentSize(texture->getContentSize());
        m_pSpriteCurWave_1->setTexture(texture);
        m_pSpriteCurWave_2->setTexture(texture);
    }
}
void CcbFightWaveLayer::setMaxWave(int cnt)
{
    CCString* str = CCString::createWithFormat("ccbresources/12monthdate/cartoon/pic_num_%d.png", cnt);
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(str->getCString());
    if (texture) {
        m_pSpriteMaxWave->setContentSize(texture->getContentSize());
        m_pSpriteMaxWave->setTexture(texture);
    }
}




