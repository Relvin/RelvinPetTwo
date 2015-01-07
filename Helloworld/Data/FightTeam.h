//
//  FightTeam.h
//  HelloWorld
//
//  Created by long on 13-9-3.
//
//

#ifndef __HelloWorld__FightTeam__
#define __HelloWorld__FightTeam__

#include <iostream>
#include "Defines.h"
#include "PetBattleData.h"

class FightPet;


class FightTeam
{
public:
	typedef std::map<uint16, FightPet*> MapFightTeam;
    
	enum E_TEAM_TYPE
	{
		E_TEAM_TYPE_MY,
		E_TEAM_TYPE_ENERMY,
		E_TEAM_TYPE_BOSS,
	};
public:
	FightTeam();
	~FightTeam();
    
    static FightTeam *creat( std::vector<STC_FIGHT_PET_INFO> vecPet);
    
	void LoadTeamInfo( std::vector<STC_FIGHT_PET_INFO> vecPet);
    
	uint32 GetTeamHpMax() { return m_dwTeamHpMax; }
	uint32 GetTeamHp() { return m_dwTeamHp; }
    
	void SetTeamHpMax(uint32 dwNum) { m_dwTeamHpMax = dwNum; }
	void SetTeamHp(uint32 dwNum) { m_dwTeamHp = dwNum; }

    void setMaxDropHeart(uint32 dwMaxHeart);
    uint32 getMaxDropHeart(){return m_dwMaxHeart;};
    CC_MY_PROPERTY(uint32, m_dwCurDropHeart, CurDropHeart);
    
	void AddTeamHp(int nNum)
	{
		if (!nNum || m_dwTeamHp <= 0)
		{
			return ;
		}
		int nCurTeamHp = m_dwTeamHp + nNum;
		if (nCurTeamHp < 0)
		{
			nCurTeamHp = 0;
		}
		if (nCurTeamHp > m_dwTeamHpMax)
		{
			nCurTeamHp = m_dwTeamHpMax;
		}
        
		SetTeamHp(nCurTeamHp);
	}
    
    void loseTeamHp(int nNum)
    {
        if (!nNum || m_dwTeamHp <= 0)
		{
			return ;
		}
        int nCurTeamHp = m_dwTeamHp - nNum;
		if (nCurTeamHp < 0)
		{
			nCurTeamHp = 0;
		}
		if (nCurTeamHp > m_dwTeamHpMax)
		{
			nCurTeamHp = m_dwTeamHpMax;
		}
        
		SetTeamHp(nCurTeamHp);
    }
    
    
    //获取掉落心珠}
    uint32 getDropHeart(uint8 enemyCnt);
    
    uint16 getLivePetCount();
    uint16 getDeadPetCount();
    
	void SetTeamType(uint8 byType) { m_byTeamType = byType; }
	uint8 GetTeamType() { return m_byTeamType; }
    
	MapFightTeam& GetTeam() { return m_vecFightList; }
    
	void UpdateBuffPerRound(uint16 wRound);
    void InitBuff(uint16 wRound);
    
    void waveEndPasskill(uint16 wRound);
    //回合开始，检查自动触发的被动技能}
    void beforeRoundPassvieSkill(uint16 wRound);
    //回合结束，检查自动触发的被动技能}
    void afterRoundPassiveSkill(uint16 wRound);
    
    uint16 eatHeart(uint16 wRound);
    
    void updatePower(uint16 wRound);
    
    bool getLastDeadFlag(){return m_bLastDeadFlag;};
    void setLastDeadFlag(bool flag){m_bLastDeadFlag = flag;};
    
    int getRecover(uint16 wRound);
    
    void setIsCanDead(bool var);
private:
	void InitTeamHp();
    
	void InitLeaderSpell();
    
    std::vector<uint16> chooseInRandom(FightTeam *team, uint8 count);
    
private:
	//CRole* m_pRole;
    
	uint32	m_dwTeamHp;
	uint32	m_dwTeamHpMax;

    uint32 m_dwMaxHeart;
    
	uint32	m_dwPetLeaderObjId;
    
	MapFightTeam m_vecFightList;
    
	uint8 m_byTeamType;
    
    bool m_bLastDeadFlag;
    
};
#endif /* defined(__HelloWorld__FightTeam__) */
