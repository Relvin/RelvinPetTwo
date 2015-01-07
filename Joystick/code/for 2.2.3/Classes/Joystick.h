/****************************************************************************
 for cocos2d-x 2.2.3

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "cocos2d.h"

enum JoystickEventType{JET_TOUCH_BEGIN,JET_TOUCH_MOVE,JET_TOUCH_END};

//interval��ʱ����,�����x��y�ķ�Χ����0-1.0F,JoystickEventType�����ͣ���ʼ,�ƶ�,������
typedef void (cocos2d::CCObject::*SEL_JoystickEvent)(float interval,float x, float y,JoystickEventType type);
#define joystickEvent_selector(_SELECTOR) (SEL_JoystickEvent)(&_SELECTOR)

/**
 * @brief һ������ҡ����
 *
 * ���ݸ�,�����Ͱ�ť�����Ǿ�����,���ǵ�ê��һֱ����ccp(0.5,0.5)
 * ������setHandleEventListener��������ҡ��ҡ���¼��Ĵ���
 */
class Joystick : public cocos2d::CCNode,public cocos2d::CCTargetedTouchDelegate
{
public:
	Joystick():m_bMove(false){}
	virtual ~Joystick(){}

	/**
	 * ����һ��ҡ��ʵ���ľ�̬����
	 *@param fnBg ����ͼƬ���ļ���,��������ҡ�˵ĵ��̾���
	 *@param bgRadius ҡ�˵ĵ��̵İ뾶
	 *@param fnHandle ҡ��ͼƬ���ļ���,��������ҡ�˾���
	 *@param handleRadius ҡ�˵İ뾶
	 */
	static Joystick* create(const char *fnBg,     float bgRadius,
					        const char *fnHandle, float handleRadius);

	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void onEnter();
	void onExit();

	///����ҡ���ƶ�ʱҪ���õķ������������������Ϊvoid f��float interval, float x, float y��,interval��ʱ�����������x��y�ķ�Χ����0-1.0F
	void setHandleEventListener(cocos2d::CCObject *target, SEL_JoystickEvent selector);

	///�������ÿһ֡��������,���������ҡ���¼��Ĵ���Ļ���������ĸ�������
	void callHandleEvent(float interval);
protected:
	cocos2d::CCSprite* m_bg;        ///<���̵ľ���
	cocos2d::CCSprite* m_handle;    ///<ҡ�˵ľ���

	float m_bgRadius;               ///<���̵İ뾶
	float m_handleRadius;           ///<ҡ�˵İ뾶
	bool  m_bMove;		            ///<ҡ���Ƿ������ƶ�

	cocos2d::CCPoint m_handlePos;   ///<ҡ���ڵ�������ϵ������

	cocos2d::CCObject*  m_touchEventListener;
    SEL_JoystickEvent   m_touchEventSelector;

	bool init(const char *fnBg,     float bgRadius,
			  const char *fnHandle, float handleRadius);
	
};

inline void Joystick::setHandleEventListener(cocos2d::CCObject *target, SEL_JoystickEvent selector)
{
	m_touchEventListener = target;
	m_touchEventSelector = selector;
}

#endif