//
//  ScrollNoticeLayer.h
//  MyGame
//
//  Created by Relvin on 14/10/30.
//
//

#ifndef __MyGame__ScrollNoticeLayer__
#define __MyGame__ScrollNoticeLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "WorldPacket.h"

class ScrollNoticeLayer
: public cocos2d::CCLayer
{
public:
    
    static ScrollNoticeLayer* shareInstance();
    void purgeScrollNotice();
    
    void showScrollNotice(const char * text);
    
    CREATE_FUNC(ScrollNoticeLayer);
    ScrollNoticeLayer();
    virtual ~ScrollNoticeLayer();
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    
    //
    void afterScrollOverCallBack(CCObject *pObject);
    
    void scheduleToHide(float cTime);
    
    void listenNotificationCallBack(CCObject *pObject);
private:
    cocos2d::extension::CCScrollView* m_pScrollView;
    CCNode*   m_pLastShowText;
    int  scrollIndex;
    
    
};

#endif /* defined(__MyGame__ScrollNoticeLayer__) */
