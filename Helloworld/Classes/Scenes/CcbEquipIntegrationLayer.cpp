#include "CcbEquipIntegrationLayer.h"
#include "CcbManager.h"
#include "CcbPetShowLayer.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "PacketDataMgr.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "TeamCtrl.h"
#include "PetCtrl.h"
#include "Team.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "GuideData.h"
#include "StageScene.h"
#include "CcbDropTipLayer.h"
#include "GuideBtnPos.h"
#include "FlyTextLayer.h"

#include <algorithm>

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

CcbEquipIntegrationScene::CcbEquipIntegrationScene()
{
    m_pLabelTTFName = NULL;
}

CcbEquipIntegrationScene::~CcbEquipIntegrationScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbEquipIntegrationScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbEquipIntegrationScene* pLayer = CcbEquipIntegrationScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbEquipIntegrationScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbEquipIntegrationScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbEquipIntegrationLayer(this));
    return true;
}

void CcbEquipIntegrationScene::onEnter()
{
	CCLayer::onEnter();
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setString("强化进化");
    }
    
}

void CcbEquipIntegrationScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipIntegrationScene::onExit()
{
//    CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_TEAM);
	CCLayer::onExit();
}

void CcbEquipIntegrationScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}


CcbEquipIntegrationLayer::~CcbEquipIntegrationLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonPet_1);
    CC_SAFE_RELEASE_NULL(m_pLayerPet1);
    CC_SAFE_RELEASE_NULL(m_pSpriteCanChange_1);
    CC_SAFE_RELEASE_NULL(m_pControlButtonPet_2);
    CC_SAFE_RELEASE_NULL(m_pLayerPet2);
    CC_SAFE_RELEASE_NULL(m_pSpriteCanChange_2);
    CC_SAFE_RELEASE_NULL(m_pControlButtonPet_3);
    CC_SAFE_RELEASE_NULL(m_pLayerPet3);
    CC_SAFE_RELEASE_NULL(m_pSpriteCanChange_3);
    CC_SAFE_RELEASE_NULL(m_pControlButtonPet_4);
    CC_SAFE_RELEASE_NULL(m_pLayerPet4);
    CC_SAFE_RELEASE_NULL(m_pSpriteCanChange_4);
    CC_SAFE_RELEASE_NULL(m_pControlButtonPet_5);
    CC_SAFE_RELEASE_NULL(m_pLayerPet5);
    CC_SAFE_RELEASE_NULL(m_pSpriteCanChange_5);
    CC_SAFE_RELEASE_NULL(m_pControlButtonPet_6);
    CC_SAFE_RELEASE_NULL(m_pLayerPet6);
    CC_SAFE_RELEASE_NULL(m_pSpriteCanChange_6);
    CC_SAFE_RELEASE_NULL(m_pNodePetSelect);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEquipStrengthen);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEquipEvo);
    CC_SAFE_RELEASE_NULL(m_pLayerList);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNothing_go);
    CC_SAFE_RELEASE_NULL(m_pControlButtonQuest);
    CC_SAFE_RELEASE_NULL(m_pSpriteQuest);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEquip_1);
    CC_SAFE_RELEASE_NULL(m_pSpritePlus_1);
    CC_SAFE_RELEASE_NULL(m_pLayerEquipIcon_1);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEquip_2);
    CC_SAFE_RELEASE_NULL(m_pSpritePlus_2);
    CC_SAFE_RELEASE_NULL(m_pLayerEquipIcon_2);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEquip_3);
    CC_SAFE_RELEASE_NULL(m_pSpritePlus_3);
    CC_SAFE_RELEASE_NULL(m_pLayerEquipIcon_3);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEquip_4);
    CC_SAFE_RELEASE_NULL(m_pSpritePlus_4);
    CC_SAFE_RELEASE_NULL(m_pLayerEquipIcon_4);
    CC_SAFE_RELEASE_NULL(m_pNodeEquipSelect);
    CC_SAFE_RELEASE_NULL(m_pControlButtonChange);
    CC_SAFE_RELEASE_NULL(m_pSpriteCanChange);
    CC_SAFE_RELEASE_NULL(m_pNodeEquipEnh);
    
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEquipIntegrationLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEquipIntegrationLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEquipIntegrationLayer", CcbEquipIntegrationLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back2.ccb]", [ccb/header_back2.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_integration.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEquipIntegrationLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbEquipIntegrationLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPet_1", CCControlButton*, this->m_pControlButtonPet_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet1", CcbPetIcon*, this->m_pLayerPet1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanChange_1", CCSprite*, this->m_pSpriteCanChange_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPet_2", CCControlButton*, this->m_pControlButtonPet_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet2", CcbPetIcon*, this->m_pLayerPet2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanChange_2", CCSprite*, this->m_pSpriteCanChange_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPet_3", CCControlButton*, this->m_pControlButtonPet_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet3", CcbPetIcon*, this->m_pLayerPet3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanChange_3", CCSprite*, this->m_pSpriteCanChange_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPet_4", CCControlButton*, this->m_pControlButtonPet_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet4", CcbPetIcon*, this->m_pLayerPet4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanChange_4", CCSprite*, this->m_pSpriteCanChange_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPet_5", CCControlButton*, this->m_pControlButtonPet_5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet5", CcbPetIcon*, this->m_pLayerPet5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanChange_5", CCSprite*, this->m_pSpriteCanChange_5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPet_6", CCControlButton*, this->m_pControlButtonPet_6);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet6", CcbPetIcon*, this->m_pLayerPet6);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanChange_6", CCSprite*, this->m_pSpriteCanChange_6);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePetSelect", CCNode*, this->m_pNodePetSelect);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquipStrengthen", CCControlButton*, this->m_pControlButtonEquipStrengthen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquipEvo", CCControlButton*, this->m_pControlButtonEquipEvo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerList", CCLayer*, this->m_pLayerList);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNothing_go", CCLabelTTF*, this->m_pLabelTTFNothing_go);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonQuest", CCControlButton*, this->m_pControlButtonQuest);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteQuest", CCSprite*, this->m_pSpriteQuest);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquip_1", CCControlButton*, this->m_pControlButtonEquip_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePlus_1", CCSprite*, this->m_pSpritePlus_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquipIcon_1", CcbItemIconLayer*, this->m_pLayerEquipIcon_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquip_2", CCControlButton*, this->m_pControlButtonEquip_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePlus_2", CCSprite*, this->m_pSpritePlus_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquipIcon_2", CcbItemIconLayer*, this->m_pLayerEquipIcon_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquip_3", CCControlButton*, this->m_pControlButtonEquip_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePlus_3", CCSprite*, this->m_pSpritePlus_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquipIcon_3", CcbItemIconLayer*, this->m_pLayerEquipIcon_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquip_4", CCControlButton*, this->m_pControlButtonEquip_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePlus_4", CCSprite*, this->m_pSpritePlus_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquipIcon_4", CcbItemIconLayer*, this->m_pLayerEquipIcon_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquipSelect", CCNode*, this->m_pNodeEquipSelect);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonChange", CCControlButton*, this->m_pControlButtonChange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanChange", CCSprite*, this->m_pSpriteCanChange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEquipEnh", CCNode*, this->m_pNodeEquipEnh);
    
	return false;
}

bool CcbEquipIntegrationLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEquipIntegrationLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEquipIntegrationLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEquipIntegrationLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonPet", CcbEquipIntegrationLayer::onPressControlButtonPet);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEquip", CcbEquipIntegrationLayer::onPressControlButtonEquip);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonChange", CcbEquipIntegrationLayer::onPressControlButtonChange);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonQuest", CcbEquipIntegrationLayer::onPressControlButtonQuest);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEquipTab", CcbEquipIntegrationLayer::onPressControlButtonEquipTab);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipIntegrationLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    clipRect.origin = getWorldPos(m_pLayerList);
    clipRect.size = m_pLayerList->getContentSize();
    
    m_selectEquip = -1;
    m_pSpriteCanChange->setVisible(false);
    
    arrPlus.clear();
    arrPlus.push_back(m_pSpritePlus_1);
    arrPlus.push_back(m_pSpritePlus_2);
    arrPlus.push_back(m_pSpritePlus_3);
    arrPlus.push_back(m_pSpritePlus_4);
    
    arrEquipBtn.clear();
    arrEquipBtn.push_back(m_pControlButtonEquip_1);
    arrEquipBtn.push_back(m_pControlButtonEquip_2);
    arrEquipBtn.push_back(m_pControlButtonEquip_3);
    arrEquipBtn.push_back(m_pControlButtonEquip_4);
    
    arrEquipIcon.clear();
    arrEquipIcon.push_back(m_pLayerEquipIcon_1);
    arrEquipIcon.push_back(m_pLayerEquipIcon_2);
    arrEquipIcon.push_back(m_pLayerEquipIcon_3);
    arrEquipIcon.push_back(m_pLayerEquipIcon_4);
    for (int i = 0; i < arrPlus.size(); i++) {
        arrPlus[i]->setVisible(false);
        arrPlus[i]->runAction(CCRepeatForever::create(
                                                      CCSequence::create(CCFadeOut::create(1.5),
                                                                         CCFadeIn::create(1.5),
                                                                         NULL)));
        arrEquipBtn[i]->setTag(i);
    }
    
    arrCanChange.clear();
    arrCanChange.push_back(m_pSpriteCanChange_1);
    arrCanChange.push_back(m_pSpriteCanChange_3);
    arrCanChange.push_back(m_pSpriteCanChange_5);
    arrCanChange.push_back(m_pSpriteCanChange_2);
    arrCanChange.push_back(m_pSpriteCanChange_4);
    arrCanChange.push_back(m_pSpriteCanChange_6);
    
    m_table = CCTableView::create(this, m_pLayerList->getContentSize());
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setPosition(getWidth(m_pLayerList)* 0.5, getHeight(m_pLayerList)*0.5);
    m_table->setAnchorPoint(ccp(0.5, 0.5));
    m_table->ignoreAnchorPointForPosition(false);
    m_pLayerList->addChild(m_table);
    
    m_pControlButtonEquipStrengthen->setZOrder(-1);
    m_pControlButtonEquipEvo->setZOrder(-2);
}


void CcbEquipIntegrationLayer::onEnter()
{
    CCLayer::onEnter();
    //在scene()之后被调用}
    //这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
    loadData();
}

void CcbEquipIntegrationLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
    this->runAction(
                    CCSequence::create(CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbEquipIntegrationLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
    CRole* pRole = CGameSession::GetRole();
    pRole->SetbyNotiNewEquip(false);
    //    pRole->SetbyNotiUnit(pRole->GetbyNotiNewPet() | pRole->GetbyNotiNewEmblem());
    
    m_table->reloadData();
}

void CcbEquipIntegrationLayer::addGuideLayer() {
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonPet_1, GuideBtnPos::E_EQUIP_PET_TWO);
        
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("hero_guide_end");
#endif
        
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_2_EQUIP,
                                                 
                                                 GuideData::E_SYS_GUIDE_6_HERO,
                                                 NULL
                                                 );
    }
}

void CcbEquipIntegrationLayer::onExit()
{
    CGameSession::Detach(this);
    CCLayer::onExit();
}

void CcbEquipIntegrationLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}



void CcbEquipIntegrationLayer::initBtnChange()
{
    m_bChange = false;
    m_pControlButtonChange->setTitleForState(CCString::create(GET_STR(Str_change)), CCControlStateNormal);
}

void CcbEquipIntegrationLayer::onPressControlButtonQuest(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
//    PetLoadingLayer::sharedLayer()->WaitForPacket();
//    StageCtrl::Get()->setKind(StageCtrl::kNormalStage);
//    CGameSession::SendNormalMap();
    uint32 id = 0;
    switch (m_selectEquip + 1) {
        case E_EQUIP_PART_WEAPON:
            id = E_BASE_EQUIP_PART_1;
            break;
        case E_EQUIP_PART_CLOTHES:
            id = E_BASE_EQUIP_PART_2;
            break;
        case E_EQUIP_PART_HELMET:
            id = E_BASE_EQUIP_PART_3;
            break;
        case E_EQUIP_PART_NECKLACE:
            id = E_BASE_EQUIP_PART_4;
            break;
            
        default:
            break;
    }
    
    if (id) {
        CcbDropTipLayer::showDropTip(id);
    }
}

void CcbEquipIntegrationLayer::onPressControlButtonPet(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    int tag = ((CCNode*)pSender)->getTag();
    
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_SYS_GUIDE_3_EQUIP,
                                             NULL
                                             );
    
    if (tag == m_selectPet) {
        return;
    }
    
    m_selectPet = tag;
    m_selectEquip = -1;
    initBtnChange();
    
//    //切换宠物时不飘字}
//    if (m_pLayerEquipEnhLayer) {
//        m_pLayerEquipEnhLayer->setIsNeedFly(false);
//    }
    onSelectPet();
}

void CcbEquipIntegrationLayer::onPressControlButtonEquip(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    int tag = ((CCNode*)pSender)->getTag();
    if (tag == m_selectEquip) {
        return;
    }
    m_selectEquip = tag;
    
    initBtnChange();
    
//    //切换装备时不飘字}
//    if (m_pLayerEquipEnhLayer) {
//        m_pLayerEquipEnhLayer->setIsNeedFly(false);
//    }
    onSelectEquip();
}

void CcbEquipIntegrationLayer::onPressControlButtonChange(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (!m_bChange) {
        m_bChange = true;
        m_pControlButtonChange->setTitleForState(CCString::create(GET_STR(Str_cancel)), CCControlStateNormal);
        g_EquipData->SetDressEquipPart(m_selectEquip + 1);
        hideEquipEnhLayer();
//        loadEquipList();
    }
    else{
        initBtnChange();
        showEquipEnhLayer();
    }
    
}

void CcbEquipIntegrationLayer::onPressControlButtonEquipTab(CCObject* pSender, CCControlEvent event)
{
    CCControlButton* pButton = (CCControlButton*)pSender;
    if (!pButton) {
        return;
    }
    
    if (m_pCurEquipTabBtn) {
        m_pCurEquipTabBtn->setZOrder(-2);
    }
    pButton->setZOrder(-1);
    m_pCurEquipTabBtn = pButton;
    
    this->showEquipInfoLayerByIndex(pButton->getTag());
}

void CcbEquipIntegrationLayer::showEquipInfoLayerByIndex(int index)
{
    if (index == 0) {
        if (m_pLayerEquipEnhLayer) {
            m_pLayerEquipEnhLayer->loadEnhData();
        }
    }
    else
    {
        if (m_pLayerEquipEnhLayer) {
            m_pLayerEquipEnhLayer->loadEvoData();
        }
    }
}

void CcbEquipIntegrationLayer::loadData()
{
    CTeam* team = CTeamCtrl::GetCurTeam();
    std::vector<uint32> arrPetId = team->getarrPetObId();
    
    //宠物}
    arrPetIcon.push_back(m_pLayerPet1);
    arrPetIcon.push_back(m_pLayerPet2);
    arrPetIcon.push_back(m_pLayerPet3);
    arrPetIcon.push_back(m_pLayerPet4);
    arrPetIcon.push_back(m_pLayerPet5);
    arrPetIcon.push_back(m_pLayerPet6);
    std::vector<CCControlButton*> arrPetBtn;
    arrPetBtn.push_back(m_pControlButtonPet_1);
    arrPetBtn.push_back(m_pControlButtonPet_2);
    arrPetBtn.push_back(m_pControlButtonPet_3);
    arrPetBtn.push_back(m_pControlButtonPet_4);
    arrPetBtn.push_back(m_pControlButtonPet_5);
    arrPetBtn.push_back(m_pControlButtonPet_6);
    
    int cnt = 0;
    uint32 chooseId = CPetCtrl::Get()->GetShowPetObjId();
    uint8 chooseSite = 0;
    //1-3-5
    for (int i = 0; i < 3; i++) {
        uint8 site = i*2 + 1;
        if (!arrPetId[site]) {
            continue;
        }
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrPetId[site]);
        if (!pet) {
            continue;
        }
        arrPetIcon[cnt]->setPetId(pet->GetwIndex());
        arrPetIcon[cnt]->setBtnEnable(false);
        
        arrPetBtn[cnt]->setTag(cnt);
        arrPetObjId.push_back(pet->GetObjId());
        arrTeamSite.push_back(site);
        
//        arrCanChange[cnt]->setVisible(g_PacketDataMgr->checkHasCanChangeEquip(pet->GetObjId()));
        
        if (arrPetId[site] == chooseId) {
            chooseSite = cnt;
        }
        cnt++;
    }
    //2-4-6
    for (int i = 1; i <= 3; i++) {
        uint8 site = i*2;
        if (!arrPetId[site]) {
            continue;
        }
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrPetId[site]);
        if (!pet) {
            continue;
        }
        arrPetIcon[cnt]->setPetId(pet->GetwIndex());
        arrPetIcon[cnt]->setBtnEnable(false);
        arrPetBtn[cnt]->setTag(cnt);
        arrPetObjId.push_back(pet->GetObjId());
        arrTeamSite.push_back(site);
        
//        arrCanChange[cnt]->setVisible(g_PacketDataMgr->checkHasCanChangeEquip(pet->GetObjId()));
        
        if (arrPetId[site] == chooseId) {
            chooseSite = cnt;
        }
        cnt++;
    }
    
    checkPetCanChangeEquip();
    
    for (; cnt < 6; cnt++) {
        arrPetIcon[cnt]->getParent()->setVisible(false);
    }
    
    m_selectPet = chooseSite;
    //如果是从宠物详情中进入的，转到选中宠物的选中装备位置}
    if (g_EquipData->GetDressEquipPart()) {
        m_selectEquip = g_EquipData->GetDressEquipPart() - 1;
    }
    
    onSelectPet();
}

void CcbEquipIntegrationLayer::checkPetCanChangeEquip()
{
    CTeam* team = CTeamCtrl::GetCurTeam();
    std::vector<uint32> arrPetId = team->getarrPetObId();
    int cnt = 0;
    //1-3-5
    for (int i = 0; i < 3; i++) {
        uint8 site = i*2 + 1;
        if (!arrPetId[site]) {
            continue;
        }
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrPetId[site]);
        if (!pet) {
            continue;
        }
        arrCanChange[cnt]->setVisible(g_PacketDataMgr->checkHasCanChangeEquip(pet->GetObjId()));
        cnt++;
    }
    //2-4-6
    for (int i = 1; i <= 3; i++) {
        uint8 site = i*2;
        if (!arrPetId[site]) {
            continue;
        }
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrPetId[site]);
        if (!pet) {
            continue;
        }
        arrCanChange[cnt]->setVisible(g_PacketDataMgr->checkHasCanChangeEquip(pet->GetObjId()));
        cnt++;
    }
    
    for (; cnt < 6; cnt++) {
        arrCanChange[cnt]->setVisible(false);
    }
}

void CcbEquipIntegrationLayer::loadWearEquip()
{
    arrCurEquipObjId.clear();
    arrCurEquipObjId.push_back(0);
    arrCurEquipObjId.push_back(0);
    arrCurEquipObjId.push_back(0);
    arrCurEquipObjId.push_back(0);
    std::map<uint8, uint32>mapEquip = g_EquipTeamData->getEquipsBySite(arrTeamSite[m_selectPet]);
    std::map<uint8, uint32>::iterator ii = mapEquip.begin();
    for (; ii != mapEquip.end(); ii++) {
        arrCurEquipObjId[ii->first] = ii->second;
    }
    
    for ( int i = 0; i < arrPlus.size(); i++) {
        const CEquip* equip = g_PacketDataMgr->GetEquipInfoByKeyID(arrCurEquipObjId[i]);
        if (!equip) {
            arrEquipIcon[i]->setVisible(false);
        }
        else{
//            arrPlus[i]->setVisible(false);
            arrEquipIcon[i]->setVisible(true);
            arrEquipIcon[i]->loadIndexData(equip->GetIndex());
            arrEquipIcon[i]->showIconOnly();
            arrEquipIcon[i]->setBtnEnable(false);
        }
        arrPlus[i]->setVisible(g_PacketDataMgr->checkHasCanUseEquip(i+1, arrCurEquipObjId[i]));
    }
    //切换宠物时默认选中第一件装备(<0表示初始情况)，否则认为是刷新，不变}
    if (m_selectEquip < 0) {
        m_selectEquip = 0;
    }
    
    onSelectEquip();
    
}

void CcbEquipIntegrationLayer::onSelectPet()
{
    m_pNodePetSelect->setPositionX(arrPetIcon[m_selectPet]->getParent()->getPositionX());
    CPetCtrl::Get()->SetNeedRefreshValue(true);
    ShowFlyLayer();
    CTeamCtrl::SetSelectedMemberSite(arrTeamSite[m_selectPet]);
    loadWearEquip();
}

void CcbEquipIntegrationLayer::onSelectEquip()
{
    m_pNodeEquipSelect->setPositionX(arrPlus[m_selectEquip]->getParent()->getPositionX());
    
    //有装备，显示强化面板}
    if (arrEquipIcon[m_selectEquip]->isVisible()) {
        m_pControlButtonChange->setEnabled(true);
        
//        if (arrPlus[m_selectEquip]->isVisible()) {
            m_pSpriteCanChange->setVisible(arrPlus[m_selectEquip]->isVisible());
//        }
        
        showEquipEnhLayer();
    }
    else{
        //没装备，显示装备列表}
        m_pSpriteCanChange->setVisible(false);
        m_pControlButtonChange->setEnabled(false);
        g_EquipData->SetDressEquipPart(m_selectEquip + 1);
        hideEquipEnhLayer();
        
        // 防止背包中没有装备的情况，只要没装备到身上就不引导
        uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
        //CCLog("wtrigger:%d", wTrigger);
        if (wTrigger == GuideData::E_SYS_GUIDE_6_HERO) {
            GuideData::GetInstance()->setStepId(GuideData::E_SYS_GUIDE_END_HERO);
        }
    }
}

void CcbEquipIntegrationLayer::RefeashLayer()
{
    PetLoadingLayer::sharedLayer()->End();
//    //有装备更新时飘字}
//    if (m_pLayerEquipEnhLayer) {
//        m_pLayerEquipEnhLayer->setIsNeedFly(true);
//    }
    checkPetCanChangeEquip();
    
    initBtnChange();
    loadWearEquip();
    ShowFlyLayer();
}

void CcbEquipIntegrationLayer::showEquipEnhLayer()
{
    m_pControlButtonQuest->getParent()->setVisible(false);
    m_pLayerList->setVisible(false);
    if (m_pLayerEquipEnhLayer) {
        //加载数据}
        if (g_EquipData->GetChosenEquipKeyID() != arrCurEquipObjId[m_selectEquip]) {
            g_EquipData->SetChosenEquipKeyID(arrCurEquipObjId[m_selectEquip]);
            m_pLayerEquipEnhLayer->CreateEquipData();
        }
        m_vecEquipListId.clear();
        
        m_pLayerEquipEnhLayer->setVisible(true);
        return;
    }
    m_pLayerEquipEnhLayer = dynamic_cast<CcbEquipStrengthenLayer*>(CcbManager::sharedManager()->LoadCcbEquipStrengthenLayer(this));
    //加载数据}
    g_EquipData->SetChosenEquipKeyID(arrCurEquipObjId[m_selectEquip]);
    m_pLayerEquipEnhLayer->CreateEquipData();
    m_pNodeEquipEnh->addChild(m_pLayerEquipEnhLayer);
    
    this->showEquipInfoLayerByIndex(0);
}

void CcbEquipIntegrationLayer::hideEquipEnhLayer()
{
    if (m_pLayerEquipEnhLayer) {
        m_pLayerEquipEnhLayer->setVisible(false);
    }
    loadEquipList();
}

void CcbEquipIntegrationLayer::loadEquipList()
{
    
    m_vecEquipListId.clear();
    vector<uint32>tempList = g_EquipData->GetVecShowEquipKeyID();
    std::vector<uint32> arrWear;
    uint32 equipId = arrCurEquipObjId[m_selectEquip];
    
    uint8 part = g_EquipData->GetDressEquipPart();
    
    
    for (int i = 0; i < tempList.size(); i++)
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
        
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(CTeamCtrl::GetCurTeam()->getarrPetObId()[equip->GetWearPetID()/10000]);
        if (pet) {
            continue;
            arrWear.push_back(tempList[i]);
        }
        else{
            m_vecEquipListId.push_back(tempList[i]);
        }
    }
    
    for (int i = 0 ; i < arrWear.size(); i++) {
        m_vecEquipListId.push_back(arrWear[i]);
    }
    
    if (m_vecEquipListId.size() == 0 && equipId == 0) {
        m_pControlButtonQuest->getParent()->setVisible(true);
        m_pLayerList->setVisible(false);
        return;
    }
    else{
        m_pControlButtonQuest->getParent()->setVisible(false);
    }
    
    sort(m_vecEquipListId.begin(), m_vecEquipListId.end(), CcbPetShowLayer::cmpEquip);
    
    if (equipId) {
        m_vecEquipListId.insert(m_vecEquipListId.begin(), equipId);// .push_back(equipId);
    }
    
    m_pLayerList->setVisible(true);
    
    m_table->reloadData();
}

CCSize CcbEquipIntegrationLayer::cellSizeForTable(CCTableView *table)
{
    return CCSize(getWidth(m_pLayerList), 91 + 5);
}

CCTableViewCell* CcbEquipIntegrationLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CcbEquipNormalFrameLayer* pNode = dynamic_cast<CcbEquipNormalFrameLayer*>(CcbManager::sharedManager()->LoadCcbEquipNormalFrameLayer(this));
        pNode->setPosition(getWidth(m_pLayerList) *0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pNode->setClipRect(clipRect);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbEquipNormalFrameLayer* pNode = (CcbEquipNormalFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->loadData(m_vecEquipListId[idx]);
        pNode->setTeamSite(arrTeamSite[m_selectPet]);
        if (arrCurEquipObjId[m_selectEquip] && idx == 0) {
            pNode->setFrameType(E_EQUIP_FRAME_DOWN);
        }
        else{
            pNode->setFrameType(E_EQUIP_FRAME_WEAR);
        }
    }
    return pCell;
}

unsigned int CcbEquipIntegrationLayer::numberOfCellsInTableView(CCTableView *table)
{
    return m_vecEquipListId.size();
}

void CcbEquipIntegrationLayer::ShowFlyLayer()
{
    
    CTeam* team = CTeamCtrl::GetCurTeam();
    std::vector<uint32> arrPetId = team->getarrPetObId();
    uint8 site = arrTeamSite[m_selectPet];
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrPetId[site]);
    
    if (!pet)
    {
        return;
    }
    
    if (CPetCtrl::Get()->isNeedRefreshValue())
    {
        /*
         生命 1
         普攻 2
         普防 3
         回复 4
         特攻 5
         特防 6
         暴击 7
         速度 8
         命中 9
         闪避 10
         爆伤 11
         抗暴 12
         攻击 13
         */
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_HP, pet->GetdwHpValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_CATT, pet->GetdwAttackValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_CDEF, pet->GetdwDefenseValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_REV, pet->GetdwRecoverValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_SATT, pet->GetdwSAttackValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_SDEF, pet->GetdwSDefenseValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_CRIT, pet->GetdwCritRateValue() / 100);
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_SPEED, pet->GetdwSpeedValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_HIT, pet->GetdwHitValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_DODGE, pet->GetdwDodgeValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_CRIT_HURT, pet->GetdwCritHurtValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_CRIT_FREE, pet->GetdwCritFreeValue());
    }
    CPetCtrl::Get()->SetNeedRefreshValue(false);
    //攻击特殊判断
    uint32 dwLastCAtk = CPetCtrl::Get()->GetPetFristAttriValue(E_ATTR_CATT);
    int atkAdd = pet->GetdwAttackValue() - dwLastCAtk;
    int cnt = 0;
    if (atkAdd != 0) {
        cnt++;
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_CATT, pet->GetdwAttackValue());
        CPetCtrl::Get()->SetPetFirstAttriValue(E_ATTR_SATT, pet->GetdwSAttackValue());
        FlyTextLayer::showText(E_ATTR_ALL_ATT, atkAdd);
    }
    
    uint32 arrCurValue[E_ATTR_ALL_ATT];
    arrCurValue[E_ATTR_HP] = pet->GetdwHpValue();
    arrCurValue[E_ATTR_CATT] = pet->GetdwAttackValue();
    arrCurValue[E_ATTR_CDEF] = pet->GetdwDefenseValue();
    arrCurValue[E_ATTR_REV] = pet->GetdwRecoverValue();
    arrCurValue[E_ATTR_SATT] = pet->GetdwSAttackValue();
    arrCurValue[E_ATTR_SDEF] = pet->GetdwSDefenseValue();
    arrCurValue[E_ATTR_CRIT] = pet->GetdwCritRateValue() / 100;
    arrCurValue[E_ATTR_SPEED] = pet->GetdwSpeedValue();
    arrCurValue[E_ATTR_HIT] = pet->GetdwHitValue();
    arrCurValue[E_ATTR_DODGE] = pet->GetdwDodgeValue();
    arrCurValue[E_ATTR_CRIT_HURT] = pet->GetdwCritHurtValue();
    arrCurValue[E_ATTR_CRIT_FREE] = pet->GetdwCritFreeValue();
    
    
    for (int i = 1; i < E_ATTR_ALL_ATT; i++) {
        if (i == E_ATTR_CATT ||
            i == E_ATTR_SATT ||
            i == E_ATTR_ALL_ATT) {
            continue;
        }
        int add = arrCurValue[i] - CPetCtrl::Get()->GetPetFristAttriValue(i);
        if (add != 0) {
            FlyTextLayer::showText(i, add, cnt*0.5);
            cnt++;
        }
        CPetCtrl::Get()->SetPetFirstAttriValue(i, arrCurValue[i]);
    }
    
    
}
