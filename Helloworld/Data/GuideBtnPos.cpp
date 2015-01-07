//
//  GuideBtnPos.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/4.
//
//

#include "GuideBtnPos.h"
#include "UISupport.h"

using namespace std;
USING_NS_CC;

void GuideBtnPos::addNodeWorldPos(cocos2d::CCNode *_node, int _enum, bool _force) {
    CCLOG("add enum:%d", _enum);
    
    MAP_RECT::iterator pIter = m_mapRect.find(_enum);
    if (pIter != m_mapRect.end() && !_force) {
        return;
    } else {
        CCRect rect;
        CCPoint pos = _node->getParent()->convertToWorldSpace(getOrigin(_node));
        CCSize size = _node->getContentSize();
        
        if (_enum == E_TALK_150) {
            pos = ccpAdd(pos, ccp(0, -40));
        }
        
        rect = CCRectMake(pos.x, pos.y, size.width, size.height);
        CCLOG("add enum:%d, rect=[%f, %f, %f, %f] to map", _enum, pos.x, pos.y, size.width, size.height);
        m_mapRect[_enum] = rect;
    }
}

void GuideBtnPos::setWorldRect(int _enum, cocos2d::CCRect _rect) {
    m_mapRect[_enum] = _rect;
}

CCRect GuideBtnPos::worldRectWithEnum(int _enum) {
    MAP_RECT::iterator pIter = m_mapRect.find(_enum);
    
    if (pIter != m_mapRect.end()) {
        return pIter->second;
    }
    
    assert(1);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    return CCRectMake(0, 0, winSize.width, winSize.height);
}
