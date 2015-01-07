//
//  ShopDataMgr.h
//  HelloWorld
//
//  Created by jun on 13-12-26.
//
//

#ifndef __HelloWorld__ShopDataMgr__
#define __HelloWorld__ShopDataMgr__

#include <iostream>
#include "Defines.h"
#include "Singleton.h"
#include "cocos2d.h"
#include <map>
#include <vector>
using namespace std;

struct SHOP_ITEM_INFO
{
    uint32  dwGoodsId;      //物品在商店里配的ID}
  
    uint8	byShopType;     //物品在商店里页签，1充值、2普通道具3、打折道具}
    uint32  dwBuyTypeId;    //物品的对应的物品ID前缀}
    uint32  dwBuyContentId; //物品的对应ID，如10000051}
    uint32  dwBuyCount;     //物品一次购买的数量}
    
    uint32  dwCostTypeId;   //物品的花费类型的TypeID，4 特殊类型}
    uint32  dwCostContentId;//物品的花费类型的ID，40000001金币，40000002钻石}
    uint32  dwCostCount;    //商品花费多少}
    uint32  dwCostDiscount; //商品打折价
   
    string  strName;        //商品显示的名字}
    string  strDescription; //商品描述}
    uint32  dwIconId;       //商品的Icon}
    
    uint8   byStatus;       //在售状态：0下架，1在售，2热卖}
    uint32  dwSortIdx;      //排序，从小到大排}
    
    uint32 dwDisappearTime; //购买剩余时间（秒）0=无限制}
    
    uint32 dwBuyCnt;          // 已经购买次数}
    int	 dwMaxCnt;            //总购买次数 ( -1 无限制)}
    
    SHOP_ITEM_INFO()
    {
        dwGoodsId = 0;
        byShopType = 0;
        dwBuyTypeId = 0;
        dwBuyContentId = 0;
        dwBuyCount = 0;
        dwCostTypeId = 0;
        dwCostContentId = 0;
        dwCostCount = 0;
        strName = "";
        strDescription = "";
        dwIconId = 0;
        byStatus = 0;
        dwSortIdx = 0;
        
        dwDisappearTime = 0;
        dwBuyCnt = 0;
        dwMaxCnt = -1;
    }
};

enum E_BUY_TYPE
{
    E_BUY_TYPE_NORMAL   = 0, // Normal pay
    E_BUY_TYPE_CARD     = 1, // weeky / monthly card
    
};

struct STORE_PAY_LIST_INFO
{
    uint8  byBuyType;
    uint8  byFirstPay;
    uint32 dwGoodsId;
    uint32 dwDollar;
    uint32 dwPrice;
    uint32 dwLeftDay;
    string strFirstLine;
    string strSecondLine;
    string strThirdLine;
    string strAppleId;
    
    STORE_PAY_LIST_INFO()
    {
        byBuyType = E_BUY_TYPE_NORMAL;
        byFirstPay = 0;
        dwGoodsId = 0;
        dwDollar = 0;
        dwLeftDay = 0;
        strFirstLine = "";
        strSecondLine = "";
        strThirdLine = "";
    }
};

enum E_SHOP_TYPE
{
    E_SHOP_TYPE_RECHARGE    = 1,//充值}
    E_SHOP_TYPE_NORMAL      = 2,//普通道具}
    E_SHOP_TYPE_REDUCED     = 3,//打折道具}
};

const int SHOP_TYPE_MAX = 3;    //商城显示页面类型}

typedef map<int, SHOP_ITEM_INFO> MAP_SHOP_ITEM_INFO;
typedef map<int, SHOP_ITEM_INFO>::iterator ITER_MAP_SHOP_ITEM_INFO;

typedef vector<SHOP_ITEM_INFO> VEC_SHOP_ITEM_INFO;
typedef vector<SHOP_ITEM_INFO>::iterator ITER_VEC_ITEM_INFO;

typedef vector<STORE_PAY_LIST_INFO> VEC_PAY_LIST_INFO;
typedef vector<STORE_PAY_LIST_INFO>::iterator ITER_VEC_PAY_LIST_INFO;

class CShopDataMgr : public Singleton<CShopDataMgr>
{
public:
    CShopDataMgr()
    : m_nCellIndex(-1)
    , m_dwItemId(0)
    {
        for (int i = 0; i < SHOP_TYPE_MAX; i++)
        {
            m_mapShopListTab[i].clear();
        }
        m_dwCurChosenGoodsId = 0;
        m_pShopSceneListNode = NULL;
        m_isDlgOpen = false;
        m_nSelectNum = 0;
        
    };
    ~CShopDataMgr() {};
    
    void AddShopItemList(const SHOP_ITEM_INFO& info);
    MAP_SHOP_ITEM_INFO GetShopListByType(E_SHOP_TYPE type);
    SHOP_ITEM_INFO GetShopItemByID(uint32 dwItemId);
    MAP_SHOP_ITEM_INFO m_mapShopListTab[SHOP_TYPE_MAX];//存放各个商品列表}
    
    void AddStorePayList(const STORE_PAY_LIST_INFO& info);
    void ClearStorePayList() { m_vecStorePayList.clear(); };
    VEC_PAY_LIST_INFO GetStorePayList() { return m_vecStorePayList; };
    VEC_PAY_LIST_INFO m_vecStorePayList;
     STORE_PAY_LIST_INFO* GetStorePayGoodsInfoById(uint32 dwGoodsId);
    
    
    void SetCurShopShowType(int type) { m_nCurShowType = type; };
    int GetCurShopShowType() { return m_nCurShowType; };
    int m_nCurShowType;//当前显示的标签页，分为两大类，1购买钻石界面、2购买普通商品界面}
    
    void setViewLayerRect( cocos2d::CCRect rect);
    cocos2d::CCRect getViewLayerRect();
    cocos2d::CCRect m_ViewLayerRect;

    //商城条目ID}
    void SetCurChosenGoodsId(uint32 dwGoodsId);
    uint32 GetCurChosenGoodsId();
    uint32 m_dwCurChosenGoodsId;
    
    //具体物品ID}
    void SetCurBuyContentId(uint32 dwContentId){ m_dwCurBuyContentId = dwContentId; };
    uint32 GetCurBuyContentId(){ return m_dwCurBuyContentId; } ;
    uint32 m_dwCurBuyContentId;
    
    //该条目商品的单价}
    void SetCurGoodsCostCount(uint32 dwCostCount){ m_dwGoodsCostCount = dwCostCount; };
    uint32 GetCurGoodsCostCount(){ return m_dwGoodsCostCount; };
    uint32 m_dwGoodsCostCount;
    
    void OpenDlgSelectNum();
    void SetDlgOpenNode(cocos2d::CCNode *node);
    cocos2d::CCNode* m_pShopSceneListNode;//绑定节点}
    
    void SetDlgOpenState(bool state);
    bool GetDlgOpenState();
    bool m_isDlgOpen;
    
    void SetSelectNum(int num);
    int GetSelectNum();
    int m_nSelectNum;
    
    void setAddMoney(uint32 dwMoney) { m_dwAddMoney = dwMoney; };
    uint32 GetAddMoney() { return m_dwAddMoney; };
    uint32 m_dwAddMoney;
    
    const char* GetOrderSerialByGoodsId(uint32 dwGoodsId);
    
    CC_SYNTHESIZE(int, m_nCellIndex, CellIndex);
    CC_SYNTHESIZE(uint32, m_dwItemId, ItemId);
    
};

#define g_ShopData CShopDataMgr::Get()

#endif /* defined(__HelloWorld__ShopDataMgr__) */

