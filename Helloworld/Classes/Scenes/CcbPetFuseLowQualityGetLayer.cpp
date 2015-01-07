#include "CcbPetFuseLowQualityGetLayer.h"
//#include "CcbManager.h"
#include "CcbItemIconLayer.h"
#include "CFuseDadaMgr.h"
#include "ConfigGet.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "EnumDefines.h"
#include "GameSession.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"
#include "Equip.h"
#include "PacketDataMgr.h"
#include "ResourceStringClient.h"
#include "GuideData.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPetFuseLowQualityGetLayer::~CcbPetFuseLowQualityGetLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
    CC_SAFE_RELEASE_NULL(m_pControlButtonFuse);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFDes);
    CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_1);
    CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_2);
    CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_3);
    CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_4);
    CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_5);
    
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 CCNode* LoadCcbPetFuseLowQualityGetLayer( CCObject* owner );
 
 //CcbManager.cpp
 CCNode* CcbManager::LoadCcbPetFuseLowQualityGetLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetFuseLowQualityGetLayer", CcbPetFuseLowQualityGetLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/item_icon.ccb]", [ccb/item_icon.ccb]Loader::loader() );
 
 
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_fuse_lowquality.ccbi", owner);
	pCCBReader->release();
 
	return pNode;
 }
 */


bool CcbPetFuseLowQualityGetLayer::init()
{
    // First be called.
    if (!CCLayer::init()) {
        return false;
    }
    // code here
    setTouchEnabled(true);
    return true;
}

void CcbPetFuseLowQualityGetLayer::onEnter()
{
    CCLayer::onEnter();
    //在scene()之后被调用
    //这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    loadData();
}

void CcbPetFuseLowQualityGetLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.2f),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetFuseLowQualityGetLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbPetFuseLowQualityGetLayer::addGuideLayer() {
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonFuse, GuideBtnPos::E_COMFIRM_FENJIE);
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_6_MYSTERY,
                                                 NULL
                                                 );
    }
}

void CcbPetFuseLowQualityGetLayer::onExit()
{
    CCLayer::onExit();
}

void CcbPetFuseLowQualityGetLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetFuseLowQualityGetLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFuse", CCControlButton*, this->m_pControlButtonFuse);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDes", CCLabelTTF*, this->m_pLabelTTFDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_1", CcbItemIconLayer*, this->m_pLayerItemIcon_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_2", CcbItemIconLayer*, this->m_pLayerItemIcon_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_3", CcbItemIconLayer*, this->m_pLayerItemIcon_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_4", CcbItemIconLayer*, this->m_pLayerItemIcon_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_5", CcbItemIconLayer*, this->m_pLayerItemIcon_5);
    
    return false;
}

bool CcbPetFuseLowQualityGetLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetFuseLowQualityGetLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
    return NULL;
}

SEL_MenuHandler CcbPetFuseLowQualityGetLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
    return NULL;
}

SEL_CCControlHandler CcbPetFuseLowQualityGetLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbPetFuseLowQualityGetLayer::onPressControlButtonCancel);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFuse", CcbPetFuseLowQualityGetLayer::onPressControlButtonFuse);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbPetFuseLowQualityGetLayer::onPressControlButtonClose);
    
    return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetFuseLowQualityGetLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    // 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
    // 可以删除，如果不需要
    m_pControlButtonCancel->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pControlButtonFuse->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 1);
    
    if (g_FuseDada->getFuseTab() == E_FUSE_TAB_PET) {
        m_pLabelTTFDes->setString(GET_STR(Str_fuse_pet_get));
    }
    else{
        m_pLabelTTFDes->setString(GET_STR(Str_fuse_equip_get));
    }
    
}

void CcbPetFuseLowQualityGetLayer::loadData()
{
    std::vector<uint32> arrId = g_FuseDada->getSelected();
    int itemCnt = 0;
    
    uint32 coinId = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_COIN;
    
    std::vector<CcbItemIconLayer* > arrItemIcon;
    arrItemIcon.push_back(m_pLayerItemIcon_1);
    arrItemIcon.push_back(m_pLayerItemIcon_2);
    arrItemIcon.push_back(m_pLayerItemIcon_3);
    arrItemIcon.push_back(m_pLayerItemIcon_4);
    arrItemIcon.push_back(m_pLayerItemIcon_5);
    
    
    std::map<uint32, uint32> mapGetItem;
    
    for (int i = 0; i < arrId.size(); i++) {
        uint8 lv = 0;
        uint8 evo = 0;
        uint32 dwIndex = 0;
        
        if (g_FuseDada->getFuseTab() == E_FUSE_TAB_PET) {
            CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrId[i]);
            if (!pet) {
                continue;
            }
            lv = pet->GetbyLv();
            evo = pet->GetbyEvolveLv();
            dwIndex = pet->GetwIndex();
            
            //融合奖励
            PetFuseConfig::STC_PET_FUSE_CONFIG *fsCfg = GET_CONFIG_STC(PetFuseConfig, dwIndex);
            if (fsCfg) {
                uint32 getCnt = 0;
                if (mapGetItem.find(fsCfg->wGetItemId) != mapGetItem.end()) {
                    getCnt = mapGetItem[fsCfg->wGetItemId];
                }
                getCnt += fsCfg->wGetCnt;
                mapGetItem[fsCfg->wGetItemId] = getCnt;
                
                //4星以下，额外获得金币，并且不用读exp表
                if(pet->GetbyStarLv() < 4){
                    getCnt = 0;
                    if (mapGetItem.find(coinId) != mapGetItem.end()) {
                        getCnt = mapGetItem[coinId];
                    }
                    getCnt += fsCfg->dwNeedMoney + pet->GetbyLv() * 10;
                    mapGetItem[coinId] = getCnt;
                    continue;
                }
            }
            
            //金币
            ExpConfig::STC_EXP_CONFIG* lvCfg = GET_CONFIG_STC(ExpConfig, lv);
            if (lvCfg && lv > 0) {
                uint32 getCnt = 0;
                if (mapGetItem.find(coinId) != mapGetItem.end()) {
                    getCnt = mapGetItem[coinId];
                }
                getCnt += lvCfg->dwGetPetFuseMoney;
                mapGetItem[coinId] = getCnt;
                
                //蛋壳
                getCnt = 0;
                if (mapGetItem.find(lvCfg->dwGetPetFusePetId) != mapGetItem.end()) {
                    getCnt = mapGetItem[lvCfg->dwGetPetFusePetId];
                }
                getCnt += lvCfg->dwGetPetFusePetCnt;
                mapGetItem[lvCfg->dwGetPetFusePetId] = getCnt;
            }
            //进阶印章
            ExpConfig::STC_EXP_CONFIG* evoCfg = GET_CONFIG_STC(ExpConfig, evo);
            if (evoCfg && evo > 0) {
                uint32 getCnt = 0;
                if (mapGetItem.find(evoCfg->dwGetPetFuseItemId) != mapGetItem.end()) {
                    getCnt = mapGetItem[evoCfg->dwGetPetFuseItemId];
                }
                getCnt += evoCfg->dwGetPetFuseItemCnt;
                mapGetItem[evoCfg->dwGetPetFuseItemId] = getCnt;
            }
            
        }
        else{
            const CEquip* equip = g_PacketDataMgr->GetEquipInfoByKeyID(arrId[i]);
            if (!equip) {
                continue;
            }
            lv = equip->GetLevel();
            evo = equip->getEvoLv();
            dwIndex = equip->GetIndex();
            
            //符文
//            PetFuseConfig::STC_PET_FUSE_CONFIG *fsCfg = GET_CONFIG_STC(PetFuseConfig, dwIndex);
//            if (fsCfg) {
//                uint32 getCnt = 0;
//                if (mapGetItem.find(fsCfg->wGetItemId) != mapGetItem.end()) {
//                    getCnt = mapGetItem[fsCfg->wGetItemId];
//                }
//                getCnt += fsCfg->wGetCnt;
//                mapGetItem[fsCfg->wGetItemId] = getCnt;
//            }
            //金币
            ExpConfig::STC_EXP_CONFIG* lvCfg = GET_CONFIG_STC(ExpConfig, lv);
            if (lvCfg && lv > 0) {
                uint32 getCnt = 0;
                if (mapGetItem.find(coinId) != mapGetItem.end()) {
                    getCnt = mapGetItem[coinId];
                }
                getCnt += lvCfg->dwGetEquipFuseMoney * equip->GetConfigData().dwCostBaseValue / 100;
                mapGetItem[coinId] = getCnt;
            }
        }
    }
    
    std::map<uint32, uint32>::iterator it = mapGetItem.begin();
    for (; it != mapGetItem.end(); it++) {
        if (it->first == 0) {
            continue;
        }
        arrItemIcon[itemCnt]->loadIndexData(it->first);
        arrItemIcon[itemCnt]->showName();
        arrItemIcon[itemCnt]->showCntFromTo(it->second, it->second);
        arrItemIcon[itemCnt]->setBtnEnable(false);
        itemCnt++;
    }
    
    for (; itemCnt < arrItemIcon.size(); itemCnt++) {
        arrItemIcon[itemCnt]->setVisible(false);
    }
    
}

void CcbPetFuseLowQualityGetLayer::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    removeFromParent();
}

void CcbPetFuseLowQualityGetLayer::onPressControlButtonFuse(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    uint8 byType = g_FuseDada->getFuseTab() == E_FUSE_TAB_PET? E_UNITE_TYPE_PET : E_UNITE_TYPE_EQUIP;
    CGameSession::SendPetFuse(byType, g_FuseDada->getSelected());
    if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_SYS_GUIDE_7_MYSTERY) {
        GuideData::GetInstance()->onlyRmGuideLayer();
    }
}

void CcbPetFuseLowQualityGetLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    removeFromParent();
}



void CcbPetFuseLowQualityGetLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool CcbPetFuseLowQualityGetLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}







