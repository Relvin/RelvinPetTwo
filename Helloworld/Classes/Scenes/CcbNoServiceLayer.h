/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-01-20 14:32:15
*/

#ifndef __CCBNOSERVICELAYER__H__
#define __CCBNOSERVICELAYER__H__

//CcbNoServiceLayer.h come from ccb/noservice.ccb

#include "cocos2d.h"
#include "SystemMessageProtocol.h"

USING_NS_CC;

class CcbNoServiceLayer:
	public cocos2d::CCLayer
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbNoServiceLayer()
	{	}
	~CcbNoServiceLayer();

    CREATE_FUNC(CcbNoServiceLayer);
	
private:
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);

	void forceClose(CCObject *pObject);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};


#endif // __CCBNOSERVICELAYER__H__