#include "CcbPetChooseInfoLayer.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "MainShowPet.h"
#include "GuideData.h"
#include "Instruments.h"
#include "ConfigData.h"
#include "PetCtrl.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif
USING_NS_CC;
USING_NS_CC_EXT;


CCScene* CcbPetChooseInfoScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbPetChooseInfoScene* pLayer = CcbPetChooseInfoScene::create();
    pLayer->addChild(pLayer);
    return pScene;
}

bool CcbPetChooseInfoScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbPetChooseInfoLayer(this));
    return true;
}

void CcbPetChooseInfoScene::onEnter()
{
    CCLayer::onEnter();
}

void CcbPetChooseInfoScene::onExit()
{
    CCLayer::onExit();
}

#pragma mark CcbPetChooseInfoLayer

CcbPetChooseInfoLayer::~CcbPetChooseInfoLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAdd2);
	CC_SAFE_RELEASE_NULL(m_pSpriteAttribute2);
	CC_SAFE_RELEASE_NULL(m_pSpriteStar2);
	CC_SAFE_RELEASE_NULL(m_pSpriteAttribute1);
	CC_SAFE_RELEASE_NULL(m_pSpriteStar1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDes);
	CC_SAFE_RELEASE_NULL(m_pControlButtonActive);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLayerLeft);
    CC_SAFE_RELEASE_NULL(m_pLayerRight);
    CC_SAFE_RELEASE_NULL(m_pNodePet1);
    CC_SAFE_RELEASE_NULL(m_pNodePet2);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetChooseInfoLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetChooseInfoLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetChooseInfoLayer", CcbPetChooseInfoLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/mainpet.ccb]", [ccb/mainpet.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/novicepetactive.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetChooseInfoLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbPetChooseInfoLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbPetChooseInfoLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetChooseInfoLayer::onExit()
{
	CCLayer::onExit();
}

void CcbPetChooseInfoLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetChooseInfoLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAdd2", CCLabelTTF*, this->m_pLabelTTFAdd2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute2", CCSprite*, this->m_pSpriteAttribute2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar2", CCSprite*, this->m_pSpriteStar2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute1", CCSprite*, this->m_pSpriteAttribute1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar1", CCSprite*, this->m_pSpriteStar1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDes", CCLabelTTF*, this->m_pLabelTTFDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonActive", CCControlButton*, this->m_pControlButtonActive);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerLeft", CCLayer*, this->m_pLayerLeft);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRight", CCLayer*, this->m_pLayerRight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet1", CCNode*, this->m_pNodePet1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodePet2", CCNode*, this->m_pNodePet2);
	return false;
}

bool CcbPetChooseInfoLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetChooseInfoLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetChooseInfoLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetChooseInfoLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbPetChooseInfoLayer::onPressControlButtonClose);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonActive", CcbPetChooseInfoLayer::onPressControlButtonActive);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetChooseInfoLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonActive->setTouchPriority(-1);
    m_pControlButtonClose->setTouchPriority(-1);
    m_pLabelTTFDes->noStroke();
}


void CcbPetChooseInfoLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    removeFromParent();
}

void CcbPetChooseInfoLayer::onPressControlButtonActive(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendChoosePet(m_wPetIdx);
    GuideData* pDate = GuideData::GetInstance();

    pDate->connectToServer();   // send 500 to server
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("choose_pet_over");
#endif
}

void CcbPetChooseInfoLayer::setPetIdx(uint16 wOrgPetIdx, uint16 wDesPetIdx)
{
    m_wPetIdx = wOrgPetIdx;
    
    MainShowPet* pOrgPet = MainShowPet::create(m_wPetIdx);
    MainShowPet* pDesPet = MainShowPet::create(wDesPetIdx);
    pOrgPet->setPosition(m_pNodePet1->getPosition());
    pDesPet->setPosition(m_pNodePet2->getPosition());
    m_pLayerLeft->addChild(pOrgPet, 1);
    m_pLayerRight->addChild(pDesPet, 1);
    
    PetConfig::STC_PET_CONFIG* pOrgPetCfg = GET_CONFIG_STC(PetConfig, m_wPetIdx);
    PetConfig::STC_PET_CONFIG* pDesPetCfg = GET_CONFIG_STC(PetConfig, wDesPetIdx);
    
    if (!pOrgPetCfg || !pDesPetCfg) {
        return;
    }
    
    m_pLabelTTFDes->setString(pOrgPetCfg->strDes.c_str());
    m_pLabelTTFName->setString(pOrgPetCfg->strName.c_str());
    
    // 星级，属性球}
    CCSpriteFrame* pSf = CPetCtrl::Get()->GetPetNaturePicSF(wOrgPetIdx);
    m_pSpriteAttribute1->setDisplayFrame(pSf);
    m_pSpriteAttribute2->setDisplayFrame(pSf);
    
    int nOrgStar = pOrgPetCfg->byStarLv;
    int nDesStar = pDesPetCfg->byStarLv;
    
    float fWidth = m_pSpriteStar1->getContentSize().width + 2;
    float fStart = m_pSpriteStar1->getPositionX();
    
    
    for (int i = 1; i < nOrgStar; i++) {
        CCSprite* pStar = CCSprite::createWithTexture(m_pSpriteStar1->getTexture());
        pStar->setAnchorPoint(ccp(0.5, 0.5));
        pStar->setPosition(ccp(fStart + (i * fWidth), getCenterY(m_pSpriteStar1)));
        m_pLayerLeft->addChild(pStar, 1);
    }
    
    fStart = m_pSpriteStar2->getPositionX();
    for (int i = 1; i < nDesStar; i++) {
        CCSprite* pStar = CCSprite::createWithTexture(m_pSpriteStar1->getTexture());
        pStar->setAnchorPoint(ccp(0.5, 0.5));
        pStar->setPosition(ccp(fStart + (i*fWidth), getCenterY(m_pSpriteStar2)));
        m_pLayerRight->addChild(pStar, 1);
    }
}

void CcbPetChooseInfoLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool CcbPetChooseInfoLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSize infoSize = this->getContentSize();
    CCPoint parentPoint = this->getPosition();
    CCSize parentSize = this->getParent()->getContentSize();
    parentPoint = ccpSub(parentPoint, ccp(infoSize.width*0.5, infoSize.height*0.5));
    
    CCRect infoRect = CCRectMake(parentPoint.x, parentPoint.y, infoSize.width, infoSize.height);
    CCPoint touch1Point = pTouch->getLocation();    //Screen
    
    if (!infoRect.containsPoint(touch1Point)) {
        onPressControlButtonClose(NULL, CCControlEventTouchUpInside);
    }
    
    return true;
}





