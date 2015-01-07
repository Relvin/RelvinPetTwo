#include "CcbPetFuseLayer.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "BackCtrl.h"
#include "ConfigGet.h"
#include "PetLoadingLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "EventDataMgr.h"
#include "EnumDefines.h"
#include "EquipDataMgr.h"
#include "CcbShowGetLayer.h"
#include "CFuseDadaMgr.h"
#include "CcbPetEquipIcon.h"
#include "GuideData.h"
#include "PacketDataMgr.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "FlyTextLayer.h"
#include "GuideBtnPos.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

PetFuseScene::PetFuseScene()
{
    m_pLabelTTFName = NULL;
}

PetFuseScene::~PetFuseScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* PetFuseScene::scene()
{
    CCScene* pScene = CCScene::create();
    PetFuseScene* pLayer = PetFuseScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool PetFuseScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool PetFuseScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbPetFuseLayer(this));
    return true;
}

void PetFuseScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_fuse_house));
}

void PetFuseScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void PetFuseScene::onExit()
{
	CCLayer::onExit();
}

void PetFuseScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}


CcbPetFuseLayer::~CcbPetFuseLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonAddpet);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAddequip);
	CC_SAFE_RELEASE_NULL(m_pControlButtonShop);
	CC_SAFE_RELEASE_NULL(m_pControlButtonDes);
	CC_SAFE_RELEASE_NULL(m_pLayerElem1);
	CC_SAFE_RELEASE_NULL(m_pLayerElem2);
	CC_SAFE_RELEASE_NULL(m_pLayerElem3);
	CC_SAFE_RELEASE_NULL(m_pLayerElem4);
	CC_SAFE_RELEASE_NULL(m_pControlButtonFuse);
    CC_SAFE_RELEASE_NULL(m_pLayerElem);

    CC_SAFE_RELEASE_NULL(m_pSprite_add_1);
    CC_SAFE_RELEASE_NULL(m_pSprite_add_2);
    CC_SAFE_RELEASE_NULL(m_pSprite_add_3);
    CC_SAFE_RELEASE_NULL(m_pSprite_add_4);
    
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetFuseLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetFuseLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetFuseLayer", CcbPetFuseLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_fuse.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CcbPetFuseLayer* CcbPetFuseLayer::m_curScene = NULL;
bool CcbPetFuseLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_curScene = this;
	return true;
}

void CcbPetFuseLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_FUSE);
    loadData();
}

void CcbPetFuseLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetFuseLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbPetFuseLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonAddpet, GuideBtnPos::E_ADD_PET);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonFuse, GuideBtnPos::E_START_FENJIE);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonShop, GuideBtnPos::E_MYSTERY);
        
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_4_MYSTERY,
                                                 NULL
                                                 );
    }
}

void CcbPetFuseLayer::onExit()
{
	CCLayer::onExit();
    CPetCtrl::Get()->ClearSelectedPet();
}

void CcbPetFuseLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetFuseLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAddpet", CCControlButton*, this->m_pControlButtonAddpet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAddequip", CCControlButton*, this->m_pControlButtonAddequip);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShop", CCControlButton*, this->m_pControlButtonShop);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonDes", CCControlButton*, this->m_pControlButtonDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem1", CcbPetIcon*, this->m_pLayerElem1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem2", CcbPetIcon*, this->m_pLayerElem2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem3", CcbPetIcon*, this->m_pLayerElem3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem4", CcbPetIcon*, this->m_pLayerElem4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFuse", CCControlButton*, this->m_pControlButtonFuse);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem", CCLayer*, this->m_pLayerElem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_add_1", CCSprite*, this->m_pSprite_add_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_add_2", CCSprite*, this->m_pSprite_add_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_add_3", CCSprite*, this->m_pSprite_add_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_add_4", CCSprite*, this->m_pSprite_add_4);
	return false;
}

bool CcbPetFuseLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetFuseLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetFuseLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetFuseLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAddpet", CcbPetFuseLayer::onPressControlButtonAddpet);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAddEquip", CcbPetFuseLayer::onPressControlButtonAddEquip);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShop", CcbPetFuseLayer::onPressControlButtonShop);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonDes", CcbPetFuseLayer::onPressControlButtonDes);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFuse", CcbPetFuseLayer::onPressControlButtonFuse);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetFuseLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    isPetFuse = true;
    arrId.clear();
    arrElem.clear();
    arrElem.push_back(m_pLayerElem1);
    arrElem.push_back(m_pLayerElem2);
    arrElem.push_back(m_pLayerElem3);
    arrElem.push_back(m_pLayerElem4);
    
    arrElemAdd.clear();
    arrElemAdd.push_back(m_pSprite_add_1);
    arrElemAdd.push_back(m_pSprite_add_2);
    arrElemAdd.push_back(m_pSprite_add_3);
    arrElemAdd.push_back(m_pSprite_add_4);
    for (int i = 0; i < arrElemAdd.size(); i++) {
        arrElemAdd[i]->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.5),
                                                                            CCFadeIn::create(1.5),
                                                                            NULL)));
    }
}


void CcbPetFuseLayer::onPressControlButtonFuse(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    //有5星宠时
    if (g_FuseDada->getFuseTab() == E_FUSE_TAB_PET) {
        for (int i = 0; i < arrId.size(); i++) {
            CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrId[i]);
            if (pet && pet->GetbyStarLv() >= 5) {
                CCNode* node = CcbManager::sharedManager()->LoadCcbPetFuseHighQualityGetLayer();
                if (node) {
                    addChild(node, 999, 111);
                }
                
                return;
            }
        }
    }
    //没有5星宠时
    CCNode* node = CcbManager::sharedManager()->LoadCcbPetFuseLowQualityGetLayer();
    if (node) {
        addChild(node, 999, 111);
    }
    
}

void CcbPetFuseLayer::onPressControlButtonAddpet(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    g_FuseDada->setFuseTab(E_FUSE_TAB_PET);
    g_FuseDada->atuoSelecte();
    loadData();
    
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_SYS_GUIDE_5_MYSTERY,
                                             NULL
                                             );
}

void CcbPetFuseLayer::onPressControlButtonAddEquip(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    g_FuseDada->setFuseTab(E_FUSE_TAB_EQUIP);
    g_FuseDada->atuoSelecte();
    loadData();
}

void CcbPetFuseLayer::onPressControlButtonShop(CCObject* pSender, CCControlEvent event)
{
    if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_SYS_GUIDE_END_MYSTERY) {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("mystery_guide_end");
#endif
    }
    
    g_EventData->setMyShopType(E_MY_SHOP_MYSTERY);
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendReqMJShopList();
    CGameSession::SendReqMySteryShopList();
//    g_EventData->SetCurShowEventType(SHOW_MY_STERY_SHOP);
//    BackCtrl::ReplaceCurScene(kEventScene);
}

void CcbPetFuseLayer::onPressControlButtonDes(CCObject* pSender, CCControlEvent event)
{
    SystemMessage::showSystemMessage(0, this, GET_STR(Str_fuse_des));
}


void CcbPetFuseLayer::loadData()
{
    isPetFuse = g_FuseDada->getFuseTab() == E_FUSE_TAB_PET;
    arrId = g_FuseDada->getSelected();
    
    m_dwNeedMoney = 0;
    m_wGetFuse = 0;
    int count = 0;

    for (int i = 0; i < 4; ++i)
    {
        m_pLayerElem->removeChildByTag(100+i);
        arrElem[i]->setVisible(true);
    }
    
    for (int i = 0; i < arrId.size(); ++i)
    {
        if (isPetFuse)
        {
            CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrId[i]);
            if (!pet)
            {
                continue;
            }
            arrElem[count]->setPetObjId(pet->GetObjId());
            arrElem[count]->setBtnEnable(true);
            arrElemAdd[count]->setVisible(false);
            count++;
            
            PetFuseConfig::STC_PET_FUSE_CONFIG *fuCfg = GET_CONFIG_STC(PetFuseConfig, pet->GetwIndex());
            if (fuCfg)
            {
                m_dwNeedMoney += fuCfg->dwNeedMoney;
                m_wGetFuse += fuCfg->wGetCnt;
            }
        }
        else
        {
            const CEquip* equip = g_PacketDataMgr->GetEquipInfoByKeyID(arrId[i]);
            if (equip)
            {
                PetFuseConfig::STC_PET_FUSE_CONFIG *fuCfg = GET_CONFIG_STC(PetFuseConfig, equip->GetIndex());
                if (fuCfg)
                {
                    m_dwNeedMoney += fuCfg->dwNeedMoney;
                    
                    ExpConfig::STC_EXP_CONFIG* expCfg = GET_CONFIG_STC(ExpConfig, equip->GetLevel());
                    if (expCfg) {
                        m_wGetFuse += expCfg->dwGetEquipFuseMoney * equip->GetConfigData().dwCostBaseValue / 100;
                    }
                    
                    
                    CcbPetEquipIcon* icon = dynamic_cast<CcbPetEquipIcon*>(CcbManager::sharedManager()->LoadCcbPetEquipIcon(this));
                    icon->setEquipObjId(equip->GetKeyID());
                    icon->setPosition(arrElem[count]->getPosition());
                    icon->setAnchorPoint(ccp(0.5, 0.5));
                    icon->showName(false);
                    m_pLayerElem->addChild(icon, 100, 100+count);
                    arrElem[count]->setVisible(false);
                    arrElemAdd[count]->setVisible(false);
                    count++;               
                }                
            }
        }
    }
    
    if (count == 0) {
        m_pControlButtonFuse->setEnabled(false);
    }
    else
    {
        m_pControlButtonFuse->setEnabled(true);
    }
    
    for (int i = count; i < 4; i++) {
        arrElem[i]->setPetObjId(0);
        arrElem[i]->setBtnEnable(true);
        arrElemAdd[i]->setVisible(true);
    }
}
// 宠物 合成融合石 结果 {uint16 wError + uint32 dwCnt }
void CcbPetFuseLayer::handlerPetFuseResult(WorldPacket &packet)
{
    PetLoadingLayer::sharedLayer()->End();
    uint16 wError;
    packet >> wError;
    if (wError) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
    }
    else
    {
        if (getChildByTag(111)) {
            removeChildByTag(111);
        }
        
        if (g_FuseDada->getFuseTab() == E_FUSE_TAB_PET) {
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_pet_fuse));
        }
        else{
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_armor_fuse));
        }
        
        EffectLayer* eff = EffectLayer::create(E_ANI_EFFECT_RONGHE_EFF, 1, 0.1);
        eff->setPosition(ccp(getWidth(m_pLayerElem)*0.5, getHeight(m_pLayerElem)*0.5));
        eff->setScale(1.5f);
        eff->setAnchorPoint(ccp(0.5, 0.5));
        eff->setTag(11);
        eff->ignoreAnchorPointForPosition(false);
        m_pLayerElem->addChild(eff, 200);
        eff->onRun();
        
        uint8 bySize;
        uint32 dwUniteType, dwUniteNum;
        
        packet >> bySize;
        CcbShowGetLayer* pGetLayer = dynamic_cast<CcbShowGetLayer*>(CcbManager::sharedManager()->LoadCcbShowGetLayer());
        pGetLayer->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width*0.5, CCDirector::sharedDirector()->getWinSize().height*0.5));
        for (int i = 0; i < bySize; i++) {
            packet >> dwUniteType >> dwUniteNum;
            pGetLayer->addGetItem(dwUniteType, dwUniteNum);
        }
        pGetLayer->reloadItems();
        this->runAction(CCSequence::create(CCDelayTime::create(eff->getDuring()+0.3),
                                           CCCallFuncND::create(this, callfuncND_selector(CcbPetFuseLayer::showGet),pGetLayer),
                                           NULL));
    }
}

void CcbPetFuseLayer::showGet( CCNode* node, void *vptr)
{
    g_FuseDada->clearSelected();
    arrId.clear();
    loadData();
    CCDirector::sharedDirector()->getRunningScene()->addChild((CCNode*)vptr, 999, 637);
}

void CcbPetFuseLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    uint8 byType = isPetFuse? E_UNITE_TYPE_PET : E_UNITE_TYPE_EQUIP;
    CGameSession::SendPetFuse(byType, arrId);
}

void CcbPetFuseLayer::onActionOver()
{

}
