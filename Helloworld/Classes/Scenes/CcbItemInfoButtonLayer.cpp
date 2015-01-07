#include "CcbItemInfoButtonLayer.h"
//#include "CcbManager.h"
#include "CcbItemInfoLayer.h"
#include "EnumDefines.h"
#include "PetCtrl.h"
#include "BackCtrl.h"


CcbItemInfoButtonLayer::~CcbItemInfoButtonLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonShowItemInfo);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbItemInfoButtonLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbItemInfoButtonLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbItemInfoButtonLayer", CcbItemInfoButtonLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/iteminfo_button.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbItemInfoButtonLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_dwShowItemID = 0;
//    setTouchEnabled(true);
	return true;
}

void CcbItemInfoButtonLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbItemInfoButtonLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbItemInfoButtonLayer::onExit()
{
	CCLayer::onExit();
}

void CcbItemInfoButtonLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbItemInfoButtonLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShowItemInfo", CCControlButton*, this->m_pControlButtonShowItemInfo);

	return false;
}

bool CcbItemInfoButtonLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbItemInfoButtonLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbItemInfoButtonLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbItemInfoButtonLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShowItemInfo", CcbItemInfoButtonLayer::onPressControlButtonShowItemInfo);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbItemInfoButtonLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonShowItemInfo->setVisible(false);
    m_btnShow = CCScrollButton::createTransWithHightLight();
    m_btnShow->setZoomOnTouchDown(false);
    m_btnShow->setPreferredSize(m_pControlButtonShowItemInfo->getContentSize());
    m_btnShow->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbItemInfoButtonLayer::onPressControlButtonShowItemInfo), CCControlEventTouchUpInside);
    m_btnShow->setPosition(m_pControlButtonShowItemInfo->getPosition());
    m_btnShow->ignoreAnchorPointForPosition(true);
    addChild(m_btnShow);
    m_btnShow->setTouchPriority(kCCMenuHandlerPriority* 2 + 10);
}

//void CcbItemInfoButtonLayer::registerWithTouchDispatcher()
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
//}

//bool CcbItemInfoButtonLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    m_StartTouchPos = CCPoint(0, 0);
//    m_StartTouchPos = pTouch->getLocation();
//    return false;
//}

//void CcbItemInfoButtonLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//    m_EndTouchPos = CCPoint(0, 0);
//    m_EndTouchPos = pTouch->getLocation();
//}

void CcbItemInfoButtonLayer::onPressControlButtonShowItemInfo(CCObject* pSender, CCControlEvent event)
{
	// TODO:
//    if( fabs(m_StartTouchPos.x - m_EndTouchPos.x) > 20 || fabs(m_StartTouchPos.y - m_EndTouchPos.y) > 10)
//    {
//        return;
//    }
    if (m_dwShowItemID == 0)
    {
        return;
    }
    
    if (m_dwShowItemID >= 50000002 && m_dwShowItemID <= 51000000)
    {
        return;
    }
    
    if (m_dwShowItemID / E_UNITE_BASE_FABIO == E_UNITE_TYPE_PET) {
        CPetCtrl::Get()->setPetTujianShowId(m_dwShowItemID);
        BackCtrl::InsertNextScene(kShowPetTujian, kNormalTrans);
        return;
    }
    if (m_dwShowItemID)
    {
        CShowItemInfo::Get()->Show(m_dwShowItemID);
    }
    
}

void CcbItemInfoButtonLayer::setClipRect(CCRect rect)
{
    m_btnShow->setClipRect(rect);
}







