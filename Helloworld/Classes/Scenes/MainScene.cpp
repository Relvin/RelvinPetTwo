#include "MainScene.h"
#include "CcbManager.h"
#include "CcbEvolveLayer.h"
#include "GuideData.h"
#include "GameSession.h"
#include "Role.h"
#include "GlobalData.h"

USING_NS_CC;
USING_NS_CC_EXT;


MainScene::~MainScene() {
    
}


CCScene* MainScene::scene()
{
	// scene() was called after init()
	CCScene* scene = CCScene::create();
    MainScene* pLayer = MainScene::create();
    pLayer->setTag(1);
    scene->addChild(pLayer);
    
	return scene;
}

bool MainScene::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    addChild(CcbManager::sharedManager()->LoadMainLayer(this),1,1);
    GlobalData::bCloseForce = false;
	return true;
}
void MainScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void MainScene::onExit()
{
    this->stopAllActions();
	CCLayer::onExit();
}

void MainScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
    
}

void MainScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
//                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(MainScene::addGuide)),
                                       NULL
                                       )
                    );
}

void MainScene::addGuide() {
    CRole* pRole = CGameSession::GetRole();
    int wTrigger = pRole->GetwGuideTrigger();
    
    bool bConnect = false;
    switch (wTrigger) {
        case GuideData::E_GUIDE_TRIGGER_FIR_END_ATTACK:
            wTrigger = GuideData::E_GUIDE_TRIGGER_FIR_ATTACK;
            break;
        case GuideData::E_GUIDE_TRIGGER_SEC_END_ATTACK:
            wTrigger = GuideData::E_GUIDE_TRIGGER_SEC_ATTACK;
            break;
        case GuideData::E_GUIDE_TRIGGER_THI_END_ATTACK:
            wTrigger = GuideData::E_GUIDE_TRIGGER_THI_TALK_1;
            break;
        case GuideData::E_GUIDE_TRIGGER_FOUR_END_ATTACK:
            wTrigger = GuideData::E_GUIDE_TRIGGER_FOUR_ATTACK;
            break;
        case GuideData::E_GUIDE_TRIGGER_4_TEAM:
            wTrigger = GuideData::E_GUIDE_TRIGGER_SEC_ATTACK;
            break;
        case GuideData::E_GUIDE_TRIGGER_3_GACHA:
            // 抽奖完了
            wTrigger = GuideData::E_GUIDE_TRIGGER_MAIN_TEAM;
            break;
        case GuideData::E_GUIDE_TRIGGER_1_PRESS_MAIN:
            wTrigger = GuideData::E_GUIDE_TRIGGER_PET_ENHANCE;
            break;
        case GuideData::E_GUIDE_TRIGGER_2_PRESS_MAIN:
            wTrigger = GuideData::E_GUIDE_TRIGGER_PET_EVOLVE;
            break;
        case GuideData::E_GUIDE_TRIGGER_PET_ENHANCE_1_TALK:
            wTrigger = GuideData::E_GUIDE_TRIGGER_FOUR_ATTACK;
            break;

        case GuideData::E_GUIDE_TRIGGER_END_PET_EVOLVE:
            wTrigger = GuideData::E_GUIDE_TRIGGER_FIVE_ATTACK;
            break;
        case GuideData::E_GUIDE_TRIGGER_GET_STAR: {
            if (wTrigger < GuideData::E_SYS_GUIDE_EQUIP) {
                wTrigger = GuideData::E_GUIDE_END_TRIGGER;
                bConnect = true;
            }
        }
        case GuideData::E_GUIDE_TRIGGER_1_GET_STAR:
            wTrigger = GuideData::E_GUIDE_END_TRIGGER;
            bConnect = true;
        default:
            break;
    }
    GuideData::GetInstance()->setStepId(wTrigger);
    if (bConnect) {
        GuideData::GetInstance()->connectToServer();
    }
    

    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_FIR_ATTACK,
                                             GuideData::E_GUIDE_TRIGGER_TEAM,
                                             GuideData::E_GUIDE_TRIGGER_SEC_ATTACK,
                                             GuideData::E_GUIDE_TRIGGER_GACHA,
                                             GuideData::E_GUIDE_TRIGGER_MAIN_TEAM,
                                             GuideData::E_GUIDE_TRIGGER_THI_TALK_1,
                                             GuideData::E_GUIDE_TRIGGER_PET_ENHANCE,
                                             GuideData::E_GUIDE_TRIGGER_FOUR_ATTACK,
                                             GuideData::E_GUIDE_TRIGGER_PET_EVOLVE,
                                             GuideData::E_GUIDE_TRIGGER_FIVE_ATTACK,
                                             
                                             GuideData::E_SYS_GUIDE_HERO,
                                             NULL
                                             );
}




