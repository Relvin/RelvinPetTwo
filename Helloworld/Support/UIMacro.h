#pragma once

#ifndef _UI_MACRO_H_
#define _UI_MACRO_H_

#include "cocos2d.h"

#define SAFE_INIT_AUTORELEASE(t,i) { \
	t* pRet = new t(); \
	if( pRet && (pRet->i) ) { pRet->autorelease(); return pRet; } \
	if( pRet ) delete pRet; \
	return 0; \
}

#define DEF_NODE_RECT_IN_NODE_SPACE \
	cocos2d::CCRect rectInNodeSpace() const { \
		return cocos2d::CCRect( -m_tContentSize.width*m_tAnchorPoint.x, -m_tContentSize.height*m_tAnchorPoint.y, \
			m_tContentSize.width, m_tContentSize.height ); \
	}
#define DEF_NODE_RECT_IN_PARENT_SPACE \
	cocos2d::CCRect rectInParentSpace() const { \
		return cocos2d::CCRect( m_tPosition.x-m_tContentSize.width*m_tAnchorPoint.x, m_tPosition.y-m_tContentSize.height*m_tAnchorPoint.y, \
			m_tContentSize.width, m_tContentSize.height ); \
	}
#define DEF_NODE_RECT_IN_WORLD_SPACE \
	cocos2d::CCRect rectInWorldSpace() { \
		cocos2d::CCRect rc = rectInNodeSpace(); \
		cocos2d::CCPoint rb(rc.origin.x+rc.size.width, rc.origin.y+rc.size.height); \
		return makeRectByTwoPoints( convertToWorldSpace(rc.origin), convertToWorldSpace(rb) ); \
	}
#define DEF_NODE_RECT \
	DEF_NODE_RECT_IN_NODE_SPACE \
	DEF_NODE_RECT_IN_PARENT_SPACE \
	DEF_NODE_RECT_IN_WORLD_SPACE

inline cocos2d::CCRect makeRectByTwoPoints(const cocos2d::CCPoint& p1,const cocos2d::CCPoint& p2) {
	float t;
	cocos2d::CCPoint m1(p1),m2(p2);
	if( m1.x>m2.x ) { t=m1.x;m1.x=m2.x;m2.x=t; }
	if( m1.y>m2.y ) { t=m1.y;m1.y=m2.y;m2.y=t; }
	return cocos2d::CCRect(m1.x, m1.y, m2.x-m1.x, m2.y-m1.y);
}

inline cocos2d::CCRect nodeRectInNodeSpace(cocos2d::CCNode* node) {
	cocos2d::CCPoint t_anchor = node->getAnchorPoint();
	cocos2d::CCSize t_size = node->getContentSize();
	return cocos2d::CCRect( -t_size.width*t_anchor.x, -t_size.height*t_anchor.y, t_size.width, t_size.height );
}

inline cocos2d::CCRect nodeRectInParentSpace(cocos2d::CCNode* node) {
	cocos2d::CCPoint t_pos = node->getPosition();
	cocos2d::CCPoint t_anchor = node->getAnchorPoint();
	cocos2d::CCSize t_size = node->getContentSize();
	return cocos2d::CCRect( t_pos.x-t_size.width*t_anchor.x, t_pos.y-t_size.height*t_anchor.y, t_size.width, t_size.height );
}

inline cocos2d::CCRect nodeRectInWorldSpace(cocos2d::CCNode* node) {
	cocos2d::CCRect rc = nodeRectInNodeSpace(node);
	cocos2d::CCPoint rb(rc.origin.x+rc.size.width, rc.origin.y+rc.size.height);
	return makeRectByTwoPoints( node->convertToWorldSpace(rc.origin), node->convertToWorldSpace(rb) );
}

#endif
