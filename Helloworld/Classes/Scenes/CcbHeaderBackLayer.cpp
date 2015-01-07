#include "CcbHeaderBackLayer.h"
#include "BackCtrl.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "StageScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbHeaderBackLayer::~CcbHeaderBackLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
    CC_SAFE_RELEASE_NULL(m_pNodeBg);
}


bool CcbHeaderBackLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_fOffset = CCDirector::sharedDirector()->getWinSize().width;
	return true;
}

void CcbHeaderBackLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}

    
    //子ccb的action manager的绑定需要在onEnter中进行，在onNodeLoaded中无法绑定成功}
//    CC_SAFE_RELEASE_NULL(mAnimationManager);
//    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
//    CC_SAFE_RETAIN(mAnimationManager);
    
    CCPoint pos = ccpAdd(ccp(m_fOffset, 0), m_pNodeBg->getPosition());
    m_pNodeBg->setPosition(pos);

    
    // 暂停之前的切出action，否则会影响到加载的action}
//    this->stopActionByTag(234);
    this->stopAllActions();
    
}

void CcbHeaderBackLayer::onEnterTransitionDidFinish()
{
    m_pNodeBg->runAction(CCMoveBy::create(TRANS_DUR*0.5, ccp(-m_fOffset, 0.0f)));
    CCLayer::onEnterTransitionDidFinish();
}

void CcbHeaderBackLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
    
    CCAction* pMoveAction = CCMoveBy::create(TRANS_DUR*0.5, ccp(m_fOffset, 0.0f));
    pMoveAction->setTag(234);
    this->runAction(pMoveAction);

}

void CcbHeaderBackLayer::onExit()
{
	CCLayer::onExit();
}


SEL_CallFuncN CcbHeaderBackLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbHeaderBackLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

bool CcbHeaderBackLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeBg", CCNode*, this->m_pNodeBg);
    
	return false;
}


bool CcbHeaderBackLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


SEL_CCControlHandler CcbHeaderBackLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbHeaderBackLayer::onPressControlButtonBack);
	return NULL;
}

void CcbHeaderBackLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonBack->setTouchPriority(kCCMenuHandlerPriority+30);
    m_backFlag = false;
}


void CcbHeaderBackLayer::onPressControlButtonBack(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    if (m_backFlag) {
        return;
    }
    m_backFlag = true;
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    
    if (BackCtrl::GetCurSceneIdx() == kStageScene) {
        PetLoadingLayer::sharedLayer()->WaitForPacket(true);
        if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage || StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
            CGameSession::SendNormalMap();
        } else if (StageCtrl::Get()->kind() == StageCtrl::kActivityStage) {
            StageCtrl::Get()->setFromJump(false);
            CGameSession::SendSpecialMapList();
        }
    } else {
        BackCtrl::BacktoUpperScene();
    }
}









