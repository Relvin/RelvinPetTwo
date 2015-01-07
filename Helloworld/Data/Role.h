//
//  Role.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-18.}
//
//

#ifndef __HelloWorld__Role__
#define __HelloWorld__Role__

#include "DynamicStruct.h"
#include "Observer.h"

#define SWEEP_LV 16

#define PROPERTY_DEF(T,name) \
T Get##name() { return m_##name;}; \
void Set##name(T name) { m_##name = name; Notify##name(name);}; \

#define PROPERTY_UNIT_CHILD_DEF(T,name) \
T Get##name() { return m_##name;}; \
void Set##name(T name) { m_##name = name; Notify##name(name); SetbyNotiUnit();}; \

class CRole: public CSubjectRole, public CDynamicStruct
{
public:
    typedef enum _E_PROPERTY_ROLE
	{
        E_ROLE_dwAccountId,
        E_ROLE_strAccount,
        E_ROLE_strUserName,
        E_ROLE_wRoleLv,
        E_ROLE_dwRoleExp,
        E_ROLE_dwEnergy,
        E_ROLE_dwEnergyMax,
        E_ROLE_dwCoin,
        E_ROLE_dwDollar,
        E_ROLE_byVipLv,
        E_ROLE_dwVipExp,
        E_ROLE_wPhoto,
        E_ROLE_dwResFarmNum,
        E_ROLE_byArenaUseCnt,
        E_ROLE_dwReputation,
        E_ROLE_wPassMapId,
        E_ROLE_wPassStageId,
        E_ROLE_dwItemBagCnt,
        E_ROLE_dwRoleMaxExp,
        E_ROLE_dwEnergyRecTime,
        E_ROLE_dwPetBagCnt,
        E_ROLE_byArenaGroup,
        E_ROLE_byEnergyRewStatus,
        E_ROLE_dwSevenRewDay,
        E_ROLE_bySevenRewStatus,
        E_ROLE_dwThirtyRewDay,
        E_ROLE_byThirtyRewStatus,
        E_ROLE_dwBattleBagCnt,
        E_ROLE_dwWorldInitTime,
        E_ROLE_dwScore,      // 祭炼}
        E_ROLE_wGuideTrigger,
        E_ROLE_wHeroStage,
        E_ROLE_wHeroMap,
        E_ROLE_byIsAutoFight,
        E_ROLE_dwSweepUseTime,
        E_ROLE_dwSweepCDTime,
        E_ROLE_dwFightScore,
        E_ROLE_dwShareCnt,
	}E_PROPERTY_ROLE;
    
	CRole();
	~CRole();
    
	////////////////////////////////////
    const uint32 GetdwAccountId() { return m_dwAccountId; };
    void SetdwAccountId(uint32 dwAccountId) {
        m_dwAccountId = dwAccountId;
        NotifydwAccountId(m_dwAccountId);
    }
    
    PROPERTY_DEF(const std::string &, strAccount);
    PROPERTY_DEF(const std::string &, strUserName);
    
//	const std::string & GetstrAccount() { return m_strAccount;};
//	void SetstrAccount(const std::string & strAccount)
//	{
//		m_strAccount = strAccount;
//		NotifystrUserName(m_strAccount);
//	}
//    
//	const std::string & GetstrUserName() { return m_strUserName;};
//	void SetstrUserName(const std::string & strUserName)
//	{
//		m_strUserName = strUserName;
//		NotifystrUserName(m_strUserName);
//	}
    
    PROPERTY_DEF(uint16, wRoleLv);
    PROPERTY_DEF(uint32, dwRoleExp);
    PROPERTY_DEF(uint32, dwRoleMaxExp);
    PROPERTY_DEF(uint32, dwEnergy);
    PROPERTY_DEF(uint32, dwEnergyMax);
    PROPERTY_DEF(uint32, dwCoin);
    PROPERTY_DEF(uint32, dwDollar);
    PROPERTY_DEF(uint8, byVipLv);
    PROPERTY_DEF(uint32, dwVipExp);
    PROPERTY_DEF(uint16, wPhoto);
    PROPERTY_DEF(uint32, dwResFarmNum);
    PROPERTY_DEF(uint8, byArenaUseCnt);
    PROPERTY_DEF(uint32, dwReputation);
    PROPERTY_DEF(uint16, wPassMapId);
    PROPERTY_DEF(uint16, wPassStageId);
    PROPERTY_DEF(uint32, dwItemBagCnt);
    PROPERTY_DEF(uint32, dwEnergyRecTime);
    PROPERTY_DEF(uint32, dwPetBagCnt);
    PROPERTY_DEF(uint8, byArenaGroup);
    PROPERTY_DEF(uint8, byEnergyRewStatus);
    PROPERTY_DEF(uint32, dwSevenRewDay);
    PROPERTY_DEF(uint8, bySevenRewStatus);
    PROPERTY_DEF(uint32, dwThirtyRewDay);
    PROPERTY_DEF(uint8, byThirtyRewStatus);
    PROPERTY_DEF(uint32, dwBattleBagCnt);
    PROPERTY_DEF(uint32, dwWorldInitTime);
    PROPERTY_DEF(uint32, dwScore);
    PROPERTY_DEF(uint16, wGuideTrigger);
    PROPERTY_DEF(uint16, wHeroStage);
    PROPERTY_DEF(uint16, wHeroMap);
    PROPERTY_DEF(uint16, byIsAutoFight);
    PROPERTY_DEF(uint32, dwSweepUseTime);
    PROPERTY_DEF(uint32, dwSweepCDTime);
    PROPERTY_DEF(uint32, dwRoleFightValue);
    PROPERTY_DEF(uint32, dwShareCnt);
    
    
    PROPERTY_DEF(uint8, byNotiUnit);
    PROPERTY_DEF(uint8, byNotiGacha);
    PROPERTY_DEF(uint8, byNotiShop);
    PROPERTY_DEF(uint8, byNotiActive);
    PROPERTY_DEF(uint8, byNotiFriend);
    PROPERTY_DEF(uint8, byNoti30Day);
    PROPERTY_DEF(uint8, byNotiReward);
    PROPERTY_DEF(uint8, byNotiMystery);
    PROPERTY_UNIT_CHILD_DEF(uint8, byNotiNewPet);
    PROPERTY_UNIT_CHILD_DEF(uint8, byNotiNewEquip);
    PROPERTY_UNIT_CHILD_DEF(uint8, byNotiNewEmblem);
    PROPERTY_DEF(uint8, byNotiAward);
    PROPERTY_UNIT_CHILD_DEF(uint8, byNotiBox);
    PROPERTY_UNIT_CHILD_DEF(uint8, byNotiChips);
private:
	uint32 m_dwAccountId;
	std::string m_strAccount;
	std::string m_strUserName;
    uint16 m_wRoleLv;
    uint32 m_dwRoleExp;
    uint32 m_dwEnergy;
    uint32 m_dwEnergyMax;
    uint32 m_dwCoin;
    uint32 m_dwDollar;
    uint8 m_byVipLv;
    uint32 m_dwVipExp;
    uint16 m_wPhoto;
    uint32 m_dwResFarmNum;
    uint8 m_byArenaUseCnt;
    uint32 m_dwReputation;
    uint16 m_wPassMapId;
    uint16 m_wPassStageId;
    uint32 m_dwItemBagCnt;
    uint32 m_dwRoleMaxExp;
    uint32 m_dwEnergyRecTime;
    uint32 m_dwPetBagCnt;
    uint8 m_byArenaGroup;
    uint8 m_byEnergyRewStatus;
    uint32 m_dwSevenRewDay;
    uint8 m_bySevenRewStatus;
    uint32 m_dwThirtyRewDay;
    uint8 m_byThirtyRewStatus;
    uint32 m_dwBattleBagCnt;
    uint32 m_dwWorldInitTime;
    uint32 m_dwScore;
    uint16 m_wGuideTrigger;
    uint16 m_wHeroStage;
    uint16 m_wHeroMap;
    uint8 m_byIsAutoFight;
    uint32 m_dwSweepUseTime;
    uint32 m_dwSweepCDTime;
    uint32 m_dwRoleFightValue;
    uint32 m_dwShareCnt;
    
    // notification
    uint8 m_byNotiUnit;
    uint8 m_byNotiGacha;
    uint8 m_byNotiShop;
    uint8 m_byNotiActive;
    uint8 m_byNotiFriend;
    uint8 m_byNoti30Day;
    uint8 m_byNotiReward;
    uint8 m_byNotiMystery;  // 神秘商店}
    uint8 m_byNotiNewPet;
    uint8 m_byNotiNewEquip;
    uint8 m_byNotiNewEmblem;
    uint8 m_byNotiAward;
    uint8 m_byNotiBox;  //物品中箱子
    uint8 m_byNotiChips; //各种碎片
    
private:
    void SetbyNotiUnit();
    
    std::vector<uint8*> arrUnitChildren;
};
#endif /* defined(__HelloWorld__Role__) */
