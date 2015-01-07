#include "HelloWorldScene.h"

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "visible.png",
                                        "visible.png",
                                        this,
                                        menu_selector(HelloWorld::btVisbleCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width  - pCloseItem->getContentSize().width/2 ,
								origin.y + visibleSize.height - pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
 


	/*Frame�Ĳ���*/
	
	Widget* frame = GUIReader::shareReader()->widgetFromJsonFile("UIRes/DemoLogin.ExportJson");
	
	UILayer* layer =UILayer::create();
	layer->setScale(0.8f); //���ű��������������
	layer->addWidget(frame);
	this->addChild(layer);

	//��������
	layer->getWidgetByName("login_Button")->addTouchEventListener(this,toucheventselector(HelloWorld::btMenuCallBack));
	layer->getWidgetByName("close_Button")->addTouchEventListener(this,toucheventselector(HelloWorld::btMenuCallBack));
	layer->getWidgetByName("agree_CheckBox")->addTouchEventListener(this,toucheventselector(HelloWorld::btMenuCallBack));
	layer->getWidgetByName("name_TextField")->addTouchEventListener(this,toucheventselector(HelloWorld::btMenuCallBack));
	layer->getWidgetByName("password_TextField")->addTouchEventListener(this,toucheventselector(HelloWorld::btMenuCallBack));
	layer->getWidgetByName("confirm_TextField")->addTouchEventListener(this,toucheventselector(HelloWorld::btMenuCallBack));

	//frame��ʼ��,������һ�²���ʼ����ֱ��layer->setVisible(false);���ô��ڲ��ɼ�֮��,�����ԭ���İ�ť���򣬿����Ƿ��жԻ������
	m_frame.setFrame(frame,(UIImageView*)layer->getWidgetByName("backageImg"));
	m_frame.setFrameVisible(true);


    return true;
}


void HelloWorld::btVisbleCallback(CCObject* pSender)
{
	m_frame.setFrameVisible(true);
}

void HelloWorld::btMenuCallBack(CCObject* pObject,TouchEventType eventType)
{
	if(eventType == TOUCH_EVENT_ENDED)
	{
		CCMessageBox("","");
	}
}