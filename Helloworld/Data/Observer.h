
#ifndef _OBSERVER_H
#define _OBSERVER_H
#include <set>
#include "Defines.h"
#include "WorldPacket.h"

#define OBSERVERROLE_HEADER_FUNC_DEF(T,name) \
	virtual void name##Changed(T name) {};\


#define SUBJECTROLE_HEADER_FUNC_DEF(T,name) \
	virtual void Notify##name(T name);\


class CObserverRole
{
public:
	CObserverRole() {};
	virtual ~CObserverRole() {};
	
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwAccountId);
    OBSERVERROLE_HEADER_FUNC_DEF(const std::string &, strAccount);
    OBSERVERROLE_HEADER_FUNC_DEF(const std::string &, strUserName);
    OBSERVERROLE_HEADER_FUNC_DEF(uint16, wRoleLv);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwRoleExp);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwEnergy);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwEnergyMax);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwCoin);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwDollar);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byVipLv);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwVipExp);
    OBSERVERROLE_HEADER_FUNC_DEF(uint16, wPhoto);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwResFarmNum);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byArenaUseCnt);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwReputation);
    OBSERVERROLE_HEADER_FUNC_DEF(uint16, wPassMapId);
    OBSERVERROLE_HEADER_FUNC_DEF(uint16, wPassStageId);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwItemBagCnt);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwRoleMaxExp);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwEnergyRecTime);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwPetBagCnt);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byArenaGroup);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byEnergyRewStatus);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwSevenRewDay);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, bySevenRewStatus);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwThirtyRewDay);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byThirtyRewStatus);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwBattleBagCnt);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwWorldInitTime);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwScore);
    OBSERVERROLE_HEADER_FUNC_DEF(uint16, wGuideTrigger);
    OBSERVERROLE_HEADER_FUNC_DEF(uint16, wHeroStage);
    OBSERVERROLE_HEADER_FUNC_DEF(uint16, wHeroMap);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byIsAutoFight);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwSweepUseTime);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwSweepCDTime);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwRoleFightValue);
    OBSERVERROLE_HEADER_FUNC_DEF(uint32, dwShareCnt);
//	virtual void TujianInfoChanged(uint16 wCatch, uint16 wVisited) {};
    
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiUnit);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiGacha);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiShop);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiActive);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiFriend);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNoti30Day);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiReward);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiMystery);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiNewPet);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiNewEquip);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiNewEmblem);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiAward);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiBox);
    OBSERVERROLE_HEADER_FUNC_DEF(uint8, byNotiChips);
};

class CSubjectRole
{
public:
	CSubjectRole();
	virtual ~CSubjectRole();
	
	virtual void Attach(CObserverRole *);
	virtual void Detach(CObserverRole *);

    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwAccountId);
    SUBJECTROLE_HEADER_FUNC_DEF(const std::string &, strAccount);
    SUBJECTROLE_HEADER_FUNC_DEF(const std::string &, strUserName);
    SUBJECTROLE_HEADER_FUNC_DEF(uint16, wRoleLv);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwRoleExp);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwEnergy);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwEnergyMax);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwCoin);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwDollar);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byVipLv);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwVipExp);
    SUBJECTROLE_HEADER_FUNC_DEF(uint16, wPhoto);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwResFarmNum);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byArenaUseCnt);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwReputation);
    SUBJECTROLE_HEADER_FUNC_DEF(uint16, wPassMapId);
    SUBJECTROLE_HEADER_FUNC_DEF(uint16, wPassStageId);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwItemBagCnt);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwRoleMaxExp);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwEnergyRecTime);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwPetBagCnt);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byArenaGroup);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byEnergyRewStatus);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwSevenRewDay);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, bySevenRewStatus);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwThirtyRewDay);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byThirtyRewStatus);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwBattleBagCnt);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwWorldInitTime);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwScore);
    SUBJECTROLE_HEADER_FUNC_DEF(uint16, wGuideTrigger);
    SUBJECTROLE_HEADER_FUNC_DEF(uint16, wHeroStage);
    SUBJECTROLE_HEADER_FUNC_DEF(uint16, wHeroMap);
    
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byIsAutoFight);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwSweepUseTime);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwSweepCDTime);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwRoleFightValue);
    SUBJECTROLE_HEADER_FUNC_DEF(uint32, dwShareCnt);
//	virtual void NotifyTujianInfoChanged(uint16 wCatch, uint16 wVisited);
    
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiUnit);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiGacha);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiShop);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiActive);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiFriend);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNoti30Day);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiReward);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiMystery);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiNewPet);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiNewEquip);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiNewEmblem);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiAward);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiBox);
    SUBJECTROLE_HEADER_FUNC_DEF(uint8, byNotiChips);
private:
	std::set<CObserverRole *> m_setObservers;
};


class CObserverMsg
{
public:
	CObserverMsg();
	virtual ~CObserverMsg();

    virtual bool NotifyErrorMsg(uint16 wErrorNo) { return false; };
	virtual void FriendInfo(uint32 dwFriendId,const std::string & strInfo) {};

	//
	virtual void HandlerCmdMsg(const std::string & strInfo) {};

    //重新刷界面}
	virtual void RefeashLayer() {};
	
	//战斗信息}
	virtual void HandlerBattleInfo(WorldPacket & data) {};
    
	//进化成功}
	virtual void HandlerEvolveResult(uint32 dwPetObjId) {};
    
	//交配成功}
	virtual void HandlerMateResult() {};

	//...
private:

};

#endif