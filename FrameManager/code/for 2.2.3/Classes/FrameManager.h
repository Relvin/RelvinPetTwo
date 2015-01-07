/****************************************************************************
 for cocos2d-x 2.2.3

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _FRAME_MANAGER_H_
#define _FRAME_MANAGER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

//�������ڶԻ������ʱ��Ļص�����
typedef void (cocos2d::CCObject::*SEL_TouchOutOfFrameEvent)(cocos2d::ui::Widget*);
#define TouchOutOfFrameEvent_selector(_SELECTOR) (SEL_TouchOutOfFrameEvent)(&_SELECTOR)

/**
 *  �Ի��������
 *  ����:�����cocostudio�����ĶԻ���UI������
 *       ��������λ���ڶԻ���֮�⣬�Զ����ضԻ��򣬲�ʹ���ڲ��ؼ����ɴ���
 */
class FrameManager : public cocos2d::CCObject,public cocos2d::CCTargetedTouchDelegate 
{
public:
	FrameManager();
	~FrameManager(){}

	/**
	 * ����Ի���ĸ��ڵ�ͱ����ڵ�
	 *@param frameLayer �Ի��������
	 *@param frameBg �Ի���ı����ڵ�,�������жϴ����Ƿ��ڶԻ�����
	 */
	bool setFrame(cocos2d::ui::Widget* frameLayer,cocos2d::ui::Widget* frameBg);

	void setFrameVisible(bool bVisible);

	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	cocos2d::ui::Widget* getFrameLayer() {return m_frameLayer;}

	void setTouchOutOfFrameEventListener(cocos2d::CCObject* target,SEL_TouchOutOfFrameEvent selector)
	{
		m_eventTarget   = target;
		m_eventSelector = selector;
	}

protected:
	cocos2d::ui::Widget*  m_frameLayer;
	cocos2d::ui::Widget*  m_frameBg;
	cocos2d::CCSize   m_frameSize;
	cocos2d::CCPoint  m_anchorPoint;  ///<ê���ڱ�������ϵ������,���귶Χ��(0.0f,0.0f)��m_frameSize
	bool m_bFrameVisible;

	cocos2d::CCObject* m_eventTarget;
	SEL_TouchOutOfFrameEvent m_eventSelector;

	///���öԻ����Ƿ�ɼ���ͬʱ���öԻ����еĿؼ��Ƿ�ɴ���(��ֹ�Ի��򲻿ɼ�,���ؼ����յ�������Ϣ)
	void setChildrenTouchEnabled(cocos2d::CCNode* pNode, bool bTouchEnabled);

	bool isOutsideFrame(cocos2d::CCTouch *pTouch);
};

#endif