#include "CcbSystemNoticeFrameLayer.h"
#include "ReRichText.h"
#include "SystemNoticeDataMgr.h"
#include "ResourceDefine.h"
#include "UISupport.h"

CcbSystemNoticeFrameLayer::~CcbSystemNoticeFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteBG);
	CC_SAFE_RELEASE_NULL(m_pLayerTitle);

}


bool CcbSystemNoticeFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbSystemNoticeFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbSystemNoticeFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbSystemNoticeFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbSystemNoticeFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbSystemNoticeFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteBG", CCScale9Sprite*, this->m_pScale9SpriteBG);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTitle", CCLayer*, this->m_pLayerTitle);

	return false;
}

bool CcbSystemNoticeFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbSystemNoticeFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbSystemNoticeFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbSystemNoticeFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbSystemNoticeFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}


void CcbSystemNoticeFrameLayer::CreatNoticeText()
{
    SYSTEM_NOTICE_INFO showInfo = g_SystemNoticeDataMgr->GetNoticeInfoFromMap(getLocalTag());
   
    CCLabelTTF* pTitleText = (CCLabelTTF*)getChildByTag(123);
    if (!pTitleText)
    {
        pTitleText = CCLabelTTF::create("", FONT_FZCQJW, 16, CCSize(260, 0), kCCTextAlignmentCenter);
        addChild(pTitleText, 1, 123);
        pTitleText->setPosition(ccp(getWidth(m_pScale9SpriteBG)*0.5 - 8, getHeight(m_pScale9SpriteBG)*0.5));
        pTitleText->setAnchorPoint(ccp(0.5, 1));
        pTitleText->ignoreAnchorPointForPosition(false);
//        pTitleText->setEnableStroke(ccBLACK);
        pTitleText->setColor(ccWHITE);
    }
    pTitleText->setString(showInfo.title.c_str());
    
    ReRichText* pContentText = (ReRichText*)getChildByTag(1234);
    if (!pContentText)
    {
        pContentText = ReRichText::create("", FONT_HEL, 10, CCSize(260, 0), kCCTextAlignmentLeft);
        this->addChild(pContentText, 1, 1234);
    }
    pContentText->setString(showInfo.content.c_str());
    pContentText->setAnchorPoint(ccp(0.5, 1));
    pContentText->ignoreAnchorPointForPosition(false);
    //TODO: change temporary, will change later
    pContentText->setColor(ccc3(236, 224, 182));
    
    CCSize sizeBg;
    sizeBg.height = pTitleText->getContentSize().height + pContentText->getContentSize().height + 20;
    sizeBg.width = getWidth(m_pScale9SpriteBG);
    m_pScale9SpriteBG->setContentSize(sizeBg);
    
    pTitleText->setPositionY(getTop(m_pScale9SpriteBG) - 5);
    pContentText->setPosition(ccp(getWidth(m_pScale9SpriteBG)*0.5 - 8, getBottom(pTitleText) - 5));
    
//    CCLayerColor* laTit = dynamic_cast<CCLayerColor*>(getChildByTag(111));
//    if (!laTit) {
//        laTit = CCLayerColor::create(ccc4(0, 0, 0, 255));
//        laTit->setAnchorPoint(pTitleText->getAnchorPoint());
//        laTit->ignoreAnchorPointForPosition(false);
//        addChild(laTit, 0, 111);
//    }
//    laTit->setPosition(pTitleText->getPosition());
//    laTit->setContentSize(pTitleText->getContentSize());
//    
//    CCLayerColor* laCon = dynamic_cast<CCLayerColor*>(getChildByTag(112));
//    if (!laCon) {
//        laCon = CCLayerColor::create(ccc4(0, 0, 0, 255));
//        laCon->setAnchorPoint(pContentText->getAnchorPoint());
//        laCon->ignoreAnchorPointForPosition(false);
//        addChild(laCon, 0, 112);
//    }
//    laCon->setPosition(pContentText->getPosition());
//    laCon->setContentSize(pContentText->getContentSize());
    
    m_Localsize = sizeBg;
    m_Localsize.height += 5;
}


