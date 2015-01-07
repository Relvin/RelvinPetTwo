/****************************************************************************
 for cocos2d-x 2.2.3

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _NUMBER_COUNT_H_
#define _NUMBER_COUNT_H_

#include "cocos2d.h"
#include "cocos-ext.h"

/**
 * @brief һ�����ֱ�ǩ����ǿ������
 *
 * ���ܣ������ֱ�ǩ���趨������һ������
 *       ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ���ܹ�����m_increment
 *
 * Ӧ�÷�Χ���������ڷ�������ʾ
 * ���Թ��� cocos2d �� cocos2d::CCLabelAtlas ��
 * �� cocostudio ������ cocos2d::ui::LabelAtlas
 */
class NumberCount : public cocos2d::CCObject
{
public:
	NumberCount();

	void setLabelAtlas(cocos2d::CCLabelAtlas* ccLabelAtlas)   
	{
		m_ccLabelAtlas = ccLabelAtlas;
		m_ccLabelAtlas->setString(cocos2d::CCString::createWithFormat("%d",m_number)->getCString());
	}

	void setLabelAtlas(cocos2d::ui::LabelAtlas* uiLabelAtlas) 
	{
		m_ccLabelAtlas = (cocos2d::CCLabelAtlas*)uiLabelAtlas->getVirtualRenderer();
		m_ccLabelAtlas->setString(cocos2d::CCString::createWithFormat("%d",m_number)->getCString());
	}

	int getNumber(){return m_number;}

	/**
	 * �������ֵ�����m_increment
	 * ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ���ܹ�����m_increment
	 */
	void setIncrement(int increment)   {m_increment   = increment;}

	/**
	 * �������ֵ�����m_increment����ԭ����m_increment���ټ�increment��
	 * ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ���ܹ�����m_increment
	 */
	void addIncrement(int increment)   {m_increment += increment;}

	/**
	 * ��������ÿһ�����ӵ������ľ���ֵm_numberDelta
	 * ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ���ܹ�����m_increment
	 */
	void setNumberDelta(int delta)     {m_numberDelta = abs(delta);}
	
	/**
	 * ��������ÿһ�����ӵ�ʱ����m_timeDelta
	 * ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ���ܹ�����m_increment
	 */
	void setTimeDelta(float timeDelta) {m_timeDelta   = timeDelta;}

	/**
	 * ��������
	 *@param number Ŀ������
	 *@param bGradually �ǲ����ɵ�ǰ����һ��һ�����ӵ�Ŀ������
	 */
	bool setNumber(int number, bool bGradually);

	///schedule����,�������ӵļ����������ʵ��
	void updateNumber(float fInterval);

private:
	cocos2d::CCLabelAtlas* m_ccLabelAtlas;

	int   m_number;
	int   m_increment;
	int   m_numberDelta;
	float m_timeDelta;
	float m_timeEscape;
};

#endif