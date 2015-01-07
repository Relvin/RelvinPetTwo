//
//  FriendMiddleBaseLayer.h
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/21.
//
//

#ifndef __MyGame__FriendMiddleBaseLayer__
#define __MyGame__FriendMiddleBaseLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

class FriendMiddleBaseLayer : public cocos2d::CCLayer
,   public cocos2d::extension::CCTableViewDataSource
{
    
public:
    FriendMiddleBaseLayer() {
        m_pTableView = NULL;
    }
    
    virtual ~FriendMiddleBaseLayer() {
        
    }
    
    virtual bool init(cocos2d::CCSize size);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual void reloadTableData();
    
    // CCTableViewDelegate
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView* table, unsigned int idx) = 0;
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
protected:
    cocos2d::CCSize m_size;
    cocos2d::CCSize m_tableViewSize;
    cocos2d::CCPoint m_tablePosition;
    cocos2d::CCSize m_frameSize;
    
    cocos2d::extension::CCTableView* m_pTableView;
    int m_nFriendCnt;
};

#endif /* defined(__MyGame__FriendMiddleBaseLayer__) */
