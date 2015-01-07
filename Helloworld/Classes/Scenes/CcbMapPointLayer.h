/**
* CcbMapPointLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-09-29 18:08:46
*/

#ifndef __CCBMAPPOINTLAYER__H__
#define __CCBMAPPOINTLAYER__H__

//CcbMapPointLayer.h come from ccb/map_point.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CCScrollButton;
class CcbMapPointLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbMapPointLayer()
	{
		m_pControlButtonStage = NULL;
        m_pSpriteStar1 = NULL;
        m_pSpriteStar2 = NULL;
        m_pSpriteStar3 = NULL;
        m_pLabelTTFName = NULL;
        m_pLayerNew = NULL;
        m_pLayerClear = NULL;
	}
	~CcbMapPointLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbMapPointLayer, create);
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
	CCScrollButton* m_pControlButtonStage;
    cocos2d::CCSprite* m_pSpriteStar1;
    cocos2d::CCSprite* m_pSpriteStar2;
    cocos2d::CCSprite* m_pSpriteStar3;
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    CCLayer* m_pLayerNew;
    CCLayer* m_pLayerClear;

    uint8 m_byStatus;
    std::string m_strName;
    std::string m_strDes;
    std::string m_strTm;
    int m_nTag;

    cocos2d::CCSprite* m_pSpriteStars[3];
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
    void setMapPoint(
                     uint8 byStatus,
                     std::string strName,
                     std::string strDes,
                     std::string strTm,
                     int nTag
                     );
    void setMapNotOpen();
    void setMapStarCnt(int _cnt);
    void setMapClear();
    void setMapNew();
};

class CcbMapPointLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbMapPointLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbMapPointLayer);
};


#endif // __CCBMAPPOINTLAYER__H__