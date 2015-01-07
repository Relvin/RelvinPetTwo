//
//  CaptureScene.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-8.}
//
//

#ifndef __HelloWorld__CaptureScene__
#define __HelloWorld__CaptureScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "WorldPacket.h"

#pragma mark CaptureCtrl

class CaptureCtrl {
    
public:
    typedef struct _STC_MASTER
    {
        uint32 dwMasterId;          // 主人信息 ID}
        std::string strMasterName;  // 主人信息 名字}
        uint32 dwCaptureTime;       // 主人信息 抓捕时间}
        uint8 byMasterType;         // 主人信息 在哪种建筑被抓}
        uint8 byMasterFarmId;       // 主人信息 哪一个矿坑}
        uint16 wLeaderId;
        uint8 byGroupId;
        uint32 dwLeftTime;  //second
        _STC_MASTER() {
            dwMasterId = 0;
            strMasterName = "";
            dwCaptureTime = 0;
            byMasterType = 0;
            byMasterFarmId = 0;
            wLeaderId = 0;
            byGroupId = 0;
            dwLeftTime = 0;
        };
    }STC_MASTER;
    
    typedef struct _STC_MINE_INFO
    {
        uint32 dwSlaveId;       // 奴隶Id}
        std::string strName;    // 奴隶名字}
        uint8 byRobLv;          // 奴隶等级}
        uint32 dwRewCnt;        // 领奖可获得的数量 //不显示，标示是否可领奖}
        uint16 wPetLeaderId;    // 队长模型}
        uint32 dwLeftTime;      // 剩余时间 秒}
        _STC_MINE_INFO() {
            dwSlaveId = 0;
            strName = "";
            byRobLv = 0;
            dwRewCnt = 0;
            wPetLeaderId = 0;
            dwLeftTime = 0;
        };
    }STC_MINE_INFO;
    
    typedef std::vector<std::string> VEC_MSG;
    typedef std::vector<STC_MINE_INFO> VEC_MINE;
    
    static STC_MASTER masterInfo;
    static uint8 byCurType;     //建筑类型}

    static VEC_MINE m_vecMine;  //矿坑信息}
    static uint8 bIsNew;        //是否有新消息提醒}
    static VEC_MSG m_vecMsg;
    static uint8 byCurFarmId;   //第几个坑位}
    
    static void HandlerCaptureInfo(WorldPacket& packet);
    static void HandlerRobRewardUpdate(WorldPacket& packet);
};


#pragma mark CaptureScene

class CaptureScene : public cocos2d::CCLayer
,   public cocos2d::extension::CCBMemberVariableAssigner {
    
public:
    CaptureScene() {
        m_pLabelTTFName = NULL;
    };
    ~CaptureScene() {
        CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    };
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(CaptureScene);
    // Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
private:
    cocos2d::CCLabelTTF* m_pLabelTTFName;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

#endif /* defined(__HelloWorld__CaptureScene__) */
