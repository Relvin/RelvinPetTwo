#include "CcbPetBattleBossLayer.h"
//#include "CcbManager.h"
#include "CcbPetBattleLayer.h"
#include "SequenceAction.h"
#include "SequencePet.h"
#include "PetCtrl.h"
#include "UISupport.h"
#include "GuideData.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPetBattleBossLayer::~CcbPetBattleBossLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpritePetMc);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetBattleBossLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetBattleBossLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetBattleBossLayer", CcbPetBattleBossLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_boss.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetBattleBossLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbPetBattleBossLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbPetBattleBossLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetBattleBossLayer::onExit()
{
	CCLayer::onExit();
}

void CcbPetBattleBossLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetBattleBossLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetMc", CCSprite*, this->m_pSpritePetMc);

	return false;
}

bool CcbPetBattleBossLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbPetBattleBossLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "showPlist", CcbPetBattleBossLayer::showPlist);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "showBoss", CcbPetBattleBossLayer::showBoss);
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onRemoveSalf", CcbPetBattleBossLayer::onRemoveSalf);
	return NULL;
}

SEL_MenuHandler CcbPetBattleBossLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetBattleBossLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetBattleBossLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    plistId = 1;
    m_bossId = 0;
    m_pSpritePetMc->setVisible(false);
}

void CcbPetBattleBossLayer::showPlist()
{
    CCString* str = CCString::createWithFormat("ccbresources/12monthdate/battle/pet_boss_0%d.plist", plistId);
    CCParticleSystemQuad* plist = CCParticleSystemQuad::create(str->getCString());
    float fDur = 0.2f;
    if (plist) {
        fDur = plist->getDuration();
        plist->setPosition(m_pSpritePetMc->getPosition());
        m_pSpritePetMc->getParent()->addChild(plist);
    }
    plistId++;
    if (plistId > 3) {
        return;
    }
    this->runAction(CCSequence::create(CCDelayTime::create(fDur),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBattleBossLayer::showPlist)),
                                       NULL));
}

void CcbPetBattleBossLayer::showBoss()
{
    if (m_bossId) {
        SequencePet* mc = SequencePet::create(m_bossId);
        mc->runAction(CCRepeatForever::create(SequenceAction::create(mc, SEQ_ACT_STAND)));
        mc->setPosition(CPetCtrl::Get()->ConvertFlccPos(m_bossId, getWidth(mc), m_pSpritePetMc->getPosition()));
        mc->setAnchorPoint(ccp(0.5, 0));
        m_pSpritePetMc->getParent()->addChild(mc);
    }
}

void CcbPetBattleBossLayer::onRemoveSalf()
{
    removeFromParent();
    if (m_delegate) {
        m_delegate->runAction(
                              CCSequence::create(
                                                 CCDelayTime::create(0.5),
                                                 CCCallFunc::create(m_delegate, callfunc_selector(CcbPetBattleLayer::roundStart)),
                                                 NULL
                                                 )
                              );
        
        m_delegate->pauseAll();
        
//        CRole* pRole = CGameSession::GetRole();
//        pRole->SetwGuideTrigger(GuideData::E_GUIDE_TRIGGER_BOSS_7_TALK);
        GuideData::GetInstance()->addGuideLayer();
    }
}

bool CcbPetBattleBossLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void CcbPetBattleBossLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2*kCCMenuHandlerPriority, true);
}







