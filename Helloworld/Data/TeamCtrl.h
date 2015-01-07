//
//  TeamCtrl.h
//  HelloWorld
//
//  Created by long on 13-10-22.
//
//

#ifndef __HelloWorld__TeamCtrl__
#define __HelloWorld__TeamCtrl__

#include <iostream>
#include "Defines.h"
#include "ByteBuffer.h"
#include <map>
#include "ConfigGet.h"
#include "ConfigData.h"

class CTeam;
//class ConfigData;

//typedef std::vector<uint8> VEC_TEAMS;

class CTeamCtrl
{
public:
    
    typedef std::map<uint8, CTeam *> MAP_TEAMS;
    typedef std::vector<uint32> VEC_TEAMS;
    
    enum E_TEAM_STATE
    {
        E_TEAM_STATE_NON = 0,
        E_TEAM_STATE_CHG_LEADER,    //改变队长}
        E_TEAM_STATE_CHG_SITE,           //调换位置}
    };
    
    //摧毁所有队伍对象}
	static void UnInit();
    
    //新增队伍}
	static void NewTeamAdd(CTeam *pTeam);

    //通过obId获取队伍}
	static CTeam * GetTeamByObjId(uint8 byTeamId);
    //更新队伍信息}
	static void TeamPropertyUpdate(uint8 byTeamId, ByteBuffer & data);
    
    static MAP_TEAMS GetAllTeam(){return m_mapTeams;};
    
    
    //保存队伍修改}
    static void SaveTeamUpdate();
    
    //获取当前Team 0-5}
    static uint8 GetCurTeamId(){return m_byCurTeamId;};
    static CTeam *GetCurTeam();
    //设置当前队伍}
    static void ChgCurTeam(uint8 byTeamId);
    
    //改变当前队伍队长位置}
    static void SetTeamLeaderBySite(uint8 bySite);
    //获取当前队伍队长}
    static uint8 GetTeamLeaderSite();
    /** 获取当前队伍队长的图片路径 */
    static const char* GetCurTeamLeaderPath();
    
    /** 获取当前队长的宠物Index */
    static uint16 GetCurTeamLeaderPetIndex();
    
//    /** 获取给定队伍队长的技能名称 */}
//    static const char* GetTeamLeaderSkillName();
//    /** 获取给定队伍队长的技能说明 */}
//    static const char* GetTeamLeaderSkillDes();
    /** 获取给定队伍队长技能 }*/
    static LeaderSkillConfig::STC_LEADER_SKILL_CONFIG* GetTeamLeaderSkill(uint8 byTeamId);
    //改变队长}
    static void SetTeamLeader(uint32 dwPetObjId);
    
    //设置队员}
    static void SetCurTeamMamber(uint32 dwPetObjId);
    //改变队员位置}
    static void ChgTeamMamberSite(uint8 byFromSite, uint8 byToSite);
    //删除队员}
    static void DelTeamMamber(uint8 bySite);
    //设置当前选择的队员位置}
    static void SetSelectedMemberSite(uint8 bySite){m_bySelectMemberSite = bySite;};
    //取当前选择队员的位置}
    static uint8 GetSelectedMemberSite(){return m_bySelectMemberSite;};
    
    
    static bool GetTeamChanged() {
        return m_isTeamChg;
    };
    
    //设置队伍状态(换队长、换位置)}
    static void setTeamState(uint8 state){m_byTeamState = state;};
    static uint8 getTeamState(){return m_byTeamState;};
    
    //获取玩家当前等级可出战宠物个数}
    static uint32 getTeamMemberSize();
    
    //根据宠物Id获取site(当前队伍)}
    static uint8 getSiteByPetId(uint32 petObjId);
    
    static int getCurrentTeamPetNums();
private:
    static MAP_TEAMS m_mapTeams;
    static uint8 m_byCurTeamId;
    static uint8 m_byBattleTeam;
    
    static uint8 m_bySelectMemberSite;
    static bool m_isTeamChg;
    static uint8 m_byTeamState;
};
#endif /* defined(__HelloWorld__TeamCtrl__) */
