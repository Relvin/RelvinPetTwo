//
//  EquipDataMgr.h
//  HelloWorld
//
//  Created by jun on 14-2-11.
//
//

#ifndef __HelloWorld__EquipDataMgr__
#define __HelloWorld__EquipDataMgr__

#include <iostream>
#include "Singleton.h"
#include "Equip.h"
#include "Rune.h"
#include "CcbEquipListLayer.h"
#include "CcbEquipInlayLayer.h"
#include <vector>


using namespace std;


//装备合成标签类型}
enum SHOW_TAB_TYPE
{
    SHOW_TAB_ATTRI_HP   = 0, //生命}
    SHOW_TAB_ATTRI_ATK  = 1, //攻击}
    SHOW_TAB_ATTRI_DEF  = 2, //防御}
    SHOW_TAB_ATTRI_REV  = 3, //回复}
    SHOW_TAB_ATTRI_CRIT = 4, //暴击}
};

enum ATTIR_TYPE
{
    ATTRI_HP   = 1, //生命}
    ATTRI_ATK  = 2, //攻击}
    ATTRI_DEF  = 3, //防御}
    ATTRI_REV  = 4, //回复}
    ATTRI_CRIT = 5, //暴击}
};

//装备部位}
enum E_EQUIP_PART
{
    E_EQUIP_PART_WEAPON     = 1,    //爪}
    E_EQUIP_PART_CLOTHES    = 2,    //羽}
    E_EQUIP_PART_HELMET     = 3,    //牙}
    E_EQUIP_PART_NECKLACE   = 4,    //角}
};

//装备frame类型}
enum E_EQUIP_FRAME_TYPE
{
    E_EQUIP_FRAME_ENHANCE   = 1,    //强化}
    E_EQUIP_FRAME_WEAR      = 2,    //装备}
    E_EQUIP_FRAME_DOWN      = 3,    //脱下}
    E_EQUIP_FRAME_RUNE      = 4,    //镶嵌}
};

//装备列表显示方式}
enum E_EQUIP_LIST_MODE
{
    E_SHOW_LIST_PET = 1, //通过宠物详情Icon进入，1当前宠物装备位置上无装备，只有穿着装备功能，2当前宠物装备位置上有装备，有卸下当前装备功能}
    E_SHOW_LIST_ALL = 2, //装备一览，带有出售功能，进阶功能，强化功能}
    E_SHOW_LIST_INPLAY = 3, //宝石镶嵌，只有镶嵌功能}
};


class CEquipDataMgr : public Singleton<CEquipDataMgr>
{
public:
    CEquipDataMgr()
    {
        m_emCompoundTabType = SHOW_TAB_ATTRI_HP;
        m_emEquipListShowMode = E_SHOW_LIST_ALL;
        m_arrSelectedEquipId.clear();
        m_EquipOffset = ccp(0, 1);
        m_dwDressEquipKeyID = 0;
        m_isEquipShow = false;
    };
    
public:
    void AddShowEquipKeyID(uint32 dwKeyID);
    vector<uint32> GetVecShowEquipKeyID();
    void ClearShowEquipKeyID();
    void DelKeyIDFormEquipShowVector(uint32 dwKeyID);
    
    void AddShowRuneKeyID(uint32 dwKeyID);
    vector<uint32> GetVecShowRuneKeyID();
    void ClearShowRuneKeyID();
    void DelKeyIDFormRuneShowVector(uint32 dwKeyID);
private:
    vector<uint32> m_vecShowEquipKeyID;
    vector<uint32> m_vecShowRuneKeyID;
    
    uint8 m_emDressEquipPart;
    uint32 m_dwDressEquipKeyID;
    E_EQUIP_LIST_MODE m_emEquipListShowMode;
    uint32 m_dwChosenEquipKeyID;
    //是否显示装备}
    bool m_isEquipShow;
    bool m_isNeedJumpScene;
    uint32 m_dwCompoundIndex;
    SHOW_TAB_TYPE m_emCompoundTabType;
    CCPoint m_EquipOffset;
    bool m_isShowLv;
public:
    //在宠物详情界面里，选择要装备的位置索引，值取值范围：1-4}
    void SetDressEquipPart(uint8 part) { m_emDressEquipPart = part; };
    uint8 GetDressEquipPart() { return m_emDressEquipPart; };
    
    
    //在宠物详情界面里，选择装备位置上的装备KeyID,用于卸下的}
    void SetDressEquipKeyID(uint32 dwKeyID) { m_dwDressEquipKeyID = dwKeyID; };
    uint32 GetDressEquipKeyID() { return m_dwDressEquipKeyID; };
    
    
    void SetEquipListShowMode(E_EQUIP_LIST_MODE mode) { m_emEquipListShowMode = mode;};
    E_EQUIP_LIST_MODE GetEquipListShowMode() { return m_emEquipListShowMode; };
    
    
    //被镶嵌，被强化的装备KeyID}
    void SetChosenEquipKeyID(uint32 dwKeyID) { m_dwChosenEquipKeyID = dwKeyID; };
    uint32 GetChosenEquipKeyID() { return m_dwChosenEquipKeyID; };
    
    
    //是否需要跳回宠物详情界面}
    void SetNeedJumpScene(bool isNeed) { m_isNeedJumpScene = isNeed; };
    bool IsNeedJumpScene() { return m_isNeedJumpScene;};
    
    
    //合成界面合成表编号}
    void SetCompoundIndex(uint32 index) { m_dwCompoundIndex = index; };
    uint32 GetCompoundIndex() { return m_dwCompoundIndex; };
    
    
    //合成类编}
    void SetCompoundTabType(SHOW_TAB_TYPE type) { m_emCompoundTabType = type; };
    SHOW_TAB_TYPE GetCompoundTabType() { return m_emCompoundTabType; };
    
    
    
    //装备一览列表偏移}
    void SetEquipOffset(CCPoint pos) { m_EquipOffset = pos; };
    CCPoint GetEquipOffset() { return m_EquipOffset; };
    

    void SetStartClock();
    double GetLostTime();//单位：秒}
    double m_dwStartClock;
    
    //是否是装备强化}
    void setIsEquipShow(bool flag) {m_isEquipShow = flag;};
    bool getIsEquipShow(){return m_isEquipShow;};
private:
    std::vector<uint32> m_arrSelectedEquipId;
};

#define g_EquipData CEquipDataMgr::Get()

class CEquipTeamDataMgr : public Singleton<CEquipTeamDataMgr>
{
public:
    CEquipTeamDataMgr()
    {
       
    };
    
public:
    //初始}
    void initEquipTeam(std::map<uint8, std::map<uint8, uint32> > mapEquipTeam);
    //更新}
    void updateEquipTeam(uint8 site, uint8 part, uint32 equipId);
    //装备}
    void wearEquip(uint8 site, uint8 part, uint32 equipId);
    //卸下}
    void downEquip(uint8 site, uint8 part);
    //获取战位上的装备}
    std::map<uint8, uint32>getEquipsBySite(uint8 site);
    //根据战位和部位获取装备id}
    uint32 getEquipIdBySiteAPart(uint8 site, uint8 part);
    //验证装备是否被穿戴
    bool checkEquipIsWear(uint32 equipId);
private:
    std::map<uint8, std::map<uint8, uint32> > m_mapEquipTeam;
};

#define g_EquipTeamData CEquipTeamDataMgr::Get()
#endif /* defined(__HelloWorld__EquipDataMgr__) */
