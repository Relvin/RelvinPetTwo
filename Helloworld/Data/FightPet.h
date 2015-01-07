//
//  FightPet.h
//  HelloWorld
//
//  Created by long on 13-8-26.
//
//

#ifndef __HelloWorld__FightPet__
#define __HelloWorld__FightPet__

#include <iostream>
#include "PetBattleData.h"
//#include "CCPlatformMacros.h"
#include "EnumDefines.h"
#include "FightTeam.h"
class FightPet
{
public:
    FightPet();
    ~FightPet();
    static FightPet *creat(STC_FIGHT_PET_INFO *info, FightTeam *myTeam);
    
    bool init(STC_FIGHT_PET_INFO *info, FightTeam *myTeam);

public:
    //我的队伍}
    void setMyTeam(FightTeam* var){ m_MyTeam = var;};
    FightTeam* getMyTeam(void ){return m_MyTeam;};
    //精灵基本信息}
    void setPetInfo(STC_PET_INFO var){ m_petInfo = var;};
    STC_PET_INFO getPetInfo(void ){return m_petInfo;};
    
    
    //队长}
    CC_MY_PROPERTY(uint32, m_LeaderSkillId, LeaderSkillId)

    //携带的Buff}
    std::map<uint8, std::vector<STC_BUFF> > getMapBuff(){return m_mapBuff;};
    void setMapBuff(std::map<uint8, std::vector<STC_BUFF> > mapBuff)
    {
        m_mapBuff = mapBuff;
    };
    
    std::map<uint8, std::vector<STC_BUFF> > getMapSpecBuff(){return m_mapSpecBuff;};
    
    CC_MY_PROPERTY(std::vector<STC_BUFF_VALUE>, m_arrBufValue, ArrBuffValue);
    
    //携带的Effect()}
    CC_MY_PROPERTY(std::vector<STC_EFFECT>, m_arrEff, ArrEff)
    CC_MY_PROPERTY(bool, m_isCanDead, IsCanDead);
    //当前血量}
    CC_MY_PROPERTY(int, m_curHP, CurHP)
    //当前气量}
    CC_MY_PROPERTY(int, m_curPower, CurPower)
    //当前掉落心珠数}
    CC_MY_PROPERTY(uint32, m_curHeart, CurHeart);
    //最大掉落心珠数}
    CC_MY_PROPERTY(uint32, n_MaxDropHeart, MaxDropHeart);
    
    //连击次数}
    CC_MY_PROPERTY(uint16, m_DoubleCount, DoubleCount);
    
    //是否是Boss}
    CC_MY_PROPERTY(bool, m_IsBoss, IsBoss);
    
    //是否在等待技能释放}
    CC_MY_PROPERTY(bool, m_IsWaitSkill, IsWaitSkill);
    
    //连携加成}
    CC_MY_PROPERTY(uint16, m_wLianXieAdd, LianXieAdd);
    //连携状态}
    CC_MY_PROPERTY(uint8, m_byLianXieState, LianXieState);
    
    //获取当前速度}
    uint32 getCurSpeed(uint8 round);
    
    //组攻击包}
    STC_BATTLE_DATA getAttackData(STC_START_BATTLE_DATA sData , uint16 wCurRound);

    
    std::vector<STC_TRIGGERED_PSKILL> getTrigPassive(){return arrTriggerPassiveSkill;};


private:
    FightTeam *m_MyTeam;
    STC_PET_INFO m_petInfo;
    
    //携带的Buff}
    std::map<uint8, std::vector<STC_BUFF> > m_mapBuff;
    std::map<uint8, std::vector<STC_BUFF> > m_mapSpecBuff;
public:
    //波次开始时检查被动技能触发}
    void waveStartPassvieSkill(uint16 wRound);
    
    //波次结束时检查被动技能触发}
    void waveEndPassvieSkill(uint16 wRound);
    
    //回合开始，检查自动触发的被动技能}
    void beforeRoundPassvieSkill(uint16 wRound);
    
    //回合结束，检查自动触发的被动技能}
    void afterRoundPassiveSkill(uint16 wRound);
    
    //更新Buff}
    void updateBuff(uint16 wRound);
    void updateHpBuff(uint16 wRound);
    //Buff回血或掉血生效}
    void buffAddorLoseHp(bool flag);
        
    std::vector<STC_PASSIVE_SKILL> checkPassvie(uint16 wRound, uint8 eBattleTiem, uint8 triggerType, uint32 skillId = 0, FightPet *enemy = NULL);
    //受伤触发}
    std::vector<STC_TRIGGERED_PSKILL> checkPassiveHurt(FightPet* enemy);
    //闪避触发}
    std::vector<STC_TRIGGERED_PSKILL> checkPassiveDodge(FightPet* enemy);
    //暴击触发}
    std::vector<STC_TRIGGERED_PSKILL> checkPassiveCirt(FightPet* enemy);
    //杀死敌人}
    std::vector<STC_TRIGGERED_PSKILL> checkPassiveKill(FightPet* enemy);
    //死亡触发}
    std::vector<STC_TRIGGERED_PSKILL> checkPassiveDead(FightPet* enemy);
//    void checkPassvieAfterAttack(FightPet *enemy, uint32 damage);
    
    
    
    std::vector<STC_TRIGGERED_PSKILL> effPSkillActive(std::vector<STC_TRIGGERED_PSKILL> arrTPSkill, int damage);
    std::vector<STC_EFFECT> effActive(std::vector<STC_EFFECT> arrEff, int damage, FightPet *enemyPet);
    
    //攻击长气}
    void addBasePower(uint16 wRound);
    //受伤长气}
    void addHurtPower(uint16 wRound);
    //effect长气}
    void addPower(uint16 wRound, int value);

    //队长技能与buff提升的攻击力}
    int checkAtkAddByBuff(uint16 wRound, uint8 attType);
    //队长技能与buff提升的防御力}
    int checkDefAddByBuff(uint16 wRound, uint8 attType);
    //队长技能与buff提升的伤害}
    int checkDamAddByBuff(FightPet* pDef, uint16 wRound);
    //队长技能与buff减少的伤害}
    int checkHitDamDownByBuff(FightPet* pAttacker, uint16 wRound);
    //属性相克}
    int checkAttributeRegulate(uint16 attNature, uint16 defNature);
    
    //队长技能与buff提升的恢复力}
    int checkRestoreAdd(uint16 wRound);
    
    //遗迹挑战中天气加成攻击力
    int checkDamAddByWeather();
    
    //伤害值分combo}
    std::map<uint16, STC_FRAME_DAMAGE> makeCombo(int &allDamage, uint32 skillId);

    //获取必杀技造成的伤害}
    int getUltimateDamage(int atk, int def, int curEnemyHp, uint32 skillId);

    
    std::vector<STC_TRIGGERED_PSKILL> triggerBuffAddEff(uint16 wRound, FightPet *enemy, std::vector<STC_PASSIVE_SKILL> arrTriggerPassive);
    STC_TRIGGERED_PSKILL triggerPassiveBuffAddEff(FightPet *enemy, STC_PASSIVE_SKILL *passive);
    STC_PET_EFF_BY_USKILL triggerUltBuffAddEff(FightPet *enemy, uint32 skillId);
    
    //心珠掉落}
    std::vector<STC_ITEM_DROP> getDropItems(int damage, FightPet *enemy);
    
    
    
    
    uint32  HasBuffTypeNum(uint8 byCurRound, uint8 byType);
	uint16  HasBuffTypeId(uint8 byCurRound, uint8 byType);
    
	/* EFFECT INFO */
	bool	HasEffect(uint8 byCurRound, uint8 byType);
	uint32  HasEffectType(uint8 byCurRound, uint8 byType);

    bool addNewBuff(STC_BUFF buff);
    void newToOldBuff();
    void addnewEff(STC_EFFECT eff);
    
    void unlockBuff(uint32 effId);
    
    void addHP(int dwValue);
    void loseHP(int dwValue);
    
    int eatHeart(int num, uint16 wRound);
    
    int getRecover(uint16 wRound){
        return getPetInfo().wRestore + (float)getPetInfo().wBaseRestore* checkRestoreAdd(wRound) / 10000;
    };
    
    //战斗中暴击触发}
    bool critTiggerInFight(uint16 wEnemyIndex);
    
    std::map<uint16, std::vector<STC_EFFECT> > ultSkillToMyBuff(uint32 skillId);
    
    //当前攻击力
    uint32 m_dwCurAtk;
public:

    /*
     E_LEADER_SPELL_TYPE_ATTACK			= 1, // 1 攻击加成}
     E_LEADER_SPELL_TYPE_NATURE_DEFFENSE = 2, // 2 属性防御}
     E_LEADER_SPELL_TYPE_NATURE_DAMGAGE	= 3, // 3 属性伤害}
     E_LEADER_SPELL_TYPE_HEART_GEM		= 4, // 7 心珠掉落}
     E_LEADER_SPELL_TYPE_RECOVER			= 5, // 8 回复增加}
     E_LEADER_SPELL_TYPE_HP				= 6, // 9 血量增加}
     E_LEADER_SPELL_TYPE_CRIT			= 7, //10 暴击增加}
     E_LEADER_SPELL_TYPE_DEF				= 8, //11 防御增加}
     E_LEADER_SPELL_TYPE_SPELL_COOL		= 9,  // 12 技能冷却}
     E_LEADER_SPELL_TYPE_COIN_ADD		= 10, // 13 金币增加}
     E_LEADER_SPELL_TYPE_FARMRES_ADD		= 11, // 14 水晶增加}
     E_LEADER_SPELL_TYPE_CRIT_DAMAGE		= 12, //15 暴击伤害}
     E_LEADER_SPELL_TYPE_ADD_HIT			= 13, //16 命中增加}
     E_LEADER_SPELL_TYPE_ADD_DODGE		= 14, //17 闪避增加}
     */
#pragma mark Leader Skill
    //队长技能加成}
    int GetLeaderAddSelfValue(uint8 byAddType);
	int GetLeaderAddOtherValue(uint8 byAddType, uint8 byOtherNature);
    
    int GetLeaderAttackValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_ATTACK); }
	int GetLeaderNatureDefValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_NATURE_DEFFENSE); }
	int GetLeaderNatureDamValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_NATURE_DAMGAGE); }
	int GetLeaderHeartGemValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_HEART_GEM); }
	int GetLeaderRecoverValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_RECOVER); }
	int GetLeaderHpAddValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_HP); }
	int GetLeaderCritAddValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_CRIT); }
	int GetLeaderCritDamAddValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_CRIT_DAMAGE); }
    int GetLeaderDefAddValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_DEF); }
    
    int GetLeaderSkillCoolValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_SPELL_COOL); }
	int GetLeaderCoinAddValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_COIN_ADD); }
	int GetLeaderFarmresAddValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_FARMRES_ADD); }
	int GetLeaderHitAddValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_ADD_HIT); }
    int GetLeaderDodgeAddValue() { return GetLeaderAddSelfValue(E_LEADER_SPELL_TYPE_ADD_DODGE); }
    
    //队长技能对于某属性加成}
	int GetLeaderAttackOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_ATTACK , byOtherNature); }
	int GetLeaderNatureDefOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_NATURE_DEFFENSE, byOtherNature); }
	int GetLeaderNatureDamOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_NATURE_DAMGAGE, byOtherNature); }
	int GetLeaderHeartGemOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_HEART_GEM, byOtherNature); }
	int GetLeaderRecoverOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_RECOVER, byOtherNature); }
	int GetLeaderHpAddOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_HP, byOtherNature); }
	int GetLeaderCritAddOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_CRIT, byOtherNature); }
	int GetLeaderDefAddOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_DEF, byOtherNature); }
    
    int GetLeaderSkillCoolOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_SPELL_COOL, byOtherNature); }
	int GetLeaderCoinAddOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_COIN_ADD, byOtherNature); }
	int GetLeaderFarmresAddOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_FARMRES_ADD, byOtherNature); }
	int GetLeaderHitAddOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_ADD_HIT, byOtherNature); }
    int GetLeaderDodgeAddOtherValue(uint8 byOtherNature) { return GetLeaderAddOtherValue(E_LEADER_SPELL_TYPE_ADD_DODGE, byOtherNature); }
    
#pragma mark Buff
    //获取Buff加成}
    uint32 HasNumAttackBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_ATTACK); }
	uint32 HasNumDeffenseBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_DEFFENSE); }
    
    uint32 HasNumCAttBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_CATT); }
	uint32 HasNumCDefBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_CDEF); }
    
    uint32 HasNumSAttBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_SATT); }
	uint32 HasNumSDefBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_SDEF); }
    
	uint32 HasNumRecoverBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_RECOVER); }
	uint32 HasNumAllBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_ALL); }
	uint32 HasNumCritBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_CRIT); }
//    E_BUFF_NUM_CRIT_DAMAGE     = 24,		// 数值类 暴伤	}
    uint32 HasNumCritDamageBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_NUM_CRIT_DAMAGE); }
    
    uint32 HasNumSpeedAddBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_ADD_SPEED); }
    uint32 HasNumSpeedDecBuff(uint8 byCurRound) { return HasBuffTypeNum(byCurRound, E_BUFF_DEC_SPEED); }
    
	//获取Buff效果}
    uint16 HasRecoverBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_RECOVERY); }
	uint16 HasFiringBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_FIRING); }//灼烧}
	uint16 HasFrozenBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_FROZEN); }//冰冻}
    uint16 HasPoisonBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_POISON); }//中毒}
	uint16 HasBindBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_BIND); }
	uint16 HasPalsyBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_PALSY); }
	uint16 HasSealBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_SEAL); }
	uint16 HasInvincibleBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_INVINCIBLE); }
//    E_BUFF_CONFUSED		= 17,				// 混乱 17}
//	E_BUFF_DODGE		= 18,				// 闪避 18}
//	E_BUFF_HP_MAX_RATE	= 19,				// 最大血量百分比回复 19}
    uint16 HasConfusedBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_CONFUSED); }
    uint16 HasDodgeBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_DODGE); }
    uint16 HasMaxRateBuff(uint8 byCurRound) { return HasBuffTypeId(byCurRound, E_BUFF_HP_MAX_RATE); }
    
    int GetBuffTypeValue( std::vector<STC_BUFF> arrbuff);

#pragma mark Effect
    /*
     E_EFFECT_CRIT_HIT		= 1,			// 暴击  1	// FightAi  CalcDamage 中使用}
     E_EFFECT_DOUBLE_HIT		= 2,			// 连击  2  // FightPet }
     E_EFFECT_RECOVER_HP_CUR	= 3,			// 回复 当前  3 // FightPet}
     E_EFFECT_RECOVER_HP_MAX = 4,			// 回复 最大  4 // FightPet}
     E_EFFECT_UNLOCK_STATE	= 5,			// 解状态  5 // FightPet}
     E_EFFECT_SPECIAL_ITEM	= 6,			// 心珠  6 // FightPet}
     E_EFFECT_SUCK_BLOOD		= 7,			// 吸血 7 // Ai}
     E_EFFECT_RECOVER_HP		= 8,			// 回复值回复 8 // FightPet}
     E_EFFECT_INITIAL_ADD	= 9,			// 主动技能+}
     E_EFFECT_INITIAL_DEC	= 10,			// 主动技能-}
     E_EFFECT_ADD_DAMAGE		= 11,			// 额外伤害}
     E_EFFECT_DEC_DAMAGE		= 12,			// 减少伤害}
     E_EFFECT_ADD_ATK		= 13,			// 增加攻击力}
     */
    uint32 HasNumCritEff() { return HasEffNum(E_EFFECT_CRIT_HIT); }
    uint32 HasNumDoubleEff() { return HasEffNum(E_EFFECT_DOUBLE_HIT); }
    uint32 HasNumRevCurHpEff() { return HasEffNum(E_EFFECT_RECOVER_HP_CUR); }
    uint32 HasNumRevMaxHpEff() { return HasEffNum(E_EFFECT_RECOVER_HP_MAX); }
    uint32 HasNumUnlockEff() { return HasEffNum(E_EFFECT_UNLOCK_STATE); }
    uint32 HasNumHeartEff() { return HasEffNum(E_EFFECT_SPECIAL_ITEM); }
    uint32 HasNumSuckBloodEff() { return HasEffNum(E_EFFECT_SUCK_BLOOD); }
    uint32 HasNumRevHpEff() { return HasEffNum(E_EFFECT_RECOVER_HP); }
    uint32 HasNumInitialAddEff() { return HasEffNum(E_EFFECT_INITIAL_ADD); }
    uint32 HasNumInitialDecEff() { return HasEffNum(E_EFFECT_INITIAL_DEC); }
    uint32 HasNumDamageAddEff() { return HasEffNum(E_EFFECT_ADD_DAMAGE); }
    uint32 HasNumDamageDecEff() { return HasEffNum(E_EFFECT_DEC_DAMAGE); }
    uint32 HasNumAtkAddEff() { return HasEffNum(E_EFFECT_ADD_ATK); }
    uint32 HasEffNum(uint8 type);
    
//    //获取Effect效果}
//	bool HasCritEffect();
//    //effect提升的伤害}
//    int checkDamAddByEff();
//    //effect减少的伤害}
//    int checkDamDownByEff();
//    //effect加攻击力}
//    int checkAttAddByEff();
    //暴击增加的伤害}
    int getCritAdd();
#pragma mark Talent
    int GetTalentCritDamAdd(){return GetTalentAddValue(E_TALENT_TYPE_CRIT_DAMAGE_ADD);};
    int GetTalentNatureDamAdd(uint8 nature){return GetTalentAddValue(E_TALENT_TYPE_DAMAGE_ADD_WATER + nature - 1);};
    int GetTalentNatureDamSub(uint8 nature){return GetTalentAddValue(E_TALENT_TYPE_DAMAGE_DEC_WATER + nature - 1);};
//    E_TALENT_TYPE_DEC_DAMAGE					= 33, // 受到伤害减少}
    int GetTalentDamSub(){return GetTalentAddValue(E_TALENT_TYPE_DEC_DAMAGE);};
    int GetTalentSDamSub(){return GetTalentAddValue(E_TALENT_TYPE_SA_DEC_DAMAGE);}; //特攻伤害减少
    int GetTalentCDamSub(){return GetTalentAddValue(E_TALENT_TYPE_CA_DEC_DAMAGE);}; //普攻伤害减少
    
    int GetTalentDamAdd(){return GetTalentAddValue(E_TALENT_TYPE_ADD_DAMAGE);}; //伤害加成
//    E_TALENT_TYPE_DROGE_HURT					= 40, // 受龙系伤害加深}
    int GetTalentDrogeHurtDamAdd(){return GetTalentAddValue(E_TALENT_TYPE_DROGE_HURT);};
    int GetTalentAddValue(uint8 byType);
    
    /*
    E_TALENT_TYPE_IMMUNE_POISON					= 22, // 免疫中毒}
	E_TALENT_TYPE_IMMUNE_FIRING					= 23, // 免疫灼烧}
	E_TALENT_TYPE_IMMUNE_BIND					= 24, // 免疫缠绕}
	E_TALENT_TYPE_IMMUNE_SEAL					= 25, // 免疫封印}
	E_TALENT_TYPE_IMMUNE_PALSY					= 26, // 免疫麻痹}
	E_TALENT_TYPE_IMMUNE_FROZEN					= 27, // 免疫冰冻}
    E_TALENT_TYPE_IMMUNE_CA						= 38, // 免疫普攻}
    E_TALENT_TYPE_IMMUNE_SA						= 39, // 免疫特攻}
    */
    uint16 HasTalentImmune(uint8 talentType);
    uint16 HasTalentImmunePoison(){return HasTalentImmune(E_TALENT_TYPE_IMMUNE_POISON);};
    uint16 HasTalentImmuneFiring(){return HasTalentImmune(E_TALENT_TYPE_IMMUNE_FIRING);};
    uint16 HasTalentImmuneBind(){return HasTalentImmune(E_TALENT_TYPE_IMMUNE_BIND);};
    uint16 HasTalentImmuneSeal(){return HasTalentImmune(E_TALENT_TYPE_IMMUNE_SEAL);};
    uint16 HasTalentImmunePalsy(){return HasTalentImmune(E_TALENT_TYPE_IMMUNE_PALSY);};
    uint16 HasTalentImmuneFrozen(){return HasTalentImmune(E_TALENT_TYPE_IMMUNE_FROZEN);};
    uint16 HasTalentImmuneCA(){return HasTalentImmune(E_TALENT_TYPE_IMMUNE_CA);};
    uint16 HasTalentImmuneSA(){return HasTalentImmune(E_TALENT_TYPE_IMMUNE_SA);};
    

    //触发的被动技能}
    std::vector<STC_TRIGGERED_PSKILL> arrTriggerPassiveSkill;
private:
    //未命中次数}
    uint8 m_unHitCnt;
    
    //技能攻击的效果触发序列}
    int skillTriggerCounter;
    bool skillTriggerUsedFlag;
    std::vector<STC_SKILL_TRIGGER > arrSkillTrigger;
    
    //被动技能触发序列}
    int passiveSkillTriggerCounter;
    bool passiveSkillTriggerUsedFlag;
    std::vector<std::map<uint32, STC_PASSIVE_SKILL_TRIGGER> > arrPassiveSkillTrigger;
    //暴击触发序列}
    int critTriggerCounter;
    bool critTriggerUsedFlag;
    std::vector<std::vector<int> > arrCritTrigger;
    
    

};
#endif /* defined(__HelloWorld__FightPet__) */
