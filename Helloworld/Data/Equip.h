//
//  Equip.h
//  HelloWorld
//
//  Created by jun on 14-1-23.
//
//

#ifndef __HelloWorld__Equip__
#define __HelloWorld__Equip__

#include <iostream>
#include "Defines.h"
#include "ConfigGet.h"

using namespace std;

#define EQUIP_SYNTHESIZE(varType, varName, funName)  \
private:                                            \
varType varName;                                \
public:                                             \
void Set##funName(varType var){ varName = var; }\
varType Get##funName(void) const { return varName; }

class CEquip
{
public:
    CEquip();
    ~CEquip();

public:
    void AddConfigData();
    EQUIPNEW_CONFIG_DATA GetConfigData() const;
    LP_EQUIPEVO_CONFIG GetEvoConfigDataByLv(uint8 byEvoLv) const;
    
    //进阶到下一级消耗的金钱}
    const uint32 GetCurStrengthenCostMoney();
    
    //获取当前进阶等级}
    uint16 getEvoLv() const;
    
    uint32 getEquipAttrInfoByType(uint8 byType) const;
    
private:
    EQUIPNEW_CONFIG_DATA m_ConfigData;
    /*
     E_EQUIP_dwRunes1,		// 5 符文 1	}
     E_EQUIP_dwRunes2,		// 6 符文 2}
     E_EQUIP_dwAddHp,		// 7 血量}
     E_EQUIP_dwAddCA,		// 8 普攻}
     E_EQUIP_dwAddCD,		// 9 普防}
     E_EQUIP_dwAddRev,		// 10 回复}
     E_EQUIP_dwAddSA,		// 11 特攻}
     E_EQUIP_dwAddSD,		// 12 特防}
     
     E_EQUIP_dwAddCrit,		// 13 暴击}
     E_EQUIP_dwAddSpeed,		// 14 速度}
     E_EQUIP_dwAddHit,		// 15 命中}
     E_EQUIP_dwAddDodge,		// 16 闪避}
     E_EQUIP_dwAddCritDamage,	// 17 暴伤}
     E_EQUIP_dwAddCritFree,		// 18 抗暴}
     E_EQUIP_dwAddAllAtk,    //全攻}
     */
    
    EQUIP_SYNTHESIZE(uint32, m_dwKeyID, KeyID);         //唯一标识}
    EQUIP_SYNTHESIZE(uint32, m_dwIndex, Index);         //装备的索引}
    EQUIP_SYNTHESIZE(uint8, m_byLv, Level);             //装备的强化等级}
    EQUIP_SYNTHESIZE(uint32, m_dwWearPetID, WearPetID); //装备穿在宠物上的宠物ID}
    
    EQUIP_SYNTHESIZE(uint32, m_dwRunesCnt, RunesCnt);   //符文开启的数量}
    EQUIP_SYNTHESIZE(uint32, m_dwRune1, Rune1);         //镶嵌的符文1}
    EQUIP_SYNTHESIZE(uint32, m_dwRune2, Rune2);         //镶嵌的符文2}
    
    EQUIP_SYNTHESIZE(uint32, m_dwHP, HP);       //血量}
    EQUIP_SYNTHESIZE(uint32, m_dwCAtk, CAtk);     //普攻}
    EQUIP_SYNTHESIZE(uint32, m_dwCDef, CDef);     //普防}
    EQUIP_SYNTHESIZE(uint32, m_dwRev, Rev);     //回复}
    EQUIP_SYNTHESIZE(uint32, m_dwSAtk, SAtk);     //特攻}
    EQUIP_SYNTHESIZE(uint32, m_dwSDef, SDef);     //特防}
    
    EQUIP_SYNTHESIZE(uint32, m_dwCrit, Crit);   //暴击}
    EQUIP_SYNTHESIZE(uint32, m_dwSpeed, Speed);     //速度}
    EQUIP_SYNTHESIZE(uint32, m_dwHit, Hit);     //命中}
    EQUIP_SYNTHESIZE(uint32, m_dwDodge, Dodge);   //闪避}
    EQUIP_SYNTHESIZE(uint32, m_dwCritDamage, CritDamage);     //暴伤}
    EQUIP_SYNTHESIZE(uint32, m_dwCritFree, CritFree);     //抗暴}
    
    EQUIP_SYNTHESIZE(uint32, m_dwAllAtk, AllAtk);     //全攻}
};


#endif /* defined(__HelloWorld__Equip__) */
