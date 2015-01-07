//
//  BuildUpScene.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-12-20.}
//
//

#ifndef __HelloWorld__BuildUpScene__
#define __HelloWorld__BuildUpScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "WorldPacket.h"
#include "Singleton.h"

class CBuildUpDataMgr : public Singleton<CBuildUpDataMgr> {
    
public:
    // 建筑升级全包信息，（同时也是更新包信息）}
    /*
     {uint8 bySize + {
        uint8 byType + 
        uint16 wBuildLv + 
        uint32 dwExp 钱 + 
        uint32 dwNeedExp 魂 }
     */
    void handlerUpgradeInfo(WorldPacket& packet);
    
    typedef struct _STC_BUILD_INFO {
        uint16 wBuildLv; // 当前建筑等级}
        uint32 dwMoney;  // 升级需要的金枪}
        uint32 dwHun;    // 升级需要的魂}
        _STC_BUILD_INFO() {
            wBuildLv = 0;
            dwMoney = 0;
            dwHun = 0;
        }
    }STC_BUILD_INFO;
    
    typedef std::map<uint8, STC_BUILD_INFO> MAP_INFO;
    
    STC_BUILD_INFO getBuildingByType(uint8 kType);
    MAP_INFO getBuildingMap() {
        return m_mapBuild;
    }
private:
    MAP_INFO m_mapBuild;
    
};

class BuildUpScene :
    public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    BuildUpScene() {
        m_pLabelTTFName = NULL;
    }
    ~BuildUpScene() {
        CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    }
    
    static cocos2d::CCScene* scene();\
    
    CREATE_FUNC(BuildUpScene);
    // Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
private:
    cocos2d::CCLabelTTF* m_pLabelTTFName;
};

#endif /* defined(__HelloWorld__BuildUpScene__) */
