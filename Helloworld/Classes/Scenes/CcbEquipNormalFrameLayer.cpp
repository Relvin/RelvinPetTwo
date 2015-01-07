#include "CcbEquipNormalFrameLayer.h"
//#include "CcbManager.h"
#include "EquipDataMgr.h"
#include "PacketDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "PetCtrl.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "EmblemDataMgr.h"
#include "MusicCtrl.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "Team.h"
#include "TeamCtrl.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbEquipNormalFrameLayer::~CcbEquipNormalFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteRune1);
	CC_SAFE_RELEASE_NULL(m_pSpriteRune2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFState);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEquipAttri1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEquipAttri2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRuneAttri1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRuneAttri2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEquipAttriText1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEquipAttriText2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRuneAttriText1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRuneAttriText2);
	CC_SAFE_RELEASE_NULL(m_pControlButtonEvo);
	CC_SAFE_RELEASE_NULL(m_pControlButtonStrengthen);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEquipNormalFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEquipNormalFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEquipNormalFrameLayer", CcbEquipNormalFrameLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/item_icon.ccb]", [ccb/item_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_normal_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEquipNormalFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEquipNormalFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    
}

void CcbEquipNormalFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonStrengthen, GuideBtnPos::E_EQUIP_ON);
    }
}

void CcbEquipNormalFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEquipNormalFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEquipNormalFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRune1", CCSprite*, this->m_pSpriteRune1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRune2", CCSprite*, this->m_pSpriteRune2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFState", CCLabelTTF*, this->m_pLabelTTFState);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEquipAttri1", CCLabelTTF*, this->m_pLabelTTFEquipAttri1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEquipAttri2", CCLabelTTF*, this->m_pLabelTTFEquipAttri2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRuneAttri1", CCLabelTTF*, this->m_pLabelTTFRuneAttri1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRuneAttri2", CCLabelTTF*, this->m_pLabelTTFRuneAttri2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEquipAttriText1", CCLabelTTF*, this->m_pLabelTTFEquipAttriText1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEquipAttriText2", CCLabelTTF*, this->m_pLabelTTFEquipAttriText2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRuneAttriText1", CCLabelTTF*, this->m_pLabelTTFRuneAttriText1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRuneAttriText2", CCLabelTTF*, this->m_pLabelTTFRuneAttriText2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEvo", CCScrollButton*, this->m_pControlButtonEvo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStrengthen", CCScrollButton*, this->m_pControlButtonStrengthen);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);

	return false;
}

bool CcbEquipNormalFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEquipNormalFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEquipNormalFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEquipNormalFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEvo", CcbEquipNormalFrameLayer::onPressControlButtonEvo);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonStrengthen", CcbEquipNormalFrameLayer::onPressControlButtonStrengthen);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipNormalFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_dwEquipObjId = 0;
    m_byType = 0;
    m_bTouchFlag = false;
    m_bySite = 0;
}



void CcbEquipNormalFrameLayer::onPressControlButtonEvo(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_bTouchFlag = true;
    switch (m_byType) {
        case E_EQUIP_FRAME_DOWN:
        case E_EQUIP_FRAME_WEAR:
            onEnhance();
            break;
        default:
        {
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_SPECIAL);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                m_bTouchFlag = false;
                return;
            }
        }
            onEvo();
            break;
    }
    
}

void CcbEquipNormalFrameLayer::onPressControlButtonStrengthen(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    switch (m_byType) {
        case E_EQUIP_FRAME_DOWN:
            onDown();
            break;
        case E_EQUIP_FRAME_WEAR:
            onWear();
            break;
        case E_EQUIP_FRAME_ENHANCE:
            onEnhance();
            break;
        case E_EQUIP_FRAME_RUNE:
            onRune();
            break;
            
        default:
            break;
    }
}

void CcbEquipNormalFrameLayer::loadData(uint32 dwEquipObjId)
{
    m_dwEquipObjId = dwEquipObjId;
    const CEquip* equip = g_PacketDataMgr->GetEquipInfoByKeyID(m_dwEquipObjId);
    
    if (!equip) {
        return;
    }
    
    //icon
    m_pLayerIcon->loadObjData(m_dwEquipObjId, E_UNITE_TYPE_EQUIP);
    m_pLayerIcon->hideName();
    m_pLayerIcon->setBtnEnable(false);
    //名字}
    m_pLabelTTFName->setString(equip->GetConfigData().strName.c_str());
    uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(equip->GetIndex());
    m_pLabelTTFName->setColor(g_PacketDataMgr->getQualityColor(quality));
    
    //装备者}
    CCString* str = CCString::create("");
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(CTeamCtrl::GetCurTeam()->getarrPetObId()[equip->GetWearPetID()/10000]);
    if (pet) {
        PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
        if (petCfg) {
            //m_pLabelTTFState->setString(const char *label)
            str->initWithFormat("装备于%s", petCfg->strName.c_str());
        }
    }
    m_pLabelTTFState->setString(str->getCString());
    //属性}
    std::vector<CCLabelTTF*> arrAttri;
    arrAttri.push_back(m_pLabelTTFEquipAttri1);
    arrAttri.push_back(m_pLabelTTFEquipAttri2);
    arrAttri.push_back(m_pLabelTTFRuneAttri1);
    arrAttri.push_back(m_pLabelTTFRuneAttri2);
    
    std::vector<CCLabelTTF*> arrTextAttri;
    arrTextAttri.push_back(m_pLabelTTFEquipAttriText1);
    arrTextAttri.push_back(m_pLabelTTFEquipAttriText2);
    arrTextAttri.push_back(m_pLabelTTFRuneAttriText1);
    arrTextAttri.push_back(m_pLabelTTFRuneAttriText2);
    
    std::vector<uint32> arrValue;

    /*
     E_EQUIP_dwRunes1,		// 5 符文 1	}
     E_EQUIP_dwRunes2,		// 6 符文 2}
     E_EQUIP_dwAddHp,		// 7 血量}
     E_EQUIP_dwAddCA,		// 8 普攻}
     E_EQUIP_dwAddCD,		// 9 普防}
     E_EQUIP_dwAddRev,		// 10 回复}
     E_EQUIP_dwAddSA,		// 11 特攻}
     E_EQUIP_dwAddSD,		// 12 特防}
     
     E_EQUIP_dwAddCrit,		// 13 暴击}
     E_EQUIP_dwAddSpeed,		// 14 速度}
     E_EQUIP_dwAddHit,		// 15 命中}
     E_EQUIP_dwAddDodge,		// 16 闪避}
     E_EQUIP_dwAddCritDamage,	// 17 暴伤}
     E_EQUIP_dwAddCritFree,		// 18 抗暴}
     E_EQUIP_dwAddAllAtk,    //全攻}
     */
    
    
    arrValue.push_back(equip->GetHP());
    arrValue.push_back(0);//普攻
    arrValue.push_back(equip->GetCDef());
    arrValue.push_back(equip->GetRev());
    arrValue.push_back(0);//特攻
    arrValue.push_back(equip->GetSDef());
    arrValue.push_back(equip->GetCrit());
    arrValue.push_back(equip->GetSpeed());
    arrValue.push_back(equip->GetHit());
    arrValue.push_back(equip->GetDodge());
    arrValue.push_back(equip->GetCritDamage());
    arrValue.push_back(equip->GetCritFree());
    arrValue.push_back(0);//全攻

    int cnt = 0;
    //全攻
    if (equip->GetAllAtk() > 0) {
        str->initWithFormat("+%d", equip->GetAllAtk());
        arrAttri[cnt]->setString(str->getCString());
        
        arrTextAttri[cnt]->setVisible(true);
        arrTextAttri[cnt]->setString(g_PacketDataMgr->getAttrText(E_ATTR_ALL_ATT).c_str());
        cnt++;
    }
    //普攻
    if (equip->GetCAtk() - equip->GetAllAtk() > 0) {
        str->initWithFormat("+%d", equip->GetCAtk() - equip->GetAllAtk());
        arrAttri[cnt]->setString(str->getCString());
        
        arrTextAttri[cnt]->setVisible(true);
        arrTextAttri[cnt]->setString(g_PacketDataMgr->getAttrText(E_ATTR_CATT).c_str());
        cnt++;
    }
    //特攻
    if (equip->GetSAtk() - equip->GetAllAtk() > 0) {
        str->initWithFormat("+%d", equip->GetSAtk() - equip->GetAllAtk());
        arrAttri[cnt]->setString(str->getCString());
        
        arrTextAttri[cnt]->setVisible(true);
        arrTextAttri[cnt]->setString(g_PacketDataMgr->getAttrText(E_ATTR_SATT).c_str());
        cnt++;
    }
    
    for (int i = 0 ; i < arrValue.size(); i++) {
        if (arrValue[i] > 0 && cnt < arrAttri.size()) {
            str->initWithFormat("+%d", arrValue[i]);
            arrAttri[cnt]->setString(str->getCString());
            
            arrTextAttri[cnt]->setVisible(true);
            arrTextAttri[cnt]->setString(g_PacketDataMgr->getAttrText(i+1).c_str());
            cnt++;
        }
    }
    for (; cnt < arrAttri.size(); cnt++) {
        arrAttri[cnt]->setString("");
        arrTextAttri[cnt]->setVisible(false);
    }
    //镶嵌}
    if (equip->GetRune1()) {
        m_pSpriteRune1->setVisible(true);
        m_pSpriteRune1->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetRuneIconByIndex(equip->GetRune1()).c_str()));
    }
    else{
        m_pSpriteRune1->setVisible(false);
    }
    if (equip->GetRune2()) {
        m_pSpriteRune2->setVisible(true);
        m_pSpriteRune2->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetRuneIconByIndex(equip->GetRune2()).c_str()));
    }
    else{
        m_pSpriteRune2->setVisible(false);
    }

}

void CcbEquipNormalFrameLayer::setFrameType(uint8 type)
{
    m_byType = type;
    string str = "";
    m_pControlButtonEvo->setVisible(false);
    switch (m_byType) {
        case E_EQUIP_FRAME_DOWN:
            str = GET_STR(Str_Discharge);
            m_pLabelTTFState->setString(GET_STR(Str_Equiped));
            break;
        case E_EQUIP_FRAME_WEAR:
            str = GET_STR(Str_equip);
            break;
        case E_EQUIP_FRAME_ENHANCE:
            str = GET_STR(Str_Enhance);
            break;
        case E_EQUIP_FRAME_RUNE:
            str = GET_STR(Str_equip_inlay);
            break;
            
        default:
            break;
    }
    
    if (m_byType == E_EQUIP_FRAME_ENHANCE) {
        uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_EQUIP_EVO);
        if (syslockId) {
            m_pControlButtonEvo->setColor(ccGRAY);
        }
    }
    
    m_pControlButtonStrengthen->setTitleForState(CCString::create(str), CCControlStateNormal);
    m_pControlButtonStrengthen->setTitleForState(CCString::create(str), CCControlStateHighlighted);
    m_pControlButtonStrengthen->setTitleForState(CCString::create(str), CCControlStateDisabled);
}

void CcbEquipNormalFrameLayer::onWear()
{
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(m_dwEquipObjId);
    if (pEquip && m_bySite)
    {
        g_EquipTeamData->wearEquip(m_bySite, pEquip->GetConfigData().byPos-1, m_dwEquipObjId);
        CGameSession::SendEquipToPet(m_dwEquipObjId, m_bySite, pEquip->GetConfigData().byPos-1);
    }
}

void CcbEquipNormalFrameLayer::onDown()
{
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(m_dwEquipObjId);
    g_EquipData->SetChosenEquipKeyID(0);
    if (pEquip)
    {
        g_EquipTeamData->downEquip(m_bySite, pEquip->GetConfigData().byPos-1);
        CGameSession::SendEquipVail(m_dwEquipObjId, m_bySite, pEquip->GetConfigData().byPos-1);
    }
}

void CcbEquipNormalFrameLayer::onEnhance()
{
    g_EquipData->SetChosenEquipKeyID(m_dwEquipObjId);
    BackCtrl::InsertNextScene(kEquipStrengthenScene);
}

void CcbEquipNormalFrameLayer::onRune()
{
    if (m_bTouchFlag) {
        return;
    }
    m_bTouchFlag = true;
    g_EquipData->SetChosenEquipKeyID(m_dwEquipObjId);
    BackCtrl::BacktoUpperScene();
}

void CcbEquipNormalFrameLayer::onEvo()
{
    g_EquipData->SetChosenEquipKeyID(m_dwEquipObjId);
    BackCtrl::InsertNextScene(kEquipEvolveScene);
}

void CcbEquipNormalFrameLayer::setClipRect(CCRect rect)
{
    m_pControlButtonEvo->setClipRect(rect);
    m_pControlButtonStrengthen->setClipRect(rect);
}

