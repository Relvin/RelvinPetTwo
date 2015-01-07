//
//  Emblem.h
//  MyGame
//
//  Created by long on 14-7-4.
//
//

#ifndef __MyGame__Emblem__
#define __MyGame__Emblem__

#include <iostream>
#include "Defines.h"
#include "ByteBuffer.h"
#include "ccMacros.h"
#include "Observer.h"
#include "DynamicStruct.h"

class CEmblem : public CDynamicStruct
{
public:
    
    CEmblem(uint32 dwEmlemObjId);
    ~CEmblem();
    
    void DeSerializeDataClient(ByteBuffer &data);
    
    void PropertyUpdate(ByteBuffer & data);
    
    /** 徽章动态结构}
     */
    enum
    {
     E_EMBLEM_dwKeyId,		// 0 ObjId
     E_EMBLEM_dwIndex,		// 1 徽章id}
     E_EMBLEM_byLv,			// 2 等级}
     E_EMBLEM_dwExp,			// 3 经验}
     E_EMBLEM_dwWearPetId,	// 4 装备的宠物ObjId}
    };
    
    CC_SYNTHESIZE(uint32, m_dwEmlemObjId, dwEmlemObjId);
    CC_SYNTHESIZE(uint32, m_dwIndexId, dwIndexId);
    CC_SYNTHESIZE(uint8, m_byLv, byLv);
    CC_SYNTHESIZE(uint32, m_dwExp, dwExp);
    CC_SYNTHESIZE(uint32, m_dwPetObjId, dwPetObjId);
    
private:

    
};
#endif /* defined(__MyGame__Emblem__) */
