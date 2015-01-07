#include "CcbPetIconCtrl.h"
//#include "CcbManager.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "PetCtrl.h"
#include "CcbPetShowLayer.h"
#include "CCScrollButton.h"
#include "BackCtrl.h"
#include "MainScene.h"
#include "Team.h"
#include "TeamCtrl.h"
#include "ResourcePic.h"
#include "CFuseDadaMgr.h"
#include "GuideData.h"
#include "EmblemDataMgr.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "PacketDataMgr.h"
#include "ChallengeCtrl.h"

CcbPetIconCtrl::~CcbPetIconCtrl()
{
	CC_SAFE_RELEASE_NULL(m_pSpritePetBg);
    CC_SAFE_RELEASE_NULL(m_pSpritePet);
	CC_SAFE_RELEASE_NULL(m_pSpritePetFrame);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
	CC_SAFE_RELEASE_NULL(m_pSpriteE);
	CC_SAFE_RELEASE_NULL(m_pNodeNumBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNum);
	CC_SAFE_RELEASE_NULL(m_pSpriteNumBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteTeam);
    CC_SAFE_RELEASE_NULL(m_pSpriteLocked);
    CC_SAFE_RELEASE_NULL(m_pSpriteAttribute);
    CC_SAFE_RELEASE_NULL(m_pSpriteStar);
    CC_SAFE_RELEASE_NULL(m_pNodeStar);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetIconCtrl( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetIconCtrl( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetIconCtrl", CcbPetIconCtrlLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_icon_ctrl.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetIconCtrl::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbPetIconCtrl::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbPetIconCtrl::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetIconCtrl::onExit()
{
	CCLayer::onExit();
}

void CcbPetIconCtrl::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetIconCtrl::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetBg", CCSprite*, this->m_pSpritePetBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet", CCSprite*, this->m_pSpritePet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetFrame", CCSprite*, this->m_pSpritePetFrame);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteE", CCSprite*, this->m_pSpriteE);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNumBg", CCNode*, this->m_pNodeNumBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNum", CCLabelTTF*, this->m_pLabelTTFNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNumBg", CCSprite*, this->m_pSpriteNumBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTeam", CCSprite*, this->m_pSpriteTeam);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLocked", CCSprite*, this->m_pSpriteLocked);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute", CCSprite*, this->m_pSpriteAttribute);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar", CCSprite*, this->m_pSpriteStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeStar", CCNode*, this->m_pNodeStar);
	return false;
}

bool CcbPetIconCtrl::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetIconCtrl::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetIconCtrl::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetIconCtrl::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
//	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSelect", CcbPetIconCtrl::onPressControlButtonSelect);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetIconCtrl::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    
    m_pSpriteE->setVisible(false);
    m_pNodeNumBg->setVisible(false);
    m_pSpriteTeam->setVisible(false);

    m_pSpriteLocked->setVisible(false);
    m_bCanTouch = true;
    
    CCSize size = m_pSpritePetFrame->getContentSize();
    size.width -= 2;//m_pSpritePet->getScaleX();
    size.height -= 2;//m_pSpritePet->getScaleY();
    m_pControlButtonSelect = CCScrollButton::createTransWithHightLight();//create(sSprite);

    m_pControlButtonSelect->setPreferredSize(size);
    m_pControlButtonSelect->setZoomOnTouchDown(false);
    m_pControlButtonSelect->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbPetIconCtrl::onPressControlButtonSelect), CCControlEventTouchUpInside);
    
    m_pControlButtonSelect->setPosition(ccp(getWidth(m_pSpritePetFrame) * 0.5, getHeight(m_pSpritePetFrame)*0.5));
    m_pControlButtonSelect->setAnchorPoint(ccp(0.5, 0.5));
    m_pControlButtonSelect->setClipRect(CCRectMake(0, 0, getWidth(m_pSpritePetFrame), getHeight(m_pSpritePetFrame)));

    m_pControlButtonSelect->setZOrder(1);
    m_pSpritePetFrame->getParent()->addChild(m_pControlButtonSelect);
    m_pSpritePetFrame->setZOrder(2);
    m_pSpriteAttribute->setZOrder(3);
    m_pNodeStar->setZOrder(3);
//    layerUnEnable
    layerUnEnable = CCLayerColor::create(ccc4(0, 0, 0, 50));
    layerUnEnable->setContentSize(m_pSpritePetFrame->getContentSize());
    layerUnEnable->setPosition(CCPointZero);
    layerUnEnable->setAnchorPoint(CCPointZero);
    layerUnEnable->setOpacity(150);
    layerUnEnable->setVisible(false);
    m_pSpritePetFrame->addChild(layerUnEnable);
    
    m_pet = NULL;
}



void CcbPetIconCtrl::onPressControlButtonSelect(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    if (!m_bCanTouch) {
        return;
    }
    if (layerUnEnable->isVisible()) {
        return;
    }
    CCLog(" touch pet Obj Id ：%d", getPetObjId());
    switch (CPetCtrl::Get()->GetPetBagType()) {
        case CPetCtrl::E_BAG_ENTER_TYPE_ALL:
            //跳转到详细界面}
            CPetCtrl::Get()->SetShowPetObjId(m_pet->GetObjId());
            CPetCtrl::Get()->SetNeedRefreshValue(true);
            BackCtrl::InsertNextScene(kPetShowScene, kNormalTrans);
            break;

        case CPetCtrl::E_BAG_ENTER_TYPE_SALE:
            //显示选号}
            if (m_pNodeNumBg && m_pNodeNumBg->isVisible()) {
                m_pNodeNumBg->setVisible(false);
                CPetCtrl::Get()->UnSelectedPet(m_pet->GetObjId());
            }
            else
            {
                CPetCtrl::Get()->AddSelectedPet(m_pet->GetObjId());
            }
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_PARTY_NORMAL:
            //跳回队伍界面}
            CTeamCtrl::SetCurTeamMamber(m_pet->GetObjId());
//            CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_TEAM);
//            BackCtrl::BacktoUpperScene();
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_PARTY_LEADER:
            //跳回队伍界面}
            CTeamCtrl::SetTeamLeader(m_pet->GetObjId());
//            CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_TEAM);
//            BackCtrl::BacktoUpperScene();
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_INTENSIFY_PRIMARY:
            //不能强化的宠物不可选中，跳回强化界面}
            CPetCtrl::Get()->SetIntensifyPet(m_pet->GetObjId());
            BackCtrl::InsertNextScene(kEnhanceScene);
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_INTENSIFY_SUB:
            //不能被吃的宠物不可选中，显示编号}
            //显示选号}
            if (m_pNodeNumBg && m_pNodeNumBg->isVisible()) {
                m_pNodeNumBg->setVisible(false);
                CPetCtrl::Get()->UnSelectedPet(m_pet->GetObjId());
            }
            else
            {
                CPetCtrl::Get()->AddSelectedPet(m_pet->GetObjId());
            }
            
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_EVOLVE:
            //不能进化的宠物不可选中，跳回进化界面}
            CPetCtrl::Get()->SetEvolvePet(m_pet->GetObjId());
            BackCtrl::InsertNextScene(kEvolveScene);
            break;
            
        case CPetCtrl::E_BAG_ENTER_TYPE_FUSE:
            //显示选号}
            if (m_pNodeNumBg && m_pNodeNumBg->isVisible()) {
                m_pNodeNumBg->setVisible(false);
                g_FuseDada->delSelected(m_pet->GetObjId());
            }
            else
            {
                g_FuseDada->addSelected(m_pet->GetObjId());
            }
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_EMBLEM:
            
            break;
            
        default:
            break;
    }
}

void CcbPetIconCtrl::setPet(CPet *pet)
{
    m_pet = pet;
}

void CcbPetIconCtrl::loadData()
{
    if (!m_pet || m_pet->GetwIndex() == 0) {
        return;
    }
    //    头像}
    m_pSpritePet->setTexture(CPetCtrl::Get()->GetPetHeadTexture(m_pet->GetwIndex()));
    //属性}
    CCSpriteFrame *fs = CPetCtrl::Get()->GetPetNaturePicSF(m_pet->GetwIndex());
    m_pSpriteAttribute->setDisplayFrame(fs);
    
    uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(m_pet->GetwIndex());
    //框}
    m_pSpritePetFrame->setVisible(true);
    m_pSpritePetFrame->setDisplayFrame(g_PacketDataMgr->getQualityFrameSF(quality));
    //背景}
    m_pSpritePetBg->setDisplayFrame(g_PacketDataMgr->getQualityBgSF(quality));
    
    if (!m_bCanTouch) {
        //等级}
        if (CPetCtrl::Get()->IsLvMax(m_pet->GetObjId())) {
            //            imgLvMax->setVisible(true);
            m_pLabelTTFLv->setString(CCString::createWithFormat("%s%s", SB_Lv, SB_Max)->getCString());
        }
        else
        {
            m_pLabelTTFLv->setString(CCString::createWithFormat("%s%d", SB_Lv, m_pet->GetbyLv())->getCString());
        }
        return;
    }
    //星级}
#if 0
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/star.plist");
    
    string framePath = CCString::createWithFormat("star_%d.png", m_pet->GetbyStarLv())->getCString();
    m_pSpriteStar->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framePath.c_str()));
#endif
    
    m_pNodeStar->removeAllChildren();
    CCSprite* pSpriteStar = NULL;
    float fWidth = 0.0f;
    for (int i = 0; i < m_pet->GetbyStarLv(); i++) {
        pSpriteStar = CCSprite::create(GET_PIC(Pic_Pet_Star_Level));
        m_pNodeStar->addChild(pSpriteStar);
        pSpriteStar->setAnchorPoint(CCPointZero);
        pSpriteStar->setPosition(ccp(fWidth, 0));
        
        float fSub = 4.0f;
        if (i == m_pet->GetbyStarLv() - 1) {
            fSub = 0.0f;
        }
        fWidth += pSpriteStar->getContentSize().width - fSub;
    }
    if (pSpriteStar) {
        m_pNodeStar->setContentSize(CCSizeMake(fWidth, pSpriteStar->getContentSize().height));
    }
    
    m_pSpriteE->setVisible(false);
    m_pNodeNumBg->setVisible(false);
    m_pSpriteTeam->stopAllActions();
    m_pSpriteTeam->setVisible(false);
    m_pLabelTTFLv->setVisible(true);
    m_pSpriteLocked->setVisible(false);
    //队伍}
    switch (CPetCtrl::Get()->IsInParty(m_pet->GetObjId())) {
        case -1:
            
            break;
        case 0:
            break;
            
        case 1:
            m_pSpriteTeam->setVisible(true);
            m_pSpriteTeam->runAction(CCRepeatForever::create(CCBlink::create(1, 1)));
            break;
        default:
            break;
    }
    //装备}
//    if (CPetCtrl::Get()->IsHasEquip(m_pet->GetObjId())) {
//    }
    
    //锁定}
    if (m_pet->GetbIsLock()) {
        m_pSpriteLocked->setVisible(true);
    }
    
    switch (CPetCtrl::Get()->GetSortType()) {
        case CPetCtrl::E_PET_SORT_TYPE_NATURE:
        case CPetCtrl::E_PET_SORT_TYPE_LV:
        case CPetCtrl::E_PET_SORT_TYPE_BIRTHDAY:
        case CPetCtrl::E_PET_SORT_TYPE_STAR:
            //等级}
            if (CPetCtrl::Get()->IsLvMax(m_pet->GetObjId())) {
                m_pLabelTTFLv->setString(CCString::createWithFormat("%s%s", SB_Lv, SB_Max)->getCString());
            }
            else
            {
                m_pLabelTTFLv->setString(CCString::createWithFormat("%s%d", SB_Lv, m_pet->GetbyLv())->getCString());
            }
            break;
        case CPetCtrl::E_PET_SORT_TYPE_ATTACK:
            m_pLabelTTFLv->setString(CCString::createWithFormat("%d", m_pet->GetdwAttackValue())->getCString());
            break;
        case CPetCtrl::E_PET_SORT_TYPE_DEFENSE:
            m_pLabelTTFLv->setString(CCString::createWithFormat("%d", m_pet->GetdwDefenseValue())->getCString());
            break;
        case CPetCtrl::E_PET_SORT_TYPE_SDEF:
            m_pLabelTTFLv->setString(CCString::createWithFormat("%d", m_pet->GetdwSDefenseValue())->getCString());
            break;
        case CPetCtrl::E_PET_SORT_TYPE_RECOVER:
            m_pLabelTTFLv->setString(CCString::createWithFormat("%d", m_pet->GetdwRecoverValue())->getCString());
            break;
        case CPetCtrl::E_PET_SORT_TYPE_HP:
            m_pLabelTTFLv->setString(CCString::createWithFormat("%d", m_pet->GetdwHpValue())->getCString());
            break;
        default:
            break;
    }
    
    
    //能否选择}
    layerUnEnable->setVisible(false);
    switch (CPetCtrl::Get()->GetPetBagType()) {
        case CPetCtrl::E_BAG_ENTER_TYPE_ALL:
            
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_SALE:
            if (!CPetCtrl::Get()->IsCanSale(m_pet->GetObjId())) {
                layerUnEnable->setVisible(true);
            }
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_PARTY_NORMAL:
            
        case CPetCtrl::E_BAG_ENTER_TYPE_PARTY_LEADER:
            
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_INTENSIFY_PRIMARY:
            if (!CPetCtrl::Get()->IsCanIntensify(m_pet->GetObjId())) {
                layerUnEnable->setVisible(true);
            }
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_INTENSIFY_SUB:
            if (CPetCtrl::Get()->IsProtected(m_pet->GetObjId())) {
                layerUnEnable->setVisible(true);
            }
            break;
        case CPetCtrl::E_BAG_ENTER_TYPE_EVOLVE:
            if (!CPetCtrl::Get()->IsCanEvolve(m_pet->GetObjId())) {
                layerUnEnable->setVisible(true);
            }
            break;
            
        default:
            break;
    }
    
    if (ChallengeCtrl::Get()->getChallengePetChoose()) {
        if (m_pet->GetbyStarLv() == 4 || (m_pet->GetbyType2() == E_PET_FORM_DRAGRON && m_pet->GetbyStarLv() > 4)) {
            layerUnEnable->setVisible(false);
        }
        else
        {
            layerUnEnable->setVisible(true);
        }
    }
    
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_SUB ||
        CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_SALE) {
      
        std::vector<uint32> arrSelectedPet = CPetCtrl::Get()->GetSelectedPet();
        if (arrSelectedPet.size() > 0) {
            bool unEnable = CPetCtrl::Get()->IsSeletedFull();
            
            int size = arrSelectedPet.size();
            for (int i = 0; i < size; i++) {
                uint32 objId = arrSelectedPet[i];
                if (objId != m_pet->GetObjId()) {
                    continue;
                }
                setNum(i+1);
                break;
            }
            setEnable(!unEnable);
        }
    }
    
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_FUSE) {
        std::vector<uint32> arrSelectedPet = g_FuseDada->getSelected();
        if (arrSelectedPet.size() > 0) {
            bool unEnable = g_FuseDada->isSelectedFull();
            
            int size = arrSelectedPet.size();
            for (int i = 0; i < size; i++) {
                uint32 objId = arrSelectedPet[i];
                if (objId != m_pet->GetObjId()) {
                    continue;
                }
                setNum(i+1);
                break;
            }
            setEnable(!unEnable);
        }
    }
}

void CcbPetIconCtrl::setNum(uint8 byNum)
{
    if (byNum == 0) {
        m_pNodeNumBg->setVisible(false);
        return;
    }
    CCString *str = CCString::createWithFormat("%d", byNum);
    m_pLabelTTFNum->setString(str->getCString());
    m_pNodeNumBg->setVisible(true);
}
void CcbPetIconCtrl::setEnable(bool isEnable)
{
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_SALE
        && !CPetCtrl::Get()->IsCanSale(getPetObjId())) {
        return;
    }
    
    //有编号显示的不置灰}
    if (m_pNodeNumBg && m_pNodeNumBg->isVisible()) {
        layerUnEnable->setVisible(false);
        return;
    }
    layerUnEnable->setVisible(!isEnable);
}
void CcbPetIconCtrl::setTouchEnable(bool isTouch)
{
    if (m_bCanTouch != isTouch) {
        m_bCanTouch = isTouch;
        loadData();
    }
}
void CcbPetIconCtrl::setClipRect(CCRect rect)
{
    m_pControlButtonSelect->setClipRect(rect);
}



