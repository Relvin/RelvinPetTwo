#include "CcbWorldBossRankLayer.h"
//#include "CcbManager.h"
#include "ResourceDefine.h"
#include "WorldBossDataMgr.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "ResourceStringClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbWorldBossRankLayer::~CcbWorldBossRankLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerRankList);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbWorldBossRankLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbWorldBossRankLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbWorldBossRankLayer", CcbWorldBossRankLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/world_boss_damagerank.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbWorldBossRankLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbWorldBossRankLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbWorldBossRankLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbWorldBossRankLayer::onExit()
{
	CCLayer::onExit();
}

void CcbWorldBossRankLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbWorldBossRankLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRankList", CCLayer*, this->m_pLayerRankList);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);

	return false;
}

bool CcbWorldBossRankLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbWorldBossRankLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbWorldBossRankLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbWorldBossRankLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbWorldBossRankLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbWorldBossRankLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 16);
    
    m_scroll = CCScrollView::create(m_pLayerRankList->getContentSize());
    m_scroll->setDirection(kCCScrollViewDirectionVertical);
    m_scroll->setTouchPriority(kCCMenuHandlerPriority - 16);
    m_pLayerRankList->addChild(m_scroll);
    
}

void CcbWorldBossRankLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    this->setVisible(false);
}

void CcbWorldBossRankLayer::loadData()
{
    m_scroll->getContainer()->removeAllChildren();
    
    float allH = 0;
    std::vector<STC_BOSS_RANK_INFO> arrRank = g_WorldBossData->getLastRank();
    for (int i = arrRank.size() - 1; i >= 0; i--) {
        STC_BOSS_RANK_INFO info = arrRank[i];
        CCNode* node = CCNode::create();
        node->setContentSize(CCSizeMake(getWidth(m_pLayerRankList), 20));
        
        CCString* str = CCString::createWithFormat("%s(%d)", info.strName.c_str(), info.dwRoleId);
        CCLabelTTF* lblName = CCLabelTTF::create(str->getCString(), FONT_HEL, 12);
        
        str->initWithFormat(GET_STR(Str_dijiming), i+1);
        CCLabelTTF* lblRank = CCLabelTTF::create(str->getCString(), FONT_HEL, 12);
        
        str->initWithFormat("%d", info.dwAllDamage);
        CCLabelTTF* lblDam = CCLabelTTF::create(str->getCString(), FONT_HEL, 12);
        
        lblRank->setPosition(ccp(26, getHeight(node)*0.5));
        lblRank->setAnchorPoint(ccp(0.5, 0.5));
        
        lblName->setPosition(ccp(135, getHeight(node)*0.5));
        lblName->setAnchorPoint(ccp(0.5, 0.5));
        
        lblDam->setPosition(ccp(220, getHeight(node)*0.5));
        lblDam->setAnchorPoint(ccp(0, 0.5));
        
        node->addChild(lblName);
        node->addChild(lblRank);
        node->addChild(lblDam);
        
        node->setPosition(0, allH);
        node->setAnchorPoint(ccp(0, 0));
        m_scroll->addChild(node);
        allH += getHeight(node);
    }
    
    m_scroll->setContentSize(CCSizeMake(getWidth(m_pLayerRankList), allH));
    m_scroll->setContentOffset(m_scroll->getViewSize() - m_scroll->getContentSize());
}

bool CcbWorldBossRankLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return isVisible();
}

void CcbWorldBossRankLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 15, true);
}




