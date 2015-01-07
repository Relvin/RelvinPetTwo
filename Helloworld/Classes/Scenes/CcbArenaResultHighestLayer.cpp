#include "CcbArenaResultHighestLayer.h"
//#include "CcbManager.h"
#include "ArenaDataMgr.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "CcbArenaResultWinLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbArenaResultHighestLayer::~CcbArenaResultHighestLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonOK);
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontPreRank);
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontCurRank);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRewardNums);
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontUpNums);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaResultHighestLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaResultHighestLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaResultHighestLayer", CcbArenaResultHighestLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_result_highest.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaResultHighestLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbArenaResultHighestLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_player_lv_up));
}

void CcbArenaResultHighestLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaResultHighestLayer::onExit()
{
	CCLayer::onExit();
}

void CcbArenaResultHighestLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaResultHighestLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOK", CCControlButton*, this->m_pControlButtonOK);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontPreRank", CCLabelBMFont*, this->m_pLabelBMFontPreRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontCurRank", CCLabelBMFont*, this->m_pLabelBMFontCurRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRewardNums", CCLabelTTF*, this->m_pLabelTTFRewardNums);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontUpNums", CCLabelBMFont*, this->m_pLabelBMFontUpNums);

	return false;
}

bool CcbArenaResultHighestLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbArenaResultHighestLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaResultHighestLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaResultHighestLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOK", CcbArenaResultHighestLayer::onPressControlButtonOK);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaResultHighestLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    RESULT_INFO_ALL showInfo = CArenaDataMgr::Get()->GetResultInfo();
    CCString *str = CCString::create("");
    
    str->initWithFormat("%d", g_ArenaData->getMyPreRank());
    m_pLabelBMFontPreRank->setString(str->getCString());
    
    str->initWithFormat("%d", showInfo.infoPersonal[0].dwRank);
    m_pLabelBMFontCurRank->setString(str->getCString());
    
    str->initWithFormat("%d", g_ArenaData->getMyPreRank() - showInfo.infoPersonal[0].dwRank);
    m_pLabelBMFontUpNums->setString(str->getCString());
    
    str->initWithFormat("%d", showInfo.dwMaxRankDollar);
    m_pLabelTTFRewardNums->setString(str->getCString());
    
    
    m_pControlButtonOK->setTouchPriority(2*kCCMenuHandlerPriority - 24);
}



void CcbArenaResultHighestLayer::onPressControlButtonOK(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_delegate) {
        m_delegate->addGuideLayer();
    }
    removeFromParent();
    
}


void CcbArenaResultHighestLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2*kCCMenuHandlerPriority - 23, true);
}

bool CcbArenaResultHighestLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
    
}






