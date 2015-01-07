//
//  ConfigData.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-7-15.}
//
//

#include "ConfigData.h"
#include "ConfigUtil.h"
#include "ResourceStringConverter.h"


// read the cell and assign to an Integer, if this cell is empty, assign 0
#define GET_INT_DATA( _to, _row, _header_id )  \
do \
{ \
int _idx = m_pReader->getColumnIdxByHeaderId( _header_id ); \
if ( _idx < 0 ) \
{ \
IME_ERROR( "Column Header Not Found, id=%u", _header_id ); \
return false; \
} \
const char* v = (*_row)[ _idx ].c_str(); \
if ( strlen( v ) == 0 ) \
{\
_to = 0; \
}\
else \
{\
_to = atoi(v); \
}\
} while(0);

#define GET_STRING_DATA( _to, _row, _header_id ) \
_to = (*_row)[ m_pReader->getColumnIdxByHeaderId( _header_id ) ];


template <typename T>
void SplitCellToVector(std::vector<T>& vec, const std::string& cell, const std::string splitCh )
{
    std::vector<std::string> vRes;
    
    CUtil::StrSplit( cell, splitCh, vRes );
    FOR_EACH( std::string, strHitPoint, std::vector<std::string>, vRes )
    {
        vec.push_back( (T)atoi( strHitPoint.c_str() ) );
    }
}

bool PetConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_PET_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wGroupId  , row , E_CONFIG_PET_GROUP );
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_PET_INDEX );
        GET_STRING_DATA(t.strName, row, E_CONFIG_PET_NAME);
        GET_INT_DATA( t.byNature1  , row , E_CONFIG_PET_NATURE_1 );
        GET_INT_DATA( t.byNature2  , row , E_CONFIG_PET_NATURE_2 );
        GET_INT_DATA( t.byType1  , row , E_CONFIG_PET_TYPE_1 );
        GET_INT_DATA( t.byType2  , row , E_CONFIG_PET_TYPE_2 );
        GET_INT_DATA( t.byStarLv  , row , E_CONFIG_PET_STAR_LV );
        GET_INT_DATA( t.byLvMax  , row , E_CONFIG_PET_LV_MAX );
        GET_INT_DATA( t.dwExpFatio  , row , E_CONFIG_PET_EXP_FATIO );
        
        GET_INT_DATA( t.dwHpValue  , row , E_CONFIG_PET_HP_VALUE );
        GET_INT_DATA( t.dwAttackValue  , row , E_CONFIG_PET_ATTACK_VALUE );
        GET_INT_DATA( t.dwDeffenseValue  , row , E_CONFIG_PET_DEFFENSE_VALUE );
        GET_INT_DATA( t.dwSAttackValue  , row , E_CONFIG_PET_SATTACK_VALUE );
        GET_INT_DATA( t.dwSDeffenseValue  , row , E_CONFIG_PET_SDEFFENSE_VALUE );
        GET_INT_DATA( t.dwRecoverValue  , row , E_CONFIG_PET_RECOVER_VALUE );
        GET_INT_DATA( t.dwLuckValue  , row , E_CONFIG_PET_LUCK_VALUE );
        GET_INT_DATA( t.dwHitValue  , row , E_CONFIG_PET_HIT_VALUE );
        GET_INT_DATA( t.dwDodgeValue  , row , E_CONFIG_PET_DODGE_VALUE );
        
        GET_INT_DATA( t.dwHpChg  , row , E_CONFIG_PET_HP_CHG );
        GET_INT_DATA( t.dwAttackChg  , row , E_CONFIG_PET_ATTACK_CHG );
        GET_INT_DATA( t.dwDeffenseChg  , row , E_CONFIG_PET_DEFFENSE_CHG );
        GET_INT_DATA( t.dwSAttackChg  , row , E_CONFIG_PET_SATTACK_CHG );
        GET_INT_DATA( t.dwSDeffenseChg  , row , E_CONFIG_PET_SDEFFENSE_CHG );
        GET_INT_DATA( t.dwRecoverChg  , row , E_CONFIG_PET_RECOVER_CHG );
        GET_INT_DATA( t.dwLuckChg  , row , E_CONFIG_PET_LUCK_CHG );
        
        GET_INT_DATA( t.dwSpeedValue  , row , E_CONFIG_PET_SPEED_VALUE );
        GET_INT_DATA( t.dwSpeedChg  , row , E_CONFIG_PET_SPEED_CHG );
        
        GET_INT_DATA( t.wComboId  , row , E_CONFIG_PET_COMBO_ID );
        GET_INT_DATA( t.wEffectId  , row , E_CONFIG_PET_EFFECT_ID );
        GET_INT_DATA( t.wLeaderSkillId  , row , E_CONFIG_PET_LEADER_SKILL_ID );
        
        GET_INT_DATA( t.wPassiveSkillId1  , row , E_CONFIG_PET_PASSIVE_SKILL_ID_1 );
        GET_INT_DATA( t.wPassiveSkillId2  , row , E_CONFIG_PET_PASSIVE_SKILL_ID_2 );
        GET_INT_DATA( t.wPassiveSkillId3  , row , E_CONFIG_PET_PASSIVE_SKILL_ID_3 );
        GET_INT_DATA(t.dwTalentId, row, E_CONFIG_PET_TALENT_SKILL_ID);
        
        GET_INT_DATA( t.wInitialSkillId  , row , E_CONFIG_PET_INITIALSKILL_ID );
        GET_INT_DATA( t.dwNomaleAttId  , row , E_CONFIG_PET_NOMALE_ATT_ID );
        GET_INT_DATA( t.dwMergeExpFatio  , row , E_CONFIG_PET_MERGE_EXP_FATIO );
        GET_INT_DATA( t.dwMergeCoinFatio  , row , E_CONFIG_PET_MERGE_COIN_FATIO );
        
        GET_STRING_DATA(t.strDes, row, E_CONFIG_PET_DES);
        
        GET_INT_DATA(t.dwModelIndex, row, E_CONFIG_PET_MODEL);
        
        GET_INT_DATA(t.byAttackType, row, E_CONFIG_PET_ATTACK_TYPE);
        
        GET_INT_DATA( t.wStandFrame  , row , E_CONFIG_PET_STAND_FRAME );
        GET_INT_DATA( t.wAtkFrame  , row , E_CONFIG_PET_ATK_FRAME );
        GET_STRING_DATA(t.strKeyFrames, row, E_CONFIG_PET_KEY_FRAMES);
        GET_STRING_DATA(t.strAltKeyFrames, row, E_CONFIG_PET_ALT_KEY_FRAMES);
        GET_INT_DATA(t.wMusicId, row, E_CONFIG_PET_MUSIC_ID);
        GET_STRING_DATA(t.strStandSize, row, E_CONFIG_PET_STAND_SIZE);
        GET_STRING_DATA(t.strAtkSize, row, E_CONFIG_PET_ATK_SIZE);
        GET_INT_DATA(t.wSoundLeader, row, E_CONFIG_PET_SOUND_LEADER);
        GET_INT_DATA(t.wSoundAlt, row, E_CONFIG_PET_SOUND_ALT);
        GET_INT_DATA(t.wAltEffSound, row, E_CONFIG_PET_ALT_SOUND);
        GET_INT_DATA(t.byIsTujian, row, E_CONFIG_PET_IS_TUJIAN);
        GET_INT_DATA(t.byIsGachaShow, row, E_CONFIG_PET_IS_GACHASHOW);
        
        for (int k = 0; k < 4; k++) {
            GET_INT_DATA(t.arrQyIndex[k], row, E_CONFIG_PET_QY_INDEX + k);
        }

        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}

bool PetExpConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_PETEXP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wPetLv  , row , E_CONFIG_PETEXP_LV );
        GET_INT_DATA( t.dwNeedExp  , row , E_CONFIG_PETEXP_NEED_EXP );
                
        m_mapConfig.insert( std::make_pair( t.wPetLv, t ) );
    }
    
    return true;
}

bool PetModel::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_PET_MODEL_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_PET_MODEL_INDEX );
        GET_INT_DATA( t.wSkeletonIndex  , row , E_CONFIG_PET_MODEL_SKELETON_INDEX );
        GET_INT_DATA( t.wActIndex  , row , E_CONFIG_PET_MODEL_ACT_INDEX );
        GET_INT_DATA( t.wStartTime1  , row , E_CONFIG_PET_MODEL_START_TIME_1 );
        GET_INT_DATA( t.wEffIndex1  , row , E_CONFIG_PET_MODEL_EFF_INDEX_1 );
        GET_INT_DATA( t.wStartTime2  , row , E_CONFIG_PET_MODEL_START_TIME_2 );
        GET_INT_DATA( t.wEffIndex2  , row , E_CONFIG_PET_MODEL_EFF_INDEX_2 );
        GET_INT_DATA(t.wEffStandIndex, row, E_CONFIG_PET_MODEL_EFF_STAND);
        GET_STRING_DATA(t.strKeyFrame, row, E_CONFIG_PET_MODEL_KEY_FRAME);
        GET_INT_DATA( t.byMusicId, row, E_CONFIG_PET_MODEL_MUSIC);
        for (int k = 0; k < 30; k++) {
            int partId = 0;
            GET_INT_DATA( partId  , row , E_CONFIG_PET_MODEL_PART + k );
            if (partId != 0) {
                t.mapPart.insert(std::make_pair(k + 1, partId));
            }
        }
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}

bool LeaderSkillConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_LEADER_SKILL_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_LEAKER_SKILL_INDEX );
        GET_STRING_DATA(t.strName, row, E_CONFIG_LEAKER_SKILL_NAME)
        for ( int k = 0; k < 5; k++ )
        {
            GET_INT_DATA(t.wSkillType[k], row, E_CONFIG_LEAKER_SKILL_TYPE + k);
        }
        GET_INT_DATA( t.wStrikeCondition  , row , E_CONFIG_LEAKER_SKILL_STRINKE_CONDITION );
        GET_INT_DATA( t.byEffectNature1  , row , E_CONFIG_LEAKER_SKILL_EFF_NATURE_1 );
        GET_INT_DATA( t.byEffectNature2  , row , E_CONFIG_LEAKER_SKILL_EFF_NATURE_2 );
        GET_INT_DATA( t.byEffectType1  , row , E_CONFIG_LEAKER_SKILL_EFF_TYPE_1 );
        GET_INT_DATA( t.byEffectType2  , row , E_CONFIG_LEAKER_SKILL_EFF_TYPE_2 );
        for ( int k = 0; k < 8; k++ )
        {
            GET_INT_DATA(t.szSkillPara[k], row, E_CONFIG_LEAKER_SKILL_PARA + k);
        }
        GET_STRING_DATA(t.strDes, row, E_CONFIG_LEAKER_SKILL_DES)
        
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}


bool PassiveSkillConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_PASSIVE_SKILL_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.dwIndex  , row , E_CONFIG_PASSIVE_SKILL_INDEX );
        GET_STRING_DATA(t.strName, row, E_CONFIG_PASSIVE_SKILL_NAME)
        GET_INT_DATA( t.wStrikeCondition1  , row , E_CONFIG_PASSIVE_SKILL_STRIKE_CONDITION_1 );
        GET_INT_DATA( t.wStrikePara1  , row , E_CONFIG_PASSIVE_SKILL_STRIKE_PARA_1 );
        GET_INT_DATA( t.wStrikeChg1  , row , E_CONFIG_PASSIVE_SKILL_STRIKE_CHG_1 );
        
        GET_INT_DATA( t.byTriggerType  , row , E_CONFIG_PASSIVE_SKILL_TRIGGER_TYPE );
        
        GET_INT_DATA( t.wStrikeCondition2  , row , E_CONFIG_PASSIVE_SKILL_STRIKE_CONDITION_2 );
        GET_INT_DATA( t.wStrikePara2  , row , E_CONFIG_PASSIVE_SKILL_STRIKE_PARA_2 );
        GET_INT_DATA( t.wStrikeChg2  , row , E_CONFIG_PASSIVE_SKILL_STRIKE_CHG_2 );

//        GET_INT_DATA( t.byHurtType  , row , E_CONFIG_PASSIVE_SKILL_HURT_TYPE );
//        for ( int k = 0; k < 2; k++ )
//        {
//            GET_INT_DATA(t.szLevelPara[k], row, E_CONFIG_PASSIVE_SKILL_LV_PARA + k);
//        }
        GET_INT_DATA( t.byEffectNature1  , row , E_CONFIG_PASSIVE_SKILL_EFF_NATURE_1 );
        GET_INT_DATA( t.byEffectNature2  , row , E_CONFIG_PASSIVE_SKILL_EFF_NATURE_2 );
        GET_INT_DATA( t.byAttackerScope  , row , E_CONFIG_PASSIVE_SKILL_ATT_SCOPE );
        

        GET_INT_DATA( t.byDeffenseScope  , row , E_CONFIG_PASSIVE_SKILL_DEFF_SCOPE );
        GET_INT_DATA( t.byDeffenseEffectNature1  , row , E_CONFIG_PASSIVE_SKILL_DEFF_EFF_NATURE_1 );
        GET_INT_DATA( t.byDeffenseEffectNature2  , row , E_CONFIG_PASSIVE_SKILL_DEFF_EFF_NATURE_2 );

        
        GET_INT_DATA( t.wAttackBuffHit  , row , E_CONFIG_PASSIVE_SKILL_ATT_BUFF_HIT);
        GET_INT_DATA( t.wDeffenseBuffHit  , row , E_CONFIG_PASSIVE_SKILL_DEFF_BUFF_HIT);
        for (int k = 0; k < 3; k++) {
            GET_INT_DATA( t.wAttackBuff[k]  , row , E_CONFIG_PASSIVE_SKILL_ATT_BUFF + k);
            
            GET_INT_DATA( t.wAttackBuffTime[k]  , row , E_CONFIG_PASSIVE_SKILL_ATT_BUFF_TIME + k);
            
            GET_INT_DATA( t.wAttackEff[k]  , row , E_CONFIG_PASSIVE_SKILL_ATT_EFF + k);
            GET_INT_DATA( t.wAttackEffHit[k]  , row , E_CONFIG_PASSIVE_SKILL_ATT_EFF_HIT + k);
            
            
            GET_INT_DATA( t.wDeffenseBuff[k]  , row , E_CONFIG_PASSIVE_SKILL_DEFF_BUFF + k);
            
            GET_INT_DATA( t.wDeffenseBuffTime[k]  , row , E_CONFIG_PASSIVE_SKILL_DEFF_BUFF_TIME + k);
            
            GET_INT_DATA( t.wDeffenseEff[k]  , row , E_CONFIG_PASSIVE_SKILL_DEFF_EFF + k);
            GET_INT_DATA( t.wDeffenseEffHit[k]  , row , E_CONFIG_PASSIVE_SKILL_DEFF_EFF_HIT + k);
        }
        
        GET_STRING_DATA(t.strDes, row, E_CONFIG_PASSIVE_SKILL_DES)
        GET_INT_DATA(t.wIcon, row, E_CONFIG_PASSIVE_SKILL_ICON);
        GET_INT_DATA(t.wMaxLv, row, E_CONFIG_PASSIVE_SKILL_LV_MAX);
        GET_INT_DATA(t.byIsShow, row, E_CONFIG_PASSIVE_SKILL_ISSHOW);
        
        m_mapConfig.insert( std::make_pair( t.dwIndex, t ) );
    }
    
    return true;
}

bool UltimateSkillConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_ULIMATE_SKILL_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_ULIMATE_SKILL_INDEX );
        GET_INT_DATA( t.byType  , row , E_CONFIG_ULIMATE_SKILL_TYPE );
        GET_STRING_DATA(t.strName, row, E_CONFIG_ULIMATE_SKILL_NAME)
        GET_INT_DATA( t.wStripeCondition  , row , E_CONFIG_ULIMATE_SKILL_STRIPE_CONDITION );
//        GET_INT_DATA( t.bySkillCoolCnt  , row , E_CONFIG_ULIMATE_SKILL_COOL_CNT );
//        GET_INT_DATA( t.bySkillCoolChg  , row , E_CONFIG_ULIMATE_SKILL_COOL_CHG );

        GET_INT_DATA( t.byEffectObj  , row , E_CONFIG_ULIMATE_SKILL_EFF_OBJ );

        GET_INT_DATA( t.byEffectNature1  , row , E_CONFIG_ULIMATE_SKILL_EFF_NATURE_1 );
        GET_INT_DATA( t.byEffectNature2  , row , E_CONFIG_ULIMATE_SKILL_EFF_NATURE_2 );
        GET_INT_DATA( t.byAttackScope  , row , E_CONFIG_ULIMATE_SKILL_ATT_SCOPE );
        GET_INT_DATA( t.byHurtType  , row , E_CONFIG_ULIMATE_SKILL_HURT_TYPE );

        GET_INT_DATA( t.dwSkillAbi  , row , E_CONFIG_ULIMATE_SKILL_ABI );
        GET_INT_DATA( t.dwSkillAbiChg  , row , E_CONFIG_ULIMATE_SKILL_ABI_CHG );
        GET_INT_DATA( t.bySkillLvMax  , row , E_CONFIG_ULIMATE_SKILL_LV_MAX );

        GET_INT_DATA( t.dwSkillPara1  , row , E_CONFIG_ULIMATE_SKILL_PARA_1 );
        GET_INT_DATA( t.dwSkillPara2  , row , E_CONFIG_ULIMATE_SKILL_PARA_2 );
        GET_INT_DATA( t.dwSkillPara3  , row , E_CONFIG_ULIMATE_SKILL_PARA_3 );

        GET_INT_DATA( t.wAttackBuffHit  , row , E_CONFIG_ULIMATE_SKILL_ATT_BUFF_HIT);
        GET_INT_DATA( t.byAttackBuffScope  , row , E_CONFIG_ULIMATE_SKILL_ATT_BUFF_SCOPE);
        GET_INT_DATA( t.wDeffenseBuffHit  , row , E_CONFIG_ULIMATE_SKILL_DEFF_BUFF_HIT);
        for (int k = 0; k < 3; k++) {
            GET_INT_DATA( t.wAttackBuff[k]  , row , E_CONFIG_ULIMATE_SKILL_ATT_BUFF + k);
            
            GET_INT_DATA( t.wAttackBuffTime[k]  , row , E_CONFIG_ULIMATE_SKILL_ATT_BUFF_TIME + k);
            
            GET_INT_DATA( t.wAttackEff[k]  , row , E_CONFIG_ULIMATE_SKILL_ATT_EFF + k);
            GET_INT_DATA( t.wAttackEffHit[k]  , row , E_CONFIG_ULIMATE_SKILL_ATT_EFF_HIT + k);
            
            
            GET_INT_DATA( t.wDeffenseBuff[k]  , row , E_CONFIG_ULIMATE_SKILL_DEFF_BUFF + k);
            
            GET_INT_DATA( t.wDeffenseBuffTime[k]  , row , E_CONFIG_ULIMATE_SKILL_DEFF_BUFF_TIME + k);
            
            GET_INT_DATA( t.wDeffenseEff[k]  , row , E_CONFIG_ULIMATE_SKILL_DEFF_EFF + k);
            GET_INT_DATA( t.wDeffenseEffHit[k]  , row , E_CONFIG_ULIMATE_SKILL_DEFF_EFF_HIT + k);
        }
        GET_INT_DATA( t.wComboid  , row , E_CONFIG_ULIMATE_SKILL_COMBOID );
        GET_INT_DATA( t.wShowEffectId  , row , E_CONFIG_ULIMATE_SKILL_EFF_ID );

        GET_STRING_DATA(t.strDes, row, E_CONFIG_ULIMATE_SKILL_DES);
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}



bool SkillEffectConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_SKILL_EFFECT_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_SKILL_EFFECT_INDEX );
        GET_STRING_DATA( t.strName  , row , E_CONFIG_SKILL_EFFECT_NAME );
        GET_INT_DATA( t.byType  , row , E_CONFIG_SKILL_EFFECT_TYPE );

        for (int k = 0; k < 3; k++) {
            GET_INT_DATA( t.szSkillPara[k]  , row , E_CONFIG_SKILL_EFFECT_PARA + k );
        }
        
        GET_STRING_DATA( t.strDes  , row , E_CONFIG_SKILL_EFFECT_DES );
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}


bool ComboIdConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_COMBOID_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wComboId  , row , E_CONFIG_COMBOID_INDEX );
        GET_INT_DATA( t.wComboOffId  , row , E_CONFIG_COMBOID_OFF_TYPE );
        for ( int k = 0; k < 15; k++ )
        {
            GET_INT_DATA( t.dwComboTime[k] , row , E_CONFIG_COMBOID_CBTIME + k );
            GET_INT_DATA( t.dwComboPer[k] , row , E_CONFIG_COMBOID_CBPER + k );
        }
        
        m_mapConfig.insert( std::make_pair( t.wComboId, t ) );
    }
    
    return true;
}


bool SkillBuffConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_SKILL_BUFF_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_SKILL_BUFF_INDEX );
        GET_STRING_DATA( t.strName  , row , E_CONFIG_SKILL_BUFF_NAME );
        GET_INT_DATA( t.wBuffEff  , row , E_CONFIG_SKILL_BUFF_EFF );
        GET_INT_DATA( t.wType  , row , E_CONFIG_SKILL_BUFF_TYPE );
        GET_INT_DATA( t.wHurtType  , row , E_CONFIG_SKILL_BUFF_HURT_TYPE );
        GET_INT_DATA( t.byStartTime  , row , E_CONFIG_SKILL_BUFF_START_TIME );
        
        for (int k = 0; k < 3; k++) {
            GET_INT_DATA( t.buffPara[k]  , row , E_CONFIG_SKILL_BUFF_PARA + k );
        }
        GET_INT_DATA( t.wIcon  , row , E_CONFIG_SKILL_BUFF_ICON );
        GET_STRING_DATA( t.strDes  , row , E_CONFIG_SKILL_BUFF_DES );
        GET_STRING_DATA( t.strFlyText  , row , E_CONFIG_SKILL_BUFF_FLYTEXT );
        
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}


bool TriggerConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_TRIGGER_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_TRIGGER_INDEX );
        GET_STRING_DATA( t.strName  , row , E_CONFIG_TRIGGER_NAME );
        
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}

bool ResourcePicConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_CONFIG_RESOURCE_PIC t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );

        GET_INT_DATA( t.dwPicId, row, E_CONFIG_PIC_ID );
        GET_STRING_DATA( t.strPicName, row, E_CONFIG_PIC_NAME );
        m_mapConfig.insert( std::make_pair( t.dwPicId, t ) );
    }
    
    return true;
}


bool ResourceStringClientConfig::Load(const char * filePath)
{
    if ( !ConfigBase::Load(filePath) ) {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    
    for (int i = 0; i < nRow; i++) {
        STC_CONFIG_RESOURCE_STRING_CLIENT t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.dwId, row, E_CONFIG_RESOURCE_STRING_CLIENT_ID );
        GET_STRING_DATA( t.strText, row, E_CONFIG_RESOURCE_STRING_CLIENT_TEXT );
        m_mapConfig.insert( std::make_pair( t.dwId, t ) );
    }
    return true;
}


bool EffectGroupConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_EFFECT_GROUP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_EFFECT_GROUP_INDEX );
        GET_INT_DATA( t.byType  , row , E_CONFIG_EFFECT_GROUP_TYPE );
        GET_INT_DATA( t.byAltEffType  , row , E_CONFIG_EFFECT_GROUP_IS_FULL_SCREEN );
        for ( int k = 0; k < 5; k++ )
        {
            std::string str;
            GET_STRING_DATA(str, row, E_CONFIG_EFFECT_GROUP_PARTS + k);
            t.effParts.push_back(str);
        }
        GET_STRING_DATA(t.strArmEff, row, E_CONFIG_EFFECT_GROUP_ARM_EFF);
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}

bool InterPlayConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_INTER_PLAY_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_INTER_PLAY_INDEX );
        for (int k = 0; k < 6; k++) {
            GET_INT_DATA( t.arrNature[k]  , row , E_CONFIG_INTER_PLAY_NATURE + k );
        }

        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}

bool MapConfig::Load(const char* filePath) {
    if ( !ConfigBase::Load( filePath )) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for ( int i = 0; i < nRow; i++ ) {
        STC_MAP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wMapId, row, E_MAP_CONFIG_ID );
        GET_STRING_DATA( t.strName, row, E_MAP_CONFIG_NAME );
        GET_INT_DATA( t.wNeedPassId, row, E_MAP_CONFIG_NEED_PASS_ID );
        GET_INT_DATA( t.byAreaId, row, E_MAP_CONFIG_AREA_ID );
        GET_INT_DATA( t.posX, row, E_MAP_CONFIG_POS_X );
        GET_INT_DATA( t.posY, row, E_MAP_CONFIG_POS_Y );
        
        m_mapConfig.insert( std::make_pair( t.wMapId, t ));
    }
    return true;
}


bool EvolveConfig::Load(const char* filePath) {
    if ( !ConfigBase::Load( filePath ) ) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_EVOLVE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex, row, E_EVOLVE_CONFIG_INDEX );
        GET_INT_DATA( t.wNextId, row, E_EVOLVE_CONFIG_NEXT_ID );
        GET_INT_DATA( t.byLv, row, E_EVOLVE_CONFIG_LV );
        GET_INT_DATA( t.wPetLv, row, E_EVOLVE_CONFIG_PET_LV );
        GET_INT_DATA( t.dwAddHP, row, E_EVOLVE_CONFIG_ADD_HP );
        GET_INT_DATA( t.dwAddCATK, row, E_EVOLVE_CONFIG_ADD_CATK );
        GET_INT_DATA( t.dwAddCDEF, row, E_EVOLVE_CONFIG_ADD_CDEF );
        GET_INT_DATA( t.dwAddREV, row, E_EVOLVE_CONFIG_ADD_REV );
        GET_INT_DATA( t.dwAddSATK, row, E_EVOLVE_CONFIG_ADD_SATK );
        GET_INT_DATA( t.dwAddSDEF, row, E_EVOLVE_CONFIG_ADD_SDEF );
        GET_INT_DATA( t.dwAddCRIT, row, E_EVOLVE_CONFIG_ADD_CRIT );
        GET_INT_DATA( t.dwAddSPEED, row, E_EVOLVE_CONFIG_ADD_SPEED );
        for (int k = 0; k < 5; k++) {
            GET_INT_DATA( t.wEvoItemId[k], row, E_EVOLVE_CONFIG_EVO_ITEM_ID + k );
            GET_INT_DATA( t.byEvoItemCnt[k], row, E_EVOLVE_CONFIG_EVO_ITEM_CNT + k);
        }
        GET_INT_DATA( t.wBasePetId, row, E_EVOLVE_CONFIG_BASE_PET_ID );
        GET_INT_DATA( t.wNextPetId, row, E_EVOLVE_CONFIG_NEXT_PET_ID );
        GET_INT_DATA( t.dwNeedMoney, row, E_EVOLVE_CONFIG_NEED_MONEY );
        GET_INT_DATA( t.dwAddSkillId1, row, E_EVOLVE_CONFIG_ADD_SKILL_1 );
//        GET_INT_DATA( t.dwAddSkillId2, row, E_EVOLVE_CONFIG_ADD_SKILL_2 );
        GET_INT_DATA( t.byIcon, row, E_EVOLVE_CONFIG_ICON );
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    return true;
}

bool EvolveInfoConfig::Load(const char* filePath) {
    if ( !ConfigBase::Load( filePath ) ) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_EVOLVE_INFO_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA(t.wIndex, row, E_EVOLVE_INFO_CONFIG_INDEX);
        
        for (int k = 0; k < 12; k++) {
            GET_INT_DATA(t.arrStageType[k], row, E_EVOLVE_INFO_CONFIG_TYPE + k*2);
            GET_INT_DATA(t.arrStageId[k], row, E_EVOLVE_INFO_CONFIG_STAGEID + k*2);
            GET_INT_DATA(t.arrDropProb[k], row, E_EVOLVE_INFO_CONFIG_DROP_PROB + k);
        }
        
        GET_STRING_DATA(t.strDes, row, E_EVOLVE_INFO_CONFIG_DES);
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    return true;
}

bool ItemConfig::Load(const char* filePath) {
    if ( !ConfigBase::Load( filePath ) ) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_ITEM_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex, row, E_ITEM_CONFIG_INDEX );         //物品Objid}
        GET_STRING_DATA(t.strName, row, E_ITEM_CONFIG_NAME);        //物品名字}
        GET_INT_DATA(t.byType, row, E_ITEM_CONFIG_TYPE);            //物品类型}
        GET_STRING_DATA(t.strDesc, row, E_ITEM_CONFIG_DES);         //物品描述}
        GET_INT_DATA(t.byQuality, row, E_ITEM_CONFIG_QUALITY);      //物品品质}
        GET_INT_DATA(t.byIsCanSale, row, E_ITEM_CONFIG_IS_CAN_SALE);//物品是否主动使用}
        GET_INT_DATA(t.wUseLv, row, E_ITEM_CONFIG_USE_LV);          //物品使用等级}
        GET_INT_DATA(t.wGroupCnt, row, E_ITEM_CONFIG_GROUP_CNT);    //堆叠上限}
        GET_INT_DATA(t.wMaxHasCnt, row, E_ITEM_CONFIG_MAX_HAS_CNT); //最大拥有数}
        GET_INT_DATA(t.dwPrice, row, E_ITEM_CONFIG_PRICE);          //出售价格}
        
        for (int k = 0; k < 5; k++)
        {
            GET_INT_DATA( t.wParas[k], row, E_ITEM_CONFIG_PARA + k );//参数1-5}
        }
        GET_INT_DATA( t.dwIconId, row, E_ITEM_CONFIG_ICON_ID );//iconID
        
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    return true;
}

bool GemConfig::Load(const char *filePath){
    if ( !ConfigBase::Load( filePath ) ) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_GEM_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA(t.dwIndex, row, E_GEM_CONFIG_INDEX);       //宝石物品编号}
        GET_STRING_DATA(t.strName, row, E_GEM_CONFIG_NAME);     //宝石名字}
        GET_INT_DATA(t.byType, row, E_GEM_CONFIG_TYPE);         //宝石使用的技能类型，天赋技能，被动技能}
        GET_INT_DATA(t.wParam, row, E_GEM_CONFIG_PARAM);        //宝石使用的技能ID}
        GET_INT_DATA(t.byQuality, row, E_GEM_CONFIG_QUALITY);   //宝石的品质}
        GET_INT_DATA( t.wIcon, row, E_GEM_CONFIG_ICON );        //宝石icon}
        GET_STRING_DATA(t.strDesc, row, E_GEM_CONFIG_DESC);     //宝石说明}
        
        m_mapConfig.insert( std::make_pair( t.dwIndex, t ) );
    }
    return true;
}

bool RankRewardConfig::Load(const char* filePath){
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_RANKREWARD_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA(t.wIndex, row, E_RANKREWARD_CONFIG_INDEX);
        GET_STRING_DATA(t.strGroupName, row, E_RANKREWARD_CONFIG_GROUP_NAME);
        GET_INT_DATA(t.dwGetMoney, row, E_RANKREWARD_CONFIG_MONEY);
        GET_INT_DATA(t.dwGetReputation, row, E_RANKREWARD_CONFIG_REPUTATION);
        GET_INT_DATA(t.wIcon, row, E_RANKREWARD_CONFIG_ICON);
        GET_INT_DATA(t.wBadge, row, E_RANKREWARD_CONFIG_BADGE);
        GET_INT_DATA(t.dwcolor, row, E_RANKREWARD_CONFIG_COLOR);
        
        for (int k = 0; k < 10; k++)
        {
            GET_INT_DATA(t.dwShowItems[k], row, E_RANKREWARD_CONFIG_SHOW_ITEMS + k);
        }
        
        m_mapConfig.insert( std::make_pair( t.wIndex, t));
    }
    
    return true;
}

bool UserLvConfig::Load(const char* filePath){
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_USERLV_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA(t.wIndex, row, E_USERLV_CONFIG_INDEX);
        GET_INT_DATA(t.dwExp, row, E_USERLV_CONFIG_EXP);
        GET_INT_DATA(t.wEnergy, row, E_USERLV_CONFIG_ENERGY);
        m_mapConfig.insert( std::make_pair( t.wIndex, t));
    }
    
    return true;
}

#if 0
//装备--不用}
bool EquipConfig::Load(const char* filePath)
{
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_EQUIP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_EQUIP_CONFIG_INDEX);
        
        GET_STRING_DATA(t.strName, row, E_EQUIP_CONFIG_NAME);
        GET_INT_DATA(t.dwGroupId, row, E_EQUIP_CONFIG_GROUP_ID);
        //GET_INT_DATA(t.wUseLV, row, E_EQUIP_CONFIG_USE_LV);
        //GET_INT_DATA(t.wStrengthenLv, row, E_EQUIP_CONFIG_STRENGTHEN_LV);
        GET_INT_DATA(t.byPos, row, E_EQUIP_CONFIG_POS);
        
        GET_INT_DATA(t.byEffectType1, row, E_EQUIP_CONFIG_EFFECT_TYPE_1);
        GET_INT_DATA(t.wEffectValue1, row, E_EQUIP_CONFIG_BASE_VAL_1);
        GET_INT_DATA(t.wGrowthRate1, row, E_EQUIP_CONFIG_GROWTH_RATE_1);
        
        GET_INT_DATA(t.byEffectType2, row, E_EQUIP_CONFIG_EFFECT_TYPE_2);
        GET_INT_DATA(t.wEffectValue2, row, E_EQUIP_CONFIG_BASE_VAL_2);
        GET_INT_DATA(t.wGrowthRate2, row, E_EQUIP_CONFIG_GROWTH_RATE_2);
        
        GET_INT_DATA(t.dwCostBaseValue, row, E_EQUIP_CONFIG_COST_BASE_VAL);
        GET_INT_DATA(t.dwPrice, row, E_EQUIP_CONFIG_PRICE);
        GET_STRING_DATA(t.strDesc, row, E_EQUIP_CONFIG_DESC);
        GET_INT_DATA(t.dwIcon, row, E_EQUIP_CONFIG_ICON);
        GET_INT_DATA(t.byStar, row, E_EQUIP_CONFIG_STAR);
        GET_INT_DATA(t.byQuality, row, E_EQUIP_CONFIG_QUALITY);
        
        GET_INT_DATA(t.dwEvoID, row, E_EQUIP_CONFIG_EVO_ID);
        GET_INT_DATA(t.wEvoLV, row, E_EQUIP_CONFIG_EVO_LV);
        GET_INT_DATA(t.wEvoCoef, row, E_EQUIP_CONFIG_EVO_COEF);
        GET_INT_DATA(t.dwEvoMaterial1, row, E_EQUIP_CONFIG_EVO_MATERIAL);
        GET_INT_DATA(t.dwEvoMaterialAttri1, row, E_EQUIP_CONFIG_EVO_MATERIAL_ATTRI);
        GET_INT_DATA(t.dwEvoMaterial2, row, E_EQUIP_CONFIG_EVO_MATERIAL2);
        GET_INT_DATA(t.dwEvoMaterialAttri2, row, E_EQUIP_CONFIG_EVO_MATERIAL_ATTRI2);
        
        GET_INT_DATA(t.dwEvoCostMoney, row, E_EQUIP_CONFIG_EVO_COST_MONEY);
        
        m_mapConfig.insert(std::make_pair( t.dwIndex, t));
    }
    return true;
}
#endif

//装备}
bool EquipNewConfig::Load(const char* filePath)
{
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_EQUIP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_EQUIP_CONFIG_INDEX);
        GET_INT_DATA(t.dwEvoItemID, row,E_EQUIP_CONFIG_EVOITEM_ID);
        GET_STRING_DATA(t.strName, row, E_EQUIP_CONFIG_NAME);
        GET_INT_DATA(t.byPos, row, E_EQUIP_CONFIG_POS);
        
        GET_INT_DATA(t.byEffectType1, row, E_EQUIP_CONFIG_EFFECT_TYPE_1);
        GET_INT_DATA(t.wEffectValue1, row, E_EQUIP_CONFIG_BASE_VAL_1);
        GET_INT_DATA(t.wGrowthRate1, row, E_EQUIP_CONFIG_GROWTH_RATE_1);
        
        GET_INT_DATA(t.byEffectType2, row, E_EQUIP_CONFIG_EFFECT_TYPE_2);
        GET_INT_DATA(t.wEffectValue2, row, E_EQUIP_CONFIG_BASE_VAL_2);
        GET_INT_DATA(t.wGrowthRate2, row, E_EQUIP_CONFIG_GROWTH_RATE_2);
        
        GET_INT_DATA(t.byEvoType1, row, E_EQUIP_CONFIG_EVO_TYPE_1);
        GET_INT_DATA(t.byEvoDataType1, row, E_EQUIP_CONFIG_EVO_DATA_TYPE_1);
        GET_INT_DATA(t.dwEvoData1, row, E_EQUIP_CONFIG_EVO_DATA_1);
        
        GET_INT_DATA(t.byEvoType2, row, E_EQUIP_CONFIG_EVO_TYPE_2);
        GET_INT_DATA(t.byEvoDataType2, row, E_EQUIP_CONFIG_EVO_DATA_TYPE_2);
        GET_INT_DATA(t.dwEvoData2, row, E_EQUIP_CONFIG_EVO_DATA_2);
        
        GET_INT_DATA(t.dwCostBaseValue, row, E_EQUIP_CONFIG_COST_BASE_VAL);
        GET_INT_DATA(t.dwPrice, row, E_EQUIP_CONFIG_PRICE);
        GET_STRING_DATA(t.strDesc, row, E_EQUIP_CONFIG_DESC);
        GET_INT_DATA(t.dwIcon, row, E_EQUIP_CONFIG_ICON);
        GET_INT_DATA(t.byStar, row, E_EQUIP_CONFIG_STAR);
        GET_INT_DATA(t.byQuality, row, E_EQUIP_CONFIG_QUALITY);
        
        
        m_mapConfig.insert(std::make_pair( t.dwIndex, t));
    }
    return true;
}

//进阶}
bool EquipEvoConfig::Load(const char* filePath)
{
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_EQUIP_EVO_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwEvoItemId, row,E_EQUIP_EVO_CONFIG_EVOITEMID);
        GET_INT_DATA(t.wEvoLv, row,E_EQUIP_EVO_CONFIG_EVOLV);
        GET_INT_DATA(t.dwEvoMaterial1, row,E_EQUIP_EVO_CONFIG_EVOMATERIAL1);
        GET_INT_DATA(t.dwEvoMaterial1Num, row,E_EQUIP_EVO_CONFIG_EVOMATERIAL1NUM);
        GET_INT_DATA(t.dwEvoMaterial2, row,E_EQUIP_EVO_CONFIG_EVOMATERIAL2);
        GET_INT_DATA(t.dwEvoMaterial2Num, row,E_EQUIP_EVO_CONFIG_EVOMATERIAL2NUM);
        GET_INT_DATA(t.dwEvoCostMoney, row,E_EQUIP_EVO_CONFIG_EVOCOSTMONEY);
        GET_INT_DATA(t.dwEvoNeedStrengthenLv, row,E_EQUIP_EVO_CONFIG_EVONEEDSTRENGTHENLV);
        
        m_mapConfig.insert(std::make_pair( t.dwEvoItemId * 100 + t.wEvoLv, t));
    }
    return true;
}

//符文}
bool RuneConfig::Load( const char* filePath )
{
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_RUNE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        GET_INT_DATA(t.dwIndex, row, E_RUNE_CONFIG_INDEX);               //符文编号}
        GET_STRING_DATA(t.strName, row, E_RUNE_CONFIG_NAME);            //符文名字}
        GET_INT_DATA(t.byEffectType1, row, E_RUNE_CONFIG_EFFECT_TYPE_1);//作用属性1}
        GET_INT_DATA(t.wEffectValue1, row, E_RUNE_CONFIG_BASE_VAL_1);       //作用数值1}
        GET_INT_DATA(t.byEffectType2, row, E_RUNE_CONFIG_EFFECT_TYPE_2);//作用属性2}
        GET_INT_DATA(t.wEffectValue2, row, E_RUNE_CONFIG_BASE_VAL_2);       //作用数值2}
        GET_INT_DATA(t.dwCostMoney, row, E_RUNE_CONFIG_COST_MONEY);     //消耗金钱}
        GET_INT_DATA(t.dwCostSoul, row, E_RUNE_CONFIG_COST_SOUL);       //消耗魂}
        GET_INT_DATA(t.dwPrice, row, E_RUNE_CONFIG_PRICE);              //出售价格}
        GET_INT_DATA(t.wCompoundRate, row, E_RUNE_CONFIG_COMPOUND_RATE);//合成成功率}
        GET_INT_DATA(t.dwCostDollor, row, E_RUNE_CONFIG_COST_DOLLAR);   //合成消耗钻石}
        GET_STRING_DATA(t.strDesc, row, E_RUNE_CONFIG_DESC);            //描述说明}
        GET_INT_DATA(t.dwIcon, row, E_RUNE_CONFIG_ICON);                 //ICON
        
        m_mapConfig.insert(std::make_pair( t.dwIndex, t));
    }
    
    return true;
}

//强化装备金钱消耗}
bool EquipStrengthenConfig::Load(const char * filePath)
{
    if ( !ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_EQUIP_STRENGTHEN_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        GET_INT_DATA(t.byLevel, row, E_EQUIP_STRENGTHEN_LEVEL);
        GET_INT_DATA(t.dwCostMoney, row, E_EQUIP_STRENGTHEN_COST);
        
        m_mapConfig.insert(std::make_pair( t.byLevel, t));
    }

    
    return true;
}

bool EquipCompoundConfig::Load(const char * filePath)
{
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_EQUIP_COMPOUND_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        GET_INT_DATA(t.wIndex, row, E_EQUIP_COMPOUND_INDEX);
        GET_INT_DATA(t.byShowTabType, row, E_EQUIP_COMPOUND_SHOWTABTYPE);
        GET_INT_DATA(t.dwMakeObjID, row, E_EQUIP_COMPOUND_MAKEOBJID);
        GET_INT_DATA(t.wMakeCount, row, E_EQUIP_COMPOUND_MAKECOUNT);
        for (int k = 0; k < 5; k++)
        {
            GET_INT_DATA(t.dwCostObjID[k], row, E_EQUIP_COMPOUND_COSTOBJID + 100 * k);
            GET_INT_DATA(t.wCostCount[k], row, E_EQUIP_COMPOUND_COSTCOUNT + 100 * k);
        }
        GET_INT_DATA(t.dwCostSoul, row, E_EQUIP_COMPOUND_COSTSOUL);
        GET_INT_DATA(t.dwCostMonye, row, E_EQUIP_COMPOUND_COSTMONEY);
        GET_STRING_DATA(t.strDesc, row, E_EQUIP_COMPOUND_DESC);
        
        m_mapConfig.insert(std::make_pair( t.wIndex, t));
    }
    return true;
}

bool TalentConfig::Load(const char* filePath){
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_TALENT_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA(t.wIndex, row, E_TALENT_CONFIG_INDEX);
        GET_STRING_DATA(t.strName, row, E_TALENT_CONFIG_NAME);
        GET_INT_DATA(t.wMaxLv, row, E_TALENT_CONFIG_MAX_LV);
        GET_INT_DATA(t.byTalentType, row, E_TALENT_CONFIG_TANLENT_TYPE);
        GET_INT_DATA(t.byEffType, row, E_TALENT_CONFIG_EFF_TYPE);
        GET_INT_DATA(t.dwValue, row, E_TALENT_CONFIG_VALUE);
        GET_INT_DATA(t.dwChgValue, row, E_TALENT_CONFIG_CHG_VALUE);
        GET_STRING_DATA(t.strDes, row, E_TALENT_CONFIG_DES);
        GET_INT_DATA(t.dwIcon, row, E_TALENT_CONFIG_ICON);
        
        m_mapConfig.insert( std::make_pair( t.wIndex, t));
    }
    
    return true;
}

bool PassiveSkillExpConfig::Load(const char* filePath){
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_PASSIVE_SKILL_EXP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA(t.wIndex, row, E_CONFIG_PASSIVE_SKILL_LV);
        GET_INT_DATA(t.dwTValue, row, E_CONFIG_PASSIVE_SKILL_T_EXP);
        GET_INT_DATA(t.dwPValue, row, E_CONFIG_PASSIVE_SKILL_P_EXP);
        m_mapConfig.insert( std::make_pair( t.wIndex, t));
    }
    
    return true;
}

bool UltimateSkillExpConfig::Load(const char* filePath){
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_ULTIMATE_SKILL_EXP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA(t.wIndex, row, E_CONFIG_ULTIMATE_SKILL_LV);
        GET_INT_DATA(t.dwValue, row, E_CONFIG_ULTIMATE_SKILL_EXP);
        m_mapConfig.insert( std::make_pair( t.wIndex, t));
    }
    
    return true;
}

bool AnimationEffectConfig::Load(const char* filePath) {
    if ( !ConfigBase::Load(filePath) ) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_ANIMATION_EFFECT_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA(t.wIndex, row, E_CONFIG_ANI_EFFECT_ID);
        GET_STRING_DATA(t.strPath, row, E_CONFIG_ANI_EFFECT_PATH);
        GET_STRING_DATA(t.strName, row, E_CONFIG_ANI_EFFECT_NAME);
        GET_INT_DATA(t.wCnt, row, E_CONFIG_ANI_EFFECT_CNT);
        
        m_mapConfig.insert( std::make_pair(t.wIndex, t) );
    }
    return true;
}

bool SpecialMapConfig::Load(const char *filePath) {
    if ( !ConfigBase::Load(filePath) ) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_SPECIAL_MAP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wMapId, row, E_CONFIG_SPEMAP_ID);
        GET_STRING_DATA(t.strMapName, row, E_CONFIG_SPEMAP_NAME);
        GET_INT_DATA(t.wPicId, row, E_CONFIG_SPEMAP_PIC_ID);

        GET_INT_DATA(t.wLimitLv, row, E_CONFIG_SPEMAP_LIMIT_LV);
        GET_STRING_DATA(t.wLimitDes, row, E_CONFIG_SPEMAP_LIMIT_DES);
        
        m_mapConfig.insert( std::make_pair(t.wMapId, t ));
    }
    return true;
}

bool EventReward7Config::Load(const char *filePath){
    if ( !ConfigBase::Load(filePath) )
    {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_EVENT_REWARD_7_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wIndex, row, E_CONFIG_REWARD_7_INDEX);
        for (int k = 0; k < 4; k++)
        {
            GET_INT_DATA(t.dwItemID[k], row, E_CONFIG_REWARD_7_ITEMID1 + 100 * k);
            GET_INT_DATA(t.dwItemCount[k], row, E_CONFIG_REWARD_7_ITEMCOUNT1 + 100 * k);
        }
        m_mapConfig.insert( std::make_pair(t.wIndex, t));
    }
    return true;
}

bool EventReward30Config::Load(const char *filePath){
    if ( !ConfigBase::Load(filePath) )
    {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_EVENT_REWARD_30_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wIndex, row, E_CONFIG_REWARD_30_INDEX);
        for (int k = 0; k < 4; k++)
        {
            GET_INT_DATA(t.dwItemID[k], row, E_CONFIG_REWARD_30_ITEMID1 + 100 * k);
            GET_INT_DATA(t.dwItemCount[k], row, E_CONFIG_REWARD_30_ITEMCOUNT1 + 100 * k);
        }
        m_mapConfig.insert( std::make_pair(t.wIndex, t));
    }
    return true;
}

bool GuideConfig::Load(const char *filePath) {
    if ( ! ConfigBase::Load(filePath) ) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    
    for (int i = 0; i < nRow; i++) {
        STC_GUIDE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wId, row, E_CONFIG_GUIDE_ID);
        GET_INT_DATA(t.wGroupId, row, E_CONFIG_GUIDE_GROUP_ID);
        GET_INT_DATA(t.wDialogId, row, E_CONFIG_GUIDE_DIALOG_ID);
        GET_INT_DATA(t.wButtonId, row, E_CONFIG_GUIDE_BUTTON_ID);
        GET_STRING_DATA(t.strName, row, E_CONFIG_GUIDE_NAME);
        GET_STRING_DATA(t.strText, row, E_CONFIG_GUIDE_TEXT);
        GET_INT_DATA(t.wNameColor, row, E_CONFIG_GUIDE_NAME_COLOR);
        GET_INT_DATA(t.wTextColor, row, E_CONFIG_GUIDE_TEXT_COLOR);
        GET_INT_DATA(t.nPosY, row, E_CONFIG_GUIDE_POSY);
        GET_INT_DATA(t.wLadyPath, row, E_CONFIG_GUIDE_LADY_PATH);
        GET_INT_DATA(t.byLadyOffset, row, E_CONFIG_GUIDE_LADY_OFFSET);
        GET_INT_DATA(t.wOpenLv, row, E_CONFIG_GUIDE_OPEN_LV);
        
        m_mapConfig.insert( std::make_pair(t.wId, t));
    }
    return true;
}

bool GuideButtonConfig::Load(const char *filePath) {
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_GUIDE_BUTTON_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wId, row, E_CONFIG_GUIDE_BUTTON_KEY_ID);
        GET_INT_DATA(t.byLock, row, E_CONFIG_GUIDE_BUTTON_LOCK);
        GET_INT_DATA(t.byDirection, row, E_CONFIG_GUIDE_BUTTON_DIRECTION);
        GET_INT_DATA(t.byDark, row, E_CONFIG_GUIDE_BUTTON_DARK);
        
        m_mapConfig.insert( std::make_pair(t.wId, t));
    }
    return true;
}

bool AchieveRewardConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load(filePath) )
    {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_ACHIEVE_REWARD_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_CONFIG_ACHIEVE_INDEX);
        GET_INT_DATA(t.byType, row, E_CONFIG_ACHIEVE_TYPE);
        for (int k = 0; k < 2; k++)
        {
            GET_INT_DATA(t.dwParam[k], row, E_CONFIG_ACHIEVE_PARAM_1+ k);
            GET_INT_DATA(t.dwRewardID[k], row, E_CONFIG_ACHIEVE_REWARD_ID_1 + k * 100);
            GET_INT_DATA(t.dwRewardCnt[k], row, E_CONFIG_ACHIEVE_REWARD_CNT_1 + k * 100);
        }
        GET_STRING_DATA(t.strTitle, row, E_CONFIG_ACHIEVE_TITLE);
        GET_STRING_DATA(t.strDesc, row, E_CONFIG_ACHIEVE_DESC);
        GET_STRING_DATA(t.strNextScene, row, E_CONFIG_ACHIEVE_NEXT_SCENE);
        m_mapConfig.insert(std::make_pair(t.dwIndex, t));
    }
    return true;
}

bool DailyQuestConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load(filePath) )
    {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_DAILY_QUEST_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_CONFIG_DAILY_QUEST_INDEX);
        GET_INT_DATA(t.byType, row, E_CONFIG_DAILY_QUEST_TYPE);
        for (int k = 0; k < 2; k++)
        {
            GET_INT_DATA(t.dwParam[k], row, E_CONFIG_DAILY_QUEST_PARAM_1 + k);
            GET_INT_DATA(t.dwRewardID[k], row, E_CONFIG_DAILY_QUEST_REWARD_ID_1 + k * 100);
            GET_INT_DATA(t.dwRewardCnt[k], row, E_CONFIG_DAILY_QUEST_REWARD_CNT_1 + k * 100);
        }
        GET_STRING_DATA(t.strTitle, row, E_CONFIG_DAILY_QUEST_TITLE);
        GET_STRING_DATA(t.strDesc, row, E_CONFIG_DAILY_QUEST_DESC);
        GET_INT_DATA(t.dwScore, row, E_CONFIG_DAILY_QUEST_SCORE);
        GET_STRING_DATA(t.strNextScene, row, E_CONFIG_DAILY_QUEST_NEXT_SCENE);
        
        m_mapConfig.insert(std::make_pair(t.dwIndex, t));
    }
    return true;
}

bool RandomNameConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load(filePath) ) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_RANDOM_NAME t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_CONFIG_RANDOM_NAME_ID);
        GET_STRING_DATA(t.strFistName, row, E_CONFIG_RANDOM_FIRST_NAME);
        GET_STRING_DATA(t.strSecondName, row, E_CONFIG_RANDOM_SECOND_NAME);
        GET_STRING_DATA(t.strThirdName, row, E_CONFIG_RANDOM_THIRD_NAME);
        
        m_mapConfig.insert(std::make_pair(t.dwIndex, t));
    }
    return true;
}

bool PetFuseConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load(filePath) )
    {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_PET_FUSE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wIndex, row, E_CONFIG_PET_FUSE_INDEX);
        GET_INT_DATA(t.dwNeedMoney, row, E_CONFIG_PET_FUSE_NEED_MONEY);
        GET_INT_DATA(t.wGetItemId, row, E_CONFIG_PET_FUSE_GET_FUSE);
        GET_INT_DATA(t.wGetCnt, row, E_CONFIG_PET_FUSE_GET_FUSE_CNT);
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool InviteConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load(filePath) )
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_INVITE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
       
        GET_INT_DATA(t.dwIndex, row, E_CONFIG_INVITE_INDEX);
        for (int k = 0; k < 5; k++)
        {
            GET_INT_DATA(t.dwRewardID[k], row, E_CONFIG_INVITE_REWARDID1 + k * 100);
            GET_INT_DATA(t.dwRewardCount[k], row, E_CONFIG_INVITE_REWARDCOUNT1 + k * 100);
        }
        GET_STRING_DATA(t.strDesc, row, E_CONFIG_INVITE_DESC);
        
        m_mapConfig.insert(std::make_pair(t.dwIndex, t));
    }
    
    return true;
}

bool InviteeConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load(filePath) )
    {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_INVITEE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_CONFIG_INVITEE_INDEX);
        GET_INT_DATA(t.byLevel, row, E_CONFIG_INVITEE_LEVEL);
        for (int k = 0; k < 5; k++)
        {
            GET_INT_DATA(t.dwRewardID[k], row, E_CONFIG_INVITEE_REWARDID1 + k * 100);
            GET_INT_DATA(t.dwRewardCount[k], row, E_CONFIG_INVITEE_REWARDCOUNT1 + k * 100);
        }
        GET_STRING_DATA(t.strDesc, row, E_CONFIG_INVITEE_DESC);
        
        m_mapConfig.insert(std::make_pair(t.dwIndex, t));
    }

    return true;
}

bool EpitasisConfig::Load(const char *filePath) {
    if (!ConfigBase::Load(filePath)) {
        return false;
    }
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++) {
        STC_EPITASIS_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_CONFIG_EPITASIS_ID);
        GET_STRING_DATA(t.strContent, row, E_CONFIG_EPITASIS_CONTENT);
        GET_STRING_DATA(t.strName, row, E_CONFIG_EPITASIS_NAME);
        GET_INT_DATA(t.wPicIndex, row, E_CONFIG_EPITASIS_PIC_ID);
        GET_INT_DATA(t.byPicPos, row, E_CONFIG_EPITASIS_PIC_POS);
        GET_INT_DATA(t.wMapId, row, E_CONFIG_EPITASIS_MAP_ID);
        GET_INT_DATA(t.byContentColor, row, E_CONFIG_EPITASIS_COLOR_CONTENT);
        GET_INT_DATA(t.byNameColor, row, E_CONFIG_EPITASIS_COLOR_NAME);
        GET_INT_DATA(t.wStageId, row, E_CONFIG_EPITASIS_STAGE);
//        GET_INT_DATA(t.nOffX, row, E_CONFIG_EPITASIS_OFF_X);
//        GET_INT_DATA(t.nOffY, row, E_CONFIG_EPITASIS_OFF_Y);
        GET_INT_DATA(t.wScale, row, E_CONFIG_EPITASIS_SCALE);
        GET_INT_DATA(t.byInsertBefore, row, E_CONFIG_EPITASIS_INSERT_BEFORE);
        
        m_mapConfig.insert(std::make_pair(t.dwIndex, t));
    }
    return true;
}

bool GrowPlanConfig::Load(const char *filePath) {
   
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_GROW_PLAN_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_CONFIG_GROW_PLAN_INDEX);
        GET_INT_DATA(t.byLevel, row, E_CONFIG_GROW_PLAN_LEVEL);
        GET_INT_DATA(t.dwRewardID, row, E_CONFIG_GROW_PLAN_REWARDID);
        GET_INT_DATA(t.dwCount, row, E_CONFIG_GROW_PLAN_COUNT);
        GET_STRING_DATA(t.strTitle, row, E_CONFIG_GROW_PLAN_TITLE);
        GET_STRING_DATA(t.strDesc, row, E_CONFIG_GROW_PLAN_DESC);
        
        m_mapConfig.insert(std::make_pair(t.dwIndex, t));
    }
    return true;
    
}

bool SystemDebLockingConfig::Load(const char *filePath) {
    
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_SYSTEM_DEB_LOCKING_CONFIHG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_CONFIG_SYSTEM_DEB_LOCKING_INDEX);
        GET_INT_DATA(t.byType, row, E_CONFIG_SYSTEM_DEB_LOCKING_TYPE);
        GET_INT_DATA(t.wPara, row, E_CONFIG_SYSTEM_DEB_LOCKING_PARA);
        GET_INT_DATA(t.dwGuideId, row, E_CONFIG_SYSTEM_DEB_LOCKING_GUIDEID);
        GET_STRING_DATA(t.strUnLock, row, E_CONFIG_SYSTEM_DEB_LOCKING_UNLOCK);
        GET_STRING_DATA(t.strDesc, row, E_CONFIG_SYSTEM_DEB_LOCKING_DES);
        GET_STRING_DATA(t.strDescShow, row, E_CONFIG_SYSTEM_DEB_LOCKING_DES_SHOW);
        for (int k = 0; k < 3; k++) {
            GET_INT_DATA(t.wIcon[k], row, E_CONFIG_SYSTEM_DEB_LOCKING_ICON + k*2);
            GET_STRING_DATA(t.strIconName[k], row, E_CONFIG_SYSTEM_DEB_LOCKING_ICON_NAME + k*2);
        }
        
        m_mapConfig.insert(std::make_pair(t.dwIndex, t));
    }
    return true;
    
}

bool StageConfig::Load(const char *filePath) {
    
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_STAGE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwMapId, row, E_CONFIG_STAGE_MAPID);
        GET_INT_DATA(t.dwStageId, row, E_CONFIG_STAGE_STAGEID );
        GET_STRING_DATA(t.strName, row, E_CONFIG_STAGE_NAME);
        GET_INT_DATA(t.wAttCnt, row, E_CONFIG_STAGE_ATT_CNT);
        GET_INT_DATA(t.wCostEnergy, row, E_CONFIG_STAGE_COST_ENERGY);
        GET_INT_DATA(t.wWaveCnt, row, E_CONFIG_STAGE_WAVE_CNT);
        
        GET_INT_DATA(t.dwFirstRewItemId1, row, E_CONFIG_STAGE_FIRST_REW_ITEM_ID_1);
        GET_INT_DATA(t.dwFirstRewItemCnt1, row, E_CONFIG_STAGE_FIRST_REW_ITEM_CNT_1);
        GET_INT_DATA(t.dwFirstRewItemId2, row, E_CONFIG_STAGE_FIRST_REW_ITEM_ID_2);
        GET_INT_DATA(t.dwFirstRewItemCnt2, row, E_CONFIG_STAGE_FIRST_REW_ITEM_CNT_2);
        
        GET_STRING_DATA(t.strDesc, row, E_CONFIG_STAGE_DES);
        GET_INT_DATA(t.dwStageIcon, row, E_CONFIG_STAGE_ICON);
        
        std::string str = "";
        GET_STRING_DATA(str, row, E_CONFIG_STAGE_NORMAL_BGM);
        ResourceStringConverter::StrSplit(str, "_", t.vectNormalBgm);
        GET_STRING_DATA(str, row, E_CONFIG_STAGE_BOSS_BGM);
        ResourceStringConverter::StrSplit(str, "_", t.vectBossBgm);
        
        GET_INT_DATA(t.byFlag, row, E_CONFIG_STAGE_FLAG);
        GET_INT_DATA(t.wShowMapId, row, E_CONFIG_STAGE_SHOW_MAPID);
        m_mapConfig.insert(std::make_pair(t.dwStageId, t));
    }
    return true;
    
}

bool StageHConfig::Load(const char *filePath) {
    
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_STAGE_H_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwMapId, row, E_CONFIG_STAGE_MAPID);
        GET_INT_DATA(t.dwStageId, row, E_CONFIG_STAGE_STAGEID );
        GET_STRING_DATA(t.strName, row, E_CONFIG_STAGE_NAME);
        GET_INT_DATA(t.wAttCnt, row, E_CONFIG_STAGE_ATT_CNT);
        GET_INT_DATA(t.wCostEnergy, row, E_CONFIG_STAGE_COST_ENERGY);
        GET_INT_DATA(t.wWaveCnt, row, E_CONFIG_STAGE_WAVE_CNT);
        
        GET_INT_DATA(t.dwFirstRewItemId1, row, E_CONFIG_STAGE_FIRST_REW_ITEM_ID_1);
        GET_INT_DATA(t.dwFirstRewItemCnt1, row, E_CONFIG_STAGE_FIRST_REW_ITEM_CNT_1);
        GET_INT_DATA(t.dwFirstRewItemId2, row, E_CONFIG_STAGE_FIRST_REW_ITEM_ID_2);
        GET_INT_DATA(t.dwFirstRewItemCnt2, row, E_CONFIG_STAGE_FIRST_REW_ITEM_CNT_2);
        
        GET_STRING_DATA(t.strDesc, row, E_CONFIG_STAGE_DES);
        GET_INT_DATA(t.dwStageIcon, row, E_CONFIG_STAGE_ICON);
        
        std::string str = "";
        GET_STRING_DATA(str, row, E_CONFIG_STAGE_NORMAL_BGM);
        ResourceStringConverter::StrSplit(str, "_", t.vectNormalBgm);
        GET_STRING_DATA(str, row, E_CONFIG_STAGE_BOSS_BGM);
        ResourceStringConverter::StrSplit(str, "_", t.vectBossBgm);
        
        GET_INT_DATA(t.byFlag, row, E_CONFIG_STAGE_FLAG);
        GET_INT_DATA(t.wShowMapId, row, E_CONFIG_STAGE_SHOW_MAPID);
        
        m_mapConfig.insert(std::make_pair(t.dwStageId, t));
    }
    
    CCLOG("stage_h size %lu", m_mapConfig.size());
    return true;
    
}

bool StageShowConfig::Load(const char *filePath) {
    
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_STAGE_SHOW_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.dwIndex, row, E_CONFIG_STAGE_SHOW_INDEX);
        
        for (int k = 0; k < 6; ++k) {   // 最多两个！！// [2014-09-14]修改最多6个}
            GET_INT_DATA(t.arrPetId[k], row, E_CONFIG_STAGE_SHOW_PETID + k);
            GET_INT_DATA(t.arrItemId[k], row, E_CONFIG_STAGE_SHOW_ITEMID + k);
        }

        m_mapConfig.insert(std::make_pair(t.dwIndex, t));
    }
    return true;
    
}

bool VipShowConfig::Load(const char *filePath)
{
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_VIP_SHOW_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wIndex, row, E_CONFIG_VIP_SHOW_INDEX);
        GET_INT_DATA(t.dwRechargeVal, row, E_CONFIG_VIP_SHOW_RECHARGE_VAL);
        GET_INT_DATA(t.bySweepOpen, row, E_CONFIG_VIP_SHOW_SWEEP_OPEN);
        GET_INT_DATA(t.wFreeSweepCnt, row, E_CONFIG_VIP_SHOW_SWEEP_CNT);
        GET_INT_DATA(t.bySweepCanClear, row, E_CONFIG_VIP_SHOW_SWEEP_CLEAR);
        GET_INT_DATA(t.wFriendMax, row, E_CONFIG_VIP_SHOW_FRIEND_MAX);
        GET_INT_DATA(t.wStageBuyMax, row, E_CONFIG_VIP_SHOW_STAGE_BUY_MAX);
        GET_INT_DATA(t.wHStageBuyMax, row, E_CONFIG_VIP_SHOW_H_STAGE_BUY_MAX);
        GET_INT_DATA(t.wActivityBuyMax, row, E_CONFIG_VIP_SHOW_ACTIVITY_BUY_MAX);
        GET_INT_DATA(t.wMoneyCatBuyMax, row, E_CONFIG_VIP_SHOW_MONEY_CAT_BUY_MAX);
        GET_INT_DATA(t.wTowerResetMax, row, E_CONFIG_VIP_SHOW_TOWER_RESET_MAX);
        GET_INT_DATA(t.wCoinBuyMax, row, E_CONFIG_VIP_SHOW_COIN_BUY_MAX);
        GET_INT_DATA(t.wPetBagMax, row, E_CONFIG_VIP_SHOW_PET_BAG_MAX);
        GET_INT_DATA(t.wItemBagMax, row, E_CONFIG_VIP_SHOW_ITEM_BAG_MAX);
        GET_INT_DATA(t.wEnergyBuyMax, row, E_CONFIG_VIP_SHOW_ENERGY_BUY_MAX);
        GET_INT_DATA(t.wArenaBuyMax, row, E_CONFIG_VIP_SHOW_ARENA_BUY_MAX);
        GET_STRING_DATA(t.strDes, row, E_CONFIG_VIP_SHOW_DES);
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool ActiveStageConfig::Load(const char *filePath)
{
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_ACTIVE_STAGE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wIndex, row, E_ACTIVE_STAGE_CONFIG_INDEX);
        GET_INT_DATA(t.byLvLimit, row, E_ACTIVE_STAGE_CONFIG_LVLIMIT);
        GET_INT_DATA(t.byPicId, row, E_ACTIVE_STAGE_CONFIG_PICID);
        GET_STRING_DATA(t.strName, row, E_ACTIVE_STAGE_CONFIG_NAME);
        GET_INT_DATA(t.byDiffiValue, row, E_ACTIVE_STAGE_CONFIG_DIFFVALUE);
        GET_STRING_DATA(t.strDes, row, E_ACTIVE_STAGE_CONFIG_DES);
        GET_INT_DATA(t.wBattleMapId, row, E_ACTIVE_STAGE_CONFIG_MAP_ID);
        
        std::string str = "";
        GET_STRING_DATA(str, row, E_ACTIVE_STAGE_CONFIG_NORMAL_BGM);
        ResourceStringConverter::StrSplit(str, "_", t.vectNormalBgm);
        GET_STRING_DATA(str, row, E_ACTIVE_STAGE_CONFIG_BOSS_BGM);
        ResourceStringConverter::StrSplit(str, "_", t.vectBossBgm);
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool ArenaRewardConfig::Load(const char *filePath)
{
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_ARENA_REWARD_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wIndex, row, E_ARENA_REWARD_CONFIG_INDEX);
        GET_INT_DATA(t.wRankBegin, row, E_ARENA_REWARD_CONFIG_RANK_BEGIN);
        GET_INT_DATA(t.wRankEnd, row, E_ARENA_REWARD_CONFIG_RANK_END);
        GET_INT_DATA(t.dwMoneyMax, row, E_ARENA_REWARD_CONFIG_MONEY_MAX);
        GET_INT_DATA(t.dwMoneyMin, row, E_ARENA_REWARD_CONFIG_MONEY_MIN);
        GET_INT_DATA(t.dwReputationMax, row, E_ARENA_REWARD_CONFIG_REPUTATION_MAX);
        GET_INT_DATA(t.dwReputationMin, row, E_ARENA_REWARD_CONFIG_REPUTATION_MIN);
        
        for (int k = 0; k < 5; k++)
        {
            GET_INT_DATA(t.dwItemID[k], row, E_ARENA_REWARD_CONFIG_ITEM_ID + 100 * k);
            GET_INT_DATA(t.dwItemCount[k], row, E_ARENA_REWARD_CONFIG_ITEM_COUNT + 100 * k);
        }
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool FirstRechargeConfig::Load(const char *filePath)
{
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_FIRST_RECHARGE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wIndex, row, E_FIRST_REWARD_CONFIG_INDEX);
        for (int k = 0; k < 5; k++)
        {
            GET_INT_DATA(t.dwItemID[k], row, E_FIRST_REWARD_CONFIG_ITEMID + 100 * k);
            GET_INT_DATA(t.dwItemCount[k], row, E_FIRST_REWARD_CONFIG_ITEMCOUNT + 100 * k);
        }
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

//combo_xy.csv
bool ComboOffConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_COMBO_OFF_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wIndex  , row , E_CONFIG_COMBO_OFF_INDEX );
        for ( int k = 0; k < 15; k++ )
        {
            std::string off = "";
            GET_STRING_DATA( off , row , E_CONFIG_COMBO_OFF_POINT + k );
            std::vector<int> arrOff;
            ResourceStringConverter::StrSplit(off, "_", arrOff);
            if (arrOff.size()>0) {
                t.arrComboOffX[k] = arrOff[0];
            }
            if (arrOff.size() > 1) {
                t.arrComboOffY[k] = arrOff[1];
            }
        }
        
        m_mapConfig.insert( std::make_pair( t.wIndex, t ) );
    }
    
    return true;
}

bool EmblemConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_EMBLEM_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.dwIndex  , row , E_CONFIG_EMBLEM_INDEX );
        GET_STRING_DATA( t.strName , row , E_CONFIG_EMBLEM_NAME );
        GET_INT_DATA( t.byStarLv  , row , E_CONFIG_EMBLEM_STAR_LV );
        GET_INT_DATA( t.wMaxLv  , row , E_CONFIG_EMBLEM_MAX_LV );
        GET_INT_DATA( t.dwExpFatio  , row , E_CONFIG_EMBLEM_EXPFATIO );
        GET_INT_DATA( t.dwEatExp  , row , E_CONFIG_EMBLEM_EATEXP );
        
        for (int k = 0; k < 3; k++) {
            GET_INT_DATA( t.byAttribute[k]  , row , E_CONFIG_EMBLEM_ATTRIBUTE + k*100 );
            GET_INT_DATA( t.byAttrType[k]  , row , E_CONFIG_EMBLEM_ATTRTYPE + k*100 );
            GET_INT_DATA( t.dwAttrValue[k]  , row , E_CONFIG_EMBLEM_ATTRVALUE + k*100 );
            GET_INT_DATA( t.dwAttrChg[k]  , row , E_CONFIG_EMBLEM_ATTRCHG + k*100 );
        }
        
        for (int k = 0; k < 5; k++) {
            GET_INT_DATA( t.wExcPetIndex[k]  , row , E_CONFIG_EMBLEM_EXCPET_INDEX + k*100 );
            GET_INT_DATA( t.byExcAttr[k]  , row , E_CONFIG_EMBLEM_EXCATTR + k*100 );
            GET_INT_DATA( t.dwExcAttrValue[k]  , row , E_CONFIG_EMBLEM_EXCATTRVALUE + k*100 );
        }
        
        GET_STRING_DATA( t.strDes , row , E_CONFIG_EMBLEM_DES );
        GET_INT_DATA( t.wIcon  , row , E_CONFIG_EMBLEM_ICON );
        
        m_mapConfig.insert( std::make_pair( t.dwIndex, t ) );
    }
    
    return true;
}

bool ExpConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_EXP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        
        GET_INT_DATA( t.wLv  , row , E_CONFIG_EXP_LV );
        GET_INT_DATA( t.dwUserExp , row , E_CONFIG_EXP_USER_EXP );
        GET_INT_DATA( t.dwEnergyMax  , row , E_CONFIG_EXP_ENERGY );
        GET_INT_DATA( t.dwEquipCost  , row , E_CONFIG_EXP_EQUIP_COST );
        GET_INT_DATA( t.dwPetExp  , row , E_CONFIG_EXP_PET_EXP );
        GET_INT_DATA( t.dwTalentExp  , row , E_CONFIG_EXP_TALENT_EXP );
        GET_INT_DATA( t.dwPassiveExp  , row , E_CONFIG_EXP_PASSIVE_EXP );
        GET_INT_DATA( t.dwEmblemExp  , row , E_CONFIG_EXP_EMBLEM_EXP );
        GET_INT_DATA( t.dwGetEquipFuseMoney  , row , E_CONFIG_EXP_FUSE_EQUIP_GET_MONEY );
        
        GET_INT_DATA( t.dwGetPetFusePetId  , row , E_CONFIG_EXP_FUSE_PET_GET_PET_ID );
        GET_INT_DATA( t.dwGetPetFusePetCnt  , row , E_CONFIG_EXP_FUSE_PET_GET_PET_CNT );
        GET_INT_DATA( t.dwGetPetFuseMoney  , row , E_CONFIG_EXP_FUSE_PET_GET_MONEY );
        GET_INT_DATA( t.dwGetPetFuseItemId  , row , E_CONFIG_EXP_FUSE_PET_GET_ITEM_ID );
        GET_INT_DATA( t.dwGetPetFuseItemCnt  , row , E_CONFIG_EXP_FUSE_PET_GET_ITEM_CNT );
        
        
        m_mapConfig.insert( std::make_pair( t.wLv, t ) );
    }
    
    return true;
}

bool TowerConfig::Load(const char * filePath)
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_TOWER_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wIndex, row, E_CONFIG_TOWER_INDEX);
        GET_INT_DATA( t.byIsSpecial, row, E_CONFIG_TOWER_IS_SPECIAL);
        GET_INT_DATA( t.wBattleMapId, row, E_CONFIG_TOWER_MAP_ID);

        for (int k = 0; k < 4; k++ )
        {
            GET_INT_DATA( t.dwRewardID[k], row, E_CONFIG_TOWER_REWARD_ID + 2 * k);
            GET_INT_DATA( t.dwRewardCount[k], row, E_CONFIG_TOWER_REWARD_COUNT + 2 * k);
        }
        GET_INT_DATA( t.dwPetLevel, row, E_CONFIG_TOWER_PET_LEVEL);
        GET_STRING_DATA( t.strDesc, row, E_CONFIG_TOWER_DESC);
        GET_INT_DATA( t.dwPetIcon, row, E_CONFIG_TOWER_PET_ICON);
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool SupportSkillConfig::Load(const char * filePath)
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_SUPPORT_SKILL_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wPetIndex, row, E_CONFIG_SUPPORT_SKILL_INDEX);
        for (int k = 0; k < 4; k++ )
        {
            GET_INT_DATA( t.byNature[k], row, E_CONFIG_SUPPORT_SKILL_NATURE + 100 * k);
            GET_INT_DATA( t.dwPassSkillId[k], row, E_CONFIG_SUPPORT_SKILL_PASSIVE_ID + 100 * k);
        }
        
        m_mapConfig.insert(std::make_pair(t.wPetIndex, t));
    }
    return true;
}


bool ChallengeConfig::Load(const char * filePath)
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_CHALLENGE_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wIndex, row, E_CONFIG_CHANLLENGE_INDEX);
        GET_STRING_DATA( t.strName, row, E_CONFIG_CHANLLENGE_NAME);

        for (int k = 0; k < 4; k++ )
        {
            GET_INT_DATA( t.dwRewardItem[k], row, E_CONFIG_CHANLLENGE_REWARD_ITEM + 100 * k);
            GET_INT_DATA( t.dwRewardItemCnt[k], row, E_CONFIG_CHANLLENGE_REWARD_ITEM_CNT + 100 * k);
        }
        GET_INT_DATA( t.dwShowMapId, row, E_CONFIG_CHANLLENGE_MAP_ID);
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool ChallengeBuffConfig::Load(const char * filePath)
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_CHALLENGE_BUFF_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wIndex, row, E_CONFIG_CHANLLENGE_BUFF_INDEX);
        GET_INT_DATA( t.byBuffType1, row, E_CONFIG_CHANLLENGE_BUFF_TYPE_1);
        GET_INT_DATA( t.dwPara1, row, E_CONFIG_CHANLLENGE_BUFF_PARA_1);
        GET_INT_DATA( t.byBuffType2, row, E_CONFIG_CHANLLENGE_BUFF_TYPE_2);
        GET_INT_DATA( t.dwPara2, row, E_CONFIG_CHANLLENGE_BUFF_PARA_2);
        
        GET_STRING_DATA( t.strDesc, row, E_CONFIG_CHANLLENGE_BUFF_DES);
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool StageBonusConfig::Load(const char* filePath) {
    if ( !ConfigBase::Load( filePath ) ) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_BONUS t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wIndex, row, E_STAGE_BONUS_ID );

        for (int j = 0; j < 3; j++) {
            GET_INT_DATA( t.wRewardNeed[j], row, E_STAGE_BONUS_REWARD_NEED + j * 100);
            GET_INT_DATA( t.dwRewardId[j], row, E_STAGE_BONUS_REWARD_ID + j * 100);
            GET_INT_DATA( t.dwRewardCnt[j], row, E_STAGE_BONUS_REWARD_CNT + j * 100);
        }
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool MusicConfig::Load(const char *filePath) {
    if ( !ConfigBase::Load(filePath) ) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_MUSIC t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wIndex, row, E_CONFIG_MUSIC_ID );
        GET_STRING_DATA( t.strPath, row, E_CONFIG_MUSIC_PATH );
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool ArmatureConfig::Load(const char *filePath) {
    if ( !ConfigBase::Load(filePath) ) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_ARMATURE t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wIndex, row, E_CONFIG_ARMATURE_ID );
        GET_STRING_DATA( t.strPath, row, E_CONFIG_ARMATURE_PATH );
        GET_STRING_DATA( t.strName, row, E_CONFIG_ARMATURE_NAME );
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}


bool TipsConfig::Load(const char *filePath) {
    if ( !ConfigBase::Load(filePath) ) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_TIPS t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wIndex, row, E_CONFIG_TIPS_ID );
        GET_STRING_DATA( t.strText, row, E_CONFIG_TIPS_TEXT );
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool VipBuyConfig::Load(const char *filePath) {
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_VIP_BUY t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wBuyCnt, row, E_CONFIG_VIP_BUY_CNT );
        GET_INT_DATA( t.wArena, row, E_CONFIG_VIP_BUY_ANENA);
        GET_INT_DATA( t.wEnergy, row, E_CONFIG_VIP_BUY_ENERGY);
        GET_INT_DATA( t.wNormalStage, row, E_CONFIG_VIP_BUY_NORMAL_STAGE);
        GET_INT_DATA( t.wSpecialStage, row, E_CONFIG_VIP_BUY_SPECIAL_STAGE);
        GET_INT_DATA( t.wMoneyCat, row, E_CONFIG_VIP_BUY_MONEY_CAT);
        GET_INT_DATA( t.wTower, row, E_CONFIG_VIP_BUY_TOWER);
        GET_INT_DATA( t.wHeroStage, row, E_CONFIG_VIP_BUY_HERO_STAGE);
        
        m_mapConfig.insert(std::make_pair(t.wBuyCnt, t));
    }
    return true;
}

bool PetLiuWeiConfig::Load(const char *filePath) {
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_PET_LIUWEI t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        GET_INT_DATA( t.wIndex, row, E_CONFIG_PET_LIUWEI_ID );
        GET_INT_DATA( t.wHp, row, E_CONFIG_PET_LIUWEI_HP);
        GET_INT_DATA( t.wAtk, row, E_CONFIG_PET_LIUWEI_ATK);
        GET_INT_DATA( t.wCDef, row, E_CONFIG_PET_LIUWEI_CDEF);
        GET_INT_DATA( t.wSDef, row, E_CONFIG_PET_LIUWEI_SDEF);
        GET_INT_DATA( t.wSupp, row, E_CONFIG_PET_LIUWEI_SUPP);
        GET_INT_DATA( t.wControl, row, E_CONFIG_PET_LIUWEI_CONTROL);
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool MysteryShopConfig::Load(const char *filePath) {
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_MYSTERY_SHOP t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        GET_INT_DATA( t.wIndex, row, E_CONFIG_MYSTERY_SHOP_ID );
        GET_STRING_DATA( t.strName, row, E_CONFIG_MYSTERY_SHOP_NAME );
        GET_INT_DATA( t.byType, row, E_CONFIG_MYSTERY_SHOP_TYPE);
        GET_INT_DATA( t.dwItemId, row, E_CONFIG_MYSTERY_SHOP_ITEM_ID);
        GET_INT_DATA( t.dwItemCnt, row, E_CONFIG_MYSTERY_SHOP_ITEM_CNT);
        GET_INT_DATA( t.dwCanBuyCnt, row, E_CONFIG_MYSTERY_SHOP_CAN_BUY_CNT);
        GET_INT_DATA( t.dwBuyCost, row, E_CONFIG_MYSTERY_SHOP_BUY_COST);
//        GET_INT_DATA( t.dwRefCostDollor, row, E_CONFIG_MYSTERY_SHOP_REF_COST_DOLLOR);
//        GET_INT_DATA( t.dwRefCostStone, row, E_CONFIG_MYSTERY_SHOP_REF_COST_STONE);
        GET_STRING_DATA( t.strDes, row, E_CONFIG_MYSTERY_SHOP_DES );
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}


bool ArenaShopConfig::Load(const char *filePath) {
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_ARENA_SHOP t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        GET_INT_DATA( t.wIndex, row, E_CONFIG_ARENA_SHOP_ID );
        GET_STRING_DATA( t.strName, row, E_CONFIG_ARENA_SHOP_NAME );
        GET_INT_DATA( t.dwItemId, row, E_CONFIG_ARENA_SHOP_ITEM_ID);
        GET_INT_DATA( t.dwItemCnt, row, E_CONFIG_ARENA_SHOP_ITEM_CNT);
        GET_INT_DATA( t.dwCanBuyCnt, row, E_CONFIG_ARENA_SHOP_CAN_BUY_CNT);
        GET_INT_DATA( t.dwBuyCost, row, E_CONFIG_ARENA_SHOP_BUY_COST);
        GET_STRING_DATA( t.strDes, row, E_CONFIG_ARENA_SHOP_DES );
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool DailyRewardConfig::Load(const char *filePath)
{
        if ( !ConfigBase::Load(filePath)) {
            return false;
        }
        
        int wRow = m_pReader->rowCount();
        
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_DAILYREWARD t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( t.wRewardId, row, E_CONFIG_DAILY_REWARD_ID );
        GET_INT_DATA( t.dwNeedScore, row, E_CONFIG_DAILY_REWARD_NEED_SCORE );
        
        for (int j = 0; j < 4; j++) {
            GET_INT_DATA( t.dwRewardItemId[j], row, E_CONFIG_DAILY_REWARD_REWARD_ITEM_1 + j * 100);
            GET_INT_DATA( t.dwRewardItemNum[j], row, E_CONFIG_DAILY_REWARD_REWARD_ITEM_NUM_1 + j * 100);
        }
        m_mapConfig.insert(std::make_pair(t.wRewardId, t));
    }

        return true;

}

bool ChestConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_CHEST configInfo;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA( configInfo.dwIndex, row, E_CONFIG_CHEST_INDEX );
        configInfo.vecInfo.clear();
        STC_UNITE_RESOURCE cellItem;
        for (int j = 0; j < 8; j++) {
            GET_INT_DATA(cellItem.dwUniteId, row, E_CONFIG_CHEST_ITEM_INDEX1 + j * 2);
            GET_INT_DATA(cellItem.dwUniteCnt, row, E_CONFIG_CHEST_ITEM_NUM1 + j * 2 );
            if (cellItem.dwUniteId != 0) {
                configInfo.vecInfo.push_back(cellItem);
            }
        }
        
        GET_INT_DATA(configInfo.wIcon, row, E_CONFIG_CHEST_ITEM_ICON);
        GET_STRING_DATA(configInfo.strDes, row, E_CONFIG_CHEST_ITEM_DES);
        GET_STRING_DATA(configInfo.strName, row, E_CONFIG_CHEST_ITEM_NAME);
        m_mapConfig.insert(std::make_pair(configInfo.dwIndex, configInfo));
    }
    
    return true;
    
}


bool WorldBossInfoConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load(filePath)) {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    
    for (int i = 0; i < wRow; i++) {
        STC_CONFIG_WORLD_BOSS_INFO t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);

        GET_INT_DATA( t.wBossIndex, row, E_CONFIG_WORLD_INFO_BOSS_INDEX );
        GET_INT_DATA( t.dwAttCDTime, row, E_CONFIG_WORLD_INFO_ATT_CD );
        GET_INT_DATA( t.dwAttFuhuoDollor, row, E_CONFIG_WORLD_INFO_ATT_DOLLOR );
        GET_INT_DATA( t.dwBlessMoney, row, E_CONFIG_WORLD_INFO_BLESS_MONEY );
        GET_INT_DATA( t.dwBlessMoneyAddMax, row, E_CONFIG_WORLD_INFO_BLESS_MONEY_MAX );
        GET_INT_DATA( t.dwBlessDollor, row, E_CONFIG_WORLD_INFO_BLESS_DOLLOR );
        GET_INT_DATA( t.dwBlessDollorAddMax, row, E_CONFIG_WORLD_INFO_BLESS_DOLLOR_MAX );
        GET_INT_DATA( t.dwBlessMoneyCD, row, E_CONFIG_WORLD_INFO_BLESS_MONEY_CD );
        
        
        m_mapConfig.insert(std::make_pair(t.wBossIndex, t));
    }
    
    return true;
    
}

bool WorldBossRewardConfig::Load(const char *filePath)
{
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }
    
    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_WORLD_BOSS_REWARD_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wIndex, row, E_WORLD_BOSS_REWARD_CONFIG_INDEX);
        GET_INT_DATA(t.wRankBegin, row, E_WORLD_BOSS_REWARD_CONFIG_RANK_BEGIN);
        GET_INT_DATA(t.wRankEnd, row, E_WORLD_BOSS_REWARD_CONFIG_RANK_END);
        
        for (int k = 0; k < 4; k++)
        {
            GET_INT_DATA(t.dwItemID[k], row, E_WORLD_BOSS_REWARD_CONFIG_ITEM_ID + 100 * k);
            GET_INT_DATA(t.dwItemCount[k], row, E_WORLD_BOSS_REWARD_CONFIG_ITEM_COUNT + 100 * k);
        }
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool QingYuanConfig::Load(const char *filePath)
{
    if (!ConfigBase::Load(filePath))
    {
        return false;
    }

    int nRow = m_pReader->rowCount();
    for (int i = 0; i < nRow; i++)
    {
        STC_QING_YUAN_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow(i);
        
        GET_INT_DATA(t.wIndex, row, E_QING_YUAN_CONFIG_INDEX);
        GET_STRING_DATA(t.strName, row, E_QING_YUAN_CONFIG_NAME);
        GET_INT_DATA(t.dwAttType, row, E_QING_YUAN_CONFIG_ATT_TYPE);
        GET_INT_DATA(t.dwAttValue, row, E_QING_YUAN_CONFIG_ATT_VALUE);
        
        for (int k = 0; k < 4; k++)
        {
            GET_INT_DATA(t.dwQyPetGroup[k], row, E_QING_YUAN_CONFIG_QY_PET + k);
            GET_STRING_DATA(t.strPetName[k], row, E_QING_YUAN_CONFIG_QY_PET_NAME + k);
        }
        
        m_mapConfig.insert(std::make_pair(t.wIndex, t));
    }
    return true;
}

bool EmblemShowConfig::Load(const char * filePath )
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_EMBLEM_SHOW_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        GET_INT_DATA( t.dwIndex  , row , E_CONFIG_EMBLEM_SHOW_INDEX );
        
        for (int k = 0; k < 2; k++) {
            GET_INT_DATA( t.wExcEmIndex[k]  , row , E_CONFIG_EMBLEM_SHOW_EXCEM_INDEX + k*100 );
            GET_INT_DATA( t.byExcAttr[k]  , row , E_CONFIG_EMBLEM_SHOW_EXCATTR + k*100 );
            GET_INT_DATA( t.dwExcAttrValue[k]  , row , E_CONFIG_EMBLEM_SHOW_EXCATTRVALUE + k*100 );
            GET_STRING_DATA(t.strName[k], row, E_CONFIG_EMBLEM_SHOW_NAME + k*100);
        }
        
        GET_INT_DATA( t.wExcEquipIndex  , row , E_CONFIG_EMBLEM_SHOW_EQUIP_EXCEM_INDEX );
        GET_INT_DATA( t.byExcEquipAttr  , row , E_CONFIG_EMBLEM_SHOW_EQUIP_EXCATTR );
        GET_INT_DATA( t.dwExEquipcAttrValue  , row , E_CONFIG_EMBLEM_SHOW_EQUIP_EXCATTRVALUE  );
        GET_STRING_DATA(t.strExcEquipName, row, E_CONFIG_EMBLEM_SHOW_EQUIP_NAME );
        m_mapConfig.insert( std::make_pair( t.dwIndex, t ) );
    }
    
    return true;
}

bool ShareConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_SHARE_CONFIG stcShare;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        GET_INT_DATA( stcShare.dwIndex  , row , E_CONFIG_SHARE_INDEX );
        GET_INT_DATA( stcShare.dwItemIndex, row, E_CONFIG_SHARE_ITEM_INDEX);
        GET_INT_DATA( stcShare.dwItemCount, row, E_CONFIG_SHARE_ITEM_COUNT);
        
        m_mapConfig.insert( std::make_pair( stcShare.dwIndex, stcShare ) );
    }
    
    return true;
}


bool EquipGroupConfig::Load(const char *filePath)
{
    if ( !ConfigBase::Load( filePath ) )
    {
        return false;
    }
    
    /*
     套装ID*10+部件位置=装备真ID
     装备真ID*10000=装备indexid
     装备indexid+进阶等级=装备进阶后的indexid
     */
    
    int wRow = m_pReader->rowCount();
    
    for ( int i = 0; i < wRow; ++i )
    {
        STC_EQUIP_GROUP_CONFIG t;
        const CsvReader::CSV_ROW_TYPE* row = m_pReader->getRow( i );
        GET_INT_DATA( t.dwEquipGroupId  , row , E_CONFIG_EQUIP_GROUP_INDEX );
        GET_INT_DATA( t.dwSuitId, row, E_CONFIG_EQUIP_GROUP_SUIT);
        GET_STRING_DATA(t.strName, row, E_CONFIG_EQUIP_GROUP_NAME);

//        E_CONFIG_EQUIP_GROUP_ATTR_TYPE = 201,
//        E_CONFIG_EQUIP_GROUP_ATTR_ADD_TYPE = 202,
//        E_CONFIG_EQUIP_GROUP_ATTR_VALUE = 203,

        for (int q = 0; q < 2; q++) {
            GET_INT_DATA( t.byAttrType_1[q]  , row , E_CONFIG_EQUIP_GROUP_ATTR_TYPE + q*10);
            GET_INT_DATA( t.byAttrAddType_1[q]  , row , E_CONFIG_EQUIP_GROUP_ATTR_TYPE  + q*10);
            GET_INT_DATA( t.dwAttrValue_1[q]  , row , E_CONFIG_EQUIP_GROUP_ATTR_TYPE  + q*10);
        }

        for (int q = 0; q < 2; q++) {
            GET_INT_DATA( t.byAttrType_2[q]  , row , E_CONFIG_EQUIP_GROUP_ATTR_TYPE + 100 + q*10);
            GET_INT_DATA( t.byAttrAddType_2[q]  , row , E_CONFIG_EQUIP_GROUP_ATTR_TYPE + 100  + q*10);
            GET_INT_DATA( t.dwAttrValue_2[q]  , row , E_CONFIG_EQUIP_GROUP_ATTR_TYPE + 100 + q*10);
        }
        
        for (int q = 0; q < 2; q++) {
            GET_INT_DATA( t.byAttrType_3[q]  , row , E_CONFIG_EQUIP_GROUP_ATTR_TYPE + 200 + q*10);
            GET_INT_DATA( t.byAttrAddType_3[q]  , row , E_CONFIG_EQUIP_GROUP_ATTR_TYPE + 200  + q*10);
            GET_INT_DATA( t.dwAttrValue_3[q]  , row , E_CONFIG_EQUIP_GROUP_ATTR_TYPE + 200  + q*10);
        }
        
        m_mapConfig.insert( std::make_pair( t.dwEquipGroupId, t ) );
    }
    
    return true;
}