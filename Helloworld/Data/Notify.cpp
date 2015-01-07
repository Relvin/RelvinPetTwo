//
//  Notify.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14-9-10.}
//
//

#include "Notify.h"
#include "Role.h"
#include "GameSession.h"

CNotify::CNotify() {
    m_byNotiNewPet = 0;
    m_byNotiNewEquip = 0;
    m_byNotiNewEmblem = 0;
    m_byNotiGacha = 0;
    m_byNotiMysteryShop = 0;
    m_byNotiFriend = 0;
}

CNotify::~CNotify() {
    
}

void CNotify::DeSerializeDataClient(ByteBuffer &data) {
    loadDataLoose(data);
    
    CRole* pRole = CGameSession::GetRole();
    
    m_byNotiNewPet = getProperty(E_NEWS_byNewPet).get<uint8>();
    m_byNotiNewEquip = getProperty(E_NEWS_byNewEquip).get<uint8>();
    m_byNotiNewEmblem = getProperty(E_NEWS_byNewEmblem).get<uint8>();
    
    pRole->SetbyNotiNewPet(m_byNotiNewPet);
    pRole->SetbyNotiNewEquip(m_byNotiNewEquip);
    pRole->SetbyNotiNewEmblem(m_byNotiNewEmblem);
//    pRole->SetbyNotiUnit(m_byNotiNewPet | m_byNotiNewEquip | m_byNotiNewEmblem);
    
    m_byNotiGacha = getProperty(E_NEWS_byGacha).get<uint8>();

    pRole->SetbyNotiGacha(m_byNotiGacha);
    
    m_byNotiMysteryShop = getProperty(E_NEWS_byMysteryShop).get<uint8>();
    
    pRole->SetbyNotiMystery(m_byNotiMysteryShop);
    pRole->SetbyNotiActive(
                           m_byNotiMysteryShop// |
//                           pRole->GetbySevenRewStatus() |
//                           pRole->GetbyThirtyRewStatus() |
//                           pRole->GetbyEnergyRewStatus()
                           );
    
    m_byNotiFriend = getProperty(E_NEWS_byFriendRew).get<uint8>();
    
    pRole->SetbyNotiFriend(m_byNotiFriend);
}

void CNotify::PropertyUpdate(ByteBuffer &data)
{
    CRole* pRole = CGameSession::GetRole();
    
    loadDataLoose(data);
    std::map<CDynamicStruct::key_type, AnyType> mapData;
    toMap(mapData);
    for (std::map<CDynamicStruct::key_type, AnyType>::iterator ii = mapData.begin(); ii != mapData.end(); ++ii) {
        switch (ii->first) {
            case E_NEWS_byNewPet:
                m_byNotiNewPet = (ii->second).get<uint8>();
                pRole->SetbyNotiNewPet(m_byNotiNewPet);
//                pRole->SetbyNotiUnit(pRole->GetbyNotiNewEquip() | pRole->GetbyNotiNewEmblem() | m_byNotiNewPet);
                break;
            case E_NEWS_byNewEquip:
                m_byNotiNewEquip = (ii->second).get<uint8>();
                pRole->SetbyNotiNewEquip(m_byNotiNewEquip);
//                pRole->SetbyNotiUnit(pRole->GetbyNotiNewPet() | pRole->GetbyNotiNewEmblem() | m_byNotiNewEquip);
                break;
            case E_NEWS_byNewEmblem:
                m_byNotiNewEmblem = (ii->second).get<uint8>();
                pRole->SetbyNotiNewEmblem(m_byNotiNewEmblem);
//                pRole->SetbyNotiUnit(pRole->GetbyNotiNewPet() | pRole->GetbyNotiNewEquip() | m_byNotiNewEmblem);
                break;
            case E_NEWS_byGacha:
                m_byNotiGacha = (ii->second).get<uint8>();
                pRole->SetbyNotiGacha(m_byNotiGacha);
                break;
            case E_NEWS_byMysteryShop:
                m_byNotiMysteryShop = (ii->second).get<uint8>();
                pRole->SetbyNotiMystery(m_byNotiMysteryShop);
                pRole->SetbyNotiActive(
//                                       pRole->GetbySevenRewStatus() |
//                                       pRole->GetbyThirtyRewStatus() |
                                       pRole->GetbyEnergyRewStatus() //|
//                                       m_byNotiMysteryShop
                                       );
                break;
            case E_NEWS_byFriendRew:
                m_byNotiFriend = (ii->second).get<uint8>();
                pRole->SetbyNotiFriend(m_byNotiFriend);
                break;
            default:
                break;
        }
    }
}
