//
//  GachaDataMgr.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-26.}
//
//

#ifndef __HelloWorld__GachaDataMgr__
#define __HelloWorld__GachaDataMgr__

#include <iostream>
#include "Singleton.h"
#include "Defines.h"
#include <vector>
#include "WorldPacket.h"

using namespace std;

enum GACHA_TYPE { // 抽奖类型}
    E_LOTTERY_TYPE_JUNIOR = 1,      // 低级抽}
    E_LOTTERY_TYPE_SENIOR = 2,      // 高级抽}
};

struct GACHA_PET_INFO
{
    uint32 dwPetObjId;
    uint8 byIsNew;
};

typedef vector<GACHA_PET_INFO> VEC_GACHA_PET_IDX;

class CGachaDataMgr : public Singleton<CGachaDataMgr> {
    
public:
    CGachaDataMgr();
//   增加宠物}
    void AddGachaPetIdx(uint32 objId, uint8 isNew);
    
//   清除宠物}
    void ClearGachaPet();
    
    void SetGachaInfo(WorldPacket& packet);
    void SetGachaDollar(WorldPacket& packet);
    
    void setByType(uint8 _byType) {
        m_byType = _byType;
    }
    uint8 byType() {
        return m_byType;
    }
    
    void setByIsTen(uint8 _byIsTen) {
        m_byIsTen = _byIsTen;
    }
    uint8 byIsTen() {
        return m_byIsTen;
    }
    
    uint32 dwLeftTime() {
        return m_dwLeftTime;
    }
    
    uint8 getFreeCnt(){
        return m_byFreeCnt;
    }
    uint32 getFreeCntMax(){
        return m_dwFreeCntMax;
    }
    
    uint32 getOneDollar(){
        return m_dwOneDollar;
    }
    uint32 getTenDollar(){
        return m_dwTenDollar;
    }
    
    uint32 getFreeLeftTime(){
        return m_dwFreeLeftTime;
    }
    
    uint32 getDollarLeftCnt(){
        return m_dwDollarLeftCnt;
    }
    
    void setCurCnt(int cnt){m_curCnt = cnt;};
    int getCurCnt(){return m_curCnt;};
    
    void setGachaFlag(bool isGacha){m_bGachaFlag = isGacha;};
    bool getGachaFlag(){return m_bGachaFlag;};
    
    void setIsBoardOpen(bool isOpen){m_bIsBoardOpen = isOpen;};
    bool getIsBoardOpen(){return m_bIsBoardOpen;};
    
    std::vector<uint16> getAllTicketPet(){return m_arrTicketPet;};
    std::vector<uint16> getAllDollarPet(){return m_arrDollarPet;};
public:
    VEC_GACHA_PET_IDX m_vecGachaPetIdx;
    uint32 m_dwGetMoney;
private:
    uint8 m_byType;       // 奖券抽或者钻石抽}
    uint8 m_byIsTen;      // 是否是十连抽}
    
    
    uint8 m_byFreeCnt;      //奖券抽免费次数
    uint32 m_dwFreeCntMax;  //奖券抽免费最大次数
    uint32 m_dwFreeLeftTime;    //奖券抽CD时间
    
    uint32 m_dwLeftTime;    // 剩余钻石抽时间}
    uint32 m_dwOneDollar;   //单抽钻石
    uint32 m_dwTenDollar;   //十连抽钻石
    uint32 m_dwDollarLeftCnt;//再多少次可必得5星
    
    int m_curCnt;       //十连抽计数用
    
    bool m_bGachaFlag;  //用于从抽奖进图鉴
    
    bool m_bIsBoardOpen; //预览是否打开
    
    std::vector<uint16> m_arrTicketPet;
    std::vector<uint16> m_arrDollarPet;
    
private:
    void loadPet();
};

#define g_GachaData CGachaDataMgr::Get()
#endif /* defined(__HelloWorld__GachaDataMgr__) */
