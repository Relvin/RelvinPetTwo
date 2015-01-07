//
//  ChanllengeDataMgr.cpp
//  MyGame
//
//  Created by long on 14-7-29.
//
//

#include "ChallengeDataMgr.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"

ChallengeDataMgr::ChallengeDataMgr()
{

}

ChallengeDataMgr::~ChallengeDataMgr()
{

}


void ChallengeDataMgr::handlerCurStageInfo(WorldPacket &packet)
{

    uint32 wIndexId;
    uint8 byRewStatus;
    uint8 byResetCnt;
    std::string strDefName;
    uint16 wRoleLv;
    std::vector<uint16> arrPetId;
    std::vector<uint32> arrRewItemId;
    std::vector<uint32> arrRewItemCnt;
    
    packet >> wIndexId;
    packet >> byRewStatus;
    packet >> byResetCnt;
    packet >> strDefName;
    packet >> wRoleLv;
    uint8 bySize;
    packet >> bySize;
    for (int i = 0; i < bySize; i++) {
        uint16 wPetId;
        packet >> wPetId;
        arrPetId.push_back(wPetId);
    }
    bySize = 0;
    packet >> bySize;
    for (int i = 0; i < bySize; i++) {
        uint32 dwItemId;
        uint32 dwItemCnt;
        packet >> dwItemId;
        packet >> dwItemCnt;
        arrRewItemId.push_back(dwItemId);
        arrRewItemCnt.push_back(dwItemCnt);
    }
    
    m_curStageInfo.wIndexId = wIndexId;
    m_curStageInfo.byRewStatus = byRewStatus;
    m_curStageInfo.byResetCnt = byResetCnt;
    m_curStageInfo.strDefName = strDefName;
    m_curStageInfo.wRoleLv = wRoleLv;
    m_curStageInfo.arrPetId = arrPetId;
    m_curStageInfo.arrRewItemId = arrRewItemId;
    m_curStageInfo.arrRewItemCnt = arrRewItemCnt;
}

