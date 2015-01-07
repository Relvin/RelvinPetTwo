#include "CcbInviteFriendLayer.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "CcbInviteFriendFrameLayer.h"
#include "Role.h"
#include "ConfigGet.h"
#include "EnumDefines.h"
#include "ResourceStringClient.h"
#include "FlyTextLayer.h"
#include "UISupport.h"

CcbInviteFriendLayer::~CcbInviteFriendLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFInviter);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFText2);
	CC_SAFE_RELEASE_NULL(m_pNodeInviteInfo);
	CC_SAFE_RELEASE_NULL(m_pControlButtonConfirm);
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteEnterID);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFText1);
	CC_SAFE_RELEASE_NULL(m_pNodeEnterInviter);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBeInvited);
	CC_SAFE_RELEASE_NULL(m_pControlButtonInvite);
	CC_SAFE_RELEASE_NULL(m_pLayerView);
	CC_SAFE_RELEASE_NULL(m_pNodeViewParent);
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteNum);
	CC_SAFE_RELEASE_NULL(m_pScale9SpritePlayerID);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFInviteCount);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPlayerID);
    CC_SAFE_RELEASE_NULL(m_tableView);
    CC_SAFE_RELEASE_NULL(m_pEditBoxEnterInviteID);
    CC_SAFE_RELEASE_NULL(m_pSpriteDown);
    CC_SAFE_RELEASE_NULL(m_pLayerUp);
    
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbInviteFriendLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbInviteFriendLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbInviteFriendLayer", CcbInviteFriendLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/invite_friend.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbInviteFriendLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_ShowType = 1;
	return true;
}

void CcbInviteFriendLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
}

void CcbInviteFriendLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    m_tableView->reloadData();
}

void CcbInviteFriendLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
}

void CcbInviteFriendLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbInviteFriendLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFInviter", CCLabelTTF*, this->m_pLabelTTFInviter);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText2", CCLabelTTF*, this->m_pLabelTTFText2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeInviteInfo", CCNode*, this->m_pNodeInviteInfo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonConfirm", CCControlButton*, this->m_pControlButtonConfirm);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteEnterID", CCScale9Sprite*, this->m_pScale9SpriteEnterID);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText1", CCLabelTTF*, this->m_pLabelTTFText1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEnterInviter", CCNode*, this->m_pNodeEnterInviter);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBeInvited", CCControlButton*, this->m_pControlButtonBeInvited);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonInvite", CCControlButton*, this->m_pControlButtonInvite);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerView", CCLayer*, this->m_pLayerView);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeViewParent", CCNode*, this->m_pNodeViewParent);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteNum", CCScale9Sprite*, this->m_pScale9SpriteNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpritePlayerID", CCScale9Sprite*, this->m_pScale9SpritePlayerID);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFInviteCount", CCLabelTTF*, this->m_pLabelTTFInviteCount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPlayerID", CCLabelTTF*, this->m_pLabelTTFPlayerID);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDown", CCSprite*, this->m_pSpriteDown);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerUp", CCLayer*, this->m_pLayerUp);

	return false;
}

bool CcbInviteFriendLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbInviteFriendLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbInviteFriendLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbInviteFriendLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonConfirm", CcbInviteFriendLayer::onPressControlButtonConfirm);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBeInvited", CcbInviteFriendLayer::onPressControlButtonBeInvited);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonInvite", CcbInviteFriendLayer::onPressControlButtonInvite);

	return NULL;
}

void CcbInviteFriendLayer::InitData()
{
    CRole* pRole = CGameSession::GetRole();
    char szTemp[32] = "";
    //玩家自己的ID}
    sprintf(szTemp, "%u", pRole->GetdwAccountId());
    m_pLabelTTFPlayerID->setString(szTemp);

    INVITE_USER_INFO InviteUserInfo = FriendCtrl::Get()->GetInviteUserInfo();
    //已邀请人数}
    sprintf(szTemp, "%u", InviteUserInfo.dwInviteCount);
    m_pLabelTTFInviteCount->setString(szTemp);
    //是否有邀请人}
    if (InviteUserInfo.dwInviteID == 0)
    {
        m_pNodeEnterInviter->setVisible(true);
        m_pNodeInviteInfo->setVisible(false);
    }
    else
    {
        m_pNodeEnterInviter->setVisible(false);
        m_pNodeInviteInfo->setVisible(true);
        
        //邀请人名字}
        m_pLabelTTFInviter->setString(InviteUserInfo.strName.c_str());
    }
    
    m_vecShowList[0].clear();
    m_vecShowList[1].clear();
   
    //邀请人列表}
    map<uint32, INVITE_CONFIG> mapConfig;
    map<uint32, INVITE_CONFIG>::iterator iter;
    
    mapConfig = GET_CONFIG_MAP(InviteConfig);
    for (iter = mapConfig.begin(); iter != mapConfig.end(); iter++)
    {
        INVITE_LIST_SHOW_INFO temp;
        temp.info.dwRewardIndex = iter->first;
        temp.info.byStatus = FriendCtrl::Get()->GetInviteListInfobyIndex(iter->first).byStatus;
        
        temp.config.dwIndex = iter->second.dwIndex;
        temp.config.strDesc = iter->second.strDesc;
        for (int i = 0; i < 5; i++)
        {
            temp.config.dwRewardID[i] = iter->second.dwRewardID[i];
            temp.config.dwRewardCount[i] = iter->second.dwRewardCount[i];
        }
        m_vecShowList[0].push_back(temp);
    }
    
    //被邀请人列表}
    map<uint32, INVITEE_CONFIG> mapConfig2;
    map<uint32, INVITEE_CONFIG>::iterator iter2;

    mapConfig2 = GET_CONFIG_MAP(InviteeConfig);
    for (iter2 = mapConfig2.begin(); iter2 != mapConfig2.end(); iter2++)
    {
        INVITE_LIST_SHOW_INFO temp;
        temp.info.dwRewardIndex = iter2->first;
        temp.info.byStatus = FriendCtrl::Get()->GetInviteeListInfobyIndex(iter2->first).byStatus;
        
        temp.config.dwIndex = iter2->second.dwIndex;
        temp.config.strDesc = iter2->second.strDesc;
        for (int i = 0; i < 5; i++)
        {
            temp.config.dwRewardID[i] = iter2->second.dwRewardID[i];
            temp.config.dwRewardCount[i] = iter2->second.dwRewardCount[i];
        }
        m_vecShowList[1].push_back(temp);
    }
    
    m_pControlButtonInvite->setEnabled(false);
    m_pControlButtonBeInvited->setEnabled(true);
}

// Inhert CCNodeLoaderListener
void CcbInviteFriendLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    InitData();
    
    m_pLayerView->setContentSize(CCSizeMake(getWidth(m_pLayerView), getBottom(m_pLayerUp) - getTop(m_pSpriteDown) + 5));
    
    //Create TableView
    m_tableView = CCTableView::create(this, m_pLayerView->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->retain();
    m_tableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    
    m_pLayerView->addChild(m_tableView);
    
    //Create EditBox
    CCSize EditBoxSize = m_pScale9SpriteEnterID->getContentSize();
    CCPoint EditBoxPos = m_pScale9SpriteEnterID->getPosition();
    m_pScale9SpriteEnterID->removeFromParent();
    
    m_pEditBoxEnterInviteID = CCEditBox::create(EditBoxSize, m_pScale9SpriteEnterID);
    m_pEditBoxEnterInviteID->setInputMode(kEditBoxInputModeNumeric);
    m_pEditBoxEnterInviteID->setPosition(EditBoxPos);
    m_pEditBoxEnterInviteID->setMaxLength(12);
    m_pEditBoxEnterInviteID->setPlaceHolder(GET_STR(Str_input_inviter_id));
    m_pEditBoxEnterInviteID->setText("");
    
    m_pEditBoxEnterInviteID->retain();
    m_pNodeEnterInviter->addChild(m_pEditBoxEnterInviteID);
    m_pEditBoxEnterInviteID->setDelegate(this);
}

CCSize CcbInviteFriendLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerView), 96 + 5);
}

CCTableViewCell* CcbInviteFriendLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbInviteFriendFrameLayer(this);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->setPosition(getWidth(m_pLayerView)*0.5, 0);
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbInviteFriendFrameLayer *pNode = (CcbInviteFriendFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        INVITE_LIST_SHOW_INFO showInfo = m_vecShowList[m_ShowType-1][idx];
        pNode->loadData(showInfo);
    }//end if (pNode)
    
    return pCell;
}

unsigned int CcbInviteFriendLayer::numberOfCellsInTableView(CCTableView *table)
{
    if (m_ShowType == 1)
    {
        return m_vecShowList[0].size();
    }
    else if (m_ShowType == 2)
    {
        return m_vecShowList[1].size();
    }
    return 0;
}

void CcbInviteFriendLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox * editbox)
{
    
}

void CcbInviteFriendLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox * editbox)
{
    
}

void CcbInviteFriendLayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    
}

void CcbInviteFriendLayer::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
    char szTextNum[32] = "";
    strncpy(szTextNum, m_pEditBoxEnterInviteID->getText(), 20);
    
    for (int i = 0; i < 20; i++)
    {
        if (szTextNum[i] == '\0')
        {
            return;
        }
        
        if (szTextNum[i] < '0' || szTextNum[i] > '9')
        {
//            CCMessageBox("qqqqqqqqqqqqq请输入有效ID", "输入错误");
            FlyTextLayer::showTips(GET_STR(Str_input_useful_id));
            return;
        }
    }
}

void CcbInviteFriendLayer::RefeashLayer()
{
    InitData();
    CCPoint offpos = m_tableView->getContentOffset();
    m_tableView->reloadData();
    m_tableView->setContentOffset(offpos);
}
    

void CcbInviteFriendLayer::onPressControlButtonConfirm(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    char szTempID[32];
    strncpy(szTempID, m_pEditBoxEnterInviteID->getText(), 20);
    
    if (strcmp(szTempID, "") == 0)
    {
//        CCMessageBox("qqqqqqqqqqqqq请输入邀请人ID", "提示");
        FlyTextLayer::showTips(GET_STR(Str_input_inviter_id));
        return;
    }
    uint32 InviteID = atoll(szTempID);
    CGameSession::SendInviteID(InviteID);
}

void CcbInviteFriendLayer::onPressControlButtonBeInvited(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    m_ShowType = 2;
    m_pControlButtonBeInvited->setEnabled(false);
    m_pControlButtonInvite->setEnabled(true);
    m_tableView->reloadData();
}

void CcbInviteFriendLayer::onPressControlButtonInvite(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    m_ShowType = 1;
    m_pControlButtonBeInvited->setEnabled(true);
    m_pControlButtonInvite->setEnabled(false);
    m_tableView->reloadData();
}







