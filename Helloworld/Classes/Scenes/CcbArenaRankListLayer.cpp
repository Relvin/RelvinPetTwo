#include "CcbArenaRankListLayer.h"
//#include "CcbManager.h"
#include "ArenaDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"

CcbArenaRankListLayer::~CcbArenaRankListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonBattle);
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteCrown);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRank);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMoney);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFReputation);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFWin);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLose);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaRankListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaRankListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaRankListLayer", CcbArenaRankListLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_rank_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaRankListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbArenaRankListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbArenaRankListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaRankListLayer::onExit()
{
	CCLayer::onExit();
}

void CcbArenaRankListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaRankListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBattle", CCControlButton*, this->m_pControlButtonBattle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCrown", CCSprite*, this->m_pSpriteCrown);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRank", CCLabelTTF*, this->m_pLabelTTFRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMoney", CCLabelTTF*, this->m_pLabelTTFMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFReputation", CCLabelTTF*, this->m_pLabelTTFReputation);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWin", CCLabelTTF*, this->m_pLabelTTFWin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLose", CCLabelTTF*, this->m_pLabelTTFLose);

	return false;
}

bool CcbArenaRankListLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaRankListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaRankListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaRankListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBattle", CcbArenaRankListLayer::onPressControlButtonBattle);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaRankListLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbArenaRankListLayer::onPressControlButtonBattle(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    if( fabs(m_StartTouchPos.x - m_EndTouchPos.x) > 20 || fabs(m_StartTouchPos.y - m_EndTouchPos.y) > 10)
    {
        return;
    }
    
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    
    int index = getLocalTag();
    ARENA_BATTLE_LIST_INFO tempInfo = CArenaDataMgr::Get()->GetRankList()[index];
    CGameSession::SendArenaLearn(tempInfo.dwUserId, tempInfo.dwRank);
    //CCLog("切磋");

}


void CcbArenaRankListLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool CcbArenaRankListLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_StartTouchPos = CCPoint(0, 0);
    m_StartTouchPos = pTouch->getLocation();
    return true;
}

void CcbArenaRankListLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_EndTouchPos = CCPoint(0, 0);
    m_EndTouchPos = pTouch->getLocation();
}




