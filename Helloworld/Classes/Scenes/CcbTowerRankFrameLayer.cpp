#include "CcbTowerRankFrameLayer.h"
//#include "CcbManager.h"
#include "TowerDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbTowerRankFrameLayer::~CcbTowerRankFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFlood);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRank);
	CC_SAFE_RELEASE_NULL(m_pLayerPetIcon);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTowerRankFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTowerRankFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTowerRankFrameLayer", CcbTowerRankFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_rankframe.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbTowerRankFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbTowerRankFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbTowerRankFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbTowerRankFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTowerRankFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTowerRankFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFlood", CCLabelTTF*, this->m_pLabelTTFFlood);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRank", CCLabelTTF*, this->m_pLabelTTFRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetIcon", CcbPetIcon*, this->m_pLayerPetIcon);

	return false;
}

bool CcbTowerRankFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTowerRankFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTowerRankFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTowerRankFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTowerRankFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}


void CcbTowerRankFrameLayer::loadData(uint16 wIndex)
{
//    vector<TOWER_RANK_INFO> showInfo = g_TowerDataMgr->GetTowerRankList();
    TOWER_RANK_INFO info = g_TowerDataMgr->GetTowerRankList()[wIndex];
    char szTemp[32] = "";
    
    //名次}
    sprintf(szTemp, GET_STR(Str_dijiming), wIndex + 1);
    m_pLabelTTFRank->setString(szTemp);
    
    //宠物队长头像}
    m_pLayerPetIcon->setPetId(info.wLeader);
    m_pLayerPetIcon->setBtnEnable(false);
    
    //名字}
    m_pLabelTTFName->setString(info.strName.c_str());
    
    //层数}
    sprintf(szTemp, GET_STR(Str_dijiceng), info.dwMaxFloor);
    m_pLabelTTFFlood->setString(szTemp);
}






