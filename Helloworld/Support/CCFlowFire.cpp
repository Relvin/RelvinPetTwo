//
//  CCFlowFire.cpp
//  HelloWorld
//
//  Created by long on 14-3-25.
//
//

#include "CCFlowFire.h"
CCFlowFire::CCFlowFire()
{
    m_arrPoint.clear();
}
CCFlowFire::~CCFlowFire()
{
    m_arrPoint.clear();
}

/**
 @brief 默认一个100*100的矩形}
*/
CCFlowFire* CCFlowFire::create()
{
    CCFlowFire* pRet = new CCFlowFire();
    std::vector<CCPoint> arrPoint;
    arrPoint.push_back(ccp(0, 0));
    arrPoint.push_back(ccp(0, 100));
    arrPoint.push_back(ccp(100, 100));
    arrPoint.push_back(ccp(100, 0));
    if (pRet && pRet->init(arrPoint))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

CCFlowFire* CCFlowFire::createCircle(float radius, CCPoint center)
{
    CCFlowFire* pRet = new CCFlowFire();
    if (pRet && pRet->initCircle(radius, center))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}
/**
 @brief arrPoint   必须是大于等于3个点的闭环
*/
CCFlowFire* CCFlowFire::createPolygon(std::vector<CCPoint> arrPoint)
{
    CCFlowFire* pRet = new CCFlowFire();
    if (pRet && pRet->init(arrPoint))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}


bool CCFlowFire::init(std::vector<CCPoint> arrPoint)
{
    if (!CCLayer::init()) {
        return false;
    }
    m_arrPoint.clear();
    m_arrPoint = arrPoint;
    
//    schedule(schedule_selector(CCFlowFire::updateForMove));}
    return true;
}


bool CCFlowFire::initCircle(float radius, CCPoint center)
{
    if (!CCLayer::init()) {
        return false;
    }
    m_radius = 0;
    m_radius = radius;
    m_center = center;
    
    return true;
}

void CCFlowFire::onEnter()
{
    CCLayer::onEnter();
    particle1 = CCParticleSystemQuad::create("ccbresources/12monthdate/universal/kuang.plist");
    
    if (!particle1) {
        return;
    }
    
    addChild(particle1);
    if (m_arrPoint.size() > 0) {
        speed = 200;
        curPoint = 0;
        particle1->setPosition(m_arrPoint[0]);
        
        actionForPolygon();
        return;
    }
    
    if (m_radius > 0) {
        particle1->setPosition(ccp(m_center.x, m_center.y - m_radius));
        particle2 = CCParticleSystemQuad::create("ccbresources/12monthdate/universal/kuang.plist");
        particle2->setPosition(ccp(m_center.x, m_center.y + m_radius));
        addChild(particle2);
        m_fAngle = 360;
        schedule(schedule_selector(CCFlowFire::updateForCircle));
    }
}
void CCFlowFire::onExit()
{
    CCLayer::onExit();
    if (m_radius > 0) {
        schedule(schedule_selector(CCFlowFire::updateForCircle));
    }
}
void CCFlowFire::updateForCircle(float time)
{
    m_fAngle -= 2.0f;
    if (m_fAngle < 0) {
        m_fAngle += 360;
    }
    particle1->setAngle(m_fAngle);
    particle1->setPosition(ccp(m_center.x + cosf(m_fAngle/180 * M_PI)*m_radius,
                            m_center.y + sinf(m_fAngle/ 180 * M_PI)*m_radius));
    
    particle2->setAngle(m_fAngle + 180);
    particle2->setPosition(ccp(m_center.x + cosf((m_fAngle + 180)/180 * M_PI)*m_radius,
                               m_center.y + sinf((m_fAngle + 180)/ 180 * M_PI)*m_radius));
}

void CCFlowFire::actionForPolygon()
{
    int nextPoint = (curPoint+1) % m_arrPoint.size();
    
    float leng = sqrt((m_arrPoint[curPoint].x - m_arrPoint[nextPoint].x) * (m_arrPoint[curPoint].x - m_arrPoint[nextPoint].x)
                      + (m_arrPoint[curPoint].y - m_arrPoint[nextPoint].y) * (m_arrPoint[curPoint].y - m_arrPoint[nextPoint].y));
    
    float time = leng / speed;
    float y = m_arrPoint[curPoint].y - m_arrPoint[nextPoint].y;
    float x = m_arrPoint[curPoint].x - m_arrPoint[nextPoint].x;
    float angle = atan2f(y, x);
    
    angle = angle * 180 / M_PI;
    
    if (angle < 0) {
        angle += 360;
    }
//    if (x < 0 && y < 0) {
//        angle += 180;
//    }
    
    particle1->setAngle(angle);
    particle1->runAction(CCSequence::create(
                                           CCMoveTo::create(time, m_arrPoint[nextPoint]),
                                           CCCallFunc::create(this, callfunc_selector(CCFlowFire::actionForPolygon)),
                                           NULL));
    curPoint = nextPoint;
    
}