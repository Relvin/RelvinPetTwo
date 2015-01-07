#include "HelloWorldScene.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	createInitMenu();

    return true;
}

//һЩ�˵������ò���Ҳ����,���ͼ��صĲ�����okCallback����
void HelloWorld::createInitMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_setLayer = Layer::create();
	this->addChild(m_setLayer);

	//��������
	Vector<MenuItem*> dirItemFronts;
	dirItemFronts.pushBack(MenuItemFont::create("Right to Left"));
	dirItemFronts.pushBack(MenuItemFont::create("Left to Right"));
	dirItemFronts.pushBack(MenuItemFont::create("Top to Bottom"));
	dirItemFronts.pushBack(MenuItemFont::create("Bottom to Top"));
	m_dirSelItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(HelloWorld::toggleCallback,this),
        dirItemFronts);

	m_dirSelItem->setAnchorPoint(Vec2(0.5f,0.5f));
	m_dirSelItem->setPosition(Vec2(visibleSize.width/2 ,
								visibleSize.height/4*3));

    MenuItemImage *nextDir = MenuItemImage::create(
                                        "nextNor.png",
                                        "nextCli.png",
                                        CC_CALLBACK_1(HelloWorld::dirChangeCallback,this));

	nextDir->setTag(1);
	nextDir->setAnchorPoint(Vec2(0.5f,0.5f));
	nextDir->setPosition(Vec2(visibleSize.width/6*5,
                             visibleSize.height/4*3));

	MenuItemImage *lastDir = MenuItemImage::create(
                                        "lastNor.png",
                                        "lastCli.png",
                                        CC_CALLBACK_1(HelloWorld::dirChangeCallback,this));
	lastDir->setTag(-1);
	lastDir->setAnchorPoint(Vec2(0.5f,0.5f));
	lastDir->setPosition(Vec2(visibleSize.width/6,
                             visibleSize.height/4*3));



   //ģʽ����
	Vector<MenuItem*> modeItemFronts;
	modeItemFronts.pushBack(MenuItemFont::create("Loop Mode"));
	modeItemFronts.pushBack(MenuItemFont::create("Drop Mode"));
	m_modeSelItem = MenuItemToggle::createWithCallback(
	   CC_CALLBACK_1(HelloWorld::toggleCallback,this),
       modeItemFronts);

	m_modeSelItem->setAnchorPoint(Vec2(0.5f,0.5f));
	m_modeSelItem->setPosition(Vec2(visibleSize.width/2 ,
								visibleSize.height/3));

	m_modeSelItem->setAnchorPoint(Vec2(0.5f,0.5f));
	m_modeSelItem->setPosition(Vec2(visibleSize.width/2 ,
								visibleSize.height/2));

	MenuItemImage *nextMode = MenuItemImage::create(
                                        "nextNor.png",
                                        "nextCli.png",
                                        CC_CALLBACK_1(HelloWorld::modeChangeCallback,this));
	nextMode->setTag(1);
	nextMode->setAnchorPoint(Vec2(0.5f,0.5f));
	nextMode->setPosition(Vec2(visibleSize.width/6*5,
                             visibleSize.height/2));

	MenuItemImage *lastMode = MenuItemImage::create(
                                        "lastNor.png",
                                        "lastCli.png",
                                        CC_CALLBACK_1(HelloWorld::modeChangeCallback,this));
	lastMode->setTag(-1);
	lastMode->setAnchorPoint(Vec2(0.5f,0.5f));
	lastMode->setPosition(Vec2(visibleSize.width/6,
                             visibleSize.height/2));

	MenuItemFont* pOK = MenuItemFont::create("OK",CC_CALLBACK_1(HelloWorld::okCallback,this));
	pOK->setPosition(Vec2(visibleSize.width/3,visibleSize.height/4));

	MenuItemFont* pQuit = MenuItemFont::create("Quit",CC_CALLBACK_1(HelloWorld::quitCallback,this));
	pQuit->setPosition(Vec2(visibleSize.width/3*2,visibleSize.height/4));

	Menu* pMenu = Menu::create(lastDir,m_dirSelItem,nextDir,lastMode,m_modeSelItem,nextMode,pOK,pQuit,NULL);
	pMenu->setPosition(Vec2::ZERO);

    m_setLayer->addChild(pMenu);

	m_bg = 0;
}

void HelloWorld::pauseCallback(Ref* pObject)
{
	int i = ((MenuItemToggle*)pObject)->getSelectedIndex();
	
	if(i)
		m_bg->pauseScroll();
	else
		m_bg->resumeScroll(m_bg->getVelocity());
}

void HelloWorld::reverseCallback(Ref* pSender)
{
	m_bg->setVelocity(-m_bg->getVelocity());
}

void HelloWorld::addBgSpriteCallback(Ref*)
{
	if(addBgSprite(5))
	{
		m_addTipsLabel->setString("add background - success");
		__String num;
		num.initWithFormat("the number of background sprites : %d",m_bg->getNumBgSprite());
		m_numBgLabel->setString(num.getCString());
	}

	else
		m_addTipsLabel->setString("add background - failure");  
}

void HelloWorld::dirChangeCallback(Ref* pSender)
{
	int index = m_dirSelItem->getSelectedIndex();
	int tag   = ((MenuItemImage*)pSender)->getTag();
	if(tag<0)
	{
		index--;
		if(index<0)
			index = 3;
	}
	else
	{
		index++;
		index%=4;
	}
	m_dirSelItem->setSelectedIndex(index);
}

void HelloWorld::modeChangeCallback(Ref* pSender)
{
	int index = m_modeSelItem->getSelectedIndex();
	int tag   = ((MenuItemImage*)pSender)->getTag();
	if(tag<0)
	{
		index--;
		if(index<0)
			index = 1;
	}
	else
	{
		index++;
		index%=2;
	}
	m_modeSelItem->setSelectedIndex(index);
}

void HelloWorld::toggleCallback(Ref* pSender)
{
	
}

void HelloWorld::nextBgCallback(Ref* pSender)
{
	if(((MenuItemImage*)pSender)->getTag()==0)
	{
		switch(m_direction)
		{
		case ScrollDirection::SD_BOTTOM_TO_TOP:
		case ScrollDirection::SD_LEFT_TO_RIGHT:
			m_bg->scrollToNextBgSprite(m_velocity);
			break;
		case ScrollDirection::SD_TOP_TO_BOTTOM:
		case ScrollDirection::SD_RIGHT_TO_LEFT:
			m_bg->scrollToNextBgSprite(-m_velocity);
			break;
		}
		
	}
	else
	{
		switch(m_direction)
		{
		case ScrollDirection::SD_BOTTOM_TO_TOP:
		case ScrollDirection::SD_LEFT_TO_RIGHT:
			m_bg->scrollToNextBgSprite(-m_velocity);
			break;
		case ScrollDirection::SD_TOP_TO_BOTTOM:
		case ScrollDirection::SD_RIGHT_TO_LEFT:
			m_bg->scrollToNextBgSprite(m_velocity);
			break;
		}
	}
}

void HelloWorld::okCallback(Ref* pSender)
{
	if(!m_bg)
	{
		m_runLayer = Layer::create();
		this->addChild(m_runLayer);

		int dirSel = m_dirSelItem->getSelectedIndex();
		switch (dirSel)
		{
		case 0:
			m_bg = ScrollingBackground::create(ScrollDirection::SD_RIGHT_TO_LEFT);
			m_direction = ScrollDirection::SD_RIGHT_TO_LEFT;
			break;
		case 1:
			m_bg = ScrollingBackground::create(ScrollDirection::SD_LEFT_TO_RIGHT);
			m_direction = ScrollDirection::SD_LEFT_TO_RIGHT;
			break;
		case 2:
			m_bg = ScrollingBackground::create(ScrollDirection::SD_TOP_TO_BOTTOM);
			m_direction = ScrollDirection::SD_TOP_TO_BOTTOM;
			break;
		case 3:
			m_bg = ScrollingBackground::create(ScrollDirection::SD_BOTTOM_TO_TOP);
			m_direction = ScrollDirection::SD_BOTTOM_TO_TOP;
			break;
		default:
			break;
		}

		m_runLayer->addChild(m_bg,1);

		for (int i = 1; i < 5; i++)
		{
			addBgSprite(i);
		}

		/*
		//����һ���������鳹���뿪��Ļ��ʱ�����Ϣ,���ַ�ʽ
		if(m_modeSelItem->getSelectedIndex()==0)
			m_bg->setBgChangeEventListener(this,bgSpriteChangeEvent(HelloWorld::loopBgChangeCallback)); //ѭ��ģʽ
		else
			m_bg->setBgChangeEventListener(this,bgSpriteChangeEvent(HelloWorld::dropBgChangeCallback)); //����ģʽ
		*/
		//����һ���������鳹���뿪��Ļ��ʱ�����Ϣ,���ַ�ʽ
		if(m_modeSelItem->getSelectedIndex()==0)
			m_bg->setBgChangeEventListener(CC_CALLBACK_3(HelloWorld::loopBgChangeCallback,this)); //ѭ��ģʽ
		else
			m_bg->setBgChangeEventListener(CC_CALLBACK_3(HelloWorld::dropBgChangeCallback,this)); //����ģʽ

		/*
		//�����������ƶ�ʱ�����Ϣ,���ַ�ʽ
		m_bg->setBgMoveEventListener(this,bgSpriteMoveEvent(HelloWorld::bgMoveCallback));
		*/
		//�����������ƶ�ʱ�����Ϣ,���ַ�ʽ
		m_bg->setBgMoveEventListener(CC_CALLBACK_2(HelloWorld::bgMoveCallback,this));

		m_velocity = 300.0f;
		m_bgSprite = m_bg->getCurBgSprite();
		m_bg->beginContinuousScroll(m_velocity);

		//һ�����汳���ƶ�������
		m_pItem = Sprite::create("item.png");
		m_pItem->setAnchorPoint(Vec2(0.5f,0.5f));
		m_pItem->setPosition(Vec2(0.0f,0.0f));
		m_runLayer->addChild(m_pItem,2);

		//pItemê��һֱ����(0.5,0.5),����һֱ��(0.0,0.0),ע�⿴�������л���ʱ���������������
		//�������龫���ê�㲻ͬ����Ӱ��pItem��λ��
		m_pItem->setPosition(m_bg->getCurBgSprite()->getPosition());
		




		/*�������һЩ�˵�������,����Ҳ����*/
		Size visibleSize = Director::getInstance()->getVisibleSize();

		//���ذ�ť
		MenuItemFont* back = MenuItemFont::create("back",CC_CALLBACK_1(HelloWorld::backCallback,this));
		back->setAnchorPoint(Vec2(1.0f,1.0f));
		back->setPosition(Vec2(visibleSize.width/2.0f,visibleSize.height/2.0f));

		//�����෴�ٶȵİ�ť
		MenuItemFont* reverse = MenuItemFont::create("reverse",CC_CALLBACK_1(HelloWorld::reverseCallback,this));

		//��ͣ
		MenuItemToggle* pause = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::pauseCallback,this),
																	MenuItemFont::create("pause"),
																	MenuItemFont::create("resume"),
																	NULL);
		pause->setPosition(Vec2(0.0f,50.0f));

		//��һ������
		MenuItemImage* lastBg = MenuItemImage::create("lastBgNor.png","lastBgCli.png","",CC_CALLBACK_1(HelloWorld::nextBgCallback,this));
		lastBg->setTag(0);
		lastBg->setAnchorPoint(Vec2(0.0f,0.5f));
		lastBg->setPosition(Vec2(-visibleSize.width/2.0f,0.0f));

		//��һ������
		MenuItemImage* nextBg = MenuItemImage::create("NextBgNor.png","NextBgCli.png","",CC_CALLBACK_1(HelloWorld::nextBgCallback,this));
		nextBg->setTag(1);
		nextBg->setAnchorPoint(Vec2(1.0f,0.5f));
		nextBg->setPosition(Vec2(visibleSize.width/2.0f,0.0f));

		//���ӱ�������
		MenuItemFont* add = MenuItemFont::create("add background",CC_CALLBACK_1(HelloWorld::addBgSpriteCallback,this));
		add->setPosition(Vec2(0.0f,-50.0f));

		Menu* pMenu = Menu::create(pause,reverse,add,lastBg,nextBg,back,NULL);
		pMenu->setPosition(Vec2(visibleSize.width/2.0f,visibleSize.height/2.0f));
		m_runLayer->addChild(pMenu,3);

		//������ʾ��
		Color3B color(255,0,0);
		m_itemTipsLabel = Label::createWithTTF("","fonts/arial.ttf",17.0f);
		m_itemTipsLabel->setColor(color);
		m_itemTipsLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		m_itemTipsLabel->setPosition(Vec2(visibleSize.width/2.0f,visibleSize.height/6.0f));
		m_runLayer->addChild(m_itemTipsLabel,3);

		m_numBgLabel = Label::createWithTTF("","fonts/arial.ttf",17.0f);
		m_numBgLabel->setColor(color);
		m_numBgLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		m_numBgLabel->setPosition(Vec2(visibleSize.width/2.0f,visibleSize.height/10.0f));
		m_runLayer->addChild(m_numBgLabel,3);

		
		m_addTipsLabel = Label::createWithTTF("","fonts/arial.ttf",17.0f);
		m_addTipsLabel->setColor(color);
		m_addTipsLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		m_addTipsLabel->setPosition(Vec2(visibleSize.width/2.0f,visibleSize.height/10.0f*9.0f));
		m_addTipsLabel->setString("");
		m_runLayer->addChild(m_addTipsLabel,3);

		setTextTips(m_bg->getCurBgSprite());

		this->removeChild(m_setLayer);
		m_setLayer = 0;
	}
}

void HelloWorld::setTextTips(Sprite* bgSprite)
{
	std::string str = "the item is on the ";

	int tag = bgSprite->getTag();
	switch(tag)
	{
	case 1:
		str+="center of the bg (bg : 1)";
		break;
	case 2:
		str+="the lower left corner of the bg (bg : 2)";
		break;
	case 3:
		str+="the upper right corner of the bg (bg : 3)";
		break;
	case 4:
		str+="the lower right corner of the bg (bg : 4)";
		break;
	case 5:
		str+="center of the bg (bg : add)";
		break;
	}

	m_itemTipsLabel->setString(str.c_str());

	__String num;
	num.initWithFormat("the number of background sprites : %d",m_bg->getNumBgSprite());
	m_numBgLabel->setString(num.getCString());
}

bool HelloWorld::addBgSprite(int index)
{
	if(!m_bg)
		return false;

	Sprite *pSprite;
	switch(index)
	{
	case 1:
		pSprite = Sprite::create("1.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(1);
		pSprite->setAnchorPoint(Vec2(0.5f,0.5f));//ê��Ϊ��������
		break;
			  
	case 2:
		pSprite = Sprite::create("2.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(2);
		pSprite->setAnchorPoint(Vec2(0.0f,0.0f));//ê��Ϊ�������½�
		break;


	case 3:
		pSprite = Sprite::create("3.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(3);
		pSprite->setAnchorPoint(Vec2(1.0f,1.0f));//ê��Ϊ�������Ͻ�
		break;

	case 4:
		pSprite = Sprite::create("4.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(4);
		pSprite->setAnchorPoint(Vec2(1.0f,0.0f));//ê��Ϊ�������½�
		break;

	case 5:
		pSprite = Sprite::create("add.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(5);
		pSprite->setAnchorPoint(Vec2(0.5f,0.5f));//ê��Ϊ��������
		break;

	default:
		return false;
	}


	//���ӱ�������,����Ľڵ���Զ�����������Ļ,���ӵ�����β
	//����һ�߹���һ�����ӱ�������ڵ�,�����ǰ�ڵ�������β,��ʧ�ܲ�����false
	if(m_bg->addBackgroundSprite(pSprite))
		return true;
	else
		return false;
}

void HelloWorld::dropBgChangeCallback(Sprite* current,Sprite* follow,Sprite* leave)
{
	//�������뿪��Ļ�ı��������Ƴ�
	m_bg->removeBgSprite(leave);
	
	if(m_bg->getVelocity()>0.0f)
		m_bgSprite = current; //current�������������뿪��Ļ���Ǹ�����
	else
		m_bgSprite = follow;  //follow�Ǹ����������뿪��Ļ���Ǹ�����

	setTextTips(m_bgSprite);

	switch(m_bgSprite->getTag())
	{
	case 2:
		m_pItem->setAnchorPoint(Vec2(0.0f,0.0f));
		break;
	case 3:
		m_pItem->setAnchorPoint(Vec2(1.0f,1.0f));
		break;
	case 4:
		m_pItem->setAnchorPoint(Vec2(1.0f,0.0f));
		break;
	default:
		m_pItem->setAnchorPoint(Vec2(0.5f,0.5f));
		break;
	}
}

void HelloWorld::loopBgChangeCallback(Sprite* current,Sprite* follow,Sprite* leave)
{
	if(m_bg->getVelocity()>0.0f)
		m_bgSprite = current; //current�������������뿪��Ļ���Ǹ�����
	else
		m_bgSprite = follow;  //follow�Ǹ����������뿪��Ļ���Ǹ�����

	setTextTips(m_bgSprite);

	switch(m_bgSprite->getTag())
	{
	case 2:
		m_pItem->setAnchorPoint(Vec2(0.0f,0.0f));
		break;
	case 3:
		m_pItem->setAnchorPoint(Vec2(1.0f,1.0f));
		break;
	case 4:
		m_pItem->setAnchorPoint(Vec2(1.0f,0.0f));
		break;
	default:
		m_pItem->setAnchorPoint(Vec2(0.5f,0.5f));
		break;
	}
}

void HelloWorld::bgMoveCallback(Sprite* current,Sprite* follow)
{
	m_pItem->setPosition(m_bgSprite->getPosition());
}

void HelloWorld::backCallback(Ref*)
{
	m_runLayer->removeChild(m_bg);
	this->removeChild(m_runLayer);
	m_runLayer = 0;
	m_bg = 0;

	createInitMenu();
}

void HelloWorld::quitCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}