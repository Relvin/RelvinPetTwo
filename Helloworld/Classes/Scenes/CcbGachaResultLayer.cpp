#include "CcbGachaResultLayer.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "CcbGachaResultEgg.h"
#include "EnumDefines.h"
#include "GachaDataMgr.h"
#include "PetCtrl.h"
#include "FlyTextLayer.h"
#include "ConfigGet.h"
#include "BackCtrl.h"
//#include "CcbPetIcon.h"
#include "CcbTujianShowLayer.h"
#include "MusicCtrl.h"
#include "CcbItemIconLayer.h"
#include "CcbGachaOpenEgg.h"

GachaResultScene::GachaResultScene()
{
    
}

GachaResultScene::~GachaResultScene()
{
    
}

CCScene* GachaResultScene::scene()
{
    CCScene* pScene = CCScene::create();
    GachaResultScene* pLayer = GachaResultScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool GachaResultScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbGachaResultLayer(this));
    return true;
}

void GachaResultScene::onEnter()
{
	CCLayer::onEnter();
}

void GachaResultScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void GachaResultScene::onExit()
{
	CCLayer::onExit();
}

void GachaResultScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

CcbGachaResultLayer::~CcbGachaResultLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteGlyph2);
	CC_SAFE_RELEASE_NULL(m_pLayerGlyph2);
	CC_SAFE_RELEASE_NULL(m_pSpriteGlyph1);
	CC_SAFE_RELEASE_NULL(m_pLayerGlyph1);
	CC_SAFE_RELEASE_NULL(m_pLayerTenBg);
	CC_SAFE_RELEASE_NULL(m_pSpritePetIcon);
	CC_SAFE_RELEASE_NULL(m_pLayerOpenEgg);
	CC_SAFE_RELEASE_NULL(m_pLayerAll);
    CC_SAFE_RELEASE_NULL(m_pLayerFinger);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbGachaResultLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbGachaResultLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGachaResultLayer", CcbGachaResultLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_result_3.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/
void CcbGachaResultLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
bool CcbGachaResultLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return isCanBack;
}
void CcbGachaResultLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    isCanBack = false;
    CCLog("back from gacha~~~~~");
    BackCtrl::BacktoUpperScene();
}

bool CcbGachaResultLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbGachaResultLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    onStart();

    m_pSpriteGlyph1->runAction(CCRepeatForever::create(CCRotateBy::create(2, 360)));
    m_pSpriteGlyph2->runAction(CCRepeatForever::create(CCRotateBy::create(4, -360)));
}

void CcbGachaResultLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbGachaResultLayer::onExit()
{
	CCLayer::onExit();
}

void CcbGachaResultLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
    CCDirector::sharedDirector()->purgeCachedData();
}

// Inhert MemberVariableAssigner
bool CcbGachaResultLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteGlyph2", CCSprite*, this->m_pSpriteGlyph2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerGlyph2", CCLayer*, this->m_pLayerGlyph2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteGlyph1", CCSprite*, this->m_pSpriteGlyph1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerGlyph1", CCLayer*, this->m_pLayerGlyph1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTenBg", CCLayer*, this->m_pLayerTenBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetIcon", CCSprite*, this->m_pSpritePetIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerOpenEgg", CcbGachaOpenEgg*, this->m_pLayerOpenEgg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerAll", CCLayer*, this->m_pLayerAll);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerFinger", CCLayer*, this->m_pLayerFinger);
	return false;
}

bool CcbGachaResultLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbGachaResultLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
//    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "onStart", CcbGachaResultLayer::onStart);
//    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "showEgg", CcbGachaResultLayer::showEgg);
//    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "showLight", CcbGachaResultLayer::showLight);
	return NULL;
}

SEL_MenuHandler CcbGachaResultLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbGachaResultLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGachaResultLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    isCanBack = false;
    
    m_pSpritePetIcon->setVisible(false);
    m_pLayerTenBg->setVisible(false);
//    m_pSpriteStar->setVisible(false);
//    m_pLabelTTFName->setVisible(false);
    
//    m_pLayerStarBg = CCLayer::create();
//    m_pLayerStarBg->setPosition(ccp(m_pSpriteStar->getPosition().x, getBottom(m_pSpriteStar) - 10));
//    m_pLayerStarBg->ignoreAnchorPointForPosition(false);
//    m_pLayerStarBg->setAnchorPoint(ccp(0.5,0));
//    m_pLayerStarBg->setContentSize(CCSizeMake(320, getHeight(m_pLayerStarBg)));
//    m_pLayerAll->addChild(m_pLayerStarBg);
    
    m_curPetCnt = g_GachaData->getCurCnt();
    
    quality = 0;
    VEC_GACHA_PET_IDX arrPet = g_GachaData->m_vecGachaPetIdx;
    //找出最高品质的}
    for (int i = 0; i < arrPet.size(); i++) {
        uint32 petId = arrPet[i].dwPetObjId;
        CPet *pet = CPetCtrl::Get()->GetPetByObjId(petId);
        if (!pet) {
            continue;
        }
        uint8 q = CPetCtrl::Get()->getPetQuality(pet->GetwIndex());
        if (q > quality) {
            quality = q;
        }
    }
    
    //十连抽最高只显示3阶品质的蛋}
    if (arrPet.size() > 0 && quality > E_GACHA_EGG_TYPE_CHAOJUE_XIYOU) {
        quality = E_GACHA_EGG_TYPE_CHAOJUE_XIYOU;
    }
    
    m_pLayerOpenEgg->loadData(quality);
    m_pLayerOpenEgg->setDelegate(this);
}

void CcbGachaResultLayer::onStart()
{
    if (m_curPetCnt >= 0) {
        m_pLayerOpenEgg->hideEgg();
        m_pLayerFinger->setVisible(false);
        showPet();
//        return;
    }
    CCParticleSystemQuad* center1 = CCParticleSystemQuad::create("ccbresources/12monthdate/gacha/center.plist");
    center1->setPosition(getCenter(m_pLayerGlyph1));
    m_pLayerAll->addChild(center1);
//    CCParticleSystemQuad* center2 = CCParticleSystemQuad::create("ccbresources/12monthdate/gacha/center1.plist");
//    center2->setPosition(getCenter(m_pLayerGlyph1));
//    m_pLayerAll->addChild(center2);
}

void CcbGachaResultLayer::showEgg()
{
    if (g_GachaData->m_dwGetMoney > 0) {
        FlyTextLayer::showText(FlyTextLayer::kMoneyAdd, g_GachaData->m_dwGetMoney, 1.0);
        g_GachaData->m_dwGetMoney = 0;
    }
    if (m_curPetCnt >= 0) {
        return;
    }
    m_pLayerFinger->setVisible(false);
    CcbGachaResultEgg *egg = dynamic_cast<CcbGachaResultEgg *>(CcbManager::sharedManager()->LoadCcbGachaResultEgg(this));
    egg->setPosition(CCPointZero);
    egg->loadData(quality);
    egg->setDelegate(this);
    m_pLayerAll->addChild(egg);
    
//    m_pSpriteGlyph1->runAction(CCFadeOut::create(0.3));
//    m_pSpriteGlyph2->runAction(CCFadeOut::create(0.3));
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_egg_show));
}

void CcbGachaResultLayer::showLight()
{
    if (m_curPetCnt >= 0) {
        return;
    }
//    uint8 type = 1;
    float time = 0.4;
    CCString* path = CCString::createWithFormat("ccbresources/12monthdate/gacha/white%d.plist", quality);
    CCParticleSystemQuad* light = CCParticleSystemQuad::create(path->getCString());
    light->setScale(3);
    if (light) {
        light->setPosition(ccp(getWidth(m_pLayerAll)*0.5, getHeight(m_pLayerAll)*0.5));
        time = MAX(time, light->getDuration());
        m_pLayerAll->addChild(light);
    }
    
    m_pLayerAll->runAction(CCSequence::create(CCDelayTime::create(time - 0.1),
                                       CCCallFunc::create(this, callfunc_selector(CcbGachaResultLayer::showPet)),
                                       NULL));
}

void CcbGachaResultLayer::showPet()
{
    //十连抽}
    if (g_GachaData->m_vecGachaPetIdx.size() > 1) {
        showTenPet();
    }
    //单个}
    else if(g_GachaData->m_vecGachaPetIdx.size() == 1)
    {
        showOnePet();
    }
}
//单个}
void CcbGachaResultLayer::showOnePet()
{
    uint32 petObjId = g_GachaData->m_vecGachaPetIdx[0].dwPetObjId;
    
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(petObjId);
    if (!pet) {
        return;
    }
    
    //跳去图鉴}
    isCanBack = false;  //防止跳转时被返回}
    CPetCtrl::Get()->setPetTujianShowId(pet->GetwIndex());
    BackCtrl::ReplaceCurScene(kShowPetTujian, kNormalTrans);
    return;

}

//十连抽}
void CcbGachaResultLayer::showTenPet()
{
    VEC_GACHA_PET_IDX arrPet = g_GachaData->m_vecGachaPetIdx;
    for (int i = 0; i <= m_curPetCnt; i++) {
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrPet[i].dwPetObjId);
        if (!pet) {
            continue;
        }
        CCPoint pos = m_pSpritePetIcon->getPosition() + ccp(i % 5 * 60 - 30, -i / 5 * 60 - 60);
        CcbItemIconLayer* icon = dynamic_cast<CcbItemIconLayer*>(CcbManager::sharedManager()->LoadCcbItemIconLayer(this));
        icon->ignoreAnchorPointForPosition(true);
        icon->loadIndexData(pet->GetwIndex());
        icon->showIconOnly();
        icon->showStarLv();
        icon->setBtnEnable(false);
        icon->setPosition(pos);
        m_pLayerAll->addChild(icon, 1);
        //底部发光}
        uint8 type = CPetCtrl::Get()->getPetQuality(pet->GetwIndex());
        CCString* str = CCString::createWithFormat("ccbresources/12monthdate/gacha/iconflash%d.plist", type);
        CCParticleSystemQuad* flash = CCParticleSystemQuad::create(str->getCString());
        if (flash) {
            flash->setPosition(pos + ccp(getWidth(icon)* 0.5, getHeight(icon)*0.5));
            flash->setAnchorPoint(ccp(0.5, 0.5));
            m_pLayerAll->addChild(flash, 0);
        }
        
    }
    
    schedule(schedule_selector(CcbGachaResultLayer::addPet), 0.5);
    m_pLayerTenBg->setVisible(true);

}
//显示十连抽的宠物icon}
void CcbGachaResultLayer::addPet(float time)
{
    VEC_GACHA_PET_IDX arrPet = g_GachaData->m_vecGachaPetIdx;
    
    m_curPetCnt++;
    
    if (m_curPetCnt >= arrPet.size()) {
        unschedule(schedule_selector(CcbGachaResultLayer::addPet));
        setCanBack();
        return;
    }
    
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrPet[m_curPetCnt].dwPetObjId);
    if (!pet) {
        return;
    }
    
    CCPoint pos = m_pSpritePetIcon->getPosition() + ccp(m_curPetCnt % 5 * 60 - 30, -m_curPetCnt / 5 * 60 - 60);
    float dur = 0.2;
    
    CcbItemIconLayer* icon = dynamic_cast<CcbItemIconLayer*>(CcbManager::sharedManager()->LoadCcbItemIconLayer(this));
    icon->ignoreAnchorPointForPosition(true);
    icon->loadIndexData(pet->GetwIndex());
    icon->showIconOnly();
    icon->showStarLv();
    icon->setBtnEnable(false);
    icon->setPosition(ccp(160 - 30, 480 - 60));
    icon->setOpacity(0);
    m_pLayerAll->addChild(icon, 2);
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_egg_show));
    
    CCSprite* light = CCSprite::create("ccbresources/12monthdate/gacha/icon_highlight.png");
    
    if (light) {
        light->setPosition(ccp(getWidth(icon)*0.5, getHeight(icon)*0.5));
        icon->addChild(light);
        
        light->runAction(CCSequence::create(CCDelayTime::create(dur),
                                            CCFadeOut::create(dur),
                                            NULL));
    }
    
    CCSprite* light2 = CCSprite::create("ccbresources/12monthdate/gacha/icon_highlight.png");
    
    if (light2) {
        light2->setPosition(ccp(getWidth(icon)*0.5, getHeight(icon)*0.5));
        icon->addChild(light2);
        
        light2->runAction(
                          CCSequence::create(
                                             CCDelayTime::create(dur),
                                             CCFadeOut::create(dur),
                                             NULL
                                             )
                          );
    }
    
    icon->runAction(
                    CCSequence::create(
                                       CCSpawn::create(
                                                       CCMoveTo::create(dur, pos),
                                                       CCRotateBy::create(dur, 4 * 360),
                                                       NULL
                                                       ),
                                       CCSpawn::create(
                                                       CCFadeIn::create(dur),
                                                       CCCallFuncND::create(this, callfuncND_selector(CcbGachaResultLayer::showPetEff), pet),
                                                       NULL
                                                       ),
                                       CCCallFunc::create(this, callfunc_selector(CcbGachaResultLayer::jumpToPetshow)),
                                       NULL
                                       )
                    );
    
    
}

//十连抽 宠物icon落地时的特效}
void CcbGachaResultLayer::showPetEff(CCNode *node, void *vptr)
{
	CPet *pet = (CPet *)vptr;
    CCPoint pos = m_pSpritePetIcon->getPosition() + ccp(m_curPetCnt % 5 * 60 - 30, -m_curPetCnt / 5 * 60 - 60);
    uint8 type = CPetCtrl::Get()->getPetQuality(pet->GetwIndex());
    CCString* str = CCString::createWithFormat("ccbresources/12monthdate/gacha/iconhit%d.plist", type);
    CCParticleSystemQuad* hit = CCParticleSystemQuad::create(str->getCString());
    if (hit) {
        hit->setPosition(pos + ccp(getWidth(node)* 0.5, getHeight(node)*0.5));
        m_pLayerAll->addChild(hit, 3);
    }
    
    
    CCParticleSystemQuad* hit1 = CCParticleSystemQuad::create("ccbresources/12monthdate/gacha/iconhitdown.plist");
    if (hit1) {
        hit1->setPosition(pos + ccp(getWidth(node)* 0.5, getHeight(node)*0.5));
        m_pLayerAll->addChild(hit1, 1);
    }
    
    str->initWithFormat("ccbresources/12monthdate/gacha/iconflash%d.plist", type);
    CCParticleSystemQuad* flash = CCParticleSystemQuad::create(str->getCString());
    if (flash) {
        flash->setPosition(pos + ccp(getWidth(node)* 0.5, getHeight(node)*0.5));
        flash->setAnchorPoint(ccp(0.5, 0.5));
        m_pLayerAll->addChild(flash, 0);
    }
}

void CcbGachaResultLayer::setCanBack()
{
    isCanBack = true;
}

void CcbGachaResultLayer::jumpToPetshow()
{
    VEC_GACHA_PET_IDX arrPet = g_GachaData->m_vecGachaPetIdx;
    if (m_curPetCnt < arrPet.size() && arrPet[m_curPetCnt].byIsNew) {
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(arrPet[m_curPetCnt].dwPetObjId);
        if (!pet) {
            setCanBack();
            return;
        }
        isCanBack = false;  //防止跳转时被返回}
        CPetCtrl::Get()->setPetTujianShowId(pet->GetwIndex());
        CcbTujianShowLayer::m_bTouchThenBack = true;
        if (arrPet.size() > 1) {
            if (curStarCnt == arrPet.size() - 1) {
                curStarCnt = -1;
            }
            g_GachaData->setCurCnt(m_curPetCnt);
            unschedule(schedule_selector(CcbGachaResultLayer::addPet));
            BackCtrl::InsertNextScene(kShowPetTujian, kNormalTrans);
            return;
        }
        else{
            m_curPetCnt = -1;
            unschedule(schedule_selector(CcbGachaResultLayer::addPet));
            BackCtrl::ReplaceCurScene(kShowPetTujian, kNormalTrans);
            return;
        }
    }
}

