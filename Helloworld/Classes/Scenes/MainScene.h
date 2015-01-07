/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-08-29 18:06:24
*/

#ifndef __MAINSCENE__H__
#define __MAINSCENE__H__

#include "cocos2d.h"

class MainScene:
	public cocos2d::CCLayer
{
public:
	// Constructor
	MainScene() {
	}
	~MainScene();

	// must have
	static cocos2d::CCScene* scene();

    CREATE_FUNC(MainScene);

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
	
private:
    void addGuide();
};


#endif // __MAINSCENE__H__