/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-03-14 20:51:06
*/

#ifndef __CCBUPDATERESOURCELAYER__H__
#define __CCBUPDATERESOURCELAYER__H__

//CcbUpdateResourceLayer.h come from ccb/update_resource.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include <list>
#include "SystemMessage.h"

USING_NS_CC;

class CcbUpdateResourceLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbUpdateResourceLayer()
	{
        m_pLabelTTFTips = NULL;
        m_pSpriteDownload = NULL;
        m_pLabelGameTips = NULL;
	}
	~CcbUpdateResourceLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbUpdateResourceLayer, create);
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
    cocos2d::CCLabelTTF* m_pLabelTTFTips;
    cocos2d::CCSprite* m_pSpriteDownload;
    cocos2d::CCLabelTTF* m_pLabelGameTips;
    uint16 m_curTipsId;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
public:
	// Funcitons
    // Touch Method
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void systemMessageOKTapped(SystemMessage* systemMessage);
    
    void startUpdate();
    void updateProgress();
    
    static const char* GetRemoteFullPath(const char* pRemotePath);
    static const char* GetLocalWriteFullPath(const char* pLocalPath);
    static unsigned char* GetLocalFileData(const char* pLocalPath, unsigned long* size);
protected:
    enum {
        E_STATE_NEED_UPDATE     = 0,
        E_STATE_WAIT_USER       = 1,
        E_STATE_GET_FILE_LIST   = 2,
        E_STATE_CHECK_DIF       = 3,
        E_STATE_DOWNLOAD        = 4,
        E_STATE_RELOAD          = 5,
        E_STATE_COMPLETE        = 6,
        E_STATE_ERROR           = 7,
    };
private:
    void DeltaUpdate(float dt);
    void setState(int state);
    void onFinish();
    float calcSpeed();
    
    int m_state;
//    CCLabelTTF* lblTips;
    std::list< std::pair<float, uint32> > m_lstSpeedCal;
    float loadWidth, loadHeight;
    int cnt;
    
    void updateForShowGameTips(float time);

};

class CcbUpdateResourceLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbUpdateResourceLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbUpdateResourceLayer);
};


#endif // __CCBUPDATERESOURCELAYER__H__