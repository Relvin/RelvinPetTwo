/*
 *  UISupport.h
 *  Untitled
 *
 *  Created by YQ on 11-9-15.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __UISUPPORT__H__
#define __UISUPPORT__H__

#include "cocos2d.h"

USING_NS_CC;

float getWidth(CCNode *node);
void setWidth(CCNode *node, float width);

float getHeight(CCNode *node);
void setHeight(CCNode *node, float height);

float getLeft(CCNode *node);
void setLeft(CCNode *node, float left);

float getRight(CCNode *node);
void setRight(CCNode *node, float right);

float getBottom(CCNode *node);
void setBottom(CCNode *node, float bottom);

float getTop(CCNode *node);
void setTop(CCNode *node, float top);

float getCenterX(CCNode *node);
void setCenterX(CCNode *node, float x);

float getCenterY(CCNode *node);
void setCenterY(CCNode *node, float y);

CCPoint getCenter(CCNode *node);
void setCenter(CCNode *node, CCPoint p);

void setSize(CCNode *node, CCSize size);
CCSize getSize(CCNode *node);

void setOrigin(CCNode *node, CCPoint p);
CCPoint getOrigin(CCNode *node);

void setCenterLayer(CCNode *node, CCPoint p);
CCPoint getWorldPos(CCNode* node);

#endif
