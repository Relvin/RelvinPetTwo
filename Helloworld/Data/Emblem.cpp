//
//  Emblem.cpp
//  MyGame
//
//  Created by long on 14-7-4.
//
//

#include "Emblem.h"


CEmblem::CEmblem(uint32 dwEmlemObjId):
m_dwEmlemObjId(dwEmlemObjId)
{
    m_dwIndexId = 0;
    m_byLv = 0;
    m_dwExp = 0;
    m_dwPetObjId = 0;
}
CEmblem::~CEmblem()
{
    m_dwEmlemObjId = 0;
    m_dwIndexId = 0;
    m_byLv = 0;
    m_dwExp = 0;
    m_dwPetObjId = 0;
}

void CEmblem::DeSerializeDataClient(ByteBuffer &data)
{
    loadDataLoose(data);
    m_dwIndexId = getProperty(E_EMBLEM_dwIndex).get<uint32>();
    m_byLv = getProperty(E_EMBLEM_byLv).get<uint8>();
    m_dwExp = getProperty(E_EMBLEM_dwExp).get<uint32>();
    m_dwPetObjId = getProperty(E_EMBLEM_dwWearPetId).get<uint32>();
//    data >> m_dwIndexId;
//    data >> m_byLv;
//    data >> m_dwExp;
//    data >> m_dwPetObjId;
}

void CEmblem::PropertyUpdate(ByteBuffer & data)
{
    loadDataLoose(data);
    std::map<CDynamicStruct::key_type,AnyType> mapData;
	toMap(mapData);
	for(std::map<CDynamicStruct::key_type,AnyType>::iterator ii = mapData.begin(); ii != mapData.end(); ++ii)
	{
		switch(ii->first)
		{
            case E_EMBLEM_dwIndex:
                m_dwIndexId = getProperty(E_EMBLEM_dwIndex).get<uint32>();
                break;
            case E_EMBLEM_byLv:
                m_byLv = getProperty(E_EMBLEM_byLv).get<uint8>();
                break;
            case E_EMBLEM_dwExp:
                m_dwExp = getProperty(E_EMBLEM_dwExp).get<uint32>();
                break;
            case E_EMBLEM_dwWearPetId:
                m_dwPetObjId = getProperty(E_EMBLEM_dwWearPetId).get<uint32>();
                break;
            default:
                break;
        }
    }
    
}