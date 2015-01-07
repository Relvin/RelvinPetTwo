//
//  FriendMiddleSuggestLayer.h
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/21.
//
//

#ifndef __MyGame__FriendMiddleSuggestLayer__
#define __MyGame__FriendMiddleSuggestLayer__

#include "FriendMiddleBaseLayer.h"

class CcbFriendCntLayer;
class CcbFindFriendLayer;
class FriendMiddleSuggestLayer : public FriendMiddleBaseLayer
{
    
public:
    FriendMiddleSuggestLayer() {
    }
    
    virtual ~FriendMiddleSuggestLayer() {
        
    }
    
    static FriendMiddleSuggestLayer* create(cocos2d::CCSize size);
    
    virtual bool init(cocos2d::CCSize size);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual void reloadTableData();
    
    // CCTableViewDelegate
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView* table, unsigned int idx);
    
private:
    CcbFriendCntLayer* m_pLayerFriendCnt;
    CcbFindFriendLayer* m_pLayerFindFriend;
};

#endif /* defined(__MyGame__FriendMiddleSuggestLayer__) */
