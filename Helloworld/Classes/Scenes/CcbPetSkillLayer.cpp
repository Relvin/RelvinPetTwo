#include "CcbPetSkillLayer.h"
#include "PetCtrl.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "CcbPetShowLayer.h"
#include "EquipDataMgr.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "EnumDefines.h"
#include "ResourceStringClient.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "ReRichText.h"
#include "TeamCtrl.h"
#include "ResourceDefine.h"
#include "PacketDataMgr.h"
#include "EmblemDataMgr.h"
#include "Emblem.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbPetSkillLayer::~CcbPetSkillLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerSkillBg);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNormal_AtkName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNor_SkillDes);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAltSkillDes);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAltSkillLv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAltSkillName);
    CC_SAFE_RELEASE_NULL(m_pLayerAltSkill);
    CC_SAFE_RELEASE_NULL(m_pScale9SpritePS_bg);
    CC_SAFE_RELEASE_NULL(m_pSprite_Jinjie);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillDes1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillEvoLv1);
    CC_SAFE_RELEASE_NULL(m_pLayerPSkill1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillDes2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillEvoLv2);
    CC_SAFE_RELEASE_NULL(m_pLayerPSkill2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillDes3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillEvoLv3);
    CC_SAFE_RELEASE_NULL(m_pLayerPSkill3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName4);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillDes4);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillEvoLv4);
    CC_SAFE_RELEASE_NULL(m_pLayerPSkill4);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName5);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillDes5);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillEvoLv5);
    CC_SAFE_RELEASE_NULL(m_pLayerPSkill5);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName6);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillDes6);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillEvoLv6);
    CC_SAFE_RELEASE_NULL(m_pLayerPSkill6);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName7);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillDes7);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillEvoLv7);
    CC_SAFE_RELEASE_NULL(m_pLayerPSkill7);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillName8);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillDes8);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPassiveSkillEvoLv8);
    CC_SAFE_RELEASE_NULL(m_pLayerPSkill8);
    CC_SAFE_RELEASE_NULL(m_pLayerPSkillBg);
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteSkill_bg);
    CC_SAFE_RELEASE_NULL(m_pSprite_JiNeng);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Lv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Evo);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Hp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Atk);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_CDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_SDef);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Rev);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Speed);
    CC_SAFE_RELEASE_NULL(m_pLabelTTF_Crit);
    CC_SAFE_RELEASE_NULL(m_pLayerInfoBg);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillDes);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillName);
    CC_SAFE_RELEASE_NULL(m_pLayerLeaderSkillBg);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPetDes);
    CC_SAFE_RELEASE_NULL(m_pLayerPetDes);
    
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteQY_bg);
    CC_SAFE_RELEASE_NULL(m_pSprite_Qingyuan);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFQYName1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFQYDes1);
    CC_SAFE_RELEASE_NULL(m_pLayerQYSkill1);
    CC_SAFE_RELEASE_NULL(m_pLayerQYBg);
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteEM_bg);
    CC_SAFE_RELEASE_NULL(m_pSprite_Emblem);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBadageName2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBadageDes2);
    CC_SAFE_RELEASE_NULL(m_pLayerEmSkill1);
    CC_SAFE_RELEASE_NULL(m_pLayerEmSkill2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBadageName1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBadageDes1);
    CC_SAFE_RELEASE_NULL(m_pLayerBadageBg);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetSkillLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetSkillLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetSkillLayer", CcbPetSkillLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow_skill.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetSkillLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbPetSkillLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbPetSkillLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetSkillLayer::onExit()
{
	CCLayer::onExit();
}

void CcbPetSkillLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetSkillLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerSkillBg", CCLayer*, this->m_pLayerSkillBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNormal_AtkName", CCLabelTTF*, this->m_pLabelTTFNormal_AtkName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNor_SkillDes", CCLabelTTF*, this->m_pLabelTTFNor_SkillDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAltSkillDes", CCLabelTTF*, this->m_pLabelTTFAltSkillDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAltSkillLv", CCLabelTTF*, this->m_pLabelTTFAltSkillLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAltSkillName", CCLabelTTF*, this->m_pLabelTTFAltSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerAltSkill", CCLayer*, this->m_pLayerAltSkill);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpritePS_bg", CCScale9Sprite*, this->m_pScale9SpritePS_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_Jinjie", CCSprite*, this->m_pSprite_Jinjie);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName1", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillDes1", CCLabelTTF*, this->m_pLabelTTFPassiveSkillDes1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillEvoLv1", CCLabelTTF*, this->m_pLabelTTFPassiveSkillEvoLv1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPSkill1", CCLayer*, this->m_pLayerPSkill1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName2", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillDes2", CCLabelTTF*, this->m_pLabelTTFPassiveSkillDes2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillEvoLv2", CCLabelTTF*, this->m_pLabelTTFPassiveSkillEvoLv2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPSkill2", CCLayer*, this->m_pLayerPSkill2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName3", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillDes3", CCLabelTTF*, this->m_pLabelTTFPassiveSkillDes3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillEvoLv3", CCLabelTTF*, this->m_pLabelTTFPassiveSkillEvoLv3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPSkill3", CCLayer*, this->m_pLayerPSkill3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName4", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillDes4", CCLabelTTF*, this->m_pLabelTTFPassiveSkillDes4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillEvoLv4", CCLabelTTF*, this->m_pLabelTTFPassiveSkillEvoLv4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPSkill4", CCLayer*, this->m_pLayerPSkill4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName5", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillDes5", CCLabelTTF*, this->m_pLabelTTFPassiveSkillDes5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillEvoLv5", CCLabelTTF*, this->m_pLabelTTFPassiveSkillEvoLv5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPSkill5", CCLayer*, this->m_pLayerPSkill5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName6", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName6);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillDes6", CCLabelTTF*, this->m_pLabelTTFPassiveSkillDes6);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillEvoLv6", CCLabelTTF*, this->m_pLabelTTFPassiveSkillEvoLv6);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPSkill7", CCLayer*, this->m_pLayerPSkill7);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName7", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName7);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillDes7", CCLabelTTF*, this->m_pLabelTTFPassiveSkillDes7);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillEvoLv7", CCLabelTTF*, this->m_pLabelTTFPassiveSkillEvoLv7);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPSkill8", CCLayer*, this->m_pLayerPSkill8);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillName8", CCLabelTTF*, this->m_pLabelTTFPassiveSkillName8);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillDes8", CCLabelTTF*, this->m_pLabelTTFPassiveSkillDes8);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPassiveSkillEvoLv8", CCLabelTTF*, this->m_pLabelTTFPassiveSkillEvoLv8);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPSkill6", CCLayer*, this->m_pLayerPSkill6);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPSkillBg", CCLayer*, this->m_pLayerPSkillBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteSkill_bg", CCScale9Sprite*, this->m_pScale9SpriteSkill_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_JiNeng", CCSprite*, this->m_pSprite_JiNeng);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Lv", CCLabelTTF*, this->m_pLabelTTF_Lv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Evo", CCLabelTTF*, this->m_pLabelTTF_Evo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Hp", CCLabelTTF*, this->m_pLabelTTF_Hp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Atk", CCLabelTTF*, this->m_pLabelTTF_Atk);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_CDef", CCLabelTTF*, this->m_pLabelTTF_CDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_SDef", CCLabelTTF*, this->m_pLabelTTF_SDef);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Rev", CCLabelTTF*, this->m_pLabelTTF_Rev);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Speed", CCLabelTTF*, this->m_pLabelTTF_Speed);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTF_Crit", CCLabelTTF*, this->m_pLabelTTF_Crit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInfoBg", CCLayer*, this->m_pLayerInfoBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillDes", CCLabelTTF*, this->m_pLabelTTFLeaderSkillDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillName", CCLabelTTF*, this->m_pLabelTTFLeaderSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerLeaderSkillBg", CCLayer*, this->m_pLayerLeaderSkillBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetDes", CCLabelTTF*, this->m_pLabelTTFPetDes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetDes", CCLayer*, this->m_pLayerPetDes);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteQY_bg", CCScale9Sprite*, this->m_pScale9SpriteQY_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_Qingyuan", CCSprite*, this->m_pSprite_Qingyuan);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFQYName1", CCLabelTTF*, this->m_pLabelTTFQYName1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFQYDes1", CCLabelTTF*, this->m_pLabelTTFQYDes1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerQYSkill1", CCLayer*, this->m_pLayerQYSkill1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerQYBg", CCLayer*, this->m_pLayerQYBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteEM_bg", CCScale9Sprite*, this->m_pScale9SpriteEM_bg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_Emblem", CCSprite*, this->m_pSprite_Emblem);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBadageName2", CCLabelTTF*, this->m_pLabelTTFBadageName2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBadageDes2", CCLabelTTF*, this->m_pLabelTTFBadageDes2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBadageName1", CCLabelTTF*, this->m_pLabelTTFBadageName1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBadageDes1", CCLabelTTF*, this->m_pLabelTTFBadageDes1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBadageBg", CCLayer*, this->m_pLayerBadageBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEmSkill1", CCLayer*, this->m_pLayerEmSkill1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEmSkill2", CCLayer*, this->m_pLayerEmSkill2);
    
	return false;
}

bool CcbPetSkillLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetSkillLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetSkillLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetSkillLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetSkillLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    arrPSkill[0] = m_pLayerPSkill1;
    arrPSkill[1] = m_pLayerPSkill2;
    arrPSkill[2] = m_pLayerPSkill3;
    arrPSkill[3] = m_pLayerPSkill4;
    arrPSkill[4] = m_pLayerPSkill5;
    arrPSkill[5] = m_pLayerPSkill6;
    arrPSkill[6] = m_pLayerPSkill7;
    arrPSkill[7] = m_pLayerPSkill8;
    
    arrPSkillName[0] = m_pLabelTTFPassiveSkillName1;
    arrPSkillName[1] = m_pLabelTTFPassiveSkillName2;
    arrPSkillName[2] = m_pLabelTTFPassiveSkillName3;
    arrPSkillName[3] = m_pLabelTTFPassiveSkillName4;
    arrPSkillName[4] = m_pLabelTTFPassiveSkillName5;
    arrPSkillName[5] = m_pLabelTTFPassiveSkillName6;
    arrPSkillName[6] = m_pLabelTTFPassiveSkillName7;
    arrPSkillName[7] = m_pLabelTTFPassiveSkillName8;
    
    arrPSkillDes[0] = m_pLabelTTFPassiveSkillDes1;
    arrPSkillDes[1] = m_pLabelTTFPassiveSkillDes2;
    arrPSkillDes[2] = m_pLabelTTFPassiveSkillDes3;
    arrPSkillDes[3] = m_pLabelTTFPassiveSkillDes4;
    arrPSkillDes[4] = m_pLabelTTFPassiveSkillDes5;
    arrPSkillDes[5] = m_pLabelTTFPassiveSkillDes6;
    arrPSkillDes[6] = m_pLabelTTFPassiveSkillDes7;
    arrPSkillDes[7] = m_pLabelTTFPassiveSkillDes8;
    
    arrPSkillEvo[0] = m_pLabelTTFPassiveSkillEvoLv1;
    arrPSkillEvo[1] = m_pLabelTTFPassiveSkillEvoLv2;
    arrPSkillEvo[2] = m_pLabelTTFPassiveSkillEvoLv3;
    arrPSkillEvo[3] = m_pLabelTTFPassiveSkillEvoLv4;
    arrPSkillEvo[4] = m_pLabelTTFPassiveSkillEvoLv5;
    arrPSkillEvo[5] = m_pLabelTTFPassiveSkillEvoLv6;
    arrPSkillEvo[6] = m_pLabelTTFPassiveSkillEvoLv7;
    arrPSkillEvo[7] = m_pLabelTTFPassiveSkillEvoLv8;
    
    arrEmblemName[0] = m_pLabelTTFBadageName1;
    arrEmblemName[1] = m_pLabelTTFBadageName2;
    
    arrEmblemDes[0] = m_pLabelTTFBadageDes1;
    arrEmblemDes[1] = m_pLabelTTFBadageDes2;
    
    arrEmSkill[0] = m_pLayerEmSkill1;
    arrEmSkill[1] = m_pLayerEmSkill2;
    
    
    m_richSkillDes = ReRichText::create();
    m_richSkillDes->setFontName(m_pLabelTTFAltSkillDes->getFontName());
    m_richSkillDes->setFontSize(m_pLabelTTFAltSkillDes->getFontSize());
    m_richSkillDes->setColor(m_pLabelTTFAltSkillDes->getColor());
//    m_richSkillDes->setSize(m_pLabelTTFAltSkillDes->getDimensions());
//    m_richSkillDes->ignoreContentAdaptWithSize(false);
    m_richSkillDes->ignoreAnchorPointForPosition(false);
    m_richSkillDes->setAnchorPoint(m_pLabelTTFAltSkillDes->getAnchorPoint());
    m_richSkillDes->setPosition(m_pLabelTTFAltSkillDes->getPosition());
    m_pLabelTTFAltSkillDes->getParent()->addChild(m_richSkillDes);
    
    
    
    m_richNorDes = ReRichText::create();
    m_richNorDes->setFontName(m_pLabelTTFNor_SkillDes->getFontName());
    m_richNorDes->setFontSize(m_pLabelTTFNor_SkillDes->getFontSize());
//    m_richNorDes->setSize(m_pLabelTTFNor_SkillDes->getDimensions());
//    m_richNorDes->ignoreContentAdaptWithSize(false);
    m_richNorDes->ignoreAnchorPointForPosition(false);
    m_richNorDes->setAnchorPoint(m_pLabelTTFNor_SkillDes->getAnchorPoint());
    m_richNorDes->setColor(m_pLabelTTFNor_SkillDes->getColor());
    m_richNorDes->setPosition(m_pLabelTTFNor_SkillDes->getPosition());
    m_pLabelTTFNor_SkillDes->getParent()->addChild(m_richNorDes);
    
    m_pLabelTTFAltSkillDes->setVisible(false);
    m_pLabelTTFNor_SkillDes->setVisible(false);
}

void CcbPetSkillLayer::loadDataPet(CPet *pet)
{
    if (!pet) {
        return;
    }

    if(!CPetCtrl::Get()->getIsFirendLook() && CTeamCtrl::getSiteByPetId(pet->GetObjId()))
    {
        loadData(pet->GetwIndex(), pet->GetbyEvolveLv(), pet->GetbyInitialSkillLv(), true, pet->GetObjId());
    }
    else{
        loadData(pet->GetwIndex(), pet->GetbyEvolveLv(), pet->GetbyInitialSkillLv(), false, pet->GetObjId());
    }
    
    //属性
    CCString*str = CCString::createWithFormat("%d", pet->GetbyLv());
    //Lv
    m_pLabelTTF_Lv->setString(str->getCString());
    //evoLv
    str->initWithFormat("%d", pet->GetbyEvolveLv());
    m_pLabelTTF_Evo->setString(str->getCString());
    //HP
    str->initWithFormat("%d", pet->GetdwHpValue());
    m_pLabelTTF_Hp->setString(str->getCString());
    //Rev
    str->initWithFormat("%d", pet->GetdwRecoverValue());
    m_pLabelTTF_Rev->setString(str->getCString());
    //Atk
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *norCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->GetwNormaleAttId());
    if (norCfg&& norCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
        str->initWithFormat("%d", pet->GetdwSAttackValue());
    }
    else{
        str->initWithFormat("%d", pet->GetdwAttackValue());
    }
    
    m_pLabelTTF_Atk->setString(str->getCString());
    //Crit
    str->initWithFormat("%d%%", pet->GetdwCritRateValue() / 100);
    m_pLabelTTF_Crit->setString(str->getCString());
    //CDef
    str->initWithFormat("%d", pet->GetdwDefenseValue());
    m_pLabelTTF_CDef->setString(str->getCString());
    //SDef
    str->initWithFormat("%d", pet->GetdwSDefenseValue());
    m_pLabelTTF_SDef->setString(str->getCString());
    //speed
    str->initWithFormat("%d", pet->GetdwSpeedValue());
    m_pLabelTTF_Speed->setString(str->getCString());
}

void CcbPetSkillLayer::loadTujianData(uint32 petId)
{
    loadData(petId, 0, 1);
    PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, petId);
    //属性
    CCString*str = CCString::createWithFormat("%d", 1);
    //Lv
    m_pLabelTTF_Lv->setString(str->getCString());
    //evoLv
    str->initWithFormat("%d", 0);
    m_pLabelTTF_Evo->setString(str->getCString());
    //HP
    str->initWithFormat("%d", pCfg->dwHpValue);
    m_pLabelTTF_Hp->setString(str->getCString());
    //Rev
    str->initWithFormat("%d", pCfg->dwRecoverValue);
    m_pLabelTTF_Rev->setString(str->getCString());
    //Atk
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *norCfg = GET_CONFIG_STC(UltimateSkillConfig, pCfg->dwNomaleAttId);
    if (norCfg&& norCfg->byHurtType == E_SPELL_HURT_SPE_ATK) {
        str->initWithFormat("%d", pCfg->dwSAttackValue);
    }
    else{
        str->initWithFormat("%d", pCfg->dwAttackValue);
    }
    
    m_pLabelTTF_Atk->setString(str->getCString());
    //Crit
    str->initWithFormat("%d%%", pCfg->dwLuckValue / 100);
    m_pLabelTTF_Crit->setString(str->getCString());
    //CDef
    str->initWithFormat("%d", pCfg->dwDeffenseValue);
    m_pLabelTTF_CDef->setString(str->getCString());
    //SDef
    str->initWithFormat("%d", pCfg->dwSDeffenseValue);
    m_pLabelTTF_SDef->setString(str->getCString());
    //speed
    str->initWithFormat("%d", pCfg->dwSpeedValue);
    m_pLabelTTF_Speed->setString(str->getCString());
}


void CcbPetSkillLayer::loadData(uint32 petId, uint8 evoLv, uint8 skillLv, bool checkQy, uint32 petObjId)
{
    allHeight = 0;
    PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, petId);
    CCString* str = CCString::create("");
    //属性
    allHeight += getHeight(m_pLayerInfoBg);
    
    //情缘
    m_pLayerQYSkill1->setVisible(false);
    float qyH = 5;
    const ccColor3B ccGreen={0,117,49};
    const ccColor3B ccGray={74,74,74};
    const ccColor3B ccRed={143,0,0};
    for (int i = 3; i >= 0; i--) {
        uint32 qyId = pCfg->arrQyIndex[i];
        if (!qyId) {
            continue;
        }
        QingYuanConfig::STC_QING_YUAN_CONFIG* qyCfg = GET_CONFIG_STC(QingYuanConfig, qyId);
        if (!qyCfg) {
            continue;
        }
        CCLayer * qyBg = CCLayer::create();
        qyBg->ignoreAnchorPointForPosition(false);
        qyBg->setAnchorPoint(m_pLayerQYSkill1->getAnchorPoint());
        
        CCLabelTTF* lblName = CCLabelTTF::create(qyCfg->strName.c_str(), m_pLabelTTFQYName1->getFontName(), m_pLabelTTFQYName1->getFontSize());
        lblName->setColor(m_pLabelTTFQYName1->getColor());
        lblName->setAnchorPoint(m_pLabelTTFQYName1->getAnchorPoint());
        lblName->setPositionX(m_pLabelTTFQYName1->getPositionX());
        qyBg->addChild(lblName);
        
        ReRichText* lblDes = ReRichText::create("",m_pLabelTTFQYDes1->getFontName(), m_pLabelTTFQYDes1->getFontSize(), CCSize(245, 0), kCCTextAlignmentLeft);
        lblDes->setColor(m_pLabelTTFQYDes1->getColor());
        lblDes->ignoreAnchorPointForPosition(false);
        lblDes->setAnchorPoint(m_pLabelTTFQYDes1->getAnchorPoint());
        lblDes->setPosition(m_pLabelTTFQYDes1->getPosition());
        lblDes->setPositionX(m_pLabelTTFQYDes1->getPositionX());

        qyBg->addChild(lblDes);
        
        std::vector<uint8> arrQyCheck;
        arrQyCheck.push_back(0);
        arrQyCheck.push_back(0);
        arrQyCheck.push_back(0);
        arrQyCheck.push_back(0);
        
        bool isAct = true;
        
        if (checkQy) {
            arrQyCheck = CPetCtrl::Get()->checkQingyuan(qyId);
        }
        str->initWithFormat("与");
        int qyCnt = 0;
        for (int q = 0; q < 4; q++) {
            if (!qyCfg->dwQyPetGroup[q] || qyCfg->dwQyPetGroup[q] == pCfg->wGroupId) {
                continue;
            }
            std::string s = str->getCString();
            if (qyCnt > 0) {
                s += "、";
            }
//            if (checkQy) {
                if (arrQyCheck[q]) {
                    str->initWithFormat("%s|cFF8F0000%s|r", s.c_str(), qyCfg->strPetName[q].c_str());
                }
                else{
                    
                    isAct = false;
                    str->initWithFormat("%s|cFF4a4a4a%s|r", s.c_str(), qyCfg->strPetName[q].c_str());
                }
//            }
//            else{
//                str->initWithFormat("%s%s", s.c_str(), qyCfg->strPetName[q].c_str());
//            }
            
            qyCnt++;
        }
        std::string s = str->getCString();
        str->initWithFormat("%s一起上阵时，%s提升%d%%", s.c_str(), g_PacketDataMgr->getAttrText(qyCfg->dwAttType).c_str(), qyCfg->dwAttValue / 100);
        
        lblDes->setString(str->getCString());
        qyBg->setContentSize(CCSizeMake(getWidth(m_pLayerQYSkill1), MAX(20, getHeight(lblDes))));
        lblName->setPositionY(getHeight(qyBg));
        lblDes->setPositionY(getHeight(qyBg));
        
        if (petObjId) {
            if (isAct) {
                lblName->setColor(ccGreen);
                lblDes->setColor(ccRed);
            }
            else{
                lblName->setColor(ccGray);
                lblDes->setColor(ccGray);
            }
        }

        qyBg->setPosition(0, qyH);
        qyH += getHeight(qyBg);
        m_pLayerQYBg->addChild(qyBg);
    }

    if (qyH == 5) {
        m_pLayerQYBg->setVisible(false);
    }
    else{
        qyH += 25;
        m_pScale9SpriteQY_bg->setPreferredSize(CCSizeMake(getWidth(m_pLayerQYBg), qyH - 10));
        m_pSprite_Qingyuan->setPositionY(qyH);
        allHeight += qyH;
        m_pLayerQYBg->setContentSize(CCSizeMake(getWidth(m_pLayerQYBg), qyH));
    }
    
    
    
    //专属徽章
    EmblemShowConfig::STC_EMBLEM_SHOW_CONFIG* emScfg = GET_CONFIG_STC(EmblemShowConfig, pCfg->wGroupId);
    if (!emScfg) {
        m_pLayerBadageBg->setVisible(false);
    }
    else{
        uint32 emId1 = 0;
        uint32 emId2 = 0;
        
        CPet* pet = NULL;
        if (petObjId) {
            pet = CPetCtrl::Get()->GetPetByObjId(petObjId);
        }
        if (pet) {
            CEmblem* emblem1 = g_EmblemData->getEmblemByObjId(pet->GetdwEmblemId1());
            CEmblem* emblem2 = g_EmblemData->getEmblemByObjId(pet->GetdwEmblemId2());
            
            if (emblem1) {
                emId1 = emblem1->getdwIndexId();
            }
            if (emblem2) {
                emId2 = emblem2->getdwIndexId();
            }
        }
        
        
        int emCnt = 0;
        for (int i = 0; i < 2; i++) {
            uint32 emId = emScfg->wExcEmIndex[i];
            if (!emId) {
                continue;
            }
            EmblemConfig::STC_EMBLEM_CONFIG* emCfg = GET_CONFIG_STC(EmblemConfig, emId);
            if (!emCfg) {
                continue;
            }
            arrEmblemName[emCnt]->setString(emScfg->strName[i].c_str());
            str->initWithFormat("佩戴 %s 时，%s提升%d%%", emCfg->strName.c_str(), g_PacketDataMgr->getAttrText(emScfg->byExcAttr[i]).c_str(), emScfg->dwExcAttrValue[i] / 100);
            arrEmblemDes[emCnt]->setString(str->getCString());
                        
            if (pet) {
                if (emId == emId1
                    || emId == emId2) {
                    arrEmblemName[emCnt]->setColor(ccGreen);
                    arrEmblemDes[emCnt]->setColor(ccRed);
                }
                else{
                    arrEmblemName[emCnt]->setColor(ccGray);
                    arrEmblemDes[emCnt]->setColor(ccGray);
                }
            }
            emCnt++;
        }
        
        if (emCnt == 0) {
            m_pLayerBadageBg->setVisible(false);
        }
        else{
            for(int i = 0; i < 2; i++)
            {
                arrEmSkill[i]->setVisible(i < emCnt);
                arrEmSkill[i]->setPositionY(5 + (emCnt - i - 1) * getHeight(arrEmSkill[i]));
            }
            
            float ph = getHeight(m_pLayerBadageBg) - getHeight(m_pLayerEmSkill1)*(2-emCnt);//减去不显示的被动技能的高度}
            m_pScale9SpriteEM_bg->setPreferredSize(CCSizeMake(getWidth(m_pLayerBadageBg), ph - 10));
            m_pSprite_Emblem->setPositionY(ph);
            allHeight += ph;
            m_pLayerBadageBg->setContentSize(CCSizeMake(getWidth(m_pLayerBadageBg), ph));
            m_pLayerBadageBg->setVisible(true);
            m_pScale9SpriteEM_bg->setVisible(true);
        }
    }
    
    //进阶技能
    uint16 eLv = 0;
    //1、找出当前index对应的最小阶}
    while (true) {
        EvolveConfig::STC_EVOLVE_CONFIG* eCfg = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(petId, eLv));
        if (eCfg || eLv > 20) {
            break;
        }
        eLv++;
    }
    //2、找到基础index}
    uint16 baseId = 0;
    EvolveConfig::STC_EVOLVE_CONFIG* eCfg = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(petId, eLv));
    if (eCfg) {
        baseId = eCfg->wBasePetId;
    }
    //3、从0阶开始查找}
    uint32 nextEvoId = GET_EVOLVE_ID(baseId, 0);
    uint8 cnt = 0;
    
    while (true) {
        EvolveConfig::STC_EVOLVE_CONFIG* eCfg = GET_CONFIG_STC(EvolveConfig, nextEvoId);
        if (!eCfg) {
            break;
        }
        nextEvoId = eCfg->wNextId;
        uint32 skillId = eCfg->dwAddSkillId1;// + eCfg->dwAddSkillId2;//技能1和技能2不同时出现}
        if (!skillId) {
            continue;
        }
        cnt++;
        setPassSkill(skillId, cnt);
        
        if (eCfg->byLv > evoLv) {
            arrPSkillEvo[cnt - 1]->setVisible(true);
            arrPSkillEvo[cnt - 1]->setColor(ccRed);
            arrPSkillName[cnt - 1]->setColor(ccGray);
            arrPSkillDes[cnt - 1]->setColor(ccGray);
            str->initWithFormat(GET_STR(Str_evo_unlock), eCfg->byLv);
            arrPSkillEvo[cnt - 1]->setString(str->getCString());
        }
        else{
            arrPSkillName[cnt - 1]->setColor(ccGreen);
            arrPSkillDes[cnt - 1]->setColor(ccGreen);
        }
        
    }
    
    if (cnt == 0) {
        m_pLayerPSkillBg->setVisible(false);
        m_pScale9SpritePS_bg->setVisible(false);
    }
    else
    {
        for(int i = 0; i < 8; i++)
        {
            arrPSkill[i]->setVisible(i < cnt);
            arrPSkill[i]->setPositionY(5 + (cnt - i - 1) * getHeight(arrPSkill[i]));
        }
        
        float ph = getHeight(m_pLayerPSkillBg) - getHeight(m_pLayerPSkill1)*(8-cnt);//减去不显示的被动技能的高度}
        m_pScale9SpritePS_bg->setPreferredSize(CCSizeMake(getWidth(m_pLayerPSkillBg), ph - 10));
        m_pSprite_Jinjie->setPositionY(ph);
        allHeight += ph;
        m_pLayerPSkillBg->setContentSize(CCSizeMake(getWidth(m_pLayerPSkillBg), ph));
        m_pLayerPSkillBg->setVisible(true);
        m_pScale9SpritePS_bg->setVisible(true);
    }
    
    //主动技能和普通技能}
//    allHeight += getHeight(m_pLayerAltSkill);
    //主动}
    float uH = getHeight(m_pLayerAltSkill);
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pCfg->wInitialSkillId);
    if (ultCfg) {
        m_pLabelTTFAltSkillName->getParent()->setVisible(true);
        m_pLabelTTFAltSkillName->setString(ultCfg->strName.c_str());
        const char* des = PARSE_STRING1(ultCfg->strDes, ultCfg->dwSkillAbi / 100);
        m_richSkillDes->setString(des);
        str->initWithFormat("%s%d", SB_Lv,skillLv);
        m_pLabelTTFAltSkillLv->setString(str->getCString());
        m_pLabelTTFAltSkillLv->setPositionX(getRight(m_pLabelTTFAltSkillName) + 10);
    }
    else
    {
        uH -= getHeight(m_pLabelTTFAltSkillName->getParent());
        m_pLabelTTFAltSkillName->getParent()->setVisible(false);
    }
    //普通
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *norCfg = GET_CONFIG_STC(UltimateSkillConfig, pCfg->dwNomaleAttId);
    if (norCfg) {
        if (!ultCfg) {
            m_pLabelTTFNormal_AtkName->getParent()->setPositionY(5);
        }
        m_pLabelTTFNormal_AtkName->getParent()->setVisible(true);
        m_pLabelTTFNormal_AtkName->setString(norCfg->strName.c_str());
        
        const char* des = PARSE_STRING1(norCfg->strDes, norCfg->dwSkillAbi / 100);        
        m_richNorDes->setString(des);
//        str->initWithFormat("Lv.%d", 1);
//        m_pLabelTTFNor_SkillDes->setString(str->getCString());
//        m_pLabelTTFAltSkillLv->setPositionX(getRight(m_pLabelTTFAltSkillName) + 10);
    }
    else
    {
        uH -= getHeight(m_pLabelTTFNormal_AtkName->getParent());
        m_pLabelTTFNormal_AtkName->getParent()->setVisible(false);
    }
    if (!norCfg && !ultCfg) {
        uH = 0;
        m_pLayerAltSkill->setVisible(false);
    }
    else{
        m_pScale9SpriteSkill_bg->setPreferredSize(CCSizeMake(getWidth(m_pLayerPSkillBg), uH - 10));
        m_pSprite_JiNeng->setPositionY(uH);
        m_pLayerAltSkill->setContentSize(CCSizeMake(getWidth(m_pLayerAltSkill), uH));
    }
    allHeight += uH;
    
    //队长}
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG *lCfg = GET_CONFIG_STC(LeaderSkillConfig, pCfg->wLeaderSkillId);
    if (lCfg) {
        allHeight += getHeight(m_pLayerLeaderSkillBg);
        m_pLayerLeaderSkillBg->setVisible(true);
        m_pLabelTTFLeaderSkillName->setString(lCfg->strName.c_str());
        m_pLabelTTFLeaderSkillDes->setString(lCfg->strDes.c_str());
    }
    else
    {
        m_pLayerLeaderSkillBg->setVisible(false);
    }
    
    //描述}
    if (pCfg) {
        allHeight += getHeight(m_pLayerPetDes);
        m_pLayerPetDes->setVisible(true);
        m_pLabelTTFPetDes->setString(pCfg->strDes.c_str());
    }
    else{
        m_pLayerPetDes->setVisible(false);
    }
    reloadPos();
}

void CcbPetSkillLayer::setPassSkill(uint32 skillId, uint8 site)
{
    string name = "";
    string des = "";
    if (skillId / E_UNITE_BASE_FABIO == E_SKILL_TYPE_PASSIVE) {
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *cfg = GET_CONFIG_STC(PassiveSkillConfig, skillId);
        if (cfg) {
            name = cfg->strName;
            des = cfg->strDes;
        }
    }
    else
    {
        TalentConfig::STC_TALENT_CONFIG *cfg = GET_CONFIG_STC(TalentConfig, skillId);
        if (cfg) {
            name = cfg->strName;
            des = cfg->strDes;
        }
    }
    

    arrPSkillName[site - 1]->setString(name.c_str());
    
    arrPSkillEvo[site - 1]->setString("");
    arrPSkillDes[site - 1]->setString(des.c_str());
}

void CcbPetSkillLayer::reloadPos()
{
    std::vector<CCNode*> arrBg;
    arrBg.push_back(m_pLayerPetDes);
    arrBg.push_back(m_pLayerLeaderSkillBg);
    arrBg.push_back(m_pLayerAltSkill);
    arrBg.push_back(m_pLayerPSkillBg);
    arrBg.push_back(m_pLayerBadageBg);
    arrBg.push_back(m_pLayerQYBg);
    arrBg.push_back(m_pLayerInfoBg);
    
    
    float h = getBottom(m_pLayerPetDes);
    for (int i = 0; i < arrBg.size(); i++) {
        CCNode* bg = arrBg[i];
        if (bg->isVisible()) {
            bg->setPositionY(h);
            h += getHeight(bg);
        }
    }
    
    this->setContentSize(CCSizeMake(getWidth(this), allHeight));
}


