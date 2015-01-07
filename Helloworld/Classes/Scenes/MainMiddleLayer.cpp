#include "MainMiddleLayer.h"
#include "CcbGMLayer.h"
#include "UISupport.h"
#include "ConfigGet.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "PetLoadingLayer.h"
#include "StageScene.h"
#include "MusicCtrl.h"
#include "EffectLayer.h"
#include "EnumDefines.h"
#include "BackCtrl.h"
#include "ChallengeCtrl.h"

MainMiddleLayer::~MainMiddleLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonBackLogin);
	CC_SAFE_RELEASE_NULL(m_pControlButtonArrowleft);
	CC_SAFE_RELEASE_NULL(m_pControlButtonArrowright);
	CC_SAFE_RELEASE_NULL(m_pControlButtonQuest);
	CC_SAFE_RELEASE_NULL(m_pLayerQuest);
	CC_SAFE_RELEASE_NULL(m_pControlButtonArena);
	CC_SAFE_RELEASE_NULL(m_pLayerArena);
	CC_SAFE_RELEASE_NULL(m_pControlButtonActive);
	CC_SAFE_RELEASE_NULL(m_pLayerActive);
	CC_SAFE_RELEASE_NULL(m_pControlButtonTower);
	CC_SAFE_RELEASE_NULL(m_pLayerTower);
    CC_SAFE_RELEASE_NULL(m_pSpriteArena);
    CC_SAFE_RELEASE_NULL(m_pSpriteQuest);
    CC_SAFE_RELEASE_NULL(m_pSpriteActive);
    CC_SAFE_RELEASE_NULL(m_pSpriteTower);
}


bool MainMiddleLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void MainMiddleLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void MainMiddleLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    addEffect();
}

void MainMiddleLayer::onExit()
{
	CCLayer::onExit();
}

void MainMiddleLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool MainMiddleLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBackLogin", CCControlButton*, this->m_pControlButtonBackLogin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonArrowleft", CCControlButton*, this->m_pControlButtonArrowleft);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonArrowright", CCControlButton*, this->m_pControlButtonArrowright);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonQuest", CCControlButton*, this->m_pControlButtonQuest);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerQuest", CCLayer*, this->m_pLayerQuest);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonArena", CCControlButton*, this->m_pControlButtonArena);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerArena", CCLayer*, this->m_pLayerArena);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonActive", CCControlButton*, this->m_pControlButtonActive);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerActive", CCLayer*, this->m_pLayerActive);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTower", CCControlButton*, this->m_pControlButtonTower);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTower", CCLayer*, this->m_pLayerTower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteQuest", CCSprite*, this->m_pSpriteQuest);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteArena", CCSprite*, this->m_pSpriteArena);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteActive", CCSprite*, this->m_pSpriteActive);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTower", CCSprite*, this->m_pSpriteTower);
	return false;
}

bool MainMiddleLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。}
    bool bRet = false;
    if (pTarget == this)
    {
        if (0 == strcmp(pMemberVariableName, "mCustomPropertyInt"))
        {
            this->mCustomPropertyInt = pCCBValue->getIntValue();
            CCLog("mCustomPropertyInt = %d", mCustomPropertyInt);
            bRet = true;
        }
        else if ( 0 == strcmp(pMemberVariableName, "mCustomPropertyFloat"))
        {
            this->mCustomPropertyFloat = pCCBValue->getFloatValue();
            CCLog("mCustomPropertyFloat = %f", mCustomPropertyFloat);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyBoolean"))
        {
            this->mCustomPropertyBoolean = pCCBValue->getBoolValue();
            CCLog("mCustomPropertyBoolean = %d", mCustomPropertyBoolean);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyString"))
        {
            this->mCustomPropertyString = pCCBValue->getStringValue();
            CCLog("mCustomPropertyString = %s", mCustomPropertyString.c_str());
            bRet = true;
        }
        
    }
    
    return bRet;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN MainMiddleLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler MainMiddleLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler MainMiddleLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBackLogin", MainMiddleLayer::onPressControlButtonBackLogin);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonArrowleft", MainMiddleLayer::onPressControlButtonArrowleft);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonArrowright", MainMiddleLayer::onPressControlButtonArrowright);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonQuest", MainMiddleLayer::onPressControlButtonQuest);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonArena", MainMiddleLayer::onPressControlButtonArena);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonActive", MainMiddleLayer::onPressControlButtonActive);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTower", MainMiddleLayer::onPressControlButtonTower);

	return NULL;
}

// Inhert CCNodeLoaderListener
void MainMiddleLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_changeFlag = false;
    m_btnFlag = false;
    arrLayer.clear();
    arrLayer.push_back(m_pLayerQuest);
    arrLayer.push_back(m_pLayerActive);
    arrLayer.push_back(m_pLayerTower);
    arrLayer.push_back(m_pLayerArena);
    
    m_curPage = 0;
    m_pLayerQuest->setVisible(true);
    m_pLayerActive->setVisible(false);
    m_pLayerTower->setVisible(false);
    m_pLayerArena->setVisible(false);
    
    CCLabelTTF* lblGm = CCLabelTTF::create("GM", "", 24);
    lblGm->setColor(ccRED);
    CCMenuItemLabel *btnGm = CCMenuItemLabel::create(lblGm, this, menu_selector(MainMiddleLayer::onGM));
    btnGm->setPosition(ccp(getRight(m_pControlButtonBackLogin) + 20, getCenterY(m_pControlButtonBackLogin)));
    CCMenu *menu = CCMenu::create(btnGm, NULL);
    menu->setPosition(CCPointZero);
#ifdef DEBUG
    addChild(menu, 1);
#else
    m_pControlButtonBackLogin->setVisible(false);
#endif
}

void MainMiddleLayer::onPressControlButtonBackLogin(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CGameSession::BackToLogin();// 爱思登出回掉}
}

void MainMiddleLayer::onPressControlButtonArrowleft(CCObject* pSender, CCControlEvent event)
{
    if (m_changeFlag || m_btnFlag) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    changePage(-1);
}

void MainMiddleLayer::onPressControlButtonArrowright(CCObject* pSender, CCControlEvent event)
{
    if (m_changeFlag || m_btnFlag) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    changePage(1);
}

void MainMiddleLayer::onPressControlButtonQuest(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (m_changeFlag || m_btnFlag) {
        return;
    }
    m_btnFlag = true;
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    StageCtrl::Get()->setKind(StageCtrl::kNormalStage);
    CGameSession::SendNormalMap();
}

void MainMiddleLayer::onPressControlButtonArena(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (m_changeFlag || m_btnFlag) {
        return;
    }
    
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ARENA);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    m_btnFlag = true;
//    CGameSession::SendEnterArenaSceneRequest();
    BackCtrl::ChangeRootScene(kArenaIndexScene);
}

void MainMiddleLayer::onPressControlButtonActive(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (m_changeFlag || m_btnFlag) {
        return;
    }
    
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ACTIVITY);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    m_btnFlag = true;
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    ChallengeCtrl::Get()->setChallengeStage(ChallengeCtrl::E_CHALLENGE_NONE);
    CGameSession::SendSpecialMapList();
}

void MainMiddleLayer::onPressControlButtonTower(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (m_changeFlag || m_btnFlag) {
        return;
    }
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_PATA);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    CGameSession::SendRequestTowerInfo();
}



void MainMiddleLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 2, false);
}
bool MainMiddleLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_changeFlag) {
        return false;
    }

    CCRect rect ;
    CCPoint p = this->convertTouchToNodeSpace(pTouch);

    CCPoint pos = ccp(getLeft(m_pLayerQuest), getBottom(m_pLayerQuest));
    rect.origin = pos;
    rect.size = m_pLayerQuest->getContentSize();
    
    if (!rect.containsPoint(p)) {
        return false;
    }
    
    m_tTouchPoint = p;
    m_fTouchLength = 0.0f;
    
    return true;
}
void MainMiddleLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    //主界面就剩一个按钮了，还滑动个毛啊}
//    CCPoint touchPointNow = this->convertTouchToNodeSpace(pTouch);
//    m_fTouchLength = touchPointNow.x - m_tTouchPoint.x;

}
void MainMiddleLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_fTouchLength < 10.0 && m_fTouchLength > -10.0) {
        return;
    }

    m_changeFlag = true;
    runAction(CCSequence::create(CCFadeOut::create(0.2),
                                 CCCallFunc::create(this, callfunc_selector(MainMiddleLayer::relocateContainer)),
                                 CCFadeIn::create(0.2),
                                 CCCallFunc::create(this, callfunc_selector(MainMiddleLayer::canChange)),
                                 NULL));
    
}
void MainMiddleLayer::relocateContainer()
{
    return;
    int off = 0;
    if (m_fTouchLength > 10.0)
    {
        off--;
    }
    else if (m_fTouchLength< -10.0)
    {
        off++;
    }
    else
    {
        return;
    }
    
    CCLayer* layer = arrLayer[m_curPage];
    layer->setVisible(false);
    m_curPage += off;
    if (m_curPage < 0)
    {
        m_curPage += arrLayer.size();
    }
    else if (m_curPage >= arrLayer.size())
    {
        m_curPage -= arrLayer.size();
    }
    layer = arrLayer[m_curPage];
    layer->setVisible(true);
}

void MainMiddleLayer::changePage(int off)
{
    m_fTouchLength = -15* off;
    runAction(CCSequence::create(CCFadeOut::create(0.2),
                                 CCCallFunc::create(this, callfunc_selector(MainMiddleLayer::relocateContainer)),
                                 CCFadeIn::create(0.2),
                                 CCCallFunc::create(this, callfunc_selector(MainMiddleLayer::canChange)),
                                 NULL));
}

void MainMiddleLayer::canChange()
{
    m_changeFlag = false;
}


void MainMiddleLayer::setOpacity(GLubyte opacity)
{
    CCLayer* layer = arrLayer[m_curPage];
    CCControlButton* btn = (CCControlButton*)layer->getChildByTag(2);
    if (btn) {
        btn->setOpacity(opacity);
    }
    CCSprite* text = (CCSprite*)layer->getChildByTag(1);
    if (text) {
        text->setOpacity(opacity);
    }
}

#define ADD_EFFECT( valueEnum, m_pLocate, m_pParent, zOrder )  \
{   \
    EffectLayer* pEffectLayer = EffectLayer::create( valueEnum, -1, fFps);  \
    pEffectLayer->ignoreAnchorPointForPosition(false);  \
    CCPoint locate = m_pLocate->getPosition();  \
    if (valueEnum == E_ANI_EFFECT_MAIN_JJC_BG) {    \
        pEffectLayer->setScale(1.1f);   \
    }   \
    if (zOrder == nEffText) {  \
        m_pLocate->setZOrder(nSprite);  \
    }   \
    pEffectLayer->setAnchorPoint(ccp(0.5f, 0.5f)); \
    pEffectLayer->setPosition(locate);    \
    m_pParent->addChild(pEffectLayer, zOrder);  \
    pEffectLayer->onRun();  \
}   \

void MainMiddleLayer::addEffect()
{
    float fFps = 1.0/10.0f;
    int nEffBg = 1, nSprite = 2, nEffText = 3;

    // 冒险背景}
    ADD_EFFECT(E_ANI_EFFECT_MAIN_ADVENTURE_BG, m_pControlButtonQuest, m_pLayerQuest, nEffBg);
    // 冒险文字流光}
    ADD_EFFECT(E_ANI_EFFECT_MAIN_ADVENTURE_TEXT, m_pSpriteQuest, m_pLayerQuest, nEffText);
//    // 精灵之塔背景}
//    ADD_EFFECT(E_ANI_EFFECT_MAIN_TOWER_BG, m_pControlButtonTower, m_pLayerTower, nEffBg);
//    // 精灵之塔文字流光}
//    ADD_EFFECT(E_ANI_EFFECT_MAIN_TOWER_TEXT, m_pSpriteTower, m_pLayerTower, nEffText);
//    // 竞技场背景}
//    ADD_EFFECT(E_ANI_EFFECT_MAIN_JJC_BG, m_pControlButtonArena, m_pLayerArena, nEffBg);
//    // 竞技场文字流光}
//    ADD_EFFECT(E_ANI_EFFECT_MAIN_JJC_TEXT, m_pSpriteArena, m_pLayerArena, nEffText);
//    // 遗迹背景}
//    ADD_EFFECT(E_ANI_EFFECT_MAIN_YIJI_BG, m_pControlButtonActive, m_pLayerActive, nEffBg);
//    // 遗迹文字流光}
//    ADD_EFFECT(E_ANI_EFFECT_MAIN_YIJI_TEXT, m_pSpriteActive, m_pLayerActive, nEffText);
    
    
//    // 遗迹增加粒子}
//    CCParticleSystemQuad* yijiPar = CCParticleSystemQuad::create("ccbresources/12monthdate/home/yiji_particle.plist");
//    yijiPar->setDuration(-1);
//    yijiPar->setAnchorPoint(ccp(0.5, 0.5));
//    yijiPar->setPosition(m_pControlButtonActive->getPosition());
//    yijiPar->setScale(0.5f);
//    m_pLayerActive->addChild(yijiPar, nSprite);
//    
//    // 精灵之塔增加粒子}
//    CCParticleSystemQuad* towerPar1 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/tower_particle.plist");
//    towerPar1->setDuration(-1);
//    towerPar1->setAnchorPoint(ccp(0.5f, 0.0f));
//    towerPar1->setPosition(ccp(m_pControlButtonTower->getPositionX(), 0.0f));
//    m_pLayerTower->addChild(towerPar1, nSprite);
//    
//    CCParticleSystemQuad* towerPar2 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/tower_particle.plist");
//    towerPar2->setDuration(-1);
//    towerPar2->setAnchorPoint(ccp(0.5f, 0.5f));
//    towerPar2->setPosition(ccp(10, 30));
//    m_pLayerTower->addChild(towerPar2, nSprite);
//    
//    CCParticleSystemQuad* towerPar3 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/tower_particle.plist");
//    towerPar3->setDuration(-1);
//    towerPar3->setAnchorPoint(ccp(0.5, 0.5));
//    towerPar3->setPosition(ccp(90, 30));
//    m_pLayerTower->addChild(towerPar3, nSprite);
}


void MainMiddleLayer::onGM(CCObject *sender)
{
    CCScene *scene = GMScene::scene();
    CCDirector::sharedDirector()->pushScene(scene);
}

