#include "CcbChatLayer.h"
#include "CcbManager.h"
#include "ReRichText.h"
#include "Defines.h"

#include "UISupport.h"
#include "GameSession.h"
#include "EnumDefines.h"
#include "ResourceDefine.h"
#include "Role.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "CcbGMLayer.h"
#include "MusicCtrl.h"
#include "BackCtrl.h"
#include "FlyTextLayer.h"
#include "ResourcePic.h"

#include "CcbChatTalkBoardLayer.h"

CcbChatLayer* CcbChatLayer::m_shared = NULL;

const int Chat_Touch_Priority = kCCMenuHandlerPriority;

CcbChatLayer::~CcbChatLayer()
{
    
	CC_SAFE_RELEASE_NULL(m_pLayerChatRoom);
	CC_SAFE_RELEASE_NULL(m_pControlButtonSent);
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteText);
	CC_SAFE_RELEASE_NULL(m_pControlButtonSmilies);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pControlButtonWorld);
    CC_SAFE_RELEASE_NULL(m_pControlButtonPersonal);
    CC_SAFE_RELEASE_NULL(m_pControlButtonAlliance);
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteInputID);
    CC_SAFE_RELEASE_NULL(m_pNodePersonal);

    CC_SAFE_RELEASE_NULL(m_pLayerDown);
    CC_SAFE_RELEASE_NULL(m_pNodeBg);
}


bool CcbChatLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    cc4WorldChannel = ccc4(255, 0, 0, 255);
    cc4LeagueChannel = ccc4(200, 100, 50, 255);
    cc4Name = ccc4(0xF7, 0xE4, 0x02, 255);
    cc4Text = ccc4(255, 255, 255, 255);
    
    setTouchEnabled(true);
    
	return true;
}

void CcbChatLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_shared = this;
}

void CcbChatLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbChatLayer::onExit()
{
	CCLayer::onExit();
    m_shared = NULL;
}

void CcbChatLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbChatLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerChatRoom",           CCLayer*,           this->m_pLayerChatRoom);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSent",       CCControlButton*,   this->m_pControlButtonSent);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteText",        CCScale9Sprite*,    this->m_pScale9SpriteText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSmilies",    CCControlButton*,   this->m_pControlButtonSmilies);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose",      CCControlButton*,   this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonWorld",      CCControlButton*,   this->m_pControlButtonWorld);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPersonal",   CCControlButton*,   this->m_pControlButtonPersonal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAlliance",   CCControlButton*,   this->m_pControlButtonAlliance);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteInputID",     CCScale9Sprite*,    this->m_pScale9SpriteInputID);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePersonal",            CCNode*,            this->m_pNodePersonal);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDown",               CCLayer*,           this->m_pLayerDown);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeBg",                  CCNode*,            this->m_pNodeBg);
	return false;
}

bool CcbChatLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbChatLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler CcbChatLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_CCControlHandler CcbChatLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSent", CcbChatLayer::onPressControlButtonSent);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSmilies", CcbChatLayer::onPressControlButtonSmilies);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonWorld", CcbChatLayer::onPressControlButtonWorld);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonPersonal", CcbChatLayer::onPressControlButtonPersonal);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAlliance", CcbChatLayer::onPressControlButtonAlliance);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbChatLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbChatLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}

    // 聊天记录显示scroll框
    m_dwTargetId = 0;
    m_strName = "";
    
    CCSize viewSize;// = m_pLayerChatRoom->getContentSize();;
    tablePos = m_pLayerChatRoom->getPosition();

    float fUp = m_pControlButtonWorld->getParent()->convertToWorldSpace(m_pControlButtonWorld->getPosition()).y;
    float fDown = m_pLayerChatRoom->getParent()->convertToWorldSpace(m_pLayerChatRoom->getPosition()).y;
    viewSize = CCSizeMake(m_pLayerChatRoom->getContentSize().width, fUp - fDown);
    
    m_pTableMsg = CCTableView::create(this, viewSize);
    m_pTableMsg->setDirection( kCCScrollViewDirectionVertical );
    m_pTableMsg->setVerticalFillOrder( kCCTableViewFillTopDown );
    m_pTableMsg->ignoreAnchorPointForPosition(false);
    m_pTableMsg->setAnchorPoint(ccp(0.5, 0));
    m_pTableMsg->setPosition(tablePos);
    
    m_pNodeBg->addChild(m_pTableMsg);
    
    CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->addSpriteFramesWithFile(GET_PIC(Pic_face_plist), GET_PIC(Pic_face_pvr_ccz));

    showEditBox();
    
    m_pControlButtonWorld->setTouchPriority(Chat_Touch_Priority-22);
    m_pControlButtonPersonal->setTouchPriority(Chat_Touch_Priority-22);
    m_pControlButtonClose->setTouchPriority(Chat_Touch_Priority-22);
    m_pControlButtonAlliance->setTouchPriority(Chat_Touch_Priority-22);
    m_pControlButtonSent->setTouchPriority(Chat_Touch_Priority-22);
    m_pControlButtonSmilies->setTouchPriority(Chat_Touch_Priority-22);
    m_pTableMsg->setTouchPriority(Chat_Touch_Priority-1);

    onPressControlButtonWorld(m_pControlButtonWorld, CCControlEventTouchUpInside);
}

void CcbChatLayer::showEditBox() {
    CCSize sizeInput;
    CCPoint pointInput;
    sizeInput = m_pScale9SpriteText->getContentSize();
    pointInput = m_pScale9SpriteText->getParent()->convertToWorldSpace(m_pScale9SpriteText->getPosition());
    
    // 聊天框
    m_pScale9SpriteText->removeFromParent();
    
    m_pEditBoxInput = CCEditBox::create(sizeInput, m_pScale9SpriteText);
    m_pEditBoxInput->setAnchorPoint(ccp(0.5, 0.5));
    m_pEditBoxInput->setPosition(pointInput);
    
    m_pEditBoxInput->setFontName(T_Font);
    m_pEditBoxInput->setFontSize(16.0f);
    m_pEditBoxInput->setPlaceHolder(GET_STR(Str_input_text));
    m_pEditBoxInput->setDelegate(this);
    m_pEditBoxInput->setMaxLength(40);
    
    addChild(m_pEditBoxInput, 1);
    
    // ID输入框
    sizeInput = m_pScale9SpriteInputID->getContentSize();
    pointInput = m_pScale9SpriteInputID->getParent()->convertToWorldSpace(m_pScale9SpriteInputID->getPosition());
    
    m_pScale9SpriteInputID->removeFromParent();
    
    m_pEditBoxId = CCEditBox::create(sizeInput, m_pScale9SpriteInputID);
    m_pEditBoxId->setAnchorPoint(ccp(0.5, 0.5));
    m_pEditBoxId->setPosition(pointInput);
    m_pEditBoxId->setPlaceHolder("输入好友ID");
    m_pEditBoxId->setFontName(T_Font);
    m_pEditBoxId->setFontSize(12.0f);
    m_pEditBoxId->setDelegate(this);
    m_pEditBoxId->setMaxLength(10);
    
    addChild(m_pEditBoxId, 1);
    
    m_pEditBoxId->setTouchPriority(Chat_Touch_Priority-1);
    m_pEditBoxInput->setTouchPriority(Chat_Touch_Priority-1);
}

void CcbChatLayer::onPressControlButtonSent(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    if (m_nCurType == CHAT_CHANNEL_WOLRD) {
        if (m_pEditBoxInput->getText() == NULL || strlen(m_pEditBoxInput->getText()) == 0) {
            FlyTextLayer::showTips("没内容");
            return;
        }
        
        CGameSession::SendChatMsg(CHAT_CHANNEL_WOLRD, 0, "0", m_pEditBoxInput->getText());
        m_pEditBoxInput->setText("");
        m_nFaceCnt = 0;
        return;
    } else if (m_nCurType == CHAT_CHANNEL_PERSONAL) {
        if (m_pEditBoxId->getText() == NULL || strlen(m_pEditBoxId->getText()) == 0) {
            // 没有指定收信人
            FlyTextLayer::showTips("没对象");
            return;
        }
        int _targetId = atoi(m_pEditBoxId->getText());
        
        if (m_pEditBoxInput->getText() == NULL || strlen(m_pEditBoxInput->getText()) == 0) {
            FlyTextLayer::showTips("没内容");
            return;
        }
        
        CGameSession::SendChatMsg(CHAT_CHANNEL_PERSONAL, _targetId, "", m_pEditBoxInput->getText());
        m_pEditBoxInput->setText("");
        m_nFaceCnt = 0;
        return;
    }
}

void CcbChatLayer::onPressControlButtonSmilies(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
	CCNode* pNode = CcbManager::sharedManager()->LoadCcbChatFaceLayer(this);
    pNode->ignoreAnchorPointForPosition(false);
    pNode->setAnchorPoint(ccp(0.5, 0));
    pNode->setPosition(ccp(160.0f, tablePos.y + 4.0));
    m_pNodeBg->addChild(pNode, 99);
}

void CcbChatLayer::onPressControlButtonWorld(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    
    if (m_nCurType == CHAT_CHANNEL_WOLRD) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    
    m_pNodePersonal->setVisible(false);
    m_pEditBoxId->setVisible(false);
    
    m_pControlButtonWorld->setEnabled(false);
    m_pControlButtonPersonal->setEnabled(true);
    m_pControlButtonAlliance->setEnabled(true);

    m_nCurType = CHAT_CHANNEL_WOLRD;
    reloadData();
}

void CcbChatLayer::onPressControlButtonPersonal(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    if (m_nCurType == CHAT_CHANNEL_PERSONAL) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    
    m_pNodePersonal->setVisible(true);
    m_pEditBoxId->setVisible(true);
    
    m_pControlButtonWorld->setEnabled(true);
    m_pControlButtonPersonal->setEnabled(false);
    m_pControlButtonAlliance->setEnabled(true);

    m_nCurType = CHAT_CHANNEL_PERSONAL;
    reloadData();
}

void CcbChatLayer::onPressControlButtonAlliance(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    FlyTextLayer::showTips("暂未开放");
    return;
    m_nCurType = CHAT_CHANNEL_GUILD;
}

void CcbChatLayer::onPressControlButtonClose(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    removeFromParent();
}

#pragma mark CCEditBoxDelegate Method
void CcbChatLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox)
{
    
}

void CcbChatLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox)
{
    
}

void CcbChatLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, const std::string &text)
{
    
}

void CcbChatLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox)
{
    
}

void CcbChatLayer::addFaceCode(int _code)
{
    string orgString = m_pEditBoxInput->getText();
    char codeBuf[8];
    sprintf(codeBuf, "[/%d]", _code);
    orgString += codeBuf;
    m_pEditBoxInput->setText(orgString.c_str());
    
    m_nFaceCnt++;
}

#pragma mark -- Touch Delegate --
void CcbChatLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, Chat_Touch_Priority, true);
}

bool CcbChatLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    return true;
}

#pragma mark -- Table Delegate --
void CcbChatLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell) {
    return;
}

CCTableViewCell* CcbChatLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    CCTableViewCell* pCell = table->dequeueCell();
    
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbChatTalkBoardLayer* pTalkBoard = dynamic_cast<CcbChatTalkBoardLayer*>(CcbManager::sharedManager()->LoadCcbChatTalkBoardLayer(NULL));
        if (!pTalkBoard) {
            return NULL;
        }
        
        pTalkBoard->setNodeData(ChatDataMgr::Get()->msgAtIdx(idx, m_nCurType));
        pTalkBoard->setPosition(ccp(25, 5));
        pCell->addChild(pTalkBoard);
        pTalkBoard->setTag(123);
    } else {
        CcbChatTalkBoardLayer* pTalkBoard = dynamic_cast<CcbChatTalkBoardLayer*>(pCell->getChildByTag(123));
        pTalkBoard->setNodeData(ChatDataMgr::Get()->msgAtIdx(idx, m_nCurType));
    }
    return pCell;
}

unsigned int CcbChatLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table) {
    int nTableCnt = ChatDataMgr::Get()->msgCnt(m_nCurType);
//    CCLog("table cnt:%d", nTableCnt);
    return nTableCnt;
}

CCSize CcbChatLayer::cellSizeForTable(cocos2d::extension::CCTableView *table) {
    return CCSizeMake(250.0f, 60.0f);
}

void CcbChatLayer::reloadData()
{
    if (m_pTableMsg) {
        m_pTableMsg->reloadData();
        m_pTableMsg->scrollToIndex(numberOfCellsInTableView(m_pTableMsg)-1);
    }
}

void CcbChatLayer::touchToPrivate(uint32 dwAccount) {
    onPressControlButtonPersonal(m_pControlButtonPersonal, CCControlEventTouchUpInside);
    CCString* pString = CCString::createWithFormat("%d", dwAccount);
    m_pEditBoxId->setText(pString->getCString());
}

