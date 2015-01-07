#include "CcbEquipCompoundListLayer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "CcbEquipCompoundFrame1Layer.h"
#include "GuideData.h"
#include "PacketDataMgr.h"
#include "UISupport.h"
#include "MusicCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbEquipCompoundListLayer::~CcbEquipCompoundListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonType1);
	CC_SAFE_RELEASE_NULL(m_pControlButtonType2);
	CC_SAFE_RELEASE_NULL(m_pControlButtonType3);
	CC_SAFE_RELEASE_NULL(m_pControlButtonType4);
	CC_SAFE_RELEASE_NULL(m_pControlButtonType5);
	CC_SAFE_RELEASE_NULL(m_pLayerEquipBg);
	CC_SAFE_RELEASE_NULL(m_pLayerParent);
    CC_SAFE_RELEASE_NULL(m_tableView);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEquipCompoundListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEquipCompoundListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEquipCompoundListLayer", CcbEquipCompoundListLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_compound_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEquipCompoundListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    //g_EquipData->SetEquipCompoundLayer(this);
    m_emShowTabType = g_EquipData->GetCompoundTabType();
    return true;
}

void CcbEquipCompoundListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEquipCompoundListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
//    this->runAction( CCSequence::create(CCDelayTime::create(TRANS_DUR*0.5), CCCallFunc::create(this, callfunc_selector(CcbEquipCompoundListLayer::addGuideLayer)), NULL) );
    
    m_tableView->reloadData();
    
}

//void CcbEquipCompoundListLayer::addGuideLayer()
//{
//    GuideData::GetInstance()->addGuideofEnum(GuideData::E_SYS_GUIDE_COUNTRY_2, NULL);
//}

void CcbEquipCompoundListLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEquipCompoundListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEquipCompoundListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType1", CCControlButton*, this->m_pControlButtonType1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType2", CCControlButton*, this->m_pControlButtonType2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType3", CCControlButton*, this->m_pControlButtonType3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType4", CCControlButton*, this->m_pControlButtonType4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType5", CCControlButton*, this->m_pControlButtonType5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquipBg", CCLayer*, this->m_pLayerEquipBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent", CCLayer*, this->m_pLayerParent);
    
	return false;
}

bool CcbEquipCompoundListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEquipCompoundListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEquipCompoundListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEquipCompoundListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonType1", CcbEquipCompoundListLayer::onPressControlButtonType1);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonType2", CcbEquipCompoundListLayer::onPressControlButtonType2);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonType3", CcbEquipCompoundListLayer::onPressControlButtonType3);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonType4", CcbEquipCompoundListLayer::onPressControlButtonType4);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonType5", CcbEquipCompoundListLayer::onPressControlButtonType5);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipCompoundListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CreateRunesList();
    ChangeTab();
    m_clipRect.origin = getWorldPos(m_pLayerEquipBg);
    m_clipRect.size = m_pLayerEquipBg->getContentSize();
    
    
    m_tableView = CCTableView::create(this, m_pLayerEquipBg->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->setDelegate(this);
    m_tableView->retain();
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_pLayerEquipBg->addChild(m_tableView);
    
}

CCSize CcbEquipCompoundListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerEquipBg), 79 + 3);
}

CCTableViewCell* CcbEquipCompoundListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbEquipCompoundFrame1Layer(this);
        pNode->setPosition(ccp(getWidth(m_pLayerEquipBg)*0.5, 0));
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    CcbEquipCompoundFrame1Layer* pNode = (CcbEquipCompoundFrame1Layer*)pCell->getChildByTag(123);
    
    if (pNode)
    {
        pNode->setClipRect(m_clipRect);
        pNode->loadData(m_vecRuneList[m_emShowTabType][idx]);
    }
    return pCell;
}

unsigned int CcbEquipCompoundListLayer::numberOfCellsInTableView(CCTableView *table)
{
    return m_vecRuneList[m_emShowTabType].size();
}

void CcbEquipCompoundListLayer::onPressControlButtonType1(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    m_emShowTabType = SHOW_TAB_ATTRI_HP;
    ChangeTab();
    m_tableView->reloadData();
}

void CcbEquipCompoundListLayer::onPressControlButtonType2(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    m_emShowTabType = SHOW_TAB_ATTRI_ATK;
    ChangeTab();
    m_tableView->reloadData();
}

void CcbEquipCompoundListLayer::onPressControlButtonType3(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    m_emShowTabType = SHOW_TAB_ATTRI_DEF;
    ChangeTab();
    m_tableView->reloadData();
}

void CcbEquipCompoundListLayer::onPressControlButtonType4(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    m_emShowTabType = SHOW_TAB_ATTRI_REV;
    ChangeTab();
    m_tableView->reloadData();
}

void CcbEquipCompoundListLayer::onPressControlButtonType5(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    m_emShowTabType = SHOW_TAB_ATTRI_CRIT;
    ChangeTab();
    m_tableView->reloadData();
}

void CcbEquipCompoundListLayer::CreateRunesList()
{
    for (int i = 0; i < 5; i++)
    {
        m_vecRuneList[i].clear();
    }
    
    map<uint32, RUNE_CONFIG_DATA> mapRuneList = GET_CONFIG_MAP(RuneConfig);
    map<uint32, RUNE_CONFIG_DATA>::iterator iter = mapRuneList.begin();
    for (; iter != mapRuneList.end(); iter++)
    {

        if (iter->second.dwIndex % 10 == 1)//过滤掉1级符文}
        {
            continue;
        }
        m_vecRuneList[iter->second.byEffectType1 - 1].push_back(iter->first);
    }
}

void CcbEquipCompoundListLayer::ChangeTab()
{
    CCControlButton* pButton[5];
    pButton[0] = m_pControlButtonType1;
    pButton[1] = m_pControlButtonType2;
    pButton[2] = m_pControlButtonType3;
    pButton[3] = m_pControlButtonType4;
    pButton[4] = m_pControlButtonType5;
    
    for (int i = 0; i < 5; i++)
    {
        if (i == m_emShowTabType)//m_nTabType 从0到5}
        {
            pButton[i]->setEnabled(false);
            pButton[i]->setZOrder(2);
        }
        else
        {
            pButton[i]->setEnabled(true);
            pButton[i]->setZOrder(1);
        }
    }
    g_EquipData->SetCompoundTabType(m_emShowTabType);
}
