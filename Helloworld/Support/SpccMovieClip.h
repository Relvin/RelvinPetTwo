#ifndef __SPCC_MOVIE_CLIP_H__
#define __SPCC_MOVIE_CLIP_H__

#include "SpccData.h"
#include "cocos2d.h"
#include "ResourceDefine.h"

#define _SPCC_CONFIG_FILE_PATH_     EFFECT_SPCC
#define _SPCC_TEXTURE_FILE_PATH_    EFFECT_TEXTURE
#define _SPCC_PLIST_FILE_PATH_      EFFECT_PLIST
#define _SPCC_SPRITE_FRAME_NAME_    EFFECT_SPRITE_FRAME
#define _SPCC_SPRITE_FILE_NAME_     EFFECT_SPRITE_FILE

USING_NS_CC;

class SpccMovieFPSAction;

class SpccMovieClip : public CCSprite
{
public:
    static SpccMovieClip* create( uint32 dwId, int8 byDirection = 1, bool bMultiPng = false );
    
//    static SpccMovieClip* createByPetId( uint16 petId, int8 byDirection = 1, bool bMultiPng = false );
    
public:
    
    SpccMovieClip();
    virtual ~SpccMovieClip();
    
    void setFrameIdx( uint16 wFrameIdx );
    
    uint16 getTotalFrame();
    
    uint16 getCurFrame(){return m_wCurFrame;};
    
//    void runFPSAction();
    
    //按帧执行的动画}
    void runFPSAction(SpccMovieFPSAction *action);
    //暂停动画（pauseFrame为暂停的帧数，-1表示一直暂停下去）}
    void pauseFPSAction(int pauseFrame);
    //恢复动画}
    void resumeFPSAction();
    //停止动画}
    void stopFPSAction();
    
protected:
    bool initWithSpccId( uint32 dwId, int8 byDirection, bool bMultiPng );
    
    SpccEffectConfig    m_effectConfig;
    int8                m_direction;
    CCSprite*           m_pContent;
    uint32              m_dwId;
    uint16              m_wCurFrame;
    bool                m_bMultiPng;
    bool                m_bSD;
    
    SpccMovieFPSAction *m_fpsAction;
};


#endif
