#include "CcbShopSelectNumLayer.h"
//#include "CcbManager.h"
#include "ShopDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "SystemMessage.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "PacketDataMgr.h"
#include "FlyTextLayer.h"
#include "CcbItemIconLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbShopSelectNumLayer::~CcbShopSelectNumLayer()
{
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteNum);
	CC_SAFE_RELEASE_NULL(m_pControlButtonPlus);
	CC_SAFE_RELEASE_NULL(m_pControlButtonMinus);
	CC_SAFE_RELEASE_NULL(m_pControlButtonConfirm);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
    CC_SAFE_RELEASE_NULL(m_pEditBoxNum);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCost);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemNum);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItem);
    CC_SAFE_RELEASE_NULL(m_pNodeItemicon);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCanBuyCnt);
    CC_SAFE_RELEASE_NULL(m_pControlButtonMax);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbShopSelectNumLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbShopSelectNumLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbShopSelectNumLayer", CcbShopSelectNumLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_select_num.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbShopSelectNumLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    this->setTouchEnabled(true);
	return true;
}

void CcbShopSelectNumLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbShopSelectNumLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbShopSelectNumLayer::onExit()
{
	CCLayer::onExit();
}

void CcbShopSelectNumLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbShopSelectNumLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteNum", CCScale9Sprite*, this->m_pScale9SpriteNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPlus", CCControlButton*, this->m_pControlButtonPlus);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMinus", CCControlButton*, this->m_pControlButtonMinus);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonConfirm", CCControlButton*, this->m_pControlButtonConfirm);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCost", CCLabelTTF*, this->m_pLabelTTFCost);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemNum", CCLabelTTF*, this->m_pLabelTTFItemNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItem", CCLabelTTF*, this->m_pLabelTTFItem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeItemicon", CcbItemIconLayer*, this->m_pNodeItemicon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCanBuyCnt", CCLabelTTF*, this->m_pLabelTTFCanBuyCnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMax", CCControlButton*, this->m_pControlButtonMax);
	return false;
}

bool CcbShopSelectNumLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbShopSelectNumLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbShopSelectNumLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbShopSelectNumLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonPlus", CcbShopSelectNumLayer::onPressControlButtonPlus);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMinus", CcbShopSelectNumLayer::onPressControlButtonMinus);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonConfirm", CcbShopSelectNumLayer::onPressControlButtonConfirm);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbShopSelectNumLayer::onPressControlButtonCancel);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMax", CcbShopSelectNumLayer::onPressControlButtonMax);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbShopSelectNumLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    //具体物品名字}
    m_pLabelTTFItem->setString(g_PacketDataMgr->GetObjectNameByIndex(g_ShopData->GetCurBuyContentId()).c_str());
    //物品数量}
    char szTemp[32] = "";
    sprintf(szTemp, "%d", g_PacketDataMgr->GetObjectCountByIndex(g_ShopData->GetCurBuyContentId()));
    m_pLabelTTFItemNum->setString(szTemp);
    //总花费}
    sprintf(szTemp, "%d", g_ShopData->GetCurGoodsCostCount());
    m_pLabelTTFCost->setString(szTemp);
    
    CCSize EditBoxSize = m_pScale9SpriteNum->getContentSize();
    CCPoint EditBoxPos = m_pScale9SpriteNum->getPosition();
    m_pScale9SpriteNum->removeFromParent();
    
    m_pEditBoxNum = CCEditBox::create(EditBoxSize, m_pScale9SpriteNum);
    
    m_pEditBoxNum->setHorizontalAlignment(kCCTextAlignmentCenter);
    
    m_pEditBoxNum->setInputMode(kEditBoxInputModeNumeric);
    m_pEditBoxNum->setPosition(EditBoxPos);
    m_pEditBoxNum->setMaxLength(3);
//    m_pEditBoxNum->setPlaceHolder(GET_STR(Str_input_cnt));
    m_pEditBoxNum->setText("1");
    
    g_ShopData->SetSelectNum(1);
    m_pEditBoxNum->retain();
    addChild(m_pEditBoxNum);
    m_pEditBoxNum->setDelegate(this);
    
    m_pControlButtonCancel->setTouchPriority(kCCMenuHandlerPriority - 22);
    m_pControlButtonConfirm->setTouchPriority(kCCMenuHandlerPriority - 22);
    m_pControlButtonMinus->setTouchPriority(kCCMenuHandlerPriority - 22);
    m_pControlButtonPlus->setTouchPriority(kCCMenuHandlerPriority - 22);
    
    m_pEditBoxNum->setTouchPriority(kCCMenuHandlerPriority - 22);
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 22);
    m_pControlButtonMax->setTouchPriority(kCCMenuHandlerPriority - 22);
    
    m_pNodeItemicon->loadIndexData(g_ShopData->GetCurBuyContentId());
    m_pNodeItemicon->hideName();
    
    m_maxCnt = 99;
}

#pragma mark - Touch Functions -
void CcbShopSelectNumLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 21, true);
}

bool CcbShopSelectNumLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

#pragma mark - Button Functions -
void CcbShopSelectNumLayer::onPressControlButtonPlus(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	
    char szTempNum[16];
    strncpy(szTempNum, m_pEditBoxNum->getText(), 2);
    int nTempNum = atoi(szTempNum);
    nTempNum ++;
    nTempNum = checkNum(nTempNum);
    g_ShopData->SetSelectNum(nTempNum);
    sprintf(szTempNum, "%d", nTempNum);
    m_pEditBoxNum->setText(szTempNum);
    //刷新总花费}
    sprintf(szTempNum, "%d", g_ShopData->GetCurGoodsCostCount() * nTempNum);
    m_pLabelTTFCost->setString(szTempNum);
}

void CcbShopSelectNumLayer::onPressControlButtonMinus(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	
    char szTempNum[16];
    strncpy(szTempNum, m_pEditBoxNum->getText(), 2);
    int nTempNum = atoi(szTempNum);
    nTempNum --;
    nTempNum = checkNum(nTempNum);
    g_ShopData->SetSelectNum(nTempNum);
    sprintf(szTempNum, "%d", nTempNum);
    m_pEditBoxNum->setText(szTempNum);
    //刷新总花费}
    sprintf(szTempNum, "%d", g_ShopData->GetCurGoodsCostCount() * nTempNum);
    m_pLabelTTFCost->setString(szTempNum);
}

void CcbShopSelectNumLayer::onPressControlButtonConfirm(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	
    if (g_ShopData->GetSelectNum() == 0)
    {
        FlyTextLayer::showTips(GET_STR(Str_input_buy_cnt));
        return;
    }
    
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendShopBuyItem(g_ShopData->GetCurChosenGoodsId(), g_ShopData->GetSelectNum());
    g_ShopData->SetDlgOpenState(false);
    removeFromParent();
}

void CcbShopSelectNumLayer::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    g_ShopData->SetDlgOpenState(false);
    removeFromParent();
}

void CcbShopSelectNumLayer::onPressControlButtonMax(CCObject* pSender, CCControlEvent event)
{
    int nTempNum = checkNum(m_maxCnt);
    
    g_ShopData->SetSelectNum(nTempNum);
    
    m_pEditBoxNum->setText(CCString::createWithFormat("%d",nTempNum)->getCString());
    m_pLabelTTFCost->setString(CCString::createWithFormat("%d",g_ShopData->GetCurGoodsCostCount() * nTempNum)->getCString());
}

void CcbShopSelectNumLayer::setMaxCnt(uint16 maxCnt)
{
    m_maxCnt = maxCnt;
    m_pLabelTTFCanBuyCnt->setString(CCString::createWithFormat(GET_STR(Str_Times),m_maxCnt)->getCString());
    if (m_pEditBoxNum) {
        checkNum(atoi(m_pEditBoxNum->getText()));
    }
    
}

void CcbShopSelectNumLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox * editbox)
{
    //
}

void CcbShopSelectNumLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox * editbox)
{
    //
}

void CcbShopSelectNumLayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    //
}
void CcbShopSelectNumLayer::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
    int nTempNum = atoi(editBox->getText());
    nTempNum = checkNum(nTempNum);
    
    g_ShopData->SetSelectNum(nTempNum);
    
    m_pEditBoxNum->setText(CCString::createWithFormat("%d",nTempNum)->getCString());
    m_pLabelTTFCost->setString(CCString::createWithFormat("%d",g_ShopData->GetCurGoodsCostCount() * nTempNum)->getCString());
}

int CcbShopSelectNumLayer::checkNum(int num)
{
    m_pControlButtonMinus->setEnabled(true);
    m_pControlButtonPlus->setEnabled(true);
    m_pControlButtonMax->setEnabled(true);
    if (num <= 1)
    {
        num = 1;
        m_pControlButtonMinus->setEnabled(false);
    }
    
    if (num >= m_maxCnt)
    {
        num = m_maxCnt;
        m_pControlButtonPlus->setEnabled(false);
        m_pControlButtonMax->setEnabled(false);
    }
    
    return num;
}