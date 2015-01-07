//
//  DropItemSprite.h
//  HelloWorld
//
//  Created by long on 13-9-11.
//
//

#ifndef __HelloWorld__DropItemSprite__
#define __HelloWorld__DropItemSprite__

#include <iostream>
#include "cocos2d.h"
#include "PetBattleData.h"

USING_NS_CC;

class DropItemSprite : public CCSprite
{
public:
    
    DropItemSprite(){};
    ~DropItemSprite();
    
    virtual void onExit();
    
    static DropItemSprite* create(uint32 itemType);
    
    bool init(uint32 itemType);
    
    void runAct();
    
    CC_MY_PROPERTY(STC_ITEM_DROP, m_item, Item);
private:
    CCNode* getItemByType(uint32 itemType);
    
};

#endif /* defined(__HelloWorld__DropItemSprite__) */
