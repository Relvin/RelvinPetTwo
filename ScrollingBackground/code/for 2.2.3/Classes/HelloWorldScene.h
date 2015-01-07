#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ScrollingBackground.h"
#include <string>

USING_NS_CC;

/**
 * SpriteBackground�����ʾdemo
 * ��Ļ��СҲ������main.cpp����,�������Զ�������Ļ
 * ������ģʽ,ѭ�������Ͷ�������
 * ���������Ĳ������� void okCallback(CCObject*) ������е�,ע�⿴����
 * setBgSpriteScrollBy �� setFullScreen ����û��������ʾ,��������������Ҳ�ܼ�,����ע�;ͻ�����
 */
class HelloWorld : public cocos2d::CCLayer
{
public:
    virtual bool init();  
	
	void quitCallback(CCObject*);

	///�����ǲ˵�������,���ÿ�
	void createInitMenu();//����ѡ��
	void dirChangeCallback(CCObject*);

	///ģʽѡ��,ѭ������ģʽ�ͱ߹����߶�������ģʽ
	void modeChangeCallback(CCObject*);

	void toggleCallback(CCObject*);

	///ȷ��ѡ��ť,���������Ĳ��������������
	void okCallback(CCObject*);

	///���ذ�ť,����ѡ�����ģʽ
	void backCallback(CCObject*);

	///�������¸���������ϸ�����
	void nextBgCallback(CCObject*);

	///��ͣ�Ϳ�ʼ
	void pauseCallback(CCObject*);

	//���ñ������������
	void reverseCallback(CCObject*);

	///���Ӿ��鱳��
	void addBgSpriteCallback(CCObject*);

	///ѭ��ģʽ����һ�����������뿪��Ļ��ʱ�����
	void loopBgChangeCallback(CCSprite* current,CCSprite* follow,CCSprite* leave);
	
	///����ģʽ����һ�����������뿪��Ļ��ʱ�����
	void dropBgChangeCallback(CCSprite* current,CCSprite* follow,CCSprite* leave);

	///ÿһ֡�����ƶ���ʱ�����
	void bgMoveCallback(CCSprite* current,CCSprite* follow);

    static cocos2d::CCScene* scene();
	
    CREATE_FUNC(HelloWorld);

private:
	ScrollingBackground* m_bg;
	ScrollDirection      m_direction;

	//��ʼ�ķ����ģʽѡ��˵�
	CCLayer*          m_setLayer;
	CCMenuItemToggle* m_dirSelItem;
	CCMenuItemToggle* m_modeSelItem;

	//��������֮��Ĳ˵�
	CCLayer*          m_runLayer;
	CCLabelTTF*       m_itemTipsLabel; ///<itemλ����ʾ
	CCLabelTTF*       m_addTipsLabel;  ///<���ӱ����Ƿ�ɹ�����ʾ
	CCLabelTTF*       m_numBgLabel;	   ///<������Ŀ����ʾ
	CCSprite*         m_bgSprite;      ///<��ǰ���鱳��
	CCSprite*         m_pItem;         ///<һ������,ע���������Ǳ��������child,ֻ�������汳����������,����HelloWorld��child
	float			  m_velocity;

	//���ӱ�������
	bool addBgSprite(int index);

	//����������ʾ
	void setTextTips(CCSprite* bgSprite);
};

#endif
