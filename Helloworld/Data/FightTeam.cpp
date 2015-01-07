//
//  FightTeam.cpp
//  HelloWorld
//
//  Created by long on 13-9-3.
//
//

#include "FightTeam.h"
#include "FightPet.h"
FightTeam::FightTeam()
{
    m_bLastDeadFlag = false;
}

FightTeam::~FightTeam()
{
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        delete it->second;
    }
}

FightTeam *FightTeam::creat( std::vector<STC_FIGHT_PET_INFO> vecPet)
{
    FightTeam *team = new FightTeam();
    team->LoadTeamInfo(vecPet);
    
    return team;
}

void FightTeam::LoadTeamInfo( std::vector<STC_FIGHT_PET_INFO> vecPet)
{
	m_vecFightList.clear();
//	std::vector<STC_FIGHT_PET_INFO>::iterator it = vecPet->begin();
    uint32 dwTotalCur = 0;
    uint32 dwTotalMax = 0;
	for ( int i = 0; i < vecPet.size(); i++)
	{
		STC_FIGHT_PET_INFO info = vecPet[i];
		FightPet* pFightPet =  FightPet::creat(&info, this);
        if (!pFightPet) {
            continue;
        }
        
        CCLOG("~~~~~pet Id : %d, ~~~~~ Hp : %d~~~~~~~~",info.petInfo.wBattleIndex, info.petInfo.wHP);
        
        dwTotalCur += pFightPet->getPetInfo().wCurHP;
        dwTotalMax += pFightPet->getPetInfo().wHP;
		m_vecFightList[info.petInfo.wBattleIndex] = pFightPet;
	}
    m_dwTeamHpMax = dwTotalMax;
	m_dwTeamHp = dwTotalCur;
    m_dwCurDropHeart = 0;
//    InitTeamHp();
}

//void FightTeam::UpdateTeamAfterRound(uint8 byCurRound)
//{
//	MapFightTeam::iterator it = m_vecFightList.begin();
//	for ( ; it != m_vecFightList.end(); ++it)
//	{
//        (*it)->up(byCurRound);
//	}
//}


//uint32 FightTeam::GetTeamAverageLv()
//{
//	uint32 dwTotal = 0;
//	uint8 byTeamSize = 0;
//	for (VecFightTeam::iterator it = m_vecFightList.begin(); it != m_vecFightList.end(); ++it)
//	{
//		if ((*it))
//		{
//			byTeamSize++;
//			dwTotal += (*it)->GetPetLv();
//		}
//	}
//	return dwTotal/byTeamSize;
//    
//}


void FightTeam::InitTeamHp()
{
	uint32 dwTotal = 0;
	MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
		if (it->second)
		{
			dwTotal += it->second->getPetInfo().wHP;
		}
	}
	m_dwTeamHpMax = dwTotal;
	m_dwTeamHp = dwTotal;
}

void FightTeam::InitLeaderSpell()
{
	
}

void FightTeam::UpdateBuffPerRound(uint16 wRound)
{
	MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (!it->second) {
            continue;
        }
		it->second->updateHpBuff(wRound);
	}
}
void FightTeam::InitBuff(uint16 wRound)
{
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (!it->second) {
            continue;
        }
		it->second->waveStartPassvieSkill(wRound);
	}
}
void FightTeam::waveEndPasskill(uint16 wRound)
{
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (!it->second) {
            continue;
        }
		it->second->waveEndPassvieSkill(wRound);
	}
}
//回合开始，检查自动触发的被动技能}
void FightTeam::beforeRoundPassvieSkill(uint16 wRound)
{
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (!it->second) {
            continue;
        }
		it->second->beforeRoundPassvieSkill(wRound);
	}
}
//回合结束，检查自动触发的被动技能}
void FightTeam::afterRoundPassiveSkill(uint16 wRound)
{
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (!it->second) {
            continue;
        }
		it->second->afterRoundPassiveSkill(wRound);
	}
}


void FightTeam::updatePower(uint16 wRound)
{
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (!it->second) {
            continue;
        }
//		it->second->updatePower(wRound);
	}
}

uint16 FightTeam::getLivePetCount()
{
    uint16 ret = 0;
    
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (!it->second || (it->second->getIsCanDead() && it->second->getCurHP() == 0)) {
            continue;
        }
		ret++;
	}    
    
    return ret;
}

uint16 FightTeam::getDeadPetCount()
{
    uint16 ret = 0;
    
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (it->second &&  it->second->getCurHP() == 0) {
            ret++;
        }
	}
    
    return ret;
}

//选出可以吃心珠的宠}
/*
1		满血的宠物不吸收心珠
2		空血的宠物随机进行分配
3       如果所有宠物都满血，随即分配
*/
uint16 FightTeam::eatHeart(uint16 wRound)
{
    std::vector<uint16> arrPetId;
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        FightPet *pet = it->second;
        if (!pet || (pet->getIsCanDead() && pet->getCurHP() == 0)
            || pet->getCurHP() == pet->getPetInfo().wHP) {
            continue;
        }
        arrPetId.push_back(it->first);
		//hp += pet->eatHeart(1, wRound);}
	}
    if (arrPetId.size() == 0) {
        it = m_vecFightList.begin();
        for ( ; it != m_vecFightList.end(); ++it)
        {
            FightPet *pet = it->second;
            if (!pet || (pet->getIsCanDead() && pet->getCurHP() == 0)) {
                continue;
            }
            arrPetId.push_back(it->first);
            //hp += pet->eatHeart(1, wRound);
        }
    }
    
    if (arrPetId.size() > 0) {
        int i = rand() % arrPetId.size();
        return arrPetId[i];
    }
    return 0;
}
//获取掉落心珠}
uint32 FightTeam::getDropHeart(uint8 enemyCnt)
{
    int cnt = 0;
    //按照5回合，6个人攻击来算此次攻击总共掉落心珠数（群攻时是总共掉落）}
    cnt = m_dwMaxHeart / 5 / 6;
    if (cnt + m_dwCurDropHeart > m_dwMaxHeart) {
        cnt = m_dwMaxHeart - m_dwCurDropHeart;
    }
    m_dwCurDropHeart += cnt;
    
    //如果是群攻，从被攻击者中选出2个掉落心珠（即将掉落的心珠数一分为2）}
    if (enemyCnt > 1) {
        cnt *= 0.5;
    }
    return cnt;
}

//获取队伍的总回复值}
int FightTeam::getRecover(uint16 wRound)
{
    int rec = 0;
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (!it->second || (it->second->getIsCanDead() && it->second->getCurHP() == 0)) {
            continue;
        }
		rec += it->second->getRecover(wRound);
	}
    return rec;
}

void FightTeam::setIsCanDead(bool var)
{
    MapFightTeam::iterator it = m_vecFightList.begin();
	for ( ; it != m_vecFightList.end(); ++it)
	{
        if (!it->second) {
            continue;
        }
		it->second->setIsCanDead(var);
	}
}

void FightTeam::setMaxDropHeart(uint32 dwMaxHeart)
{
    m_dwMaxHeart = dwMaxHeart;
    //从所有成员中，取出3个，赋予心珠，这3个被攻击时概率掉落心珠，}
    //如果成员少于3个，则全部赋予心珠}
    std::vector<uint16> arrPetIndex = chooseInRandom(this, 3);
    int n = arrPetIndex.size();
    for (int i = 0; i < n; i++) {
        FightPet *pet = m_vecFightList[arrPetIndex[i]];
        if (!pet) {
            continue;
        }
        pet->setMaxDropHeart(m_dwMaxHeart / n);
        if (i == 0) {
            pet->setMaxDropHeart(m_dwMaxHeart%n + m_dwMaxHeart / n);
        }
    }    
}

std::vector<uint16> FightTeam::chooseInRandom(FightTeam *team, uint8 count)
{
    std::vector<uint16> arrEnemy;
    if (count == 0) {
        return arrEnemy;
    }
    
    std::vector<uint16> arrRand;
    MapFightTeam mapPet = team->GetTeam();
    MapFightTeam::iterator it = mapPet.begin();
    for (; it != mapPet.end(); it++) {
        if (!it->second) {
            continue;
        }
        if (it->first > PetCnt && it->second->getCurHP() == 0) {
            continue;
        }
        arrRand.push_back(it->first);
    }
    
    int i = -1;

    for (int j = arrRand.size(); j > 0; j--) {
        if (count <= 0) {
            break;
        }
        i = (int)(rand() % j);
        arrEnemy.push_back(arrRand[i]);
        arrRand[i] = arrRand[j - 1];
        count--;
    }
    
    return arrEnemy;
}