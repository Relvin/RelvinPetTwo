/*
 *  untitled.cpp
 *  Untitled
 *
 *  Created by YQ on 11-9-17.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "UISupport.h"

float getWidth(CCNode *node)
{
	return node->boundingBox().size.width;
}

void setWidth(CCNode *node, float width)
{
	node->setScaleX(width / node->getContentSize().width);
}

float getHeight(CCNode *node)
{
	return node->boundingBox().size.height;
}

void setHeight(CCNode *node, float height)
{
	node->setScaleY(height / node->getContentSize().height);
}

float getLeft(CCNode *node)
{
    if (node->isIgnoreAnchorPointForPosition())
    {
        return node->getPosition().x;
    }
	return node->getPosition().x - getWidth(node) * node->getAnchorPoint().x;
}

void setLeft(CCNode *node, float left)
{
    if (node->isIgnoreAnchorPointForPosition())
    {
        node->setPositionX(left);
        return;
    }
	node->setPosition(ccp(left + getWidth(node) * node->getAnchorPoint().x, node->getPosition().y));
}

float getRight(CCNode *node)
{
    if (node->isIgnoreAnchorPointForPosition())
    {
        return node->getPosition().x + getWidth(node);
    }
	return node->getPosition().x + getWidth(node) * (1 - node->getAnchorPoint().x);
}

void setRight(CCNode *node, float right)
{
    if (node->isIgnoreAnchorPointForPosition())
    {
        node->setPositionX(right - getWidth(node));
        return;
    }
	node->setPosition(ccp(right - getWidth(node) * (1 - node->getAnchorPoint().x), node->getPosition().y));
}

float getBottom(CCNode *node)
{
    if (node->isIgnoreAnchorPointForPosition())
    {
        return node->getPosition().y;
    }
	return node->getPosition().y - getHeight(node) * node->getAnchorPoint().y;
}

void setBottom(CCNode *node, float bottom)
{
    if (node->isIgnoreAnchorPointForPosition())
    {
        node->setPositionY(bottom);
        return;
    }
	node->setPosition(ccp(node->getPosition().x, bottom + getHeight(node) * node->getAnchorPoint().y));
}

float getTop(CCNode *node)
{
    if (node->isIgnoreAnchorPointForPosition())
    {
        return node->getPosition().y + getHeight(node);
    }
	return node->getPosition().y + getHeight(node) * (1 - node->getAnchorPoint().y);
}

void setTop(CCNode *node, float top)
{
    if (node->isIgnoreAnchorPointForPosition())
    {
        node->setPositionY(top - getHeight(node));
        return;
    }
	node->setPosition(ccp(node->getPosition().x, top - getHeight(node) * (1 - node->getAnchorPoint().y)));
}

float getCenterX(CCNode *node)
{
	return getLeft(node) + getWidth(node) * 0.5f;
}

void setCenterX(CCNode *node, float x)
{
	node->setPosition(ccp(x + getWidth(node) * (node->getAnchorPoint().x - 0.5f), 
						  node->getPosition().y));
}

float getCenterY(CCNode *node)
{
	return getBottom(node) + getHeight(node) * 0.5f;
}

void setCenterY(CCNode *node, float y)
{
	node->setPosition(ccp(node->getPosition().x,
						  y + getHeight(node) * (node->getAnchorPoint().y - 0.5f)));
}

CCPoint getCenter(CCNode *node)
{
	float x = getCenterX(node);
	float y = getCenterY(node);
	return ccp(x, y);
}

void setCenter(CCNode *node, CCPoint p)
{
	node->setPosition(ccp(p.x + getWidth(node) * (node->getAnchorPoint().x - 0.5f), 
						  p.y + getHeight(node) * (node->getAnchorPoint().y - 0.5f)));
}

void setSize(CCNode *node, CCSize size)
{
	setWidth(node, size.width);
	setHeight(node, size.height);
}

CCSize getSize(CCNode *node)
{
	float width = getWidth(node);
	float height = getHeight(node);
	return CCSize(width, height);
}

void setOrigin(CCNode *node, CCPoint p)
{
	setLeft(node, p.x);
	setBottom(node, p.y);
}

CCPoint getOrigin(CCNode *node)
{
	float x = getLeft(node);
	float y = getBottom(node);
	return ccp(x, y);
}

void setCenterLayer(CCNode *node, CCPoint p)
{
	node->setPosition(ccp(p.x + node->getContentSize().width * (-0.5f), 
						  p.y + node->getContentSize().height * (-0.5f)));
}

CCPoint getWorldPos(CCNode* node)
{
    CCPoint p = getOrigin(node);
    //    CCNode *parent = node;
    while (true)
    {
        if (!node->getParent())
        {
            break;
        }
        node = node->getParent();
        p = ccpAdd(p, getOrigin(node));
    }
    return p;
}