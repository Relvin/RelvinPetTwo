#include "CcbTeamMemberLayer.h"
//#include "CcbManager.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "FlccMovieClip.h"
#include "FlccMovieAction.h"
#include "TeamCtrl.h"
#include "BackCtrl.h"
#include "UISupport.h"
//#include "SequencePet.h"
//#include "SequenceAction.h"
#include "SystemMessage.h"
#include "CCScrollButton.h"
#include "ResourceStringClient.h"
#include "FlyTextLayer.h"
#include "Role.h"
#include "GameSession.h"
#include "EquipDataMgr.h"
#include "PacketDataMgr.h"
#include "ChallengeCtrl.h"


CcbTeamMemberLayer::~CcbTeamMemberLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpritePet);
	CC_SAFE_RELEASE_NULL(m_pSpriteLvStar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFightValue);
	CC_SAFE_RELEASE_NULL(m_pLayerValue);
	CC_SAFE_RELEASE_NULL(m_pSpritePetType);
	CC_SAFE_RELEASE_NULL(m_pSpriteAttribute);
	CC_SAFE_RELEASE_NULL(m_pSpriteLeaderMark);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
	CC_SAFE_RELEASE_NULL(m_pLayerNormal);
	CC_SAFE_RELEASE_NULL(m_pControlButtonPetcard);
	CC_SAFE_RELEASE_NULL(m_pSpriteLock);
    CC_SAFE_RELEASE_NULL(m_pSpriteNormal);
    CC_SAFE_RELEASE_NULL(m_pSpritePlus);
    CC_SAFE_RELEASE_NULL(m_pNodeTip);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTeamMemberLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTeamMemberLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTeamMemberLayer", CcbTeamMemberLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/teamcircleset.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbTeamMemberLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_wPetObjId = 0;
    m_bySite = 0;
    m_isTouchEnable = true;
	return true;
}

void CcbTeamMemberLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_wPetObjId = 0;
}

void CcbTeamMemberLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    runAction(
              CCSequence::create(
                                 CCDelayTime::create(0.2f),
                                 CCCallFunc::create(this, callfunc_selector(CcbTeamMemberLayer::restoreTouch)),
                                 NULL
                                 )
              );
}

void CcbTeamMemberLayer::restoreTouch() {
    m_bCanTouchBtn = true;
}

void CcbTeamMemberLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTeamMemberLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTeamMemberLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet", CCSprite*, this->m_pSpritePet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFightValue", CCLabelTTF*, this->m_pLabelTTFFightValue);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerValue", CCLayer*, this->m_pLayerValue);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetType", CCSprite*, this->m_pSpritePetType);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute", CCSprite*, this->m_pSpriteAttribute);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLeaderMark", CCSprite*, this->m_pSpriteLeaderMark);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerNormal", CCLayer*, this->m_pLayerNormal);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPetcard", CCScrollButton*, this->m_pControlButtonPetcard);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLock", CCSprite*, this->m_pSpriteLock);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLvStar", CCSprite*, this->m_pSpriteLvStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNormal", CCSprite*, this->m_pSpriteNormal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePlus", CCSprite*, this->m_pSpritePlus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTip",CCNode*, this->m_pNodeTip);
	return false;
}

bool CcbTeamMemberLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTeamMemberLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTeamMemberLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTeamMemberLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonPetcard", CcbTeamMemberLayer::onPressControlButtonPetcard);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTeamMemberLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pSpriteLeaderMark->setVisible(false);
    m_pControlButtonPetcard->setVisible(false);
    m_pSpriteLock->setVisible(false);
    m_isLock = false;
    m_pControlButtonPetcard->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pSpritePlus->setVisible(false);
}


void CcbTeamMemberLayer::onPressControlButtonPetcard(CCObject* pSender, CCControlEvent event)
{
    if (m_isLock) {
        CRole* role = CGameSession::GetRole();
        uint8 lv = 2;
        if (role->GetwRoleLv() < 2) {
            lv = 2;
        }
        else if (role->GetwRoleLv() < 3)
        {
            lv = 3;
        }
        else if (role->GetwRoleLv() < 10)
        {
            lv = 10;
        }
        else if (role->GetwRoleLv() < 18)
        {
            lv = 18;
        }
        else if (role->GetwRoleLv() < 22)
        {
            lv = 22;
        }
        FlyTextLayer::showTips(CCString::createWithFormat(GET_STR(Str_team_no_lv), lv)->getCString());
        return;
    }
    onSetMember();
}

void CcbTeamMemberLayer::onSetMember()
{
    if (!m_bCanTouchBtn) {
        return;
    }
    if (!m_isTouchEnable) {
        return;
    }

    CTeamCtrl::SetSelectedMemberSite(m_bySite);
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(m_wPetObjId);
    if (pet && m_pNodeTip->isVisible() == false) {
        g_EquipData->setIsEquipShow(true);
        BackCtrl::InsertNextScene(kPetShowScene, kNormalTrans);
    }
    else{
        CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_PARTY_NORMAL);
        BackCtrl::InsertNextScene(kPetBagScene);
    }
}

void CcbTeamMemberLayer::setPetObjIdAndSite(uint16 wPetObjId, uint8 bySite)
{
    m_bySite = bySite;
    m_wPetObjId = wPetObjId;
    loadData();
}

void CcbTeamMemberLayer::loadData()
{
    setIsLeader(false);
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(m_wPetObjId);
    if (!pet) {
        m_wPetObjId = 0;
        m_pLayerNormal->setVisible(false);
        m_pControlButtonPetcard->setVisible(true);
        m_pSpritePlus->setVisible(true);
        return;
    }
    m_pLayerNormal->setVisible(true);
    m_pControlButtonPetcard->setVisible(m_isButtonTouchEnable);
    //icon
    m_pSpritePet->setTexture(CPetCtrl::Get()->GetPetBattleHeadTexture(pet->GetwIndex()));
    //属性球}
    m_pSpriteAttribute->setDisplayFrame(CPetCtrl::Get()->GetPetNaturePicSF(pet->GetwIndex()));
    //框
    m_pSpriteNormal->setDisplayFrame(g_PacketDataMgr->getTeamFrame(pet->GetwIndex()));
    
    //类型}
    m_pSpritePetType->setDisplayFrame(CPetCtrl::Get()->GetPetTypeSF(pet->GetwIndex()));
    //基础数据}
    CCString *str = CCString::create("");
    
    str->initWithFormat("%s%d", SB_Lv, pet->GetbyLv());
    m_pLabelTTFLv->setString(str->getCString());
    m_pLabelTTFLv->setVisible(true);
    
    str->initWithFormat("%d", pet->GetdwFightValue());
    m_pLabelTTFFightValue->setString(str->getCString());
    
    //星级
    m_pSpriteLvStar->setScale(1.0);
    m_pSpriteLvStar->removeAllChildren();
    m_pSpriteLvStar->setContentSize(CCSizeMake(m_pSpriteLvStar->getTexture()->getContentSize().width, getHeight(m_pSpriteLvStar)));
    for (int i = 1; i < pet->GetbyStarLv(); i++) {
        CCSprite *star = CCSprite::createWithTexture(m_pSpriteLvStar->getTexture());// ("ccbresources/12monthdate/pet/pic_lvstar.png");
        m_pSpriteLvStar->setContentSize(star->getContentSize());
        star->setAnchorPoint(ccp(0, 0));
        star->setPosition(ccp(i*getWidth(star)*0.75, 0));
        m_pSpriteLvStar->addChild(star);
    }
    m_pSpriteLvStar->setContentSize(CCSizeMake((getWidth(m_pSpriteLvStar)*0.75)*(pet->GetbyStarLv()-1)+ getWidth(m_pSpriteLvStar)*0.75, getHeight(m_pSpriteLvStar)));
    m_pSpriteLvStar->setScale(0.75);
    setIsLock(false);
    
    if (ChallengeCtrl::Get()->getChallengePetChoose()) {
        if (pet->GetbyStarLv() == 4 || ( pet->GetbyType2() == E_PET_FORM_DRAGRON && pet->GetbyStarLv() > 4)) {
            
        }
        else
        {
            m_pNodeTip->setVisible(true);
        }
    }
    
}

void CcbTeamMemberLayer::ShowBaseValue(bool bIsShow)
{
    if (m_wPetObjId) {
        m_pLayerValue->setVisible(bIsShow);
    }
    else
    {
        m_pLayerValue->setVisible(false);
    }
}

void CcbTeamMemberLayer::setIsLeader(bool bIsLeader)
{
    m_pSpriteLeaderMark->setVisible(bIsLeader);
//    m_pSpriteLeaderMark->setZOrder(3);
}

uint16 CcbTeamMemberLayer::getPetObjId()
{
    return m_wPetObjId;
}

 void CcbTeamMemberLayer::setIsLock(bool lock)
{
    m_isLock = lock;
    m_pSpriteLock->setVisible(m_isLock);
    if (m_isLock) {
        m_pSpritePlus->setVisible(false);
    }
}



