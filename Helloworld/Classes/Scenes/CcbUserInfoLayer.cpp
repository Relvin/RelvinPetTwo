#include "CcbUserInfoLayer.h"
#include "Role.h"
#include "GameSession.h"
#include "UISupport.h"
#include "PetCtrl.h"
#include "Team.h"
#include "TeamCtrl.h"
#include "Pet.h"
#include "Instruments.h"
#include "CcbPetIcon.h"
#include "ItemDataMgr.h"
#include "EnumDefines.h"
#include "PacketDataMgr.h"
#include "ResourceStringClient.h"
#include "GlobalData.h"
#include "MusicCtrl.h"
#include "BackCtrl.h"
#include "UserInfoDataMgr.h"
#include "SystemNoticeDataMgr.h"
#include "CcbManager.h"
#include "PetLoadingLayer.h"

#if (defined VERSION_I4) || (defined VERSION_D9)||(defined VERSION_PP)||(defined VERSION_91)
#include "Account.h"
#endif



USING_NS_CC;
USING_NS_CC_EXT;

CcbUserInfoLayer::~CcbUserInfoLayer()
{
    CGameSession::GetRole()->Detach(this);
    CGameSession::Detach(this);
    CC_SAFE_RELEASE_NULL(m_pLayerHeadIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteEnergy);
	CC_SAFE_RELEASE_NULL(m_pSpriteExp);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRecTime);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRecAll);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPetCnt);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCoin);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDollar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRonheStone);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFExpDes);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEnergyDes);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFID);
    CC_SAFE_RELEASE_NULL(m_pControlButtonOk);
    
    CC_SAFE_RELEASE_NULL(m_pControlButtonUserCenter);
    CC_SAFE_RELEASE_NULL(m_pControlButtonAnnounce);
    CC_SAFE_RELEASE_NULL(m_pControlButtonMusic);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEffect);
    CC_SAFE_RELEASE_NULL(m_pControlButtonExit);
    CC_SAFE_RELEASE_NULL(m_pLabelEffect);
    CC_SAFE_RELEASE_NULL(m_pLabelMusic);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFVip);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFUserLv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Alliance);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFontTitle);
    CC_SAFE_RELEASE_NULL(m_pControlButtonGoexchange);
    CC_SAFE_RELEASE_NULL(m_pControlButtonGoVip);
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 CCNode* LoadCcbUserInfoLayer( CCObject* owner );
 
 //CcbManager.cpp
 CCNode* CcbManager::LoadCcbUserInfoLayer( CCObject* owner ) {
 CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
 pLoaderLib->registerCCNodeLoader( "CcbUserInfoLayer", CcbUserInfoLayerLoader::loader() );
 
 
 CCBReader* pCCBReader = new CCBReader(pLoaderLib);
 CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/user_info.ccbi", owner);
 pCCBReader->release();
 
 return pNode;
 }
 */


bool CcbUserInfoLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CGameSession::Attach(this);
    CGameSession::GetRole()->Attach(this);
    setTouchEnabled(true);
	return true;
}

void CcbUserInfoLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::SendUpdateEnergyRecTime();
}

void CcbUserInfoLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    m_pLayerHeadIcon->setPetId(m_wLeaderIndexId);
    m_pLayerHeadIcon->loadData();
    m_pLayerHeadIcon->setBtnEnable(false);
}

void CcbUserInfoLayer::onExit()
{
	CCLayer::onExit();
}

void CcbUserInfoLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

void CcbUserInfoLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*2+2, true);
}

bool CcbUserInfoLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

// Inhert MemberVariableAssigner
bool CcbUserInfoLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHeadIcon", CcbPetIcon*, this->m_pLayerHeadIcon);
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEnergy", CCSprite*, this->m_pSpriteEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteExp", CCSprite*, this->m_pSpriteExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRecTime", CCLabelTTF*, this->m_pLabelTTFRecTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRecAll", CCLabelTTF*, this->m_pLabelTTFRecAll);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetCnt", CCLabelTTF*, this->m_pLabelTTFPetCnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoin", CCLabelTTF*, this->m_pLabelTTFCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDollar", CCLabelTTF*, this->m_pLabelTTFDollar);
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRonheStone", CCLabelTTF*, this->m_pLabelTTFRonheStone);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFExpDes", CCLabelTTF*, this->m_pLabelTTFExpDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnergyDes", CCLabelTTF*, this->m_pLabelTTFEnergyDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFID", CCLabelTTF*, this->m_pLabelTTFID);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOk", CCControlButton*, this->m_pControlButtonOk);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonUserCenter", CCControlButton*, this->m_pControlButtonUserCenter);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAnnounce", CCControlButton*, this->m_pControlButtonAnnounce);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMusic", CCControlButton*, this->m_pControlButtonMusic);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEffect", CCControlButton*, this->m_pControlButtonEffect);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExit", CCControlButton*, this->m_pControlButtonExit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelEffect", CCLabelTTF*, this->m_pLabelEffect);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelMusic", CCLabelTTF*, this->m_pLabelMusic);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFVip", CCLabelTTF*, this->m_pLabelTTFVip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFUserLv", CCLabelTTF*, this->m_pLabelTTFUserLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Alliance", CCLabelTTF*, this->m_pLabelTTF_Alliance);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFontTitle", CCLabelTTF*, this->m_pLabelTTFontTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGoexchange", CCControlButton*, this->m_pControlButtonGoexchange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGoVip", CCControlButton*, this->m_pControlButtonGoVip);
    
	return false;
}

bool CcbUserInfoLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbUserInfoLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler CcbUserInfoLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_CCControlHandler CcbUserInfoLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbUserInfoLayer::onPressControlButtonClose);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSet", CcbUserInfoLayer::onPressControlButtonSet);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFriend", CcbUserInfoLayer::onPressControlButtonFriend);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExit", CcbUserInfoLayer::onPressControlButtonExit);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAnnounce", CcbUserInfoLayer::onPressControlButtonAnnounce);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMusicCallBack", CcbUserInfoLayer::onPressControlButtonMusicCallBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEffectCallBack", CcbUserInfoLayer::onPressControlButtonEffectCallBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUserCenter", CcbUserInfoLayer::onPressControlButtonUserCenter);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExchange", CcbUserInfoLayer::onPressControlButtonExchange);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGoVip", CcbUserInfoLayer::onPressControlButtonGoVip);
	return NULL;
}

#define SET_ENERGY( lblType )    \
{   \
snprintf(strBuf64, BUFFER_SIZE_64, "%d/%d", m_dwCurEnergy, m_dwEnergyMax);    \
lblType->setString(strBuf64);  \
float _scale = ((float)m_dwCurEnergy / m_dwEnergyMax) > 1.0f ? 1.0f : ((float)m_dwCurEnergy / m_dwEnergyMax);   \
m_pSpriteEnergy->setTextureRect(CCRectMake(0, 0, _scale * m_fEnergyBarWidth, getHeight(m_pSpriteEnergy))); \
}   \

#define SET_EXP( lblType, valueType )   \
{   \
snprintf(strBuf64, BUFFER_SIZE_64, "%d/%d", valueType, m_dwExpMax); \
lblType->setString(strBuf64);  \
float _scale = ((float)m_dwCurExp / m_dwExpMax) > 1.0f ? 1.0f : ((float)m_dwCurExp / m_dwExpMax); \
m_pSpriteExp->setTextureRect(CCRectMake(0, 0, _scale * m_fExpBarWidth, getHeight(m_pSpriteExp)));    \
}   \

#define SET_MAX_ENERGY    \
{   \
m_pLabelTTFRecTime->setString(GET_STR(Str_energy_max)); \
m_pLabelTTFRecAll->setString(GET_STR(Str_energy_max));  \
m_dwRecTime = 0;    \
m_dwRecAllTime = 0; \
}   \

// Inhert CCNodeLoaderListener
void CcbUserInfoLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    touchFlag = false;
    m_pLabelTTFExpDes->noStroke();
    m_pLabelTTFEnergyDes->noStroke();
    
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority * 2 + 1);
    m_pControlButtonOk->setTouchPriority(kCCMenuHandlerPriority * 2 + 1);
    
    m_pControlButtonUserCenter->setTouchPriority(kCCMenuHandlerPriority * 2 + 1);
    m_pControlButtonAnnounce->setTouchPriority(kCCMenuHandlerPriority * 2 + 1);
    m_pControlButtonMusic->setTouchPriority(kCCMenuHandlerPriority * 2 + 1);
    m_pControlButtonEffect->setTouchPriority(kCCMenuHandlerPriority * 2 + 1);
    m_pControlButtonExit->setTouchPriority(kCCMenuHandlerPriority * 2 + 1);
    m_pControlButtonGoexchange->setTouchPriority(kCCMenuHandlerPriority * 2 + 1);
    m_pControlButtonGoVip->setTouchPriority(kCCMenuHandlerPriority * 2 + 1);
    
    if (GlobalData::shared()->getShareSwitch()) {
        m_pControlButtonGoexchange->setVisible(false);
    }
    if (GlobalData::shared()->getVipSwitch())
    {
        m_pLabelTTFVip->getParent()->setVisible(false);
    }
    
    CRole* pRole = CGameSession::GetRole();
    
    m_pLabelTTFVip->setString(CCString::createWithFormat("%d",pRole->GetbyVipLv())->getCString());
    
    CCString* pFormat = NULL;
    pFormat = CCString::createWithFormat("%d", pRole->GetdwDollar());
    m_pLabelTTFDollar->setString(pFormat->getCString());
    
    pFormat = CCString::createWithFormat("%d", pRole->GetdwCoin());
    m_pLabelTTFCoin->setString(pFormat->getCString());
    
    //融合石}
    pFormat = CCString::createWithFormat("%d", pRole->GetdwResFarmNum());
    m_pLabelTTFRonheStone->setString(pFormat->getCString());
    
    m_dwEnergyMax = pRole->GetdwEnergyMax();
    m_dwCurEnergy = pRole->GetdwEnergy();
    m_dwExpMax = pRole->GetdwRoleMaxExp();
    m_dwCurExp = pRole->GetdwRoleExp();
    
    pFormat->initWithFormat("%u", pRole->GetdwAccountId());
    m_pLabelTTFID->setString(pFormat->getCString());
    
//    m_fEnergyBarWidth = getWidth(m_pSpriteEnergy);
//    m_fExpBarWidth = getWidth(m_pSpriteExp);
    
    snprintf(strBuf64, BUFFER_SIZE_64, "%d/%d", m_dwCurEnergy, m_dwEnergyMax);
    m_pLabelTTFEnergyDes->setString(strBuf64);
//    SET_ENERGY(m_pLabelTTFEnergyDes);
    
    snprintf(strBuf64, BUFFER_SIZE_64, "%d/%d", m_dwCurExp, m_dwExpMax);
    m_pLabelTTFExpDes->setString(strBuf64);
//    SET_EXP(m_pLabelTTFExpDes, m_dwCurExp);
    
    m_pLabelTTFUserLv->setString(CCString::createWithFormat("%d",pRole->GetwRoleLv())->getCString());
    
    uint16 wIndex = pRole->GetbyArenaGroup();
    if (wIndex == 0) {
        wIndex = 12;
    }
    RankRewardConfig::STC_RANKREWARD_CONFIG* pConfig = GET_CONFIG_STC(RankRewardConfig, wIndex);
    if (pConfig)
    {
        this->m_pLabelTTFontTitle->setString(pConfig->strGroupName.c_str());

    }
//    int nTeamMax = pRole->GetdwBattleBagCnt();
    int nTeamMemberCnt = 0;
    CTeam* pTeam = CTeamCtrl::GetCurTeam();
    if (pTeam) {
        for (int i = 1; i < 7; i++) {
            uint32 dwPetObjId = pTeam->getarrPetObId()[i];
            CPet* pPet = CPetCtrl::Get()->GetPetByObjId(dwPetObjId);
            if (pPet) {
                nTeamMemberCnt++;
                if (i == pTeam->getbyLeaderSite()) {
                    m_wLeaderIndexId = pPet->GetwIndex();
                }
            }
        }
//        pFormat = CCString::createWithFormat("%d/%d", nTeamMemberCnt, nTeamMax);
//        m_pLabelTTFPetCnt->setString(pFormat->getCString());
    }
    
    pFormat = CCString::createWithFormat("%s", pRole->GetstrUserName().c_str());
    m_pLabelTTFName->setString(pFormat->getCString());
    m_pLabelTTFName->noStroke();
    
    m_dwRecTime = UserInfoDataMgr::Get()->localRecTime();
    m_nNeedEnergy = m_dwEnergyMax - m_dwCurEnergy;
    
    if (m_dwRecTime > 0 && m_nNeedEnergy > 0) {
        m_dwRecAllTime = m_dwRecTime + 360 * (m_nNeedEnergy - 1);
        m_pLabelTTFRecTime->setString(getLeftTimeFromInt(m_dwRecTime)->getCString());
        m_pLabelTTFRecAll->setString(getLeftTimeFromInt(m_dwRecAllTime)->getCString());
        
        schedule(schedule_selector(CcbUserInfoLayer::updateTime), 1.0f);
    } else {
        SET_MAX_ENERGY;
    }
    
    m_bMusicBg = CMusicCtrl::GetIsMusicOn();
    m_bMusicEffect = CMusicCtrl::GetIsEffectOn();
    this->changeMusicButtonStatus();
}

#pragma mark - Self Functions -
void CcbUserInfoLayer::RefeashLayer() {
    m_dwRecTime = UserInfoDataMgr::Get()->localRecTime();
    m_dwRecAllTime = m_dwRecTime + 360 * (m_nNeedEnergy - 1);
}

void CcbUserInfoLayer::updateTime(float dTime) {
    
    if (m_nNeedEnergy <= 0 || m_dwRecAllTime <= 0) {
        SET_MAX_ENERGY;
        unschedule(schedule_selector(CcbUserInfoLayer::updateTime));
        return;
    }
    
    if (m_dwRecTime <= 0) {
        CGameSession::GetRole()->SetdwEnergy(++m_dwCurEnergy);
        
        m_nNeedEnergy = m_dwEnergyMax - m_dwCurEnergy;
//        SET_ENERGY(m_pLabelTTFEnergyDes);
        snprintf(strBuf64, BUFFER_SIZE_64, "%d/%d", m_dwCurEnergy, m_dwEnergyMax);
        m_pLabelTTFEnergyDes->setString(strBuf64);
        
        if (m_nNeedEnergy <= 0) {
            SET_MAX_ENERGY;
            unschedule(schedule_selector(CcbUserInfoLayer::updateTime));
            return;
        } else {
            m_dwRecTime = 360;
        }
    }
    m_dwRecTime--;
    m_dwRecAllTime--;
    m_pLabelTTFRecTime->setString(getLeftTimeFromInt(m_dwRecTime)->getCString());
    m_pLabelTTFRecAll->setString(getLeftTimeFromInt(m_dwRecAllTime)->getCString());
}

void CcbUserInfoLayer::dwDollarChanged(uint32 dwDollar)
{
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", dwDollar);
    m_pLabelTTFDollar->setString(strBuf64);
}


void CcbUserInfoLayer::dwEnergyChanged(uint32 dwEnergy)
{
    m_dwCurEnergy = dwEnergy;
    m_nNeedEnergy = m_dwEnergyMax - m_dwCurEnergy;
//    SET_ENERGY(m_pLabelTTFEnergyDes);
    snprintf(strBuf64, BUFFER_SIZE_64, "%d/%d", m_dwCurEnergy, m_dwEnergyMax);
    m_pLabelTTFEnergyDes->setString(strBuf64);
}

void CcbUserInfoLayer::dwCoinChanged(uint32 dwCoin)
{
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", dwCoin);
    m_pLabelTTFCoin->setString(strBuf64);
}

void CcbUserInfoLayer::dwResFarmNumChanged(uint32 dwResFarmNum)
{
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", dwResFarmNum);
    m_pLabelTTFRonheStone->setString(strBuf64);
}

#pragma mark - Button Functions -
void CcbUserInfoLayer::onPressControlButtonClose(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    removeFromParentAndCleanup(true);
}

void CcbUserInfoLayer::onPressControlButtonSet(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (touchFlag) {
        return;
    }
    touchFlag = true;
    BackCtrl::InsertNextScene(kSystemScene);
}

void CcbUserInfoLayer::onPressControlButtonFriend(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (touchFlag) {
        return;
    }
    touchFlag = true;
    BackCtrl::InsertNextScene(kFriendSystemScene);
}

void CcbUserInfoLayer::onPressControlButtonExit(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
#ifdef VERSION_D9
    Account::shareInstance()->switchAccount();
#elif defined VERSION_PP
    Account::shareInstance()->logout();
#else
    CGameSession::BackToLogin();
#endif
}

void CcbUserInfoLayer::onPressControlButtonAnnounce(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (g_SystemNoticeDataMgr->GetSystemNoticeMap().size() != 0)
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(CcbManager::sharedManager()->LoadCcbSystemNoticeLayer(), 99, 3124);
    }
    else
    {
        CGameSession::SendNoticeGet();
    }
    
}

void CcbUserInfoLayer::onPressControlButtonUserCenter(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
#if defined  VERSION_I4||VERSION_PP || VERSION_D9||VERSION_91
    Account::shareInstance()->center();
#endif
}

void CcbUserInfoLayer::onPressControlButtonMusicCallBack(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    m_bMusicBg = !m_bMusicBg;
    CMusicCtrl::SetIsMusicOn(m_bMusicBg);
    this->changeMusicButtonStatus();
}

void CcbUserInfoLayer::onPressControlButtonEffectCallBack(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    m_bMusicEffect = !m_bMusicEffect;
    CMusicCtrl::SetIsEffectOn(m_bMusicEffect);
    this->changeMusicButtonStatus();
    
}

void CcbUserInfoLayer::onPressControlButtonExchange(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::InsertNextScene(kExchangeCodeScene);
}

void CcbUserInfoLayer::onPressControlButtonGoVip(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    UserInfoDataMgr::Get()->setGotoVipFlag(true);
    CGameSession::SendRequestStorePayList();
    this->removeFromParent();
}

void CcbUserInfoLayer::changeMusicButtonStatus()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/system/user_infopacker.plist");
    CCSpriteFrame* pSpriteMusicFrame = NULL;
    CCSpriteFrame* pSpriteEffectFrame = NULL;
    if (m_bMusicBg) {
        pSpriteMusicFrame = CCSprite::createWithSpriteFrameName("button_music_on.png")->displayFrame();
        m_pLabelMusic->setString(GET_STR(Str_UserInfo_Music_on));
    }
    else
    {
        pSpriteMusicFrame = CCSprite::createWithSpriteFrameName("button_music_off.png")->displayFrame();
        m_pLabelMusic->setString(GET_STR(Str_UserInfo_Music_off));
    }
    if (m_bMusicEffect) {
        pSpriteEffectFrame = CCSprite::createWithSpriteFrameName("button_soundeff_on.png")->displayFrame();
        m_pLabelEffect->setString(GET_STR(Str_UserInfo_Music_on));
    }
    else
    {
        pSpriteEffectFrame = CCSprite::createWithSpriteFrameName("button_soundeff_off.png")->displayFrame();
        m_pLabelEffect->setString(GET_STR(Str_UserInfo_Music_off));
    }
    for (int i = 0; i < 4; i++) {
        m_pControlButtonMusic->setBackgroundSpriteFrameForState(pSpriteMusicFrame,1 << i);
        m_pControlButtonEffect->setBackgroundSpriteFrameForState(pSpriteEffectFrame,1 << i);
    }
}
