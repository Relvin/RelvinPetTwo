#include "CcbPetBattleHpBarLayer.h"
//#include "CcbManager.h"
#include "FightAI.h"
#include "FightPet.h"
#include "UISupport.h"
#include "PetCtrl.h"
USING_NS_CC;
USING_NS_CC_EXT;

CcbPetBattleHpBarLayer::~CcbPetBattleHpBarLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteEnemyNature);
	CC_SAFE_RELEASE_NULL(m_pSpriteEnemyHpBar);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetBattleHpBarLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetBattleHpBarLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetBattleHpBarLayer", CcbPetBattleHpBarLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_hp_bar.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetBattleHpBarLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbPetBattleHpBarLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbPetBattleHpBarLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetBattleHpBarLayer::onExit()
{
	CCLayer::onExit();
}

void CcbPetBattleHpBarLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetBattleHpBarLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEnemyNature", CCSprite*, this->m_pSpriteEnemyNature);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEnemyHpBar", CCSprite*, this->m_pSpriteEnemyHpBar);

	return false;
}

bool CcbPetBattleHpBarLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetBattleHpBarLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetBattleHpBarLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetBattleHpBarLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetBattleHpBarLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_fightId = 0;
    m_MaxHp = UINT32_MAX;
    hpBarWidth = getWidth(m_pSpriteEnemyHpBar);
}

void CcbPetBattleHpBarLayer::loadData(uint16 fightId)
{
    if (fightId == m_fightId) {
        return;
    }
    m_fightId = fightId;
    FightPet* pet = FightAI::Get()->getFightPetByBIndex(m_fightId);
    if (!pet) {
        return;
    }
    
    m_MaxHp = pet->getPetInfo().wHP;
    int curHp = pet->getCurHP();
    float width = (float)curHp / m_MaxHp * hpBarWidth / m_pSpriteEnemyHpBar->getScaleX();
    
    //        CCString *str = CCString::createWithFormat("%d", hp);
    //        m_pLabelTTFEnemyMaxHP->setString(str->getCString());
    //        str->initWithFormat("%d", curHp);
    //        m_pLabelTTFEnemyCurHP->setString(str->getCString());
    
    
    m_pSpriteEnemyHpBar->setTextureRect(CCRectMake(0, 0, width, getHeight(m_pSpriteEnemyHpBar) / m_pSpriteEnemyHpBar->getScaleY()));
    
    //名字}
    //        m_pLabelTTFEnemyName->setString(pSprite->getPetName().c_str());
    //    imgAttribute = CCSprite::create(GET_PIC(PIC_attribute_mark));
    //属性}
    //        CCSpriteFrameCache::sharedSpriteFrameCache()
    //        ->addSpriteFramesWithFile("ccbresources/ui/interplay.plist");
    //        str->initWithFormat("interplay_%02d.png", pSprite->getPetNature());
    CCSpriteFrame *sf = CPetCtrl::Get()->GetPetNaturePicSF(pet->getPetInfo().wPetIndexId);
    //        m_pSpriteEnemyNature->initWithSpriteFrame(sf);
    m_pSpriteEnemyNature->setDisplayFrame(sf);
}

void CcbPetBattleHpBarLayer::setHp(uint32 hp)
{
    float width;

    width = (float)hp / m_MaxHp * hpBarWidth / m_pSpriteEnemyHpBar->getScaleX();

    m_pSpriteEnemyHpBar->setTextureRect(CCRectMake(0, 0, width, getHeight(m_pSpriteEnemyHpBar) / m_pSpriteEnemyHpBar->getScaleY()));
}





