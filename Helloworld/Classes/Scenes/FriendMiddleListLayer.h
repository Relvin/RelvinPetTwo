//
//  FriendMiddleListLayer.h
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/21.
//
//

#ifndef __MyGame__FriendMiddleListLayer__
#define __MyGame__FriendMiddleListLayer__

#include "FriendMiddleBaseLayer.h"

class CcbFriendCntLayer;
class FriendMiddleListLayer : public FriendMiddleBaseLayer
{
    
public:
    FriendMiddleListLayer() {

    }
    
    virtual ~FriendMiddleListLayer() {
        
    }
    
    static FriendMiddleListLayer* create(cocos2d::CCSize size);
    
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
};

#endif /* defined(__MyGame__FriendMiddleListLayer__) */
