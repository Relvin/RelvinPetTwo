//
//  Team.h
//  HelloWorld
//
//  Created by long on 13-10-22.
//
//

#ifndef __HelloWorld__Team__
#define __HelloWorld__Team__

#include <iostream>
#include "Defines.h"
#include "ByteBuffer.h"
#include "ccMacros.h"


class CTeam
{
public:

    CTeam(uint8 byTeamId);
    ~CTeam();
    
    void DeSerializeDataClient(ByteBuffer &data);
    
    void PropertyUpdate(ByteBuffer & data);
    
    
    CC_SYNTHESIZE(uint8, m_byTeamId, byTeamId);
    CC_SYNTHESIZE(uint8, m_byIsBattle, byIsBattle)
    CC_SYNTHESIZE(uint8, m_byLeaderSite, byLeaderSite)
    CC_SYNTHESIZE(std::vector<uint32>, m_arrPetObId, arrPetObId)
    
    void SetTeamMember(uint8 site, uint32 petObjId);

};
#endif /* defined(__HelloWorld__Team__) */
