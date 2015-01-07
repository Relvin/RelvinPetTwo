#include "CcbArenaRankRewardFrameLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "ConfigGet.h"
#include "EnumDefines.h"
#include "ResourceStringClient.h"
#include "PetBattleData.h"

CcbArenaRankRewardFrameLayer::~CcbArenaRankRewardFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteCanGet);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRankNum);
	CC_SAFE_RELEASE_NULL(m_pSpriteRankType);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFGroupName);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon1);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon2);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon3);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon4);
    
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 CCNode* LoadCcbArenaRankRewardFrameLayer( CCObject* owner );
 
 //CcbManager.cpp
 CCNode* CcbManager::LoadCcbArenaRankRewardFrameLayer( CCObject* owner ) {
 CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
 pLoaderLib->registerCCNodeLoader( "CcbArenaRankRewardFrameLayer", CcbArenaRankRewardFrameLayerLoader::loader() );
 
 
 CCBReader* pCCBReader = new CCBReader(pLoaderLib);
 CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_rank_reward_frame.ccbi", owner);
 pCCBReader->release();
 
 return pNode;
 }
 */


bool CcbArenaRankRewardFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbArenaRankRewardFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbArenaRankRewardFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaRankRewardFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbArenaRankRewardFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaRankRewardFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanGet", CCSprite*, this->m_pSpriteCanGet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRankNum", CCLabelTTF*, this->m_pLabelTTFRankNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRankType", CCSprite*, this->m_pSpriteRankType);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGroupName", CCLabelTTF*, this->m_pLabelTTFGroupName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon1", CcbItemIconLayer*, this->m_pLayerIcon1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon2", CcbItemIconLayer*, this->m_pLayerIcon2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon3", CcbItemIconLayer*, this->m_pLayerIcon3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon4", CcbItemIconLayer*, this->m_pLayerIcon4);
    //    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemButton5", CCLayer*, this->m_pLayerItemButton5);
    
    
	return false;
}

bool CcbArenaRankRewardFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaRankRewardFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler CcbArenaRankRewardFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_CCControlHandler CcbArenaRankRewardFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaRankRewardFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    arrIcon.push_back(m_pLayerIcon1);
    arrIcon.push_back(m_pLayerIcon2);
    arrIcon.push_back(m_pLayerIcon3);
    arrIcon.push_back(m_pLayerIcon4);
}


void CcbArenaRankRewardFrameLayer::loadData(uint16 index)
{
    ArenaRewardConfig::STC_ARENA_REWARD_CONFIG* cfg = GET_CONFIG_STC(ArenaRewardConfig, index);
    if (!cfg) {
        return;
    }
    CCString* str = CCString::create("");
    //排名}
    if (cfg->wRankBegin == cfg->wRankEnd)
    {
        str->initWithFormat(GET_STR(Str_dijiming), cfg->wRankBegin);
        
    }
    else if (cfg->wRankBegin < cfg->wRankEnd)
    {
        std::string str1 = GET_STR(Str_dijiming);
        str1 += "~" + str1;
        str->initWithFormat(str1.c_str(), cfg->wRankBegin, cfg->wRankEnd);
    }
    else
    {
        str->initWithFormat(GET_STR(Str_dijiming_later), cfg->wRankBegin);
    }
    m_pLabelTTFRankNum->setString(str->getCString());
    //组别}
    CRole* pRole = CGameSession::GetRole();
    
    if (pRole->GetbyArenaGroup() == index)
    {
        m_pSpriteCanGet->setVisible(true);
    }
    else
    {
        m_pSpriteCanGet->setVisible(false);
    }
    RankRewardConfig::STC_RANKREWARD_CONFIG* pConfig = GET_CONFIG_STC(RankRewardConfig, index);
    if (pConfig)
    {
        m_pLabelTTFGroupName->setString(pConfig->strGroupName.c_str());
    }
    else
    {
        m_pLabelTTFGroupName->setString("");
    }
    
    //组别Icon}
    CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(GET_ARENA_BADGE_PIC(pConfig->wBadge));
    if (pTexture) {
        m_pSpriteRankType->setVisible(true);
        m_pSpriteRankType->setTexture(pTexture);
    }
    else{
        m_pSpriteRankType->setVisible(false);
    }
    //奖励icon}
    std::vector<STC_ITEM_DROP> arrItem;
    STC_ITEM_DROP item;
    //金币}
    item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_COIN;
    item.wCount = cfg->dwMoneyMin;
    item.wHasCount = cfg->dwMoneyMax;
    arrItem.push_back(item);
    //声望}
    item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_REPUTATION;
    item.wCount = cfg->dwReputationMin;
    item.wHasCount = cfg->dwReputationMax;
    arrItem.push_back(item);
    for (int i = 0; i < 5; i++) {
        item.wItemType = cfg->dwItemID[i];
        if (item.wItemType == 0) {
            continue;
        }
        
        item.wCount = cfg->dwItemCount[i];
        item.wHasCount = cfg->dwItemCount[i];
        arrItem.push_back(item);
    }
    
    int count = 0;
    for (int i = 0; i < arrItem.size(); i++) {
        STC_ITEM_DROP itemE = arrItem[i];
        if (itemE.wItemType == 0) {
            continue;
        }
        if (count == arrIcon.size()) {
            break;
        }
        arrIcon[count]->setVisible(true);
        arrIcon[count]->loadIndexData(itemE.wItemType);
        arrIcon[count]->showCntFromTo(itemE.wHasCount, itemE.wHasCount);
        count++;
    }
    for (; count < arrIcon.size(); count++) {
        arrIcon[count]->setVisible(false);
    }
}






