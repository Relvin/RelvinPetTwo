#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
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
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    m_label = Label::createWithTTF("", "fonts/arial.ttf", 24);
	m_label->setAnchorPoint(Vec2(0.5f,1.0f));

    // position the label on the center of the screen
    m_label->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height));

    // add the label as a child to this layer
    this->addChild(m_label, 1);

    // add "HelloWorld" splash screen"
    Sprite* pSprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    

	m_ball = CCSprite::create("ball.png");
	m_ball->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	m_ball->setScale(0.5f);
	this->addChild(m_ball,2);

	//����ҡ��ʵ
	Joystick* j = Joystick::create("joystickBg.png",40.0f,"joystickHandle.png",25.0f);
	j->setPosition(Vec2(40,40));


	//���������ûص��ķ���������
	//j->setHandleEventListener(this,joystickEvent_selector(HelloWorld::moveSpr));
	j->setHandleEventListener(JOYSTICK_CALLBACK(HelloWorld::moveSpr,this));
	
	this->addChild(j,3);

    return true;
}

//ҡ���¼�����
void HelloWorld::moveSpr(float interval,float x , float y,JoystickEventType type)
{
	
	Point pos = m_ball->getPosition();
	
	pos.x+=x*.5;
	
	pos.y+=y*.5;
	
	m_ball->setPosition(pos);

	std::string str;

	switch(type)
	{
	case JoystickEventType::JET_TOUCH_BEGIN:
		str = "Begin";
		break;
	case JoystickEventType::JET_TOUCH_MOVE:
		str = "Move";
		break;
	case JoystickEventType::JET_TOUCH_END:
		str = "End";
		break;
	}

	m_label->setString(str.c_str());
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
