#include "CcbBossWarningLayer.h"
//#include "CcbManager.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "StageScene.h"
#include "FightAI.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbBossWarningLayer::~CcbBossWarningLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteBoxOpen_1);
	CC_SAFE_RELEASE_NULL(m_pSpriteBoxClose);
	CC_SAFE_RELEASE_NULL(m_pSpriteBoxOpen_2);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBossWarningLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBossWarningLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBossWarningLayer", CcbBossWarningLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/boss.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbBossWarningLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbBossWarningLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbBossWarningLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbBossWarningLayer::onExit()
{
	CCLayer::onExit();
}

void CcbBossWarningLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBossWarningLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBoxOpen_1", CCSprite*, this->m_pSpriteBoxOpen_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBoxClose", CCSprite*, this->m_pSpriteBoxClose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBoxOpen_2", CCSprite*, this->m_pSpriteBoxOpen_2);

	return false;
}

bool CcbBossWarningLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbBossWarningLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "stopBgm", CcbBossWarningLayer::stopBgm);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "playBossBgm", CcbBossWarningLayer::playBossBgm);
	return NULL;
}

SEL_MenuHandler CcbBossWarningLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBossWarningLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbBossWarningLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbBossWarningLayer::stopBgm(cocos2d::CCNode *pNode)
{
    CMusicCtrl::StopBackgroundMusic();
}

void CcbBossWarningLayer::playBossBgm(cocos2d::CCNode *pNode)
{
    switch (FightAI::Get()->getFightType()) {
        case E_BATTLE_TYPE_MAP:
        case E_BATTLE_TYPE_HERO_MAP:
        case E_BATTLE_TYPE_ACTIVE_MAP:
        case E_BATTLE_TYPE_COIN_TREE:
        {
            StageCtrl::STC_STAGE stage = StageCtrl::Get()->selectedStage();
            int m = stage.vectNormalBgm.size();
            if (m > 0) {
                m = rand() % m;
                CMusicCtrl::PlayBackgroundMusic(GET_BATTLE_BOSS_MUSIC(stage.vectBossBgm[m]));
                return;
            }
        }
            break;
            
        default:
            break;
    }
    
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Bgm_activity_boss));
}







