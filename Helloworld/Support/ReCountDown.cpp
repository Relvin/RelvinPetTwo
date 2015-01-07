//
//  ReCountDown.cpp
//  MyGame
//
//  Created by Relvin on 14/11/4.
//
//

#include "ReCountDown.h"
#include "Instruments.h"

USING_NS_CC;

void ReCountDownDelegate::countDownScheduleCallBack(float cTime,CountType type)
{
    
}

// R倒e计时
ReCountDown::ReCountDown()
: _label(NULL)
, time(0)
, m_pDelegate(NULL)
{
    
}

ReCountDown::~ReCountDown()
{
    
}

ReCountDown* ReCountDown::create()
{
    return ReCountDown::create(NULL);
}

ReCountDown* ReCountDown::create(CCLabelTTF* object)
{
    ReCountDown* node = new ReCountDown();
    if(node)
    {
        node->initCountDownNode(object);
        node->autorelease();
    }
    return node;
}

/**
 * 附加一个Agent Label:
 */
void ReCountDown::initCountDownNode(CCLabelTTF* object)
{
    _label = object;
}

void ReCountDown::setTime(int ttime)
{
    time = ttime ;
}

void ReCountDown::onEnter()
{
    CCNode::onEnter();
    
}

void ReCountDown::onExit()
{
    this->stopUpdateCountDown();
    CCNode::onExit();
}

void ReCountDown::startUpdateCountDown()
{
    int nTime = time - getLocalCurTimeSec();
    if (nTime <= 0) {
        if (m_pDelegate) {
            m_pDelegate->countDownScheduleCallBack(nTime,ReCountDownDelegate::ENUM_COMPLETE);
        }
        return;
    }
    else
    {
        if (m_pDelegate) {
            m_pDelegate->countDownScheduleCallBack(nTime,ReCountDownDelegate::ENUM_START);
        }
    }
    this->stopUpdateCountDown();
    this->scheduleCountDown(0);
    this->schedule(schedule_selector(ReCountDown::scheduleCountDown), 1.0f);
}

void ReCountDown::scheduleCountDown(float cTime)
{
    int tmpTime = time - getLocalCurTimeSec();
    
    if (tmpTime < 0)
    {
        this->stopUpdateCountDown();
        tmpTime = 0;
        this->updateCountDown(0);
        if (m_pDelegate) {
            m_pDelegate->countDownScheduleCallBack(time,ReCountDownDelegate::ENUM_COMPLETE);
        }
        return;
    }
    this->updateCountDown(tmpTime);

}

void ReCountDown::updateCountDown(float cTime)
{
    if (_label) {
        _label->setString(getLeftTimeFromInt(cTime)->getCString());
    }
    if (m_pDelegate) {
        m_pDelegate->countDownScheduleCallBack(cTime,ReCountDownDelegate::ENUM_UPDATE);
    }

}

void ReCountDown::stopUpdateCountDown()
{
    this->unschedule(schedule_selector(ReCountDown::updateCountDown));
}
