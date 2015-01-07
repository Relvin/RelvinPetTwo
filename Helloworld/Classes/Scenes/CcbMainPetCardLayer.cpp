#include "CcbMainPetCardLayer.h"
//#include "CcbManager.h"
#include "Pet.h"
#include "ConfigGet.h"
#include "PetCtrl.h"
#include "BackCtrl.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "FlyTextLayer.h"
#include "ResourceStringClient.h"
#include "GameSession.h"
#include "Role.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "EquipDataMgr.h"
#include "PacketDataMgr.h"
#include "EmblemDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbMainPetCardLayer::~CcbMainPetCardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpritePet);
	CC_SAFE_RELEASE_NULL(m_pControlButtonPetcard);
	CC_SAFE_RELEASE_NULL(m_pSpriteLeader);
	CC_SAFE_RELEASE_NULL(m_pSpriteNature);
	CC_SAFE_RELEASE_NULL(m_pSpriteLvstar);
	CC_SAFE_RELEASE_NULL(m_pSpriteLock);
    CC_SAFE_RELEASE_NULL(m_pSpriteHasEquip);
	CC_SAFE_RELEASE_NULL(m_pSpriteHasAllEquip);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
    CC_SAFE_RELEASE_NULL(m_pSpriteNormal);
    CC_SAFE_RELEASE_NULL(m_pSpritePlus);
    CC_SAFE_RELEASE_NULL(m_pSpriteCanEvo);
    CC_SAFE_RELEASE_NULL(m_pSpriteLvStar);
    CC_SAFE_RELEASE_NULL(m_pSpritePetType);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbMainPetCardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbMainPetCardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbMainPetCardLayer", CcbMainPetCardLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/main_petcard.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbMainPetCardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbMainPetCardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbMainPetCardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbMainPetCardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbMainPetCardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbMainPetCardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet", CCSprite*, this->m_pSpritePet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPetcard", CCControlButton*, this->m_pControlButtonPetcard);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLeader", CCSprite*, this->m_pSpriteLeader);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNature", CCSprite*, this->m_pSpriteNature);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLvstar", CCSprite*, this->m_pSpriteLvstar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLock", CCSprite*, this->m_pSpriteLock);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteHasEquip", CCSprite*, this->m_pSpriteHasEquip);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteHasAllEquip", CCSprite*, this->m_pSpriteHasAllEquip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNormal", CCSprite*, this->m_pSpriteNormal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePlus", CCSprite*, this->m_pSpritePlus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCanEvo", CCSprite*, this->m_pSpriteCanEvo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLvStar", CCSprite*, this->m_pSpriteLvStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetType", CCSprite*, this->m_pSpritePetType);

	return false;
}

bool CcbMainPetCardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbMainPetCardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbMainPetCardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbMainPetCardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonPetcard", CcbMainPetCardLayer::onPressControlButtonPetcard);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbMainPetCardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_dwPetObjId = 0;
    m_bySite = 0;
    m_TouchFlag = false;
    m_isLock = false;
    m_pSpriteLock->setVisible(false);
    m_pSpriteLeader->setVisible(false);
    m_pSpriteHasAllEquip->setVisible(false);
    m_pSpriteHasEquip->setVisible(false);
    m_pSpritePlus->setVisible(false);
    m_pSpriteCanEvo->setVisible(false);
}



void CcbMainPetCardLayer::onPressControlButtonPetcard(CCObject* pSender, CCControlEvent event)
{
    if (m_TouchFlag) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
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
    
    CTeamCtrl::SetSelectedMemberSite(m_bySite);
    if (m_dwPetObjId) {
        g_EquipData->setIsEquipShow(true);
        CPetCtrl::Get()->SetShowPetObjId(m_dwPetObjId);
        CPetCtrl::Get()->SetNeedRefreshValue(true);
        BackCtrl::InsertNextScene(kPetShowScene, kNormalTrans);
        m_TouchFlag = true;
        return;
    }
    else
    {
        CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_PARTY_NORMAL);
        BackCtrl::InsertNextScene(kPetBagScene, kNormalTrans);
    }
}

void CcbMainPetCardLayer::setPetObjIdAndSite(uint32 dwPetObjId, uint8 bySite)
{
    m_dwPetObjId = dwPetObjId;
    m_bySite = bySite;
    if (m_dwPetObjId == 0) {
        m_pSpriteNature->getParent()->setVisible(false);
        m_pSpritePet->setVisible(false);
        m_pSpritePlus->setVisible(true);
        return;
    }
    m_pSpriteNature->getParent()->setVisible(true);
    m_pSpritePet->setVisible(true);
    
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(m_dwPetObjId);
    //原画}
    m_pSpritePet->setTexture(CPetCtrl::Get()->GetPetBattleHeadTexture(pet->GetwIndex()));
    //属性}
    m_pSpriteNature->setDisplayFrame(CPetCtrl::Get()->GetPetNaturePicSF(pet->GetwIndex()));
    //等级}
    CCString* str = CCString::createWithFormat("%s%d", SB_Lv, pet->GetbyLv());
    m_pLabelTTFLv->setString(str->getCString());
    //框
    m_pSpriteNormal->setDisplayFrame(g_PacketDataMgr->getMainFrame(pet->GetwIndex()));
    //星级}
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
    
    
    //进化 / 装备
    if (CPetCtrl::Get()->checkPetCanEvo(m_dwPetObjId)
        || g_PacketDataMgr->checkHasCanChangeEquip(m_dwPetObjId)
        || ((!pet->GetdwEmblemId1() || !pet->GetdwEmblemId2()) && g_EmblemData->hasFreeEmblem())) {
        m_pSpriteCanEvo->setVisible(true);
    }
    //类型}
    m_pSpritePetType->setDisplayFrame(CPetCtrl::Get()->GetPetTypeSF(pet->GetwIndex()));
//    //装备}
//    if (g_EquipTeamData->getEquipIdBySiteAPart(bySite, E_EQUIP_PART_WEAPON-1) &&
//        g_EquipTeamData->getEquipIdBySiteAPart(bySite, E_EQUIP_PART_CLOTHES-1) &&
//        g_EquipTeamData->getEquipIdBySiteAPart(bySite, E_EQUIP_PART_HELMET-1) &&
//        g_EquipTeamData->getEquipIdBySiteAPart(bySite, E_EQUIP_PART_NECKLACE-1)) {
//        m_pSpriteHasAllEquip->setVisible(true);
//        m_pSpriteHasEquip->setVisible(false);
//    }
//    else{
//        m_pSpriteHasAllEquip->setVisible(false);
//        m_pSpriteHasEquip->setVisible(true);
//    }
}

void CcbMainPetCardLayer::setIsLeader(bool isLeader)
{
    m_pSpriteLeader->setVisible(isLeader);
}

void CcbMainPetCardLayer::setIsLock(bool isLock)
{
    m_isLock = isLock;
    m_pSpriteLock->setVisible(m_isLock);
    
    m_pSpritePlus->setVisible(!m_isLock);
}

void CcbMainPetCardLayer::hideAll()
{
    m_pSpriteLock->setVisible(false);
    m_pSpritePet->setVisible(false);
    m_pSpriteLeader->getParent()->setVisible(false);
    m_pSpritePlus->setVisible(false);
}
