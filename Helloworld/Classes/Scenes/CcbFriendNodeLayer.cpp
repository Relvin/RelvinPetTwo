#include "CcbFriendNodeLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "CcbFriendLayer.h"
#include "PetCtrl.h"
#include "BackCtrl.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "CcbPetIcon.h"
#include "PetLoadingLayer.h"
#include "CCScrollButton.h"
#include "MusicCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFriendNodeLayer::~CcbFriendNodeLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerHead);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFGroup);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAccept);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReject);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTitle);
}

//-- copy this to CcbManager 
/*
//CcbManager.h


//CcbManager.cpp

*/


bool CcbFriendNodeLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbFriendNodeLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbFriendNodeLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFriendNodeLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendNodeLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendNodeLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHead", CcbPetIcon*, this->m_pLayerHead);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGroup", CCLabelTTF*, this->m_pLabelTTFGroup);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAccept", CCScrollButton*, this->m_pControlButtonAccept);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReject", CCScrollButton*, this->m_pControlButtonReject);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSelf", CCScrollButton*, this->m_pControlButtonSelf);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTitle", CCLabelTTF*, this->m_pLabelTTFTitle);
	return false;
}

bool CcbFriendNodeLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFriendNodeLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFriendNodeLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFriendNodeLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSelf", CcbFriendNodeLayer::onPressControlButtonSelf);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAccept", CcbFriendNodeLayer::onPressControlButtonAccept);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReject", CcbFriendNodeLayer::onPressControlButtonReject);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFriendNodeLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbFriendNodeLayer::onPressControlButtonSelf(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if ( FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendList ) {
        FriendCtrl::Get()->setUserId(m_dwCurUserId);
        BackCtrl::InsertNextScene(kFriendMailScene);
    } else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromTotalMail) {
        if (m_byMailType == FriendCtrl::kFriendMsg) {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendReadMailInfo(m_dwMailId);
        }
    }
}

void CcbFriendNodeLayer::onPressControlButtonAccept(cocos2d::CCObject *pSender, CCControlEvent event)
{

    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFindFriend) {
        // 申请加好友}
        CGameSession::SendReqApplyFriend(m_dwCurUserId);
    }
    else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromTotalMail) {
        // 同意其他人的申请}
        if (m_byMailType == FriendCtrl::kFriendApply) {
            CGameSession::SendAgreeFriendApply(m_dwFriendId);
        }
    }
}

void CcbFriendNodeLayer::onPressControlButtonReject(cocos2d::CCObject *pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));

    if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendList) {
        SystemMessage::showSystemMessage(1, NULL, GET_STR(Str_sure_del_friend), this, false, 1);
    }
    else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromTotalMail) {
        if (m_byMailType == FriendCtrl::kFriendApply) {
            CGameSession::SendDisagreeFriendApply(m_dwFriendId);
//            FriendCtrl::Get()->removeUserWithRoleId(m_dwFriendId);
            FriendCtrl::Get()->removeDzhWithId(m_dwFriendId);
        } else if (m_byMailType == FriendCtrl::kFriendMsg) {
            
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendReadMailInfo(m_dwMailId);
        }
    } else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFindFriend) {
        this->setVisible(false);
    }

}

#pragma mark Private Method
void CcbFriendNodeLayer::setGroupString(uint8 byGroupId)
{
    // 竞技场分组}
    RankRewardConfig::STC_RANKREWARD_CONFIG* pConfig = GET_CONFIG_STC(RankRewardConfig, byGroupId);
    if (pConfig) {
        m_pLabelTTFGroup->setString(pConfig->strGroupName.c_str());
    }
}

void CcbFriendNodeLayer::setLvString(uint16 wRoleLv)
{
    CCString* strLv = CCString::createWithFormat("%d", wRoleLv);
    m_pLabelTTFLv->setString(strLv->getCString());
}

void CcbFriendNodeLayer::setHeadPicture(uint16 wLeadId)
{
    m_pLayerHead->setPetId(wLeadId);
    m_pLayerHead->loadData();
    m_pLayerHead->setAccountId(m_dwCurUserId);
    if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendList) {
        m_pLayerHead->setBtnEnable(true);
    } else {
        m_pLayerHead->setBtnEnable(false);
    }
}

#pragma mark Public Method
void CcbFriendNodeLayer::setNode(FriendCtrl::STC_USER_INFO nodeInfo)
{
    if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendList) {
        m_pControlButtonAccept->setVisible(false);
        m_pControlButtonReject->setVisible(true);
        m_pControlButtonReject->setTitleForState(CCString::create(GET_STR(Str_delete)), CCControlStateNormal);
        m_pLabelTTFTitle->setVisible(false);
    }
    else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFindFriend) {
        //TODO: 修改“确定”按钮图片为“申请”}
        m_pControlButtonAccept->setVisible(true);
        m_pControlButtonAccept->setTitleForState(CCString::create(GET_STR(Str_apply)), CCControlStateNormal);
        m_pControlButtonReject->setVisible(true);
        m_pControlButtonReject->setTitleForState(CCString::create(GET_STR(Str_cancel)), CCControlStateNormal);
        m_pLabelTTFTitle->setVisible(false);
    }
    
    m_wLeaderId = nodeInfo.wLeaderId;
    m_dwCurUserId = nodeInfo.dwRoleId;
    
    m_pLabelTTFName->setString(nodeInfo.strName.c_str());
    
    setGroupString(nodeInfo.byGroupId);
    setLvString(nodeInfo.wRoleLv);
    setHeadPicture(nodeInfo.wLeaderId);
}

void CcbFriendNodeLayer::setMsgInfo(FriendCtrl::STC_FRIEND_MAIL sMail, uint8 byType)
{
    if (byType == FriendCtrl::kFriendMsg) {
        // 好友邮件}
        m_byMailType = FriendCtrl::kFriendMsg;
        
        m_pControlButtonAccept->setVisible(false);
        m_pControlButtonReject->setVisible(true);
        m_pControlButtonReject->setTitleForState(CCString::create(GET_STR(Str_read)), CCControlStateNormal);
        
        m_dwMailId = sMail.dwIndex;
        m_pLabelTTFTitle->setString(sMail.strTitle.c_str());
        
    } else if (byType == FriendCtrl::kFriendApply) {
        m_byMailType = FriendCtrl::kFriendApply;
        
        m_pControlButtonAccept->setVisible(true);
        m_pControlButtonAccept->setTitleForState(CCString::create(GET_STR(Str_accept)), CCControlStateNormal);
        m_pControlButtonReject->setVisible(true);
        m_pControlButtonReject->setTitleForState(CCString::create(GET_STR(Str_reject)), CCControlStateNormal);
        
        m_dwFriendId = sMail.dwIndex;
        m_pLabelTTFTitle->setString(GET_STR(Str_friend_apply));
    }
    m_pLabelTTFName->setString(sMail.strSendName.c_str());
    setGroupString(sMail.byArenaGroupId);
    setLvString(sMail.wRoleLv);
    setHeadPicture(sMail.wLeaderPetId);
}


#pragma mark SystemMessageProtocol
void CcbFriendNodeLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    CGameSession::SendDelFriend(m_dwCurUserId);
}



