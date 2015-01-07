//
//  ParticleSence.cpp
//  HelloWorld
//
//  Created by long on 13-7-15.
//
//

#include "ParticleScene.h"
#include "CCScrollButton.h"
#include "ConfigData.h"
#include "ConfigGet.h"
#include "ResourcePic.h"
#include "FlccMovieAction.h"
ParticleScene::ParticleScene()
{
    
}
ParticleScene::~ParticleScene()
{
    //cur_Particle = NULL;
}

CCScene *ParticleScene::scene()
{
    CCScene *scene = CCScene::create();
    
    ParticleScene *layer = ParticleScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ParticleScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    int fontS = 20;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    imgTest = CCSprite::create(GET_PIC(Btn_emblem));
    imgTest->setPosition(ccp(0-winSize.width, 0-winSize.height));
    addChild(imgTest);
    
    
    CCLabelTTF *lblBack = CCLabelTTF::create("BACK", "", fontS);
    CCMenuItemLabel *btnBack = CCMenuItemLabel::create(lblBack, this, menu_selector(ParticleScene::onBack));
    btnBack->setPosition(ccp(winSize.width - 30, winSize.height-30));
    
    CCMenu *menu = CCMenu::createWithItem(btnBack);
    menu->setPosition(CCPointZero);
    addChild(menu);
    
    arrEffIndex.clear();
    std::map<uint32, EffectGroupConfig::STC_EFFECT_GROUP_CONFIG> map = GET_CONFIG_MAP(EffectGroupConfig);
    std::map<uint32, EffectGroupConfig::STC_EFFECT_GROUP_CONFIG>::iterator it = map.begin();
    while (it != map.end()) {
        arrEffIndex.push_back(it->second.wIndex);
        it++;
    }
    
    
//    CCString *str = CCString::createWithFormat("pet/texture/hero_%d-hd.plist", 11);
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(str->getCString());
//    //        FlccMovieClip* mc = FlccMovieClip::create( 5 + i );
//    
//    std::map<uint8, uint8> part;
//    //        part[1] = 22;
//    //        part[2] = 1;
//    for ( int i = 1; i <= 8; i++) {
//        part[i] = 1;
//        if (i == 3) {
//            part[i] = 2;
//        }
//    }
    
    mc = FlccMovieClip::create(3);
    
//    mc->setScale(0.4);
    //mc->setFlipX(true);
    mc->setRotationY(180);
    mc->setPosition(ccp(100, 320));
    
    mc->runAction( CCRepeatForever::create(FlccMovieAction::create(mc, FLCC_ACT_STAND)));
    addChild(mc);
    
    cocos2d::extension::CCTableView *table = cocos2d::extension::CCTableView::create(this, CCSizeMake(50, 400));
    table->setAnchorPoint(ccp(0, 0));
    table->setPosition(ccp(10, 40));
    table->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
    //table->setDelegate(this);
    table->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
    addChild(table);
    
    table->reloadData();
    return true;
}
cocos2d::extension::CCTableViewCell* ParticleScene::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    cocos2d::extension::CCTableViewCell* cell = table->dequeueCell();
    if (!cell) {
        cell = new cocos2d::extension::CCTableViewCell();
        
        CCString *str = CCString::createWithFormat("%d", arrEffIndex[idx]);
        CCLabelTTF *lbl = CCLabelTTF::create(str->getCString(), "", 25);
        lbl->setTag(1);
        CCMenuItemLabel *btn = CCMenuItemLabel::create(lbl, this, menu_selector(ParticleScene::onTab));
        btn->setTag(1);
        btn->setPosition(ccp(25, 15));
        
        CCMenu * menu = CCMenu::create(btn, NULL);
        menu->setTag(1);
        menu->setPosition(CCPointZero);
        cell->addChild(menu);
        cell->setTag(idx);
    }
    CCLabelTTF *lbl = (CCLabelTTF*)(cell->getChildByTag(1)->getChildByTag(1)->getChildByTag(1));
    CCString *str = CCString::createWithFormat("%d", arrEffIndex[idx]);
    lbl->setString(str->getCString());
    cell->setTag(idx);
    return cell;
}
unsigned int ParticleScene::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return GET_CONFIG_MAP(EffectGroupConfig).size();
}

void ParticleScene::onTab(CCObject *sender)
{
    int idx = ((CCMenuItemLabel*)sender)->getParent()->getParent()->getTag();
    uint16 wIndex = arrEffIndex[idx];
    EffectGroupConfig::STC_EFFECT_GROUP_CONFIG *config = GET_CONFIG_STC(EffectGroupConfig, wIndex);
    CCArray *arrAct = CCArray::create();
    for (int i = 0; i < config->effParts.size(); i++) {
        std::string str = config->effParts[i];
        
        if (str == "0") {
            continue;
        }
        CCParticleSystemQuad * particle = CCParticleSystemQuad::create(getEffPath(str).c_str());
        particle->setAutoRemoveOnFinish(true);
        //particle->getDuration();
        if (config->byAltEffType) {
            //particle->setPosition(ccp(160, 360));
        }
        else
        {
            particle->setPosition(mc->getPosition());
        }
        //particle->setScale(0.5);
        
        if (config->byType == 2) {
            arrAct->addObject(CCCallFuncO::create(this, callfuncO_selector(ParticleScene::onParticle), particle));
            arrAct->addObject(CCDelayTime::create(particle->getDuration()));
        }
        else if(config->byType == 1)
        {
            addChild(particle);
        }
    }
    if (arrAct->count() > 0) {
        imgTest->runAction(CCSequence::create(arrAct));
    }
}
void ParticleScene::onParticle(CCObject *pObject)
{
	CCParticleSystemQuad *particle = (CCParticleSystemQuad*)pObject;
    addChild(particle);
}
void ParticleScene::onBack(CCObject *pObject)
{
    CCDirector::sharedDirector()->popScene();
}
std::string ParticleScene::getEffPath(std::string idx)
{
    char buf[256];
    sprintf(buf, "effect/effect_%s.plist",idx.c_str());
    return buf;
}