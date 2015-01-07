//
//  Team.cpp
//  HelloWorld
//
//  Created by long on 13-10-22.
//
//

#include "Team.h"
CTeam::CTeam(uint8 byTeamId):
m_byTeamId(byTeamId)
{
    
}
CTeam::~CTeam()
{
    
}

void CTeam::DeSerializeDataClient(ByteBuffer &data)
{
    data >> m_byIsBattle;
    data >> m_byLeaderSite;
    
    uint8 size = 0;
    data >> size;
    m_arrPetObId.clear();
    m_arrPetObId.push_back(0);
    for (int i = 1; i <= size; i++) {
        uint32 dwPetObjId;
        data >> dwPetObjId;
        m_arrPetObId.push_back(dwPetObjId);
    }
}

void CTeam::PropertyUpdate(ByteBuffer & data)
{
    data >> m_byIsBattle;
    data >> m_byLeaderSite;
    
    uint8 size = 0;
    data >> size;
    m_arrPetObId.clear();
    m_arrPetObId.push_back(0);
    for (int i = 1; i <= size; i++) {
        uint32 dwPetObjId;
        data >> dwPetObjId;
        m_arrPetObId.push_back(dwPetObjId);
    }
}

void CTeam::SetTeamMember(uint8 site, uint32 petObjId)
{
    if (site < m_arrPetObId.size()) {
        m_arrPetObId[site] = petObjId;
    }
}

