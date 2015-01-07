//
//  EffectLayer.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-2-25.}
//
//

#ifndef __HelloWorld__EffectLayer__
#define __HelloWorld__EffectLayer__

#include <iostream>
#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;

class EffectLayerProtocol {
    
public:
    virtual void onActionOver();
};

class EffectLayer : public CCLayer {
    
public:
    EffectLayer();
    ~EffectLayer();
    
     //loop重复次数，默认一次，负数为无限循环}
    static EffectLayer* create(uint16 effectId);
    static EffectLayer* create(uint16 effectId, float fps);
    static EffectLayer* create(uint16 effectId, int loop, float fps);
    
    bool init(uint16 effectId, int loop, float fps);
    
    virtual void onEnter();
    void setDelegate(EffectLayerProtocol* _delegate);

    float getDuring(){return m_fDuring;};
    void onRun();
    void setInterval(float interval){m_interval = interval;};
    
    //设置图片为additive模式}
    void setSpriteAdd();
    
    CCSprite* getSprite(){
        CCSprite* pSprite = dynamic_cast<CCSprite*>(getChildByTag(11));
        if (pSprite) {
            return pSprite;
        }
        return NULL;
    };
private:
    uint16 m_wEffectId;
    EffectLayerProtocol* delegate;
    CCActionInterval* m_pSeq;
    int m_loop;
    float m_fps;
    float m_fDuring;
    float m_interval;
    void onOver();
    std::string strPlist;
};

#endif /* defined(__HelloWorld__EffectLayer__) */
