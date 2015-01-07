//
//  HexagonLayer.h
//  MyGame
//
//  Created by Relvin on 14/11/25.
//
//

#ifndef __MyGame__HexagonLayer__
#define __MyGame__HexagonLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class HexagonLayer
: public CCLayer
{
public:
    CREATE_FUNC(HexagonLayer);
    HexagonLayer();
    virtual bool init();
    
    virtual void draw();
    
    CC_SYNTHESIZE(int , m_nPointNum, NumberOfPoints);
    CC_SYNTHESIZE(ccColor4F, m_color, Color);
    void setEachPoints( CCPoint Point[]);
private:
    cocos2d::CCPoint arrPoint[6];
    
};

#endif /* defined(__MyGame__HexagonLayer__) */
