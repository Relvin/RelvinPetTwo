//
//  CheckPointMgr.h
//  MyGame
//
//  Created by 朱 俊杰 on 14/10/28.
//
//

#ifndef __MyGame__CheckPointMgr__
#define __MyGame__CheckPointMgr__

#include "Singleton.h"
#include "ConfigData.h"
#include <vector>
#include "Defines.h"
#include <map>
#include "cocos2d.h"

class CcbPadLayer;
class CcbPetBattleLayer;
class StageLayer;
class CheckPointMgr : public Singleton<CheckPointMgr> {
    
public:
    CheckPointMgr();
    virtual ~CheckPointMgr() {}
    
    enum {
        kBossTalk = 0,
        kStageTalk,
        kFightEndTalk,
    };
    
    /*!
     MapId && (StageId == 0) && 0 equals MapTalk
     MapId && (StageId != 0) && 0 equals BossTalk
     MapId && (StageId != 0) && 1 equals StageTalk
     MapId && (StageId != 0) && 2 equals FightEndTalk
     @param _bStageTalk true    加在Stage之前说话
                        false   加在Boss和FightEnd之前的对话
     */
    void loadTalkData(uint16 _wMapId, uint16 _wStageId, bool _bStageTalk);
    void clrTalkData();
    
    int talkPadCnt();
    int FightEndCnt();
    
    void addMapTalk(int _idx, StageLayer* _parent);
    void addStageTalk(int _idx, StageLayer* _parent);
    void addBossTalk(int _idx, CcbPetBattleLayer* _parent);
    void addFightEndTalk(int _idx, CcbPetBattleLayer* _parent);
private:
    typedef std::vector<EpitasisConfig::STC_EPITASIS_CONFIG> VEC_EPITASIS;
    VEC_EPITASIS m_vecEpitasis;
    VEC_EPITASIS m_vecFightEndTalk;
    typedef std::map<uint32, EpitasisConfig::STC_EPITASIS_CONFIG> MAP_EPITASIS;
    
    cocos2d::CCSize winSize;
};

#endif /* defined(__MyGame__CheckPointMgr__) */
