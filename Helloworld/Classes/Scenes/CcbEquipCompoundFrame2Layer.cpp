#include "CcbEquipCompoundFrame2Layer.h"
//#include "CcbManager.h"
#include "EquipDataMgr.h"

CcbEquipCompoundFrame2Layer::~CcbEquipCompoundFrame2Layer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNeedNum);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFOwnNum);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEquipCompoundFrame2Layer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEquipCompoundFrame2Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEquipCompoundFrame2Layer", CcbEquipCompoundFrame2LayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_compound_frame2.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEquipCompoundFrame2Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    this->setTouchEnabled(true);
	return true;
}

void CcbEquipCompoundFrame2Layer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}

}

void CcbEquipCompoundFrame2Layer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipCompoundFrame2Layer::onExit()
{
	CCLayer::onExit();
}

void CcbEquipCompoundFrame2Layer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEquipCompoundFrame2Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNeedNum", CCLabelTTF*, this->m_pLabelTTFNeedNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFOwnNum", CCLabelTTF*, this->m_pLabelTTFOwnNum);

	return false;
}

bool CcbEquipCompoundFrame2Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEquipCompoundFrame2Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEquipCompoundFrame2Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEquipCompoundFrame2Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipCompoundFrame2Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
//    m_pLabelTTFName->setStrokeForLabelTTF(ccBLACK, 1.0f);
//    m_pLabelTTFNeedNum->setStrokeForLabelTTF(ccBLACK, 1.0f);
//    m_pLabelTTFOwnNum->setStrokeForLabelTTF(ccBLACK, 1.0f);
}

void CcbEquipCompoundFrame2Layer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool CcbEquipCompoundFrame2Layer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_StartTouchPos = CCPoint(0, 0);
    m_StartTouchPos = pTouch->getLocation();
    return true;
}

void CcbEquipCompoundFrame2Layer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_EndTouchPos = CCPoint(0, 0);
    m_EndTouchPos = pTouch->getLocation();
}







