/****************************************************************************
 for cocos2d-x 3.2

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _FRAME_MANAGER_H_
#define _FRAME_MANAGER_H_

#include "cocos2d.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

//�������ڶԻ������ʱ��Ļص�����
typedef void (cocos2d::Ref::*SEL_TouchOutOfFrameEvent)(cocos2d::ui::Widget*);
#define TouchOutOfFrameEvent_selector(_SELECTOR) (SEL_TouchOutOfFrameEvent)(&_SELECTOR)

/**
 *  �Ի��������
 *  ����:�����cocostudio�����ĶԻ���UI������
 *       ��������λ���ڶԻ���֮�⣬�Զ����ضԻ��򣬲�ʹ���ڲ��ؼ����ɴ���
 */
class FrameManager : public cocos2d::Ref
{
public:
	FrameManager();
	~FrameManager()
	{
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(m_touchListener);
	}

	/**
	 * ����Ի���ĸ��ڵ�ͱ����ڵ�
	 *@param frameLayer �Ի��������
	 *@param frameBg �Ի���ı����ڵ�,�������жϴ����Ƿ��ڶԻ�����
	 */
	bool setFrame(cocos2d::ui::Widget* frameLayer,cocos2d::ui::Widget* frameBg);

	void setFrameVisible(bool bVisible);

	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	cocos2d::ui::Widget* getFrameLayer() {return m_frameLayer;}

	void setTouchOutOfFrameEventListener(cocos2d::Ref* target,SEL_TouchOutOfFrameEvent selector)
	{
		m_eventTarget   = target;
		m_eventSelector = selector;
	}

	void setTouchOutOfFrameEventListener(std::function<void(cocos2d::ui::Widget*)> callback)
	{
		m_eventCallback = callback;
	}

protected:
	cocos2d::ui::Widget*  m_frameLayer;
	cocos2d::ui::Widget*  m_frameBg;
	cocos2d::Size   m_frameSize;
	cocos2d::Point  m_anchorPoint;  ///<ê���ڱ�������ϵ������,���귶Χ��(0.0f,0.0f)��m_frameSize
	bool m_bFrameVisible;
	cocos2d::EventListenerTouchOneByOne* m_touchListener;
	std::function<void(cocos2d::ui::Widget*)> m_eventCallback;

	cocos2d::Ref* m_eventTarget;
	SEL_TouchOutOfFrameEvent m_eventSelector;

	///���öԻ����Ƿ�ɼ���ͬʱ���öԻ����еĿؼ��Ƿ�ɴ���(��ֹ�Ի��򲻿ɼ�,���ؼ����յ�������Ϣ)
	void setChildrenTouchEnabled(cocos2d::Node* pNode, bool bTouchEnabled);

	bool isOutsideFrame(cocos2d::Touch *pTouch);
};

#endif