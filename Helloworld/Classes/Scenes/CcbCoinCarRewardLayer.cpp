#include "CcbCoinCarRewardLayer.h"
//#include "CcbManager.h"
#include "FightAI.h"
USING_NS_CC;
USING_NS_CC_EXT;

CcbCoinCarRewardLayer::~CcbCoinCarRewardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDamage);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCoin);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbCoinCarRewardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbCoinCarRewardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbCoinCarRewardLayer", CcbCoinCarRewardLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/coin_cat_reward.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbCoinCarRewardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbCoinCarRewardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbCoinCarRewardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbCoinCarRewardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbCoinCarRewardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbCoinCarRewardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDamage", CCLabelTTF*, this->m_pLabelTTFDamage);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoin", CCLabelTTF*, this->m_pLabelTTFCoin);

	return false;
}

bool CcbCoinCarRewardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbCoinCarRewardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbCoinCarRewardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbCoinCarRewardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbCoinCarRewardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbCoinCarRewardLayer::loadData()
{
    curDam = 0;
    curMoney = 0;
    bIsEnd = false;
    m_pLabelTTFDamage->setString("0");
    m_pLabelTTFCoin->setString("0");
    damAdd = FightAI::Get()->getCoinCatDamage() / 120;
    moneyAdd = FightAI::Get()->getCoinCatMoney() / 120;
    
}
void CcbCoinCarRewardLayer::updateValue(float time)
{
    curDam += damAdd;
    curMoney += moneyAdd;
    if (curDam > FightAI::Get()->getCoinCatDamage()) {
        curDam = FightAI::Get()->getCoinCatDamage();
    }
    if (curMoney > FightAI::Get()->getCoinCatMoney()) {
        curMoney = FightAI::Get()->getCoinCatMoney();
        
        showEnd();
        return;
    }
    CCString* str = CCString::createWithFormat("%d", curDam);
    m_pLabelTTFDamage->setString(str->getCString());
    str->initWithFormat("%d", curMoney);
    m_pLabelTTFCoin->setString(str->getCString());
}
void CcbCoinCarRewardLayer::onShow()
{
    schedule(schedule_selector(CcbCoinCarRewardLayer::updateValue));
}
void CcbCoinCarRewardLayer::showEnd()
{
    if (bIsEnd) {
        return;
    }
    unschedule(schedule_selector(CcbCoinCarRewardLayer::updateValue));
    bIsEnd = true;
    CCString* str = CCString::createWithFormat("%d", FightAI::Get()->getCoinCatDamage());
    m_pLabelTTFDamage->setString(str->getCString());
    str->initWithFormat("%d", FightAI::Get()->getCoinCatMoney());
    m_pLabelTTFCoin->setString(str->getCString());
}





