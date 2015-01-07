//
//  BuyDataMgr.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-6-13.}
//
//

#ifndef __HelloWorld__BuyDataMgr__
#define __HelloWorld__BuyDataMgr__

#include <iostream>
#include "Singleton.h"
#include "WorldPacket.h"
#include "Defines.h"
#include <vector>

class BuyDataMgr : public Singleton<BuyDataMgr> {
    
public:
    BuyDataMgr(){
        m_curBuyType = 0;
        m_bChangeToBuyScene = true;
    };
    typedef struct _STC_BUY {
        uint8 byType;
        uint32 dwCostDollar;
        uint32 dwLeftCnt;
        uint32 dwEarnCnt;
    }STC_BUY;
    
    void handleBuyShopInfo(WorldPacket& packet);
    void handleBuyShopUpdateInfo(WorldPacket& packet);
    
    STC_BUY buyInfoByType(uint8 byTType);
    
    void setCurBuyType(uint8 type){m_curBuyType = type;};
    uint8 getCurBuyType(){return m_curBuyType;};
    
    bool getChangeToBuyScene() {return m_bChangeToBuyScene;}
    void setChangeToBuyScene(bool change) {m_bChangeToBuyScene = change;};
private:
    typedef std::vector<STC_BUY> VEC_BUY_INFO;
    typedef std::vector<STC_BUY>::iterator ITR_VEC_BUY;
    VEC_BUY_INFO m_vecBuyInfo;
    
    uint8 m_curBuyType;
    bool    m_bChangeToBuyScene;
};

#endif /* defined(__HelloWorld__BuyDataMgr__) */
