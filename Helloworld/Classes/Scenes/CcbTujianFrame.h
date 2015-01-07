/**
* CcbTujianFrame.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-11 16:21:27
*/

#ifndef __CCBTUJIANFRAME__H__
#define __CCBTUJIANFRAME__H__

//CcbTujianFrame.h come from ccb/tujian_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"


class CcbTujianFrame:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbTujianFrame()
	{
		m_pSpriteLvStar = NULL;
		m_pLabelTTFGetCnt = NULL;
		m_pLayerBg = NULL;
        m_pScale9SpriteBg = NULL;

	}
	~CcbTujianFrame();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTujianFrame, create);
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
	cocos2d::CCSprite* m_pSpriteLvStar;
	cocos2d::CCLabelTTF* m_pLabelTTFGetCnt;
	cocos2d::CCLayer* m_pLayerBg;
    cocos2d::extension::CCScale9Sprite* m_pScale9SpriteBg;


    cocos2d::CCRect m_clipRect;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    uint16 loadData(std::vector<uint16> arrPetId);


    void setClipRect(cocos2d::CCRect rect){m_clipRect = rect;};

};

class CcbTujianFrameLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTujianFrameLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTujianFrame);
};


#endif // __CCBTUJIANFRAME__H__