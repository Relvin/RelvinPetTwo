#include "CcbPetShowBackLayer.h"
//#include "CcbManager.h"
#include "ConfigGet.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "UISupport.h"
#include "BackCtrl.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPetShowBackLayer::~CcbPetShowBackLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPetName);
	CC_SAFE_RELEASE_NULL(m_pSpriteLvStar);
    CC_SAFE_RELEASE_NULL(m_pSpriteAttribute);
    CC_SAFE_RELEASE_NULL(m_pLayerEvoLv);
	CC_SAFE_RELEASE_NULL(m_pControlButtonLock);
    CC_SAFE_RELEASE_NULL(m_pControlButtonUnLock);
    CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
    CC_SAFE_RELEASE_NULL(m_pSpritePetTypeIcon);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetShowBackLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetShowBackLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetShowBackLayer", CcbPetShowBackLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow_back.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetShowBackLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbPetShowBackLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    this->setTouchEnabled(true);
    this->setTouchPriority(kCCMenuHandlerPriority);
    
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);

    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger == GuideData::E_GUIDE_TRIGGER_3_GACHA) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonBack, GuideBtnPos::E_COMMON_BACK);
    } else if (wTrigger == GuideData::E_GUIDE_TRIGGER_4_GACHA) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonBack, GuideBtnPos::E_INFO_BACK);
    }
}

void CcbPetShowBackLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    onMoveIn();
    runAction(
              CCSequence::create(
                                 CCDelayTime::create(0.2f),
                                 CCCallFunc::create(this, callfunc_selector(CcbPetShowBackLayer::restoreTouch)),
                                 NULL
                                 )
              );
}

void CcbPetShowBackLayer::restoreTouch() {
    m_bCanTouchBtn = true;
}

void CcbPetShowBackLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

void CcbPetShowBackLayer::onExit()
{
	CCLayer::onExit();
}

// Inhert MemberVariableAssigner
bool CcbPetShowBackLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetName", CCLabelTTF*, this->m_pLabelTTFPetName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLvStar", CCSprite*, this->m_pSpriteLvStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute", CCSprite*, this->m_pSpriteAttribute);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEvoLv", CCLabelTTF*, this->m_pLayerEvoLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonLock", CCControlButton*, this->m_pControlButtonLock);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonUnLock", CCControlButton*, this->m_pControlButtonUnLock);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetTypeIcon", CCSprite*, this->m_pSpritePetTypeIcon);
	return false;
}

bool CcbPetShowBackLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetShowBackLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetShowBackLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetShowBackLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbPetShowBackLayer::onPressControlButtonBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLock", CcbPetShowBackLayer::onPressControlButtonLock);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUnLock", CcbPetShowBackLayer::onPressControlButtonUnLock);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetShowBackLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_backFlag = false;
    m_isHideOnly = false;
    m_dwPetObjId = 0;
    
    m_pControlButtonLock->setTouchPriority(2*kCCMenuHandlerPriority - 6);
    m_pControlButtonUnLock->setTouchPriority(2*kCCMenuHandlerPriority - 6);
    m_pControlButtonBack->setTouchPriority(2*kCCMenuHandlerPriority - 2);
}

void CcbPetShowBackLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    
    if (m_isHideOnly && m_delegate) {
        m_delegate->setVisible(false);
        return;
    }
    
    if (m_backFlag) {
        return;
    }
    m_backFlag = true;
    BackCtrl::BacktoUpperScene(kNormalTrans);
}

void CcbPetShowBackLayer::onPressControlButtonLock(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_ui_lock));
    CPetCtrl::Get()->setPetLocked(m_dwPetObjId, true);
    CPetCtrl::Get()->saveLocked();
    m_pControlButtonLock->setVisible(false);
    m_pControlButtonUnLock->setVisible(true);
}

void CcbPetShowBackLayer::onPressControlButtonUnLock(CCObject* pSender, CCControlEvent event)
{
	CMusicCtrl::PlayEffect(GET_MUSIC(Eff_ui_unlock));
    CPetCtrl::Get()->setPetLocked(m_dwPetObjId, false);
    CPetCtrl::Get()->saveLocked();
    m_pControlButtonLock->setVisible(true);
    m_pControlButtonUnLock->setVisible(false);
}

void CcbPetShowBackLayer::loadObjData(CPet *pet, bool isHideOnly)
{
    if (!pet) {
        return;
    }
    m_isHideOnly = isHideOnly;
    
    m_dwPetObjId = pet->GetObjId();
    loadData(pet->GetwIndex(), m_isHideOnly);
    
    if (m_isHideOnly) {
        m_pControlButtonUnLock->setVisible(false);
        m_pControlButtonLock->setVisible(false);
    }
    else{
        if (pet->GetbIsLock()) {
            m_pControlButtonUnLock->setVisible(true);
            m_pControlButtonLock->setVisible(false);
        }
        else{
            m_pControlButtonUnLock->setVisible(false);
            m_pControlButtonLock->setVisible(true);
        }
    }
    
    //进阶等级}
    m_pLayerEvoLv->setVisible(true);
    m_pLayerEvoLv->setString(CCString::createWithFormat("+%d", pet->GetbyEvolveLv())->getCString());
    m_pLayerEvoLv->setPositionX(getRight(m_pLabelTTFPetName) + 3);
}

void CcbPetShowBackLayer::loadData(uint16 wPetIndex, bool isHideOnly)
{
    m_isHideOnly = isHideOnly;
    hideLock();
    m_pLayerEvoLv->setVisible(false);
    PetConfig::STC_PET_CONFIG *pet = GET_CONFIG_STC(PetConfig, wPetIndex);
    if (!pet) {
        return;
    }
    //名字}
    m_pLabelTTFPetName->setString(pet->strName.c_str());
    //属性}
    m_pSpriteAttribute->setDisplayFrame(CPetCtrl::Get()->GetPetNaturePicSF(wPetIndex));
//    m_pSpriteAttribute->setPositionX(getLeft(m_pLabelTTFPetName) - 5);
    m_pSpritePetTypeIcon->setDisplayFrame(CPetCtrl::Get()->getPetType2SF(wPetIndex));
    //星级}
    m_pSpriteLvStar->removeAllChildren();
    m_pSpriteLvStar->setContentSize(CCSizeMake(m_pSpriteLvStar->getTexture()->getContentSize().width, getHeight(m_pSpriteLvStar)));
    for (int i = 1; i < pet->byStarLv; i++) {
        CCSprite *star = CCSprite::createWithTexture(m_pSpriteLvStar->getTexture());// ("ccbresources/12monthdate/pet/pic_lvstar.png");
        m_pSpriteLvStar->setContentSize(star->getContentSize());
        star->setAnchorPoint(ccp(0, 0));
        star->setPosition(ccp(i*(getWidth(star) + 1), 0));
        m_pSpriteLvStar->addChild(star);
    }
    m_pSpriteLvStar->setContentSize(CCSizeMake((getWidth(m_pSpriteLvStar)+1)*pet->byStarLv, getHeight(m_pSpriteLvStar)));
    m_pSpriteAttribute->setPositionX(getLeft(m_pSpriteLvStar) - 18);
}

void CcbPetShowBackLayer::onMoveIn()
{
//    mAnimationManager->runAnimationsForSequenceNamed("move_in");
}
void CcbPetShowBackLayer::onMoveOut()
{
//    mAnimationManager->runAnimationsForSequenceNamed("move_out");
}

void CcbPetShowBackLayer::hideLock()
{
    m_pControlButtonLock->setVisible(false);
    m_pControlButtonUnLock->setVisible(false);
}



