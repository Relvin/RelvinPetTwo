//
//  GuideLayer.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-3-12.}
//
//

#ifndef __HelloWorld__GuideLayer__
#define __HelloWorld__GuideLayer__

#include "cocos2d.h"
#include "GuideData.h"

class GuideLayer : public cocos2d::CCLayer {

public:
    // 根据groupId播放引导}
    void playGuide(GuideData::STC_DIALOG dialog);
    
    CREATE_FUNC(GuideLayer);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();

    GuideLayer();
    virtual ~GuideLayer();
private:
    cocos2d::CCSize winSize;
    void skip(cocos2d::CCObject *pSender);
};

#endif /* defined(__HelloWorld__GuideLayer__) */
