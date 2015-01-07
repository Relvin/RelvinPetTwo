#include "CcbTeamFrameLayer.h"
//#include "CcbManager.h"
#include "CcbTeamMemberLayer.h"
#include "Team.h"
#include "TeamCtrl.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "ConfigGet.h"
#include "PetBattleData.h"
#include "UISupport.h"
#include "ResourceStringClient.h"
#include "CcbTeamLayer.h"
#include "MusicCtrl.h"
#include "GuideBtnPos.h"
#include "GuideData.h"

CcbTeamFrameLayer::~CcbTeamFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTeamId);
	
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillDes);
	CC_SAFE_RELEASE_NULL(m_pLayerMask);
	CC_SAFE_RELEASE_NULL(m_pSpritePetBg_2);
	CC_SAFE_RELEASE_NULL(m_pSpritePetBg_4);
	CC_SAFE_RELEASE_NULL(m_pSpritePetBg_6);
	CC_SAFE_RELEASE_NULL(m_pSpritePetBg_1);
	CC_SAFE_RELEASE_NULL(m_pSpritePetBg_3);
	CC_SAFE_RELEASE_NULL(m_pSpritePetBg_5);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_2);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_4);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_6);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_1);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_3);
	CC_SAFE_RELEASE_NULL(m_pLayerMember_5);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSetLeader);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTeamFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTeamFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTeamFrameLayer", CcbTeamFrameLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/teamcircleset.ccb]", [ccb/teamcircleset.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/teamframe.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbTeamFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_wTeamId = 10;
    
    
	return true;
}

void CcbTeamFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    setTouchEnabled(true);
    arrMembers[0] = NULL;
    m_mapMember[1] = m_pLayerMember_1;
    m_mapMember[2] = m_pLayerMember_2;
    m_mapMember[3] = m_pLayerMember_3;
    m_mapMember[4] = m_pLayerMember_4;
    m_mapMember[5] = m_pLayerMember_5;
    m_mapMember[6] = m_pLayerMember_6;
    
    arrPos[1] = m_pLayerMember_1->getPosition();
    arrPos[2] = m_pLayerMember_2->getPosition();
    arrPos[3] = m_pLayerMember_3->getPosition();
    arrPos[4] = m_pLayerMember_4->getPosition();
    arrPos[5] = m_pLayerMember_5->getPosition();
    arrPos[6] = m_pLayerMember_6->getPosition();
}

void CcbTeamFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerMember_1, GuideBtnPos::E_TEAM_ONE);
    }
}

void CcbTeamFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTeamFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTeamFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTeamId", CCLabelTTF*, this->m_pLabelTTFTeamId);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillName", CCLabelTTF*, this->m_pLabelTTFLeaderSkillName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillDes", CCLabelTTF*, this->m_pLabelTTFLeaderSkillDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMask", CCLayer*, this->m_pLayerMask);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetBg_2", CCSprite*, this->m_pSpritePetBg_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetBg_4", CCSprite*, this->m_pSpritePetBg_4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetBg_6", CCSprite*, this->m_pSpritePetBg_6);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetBg_1", CCSprite*, this->m_pSpritePetBg_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetBg_3", CCSprite*, this->m_pSpritePetBg_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetBg_5", CCSprite*, this->m_pSpritePetBg_5);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_2", CcbTeamMemberLayer*, this->m_pLayerMember_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_4", CcbTeamMemberLayer*, this->m_pLayerMember_4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_6", CcbTeamMemberLayer*, this->m_pLayerMember_6);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_1", CcbTeamMemberLayer*, this->m_pLayerMember_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_3", CcbTeamMemberLayer*, this->m_pLayerMember_3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMember_5", CcbTeamMemberLayer*, this->m_pLayerMember_5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSetLeader", CCLabelTTF*, this->m_pLabelTTFSetLeader);

	return false;
}

bool CcbTeamFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTeamFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTeamFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTeamFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTeamFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    isChgLeader = false;
    isMove = false;
    m_bySiteFrom = 0;
    m_FromPet = NULL;
    m_delegate = NULL;
    m_pLabelTTFSetLeader->setVisible(false);
    m_pLabelTTFSetLeader->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(1.5),
                                                                               CCFadeOut::create(1.5),
                                                                               NULL)));
    arrMemBg[1] = m_pSpritePetBg_1;
    arrMemBg[2] = m_pSpritePetBg_2;
    arrMemBg[3] = m_pSpritePetBg_3;
    arrMemBg[4] = m_pSpritePetBg_4;
    arrMemBg[5] = m_pSpritePetBg_5;
    arrMemBg[6] = m_pSpritePetBg_6;
}



void CcbTeamFrameLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 20, true);
}

bool CcbTeamFrameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_wTeamId != CTeamCtrl::GetCurTeamId()) {
        return false;
    }
    isMove = false;
    posFrom = pTouch->getLocation();
    CCPoint p = convertToNodeSpace(pTouch->getLocation());
    for (int i = 1; i <= PetCnt; i++) {
//        CCLog(" !~~~2222~~getId : %d", arrMembers[i]->getPetObjId());
        CcbTeamMemberLayer* member = m_mapMember[i];
        if (!member) {
            continue;
        }
        
        CCRect rect = member->boundingBox();

        if (rect.containsPoint(p)) {
            //如果是选队长}
            if (isChgLeader) {
                chgLeader(i);
                return true;
            }
            //如果是换位置}
            else
            {
                //如果点中的是 没有队员或者锁定时，直接穿透}
                if (!member->getPetObjId()) {
                    return false;
                }
                chgSiteFrom(i);
            }
            return true;
        }
    }
    
    if (isChgLeader) {
        return true;
    }
    
    return false;
}

void CcbTeamFrameLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (isChgLeader) {
        return;
    }
    CCPoint p = pTouch->getLocation();
    if (m_FromPet) {
        
        CCLog("~~~~~~~~~m_FromPet x %f, y %f", (p - posFrom).x, (p - posFrom).y);
        
        m_FromPet->setPosition(arrPos[m_bySiteFrom] + p - posFrom);
        CCLog("m_FromPet x %f, y %f", m_FromPet->getPosition().x, m_FromPet->getPosition().y);
    }
    
    if (fabs(p.y - posFrom.y) > 10
        || fabs(p.x - posFrom.x) > 10) {
        isMove = true;
    }
    
    p = convertToNodeSpace(p);
    for (int i = 1; i <= PetCnt; i++) {
        CCRect rect = arrMemBg[i]->boundingBox();
        if (rect.containsPoint(p)) {
            //移动到别的位置后，对应位置有提示}
            if (m_byMoveSite != i) {
                m_byMoveSite = i;
                CMusicCtrl::PlayEffect(GET_MUSIC(Eff_pet_change));
            }
            
            break;
        }
    }
}

void CcbTeamFrameLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //设置队长时，遮罩出现，点到空白位置时，遮罩消失，取消设置}
    if (isChgLeader) {
        endLeaderChg();
        return;
    }
    
    if (m_FromPet) {
        if (!m_bySiteFrom) {
            return;
        }
        
        CCPoint p = convertToNodeSpace(pTouch->getLocation());
        
        if (!isMove) {
            m_FromPet->onSetMember();
            return;
        }
        
        for (int i = 1; i <= PetCnt; i++) {
            if (!m_mapMember[i]) {
                continue;
            }
            CCRect rect = arrMemBg[i]->boundingBox();
//            rect.size.height = rect.size.height;
            if (!rect.containsPoint(p)) {
                continue;
            }
            chgSiteTo(i);
            return;
        }
        moveBack(m_bySiteFrom);
    }
    m_bySiteFrom = 0;
    isMove = false;
}

void CcbTeamFrameLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_FromPet) {
        moveBack(m_bySiteFrom);
    }
    isMove = false;
}


void CcbTeamFrameLayer::setTeamId(uint16 wTeamId)
{
    if (m_wTeamId != wTeamId) {
        m_wTeamId = wTeamId;
        loadData();
    }
}
void CcbTeamFrameLayer::loadData()
{
    CTeam *team = CTeamCtrl::GetTeamByObjId(m_wTeamId);
    if (!team) {
        return;
    }
    
    int cnt = team->getarrPetObId().size();
    int count = 0;
    
    for (int i = 1; i < cnt; i++) {
        if (team->getarrPetObId()[i]) {
            m_mapMember[i]->setPetObjIdAndSite(team->getarrPetObId()[i], i);
            if (i == team->getbyLeaderSite()) {
                m_mapMember[i]->setIsLeader(true);
            }
            count++;
        }
    }
    
    //当前站位上限（按1-3-5-2-4-6来解锁）}
    int teamSize = CTeamCtrl::getTeamMemberSize();
    //1-3-5
    for (int i = 0; i < 3; i++) {
        uint8 site = i*2 + 1;
        if (team->getarrPetObId()[site]) {
            continue;
        }
        count++;
        m_mapMember[site]->setPetObjIdAndSite(team->getarrPetObId()[site], site);
        if (!team->getarrPetObId()[site] && count > teamSize){
            m_mapMember[site]->setIsLock(true);
            continue;
        }
    }
    //2-4-6
    for (int i = 0; i < 3; i++) {
        uint8 site = i*2 + 2;
        if (team->getarrPetObId()[site]) {
            continue;
        }
        count++;
        m_mapMember[site]->setPetObjIdAndSite(team->getarrPetObId()[site], site);
        if (!team->getarrPetObId()[site] && count > teamSize){
            m_mapMember[site]->setIsLock(true);
            continue;
        }
    }
    
    std::string s = "";
    switch (m_wTeamId+1) {
        case 1:
            s = GET_STR(Str_one);
            break;
        case 2:
            s = GET_STR(Str_two);
            break;
        case 3:
            s = GET_STR(Str_three);
            break;
        case 4:
            s = GET_STR(Str_four);
            break;
        case 5:
            s = GET_STR(Str_five);
            break;
        case 6:
            s = GET_STR(Str_six);
            break;
        default:
            break;
    }
    CCString *str = CCString::createWithFormat("%s%s", GET_STR(Str_team), s.c_str());
    m_pLabelTTFTeamId->setString(str->getCString());
    
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(team->getarrPetObId()[team->getbyLeaderSite()]);
    if (!pet) {
        return;
    }
    
    PetConfig::STC_PET_CONFIG *pConfig = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    if (!pConfig) {
        return;
    }
    
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG *lConfig = GET_CONFIG_STC(LeaderSkillConfig, pConfig->wLeaderSkillId);
    if (!lConfig) {
        m_pLabelTTFLeaderSkillName->setString("");
        m_pLabelTTFLeaderSkillDes->setString("");
        return;
    }
    m_pLabelTTFLeaderSkillDes->setString(lConfig->strDes.c_str());
    m_pLabelTTFLeaderSkillName->setString(lConfig->strName.c_str());
}

//切换队长}
void CcbTeamFrameLayer::chgLeader(uint8 bySite)
{
    
//    endLeaderChg();
    if (!m_mapMember[bySite] || m_mapMember[bySite]->getPetObjId() == 0) {
        return;
    }
    uint8 curLeader = CTeamCtrl::GetCurTeam()->getbyLeaderSite();
    if (bySite == curLeader) {
        return;
    }
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_pet_change));
    
    CTeamCtrl::SetTeamLeaderBySite(bySite);
    m_mapMember[curLeader]->setIsLeader(false);
    m_mapMember[bySite]->setIsLeader(true);
    
    CPet *pet = CPetCtrl::Get()->GetPetByObjId(m_mapMember[bySite]->getPetObjId());
    if (!pet) {
        return;
    }
    
    PetConfig::STC_PET_CONFIG *pConfig = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    if (!pConfig) {
        return;
    }
    
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG *lConfig = GET_CONFIG_STC(LeaderSkillConfig, pConfig->wLeaderSkillId);
    if (!lConfig) {
        m_pLabelTTFLeaderSkillName->setString("");
        m_pLabelTTFLeaderSkillDes->setString("");
        return;
    }
    m_pLabelTTFLeaderSkillName->setString(lConfig->strName.c_str());
    m_pLabelTTFLeaderSkillDes->setString(lConfig->strDes.c_str());

}
void CcbTeamFrameLayer::chgSiteFrom(uint8 bySiteFrom)
{
    if (!m_mapMember[bySiteFrom]) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_pickup));
    m_byMoveSite = bySiteFrom;
    m_bySiteFrom = bySiteFrom;
    CCLOG("site From ********* ~~~~~%d", m_bySiteFrom);
    m_FromPet = m_mapMember[bySiteFrom];
    m_FromPet->runAction(CCScaleTo::create(0.05, 1.05));
    m_FromPet->setZOrder(7);
}
void CcbTeamFrameLayer::chgSiteTo(uint8 bySiteTo)
{
    if (!m_bySiteFrom){
        return;
    }
    CCLOG("site From ~~~~~%d", m_bySiteFrom);
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_putdown));
    //map的key就是site位置，换位置其实就是调换两位置的value}
    CcbTeamMemberLayer *temp = m_mapMember[m_bySiteFrom];
    moveBack(bySiteTo);
    if (bySiteTo == m_bySiteFrom) {
        return;
    }
    
    CCPoint posFrom = arrPos[m_bySiteFrom];
    m_mapMember[bySiteTo]->setPosition(posFrom);
    m_mapMember[m_bySiteFrom] = m_mapMember[bySiteTo];
    m_mapMember[bySiteTo] = temp;
    
    m_mapMember[m_bySiteFrom]->setSite(m_bySiteFrom);
    m_mapMember[bySiteTo]->setSite(bySiteTo);

    CTeamCtrl::ChgTeamMamberSite(m_bySiteFrom, bySiteTo);
    
    m_bySiteFrom = 0;
    resetZorder();
}

void CcbTeamFrameLayer::showPetBaseValue(bool isShow)
{
    for (int i = 1; i <= PetCnt; i++) {
        if (!m_mapMember[i]) {
            continue;
        }
        m_mapMember[i]->ShowBaseValue(isShow);
    }
}

void CcbTeamFrameLayer::moveBack(uint8 bysite)
{
    if (m_FromPet) {
        m_FromPet->runAction(CCSpawn::create(CCScaleTo::create(0.05, 1.0),
                                             CCMoveTo::create(0.05, arrPos[bysite]),
                                             NULL));
    }
}

void CcbTeamFrameLayer::startLeaderChg()
{
    m_pLayerMask->setVisible(true);
    m_pLabelTTFSetLeader->setVisible(true);
    isChgLeader = true;
}

void CcbTeamFrameLayer::endLeaderChg()
{
//    m_pControlButtonChgLeader->setVisible(true);
    m_pLabelTTFSetLeader->setVisible(false);
    m_pLayerMask->setVisible(false);
    isChgLeader = false;
    if (m_delegate) {
        m_delegate->endLeaderChg();
    }
}

void CcbTeamFrameLayer::resetZorder()
{
    for (int i = 1; i <= PetCnt; i++) {
        m_mapMember[i]->setZOrder(i);
    }
}

