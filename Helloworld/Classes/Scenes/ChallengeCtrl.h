//
//  ChallengeCtrl.h
//  MyGame
//
//  Created by Relvin on 14/11/15.
//
//

#ifndef __MyGame__ChallengeCtrl__
#define __MyGame__ChallengeCtrl__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Singleton.h"
#include "Defines.h"

class ChallengeCtrl : public Singleton<ChallengeCtrl> {
    
public:
    ChallengeCtrl();
    ~ChallengeCtrl();
    
    typedef std::vector<uint16> VECSTAGE;
    
    enum ChallengeType
    {
        kTypeNone = 0,
        kPetRelics = 1,
        kEggTag = 2,
        kGodRelics = 3,
        kStoneRelics = 4,
        kMoneyCat = 5,
        kDaoGuanTag = 6,
        kTowerTag = 7,
    };
    enum ChallengeStage
    {
        E_CHALLENGE_NONE = 0,
        E_CHALLENGE_TOWER = 1,
        E_CHALLENGE_PAVILION = 2,
        E_CHALLENGE_FIGHT = 3,
        E_CHALLENGE_TRIAL = 4,
    };
    
    void loadDataFromConfigByMapId(uint16 wMapId);
    VECSTAGE* getChallengeStageInfoByDiffiValue(uint8 byValue);
    int getChallengeStageInfoCountByMapId(uint16 wMapId);
    CC_SYNTHESIZE(uint8, m_byType, ChallengeType);
    CC_SYNTHESIZE(bool, m_bChoose, ChallengePetChoose);
    CC_SYNTHESIZE(uint8, m_byStage, ChallengeStage);
    
    ChallengeCtrl::VECSTAGE* getChallengeStageInfoByMapId(uint16 wMapId);
    CC_SYNTHESIZE(int, m_nCellIndex, CellIndex);
private:
    std::map<uint8, VECSTAGE> m_stageDiffiValue;
    VECSTAGE m_vecStageInfo;
    uint16 m_wMapId;
};
#endif /* defined(__MyGame__ChallengeCtrl__) */
