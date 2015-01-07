//
//  TeamCtrl.cpp
//  HelloWorld
//
//  Created by long on 13-10-22.
//
//

#include "TeamCtrl.h"
#include "Team.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "GlobalData.h"
#include "BackCtrl.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "Role.h"
//#include "ConfigGet.h"

CTeamCtrl::MAP_TEAMS CTeamCtrl::m_mapTeams;
uint8 CTeamCtrl::m_byCurTeamId = 0;
uint8 CTeamCtrl::m_byBattleTeam = 0;
uint8 CTeamCtrl::m_bySelectMemberSite = 0;
bool CTeamCtrl::m_isTeamChg = false;
uint8 CTeamCtrl::m_byTeamState = 0;

//摧毁所有队伍对象}
void CTeamCtrl::UnInit()
{
    MAP_TEAMS::iterator ii = m_mapTeams.begin();
    
	for(; ii != m_mapTeams.end(); ++ii)
	{
        CC_SAFE_DELETE(ii->second);
	}
	m_mapTeams.clear();
	
    m_byCurTeamId = 0;
}

//新增队伍}
void CTeamCtrl::NewTeamAdd(CTeam *pTeam)
{
    
    MAP_TEAMS::iterator ii = m_mapTeams.find(pTeam->getbyTeamId());
	if (ii != m_mapTeams.end())
	{
		//重复？}
//		assert(false);
//		delete ii->second;
        CC_SAFE_DELETE(ii->second);
		m_mapTeams[pTeam->getbyTeamId()] = pTeam;
		return ;
	}
	m_mapTeams[pTeam->getbyTeamId()] = pTeam;

    if (pTeam->getbyIsBattle()) {
        m_byCurTeamId = pTeam->getbyTeamId();
        m_byBattleTeam = m_byCurTeamId;
    }
}

//通过obId获取队伍}
CTeam * CTeamCtrl::GetTeamByObjId(uint8 dwTeamId)
{
    MAP_TEAMS::iterator ii = m_mapTeams.find(dwTeamId);
    if (ii == m_mapTeams.end()) {
        return NULL;
    }
    return ii->second;
}
//更新队伍信息}
void CTeamCtrl::TeamPropertyUpdate(uint8 byTeamId, ByteBuffer & data)
{
    CTeam *pTeam = GetTeamByObjId(byTeamId);
	assert(pTeam != NULL);
	pTeam->PropertyUpdate(data);
}


//保存队伍修改}
void CTeamCtrl::SaveTeamUpdate()
{
    if (m_byBattleTeam != m_byCurTeamId) {
        CGameSession::SendChdBattleTeam(m_byCurTeamId, m_byBattleTeam);
        m_byBattleTeam = m_byCurTeamId;
    }
    
    if (m_isTeamChg) {
//        BackCtrl::AddWaitScene();
//        return;
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        CGameSession::SendCurTeam(GetCurTeam());
    }
    
    
   
    
    
//    MAP_TEAMS::iterator ii = m_mapTeams.begin();
//    for (; ii != m_mapTeams.end(); ii++) {
//        if (!ii->second) {
//            continue;
//        }
//        CTeam *team = ii->second;
//        CGameSession::SendTeamUpdate(team->getbyTeamId(), team->getbyLeaderSite(),team->getarrPetObId().size()- 1, team->getarrPetObId());
//    }
    
    GlobalData::bNeecConnection = false;
    m_isTeamChg = false;
}


//获取当前Team}
CTeam *CTeamCtrl::GetCurTeam()
{
    return GetTeamByObjId(m_byCurTeamId);
}
//设置当前队伍]}
void CTeamCtrl::ChgCurTeam(uint8 byTeamId)
{
    if (m_byCurTeamId == byTeamId) {
        return;
    }
    CTeam *team1 = GetTeamByObjId(byTeamId);
    CTeam *team2 = GetTeamByObjId(m_byCurTeamId);
    if (!team1 || !team2) {
        return;
    }
    team1->setbyIsBattle(1);
    team2->setbyIsBattle(0);
    m_byCurTeamId = byTeamId;
    m_isTeamChg = true;
    GlobalData::bNeecConnection = true;
}

//改变当前队伍队长位置}
void CTeamCtrl::SetTeamLeaderBySite(uint8 bySite)
{
    CTeam *team = GetCurTeam();
    uint8 byLeaderSite = team->getbyLeaderSite();
    if (byLeaderSite == bySite) {
        return;
    }
    team->setbyLeaderSite(bySite);
    m_isTeamChg = true;
    GlobalData::bNeecConnection = true;
}
//获取当前队伍队长}
uint8 CTeamCtrl::GetTeamLeaderSite()
{
    CTeam *team = GetCurTeam();
    return team->getbyLeaderSite();
}

const char* CTeamCtrl::GetCurTeamLeaderPath()
{
    CTeam* pTeam = GetCurTeam();
    int nLeaderSite = pTeam->getbyLeaderSite();
    if (!nLeaderSite) {
        CCMessageBox("Error", "TeamCtrl::GetCurTeamLeaderPath TeamLeader = 0 Error");
        return "";
    }
    CPet* pPet = CPetCtrl::Get()->GetPetByObjId(pTeam->getarrPetObId()[nLeaderSite]);
    return CPetCtrl::Get()->GetPetHeadPicName(pPet->GetwIndex()).c_str();
}

uint16 CTeamCtrl::GetCurTeamLeaderPetIndex()
{
    CTeam* pTeam = GetCurTeam();
    int nLeaderSite = pTeam->getbyLeaderSite();
    if (!nLeaderSite) {
        CCMessageBox("Error", "TeamCtrl::GetCurTeamLeaderPath TeamLeader = 0 Error");
        return 0;
    }
    CPet* pPet = CPetCtrl::Get()->GetPetByObjId(pTeam->getarrPetObId()[nLeaderSite]);
    return pPet->GetwIndex();
}

LeaderSkillConfig::STC_LEADER_SKILL_CONFIG* CTeamCtrl::GetTeamLeaderSkill(uint8 byTeamId)
{
    CTeam* pTeam = GetTeamByObjId(byTeamId);
    int nLeaderSite = pTeam->getbyLeaderSite();
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG* pLeaderConfig = NULL;
    
    CPet* pPet = CPetCtrl::Get()->GetPetByObjId(pTeam->getarrPetObId()[nLeaderSite]);
    if (!pPet) {
        CCMessageBox("Error", "TeamCtrl::GetTeamLeaderSkillName Pet Error");
    }
    PetConfig::STC_PET_CONFIG* pConfig = GET_CONFIG_STC(PetConfig, pPet->GetwIndex());
    if (!pConfig) {
        CCMessageBox("Error", "TeamCtrl::GetTeamLeaderSkillName PetConfig Error");
    }
    pLeaderConfig = GET_CONFIG_STC(LeaderSkillConfig, pConfig->wLeaderSkillId);
//    if (!pLeaderConfig) {
//        CCMessageBox("Error", "TeamCtrl::GetTeamLeaderSkillName LeaderConfig Error");
//    }
//    strName = pLeaderConfig->strName;
//    return strName.c_str();
    return pLeaderConfig;
}

//改变队长}
void CTeamCtrl::SetTeamLeader(uint32 dwPetObjId)
{
    CTeam *team = GetCurTeam();
    uint8 byLeaderSite = team->getbyLeaderSite();
    team->SetTeamMember(byLeaderSite, dwPetObjId);
    m_isTeamChg = true;
    SaveTeamUpdate();

//    GlobalData::bNeecConnection = true;
}

//设置队员}
void CTeamCtrl::SetCurTeamMamber(uint32 dwPetObjId)
{
    CTeam *team = GetCurTeam();
    uint8 bySite = GetSelectedMemberSite();
//    uint32 oldObjId = team->getarrPetObId()[bySite];
//    DelTeamMamber(bySite);
    team->SetTeamMember(bySite, dwPetObjId);
    m_isTeamChg = true;
    SaveTeamUpdate();
//    m_isTeamChg = true;
//    GlobalData::bNeecConnection = true;
}
//改变队员位置}
void CTeamCtrl::ChgTeamMamberSite(uint8 byFromSite, uint8 byToSite)
{
    CTeam *team = GetCurTeam();
    uint32 fromPet = team->getarrPetObId()[byFromSite];
    uint32 toPet = team->getarrPetObId()[byToSite];
    
    team->SetTeamMember(byToSite, fromPet);
    team->SetTeamMember(byFromSite, toPet);
    
    if (byFromSite == team->getbyLeaderSite()) {
        team->setbyLeaderSite(byToSite);
    }
    else if (byToSite == team->getbyLeaderSite())
    {
        team->setbyLeaderSite(byFromSite);
    }
    
    m_isTeamChg = true;
    GlobalData::bNeecConnection = true;
}
//删除队员}
void CTeamCtrl::DelTeamMamber(uint8 bySite)
{
    CTeam *team = GetCurTeam();
    uint32 objId = team->getarrPetObId()[bySite];
    
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(objId);
    if (!pet) {
        return;
    }
    switch (team->getbyTeamId()) {
        case 0:
            pet->SetbyTeamId1(0);
            break;
        case 1:
            pet->SetbyTeamId2(0);
            break;
        case 2:
            pet->SetbyTeamId3(0);
            break;
        case 3:
            pet->SetbyTeamId4(0);
            break;
        case 4:
            pet->SetbyTeamId5(0);
            break;
        case 5:
            pet->SetbyTeamId6(0);
            break;
            
        default:
            break;
    }
    
    
    team->SetTeamMember(bySite, 0);
    m_isTeamChg = true;
    GlobalData::bNeecConnection = true;
}

//获取玩家当前等级可出战宠物个数(暂时写死)}
uint32 CTeamCtrl::getTeamMemberSize()
{
    CRole *role = CGameSession::GetRole();
    uint32 ret = role->GetdwBattleBagCnt();
    
    return ret;
}

//根据宠物Id获取site(当前队伍)}
uint8 CTeamCtrl::getSiteByPetId(uint32 petObjId)
{
    uint8 site = 0;
    CTeam* team = GetCurTeam();
    for (int i = 0; i < team->getarrPetObId().size(); i++) {
        if (team->getarrPetObId()[i] == petObjId) {
            site = i;
            break;
        }
    }
    return site;
}

int CTeamCtrl::getCurrentTeamPetNums()
{
    int num = 0;
    CTeam* team = GetCurTeam();
    for (int i = 0; i < team->getarrPetObId().size(); i++) {
        if (team->getarrPetObId()[i] != 0) {
            num++;
        }
    }
    return num;
}

