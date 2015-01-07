//
//  CScrollMsg.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-3-6.}
//
//

#ifndef __HelloWorld__CScrollMsg__
#define __HelloWorld__CScrollMsg__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;


class CScrollMsg : public CCLayer {
    
public:
    typedef struct _STC_MSG {
        CCLabelTTF* pLabelName;
        CCLabelTTF* pLabelInfo;
        bool bHaveString;
        CCScrollView* pView;
    }STC_MSG;
    
    bool init();
    virtual ~CScrollMsg();
    
    CREATE_FUNC(CScrollMsg);
    
    float addScrollMsg(const char* szName, ccColor3B colorName, const char* szMsg, ccColor3B colorMsg);
    
    void updateSelf(float time);
    
private:
    std::vector<STC_MSG> m_vecLabels;
    
    CCScrollView* m_pTarget;
    
    float m_fSpeed;
    float m_fTotalDis;
};

#endif /* defined(__HelloWorld__CScrollMsg__) */
