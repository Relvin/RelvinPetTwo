//
//  FigthAI.cpp
//  HelloWorld
//
//  Created by long on 13-8-26.
//
//

#include "FightAI.h"
#include "EnumDefines.h"
#include "ConfigGet.h"
#include "StageScene.h"
#include "CheckPointMgr.h"

#define waveMaxCoin     30

FightAI::FightAI()
{
    m_myTeam = NULL;
    m_myTeam = NULL;
    m_enemyTeam = NULL;
    m_allWaveCnt = 0;
    m_curWave = 1;
    m_wCurSelectedEnemy = 0;
    m_curRound = 0;
    m_bIsMyAtt = false;
    m_curAttCnt = 0;
    
    m_dwEffHeartCnt = 0;
    m_dwTeamHeartCnt = 0;
    
    m_byAllRound = 0;
    m_byFightType = 0;
    m_fightStar = 0;
    m_bIsMJShopOpen = false;
}

FightAI::~FightAI()
{}

//清除所有数据}
void FightAI::uninit()
{
    delete m_myTeam;
    m_myTeam = NULL;
    delete m_enemyTeam;
    m_enemyTeam = NULL;
    m_arrEnemyTeams.clear();
    m_allWaveCnt = 0;
    m_curWave = 1;
    m_wCurSelectedEnemy = 0;
    m_curRound = 0;
    m_bIsMyAtt = false;
    m_mapBattleData.clear();
    m_arrCurRoundDropItems.clear();
    m_arrAllDropItems.clear();
    m_arrCurWaveDropItems.clear();
    m_curAttCnt = 0;
    m_arrWaitBattleData.clear();
    m_dwEffHeartCnt = 0;
    m_dwTeamHeartCnt = 0;
    m_byAllRound= 0;
    m_arrBoxItems.clear();
    //招财猫副本的伤害和金钱}
    m_dwCoinCatDamage = 0;
    m_dwCoinCatMoney = 0;
    m_fightStar = 0;
    //    m_wStageId = 0;
    m_arrPveReward.clear();
    m_arrWorldLoot.clear();
    m_stcPerData = *new STC_BATTLE_PRE_DATA();
    m_bIsMJShopOpen = false;
}

void FightAI::handlerPVPInfo(WorldPacket &packet)
{
    uint8 wFigthType;
    packet >> wFigthType;
    setFightType(wFigthType);
    
    uint16 wPetIconIndex;
    packet >> wPetIconIndex;
    std::string strMyTeamName;
    packet >> strMyTeamName;
    uint32 dwMyRank;
    packet >> dwMyRank;
    
    uint16 wEnemyIconIndex;
    packet >> wEnemyIconIndex;
    std::string strEnemyTeamName;
    packet >> strEnemyTeamName;
    uint32 dwEnemyRank;
    packet >> dwEnemyRank;
    
    
    uint8 byMyTeamId;
    packet >> byMyTeamId;
    uint32 dwMyTeamHp;
    packet >> dwMyTeamHp;
    
    m_stcArenaRoleData.wPetIconIndex = wPetIconIndex;
    m_stcArenaRoleData.strMyTeamName = strMyTeamName;
    m_stcArenaRoleData.dwMyRank = dwMyRank;
    
    m_stcArenaRoleData.wEnemyIconIndex = wEnemyIconIndex;
    m_stcArenaRoleData.strEnemyTeamName = strEnemyTeamName;
    m_stcArenaRoleData.dwEnemyRank = dwEnemyRank;
    
//    m_dwMyTeamHP = dwMyTeamHp;
//    m_dwCurMyTeamHP = dwMyTeamHp;
    
    //    CCString *str = CCString::createWithFormat("%d", m_dwMyTeamHP);
    
    uint8 byMyTeamCnt;
    packet >> byMyTeamCnt;
    std::vector<STC_FIGHT_PET_INFO> vecPet;
    for (int i = 0; i < byMyTeamCnt; i++) {
        uint8  byFightId;
        uint16 wPetId;
        uint8  byPetLv;
        uint32 dwPetCurHP;
        uint32 dwPetMaxHP;
        uint8 byNature;
        uint8 byType;
        uint8  byMaxPower; //主动技能冷却值				// new add}
        uint32 dwNorSkillId;
        uint32 dwSkillId;
        uint16 wCurPower;
        
        packet >> byFightId;
        packet >> wPetId;
        packet >> byPetLv;
        packet >> dwPetCurHP;
        packet >> dwPetMaxHP;
        packet >> byNature;
        packet >> byType;
        packet >> byMaxPower;
        packet >> dwNorSkillId;
        packet >> dwSkillId;
        packet >> wCurPower;
        
        STC_PET_INFO pet;
        pet.wBattleIndex = byFightId;
        pet.wPetIndexId = wPetId % 1000;
        pet.byEvoLv = wPetId / 1000;
        pet.wHP = dwPetMaxHP;
        pet.petNature = byNature;
        pet.wAllPower = byMaxPower;
        pet.wPowerCur = wCurPower;
        pet.wNormalAttId = dwNorSkillId;
        pet.wSkillId = dwSkillId;
        pet.wCurHP = dwPetCurHP;
        STC_FIGHT_PET_INFO fPet;
        fPet.petInfo = pet;
        vecPet.push_back(fPet);
    }
    FightTeam *myTeam = FightTeam::creat(vecPet);
    vecPet.clear();
    
    
    uint8 byEnemyTeamId;
    uint32 dwEnemyTeamHp;
    uint8 byEnemyTeamCnt;
    
    
    packet >> byEnemyTeamId;
    packet >> dwEnemyTeamHp;
    //    m_dwEnemyTeamHP = dwEnemyTeamHp;
    //    m_dwCurEnemyTeamHP = dwEnemyTeamHp;
    
    //    str->initWithFormat("%d", m_dwEnemyTeamHP);
    
    packet >> byEnemyTeamCnt;
    std::vector<STC_FIGHT_PET_INFO> vecEnemy;
    for (int i = 0; i < byEnemyTeamCnt; i++) {
        uint8  byFightId;
        uint16 wPetId;
        uint8  byPetLv;
        uint32 dwPetCurHP;
        uint32 dwPetMaxHP;
        uint8 byNature;
        uint8 byType;
        uint8  byMaxPower; //主动技能冷却值				// new add}
        uint32 dwNorSkillId;
        uint32 dwSkillId;
        uint16 wCurPower;
        
        packet >> byFightId;
        packet >> wPetId;
        packet >> byPetLv;
        packet >> dwPetCurHP;
        packet >> dwPetMaxHP;
        packet >> byNature;
        packet >> byType;
        packet >> byMaxPower;
        packet >> dwNorSkillId;
        packet >> dwSkillId;
        packet >> wCurPower;
        
        STC_PET_INFO pet;
        pet.wBattleIndex = byFightId;
        pet.wPetIndexId = wPetId % 1000;
        pet.byEvoLv = wPetId / 1000;
        pet.wHP = dwPetMaxHP;
        pet.petNature = byNature;
        pet.wAllPower = byMaxPower;
        pet.wPowerCur = wCurPower;
        pet.wNormalAttId = dwNorSkillId;
        pet.wSkillId = dwSkillId;
        pet.wCurHP = dwPetCurHP;
        if(i == 0)
        {
            pet.isBoss = true;
        }
        STC_FIGHT_PET_INFO fPet;
        fPet.petInfo = pet;
        vecEnemy.push_back(fPet);
    }
    FightTeam *enemyTeam = FightTeam::creat(vecEnemy);
    setPVPTeam(myTeam, enemyTeam);
    
    m_pvpData = packet;
}

//战斗掉落 { uint8 bySize + { uint32 dwUniteType + uint32 dwUniteNum}, uint8 bySize {uint32 dwPetObjId, uint8 isNew}}
void FightAI::handlerPVEReward(WorldPacket &packet)
{
    packet >> m_fightStar;
    
    m_arrPveReward.clear();
    uint8 bySize;
    packet >> bySize;
    for (int i = 0; i < bySize; i++) {
        uint32 dwUniteType ;
        uint32 dwUniteNum;
        packet >> dwUniteType;
        packet >> dwUniteNum;
        
        STC_FIGHT_REWARD_ITEM item;
        item.dwItemId = dwUniteType;
        item.dwCount = dwUniteNum;
        m_arrPveReward.push_back(item);
    }
    
    packet >> bySize;
    for (int i = 0; i < bySize; i ++) {
        uint32 dwPetObjId;
        uint8 isNew;
        packet >> dwPetObjId;
        packet >> isNew;
        
        STC_FIGHT_REWARD_ITEM item;
        item.dwItemId = dwPetObjId;
        item.byIsNew  = isNew;
        item.dwCount = 1;
        m_arrPveReward.push_back(item);
    }
    
    packet >> bySize;
    for (int i = 0; i < bySize; i++) {
        uint32 dwUniteType ;
        uint32 dwUniteNum;
        packet >> dwUniteType;
        packet >> dwUniteNum;
        
        STC_FIGHT_REWARD_ITEM item;
        item.dwItemId = dwUniteType;
        item.dwCount = dwUniteNum;
        item.byType = 1;
        m_arrPveReward.push_back(item);
    }
}


void FightAI::handlerPVEInfo(WorldPacket &packet)
{
    uninit();

    uint8 byFightType; //战斗类型}
    packet >> byFightType;
    m_byFightType = byFightType;
    uint8 byAllRound;
    packet >> byAllRound;
    m_byAllRound = byAllRound;
    
    uint8  byLianXieSize;//连协攻击size // add}
    packet >> byLianXieSize;
    for (int i = 0; i < byLianXieSize; i++) {
        int wLianXieRate; //概率		// add}
        int wLianXieValue; //加成值		// add}
        packet >> wLianXieRate;
        packet >> wLianXieValue;
        m_stcDamFloat.arrLianXieRate[i] = wLianXieRate;
        m_stcDamFloat.arrLianXieValue[i] = wLianXieValue;
    }
    
    uint32 dwCritFloat; //暴击倍率值			// add begin 2014-02-19}
	uint32 dwSparkFloat; //合击伤害值}
	uint32 dwDamFloat; //伤害浮动}
	uint32 dwSkillDamFloat; //技能浮动				// add end  2014-02-19}
    uint32 dwCoinCatFloat; //招财猫金钱比例}
    uint32 dwRecoverFloat; //回复计算}
    uint32 dwLvDamAdd;  //等级压制 	[New Add]
    uint32 dwEvoLvDamAdd;   //阶级压制		[New Add]
    
    packet >> dwCritFloat;
    packet >> dwSparkFloat;
    packet >> dwDamFloat;
    packet >> dwSkillDamFloat;
    packet >> dwCoinCatFloat;
    packet >> dwRecoverFloat;
    packet >> dwLvDamAdd;
    packet >> dwEvoLvDamAdd;
    m_stcDamFloat.dwCritFloat = dwCritFloat;
    m_stcDamFloat.dwSparkFloat = dwSparkFloat;
    m_stcDamFloat.dwDamFloat = dwDamFloat;
    m_stcDamFloat.dwSkillFloat = dwSkillDamFloat;
    m_stcDamFloat.dwCoinCatFloat = dwCoinCatFloat;
    m_stcDamFloat.dwRecoverFloat = dwRecoverFloat;
    m_stcDamFloat.dwLvDamAdd = dwLvDamAdd;
    m_stcDamFloat.dwEvoLvDamAdd = dwEvoLvDamAdd;
    
    uint16 StageId;
    packet >> StageId;

    uint8 byStageLoot;// 掉落  // add}
    packet >> byStageLoot;
    for (int i = 0; i < byStageLoot; i++) {
        uint32 itemType;// 物品类型  // add}
        uint32 dwCount; // 物品数量  // add}
        packet >>itemType >> dwCount;
        STC_ITEM_DROP item;
        item.wItemType = itemType;
        item.wCount = dwCount;
        item.wHasCount = dwCount;
        
        m_arrAllDropItems.push_back(item);
    }
    
    uint8 byBOXLoot;		//宝箱掉落 [new Add]
    packet >> byBOXLoot;
    for (int i = 0; i < byBOXLoot; i++) {
        uint32 itemType;// 物品类型  // add}
        uint32 dwCount; // 物品数量  // add}
        packet >>itemType >> dwCount;
        STC_ITEM_DROP item;
        item.wItemType = itemType;
        item.wCount = dwCount;
        item.wHasCount = dwCount;
        
        m_arrBoxItems.push_back(item);
    }
    
    uint32 dwDropEggCnt;    //掉出的蛋的数量
    packet >> dwDropEggCnt;
    STC_ITEM_DROP item;
    item.wItemType = 1;
    item.wCount = dwDropEggCnt;
    item.wHasCount = dwDropEggCnt;
    m_arrAllDropItems.push_back(item);
    
    uint8 size = 0;
    packet >> size;
    for (int i = 0; i < size; i++) {
        
        uint8 fightOrder;
        packet >> fightOrder;
        std::string strTeamName;
        packet >> strTeamName;
        uint32 dwTeamHPMax;
        packet >> dwTeamHPMax;
        uint32 dwMaxHeart;
        packet >> dwMaxHeart;
        uint8 byTeamSize;
        packet >> byTeamSize;
        
        std::vector<STC_FIGHT_PET_INFO> arrFightPetInfo;
        arrFightPetInfo.clear();
        for (int j = 0; j < byTeamSize; j++) {
            STC_FIGHT_PET_INFO info;
            STC_PET_INFO pet;
            std::vector<STC_ITEM_DROP> arrItem;
            
            std::vector<std::map<uint32, STC_PASSIVE_SKILL_TRIGGER> > arrPassiveSkillTrigger;
            
            std::vector<STC_SKILL_TRIGGER > arrSkillTrigger;
            
            std::vector<std::vector<int> > arrCritTrigger;
            
            uint8  fightId;
            uint16 petId;
            uint8  petLv;
            uint32 petHP;
            uint8 petNature;
            uint8 petType;
            uint32 baseHp;
            
            /*
             uint32 基础血量
             uint32 基础普攻
             uint32 基础普防
             uint32 基础回复
             uint32 基础特攻
             uint32 基础特防
             
             uint32 血量
             uint32 普攻
             uint32 防御
             uint32 回复
             uint32 特攻
             uint32 特防
             
             uint32 基础命中
             uint32 基础闪避
             uint32 基础速度
             
             uint32 命中
             uint32 闪避
             uint32 速度
             uint32 暴击率
             uint32 暴伤
             uint32 抗暴
             
             uint32 普攻技能
             */
            
            uint32 baseAttack;
            uint32 baseDefense;
            uint32 baseRestore;
            uint32 baseSAttack;
            uint32 baseSDefense;

            
            
            uint32 wHP;
            uint32 wAttack;
            uint32 wDefense;
            uint32 wRestore;
            uint32 wSAttack;
            uint32 wSDefense;
            
            
            uint32 baseHit;
            uint32 baseDodge;
            uint32 baseSpeed;//基础速度 // add}
            
            uint32 wHit;
            uint32 wDodge;
            uint32 wSpeed;//速度 // add}
            
            uint32 wLucky;
            uint32 wCritHurt;
            uint32 wCritFree;
            
            uint32 wNormalAttId;
            uint32 wLeaderSkillId;
            uint32 wSkillId;
            uint8  wSkillLv;
            uint32 dwSkillValue;//主动技能技能威力					// new add}
            uint16 wPowerAdd;//主动技能增量					// new add}
            uint16 wPowerHurtAdd;//受伤时增量}
            uint16 wPowerCur;//主动技能初始怒气		// add}
            
            packet >> fightId;
            packet >> petId;
            packet >> petLv;
            packet >> petHP;
            packet >> petNature;
            packet >> petType;
            
            packet >> baseHp;
            packet >> baseAttack;
            packet >> baseDefense;
            packet >> baseRestore;
            packet >> baseSAttack;
            packet >> baseSDefense;
            
            packet >> wHP;
            packet >> wAttack;
            packet >> wDefense;
            packet >> wRestore;
            packet >> wSAttack;
            packet >> wSDefense;

            
            packet >> baseHit;
            packet >> baseDodge;
            packet >> baseSpeed;
            
            packet >> wHit;
            packet >> wDodge;
            packet >> wSpeed;
            
            packet >> wLucky;
            packet >> wCritHurt;
            packet >> wCritFree;
            
            
            packet >> wNormalAttId;
            packet >> wLeaderSkillId;
            
            packet >> wSkillId;
            packet >> wSkillLv;
            packet >> dwSkillValue;
            packet >> wPowerAdd;
            packet >> wPowerHurtAdd;
            packet >> wPowerCur;
            
            pet.wBattleIndex = fightId;
            pet.wPetIndexId = petId % 1000;
            pet.byEvoLv = petId / 1000;
            pet.petLv = petLv;
            pet.wHP = petHP;
            pet.wCurHP = petHP;
            if (pet.wHP == 0) {
                CCMessageBox(" pet init hp 0 ~~", "Error");
            }
            pet.petNature = petNature;
            pet.petType = petType;
            
            pet.wBaseAttack = baseAttack;
            pet.wBaseDefense = baseDefense;
            pet.wBaseRestore = baseRestore;
            pet.wBaseSAttack = baseSAttack;
            pet.wBaseSDefense = baseSDefense;
            
            pet.wAttack = wAttack;
            pet.wDefense = wDefense;
            pet.wRestore = wRestore;
            pet.wSAttack = wSAttack;
            pet.wSDefense = wSDefense;
            
            pet.wBaseSpeed = baseSpeed;
            pet.wBaseHit = baseHit;
            pet.wBaseDodge = baseDodge;
            
            pet.wSpeed = wSpeed;
            pet.wHit = wHit;
            pet.wDodge = wDodge;
            
            pet.wLucky = wLucky;
            pet.wCritHurt = wCritHurt;
            pet.wCritFree = wCritFree;
            
            pet.wNormalAttId = wNormalAttId;
            
            pet.wLeaderSkillId = wLeaderSkillId;
            pet.wSkillId = wSkillId;
            pet.wSkillLv = wSkillLv;
            pet.dwSkillValue = dwSkillValue;
            pet.wAllPower = E_INITAIL_SPELL_BASE;
            pet.wPowerAdd = wPowerAdd;
            pet.wPowerHurtAdd = wPowerHurtAdd;
            pet.wPowerCur = wPowerCur;
            
            uint8 passiveSize;
            packet >> passiveSize;
            std::map<uint32, STC_PASSIVE_SKILL> arrPassive;
            for (int k = 0; k < passiveSize; k++) {
                STC_PASSIVE_SKILL pass;
                uint32 passiveId;
                uint8  passiveLv;
                uint32 passiveValue;//被动技能威力}
                packet >> passiveId;
                packet >> passiveLv;
                packet >> passiveValue;
                
                if (passiveId != 0) {
                    pass.wIndex = passiveId;
                    pass.wLv = passiveLv;
                    pass.dwValue = passiveValue;
                    arrPassive[passiveId] = pass;
                    
                }
            }
            
            uint8 talentSize;
            packet >> talentSize;

            for (int k = 0; k < talentSize; k++) {
                STC_PASSIVE_SKILL pass;
                uint32 talentId;
                uint8  talentLv;
                uint32 talentValue;//天赋技能威力}
                packet >> talentId;
                packet >> talentLv;
                packet >> talentValue;
                if (talentId != 0) {
                    pass.wIndex = talentId;
                    pass.wLv = talentLv;
                    pass.dwValue = talentValue;
                    arrPassive[talentId] = pass;
                    
                }
            }
            pet.arrPassiveSkill = arrPassive;
            
            uint32 wGemSkillId;
            uint8  wGemSkillLv;
            
//            uint32 dwBoxId;
            uint16 wDropPetIndexId;
//            uint32 dwBoxItemId;
//            uint32 dwBoxItemCount;
            packet >> wGemSkillId;
            packet >>  wGemSkillLv;
//            packet >> dwBoxId;
            packet >> wDropPetIndexId;
//            packet >> dwBoxItemId;
//            packet >> dwBoxItemCount;
            
            pet.wGemSkillId = wGemSkillId;
            pet.wGemSkillLv = wGemSkillLv;
            
            uint8 bIsBoss; // add
            packet >> bIsBoss;
            pet.isBoss = bIsBoss > 0;
//            STC_ITEM_DROP boxItem;
//            boxItem.wItemType = dwBoxItemId;
//            boxItem.wCount = dwBoxItemCount;
//            boxItem.wHasCount = dwBoxItemCount;
//            pet.boxItem = boxItem;
//            if (dwBoxItemId) {
//                pet.isBox = true;
//            }
//            else
//            {
//                pet.isBox = false;
//            }

            if (wDropPetIndexId > 0) {
                pet.isEgg = true;
                pet.wDropPetIndexId = wDropPetIndexId;
            }
            else
            {
                pet.isEgg = false;
                pet.wDropPetIndexId = 0;
            }
            
            uint8 byCritSize;
            packet >> byCritSize;
            for (int k = 0; k < byCritSize; k++) {
                uint8 byDefSize;
                packet >> byDefSize;
                std::vector<int> arrCrit;
                for (int l = 0; l < byDefSize; l++) {
                    uint8 byCrit;
                    packet >> byCrit;
                    arrCrit.push_back(byCrit);
                }
                arrCritTrigger.push_back(arrCrit);
            }
            
            //总共30回合的}
            uint8 byPassiveTriggerSize;
            packet >> byPassiveTriggerSize;
            for (int k = 0; k < byPassiveTriggerSize; k++) {
                
                //每回合触发的被动技能个数}
                uint8 byPassiveTrigger;
                packet >> byPassiveTrigger;
                
                std::map<uint32, STC_PASSIVE_SKILL_TRIGGER> mapPassTrigger;
                for (int l = 0; l < byPassiveTrigger; l++) {
                    uint8 byIsTrigger;
                    //判断被动技能是否触发}
                    packet >> byIsTrigger;
                    if (!byIsTrigger) {
                        continue;
                    }
                    STC_PASSIVE_SKILL_TRIGGER pTrigger;
                    pTrigger.wSize = byIsTrigger;
                    uint32 wpassId;
                    uint8 byMyBuffHit;
                    
                    packet >> wpassId;
                    packet >> byMyBuffHit;
                    pTrigger.wSkillId = wpassId;
                    pTrigger.byMyBuffHit = byMyBuffHit;
                    for (int x = 0; x < 3; x++) {
                        uint8 byMyEff;
                        packet >> byMyEff;
                        pTrigger.arrMyEffHit.push_back(byMyEff);
                    }
                    uint8 byDefBuffHit;
                    packet >> byDefBuffHit;
                    pTrigger.byEnemyBuffHit = byDefBuffHit;
                    for (int x = 0; x < 3; x++) {
                        uint8 byDefEff;
                        packet >> byDefEff;
                        pTrigger.arrEnemyEffHit.push_back(byDefEff);
                    }
                    mapPassTrigger[wpassId] = pTrigger;
                }
                arrPassiveSkillTrigger.push_back(mapPassTrigger);
            }
            
            uint8 bySkillTriggerSize;
            packet >> bySkillTriggerSize;
            for (int k = 0; k < bySkillTriggerSize; k++) {
                STC_SKILL_TRIGGER sTriiger;
                uint32 wIndex;
                packet >> wIndex;
                sTriiger.wSkillId = wIndex;
                uint8 byMyBuffHit;
                packet >> byMyBuffHit;
                sTriiger.byMyBuffHit = byMyBuffHit;
                for (int l = 0; l < 3; l++) {
                    uint8 byMyEff;
                    packet >> byMyEff;
                    sTriiger.arrMyEffHit.push_back(byMyEff);
                }
                
                for (int l = 0; l < 6; l++) {
                    uint8 byDefBuffHit;
                    packet >> byDefBuffHit;
                    sTriiger.byEnemyBuffHit.push_back(byDefBuffHit);
                }
                
                for (int l = 0; l < 6; l++) {
                    std::vector<uint8> arrEffHit;
                    for (int x = 0; x < 3; x++) {
                        uint8 byDefEff;
                        packet >> byDefEff;
                        arrEffHit.push_back(byDefEff);
                        
                    }
                    sTriiger.arrEnemyEffHit.push_back(arrEffHit);
                }
                arrSkillTrigger.push_back(sTriiger);
            }
            
            info.petInfo = pet;
            info.arrCritTrigger = arrCritTrigger;
            info.arrPassiveSkillTrigger = arrPassiveSkillTrigger;
            info.arrSkillTrigger = arrSkillTrigger;
            
            arrFightPetInfo.push_back(info);
        }
        
        if (i == 0) {
            m_myTeam = FightTeam::creat(arrFightPetInfo);
            m_myTeam->SetTeamType(FightTeam::E_TEAM_TYPE_MY);
            m_myTeam->SetTeamHp(dwTeamHPMax);
            m_myTeam->setIsCanDead(true);
            m_myTeam->SetTeamHpMax(dwTeamHPMax);
        }
        else
        {
            FightTeam *enemyTeam = FightTeam::creat(arrFightPetInfo);
            enemyTeam->SetTeamType(FightTeam::E_TEAM_TYPE_ENERMY);
            enemyTeam->SetTeamHp(dwTeamHPMax);
            enemyTeam->SetTeamHpMax(dwTeamHPMax);
            enemyTeam->setIsCanDead(true);
            enemyTeam->setMaxDropHeart(dwMaxHeart);
            m_arrEnemyTeams.push_back(enemyTeam);
        }
    }
    
    if (!m_myTeam || m_arrEnemyTeams.size() < 1) {
        // 此处可以改成HttpLog}
		assert("team info not full");
    }
    m_enemyTeam = m_arrEnemyTeams[0];
    
    m_allWaveCnt = m_arrEnemyTeams.size();
    m_curWave = 1;
    
    CheckPointMgr::Get()->clrTalkData();
    if (getFightType() == E_BATTLE_TYPE_MAP) {
        uint8 _bNewStage = StageCtrl::Get()->selectedStage().byStatus;
        if (_bNewStage) {
            CheckPointMgr::Get()->loadTalkData(0, StageCtrl::Get()->selectedStage().wStageId, 0);
        }
    }
}

//取加权随机数}
int FightAI::RandFactor(std::vector<int>& value)
{
    uint32 sum = 0;
    for (unsigned int i = 0; i < value.size(); ++i)
    {
        sum += value[i];
    }
    if (!sum)
    {
        return -1;
    }
    uint32 randValue = rand() % sum;
    uint32 min = 0;
    uint32 max = 0;
    for(unsigned int i = 0; i < value.size(); ++i)
    {
        min = max;
        max += value[i];
        if (randValue >= min && randValue < max)
        {
            //IME_LOG("RAND FACTOR[RandValue=%u RetI=%u size=%u]", randValue, i, value.size());
            return i;
        }
    }
    return -1;
}


#pragma mark function
//根据battleIndex获取fightPet}
FightPet *FightAI::getFightPetByBIndex(uint16 wBattleIndex)
{
    FightPet *pet = NULL;
    if (wBattleIndex <= PetCnt) {
        pet = m_myTeam->GetTeam()[wBattleIndex];
    }
    else
    {
        pet = m_enemyTeam->GetTeam()[wBattleIndex];
    }
    return pet;
}
//获取boss}
FightPet* FightAI::getBoss()
{
    FightPet *pet = NULL;
    if (m_curWave != m_allWaveCnt) {
        return pet;
    }
    std::map<uint16, FightPet*>::iterator it = FightAI::getEnemyTeam()->GetTeam().begin();
    for (; it !=  FightAI::getEnemyTeam()->GetTeam().end(); it++) {
        if (!it->second) {
            continue;
        }
        if (it->second->getPetInfo().isBoss) {
            pet = it->second;
            break;
        }
    }
    return pet;
}
//设置选中怪}
void FightAI::setSelectedEnemy(uint16 wEnemyIndex)
{
    m_wCurSelectedEnemy = wEnemyIndex;
}

//生成预战斗包}
STC_START_BATTLE_DATA FightAI::getStartBattleData(uint16 wBattleIndex, uint32 skillId)
{
    STC_START_BATTLE_DATA data;
    
    //    FightPet *pet = getFightPetByBIndex(wBattleIndex);
    uint8 eEffObj = E_EFFECT_OBJECT_ENEMY;
    uint8 scope = E_ATTACK_SCOPE_BF_SINLGE;
    if (skillId) {
        UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *uConfig = GET_CONFIG_STC(UltimateSkillConfig, skillId);
        if (uConfig) {
            eEffObj = uConfig->byEffectObj;
            scope = uConfig->byAttackScope;
        }
    }
    data.eEffObj = eEffObj;
    data.dwSkillId = skillId;
    data.wBattleIndex = wBattleIndex;
    
    data.arrEnemyIndexs = chooseMy(wBattleIndex, skillId);
    
    if(data.arrEnemyIndexs.size() == 0) //没有选到怪，说明怪都死了}
    {
        //死光了还打什么打啊，浪费技能}
//        if (wBattleIndex <= PetCnt) {   //如果是我打敌人时，允许鞭尸}
//            data.arrEnemyIndexs.push_back(m_wCurSelectedEnemy);
//            data.wAttIndex = m_wCurSelectedEnemy % 100;
//        }
    }
    else if (data.arrEnemyIndexs.size() == 1)  //只有一个目标时，攻击位置就是那个目标}
    {
        data.wAttIndex = data.arrEnemyIndexs[0] % 100;
    }
    else    //多个目标时，默认是中间位置}
    {
        data.wAttIndex = 3;
    }
    
    switch (scope) {
        case E_ATTACK_SCOPE_BF_SINLGE:

        case E_ATTACK_SCOPE_AF_SINGLE:

        case E_ATTACK_SCOPE_ATK_MAX:

        case E_ATTACK_SCOPE_HP_MIN:

        case E_ATTACK_SCOPE_DEF_MIN:

        case E_ATTACK_SCOPE_NATURE_SELECT:
            
        case E_ATTACK_SCOPE_RAND_TWO:
            
        case E_ATTACK_SCOPE_RAND_THREE:
            
        case E_ATTACK_SCOPE_ATK_MAX_2:
            
        case E_ATTACK_SCOPE_HP_MIN_2:
            
        case E_ATTACK_SCOPE_DEF_MIN_2:
            
        case E_ATTACK_SCOPE_NATURE_SELECT_2:
            //已经由默认方式 获取到了正确的攻击位置}
            break;
        case E_ATTACK_SCOPE_COLUMN:
            if (data.arrEnemyIndexs.size() > 0) {
                data.wAttIndex = data.arrEnemyIndexs[0] % 100;
                break;
            }
            break;
        case E_ATTACK_SCOPE_AF_ALL:
        case E_ATTACK_SCOPE_BF_ALL:
            if (data.arrEnemyIndexs.size() > 0 && data.arrEnemyIndexs[0] % 2 > 0) {
                    //因为是后排全体，如果选择的有前排，说明后排没有目标了(要买全部前排，要买全部后排)}
                    data.wAttIndex = 3;
                    break;
                }
            else{
                data.wAttIndex = 4;
            }
            break;
        case E_ATTACK_SCOPE_ALL:
            data.wAttIndex = 3;
            break;

        default:
            break;
    }
    
    if (eEffObj == E_EFFECT_OBJECT_MY) {
        data.wAttIndex = 3;
    }
    
    return data;
}

//生成战斗包}
uint16 FightAI::getBattleData(STC_START_BATTLE_DATA startData)
{
    uint16 key = 1;
    if (m_mapBattleData.size() > 0) {
        MAP_BATTLE_DATAS::iterator it = m_mapBattleData.end();
        it--;
        key = it->first+1;
    }
    STC_BATTLE_DATA data;
    
    FightPet* pet = getFightPetByBIndex(startData.wBattleIndex);
    data = pet->getAttackData(startData, m_curRound);
    m_mapBattleData[key] = data;

    return key;
    
}

//根据key获取战斗包}
STC_BATTLE_DATA FightAI::getBattleDataByKey(uint16 key)
{
    return m_mapBattleData[key];
}

//验证Spark}
void FightAI::checkSpark(uint16 key)
{
    //最大循环次数：5 * 6 * 15次}
    
    //循环当前攻击序列中所有攻击包，与即将加入攻击序列的包比较spark}
    
    STC_BATTLE_DATA data = m_mapBattleData[key];
    float sparkAdd = 1.0;//m_stcDamFloat.dwSparkFloat / 10000.0;
    
    for (int i = 0; i < m_arrWaitBattleData.size(); i++) {
        STC_WAIT_BATTLE_DATA curWait = m_arrWaitBattleData[i];
        //如果该包已经发出，比较下一战斗包}
        if (curWait.frame >= startFrames) {
            continue;
        }
        STC_BATTLE_DATA bData = m_mapBattleData[curWait.key];
        //循环战斗包中所有攻击对象，与即将加入的战斗包中的攻击对象比较}
        
        std::map<uint16, STC_ATTACK_DATA>::iterator itAtt = bData.arrAttData.begin();
        while (itAtt != bData.arrAttData.end()) {
            STC_ATTACK_DATA attData = itAtt->second;
            //如果改对象不在 下一个战斗包中，比较下一对象}
            if (data.arrAttData.find(attData.wEnemyIndex) == data.arrAttData.end()) {
                itAtt++;
                continue;
            }
            STC_ATTACK_DATA aData = data.arrAttData.find(attData.wEnemyIndex)->second;
            //如果攻击对象相同，循环攻击动作的伤害帧，同帧则spark}
            std::map<uint16, STC_FRAME_DAMAGE>::iterator itFra = attData.arrDamage.begin();
            while (itFra != attData.arrDamage.end()) {
                int frame =  - curWait.frame + itFra->second.wFrame;
                //如果帧不同，比较下一帧}
                if (frame < 0 || aData.arrDamage.find(frame) == aData.arrDamage.end()) {
                    itFra++;
                    continue;
                }
                //同帧spark，伤害加成}
                //(要检查队长技能，spark暴击、spark伤害、spark心珠)}
                
                if (!attData.isSpark && itFra->second.dwDamege != 1) {
                    itFra->second.dwDamege += sparkAdd * attData.dwAllDamage;
                    attData.isSpark = true;
                    //                    itFra->second.isSpark = true;
                    int dam = sparkAdd * attData.dwAllDamage;
                    attData.dwAllDamage += dam;
                }
                
                if (!aData.isSpark && aData.arrDamage.find(frame)->second.dwDamege != 1) {
                    aData.isSpark = true;
                    aData.arrDamage.find(frame)->second.dwDamege += sparkAdd * aData.dwAllDamage;
                    aData.arrDamage.find(frame)->second.isSpark = true;
                    int dam = sparkAdd * aData.dwAllDamage;
                    aData.dwAllDamage += dam;
                    
                    //                    FightPet *pet = getFightPetByBIndex(attData.wEnemyIndex);
                    //                    pet->loseHP(dam);
                }
                
                itFra++;
            }
            itAtt->second = attData;
            itAtt++;
            data.arrAttData.find(attData.wEnemyIndex)->second = aData;
            
        }
        m_mapBattleData[curWait.key] = bData;
    }
    
    m_mapBattleData[key] = data;
}

//真正攻击前，结算伤害}
void FightAI::doBattle(uint16 key)
{
    STC_BATTLE_DATA data = m_mapBattleData[key];
    
    do {
        if (data.eEffObj == E_EFFECT_OBJECT_MY) {
            break;
        }
        
        std::map<uint16, STC_ATTACK_DATA>::iterator itAtt = data.arrAttData.begin();
        while (itAtt != data.arrAttData.end()) {
            STC_ATTACK_DATA attData = itAtt->second;
            
            FightPet *pet = getFightPetByBIndex(attData.wEnemyIndex);
            pet->loseHP(attData.dwAllDamage);
            if (data.wBattleIndex <= PetCnt) {
                std::vector<STC_ITEM_DROP> vctItem = getDropItemByDamage(attData.dwAllDamage, pet);
                for (int i = 0; i < vctItem.size(); i++) {
                    STC_ITEM_DROP item = vctItem[i];
                    attData.arrItems.push_back(item);
                }
                itAtt->second = attData;
            }
            itAtt++;
        }
        
    } while (0);
    m_mapBattleData[key] = data;
}

//波次开始}
void FightAI::waveStart()
{
    m_curRound = 1;
    m_bIsMyAtt = false;
    m_myTeam->InitBuff(m_curRound);
    
    m_enemyTeam = m_arrEnemyTeams[m_curWave - 1];

    m_enemyTeam->InitBuff(m_curRound);
    m_curRound = 0;
    setCurWaveDropItem();
}
//波次结束}
void FightAI::waveEnd()
{
    m_myTeam->waveEndPasskill(m_curRound);
    m_enemyTeam->waveEndPasskill(m_curRound);
    m_curWave++;
}
//回合开始}
void FightAI::roundStart()
{
    //第一回合触发的，在波次开始触发中做了，故这里过滤}
    m_bIsMyAtt = !m_bIsMyAtt;
    m_curRound++;
    
    m_myTeam->beforeRoundPassvieSkill(m_curRound);
    m_enemyTeam->beforeRoundPassvieSkill(m_curRound);
}
//回合结束}
void FightAI::roundEnd()
{
    m_arrCurRoundDropItems.clear();
    
    m_myTeam->afterRoundPassiveSkill(m_curRound);
    m_enemyTeam->afterRoundPassiveSkill(m_curRound);
}

//buff结算}
void FightAI::buffActive()
{
    m_myTeam->UpdateBuffPerRound(m_curRound);
    m_enemyTeam->UpdateBuffPerRound(m_curRound);
}
//获取可攻击人的数量}
uint8 FightAI::getCanFightPetCnt()
{
    uint8 count = 0;
    if (m_bIsMyAtt) {
        for (int i = 1; i <= PetCnt; i++) {
            FightPet *pet = m_myTeam->GetTeam()[i];
            if (!pet) {
                continue;
            }
            if ((pet->getIsCanDead() && pet->getCurHP() == 0) || pet->HasPalsyBuff(m_curRound) || pet->HasConfusedBuff(m_curRound)) {
                continue;
            }
            count++;
        }
    }
    else
    {
        for (int i = 1; i <= PetCnt; i++) {
            FightPet *pet = m_enemyTeam->GetTeam()[i+100];
            if (!pet) {
                continue;
            }
            if ((pet->getIsCanDead() && pet->getCurHP() == 0) || pet->HasPalsyBuff(m_curRound) || pet->HasConfusedBuff(m_curRound)) {
                continue;
            }
            count++;
        }
    }
    return count;
}
//根据参数随即命中与否}
bool FightAI::RandEither(uint16 value, uint16 valueMax)
{
    if (value == 0)
    {
        return false;
    }
    if (value >= valueMax)
    {
        return true;
    }
    uint32 randValue = rand() % valueMax;
    if (randValue < value)
    {
        return true;
    }
    return false;
}

//我方攻击时 选怪}
std::vector<uint16> FightAI::chooseMy(uint16 wBattleIndex, uint32 skillId)
{
    std::vector<uint16> arrEnemy;
//    uint8 count = 1;
    uint8 eEffObj = E_EFFECT_OBJECT_ENEMY;
    uint8 atkScope= E_ATTACK_SCOPE_BF_SINLGE;
    //    FightPet *pet = getFightPetByBIndex(wBattleIndex);
    if (skillId) {
        UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *uConfig = GET_CONFIG_STC(UltimateSkillConfig, skillId);
        if (uConfig) {
            atkScope = uConfig->byAttackScope;
            eEffObj = uConfig->byEffectObj;
        }
    }
    FightTeam* team = m_enemyTeam;
    if ((wBattleIndex <= PetCnt && eEffObj == E_EFFECT_OBJECT_MY)
        ||
        (wBattleIndex > PetCnt && eEffObj == E_EFFECT_OBJECT_ENEMY)) {
        team = m_myTeam;
    }
    switch (atkScope) {
        case E_ATTACK_SCOPE_BF_SINLGE:
            arrEnemy = chooseByTypeBFSingle(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_AF_SINGLE:
            arrEnemy = chooseByTypeAFSingle(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_BF_ALL:
            arrEnemy = chooseByTypeBFAll(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_AF_ALL:
            arrEnemy = chooseByTypeAFAll(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_ALL:
            arrEnemy = chooseByTypeAll(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_RAND_TWO:
            arrEnemy = chooseByTypeRandTow(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_RAND_THREE:
            arrEnemy = chooseByTypeRandThree(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_ATK_MAX:
            arrEnemy = chooseByTypeAtkMax(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_HP_MIN:
            arrEnemy = chooseByTypeHpMin(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_DEF_MIN:
            arrEnemy = chooseByTypeDefMin(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_NATURE_SELECT:
            arrEnemy = chooseByTypeNautre(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_COLUMN:
            arrEnemy = chooseByTypeColumn(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_ATK_MAX_2:
            arrEnemy = chooseByTypeAtkMax_2(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_HP_MIN_2:
            arrEnemy = chooseByTypeHpMin_2(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_DEF_MIN_2:
            arrEnemy = chooseByTypeDefMin_2(wBattleIndex, team);
            break;
        case E_ATTACK_SCOPE_NATURE_SELECT_2:
            arrEnemy = chooseByTypeNautre_2(wBattleIndex, team);
            break;
        default:
            break;
    }
    return arrEnemy;
}

std::vector<uint16> FightAI::chooseFromVect(std::vector<uint16> arrId, uint8 count)
{
    std::vector<uint16> arrEnemy;
    
    for (int i = 0; i < arrId.size(); ++i) {
        if (count == 0) {
            break;
        }
        FightPet* pet = getFightPetByBIndex(arrId[i]);
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        arrEnemy.push_back(arrId[i]);
        --count;
    }
    
    return arrEnemy;
}
//前排单体}
std::vector<uint16> FightAI::chooseByTypeBFSingle(uint16 battleId, FightTeam* team)
{
    uint16 arr[7][7]=
    {
        {0,1,2,3,4,5,6},
        {0,1,1,3,3,5,5},
        {0,2,2,4,4,6,6},
        {0,3,3,1,1,3,3},
        {0,4,4,2,2,4,4},
        {0,5,5,5,5,1,1},
        {0,6,6,6,6,2,2}
    };
    std::vector<uint16> arrEnemy;
    
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    int id = battleId%100;// + off;
    
    for (int i = 1; i <= PetCnt; i++) {
        arrEnemy.push_back(arr[i][id] + off);
    }
    
    
//    if (battleId % 2 == 0) {
//        --id;
//    }
//    arrEnemy.push_back(id + off);
//    for (int i = 1; i <= 5; ++i) {
//        int k = i+id;
//        if (k > PetCnt) {
//            k %= PetCnt;
//        }
//        arrEnemy.push_back(k + off);
//    }
//    for (int i = 1; i <= 3; ++i) {
//        if (i*2 - 1 + off == id) {
//            continue;
//        }
//        arrEnemy.push_back(i*2 - 1 + off);
//    }
//
//    for (int i = 1; i <= 3; i++) {
//        arrEnemy.push_back(i*2 + off);
//    }
    
    return chooseFromVect(arrEnemy, 1);
}
//后排单体}
std::vector<uint16> FightAI::chooseByTypeAFSingle(uint16 battleId, FightTeam* team)
{
    uint16 arr[7][7]=
    {
        {0,1,2,3,4,5,6},
        {0,2,2,4,4,6,6},
        {0,1,1,3,3,5,5},
        {0,4,4,2,2,4,4},
        {0,3,3,1,1,3,3},
        {0,6,6,6,6,2,2},
        {0,5,5,5,5,1,1}
    };
    
    std::vector<uint16> arrEnemy;
    
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    int id = battleId%100;// + off;
    
    for (int i = 1; i <= PetCnt; i++) {
        arrEnemy.push_back(arr[i][id] + off);
    }
    
//    if (battleId % 2 > 0) {
//        ++id;
//    }
//    arrEnemy.push_back(id + off);
//    
//    
//    for (int i = 1; i <= 5; ++i) {
//        if (battleId % 2 > 0) {
//            id += 2;
//        }
//        else
//        {
//            id--;
//        }
//        id = (id+PetCnt)%(PetCnt+1);
//        arrEnemy.push_back(id+off);
//    }
    
    
//    for (int i = 1; i < 3; ++i) {
//        if (i*2 + off == id) {
//            continue;
//        }
//        arrEnemy.push_back(i*2 + off);
//    }
//    
//    for (int i = 1; i < 3; i++) {
//        arrEnemy.push_back(i*2 - 1 + off);
//    }
    
//    return arrEnemy;
    return chooseFromVect(arrEnemy, 1);
}
//前排全体}
std::vector<uint16> FightAI::chooseByTypeBFAll(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    //先取前排。}
    for (int i = 1; i <= 3; ++i) {
        FightPet* pet = team->GetTeam()[1 + 2*(i-1) + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        arrEnemy.push_back(pet->getPetInfo().wBattleIndex);
    }
    
    if (arrEnemy.size() > 0) {
        return arrEnemy;
    }
    //如果前排没有怪则选后排}
    for (int i = 1; i <= 3; ++i) {
        FightPet* pet = team->GetTeam()[2*i + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        arrEnemy.push_back(pet->getPetInfo().wBattleIndex);
    }
    
    return arrEnemy;
}
//后排全体}
std::vector<uint16> FightAI::chooseByTypeAFAll(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    //先取后排。}
    for (int i = 1; i <= 3; ++i) {
        FightPet* pet = team->GetTeam()[2*i + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        arrEnemy.push_back(pet->getPetInfo().wBattleIndex);
    }
    
    if (arrEnemy.size() > 0) {
        return arrEnemy;
    }
    //如果后排没有怪则选前排}
    for (int i = 1; i <= 3; ++i) {
        FightPet* pet = team->GetTeam()[1 + 2*(i-1) + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        arrEnemy.push_back(pet->getPetInfo().wBattleIndex);
    }
    
    return arrEnemy;
}
//全体}
std::vector<uint16> FightAI::chooseByTypeAll(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    for (int i = 1; i <= PetCnt; i++) {
        FightPet* pet = team->GetTeam()[i + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        arrEnemy.push_back(pet->getPetInfo().wBattleIndex);
    }
    
    return arrEnemy;
}
//随机2目标}
std::vector<uint16> FightAI::chooseByTypeRandTow(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    arrEnemy = chooseInRandom(0, team, 2);
    
    return arrEnemy;
}
//随机3目标}
std::vector<uint16> FightAI::chooseByTypeRandThree(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    arrEnemy = chooseInRandom(0, team, 3);
    
    return arrEnemy;
}
//敌方攻击最高的}
std::vector<uint16> FightAI::chooseByTypeAtkMax(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    uint32 atk = 0;
    uint16 id = 0;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    for ( int i = 1; i <= PetCnt; i++) {
        FightPet* pet = team->GetTeam()[i + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        if (pet->getPetInfo().wAttack > atk) {
            atk = pet->getPetInfo().wAttack;
            id = pet->getPetInfo().wBattleIndex;
        }
    }
    
    if (id != 0) {
        arrEnemy.push_back(id);
    }
    
    return arrEnemy;
}
//敌方血量最少的}
std::vector<uint16> FightAI::chooseByTypeHpMin(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    uint32 hp = 9999999;
    uint16 id = 0;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    for ( int i = 1; i <= PetCnt; i++) {
        FightPet* pet = team->GetTeam()[i + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        if (pet->getCurHP() < hp) {
            hp = pet->getCurHP();
            id = pet->getPetInfo().wBattleIndex;
        }
    }
    
    if (id != 0) {
        arrEnemy.push_back(id);
    }
    
    
    return arrEnemy;
}
//敌方防御最低的}
std::vector<uint16> FightAI::chooseByTypeDefMin(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    uint32 def = 9999999;
    uint16 id = 0;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    for ( int i = 1; i <= PetCnt; i++) {
        FightPet* pet = team->GetTeam()[i + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        if (pet->getPetInfo().wDefense < def) {
            def = pet->getPetInfo().wDefense;
            id = pet->getPetInfo().wBattleIndex;
        }
    }
    
    if (id != 0) {
        arrEnemy.push_back(id);
    }
    
    return arrEnemy;
}
//选择固定属性的}
std::vector<uint16> FightAI::chooseByTypeNautre(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    FightPet* pet = getFightPetByBIndex(battleId);
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->getPetInfo().wSkillId);
    if (!ultCfg) {
        CCLOG("pet %d UltimateSkill %d not found", battleId, pet->getPetInfo().wSkillId);
        return arrEnemy;
    }
//    ultCfg->byEffectNature1;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    for (int i = 1; i <= PetCnt; ++i) {
        FightPet* petE = team->GetTeam()[i+off];
        if (!petE || petE->getCurHP() == 0 ||
            petE->getPetInfo().petNature != ultCfg->byEffectNature1) {
            continue;
        }
        arrEnemy.push_back(petE->getPetInfo().wBattleIndex);
    }
    if (arrEnemy.size() == 0) {
        return chooseInRandom(0, team, 1);
    }
    else
    {
        return chooseFromVect(arrEnemy, 1);
    }
    
    return arrEnemy;
}
// 当前纵列}
std::vector<uint16> FightAI::chooseByTypeColumn(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    int column = (battleId % 100 - 1) / 2;
    
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    arrEnemy.push_back(column*2 + 1 + off);
    arrEnemy.push_back(column*2 + 2 + off);
    
    arrEnemy = chooseFromVect(arrEnemy, 2);
    if (arrEnemy.size() > 0) {
        return arrEnemy;
    }
//    arrEnemy.clear();
    for (int i = 0; i < 3; i++) {
        if (i == column ) {
            continue;
        }
        arrEnemy.clear();
        arrEnemy.push_back(i*2 + 1 + off);
        arrEnemy.push_back(i*2 + 2 + off);
        
        arrEnemy = chooseFromVect(arrEnemy, 2);
        if (arrEnemy.size() > 0) {
            return arrEnemy;
        }
    }
    
    return arrEnemy;
}

//敌方攻击最高的(2个目标)}
std::vector<uint16> FightAI::chooseByTypeAtkMax_2(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    uint32 atk1 = 0;
    uint16 id1 = 0;
    uint32 atk2 = 0;
    uint16 id2 = 0;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    for ( int i = 1; i <= PetCnt; i++) {
        FightPet* pet = team->GetTeam()[i + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        if (pet->getPetInfo().wAttack > atk2) {
            atk2 = pet->getPetInfo().wAttack;
            id2 = pet->getPetInfo().wBattleIndex;
            
            if (atk2 > atk1) {
                uint32 tempAtk = atk1;
                atk1 = atk2;
                atk2 = tempAtk;
                
                uint16 tempId = id1;
                id1 = id2;
                id2 = tempId;
            }
        }
    }
    
    if (id1 != 0) {
        arrEnemy.push_back(id1);
    }
    
    if (id2 != 0) {
        arrEnemy.push_back(id2);
    }
    
    return arrEnemy;
}
//敌方血量最少的(2个目标)}
std::vector<uint16> FightAI::chooseByTypeHpMin_2(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    uint32 hp1 = 9999999;
    uint16 id1 = 0;
    uint32 hp2 = 9999999;
    uint16 id2 = 0;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    for ( int i = 1; i <= PetCnt; i++) {
        FightPet* pet = team->GetTeam()[i + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        if (pet->getCurHP() < hp2) {
            hp2 = pet->getCurHP();
            id2 = pet->getPetInfo().wBattleIndex;
            
            if (hp1 > hp2) {
                uint32 tempHp = hp1;
                hp1 = hp2;
                hp2 = tempHp;
                
                uint16 tempId = id1;
                id1 = id2;
                id2 = tempId;
            }
        }
    }
    
    if (id1 != 0) {
        arrEnemy.push_back(id1);
    }
    
    if (id2 != 0) {
        arrEnemy.push_back(id2);
    }
    
    return arrEnemy;
}
//敌方防御最低的(2个目标)}
std::vector<uint16> FightAI::chooseByTypeDefMin_2(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    uint32 def1 = 0;
    uint16 id1 = 0;
    uint32 def2 = 0;
    uint16 id2 = 0;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    for ( int i = 1; i <= PetCnt; i++) {
        FightPet* pet = team->GetTeam()[i + off];
        if (!pet || pet->getCurHP() == 0) {
            continue;
        }
        if (pet->getPetInfo().wDefense < def2) {
            def2 = pet->getPetInfo().wDefense;
            id2 = pet->getPetInfo().wBattleIndex;
            
            if (def1 > def2) {
                uint32 tempAtk = def1;
                def1 = def2;
                def2 = tempAtk;
                
                uint16 tempId = id1;
                id1 = id2;
                id2 = tempId;
            }
        }
    }
    
    if (id1 != 0) {
        arrEnemy.push_back(id1);
    }
    
    if (id2 != 0) {
        arrEnemy.push_back(id2);
    }
    
    return arrEnemy;
}
//选择固定属性的(2个目标)}
std::vector<uint16> FightAI::chooseByTypeNautre_2(uint16 battleId, FightTeam* team)
{
    std::vector<uint16> arrEnemy;
    
    FightPet* pet = getFightPetByBIndex(battleId);
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->getPetInfo().wSkillId);
    if (!ultCfg) {
        CCLOG("pet %d UltimateSkill %d not found", battleId, pet->getPetInfo().wSkillId);
        return arrEnemy;
    }
    //    ultCfg->byEffectNature1;
    int off = 100;
    if (team->GetTeamType() == team->E_TEAM_TYPE_MY) {
        off = 0;
    }
    for (int i = 1; i <= PetCnt; ++i) {
        FightPet* petE = team->GetTeam()[i+off];
        if (!petE || petE->getCurHP() == 0 ||
            petE->getPetInfo().petNature != ultCfg->byEffectNature1) {
            continue;
        }
        arrEnemy.push_back(petE->getPetInfo().wBattleIndex);
    }
    if (arrEnemy.size() == 0) {
        return chooseInRandom(0, team, 2);
    }
    else
    {
        return chooseFromVect(arrEnemy, 2);
    }
    return arrEnemy;
}

//敌方攻击时 选怪}
std::vector<uint16> FightAI::chooseEnemy(uint16 wBattleIndex, uint32 skillId)
{
    std::vector<uint16> arrEnemy;

    return arrEnemy;
}
//纯随即选择}
std::vector<uint16> FightAI::chooseInRandom(uint16 wNoChoose, FightTeam *team, uint8 count)
{
    std::vector<uint16> arrEnemy;
    if (count == 0) {
        return arrEnemy;
    }
    
    std::vector<uint16> arrRand;
    FightTeam::MapFightTeam mapPet = team->GetTeam();
    FightTeam::MapFightTeam::iterator it = mapPet.begin();
    for (; it != mapPet.end(); it++) {
        if (!it->second) {
            continue;
        }
        if (it->second->getIsCanDead() && it->second->getCurHP() == 0) {
            continue;
        }
        if (it->first == wNoChoose) {
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
//顺序选择}
std::vector<uint16> FightAI::chooseInOrder(uint16 wNoChoose, FightTeam *team, uint8 count)
{
    std::vector<uint16> arrEnemy;
    if (count == 0) {
        return arrEnemy;
    }
    
    std::vector<uint16> arrRand;
    std::map<uint16, FightPet*>::iterator it = team->GetTeam().begin();
    for (; it != team->GetTeam().end(); it++) {
        if (count <= 0) {
            break;
        }
        if (!it->second) {
            continue;
        }
        if (it->second->getIsCanDead() && it->second->getCurHP() == 0) {
            continue;
        }
        if (it->first == wNoChoose) {
            continue;
        }
        arrEnemy.push_back(it->first);
        count--;
        
    }
    
    return arrEnemy;
}

//设置当前回合掉落}
void FightAI::setCurRoundDropItem(bool isWaveEnd)
{
    m_arrCurRoundDropItems.clear();
    //回合开始即设置当前回合的金钱及物品的掉落，材料掉落由战斗中随机取得}
    for (int i = 0; i < m_arrCurWaveDropItems.size(); i++) {
        STC_ITEM_DROP aItem = m_arrCurWaveDropItems[i];
        if (aItem.wHasCount == 0) {
            continue;
        }
        STC_ITEM_DROP item;
        //        std::vector<STC_ITEM_DROP> arrI;
        switch (aItem.wItemType / E_UNITE_BASE_FABIO) {
            case E_UNITE_TYPE_SPECIAL:
                item.wItemType = aItem.wItemType;
                if (isWaveEnd) {
                    item.wCount = aItem.wHasCount;
                }
                else
                {
                    //安照 每波5回合、6个满员的情况，均分金钱和魂，来分配每次攻击的掉落}
                    item.wCount = (CCRANDOM_0_1()*0.5 + 0.5) * (aItem.wCount / 5);
                    if (item.wCount > aItem.wHasCount) {
                        item.wCount = aItem.wHasCount;
                    }
                }
                
                aItem.wHasCount -= item.wCount;
                
                m_arrCurRoundDropItems.push_back(item);
                break;
                
            default:
                break;
        }
        m_arrCurWaveDropItems[i] = aItem;
    }
}
//设置宝箱掉落
void FightAI::setBoxDrop()
{
    int cnt = 0;
    int pCnt = m_enemyTeam->getLivePetCount();
    //给boss分3个
    uint16 wNoChoose = 0;
    FightPet* pet = getFightPetByBIndex(103);
    if (pet && pet->getPetInfo().isBoss && pet->getCurHP() > 0) {
        wNoChoose = 103;
        std::vector<STC_ITEM_DROP> arrItem;
        int iCnt = MIN(3, m_arrBoxItems.size());
        
        if (pCnt == 1) {
            iCnt = m_arrBoxItems.size();
        }
        
        for (int k = 0; k < iCnt; k++) {
            STC_ITEM_DROP item = m_arrBoxItems[cnt];
            arrItem.push_back(item);
            cnt++;
        }
        STC_PET_INFO info = pet->getPetInfo();
        info.boxItem = arrItem;
        pet->setPetInfo(info);
        
        pCnt--;
    }

    if (cnt >= m_arrBoxItems.size()) {
        return;
    }
    
    std::vector<uint16> arrEn = chooseInRandom(wNoChoose, m_enemyTeam, pCnt);
    
    if (arrEn.size() == 0) {
        return;
    }
    
    int dCnt = (m_arrBoxItems.size() - cnt) / arrEn.size();
    int moCnt = (m_arrBoxItems.size() - cnt) % arrEn.size();
    
    for (int i = 0; i < arrEn.size(); i++) {
        FightPet* pet = getFightPetByBIndex(arrEn[i]);

        std::vector<STC_ITEM_DROP> arrItem;
        int iCnt = dCnt;
        if (i < moCnt) {
            iCnt++;
        }
        for (int k = 0; k < iCnt; k++) {
            STC_ITEM_DROP item = m_arrBoxItems[cnt];
            arrItem.push_back(item);
            cnt++;
        }
        STC_PET_INFO info = pet->getPetInfo();
        info.boxItem = arrItem;
        pet->setPetInfo(info);
    }
}
//设置当前波次掉落}
void FightAI::setCurWaveDropItem()
{
    m_arrCurWaveDropItems.clear();
    dwCoinValue = 0;
    dwResValue = 0;
    
    if (m_curWave == m_allWaveCnt) {
        setBoxDrop();
    }
    
    //波次开始即设置当前波次的金钱及物品的掉落，材料掉落由战斗中随机取得}
    for (int i = 0; i < m_arrAllDropItems.size(); i++) {
        STC_ITEM_DROP aItem = m_arrAllDropItems[i];
        if (aItem.wHasCount == 0) {
            continue;
        }
        STC_ITEM_DROP item;
        //        std::vector<STC_ITEM_DROP> arrI;
        switch (aItem.wItemType / E_UNITE_BASE_FABIO) {
            case E_UNITE_TYPE_PET:
            {
                //最后一波把所有物品掉出}
                if (m_curWave == m_allWaveCnt) {
                    item.wCount = aItem.wHasCount;
                }
                else
                {
                    item.wCount = aItem.wCount / m_allWaveCnt;
                    
                    if (item.wCount % m_allWaveCnt >= m_curWave) {
                        item.wCount ++;
                    }
                }
                item.wCount = MIN(m_enemyTeam->getLivePetCount(), item.wCount);
                item.wCount = MIN(aItem.wHasCount, item.wCount);
                
                std::vector<uint16> arrEn = chooseInRandom(0, m_enemyTeam, item.wCount);
                if (arrEn.size() == 0) {
                    continue;
                }
                for (int i = 0; i < arrEn.size(); i++) {
                    FightPet* pet = getFightPetByBIndex(arrEn[i]);
                    STC_PET_INFO info = pet->getPetInfo();
                    info.isEgg = true;
                    pet->setPetInfo(info);
                }
                
                aItem.wHasCount -= item.wCount;
                
                m_arrCurWaveDropItems.push_back(item);
            }
                break;
            case E_UNITE_TYPE_SPECIAL:
                item.wItemType = aItem.wItemType;
                //最后一波把所有物品掉出}
                if (m_curWave == m_allWaveCnt) {
                    item.wCount = aItem.wHasCount;
                }
                else
                {
                    item.wCount = (CCRANDOM_0_1()*0.1 + 0.9) * (aItem.wCount /(m_allWaveCnt+1));
                }
                if (item.wCount > aItem.wHasCount) {
                    item.wCount = aItem.wHasCount;
                }
                item.wHasCount = item.wCount;
                
                //每波次最多掉30个金币}
                if (aItem.wItemType % E_UNITE_BASE_FABIO == E_SPECIAL_ID_COIN) {
                    dwCoinValue = item.wCount / waveMaxCoin;
                    
                    if (item.wCount % waveMaxCoin > waveMaxCoin * 0.5) {
                        dwCoinValue++;
                    }
                    
                    if (dwCoinValue == 0) {
                        dwCoinValue = 1;
                    }
                }
                else if(aItem.wItemType % E_UNITE_BASE_FABIO == E_SPECIAL_ID_FARM_RES) {
                    dwResValue = item.wCount / waveMaxCoin;
                    
                    if (item.wCount % waveMaxCoin > waveMaxCoin * 0.5) {
                        dwResValue++;
                    }
                    
                    if (dwResValue == 0) {
                        dwResValue = 1;
                    }
                }
                
                aItem.wHasCount -= item.wCount;
                
                m_arrCurWaveDropItems.push_back(item);
                break;
                
            default:
                break;
        }
        m_arrAllDropItems[i] = aItem;
    }
    
}

std::vector<uint32> FightAI::getItemValue(uint8 cnt, uint32 dwAllValue)
{
    std::vector<uint32> arr;
    // bug fixed, cnt may equal 0
    if (cnt == 0) {
        return arr;
    }
    uint32 value = dwAllValue / cnt;
    for (int i = 0; i < cnt; i++) {
        if (i == 0) {
            arr.push_back(value + dwAllValue - value*cnt);
        }
        else
        {
            arr.push_back(value);
        }
    }
    
    return arr;
}
//获取此次攻击的物品掉落（不包括心珠）}
std::vector<STC_ITEM_DROP> FightAI::getDropItemByDamage(int damage, FightPet *enemy)
{
    std::vector<STC_ITEM_DROP> arrItem;
    if (damage == 0) {
        return arrItem;
    }
    if (FightAI::getFightType() == E_BATTLE_TYPE_COIN_TREE) {
        //金币}
        int cnt1 = rand() % (7 - 4) + 4;
        uint32 money = damage * ((float)getDamFloat().dwCoinCatFloat / 10000);
        uint32 value = money / cnt1;
        for (int i = 0; i < cnt1; i++) {
            STC_ITEM_DROP item;
            item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_COIN;
            item.wCount = 1;
            if (i == cnt1 - 1) {
                value = money - value*i;
            }
            item.wValue = value;
            arrItem.push_back(item);
        }
        return arrItem;
    }

    //金币、魂的掉落}
    int cnt1 = rand() % (3 - 1) + 1;
    int cnt2 = rand() % (3 - 1) + 1;
    bool lastFlag = false;
    if (enemy->getCurHP() == 0) {
        //如果波次结束，并且当前是最后死的一个怪}
        CCLog(" diao luo shi tui wu xue liang %d,,,,,%d", enemy->getMyTeam()->GetTeamHp(), enemy->getMyTeam()->GetTeamType());
        if (enemy->getMyTeam()->GetTeamHp() == 0 && !enemy->getMyTeam()->getLastDeadFlag()) {
            enemy->getMyTeam()->setLastDeadFlag(true);
            lastFlag = true;

            if(enemy->getIsBoss())
            {
                cnt1 += rand() % (8 - 4) + 4;
                cnt2 += rand() % (8 - 4) + 4;
            }
        }
    }
    
    //这段是为了：当钱和魂掉落完了，不再无条件掉落出来, 另外，波次最后一个死亡的怪，把本波中所有的钱都掉出来}
    for (int i = 0; i < m_arrCurWaveDropItems.size(); i++) {
        STC_ITEM_DROP aItem = m_arrCurWaveDropItems[i];
        switch (aItem.wItemType / E_UNITE_BASE_FABIO) {
            case E_UNITE_TYPE_SPECIAL:
                
            {
                switch (aItem.wItemType % E_UNITE_BASE_FABIO) {
                    case E_SPECIAL_ID_COIN:
                        
                        if (lastFlag || cnt1 * dwCoinValue > aItem.wHasCount) {
                            if (lastFlag) {
                                cnt1 = MIN(aItem.wHasCount / dwCoinValue, 8);
                            }
                            else
                            {
                                cnt1 = 1;
                            }
                            
                            std::vector<uint32> arrValue = getItemValue(cnt1, aItem.wHasCount);
                            
                            for (int i = 0; i < arrValue.size(); i++) {
                                if (arrValue[i] == 0) {
                                    continue;
                                }
                                STC_ITEM_DROP item;
                                item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_COIN;
                                item.wCount = 1;
                                item.wValue = arrValue[i];
                                aItem.wHasCount -= arrValue[i];
                                arrItem.push_back(item);
                            }
                            m_arrCurWaveDropItems[i] = aItem;
                            continue;
                        }
                        
                        for (int i = 0; i < cnt1; i++) {
                            STC_ITEM_DROP item;
                            item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_COIN;
                            item.wCount = 1;
                            item.wValue = dwCoinValue;
                            aItem.wHasCount -= dwCoinValue;
                            arrItem.push_back(item);
                        }
                        break;
                    case E_SPECIAL_ID_FARM_RES:
                        if (lastFlag || cnt2 * dwResValue > aItem.wHasCount) {
                            if (lastFlag) {
                                cnt2 = MIN(aItem.wHasCount / dwResValue, 8);
                            }
                            else
                            {
                                cnt2 = 1;
                            }
                            
                            std::vector<uint32> arrValue = getItemValue(cnt2, aItem.wHasCount);
                            
                            for (int i = 0; i < arrValue.size(); i++) {
                                STC_ITEM_DROP item;
                                item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_FARM_RES;
                                item.wCount = 1;
                                item.wValue = arrValue[i];
                                aItem.wHasCount -= arrValue[i];
                                arrItem.push_back(item);
                            }
                            continue;
                        }
                        
                        for (int i = 0; i < cnt2; i++) {
                            STC_ITEM_DROP item;
                            item.wItemType = E_UNITE_TYPE_SPECIAL * E_UNITE_BASE_FABIO + E_SPECIAL_ID_FARM_RES;
                            item.wCount = 1;
                            item.wValue = dwResValue;
                            aItem.wHasCount -= dwResValue;
                            arrItem.push_back(item);
                        }
                        break;
                    default:
                        break;
                }
                
                m_arrCurWaveDropItems[i] = aItem;
            }
                break;
                
            default:
                break;
        }
    }
    
    
    //材料、装备、玉的掉落}
    for (int i = 0; i < m_arrAllDropItems.size(); i++) {
        STC_ITEM_DROP aItem = m_arrAllDropItems[i];
        if (aItem.wHasCount == 0) {
            continue;
        }
        STC_ITEM_DROP item;
        std::vector<STC_ITEM_DROP> arrI;
        switch (aItem.wItemType / E_UNITE_BASE_FABIO) {
            case E_UNITE_TYPE_ITEM:
            case E_UNITE_TYPE_EQUIP:
            case E_UNITE_TYPE_GEM:
                if ((enemy->getIsBoss()
                    && enemy->getCurHP() == 0)
                    || (lastFlag && getCurWave() == getAllWaveCnt())) {
                    //如果boss死了 或者 最后一波的最后一个怪死的时候，把所有材料爆出}
                    for (int j = 0;j < aItem.wHasCount; j++) {
                        STC_ITEM_DROP it;
                        it.wItemType = aItem.wItemType;
                        it.wCount = 1;
                        arrItem.push_back(it);
                    }
                    aItem.wHasCount = 0;
                }
                else if (RandEither(20, 100)) {
                    item.wItemType = aItem.wItemType;
                    item.wCount = 1;
                    aItem.wHasCount--;
                    arrItem.push_back(item);
                }
                break;
            default:
                break;
        }
        m_arrAllDropItems[i] = aItem;
    }

    return arrItem;
}
//拆分物品(钱和魂)}
std::vector<STC_ITEM_DROP> FightAI::partItem(STC_ITEM_DROP item)
{
    std::vector<STC_ITEM_DROP> arrItem;
    
    return arrItem;
}