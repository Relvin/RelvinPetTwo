#include "CcbSettingsLayer.h"
#include "CcbManager.h"
#include "MailDataMgr.h"
#include "MainLayer.h"
#include "UISupport.h"
#include "CcbSysFriendFrameLayer.h"

CcbSettingsLayer::~CcbSettingsLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerView);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbSettingsLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbSettingsLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbSettingsLayer", CcbSettingsLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/settings.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbSettingsLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
    CMailDataMgr::Get()->SetSettingLayerPt(this);
    
    STC_SETTING sTujian;
    sTujian.strName = "宠物图鉴";
    sTujian.nTag = CcbSysFriendFrameLayer::kSettingTujian;
    m_vecSetting.push_back(sTujian);
    
    STC_SETTING sAnnounce;
    sAnnounce.strName = "系统公告";
    sAnnounce.nTag = CcbSysFriendFrameLayer::kSettingAnnounce;
    m_vecSetting.push_back(sAnnounce);
    
    STC_SETTING sInformation;
    sInformation.strName = "个人中心";
    sInformation.nTag = CcbSysFriendFrameLayer::kSettingInformation;
    m_vecSetting.push_back(sInformation);
    
	return true;
}

void CcbSettingsLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbSettingsLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    m_tableView->reloadData();
}

void CcbSettingsLayer::onExit()
{
	CCLayer::onExit();
    CMailDataMgr::Get()->SetSettingLayerPt(NULL);
}

void CcbSettingsLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbSettingsLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerView", CCLayer*, this->m_pLayerView);

	return false;
}

bool CcbSettingsLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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

// Inhert CCNodeLoaderListener
void CcbSettingsLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pLayerView->setContentSize(CCSizeMake(getWidth(m_pLayerView), getBottom(getChildByTag(333)) - getWorldPos(m_pLayerView).y + 5));
    
    m_tableView = CCTableView::create(this, m_pLayerView->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_tableView->setBounceable(false);
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_pLayerView->addChild(m_tableView);
}

void CcbSettingsLayer::registerWithTouchDispatcher()
{

}

bool CcbSettingsLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

CCSize CcbSettingsLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(m_fCellWidth, m_fCellHeight + 10.0f);
}

CCTableViewCell* CcbSettingsLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
    
        CcbSysFriendFrameLayer* pNode = dynamic_cast<CcbSysFriendFrameLayer*>(CcbManager::sharedManager()->LoadCcbSysFriendFrameLayer(this));
        if (!pNode) {
            return NULL;
        }
        
        m_fCellWidth = pNode->getContentSize().width;
        m_fCellHeight = pNode->getContentSize().height;
        
        pNode->setNodeData(m_vecSetting[idx].strName, m_vecSetting[idx].nTag);
        pNode->setPosition(ccp(160.0f, 0.0f));
        
        pCell->addChild(pNode);
        pNode->setTag(123);
    } else {
        CcbSysFriendFrameLayer* pNode = dynamic_cast<CcbSysFriendFrameLayer*>(pCell->getChildByTag(123));
        if (!pNode) {
            return NULL;
        }
        pNode->setNodeData(m_vecSetting[idx].strName, m_vecSetting[idx].nTag);
    }

    return pCell;
}

unsigned int CcbSettingsLayer::numberOfCellsInTableView(CCTableView *table)
{
    return m_vecSetting.size();
}



