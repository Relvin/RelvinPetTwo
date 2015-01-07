#include "CcbArenaPetCtrl.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "FightAI.h"
#include "PetBattleData.h"
#include "PetCtrl.h"
#include "CcbPetIcon.h"
#include "CcbArenaFightLayer.h"
#include "FightPetSprite.h"
#include "PacketDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbArenaPetCtrl::~CcbArenaPetCtrl()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteSkillBar);
	CC_SAFE_RELEASE_NULL(m_pSpriteHpBar);
//    CC_SAFE_RELEASE_NULL(m_pSpriteSkillBarBg);
//    CC_SAFE_RELEASE_NULL(m_pLayerPetIcon);
    CC_SAFE_RELEASE_NULL(m_pSpriteNormal);
	CC_SAFE_RELEASE_NULL(m_pSpriteDead);
	CC_SAFE_RELEASE_NULL(m_pSpriteNature);
	CC_SAFE_RELEASE_NULL(m_pSpriteNothing);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaPetCtrl( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaPetCtrl( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaPetCtrl", CcbArenaPetCtrlLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_pet_ctrl.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaPetCtrl::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbArenaPetCtrl::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbArenaPetCtrl::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaPetCtrl::onExit()
{
	CCLayer::onExit();
}

void CcbArenaPetCtrl::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaPetCtrl::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSkillBar", CCSprite*, this->m_pSpriteSkillBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteHpBar", CCSprite*, this->m_pSpriteHpBar);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSkillBarBg", CCSprite*, this->m_pSpriteSkillBarBg);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetIcon", CcbPetIcon*, this->m_pLayerPetIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNormal", CCSprite*, this->m_pSpriteNormal);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDead", CCSprite*, this->m_pSpriteDead);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNature", CCSprite*, this->m_pSpriteNature);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNothing", CCSprite*, this->m_pSpriteNothing);
	return false;
}

bool CcbArenaPetCtrl::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaPetCtrl::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaPetCtrl::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaPetCtrl::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaPetCtrl::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    barHpW = getWidth(m_pSpriteHpBar);
    barPowerW = getWidth(m_pSpriteSkillBar);
    
    m_pSpriteDead->setVisible(false);
    m_pSpriteNothing->setVisible(false);
//    m_pSpriteSkillBar->setVisible(false);
}

void CcbArenaPetCtrl::setBattleIndex(uint16 wBattleIndex)
{
    if (wBattleIndex == 0) {
        this->setVisible(false);
    }
    m_wBattleIndex = wBattleIndex;
    loadData();
}

void CcbArenaPetCtrl::loadData()
{
    FightPet *pet = FightAI::Get()->getFightPetByBIndex(m_wBattleIndex);
    if (!pet) {
//        this->setVisible(false);
//        m_pSpriteNature->setVisible(false);
//        m_pSpriteDead->setVisible(false);
//        m_pSpriteNormal->setVisible(false);
        m_pSpriteNothing->setVisible(true);
        return;
    }
    m_byMaxPower = pet->getPetInfo().wAllPower;
//    if (m_byMaxPower == 0) {
//        scaleYofSkillBar = 0;
//    }
//    else
//    {
//        scaleYofSkillBar = (float)((getHeight(m_pSpriteSkillBarBg) - 2) / m_byMaxPower - 2) / getHeight(m_pSpriteSkillBar);
//    }
//    offYofSkillBar = getHeight(m_pSpriteSkillBar) * scaleYofSkillBar + 2;
    //头像}
    m_pSpriteIcon->setTexture(CPetCtrl::Get()->GetPetBattleHeadTexture(pet->getPetInfo().wPetIndexId));
    //属性}
    m_pSpriteNature->setDisplayFrame(CPetCtrl::Get()->GetPetNaturePicSF(pet->getPetInfo().wPetIndexId));
    
    //框
    m_pSpriteNormal->setDisplayFrame(g_PacketDataMgr->getArenaFrame(pet->getPetInfo().wPetIndexId));
//    m_pSpriteIcon->setScale(0.6);
//    CcbPetIcon * icon = dynamic_cast<CcbPetIcon*>(CcbManager::sharedManager()->LoadCcbPetIcon(this));
//    m_pLayerPetIcon->setPetId(pet->getPetInfo().wPetIndexId);
//    m_pLayerPetIcon->showAttribute(false);
//    m_pLayerPetIcon->loadData();
    //血条}
    int curHp = pet->getCurHP();
    m_dwMaxHp = pet->getPetInfo().wHP;
    m_pSpriteHpBar->setTextureRect(CCRectMake(0, 0, (float)curHp / m_dwMaxHp * barHpW ,getHeight(m_pSpriteHpBar) ));
    //气条}
    int curPower = pet->getCurPower();
    setPower(curPower);
//    int maxPower = PetSkillValue;
//    m_pSpriteSkillBar->setTextureRect(CCRectMake(0, 0, (float)curPower / maxPower * barWidth, getHeight(m_pSpriteSkillBar)));
    
//    if (m_wBattleIndex > PetCnt) {
//        CCTexture2D* t2d = CCTextureCache::sharedTextureCache()->addImage("ccbresources/12monthdate/arena/button_arena_red.png");
//        if (t2d) {
//            m_pSpriteNormal->setTexture(t2d);
//        }
//    }
    
    
}

void CcbArenaPetCtrl::beHit(int curHp)
{
    m_pSpriteHpBar->setTextureRect(CCRectMake(0, 0, (float)curHp / m_dwMaxHp * barHpW ,getHeight(m_pSpriteHpBar) ));

//    m_pSpriteHpBar->setTextureRect(CCRectMake(0, 0, (float)curHp / m_dwMaxHp * barWidth, getHeight(m_pSpriteHpBar)));
}
void CcbArenaPetCtrl::setHp(int curHp)
{
    m_pSpriteHpBar->setTextureRect(CCRectMake(0, 0, (float)curHp / m_dwMaxHp * barHpW ,getHeight(m_pSpriteHpBar) ));

//    m_pSpriteHpBar->setTextureRect(CCRectMake(0, 0, (float)curHp / m_dwMaxHp * barWidth, getHeight(m_pSpriteHpBar)));
    
    if (curHp <= 0) {
        m_pSpriteDead->setVisible(true);
    }
}
void CcbArenaPetCtrl::setPower(int curPower)
{
    if (curPower > m_byMaxPower) {
        curPower = m_byMaxPower;
        if (m_delegate) {
            FightPetSprite* sPet = m_delegate->getFightPetSprite(m_wBattleIndex);
            sPet->showAltEff();
        }
    }
    m_pSpriteSkillBar->setTextureRect(CCRectMake(0, 0, (float)curPower / m_byMaxPower * barPowerW, getHeight(m_pSpriteSkillBar)));
}






