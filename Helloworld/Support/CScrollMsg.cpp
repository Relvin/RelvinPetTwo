//
//  CScrollMsg.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-3-6.}
//
//

#include "CScrollMsg.h"
#include "ResourceDefine.h"
#include "UISupport.h"
//#include "CCScrollView.h"

CScrollMsg::~CScrollMsg()
{
    
}

bool CScrollMsg::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    m_vecLabels.clear();
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    do {
        STC_MSG stcMsg;
        
        stcMsg.pLabelName = CCLabelTTF::create("qqqqqqqqqqqqq甲乙丙丁戊己庚辛壬癸", FONT_FZCQJW, 14);
        stcMsg.pLabelName->setAnchorPoint(ccp(0, 1));
        stcMsg.pLabelName->setPosition(ccp(16, 10));
        
        stcMsg.pLabelInfo = CCLabelTTF::create("子丑寅卯辰巳午未申酉戌亥", FONT_FZCQJW, 14);
        stcMsg.pLabelInfo->setAnchorPoint(ccp(0, 1));
        stcMsg.pLabelInfo->setPosition(ccp(getRight(stcMsg.pLabelName) + 1, getTop(stcMsg.pLabelName)));
        
        stcMsg.pView->setTouchEnabled(false);
        stcMsg.pView->addChild(stcMsg.pLabelName, 1);
        stcMsg.pView->addChild(stcMsg.pLabelInfo, 1);
        addChild(stcMsg.pView);
        stcMsg.bHaveString = false;
        
        m_vecLabels.push_back(stcMsg);
    } while (0);
    m_pTarget = NULL;
    m_fSpeed = 300;
    m_fTotalDis = 0.0f;
        
    return true;
}

float CScrollMsg::addScrollMsg(const char *szName, ccColor3B colorName, const char *szMsg, ccColor3B colorMsg)
{
    int i = 0;
    return 1.0f;
}

void CScrollMsg::updateSelf(float time)
{
    
}

