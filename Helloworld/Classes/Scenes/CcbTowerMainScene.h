//
//  CcbTowerMainScene.h
//  MyGame
//
//  Created by jun on 14-7-10.
//
//

#ifndef __MyGame__CcbTowerMainScene__
#define __MyGame__CcbTowerMainScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SystemMessageProtocol.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbTowerMainScene : public CCLayer
,   public SystemMessageProtocol
{
public:
    CcbTowerMainScene();
    ~CcbTowerMainScene();
    
    CREATE_FUNC(CcbTowerMainScene);
    static cocos2d::CCScene* scene();
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    static CcbTowerMainScene* getCurScene();
    
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
};

#endif /* defined(__MyGame__CcbTowerMainScene__) */
