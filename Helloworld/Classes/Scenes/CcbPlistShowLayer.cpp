#include "CcbPlistShowLayer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "CCScrollButton.h"
#include "FlccMovieAction.h"
#include "FlccMovieClip.h"
//#include "SequencePet.h"
#include "SequenceAction.h"
#include "ArmatureManager.h"
#include "AltEffArmature.h"
#include "PetCtrl.h"
#include "UISupport.h"
#include "EnumDefines.h"

USING_NS_CC;
USING_NS_CC_EXT;


PlistShowScene::PlistShowScene()
{
    
}
PlistShowScene::~PlistShowScene()
{
    
}
CCScene *PlistShowScene::scene()
{
    CCScene *scene = CCScene::create();
    PlistShowScene*layer = PlistShowScene::create();
    scene->addChild(layer);
    return scene;
}

bool PlistShowScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbPlistShowLayer(this));
    return true;
}


CcbPlistShowLayer::~CcbPlistShowLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteMyHpBar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMyMaxHP);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMyCurHP);
	CC_SAFE_RELEASE_NULL(m_pSpriteCoinBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteSoulBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteEggBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEnemyCurHP);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEnemyMaxHP);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCoin);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFSoul);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEgg);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAutoFight);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPlistShowLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPlistShowLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPlistShowLayer", CcbPlistShowLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/plist_show.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPlistShowLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    
	return true;
}

void CcbPlistShowLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbPlistShowLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPlistShowLayer::onExit()
{
	CCLayer::onExit();
}

void CcbPlistShowLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPlistShowLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBg", CCLayer*, this->m_pLayerBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMyHpBar", CCSprite*, this->m_pSpriteMyHpBar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMyMaxHP", CCLabelTTF*, this->m_pLabelTTFMyMaxHP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMyCurHP", CCLabelTTF*, this->m_pLabelTTFMyCurHP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCoinBg", CCSprite*, this->m_pSpriteCoinBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSoulBg", CCSprite*, this->m_pSpriteSoulBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEggBg", CCSprite*, this->m_pSpriteEggBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnemyCurHP", CCLabelTTF*, this->m_pLabelTTFEnemyCurHP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnemyMaxHP", CCLabelTTF*, this->m_pLabelTTFEnemyMaxHP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoin", CCLabelTTF*, this->m_pLabelTTFCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSoul", CCLabelTTF*, this->m_pLabelTTFSoul);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEgg", CCLabelTTF*, this->m_pLabelTTFEgg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAutoFight", CCControlButton*, this->m_pControlButtonAutoFight);

	return false;
}

bool CcbPlistShowLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPlistShowLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPlistShowLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPlistShowLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAutoFight", CcbPlistShowLayer::onPressControlButtonAutoFight);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPlistShowLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    
    CCMenu* pMenu = CCMenu::create(NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    CCLabelTTF *lblPar = CCLabelTTF::create("boss", "", 25);
    lblPar->setColor(ccWHITE);
    //lblPar->enableStroke(ccRED, 2.0, true);
    lblPar->setEnableStroke(ccRED, 1.0);
    
    
    CCMenuItemLabel *btnParticle = CCMenuItemLabel::create(lblPar, this, menu_selector(CcbPlistShowLayer::onBoss));
    btnParticle->setPosition(ccp(160, 400));
    pMenu->addChild(btnParticle);
    
    
    imgTest = CCSprite::create();
    imgTest->setPosition(ccp(-150, -150));
    addChild(imgTest);
    
    arrEffIndex.clear();
    std::map<uint32, EffectGroupConfig::STC_EFFECT_GROUP_CONFIG> map = GET_CONFIG_MAP(EffectGroupConfig);
    std::map<uint32, EffectGroupConfig::STC_EFFECT_GROUP_CONFIG>::iterator it = map.begin();
    while (it != map.end()) {
        arrEffIndex.push_back(it->second.wIndex);
        it++;
    }
    
    for (int i = 1; i < 60; i ++) {
        arrEffIndex.push_back(E_UNITE_BASE_FABIO + i);
    }
    
   
    arrPetPos[0] = ccp(100 + 0,125 + 210);
    arrPetPos[2] = ccp(100 + 0,75 + 210);
    arrPetPos[4] = ccp(100 + 0,25 + 210);
    arrPetPos[1] = ccp(30 + 0,125 + 210);
    arrPetPos[3] = ccp(30 + 0,75 + 210);
    arrPetPos[5] = ccp(30 + 0,25 + 210);
    
    arrEnemyPos[0] = ccp(320 - 100 + 0, 125 + 210);
    arrEnemyPos[2] = ccp(320 - 100 + 0, 75 + 210);
    arrEnemyPos[4] = ccp(320 - 100 + 0, 25 + 210);
    arrEnemyPos[1] = ccp(320 - 30 + 0, 125 + 210);
    arrEnemyPos[3] = ccp(320 - 30 + 0, 75 + 210);
    arrEnemyPos[5] = ccp(320 - 30 + 0, 25 + 210);
    
    for (int i = 0; i < 6; i ++) {
        uint16 petId = 114 + i;
        SequencePet *mc1 = SequencePet::create(petId);
        mc1->setPosition(CPetCtrl::Get()->ConvertFlccPos(petId, getWidth(mc1), arrPetPos[i], true));
        mc1->setAnchorPoint(ccp(0.5, 0));
        mc1->setRotationY(180);
        mc1->runAction(CCRepeatForever::create(SequenceAction::create(mc1, SEQ_ACT_STAND)));
        addChild(mc1);
        mc1->setZOrder(480 - arrPetPos[i].y);
        
        SequencePet *mc2 = SequencePet::create(petId);
        if (i == 1) {
            mc = mc2;
        }
        mc2->setPosition(CPetCtrl::Get()->ConvertFlccPos(petId, getWidth(mc2), arrEnemyPos[i]));
        mc2->setAnchorPoint(ccp(0.5, 0));
        
        mc2->runAction(CCRepeatForever::create(SequenceAction::create(mc2, SEQ_ACT_STAND)));
        addChild(mc2);
        mc2->setZOrder(480 - arrEnemyPos[i].y);
    }
    
    m_pLayerBg->setZOrder(800);
    
    CCTableView *table = cocos2d::extension::CCTableView::create(this, m_pLayerBg->getContentSize());
    table->setAnchorPoint(ccp(0, 0));
    table->setPosition(ccp(0, 0));
    table->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
    //table->setDelegate(this);
    table->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
    m_pLayerBg->addChild(table);
    
    table->reloadData();
}



void CcbPlistShowLayer::onPressControlButtonAutoFight(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CCDirector::sharedDirector()->popScene();
}

CCTableViewCell* CcbPlistShowLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell* cell = table->dequeueCell();
    int cnt = arrEffIndex.size() - idx * 4;
    if (cnt >4) {
        cnt  = 4;
    }
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }
    
    CCNode *node = CCNode::create();
//    node->setContentSize(CCSizeMake(table->getContentSize().width, 60));
    CCRect rect ;
    rect.origin = CCPointZero;
    rect.size = m_pLayerBg->getContentSize();
    
    for (int i = 0; i < cnt; i++) {
        uint32 id = arrEffIndex[idx * 4 + i];
        CCString *str = CCString::createWithFormat("%d", id);
        CCLabelTTF *lbl = CCLabelTTF::create(str->getCString(), FONT_HEL, 20);
        CCSprite *img = CCSprite::create("ccbresources/12monthdate/button/button_blue2_1.png");
        CCScale9Sprite *spriteNormal = CCScale9Sprite::create("ccbresources/12monthdate/button/button_blue2_1.png");
        CCScale9Sprite *spriteDis = CCScale9Sprite::create("ccbresources/12monthdate/button/button_blue2_2.png");
        CCScrollButton *btn = CCScrollButton::create(lbl, spriteNormal);
        btn->setBackgroundSpriteForState(spriteDis, CCControlStateHighlighted);
        btn->setContentSize(img->getContentSize());
        btn->setPreferredSize(img->getContentSize());
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbPlistShowLayer::onTab), CCControlEventTouchUpInside);
        btn->setTag(id);
        btn->setPosition(ccp(i * 80 + 40, 20));
        btn->setAnchorPoint(ccp(0.5, 0.5));
        btn->setClipRect(rect);
        node->addChild(btn);
    }
    node->setPosition(ccp(0, 3));
    node->setAnchorPoint(CCPointZero);
    cell->addChild(node, 1);
    return cell;
}
unsigned int CcbPlistShowLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    if (arrEffIndex.size() % 4 > 0) {
        return arrEffIndex.size() / 4 + 1;
    }
    return arrEffIndex.size() / 4;
}

void CcbPlistShowLayer::onTab(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event)
{
//    int idx = ((CCScrollButton*)pSender)->getTag();
    uint32 wIndex = ((CCScrollButton*)pSender)->getTag();//arrEffIndex[idx - 1];
    
    if (wIndex > E_UNITE_BASE_FABIO) {
        
        if (getChildByTag(121)) {
            getChildByTag(121)->removeFromParentAndCleanup(true);
        }
        
        CCString* str1 = CCString::createWithFormat("pet_60act_%03d", wIndex%E_UNITE_BASE_FABIO);
        
        CCString* str = CCString::createWithFormat("pet/pet_alt_eff/%s/%s.csb", str1->getCString(), str1->getCString());
        AltEffArmature* pPetEnhance = AltEffArmature::create(str->getCString(), str1->getCString());
        
        if (!pPetEnhance) {
            
            str->initWithFormat("%s is Error!!!!!!!", str1->getCString());
            CCMessageBox(str->getCString(), "Error");
            return;
        }
        CCPoint pos = arrEnemyPos[2] + ccp(0, getHeight(mc)*0.5);
        switch (wIndex%E_UNITE_BASE_FABIO % 4) {
            case 1:

                break;
            case 2:
                pos = pos + ccp(35, 0);
                break;
            case 3:
//                pos = pos + ccp(35, 0);
                break;
            case 0:
                pos = pos + ccp(35, 0);
                break;
                
            default:
                break;
        }
        pPetEnhance->setRotationY(180);
        pPetEnhance->setPosition(pos);
        this->addChild(pPetEnhance, 1199, 121);
        
        return;
    }
    
    
    EffectGroupConfig::STC_EFFECT_GROUP_CONFIG *config = GET_CONFIG_STC(EffectGroupConfig, wIndex);
    CCArray *arrAct = CCArray::create();
    if (!config) {
        CCString *error = CCString::createWithFormat("ID : %d group not found ", wIndex);
        CCMessageBox(error->getCString(), "Error");
        return;
    }
    for (int i = 0; i < config->effParts.size(); i++) {
        std::string str = config->effParts[i];
        
        if (str == "0" || str == "") {
//            CCString *error = CCString::createWithFormat("第%d 个 effId 为0 或者为空", i);
//            CCMessageBox(error->getCString(), "Warning");
            continue;
        }
        CCParticleSystemQuad * particle = CCParticleSystemQuad::create(getEffPath(str).c_str());
        if (!particle) {
//            CCMessageBox("plist %s no found~", getEffPath(str).c_str());
            return;
        }
        CCLabelTTF *lbl = CCLabelTTF::create(getEffPath(str).c_str(), "", 20);
        lbl->setPosition(ccp(160, 420));
        lbl->runAction(CCSequence::create(CCMoveBy::create(1, ccp(0, 30)),
                                          CCCallFuncN::create(this, callfuncN_selector(CcbPlistShowLayer::removeLabel)),
                                          NULL));
        addChild(lbl, 900);
        
        particle->setAutoRemoveOnFinish(true);
        //particle->getDuration();
        if (config->byAltEffType == 1) //有发射点的全体，需取反}
        {
            CCPoint pos = ccpAdd(mc->getPosition(), ccp(30, 20));
            particle->setPosition(ccp(pos.x, pos.y + 20));
        }
        else if (config->byAltEffType == 2) //无发射点的全体}
        {
            
        }
        else if (config->byAltEffType == 0) //单体}
        {
            particle->setPosition(ccpAdd(mc->getPosition(),ccp(0, 20)));
        }
        //particle->setScale(0.5);
        
        if (config->byType == 2) {
            arrAct->addObject(CCCallFuncO::create(this, callfuncO_selector(CcbPlistShowLayer::onParticle), particle));
            arrAct->addObject(CCDelayTime::create(particle->getDuration()));
        }
        else if(config->byType == 1)
        {
            addChild(particle, 600);
        }
    }
    if (arrAct->count() > 0) {
        imgTest->runAction(CCSequence::create(arrAct));
    }
}
void CcbPlistShowLayer::onParticle(CCObject *pObject)
{
	CCParticleSystemQuad* particle = (CCParticleSystemQuad *)pObject;
    addChild(particle, 600);
//    particle->setZOrder(600);
}

std::string CcbPlistShowLayer::getEffPath(std::string idx)
{
    char buf[256];
    sprintf(buf, "effect/effect_%s.plist",idx.c_str());
    return buf;
}

void CcbPlistShowLayer::removeLabel(cocos2d::CCNode *node)
{
    node->removeFromParentAndCleanup(true);
}


void CcbPlistShowLayer::onBoss(CCObject* obj){
    
//    CCNode* pPetEnhance = ArmatureManager::sharedManager()->LoadArmature(GET_ARM_PATH(Arm_ef_bingdong), GET_ARM_NAME(Arm_ef_bingdong));
    if (getChildByTag(121)) {
        getChildByTag(121)->removeFromParentAndCleanup(true);
    }
    
    
    CCString* str = CCString::createWithFormat("pet/pet_alt_eff/%s/%s.csb", "pet_60act_002", "pet_60act_002");
    AltEffArmature* pPetEnhance = AltEffArmature::create(str->getCString(), "pet_60act_002");
    
    
    pPetEnhance->setPosition(ccp(160, 240));
    this->addChild(pPetEnhance, 1199, 121);
}
