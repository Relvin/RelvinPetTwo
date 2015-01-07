#include "CcbTowerRewardFrameLayer.h"
//#include "CcbManager.h"
#include "CcbItemInfoButtonLayer.h"
#include "ConfigGet.h"
#include "PacketDataMgr.h"
#include "ResourceStringClient.h"

CcbTowerRewardFrameLayer::~CcbTowerRewardFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFloor);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon1);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon2);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon3);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon4);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTowerRewardFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTowerRewardFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTowerRewardFrameLayer", CcbTowerRewardFrameLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/iteminfo_button.ccb]", [ccb/iteminfo_button.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_boxframe.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbTowerRewardFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbTowerRewardFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbTowerRewardFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbTowerRewardFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTowerRewardFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTowerRewardFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFloor", CCLabelTTF*, this->m_pLabelTTFFloor);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon1", CcbItemIconLayer*, this->m_pLayerIcon1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon2", CcbItemIconLayer*, this->m_pLayerIcon2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon3", CcbItemIconLayer*, this->m_pLayerIcon3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon4", CcbItemIconLayer*, this->m_pLayerIcon4);

	return false;
}

bool CcbTowerRewardFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTowerRewardFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTowerRewardFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTowerRewardFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTowerRewardFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbTowerRewardFrameLayer::CreateRewardData(uint16 wIndex)
{
    CcbItemIconLayer* pCcbButton[4];
    pCcbButton[0] = m_pLayerIcon1;
    pCcbButton[1] = m_pLayerIcon2;
    pCcbButton[2] = m_pLayerIcon3;
    pCcbButton[3] = m_pLayerIcon4;
    
    int cnt = 0;

    TowerConfig::STC_TOWER_CONFIG* pConfig = GET_CONFIG_STC(TowerConfig, wIndex);
    if (pConfig)
    {
        for (int i = 0; i < 4; i++)
        {
            if (pConfig->dwRewardID[i] == 0)
            {
                continue;
            }
            pCcbButton[cnt]->setVisible(true);
            pCcbButton[cnt]->loadIndexData(pConfig->dwRewardID[i]);
            pCcbButton[cnt]->showCnt(pConfig->dwRewardCount[i]);
            cnt++;
        }
        
        m_pLabelTTFFloor->setString(CCString::createWithFormat(GET_STR(Str_dijiceng), pConfig->wIndex)->getCString());
    }
    for (; cnt < 4; cnt++) {
        pCcbButton[cnt]->setVisible(false);
    }
}





