/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-30 15:01:39
*/

#ifndef __CCBTEAMPOSITIONLAYER__H__
#define __CCBTEAMPOSITIONLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbTeamPositionLayer:
	public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
{
public:
	// Constructor
	CcbTeamPositionLayer()
	{
		m_pSpriteOn = NULL;
		m_pSpriteOff = NULL;
        texLight = NULL;
        texDark = NULL;
	}
	~CcbTeamPositionLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTeamPositionLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteOn;
	cocos2d::CCSprite* m_pSpriteOff;

    CCTexture2D* texLight;
    CCTexture2D* texDark;
    CCArray* m_pSprites;
    int m_curPos;
    int m_pMaxSize;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
    /**
     @brief 设置最大数量}
     */
    void SetCnt(int num);
    /**
     @brief 点亮第idx个位置点
     */
    void LightUpPos(int idx);
};

class CcbTeamPositionLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTeamPositionLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTeamPositionLayer);
};


#endif // __CCBTEAMPOSITIONLAYER__H__