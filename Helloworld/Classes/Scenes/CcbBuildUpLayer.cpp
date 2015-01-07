#include "CcbBuildUpLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "EnumDefines.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbBuildUpLayer* CcbBuildUpLayer::m_shared;

CcbBuildUpLayer::~CcbBuildUpLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonUpFarm);
	CC_SAFE_RELEASE_NULL(m_pSpriteFarm);
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontFarmLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFarmCoin);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFarmCH);
	CC_SAFE_RELEASE_NULL(m_pControlButtonMine);
	CC_SAFE_RELEASE_NULL(m_pSpriteMine);
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontMineLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMineCoin);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMineCH);
	CC_SAFE_RELEASE_NULL(m_pControlButtonTree);
	CC_SAFE_RELEASE_NULL(m_pSpriteTree);
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontTreeLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTreeCoin);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTreeCH);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRiver);
	CC_SAFE_RELEASE_NULL(m_pSpriteRiver);
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontRiverLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRiverCoin);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRiverCH);
    m_shared = NULL;
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbBuildUpLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbBuildUpLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbBuildUpLayer", CcbBuildUpLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/build_up.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbBuildUpLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_shared = this;
	return true;
}

CcbBuildUpLayer* CcbBuildUpLayer::GetCurLayer()
{
    return m_shared;
}

void CcbBuildUpLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbBuildUpLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbBuildUpLayer::onExit()
{
	CCLayer::onExit();
}

void CcbBuildUpLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbBuildUpLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonUpFarm", CCControlButton*, this->m_pControlButtonUpFarm);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFarm", CCSprite*, this->m_pSpriteFarm);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontFarmLv", CCLabelBMFont*, this->m_pLabelBMFontFarmLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFarmCoin", CCLabelTTF*, this->m_pLabelTTFFarmCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFarmCH", CCLabelTTF*, this->m_pLabelTTFFarmCH);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMine", CCControlButton*, this->m_pControlButtonMine);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMine", CCSprite*, this->m_pSpriteMine);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontMineLv", CCLabelBMFont*, this->m_pLabelBMFontMineLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMineCoin", CCLabelTTF*, this->m_pLabelTTFMineCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMineCH", CCLabelTTF*, this->m_pLabelTTFMineCH);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTree", CCControlButton*, this->m_pControlButtonTree);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTree", CCSprite*, this->m_pSpriteTree);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontTreeLv", CCLabelBMFont*, this->m_pLabelBMFontTreeLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTreeCoin", CCLabelTTF*, this->m_pLabelTTFTreeCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTreeCH", CCLabelTTF*, this->m_pLabelTTFTreeCH);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRiver", CCControlButton*, this->m_pControlButtonRiver);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRiver", CCSprite*, this->m_pSpriteRiver);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontRiverLv", CCLabelBMFont*, this->m_pLabelBMFontRiverLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRiverCoin", CCLabelTTF*, this->m_pLabelTTFRiverCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRiverCH", CCLabelTTF*, this->m_pLabelTTFRiverCH);

	return false;
}

bool CcbBuildUpLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbBuildUpLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbBuildUpLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbBuildUpLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFarm", CcbBuildUpLayer::onPressControlButtonFarm);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMine", CcbBuildUpLayer::onPressControlButtonMine);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTree", CcbBuildUpLayer::onPressControlButtonTree);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRiver", CcbBuildUpLayer::onPressControlButtonRiver);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbBuildUpLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
//    m_pLabelTTFFarmCoin->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFFarmCH->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFMineCoin->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFMineCH->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFTreeCoin->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFTreeCH->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFRiverCoin->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFRiverCH->setStrokeForLabelTTF(ccBLACK, 1.0);
    UpdateInfo( CBuildUpDataMgr::Get()->getBuildingMap() );
}



void CcbBuildUpLayer::onPressControlButtonFarm(CCObject* pSender, CCControlEvent event)
{
    onPressUpgrade(E_RES_FARM_ROB_TYPE_FARMRES);
}

void CcbBuildUpLayer::onPressControlButtonMine(CCObject* pSender, CCControlEvent event)
{
    onPressUpgrade(E_RES_FARM_ROB_TYPE_COIN);
}

void CcbBuildUpLayer::onPressControlButtonTree(CCObject* pSender, CCControlEvent event)
{
	onPressUpgrade(E_RES_BUILD_TYPE_FARMRES);
}

void CcbBuildUpLayer::onPressControlButtonRiver(CCObject* pSender, CCControlEvent event)
{
	onPressUpgrade(E_RES_BUILD_TYPE_COIN);
}


void CcbBuildUpLayer::onPressUpgrade(uint8 byType)
{
    CGameSession::SendUpgradeBuild(byType);
}

void CcbBuildUpLayer::UpdateInfo(CBuildUpDataMgr::MAP_INFO map_build)
{
    CBuildUpDataMgr::MAP_INFO::iterator iit;
    iit = map_build.find(E_RES_FARM_ROB_TYPE_FARMRES);
    if (iit == map_build.end()) {
        CCMessageBox("Farm Data Null", "Error");
        return;
    }
    m_pLabelBMFontFarmLv->setString(CCString::createWithFormat("%d", iit->second.wBuildLv)->getCString());
    m_pLabelTTFFarmCoin->setString(CCString::createWithFormat("%d", iit->second.dwMoney)->getCString());
    m_pLabelTTFFarmCH->setString(CCString::createWithFormat("%d", iit->second.dwHun)->getCString());
    
    iit = map_build.find(E_RES_FARM_ROB_TYPE_COIN);
    if (iit == map_build.end()) {
        CCMessageBox("Mine Data Null", "Error");
        return;
    }
    m_pLabelBMFontMineLv->setString(CCString::createWithFormat("%d", iit->second.wBuildLv)->getCString());
    m_pLabelTTFMineCoin->setString(CCString::createWithFormat("%d", iit->second.dwMoney)->getCString());
    m_pLabelTTFMineCH->setString(CCString::createWithFormat("%d", iit->second.dwHun)->getCString());
    
    iit = map_build.find(E_RES_BUILD_TYPE_FARMRES);
    if (iit == map_build.end()) {
        CCMessageBox("Tree Data Null", "Error");
        return;
    }
    m_pLabelBMFontTreeLv->setString(CCString::createWithFormat("%d", iit->second.wBuildLv)->getCString());
    m_pLabelTTFTreeCoin->setString(CCString::createWithFormat("%d", iit->second.dwMoney)->getCString());
    m_pLabelTTFTreeCH->setString(CCString::createWithFormat("%d", iit->second.dwHun)->getCString());
    
    iit = map_build.find(E_RES_BUILD_TYPE_COIN);
    if (iit == map_build.end()) {
        CCMessageBox("River Data Null", "Error");
        return;
    }
    m_pLabelBMFontRiverLv->setString(CCString::createWithFormat("%d", iit->second.wBuildLv)->getCString());
    m_pLabelTTFRiverCoin->setString(CCString::createWithFormat("%d", iit->second.dwMoney)->getCString());
    m_pLabelTTFRiverCH->setString(CCString::createWithFormat("%d", iit->second.dwHun)->getCString());
}


