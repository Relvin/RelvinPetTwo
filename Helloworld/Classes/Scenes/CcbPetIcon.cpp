#include "CcbPetIcon.h"
//#include "CcbManager.h"
#include "PetCtrl.h"
#include "BackCtrl.h"
#include "UISupport.h"
#include "Pet.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "EmblemDataMgr.h"
#include "MusicCtrl.h"
#include "PacketDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPetIcon::~CcbPetIcon()
{
	CC_SAFE_RELEASE_NULL(m_pSpritePet);
	CC_SAFE_RELEASE_NULL(m_pSpritePetFrame);
	CC_SAFE_RELEASE_NULL(m_pSpriteBg);
    CC_SAFE_RELEASE_NULL(m_pSpriteAttribute);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    CC_SAFE_RELEASE_NULL(m_pSpriteVip);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetIcon( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetIcon( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetIcon", CcbPetIconLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_icon.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetIcon::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbPetIcon::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
//    loadData();
}

void CcbPetIcon::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetIcon::onExit()
{
	CCLayer::onExit();
}

void CcbPetIcon::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetIcon::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet", CCSprite*, this->m_pSpritePet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetFrame", CCSprite*, this->m_pSpritePetFrame);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute", CCSprite*, this->m_pSpriteAttribute);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteVip", CCSprite*, this->m_pSpriteVip);
	return false;
}

bool CcbPetIcon::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetIcon::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetIcon::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetIcon::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetIcon::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_dwAccountId = 0;
    m_wPetId = 0;
    m_dwPetObjiId = 0;
    CCSize size = m_pSpritePetFrame->getContentSize();
    size.width -= 2;//m_pSpritePetBg->getScaleX();
    size.height -= 2;// m_pSpritePetBg->getScaleY();
    btn = CCScrollButton::createTransWithHightLight();//(sprite);
    btn->setPreferredSize(size);
    btn->setZoomOnTouchDown(false);
    btn->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbPetIcon::onSelected), CCControlEventTouchUpInside);

    btn->setPosition(ccp(getWidth(m_pSpritePetFrame)* 0.5, getHeight(m_pSpritePetFrame) * 0.5));
    btn->setAnchorPoint(ccp(0.5, 0.5));
    btn->setZOrder(1);
    addChild(btn);
    setBtnEnable(false);
    m_pSpritePetFrame->setZOrder(2);
    m_pSpriteAttribute->setZOrder(3);
    m_pLabelTTFName->setZOrder(4);
    m_pSpritePet->setVisible(false);
    
    hideName();
    hideVip();
}

void CcbPetIcon::showVip() {
    m_pSpriteVip->setVisible(true);
    m_pSpriteVip->setZOrder(10);
}

void CcbPetIcon::hideVip() {
    m_pSpriteVip->setVisible(false);
}

void CcbPetIcon::setPetId(uint16 wPetId)
{
    m_wPetId = wPetId;
    loadData();
}

void CcbPetIcon::loadData()
{
    CCSprite* sprite = dynamic_cast<CCSprite*>(getChildByTag(1));
    if (sprite) {
        sprite->setVisible(false);
        sprite->removeFromParent();
    }
    if (m_wPetId == 0) {
        m_pSpritePet->setVisible(false);
        m_pSpriteAttribute->setVisible(false);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/quality.plist");
        m_pSpritePetFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pet_nothing.png"));
        btn->setVisible(false);
        return;
    }
    
    //头像}
    m_pSpritePet->setVisible(true);
    m_pSpritePet->setTexture(CPetCtrl::Get()->GetPetHeadTexture(m_wPetId));
    
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, m_wPetId);
    //名字
    m_pLabelTTFName->setString(petCfg->strName.c_str());
    //属性}
    m_pSpriteAttribute->setVisible(true);
    CCSpriteFrame *fs = CPetCtrl::Get()->GetPetNaturePicSF(m_wPetId);
    m_pSpriteAttribute->setDisplayFrame(fs);
    uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(m_wPetId);
    
    m_pLabelTTFName->setColor(g_PacketDataMgr->getQualityColor(quality));
    
    //框}
    m_pSpritePetFrame->setVisible(true);
    m_pSpritePetFrame->setDisplayFrame(g_PacketDataMgr->getQualityFrameSF(quality));
    //背景}
    m_pSpriteBg->setDisplayFrame(g_PacketDataMgr->getQualityBgSF(quality));
}

void CcbPetIcon::setPetObjId(uint32 petObjiId)
{
    m_dwPetObjiId = petObjiId;
    loadObjData();
}
void CcbPetIcon::loadObjData()
{
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(m_dwPetObjiId);
    if (!pet) {
        btn->setVisible(false);
        m_pSpritePet->setVisible(false);
        m_pSpriteAttribute->setVisible(false);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/quality.plist");
        m_pSpritePetFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pet_nothing.png"));
        return;
    }
    
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    //名字
    m_pLabelTTFName->setString(petCfg->strName.c_str());
    
    //头像}
    m_pSpritePet->setVisible(true);
    m_pSpritePet->setTexture(CPetCtrl::Get()->GetPetHeadTexture(pet->GetwIndex()));
    //属性}
    m_pSpriteAttribute->setVisible(true);
    CCSpriteFrame *fs = CPetCtrl::Get()->GetPetNaturePicSF(pet->GetwIndex());
    m_pSpriteAttribute->setDisplayFrame(fs);
    //框}
    uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(pet->GetwIndex());
    m_pSpritePetFrame->setVisible(true);
    m_pSpritePetFrame->setDisplayFrame(g_PacketDataMgr->getQualityFrameSF(quality));
    //背景}
    m_pSpriteBg->setDisplayFrame(g_PacketDataMgr->getQualityBgSF(quality));
}

void CcbPetIcon::showAttribute(bool isShow)
{
//    m_pSpriteAttBg->setVisible(isShow);
}

void CcbPetIcon::setBtnEnable(bool enable)
{
    btn->setVisible(enable);
}

void CcbPetIcon::setRect(CCRect rect)
{
    btn->setClipRect(rect);
}

void CcbPetIcon::setName(const char *_strName) {
    showName();
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setString(_strName);
    }
}

void CcbPetIcon::onSelected(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    switch (BackCtrl::GetCurSceneIdx()) {
        case kPetTujian:
            CPetCtrl::Get()->setPetTujianShowId(m_wPetId);
            BackCtrl::InsertNextScene(kShowPetTujian, kNormalTrans);
            break;
        case kPetFuse:
            CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_FUSE);
            BackCtrl::InsertNextScene(kFuseList);
            break;
        case kFriendScene: {
            CPetCtrl::Get()->setIsFriendLook(true);
            CGameSession::SendReqOtherRoleInfo(m_dwAccountId);
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            break;
        }
            
        case kEmblemListSenec:
        {

            break;
        }
        default:
            break;
    }
}

void CcbPetIcon::setOpacity(GLubyte opacity)
{
    m_pSpritePetFrame->setOpacity(opacity);
    m_pSpritePet->setOpacity(opacity);
    m_pSpriteBg->setOpacity(opacity);
    m_pSpriteAttribute->setOpacity(opacity);
}

void CcbPetIcon::showName()
{
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setVisible(true);
    }
}
void CcbPetIcon::hideName()
{
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setVisible(false);
    }
}

