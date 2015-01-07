/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-17 20:57:58
*/

#ifndef __CCBPETSHOWTITLE__H__
#define __CCBPETSHOWTITLE__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbPetIcon.h"
#include "Pet.h"
class CcbPetShowTitle:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetShowTitle()
	{
		m_pLabelTTFHp = NULL;
		m_pLabelTTFRec = NULL;
		m_pLabelTTFDef = NULL;
		m_pLabelTTFAtt = NULL;
		m_pLabelTTFSpeed = NULL;
		m_pLabelTTFCrit = NULL;
		m_pLabelTTFLv = NULL;
		m_pLayerPetIcon = NULL;
	}
	~CcbPetShowTitle();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetShowTitle, create);
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
	cocos2d::CCLabelTTF* m_pLabelTTFHp;
	cocos2d::CCLabelTTF* m_pLabelTTFRec;
	cocos2d::CCLabelTTF* m_pLabelTTFDef;
	cocos2d::CCLabelTTF* m_pLabelTTFAtt;
	cocos2d::CCLabelTTF* m_pLabelTTFSpeed;
	cocos2d::CCLabelTTF* m_pLabelTTFCrit;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
	CcbPetIcon* m_pLayerPetIcon;
    
//    float expBarWidth;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons

    void loadData(CPet *pPet);
    void loadTujianData(uint16 petId);
};

class CcbPetShowTitleLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetShowTitleLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetShowTitle);
};


#endif // __CCBPETSHOWTITLE__H__