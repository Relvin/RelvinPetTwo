#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ScrollingBackground.h"

USING_NS_CC;
using namespace ui;

/**
 * SpriteBackground�����ʾdemo
 * ��Ļ��СҲ������main.cpp����,�������Զ�������Ļ
 * ������ģʽ,ѭ�������Ͷ�������
 * ���������Ĳ������� void okCallback(CCObject*) ������е�,ע�⿴����
 * setBgSpriteScrollBy �� setFullScreen ����û��������ʾ,��������������Ҳ�ܼ�,����ע�;ͻ�����
 */
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
   
    virtual bool init();  
   
    void quitCallback(Ref*);

	///�����ǲ˵�������,���ÿ�
	void createInitMenu();//����ѡ��
	void dirChangeCallback(Ref*);

	///ģʽѡ��,ѭ������ģʽ�ͱ߹����߶�������ģʽ
	void modeChangeCallback(Ref*);

	void toggleCallback(Ref*);

	///ȷ��ѡ��ť,���������Ĳ��������������
	void okCallback(Ref*);

	///���ذ�ť,����ѡ�����ģʽ
	void backCallback(Ref*);

	///�������¸���������ϸ�����
	void nextBgCallback(Ref*);

	///��ͣ�Ϳ�ʼ
	void pauseCallback(Ref*);

	//���ñ������������
	void reverseCallback(Ref*);

	///���Ӿ��鱳��
	void addBgSpriteCallback(Ref*);

	///ѭ��ģʽ����һ�����������뿪��Ļ��ʱ�����
	void loopBgChangeCallback(Sprite* current,Sprite* follow,Sprite* leave);
	
	///����ģʽ����һ�����������뿪��Ļ��ʱ�����
	void dropBgChangeCallback(Sprite* current,Sprite* follow,Sprite* leave);

	///ÿһ֡�����ƶ���ʱ�����
	void bgMoveCallback(Sprite* current,Sprite* follow);

    CREATE_FUNC(HelloWorld);

private:
	ScrollingBackground* m_bg;
	ScrollDirection      m_direction;

	//��ʼ�ķ����ģʽѡ��˵�
	Layer*          m_setLayer;
	MenuItemToggle* m_dirSelItem;
	MenuItemToggle* m_modeSelItem;

	//��������֮��Ĳ˵�
	Layer*   m_runLayer;
	Label*   m_itemTipsLabel; ///<itemλ����ʾ
	Label*   m_addTipsLabel;  ///<���ӱ����Ƿ�ɹ�����ʾ
	Label*   m_numBgLabel;	   ///<������Ŀ����ʾ
	Sprite*  m_bgSprite;      ///<��ǰ���鱳��
	Sprite*  m_pItem;         ///<һ������,ע���������Ǳ��������child,ֻ�������汳����������,����HelloWorld��child
	float	 m_velocity;

	//���ӱ�������
	bool addBgSprite(int index);

	//����������ʾ
	void setTextTips(Sprite* bgSprite);
};

#endif // __HELLOWORLD_SCENE_H__
