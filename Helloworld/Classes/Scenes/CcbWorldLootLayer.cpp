#include "CcbWorldLootLayer.h"
#include "CcbManager.h"
#include "FightAI.h"
#include "CcbShowGetLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"


USING_NS_CC;
USING_NS_CC_EXT;

CcbWorldLootLayer::~CcbWorldLootLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonOpen);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbWorldLootLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbWorldLootLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbWorldLootLayer", CcbWorldLootLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_sbox.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbWorldLootLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbWorldLootLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
    onDrop();
    
}

void CcbWorldLootLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbWorldLootLayer::onExit()
{
	CCLayer::onExit();
}

void CcbWorldLootLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbWorldLootLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOpen", CCControlButton*, this->m_pControlButtonOpen);

	return false;
}

bool CcbWorldLootLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbWorldLootLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbWorldLootLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbWorldLootLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOpen", CcbWorldLootLayer::onPressControlButtonOpen);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbWorldLootLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pControlButtonOpen->getParent()->setVisible(false);
    m_pControlButtonOpen->setTouchPriority(kCCMenuHandlerPriority - 20);
}

void CcbWorldLootLayer::showWorldLoot()
{
    if(FightAI::Get()->getWorldLoot().size() == 0){
        return;
    }
    
    CCNode *node = CcbManager::sharedManager()->LoadCcbWorldLootLayer();
    node->setPosition(CCDirector::sharedDirector()->getWinSize() * 0.5);
    node->ignoreAnchorPointForPosition(false);
    node->setAnchorPoint(ccp(0.5, 0.5));
    CCDirector::sharedDirector()->getRunningScene()->addChild(node, 990);
}

void CcbWorldLootLayer::onPressControlButtonOpen(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_chest));
    m_pControlButtonOpen->getParent()->setVisible(false);
    onOpen();
}


void CcbWorldLootLayer::onDrop()
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_get_chest));
    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbWorldLootLayer::endDrop));
    mAnimationManager->runAnimationsForSequenceNamed("show");
}

void CcbWorldLootLayer::endDrop()
{
    mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
    onLoop();
    
    m_pControlButtonOpen->getParent()->setVisible(true);
    CCNode* finger = CcbManager::sharedManager()->LoadCcbFingerUpLayer(this);
    finger->setPosition(m_pControlButtonOpen->getPosition() + ccp(40, -30));
    m_pControlButtonOpen->getParent()->addChild(finger);
}

void CcbWorldLootLayer::onLoop()
{
    mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
    mAnimationManager->runAnimationsForSequenceNamed("loop");
    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbWorldLootLayer::onLoop));
}

void CcbWorldLootLayer::onOpen()
{
    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbWorldLootLayer::endOpen));
    mAnimationManager->runAnimationsForSequenceNamed("end");
    m_pControlButtonOpen->getParent()->setVisible(false);
}

void CcbWorldLootLayer::endOpen()
{
    std::vector<STC_ITEM_DROP> arrItem = FightAI::Get()->getWorldLoot();
    CcbShowGetLayer* pGetLayer = dynamic_cast<CcbShowGetLayer*>(CcbManager::sharedManager()->LoadCcbShowGetLayer());
    pGetLayer->setNeedShowItemInfo(true);
    pGetLayer->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*0.5));
    
    int cnt = 0;
    for (int i = 0; i < arrItem.size(); i++) {
        STC_ITEM_DROP item = arrItem[i];
        if (!item.wItemType || !item.wCount) {
            continue;
        }
        cnt++;
        pGetLayer->addGetItem(item.wItemType, item.wCount);
    }
    CCDirector::sharedDirector()->getRunningScene()->addChild(pGetLayer, 998, 637);
    
    arrItem.clear();
    FightAI::Get()->setWorldLoot(arrItem);
    
    this->removeFromParent();
}

bool CcbWorldLootLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}
void CcbWorldLootLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 20, true);
}





