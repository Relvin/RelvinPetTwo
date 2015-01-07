#include "SpccMovieClip.h"
#include "SpccReader.h"
#include "ConfigUtil.h"
#include "ConfigGet.h"
#include "SpccMovieFPSAction.h"

SpccMovieClip::SpccMovieClip()
{
    m_wCurFrame = 0xffff;
}

SpccMovieClip::~SpccMovieClip()
{
    this->removeChild( m_pContent, true );
    
    if ( !m_bMultiPng )
    {
        CCTexture2D* tex = NULL;
        
        FOR_EACH( EffectFrameInfo, info, std::vector<EffectFrameInfo>, m_effectConfig.frames )
        {
            if ( info.byPngIdx == -1 ) continue;
            
            std::string name = CUtil::StrFormat( _SPCC_SPRITE_FRAME_NAME_, m_dwId, info.byPngIdx, FORMAT_PARAM_END );
            
            CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( name.c_str() );
            if (sf) {
                sf->release();
                
                if ( sf->retainCount() == 1 )
                {
                    tex = sf->getTexture();
                    // it is unused
                    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName( name.c_str() );
                }
            }
        }
        
        if ( tex )
        {
            CCTextureCache::sharedTextureCache()->removeTexture( tex );
        }
    }
    
//    if (m_pContent) {
//        m_pContent->removeAllChildrenWithCleanup(true);
//        this->removeChild(m_pContent, true);
//        m_pContent = NULL;
//    }
}

SpccMovieClip* SpccMovieClip::create(uint32 dwId, int8 byDirection, bool bMultiPng )
{
    SpccMovieClip* ret = new SpccMovieClip();
    
    if ( ret && ret->initWithSpccId( dwId, byDirection, bMultiPng ) )
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE( ret );
    
    return NULL;
}

//SpccMovieClip* SpccMovieClip::createByPetId( uint16 petId, int8 byDirection, bool bMultiPng )
//{
//    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, petId);
//    if (!petCfg) {
//        return NULL;
//    }
//    PetModel::STC_PET_MODEL_CONFIG *petModelCfg = GET_CONFIG_STC(PetModel, petCfg->dwModelIndex);
//    if (!petModelCfg) {
//        return NULL;
//    }
//        
//    SpccMovieClip* ret = create(petModelCfg->wEffIndex, byDirection, bMultiPng);
//    
//    return ret;
//}

bool SpccMovieClip::initWithSpccId( uint32 dwId, int8 byDirection, bool bMultiPng )
{
    if ( !CCSprite::init() ) return false;
    
    m_bMultiPng = bMultiPng;
    
    std::string name;
    
    name = CUtil::StrFormat( _SPCC_CONFIG_FILE_PATH_, dwId, FORMAT_PARAM_END );
    
    std::string configPath = CCFileUtils::sharedFileUtils()->fullPathForFilename( name.c_str() );
//        CCFileUtils::sharedFileUtils()->fullPathFromRelativePath( name.c_str() );

    if ( !SpccReader::sharedSpccReader()->readConfigFromFile( configPath, m_effectConfig ) )
    {
        return false;
    }
    
    if ( !m_bMultiPng )
    {
        name = CUtil::StrFormat( _SPCC_PLIST_FILE_PATH_, dwId, FORMAT_PARAM_END );
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( name.c_str() );
        
        FOR_EACH( EffectFrameInfo, info, std::vector<EffectFrameInfo>, m_effectConfig.frames )
        {
            if ( info.byPngIdx == -1 ) continue;
            name = CUtil::StrFormat( _SPCC_SPRITE_FRAME_NAME_, dwId, info.byPngIdx, FORMAT_PARAM_END );
            CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( name.c_str() );
            sf->retain();
        }
    }
    
    m_dwId          = dwId;
    m_direction     = byDirection;
    m_pContent      = CCSprite::create();
    
    this->addChild( m_pContent );
    this->setAnchorPoint( ccp(0, 0) );
    this->setScaleX( -m_direction );
    
    return true;
}

uint16 SpccMovieClip::getTotalFrame()
{
    return m_effectConfig.frames.size();
}

void SpccMovieClip::setFrameIdx(uint16 wFrameIdx)
{
    CCAssert( wFrameIdx < m_effectConfig.frames.size(), "invalid frame index" );
    
    if ( wFrameIdx == m_wCurFrame ) return;
    m_wCurFrame = wFrameIdx;
    
    EffectFrameInfo& info = m_effectConfig.frames[ wFrameIdx ];
    
    if ( info.byPngIdx == -1 )
    {
        m_pContent->init();
        return;
    }
    
    if ( m_bMultiPng )
    {
        std::string name = CUtil::StrFormat( _SPCC_SPRITE_FILE_NAME_, m_dwId, info.byPngIdx, FORMAT_PARAM_END );
        m_pContent->initWithFile( name.c_str() );
    }
    else 
    {
        std::string name = CUtil::StrFormat( _SPCC_SPRITE_FRAME_NAME_, m_dwId, info.byPngIdx, FORMAT_PARAM_END );
        m_pContent->initWithSpriteFrameName( name.c_str() );
    }
    
    m_pContent->setScale( m_effectConfig.lessScale );
    
    m_pContent->setAnchorPoint( ccp(0, 1) );
    //CCLog( "size(%f, %f) offset %d(%d, %d)", m_pContent->getContentSize().width, m_pContent->getContentSize().height, info.byPngIdx, info.dwOffsetX, info.dwOffsetY );
    m_pContent->setPosition( ccp( info.dwOffsetX / 2.0f, -info.dwOffsetY / 2.0f ) );
    m_pContent->setOpacity( getOpacity() );
}


void SpccMovieClip::runFPSAction(SpccMovieFPSAction *action)
{
    m_fpsAction = NULL;
    if (!action) {
        return;
    }
    m_fpsAction = action;
    m_fpsAction->setPosition(ccp(-1000,-1000));
    addChild(m_fpsAction);
    m_fpsAction->startWithTarget();
}

void SpccMovieClip::pauseFPSAction(int pauseFrame)
{
    if (!m_fpsAction) {
        return;
    }
    m_fpsAction->pause(pauseFrame);
}

void SpccMovieClip::resumeFPSAction()
{
    if (!m_fpsAction) {
        return;
    }
    m_fpsAction->pause(0);
}

void SpccMovieClip::stopFPSAction()
{
    if (!m_fpsAction) {
        return;
    }
    m_fpsAction->stop();
}