//
//  GachaDataMgr.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-26.}
//
//

#include "GachaDataMgr.h"
#include "BackCtrl.h"
#include "CcbNewGachaLayer.h"
#include "cocos2d.h"
#include "ConfigGet.h"
USING_NS_CC;

CGachaDataMgr::CGachaDataMgr()
{
    m_curCnt = -1;
    m_dwGetMoney = 0;
    m_bGachaFlag = false;
    m_bIsBoardOpen = false;
    loadPet();
}

void CGachaDataMgr::AddGachaPetIdx(uint32 objId, uint8 isNew)
{
    GACHA_PET_INFO pet;
    pet.dwPetObjId = objId;
    pet.byIsNew = isNew;
    m_vecGachaPetIdx.push_back(pet);
}

void CGachaDataMgr::ClearGachaPet()
{
    m_vecGachaPetIdx.clear();
}

/** 发送抽奖面板
 *	初级抽	uint8 byFreeCnt		剩余免费次数
 *			uint32 dwLiftTime   免费CD时间
 *	高级抽	uint32 dwLiftTime
 *	高级抽	uint32 dwDollar		单抽钻石
 *	高级抽	uint32 dwTenDollar  十连抽钻石
 *	高级抽	uint32 dwLeftCnt	必中五星剩余次数
 */
void CGachaDataMgr::SetGachaInfo(WorldPacket &packet)
{
    packet >> m_byFreeCnt;
    packet >> m_dwFreeCntMax;
    packet >> m_dwFreeLeftTime;
    
    packet >> m_dwLeftTime;
    packet >> m_dwOneDollar;
    packet >> m_dwTenDollar;
    packet >> m_dwDollarLeftCnt;
    
    CcbNewGachaLayer* pShared = CcbNewGachaLayer::GetCurScene();
    if (pShared != NULL) {
        pShared->loadData();//(m_dwLeftTime);
    } else {
//        BackCtrl::ChangeRootScene(kGachaScene);
    }
}

void CGachaDataMgr::SetGachaDollar(WorldPacket& packet)
{
    uint32 dwDollar;
    packet >> dwDollar;
    CcbNewGachaLayer* pShared = CcbNewGachaLayer::GetCurScene();
    if (pShared) {
        pShared->handlerDollarShow(dwDollar);
    }
    return;
}

void CGachaDataMgr::loadPet()
{
    m_arrTicketPet.clear();
    m_arrDollarPet.clear();
    std::vector<std::vector<uint16> > arrAllStar;
    for (int i = 0; i < 8; i++) {
        std::vector<uint16> arrStar;
        arrAllStar.push_back(arrStar);
    }
    uint8 byStarLvF_T = 4;
    uint8 byStarLvT_T = 5;
    
    uint8 byStarLvF_D = 5;
    uint8 byStarLvT_D = 6;
    
    std::map<uint16, PetConfig::STC_PET_CONFIG> mapAllPet = GET_CONFIG_MAP(PetConfig);
    std::map<uint16, PetConfig::STC_PET_CONFIG>::iterator it = mapAllPet.begin();
    for (; it != mapAllPet.end(); it++) {
        PetConfig::STC_PET_CONFIG petCfg = it->second;
        if (!petCfg.wIndex || !petCfg.byIsGachaShow) {
            continue;
        }
        //按星级分类
        std::vector<uint16> arrStar = arrAllStar[petCfg.byStarLv - 1];
        arrStar.push_back(petCfg.wIndex);
        arrAllStar[petCfg.byStarLv - 1] = arrStar;
    }
    
    for (int i = arrAllStar.size() - 1; i >= 0; i--) {
        uint32 wSize = arrAllStar[i].size();
        if (wSize == 0) {
            continue;
        }
        for (int k = 0; k < wSize; k++) {
            uint16 petId = arrAllStar[i][k];
            if (!petId) {
                continue;
            }
            PetConfig::STC_PET_CONFIG *cfg = GET_CONFIG_STC(PetConfig, petId);
            if (cfg->byStarLv >= byStarLvF_T && cfg->byStarLv <= byStarLvT_T) {
                m_arrTicketPet.push_back(petId);
            }
            
            if (cfg->byStarLv >= byStarLvF_D && cfg->byStarLv <= byStarLvT_D) {
                m_arrDollarPet.push_back(petId);
            }
        }
    }

}