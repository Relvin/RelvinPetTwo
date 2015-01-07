#include "CcbGmUserLayer.h"
//#include "CcbManager.h"
#include "Role.h"
#include "GameSession.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbGmUserLayer::~CcbGmUserLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerInsert_Lv);
	CC_SAFE_RELEASE_NULL(m_pLayerInsert_Coin);
	CC_SAFE_RELEASE_NULL(m_pLayerInsert_Dollor);
	CC_SAFE_RELEASE_NULL(m_pLayerInsert_Vip);
	CC_SAFE_RELEASE_NULL(m_pLayerInsert_Energy);
	CC_SAFE_RELEASE_NULL(m_pLayerInsert_Arena);
    CC_SAFE_RELEASE_NULL(m_pLayerInsert_Soul);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbGmUserLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbGmUserLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGmUserLayer", CcbGmUserLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/gm_insert.ccb]", [ccb/gm_insert.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gm_user.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbGmUserLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbGmUserLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbGmUserLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbGmUserLayer::onExit()
{
	CCLayer::onExit();
}

void CcbGmUserLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbGmUserLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInsert_Lv", CcbGmInsertLayer*, this->m_pLayerInsert_Lv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInsert_Coin", CcbGmInsertLayer*, this->m_pLayerInsert_Coin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInsert_Dollor", CcbGmInsertLayer*, this->m_pLayerInsert_Dollor);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInsert_Vip", CcbGmInsertLayer*, this->m_pLayerInsert_Vip);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInsert_Energy", CcbGmInsertLayer*, this->m_pLayerInsert_Energy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInsert_Arena", CcbGmInsertLayer*, this->m_pLayerInsert_Arena);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInsert_Soul", CcbGmInsertLayer*, this->m_pLayerInsert_Soul);
	return false;
}

bool CcbGmUserLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbGmUserLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbGmUserLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbGmUserLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGmUserLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbGmUserLayer::loadData()
{
    CRole *pRole = CGameSession::GetRole();
    m_pLayerInsert_Lv->setNum(pRole->GetwRoleLv());
    m_pLayerInsert_Coin->setNum(pRole->GetdwCoin());
    m_pLayerInsert_Dollor->setNum(pRole->GetdwDollar());
    m_pLayerInsert_Vip->setNum(pRole->GetbyVipLv());
    m_pLayerInsert_Energy->setNum(MAX(pRole->GetdwEnergy(), pRole->GetdwEnergyMax()));
    m_pLayerInsert_Arena->setNum(pRole->GetbyArenaUseCnt());
    m_pLayerInsert_Soul->setNum(pRole->GetdwResFarmNum());
}

CCString* CcbGmUserLayer::getGmString()
{
    CCString *str = CCString::create("");
//    CRole *pRole = CGameSession::GetRole();
    uint16 lv = m_pLayerInsert_Lv->getNum();
    uint32 coin = m_pLayerInsert_Coin->getNum();
    uint32 dollor = m_pLayerInsert_Dollor->getNum();
    uint16 vip = m_pLayerInsert_Vip->getNum();
    uint16 energy = m_pLayerInsert_Energy->getNum();
    uint16 arena = m_pLayerInsert_Arena->getNum();
    uint32 soul = m_pLayerInsert_Soul->getNum();
    str->initWithFormat("chgroleinfo %d %d %d %d %d %d %d", lv, vip, dollor, coin, energy, arena, soul);
    return str;
}





