//
//  FriendMiddleEnergyLayer.h
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/22.
//
//

#ifndef __MyGame__FriendMiddleEnergyLayer__
#define __MyGame__FriendMiddleEnergyLayer__

#include "FriendMiddleBaseLayer.h"

class CcbFriendGetAllEnergyLayer;
class CcbFriendGetAllEnergyLayer;
class FriendMiddleEnergyLayer : public FriendMiddleBaseLayer
{
    
public:
    FriendMiddleEnergyLayer() {
        
    }
    virtual ~FriendMiddleEnergyLayer() {
        
    }
    
    static FriendMiddleEnergyLayer* create(cocos2d::CCSize size);
    
    virtual bool init(cocos2d::CCSize size);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual void reloadTableData();
    
    // CCTableViewDelegate
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView* table, unsigned int idx);
    
private:
    CcbFriendGetAllEnergyLayer* m_pLayerGetAllEnergy;
};

#endif /* defined(__MyGame__FriendMiddleEnergyLayer__) */
