#include "BuyMiddleLayer.h"
#include "BackCtrl.h"
#include "CcbHeaderBackLayer.h"
#include "GameSession.h"
#include "ShopDataMgr.h"
#include "PetLoadingLayer.h"
#include "EnumDefines.h"
#include "BuyDataMgr.h"
#include "Instruments.h"
#include "CcbSystemLayer2.h"
#include "FlyTextLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "GlobalData.h"
#include "MusicCtrl.h"
#include "BuyDataMgr.h"
#include "CcbJumpTipLayer.h"
#include "CcbManager.h"
#include "UISupport.h"

USING_NS_CC;
USING_NS_CC_EXT;

BuyMiddleLayer::~BuyMiddleLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonZero);
    CC_SAFE_RELEASE_NULL(m_pControlButtonOne);
//    CC_SAFE_RELEASE_NULL(m_pControlButtonEnlageBag);
//    CC_SAFE_RELEASE_NULL(m_pControlButtonEnlagePet);
    CC_SAFE_RELEASE_NULL(m_pControlButtonRecEnergy);
    CC_SAFE_RELEASE_NULL(m_pControlButtonBuyCoin);
    
    CC_SAFE_RELEASE_NULL(m_pSpriteBg);
    CC_SAFE_RELEASE_NULL(m_pLayerBack);
    CC_SAFE_RELEASE_NULL(m_pLayerBottom);
    CC_SAFE_RELEASE_NULL(m_pLayerHead);
    CC_SAFE_RELEASE_NULL(m_pNodeBtn);
    
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftRecCnt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftPetCnt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftBagCnt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftCoinCnt);
    CC_SAFE_RELEASE_NULL(m_pSpriteLeftCoin);
    CC_SAFE_RELEASE_NULL(m_pSpriteLeftRec);
    
    CC_SAFE_RELEASE_NULL(m_pLabelTTFWord);
    m_currentScene = NULL;
}

BuyMiddleLayer* BuyMiddleLayer::m_currentScene = NULL;

bool BuyMiddleLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CShopDataMgr::Get()->setAddMoney(0);
    m_currentScene = this;
	return true;
}

void BuyMiddleLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_posNodeAction = m_pNodeBtn->getPosition();
    m_pNodeBtn->setPositionX(CCDirector::sharedDirector()->getWinSize().width + m_pNodeBtn->getContentSize().width);
}

void BuyMiddleLayer::onExit()
{
	CCLayer::onExit();
    CShowJumpTip::Get()->setJumpType(E_SHOW_JUMP_NULL);
}

void BuyMiddleLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();

    m_pNodeBtn->runAction(CCMoveTo::create(0.15f, m_posNodeAction));
}

void BuyMiddleLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
    m_pNodeBtn->runAction(CCMoveBy::create(0.15f, ccp(210, 0)));
}

SEL_CallFuncN BuyMiddleLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_MenuHandler BuyMiddleLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

bool BuyMiddleLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonZero", CCControlButton*, this->m_pControlButtonZero);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOne", CCControlButton*, this->m_pControlButtonOne);

//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEnlageBag", CCControlButton*, this->m_pControlButtonEnlageBag);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEnlagePet", CCControlButton*, this->m_pControlButtonEnlagePet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRecEnergy", CCControlButton*, this->m_pControlButtonRecEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBuyCoin", CCControlButton*, this->m_pControlButtonBuyCoin);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHead", CCLayer*, this->m_pLayerHead);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, this->m_pLayerBottom);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBack", CCLayer*, this->m_pLayerBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeBtn", CCNode*, this->m_pNodeBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftCoinCnt", CCLabelTTF*, this->m_pLabelTTFLeftCoinCnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftPetCnt", CCLabelTTF*, this->m_pLabelTTFLeftPetCnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftRecCnt", CCLabelTTF*, this->m_pLabelTTFLeftRecCnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftBagCnt", CCLabelTTF*, this->m_pLabelTTFLeftBagCnt);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLeftCoin", CCSprite*, this->m_pSpriteLeftCoin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLeftPet", CCSprite*, this->m_pSpriteLeftPet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLeftRec", CCSprite*, this->m_pSpriteLeftRec);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLeftBag", CCSprite*, this->m_pSpriteLeftBag);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWord", CCLabelTTF*, this->m_pLabelTTFWord);
	return false;
}


SEL_CCControlHandler BuyMiddleLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButton", BuyMiddleLayer::onPressControlButton);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEnlageBag", BuyMiddleLayer::onPressControlButtonEnlageBag);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEnlagePet", BuyMiddleLayer::onPressControlButtonEnlagePet);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRecEnergy", BuyMiddleLayer::onPressControlButtonRecEnergy);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBuyCoin", BuyMiddleLayer::onPressControlButtonBuyCoin);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonChest", BuyMiddleLayer::onPressControlButtonChest);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFace", BuyMiddleLayer::onPressControlButtonFace);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonDown", BuyMiddleLayer::onPressControlButtonDown);
	return NULL;
}

bool BuyMiddleLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


void BuyMiddleLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonZero->setTag(E_ROLE_OPERATE_TYPE_RECHARGE);
    m_pControlButtonOne->setTag(E_ROLE_OPERATE_TYPE_DOLLAR);
//    m_pControlButtonEnlageBag->setTag(E_ROLE_OPERATE_TYPE_ITEM_BAG);
//    m_pControlButtonEnlagePet->setTag(E_ROLE_OPERATE_TYPE_PET_BAG);
    m_pControlButtonRecEnergy->setTag(E_ROLE_OPERATE_TYPE_ENERGY);
    m_pControlButtonBuyCoin->setTag(E_ROLE_OPERATE_TYPE_GET_COIN);
    BuyDataMgr::Get()->setCurBuyType(E_ROLE_OPERATE_TYPE_NULL);
    updateLeftCnt();
    
    m_pSpriteLeftRec->setZOrder(1);
    m_pSpriteLeftCoin->setZOrder(1);
    
    if (CShowJumpTip::Get()->getJumpType() == E_POWER_NOT_ENOUGH) {
        CCNode* node = CcbManager::sharedManager()->LoadCcbStageEffLayer();
        node->setScale(getWidth(m_pControlButtonRecEnergy) / getWidth(node), getHeight(m_pControlButtonRecEnergy) / getHeight(node));
        node->setPosition(m_pControlButtonRecEnergy->getPosition());
        node->ignoreAnchorPointForPosition(false);
        node->setAnchorPoint(m_pControlButtonRecEnergy->getAnchorPoint());
        m_pControlButtonRecEnergy->getParent()->addChild(node);
    }
    else if(CShowJumpTip::Get()->getJumpType() == E_MONEY_NOT_ENOUGH){
        CCNode* node = CcbManager::sharedManager()->LoadCcbStageEffLayer();
        node->setScale(getWidth(m_pControlButtonBuyCoin) / getWidth(node), getHeight(m_pControlButtonBuyCoin) / getHeight(node));
        node->setPosition(m_pControlButtonBuyCoin->getPosition());
        node->ignoreAnchorPointForPosition(false);
        node->setAnchorPoint(m_pControlButtonBuyCoin->getAnchorPoint());
        m_pControlButtonBuyCoin->getParent()->addChild(node);
    }
}

void BuyMiddleLayer::onPressControlButton(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    int tag =((CCControlButton *)pSender)->getTag();
    switch (tag) {
        case E_ROLE_OPERATE_TYPE_RECHARGE:
        {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            g_ShopData->SetCurShopShowType(1);
            //CGameSession::SendOpenShopRequest();
            CGameSession::SendRequestStorePayList();
        }
            break;
        case E_ROLE_OPERATE_TYPE_DOLLAR:
        {
            CShopDataMgr::Get()->setItemId(0);
            CShopDataMgr::Get()->setCellIndex(-1);
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            g_ShopData->SetCurShopShowType(2);
            CGameSession::SendOpenShopRequest();
        }
            break;

        case E_ROLE_OPERATE_TYPE_ARENA:

        case E_ROLE_OPERATE_TYPE_ITEM_BAG:

        case E_ROLE_OPERATE_TYPE_PET_BAG:
        
        default:
            break;
    };
}

void BuyMiddleLayer::showTips()
{
    snprintf(strBuff1024, BUFFER_SIZE_1024, "%s", GET_STR(Str_no_cnt));
    FlyTextLayer::showTips(strBuff1024);
}

void BuyMiddleLayer::onPressControlButtonBuyCoin(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BuyDataMgr::STC_BUY sCoin;
    sCoin = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_GET_COIN);
    
    if (sCoin.dwLeftCnt == 0)
    {
//        showTips();
        CShowJumpTip::Get()->Show(E_VIP_NOT_ENOUGH);
    }
    else
    {
        BuyDataMgr::Get()->setCurBuyType(E_ROLE_OPERATE_TYPE_GET_COIN);
        CSystemMessage2::Get()->Show(E_TYPE_GET_COIN, sCoin.dwCostDollar, sCoin.dwEarnCnt);
    }
}

void BuyMiddleLayer::onPressControlButtonRecEnergy(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BuyDataMgr::STC_BUY sEnergy;
    sEnergy = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_ENERGY);
    
    if (sEnergy.dwLeftCnt == 0)
    {
//        showTips();
        CShowJumpTip::Get()->Show(E_VIP_NOT_ENOUGH);
    }
    else
    {
        BuyDataMgr::Get()->setCurBuyType(E_ROLE_OPERATE_TYPE_ENERGY);
        CSystemMessage2::Get()->Show(E_TYPE_POWER, sEnergy.dwCostDollar, sEnergy.dwEarnCnt);
    }
}

//void BuyMiddleLayer::onPressControlButtonEnlageBag(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
//{
//    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
//    BuyDataMgr::STC_BUY sBag;
//    sBag = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_ITEM_BAG);
//    BuyDataMgr::Get()->setCurBuyType(E_ROLE_OPERATE_TYPE_ITEM_BAG);
//    CSystemMessage2::Get()->Show(E_TYPE_ITEM_BAG, sBag.dwCostDollar, sBag.dwEarnCnt);
//}

//void BuyMiddleLayer::onPressControlButtonEnlagePet(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
//{
//    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
//    BuyDataMgr::STC_BUY sPet;
//    sPet = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_PET_BAG);
//    BuyDataMgr::Get()->setCurBuyType(E_ROLE_OPERATE_TYPE_PET_BAG);
//    CSystemMessage2::Get()->Show(E_TYPE_PET_BAG, sPet.dwCostDollar, sPet.dwEarnCnt);
//}

void BuyMiddleLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    CGameSession::SendItemBagEnlager(systemMessage->getParam());
}

void BuyMiddleLayer::systemMessageCancelTapped(SystemMessage *systemMessage)
{

}

void BuyMiddleLayer::updateLeftCnt()
{
    if (CSystemMessage2::Get() && CSystemMessage2::Get()->GetMsgType() != E_TYPE_GET_COIN)
    {
        CSystemMessage2::Get()->Close();
    }
    else
    {
        if (CShopDataMgr::Get()->GetAddMoney() > 0)
        {
            BuyDataMgr::STC_BUY sCoin;
            sCoin = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_GET_COIN);
            //先飘字再刷新对话框，不能反}
            FlyTextLayer::showText(FlyTextLayer::kMoneyAdd, CShopDataMgr::Get()->GetAddMoney());
            CSystemMessage2::Get()->Refeash(sCoin.dwCostDollar, sCoin.dwEarnCnt);
        }
    }
    
    BuyDataMgr::STC_BUY tmpStruct;

    //体力购买次数}
    tmpStruct = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_ENERGY);
//    if (tmpStruct.dwEarnCnt > 0) {
//        FlyTextLayer::showTips(CCString::createWithFormat(GET_STR(Str_buy_energy_success), tmpStruct.dwEarnCnt)->getCString());
//    }
    m_pLabelTTFLeftRecCnt->setString(cvtInt2String(tmpStruct.dwLeftCnt).c_str());
    
    
    //宠物栏扩展}
//    tmpStruct = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_PET_BAG);
//    if (tmpStruct.dwEarnCnt > 0) {
//        FlyTextLayer::showTips(GET_STR(Str_open_bag_success));
//    }
//    //背包扩展}
//    tmpStruct = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_ITEM_BAG);
//    if (tmpStruct.dwEarnCnt > 0) {
//        FlyTextLayer::showTips(GET_STR(Str_open_bag_success));
//    }

    switch (BuyDataMgr::Get()->getCurBuyType()) {
        case E_ROLE_OPERATE_TYPE_ENERGY:
            FlyTextLayer::showTips(CCString::createWithFormat(GET_STR(Str_buy_energy_success), tmpStruct.dwEarnCnt)->getCString());
            break;
        case E_ROLE_OPERATE_TYPE_PET_BAG:
        case E_ROLE_OPERATE_TYPE_ITEM_BAG:
            FlyTextLayer::showTips(GET_STR(Str_open_bag_success));
            break;
            
        default:
            break;
    }
    BuyDataMgr::Get()->setCurBuyType(E_ROLE_OPERATE_TYPE_NULL);
    //金币购买次数}
    tmpStruct = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_GET_COIN);
    m_pLabelTTFLeftCoinCnt->setString(cvtInt2String(tmpStruct.dwLeftCnt).c_str());
    if (tmpStruct.dwLeftCnt == 0)
    {
        if (CSystemMessage2::Get())
        {
            CSystemMessage2::Get()->Close();
        }
    }
    
    if (CSystemMessage2::Get() && CSystemMessage2::Get()->GetMsgType() == E_TYPE_GET_COIN)
    {
        if (CShopDataMgr::Get()->GetAddMoney() == 0)
        {
            CSystemMessage2::Get()->Close();
        }
    }
}

void BuyMiddleLayer::onPressControlButtonChest(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    int k = rand() % 3;
    switch (k) {
        case 0:
            m_pLabelTTFWord->setString("色狼...");
            break;
        case 1:
            m_pLabelTTFWord->setString("手感好不好？");
            break;
        case 2:
            m_pLabelTTFWord->setString("已经很大了，再大就要下垂了。");
            break;
        default:
            break;
    }
    
}

void BuyMiddleLayer::onPressControlButtonFace(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    int k = rand() % 3;
    switch (k) {
        case 0:
            m_pLabelTTFWord->setString("妆花了！");
            break;
        case 1:
            m_pLabelTTFWord->setString("求喂食，求领养");
            break;
        case 2:
            m_pLabelTTFWord->setString("戳到我的眼睛了，白痴");
            break;
        default:
            break;
    }
}

void BuyMiddleLayer::onPressControlButtonDown(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    int k = rand() % 3;
    switch (k) {
        case 0:
            m_pLabelTTFWord->setString("我的腿是不是比开场的妹子细？");
            break;
        case 1:
            m_pLabelTTFWord->setString("我没穿安全裤哦");
            break;
        case 2:
            m_pLabelTTFWord->setString("有点痒");
            break;
        default:
            break;
    }
}
