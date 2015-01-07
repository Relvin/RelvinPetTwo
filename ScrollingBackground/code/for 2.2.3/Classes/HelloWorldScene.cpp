#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    
    HelloWorld *layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	createInitMenu();

    return true;
}

//һЩ�˵������ò���Ҳ����,���ͼ��صĲ�����okCallback����
void HelloWorld::createInitMenu()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	m_setLayer = CCLayer::create();
	this->addChild(m_setLayer);

	//��������
	m_dirSelItem = CCMenuItemToggle::createWithTarget(this,
        menu_selector(HelloWorld::toggleCallback),
        CCMenuItemFont::create("Right to Left"),
        CCMenuItemFont::create("Left to Right"),
		CCMenuItemFont::create("Top to Bottom"),
		CCMenuItemFont::create("Bottom to Top"),
        NULL);

	m_dirSelItem->setAnchorPoint(ccp(0.5f,0.5f));
	m_dirSelItem->setPosition(ccp(visibleSize.width/2 ,
								visibleSize.height/4*3));

    CCMenuItemImage *nextDir = CCMenuItemImage::create(
                                        "nextNor.png",
                                        "nextCli.png",
                                        this,
                                        menu_selector(HelloWorld::dirChangeCallback));
	nextDir->setTag(1);
	nextDir->setAnchorPoint(ccp(0.5f,0.5f));
	nextDir->setPosition(ccp(visibleSize.width/6*5,
                             visibleSize.height/4*3));

	CCMenuItemImage *lastDir = CCMenuItemImage::create(
                                        "lastNor.png",
                                        "lastCli.png",
                                        this,
                                        menu_selector(HelloWorld::dirChangeCallback));
	lastDir->setTag(-1);
	lastDir->setAnchorPoint(ccp(0.5f,0.5f));
	lastDir->setPosition(ccp(visibleSize.width/6,
                             visibleSize.height/4*3));



   //ģʽ����
	m_modeSelItem = CCMenuItemToggle::createWithTarget(this,
        menu_selector(HelloWorld::toggleCallback),
        CCMenuItemFont::create("Loop Mode"),
        CCMenuItemFont::create("Drop Mode"),
        NULL);

	m_modeSelItem->setAnchorPoint(ccp(0.5f,0.5f));
	m_modeSelItem->setPosition(ccp(visibleSize.width/2 ,
								visibleSize.height/3));

	m_modeSelItem->setAnchorPoint(ccp(0.5f,0.5f));
	m_modeSelItem->setPosition(ccp(visibleSize.width/2 ,
								visibleSize.height/2));

	CCMenuItemImage *nextMode = CCMenuItemImage::create(
                                        "nextNor.png",
                                        "nextCli.png",
                                        this,
                                        menu_selector(HelloWorld::modeChangeCallback));
	nextMode->setTag(1);
	nextMode->setAnchorPoint(ccp(0.5f,0.5f));
	nextMode->setPosition(ccp(visibleSize.width/6*5,
                             visibleSize.height/2));

	CCMenuItemImage *lastMode = CCMenuItemImage::create(
                                        "lastNor.png",
                                        "lastCli.png",
                                        this,
                                        menu_selector(HelloWorld::modeChangeCallback));
	lastMode->setTag(-1);
	lastMode->setAnchorPoint(ccp(0.5f,0.5f));
	lastMode->setPosition(ccp(visibleSize.width/6,
                             visibleSize.height/2));

	CCMenuItemFont* pOK = CCMenuItemFont::create("OK",this,menu_selector(HelloWorld::okCallback));
	pOK->setPosition(ccp(visibleSize.width/3,visibleSize.height/4));

	CCMenuItemFont* pQuit = CCMenuItemFont::create("Quit",this,menu_selector(HelloWorld::quitCallback));
	pQuit->setPosition(ccp(visibleSize.width/3*2,visibleSize.height/4));

	CCMenu* pMenu = CCMenu::create(lastDir,m_dirSelItem,nextDir,lastMode,m_modeSelItem,nextMode,pOK,pQuit,NULL);
    pMenu->setPosition(CCPointZero);

    m_setLayer->addChild(pMenu);

	m_bg = 0;
}

void HelloWorld::pauseCallback(CCObject* pObject)
{
	int i = ((CCMenuItemToggle*)pObject)->getSelectedIndex();
	
	if(i)
		m_bg->pauseScroll();
	else
		m_bg->resumeScroll(m_bg->getVelocity());
}

void HelloWorld::reverseCallback(CCObject* pSender)
{
	m_bg->setVelocity(-m_bg->getVelocity());
}

void HelloWorld::addBgSpriteCallback(CCObject*)
{
	if(addBgSprite(5))
	{
		m_addTipsLabel->setString("add background - success");
		CCString num;
		num.initWithFormat("the number of background sprites : %d",m_bg->getNumBgSprite());
		m_numBgLabel->setString(num.getCString());
	}

	else
		m_addTipsLabel->setString("add background - failure");  
}

void HelloWorld::dirChangeCallback(CCObject* pSender)
{
	int index = m_dirSelItem->getSelectedIndex();
	int tag   = ((CCMenuItemImage*)pSender)->getTag();
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

void HelloWorld::modeChangeCallback(CCObject* pSender)
{
	int index = m_modeSelItem->getSelectedIndex();
	int tag   = ((CCMenuItemImage*)pSender)->getTag();
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

void HelloWorld::toggleCallback(CCObject* pSender)
{
	
}

void HelloWorld::nextBgCallback(CCObject* pSender)
{
	if(((CCMenuItemImage*)pSender)->getTag()==0)
	{
		switch(m_direction)
		{
		case SD_BOTTOM_TO_TOP:
		case SD_LEFT_TO_RIGHT:
			m_bg->scrollToNextBgSprite(m_velocity);
			break;
		case SD_TOP_TO_BOTTOM:
		case SD_RIGHT_TO_LEFT:
			m_bg->scrollToNextBgSprite(-m_velocity);
			break;
		}
		
	}
	else
	{
		switch(m_direction)
		{
		case SD_BOTTOM_TO_TOP:
		case SD_LEFT_TO_RIGHT:
			m_bg->scrollToNextBgSprite(-m_velocity);
			break;
		case SD_TOP_TO_BOTTOM:
		case SD_RIGHT_TO_LEFT:
			m_bg->scrollToNextBgSprite(m_velocity);
			break;
		}
	}
}

void HelloWorld::okCallback(CCObject* pSender)
{
	if(!m_bg)
	{
		m_runLayer = CCLayer::create();
		this->addChild(m_runLayer);

		int dirSel = m_dirSelItem->getSelectedIndex();
		switch (dirSel)
		{
		case 0:
			m_bg = ScrollingBackground::create(SD_RIGHT_TO_LEFT);
			m_direction = SD_RIGHT_TO_LEFT;
			break;
		case 1:
			m_bg = ScrollingBackground::create(SD_LEFT_TO_RIGHT);
			m_direction = SD_LEFT_TO_RIGHT;
			break;
		case 2:
			m_bg = ScrollingBackground::create(SD_TOP_TO_BOTTOM);
			m_direction = SD_TOP_TO_BOTTOM;
			break;
		case 3:
			m_bg = ScrollingBackground::create(SD_BOTTOM_TO_TOP);
			m_direction = SD_BOTTOM_TO_TOP;
			break;
		default:
			break;
		}

		m_runLayer->addChild(m_bg,1);

		for (int i = 1; i < 5; i++)
		{
			addBgSprite(i);
		}

		//����һ���������鳹���뿪��Ļ��ʱ�����Ϣ
		if(m_modeSelItem->getSelectedIndex()==0)
			m_bg->setBgChangeEventListener(this,bgSpriteChangeEvent(HelloWorld::loopBgChangeCallback)); //ѭ��ģʽ
		else
			m_bg->setBgChangeEventListener(this,bgSpriteChangeEvent(HelloWorld::dropBgChangeCallback)); //����ģʽ

		//�����������ƶ�ʱ�����Ϣ
		m_bg->setBgMoveEventListener(this,bgSpriteMoveEvent(HelloWorld::bgMoveCallback));

		m_velocity = 300.0f;
		m_bgSprite = m_bg->getCurBgSprite();
		m_bg->beginContinuousScroll(m_velocity);

		//һ�����汳���ƶ�������
		m_pItem = CCSprite::create("item.png");
		m_pItem->setAnchorPoint(ccp(0.5f,0.5f));
		m_pItem->setPosition(ccp(0.0f,0.0f));
		m_runLayer->addChild(m_pItem,2);

		//pItemê��һֱ����(0.5,0.5),����һֱ��(0.0,0.0),ע�⿴�������л���ʱ���������������
		//�������龫���ê�㲻ͬ����Ӱ��pItem��λ��
		m_pItem->setPosition(m_bg->getCurBgSprite()->getPosition());
		




		/*�������һЩ�˵�������,����Ҳ����*/
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

		//���ذ�ť
		CCMenuItemFont* back = CCMenuItemFont::create("back",this,menu_selector(HelloWorld::backCallback));
		back->setAnchorPoint(ccp(1.0f,1.0f));
		back->setPosition(ccp(visibleSize.width/2.0f,visibleSize.height/2.0f));

		//�����෴�ٶȵİ�ť
		CCMenuItemFont* reverse = CCMenuItemFont::create("reverse",this,menu_selector(HelloWorld::reverseCallback));

		//��ͣ
		CCMenuItemToggle* pause = CCMenuItemToggle::createWithTarget(this,
																	menu_selector(HelloWorld::pauseCallback),
																	CCMenuItemFont::create("pause"),
																	CCMenuItemFont::create("resume"),
																	NULL);
		pause->setPosition(ccp(0.0f,50.0f));

		//��һ������
		CCMenuItemImage* lastBg = CCMenuItemImage::create("lastBgNor.png","lastBgCli.png",0,this,menu_selector(HelloWorld::nextBgCallback));
		lastBg->setTag(0);
		lastBg->setAnchorPoint(ccp(0.0f,0.5f));
		lastBg->setPosition(ccp(-visibleSize.width/2.0f,0.0f));

		//��һ������
		CCMenuItemImage* nextBg = CCMenuItemImage::create("NextBgNor.png","NextBgCli.png",0,this,menu_selector(HelloWorld::nextBgCallback));
		nextBg->setTag(1);
		nextBg->setAnchorPoint(ccp(1.0f,0.5f));
		nextBg->setPosition(ccp(visibleSize.width/2.0f,0.0f));

		//���ӱ�������
		CCMenuItemFont* add = CCMenuItemFont::create("add background",this,menu_selector(HelloWorld::addBgSpriteCallback));
		add->setPosition(ccp(0.0f,-50.0f));

		CCMenu* pMenu = CCMenu::create(pause,reverse,add,lastBg,nextBg,back,NULL);
		pMenu->setPosition(ccp(visibleSize.width/2.0f,visibleSize.height/2.0f));
		m_runLayer->addChild(pMenu,3);

		//������ʾ��
		ccColor3B color = {255,0,0};
		m_itemTipsLabel = CCLabelTTF::create();
		m_itemTipsLabel->setColor(color);
		m_itemTipsLabel->setAnchorPoint(ccp(0.5f,0.5f));
		m_itemTipsLabel->setFontSize(17.0f);
		m_itemTipsLabel->setPosition(ccp(visibleSize.width/2.0f,visibleSize.height/6.0f));
		m_runLayer->addChild(m_itemTipsLabel,3);

		m_numBgLabel = CCLabelTTF::create();
		m_numBgLabel->setColor(color);
		m_numBgLabel->setAnchorPoint(ccp(0.5f,0.5f));
		m_numBgLabel->setFontSize(17.0f);
		m_numBgLabel->setPosition(ccp(visibleSize.width/2.0f,visibleSize.height/10.0f));
		m_runLayer->addChild(m_numBgLabel,3);

		
		m_addTipsLabel = CCLabelTTF::create();
		m_addTipsLabel->setColor(color);
		m_addTipsLabel->setAnchorPoint(ccp(0.5f,0.5f));
		m_addTipsLabel->setFontSize(17.0f);
		m_addTipsLabel->setPosition(ccp(visibleSize.width/2.0f,visibleSize.height/10.0f*9.0f));
		m_addTipsLabel->setString("");
		m_runLayer->addChild(m_addTipsLabel,3);

		setTextTips(m_bg->getCurBgSprite());

		this->removeChild(m_setLayer);
		m_setLayer = 0;
	}
}

void HelloWorld::setTextTips(CCSprite* bgSprite)
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

	CCString num;
	num.initWithFormat("the number of background sprites : %d",m_bg->getNumBgSprite());
	m_numBgLabel->setString(num.getCString());
}

bool HelloWorld::addBgSprite(int index)
{
	if(!m_bg)
		return false;

	CCSprite *pSprite;
	switch(index)
	{
	case 1:
		pSprite = CCSprite::create("1.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(1);
		pSprite->setAnchorPoint(ccp(0.5f,0.5f));//ê��Ϊ��������
		break;
			  
	case 2:
		pSprite = CCSprite::create("2.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(2);
		pSprite->setAnchorPoint(ccp(0.0f,0.0f));//ê��Ϊ�������½�
		break;


	case 3:
		pSprite = CCSprite::create("3.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(3);
		pSprite->setAnchorPoint(ccp(1.0f,1.0f));//ê��Ϊ�������Ͻ�
		break;

	case 4:
		pSprite = CCSprite::create("4.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(4);
		pSprite->setAnchorPoint(ccp(1.0f,0.0f));//ê��Ϊ�������½�
		break;

	case 5:
		pSprite = CCSprite::create("add.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(5);
		pSprite->setAnchorPoint(ccp(0.5f,0.5f));//ê��Ϊ��������
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

void HelloWorld::dropBgChangeCallback(CCSprite* current,CCSprite* follow,CCSprite* leave)
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
		m_pItem->setAnchorPoint(ccp(0.0f,0.0f));
		break;
	case 3:
		m_pItem->setAnchorPoint(ccp(1.0f,1.0f));
		break;
	case 4:
		m_pItem->setAnchorPoint(ccp(1.0f,0.0f));
		break;
	default:
		m_pItem->setAnchorPoint(ccp(0.5f,0.5f));
		break;
	}
}

void HelloWorld::loopBgChangeCallback(CCSprite* current,CCSprite* follow,CCSprite* leave)
{
	if(m_bg->getVelocity()>0.0f)
		m_bgSprite = current; //current�������������뿪��Ļ���Ǹ�����
	else
		m_bgSprite = follow;  //follow�Ǹ����������뿪��Ļ���Ǹ�����

	setTextTips(m_bgSprite);

	switch(m_bgSprite->getTag())
	{
	case 2:
		m_pItem->setAnchorPoint(ccp(0.0f,0.0f));
		break;
	case 3:
		m_pItem->setAnchorPoint(ccp(1.0f,1.0f));
		break;
	case 4:
		m_pItem->setAnchorPoint(ccp(1.0f,0.0f));
		break;
	default:
		m_pItem->setAnchorPoint(ccp(0.5f,0.5f));
		break;
	}
}

void HelloWorld::bgMoveCallback(CCSprite* current,CCSprite* follow)
{
	m_pItem->setPosition(m_bgSprite->getPosition());
}

void HelloWorld::backCallback(CCObject*)
{
	m_runLayer->removeChild(m_bg);
	this->removeChild(m_runLayer);
	m_runLayer = 0;
	m_bg = 0;

	createInitMenu();
}

void HelloWorld::quitCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}