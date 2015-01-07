//
//  FlyTextLayer.h
//  MyGame
//
//  Created by 朱 俊杰 on 14-6-22.}
//
//

#ifndef __MyGame__FlyTextLayer__
#define __MyGame__FlyTextLayer__

#include "cocos2d.h"
#include "Defines.h"
USING_NS_CC;

class FlyTextLayer : public CCLayer {
public:
    enum kTextType {
        kMoneyAdd = 0,  //金钱}
        kEnergyAdd = 21, //体力}
    };
public:
    FlyTextLayer();
    ~FlyTextLayer();
    virtual bool init(uint8 kType, int num, float delay);
    virtual bool init(std::string strText);
    virtual bool init(std::string strText, bool isUp, float delay, float scale);
    virtual void onEnter();
    virtual void onExit();
    
    static FlyTextLayer* create(uint8 kType, int num, float delay);
    static FlyTextLayer* create(std::string strText);
    static FlyTextLayer* create(std::string strText, bool isUp, float delay, float scale);

    /*!Usage
     Sample: FlyTextLayer::showText(FlyTextLayer::kMoneyAdd, 1000);
     */
    static void showText(uint8 kType, int num, float delay = 0);
    /*!
     飘外部传入的字
     */
    static void showTips(std::string strText);
    
    static void showBuffText(std::string strText, bool isUp, CCPoint pos, float delay = 0, float scale = 1.0, CCNode* node = NULL);
private:
    typedef enum {
        kProperty = 0,
        kErrorText,
        kBuffText,
    }kType;
    
    CCLabelBMFont* m_pLabelBMFontText;
    char szBuf[64];
    CCSize winSize;
    
    void destorySelf();
    float m_delay;
    kType t_type;
    
};

#endif /* defined(__MyGame__FlyTextLayer__) */
