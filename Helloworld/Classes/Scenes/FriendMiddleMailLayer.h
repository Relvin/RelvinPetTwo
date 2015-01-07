//
//  FriendMiddleMailLayer.h
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/22.
//
//

#ifndef __MyGame__FriendMiddleMailLayer__
#define __MyGame__FriendMiddleMailLayer__

#include "FriendMiddleBaseLayer.h"

class FriendMiddleMailLayer : public FriendMiddleBaseLayer
{
    
public:
    FriendMiddleMailLayer() {
        
    }
    virtual ~FriendMiddleMailLayer() {
        
    }
    
    static FriendMiddleMailLayer* create(cocos2d::CCSize size);
    
    virtual bool init(cocos2d::CCSize size);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual void reloadTableData();
    
    // CCTableViewDelegate
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView* table, unsigned int idx);
    
private:

};

#endif /* defined(__MyGame__FriendMiddleMailLayer__) */
