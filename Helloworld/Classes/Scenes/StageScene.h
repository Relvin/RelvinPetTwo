//
//  StageScene.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-18.}
//
//

#ifndef __HelloWorld__StageScene__
#define __HelloWorld__StageScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "WorldPacket.h"
#include "Singleton.h"

class StageCtrl : public Singleton<StageCtrl> {
    
public:
    StageCtrl();
    /*{ uint8 bySize +
            uint16 wStageId +
            std::string strName +
            uint8 bySectionCnt +
            uint16 wIconId +
            std::string strDes +
            uint8 byNeedEnergy +
            uint8 byIsNew +
            std::string strName
            uint8 bySize
                uint16 wPetId
            uint8 bySize
                uint32 dwItemId
     }
     */
    enum {
        kActivityStage = 0,     // 活动关卡}
        kNormalStage = 1,       // 普通关卡}
        kSpecialStage = 2,      // 精英关卡}
    };
    
    typedef std::vector<uint32> VEC_UINT32;
    
    typedef struct _STC_STAGE {
        uint16 wStageId;
        std::string strName;
        uint8 byFightCnt;       // 总波次}
        uint16 wIconId;
        std::string strDes;
        uint8 byCostEnergy;
        uint8 byStatus;
        uint8 byAttackCnt;      // 已攻击次数}
        uint8 byMaxAttCnt;      // 最大攻击次数}
        uint16 wRoleLvLimit;    // 进入等级限制}
        std::string strFirstBlood;
        VEC_UINT32 m_vecPetId;     // 普通掉落宠物}
        VEC_UINT32 m_vecItemId;         // 普通掉落物品}
        VEC_UINT32 m_vecFirstItemId;    // 首次掉落物品}
        VEC_UINT32 m_vecFirstItemCnt;   // 首次掉落物品数量}
        uint8 byStarCnt;        // 星数}
        uint8 byFlag;           // 是否是Boss关卡}
        uint8 byBuyCnt;         // 已经购买次数}
        uint16 wShowMapId;      //战斗场景ID
        
        std::vector<int>vectNormalBgm;
        std::vector<int>vectBossBgm;
        
        _STC_STAGE() {
            wStageId = 0;
            strName = "";
            byFightCnt = 0;
            wIconId = 0;
            strDes = "";
            byCostEnergy = 0;
            byStatus = 0;
            byAttackCnt = 0;
            byMaxAttCnt = 0;
            wRoleLvLimit = 0;
            strFirstBlood = "";
            m_vecPetId.clear();
            m_vecItemId.clear();
            m_vecFirstItemId.clear();
            m_vecFirstItemCnt.clear();
            byStarCnt = 0;
            byFlag = 0;
            byBuyCnt = 0;
            wShowMapId = 1;
            vectNormalBgm.clear();
            vectBossBgm.clear();
        }
    }STC_STAGE;
    
    typedef struct _STC_SPE_MAP {
        uint16 wMapId;
        uint32 dwReleaseTime;
        uint8 byIsOpen;
        uint8 byMapType;
        _STC_SPE_MAP() {
            wMapId = 0;
            dwReleaseTime = 0;
            byIsOpen = 0;
        }
    } STC_SPE_MAP;
    
    typedef std::vector<STC_STAGE> VECTOR_STAGE_TYPE;
    typedef std::vector<STC_SPE_MAP> VEC_SPE_MAP;
    typedef std::map<uint8, VEC_SPE_MAP> MAP_SPEMAP;
    
    void handlerStageList(WorldPacket &packet);
    void handlerActivityMap(WorldPacket& packet);       // 活动地图，竖条}
    void handlerStageUpdate(WorldPacket& packet);       // 普通关卡更新包}
    void handlerActiveStageUpdate(WorldPacket& packet); // 活动关卡更新}
    
    // 地图点名称设置}
    void setCurMapPointName(std::string strName) {     // 设置地图点名称}
        strMapPointName = strName;
    }
    const char* curMapPointName() {     // 获得地图点名称，一般在StageLayer界面的上面用}
        return strMapPointName.c_str();
    }

    // 类型设置}
    void setKind(int type) {
        kFromType = type;
    }
    int kind() {
        return kFromType;
    }
    
    // 选中的关卡}
    void setSelectedStage(int nStage) {
        m_nSelectedStage = nStage;
    }
    int selectedStageIdx() {
        return m_nSelectedStage;
    }
    STC_STAGE selectedStage() {
        if (m_nSelectedStage >= m_vecStage.size()) {
            m_nSelectedStage = 0;
        }
        return m_vecStage[m_nSelectedStage];
    }
    
    STC_STAGE stageWithIdx(int idx) {
        return m_vecStage[idx];
    }
    
    STC_STAGE* getStageByStageId(int index);

    uint16 stageId(int idx) {
        return m_vecStage[idx].wStageId;
    }
    
    int stageCnt() {
        return m_vecStage.size();
    }
    int activityMapSize() {
        return m_vecActiviyMap.size();
    }
    VEC_SPE_MAP activityMapAll() {
        return m_vecActiviyMap;
    }
    
    VEC_SPE_MAP* getActivitysByKey(uint8 byKey) {
        MAP_SPEMAP::iterator iter = m_mapActivityMap.find(byKey);
        if (iter != m_mapActivityMap.end())
        {
            return &iter->second;
        }
        return NULL;
    }
    
    STC_SPE_MAP activityMapAtIdx(int idx) {
        STC_SPE_MAP stcMap;
        if (idx < m_vecActiviyMap.size() && idx >= 0) {
            stcMap = m_vecActiviyMap[idx];
        }
        return stcMap;
    }
    
    STC_SPE_MAP* getActivityMapByMapId(uint16 wMapId) {
        for (int i = 0 ;i < m_vecActiviyMap.size();i++ )
        {
            if (m_vecActiviyMap[i].wMapId == wMapId) {
                return &m_vecActiviyMap[i];
            }
        }
        return NULL;
    }
    
    void setSelectedActivityMapIdx(int idx) {
        m_nSelectedActivityIdx = idx;
    }
    int selectedActivityMapIdx() {
        return m_nSelectedActivityIdx;
    }
    
    // 星级奖励领取}
    uint8 starGet() {
        return byStarGet;
    }
    void setStarGet(uint8 _starGet) {
        byStarGet = _starGet;
    }
    
    int curStarCnt() {
        return m_nCurStarCnt;
    }
    
    /*!
     给定_mapId的活动是否开启
     */
    bool isActivityOpen(int _mapId);
    
    void setFromJump(uint8 _Jump, uint32 _item = 0) {
        m_byFromJump = _Jump;
        m_itemIndexId = _item;
    }
    uint8 fromJump() {
        return m_byFromJump;
    }
    
    void setDropStage(uint32 _stage) {
        m_dropStage = _stage;
    }
    uint32 dropStage() {
        return m_dropStage;
    }
    CC_SYNTHESIZE(uint16, m_wStageId, SelectStageId);
    
private:
    std::string strMapPointName;     //地图点名称}
    int m_nSelectedStage;
    int kFromType;
    VECTOR_STAGE_TYPE m_vecStage;
    VEC_SPE_MAP m_vecActiviyMap;    // 特殊活动界面，也就是活动关卡界面，放在这里由于历史原因，原来地图可以有按钮跳转到活动关卡，后来改为跳转到精英关卡。}
    MAP_SPEMAP m_mapActivityMap;
    uint8 byStarGet;
    int m_nSelectedActivityIdx;
    int m_nCurStarCnt;              // 当前获得的星数}
    uint8   m_byFromJump;           // 从掉落跳转界面过来的请求，不需要跳转到对应界面 }
    uint32 m_itemIndexId;
    uint32 m_dropStage;            // 若引导的stage需要添加特效 }
};

class StageScene :
    public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
{
    
public:
    StageScene()
    {
        m_pLabelTTFName = NULL;
    }
    ~StageScene();
    static cocos2d::CCScene* scene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(StageScene, create);
    
    // Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
    
private:
    int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    
public:
    virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
};

#endif /* defined(__HelloWorld__StageScene__) */
