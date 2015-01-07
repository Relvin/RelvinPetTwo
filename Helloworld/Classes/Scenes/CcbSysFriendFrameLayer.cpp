#include "CcbSysFriendFrameLayer.h"
#include "BackCtrl.h"
#include "FriendCtrl.h"
#include "GameSession.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "Role.h"
#include "SystemNoticeDataMgr.h"
#include "CcbManager.h"
#include "Account.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbSysFriendFrameLayer::~CcbSysFriendFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonNode);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    CC_SAFE_RELEASE_NULL(m_pSpriteTip);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbSysFriendFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbSysFriendFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbSysFriendFrameLayer", CcbSysFriendFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_sys_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbSysFriendFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbSysFriendFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbSysFriendFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbSysFriendFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbSysFriendFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbSysFriendFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonNode", CCScrollButton*, this->m_pControlButtonNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTip", CCSprite*, this->m_pSpriteTip);
	return false;
}

bool CcbSysFriendFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbSysFriendFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbSysFriendFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbSysFriendFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonNode", CcbSysFriendFrameLayer::onPressControlButtonNode);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbSysFriendFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pSpriteTip->setVisible(false);
}

/*
 账号绑定代码：
 CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
 CGameSession::SendBindingRequest();
 */

void CcbSysFriendFrameLayer::onPressControlButtonNode(CCObject* pSender, CCControlEvent event)
{
    CCScrollButton* pButton = dynamic_cast<CCScrollButton*>(pSender);
    if (!pButton) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
	switch (pButton->getTag()) {
        case kFriendListTag:
            FriendCtrl::Get()->setFromType(FriendCtrl::kFromFriendList);
            BackCtrl::InsertNextScene(kFriendScene);
            break;
        case kFriendAddTag:
//            BackCtrl::InsertNextScene(kFindFriendScene);
            break;
        case kFriendMailTag:
            FriendCtrl::Get()->setFromType(FriendCtrl::kFromTotalMail);
            BackCtrl::InsertNextScene(kFriendScene);
            m_pSpriteTip->setVisible(false);
            CGameSession::GetRole()->SetbyNotiFriend(false);
            break;
        case kFriendRequst:
            CGameSession::SendEnterInviteSceneRequest();
            break;
        case kSettingTujian:
            BackCtrl::InsertNextScene(kPetTujian);
            break;
        case kSettingAnnounce:
            if (g_SystemNoticeDataMgr->GetSystemNoticeMap().size() != 0)
            {
                CCDirector::sharedDirector()->getRunningScene()->addChild(CcbManager::sharedManager()->LoadCcbSystemNoticeLayer(), 99, 3124);
            }
            else
            {
                CGameSession::SendNoticeGet();
            }
            break;
        case kSettingInformation:
#ifdef VERSION_I4
            Account::shareInstance()->center();
#endif
            break;
        default:
            break;
    }
}

void CcbSysFriendFrameLayer::setNodeData(std::string strName, int tag)
{
    m_pLabelTTFName->setString(strName.c_str());
    m_pControlButtonNode->setTag(tag);
    
    if (tag == kFriendMailTag && CGameSession::GetRole()->GetbyNotiFriend()) {
        m_pSpriteTip->setVisible(true);
    }
}






