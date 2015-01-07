//
//  HexagonLayer.cpp
//  MyGame
//
//  Created by Relvin on 14/11/25.
//
//

#include "HexagonLayer.h"

HexagonLayer::HexagonLayer()
{
    memset(arrPoint, 0, sizeof(arrPoint));
}

bool HexagonLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    

    return true;
}

void HexagonLayer::draw()
{
    CCLayer::draw();
    
    glLineWidth(1);
    ccDrawSolidPoly(arrPoint, m_nPointNum, m_color);
}

void HexagonLayer::setEachPoints( CCPoint Point[])
{
    memcpy(arrPoint, Point, sizeof(arrPoint));
    
}