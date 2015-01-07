#include "CcbTowerRewardListLayer.h"
#include "CcbManager.h"
#include "CcbTowerRewardFrameLayer.h"
#include "TowerDataMgr.h"
#include "ConfigGet.h"
#include "CcbItemInfoButtonLayer.h"
#include "EnumDefines.h"
#include "ResourceStringClient.h"
#include "PacketDataMgr.h"
#include "UISupport.h"
#include "MusicCtrl.h"

CcbTowerRewardListLayer::~CcbTowerRewardListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerViewSize);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_tableView);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTowerRewardListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTowerRewardListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTowerRewardListLayer", CcbTowerRewardListLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_boxlist.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbTowerRewardListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbTowerRewardListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbTowerRewardListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    m_tableView->reloadData();
}

void CcbTowerRewardListLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTowerRewardListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTowerRewardListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerViewSize", CCLayer*, this->m_pLayerViewSize);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);

	return false;
}

bool CcbTowerRewardListLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTowerRewardListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTowerRewardListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTowerRewardListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbTowerRewardListLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTowerRewardListLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CreateShowList();
    
    m_tableView = CCTableView::create(this, m_pLayerViewSize->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->retain();
    m_tableView->setTouchPriority(2*kCCMenuHandlerPriority - 1);
    
    m_pLayerViewSize->addChild(m_tableView);
}

void CcbTowerRewardListLayer::CreateShowList()
{
    STC_SHOW_LIST tempInfo;
    m_vecShowList.clear();
    std::map<uint16, TowerConfig::STC_TOWER_CONFIG> mapTower = GET_CONFIG_MAP(TowerConfig);
    std::map<uint16, TowerConfig::STC_TOWER_CONFIG>::iterator it = mapTower.begin();
    for (; it != mapTower.end(); it++)
    {
        if(!it->first){
            continue;
        }
        TowerConfig::STC_TOWER_CONFIG pConfig = it->second;
        if (pConfig.byIsSpecial == 1)
        {
            tempInfo.wIndex = pConfig.wIndex;
            for (int k = 0; k < 4; k++)
            {
                tempInfo.dwRewardID[k] = pConfig.dwRewardID[k];
                tempInfo.dwRewardCount[k] = pConfig.dwRewardCount[k];
            }
            
            m_vecShowList.push_back(tempInfo);
        }
        
    }
}

void CcbTowerRewardListLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 1);
}

bool CcbTowerRewardListLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbTowerRewardListLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
//    getParent()->removeChild(this);
    removeFromParent();
}


CCSize CcbTowerRewardListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerViewSize), 95);
}

CCTableViewCell* CcbTowerRewardListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbTowerRewardFrameLayer(this);
        pNode->setPosition(getWidth(m_pLayerViewSize)*0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbTowerRewardFrameLayer *pNode = (CcbTowerRewardFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->CreateRewardData(m_vecShowList[idx].wIndex);
    }//end if (pNode)
    
    return pCell;
}

unsigned int CcbTowerRewardListLayer::numberOfCellsInTableView(CCTableView *table)
{
    return m_vecShowList.size();
}




