#include "CcbEventAnnounceLayer.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "EventDataMgr.h"
#include "GameSession.h"
#include "CcbEventAnnounceFrame.h"


CcbEventAnnounceLayer::~CcbEventAnnounceLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTitle);
	CC_SAFE_RELEASE_NULL(m_pLayerAnnounce);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventAnnounceLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventAnnounceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventAnnounceLayer", CcbEventAnnounceLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_announcement.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventAnnounceLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEventAnnounceLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    loadData();
}

void CcbEventAnnounceLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEventAnnounceLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEventAnnounceLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventAnnounceLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTitle", CCLabelTTF*, this->m_pLabelTTFTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerAnnounce", CCLayer*, this->m_pLayerAnnounce);

	return false;
}

bool CcbEventAnnounceLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEventAnnounceLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventAnnounceLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventAnnounceLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventAnnounceLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_scroll = CCScrollView::create(m_pLayerAnnounce->getContentSize());
    m_scroll->setDirection(kCCScrollViewDirectionVertical);
    m_pLayerAnnounce->addChild(m_scroll);
}


void CcbEventAnnounceLayer::loadData()
{
    m_scroll->getContainer()->removeAllChildren();
    
    std::vector<STC_EVENT_ANNOUNCE_INFO> arrAnInfo = g_EventData->getEventAnnounce();
    float allH = 0;
    for (int i = 0; i < arrAnInfo.size(); i++) {
        float h = 0;
        CcbEventAnnounceFrame* node = dynamic_cast<CcbEventAnnounceFrame*>(CcbManager::sharedManager()->LoadCcbEventAnnounceFrame());
        h = node->loadData(arrAnInfo[i]);
        node->ignoreAnchorPointForPosition(false);
        node->setAnchorPoint(ccp(0, 0));
        node->setPosition(ccp(0, allH));
        
        m_scroll->addChild(node);
        allH += h + 10;
    }
    m_scroll->setContentSize(CCSizeMake(getWidth(m_pLayerAnnounce), allH));
    m_scroll->setContentOffset(ccp(0, m_scroll->getViewSize().height - allH));//(CCSizeMake(getWidth(m_pLayerAnnounce), allH));
}






