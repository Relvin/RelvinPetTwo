/**
* CcbChoosePetLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-25 11:46:04
*/

#ifndef __CCBCHOOSEPETLAYER__H__
#define __CCBCHOOSEPETLAYER__H__

//CcbChoosePetLayer.h come from ccb/CcbChoosePetLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

#pragma mark ChoosePetScene
class ChoosePetScene : public cocos2d::CCLayer {
    
public:
    ChoosePetScene() {}
    ~ChoosePetScene() {}
    
    static cocos2d::CCScene* scene();
    CREATE_FUNC(ChoosePetScene);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
};

#pragma mark CcbChoosePetLayer
class ReRichText;

class CcbChoosePetLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCEditBoxDelegate
{
public:
	// Constructor
    CcbChoosePetLayer();
	
	~CcbChoosePetLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChoosePetLayer, create);
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
	// Attributes for CCB
	cocos2d::extension::CCScale9Sprite* m_pScale9SpriteName;
	cocos2d::extension::CCControlButton* m_pControlButtonRandom;
	cocos2d::extension::CCControlButton* m_pControlButtonConfirm;
	cocos2d::CCLabelTTF* m_pLabelTTFNormal_AtkName;
	cocos2d::CCLabelTTF* m_pLabelTTFNormal_AtkLv;
	cocos2d::CCLabelTTF* m_pLabelTTFNor_SkillDes;
	cocos2d::CCLabelTTF* m_pLabelTTFAltSkillLv;
	cocos2d::CCLabelTTF* m_pLabelTTFAltSkillDes;
	cocos2d::CCLabelTTF* m_pLabelTTFAltSkillName;
	cocos2d::CCSprite* m_pSprite6Wei;
	cocos2d::CCLabelTTF* m_pLabelTTFPetName;
	cocos2d::CCLabelTTF* m_pLabelTTFPetIntro;
	cocos2d::extension::CCControlButton* m_pControlButtonLeft;
	cocos2d::extension::CCControlButton* m_pControlButtonRight;
    cocos2d::CCNode* m_pNodeChoosePet;
    cocos2d::CCLayer* m_pLayerTouchArea;
    cocos2d::CCNode* m_pParticle;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    //Touch Functions
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
	
    //EditBox Functions
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    
public:
	// Funcitons
	void onPressControlButtonRandom(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonConfirm(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonLeft(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRight(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    // Self Functions
    void updateNodePosByOffset(float offset);
    void autoAdjustNodePos();
    void changeNodeTagByDir(int dir);
    void afterAnimationFinishCallBack();
    void autoAdjustNodeZorder();
    void runBreathAnimation(CCNode *pNode);
    bool checkNameLegal();
    void setShowInfo();
private:
    cocos2d::extension::CCEditBox* m_pInputBox;
    cocos2d::CCPoint m_BeginPoint;
    cocos2d::CCPoint m_ArrPot[4];
    cocos2d::CCSize m_Distance[2];
    float m_fScale[4];
    bool m_bTouchMoved;
    cocos2d::CCRect m_LayerRect;
    cocos2d::CCNode* m_pCurRunNode;
    uint32 m_dwPetIndex[4];
    int m_nCurIndex;
    
    std::vector<std::string> m_vecFirstName;
    std::vector<std::string> m_vecSecondName;
    std::vector<std::string> m_vecThirdName;
    ReRichText* m_pRichNorDes;
    ReRichText* m_pRichSkillDes;
    cocos2d::CCPoint arrPoint[6];
    cocos2d::CCPoint m_pEditBoxPos;
//    cocos2d::ccColor4F m_StartColor4F[4];
//    cocos2d::ccColor4F m_EndColor4f[4];

};

class CcbChoosePetLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChoosePetLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChoosePetLayer);
};


#endif // __CCBCHOOSEPETLAYER__H__