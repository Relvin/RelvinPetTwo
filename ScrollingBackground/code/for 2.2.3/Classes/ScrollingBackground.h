/****************************************************************************
 for cocos2d-x 2.2.3

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _SCROLLING_BACKGROUND_H_
#define _SCROLLING_BACKGROUND_H_

#include "cocos2d.h"
#include <list>

typedef std::list<cocos2d::CCSprite*> NodeList;
typedef std::list<cocos2d::CCSprite*>::iterator ListIter;

//current �������������뿪��Ļ�ĵ�ͼ����
//follow  �������������뿪��Ļ�ĵ�ͼ����
//leave   ���ո��뿪��Ļ�ĵ�ͼ����
typedef void (cocos2d::CCObject::*SEL_BgSpriteChangeEvent)(cocos2d::CCSprite* current,cocos2d::CCSprite* follow,cocos2d::CCSprite* leave);
#define bgSpriteChangeEvent(_SELECTOR) (SEL_BgSpriteChangeEvent)(&_SELECTOR)

//current �������������뿪��Ļ�ĵ�ͼ����
//follow  �������������뿪��Ļ�ĵ�ͼ����
typedef void (cocos2d::CCObject::*SEL_BgSpriteMovbEvent)(cocos2d::CCSprite* current,cocos2d::CCSprite* follow);
#define bgSpriteMoveEvent(_SELECTOR) (SEL_BgSpriteMovbEvent)(&_SELECTOR)

///���������ķ���
enum ScrollDirection{SD_RIGHT_TO_LEFT,SD_LEFT_TO_RIGHT,SD_TOP_TO_BOTTOM,SD_BOTTOM_TO_TOP};

/**
 * ��������
 * ����ѡ�������,���ҵ���,���ϵ���,���µ����ĸ��������
 * ����ģʽ������ѭ��,ͨ�����ûص�����,����ʵ�ֱ߹��������ٻ�����߲��뻭��
 * ����addBackgroundBlock���ӻ���,���ÿ�ʼ����
 * ������Ҫ�������������ȷ����
 */
class ScrollingBackground : public cocos2d::CCNode
{
public:
	ScrollingBackground();
	virtual ~ScrollingBackground();

	/**
	 * ���ӱ�������,����Ľڵ���Զ�����������Ļ,���ӵ�����β
	 * ����һ�߹���һ�����ӱ�������ڵ�,�����ǰ�ڵ�������β,��ʧ�ܲ�����false
	 */
	bool addBackgroundSprite(cocos2d::CCSprite* bgSprite);

	///��ʼ��������
	bool beginContinuousScroll(float velocity)    {return beginScroll(velocity);}

	///�������������������ڵ��е�һ�������뿪��Ļ
	bool scrollToNextBgSprite(float velocity);

	///���ñ����ƶ��趨�ľ���
	bool setBgSpriteScrollBy(float velocity,float distance);

	///��ͣ����
	void pauseScroll()  {m_isScrolling = false;}

	///�ָ�����
	void resumeScroll(float velocity);

	///�Ƴ������ڵ�,�����뱣֤�ڵ������ڵĽڵ�������2,�Ҳ����Ƴ���ǰ��ʾ����Ļ�ڵ������ڵ�
	bool removeBgSprite(cocos2d::CCSprite* bgSprite);

	///���ñ���ȫ��������ʾ
	void setFullScreen(cocos2d::CCSprite* bgSprite);

	///���ص�ͼ�������ж����ŵ�ͼ����
	int   getNumBgSprite()			    {return m_bgSpriteList.size();}

	float getVelocity()					          {return m_velocity;}
	bool  isListBack(cocos2d::CCSprite* bgBlock)  {return bgBlock == m_bgSpriteList.back();}
	bool  isListFront(cocos2d::CCSprite* bgBlock) {return bgBlock == m_bgSpriteList.front();}
	void  setVelocity(float velocity)             {m_velocity = velocity;}

	cocos2d::CCSprite* getBackBgSprite()		  {return m_bgSpriteList.back();}
	cocos2d::CCSprite* getFrontBgSprite()	      {return m_bgSpriteList.front();}
	cocos2d::CCSprite* getCurBgSprite()		      {return m_curIter!=m_bgSpriteList.end() ? (*m_curIter):0;}
	cocos2d::CCSprite* getFollowBgSprite()	      {return m_followIter!=m_bgSpriteList.end() ? (*m_followIter):0;}
	
	/**
	 * ��һ�����泹���뿪��Ļ��ʱ��ᷢ�������Ϣ
	 * SEL_BgSpriteChangeEvent �� CCSprite* ������������Ļ�ڵ�������ͼ�ڵ��һ���Ѿ��뿪��Ļ�ĵ�ͼ�ڵ�
	 */
	void setBgChangeEventListener(cocos2d::CCObject *target, SEL_BgSpriteChangeEvent selector);

	/**
	 * ��һ�������ƶ���ʱ��ᷢ�������Ϣ
	 * SEL_BgSpriteChangeEvent �� CCSprite* ������������Ļ�ڵ�������ͼ�ڵ�
	 */
	void setBgMoveEventListener(cocos2d::CCObject *target, SEL_BgSpriteMovbEvent selector);

	/**
	 *  һ����̬����,���ڴ���ScrollingBackground
	 *@param type ����ģʽ
	 *@param ScrollDirection �������� 
	 */
	static ScrollingBackground* create(ScrollDirection direction);
protected:
	ScrollDirection m_direction;     ///<��������
	NodeList		m_bgSpriteList;   ///<�ڵ㴢������
	ListIter		m_curIter;       ///<��ǰ��������Ļ�ϵ����������ǰһ�����������ȹ�����Ļ���Ǹ���
	ListIter		m_followIter;    ///<��ǰ��������Ļ�ϵ���������ĺ�һ�������滭�棨������������Ļ���Ǹ���
	cocos2d::CCSize	m_visibleSize;   ///<������Ļ�Ĵ�С,���ڽ������������ŵ�������Ļ
	bool			m_isScrolling;   ///<�Ƿ����ڹ���
	bool		    m_bScrollToNext; ///<�Ƿ������˱������������������ڵ��е�һ�������뿪��Ļ
	bool			m_bScrollBy;     ///<�Ƿ��趨��������һ������
	float           m_velocity;      ///<�������ٶ�
	float			m_distance;      ///<�趨��������ƶ�����
	float			m_sensitivity;   ///<����scrollToNextBgSprite������������һ��ͼƬ��ʶ��������

	cocos2d::CCObject*      m_changeEventListener;
    SEL_BgSpriteChangeEvent m_changeEventSelector;

	cocos2d::CCObject*      m_moveEventListener;
    SEL_BgSpriteMovbEvent   m_moveEventSelector;

	bool init(ScrollDirection direct);

	///�����ڵ㲢���ڵ�����б�
	void addListNode(cocos2d::CCSprite* bgSprite);

	///һ�����泹���뿪��Ļ��ʱ���������,�������� m_curIter �� m_followIter
	void changeCurBgSprite();

	///ÿһ֡����һ��,���û����λ��
	void moveAction(float d);

	///���ø��滭���λ��
	void setFollowNodePosition();

	///�ж�һ�������Ƿ�����Ļ��Χ��
	bool bChangeBg(const cocos2d::CCPoint& posCur,const cocos2d::CCPoint& achorPointCur);

	///���ٶ�Ϊ����ʱ��,Ҫ��������һʱ�� m_curIter ��ָ��ı����ڵ��λ��
	void preSetCurPos();

	///������ʱ��Ĺ�������
	bool beginScroll(float velocity);
};

inline void ScrollingBackground::setBgChangeEventListener(cocos2d::CCObject *target, SEL_BgSpriteChangeEvent selector)
{
	m_changeEventListener = target;
	m_changeEventSelector = selector;
}

inline void ScrollingBackground::setBgMoveEventListener(cocos2d::CCObject *target, SEL_BgSpriteMovbEvent selector)
{
	m_moveEventListener = target;
	m_moveEventSelector = selector;
}

inline void ScrollingBackground::resumeScroll(float velocity) 
{
	m_velocity = velocity;
	m_isScrolling = true;
}

#endif