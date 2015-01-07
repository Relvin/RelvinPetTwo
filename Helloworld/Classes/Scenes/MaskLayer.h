//
//  MaskLayer.h
//  HelloWorld
//
//  Created by long on 13-10-22.
//
//

#ifndef __HelloWorld__MaskLayer__
#define __HelloWorld__MaskLayer__

#include <vector>
#include "cocos2d.h"

class MaskLayer : public cocos2d::CCLayer
{
public:
    MaskLayer();
    virtual ~MaskLayer();
    
    static MaskLayer *create(std::vector<cocos2d::CCRect> arrRect, bool allDark);
    static MaskLayer *create(std::vector<cocos2d::CCRect> arrRect);
    static MaskLayer *create(std::vector<cocos2d::CCRect> arrRect, cocos2d::CCSize contentSize, bool allDark, CCNode *shape);
    
    static MaskLayer *create(CCNode* shape, bool allDark);
    
    bool init(std::vector<cocos2d::CCRect> arrRect, cocos2d::CCSize contentSize, bool allDark, CCNode *shape);
    
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);
private:
    bool m_bDark;
    std::vector<cocos2d::CCRect> m_arrRect;

};

#endif /* defined(__HelloWorld__MaskLayer__) */
