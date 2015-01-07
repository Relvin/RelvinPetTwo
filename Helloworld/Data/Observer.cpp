#include <set>
#include "Observer.h"

#define FOR_EACH_SET(ii,container,T) \
T::iterator ii = container.begin();\
for(;ii != container.end(); ++ii)\

#define ROLE_NOTIFY_DEF(T,name) \
	void CSubjectRole::Notify##name(T name)\
	{\
		FOR_EACH_SET(ii,m_setObservers,std::set<CObserverRole *>)\
		{\
			(*ii)->name##Changed(name);\
		}\
	}\


CSubjectRole::CSubjectRole()
{
	m_setObservers.clear();
}
CSubjectRole::~CSubjectRole()
{

}
void CSubjectRole::Attach(CObserverRole * pObserver)
{
	m_setObservers.insert(pObserver);
}
void CSubjectRole::Detach(CObserverRole * pObserver)
{
	m_setObservers.erase(pObserver);
}

/*
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
*/

void CSubjectRole::NotifystrUserName(const std::string & strUserName)
{
	FOR_EACH_SET(ii,m_setObservers,std::set<CObserverRole *>)
	{
		(*ii)->strUserNameChanged(strUserName);
	}
}

//void CSubjectRole::NotifyTujianInfoChanged(uint16 wCatch, uint16 wVisited)
//{
//	FOR_EACH_SET(ii,m_setObservers,std::set<CObserverRole *>)
//	{
//		(*ii)->TujianInfoChanged(wCatch,wVisited);
//	}
//}

ROLE_NOTIFY_DEF(uint32, dwAccountId);
ROLE_NOTIFY_DEF(const std::string &, strAccount);
ROLE_NOTIFY_DEF(uint16, wRoleLv);
ROLE_NOTIFY_DEF(uint32, dwRoleExp);
ROLE_NOTIFY_DEF(uint32, dwEnergy);
ROLE_NOTIFY_DEF(uint32, dwEnergyMax);
ROLE_NOTIFY_DEF(uint32, dwCoin);
ROLE_NOTIFY_DEF(uint32, dwDollar);
ROLE_NOTIFY_DEF(uint8, byVipLv);
ROLE_NOTIFY_DEF(uint32, dwVipExp);
ROLE_NOTIFY_DEF(uint16, wPhoto);
ROLE_NOTIFY_DEF(uint32, dwResFarmNum);
ROLE_NOTIFY_DEF(uint8, byArenaUseCnt);
ROLE_NOTIFY_DEF(uint32, dwReputation);
ROLE_NOTIFY_DEF(uint16, wPassMapId);
ROLE_NOTIFY_DEF(uint16, wPassStageId);
ROLE_NOTIFY_DEF(uint32, dwItemBagCnt);
ROLE_NOTIFY_DEF(uint32, dwRoleMaxExp);
ROLE_NOTIFY_DEF(uint32, dwEnergyRecTime);
ROLE_NOTIFY_DEF(uint32, dwPetBagCnt);
ROLE_NOTIFY_DEF(uint8, byArenaGroup);
ROLE_NOTIFY_DEF(uint8, byEnergyRewStatus);
ROLE_NOTIFY_DEF(uint32, dwSevenRewDay);
ROLE_NOTIFY_DEF(uint8, bySevenRewStatus);
ROLE_NOTIFY_DEF(uint32, dwThirtyRewDay);
ROLE_NOTIFY_DEF(uint8, byThirtyRewStatus);
ROLE_NOTIFY_DEF(uint32, dwBattleBagCnt);
ROLE_NOTIFY_DEF(uint32, dwWorldInitTime);
ROLE_NOTIFY_DEF(uint32, dwScore);
ROLE_NOTIFY_DEF(uint16, wGuideTrigger);
ROLE_NOTIFY_DEF(uint16, wHeroStage);
ROLE_NOTIFY_DEF(uint16, wHeroMap);
ROLE_NOTIFY_DEF(uint8, byIsAutoFight);
ROLE_NOTIFY_DEF(uint32, dwSweepUseTime);
ROLE_NOTIFY_DEF(uint32, dwSweepCDTime);
ROLE_NOTIFY_DEF(uint32, dwRoleFightValue);
ROLE_NOTIFY_DEF(uint32, dwShareCnt);

ROLE_NOTIFY_DEF(uint8, byNotiUnit);
ROLE_NOTIFY_DEF(uint8, byNotiGacha);
ROLE_NOTIFY_DEF(uint8, byNotiShop);
ROLE_NOTIFY_DEF(uint8, byNotiActive);
ROLE_NOTIFY_DEF(uint8, byNotiFriend);
ROLE_NOTIFY_DEF(uint8, byNoti30Day);
ROLE_NOTIFY_DEF(uint8, byNotiReward);
ROLE_NOTIFY_DEF(uint8, byNotiMystery);
ROLE_NOTIFY_DEF(uint8, byNotiNewPet);
ROLE_NOTIFY_DEF(uint8, byNotiNewEquip);
ROLE_NOTIFY_DEF(uint8, byNotiNewEmblem);
ROLE_NOTIFY_DEF(uint8, byNotiAward);
ROLE_NOTIFY_DEF(uint8, byNotiBox);
ROLE_NOTIFY_DEF(uint8, byNotiChips);

CObserverMsg::CObserverMsg()
{

}
CObserverMsg::~CObserverMsg()
{

}
