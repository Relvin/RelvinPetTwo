#include "CcbInviteFriendFrameLayer.h"
//#include "CcbManager.h"

CcbInviteFriendFrameLayer::~CcbInviteFriendFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon_1);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon_2);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon_3);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon_4);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRewardDesc);
	CC_SAFE_RELEASE_NULL(m_pSpriteFinish);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbInviteFriendFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbInviteFriendFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbInviteFriendFrameLayer", CcbInviteFriendFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/invite_friend_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbInviteFriendFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbInviteFriendFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbInviteFriendFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbInviteFriendFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbInviteFriendFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbInviteFriendFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_1", CcbItemIconLayer*, this->m_pLayerIcon_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_2", CcbItemIconLayer*, this->m_pLayerIcon_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_3", CcbItemIconLayer*, this->m_pLayerIcon_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_4", CcbItemIconLayer*, this->m_pLayerIcon_4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRewardDesc", CCLabelTTF*, this->m_pLabelTTFRewardDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteFinish", CCSprite*, this->m_pSpriteFinish);

	return false;
}

bool CcbInviteFriendFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbInviteFriendFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbInviteFriendFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbInviteFriendFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbInviteFriendFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    
    pNodeItem[0] = m_pLayerIcon_1;
    pNodeItem[1] = m_pLayerIcon_2;
    pNodeItem[2] = m_pLayerIcon_3;
    pNodeItem[3] = m_pLayerIcon_4;
}

void CcbInviteFriendFrameLayer::loadData(INVITE_LIST_SHOW_INFO showInfo)
{
    if (showInfo.info.byStatus == 0)
    {
        m_pSpriteFinish->setVisible(false);
    }
    else
    {
        m_pSpriteFinish->setVisible(true);
    }
    
    
    int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        if (showInfo.config.dwRewardID[i] != 0)
        {
            pNodeItem[cnt]->setVisible(true);
            pNodeItem[cnt]->loadIndexData(showInfo.config.dwRewardID[i]);
            pNodeItem[cnt]->showCnt(showInfo.config.dwRewardCount[i]);
            cnt++;
        }
        
    }//end for (int i = 0; i < 5; i++)
    for (; cnt < 4; cnt++) {
         pNodeItem[cnt]->setVisible(false);
    }
    
    m_pLabelTTFRewardDesc->setString(showInfo.config.strDesc.c_str());
}

void CcbInviteFriendFrameLayer::setClipRect(CCRect rect)
{
    for (int cnt = 0; cnt < 4; cnt++) {
        pNodeItem[cnt]->setClipRect(rect);
    }
}




