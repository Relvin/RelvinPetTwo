#include "CcbPadLayer.h"
#include "BackCtrl.h"
#include "UISupport.h"
#include "ResourceDefine.h"
#include "GuideData.h"
#include "CcbPetBattleLayer.h"
#include "ResourcePic.h"
#include "GameSession.h"
#include "Role.h"
#include "PadDefine.h"
#include "PetCtrl.h"
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif
#include "MusicCtrl.h"
#include "ConfigGet.h"

#include "CcbBegin22Layer.h"
#include "CcbChoosePetLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPadLayer::~CcbPadLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteCharac);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    CC_SAFE_RELEASE_NULL(m_pControlButtonSelf);
    CC_SAFE_RELEASE_NULL(m_pNodeTop);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFContent);
    CC_SAFE_RELEASE_NULL(m_pLayerMask);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPadLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPadLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPadLayer", CcbPadLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/talkpad.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPadLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
    m_nKind = E_DEFAULT;
	return true;
}

void CcbPadLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbPadLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPadLayer::onExit()
{
	CCLayer::onExit();
}

void CcbPadLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPadLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCharac", CCSprite*, this->m_pSpriteCharac);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSelf", CCControlButton*, this->m_pControlButtonSelf);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTop", CCNode*, this->m_pNodeTop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFContent", CCLabelTTF*, this->m_pLabelTTFContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMask", CCLayer*, this->m_pLayerMask);
	return false;
}

bool CcbPadLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPadLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_MenuHandler CcbPadLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_CCControlHandler CcbPadLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSelf", CcbPadLayer::onPressControlButtonSelf);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPadLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pLabelTTFContent->noStroke();

    m_pLabelTTFName->setVisible(false);
    m_pControlButtonSelf->setVisible(false);
}

void CcbPadLayer::removeSelf()
{
    removeFromParent();
    
    // 由于先remove，可能会导致Delegate野指针的情况发生
    // 放在onExit中不行，下次试试把removeFromParent()放在方法的最后面
    if (m_pDelegate) {
        m_pDelegate->showStep();
    }
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    
    if (wTrigger == GuideData::E_SYS_GUIDE_12_BADGE) {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("badge_guide_end");
#endif
    }
    
    if ( wTrigger == GuideData::E_GUIDE_TRIGGER_BOSS_7_TALK ) {
        if (CcbPetBattleLayer::GetCurrScene()) {
            CcbPetBattleLayer::GetCurrScene()->remuseAll();
            CcbPetBattleLayer::GetCurrScene()->bossTransform();
        }
    } else if ( wTrigger == GuideData::E_GUIDE_TRIGGER_WAKE_1_TALK ) {
        if (CcbPetBattleLayer::GetCurrScene()) {
            CcbPetBattleLayer::GetCurrScene()->remuseAll();
        }
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("fake_battle_over");
#endif
        CCScene* pScene = CcbBegin22Layer::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
        return;
    } else if (wTrigger == GuideData::E_GUIDE_TRIGGER_NAME) {
//        CCScene* pScene = CreateNameScene::scene();
        CCScene* pScene = ChoosePetScene::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
        return;
    }
    else if (
             wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_1 ||
             wTrigger == GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_END_1_TALK
             ) {
        if (CcbPetBattleLayer::GetCurrScene()) {
            CcbPetBattleLayer::GetCurrScene()->remuseAll();
        }
    }
    else if (wTrigger == GuideData::E_GUIDE_END_TRIGGER) {
        GuideData::GetInstance()->onlyRmGuideLayer();
        GuideData::GetInstance()->connectToServer();
    }
    else {
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_2,
                                                 GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_3,
                                                 GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_4,
                                                 GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_5,
                                                 GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_6,
                                                 GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_7,
                                                 GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_8,
                                                 GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_9,
                                                 GuideData::E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_10,
                                                 GuideData::E_GUIDE_TRIGGER_BOSS_2_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_BOSS_3_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_BOSS_4_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_BOSS_5_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_BOSS_6_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_WAKE_2_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_WAKE_3_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_CHOOSE_TALK_2,
                                                 GuideData::E_GUIDE_TRIGGER_5_TEAM,
                                                 GuideData::E_GUIDE_TRIGGER_END_TEAM,
                                                 GuideData::E_GUIDE_TRIGGER_THI_TALK_2,
                                                 GuideData::E_GUIDE_TRIGGER_THI_ATTACK,
                                                 GuideData::E_GUIDE_TRIGGER_PET_ENHANCE_2_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_END_PET_ENHANCE,
                                                 GuideData::E_GUIDE_TRIGGER_PET_EVOLVE_2_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_PET_EVOLVE_3_TALK,
                                                 GuideData::E_GUIDE_TRIGGER_END_PET_EVOLVE,
                                                 
                                                 GuideData::E_SYS_GUIDE_3_JJC,
                                                 GuideData::E_SYS_GUIDE_11_BADGE,
                                                 GuideData::E_SYS_GUIDE_12_BADGE,
                                                 NULL);
    }

}

void CcbPadLayer::onPressControlButtonSelf(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_nKind == E_DEFAULT && m_bErase) {
        removeFromParent();
    } else if (m_nKind == E_BATTLE_LOSE) {
        BackCtrl::JumpToScene(kStageScene);
    } else if (m_nKind == E_GUIDE && m_bErase) {
        removeSelf();
    }
    return;
}

#pragma mark Public Method
void CcbPadLayer::setPadStyle(int code)
{
    if (code & kDesPad) {
        m_pLabelTTFName->setVisible(true);
        m_pControlButtonSelf->setVisible(true);
        m_pControlButtonSelf->setTouchPriority(3*kCCMenuHandlerPriority-1);
    }
}

void CcbPadLayer::setScrollMsg(const char* szName, ccColor3B cName, const char* szMsg, ccColor3B cMsg) {
    if (strcmp(szName, "OOXX") == 0) {
        m_pLabelTTFName->setString(CGameSession::GetRole()->GetstrUserName().c_str());
    } else {
        m_pLabelTTFName->setString(szName);
    }
    m_pLabelTTFName->setColor(cName);

    m_pLabelTTFContent->setString(szMsg);
    m_pLabelTTFContent->setColor(cMsg);
}

void CcbPadLayer::setLadyInfo(uint16 wPicPath, uint8 byPicOff, uint16 wScale)
{
    CCTexture2D* pTex = NULL;
    if (wPicPath > 1000)
    {
        pTex = CPetCtrl::Get()->GetPetBodyTexture(wPicPath - 1000);
        CCSize picSize = pTex->getContentSize();
        m_pSpriteCharac->setTexture(pTex);
        m_pSpriteCharac->setTextureRect(CCRectMake(0, 0, picSize.width, picSize.height));
        m_pSpriteCharac->setScale((float) wScale / 100.0f);
        
        // 大的宠物原画图居中显示}
        m_pSpriteCharac->setAnchorPoint(ccp(0.5, 0.0));
        m_pSpriteCharac->setPositionX(111.0f);
    }
    else
    {
        if (wPicPath == kXiaozhi) {         // 小智}
            pTex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_xiaozhi));
        } else if (wPicPath == kMiaomiao) {     // 喵喵}
            pTex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_miaomiao));
        } else if (wPicPath == kWuzang) {     // 武藏}
            pTex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_wuzang));
        } else if (wPicPath == kXiaocilang) {     // 小次郎}
            pTex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_xiaocilang));
        } else if (wPicPath == kDamowang) {     // 大魔王}
            pTex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_damowang));
        } else {}   // Default 皮卡丘}
        
        if (pTex) {
            m_pSpriteCharac->initWithTexture(pTex);// setTexture(pTex);
            m_pSpriteCharac->setAnchorPoint(ccp(0.5, 0.0));
        }
        
        if (byPicOff == kLeftOff) {
            m_pNodeTop->setPositionX(3.0f);
        } else if (byPicOff == kRightOff) {
            m_pNodeTop->setPositionX(171.0f);
        }
    }
}

void CcbPadLayer::setTouchErase(bool fade)
{
    m_bErase = fade;
}

#pragma mark Touch Delegate
void CcbPadLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*3, true);
}

bool CcbPadLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bErase) {
        removeSelf();
    }
    return true;
}

void CcbPadLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void CcbPadLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void CcbPadLayer::setFromKind(int kind)
{
    m_nKind = kind;
}

void CcbPadLayer::removeMask()
{
    m_pLayerMask->removeFromParent();
}


