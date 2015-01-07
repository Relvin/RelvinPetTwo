#include "CcbEquipListLayer.h"
#include "CcbManager.h"
#include "EquipDataMgr.h"
#include "PacketDataMgr.h"
#include "UISupport.h"
#include "BackCtrl.h"
#include "PetLoadingLayer.h"
#include "GameSession.h"
#include "GuideData.h"
#include "CcbPetShowLayer.h"

#include <algorithm>

CcbEquipListLayer::~CcbEquipListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteLine);
	CC_SAFE_RELEASE_NULL(m_pLayerEquipBg);
	CC_SAFE_RELEASE_NULL(m_pLayerEquipFrame);
	CC_SAFE_RELEASE_NULL(m_pLayerParent);
	CC_SAFE_RELEASE_NULL(m_pLayerBack);
	CC_SAFE_RELEASE_NULL(m_pLayerHead);

    CGameSession::Detach(this);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEquipListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEquipListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEquipListLayer", CcbEquipListLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/equip_normal_frame.ccb]", [ccb/equip_normal_frame.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back2.ccb]", [ccb/header_back2.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEquipListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CGameSession::Attach(this);
	return true;
}

void CcbEquipListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEquipListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    loadData();
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbEquipListLayer::addGuideLayer)),
                                       NULL
                                       )
                    ) ;
}

void CcbEquipListLayer::addGuideLayer() {
//    GuideData::GetInstance()->addGuideofEnum(
//                                             GuideData::E_SYS_GUIDE_6_TOWER,
//                                             NULL
//                                             );
}

void CcbEquipListLayer::onExit()
{
	CCLayer::onExit();
    m_offset = m_table->getContentOffset();
    g_EquipData->SetEquipOffset(m_offset);
}

void CcbEquipListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEquipListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLine", CCSprite*, this->m_pSpriteLine);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquipBg", CCLayer*, this->m_pLayerEquipBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquipFrame", CcbEquipNormalFrameLayer*, this->m_pLayerEquipFrame);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent", CCLayer*, this->m_pLayerParent);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBack", CCLayer*, this->m_pLayerBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHead", CCLayer*, this->m_pLayerHead);

	return false;
}

bool CcbEquipListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEquipListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_MenuHandler CcbEquipListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler CcbEquipListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    g_EquipData->SetNeedJumpScene(false);
    
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pos = getWorldPos(m_pLayerEquipBg);
    
    if (g_EquipData->GetEquipListShowMode() == E_SHOW_LIST_PET
        && g_EquipData->GetDressEquipKeyID()) {
        m_pLayerEquipFrame->setVisible(true);
        m_pSpriteLine->setVisible(true);
        m_pLayerEquipFrame->loadData(g_EquipData->GetDressEquipKeyID());
        m_pLayerEquipFrame->setFrameType(E_EQUIP_FRAME_DOWN);
        
        //隐藏mainhead}
        m_pLayerHead->setVisible(false);
        m_pLayerParent->setPositionY(winsize.height);
        //扩大table区域}
        m_pLayerEquipBg->setContentSize(CCSizeMake(getWidth(m_pLayerEquipBg), getBottom(m_pLayerParent) - pos.y));
    }
    else{
        m_pLayerEquipFrame->setVisible(false);
        m_pSpriteLine->setVisible(false);
        m_pLayerHead->setVisible(true);
        
        m_pLayerParent->setPositionY(getBottom(m_pLayerHead));
        //扩大table区域}
        m_pLayerEquipBg->setContentSize(CCSizeMake(getWidth(m_pLayerEquipBg), getBottom(m_pLayerParent) + getBottom(m_pLayerBack) - pos.y + 5));
    }
    
    clipRect.origin = pos;
    clipRect.size = m_pLayerEquipBg->getContentSize();
    
    m_table = CCTableView::create(this, m_pLayerEquipBg->getContentSize());
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setPosition(getWidth(m_pLayerEquipBg)* 0.5, getHeight(m_pLayerEquipBg)*0.5);
    m_table->setAnchorPoint(ccp(0.5, 0.5));
    m_table->ignoreAnchorPointForPosition(false);
    m_pLayerEquipBg->addChild(m_table);
}

CCSize CcbEquipListLayer::cellSizeForTable(CCTableView *table)
{
    return CCSize(getWidth(m_pLayerEquipBg), 91 + 5);
}

CCTableViewCell* CcbEquipListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CcbEquipNormalFrameLayer* pNode = dynamic_cast<CcbEquipNormalFrameLayer*>(CcbManager::sharedManager()->LoadCcbEquipNormalFrameLayer(this));
        pNode->setPosition(getWidth(m_pLayerEquipBg) *0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pNode->setClipRect(clipRect);
        
        switch (g_EquipData->GetEquipListShowMode()) {
            case E_SHOW_LIST_PET:
                pNode->setFrameType(E_EQUIP_FRAME_WEAR);
                break;
            case E_SHOW_LIST_ALL:
                pNode->setFrameType(E_EQUIP_FRAME_ENHANCE);
                break;
            case E_SHOW_LIST_INPLAY:
                pNode->setFrameType(E_EQUIP_FRAME_RUNE);
                break;
            default:
                break;
        }
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbEquipNormalFrameLayer* pNode = (CcbEquipNormalFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->loadData(m_vecId[idx]);
    }
    return pCell;
}

unsigned int CcbEquipListLayer::numberOfCellsInTableView(CCTableView *table)
{
    return m_vecId.size();
}

void CcbEquipListLayer::RefeashLayer()
{
    PetLoadingLayer::sharedLayer()->End();
    if (g_EquipData->IsNeedJumpScene() && BackCtrl::GetCurSceneIdx() == kEquipListScene)
    {
        BackCtrl::BacktoUpperScene();
    }
}
void CcbEquipListLayer::loadData()
{
    m_vecId.clear();
    vector<uint32>tempList = g_EquipData->GetVecShowEquipKeyID();
    uint8 type = g_EquipData->GetEquipListShowMode();
    uint32 equipId = g_EquipData->GetDressEquipKeyID();
    uint8 part = g_EquipData->GetDressEquipPart();
    for (int i = 0; i < tempList.size(); i++)
    {
        if (type == E_SHOW_LIST_PET)
        {
            if (equipId == tempList[i])
            {
                continue;
            }
            const CEquip* equip = g_PacketDataMgr->GetEquipInfoByKeyID(tempList[i]);
            if (!equip || equip->GetConfigData().byPos != part)
            {
                continue;
            }
        }
        m_vecId.push_back(tempList[i]);
    }
    
    sort(m_vecId.begin(), m_vecId.end(), CcbPetShowLayer::cmpEquip);
    
    m_offset = g_EquipData->GetEquipOffset();
    m_table->reloadData();
    float contentH = numberOfCellsInTableView(m_table)*cellSizeForTable(m_table).height;

    if (m_offset.y > 0 || m_offset.y < m_table->getViewSize().height - contentH) {
        m_offset = ccp(0, m_table->getViewSize().height - contentH);
    }
    m_table->setContentOffset(m_offset);
}






