/**
* CcbChallengeIndexLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-15 10:17:41
*/

#ifndef __CCBCHALLENGEINDEXLAYER__H__
#define __CCBCHALLENGEINDEXLAYER__H__

//CcbChallengeIndexLayer.h come from ccb/CcbChallengeIndexLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

class CcbChallengeIndexLayer;
class ChallengeIndexScene
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    ChallengeIndexScene();
    ~ChallengeIndexScene();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(ChallengeIndexScene);
    bool init();
    
    
    bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName) ;
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) ;
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
private:
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    CcbChallengeIndexLayer* m_pChildLayer;
};

class CcbChallengeIndexLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
    CcbChallengeIndexLayer();
	~CcbChallengeIndexLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengeIndexLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
public:
    // Attributes for CCB
    CCNode* m_pNodeCell;
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    cocos2d::CCLayer* m_pLayerPetChanllege;
    cocos2d::CCLayer* m_pLayerTower;
    cocos2d::CCLayer* m_pLayerYiji;
private:
    void addGuideLayer();
public:
	// Funcitons
    
    void setChallengeIndexInfo();
    void setLockStatusByNode(CCNode* pNode);


};

class CcbChallengeIndexLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengeIndexLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengeIndexLayer);
};


#endif // __CCBCHALLENGEINDEXLAYER__H__