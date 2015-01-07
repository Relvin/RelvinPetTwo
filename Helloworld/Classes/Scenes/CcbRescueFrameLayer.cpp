#include "CcbRescueFrameLayer.h"
//#include "CcbManager.h"
#include "FriendCtrl.h"
#include "TeamCtrl.h"
#include "GameSession.h"
#include "CaptureScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbRescueFrameLayer::~CcbRescueFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFInfo);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCatRes);
    CC_SAFE_RELEASE_NULL(m_pSpriteCR);
}

//-- copy this to CcbManager 
/*
//CcbManager.h


//CcbManager.cpp

*/


bool CcbRescueFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbRescueFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbRescueFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbRescueFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbRescueFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbRescueFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFInfo", CCLabelTTF*, this->m_pLabelTTFInfo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCatRes", CCControlButton*, this->m_pControlButtonCatRes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCR", CCSprite*, this->m_pSpriteCR);
	return false;
}

bool CcbRescueFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbRescueFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbRescueFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbRescueFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCatRes", CcbRescueFrameLayer::onPressControlButtonCatRes);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbRescueFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}



void CcbRescueFrameLayer::onPressControlButtonCatRes(CCObject* pSender, CCControlEvent event)
{
	//
    if (m_bMove) {
        return;
    }
    int idx = dynamic_cast<CCControlButton*>(pSender)->getTag();
//    FriendCtrl::STC_USER_INFO stcInfo = FriendCtrl::m_vecFriend[idx];
    FriendCtrl::STC_USER_INFO stcInfo = FriendCtrl::Get()->resCapUserAtIdx(idx);
    if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromCapture) {
        // zhua ren
        //#define CMD_CS_BATTLE_CAPTURE_SLAVE		CMD_MAKE_CLIENT(0x0033) // 抓奴隶　战斗　{ uint32 dwObjId + uint8 byType + uint8 byFarmId }
        CGameSession::SendCaptureSlave(stcInfo.dwRoleId, CaptureCtrl::byCurType, CaptureCtrl::byCurFarmId);
    } else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromRescue) {
        // jie jiu
        CGameSession::SendSlaveHelp(stcInfo.dwRoleId);
    }
}

#pragma mark Public
void CcbRescueFrameLayer::SetData(int idx)
{
//    FriendCtrl::STC_USER_INFO stcInfo = FriendCtrl::m_vecFriend[idx];
    FriendCtrl::STC_USER_INFO stcInfo = FriendCtrl::Get()->resCapUserAtIdx(idx);
//    CCString* cstring;
    if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromCapture) {
        //TODO: 修改为“抓捕”文字}
//        cstring = CCString::create("抓取");
//        m_pControlButtonCatRes->setTitleForState(cstring, CCControlStateNormal);
    } else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromRescue) {
        //TODO: 修改为“解救文字”}
//        cstring = CCString::create("解救");
//        m_pControlButtonCatRes->setTitleForState(cstring, CCControlStateNormal);
    } else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendList) {
        m_pControlButtonCatRes->setVisible(false);
    }
    m_pControlButtonCatRes->setTag(idx);
    CCString* lvString = CCString::createWithFormat("%d", stcInfo.wRoleLv);
    m_pLabelTTFLv->setString(lvString->getCString());
    m_pLabelTTFName->setString(stcInfo.strName.c_str());
    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(CTeamCtrl::GetCurTeamLeaderPath());
    m_pSpriteIcon->setTexture(tex);
    
    
}

void CcbRescueFrameLayer::setUpDownBound(float fUp, float fDown)
{
    //TODO: 将ControlButton修改为ScrollButton}
    m_fUpBound = fUp;
    m_fDownBound = fDown;
}

#pragma mark ccTouch Delegate
bool CcbRescueFrameLayer::TouchInTable(CCPoint point) {
    if (point.y >= m_fDownBound && point.y <= m_fUpBound) {
        return true;
    }
    return false;
}

void CcbRescueFrameLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool CcbRescueFrameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bMove = false;
    m_pStart = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    if (!TouchInTable(m_pStart)) {
        m_bMove = true;
        return false;
    }
    return true;
}

void CcbRescueFrameLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!TouchInTable(m_pStart)) {
        return;
    }
    CCPoint movePoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    if (fabsf(movePoint.y - m_pStart.y) > 6.0) {
        m_bMove = true;
    }
}




