#include "CcbPetShowLayer.h"
#include "CcbLeftArrow.h"
#include "CcbRightArrow.h"
#include "CcbPetShowTitle.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "PetCtrl.h"
#include "UISupport.h"
#include "MainScene.h"
#include "BackCtrl.h"

#include "CcbPetShowBackLayer.h"
#include "ItemDataMgr.h"
#include "EquipDataMgr.h"
#include "ConfigData.h"
#include "GameSession.h"
#include "SystemMessage.h"
#include "EnumDefines.h"
#include "ResourceStringConverter.h"
#include "ResourceStringClient.h"
#include "SequencePet.h"
#include "SequenceAction.h"
#include "MusicCtrl.h"
#include "CcbShareFrameLayer.h"
#include "Role.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "GameSession.h"
#include "Emblem.h"
#include <algorithm>
#include "PacketDataMgr.h"
#include "Instruments.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "FriendCtrl.h"
#include "CcbPetInfoLayer.h"
#include "ShareWeiboWeixin.h"
#include "EmblemDataMgr.h"
#include "GuideBtnPos.h"
#include "GlobalData.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define MOVE_INCH            7.0f/160.0f

CcbPetShowScene::~CcbPetShowScene()
{

    
}

CCScene *CcbPetShowScene::scene()
{
    CCScene* scene = CCScene::create();
    CcbPetShowScene *layer = CcbPetShowScene::create();
    scene->addChild(layer, 1, 1);
    return scene;
}

bool CcbPetShowScene::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CcbPetShowLayer* layer = dynamic_cast<CcbPetShowLayer*>(CcbManager::sharedManager()->LoadCcbPetShowLayer(this));
    this->addChild(layer);
    layer->setTag(1);
	return true;
}

void CcbPetShowScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbPetShowScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(CCFadeIn::create(1.0f));
}

void CcbPetShowScene::onExit()
{
	CCLayer::onExit();
    
}

void CcbPetShowScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
    CCAction* pAction = CCFadeOut::create(1.0f);
    this->runAction(pAction);
}

bool CcbPetShowLayer::m_bIsChangePetEnable = true;
CcbPetShowLayer* CcbPetShowLayer::m_curScene = NULL;

CcbPetShowLayer::~CcbPetShowLayer()
{
    CC_SAFE_RELEASE_NULL(m_pSpriteBg);
    CC_SAFE_RELEASE_NULL(m_pLayerBack);
    CC_SAFE_RELEASE_NULL(m_pLayerHaloLight);
    CC_SAFE_RELEASE_NULL(m_pSpritePaint);
    CC_SAFE_RELEASE_NULL(m_pLayerEquip1);
    CC_SAFE_RELEASE_NULL(m_pLayerEquip3);
    CC_SAFE_RELEASE_NULL(m_pLayerEmblem1);
    CC_SAFE_RELEASE_NULL(m_pLayerEquip2);
    CC_SAFE_RELEASE_NULL(m_pLayerEquip4);
    CC_SAFE_RELEASE_NULL(m_pLayerEmblem2);

    CC_SAFE_RELEASE_NULL(m_pControlButtonUp);
    CC_SAFE_RELEASE_NULL(m_pControlButtonStrong);
    CC_SAFE_RELEASE_NULL(m_pControlButtonYijian);
    CC_SAFE_RELEASE_NULL(m_pControlButtonChange);
    CC_SAFE_RELEASE_NULL(m_pSpriteExp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFProperty);
    CC_SAFE_RELEASE_NULL(m_pSpritePetType);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Text_SkillInfo);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNormal_AtkName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSkill_alkName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFHp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRec);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAtt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCrit);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSDef);
    CC_SAFE_RELEASE_NULL(m_pControlButtonShowSkill);
    CC_SAFE_RELEASE_NULL(m_pLayerFlash);
    CC_SAFE_RELEASE_NULL(m_pControlButtonWeiBo);
    CC_SAFE_RELEASE_NULL(m_pControlButtonWeiXin);
    CC_SAFE_RELEASE_NULL(m_pLayerShare);
    CC_SAFE_RELEASE_NULL(m_pLayerBottom);
    CC_SAFE_RELEASE_NULL(m_pLayerLeft);
    CC_SAFE_RELEASE_NULL(m_pLayerRight);
    
    CC_SAFE_RELEASE_NULL(m_pControlButtonEmblem_1);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEmblem_2);
    CC_SAFE_RELEASE_NULL(m_pSpriteEmblemHas_1);
    CC_SAFE_RELEASE_NULL(m_pSpriteEmblemHas_2);
    
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJiPan1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJiPan2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJiPan3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJiPan4);
    
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBadage1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBadage2);

    CC_SAFE_RELEASE_NULL(m_pLabelTTFPetLv);
    
    CC_SAFE_RELEASE_NULL(m_pSpriteCanEvo);
    
    CC_SAFE_RELEASE_NULL(m_pNodeShareReward);
    
    m_curScene = NULL;
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetShowLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetShowLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetShowLayer", CcbPetShowLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/arrowleft.ccb]", [ccb/arrowleft.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/arrowright.ccb]", [ccb/arrowright.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/petshowtitle.ccb]", [ccb/petshowtitle.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

bool CcbPetShowLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    isfriend = false;
    curPage = 0;
    this->setTouchEnabled(true);
    m_curScene = this;
	return true;
}

void CcbPetShowLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}

    isfriend = CPetCtrl::Get()->getIsFirendLook();
    if (!isfriend) {
        
        if (g_EquipData->getIsEquipShow()) {
            CTeam* team = CTeamCtrl::GetCurTeam();
            for (int i = 0; i < team->getarrPetObId().size(); i++) {
                if (team->getarrPetObId()[i] == 0) {
                    continue;
                }
                m_arrPetObjId.push_back(team->getarrPetObId()[i]);
            }
        }
        else{
            CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_ALL);
            m_arrPetObjId = CPetCtrl::Get()->GetBagPets();
        }
        
        //队伍编辑中进入的话，替换队员就显示替换的队员；下阵就显示队伍中第一个队员}
        if (g_EquipData->getIsEquipShow()) {
            CTeam* team = CTeamCtrl::GetCurTeam();
            uint32 objId = team->getarrPetObId()[CTeamCtrl::GetSelectedMemberSite()];
            if (!objId) {
                objId = m_arrPetObjId[0];
            }
            CPetCtrl::Get()->SetShowPetObjId(objId);
        }

        setPetObjectId(CPetCtrl::Get()->GetShowPetObjId());
        
        m_pet = CPetCtrl::Get()->GetPetByObjId(m_wObjectId);
        if (!m_pet)
        {
            return;
        }
        loadPetData();
    }
    else{
        handleOtherRoleInfo(*FriendCtrl::Get()->getFriendPet());
    }
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonStrong, GuideBtnPos::E_PET_ENHANCE);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonUp, GuideBtnPos::E_PET_EVOLVE);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonEmblem_1, GuideBtnPos::E_PET_BADGE);
    }
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CcbPetShowLayer::listenToBackFromNotification), "SHARE_SUCCESS", NULL);
    this->listenToBackFromNotification(NULL);
}

void CcbPetShowLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetShowLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
    runAction(
              CCSequence::create(
                                 CCDelayTime::create(0.2f),
                                 CCCallFunc::create(this, callfunc_selector(CcbPetShowLayer::restoreTouch)),
                                 NULL
                                 )
              );
}

void CcbPetShowLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_GUIDE_TRIGGER_1_PET_ENHANCE,
                                                 GuideData::E_GUIDE_TRIGGER_0_PET_EVOLVE,
                                                 GuideData::E_SYS_GUIDE_8_BADGE,
                                                 GuideData::E_SYS_GUIDE_10_BADGE,
                                                 NULL
                                                 );
    }
}

void CcbPetShowLayer::restoreTouch() {
    m_bCanTouchBtn = true;
}

void CcbPetShowLayer::onExit()
{
	CCLayer::onExit();
    CPetCtrl::Get()->setIsFriendLook(false);
    m_bIsChangePetEnable = true;
    m_curScene = NULL;
    
    if (CTeamCtrl::GetTeamChanged()) {
        CTeamCtrl::SaveTeamUpdate();
    }
    
    CCDirector::sharedDirector()->purgeCachedData();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "SHARE_SUCCESS");
}

void CcbPetShowLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetShowLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBack", CcbPetShowBackLayer*, this->m_pLayerBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEmblem1", CcbItemIconLayer*, this->m_pLayerEmblem1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEmblem2", CcbItemIconLayer*, this->m_pLayerEmblem2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquip1", CcbPetEquipIcon*, this->m_pLayerEquip1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquip3", CcbPetEquipIcon*, this->m_pLayerEquip3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquip2", CcbPetEquipIcon*, this->m_pLayerEquip2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEquip4", CcbPetEquipIcon*, this->m_pLayerEquip4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHaloLight", CcbHaloLightLayer*, this->m_pLayerHaloLight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerShare", CCLayer*, this->m_pLayerShare);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, this->m_pLayerBottom);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerLeft", CCLayer*, this->m_pLayerLeft);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRight", CCLayer*, this->m_pLayerRight);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePaint", CCSprite*, this->m_pSpritePaint);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonUp", CCControlButton*, this->m_pControlButtonUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStrong", CCControlButton*, this->m_pControlButtonStrong);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonYijian", CCControlButton*, this->m_pControlButtonYijian);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonChange", CCControlButton*, this->m_pControlButtonChange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteExp", CCSprite*, this->m_pSpriteExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFProperty", CCLabelTTF*, this->m_pLabelTTFProperty);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetType", CCSprite*, this->m_pSpritePetType);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Text_SkillInfo", CCLabelTTF*, this->m_pLabelTTF_Text_SkillInfo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNormal_AtkName", CCLabelTTF*, this->m_pLabelTTFNormal_AtkName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSkill_alkName", CCLabelTTF*, this->m_pLabelTTFSkill_alkName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFHp", CCLabelTTF*, this->m_pLabelTTFHp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRec", CCLabelTTF*, this->m_pLabelTTFRec);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAtt", CCLabelTTF*, this->m_pLabelTTFAtt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCrit", CCLabelTTF*, this->m_pLabelTTFCrit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCDef", CCLabelTTF*, this->m_pLabelTTFCDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSDef", CCLabelTTF*, this->m_pLabelTTFSDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShowSkill", CCControlButton*, this->m_pControlButtonShowSkill);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerFlash", CCLayer*, this->m_pLayerFlash);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonWeiBo", CCControlButton*, this->m_pControlButtonWeiBo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonWeiXin", CCControlButton*, this->m_pControlButtonWeiXin);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEmblem_1", CCControlButton*, this->m_pControlButtonEmblem_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEmblem_2", CCControlButton*, this->m_pControlButtonEmblem_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEmblemHas_1", CCSprite*, this->m_pSpriteEmblemHas_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEmblemHas_2", CCSprite*, this->m_pSpriteEmblemHas_2);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetLv", CCLabelTTF*, this->m_pLabelTTFPetLv);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJiPan1", CCLabelTTF*, this->m_pLabelTTFJiPan1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJiPan2", CCLabelTTF*, this->m_pLabelTTFJiPan2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJiPan3", CCLabelTTF*, this->m_pLabelTTFJiPan3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJiPan4", CCLabelTTF*, this->m_pLabelTTFJiPan4);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBadage1", CCLabelTTF*, this->m_pLabelTTFBadage1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBadage2", CCLabelTTF*, this->m_pLabelTTFBadage2);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanEvo", CCSprite*, this->m_pSpriteCanEvo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeShareReward", CCNode*, this->m_pNodeShareReward);
    
	return false;
}

bool CcbPetShowLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetShowLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
//    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onShowAll", CcbPetShowLayer::onShowAll);
	return NULL;
}

SEL_MenuHandler CcbPetShowLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetShowLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonWeiBo", CcbPetShowLayer::onPressControlButtonWeiBo);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonWeiXin", CcbPetShowLayer::onPressControlButtonWeiXin);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUp", CcbPetShowLayer::onPressControlButtonUp);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonStrong", CcbPetShowLayer::onPressControlButtonStrong);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonYijian", CcbPetShowLayer::onPressControlButtonYijian);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShowSkill", CcbPetShowLayer::onPressControlButtonShowSkill);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonChange", CcbPetShowLayer::onPressControlButtonChange);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEmblem", CcbPetShowLayer::onPressControlButtonEmblem);
	return NULL;
}
void CcbPetShowLayer::onPressControlButtonShowSkill(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (isfriend) {
        if (!m_petInfo) {
            m_petInfo = dynamic_cast<CcbPetInfoLayer*>(CcbManager::sharedManager()->LoadCcbPetInfoLayer());
            m_petInfo->loadPetData(m_pet);
            CCDirector::sharedDirector()->getRunningScene()->addChild(m_petInfo, 999);
            return;
        }
        else{
            m_petInfo->setVisible(true);            
        }
    }
    else{
        BackCtrl::InsertNextScene(kPetInfoScene);
    }
}

void CcbPetShowLayer::onPressControlButtonYijian(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_UNIT_EQUIP);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    putOnTheBestEquip();
}

void CcbPetShowLayer::onPressControlButtonStrong(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CPetCtrl::Get()->SetIntensifyPet(m_wObjectId);
    BackCtrl::InsertNextScene(kEnhanceScene);
}

void CcbPetShowLayer::onPressControlButtonUp(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CPetCtrl::Get()->SetEvolvePet(m_wObjectId);
    BackCtrl::InsertNextScene(kEvolveScene);
}

void CcbPetShowLayer::onPressControlButtonEmblem(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    g_EmblemData->setEmbInType(E_EMB_IN_TYPE_WEAR);
    BackCtrl::InsertNextScene(kEmblemListSenec);
}


void CcbPetShowLayer::onPressControlButtonWeiBo(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    CCRenderTexture* rt = CCRenderTexture::create(CCDirector::sharedDirector()->getWinSize().width , CCDirector::sharedDirector()->getWinSize().height);
    m_pLayerShare->setVisible(false);
    rt->begin();
    this->visit();
    rt->end();
    rt->saveToFile("screenshot.png", kCCImageFormatPNG);
    rt->release();
    m_pLayerShare->setVisible(true);

#if ENABLE_SHARE
    ShareWeiboWeixin::Create();
    ShareWeiboWeixin::Get()->onShareWeibo(GET_STR(Str_share_text_petshow));
#endif
}

void CcbPetShowLayer::onPressControlButtonWeiXin(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    CCRenderTexture* rt = CCRenderTexture::create(CCDirector::sharedDirector()->getWinSize().width , CCDirector::sharedDirector()->getWinSize().height);
    m_pLayerShare->setVisible(false);
    rt->begin();
    this->visit();
    rt->end();
    rt->saveToFile("screenshot.png", kCCImageFormatPNG);
    rt->release();
    m_pLayerShare->setVisible(true);
#if ENABLE_SHARE
    ShareWeiboWeixin::Create();
    ShareWeiboWeixin::Get()->onShareWeiXin(GET_STR(Str_share_text_petshow));
#endif
}

void CcbPetShowLayer::onPressControlButtonChange(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CTeam* team = CTeamCtrl::GetCurTeam();
    uint8 site = CTeamCtrl::getSiteByPetId(m_pet->GetObjId());
    if (!site) {
        return;
    }
    //组队界面进入宠物背包}
    if (team->getbyLeaderSite() == site) {
        CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_PARTY_LEADER);
    }
    else
    {
        CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_PARTY_NORMAL);
    }
    CTeamCtrl::SetSelectedMemberSite(site);
    BackCtrl::InsertNextScene(kPetBagScene, kNormalTrans);
}

// Inhert CCNodeLoaderListener
void CcbPetShowLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    isShareChange = false;
    m_arrPetObjId.clear();
    CPetCtrl::Get()->SetNeedRefreshValue(true);
    m_wObjectId = 0;
    m_pSpritePaint->setVisible(true);
    m_pSpriteCanEvo->setVisible(false);
    m_pLabelTTFProperty->noStroke();
    
    m_pSpritePaint->setPositionY((getBottom(m_pLayerBack) + (getTop(m_pLayerBottom) - 20)) * 0.5 );
    
    m_pLayerEmblem1->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pLayerEmblem2->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pLayerEmblem1->hideCnt();
    m_pLayerEmblem2->hideCnt();
    
    m_pLayerEquip1->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pLayerEquip2->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pLayerEquip3->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pLayerEquip4->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pControlButtonEmblem_1->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pControlButtonEmblem_2->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pControlButtonYijian->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pControlButtonWeiBo->setTouchPriority(kCCMenuHandlerPriority - 3);
    m_pControlButtonWeiXin->setTouchPriority(kCCMenuHandlerPriority - 3);
    
    arrEquip[0] = m_pLayerEquip1;
    arrEquip[1] = m_pLayerEquip2;
    arrEquip[2] = m_pLayerEquip3;
    arrEquip[3] = m_pLayerEquip4;
    
    arrQyName[0] = m_pLabelTTFJiPan1;
    arrQyName[1] = m_pLabelTTFJiPan2;
    arrQyName[2] = m_pLabelTTFJiPan3;
    arrQyName[3] = m_pLabelTTFJiPan4;

    arrQyName[4] = m_pLabelTTFBadage1;
    arrQyName[5] = m_pLabelTTFBadage2;
    
    //点击不播声音的node}
    arrUnTouchNode.push_back(m_pLayerLeft);
    arrUnTouchNode.push_back(m_pLayerRight);
    arrUnTouchNode.push_back(m_pLayerBack);
    arrUnTouchNode.push_back(m_pControlButtonUp->getParent());
    
    m_pLabelTTF_Text_SkillInfo->runAction(
                                          CCRepeatForever::create(
                                                                  CCSequence::create(
                                                                                     CCFadeOut::create(1.5),
                                                                                     CCFadeIn::create(1.5),
                                                                                     NULL
                                                                                     )
                                                                  )
                                          );
    
    m_pSpritePaint->runAction(
                              CCRepeatForever::create(
                                                      CCSequence::create(
                                                                         CCScaleTo::create(1.5, 0.95),
                                                                         CCScaleTo::create(1.5, 1.0),
                                                                         NULL
                                                                         )
                                                      )
                              );
    
    expBarW = getWidth(m_pSpriteExp);
    if (GlobalData::shared()->getShareSwitch()) {
        m_pLayerShare->setVisible(false);
    }
}


void CcbPetShowLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 2, true);
}


bool CcbPetShowLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCRect rect;
    CCPoint p = this->convertToWorldSpace(pTouch->getLocation());
    for ( int i = 0; i < arrUnTouchNode.size(); i++) {
        CCNode* node = arrUnTouchNode[i];
        if (!node || !node->isVisible()) {
            continue;
        }
        rect.origin = getWorldPos(node);
        rect.size = node->getContentSize();
        if (rect.containsPoint(p)) {
            return false;
        }
    }
    
    m_tTouchPoint = p;//this->convertTouchToNodeSpace(pTouch);
    m_fTouchLength = 0.0f;
    
    return true;
}
void CcbPetShowLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

    CCPoint touchPointNow = this->convertTouchToNodeSpace(pTouch);
    //    CCLog("touchPointNow.x %f", touchPointNow.y);
    m_fTouchLength = touchPointNow.x - m_tTouchPoint.x;
    //    CCLog("滑动距离: %f", d);
}
void CcbPetShowLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_bIsChangePetEnable || (m_fTouchLength < 40.0 && m_fTouchLength > -40.0)) {
//        CPet* pet = CPetCtrl::Get()->GetPetByObjId(m_wObjectId);
        //技能释放时播放技能语音}
        PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_pet->GetwIndex());
        if (petCfg) {
            CMusicCtrl::StopEffect(m_soundId);
            m_soundId = CMusicCtrl::PlayEffect(GET_PET_SOUND(petCfg->wSoundAlt));
        }
        
        if (!isfriend && !isShareChange) {
            if (!m_bCanTouchBtn) {
                return;
            }
            
            isShareChange = true;
            //分享与技能板切换
            if (m_pLayerBottom->getPositionY() < 0) {
                
                m_pLayerLeft->runAction(CCMoveBy::create(0.2, ccp(getLeft(m_pLayerLeft->getParent()) + getWidth(m_pLayerLeft), 0)));
                m_pLayerRight->runAction(CCMoveBy::create(0.2, ccp(-getLeft(m_pLayerLeft->getParent()) - getWidth(m_pLayerLeft), 0)));
                
                m_pLayerShare->runAction(CCMoveBy::create(0.2, ccp(0, -getHeight(m_pLayerShare))));
                m_pLayerBottom->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                                             CCMoveBy::create(0.2, ccp(0, getHeight(m_pLayerBottom))),
                                                             CCCallFunc::create(this, callfunc_selector(CcbPetShowLayer::shareChangeEnd)),
                                                             NULL));
                
            }
            else{
                m_pLayerLeft->runAction(CCMoveBy::create(0.2, ccp(-getLeft(m_pLayerLeft->getParent()) - getWidth(m_pLayerLeft), 0)));
                m_pLayerRight->runAction(CCMoveBy::create(0.2, ccp(getLeft(m_pLayerLeft->getParent()) + getWidth(m_pLayerLeft), 0)));
                
                m_pLayerBottom->runAction(CCMoveBy::create(0.2, ccp(0, -getHeight(m_pLayerBottom))));
                m_pLayerShare->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                                             CCMoveBy::create(0.2, ccp(0, getHeight(m_pLayerShare))),
                                                             CCCallFunc::create(this, callfunc_selector(CcbPetShowLayer::shareChangeEnd)),
                                                             NULL));
            }
        }
        
        return;
    }
    relocateContainer();

}

void CcbPetShowLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

void CcbPetShowLayer::relocateContainer()
{
    if (m_fTouchLength > 80.0)
    {
        curPage--;
    }
    else if (m_fTouchLength< -80.0)
    {
        curPage++;
    }

    if (curPage < 0)
    {
        curPage += m_arrPetObjId.size();
    }
    else if (curPage > m_arrPetObjId.size() - 1)
    {
        curPage = curPage % m_arrPetObjId.size();
    }
    
    changePage();
}

void CcbPetShowLayer::changePage()
{
    if(m_wObjectId != m_arrPetObjId[curPage])
    {
        m_wObjectId = m_arrPetObjId[curPage];
        CPetCtrl::Get()->SetShowPetObjId(m_wObjectId);
        m_pet = CPetCtrl::Get()->GetPetByObjId(m_wObjectId);
        
        if (g_EquipData->getIsEquipShow()) {
            uint8 site = CTeamCtrl::getSiteByPetId(m_pet->GetObjId());
            CTeamCtrl::SetSelectedMemberSite(site);
        }
        
        CPetCtrl::Get()->SetNeedRefreshValue(true);
        
        this->runAction(
                        CCSequence::create(
                                           CCFadeOut::create(TRANS_DUR),
                                           CCCallFunc::create(this, callfunc_selector(CcbPetShowLayer::loadPetData)),
                                           CCFadeIn::create(TRANS_DUR),
                                           NULL
                                           )
                        );
    };
}


void CcbPetShowLayer::setPetObjectId(uint32 wObjectId)
{
    if (m_wObjectId != wObjectId) {
        m_wObjectId = wObjectId;
        
        for (int i = 0; i < m_arrPetObjId.size(); i++) {
            if (m_wObjectId == m_arrPetObjId[i]) {
                curPage = i;
                break;
            }
        }
//        loadPetData();
    }
}

void CcbPetShowLayer::loadPetData()
{
//    m_wObjectId = CPetCtrl::Get()->GetShowPetObjId();
//    CPet *pet = CPetCtrl::Get()->GetPetByObjId(m_wObjectId);
    if (!m_pet)
    {
        return;
    }
    //基础数值}
    m_pLayerBack->loadObjData(m_pet);
    
//    m_pLayerHaloLight->setShowInfoByIndex(m_pet->GetwIndex());
    CCString*str = CCString::create("");
    
    //宠物类型}
    m_pLabelTTFProperty->setString(CPetCtrl::Get()->GetPetTypeString(m_pet->GetwIndex()).c_str());
    //类型图片}
    m_pSpritePetType->setDisplayFrame(CPetCtrl::Get()->GetPetTypeSF(m_pet->GetwIndex()));

    //必杀技能}
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* cfgUlt = GET_CONFIG_STC(UltimateSkillConfig, m_pet->GetwInitialSkillId());
    if (cfgUlt) {
        CCString *str = CCString::createWithFormat("%s·%s ", cfgUlt->strName.c_str(), covert2Roman(m_pet->GetbyInitialSkillLv()).c_str());
        
        m_pLabelTTFSkill_alkName->setString(str->getCString());
    }
    else{
        m_pLabelTTFSkill_alkName->setString(GET_STR(Str_wu));
    }
    //普通技能}
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* cfgNor = GET_CONFIG_STC(UltimateSkillConfig, m_pet->GetwNormaleAttId());
    if (cfgUlt) {
        CCString *str = CCString::createWithFormat("%s ", cfgNor->strName.c_str());
        
        m_pLabelTTFNormal_AtkName->setString(str->getCString());
    }
    
    //情缘
    PetConfig::STC_PET_CONFIG* pCfg = GET_CONFIG_STC(PetConfig, m_pet->GetwIndex());
    int qyCnt = 0;
    if (pCfg) {
        for (int i = 0; i < 4; i ++) {
            uint32 qyId = pCfg->arrQyIndex[i];
            if (!qyId) {
                continue;
            }
            QingYuanConfig::STC_QING_YUAN_CONFIG* qyCfg = GET_CONFIG_STC(QingYuanConfig, qyId);
            if (!qyCfg) {
                continue;
            }
            arrQyName[qyCnt]->setString(qyCfg->strName.c_str());
            arrQyName[qyCnt]->setColor(ccGRAY);
            //非查看好友，并且在当前队伍中
            if (!isfriend && CTeamCtrl::getSiteByPetId(m_pet->GetObjId())) {
                if (CPetCtrl::Get()->checkQingyuanActi(qyId)) {
                    arrQyName[qyCnt]->setColor(ccGREEN);
                }
            }
            qyCnt++;
        }
    }
    
    
//    int emCnt = 0;
    CEmblem* emblem1 = g_EmblemData->getEmblemByObjId(m_pet->GetdwEmblemId1());
    CEmblem* emblem2 = g_EmblemData->getEmblemByObjId(m_pet->GetdwEmblemId2());
    uint32 emId1 = 0;
    uint32 emId2 = 0;
    if (emblem1) {
        emId1 = emblem1->getdwIndexId();
    }
    if (emblem2) {
        emId2 = emblem2->getdwIndexId();
    }
    
    EmblemShowConfig::STC_EMBLEM_SHOW_CONFIG* eCfg = GET_CONFIG_STC(EmblemShowConfig, pCfg->wGroupId);
    if (eCfg) {
        for (int i = 0; i < 2; i++) {
            if (!eCfg->wExcEmIndex[i]) {
                continue;
            }
            EmblemConfig::STC_EMBLEM_CONFIG *emCfg = GET_CONFIG_STC(EmblemConfig, eCfg->wExcEmIndex[i]);
            if (!emCfg) {
                continue;
            }
            arrQyName[qyCnt]->setString(eCfg->strName[i].c_str());
            if (eCfg->wExcEmIndex[i] == emId1
                || eCfg->wExcEmIndex[i] == emId2) {
                arrQyName[qyCnt]->setColor(ccGREEN);
            }
            else{
                arrQyName[qyCnt]->setColor(ccGRAY);
            }
            qyCnt++;
        }
    }
    
    if (qyCnt == 0) {
        arrQyName[0]->setString(GET_STR(Str_wu));
        arrQyName[0]->setColor(ccWHITE);
        qyCnt++;
    }
    
    for (; qyCnt < 6; qyCnt++) {
        arrQyName[qyCnt]->setString("");
    }
    
    
    //原画}
    std::string paintPath = CPetCtrl::Get()->GetPetBodyPicName(m_pet->GetwIndex());
    CCTexture2D *paint = CCTextureCache::sharedTextureCache()->addImage(paintPath.c_str());
    if (paint) {
        m_pSpritePaint->initWithTexture(paint);

    }
    else
    {
        m_pSpritePaint->setVisible(false);
        CCString *str = CCString::createWithFormat(" pet %d paint not found ", m_pet->GetwIndex());
        CCMessageBox(str->getCString(), "Error");
    }
//    m_pSpritePaint->setAnchorPoint(ccp(0.5, 0));
//    m_pSpritePaint->setPosition(m_petPos);
    
    //六维属性
    if (!isfriend) {
        CRole* role = CGameSession::GetRole();
        str->initWithFormat("%d / %d", m_pet->GetbyLv() , role->GetwRoleLv());
        m_pLabelTTFPetLv->setString(str->getCString());
    }
    else{
        str->initWithFormat("%d", m_pet->GetbyLv());
        m_pLabelTTFPetLv->setString(str->getCString());
    }
    
    //HP
    str->initWithFormat("%d", m_pet->GetdwHpValue());
    m_pLabelTTFHp->setString(str->getCString());
    //Rev
    str->initWithFormat("%d", m_pet->GetdwRecoverValue());
    m_pLabelTTFRec->setString(str->getCString());
    //Atk
    if (isfriend) {
        str->initWithFormat("%d", m_pet->GetdwAttackValue());
    }
    else{
        if (cfgNor&& cfgNor->byHurtType == E_SPELL_HURT_SPE_ATK) {
            str->initWithFormat("%d", m_pet->GetdwSAttackValue());
        }
        else{
            str->initWithFormat("%d", m_pet->GetdwAttackValue());
        }
    }
    
    m_pLabelTTFAtt->setString(str->getCString());
    //Crit
    str->initWithFormat("%d%%", m_pet->GetdwCritRateValue() / 100);
    m_pLabelTTFCrit->setString(str->getCString());
    //CDef
    str->initWithFormat("%d", m_pet->GetdwDefenseValue());
    m_pLabelTTFCDef->setString(str->getCString());
    //SDef
    str->initWithFormat("%d", m_pet->GetdwSDefenseValue());
    m_pLabelTTFSDef->setString(str->getCString());
    
    //经验条
    if (!isfriend) {
        float curExp = m_pet->GetcurExp();
        float maxExp = curExp;
        ExpConfig::STC_EXP_CONFIG* expCfg = GET_CONFIG_STC(ExpConfig, m_pet->GetbyLv());
        if (expCfg) {
            maxExp = expCfg->dwPetExp;
        }
        m_pSpriteExp->setTextureRect(CCRectMake(0, 0, expBarW * curExp / maxExp, getHeight(m_pSpriteExp)));
        
        //徽章}
        uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
        SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
        if (cfg) {
            m_pLayerEmblem1->showIconOnly();
            m_pLayerEmblem1->setBtnEnable(false);
            
            m_pLayerEmblem2->showIconOnly();
            m_pLayerEmblem2->setBtnEnable(false);
            
            m_pLayerEmblem1->loadObjData(0, E_UNITE_TYPE_EMBLEM);
            m_pSpriteEmblemHas_1->setVisible(false);
            
            m_pLayerEmblem2->loadObjData(0, E_UNITE_TYPE_EMBLEM);
            m_pSpriteEmblemHas_2->setVisible(false);
        }
        else{
            CEmblem* emb = g_EmblemData->getEmblemByObjId(m_pet->GetdwEmblemId1());
            m_pLayerEmblem1->showIconOnly();
            m_pLayerEmblem1->setBtnEnable(false);
            if (emb) {
                m_pLayerEmblem1->loadIndexData(emb->getdwIndexId());
                m_pLayerEmblem1->showName();
                m_pLayerEmblem1->showLv(emb->getbyLv());
                m_pLayerEmblem1->showStarLv();
                m_pSpriteEmblemHas_1->setVisible(false);
            }
            else{
                m_pLayerEmblem1->loadObjData(0, E_UNITE_TYPE_EMBLEM);
                m_pSpriteEmblemHas_1->setVisible(g_EmblemData->hasFreeEmblem());
            }
            
            emb = g_EmblemData->getEmblemByObjId(m_pet->GetdwEmblemId2());
            m_pLayerEmblem2->showIconOnly();
            m_pLayerEmblem2->setBtnEnable(false);
            if (emb) {
                m_pLayerEmblem2->loadIndexData(emb->getdwIndexId());
                m_pLayerEmblem2->showName();
                m_pLayerEmblem2->showLv(emb->getbyLv());
                m_pLayerEmblem2->showStarLv();
                m_pSpriteEmblemHas_2->setVisible(false);
            }
            else{
                m_pLayerEmblem2->loadObjData(0, E_UNITE_TYPE_EMBLEM);
                m_pSpriteEmblemHas_2->setVisible(g_EmblemData->hasFreeEmblem());
            }
        }
        
        m_pLayerLeft->setVisible(false);
        m_pLayerRight->setVisible(false);
        //    //装备}
        m_pLayerEquip1->setEquipType(E_EQUIP_PART_WEAPON);
        m_pLayerEquip2->setEquipType(E_EQUIP_PART_CLOTHES);
        m_pLayerEquip3->setEquipType(E_EQUIP_PART_HELMET);
        m_pLayerEquip4->setEquipType(E_EQUIP_PART_NECKLACE);
        
        if (g_EquipData->getIsEquipShow() || isfriend) {
            
            uint32 arrEquipId[4];
            arrEquipId[0] = 0;
            arrEquipId[1] = 0;
            arrEquipId[2] = 0;
            arrEquipId[3] = 0;

            if (g_EquipData->getIsEquipShow()) {
                std::map<uint8, uint32>mapEquip = g_EquipTeamData->getEquipsBySite(CTeamCtrl::getSiteByPetId(m_pet->GetObjId()));
                std::map<uint8, uint32>::iterator ii = mapEquip.begin();
                for (; ii != mapEquip.end(); ii++) {
                    arrEquipId[ii->first] = ii->second;
                }
            }
            m_pLayerLeft->setVisible(true);
            m_pLayerRight->setVisible(true);
            m_pControlButtonYijian->setVisible(true);
            m_pControlButtonChange->setVisible(true);
            for (int i = 0; i < 4; i++) {
                arrEquip[i]->setEquipObjId(arrEquipId[i]);
                arrEquip[i]->checkHasCanUse(i+1);
            }
        }
        else{
            arrEquip[0]->getParent()->setVisible(false);
            m_pControlButtonYijian->setVisible(false);
            m_pControlButtonChange->setVisible(false);
        }
        
        
        //强化}
        if (CPetCtrl::Get()->IsCanIntensify(m_wObjectId)) {
            m_pControlButtonStrong->setEnabled(true);
        }
        else
        {
            m_pControlButtonStrong->setEnabled(false);
        }
        
        //进化}
        if (CPetCtrl::Get()->IsCanEvolve(m_wObjectId)) {
            m_pControlButtonUp->setEnabled(true);
        }
        else
        {
            m_pControlButtonUp->setEnabled(false);
        }
        
        if (CPetCtrl::Get()->checkPetCanEvo(m_wObjectId)) {
            m_pSpriteCanEvo->setVisible(true);
        }
        else{
            m_pSpriteCanEvo->setVisible(false);
        }
        
        //属性变化飘字}
        ShowFlyLayer();
    }
    else{
        m_pSpriteCanEvo->setVisible(false);
        m_pControlButtonStrong->setVisible(false);
        m_pControlButtonYijian->setVisible(false);
        m_pControlButtonUp->setVisible(false);
        m_pControlButtonChange->setVisible(false);
        m_pLayerBack->hideLock();
        
    }
}


void CcbPetShowLayer::setOpacity(GLubyte opacity)
{
    m_pSpritePaint->setOpacity(opacity);
}

void CcbPetShowLayer::RefeashLayer()
{
    m_pet = CPetCtrl::Get()->GetPetByObjId(m_wObjectId);
    loadPetData();
}

void CcbPetShowLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{

}
void CcbPetShowLayer::systemMessageCancelTapped(SystemMessage *systemMessage)
{
    
}

//一键装备}
void CcbPetShowLayer::putOnTheBestEquip()
{
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(m_wObjectId);

    if (!pet) {
        return;
    }
    uint8 site = CTeamCtrl::getSiteByPetId(m_wObjectId);
    if (!site) {
        return;
    }
    
    std::map<uint8, uint32>mapEquip = g_EquipTeamData->getEquipsBySite(site);
    uint32 arrEquipId[4];
    arrEquipId[0] = mapEquip[E_EQUIP_PART_WEAPON-1];
    arrEquipId[1] = mapEquip[E_EQUIP_PART_CLOTHES-1];
    arrEquipId[2] = mapEquip[E_EQUIP_PART_HELMET-1];
    arrEquipId[3] = mapEquip[E_EQUIP_PART_NECKLACE-1];
    int cnt = 4;
//    for (int i = 0; i < 4; i++) {
//        if (arrEquipId[i] > 0) {
//            continue;
//        }
//        cnt++;
//    }
    if (cnt == 0 && pet->GetdwEmblemId1() && pet->GetdwEmblemId2()) {
        
        FlyTextLayer::showTips(GET_STR(Str_no_equip_site));
        return;
    }
    
    std::vector<uint32> arrPos_1;
    std::vector<uint32> arrPos_2;
    std::vector<uint32> arrPos_3;
    std::vector<uint32> arrPos_4;

    vector<uint32> arrEquipKeyId = g_EquipData->GetVecShowEquipKeyID();
    
    arrPos_1.clear();
    arrPos_2.clear();
    arrPos_3.clear();
    arrPos_4.clear();

    for (int i = 0; i < arrEquipKeyId.size(); i++)
     {
        const CEquip *equip = g_PacketDataMgr->GetEquipInfoByKeyID(arrEquipKeyId[i]);
         
        if (!equip || g_EquipTeamData->checkEquipIsWear(equip->GetKeyID()))
        {
            continue;
        }
        switch (equip->GetConfigData().byPos) {
            case E_EQUIP_PART_WEAPON:
                arrPos_1.push_back(equip->GetKeyID());
                break;
            case E_EQUIP_PART_CLOTHES:
                arrPos_2.push_back(equip->GetKeyID());
                break;
            case E_EQUIP_PART_HELMET:
                arrPos_3.push_back(equip->GetKeyID());
                break;
            case E_EQUIP_PART_NECKLACE:
                arrPos_4.push_back(equip->GetKeyID());
                break;

            default:
                break;
        }
    }
    std::sort(arrPos_1.begin(), arrPos_1.end(), cmpEquip);
    std::sort(arrPos_2.begin(), arrPos_2.end(), cmpEquip);
    std::sort(arrPos_3.begin(), arrPos_3.end(), cmpEquip);
    std::sort(arrPos_4.begin(), arrPos_4.end(), cmpEquip);

    int nEquipCountOnce = 0;

    for (int i = 0; i < 4; i++)
    {
        if (!arrEquip[i]->getHasCanUse())
        {
            continue;
        }
        uint32 dwEquipKeyID = 0;
        switch (i+1) {
            case E_EQUIP_PART_WEAPON:
                if (arrPos_1.size() == 0)
                {
                    continue;
                }
                dwEquipKeyID = arrPos_1[0];
                m_pLayerEquip1->setEquipObjId(dwEquipKeyID);
                break;
            case E_EQUIP_PART_CLOTHES:
                if (arrPos_2.size() == 0)
                {
                    continue;
                }
                dwEquipKeyID = arrPos_2[0];
                m_pLayerEquip2->setEquipObjId(dwEquipKeyID);
                break;
            case E_EQUIP_PART_HELMET:
                if (arrPos_3.size() == 0)
                {
                    continue;
                }
                dwEquipKeyID = arrPos_3[0];
                m_pLayerEquip3->setEquipObjId(dwEquipKeyID);
                break;
            case E_EQUIP_PART_NECKLACE:
                if (arrPos_4.size() == 0)
                {
                    continue;
                }
                dwEquipKeyID = arrPos_4[0];
                m_pLayerEquip4->setEquipObjId(dwEquipKeyID);
                break;

            default:
                break;
        }

        if (dwEquipKeyID == 0)
        {
            continue;
        }
        nEquipCountOnce++;
        CGameSession::SendEquipToPet(dwEquipKeyID, site, i);
    }
    
    //徽章
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
//        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    std::vector<uint32> arrSpeEmblem;
    std::vector<uint32> arrNorEmblem;
    std::map<uint32, CEmblem*> mapAllEmblem = g_EmblemData->getAllEmblem();
    std::map<uint32, CEmblem*>::iterator itEm = mapAllEmblem.begin();
    for (; itEm != mapAllEmblem.end(); itEm++) {
        if (!itEm->second) {
            continue;
        }
        if (itEm->second->getdwPetObjId()) {
            continue;
        }
        if (g_EmblemData->checkExcPet(itEm->second->getdwIndexId(), m_wObjectId)) {
            arrSpeEmblem.push_back(itEm->first);
        }
        else{
            arrNorEmblem.push_back(itEm->first);
        }
    }
    
    std::sort(arrSpeEmblem.begin(), arrSpeEmblem.end(), cmpEmblem);
    std::sort(arrNorEmblem.begin(), arrNorEmblem.end(), cmpEmblem);
    for (int i = 0; i < arrNorEmblem.size(); i++) {
        uint32 id = arrNorEmblem[i];
        arrSpeEmblem.push_back(id);
    }
    
    cnt = 0;
    if (!pet->GetdwEmblemId1()) {
        cnt++;
    }
    if (!pet->GetdwEmblemId2()) {
        cnt++;
    }
    
    for (int i = 0; i < cnt; i++) {
        if (i >= arrSpeEmblem.size() ||
            arrSpeEmblem[i] == 0) {
            break;
        }
        CGameSession::SendEmblemWear(m_wObjectId, arrSpeEmblem[i]);
        nEquipCountOnce++;
    }

    CPetCtrl::Get()->SetEquipCountOnce(nEquipCountOnce);
    
    if (nEquipCountOnce == 0) {
        FlyTextLayer::showTips(GET_STR(Str_no_use_equip));
    }
}

bool CcbPetShowLayer::cmpEquip(uint32 equipKeyID1, uint32 equipKeyID2)
{
    uint32 qua1 = 0;
    uint32 value1 = 0;
    const CEquip* pEquip1 = g_PacketDataMgr->GetEquipInfoByKeyID(equipKeyID1);
    if (pEquip1)
    {
        qua1 = pEquip1->GetConfigData().byQuality * 10000 + pEquip1->GetLevel();
        value1 = pEquip1->GetCAtk() + pEquip1->GetSAtk() + pEquip1->GetRev() + pEquip1->GetHP() + pEquip1->GetSAtk()+
                pEquip1->GetSDef() + pEquip1->GetCrit() / 100;
    }
    
    uint32 qua2 = 0;
    uint32 value2 = 0;
    const CEquip* pEquip2 = g_PacketDataMgr->GetEquipInfoByKeyID(equipKeyID2);
    
    if (pEquip2)
    {
        qua2 = pEquip2->GetConfigData().byQuality * 10000 + pEquip2->GetLevel();
        value2 = pEquip2->GetCAtk() + pEquip2->GetSAtk() + pEquip2->GetRev() + pEquip2->GetHP() + pEquip2->GetSAtk()+
                pEquip2->GetSDef() + pEquip2->GetCrit() / 100;
    }
    
    if (qua1 == qua2) {
        return value1 > value2;
    }
    else{
        return qua1 > qua2;
    }
}

bool CcbPetShowLayer::cmpEmblem(uint32 emblemKeyID1, uint32 emblemKeyID2)
{
    uint32 value1 = 0;
    CEmblem* pEmb1 = g_EmblemData->getEmblemByObjId(emblemKeyID1);
    if (pEmb1)
    {
        value1 = pEmb1->getbyLv();
    }
    
    uint32 value2 = 0;
    CEmblem* pEmb2 = g_EmblemData->getEmblemByObjId(emblemKeyID2);
    if (pEmb2)
    {
        value2 = pEmb2->getbyLv();
    }
    
    return value1 > value2;
}

#pragma mark ShowFly

void CcbPetShowLayer::ShowFlyLayer()
{
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(m_wObjectId);
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
    if (atkAdd != 0) {
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
    
    int cnt = 1;
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

/** 其他人物信息 回包
 uint16	wErrorMsg				// 错误码}
 uint16	wIndex					// 宠物Index}
 uint8	byLv					// 宠物LV}
 uint8	byEvolveLv
 uint32	dwHpValue
 uint32	dwAttackValue
 uint32	dwDeffenceValue
 uint32	dwRecoverValue
 uint32	dwLuckValue
 uint8	bySize (六个装备位置　0-5)
 uint32	dwEquipIndex
 uint8		byEquipLv
 uint32	dwLeaderSpellId
 uint32	dwInitailSpellId
 uint8	byInitailSpellLv
 uint8	bySpellSize
 uint32 dwSpellId
 uint8  bySpellLv
 */
void CcbPetShowLayer::handleOtherRoleInfo(WorldPacket& packet)
{

    CPetCtrl::Get()->setIsFriendLook(true);
    
    uint16	wIndex;					// 宠物Index}
    uint8	byLv;					// 宠物LV}
    uint8	byEvolveLv;
    uint32	dwHpValue;
    uint32	dwAttackValue;
    uint32	dwDeffenceValue;
    uint32  dwSDefValue;
    uint32	dwRecoverValue;
    uint32  dwSpeedValue;
    uint32	dwLuckValue;
    
    uint8	bySize;// (六个装备位置　0-5)}
    uint32	dwEquipIndex;
    uint8	byEquipLv;
    uint32	dwLeaderSpellId;
    uint32	dwInitailSpellId;
    uint8	byInitailSpellLv;
    uint32  dwNorSkillId;
    
    
    packet >>	wIndex;					// 宠物Index}
    packet >>	byLv;					// 宠物LV}
    packet >>	byEvolveLv;
    packet >>	dwHpValue;
    packet >>	dwAttackValue;
    packet >>	dwDeffenceValue;
    packet >>   dwSDefValue;
    packet >>	dwRecoverValue;
    packet >>   dwSpeedValue;
    packet >>	dwLuckValue;
    
    
    m_pet = new CPet(0);
    m_pet->SetwIndex(wIndex);
    m_pet->SetbyLv(byLv);
    m_pet->SetbyEvolveLv(byEvolveLv);
    m_pet->SetdwHpValue(dwHpValue);
    m_pet->SetdwAttackValue(dwAttackValue);
    m_pet->SetdwDefenseValue(dwDeffenceValue);
    m_pet->SetdwSDefenseValue(dwSDefValue);
    m_pet->SetdwRecoverValue(dwRecoverValue);
    m_pet->SetdwCritRateValue(dwLuckValue);
    m_pet->SetdwSpeedValue(dwSpeedValue);
    
    m_pet->SetwEquipId1(0);
    m_pet->SetwEquipId2(0);
    m_pet->SetwEquipId3(0);
    m_pet->SetwEquipId4(0);

    
    std::vector<CEquip*> arrEquip;
    packet >>	bySize;// (六个装备位置　0-5)}
    for (int i = 0; i < bySize; i++) {
        packet >>	dwEquipIndex;
        packet >>	byEquipLv;
        CEquip* equip = new CEquip();
        equip->SetIndex(dwEquipIndex);
        equip->SetLevel(byEquipLv);
        arrEquip.push_back(equip);
    }
    
    packet >>	dwLeaderSpellId;
    packet >>	dwInitailSpellId;
    packet >>	byInitailSpellLv;
    packet >>   dwNorSkillId;
    m_pet->SetwLeaderSkillId(dwLeaderSpellId);
    m_pet->SetwInitialSkillId(dwInitailSpellId);
    m_pet->SetbyInitialSkillLv(byInitailSpellLv);
    m_pet->SetwNormaleAttId(dwNorSkillId);
    
//    packet >>	bySpellSize; //0-4
//    packet >>   dwSpellId;
//    packet >>   bySpellLv;
//    m_pet->SetwPassiveSkillId1(dwSpellId);
//    packet >>   dwSpellId;
//    m_pet->SetwPassiveSkillId2(dwSpellId);
//    packet >>   dwSpellId;
//    m_pet->SetwPassiveSkillId3(dwSpellId);
//    packet >>   dwSpellId;
//    m_pet->SetwPassiveSkillId4(dwSpellId);
//    packet >>   dwSpellId;
//    m_pet->SetwPassiveSkillId5(dwSpellId);
    
    
    m_pet->SetdwEmblemId1(0);
    m_pet->SetdwEmblemId2(0);
    uint32 dwEmblemIndex;
    uint8 byEmblemLv;
    std::vector<CEmblem*> arrEmblem;
//    packet >>	bySize;// (六个装备位置　0-5)}
    
    packet >>	dwEmblemIndex;
    packet >>	byEmblemLv;
    CEmblem* emb = new CEmblem(0);
    emb->setdwIndexId(dwEmblemIndex);
    emb->setbyLv(byEmblemLv);
    arrEmblem.push_back(emb);
    
    packet >>	dwEmblemIndex;
    packet >>	byEmblemLv;
    emb = new CEmblem(0);
    emb->setdwIndexId(dwEmblemIndex);
    emb->setbyLv(byEmblemLv);
    arrEmblem.push_back(emb);
    
//    for (int i = 0; i < bySize; i++) {
//        packet >>	dwEmblemIndex;
//        packet >>	byEmblemLv;
//        CEmblem* emb = new CEmblem(0);
//        emb->setdwIndexId(dwEmblemIndex);
//        emb->setbyLv(byEmblemLv);
//        arrEmblem.push_back(emb);
//        
//    }
    
    m_bIsChangePetEnable = false;
    isfriend = true;
    loadPetData();
    
    std::vector<CcbPetEquipIcon*> arrEquipIcon;
    arrEquipIcon.push_back(m_pLayerEquip1);
    arrEquipIcon.push_back(m_pLayerEquip2);
    arrEquipIcon.push_back(m_pLayerEquip3);
    arrEquipIcon.push_back(m_pLayerEquip4);
    for (int i = 0; i < arrEquipIcon.size(); i++) {
        
        CcbPetEquipIcon *icon = arrEquipIcon[i];
        icon->setEquipType(i+1);
        icon->setEquipObjId(0);
        CEquip* equip = arrEquip[i];
        if (i < arrEquip.size() && equip->GetIndex()) {
            icon->setIndex(equip->GetIndex());
            icon->setLv(equip->GetLevel());
        }
        icon->setEnable(false);
    }
    
    std::vector<CcbItemIconLayer*> arrEmblemIcon;
    arrEmblemIcon.push_back(m_pLayerEmblem1);
    arrEmblemIcon.push_back(m_pLayerEmblem2);
    
    m_pSpriteEmblemHas_1->setVisible(false);
    m_pSpriteEmblemHas_2->setVisible(false);
    m_pControlButtonEmblem_1->setVisible(false);
    m_pControlButtonEmblem_2->setVisible(false);
    
    for (int i = 0; i < arrEmblemIcon.size(); i++) {
        CcbItemIconLayer *icon = arrEmblemIcon[i];
        CEmblem* emb = arrEmblem[i];
        if (emb->getdwIndexId() == 0) {
            icon->setVisible(false);
            continue;
        }
        
        icon->loadIndexData(emb->getdwIndexId());
        icon->showIconOnly();
        icon->showName();
        icon->showLv(emb->getbyLv());
        icon->setBtnEnable(false);
    }
    
//    m_pLayerSkill1->setEnable(false);
//    m_pLayerSkill2->setEnable(false);

}


void CcbPetShowLayer::dwShareCntChanged(uint32 dwShareCnt)
{
    this->listenToBackFromNotification(NULL);
}

void CcbPetShowLayer::listenToBackFromNotification(cocos2d::CCObject *pObject)
{
    CRole* pRole = CGameSession::GetRole();
    if (!pRole || pRole->GetdwShareCnt() >= 3) {
        m_pNodeShareReward->setVisible(false);
        return;
    }
    
    ShareConfig::STC_SHARE_CONFIG* pShareConfig = GET_CONFIG_STC(ShareConfig, pRole->GetdwShareCnt() + 1);
    if (!pShareConfig) {
        m_pNodeShareReward->setVisible(false);
        return;
    }
    m_pNodeShareReward->setVisible(true);
    ((CCSprite *)m_pNodeShareReward->getChildByTag(0))->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetItemIconByIndex(pShareConfig->dwItemIndex).c_str()));
    ((CCLabelTTF*)m_pNodeShareReward->getChildByTag(1))->setString(CCString::createWithFormat("+%d",pShareConfig->dwItemCount)->getCString());
}

