#include "CcbEventAnnounceFrame.h"
//#include "CcbManager.h"
#include "UISupport.h"
#include "EventDataMgr.h"
#include "Instruments.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbEventAnnounceFrame::~CcbEventAnnounceFrame()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDesText);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDesTitle);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
    CC_SAFE_RELEASE_NULL(m_pNodeTitle);
    CC_SAFE_RELEASE_NULL(m_pLayerDes);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFFuliTitle);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFFuliText);
    CC_SAFE_RELEASE_NULL(m_pLayerFuli);
    CC_SAFE_RELEASE_NULL(m_pScale9Sprite_bg);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventAnnounceFrame( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventAnnounceFrame( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventAnnounceFrame", CcbEventAnnounceFrameLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_announce_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventAnnounceFrame::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEventAnnounceFrame::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbEventAnnounceFrame::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEventAnnounceFrame::onExit()
{
	CCLayer::onExit();
}

void CcbEventAnnounceFrame::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventAnnounceFrame::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDesText", CCLabelTTF*, this->m_pLabelTTFDesText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDesTitle", CCLabelTTF*, this->m_pLabelTTFDesTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTitle", CCNode*, this->m_pNodeTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDes", CCLayer*, this->m_pLayerDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFuliTitle", CCLabelTTF*, this->m_pLabelTTFFuliTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFuliText", CCLabelTTF*, this->m_pLabelTTFFuliText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerFuli", CCLayer*, this->m_pLayerFuli);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9Sprite_bg", CCScale9Sprite*, this->m_pScale9Sprite_bg);

	return false;
}

bool CcbEventAnnounceFrame::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbEventAnnounceFrame::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventAnnounceFrame::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventAnnounceFrame::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventAnnounceFrame::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pLabelTTFDesText->setDimensions(CCSizeMake(getWidth(m_pLayerDes) - 10, 0));
    m_pLabelTTFFuliText->setDimensions(CCSizeMake(getWidth(m_pLayerFuli) - 10, 0));
    m_pCountDown = ReCountDown::create();
    this->addChild(m_pCountDown);
    m_pCountDown->setDelegate(this);
}

float CcbEventAnnounceFrame::loadData(STC_EVENT_ANNOUNCE_INFO annInfo)
{
    m_pLabelTTFDesText->setString(annInfo.titleDes.c_str());
    m_pLabelTTFFuliText->setString(annInfo.fuliDes.c_str());
    
    m_pLabelTTFDesTitle->setString(annInfo.titleName.c_str());
    
    m_pCountDown->setTime(annInfo.leftTime);
    m_pCountDown->startUpdateCountDown();
    //重算高度
    m_pLabelTTFFuliText->setPositionY(5);
    m_pLabelTTFFuliTitle->setPositionY(getTop(m_pLabelTTFFuliText)+3);
    m_pLayerFuli->setContentSize(CCSizeMake(getWidth(m_pLayerFuli), getTop(m_pLabelTTFFuliTitle)));
    
    m_pLabelTTFDesText->setPositionY(5);
    m_pNodeTitle->setPositionY(getTop(m_pLabelTTFDesText));
    m_pLayerDes->setContentSize(CCSizeMake(getWidth(m_pLayerDes), getTop(m_pNodeTitle)));
    
    m_pLayerFuli->setPositionY(0);
    m_pLayerDes->setPositionY(getHeight(m_pLayerFuli));
    
    this->setContentSize(CCSizeMake(getWidth(this), getTop(m_pLayerDes) + 5));
    m_pScale9Sprite_bg->setPreferredSize(this->getContentSize());
    
    return this->getContentSize().height;
}

void CcbEventAnnounceFrame::countDownScheduleCallBack(float cTime, CountType type)
{
    if (type == ENUM_UPDATE) {
        m_pLabelTTFTime->setString(getLeftDayTimeChFormatFromInt(cTime)->getCString());
    }
    else if (type == ENUM_COMPLETE)
    {
        m_pLabelTTFTime->setString(GET_STR(Str_Active_end));
    }
}






