
#include "Pet.h"
#include "EnumDefines.h"

CPet::CPet(uint32 dwObjId)
:m_dwObjId(dwObjId)
{
	m_wIndex = 0;
    
    m_bIsLock = 0;
    
    m_byNature1 = 0;
    m_byNature2 = 0;
    m_byType1 = 0;
    m_byType2 = 0;
    m_byStarLv = 0;
    m_byEvolveLv = 0;
    m_byLv = 0;
    
    m_curExp = 0;
    
    m_dwBirthday = 0;
    
    m_dwHpValue = 0;
    m_dwAttackValue = 0;
    m_dwDefenseValue = 0;
    m_dwSAttackValue = 0;
    m_dwSDefenseValue = 0;
    m_dwRecoverValue = 0;
    
    m_dwCritRateValue = 0;
    m_dwCritHurtValue = 0;
    m_dwCritFreeValue = 0;
    m_dwSpeedValue = 0;
    m_dwHitValue = 0;
    m_dwDodgeValue = 0;

    
    m_wGemId = 0;
    m_byGemType = 0;
    m_dwGemSkillId = 0;
    m_wLeaderSkillId = 0;
    
    
    m_wPassiveSkillId1 = 0;
    m_wPassiveSkillId2 = 0;
    m_wPassiveSkillId3 = 0;
    m_wPassiveSkillId4 = 0;
    m_wPassiveSkillId5 = 0;
    m_wPassiveSkillId6 = 0;

    
    m_wNormaleAttId = 0;
    m_wInitialSkillId = 0;
    m_byInitialSkillLv = 0;
    m_dwInitalSkillExp = 0;
    
    m_byTeamId1 = 0;
	m_byTeamId2 = 0;
	m_byTeamId3 = 0;
	m_byTeamId4 = 0;
	m_byTeamId5 = 0;
	m_byTeamId6 = 0;
    
    m_dwEmblemId1 = 0;
    m_dwEmblemId2 = 0;
    
    m_byMaxLv = 0;
    
    
    m_wEquipId1 = 0;
    m_wEquipId2 = 0;
    m_wEquipId3 = 0;
    m_wEquipId4 = 0;
}

CPet::~CPet()
{
    
    
}

void CPet::DeSerializeDataClient(ByteBuffer &data)
{
	loadDataLoose(data);
    
	m_wIndex = getProperty(E_PET_wIndex).get<uint16>();

    m_byLv = getProperty(E_PET_byLv).get<uint8>();
    m_byEvolveLv = getProperty(E_PET_byEvolveClass).get<uint8>();
    m_curExp = getProperty(E_PET_dwExp).get<uint32>();
    m_byStarLv = getProperty(E_PET_byStarLv).get<uint8>();
    m_bIsLock = getProperty(E_PET_byIsLock).get<uint8>();
	
	m_byNature1 = getProperty(E_PET_byNature).get<uint8>();
	m_byNature2 = getProperty(E_PET_byNatureExtra).get<uint8>();
    
	m_byType1 = getProperty(E_PET_byType).get<uint8>();
	m_byType2 = getProperty(E_PET_byTypeExtra).get<uint8>();
    
    
	m_dwHpValue = getProperty(E_PET_dwHPShow).get<uint32>();
	m_dwAttackValue = getProperty(E_PET_dwCAShow).get<uint32>();
	m_dwDefenseValue = getProperty(E_PET_dwCDShow).get<uint32>();
    m_dwSAttackValue = getProperty(E_PET_dwSAShow).get<uint32>();
	m_dwSDefenseValue = getProperty(E_PET_dwSDShow).get<uint32>();
	m_dwRecoverValue = getProperty(E_PET_dwRVShow).get<uint32>();
    
    
    m_dwSpeedValue = getProperty(E_PET_dwSpeed).get<uint32>();
    m_dwHitValue = getProperty(E_PET_dwHit).get<uint32>();
	m_dwDodgeValue = getProperty(E_PET_dwDodge).get<uint32>();
    m_dwCritRateValue = getProperty(E_PET_dwCriteRate).get<uint32>();
    m_dwCritHurtValue = getProperty(E_PET_dwCriteHurt).get<uint32>();
	m_dwCritFreeValue = getProperty(E_PET_dwCriteFree).get<uint32>();
    
    m_wInitialSkillId = getProperty(E_PET_dwInitialSpellId).get<uint32>();
    m_byInitialSkillLv = getProperty(E_PET_byInitialSpellLv).get<uint8>();
    m_wNormaleAttId = getProperty(E_PET_dwNormalSpellId).get<uint32>();
    
	m_wPassiveSkillId1 = getProperty(E_PET_dwSpellId1).get<uint32>();
	m_wPassiveSkillId2 = getProperty(E_PET_dwSpellId2).get<uint32>();
	m_wPassiveSkillId3 = getProperty(E_PET_dwSpellId3).get<uint32>();
	m_wPassiveSkillId4 = getProperty(E_PET_dwSpellId4).get<uint32>();
	m_wPassiveSkillId5 = getProperty(E_PET_dwSpellId5).get<uint32>();
    m_wPassiveSkillId6 = getProperty(E_PET_dwSpellId6).get<uint32>();
    
	
    m_wLeaderSkillId = getProperty(E_PET_dwLeaderSpellId).get<uint32>();
    
    m_wGemId = getProperty(E_PET_dwGemId).get<uint32>();
    m_dwBirthday = getProperty(E_PET_dwGetTime).get<uint32>();
    
    m_dwFightValue = getProperty(E_PET_dwFightScore).get<uint32>();
    
    m_byTeamId1 = getProperty(E_PET_byTeamId1).get<uint8>();
	m_byTeamId2 = getProperty(E_PET_byTeamId2).get<uint8>();
	m_byTeamId3 = getProperty(E_PET_byTeamId3).get<uint8>();
	m_byTeamId4 = getProperty(E_PET_byTeamId4).get<uint8>();
	m_byTeamId5 = getProperty(E_PET_byTeamId5).get<uint8>();
	m_byTeamId6 = getProperty(E_PET_byTeamId6).get<uint8>();
    
    m_byGemType = getProperty(E_PET_byGemType).get<uint8>();
    m_dwGemSkillId = getProperty(E_PET_dwGemSpellId).get<uint32>();
    
    
    m_dwEmblemId1 = getProperty(E_PET_dwEmblem1).get<uint32>();
    m_dwEmblemId2 = getProperty(E_PET_dwEmblem2).get<uint32>();
    
   
    
}

void CPet::PropertyUpdate(ByteBuffer & data)
{
	loadDataLoose(data);
	std::map<CDynamicStruct::key_type,AnyType> mapData;
	toMap(mapData);
	for(std::map<CDynamicStruct::key_type,AnyType>::iterator ii = mapData.begin(); ii != mapData.end(); ++ii)
	{
		switch(ii->first)
		{
            case E_PET_wIndex:   m_wIndex = getProperty(E_PET_wIndex).get<uint16>(); break;
            case E_PET_byIsLock:   m_bIsLock = getProperty(E_PET_byIsLock).get<uint8>(); break;
            case E_PET_byNature:    m_byNature1 = getProperty(E_PET_byNature).get<uint8>(); break;
            case E_PET_byNatureExtra:    m_byNature2 = getProperty(E_PET_byNatureExtra).get<uint8>(); break;
            case E_PET_byType:      m_byType1 = getProperty(E_PET_byType).get<uint8>(); break;
            case E_PET_byTypeExtra:      m_byType2 = getProperty(E_PET_byTypeExtra).get<uint8>(); break;
            case E_PET_byStarLv:     m_byStarLv = getProperty(E_PET_byStarLv).get<uint8>(); break;
            case E_PET_byLv:          m_byLv = getProperty(E_PET_byLv).get<uint8>(); break;
            case E_PET_byEvolveClass:      m_byEvolveLv = getProperty(E_PET_byEvolveClass).get<uint8>(); break;
            case E_PET_dwExp:     m_curExp = getProperty(E_PET_dwExp).get<uint32>(); break;
            case E_PET_dwGetTime:    m_dwBirthday = getProperty(E_PET_dwGetTime).get<uint32>(); break;
            case E_PET_dwHPShow:    m_dwHpValue = getProperty(E_PET_dwHPShow).get<uint32>(); break;
            case E_PET_dwCAShow:    m_dwAttackValue = getProperty(E_PET_dwCAShow).get<uint32>(); break;
            case E_PET_dwCDShow:  m_dwDefenseValue = getProperty(E_PET_dwCDShow).get<uint32>(); break;
            case E_PET_dwSAShow:    m_dwSAttackValue = getProperty(E_PET_dwSAShow).get<uint32>(); break;
            case E_PET_dwSDShow:  m_dwSDefenseValue = getProperty(E_PET_dwSDShow).get<uint32>(); break;
            case E_PET_dwRVShow:   m_dwRecoverValue = getProperty(E_PET_dwRVShow).get<uint32>(); break;
            case E_PET_dwCriteRate:      m_dwCritRateValue = getProperty(E_PET_dwCriteRate).get<uint32>(); break;
            case E_PET_dwCriteHurt:      m_dwCritHurtValue = getProperty(E_PET_dwCriteHurt).get<uint32>(); break;
            case E_PET_dwCriteFree:      m_dwCritFreeValue = getProperty(E_PET_dwCriteFree).get<uint32>(); break;
            case E_PET_dwSpeed:      m_dwSpeedValue = getProperty(E_PET_dwSpeed).get<uint32>(); break;
            case E_PET_dwHit:   m_dwHitValue = getProperty(E_PET_dwHit).get<uint32>(); break;
            case E_PET_dwDodge:      m_dwDodgeValue = getProperty(E_PET_dwDodge).get<uint32>(); break;
            case E_PET_dwGemId:      m_wGemId = getProperty(E_PET_dwGemId).get<uint32>(); break;
            case E_PET_byGemType:      m_byGemType = getProperty(E_PET_byGemType).get<uint32>(); break;
            case E_PET_dwGemSpellId:      m_dwGemSkillId = getProperty(E_PET_dwGemSpellId).get<uint32>(); break;
            case E_PET_dwLeaderSpellId: m_wLeaderSkillId = getProperty(E_PET_dwLeaderSpellId).get<uint32>(); break;
            case E_PET_dwSpellId1:  m_wPassiveSkillId1 = getProperty(E_PET_dwSpellId1).get<uint32>(); break;
            case E_PET_dwSpellId2:  m_wPassiveSkillId2 = getProperty(E_PET_dwSpellId2).get<uint32>(); break;
            case E_PET_dwSpellId3:  m_wPassiveSkillId3 = getProperty(E_PET_dwSpellId3).get<uint32>(); break;
            case E_PET_dwSpellId4:  m_wPassiveSkillId4 = getProperty(E_PET_dwSpellId4).get<uint32>(); break;
            case E_PET_dwSpellId5:  m_wPassiveSkillId5 = getProperty(E_PET_dwSpellId5).get<uint32>(); break;
            case E_PET_dwSpellId6:  m_wPassiveSkillId6 = getProperty(E_PET_dwSpellId6).get<uint32>(); break;
            case E_PET_dwInitialSpellId:     m_wInitialSkillId = getProperty(E_PET_dwInitialSpellId).get<uint32>(); break;
            case E_PET_dwNormalSpellId:     m_wNormaleAttId = getProperty(E_PET_dwNormalSpellId).get<uint32>(); break;
            case E_PET_byInitialSpellLv:    m_byInitialSkillLv = getProperty(E_PET_byInitialSpellLv).get<uint8>();break;
            case E_PET_byTeamId1:  m_byTeamId1 = getProperty(E_PET_byTeamId1).get<uint8>(); break;
            case E_PET_byTeamId2:  m_byTeamId2 = getProperty(E_PET_byTeamId2).get<uint8>(); break;
            case E_PET_byTeamId3:  m_byTeamId3 = getProperty(E_PET_byTeamId3).get<uint8>(); break;
            case E_PET_byTeamId4:  m_byTeamId4 = getProperty(E_PET_byTeamId4).get<uint8>(); break;
            case E_PET_byTeamId5:  m_byTeamId5 = getProperty(E_PET_byTeamId5).get<uint8>(); break;
            case E_PET_byTeamId6:  m_byTeamId6 = getProperty(E_PET_byTeamId6).get<uint8>(); break;
            case E_PET_dwEmblem1:  m_dwEmblemId1 = getProperty(E_PET_dwEmblem1).get<uint32>(); break;
            case E_PET_dwEmblem2:  m_dwEmblemId2 = getProperty(E_PET_dwEmblem2).get<uint32>(); break;
                
            case E_PET_dwFightScore:  m_dwFightValue = getProperty(E_PET_dwFightScore).get<uint32>(); break;
		};
	}
}







