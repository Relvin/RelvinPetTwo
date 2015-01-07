#include "CcbServerNode.h"
//#include "CcbManager.h"
#include "ServerListCtrl.h"
#include "StartGameLayer.h"
#include "ConfigGet.h"
#include "ResourcePic.h"
#include "MusicCtrl.h"
#include "CCScrollButton.h"

USING_NS_CC;
USING_NS_CC_EXT;


CcbServerNode::~CcbServerNode()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonServer);
	CC_SAFE_RELEASE_NULL(m_pSpriteStatus);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAreaId);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbServerNode( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbServerNode( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbServerNode", CcbServerNodeLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/server_node.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbServerNode::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbServerNode::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbServerNode::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbServerNode::onExit()
{
	CCLayer::onExit();
}

void CcbServerNode::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbServerNode::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonServer", CCScrollButton*, this->m_pControlButtonServer);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStatus", CCSprite*, this->m_pSpriteStatus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAreaId", CCLabelTTF*, this->m_pLabelTTFAreaId);
	return false;
}

bool CcbServerNode::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbServerNode::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbServerNode::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbServerNode::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonServer", CcbServerNode::onPressControlButtonServer);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbServerNode::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonServer->setTouchPriority(kCCMenuHandlerPriority-1);
}

// 3个最近的服务器 idx分别为 100+对应的idx}
void CcbServerNode::setNodeData(int idx)
{
    int kIdx = idx;
    if (idx >= 100) {
        kIdx -= 100;
    }
    
    if (kIdx >= ServerListCtrl::Get()->getAreaNum()) {
        m_pSpriteStatus->setVisible(false);
        m_pControlButtonServer->setVisible(false);
        m_pLabelTTFAreaId->setVisible(false);
        return;
    }
    
    m_pControlButtonServer->setTag(idx);
    uint8 byStatus = ServerListCtrl::Get()->getAreaStatus(kIdx);
    
    CCTexture2D* tex;
    if (byStatus == E_SERVER_STATUS_MAINTAIN) {
        tex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(PIC_server_stop));
    } else if (byStatus == E_SERVER_STATUS_NEW) {
        tex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(PIC_server_new));
    } else if (byStatus == E_SERVER_STATUS_HOT) {
        tex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(PIC_server_hot));
    } else {
        tex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(PIC_server_stop));
    }
    m_pSpriteStatus->setTexture(tex);
    
    char szBuf[8];
    sprintf(szBuf, "%d", ServerListCtrl::Get()->getAreaId(kIdx));
    m_pLabelTTFAreaId->setString(szBuf);
#ifdef NDEBUG
    m_pLabelTTFAreaId->setVisible(false);
#endif
    
    CCString* cstrName = CCString::createWithFormat("%s", ServerListCtrl::Get()->getAreaName(kIdx));
    m_pControlButtonServer->setTitleForState(cstrName, CCControlStateNormal);
}

void CcbServerNode::onPressControlButtonServer(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    int tag = m_pControlButtonServer->getTag();
    if (tag >= 100) {
        tag -= 100;
    }

    StartGameLayer::GetCurLayer()->setCurAreaId(tag);
}




