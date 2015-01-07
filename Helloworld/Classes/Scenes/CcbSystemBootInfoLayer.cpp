#include "CcbSystemBootInfoLayer.h"
#include "CcbManager.h"
#include "SystemMessage.h"
#include "ConfigGet.h"
#include "GuideData.h"
#include "BackCtrl.h"
#include "EventDataMgr.h"
#include "MusicCtrl.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

USING_NS_CC;
USING_NS_CC_EXT;

CcbSystemBootInfoLayer::~CcbSystemBootInfoLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGO);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFText);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbSystemBootInfoLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbSystemBootInfoLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbSystemBootInfoLayer", CcbSystemBootInfoLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system_boot_info.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbSystemBootInfoLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbSystemBootInfoLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbSystemBootInfoLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbSystemBootInfoLayer::onExit()
{
	CCLayer::onExit();
}

void CcbSystemBootInfoLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbSystemBootInfoLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGO", CCControlButton*, this->m_pControlButtonGO);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText", CCLabelTTF*, this->m_pLabelTTFText);

	return false;
}

bool CcbSystemBootInfoLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbSystemBootInfoLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbSystemBootInfoLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbSystemBootInfoLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbSystemBootInfoLayer::onPressControlButtonCancel);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGO", CcbSystemBootInfoLayer::onPressControlButtonGO);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbSystemBootInfoLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_dwSysLockId = 0;
    m_pControlButtonCancel->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    m_pControlButtonGO->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    m_pLabelTTFText->noStroke();
}


void CcbSystemBootInfoLayer::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    GuideData::GetInstance()->setSysLockId(0);
    removeFromParent();
}

void CcbSystemBootInfoLayer::onPressControlButtonGO(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, m_dwSysLockId);
    if (cfg) {
        switch (cfg->dwIndex) {
            case 2:
            case 6:
            case 7:
                BackCtrl::InsertNextScene(kTeamScene);
                break;
            case 3:
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
                AnalysicsManager::sharedAnalyticsMgr()->SendEvent("hero_guide_start");
#endif
                GuideData::GetInstance()->runSystemGuide(cfg->dwGuideId);
                BackCtrl::JumpToScene(kMainScene);
                break;
            case 1:
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
                AnalysicsManager::sharedAnalyticsMgr()->SendEvent("equip_guide_start");
#endif
            case 4:
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
                AnalysicsManager::sharedAnalyticsMgr()->SendEvent("arena_guide_start");
#endif
            case 5:
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
                AnalysicsManager::sharedAnalyticsMgr()->SendEvent("active_guide_start");
#endif
            case 8:
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
                AnalysicsManager::sharedAnalyticsMgr()->SendEvent("tower_guide_start");
#endif
            case 9:
            case 10:
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
                AnalysicsManager::sharedAnalyticsMgr()->SendEvent("badge_guide_start");
#endif
            case 11:
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
                AnalysicsManager::sharedAnalyticsMgr()->SendEvent("mystery_guide_start");
#endif
                GuideData::GetInstance()->runSystemGuide(cfg->dwGuideId);
                removeFromParent();
                GuideData::GetInstance()->addGuideLayer();
                break;
            default:
                break;
        }
    }
    else
    {
        CCString* str = CCString::createWithFormat("SystemDebLock not found id %d", m_dwSysLockId);
        SystemMessage::showSystemMessage(0, this, str->getCString());
    }
    GuideData::GetInstance()->setSysLockId(0);
}

void CcbSystemBootInfoLayer::loadData(uint32 sysLockId)
{
    m_dwSysLockId = sysLockId;
    
    // 装备引导需要强制，去除cancel按钮}
    if (m_dwSysLockId == 1) {
        m_pControlButtonCancel->setVisible(false);
    }
    
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, m_dwSysLockId);
    if (cfg) {
        m_pLabelTTFText->setString(cfg->strDesc.c_str());
    }
    else
    {
        CCString* str = CCString::createWithFormat("SystemDebLock not found id %d", m_dwSysLockId);
        SystemMessage::showSystemMessage(0, this, str->getCString());
    }
}

void CcbSystemBootInfoLayer::showSystemBootInfo(uint32 sysLockId, CCNode *parent)
{
    if (!sysLockId) {
        return;
    }
    
    CcbSystemBootInfoLayer *layer = dynamic_cast<CcbSystemBootInfoLayer*>(CcbManager::sharedManager()->LoadCcbSystemBootInfoLayer());
    layer->loadData(sysLockId);
    layer->ignoreAnchorPointForPosition(false);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    layer->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
    layer->setAnchorPoint(ccp(0.5, 0.5));
    if (parent) {
        parent->addChild(layer, 9999);
    }
    else
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(layer,9999);
    }
}

bool CcbSystemBootInfoLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void CcbSystemBootInfoLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*2, true);
}



