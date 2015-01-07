#include "MainHeadLayer.h"
#include "GameSession.h"
#include "ResourcePic.h"
#include "ConfigGet.h"
#include "Role.h"
#include "UISupport.h"
#include "ResourceStringClient.h"
#include "Instruments.h"
#include "CcbManager.h"
#include "GuideData.h"
#include "SystemMessage.h"
#include "GlobalData.h"
#include "MusicCtrl.h"
#include "ScrollNoticeLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

MainHeadLayer::MainHeadLayer()
: m_pLabelTTFCoin (NULL)
, m_pLabelTTFDollar (NULL)
, m_pSpriteEnergy (NULL)
, m_pSpriteExp (NULL)
, m_pLabelTTFUserName (NULL)
, m_pLabelTTFUserLv(NULL)
, m_fExpBarWidth(0.0f)
, m_fEnergyBarWidth(0.0f)
, m_pLabelTTFEnergy(NULL)
, m_pLabelTTFontTitle(NULL)
, m_pLabelTTFExp(NULL)
, m_pSpriteRankBadge(NULL)
, m_pLabelTTFVip(NULL)
, m_pNodeNotice(NULL)
, m_pNodeVip(NULL)
, m_pLabelTTFFightValue(NULL)
{

    m_pLabelTTFArenaCnt = NULL;
    m_pLabelTTFRonheStone = NULL;
}

MainHeadLayer::~MainHeadLayer()
{
    CGameSession::GetRole()->Detach(this);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCoin);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDollar);
	CC_SAFE_RELEASE_NULL(m_pSpriteEnergy);
	CC_SAFE_RELEASE_NULL(m_pSpriteExp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFUserName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFUserLv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFArenaCnt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFontTitle);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFExp);
    CC_SAFE_RELEASE_NULL(m_pSpriteRankBadge);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFVip);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRonheStone);
    CC_SAFE_RELEASE_NULL(m_pNodeNotice);
    CC_SAFE_RELEASE_NULL(m_pNodeVip);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFFightValue);
}


bool MainHeadLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    
    CRole* pRole = CGameSession::GetRole();
    pRole->Attach(this);
    
    setTouchEnabled(true);
	return true;
}

void MainHeadLayer::onEnter()
{
	CCLayer::onEnter();

	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    winSize = CCDirector::sharedDirector()->getWinSize();
    setData();
    
    ScrollNoticeLayer::shareInstance()->setPosition(m_pNodeNotice->convertToWorldSpaceAR(CCPointZero));
}

void MainHeadLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void MainHeadLayer::onExit()
{
	CCLayer::onExit();
}

void MainHeadLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}


// Inhert MemberVariableAssigner
bool MainHeadLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoin", CCLabelTTF*, this->m_pLabelTTFCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDollar", CCLabelTTF*, this->m_pLabelTTFDollar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEnergy", CCSprite*, this->m_pSpriteEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteExp", CCSprite*, this->m_pSpriteExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFArenaCnt", CCLabelTTF*, this->m_pLabelTTFArenaCnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFUserName", CCLabelTTF*, this->m_pLabelTTFUserName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFUserLv", CCLabelTTF*, this->m_pLabelTTFUserLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnergy", CCLabelTTF*, this->m_pLabelTTFEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFontTitle", CCLabelTTF*, this->m_pLabelTTFontTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFExp", CCLabelTTF*, this->m_pLabelTTFExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRankBadge", CCSprite*, this->m_pSpriteRankBadge);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFVip", CCLabelTTF*, this->m_pLabelTTFVip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRonheStone", CCLabelTTF*, this->m_pLabelTTFRonheStone);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeNotice", CCNode*, this->m_pNodeNotice);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeVip", CCNode*, this->m_pNodeVip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFightValue", CCLabelTTF*, this->m_pLabelTTFFightValue);
	return false;
}

bool MainHeadLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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

void MainHeadLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    if (GlobalData::shared()->getVipSwitch()) {
        m_pNodeVip->setVisible(false);
    }
}

#define SET_ENERGY  \
{   \
    sprintf(strBuf64, "%d/%d", m_dwEnergy, m_dwMaxEnergy); \
    m_pLabelTTFEnergy->setString(strBuf64); \
    float percent = (float)m_dwEnergy / m_dwMaxEnergy;    \
    m_pSpriteEnergy->setTextureRect(CCRectMake(0, 0, m_fEnergyBarWidth *  (percent > 1.0f ? 1 : percent), getHeight(m_pSpriteEnergy)));  \
}   \

void MainHeadLayer::setData()
{
    CCLOG("set head begin");
    GlobalData::GetCurTime();
    m_fExpBarWidth = m_pSpriteExp->getContentSize().width;
    m_fEnergyBarWidth = m_pSpriteEnergy->getContentSize().width;
    
    m_pLabelTTFEnergy->noStroke();
    
    CRole* pRole = CGameSession::GetRole();
    
    float percent = 0.0f;
    CCString* str = CCString::createWithFormat("%d", pRole->GetdwCoin());
    if (m_pLabelTTFCoin)
    {
        // 设置金币数值}
        this->m_pLabelTTFCoin->setString(str->getCString());
    }
    //设置融合石数量}
    if (m_pLabelTTFRonheStone) {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d", pRole->GetdwResFarmNum());
        m_pLabelTTFRonheStone->setString(strBuf64);
    }
    
    if (m_pLabelTTFDollar)
    {
        str->initWithFormat("%d", pRole->GetdwDollar());
        this->m_pLabelTTFDollar->setString(str->getCString());
    }
    if (m_pLabelTTFUserName)
    {
        this->m_pLabelTTFUserName->setString(pRole->GetstrUserName().c_str());
    }
    if (m_pLabelTTFUserLv)
    {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d", pRole->GetwRoleLv());
        this->m_pLabelTTFUserLv->setString(strBuf64);
    }
    
    uint32 dwMaxExp = pRole->GetdwRoleMaxExp();
    uint32 dwExp = pRole->GetdwRoleExp();
    // 经验条数字}
    if (m_pLabelTTFExp) {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d/%d", dwExp, dwMaxExp);
        this->m_pLabelTTFExp->setString(strBuf64);
    }
    if (m_pSpriteExp)
    {
        percent = (float)dwExp / dwMaxExp;
        this->m_pSpriteExp->setTextureRect(CCRectMake(0, 0,m_fExpBarWidth * (percent > 1.0f ? 1 : percent) , getHeight(m_pSpriteExp)));
    }
    
    m_dwEnergy = pRole->GetdwEnergy();
    m_dwMaxEnergy = pRole->GetdwEnergyMax();
    
    SET_ENERGY;
    
    // 设置竞技点}
    int iArenaUseCnt = pRole->GetbyArenaUseCnt();
    if (m_pLabelTTFArenaCnt) {
        snprintf(strBuf64, BUFFER_SIZE_64,  "%d/10", iArenaUseCnt);
        m_pLabelTTFArenaCnt->setString(strBuf64);
    }
    
    
    uint16 wIndex = pRole->GetbyArenaGroup();
    if (wIndex == 0) {
        wIndex = 12;
    }
    RankRewardConfig::STC_RANKREWARD_CONFIG* pConfig = GET_CONFIG_STC(RankRewardConfig, wIndex);
    if (pConfig)
    {
        this->m_pLabelTTFontTitle->setString(pConfig->strGroupName.c_str());
        ccColor3B GroupColor;
        GroupColor.r = (0xff << 16 & pConfig->dwcolor) >> 16;
        GroupColor.g = (0xff << 8 & pConfig->dwcolor) >> 8;
        GroupColor.b = 0xff & pConfig->dwcolor;
        m_pLabelTTFontTitle->setColor(GroupColor);
        
        //徽章}
        CCTexture2D* pBadgeTexture = CCTextureCache::sharedTextureCache()->addImage(GET_ARENA_BADGE_PIC(pConfig->wBadge));
        m_pSpriteRankBadge->setTexture(pBadgeTexture);
    }
    
    if (m_pLabelTTFVip) {
        CCString* vipString = CCString::createWithFormat("%d", pRole->GetbyVipLv());
        m_pLabelTTFVip->setString(vipString->getCString());
    }
    
    m_pLabelTTFFightValue->setString(CCString::createWithFormat("%d", pRole->GetdwRoleFightValue())->getCString());
    
    CCLOG("set head end");
    GlobalData::GetCurTime();
}

#pragma mark Observer Delegate
void MainHeadLayer::dwCoinChanged(uint32 dwCoin)
{
    this->m_pLabelTTFCoin->setString(CCString::createWithFormat("%d", dwCoin)->getCString());
}

void MainHeadLayer::dwDollarChanged(uint32 dwDollar)
{
    this->m_pLabelTTFDollar->setString(CCString::createWithFormat("%d", dwDollar)->getCString());
}

void MainHeadLayer::energyChanged()
{
    CRole* pRole = CGameSession::GetRole();
    m_dwEnergy = pRole->GetdwEnergy();
    m_dwMaxEnergy = pRole->GetdwEnergyMax();

    SET_ENERGY;
}

void MainHeadLayer::dwEnergyChanged(uint32 dwEnergy) {
    energyChanged();
}

void MainHeadLayer::dwEnergyMaxChanged(uint32 dwEnergyMax) {
    energyChanged();
}

void MainHeadLayer::wRoleLvChanged(uint16 wRoleLv)
{
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", wRoleLv);
    this->m_pLabelTTFUserLv->setString(strBuf64);
}

void MainHeadLayer::expChanged()
{
    CRole* pRole = CGameSession::GetRole();
    float percent = 0.0f;
    
    uint32 dwExp = pRole->GetdwRoleExp();
    uint32 dwMaxExp = pRole->GetdwRoleMaxExp();
    if (m_pSpriteExp) {
        percent = (float)dwExp / dwMaxExp;
        this->m_pSpriteExp->setTextureRect(CCRectMake(0, 0,m_fExpBarWidth * (percent > 1.0f ? 1 : percent) , m_pSpriteExp->getContentSize().height));
    }
    
    if (m_pLabelTTFExp) {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d/%d", dwExp, dwMaxExp);
        this->m_pLabelTTFExp->setString(strBuf64);
    }
}

void MainHeadLayer::dwRoleExpChanged(uint32 dwRoleExp) {
    expChanged();
}

void MainHeadLayer::dwRoleMaxExpChanged(uint32 dwRoleMaxExp) {
    expChanged();
}

void MainHeadLayer::byArenaUseCntChanged(uint8 byArenaUseCnt)
{
    snprintf(strBuf64, BUFFER_SIZE_64, "%d/10", byArenaUseCnt);
    m_pLabelTTFArenaCnt->setString(strBuf64);
}

void MainHeadLayer::byArenaGroupChanged(uint8 byArenaGroup) {
    if (m_pLabelTTFontTitle) {
        uint16 wIndex = byArenaGroup;
        if (wIndex == 0 || wIndex > 11) {
            wIndex = 11;
        }
        RankRewardConfig::STC_RANKREWARD_CONFIG* pConfig = GET_CONFIG_STC(RankRewardConfig, wIndex);
        this->m_pLabelTTFontTitle->setString(pConfig->strGroupName.c_str());
    }
}
void MainHeadLayer::strUserNameChanged(std::string strUserName) {
    if (m_pLabelTTFUserName)
    {
        this->m_pLabelTTFUserName->setString(strUserName.c_str());
    }
}

void MainHeadLayer::byVipLvChanged(uint8 byVip)
{
    if (m_pLabelTTFVip) {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d", byVip);
        m_pLabelTTFVip->setString(strBuf64);
    }
}

void MainHeadLayer::dwResFarmNumChanged(uint32 dwResFarmNum)
{
    if (m_pLabelTTFRonheStone) {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d", dwResFarmNum);
        m_pLabelTTFRonheStone->setString(strBuf64);
    }
}

void MainHeadLayer::dwRoleFightValueChanged(uint32 dwRoleFightValue)
{
    if (m_pLabelTTFFightValue) {
        m_pLabelTTFFightValue->setString(CCString::createWithFormat("%d", dwRoleFightValue)->getCString());
    }
}

#pragma mark ccTouchDelegate
void MainHeadLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -2, false);
}

bool MainHeadLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    float upper = this->getPositionY();
    float bottom = upper - this->getContentSize().height * 2.0 /3.0;//触摸区域为上2/3的部分}
    
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    if (touchPoint.y > bottom && touchPoint.y < upper) {
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbUserInfoLayer(this);
        if (pNode)
        {
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
            pNode->setPosition(ccp(winSize.width*0.5, bottom));
            CCDirector::sharedDirector()->getRunningScene()->addChild(pNode, 10);
            return true;
        }
    }
    return false;
}

void MainHeadLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}


