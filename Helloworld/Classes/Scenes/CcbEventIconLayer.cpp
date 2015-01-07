#include "CcbEventIconLayer.h"
#include "EventDataMgr.h"
#include "CcbEventMainLayer.h"
#include "GuideData.h"
#include "SystemMessage.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "FlyTextLayer.h"
#include "GameSession.h"
#include "ResourcePic.h"
#include "ResourceStringClient.h"
#include "PetLoadingLayer.h"

CcbEventIconLayer::~CcbEventIconLayer()
{
    CGameSession::GetRole()->Detach(this);
	CC_SAFE_RELEASE_NULL(m_pControlButtonEvent);
    CC_SAFE_RELEASE_NULL(m_pSpriteTip);
    CC_SAFE_RELEASE_NULL(m_pSpriteSelectframe);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventIconLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventIconLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventIconLayer", CcbEventIconLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_icon.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventIconLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
    CGameSession::GetRole()->Attach(this);
	return true;
}

void CcbEventIconLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEventIconLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEventIconLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEventIconLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventIconLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEvent", CCScrollButton*, this->m_pControlButtonEvent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTip", CCSprite*, this->m_pSpriteTip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSelectframe", CCSprite*, this->m_pSpriteSelectframe);
	return false;
}

bool CcbEventIconLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEventIconLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventIconLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventIconLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEvent", CcbEventIconLayer::onPressControlButtonEvent);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventIconLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pSpriteTip->setVisible(false);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GET_PIC(Pic_event_packer));
}

void CcbEventIconLayer::SetShowData(int type)
{
    m_showType = type;
    
    string strImagePath;
    string strLabel;
    switch (m_showType)
    {
        case SHOW_FIRST_RECHARGE:
            strImagePath = GET_PIC(Btn_first_charge);
			strLabel = GET_STR(Str_first_charge);
            m_pSpriteTip->setVisible(false);
            break;
        case SHOW_GROW_PLAN:
            strImagePath = GET_PIC(Btn_grow_plan);
			strLabel = GET_STR(Str_grow_plan);
            m_pSpriteTip->setVisible(false);
            break;
        case SHOW_RECOVER_ENERGY:
            strImagePath = GET_PIC(Btn_get_energy);
			strLabel = GET_STR(Str_get_energy);
            if (CGameSession::GetRole()->GetbyEnergyRewStatus()) {
                m_pSpriteTip->setVisible(true);
            } else {
                m_pSpriteTip->setVisible(false);
            }
            break;
//        case SHOW_MY_STERY_SHOP:
//            strImagePath = GET_PIC(Btn_mystery_shop);
//			strLabel = GET_STR(Str_mystery_shop);
//            if (CGameSession::GetRole()->GetbyNotiMystery()) {
//                m_pSpriteTip->setVisible(true);
//            } else {
//                m_pSpriteTip->setVisible(false);
//            }
//            break;
        default:
            STC_EVENT_CHANGEABLE *pEventChangeable = g_EventData->getEventChangeableByActiveId(m_showType);
            if (!pEventChangeable) {
                return;
            }
            strImagePath = CCString::createWithFormat(GET_PIC(Pic_event_Event_Icon),pEventChangeable->wIcon)->getCString();//;
            strLabel = pEventChangeable->strTitle;
            m_pSpriteTip->setVisible(false);
            
            break;
    }
    
    isSelected(g_EventData->GetCurShowEventType() == m_showType);
    CCScale9Sprite* pScale9Sprite = NULL;
    for (int i = 0; i < 4; i++) {
        if (m_showType > SHOW_TYPE_MAX) {
            CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strImagePath.c_str());
            if (spriteFrame) {
                pScale9Sprite = CCScale9Sprite::createWithSpriteFrame(spriteFrame);
            }
            else
            {
                CCLOG("%s Not Find :%s",__PRETTY_FUNCTION__,strImagePath.c_str());
            }
            
        }
        else
        {
            pScale9Sprite = CCScale9Sprite::create( strImagePath.c_str() );
        }
        m_pControlButtonEvent->setBackgroundSpriteForState(pScale9Sprite, 1 << i);
    }
    
    m_pControlButtonEvent->setTitleForString(strLabel.c_str());
}

void CcbEventIconLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool CcbEventIconLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_StartTouchPos = CCPoint(0, 0);
    m_StartTouchPos = pTouch->getLocation();
    return true;
}

void CcbEventIconLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_EndTouchPos = CCPoint(0, 0);
    m_EndTouchPos = pTouch->getLocation();
}

void CcbEventIconLayer::onPressControlButtonEvent(CCObject* pSender, CCControlEvent event)
{
    if( fabs(m_StartTouchPos.x - m_EndTouchPos.x) > 20 || fabs(m_StartTouchPos.y - m_EndTouchPos.y) > 20 )
    {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    
    switch (m_showType)
    {
        
//        case SHOW_MY_STERY_SHOP: {
//            {
//                uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_MY_STERY_SHOP);
//                SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
//                if (cfg) {
//                    PetLoadingLayer::sharedLayer()->End();
//                    FlyTextLayer::showTips(cfg->strDescShow.c_str());
//                    return;
//                }
//            }
//            
//            CRole* pRole = CGameSession::GetRole();
//            pRole->SetbyNotiActive(
////                                   pRole->GetbySevenRewStatus() |
//                                   pRole->GetbyEnergyRewStatus() |
////                                   pRole->GetbyThirtyRewStatus() |
//                                   false
//                                   );
//            
//        }
        case SHOW_FIRST_RECHARGE:
        case SHOW_GROW_PLAN:
        case SHOW_RECOVER_ENERGY:
        default:
            g_EventData->SetCurShowEventType(m_showType);
            ((CcbEventMainLayer*)g_EventData->GetEventMainLayer())->ChangeEvent();
            break;
    }
}

void CcbEventIconLayer::ChangeIconState()
{}

#pragma mark Role Observer Delegate
void CcbEventIconLayer::byEnergyRewStatusChanged(uint8 byEnergyRewStatus)
{
    SetShowData(m_showType);
}

void CcbEventIconLayer::bySevenRewStatusChanged(uint8 bySevenRewStatus)
{
    SetShowData(m_showType);
}

void CcbEventIconLayer::byThirtyRewStatusChanged(uint8 byThirtyRewStatus)
{
    SetShowData(m_showType);
}

void CcbEventIconLayer::isSelected(bool flag)
{
    m_pSpriteSelectframe->setVisible(flag);
}