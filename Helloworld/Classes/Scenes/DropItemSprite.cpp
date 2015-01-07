//
//  DropItemSprite.cpp
//  HelloWorld
//
//  Created by long on 13-9-11.
//
//

#include "DropItemSprite.h"
#include "CcbManager.h"
//#include "DropCoinLayer.h"
//#include "DropHeartLayer.h"
//#include "DropKarmaLayer.h"
#include "EnumDefines.h"
#include "ItemDataMgr.h"
#include "PacketDataMgr.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

DropItemSprite::~DropItemSprite()
{
//    CCLog("~DropItemSprite");
}

void DropItemSprite::onExit()
{
    CCSprite::onExit();
}

DropItemSprite* DropItemSprite::create(uint32 itemType)
{
    DropItemSprite *item = new DropItemSprite();
    
    if (item && item->init(itemType)) {
        item->autorelease();
        return item;
    }
    else
    {
        item = NULL;
        delete item;
        return NULL;
    }
}

bool DropItemSprite::init(uint32 itemType)
{
    if (!CCSprite::init()) {
        return false;
    }
    CCNode *node = getItemByType(itemType);
    if (node) {
        node->setPosition(ccp(0.5, 0.5));
//        this->setContentSize(node->getContentSize());
        addChild(node);
        
    }
    return true;
}


CCNode* DropItemSprite::getItemByType(uint32 itemType)
{
    CCSprite *node = CCSprite::create();
    std::string plistName = "";
    std::string picName = "";
    switch (itemType / E_UNITE_BASE_FABIO) {
        case E_UNITE_TYPE_PET:
            plistName = "ccbresources/12monthdate/cartoon/drop_egg.plist";
            picName = "pic_egg";
            
            break;
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_EQUIP:
        case E_UNITE_TYPE_RUNES:
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_drop_item));
            picName = g_PacketDataMgr->GetObjectIconByIndex(itemType);
            break;
        case E_UNITE_TYPE_GEM:

            break;
        case E_UNITE_TYPE_SPECIAL:
            switch (itemType % E_UNITE_BASE_FABIO) {
                case E_SPECIAL_ID_COIN:                 //金币}
                    plistName = "ccbresources/12monthdate/cartoon/drop_money.plist";
                    picName = "pic_money";
                    break;
                case E_SPECIAL_ID_FARM_RES:             //魂}
                    plistName = "ccbresources/12monthdate/cartoon/drop_crystal.plist";
                    picName = "pic_crystal";
                    break;
                case E_SPECIAL_ID_HEART:                //心珠}
                    plistName = "ccbresources/12monthdate/cartoon/drop_heart.plist";
                    picName = "pic_heart";
                    break;
                    
                default:
                    break;
            }
            break;
        default:
            
            break;
    }
    
    if (plistName != "") {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName.c_str());
        CCArray *arr = CCArray::create();
        for (int i = 1; i <= 3; i++) {
            std::string path = CCString::createWithFormat("%s_%d.png", picName.c_str(), i)->getCString();
            CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path.c_str());
            if (!sf) {
                
                continue;
            }
            arr->addObject(sf);
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(arr, 10.0 / 60.0);
        CCAnimate *animate = CCAnimate::create(animation);
        if (animate) {
            this->runAction(CCRepeatForever::create(animate));
        }
    }
    else
    {
        this->setScale(0.5);
        this->initWithFile(picName.c_str());// setTexture(CCTextureCache::sharedTextureCache()->addImage(picName.c_str()));
    }
    
    return node;
}

void DropItemSprite::runAct()
{
    
    float x = CCRANDOM_MINUS1_1();
    if (x < 0) {
        x = -1;
    }
    else
    {
        x = 1;
    }

    int w = 3 + CCRANDOM_MINUS1_1()*20;

    CCActionInterval *act = CCSequence::create(
                                               CCSpawn::create(
                                                               CCRotateBy::create(0.6, 330*x),
                                                               CCSequence::create(
                                                                                  CCEaseOut::create(CCMoveBy::create(0.2, ccp(w*x, 30)), 0.5),
                                                                                  CCDelayTime::create(0.2),
                                                                                  CCEaseIn::create(CCMoveBy::create(0.2, ccp(5*x, -35)),0.5),
                                                                                  NULL),
                                                               NULL),
                                               CCSpawn::create(
                                                               CCRotateBy::create(0.3, 30*x),
                                                               CCSequence::create(
                                                                                  CCMoveBy::create(0.1, ccp(4*x+CCRANDOM_MINUS1_1(), 5)),
                                                                                  CCMoveBy::create(0.2, ccp(2*x+CCRANDOM_0_1()*5*x, CCRANDOM_MINUS1_1()*10 + -10)),
                                                                                  NULL),
                                                               NULL),
                                               NULL);
    this->runAction(act);

}
