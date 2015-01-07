//
//  PetBattleLodingScene.h
//  HelloWorld
//
//  Created by long on 13-9-13.
//
//

#ifndef __HelloWorld__PetLoadingLayer__
#define __HelloWorld__PetLoadingLayer__

#include <iostream>
#include "cocos2d.h"
#include "WorldPacket.h"
#include "SystemMessage.h"
USING_NS_CC;

const static int MAX_WAITING = 12;

class PetLoadingLayer : public CCLayer
,   public SystemMessageProtocol
{
public:
    PetLoadingLayer() {
        
    };
    ~PetLoadingLayer(){
        m_pShared->release();
    }

    static PetLoadingLayer* sharedLayer(){
        if (!m_pShared)
        {
            m_pShared = PetLoadingLayer::create();
            m_pShared->retain();
        }
        return m_pShared;
    };
        
    CREATE_FUNC(PetLoadingLayer);
    
    bool init();
    
    void onEnter();
    void onExit();

    /*!
     是否需要延时加载，默认为false, 需要延时加载则传入true.}
     */
    void WaitForPacket(bool _delay = false);
    
    void End();
    
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void updateSelf(float dTime);
    
    void CoverCouched();
    
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
private:
    static PetLoadingLayer *m_pShared;
    int referenceCnt;   //多个网络协议需要多个回包时使用}

    int m_nRetainCnt;
    bool m_bDelay;
    CCSize winSize;
    
    void addLoadLayer();
};

#endif /* defined(__HelloWorld__PetBattleLodingScene__) */
