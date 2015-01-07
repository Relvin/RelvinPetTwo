#include "CcbArenaRewardLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "ArenaDataMgr.h"
#include "BackCtrl.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbArenaRewardLayer::~CcbArenaRewardLayer()
{
	//CC_SAFE_RELEASE_NULL(m_pSpriteRewardIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
	//CC_SAFE_RELEASE_NULL(m_pLabelTTFRewardName);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReward);
    CC_SAFE_RELEASE_NULL(m_pNodeEffect);
    //CC_SAFE_RELEASE_NULL(m_pNodeShowTime);
    //CC_SAFE_RELEASE_NULL(m_pNodeButtonReward);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaRewardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaRewardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaRewardLayer", CcbArenaRewardLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_reward.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaRewardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbArenaRewardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbArenaRewardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaRewardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbArenaRewardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaRewardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRewardIcon", CCSprite*, this->m_pSpriteRewardIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRewardName", CCLabelTTF*, this->m_pLabelTTFRewardName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReward", CCControlButton*, this->m_pControlButtonReward);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeShowTime", CCNode*, this->m_pNodeShowTime);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeButtonReward", CCNode*, this->m_pNodeButtonReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEffect", CCNode*, this->m_pNodeEffect);
	return false;
}

bool CcbArenaRewardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaRewardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaRewardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaRewardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReward", CcbArenaRewardLayer::onPressControlButtonReward);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaRewardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
//    m_pLabelTTFTime->setStrokeForLabelTTF(ccBLACK, 1.0f);
//    m_pControlButtonReward->setStrokeForTitle(ccBLACK, 1.0f);
    CCParticleSystemQuad* eff1 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/eff_jiangli_1.plist");
    CCParticleSystemQuad* eff2 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/eff_jiangli_2.plist");
    
    eff1->setPosition(CCPointZero);
    m_pNodeEffect->addChild(eff1);
    
    eff2->setPosition(CCPointZero);
    m_pNodeEffect->addChild(eff2);
    m_pNodeEffect->setVisible(false);
}

void CcbArenaRewardLayer::onPressControlButtonReward(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    m_pNodeEffect->setVisible(false);
	// TODO:
//    if (g_ArenaData->isCanRequestReward())
//    {
//        PetLoadingLayer::sharedLayer()->WaitForPacket();
//        CGameSession::SendArenaReward();
//    }
//    else
    {
        BackCtrl::InsertNextScene(kArenaRankRewardScene);
    }
}

void CcbArenaRewardLayer::setEffectVisible(bool show)
{
//    m_pNodeEffect->setVisible(show);
}







