//
//  PacketDataMgr.h
//  MyGame
//
//  Created by jun on 14-8-4.
//
//

#ifndef __MyGame__PacketDataMgr__
#define __MyGame__PacketDataMgr__

#include "Singleton.h"
#include "Pet.h"
#include "Item.h"
#include "Equip.h"
#include "Rune.h"
#include <map>
#include "WorldPacket.h"
using namespace std;

class CPacketDataMgr : public Singleton<CPacketDataMgr>
{
public:
    //===========宠==物============}
    //
    //
    //============================
    
    
    //=========普=通=物=品==========}
    //
    bool AddNewItemToMap(const CItem* pItem);
    void ClearItemMap();
    const CItem* GetItemInfoByIndex(uint32 dwIndex);
    void UpdateItemCount(uint32 dwIndex, uint32 dwCount);
    uint32 GetItemCountByIndex(uint32 dwIndex);
    string GetItemIconByIndex(uint32 dwIndex);
    
    
    //==========装==备==============}
    //
    bool AddNewEquipToMap(const CEquip* pEquip);
    void ClearEquipMap();
    const CEquip* GetEquipInfoByKeyID(uint32 dwKeyID);
    const void DelEquipByKeyID(uint32 dwKeyID);
    string GetEquipIconByIndex(uint32 dwIndex);
    uint32 GetAllEquipsCountByIndex(uint32 dwIndex);
    
    //----更新装备相关数据----}
    void EquipPropertyUpdate(uint32 dwEquipKeyID, WorldPacket& packet);
    //进化，重新刷新装备的Index}
    bool UpdateEquipIndex(uint32 dwEquipKeyID, uint32 dwIndex);
    //强化，改变装备等级}
    bool UpdateEquipLevel(uint32 dwEquipKeyID, uint8 byLv);
    //穿着卸下装备，更新对应的宠物KeyID}
    bool UpdateEquipWearPetID(uint32 dwEquipKeyID, uint32 dwPetID);
    //镶嵌，更新装备开孔数}
    bool UpdateEquipRuneCount(uint32 dwEquipKeyID, uint32 dwRuneCount);
    //镶嵌，更新装备对应位置上镶嵌的符文}
    bool UpdateEquipRune(uint32 dwEquipKeyID, uint32 dwRuneKeyID, int nPos);
    //----装备的基础属性----}
    //生命}
//    bool UpdateEquipHp(uint32 dwEquipKeyID, uint32 dwHp);
//    //攻击}
//    bool UpdateEquipAtk(uint32 dwEquipKeyID, uint32 dwAtk);
//    //防御}
//    bool UpdateEquipDef(uint32 dwEquipKeyID, uint32 dwDef);
//    //回复}
//    bool UpdateEquipRev(uint32 dwEquipKeyID, uint32 dwRev);
//    //暴击}
//    bool UpdateEquipLuck(uint32 dwEquipKeyID, uint32 dwLuck);
    //判断对应位置是否有可用装备}
    bool checkHasCanUseEquip(uint8 part, uint32 equipId);
    
    //判断是否有可替换装备
    bool checkHasCanChangeEquip(uint32 petObjId);
    
    //=============符==文==============}
    //
    bool AddNewRuneToMap(const CRune* pRune);
    void ClearRuneMap();
    void DelRuneByKeyID(uint32 dwKeyID);
    const CRune* GetRuneInfoByKeyID(uint32 dwKeyID);
    int GetAllRunesCountByIndex(uint32 dwIndex);
    int GetRunesCountWithoutInlayByIndex(uint32 dwIndex);
    int GetRuneCountByIndex(uint32 dwIndex);
    bool UpdateRuneWearEquipID(uint32 dwRuneKeyID,uint32 dwEquipKeyID);
    string GetRuneIconByIndex(uint32 dwIndex);
    
    //============徽==章===============}
    string GetEmblemIconByIndex(uint32 dwIndex);
    //
    //================================
    
    
    //============通==用===============}
    //
    string GetObjectNameByIndex(uint32 dwIndex);
    string GetObjectIconByIndex(uint32 dwIndex);
    string GetObjectDescByIndex(uint32 dwIndex);
    uint32 GetObjectCountByIndex(uint32 dwIndex);
    //物品品质}
    uint8 getObjectQualityByIndex(uint32 dwIndex);
    //获取品质颜色
    ccColor3B getQualityColor(uint8 quality);
    //物品星级}
    uint8 getObjectStarByIndex(uint32 dwIndex);
    //物品属性文字}
    std::string getAttrText(uint8 attr);
    //物品属性icon}
    CCSpriteFrame* getAttrTexture(uint8 attr);
    //物品品质框}
    CCSpriteFrame* getQualityFrameSF(uint8 quality);
    //物品品质底纹}
    CCSpriteFrame* getQualityBgSF(uint8 quality);
    //物品星级Icon}
    CCSpriteFrame* getStarSF(uint8 starLv);
    
    
    //获取天气图标
    CCSpriteFrame* getWeatherSF(uint8 weather);
    
    
    //获取战斗中宠物框
    CCSpriteFrame* getBattleFrame(uint16 petId);
    //获取竞技场中宠物框
    CCSpriteFrame* getArenaFrame(uint16 petId);
    //获取队伍中宠物框
    CCSpriteFrame* getTeamFrame(uint16 petId);
    //获取主界面中宠物框
    CCSpriteFrame* getMainFrame(uint16 petId);
private:
    map<uint32, CItem*> m_mapItemPacket;
    map<uint32, CEquip*> m_mapEquipPacket;
    map<uint32, CRune*> m_mapRunePacket;
};

#define g_PacketDataMgr CPacketDataMgr::Get()

#endif /* defined(__MyGame__PacketDataMgr__) */
