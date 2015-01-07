#include "CcbWorldBossRankRewardFrame.h"
//#include "CcbManager.h"
#include "CcbItemIconLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbWorldBossRankRewardFrame::~CcbWorldBossRankRewardFrame()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon1);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon2);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon3);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon4);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRank);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbWorldBossRankRewardFrame( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbWorldBossRankRewardFrame( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbWorldBossRankRewardFrame", CcbWorldBossRankRewardFrameLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/item_icon.ccb]", [ccb/item_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/wolrd_boss_rewardframe.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbWorldBossRankRewardFrame::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbWorldBossRankRewardFrame::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbWorldBossRankRewardFrame::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbWorldBossRankRewardFrame::onExit()
{
	CCLayer::onExit();
}

void CcbWorldBossRankRewardFrame::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbWorldBossRankRewardFrame::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon1", CcbItemIconLayer*, this->m_pLayerIcon1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon2", CcbItemIconLayer*, this->m_pLayerIcon2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon3", CcbItemIconLayer*, this->m_pLayerIcon3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon4", CcbItemIconLayer*, this->m_pLayerIcon4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRank", CCLabelTTF*, this->m_pLabelTTFRank);

	return false;
}

bool CcbWorldBossRankRewardFrame::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbWorldBossRankRewardFrame::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbWorldBossRankRewardFrame::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbWorldBossRankRewardFrame::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbWorldBossRankRewardFrame::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
}


void CcbWorldBossRankRewardFrame::loadData(uint32 rewId)
{
    std::vector<CcbItemIconLayer*> arrItemIcon;
    arrItemIcon.push_back(m_pLayerIcon1);
    arrItemIcon.push_back(m_pLayerIcon2);
    arrItemIcon.push_back(m_pLayerIcon3);
    arrItemIcon.push_back(m_pLayerIcon4);
    
    for (int i = 0; i < arrItemIcon.size(); i++) {
        arrItemIcon[i]->setVisible(false);
    }
    
    WorldBossRewardConfig::STC_WORLD_BOSS_REWARD_CONFIG* cfg = GET_CONFIG_STC(WorldBossRewardConfig, rewId);
    if (!cfg) {
        return;
    }
    CCString* str = CCString::create("");
    if (cfg->wRankBegin == cfg->wRankEnd) {
        str->initWithFormat(GET_STR(Str_dijiming), cfg->wRankBegin);
    }
    else{
        std::string str1 = GET_STR(Str_dijiming);
        str1 += "~" + str1;
        str->initWithFormat(str1.c_str(), cfg->wRankBegin, cfg->wRankEnd);
    }
    m_pLabelTTFRank->setString(str->getCString());
    
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        if (!cfg->dwItemID[i]) {
            continue;
        }
        arrItemIcon[cnt]->setVisible(true);
        arrItemIcon[cnt]->loadIndexData(cfg->dwItemID[i]);
        arrItemIcon[cnt]->showIconOnly();
        arrItemIcon[cnt]->showCnt(cfg->dwItemCount[i]);
        arrItemIcon[cnt]->showName();
    }
    
}

void CcbWorldBossRankRewardFrame::setClipRect(cocos2d::CCRect rect)
{
    m_pLayerIcon1->setClipRect(rect);
    m_pLayerIcon2->setClipRect(rect);
    m_pLayerIcon3->setClipRect(rect);
    m_pLayerIcon4->setClipRect(rect);
}






