//
//  WorldInfoDataMgr.h
//  MyGame
//
//  Created by Relvin on 14/11/4.
//
//

#ifndef __MyGame__WorldInfoDataMgr__
#define __MyGame__WorldInfoDataMgr__

#include <iostream>
#include "Singleton.h"
#include "Defines.h"
#include "WorldPacket.h"

#define CC_WORLD_PROPERTY(varType, varName, funName)\
private: varType varName;\
public: varType get##funName(void) const { return varName; }\
public: void set##funName(varType var){ varName = var; }

class WorldInfoDataMgr : public Singleton<WorldInfoDataMgr> {
    
public:
    WorldInfoDataMgr();
    ~WorldInfoDataMgr();

//    uint8 GetWeatherStatus();
//    void SetWeatherStatus(uint8 weather){m_byWeather = weather;};
//    
//    uint32 GetSweepCDDollar();
//    void SetSweepCDDollar(uint32 dollar){m_dwSweepCDDollar = dollar;};
//    
//    uint8 GetIsWorldBossOpen();
//    void SetIsWorldBossOpen(uint8 isOpen){m_byWorldBossOpen = isOpen;};
    
    CC_WORLD_PROPERTY(uint8, m_byWeather, Weather);
    CC_WORLD_PROPERTY(uint8, m_dwSweepCDDollar, SweepCDDollar);
    CC_WORLD_PROPERTY(uint8, m_byWorldBossOpen, IsWorldBossOpen);
    CC_WORLD_PROPERTY(uint32, m_wAreanJumpTime, AreanJumpTime);
    CC_WORLD_PROPERTY(uint8, m_byMJShopOpen, MJShopOpen);
    
    void handlerWorldInfoUpdate(WorldPacket &packet);
private:
    
//    uint8 m_byWeather;
//    uint32 m_dwSweepCDDollar;
//    uint8  m_byWorldBossOpen;//	世界Boss是否开启

};

#endif /* defined(__MyGame__WorldInfoDataMgr__) */
