//
//  ParticleSence.h
//  HelloWorld
//
//  Created by long on 13-7-15.
//
//

#ifndef __HelloWorld__ParticleScene__
#define __HelloWorld__ParticleScene__

#include <iostream>
#include "cocos2d.h"
#include "Defines.h"
#include "FlccMovieClip.h"
#include "cocos-ext.h"
USING_NS_CC;
class ParticleScene : public CCLayer, public cocos2d::extension::CCTableViewDataSource//, public cocos2d::extension::CCTableViewDelegate
{
public:
    ParticleScene();
    ~ParticleScene();
    static CCScene *scene();
    CREATE_FUNC(ParticleScene);
    bool init();
    
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);

    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual CCSize cellSizeForTable(cocos2d::extension::CCTableView *table) {
        return CCSizeMake(50, 40);
    };
    void onTab(CCObject *sender);
    void onBack(CCObject *sender);
    
    
//    void onStop();
private:
    CCSprite *imgTest;
    
    std::vector<uint16> arrEffIndex;
    FlccMovieClip* mc;
    std::string getEffPath(std::string idx);
	void onParticle(CCObject *pObject);
};

#endif /* defined(__HelloWorld__ParticleSence__) */
