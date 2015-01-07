#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "NetClient.h"
#include "GameSession.h"
#include "AppDelegate.h"
#include "ParticleScene.h"

#include "StartGameScene.h"

#include "FlccMovieClip.h"
#include "FlccMovieAction.h"

#include "ConfigGet.h"
#include "MainScene.h"

#include "CcbManager.h"
#include "TextCriticalLayer.h"
#include "TextSparkLayer.h"

#include "DropItemSprite.h"
#include "LoadingLayer.h"
#include "PetLoadingLayer.h"
#include "UISupport.h"

#include "SpccMovieAction.h"
#include "SpccMovieClip.h"


#include "MapScene.h"
#include "WorldPacket.h"
#include "MaskLayer.h"

#include "CcbPetBattleLayer.h"
#include "ResourceStringClient.h"
#include "ResourcePic.h"
#include "CcbPlistShowLayer.h"
#include "CcbAltSkillEffLayer.h"
#include "SpccMovieAction.h"

#include "LRActionInterval.h"

#include "SequencePet.h"
#include "SequenceAction.h"
#include "CcbManager.h"
#include "HttpLog.h"
#include "ShowPetBattleWord.h"
#include "CCFlowFire.h"
#include "CCShake.h"
#include "EffectLayer.h"
#include "EnumDefines.h"

using namespace CocosDenshion;
HelloWorld *HelloWorld::m_currentScene = NULL;

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
//    CGameSession::Init();
    m_currentScene = this;
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
//    unsigned long fsize;
//    const char* filePath = (const char*)cocos2d::CCFileUtils::sharedFileUtils()->getFileData("UI/act_bg.png", "r", &fsize);
//    CCLog("file path:%s", filePath);
    
//    CCSprite *imgBg = CCSprite::create("ui/act_bg.png");
//    imgBg->setPosition(ccp(size.width/2, size.height/2));
//    addChild(imgBg);
    // add a "close" icon to exit the progress. it's an autorelease object
//    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//                                        "ui/CloseNormal.png",
//                                        "ui/CloseSelected.png",
//                                        this,
//                                        menu_selector(HelloWorld::menuCloseCallback) );
//    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
//    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 30);
//
//    
//
//    // position the label on the center of the screen
//    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
//    // add the label as a child to this layer
//    //this->addChild(pLabel, 1);
//    
//    CCLabelTTF *lblIP = CCLabelTTF::create("IP : 10.0.0.174", "Thonburi", 20);
//    lblIP->setPosition(ccp(size.width/2, size.height - 160));
//    addChild(lblIP);
//    CCLabelTTF *lblPort = CCLabelTTF::create("Port : 5000", "Thonburi", 20);
//    lblPort->setPosition(ccp(size.width/2, size.height - 180));
//    addChild(lblPort);
//    
//    lblConn = CCLabelTTF::create("连接服务器", "Thonburi", 25);
//    //lblOff = CCLabelTTF::create("断开服务器", "Thonburi", 14);
//    btnConnect = CCMenuItemLabel::create(lblConn, this, menu_selector(HelloWorld::onConnect));
//    btnConnect->setPosition(ccp(size.width/2, size.height/2));
//    pMenu->addChild(btnConnect);
//    
//    CCLog("%f",  CCDirector::sharedDirector()->getContentScaleFactor());
//    lblConnResult = CCLabelTTF::create(" ", "Thonburi", 20);
//    lblConnResult->setPosition(ccp(size.width/2, 80));
//    addChild(lblConnResult);
//    
//    
    //CCMenuItemLabel *btnSend = CCMenuItemLabel::create(lblSend, this, menu_selector(HelloWorld::onSend));
    //btnSend->setPosition(ccp(size.width/2, size.height/2 - 30));
    //pMenu->addChild(btnSend);
    CCLabelTTF *lblPar = CCLabelTTF::create("Particle Effect Preview", "", 25);
    lblPar->setColor(ccWHITE);
    //lblPar->enableStroke(ccRED, 2.0, true);
    lblPar->setEnableStroke(ccRED, 1.0);
    
    
    CCMenuItemLabel *btnParticle = CCMenuItemLabel::create(lblPar, this, menu_selector(HelloWorld::onParticle));
    btnParticle->setPosition(ccp(size.width - 80, size.height - 50));
    pMenu->addChild(btnParticle);
    m_byConnectStatus = E_UNCONNECTED;
    
//
//    
//    CCLabelTTF *lblCcb = CCLabelTTF::create("CCB", "Arial", 20);
//    CCMenuItemLabel *btnCcb = CCMenuItemLabel::create(lblCcb, this, menu_selector(HelloWorld::onCcbTest));
//    btnCcb->setPosition(ccp(80, size.height - 20));
//    pMenu->addChild(btnCcb);
//    
//    
//    testFlcc();
//    
//    
	CCLabelTTF* lblStartGame = CCLabelTTF::create("Start Game", "Arial", 20);
    CCMenuItemLabel* btnStartGame = CCMenuItemLabel::create(lblStartGame, this, menu_selector(HelloWorld::onStartGame));
    btnStartGame->setPosition(ccp(80, size.height - 120));
    pMenu->addChild(btnStartGame);
    
//    testFlcc();
//
//    
//    CCLabelTTF *lblScroll = CCLabelTTF::create("战斗界面", "Arial", 20);
//    lblScroll->enableShadow(CCSizeMake(4, 4), 0.9, 2.0);
//    
//    CCMenuItemLabel *btnScroll = CCMenuItemLabel::create(lblScroll, this, menu_selector(HelloWorld::onScroll));
//    btnScroll->setPosition(ccp(size.width - 80, size.height - 100));
//    pMenu->addChild(btnScroll);
//    
//    CCLabelTTF *lblArena = CCLabelTTF::create("竞技场", "Arial", 20);
//    lblArena->enableShadow(CCSizeMake(4, 4), 0.9, 2.0);
//    
//    CCMenuItemLabel *btnArena = CCMenuItemLabel::create(lblArena, this, menu_selector(HelloWorld::onArena));
//    btnArena->setPosition(ccp(size.width - 80, size.height - 150));
//    pMenu->addChild(btnArena);
//    
    CCLabelTTF *lblCritical = CCLabelTTF::create("Critical", "Arial", 20);
    CCMenuItemLabel* btnCritical = CCMenuItemLabel::create(lblCritical, this, menu_selector(HelloWorld::onCritical));
    btnCritical->setPosition(ccp(80, size.height - 50));
    pMenu->addChild(btnCritical);
//
    CCLabelTTF *lblSpark = CCLabelTTF::create("Spark", "Arial", 20);
    CCMenuItemLabel* btnSpark = CCMenuItemLabel::create(lblSpark, this, menu_selector(HelloWorld::onSpark));
    btnSpark->setPosition(ccp(80, size.height - 80));
    pMenu->addChild(btnSpark);
//
    CCLabelTTF* lblMap = CCLabelTTF::create("Map", "Arial", 20);
    CCMenuItemLabel* btnMap = CCMenuItemLabel::create(lblMap, this, menu_selector(HelloWorld::onMap));
    btnMap->setPosition(ccp(size.width - 80, size.height - 80));
    pMenu->addChild(btnMap);
    
    
    CCLabelTTF* lblCcb = CCLabelTTF::create("Ccb", "Arial", 20);
    CCLabelTTF* lblSprite = CCLabelTTF::create("Sprite", "Arial", 20);
    CCLabelTTF* lblMemory = CCLabelTTF::create("Memory", "Arial", 20);
    
    ccbTime = CCLabelTTF::create("0", "Thonburi", 18);
    spriteTime = CCLabelTTF::create("0", "Thonburi", 18);
    memoryTime = CCLabelTTF::create("0", "Thonburi", 18);
    
    CCMenuItemLabel* btnCcb = CCMenuItemLabel::create(lblCcb, this, menu_selector(HelloWorld::onClickCcb));
    CCMenuItemLabel* btnSprite = CCMenuItemLabel::create(lblSprite, this, menu_selector(HelloWorld::onClickSprite));
    CCMenuItemLabel* btnMemory = CCMenuItemLabel::create(lblMemory, this, menu_selector(HelloWorld::onClickMemory));
    
    btnCcb->setPosition(ccp(50, 250));
    btnSprite->setPosition(ccp(160, 250));
    btnMemory->setPosition(ccp(270, 250));
    
    ccbTime->setPosition(ccp(50, 200));
    spriteTime->setPosition(ccp(50, 180));
    memoryTime->setPosition(ccp(50, 160));
    
    addChild(ccbTime);
    addChild(spriteTime);
    addChild(memoryTime);
    
    pMenu->addChild(btnCcb);
    pMenu->addChild(btnSprite);
    pMenu->addChild(btnMemory);
    
//
//    
//    img1 = CCSprite::create("ui/battle_wipe.png");
//    img1->setPosition(ccp(370, 210));
//    img1->setAnchorPoint(CCPointZero);
//    addChild(img1, 999);
//    
//    CCSprite *img2 = CCSprite::create("ui/battle_wipe.png");
//    img2->setTextureRect(CCRectMake(113, 0, 10, getHeight(img2)));
//    img2->setScaleX(360/10);
//    img2->setAnchorPoint(CCPointZero);
//    img2->setPosition(ccp(getWidth(img1), 0));
//    img1->addChild(img2);
//    img1->setScaleY(270/getHeight(img1));
//    
//    
//    STC_PET_CTRL_INFO ctrlInfo;
//    ctrlInfo.petIndex = 1;
//    ctrlInfo.petNature = 1;
//    ctrlInfo.name = "魔女";
//    ctrlInfo.maxHP = 100;
//    ctrlInfo.curHP = 100;
//    ctrlInfo.maxSkillValue = 100;
//    ctrlInfo.curSkillValue = 100;
    
//    CCSprite *imgArena = CCSprite::create("ui/arena_frame.png");
//    imgArena->setPosition(CCPointZero);
//    imgArena->setAnchorPoint(CCPointZero);
//    addChild(imgArena);
//    
//    ArenaPetCtrl *ctrl = ArenaPetCtrl::create(ctrlInfo, true);
//    ctrl->setFlipX(true);
//    ctrl->setPosition(ccp(2, 135));
//    ctrl->setAnchorPoint(CCPointZero);
//    imgArena->addChild(ctrl);
    
    
//    PetIconCtrl *m_petIcon = PetIconCtrl::create();
//    m_petIcon->setPosition(ccp(50, 260));
//    m_petIcon->setScale(0.5);
//    addChild(m_petIcon);
//    CCSprite * sp = CCSprite::create("ccbresources/battle/pet_battle_angry_bar.png");
//    CCProgressTimer *tiemr = CCProgressTimer::create(sp);
//    tiemr->setMidpoint(ccp(0.95, 0.5));
//    tiemr->setPosition(ccp(160, 200));
//    tiemr->setPercentage(60);
//    tiemr->setType(kCCProgressTimerTypeRadial);
//    tiemr->setReverseProgress(true);
////    CCProgressTo *action = CCProgressTo::create(2, 0);
////    tiemr->runAction(CCRepeatForever::create((CCActionInterval *)action->copy()->autorelease()));
//    addChild(tiemr);
//    
//    
//    CCSprite * sp1 = CCSprite::create("ccbresources/battle/pet_battle_angry_bar.png");
//    sp1->setPosition(ccp(200, 200));
//    addChild(sp1);
    
    Port = 5000;
    
    
    
//    CCSprite *s = CCSprite::create("ui/ConvEndCircle_169x169.png");
//    s->setPosition(ccp(160, 200));
//    addChild(s, 10);
//    
//    s->runAction(CCRepeatForever::create(CCRotateBy::create(4, 360)));
    
    
//    CCParticleSystemQuad* par = CCParticleSystemQuad::create("ccbresources/12monthdate/universal/upup.plist");
//    par->setPosition(ccp(160, 160));
//    par->runAction(CCRepeatForever::create(CCSequence::create(CCDelayTime::create(0.25),
//                                                              CCBlink::create(0.5, 1),
//                                                              NULL)));
//    addChild(par);
//    
//    CCParticleSystemQuad* par2 = CCParticleSystemQuad::create("ccbresources/12monthdate/universal/upup.plist");
//    par2->setPosition(ccp(160, 150));
//    par2->runAction(CCRepeatForever::create(CCBlink::create(0.5, 1)));
//    addChild(par2);
//    
//    CCFlowFire *fire1 = CCFlowFire::create();
//    fire1->setPosition(ccp(160, 300));
//    addChild(fire1);
//    
    std::vector<CCPoint> arrPoint;
    arrPoint.push_back(ccp(0, 60));
    arrPoint.push_back(ccp(30, 120));
    arrPoint.push_back(ccp(90, 120));
    arrPoint.push_back(ccp(120, 60));
    arrPoint.push_back(ccp(90, 0));
    arrPoint.push_back(ccp(30, 0));
    
    CCFlowFire* fire2 = CCFlowFire::createPolygon(arrPoint);
    fire2->setPosition(ccp(100, 150));
    addChild(fire2);
//
//    arrPoint.clear();
//    arrPoint.push_back(ccp(120, 60));
//    arrPoint.push_back(ccp(90, 0));
//    arrPoint.push_back(ccp(30, 0));
//    arrPoint.push_back(ccp(0, 60));
//    arrPoint.push_back(ccp(30, 120));
//    arrPoint.push_back(ccp(90, 120));
//    CCFlowFire* fire4 = CCFlowFire::createPolygon(arrPoint);
//    fire4->setPosition(ccp(100, 150));
//    addChild(fire4);
//    
//    CCFlowFire* fire3 = CCFlowFire::createCircle(50, ccp(0, 0));
//    fire3->setPosition(ccp(160, 60));
//    addChild(fire3);
    

    return true;
}



void HelloWorld::onConnect()
{
    std::string IP = "172.16.1.114";
    
//    if (m_byConnectStatus != E_LOGIN_CONNECTED)
//    {
        if (!ConnectToServer(IP, Port))
        {
            m_byConnectStatus = E_UNCONNECTED;
            lblConnResult->setString("连接服务器失败，请重新连接！！！！！");
            return ;
        }
        else
        {
            CCLog("IP:  %s", IP.c_str());
            m_byConnectStatus = E_LOGIN_CONNECTED;
            lblConnResult->setString("连接服务器成功！！！！！");
            CCLabelTTF *lblSend = CCLabelTTF::create("点我有惊喜哦", "", 25);
            btnConnect->setLabel(lblSend);
        }
//    }
//    else
//    {
//        CGameSession::SendTest();
//    }

}
bool HelloWorld::ConnectToServer(std::string strIp, int nPort)
{
	CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
	pNetClient->End();
	//pNetClient->Connect("173.255.209.55",5555);
	return pNetClient->Connect(strIp.c_str(),nPort);
    strIp = "172.16.1.114";
}
void HelloWorld::onSend()
{
    CGameSession::SendTest();
}
void HelloWorld::onParticle(CCObject *sender)
{
    CCScene *scene = PlistShowScene::scene();
    
    CCDirector::sharedDirector()->pushScene(scene);
}
void HelloWorld::handlerTest(WorldPacket &packet)
{
    std::string test;
    packet >> test;
    lblConnResult->setString(test.c_str());
}
void HelloWorld::onScroll()
{
//    CCScene *scene = ScrollSceneTest::scene();
//    CCScene *scene = PetBattleScene::scene();
//    CCDirector::sharedDirector()->pushScene(scene);
    Port = 5000;
    onConnect();
//    CGameSession::SendReqPVEBattleInfo();
//    PetLoadingLayer::sharedLayer()->WaitForPacket();
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::testFlcc()
{

//    ShowPetBattleWord::showTextWord(E_WORD_TYPE_WIN, ccp(160, 240+100), this);
//    
//    ShowPetBattleWord::showTextWord(E_WORD_TYPE_CRIT_TEXT, ccp(0, 250), this);
//    
//    CCNode *node1 = CcbManager::sharedManager()->LoadCcbBossWarningLayer();
//    node1->setPosition(ccp(160, 100));
//    addChild(node1);
//    
//    CCNode *node2 = CcbManager::sharedManager()->LoadCcbLostLayer();
//    node2->setPosition(ccp(160, 150));
//    addChild(node2);
//    
//    CCNode *node3 = CcbManager::sharedManager()->LoadCcbFightStart();
//    node3->setPosition(ccp(160, 200));
//    addChild(node3);

//    DropItemSprite *d = DropItemSprite::create(12300004);
//    d->setPosition(ccp(160, 200));
//    addChild(d);
//    d->runAct();
    
//    DropCoinLayer *coin = DropCoinLayer::create();
//    addChild(coin);
//    coin->setPosition(ccp(150, 100));

//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( "pet/texture/hero_1-hd.plist" );
    
//    std::map<uint8, uint8> part;
//
//    for ( int i = 1; i < 20; i++) {
//        part[i] = 1;
//    }
    
//    FlccMovieClip* mc = FlccMovieClip::create( 1, part );
//    FlccMovieClip* mc = FlccMovieClip::create(8);
////
//    mc->setPosition( ccp( 100, 300 ) );
//    mc->setRotationY(180);
//    mc->setFPS(45);
//    SpccMovieClip *spcc = SpccMovieClip::create(30001);
//    spcc->setPosition(ccp(100, 290));
//    spcc->runAction( CCRepeatForever::create( SpccMovieAction::create(spcc, 60)));
//    addChild(spcc, 21);
//    
//
//    mc->runAction( CCRepeatForever::create( FlccMovieAction::create(mc, FLCC_ACT_STAND) ) );
//    addChild( mc, 20 );
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( "pet/pet_001_stand.plist");
//    std::string nameTemp = "1.png";
//    cnt = 1;
//    max = 5;
//    CCSpriteFrame* sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(nameTemp.c_str() );
//    if (sf) {
//        pet = CCSprite::createWithSpriteFrame(sf);
//        pet->setPosition(ccp(100, 200));
//        addChild(pet);
//        
//        pet_1 = CCSprite::createWithSpriteFrame(sf);
//        pet_1->setPosition(ccp(100, 120));
//        addChild(pet_1);
//        schedule(schedule_selector(HelloWorld::update), 1.0 / 8);
//        schedule(schedule_selector(HelloWorld::update2), 1.0 / 12.5);
//    }
//    else
//    {
//        CCString* str = CCString::createWithFormat("%s 没有找到~~", nameTemp.c_str());
//        CCMessageBox(str->getCString(), "error");
//    }
    
//    SequencePet * mc = SequencePet::create(144);
//    mc->setPosition(ccp(160, 200));
//    mc->runAction(CCRepeatForever::create(
//                                             CCSequence::create(
//                                                                SequenceAction::create(mc, SEQ_ACT_STAND),
////                                                                SequenceAction::create(sePet, SEQ_ACT_ATTACK),
//                                                                NULL)));
    
    
//    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, 144);
//    
//    std::vector<uint16> arrStand;
//    ResourceStringConverter::StrSplit(petCfg->strStandSize, "_", arrStand);
//    //    std::map<uint16, uint16>::iterator it = arrStand.begin();
//    CCPoint standPos;
//    CCSize standSize;
//    standPos.x = arrStand[0] * 0.5;
//    //    it++;
//    standPos.y = arrStand[1]* 0.5;
//    //    it++;
//    standSize.width = arrStand[2]* 0.5;
//    //    it++;
//    standSize.height = arrStand[3]* 0.5;
//    
//    arrStand.clear();
//    ResourceStringConverter::StrSplit(petCfg->strAtkSize, "_", arrStand);
//    //    it = arrStand.begin();
//    CCPoint atkPos;
//    CCSize atkSize;
//    atkPos.x = arrStand[0]* 0.5;
//    //    it++;
//    atkPos.y = arrStand[1]* 0.5;
//    //    it++;
//    atkSize.width = arrStand[2]* 0.5;
//    //    it++;
//    atkSize.height = arrStand[3]* 0.5;
//    
//    
//    
//    mc->setPosition(ccp(getWidth(mc) * 0.5 - standPos.x - standSize.width * 0.5, -standPos.y));
//    //    mc->setPosition(CCPointZero);
//    mc->setAnchorPoint(ccp(0.5, 0));
//    mc->setScaleY(3);
//    
//    
//    CCSprite* img = CCSprite::create();
//    img->addChild(mc);
//    img->setPosition(ccp(160, 200));
//    img->setAnchorPoint(ccp(0.5, 0));
//    addChild(img);
//    
//    CCLayerColor *layer2 = CCLayerColor::create(ccc4(0, 0, 255, 255));
//    layer2->setContentSize(CCSizeMake(150, 150));
//    layer2->setOpacity(150);
//    layer2->setPosition(ccp(0, 0));
//    layer2->setAnchorPoint(ccp(0, 0));
//    img->addChild(layer2);
//    img->setRotationY(180);
//    
//    CCLayerColor *layer1 = CCLayerColor::create(ccc4(0, 0, 0, 255));
//    layer1->setContentSize(CCSizeMake(50, 50));
//    layer1->setOpacity(150);
//    layer1->setPosition(ccp(160, 200));
//    layer1->setAnchorPoint(ccp(0.5, 0));
//    addChild(layer1);
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( "pet/pet_001_atk.plist");
//    std::string nameTemp = "atk_1.png";
//    cnt = 1;
//    cnt_1 = 1;
//    max = 9;
//
//    cnt2 = 1;
//    cnt2_1 = 1;
//    max2 = 9;
//    for (int i = 0; i < 6; i++) {
//        
//        CCSpriteFrame* sf= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(nameTemp.c_str() );
//        CCSprite *pet = CCSprite::createWithSpriteFrame(sf);
//        pet->setPosition(ccp(200 + 60 * (i / 3), 100 + (i % 3) * 60));
//        addChild(pet);
//        arrPet.push_back(pet);
//    }
//    for (int i = 0; i < 6; i++) {
////        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( "pet/pet_001_atk.plist");
////        std::string nameTemp = "atk_1.png";
//        CCSpriteFrame* sf= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(nameTemp.c_str() );
//        CCSprite *pet = CCSprite::createWithSpriteFrame(sf);
//        pet->setPosition(ccp(50 + 60 * (i / 3), 100 + (i % 3) * 60));
//        pet->setRotationY(180);
////        addChild(pet);
//        arrPet.push_back(pet);
//    }
//    schedule(schedule_selector(HelloWorld::update), 1.0 / 12);
//    if (sf2) {
//        pet2 = CCSprite::createWithSpriteFrame(sf2);
//        pet2->setPosition(ccp(200, 200));
//        addChild(pet2);
//        
//        pet2_1 = CCSprite::createWithSpriteFrame(sf2);
//        pet2_1->setPosition(ccp(200, 120));
//        addChild(pet2_1);
////        schedule(schedule_selector(HelloWorld::update), 1.0 / 10);
//    }
//    else
//    {
//        CCString* str = CCString::createWithFormat("%s 没有找到~~", nameTemp.c_str());
//        CCMessageBox(str->getCString(), "error");
//    }
    
    
    
    return;
}
void HelloWorld::update(float time)
{
//    cnt++;
//    if (cnt > max) {
//        cnt = 1;
//    }
//    CCSpriteFrame* sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("atk_%d.png", cnt)->getCString() );
//    for (int i = 0; i < arrPet.size(); i++) {
//        if (arrPet[i]) {
//            arrPet[i]->initWithSpriteFrame(sf);
//        }
//    }
//    if (sf) {
//        pet->initWithSpriteFrame(sf);
//    }
//    else
//    {
//        CCString* str = CCString::createWithFormat("%d.png 没有找到~~", cnt);
//        CCMessageBox(str->getCString(), "error");
//    }
//    
//    cnt2++;
//    if (cnt2 > max2) {
//        cnt2 = 1;
//    }
//    CCSpriteFrame* sf2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("atk_%d.png", cnt2)->getCString() );
//    if (sf2) {
//        pet2->initWithSpriteFrame(sf2);
//    }
//    else
//    {
//        CCString* str = CCString::createWithFormat("%d.png 没有找到~~", cnt2);
//        CCMessageBox(str->getCString(), "error");
//    }
}

void HelloWorld::update2(float time)
{
//    cnt_1++;
//    if (cnt_1 > max) {
//        cnt_1 = 1;
//    }
//    CCSpriteFrame* sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%d.png", cnt_1)->getCString() );
//    if (sf) {
//        pet_1->initWithSpriteFrame(sf);
//    }
//    else
//    {
//        CCString* str = CCString::createWithFormat("%d.png 没有找到~~", cnt_1);
//        CCMessageBox(str->getCString(), "error");
//    }
//    
//    cnt2_1++;
//    if (cnt2_1 > max2) {
//        cnt2_1 = 1;
//    }
//    CCSpriteFrame* sf2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("atk_%d.png", cnt2_1)->getCString() );
//    if (sf2) {
//        pet2_1->initWithSpriteFrame(sf2);
//    }
//    else
//    {
//        CCString* str = CCString::createWithFormat("%d.png 没有找到~~", cnt2_1);
//        CCMessageBox(str->getCString(), "error");
//    }
}
void HelloWorld::onCcbTest()
{
//    SpccMovieClip* e = SpccMovieClip::create(30001);
//    e->setPosition(ccp(100, 150));
//    e->runAction(CCRepeatForever::create(SpccMovieAction::create(e, 30)));
//    addChild(e);
    
//    CCScene *pScene = StartGameScene::scene();
//    addChild(StartGameScene::create());
//    addChild(pScene);
//    CCScene *pScene = MainScene::scene();
//    MainScene* pLayer = MainScene::create();
/*
    const char* actPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("act_bg.png").c_str();
    
    CCLog("fullpath = %s", actPath);
    const char* secPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("CloseNormal.png", actPath);
    CCLog("-------------");
    CCLog("from full path = %s", secPath);
    const char* wirteable = CCFileUtils::sharedFileUtils()->getWritablePath().c_str();
    CCLog("writeable path=%s", wirteable);
    CCLog("relative path=%s", CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("act_bg.png", wirteable));
    
    CCLog("-------------\n Correct Pic:%s", GET_PIC(1));
    CCLog("Wrong Pic:%s", GET_PIC(5));
    
//    PropertyList *pl = new PropertyList();
//    const char* temp = ResourceStringConverter::ConvertString(ConfigGet::GetResourceStringClient(1), (*pl) << (6) << ("string") << (16.987));
    
    uint32 k = 6;
    float f = 5.0;
    const char* str = "hello";
    
    CCLog("-------------\n String:%s", PARSE_STRING3(ConfigGet::GetResourceStringClient(1), k, str, f) );
*/
//    addChild(pLayer);
//    CCDirector::sharedDirector()->replaceScene(CCTransitionScene::create(1.0, pScene));
    
    WorldPacket packet;
    MapCtrl::HandlerMapInfoSpecial(packet);
    
//    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(1.2, pScene));
//    MainScene* pScene = new MainScene();
//    if (pScene) {
//        pScene->runTest();
//        pScene->release();
//    }

}

void HelloWorld::onCritical(CCObject *pObject)
{
//    CCNode* pNode = CcbManager::sharedManager()->LoadTextCriticalLayer(this);
//    ((TextCriticalLayer*)pNode)->mAnimationManager->runAnimationsForSequenceNamedTweenDuration("splash", 0.1f);
    
//    pCritical = TextCriticalLayer::create();
//    pCritical->mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(HelloWorld::onSpark));
//    pCritical->setAnchorPoint(ccp(1, 0));
    
//    CCNode *pNode = pCritical->getChildByTag(9);
//    pNode->setAnchorPoint(ccp(0.5, 0));
//    pNode->setPosition(ccp(0, 0));
    
//    pCritical = CCBTextCtrl::GetInstance()->getCritical();
//    pCritical->setPosition(ccp(160, 0));
//    CCLOG("will add.");
//    addChild(pCritical, 1000);
//    pCritical->release();
    
//    CCLog("1:%f, %f", pCritical->getAnchorPoint().x, pCritical->getAnchorPoint().y);
//    CCLog("2:%f, %f", pNode->getAnchorPoint().x, pNode->getAnchorPoint().y);
//    CCLog("width=%f, height=%f", pCritical->getContentSize().width, pCritical->getContentSize().height );
//    PetLoadingLayer::sharedLayer()->WaitForPacket();
//    CCScene* pScene = TestScene::scene();
//    CCDirector::sharedDirector()->replaceScene(pScene);
    
//    lrTuoyuanConfig config;
//    config.centerPosition = ccp(320*0.5, 480*0.5);
//    config.aLength = 140;
//    config.cLength = 40;
//    
//    CCSprite* pSprite = CCSprite::create("ccbresources/exp_1.png");
//    pSprite->setAnchorPoint(ccp(0.5, 0.5));
//    pSprite->setPosition(ccp(160.0, 40.0));
//    this->addChild(pSprite);
//    pSprite->runAction(LRTuoyuanBy::create(2.0f, config, 3.0/20.0));
//    
//    CCSprite* pS2 = CCSprite::create("ccbresources/exp_1.png");
//    pS2->setAnchorPoint(ccp(0.5, 0.5));
//    pS2->setPosition(ccp(160.0, 40.0));
//    this->addChild(pS2);
//    pS2->runAction(LRTuoyuanBy::create(2.0f, config, 7.0/20.0));
//    
//    CCSprite* pS3 = CCSprite::create("ccbresources/exp_1.png");
//    pS3->setAnchorPoint(ccp(0.5, 0.5));
//    pS3->setPosition(ccp(160.0, 40.0));
//    this->addChild(pS3);
//    pS3->runAction(LRTuoyuanBy::create(2.0f, config, 11.0/20.0));
//    
//    CCSprite* pS4 = CCSprite::create("ccbresources/exp_1.png");
//    pS4->setAnchorPoint(ccp(0.5, 0.5));
//    pS4->setPosition(ccp(160.0, 40.0));
//    this->addChild(pS4);
//    pS4->runAction(LRTuoyuanBy::create(2.0f, config, 3.0/4.0));
//    
//    CCSprite* pS5 = CCSprite::create("ccbresources/exp_1.png");
//    pS5->setAnchorPoint(ccp(0.5, 0.5));
//    pS5->setPosition(ccp(160.0, 40.0));
//    this->addChild(pS5);
//    pS5->runAction(LRTuoyuanBy::create(2.0f, config, 19.0/20.0));
    
//    CCScene* pScene = PetEnhanceSucScene::scene();
//    CCDirector::sharedDirector()->replaceScene(pScene);
    
//    CCHttpRequest* request = new CCHttpRequest();
//    request->setUrl("172.16.1.107:8888/upload?method=HelloWorld&line=628");
//    request->setRequestType(CCHttpRequest::kHttpGet);
//    request->setResponseCallback(this, httpresponse_selector(HelloWorld::onOver));
//    request->setTag("Get Test");
//    
//    CCHttpClient::getInstance()->send(request);
    
    HttpLog* pLog = HttpLog::GetInstance();
    pLog->addLogInfo("Method", "Hellowrd2");
    pLog->addLogInfo("bug", "Coming");
    pLog->sendLogInfo();
}

void HelloWorld::onSpark(CCObject *pObject)
{
    CCShake* shake = CCShake::create(0.2, 5);
    this->runAction(shake);
}

void HelloWorld::onArena()
{
    
}

void HelloWorld::onOver(CCHttpClient* client, CCHttpResponse* response)
{
    
//    CCDirector::sharedDirector()->getScheduler()->resumeTargets(pauseTargets);
//    CCDirector::sharedDirector()->getActionManager()->resumeTargets(pauseActions);
    
//    if (pSpark) {
//        CCLog("pSpark not null");
//        pSpark->removeFromParent();
//        pSpark = NULL;
//    }
//    if (pCritical) {
//        pCritical->removeFromParent();
//        pCritical = NULL;
//    }
//    pCritical->removeFromParentAndCleanup(true);
    CCLog("get response");
//    CCHttpResponse* response = (CCHttpResponse*)data;
    if (!response) {
        return;
    }
    if (0 != strlen(response->getHttpRequest()->getTag())) {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    int sCode = response->getResponseCode();
//    char sString[64] = {};
//    sprintf(sString, "Code: %d, tag: %s", sCode, response->getHttpRequest()->getTag());
    CCLog("Code: %d, tag: %s", sCode, response->getHttpRequest()->getTag());
    if (!response->isSucceed()) {
        // 访问失败}
        CCLog("error msg: %s", response->getErrorBuffer());
        return;
    }
    std::vector<char> *buffer = response->getResponseData();
    for (int i = 0; i < buffer->size(); i++) {
        CCLog("%c", (*buffer)[i]);
    }
    CCLog("\n");
}

void HelloWorld::onMap(CCObject *pObject)
{
//    CCScene* scene = MapScene::scene();
//    CCDirector::sharedDirector()->replaceScene(scene);
//    addChild(scene);
//    CCScene* pScene = MainScene::scene();
//    CCDirector::sharedDirector()->replaceScene(pScene);
    
//    SpccMovieClip* spcc1 = SpccMovieClip::create(1);
//    spcc1->setPosition(ccp(340, 240));
//    SpccMovieClip* spcc2 = SpccMovieClip::create(1);
//    spcc2->setPosition(ccp(-20, 240));
//    spcc2->setRotationY(180);
//    addChild(spcc1, 1000);
//    addChild(spcc2, 1000);
//    spcc1->runFPSAction(SpccMovieFPSAction::create(spcc1, 30));
//    spcc1->setVisible(true);
//    spcc2->runFPSAction(SpccMovieFPSAction::create(spcc2, 30));
//    spcc2->setVisible(true);
    
    CCDirector *director = CCDirector::sharedDirector();
//
//    pauseActions = NULL;
//    pauseTargets = NULL;
//    
//    CC_SAFE_RELEASE(pauseActions);
//    pauseActions = director->getActionManager()->pauseAllRunningActions();
//    CC_SAFE_RETAIN(pauseActions);
//    
//    CC_SAFE_RELEASE(pauseTargets);
//    pauseTargets = CCDirector::sharedDirector()->getScheduler()->pauseAllTargets();
//    CC_SAFE_RETAIN(pauseTargets);
//    
//    director->getScheduler()->resumeTarget(director->getActionManager());

   
    
    CcbAltSkillEffLayer *layer = dynamic_cast<CcbAltSkillEffLayer*>(CcbManager::sharedManager()->LoadCcbAltSkillEffLayer());
    layer->setPosition(ccp(0, 210));
    
    director->getNowScene()->addChild(layer, 100);
//    CCDirector::sharedDirector()->pause();
//    CCScene *scene = AltSkillEffScene::scene();
//    CCDirector::sharedDirector()->pushScene(scene);
//    this->runAction(CCSequence::create(CCDelayTime::create(3.0),
//                                       CCCallFunc::create(this, callfunc_selector(HelloWorld::onOver)), NULL));
}

void HelloWorld::onEnter()
{
    CCLayer::onEnter();

//    CCSprite* petCard = CCSprite::create("ccbresources/12monthdate/battle/button_batt_04.png");
//    petCard->ignoreAnchorPointForPosition(true);
//    petCard->setPosition(ccp(100, 100));
//    addChild(petCard);
//    
//    EffectLayer* eff = EffectLayer::create(E_ANI_EFFECT_BATTLE_CTRL_TOUCH, -1, 0.1);
//    eff->ignoreAnchorPointForPosition(false);
//    eff->setAnchorPoint(ccp(0, 0));
//    //    eff->setSpriteAdd();
//    eff->setPosition(petCard->getPosition() + ccp(28, 80 + 7));
//    eff->setAnchorPoint(petCard->getAnchorPoint());
//    eff->setZOrder(1);
//    petCard->getParent()->addChild(eff);
//    eff->onRun();
}
void HelloWorld::onExit()
{
    CCLayer::onExit();
    unschedule(schedule_selector(HelloWorld::update));
    unschedule(schedule_selector(HelloWorld::update2));
}
void HelloWorld::onStartGame(CCObject *pObject)
{
    CCLOG("hello world scene stack cnt:%d", CCDirector::sharedDirector()->GetSceneStackCnt());
    CCScene* scene = StartGameScene::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void HelloWorld::dataLoaded(float percent)
{
    CCLog("percent = %f", percent);
}


#define CNT 10

void HelloWorld::onClickCcb(CCObject *pObject)
{
    CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/eef_gyc_jinbidiaoluo.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/eef_gyc_jinbidiaoluo.ExportJson");
    
    CCArmature* armature = CCArmature::create("eef_gyc_jinbidiaoluo");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(ccp(160, 350));
    addChild(armature);
}

void HelloWorld::onClickSprite(CCObject *pObject)
{
    CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/eef_gyc_boss_lanbo.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/eef_gyc_boss_lanbo.ExportJson");
    
    CCArmature* armature = CCArmature::create("eef_gyc_boss_lanbo");
    armature->getAnimation()->playWithIndex(0);
    armature->setPosition(ccp(160, 200));
    addChild(armature);
}

void HelloWorld::onClickMemory(CCObject *pObject)
{
    
//    CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo("armature/eff_cj_xiashuidao1.ExportJson");
//    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("armature/eff_cj_xiashuidao1.ExportJson");
//    
//    CCArmature* armature = CCArmature::create("eff_cj_xiashuidao1");
//    armature->getAnimation()->playWithIndex(0);
//    armature->setPosition(ccp(160, 250));
//    addChild(armature);
    CCArmatureDataManager::purge();
    SceneReader::purge();
    ActionManager::purge();
    GUIReader::purge();
}
