//
//  FlccMovieClip.h
//
//  Created by ziRoy on 12-7-10.
//

#ifndef __FlccMovieClip_h__
#define __FlccMovieClip_h__

#include "FlccData.h"
#include "cocos2d.h"
#include "Defines.h"
#include "ResourceDefine.h"

#include <map>

#define _FLCC_CONFIG_FILE_PATH_     PET_FLCC
#define _FLCC_PLIST_FILE_PATH_      PET_PLIST
#define _FLCC_TEXTURE_FILE_PATH_    PET_TEXTURE
#define _FLCC_SPRITE_FRAME_NAME_    PET_SPRITE_FRAME

USING_NS_CC;

class FlccMovieFPSAction;

class FightPetSprite;

class FlccSpriteNode : public CCSprite
{
public:
    static FlccSpriteNode* createWithSpriteFrameName( const char* pszSpriteFrameName );
    
    void setMatrix( float a, float b, float c, float d, float tx, float ty );
    
    bool    NeedChangeTexture( uint8 alterid, uint8 frameid );
    void    SetNewTextureID( uint8 alterid, uint8 frameid );
protected:
    
    virtual CCAffineTransform nodeToParentTransform(void);
    
private:
    float m_fA;
    float m_fB;
    float m_fC;
    float m_fD;
    float m_fTx;
    float m_fTy;
    uint8 m_alterId;
    uint8 m_frameId;
};

class FlccMovieClip : public CCSprite
{
// static
public:
    
    //static FlccMovieClip* create( const char* flccFileName );
    static FlccMovieClip* create( uint32 dwHeroId );
    static FlccMovieClip* create( uint32 dwSkeletonId, std::map<uint8, uint8>& mapPart );
    
public:
    FlccMovieClip();
    virtual ~FlccMovieClip();
    
public:
    // override it to set all parts' opacity
    virtual void setOpacity( GLubyte var );
    virtual void setColor( const ccColor3B& _color );
public:
    
    // use '1' as alterId
    void useDefaultPart();
    // use map of partId -> alterId
    bool changePart( std::map<uint8, uint8>& partMap );
    
    void setAction( const std::string& actionName, bool loop = false, bool restart = true );
    const std::string& getAction();
    
    // hint : you may use CCRepeatForever instead
    bool getLoop();
    void setLoop( bool value );
    
    // dir = 1 >>>
    // dir = -1 <<<
    int8 getDirection();
    void setDirection( int8 value );
    
    void setFPS( uint16 fps );
    uint16 getFPS();
    
    uint16 getModelId();
    
    uint16 getCurrentFrame();
    uint16 getTotalFrame();
    
    float secondPerFrame();
    uint16 getTotalFrameOf( const std::string& actionName );
    
    void updateMovieClip( float dt );
    void updateMovieClip();
    
    CCRect rect();
    
    //按帧执行的动画}
    void runFPSAction(FlccMovieFPSAction *action, FightPetSprite *pet);
    //暂停动画（pauseFrame为暂停的帧数，-1表示一直暂停下去）}
    void pauseFPSAction(int pauseFrame);
    //恢复动画}
    void resumeFPSAction();
    //停止动画}
    void stopFPSAction();
    
//    void setFigthPetSprite(CCCallFunc* callFunc)
//    {
//        callFunc->execute();
////        m_FightPetSprite = pet;
//    }
//    
//    FightPetSprite* getFightPetSprite()
//    {
//        return m_FightPetSprite;
//    }
//
//    CCCallFunc *m_callFunc;
    void callBackFPSAction();
    
    virtual CCAction* runAction(CCAction *action);
    
    CCSpriteBatchNode* getSpriteNode(){return m_content;};
protected:
    
    bool initWithHeroId( uint32 dwHeroId );
    bool initWithModelId( uint32 dwModelId );
    bool initWithSkeletonId( uint32 dwSkeletonId, std::map<uint8, uint8>& mapPart  );
    
    void setPart( uint8 partId, uint8 alterId );
    void removePart( uint8 partId, uint8 frameId );
    void addPart( uint8 partId, uint8 frameId, FlccSpriteNode* prtSprite, int zOrder );
    
    FlccSpriteNode* createSpriteWithPartAndAlter( uint8 partId, uint8 alterId, uint8 frameId );
    FlccSpriteNode* ChangeSpriteTexture( FlccSpriteNode * psprite, uint8 partId, uint8 alterId, uint8 frameId , uint8 zorder);
    
    uint32              m_heroId;
    uint16              m_modelId;  // 模型ID，即为骨骼ID}
    
    CCSpriteBatchNode*  m_content;
    FlccAnimationConfig m_animationConfig;
    ActionInfo*         m_curAction;
    uint16              m_fps;
    uint16              m_curFrame;
    uint16              m_oldFrame;
    bool                m_playing;
    bool                m_loop;
    int8                m_direction;
    
    float               m_frameCT;
    float               m_frameTT;
    
    CCRect              m_rect;
    //bool                m_childAlphaEnable;
    
    uint8               m_FlccAlpha;
    
    static const std::string NO_ACTION;  
    
    // partId <-> partSprite
    std::map<uint16, FlccSpriteNode*>  m_partSpriteMap;
    
    // partId <-> alterId
    std::map<uint8, uint8>      m_partAlterMap;
    
    
    FlccMovieFPSAction *m_fpsAction;
    
    FightPetSprite *m_FightPetSprite;
};


#endif
