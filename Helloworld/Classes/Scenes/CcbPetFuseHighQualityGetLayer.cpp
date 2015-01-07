#include "CcbPetFuseHighQualityGetLayer.h"
//#include "CcbManager.h"
#include "CcbPetIcon.h"
#include "CcbItemIconLayer.h"
#include "CFuseDadaMgr.h"
#include "ConfigGet.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "EnumDefines.h"
#include "GameSession.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPetFuseHighQualityGetLayer::~CcbPetFuseHighQualityGetLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
	CC_SAFE_RELEASE_NULL(m_pControlButtonFuse);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
	CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_1);
	CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_2);
	CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_3);
	CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_4);
    CC_SAFE_RELEASE_NULL(m_pLayerItemIcon_5);
	CC_SAFE_RELEASE_NULL(m_pNodeFusereward);
	CC_SAFE_RELEASE_NULL(m_pLayerPetIcon_1);
	CC_SAFE_RELEASE_NULL(m_pLayerPetIcon_2);
	CC_SAFE_RELEASE_NULL(m_pLayerPetIcon_3);
	CC_SAFE_RELEASE_NULL(m_pLayerPetIcon_4);
	CC_SAFE_RELEASE_NULL(m_pNodeFusepet);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetFuseHighQualityGetLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetFuseHighQualityGetLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetFuseHighQualityGetLayer", CcbPetFuseHighQualityGetLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/item_icon.ccb]", [ccb/item_icon.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/pet_icon.ccb]", [ccb/pet_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_fuse_highquality.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetFuseHighQualityGetLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbPetFuseHighQualityGetLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    loadData();
}

void CcbPetFuseHighQualityGetLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetFuseHighQualityGetLayer::onExit()
{
	CCLayer::onExit();
}

void CcbPetFuseHighQualityGetLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetFuseHighQualityGetLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFuse", CCControlButton*, this->m_pControlButtonFuse);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_1", CcbItemIconLayer*, this->m_pLayerItemIcon_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_2", CcbItemIconLayer*, this->m_pLayerItemIcon_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_3", CcbItemIconLayer*, this->m_pLayerItemIcon_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_4", CcbItemIconLayer*, this->m_pLayerItemIcon_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemIcon_5", CcbItemIconLayer*, this->m_pLayerItemIcon_5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFusereward", CCNode*, this->m_pNodeFusereward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetIcon_1", CcbPetIcon*, this->m_pLayerPetIcon_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetIcon_2", CcbPetIcon*, this->m_pLayerPetIcon_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetIcon_3", CcbPetIcon*, this->m_pLayerPetIcon_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetIcon_4", CcbPetIcon*, this->m_pLayerPetIcon_4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFusepet", CCNode*, this->m_pNodeFusepet);

	return false;
}

bool CcbPetFuseHighQualityGetLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetFuseHighQualityGetLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetFuseHighQualityGetLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetFuseHighQualityGetLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbPetFuseHighQualityGetLayer::onPressControlButtonCancel);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFuse", CcbPetFuseHighQualityGetLayer::onPressControlButtonFuse);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbPetFuseHighQualityGetLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetFuseHighQualityGetLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pControlButtonCancel->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pControlButtonFuse->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 1);
    
}

void CcbPetFuseHighQualityGetLayer::loadData()
{
    std::vector<uint32> arrId = g_FuseDada->getSelected();
    int petCnt = 0;
    int itemCnt = 0;
    
    uint32 coinId = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_COIN;
    
    std::vector<CcbPetIcon* > arrPetIcon;
    arrPetIcon.push_back(m_pLayerPetIcon_1);
    arrPetIcon.push_back(m_pLayerPetIcon_2);
    arrPetIcon.push_back(m_pLayerPetIcon_3);
    arrPetIcon.push_back(m_pLayerPetIcon_4);
    
    std::vector<CcbItemIconLayer* > arrItemIcon;
    arrItemIcon.push_back(m_pLayerItemIcon_1);
    arrItemIcon.push_back(m_pLayerItemIcon_2);
    arrItemIcon.push_back(m_pLayerItemIcon_3);
    arrItemIcon.push_back(m_pLayerItemIcon_4);
    arrItemIcon.push_back(m_pLayerItemIcon_5);
    
    
    std::map<uint32, uint32> mapGetItem;
    
    for (int i = 0; i < arrId.size(); i++) {
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrId[i]);
        if (!pet) {
            continue;
        }
        
        if (pet->GetbyStarLv() >= 5) {
            arrPetIcon[petCnt]->setPetId(pet->GetwIndex());
            arrPetIcon[petCnt]->setBtnEnable(false);
            petCnt++;
        }
        //融合获得
        PetFuseConfig::STC_PET_FUSE_CONFIG *fsCfg = GET_CONFIG_STC(PetFuseConfig, pet->GetwIndex());
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
        ExpConfig::STC_EXP_CONFIG* lvCfg = GET_CONFIG_STC(ExpConfig, pet->GetbyLv());
        if (lvCfg && pet->GetbyLv() > 0) {
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
        ExpConfig::STC_EXP_CONFIG* evoCfg = GET_CONFIG_STC(ExpConfig, pet->GetbyEvolveLv());
        if (evoCfg && pet->GetbyEvolveLv() > 0) {
            uint32 getCnt = 0;
            if (mapGetItem.find(evoCfg->dwGetPetFuseItemId) != mapGetItem.end()) {
                getCnt = mapGetItem[evoCfg->dwGetPetFuseItemId];
            }
            getCnt += evoCfg->dwGetPetFuseItemCnt;
            mapGetItem[evoCfg->dwGetPetFuseItemId] = getCnt;
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
    
    for (; petCnt < arrPetIcon.size(); petCnt++) {
        arrPetIcon[petCnt]->setVisible(false);
    }
    
    for (; itemCnt < arrItemIcon.size(); itemCnt++) {
        arrItemIcon[itemCnt]->setVisible(false);
    }
    
}

void CcbPetFuseHighQualityGetLayer::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    removeFromParent();
}

void CcbPetFuseHighQualityGetLayer::onPressControlButtonFuse(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    uint8 byType = E_UNITE_TYPE_PET;
    CGameSession::SendPetFuse(byType, g_FuseDada->getSelected());
    
}

void CcbPetFuseHighQualityGetLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    removeFromParent();
}



void CcbPetFuseHighQualityGetLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool CcbPetFuseHighQualityGetLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}




