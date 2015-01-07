//
//  FlccMovieClip.cpp
//
//  Created by ziRoy on 12-7-10.
//

#include "FlccMovieClip.h"
#include "cocos2d.h"
#include "FlccReader.h"
#include "cmath"
#include "ConfigUtil.h"

#include "ConfigData.h"
#include "game_config.h"
#include "FlccMovieFPSAction.h"
#include "FightPetSprite.h"

USING_NS_CC;

#define getSpriteId(x, y)   x*100 + y

const std::string FlccMovieClip::NO_ACTION = "NO_ACTION";

FlccSpriteNode* FlccSpriteNode::createWithSpriteFrameName( const char* pszSpriteFrameName )
{
    FlccSpriteNode* ret = new FlccSpriteNode();
    if ( ret && ret->initWithSpriteFrameName( pszSpriteFrameName ) )
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE( ret );
    return NULL;
}

void FlccSpriteNode::setMatrix( float a, float b, float c, float d, float tx, float ty )
{
    m_fA    = a;
    m_fB    = b;
    m_fC    = c;
    m_fD    = d;
    m_fTx   = tx;
    m_fTy   = ty;
//    m_bIsInverseDirty = m_bIsTransformDirty = true;
    m_bInverseDirty = m_bTransformDirty = true;
}
bool    FlccSpriteNode::NeedChangeTexture( uint8 alterid, uint8 frameid )
{
    return ( m_frameId != frameid || m_alterId != alterid );
}

void    FlccSpriteNode::SetNewTextureID( uint8 alterid, uint8 frameid )
{
    m_alterId     = alterid;
    m_frameId   = frameid;
}

CCAffineTransform FlccSpriteNode::nodeToParentTransform(void)
{
//    if ( m_bIsTransformDirty )
//    {
//        m_tTransform = CCAffineTransformMake( m_fA, m_fB, m_fC, m_fD, m_fTx, m_fTy );
//        
//        if ( !CCPoint::CCPointEqualToPoint( m_tAnchorPoint, CCPointZero) )
//        {
//            m_tTransform = CCAffineTransformTranslate( m_tTransform, -m_tAnchorPointInPoints.x, -m_tAnchorPointInPoints.y );
//        }
//        m_bIsTransformDirty = false;
//    }
//    return m_tTransform;
    if ( m_bTransformDirty )
    {
        m_sTransform = CCAffineTransformMake( m_fA, m_fB, m_fC, m_fD, m_fTx, m_fTy );
        
//        if ( !CCPoint::CCPointEqualToPoint( m_obAnchorPoint, CCPointZero) )
        if ( !m_obAnchorPoint.equals(CCPointZero) )
        {
            m_sTransform = CCAffineTransformTranslate( m_sTransform, -m_obAnchorPointInPoints.x, -m_obAnchorPointInPoints.y );
        }
        m_bTransformDirty = false;
    }
    return m_sTransform;
}

FlccMovieClip::FlccMovieClip()
:m_curAction(NULL), m_heroId(0), m_fps(42), m_playing(false), m_curFrame(0),m_oldFrame(0), m_loop(true),
m_direction(-1), m_content(NULL), m_FlccAlpha( 255 ),m_FightPetSprite(NULL), m_modelId(0)
{
}

FlccMovieClip::~FlccMovieClip()
{
//    if ( m_content )
//    {
//        m_content->removeAllChildrenWithCleanup( true );
//        this->removeChild( m_content, true );
//    }
    
//    CCLOG("Bbefore: content cnt:%u", m_content->getChildrenCount());
    
    CCTexture2D* tex = NULL;

    uint8 alertId = 1;
    
    FOR_EACH( SymbolInfo, symbolInfo, std::vector<SymbolInfo>, m_animationConfig.symbols )
//    for ( std::vector<SymbolInfo>::iterator it = m_animationConfig.symbols.begin(); it != m_animationConfig.symbols.end(); it++ )
    {
		/************************************************************************/
		/* 
			R-value is released immediately by MSVC compiler
			@yuxiaofei
		*/
		/************************************************************************/
        //const char* sfName = CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_, 
        //                                      m_animationConfig.modelId,
        //                                      symbolInfo.partId,
        //                                      symbolInfo.alterId,FORMAT_PARAM_END ).c_str();
		std::string sfName = CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_,
			m_animationConfig.modelId,
			symbolInfo.partId,
			symbolInfo.alterId,
            symbolInfo.frameId, FORMAT_PARAM_END ).c_str();
        alertId = symbolInfo.alterId;
//        CCLOG("[0103] SymbolInfo: %s", sfName.c_str());
//        if (symbolInfo.partId == 7) {
//            CCLOG("[0103] SymbolInfo: %s", sfName.c_str());
//        }
        
        CCSpriteFrame* sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( sfName.c_str() );
        if (!sf) {
            continue;
        }
//        if (symbolInfo.frameId == 1) {
//            sf->release();
//        }
        sf->release();
//        CCLOG("Retain Cnt:%d", sf->retainCount());
        if ( sf->retainCount() == 1 )
        {
            tex = sf->getTexture();
            CCTextureCache::sharedTextureCache()->removeTexture( tex );
            
            // it is unused
            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName( sfName.c_str() );
        }
//        if (sf->retainCount() > 1) {
//            CCLOG("there are some sprite frame retain cnt > 2");
//        }
        
//        if (sf->retainCount() == 1) {
//            sf->release();
//        }
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
 
//    if ( tex )
//    {
//        CCTextureCache::sharedTextureCache()->removeTexture( tex );
//        tex = NULL;
        //CCTextureCache::sharedTextureCache()->removeUnusedTextures();
//    }
//    CCLOG("before: content cnt:%u", m_content->getChildrenCount());
//    std::map<uint16, FlccSpriteNode*>::iterator it = m_partSpriteMap.begin();
//    for (; it != m_partSpriteMap.end(); it++) {
//        m_content->removeChild(it->second, true);
//        
//        std::string sfName = CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_,
//                                              m_animationConfig.modelId,
//                                              (it->first / 100),
//                                              alertId,
//                                              (it->first % 100), FORMAT_PARAM_END ).c_str();
////        if (it->first / 100 == 7) {
////            CCLOG("[0103] partSpriteMap: %s", sfName.c_str());
////        }
//        
//        CCSpriteFrame* sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( sfName.c_str() );
//        if (!sf) {
//            continue;
//        }
////        sf->release();
////        if ((it->first % 100) == 1) {
////            sf->release();
////        }
////        else {
////            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName( sfName.c_str() );
////        }
//        CCLOG("[0103] partSpriteMap: %s", sfName.c_str());
//        if ( sf->retainCount() >= 1 )
//        {
//            tex = sf->getTexture();
////
////            // it is unused
//            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName( sfName.c_str() );
//        }
//        if (sf->retainCount() == 1) {
//            sf->release();
//        }
//    }
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
////    m_partSpriteMap.clear();
//    
//    if ( tex )
//    {
//        CCTextureCache::sharedTextureCache()->removeTexture( tex );
////        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
//    }
    m_partSpriteMap.clear();
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->purgeSharedSpriteFrameCache();
    
    if (m_content) {
//        CCLOG("after content cnt:%u", m_content->getChildrenCount());
        m_content->removeAllChildrenWithCleanup( true );
        this->removeChild( m_content, true );
        m_content = NULL;
    }
}

FlccMovieClip* FlccMovieClip::create( uint32 dwHeroId )
{
    FlccMovieClip* ret = new FlccMovieClip();
    if ( ret && ret->initWithHeroId( dwHeroId ) )
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE( ret );
    //取不到模型，用默认模型代替}
#ifdef DEBUG
	CCString *str = CCString::createWithFormat("Cant get [petId = %d] flcc model.", dwHeroId);
    CCMessageBox(str->getCString(), "Warnning");
    return create(1);
#endif
    return NULL;
}

FlccMovieClip* FlccMovieClip::create( uint32 dwSkeletonId, std::map<uint8, uint8>& mapPart )
{
    FlccMovieClip* ret = new FlccMovieClip();
    if ( ret && ret->initWithSkeletonId( dwSkeletonId, mapPart) )
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE( ret );
    return NULL;
}

bool FlccMovieClip::initWithHeroId(uint32 dwPetId )
{
    this->m_heroId = dwPetId;
    
    PetModel::STC_PET_MODEL_CONFIG *pConfig = Client::GetModelByPetId(dwPetId);
//    ModelConfig::STC_MODEL_CONFIG* pConfig = GET_CONFIG_STC(ModelConfig, _ID)
    m_modelId = pConfig->wSkeletonIndex;
//    ModelConfig::STC_MODEL_CONFIG* pConfig = Client::GetModelByHeroId( dwPetId );
    if ( pConfig == NULL ) return false;
    
    return initWithSkeletonId( pConfig->wSkeletonIndex, pConfig->mapPart );
}

//bool FlccMovieClip::initWithModelId( uint32 dwModelId )
//{
//    ModelConfig::STC_MODEL_CONFIG* pConfig = g_model_config.GetById( dwModelId );
//    if ( pConfig == NULL ) return false;
//    
//    return initWithSkeletonId( pConfig->dwSkeletonId, pConfig->parts );
//}

bool FlccMovieClip::initWithSkeletonId( uint32 dwSkeletonId, std::map<uint8, uint8>& mapPart )
{
    if ( !CCSprite::init() ) return false;
    
    // Note: Only this override version check whether the .plist file has been loaded before.
    // P.S. 'CCTextureCache::addImage' will check duplicate texture according to the file path.
    // It is recommended that loading all texture needed when scene entered
    // Load Texture
    CCSpriteFrameCache::sharedSpriteFrameCache()
        ->addSpriteFramesWithFile( CUtil::StrFormat( _FLCC_PLIST_FILE_PATH_ , dwSkeletonId, FORMAT_PARAM_END ).c_str() );
    
    // Load Configure
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename( CUtil::StrFormat( _FLCC_CONFIG_FILE_PATH_, dwSkeletonId, FORMAT_PARAM_END ).c_str() );
    if ( !FlccReader::sharedFlccReader()->readConfigFromFile( path, m_animationConfig ) )
    {
        IME_ERROR( "Read Flcc Fail, SkeletonId=%u", dwSkeletonId );
        return false;
    }
    
    // Note: CCSprite doesn't automatically retain CCSpriteFrame which it use to display.
    // So it may result unexpectedly when using 'removeUnusedSpriteFrames' without retaining them manually.
    FOR_EACH( SymbolInfo, symbolInfo, std::vector<SymbolInfo>, m_animationConfig.symbols )
    {
		std::string nameTemp = CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_, 
			m_animationConfig.modelId,
			symbolInfo.partId,
			symbolInfo.alterId,symbolInfo.frameId,FORMAT_PARAM_END     );
//        CCLog("----sprite frame name:%s", nameTemp.c_str());
        
		CCSpriteFrame* sf = CCSpriteFrameCache::sharedSpriteFrameCache()
            ->spriteFrameByName(nameTemp.c_str() );
#ifdef DEBUG
        if (sf == NULL) {
			CCLog("FlccMovieClip cannot get: %s", nameTemp.c_str());
            delete sf;
            return false;
        }
#else
        CCAssert( sf != NULL, "SpriteFrame Not Found" );
#endif
        
        sf->retain();
    }
    
    m_content = CCSpriteBatchNode::create( CUtil::StrFormat( _FLCC_TEXTURE_FILE_PATH_, dwSkeletonId, FORMAT_PARAM_END ).c_str() );
    m_content->setAnchorPoint( ccp( 0, 0) );
    m_content->setPosition( ccp( 0, 0 ) );	
    
    this->addChild( m_content );
    this->setAnchorPoint( ccp(0, 0) );
    this->setScaleX( -m_direction );
    
    //useDefaultPart();
    
    m_frameTT = 1.0 / m_fps;
    m_frameCT = 0;
    
    changePart( mapPart );
    
    return true;
}

FlccSpriteNode* FlccMovieClip::createSpriteWithPartAndAlter( uint8 partId, uint8 alterId, uint8 frameId )
{
    FOR_EACH( SymbolInfo, symbolInfo, std::vector<SymbolInfo>, m_animationConfig.symbols )
    {
        if ( symbolInfo.partId == partId && symbolInfo.alterId == alterId && symbolInfo.frameId == frameId )
        {
//            CCLog("%s", CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_,
//                                         m_animationConfig.modelId,
//                                         symbolInfo.partId,
//                                         symbolInfo.alterId,
//                                         symbolInfo.frameId,FORMAT_PARAM_END ).c_str());
            FlccSpriteNode* ret = FlccSpriteNode::createWithSpriteFrameName(
                                                                      CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_,
                                                                                       m_animationConfig.modelId,
                                   	                                                    symbolInfo.partId,
                                                                                       symbolInfo.alterId, symbolInfo.frameId,FORMAT_PARAM_END ).c_str() );
            ret->SetNewTextureID(symbolInfo.alterId, symbolInfo.frameId);
//            CCSprite* ret = CCSprite::createWithSpriteFrameName(
//                                                                CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_, 
//                                                                                 m_animationConfig.modelId,
//                                                                                 symbolInfo.partId,
//                                                                                 symbolInfo.alterId,FORMAT_PARAM_END ).c_str() );
            ret->setAnchorPoint( 
            ccp(
                symbolInfo.offset.x / 2.0f / (ret->getContentSize().width * m_animationConfig.lessScale),
                (ret->getContentSize().height * m_animationConfig.lessScale - symbolInfo.offset.y / 2.0f) / (ret->getContentSize().height * m_animationConfig.lessScale)
            ) );
            ret->setTag( partId );
            return ret;
        }
    }
    return NULL;
}


void FlccMovieClip::setAction( const std::string& actionName, bool loop, bool restart )
{
    if ( getAction() == actionName )
    {
        if ( restart ) m_curFrame  = 0;
        m_loop      = loop;
        return;
    }
    
    
    if ( m_curAction != NULL )
    {
        // remove previous action parts
        std::map<uint16, FlccSpriteNode*>::iterator it = m_partSpriteMap.begin();
        for (; it != m_partSpriteMap.end(); it++) {
            if ( !it->second) continue;
            m_content->removeChild( it->second, true );
//            m_partSpriteMap.erase( it );
        }
        m_partSpriteMap.clear();
        
//        FOR_EACH( PartInfo, partInfo, std::vector<PartInfo>, m_curAction->parts )
//        {
//            for (int i = 0; i < partInfo.frames.size(); i++) {
//                removePart( partInfo.partId, partInfo.frames[i].frameId);
//            }
//            
//        }
    }
    
//    if ( m_content )
//    {
//        m_content->removeAllChildrenWithCleanup( true );
//        //            this->removeChild( m_content, true );
//    }
    
    FOR_EACH( ActionInfo, actionInfo, std::vector<ActionInfo>, m_animationConfig.actions )
    {
        if ( actionInfo.name == actionName )
        {
            m_curAction = &actionInfo;
            m_curFrame  = 0;
            m_loop      = loop;
            
//            int zOrder = 1;
            FOR_EACH( PartInfo, partInfo, std::vector<PartInfo>, m_curAction->parts )
            {
                std::map<uint8, uint8>::iterator it = m_partAlterMap.find( partInfo.partId );
                if ( it == m_partAlterMap.end() )
                {
                    // the hero doesn't has this part, ignore
                    continue;
                }
                
                FlccSpriteNode* prtSprite = createSpriteWithPartAndAlter( partInfo.partId, it->second, partInfo.frames[m_curFrame].frameId );
//                CCLog("hero id :%d \naction name:%s \npartID:%d \n",  m_heroId ,actionName.c_str(),partInfo.partId);
//#ifdef WIN32
				if(prtSprite == NULL){
					char buffer[128]={0};
					snprintf(buffer ,128 , "hero id :%d \naction name:%s \npartID:%d \n", m_heroId ,actionName.c_str(),partInfo.partId);
					CCMessageBox("ERROR",buffer);
                    return;
				}
//#else
//				CCAssert( prtSprite != NULL, "Load Hero Part Error" );
//#endif
                
                
                addPart( partInfo.partId, partInfo.frames[m_curFrame].frameId , prtSprite, partInfo.zOrder);
            }
            
            updateMovieClip();
            
            return;
        }
    }
    
//    CCAssert( false, "Action Name Not Found : " + actionName );
}

bool FlccMovieClip::changePart(std::map<uint8, uint8> &partMap)
{
    std::map<uint8, uint8>::iterator it = partMap.begin();
    while ( it != partMap.end() )
    {
        //if ( m_partAlterMap.find( it->first ) == m_partAlterMap.end() ) return false;
        
        setPart( it->first, it->second );
        
        ++it;
    }
    return true;
}

void FlccMovieClip::useDefaultPart()
{
//    FOR_EACH( SymbolInfo, symbolInfo, std::vector<SymbolInfo>, m_animationConfig.symbols )
//    {
//        setPart( symbolInfo.partId, 1 );
//    }
}

void FlccMovieClip::setPart(uint8 partId, uint8 alterId)
{
    std::map<uint8, uint8>::iterator it = m_partAlterMap.find( partId );
    if ( it == m_partAlterMap.end() )
    {
        m_partAlterMap.insert( std::make_pair(partId, alterId) );
    }
    else if ( it->second == alterId ) 
    {
        return;
    }
    else
    {
        //经过查看，发现此处只在初始化的时候用到，所以默认换装id为1}
        std::map<uint16, FlccSpriteNode*>::iterator s_it = m_partSpriteMap.find( getSpriteId(partId, 1) );
        if ( s_it != m_partSpriteMap.end() )
        {
            CCAssert( s_it->second->getParent() != NULL, "Sprite in m_partSpriteMap should on stage");
            // if this part has already on stage, replace sprite
            FlccSpriteNode* newPart = createSpriteWithPartAndAlter(partId, alterId,1);
            
            int zOrder = s_it->second->getZOrder();
            
            removePart( partId , 1);
            addPart( partId, 1, newPart, zOrder );
            updateMovieClip();
        }
        it->second = alterId;
    }
}

void FlccMovieClip::addPart(uint8 partId, uint8 frameId, FlccSpriteNode *prtSprite, int zOrder )
{
//    if (partId == 7) {
//        CCLOG("Seven!!");
//    }
    prtSprite->setTag( partId );
    m_partSpriteMap.insert( std::make_pair(getSpriteId(partId, frameId), prtSprite) );
    m_content->addChild( prtSprite, zOrder );
}

void FlccMovieClip::removePart(uint8 partId, uint8 frameId)
{
    std::map<uint16, FlccSpriteNode*>::iterator it = m_partSpriteMap.find(getSpriteId(partId, frameId));
    if ( it == m_partSpriteMap.end() ) return;
    
    m_content->removeChild( it->second, true );
    m_partSpriteMap.erase( it );
}

FlccSpriteNode* FlccMovieClip::ChangeSpriteTexture( FlccSpriteNode * psprite, uint8 partId, uint8 alterId, uint8 frameId, uint8 zorder)
{
    if (psprite) {
        psprite->setVisible(false);
    }
//    int zorder = psprite->getZOrder();

    if (m_partSpriteMap.find(getSpriteId(partId, frameId)) != m_partSpriteMap.end()) {
        psprite = m_partSpriteMap[getSpriteId(partId, frameId)];
        psprite->setVisible(true);
    }
    else
    {
        // 下面这段没有用，但是为了防止pFrame没有导致crash}
        std::string str = CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_, m_modelId, partId, alterId, frameId, FORMAT_PARAM_END );
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.c_str());

        if (!pFrame) {
            CCLog("%s not found, pFrame", str.c_str());
            return NULL;
        }
        
        
        
        psprite = createSpriteWithPartAndAlter(partId, alterId, frameId);
        addPart(partId, frameId, psprite, zorder);
    }
    
    return psprite;
    
//    psprite->SetNewTextureID(alterId, frameId);
//    std::string str = CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_,8, partId, alterId, frameId, FORMAT_PARAM_END );
//    CCLog("%s",str.c_str());
//    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.c_str());
//    
//    if (!pFrame) {
//        
//        return false;
//    }
//    
//    psprite->initWithSpriteFrame(pFrame);
//    addPart(partId, psprite, zorder);
    
    
    FOR_EACH_CONST( SymbolInfo, symbolInfo, std::vector<SymbolInfo>, m_animationConfig.symbols )
    {
        if ( symbolInfo.partId == partId && symbolInfo.alterId == alterId && symbolInfo.frameId == frameId )
        {
            psprite->setAnchorPoint( ccp( symbolInfo.offset.x / 2.0f / psprite->getContentSize().width,
                                         (psprite->getContentSize().height - symbolInfo.offset.y / 2.0f) / psprite->getContentSize().height
                                         )
                                    );
//            return true;
        }
    }
//    return true;
//    // 检查资源是否存在}
//    std::string filename = CUtil::StrFormat( _FLCC_SPRITE_FRAME_NAME_, partId, alterId, actId, frameId, FORMAT_PARAM_END );
//    std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename.c_str());
//    bool isExist = CCFileUtils::sharedFileUtils()->isFileExist(fullpath);
//    if ( ! isExist )
//    {
//        // 资源不存在，不做改变}
//        return false;
//    }
//    else
//    {
//        psprite->initWithFile(filename.c_str());
//		psprite->setCascadeColorEnabled(true);
//		psprite->setColor(ccWHITE);
//        FOR_EACH_CONST( SymbolInfo, symbolInfo, std::vector<SymbolInfo>, m_skeleton->symbols )
//        {
//            if ( symbolInfo.partId == partId && symbolInfo.actId == actId && symbolInfo.frameId == frameId )
//            {
//                psprite->setAnchorPoint( ccp( symbolInfo.offset.x / 2.0f / psprite->getContentSize().width,
//                                             (psprite->getContentSize().height - symbolInfo.offset.y / 2.0f) / psprite->getContentSize().height
//                                             )
//                                        );
//            }
//        }
//        return true;
//    }
}

void FlccMovieClip::updateMovieClip()
{
    if ( m_curAction == NULL ) return;
    
    uint16 oriCurFrame = m_curFrame;
    
    if ( m_curFrame >= m_curAction->totalFrame )
    {
        if ( m_curAction->totalFrame > 0 )
        {
            m_curFrame = m_curAction->totalFrame - 1;
        }
        else
        {
            return;
        }
    }
    
    m_playing = true;
    
    // resize movieclip
    float lx = 9999.0, rx = -9999.0, ty = -9999.0, by = 9999.0;
    
    FOR_EACH( PartInfo, partInfo, std::vector<PartInfo>, m_curAction->parts )
    {
        FrameInfo& fOld = partInfo.frames[ m_oldFrame ];
        if (m_partSpriteMap.find(getSpriteId(partInfo.partId, fOld.frameId)) == m_partSpriteMap.end())
        {
            continue;
        }
        
        FlccSpriteNode* prtSprite = m_partSpriteMap[ getSpriteId(partInfo.partId, fOld.frameId) ];
        FrameInfo& f = partInfo.frames[ m_curFrame ];
        if (prtSprite->NeedChangeTexture(f.alterId, f.frameId))
        {
            prtSprite = ChangeSpriteTexture(prtSprite, partInfo.partId, m_partAlterMap.find(partInfo.partId)->second, f.frameId, partInfo.zOrder);
            if (!prtSprite) {
                continue;
            }
//            FlccSpriteNode* newPart = createSpriteWithPartAndAlter(partInfo.partId, f.alterId, f.frameId);
            
//            prtSprite = newPart;
        }
        
        prtSprite->setMatrix( f.a * m_animationConfig.lessScale,
                             -f.b * m_animationConfig.lessScale,
                             -f.c * m_animationConfig.lessScale,
                             f.d * m_animationConfig.lessScale,
                             f.tx / 2.0f,
                             -f.ty / 2.0f);
        //if ( m_childAlphaEnable ) prtSprite->setOpacity( (GLubyte)(f.alpha * 255) );
        prtSprite->setOpacity( (GLubyte)(f.alpha * m_FlccAlpha) );
        prtSprite->setDirtyRecursively( true ); // batch node 
        
        CCRect bound = prtSprite->boundingBox();
        
        lx = MIN( lx, bound.origin.x );
        rx = MAX( rx, bound.origin.x + bound.size.width );
        by = MIN( by, bound.origin.y );
        ty = MAX( ty, bound.origin.y + bound.size.height );
        
//        CCPoint pos = ccp( f.tx / 2.0f, -f.ty / 2.0f );
//        float yMax = pos.y + prtSprite->getContentSize().height - prtSprite->getAnchorPointInPoints().y;
//        float yMin = pos.y - prtSprite->getAnchorPointInPoints().y;
//        float xMax = pos.x + prtSprite->getContentSize().width - prtSprite->getAnchorPointInPoints().x;
//        float xMin = pos.x - prtSprite->getAnchorPointInPoints().x;
//        
//        
//        CCLog( "[%.1f %.1f %.1f %.1f] [%.1f %.1f %.1f %.1f]", bound.origin.x, bound.origin.y, bound.size.width, bound.size.height, xMin, xMax, yMin, yMax );
//        
//        lx = MIN(lx, xMin);
//        rx = MAX(rx, xMax);
//        by = MIN(by, yMin);
//        ty = MAX(ty, yMax);
    }
    
    m_rect = CCRectMake( m_obPosition.x + lx, m_obPosition.y + by, rx - lx, ty - by );
    setContentSize( CCSizeMake( rx - lx, ty - by ) );
    m_oldFrame = m_curFrame;
    m_curFrame = oriCurFrame;
}

void FlccMovieClip::updateMovieClip(float time)
{
    if ( m_curAction == NULL ) return;
    if ( m_curFrame >= m_curAction->totalFrame ) return;
    if ( (m_frameCT = m_frameCT + time) < m_frameTT ) return;
    
    int pass = int( m_frameCT / m_frameTT );
    
    m_frameCT -= pass * m_frameTT;
    m_curFrame += pass;
    
    if ( m_curFrame >= m_curAction->totalFrame && m_loop )
    {
        m_curFrame = 0;
    }
    else if ( m_curFrame >= m_curAction->totalFrame )
    {
        m_playing = false;
    }
    
    this->updateMovieClip();
}

float FlccMovieClip::secondPerFrame()
{
    return m_frameTT;
}

uint16 FlccMovieClip::getTotalFrameOf( const std::string& actionName )
{
    FOR_EACH( ActionInfo, actionInfo, std::vector<ActionInfo>, m_animationConfig.actions )
    {
        if ( actionInfo.name == actionName )
        {
            return actionInfo.totalFrame;
        }
    }
    
    return 0;
}

void FlccMovieClip::setFPS(uint16 fps)
{
    m_fps = fps;
    
    m_frameTT = 1.0 / m_fps;
}

uint16 FlccMovieClip::getFPS()
{
    return m_fps;
}

uint16 FlccMovieClip::getCurrentFrame()
{
    return m_curFrame;
}

uint16 FlccMovieClip::getTotalFrame()
{
    if ( m_curAction == NULL ) return 0;
    return m_curAction->totalFrame;
}

bool FlccMovieClip::getLoop()
{
    return m_loop;
}
void FlccMovieClip::setLoop(bool value)
{
    m_loop = value;
}

int8 FlccMovieClip::getDirection()
{
    return m_direction;
}

void FlccMovieClip::setDirection( int8 value )
{
    m_direction = value;
    this->setScaleX( -m_direction );
}

const std::string& FlccMovieClip::getAction()
{
    if ( m_curAction == NULL )
    {
        return NO_ACTION;
    }
    return m_curAction->name;
}

void FlccMovieClip::setOpacity( GLubyte var )
{
    //m_childAlphaEnable = false;
    m_FlccAlpha = var;
    CCSprite::setOpacity( var );
    
    CCArray* pChildren = getChildren();
    for ( int i = 0; i < pChildren->count(); i++ )
    {
        CCRGBAProtocol* ch = dynamic_cast<CCRGBAProtocol*>( pChildren->objectAtIndex( i ) );
        if ( ch ) 
        {
            ch->setOpacity( var );
        }
    }
    
    updateMovieClip();
    
//    CCArray* pContents = m_content->getChildren();
//    for ( int i = 0; i < pContents->count(); i++ )
//    {
//        CCRGBAProtocol* ch = dynamic_cast<CCRGBAProtocol*>( pContents->objectAtIndex( i ) );
//        if ( ch ) ch->setOpacity( var );
//    }
}

void FlccMovieClip::setColor(const ccColor3B &_color)
{
    //m_childAlphaEnable = false;
    CCSprite::setColor( _color );
    
    CCArray* pChildren = getChildren();
    for ( int i = 0; i < pChildren->count(); i++ )
    {
        CCRGBAProtocol* ch = dynamic_cast<CCRGBAProtocol*>( pChildren->objectAtIndex( i ) );
        if ( ch ) 
        {
            ch->setColor( _color );
        }
    }
    
    CCArray* pContents = m_content->getChildren();
    for ( int i = 0; i < pContents->count(); i++ )
    {
        CCRGBAProtocol* ch = dynamic_cast<CCRGBAProtocol*>( pContents->objectAtIndex( i ) );
        if ( ch )
        {
            ch->setCascadeColorEnabled(true);
            ch->setColor( _color );
        }
    }    
}

CCRect FlccMovieClip::rect()
{
    return m_rect;
}

void FlccMovieClip::runFPSAction(FlccMovieFPSAction *action, FightPetSprite *pet)
{
    m_fpsAction = NULL;
    if (!action) {
        return;
    }
    m_fpsAction = action;
    m_fpsAction->setPosition(ccp(-1000,-1000));
    addChild(m_fpsAction);
    m_fpsAction->startWithTarget();
    m_FightPetSprite = pet;
}

void FlccMovieClip::pauseFPSAction(int pauseFrame)
{
    if (!m_fpsAction) {
        return;
    }
    m_fpsAction->pause(pauseFrame);
}

void FlccMovieClip::resumeFPSAction()
{
    if (!m_fpsAction) {
        return;
    }
    m_fpsAction->pause(0);
}

void FlccMovieClip::stopFPSAction()
{
    if (!m_fpsAction) {
        return;
    }
    m_fpsAction->stop();
}


void FlccMovieClip::callBackFPSAction()
{
    if (m_FightPetSprite) {
        m_FightPetSprite->afterAttact();
    }
}

CCAction* FlccMovieClip::runAction(CCAction *action)
{
    return CCSprite::runAction(action);
};