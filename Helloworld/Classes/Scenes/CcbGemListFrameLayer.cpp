#include "CcbGemListFrameLayer.h"
//#include "CcbManager.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "FlyTextLayer.h"
#include "ResourceStringClient.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "Account.h"
#endif

#include "GlobalData.h"
#include "Role.h"
#include "LoginSystem.h"
#include "md5.h"
#include "GameSession.h"
#include "ResourcePic.h"
#include "EnumDefines.h"

#include "ShopDataMgr.h"
#include "SystemMessage.h"
#include "ResourceStringClient.h"


CcbGemListFrameLayer* CcbGemListFrameLayer::createCCNode(cocos2d::CCNode *pParent, cocos2d::extension::CCBReader *pCCBReader)
{
    CcbGemListFrameLayer *ret = new CcbGemListFrameLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        ret->setAnimationManager(pCCBReader->getAnimationManager());
        return ret;
    }
    CC_SAFE_RELEASE_NULL(ret);
    return NULL;
}

CcbGemListFrameLayer::~CcbGemListFrameLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonRecharge);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRmb);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBuy);
    CC_SAFE_RELEASE_NULL(m_pNodeBuyCard);
    CC_SAFE_RELEASE_NULL(m_pNodeBuyDiamond);
    CC_SAFE_RELEASE_NULL(_animationManager);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFExternGet);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDayNum);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFOnlyOnce);
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 CCNode* LoadCcbGemListFrameLayer( CCObject* owner );
 
 //CcbManager.cpp
 CCNode* CcbManager::LoadCcbGemListFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGemListFrameLayer", CcbGemListFrameLayerLoader::loader() );
	
 
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gem_list.ccbi", owner);
	pCCBReader->release();
 
	return pNode;
 }
 */


bool CcbGemListFrameLayer::init()
{
    // First be called.
    if (!CCLayer::init()) {
        return false;
    }
    // code here
    return true;
}

void CcbGemListFrameLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *animationMgr)
{
    CC_SAFE_RELEASE_NULL(_animationManager);
    _animationManager = animationMgr;
    CC_SAFE_RETAIN(_animationManager);
}

void CcbGemListFrameLayer::onEnter()
{
    CCLayer::onEnter();
    
    //在scene()之后被调用}
    //这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbGemListFrameLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbGemListFrameLayer::onExit()
{
    CCLayer::onExit();
}

void CcbGemListFrameLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbGemListFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRecharge", CCScrollButton*, this->m_pControlButtonRecharge);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRmb", CCLabelTTF*, this->m_pLabelTTFRmb);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBuy", CCLabelTTF*, this->m_pLabelTTFBuy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNode_BuyCard", CCNode*, this->m_pNodeBuyCard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNode_BuyDiamond", CCNode*, this->m_pNodeBuyDiamond);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFExternGet", CCLabelTTF*, this->m_pLabelTTFExternGet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDayNum", CCLabelTTF*, this->m_pLabelTTFDayNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFOnlyOnce", CCLabelTTF*, this->m_pLabelTTFOnlyOnce);
    return false;
}

bool CcbGemListFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbGemListFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
    return NULL;
}

SEL_MenuHandler CcbGemListFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
    return NULL;
}

SEL_CCControlHandler CcbGemListFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRecharge", CcbGemListFrameLayer::onPressControlButtonRecharge);
    return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGemListFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    // 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
    // 可以删除，如果不需要}
    
    
}



void CcbGemListFrameLayer::onPressControlButtonRecharge(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    if (m_pPayItemInfo->dwGoodsId == E_EVENT_REWARD_DAY_7 && m_pPayItemInfo->dwLeftDay > 2 ) {
        SystemMessage::showSystemMessage(0, NULL, GET_STR(Str_ShopCard_LeftNotice1));
        return;
    }
    else if(m_pPayItemInfo->dwGoodsId == E_EVENT_REWARD_DAY_30 && m_pPayItemInfo->dwLeftDay > 10 && !GlobalData::shared()->getShopListSwitch() )
    {
        SystemMessage::showSystemMessage(0, NULL, GET_STR(Str_ShopCard_LeftNotice2));
        return;
    }
    
    
    // Android pay
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    CCLog("CcbGemListFrameLayer::onPressControlButtonRecharge buy [%d]", m_pPayItemInfo ? m_pPayItemInfo->dwGoodsId : -1);
    if (m_pPayItemInfo) {
        Account::shareInstance()->buy(m_pPayItemInfo->dwGoodsId);
    }
    return;
#endif
    
#if defined  VERSION_I4||VERSION_D9||VERSION_PP||VERSION_91
    if (m_pPayItemInfo) {
        Account::shareInstance()->buy(m_pPayItemInfo->dwGoodsId);
    }
#endif
    
}


void CcbGemListFrameLayer::setClipRect(CCRect rect)
{
    m_pControlButtonRecharge->setClipRect(rect);
}

void CcbGemListFrameLayer::setChargeInfo(uint32 dwGoodsId)
{
    m_pPayItemInfo = CShopDataMgr::Get()->GetStorePayGoodsInfoById(dwGoodsId);
    this->setChargeNodeInfo();
}

void CcbGemListFrameLayer::setChargeNodeInfo()
{
    if (!m_pPayItemInfo) {
        return;
    }
    CCLabelTTF *pLabelDes = NULL;
    
    m_pControlButtonRecharge->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_able_pic)),CCControlStateNormal);
    m_pControlButtonRecharge->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_able_pic)),CCControlStateHighlighted);
    m_pLabelTTFBuy->setString(m_pPayItemInfo->strSecondLine.c_str());
    CCSprite* pSpriteLight = (CCSprite *)this->getChildByTag(0);
    pSpriteLight->setVisible(false);
    
    CCSprite *pSpriteIcon = (CCSprite *)this->getChildByTag(1);
    CCTexture2D* pTexture2D = NULL;
    if (m_pPayItemInfo->byBuyType == E_BUY_TYPE_CARD) {
        m_pNodeBuyCard->setVisible(true);
        
        if (GlobalData::shared()->getShopListSwitch()) {
            m_pLabelTTFExternGet->setVisible(false);
            m_pLabelTTFDayNum->setVisible(true);
            m_pLabelTTFDayNum->setString(GET_STR(Str_moon_shop));
        }
        
        m_pNodeBuyDiamond->setVisible(false);
        CCLabelTTF* pLabelGetDes = (CCLabelTTF *)m_pNodeBuyCard->getChildByTag(0);
        pLabelDes =  (CCLabelTTF *)m_pNodeBuyCard->getChildByTag(1);
        if (m_pPayItemInfo->dwLeftDay != 0) {
            m_pLabelTTFRmb->setString(GET_STR(Str_ShopCard_Buy));
            pLabelGetDes->setVisible(false);
            pLabelDes->setString(CCString::createWithFormat(GET_STR(Str_ShopCard_leftTimes),m_pPayItemInfo->dwLeftDay)->getCString());
            pLabelDes->setPosition(ccp(65, 27));
            pLabelDes->setFontSize(12);
            
            if (GlobalData::shared()->getShopListSwitch()) {
                pLabelDes->setString(GET_STR(Str_moon_shop));
                m_pLabelTTFRmb->setString(m_pPayItemInfo->strFirstLine.c_str());
            } else {
            
                m_pControlButtonRecharge->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_disable_pic)),CCControlStateNormal);
                m_pControlButtonRecharge->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_disable_pic)),CCControlStateHighlighted);
            }
        }
        else
        {
            m_pLabelTTFRmb->setString(m_pPayItemInfo->strFirstLine.c_str());
            pLabelGetDes->setVisible(true);
            
            if (m_pPayItemInfo->strThirdLine.length() < 3) {
                pLabelDes->setVisible(false);
            }
            else{
                pLabelDes->setVisible(true);
                pLabelDes->setString(m_pPayItemInfo->strThirdLine.c_str());
            }
            pLabelDes->setPosition(ccp(65, 19));
            pLabelDes->setFontSize(10);
            
            if (GlobalData::shared()->getShopListSwitch()) {
                pLabelGetDes->setVisible(false);
                pLabelDes->setString(GET_STR(Str_moon_shop));
            }
        }
        if (m_pPayItemInfo->dwGoodsId == E_EVENT_REWARD_DAY_7) {
            m_pLabelTTFDayNum->setVisible(true);
            pTexture2D = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_weekycard));
        }
        else
        {
            pSpriteLight->setVisible(true);
            if (_animationManager) {
                _animationManager->runAnimationsForSequenceNamed("Default Timeline");
            }
            pTexture2D = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_monthlycard));
        }
        
    }
    else
    {
        pTexture2D = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_gem_icon));
        
        m_pNodeBuyCard->setVisible(false);
        
        if (GlobalData::shared()->getShopListSwitch()) {
            m_pLabelTTFOnlyOnce->setVisible(false);
        }
        
        m_pNodeBuyDiamond->setVisible(true);
        m_pLabelTTFRmb->setString(m_pPayItemInfo->strFirstLine.c_str());
        pLabelDes =  (CCLabelTTF *)m_pNodeBuyDiamond->getChildByTag(1);
        if (m_pPayItemInfo->strThirdLine.length() < 3) {
            pLabelDes->setVisible(false);
            m_pNodeBuyDiamond->getChildByTag(0)->setVisible(false);
        }
        else{
            pLabelDes->setVisible(true);
            m_pNodeBuyDiamond->getChildByTag(0)->setVisible(true);
            pLabelDes->setString(m_pPayItemInfo->strThirdLine.c_str());
        }
        CCNode *pNode = m_pNodeBuyDiamond->getChildByTag(2);
        if (m_pPayItemInfo->byFirstPay == 0 && m_pPayItemInfo->dwGoodsId != 4) {
            pNode->setVisible(true);
        }
        else
        {
            pNode->setVisible(false);
        }
    }
    pSpriteIcon->setTexture(pTexture2D);
}




