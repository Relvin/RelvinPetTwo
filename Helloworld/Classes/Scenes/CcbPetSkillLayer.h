/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-06 16:15:58
*/

#ifndef __CCBPETSKILLLAYER__H__
#define __CCBPETSKILLLAYER__H__

//CcbPetSkillLayer.h come from ccb/petshow_skill.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "Equip.h"
#include "Pet.h"

class ReRichText;

class CcbPetSkillLayer:
	public cocos2d::CCLayerRGBA,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
    enum E_SHOW_SKILL_TYPE
    {
        E_SHOW_SKILL_TYPE_PASSIVE = 1,
        E_SHOW_SKILL_TYPE_TALENT = 2,
        E_SHOW_SKILL_TYPE_ULTIMATE = 3,
        E_SHOW_SKILL_TYPE_LEADER = 4,
        E_SHOW_SKILL_TYPE_DES = 5,
    };
    
	// Constructor
	CcbPetSkillLayer()
	{
        m_pLayerSkillBg = NULL;
        m_pLabelTTFAltSkillName = NULL;
        m_pLabelTTFAltSkillDes = NULL;
        m_pLabelTTFAltSkillLv = NULL;
        m_pLabelTTFNormal_AtkName = NULL;
        m_pLabelTTFNor_SkillDes = NULL;
        m_pLayerAltSkill = NULL;
        m_pScale9SpritePS_bg = NULL;
        m_pSprite_Jinjie = NULL;
        m_pLabelTTFPassiveSkillName1 = NULL;
        m_pLabelTTFPassiveSkillDes1 = NULL;
        m_pLabelTTFPassiveSkillEvoLv1 = NULL;
        m_pLayerPSkill1 = NULL;
        m_pLabelTTFPassiveSkillName2 = NULL;
        m_pLabelTTFPassiveSkillDes2 = NULL;
        m_pLabelTTFPassiveSkillEvoLv2 = NULL;
        m_pLayerPSkill2 = NULL;
        m_pLabelTTFPassiveSkillName3 = NULL;
        m_pLabelTTFPassiveSkillDes3 = NULL;
        m_pLabelTTFPassiveSkillEvoLv3 = NULL;
        m_pLayerPSkill3 = NULL;
        m_pLabelTTFPassiveSkillName4 = NULL;
        m_pLabelTTFPassiveSkillDes4 = NULL;
        m_pLabelTTFPassiveSkillEvoLv4 = NULL;
        m_pLayerPSkill4 = NULL;
        m_pLabelTTFPassiveSkillName5 = NULL;
        m_pLabelTTFPassiveSkillDes5 = NULL;
        m_pLabelTTFPassiveSkillEvoLv5 = NULL;
        m_pLayerPSkill5 = NULL;
        m_pLabelTTFPassiveSkillName6 = NULL;
        m_pLabelTTFPassiveSkillDes6 = NULL;
        m_pLabelTTFPassiveSkillEvoLv6 = NULL;
        m_pLayerPSkill6 = NULL;
        
        m_pLabelTTFPassiveSkillName7 = NULL;
        m_pLabelTTFPassiveSkillDes7 = NULL;
        m_pLabelTTFPassiveSkillEvoLv7 = NULL;
        m_pLayerPSkill7 = NULL;
        
        m_pLabelTTFPassiveSkillName8 = NULL;
        m_pLabelTTFPassiveSkillDes8 = NULL;
        m_pLabelTTFPassiveSkillEvoLv8 = NULL;
        m_pLayerPSkill8 = NULL;
        
        m_pLayerPSkillBg = NULL;
        m_pScale9SpriteSkill_bg = NULL;
        m_pSprite_JiNeng = NULL;
        m_pLabelTTF_Lv = NULL;
        m_pLabelTTF_Evo = NULL;
        m_pLabelTTF_Hp = NULL;
        m_pLabelTTF_Atk = NULL;
        m_pLabelTTF_CDef = NULL;
        m_pLabelTTF_SDef = NULL;
        m_pLabelTTF_Rev = NULL;
        m_pLabelTTF_Speed = NULL;
        m_pLabelTTF_Crit = NULL;
        m_pLayerInfoBg = NULL;
        m_pLabelTTFLeaderSkillDes = NULL;
        m_pLabelTTFLeaderSkillName = NULL;
        m_pLayerLeaderSkillBg = NULL;
        m_pLabelTTFPetDes = NULL;
        m_pLayerPetDes = NULL;
        
        m_pScale9SpriteQY_bg = NULL;
        m_pSprite_Qingyuan = NULL;
        m_pLabelTTFQYName1 = NULL;
        m_pLabelTTFQYDes1 = NULL;
        m_pLayerQYSkill1 = NULL;
        m_pLayerQYBg = NULL;
        m_pScale9SpriteEM_bg = NULL;
        m_pSprite_Emblem = NULL;
        m_pLabelTTFBadageName2 = NULL;
        m_pLabelTTFBadageDes2 = NULL;
        m_pLayerEmSkill2 = NULL;
        m_pLayerEmSkill1 = NULL;
        m_pLabelTTFBadageName1 = NULL;
        m_pLabelTTFBadageDes1 = NULL;
        m_pLayerBadageBg = NULL;
	}
	~CcbPetSkillLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetSkillLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerSkillBg;
    cocos2d::CCLabelTTF* m_pLabelTTFAltSkillName;
    cocos2d::CCLabelTTF* m_pLabelTTFAltSkillDes;
    cocos2d::CCLabelTTF* m_pLabelTTFAltSkillLv;
    cocos2d::CCLabelTTF* m_pLabelTTFNormal_AtkName;
    cocos2d::CCLabelTTF* m_pLabelTTFNor_SkillDes;
    
    cocos2d::CCLayer* m_pLayerAltSkill;
    cocos2d::extension::CCScale9Sprite* m_pScale9SpritePS_bg;
    cocos2d::CCSprite* m_pSprite_Jinjie;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName1;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillDes1;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillEvoLv1;
    cocos2d::CCLayer* m_pLayerPSkill1;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName2;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillDes2;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillEvoLv2;
    cocos2d::CCLayer* m_pLayerPSkill2;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName3;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillDes3;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillEvoLv3;
    cocos2d::CCLayer* m_pLayerPSkill3;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName4;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillDes4;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillEvoLv4;
    cocos2d::CCLayer* m_pLayerPSkill4;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName5;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillDes5;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillEvoLv5;
    cocos2d::CCLayer* m_pLayerPSkill5;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName6;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillDes6;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillEvoLv6;
    cocos2d::CCLayer* m_pLayerPSkill6;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName7;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillDes7;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillEvoLv7;
    cocos2d::CCLayer* m_pLayerPSkill7;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName8;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillDes8;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillEvoLv8;
    cocos2d::CCLayer* m_pLayerPSkill8;
    
    cocos2d::CCLayer* m_pLayerPSkillBg;
    cocos2d::extension::CCScale9Sprite* m_pScale9SpriteSkill_bg;
    cocos2d::CCSprite* m_pSprite_JiNeng;
    cocos2d::CCLabelTTF* m_pLabelTTF_Lv;
    cocos2d::CCLabelTTF* m_pLabelTTF_Evo;
    cocos2d::CCLabelTTF* m_pLabelTTF_Hp;
    cocos2d::CCLabelTTF* m_pLabelTTF_Atk;
    cocos2d::CCLabelTTF* m_pLabelTTF_CDef;
    cocos2d::CCLabelTTF* m_pLabelTTF_SDef;
    cocos2d::CCLabelTTF* m_pLabelTTF_Rev;
    cocos2d::CCLabelTTF* m_pLabelTTF_Speed;
    cocos2d::CCLabelTTF* m_pLabelTTF_Crit;
    cocos2d::CCLayer* m_pLayerInfoBg;
    cocos2d::CCLabelTTF* m_pLabelTTFLeaderSkillDes;
    cocos2d::CCLabelTTF* m_pLabelTTFLeaderSkillName;
    cocos2d::CCLayer* m_pLayerLeaderSkillBg;
    cocos2d::CCLabelTTF* m_pLabelTTFPetDes;
    cocos2d::CCLayer* m_pLayerPetDes;
    
    cocos2d::extension::CCScale9Sprite* m_pScale9SpriteQY_bg;
    cocos2d::CCSprite* m_pSprite_Qingyuan;
    cocos2d::CCLabelTTF* m_pLabelTTFQYName1;
    cocos2d::CCLabelTTF* m_pLabelTTFQYDes1;
    cocos2d::CCLayer* m_pLayerQYSkill1;
    cocos2d::CCLayer* m_pLayerQYBg;
    cocos2d::extension::CCScale9Sprite* m_pScale9SpriteEM_bg;
    cocos2d::CCSprite* m_pSprite_Emblem;
    cocos2d::CCLabelTTF* m_pLabelTTFBadageName2;
    cocos2d::CCLabelTTF* m_pLabelTTFBadageDes2;
    cocos2d::CCLabelTTF* m_pLabelTTFBadageName1;
    cocos2d::CCLabelTTF* m_pLabelTTFBadageDes1;
    cocos2d::CCLayer* m_pLayerEmSkill1;
    cocos2d::CCLayer* m_pLayerEmSkill2;
    cocos2d::CCLayer* m_pLayerBadageBg;
    
    ReRichText* m_richSkillDes;
    ReRichText* m_richNorDes;
    
    float allHeight;
    
    cocos2d::CCLayer* arrPSkill[8];
    cocos2d::CCLabelTTF* arrPSkillName[8];
    cocos2d::CCLabelTTF* arrPSkillDes[8];
    cocos2d::CCLabelTTF* arrPSkillEvo[8];
    
    cocos2d::CCLayer* arrEmSkill[2];
    cocos2d::CCLabelTTF* arrEmblemName[2];
    cocos2d::CCLabelTTF* arrEmblemDes[2];
    
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
    
    
    void loadTujianData(uint32 dwPetId);
    void loadDataPet(CPet *pet);

    float getAllHeight(){return allHeight;};

private:
    void loadData(uint32 dwPetId, uint8 evoLv, uint8 skillLv, bool checkQy = false, uint32 petObjId = 0);
    
    void setPassSkill(uint32 skillId, uint8 site);
    void reloadPos();
};

class CcbPetSkillLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetSkillLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetSkillLayer);
};


#endif // __CCBPETSKILLLAYER__H__