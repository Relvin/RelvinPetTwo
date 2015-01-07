/****************************************************************************
 for cocos2d-x 3.2

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _NUMBER_COUNT_H_
#define _NUMBER_COUNT_H_

#include "cocos2d.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

/**
 * @brief һ�����ֱ�ǩ����ǿ������
 *
 * ���ܣ������ֱ�ǩ���趨������һ������
 *       ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ���ܹ�����m_increment
 *
 * Ӧ�÷�Χ���������ڷ�������ʾ
 * ���Թ��� cocos2d �� cocos2d::LabelAtlas ��
 * �� cocostudio ������ cocos2d::ui::TextAtlas
 */
class NumberCount : public cocos2d::Ref
{
public:
	NumberCount();

	void setLabelAtlas(cocos2d::LabelAtlas* ccLabelAtlas)   
	{
		m_ccLabelAtlas = ccLabelAtlas;
		m_ccLabelAtlas->setString(cocos2d::__String::createWithFormat("%d",m_number)->getCString());
	}

	void setTextAtlas(cocos2d::ui::TextAtlas* uiLabelAtlas) 
	{
		m_uiLabelAtlas = uiLabelAtlas;
		m_uiLabelAtlas->setString(cocos2d::__String::createWithFormat("%d",m_number)->getCString());
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
	cocos2d::LabelAtlas*    m_ccLabelAtlas;
	cocos2d::ui::TextAtlas* m_uiLabelAtlas;

	int   m_number;
	int   m_increment;
	int   m_numberDelta;
	float m_timeDelta;
	float m_timeEscape;
};

#endif