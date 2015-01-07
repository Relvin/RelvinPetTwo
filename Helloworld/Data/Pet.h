#ifndef _PET_H
#define _PET_H

#include "DynamicStruct.h"
//#include "Observer.h"
#include "ByteBuffer.h"
#include <string>

#define PET_PROPERTY_DEF(T,name) \
	T Get##name() { return m_##name;}; \
	void Set##name(T name) { m_##name = name;}; \

#define GET_EVOLVE_ID(id, eLv) id * 100 + eLv
class CPet: public CDynamicStruct
{
public:
	enum
	{
		E_P_MIN_LV = 1,
		E_P_MAX_LV = 100,
		E_P_MALE = 1,
		E_P_FEMALE = 0,
		E_P_CHAR_PASSION = 0, 
		E_P_CHAR_SOBER = 1,
		E_P_CHAR_WAYWARD = 2,
		E_P_CHAR_SLY = 3,
		E_P_CHAR_LOVE = 4,
		E_P_CHAR_END,
	};

	typedef enum _E_MATE_TYPE
	{
		E_MATE_NONE,			//无}
		E_MATE_MONSTER,			// 怪兽组}
		E_MATE_SPRITE,			// 精灵类}
		E_MATE_HUMAN,			// 人形类}
		E_MATE_GOD,             // 神}
		E_MATE_DEMON,           // 魔}
		E_MATE_MACHINE,         // 机械}
		E_MATE_TYPE_END,
	}E_MATE_TYPE;


	CPet(uint32 dwObjId);
	~CPet();

	uint32 GetObjId() { return m_dwObjId;};
	void DeSerializeDataClient(ByteBuffer &data);
	void PropertyUpdate(ByteBuffer & data);

	/////////////
    PET_PROPERTY_DEF(uint16, wIndex);
    PET_PROPERTY_DEF(bool, bIsLock);
    PET_PROPERTY_DEF(std::string, strName);
    PET_PROPERTY_DEF(uint8, byNature1);
    PET_PROPERTY_DEF(uint8, byNature2);
    PET_PROPERTY_DEF(uint8, byType1);
    PET_PROPERTY_DEF(uint8, byType2);
    PET_PROPERTY_DEF(uint8, byStarLv);
    PET_PROPERTY_DEF(uint8, byEvolveLv);
    PET_PROPERTY_DEF(uint8, byLv);
    PET_PROPERTY_DEF(uint32, curExp);
    PET_PROPERTY_DEF(uint32, dwBirthday);
    PET_PROPERTY_DEF(uint32, dwFightValue);
    
    PET_PROPERTY_DEF(uint32,  dwHpValue);
    PET_PROPERTY_DEF(uint32,  dwAttackValue);
    PET_PROPERTY_DEF(uint32,  dwDefenseValue);
    PET_PROPERTY_DEF(uint32,  dwSAttackValue);
    PET_PROPERTY_DEF(uint32,  dwSDefenseValue);
    PET_PROPERTY_DEF(uint32,  dwRecoverValue);

    PET_PROPERTY_DEF(uint32,  dwSpeedValue);
    PET_PROPERTY_DEF(uint32,  dwHitValue);
    PET_PROPERTY_DEF(uint32,    dwDodgeValue);
    PET_PROPERTY_DEF(uint32,    dwCritRateValue);
    PET_PROPERTY_DEF(uint32,    dwCritHurtValue);
    PET_PROPERTY_DEF(uint32,    dwCritFreeValue);

    PET_PROPERTY_DEF(uint32,    wGemId);
    PET_PROPERTY_DEF(uint8,     byGemType);
    PET_PROPERTY_DEF(uint32,    dwGemSkillId);
    PET_PROPERTY_DEF(uint32,    wLeaderSkillId);
    PET_PROPERTY_DEF(uint32,	wPassiveSkillId1);
    PET_PROPERTY_DEF(uint32,	wPassiveSkillId2);
    PET_PROPERTY_DEF(uint32,    wPassiveSkillId3);
    PET_PROPERTY_DEF(uint32,	wPassiveSkillId4);
    PET_PROPERTY_DEF(uint32,	wPassiveSkillId5);
    PET_PROPERTY_DEF(uint32,	wPassiveSkillId6);

    PET_PROPERTY_DEF(uint32,    wInitialSkillId);
    PET_PROPERTY_DEF(uint32,    wNormaleAttId);
    PET_PROPERTY_DEF(uint8,     byInitialSkillLv);
    PET_PROPERTY_DEF(uint32,    dwInitalSkillExp);
    PET_PROPERTY_DEF(uint8,     byTeamId1);
    PET_PROPERTY_DEF(uint8,     byTeamId2);
    PET_PROPERTY_DEF(uint8,     byTeamId3);
    PET_PROPERTY_DEF(uint8,     byTeamId4);
    PET_PROPERTY_DEF(uint8,     byTeamId5);
    PET_PROPERTY_DEF(uint8,     byTeamId6);
    PET_PROPERTY_DEF(uint32,    dwEmblemId1);
    PET_PROPERTY_DEF(uint32,    dwEmblemId2);

    PET_PROPERTY_DEF(uint8,     byMaxLv);
    
    
    PET_PROPERTY_DEF(uint32,    wEquipId1);
    PET_PROPERTY_DEF(uint32,    wEquipId2);
    PET_PROPERTY_DEF(uint32,    wEquipId3);
    PET_PROPERTY_DEF(uint32,    wEquipId4);
private:
    uint32  m_dwObjId;
	uint16  m_wIndex;
    uint8   m_bIsLock;
    std::string m_strName;
    uint8   m_byNature1;
    uint8   m_byNature2;
    uint8   m_byType1;
    uint8   m_byType2;
    uint8   m_byStarLv;
    uint8   m_byEvolveLv;
    uint8   m_byLv;
    uint32  m_curExp;
    uint32  m_dwBirthday;
    
    uint32  m_dwFightValue;
    
    uint32  m_dwHpValue;
    uint32  m_dwAttackValue;
    uint32  m_dwDefenseValue;
    uint32  m_dwSAttackValue;
    uint32  m_dwSDefenseValue;
    uint32  m_dwRecoverValue;
    uint32  m_dwSpeedValue;
    uint32  m_dwHitValue;
    uint32  m_dwDodgeValue;
    uint32  m_dwCritRateValue;
    uint32  m_dwCritHurtValue;
    uint32  m_dwCritFreeValue;


    uint32  m_wGemId;
    uint8   m_byGemType;
    uint32  m_dwGemSkillId;
    uint32  m_wLeaderSkillId;
    uint32	m_wPassiveSkillId1;
    uint32	m_wPassiveSkillId2;
    uint32  m_wPassiveSkillId3;
    uint32	m_wPassiveSkillId4;
    uint32	m_wPassiveSkillId5;
    uint32  m_wPassiveSkillId6;
    uint32  m_wInitialSkillId;
    uint32  m_wNormaleAttId;
    uint8   m_byInitialSkillLv;
    uint32  m_dwInitalSkillExp;
    uint8   m_byTeamId1;
	uint8   m_byTeamId2;
	uint8   m_byTeamId3;
	uint8   m_byTeamId4;
	uint8   m_byTeamId5;
	uint8   m_byTeamId6;
    uint32  m_dwEmblemId1;
    uint32  m_dwEmblemId2;
    
    uint8   m_byMaxLv;
    
    
    uint32  m_wEquipId1;
    uint32  m_wEquipId2;
    uint32  m_wEquipId3;
    uint32  m_wEquipId4;
};


#endif