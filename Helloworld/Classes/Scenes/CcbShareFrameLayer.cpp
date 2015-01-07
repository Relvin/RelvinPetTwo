#include "CcbShareFrameLayer.h"
#include "CcbManager.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"



#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//#undef ENABLE_SHARE
#endif

#if ENABLE_SHARE
#include "ShareWeiboWeixin.h"
#endif

#include "MailDataMgr.h"
#include "GameSession.h"
#include "Role.h"
#include "PacketDataMgr.h"

CcbShareFrameLayer::~CcbShareFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteImage);
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteImageFrame);
	CC_SAFE_RELEASE_NULL(m_pControlButtonWeiBo);
	CC_SAFE_RELEASE_NULL(m_pControlButtonWeiXin);
    CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
    CC_SAFE_RELEASE_NULL(m_pNodeShareReward);
    
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbShareFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbShareFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbShareFrameLayer", CcbShareFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/share_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbShareFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbShareFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CMailDataMgr::Get()->SetShareFrameLayerPt(this);
    ShareWeiboWeixin::Create();
    this->setShareRewardInfo();
}

void CcbShareFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbShareFrameLayer::onExit()
{
    ShareWeiboWeixin::Destory();
	CCLayer::onExit();
}

void CcbShareFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbShareFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteImage", CCScale9Sprite*, this->m_pScale9SpriteImage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteImageFrame", CCScale9Sprite*, this->m_pScale9SpriteImageFrame);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonWeiBo", CCControlButton*, this->m_pControlButtonWeiBo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonWeiXin", CCControlButton*, this->m_pControlButtonWeiXin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeShareReward", CCNode*, this->m_pNodeShareReward);
	return false;
}

bool CcbShareFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbShareFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbShareFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbShareFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonWeiBo", CcbShareFrameLayer::onPressControlButtonWeiBo);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonWeiXin", CcbShareFrameLayer::onPressControlButtonWeiXin);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbShareFrameLayer::onPressControlButtonCancel);
    
	return NULL;
}

void CcbShareFrameLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -200, true);
    m_pControlButtonWeiBo->setTouchPriority(-201);
    m_pControlButtonWeiXin->setTouchPriority(-201);
    m_pControlButtonCancel->setTouchPriority(-201);
}

bool CcbShareFrameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

// Inhert CCNodeLoaderListener
void CcbShareFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    
}

void CcbShareFrameLayer::onPressControlButtonWeiBo(CCObject* pSender, CCControlEvent event)
{
#if ENABLE_SHARE
    ShareWeiboWeixin::Create();
    ShareWeiboWeixin::Get()->onShareWeibo(getShareText().c_str());
#endif
}

void CcbShareFrameLayer::onPressControlButtonWeiXin(CCObject* pSender, CCControlEvent event)
{
#if ENABLE_SHARE
    ShareWeiboWeixin::Create();
    ShareWeiboWeixin::Get()->onShareWeiXin(getShareText().c_str());
#endif
}

void CcbShareFrameLayer::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    removeFromParent();
}

void CcbShareFrameLayer::showShare(CCLayer* layer, uint16 shareType)
{
    CCRenderTexture* rt = CCRenderTexture::create(CCDirector::sharedDirector()->getWinSize().width , CCDirector::sharedDirector()->getWinSize().height);
    rt->begin();
    layer->visit();
    rt->end();
    
    CcbShareFrameLayer* pCcbNode = (CcbShareFrameLayer*)CcbManager::sharedManager()->LoadShareFrameLayer();
    pCcbNode->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width * 0.5, CCDirector::sharedDirector()->getWinSize().height * 0.5));
    pCcbNode->ignoreAnchorPointForPosition(false);
    pCcbNode->setAnchorPoint(ccp(0.5, 0.5));
    pCcbNode->loadData(rt->getSprite()->displayFrame(), shareType);
    CCDirector::sharedDirector()->getRunningScene()->addChild(pCcbNode, 1000);
    
    rt->saveToFile("screenshot.png", kCCImageFormatPNG);
    
    rt->release();
}

void CcbShareFrameLayer::loadData(cocos2d::CCSpriteFrame *photo, uint16 shareType)
{
    float scaleX = m_pScale9SpriteImage->getContentSize().width / CCDirector::sharedDirector()->getWinSize().width;
    float scaleY = m_pScale9SpriteImage->getContentSize().height / CCDirector::sharedDirector()->getWinSize().height;
    
    m_pScale9SpriteImage->setSpriteFrame(photo);
    m_pScale9SpriteImage->setScaleX(scaleX);
    m_pScale9SpriteImage->setScaleY(-scaleY);
    
    m_shareType = shareType;
}

std::string CcbShareFrameLayer::getShareText()
{
    return GET_STR(m_shareType);
}


void CcbShareFrameLayer::setShareRewardInfo()
{
    CRole* pRole = CGameSession::GetRole();
    if (!pRole || pRole->GetdwShareCnt() >= 3) {
        m_pNodeShareReward->setVisible(false);
        return;
    }
    
    ShareConfig::STC_SHARE_CONFIG* pShareConfig = GET_CONFIG_STC(ShareConfig, pRole->GetdwShareCnt() + 1);
    if (!pShareConfig) {
        m_pNodeShareReward->setVisible(false);
        return;
    }
    m_pNodeShareReward->setVisible(true);
    ((CCSprite *)m_pNodeShareReward->getChildByTag(0))->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetItemIconByIndex(pShareConfig->dwItemIndex).c_str()));
    ((CCLabelTTF*)m_pNodeShareReward->getChildByTag(1))->setString(CCString::createWithFormat("+%d",pShareConfig->dwItemCount)->getCString());
}
