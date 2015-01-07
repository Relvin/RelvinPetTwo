//
//  ShowPetBattleWord.cpp
//  HelloWorld
//
//  Created by long on 13-8-7.
//
//

#include "ShowPetBattleWord.h"
#include "CcbManager.h"
#include "UISupport.h"

#include "TextWinLayer.h"

#include "ArmatureManager.h"


#define NormalSize  24.0
#define UpSize      36.0
#define DownSize    12.0

void ShowPetBattleWord::showWord(std::string word, cocos2d::CCPoint worldPos, CCNode *node)
{
    E_WORD_TYPE wordType = E_WORD_TYPE_NORMAL;
    showWord(word, wordType, worldPos, node);
}

void ShowPetBattleWord::showWord(std::string word, uint16 wordType, cocos2d::CCPoint worldPos, CCNode *node)
{
    ShowPetBattleWord *show = new ShowPetBattleWord();
    //show->init(word, wordType, worldPos);
    if (show && show->init(word, wordType, worldPos, node))
	{
		show->autorelease();
		//return pRet;
//        show->retain();
	}
	else
	{
		delete show;
		show = NULL;
		//return NULL;
	}

}


void ShowPetBattleWord::showTextWord(uint16 wordType, cocos2d::CCPoint worldPos, CCNode *node)
{
    ShowPetBattleWord *show = new ShowPetBattleWord();
    //show->init(word, wordType, worldPos);
    if (show && show->init(wordType, worldPos, node))
	{
		show->autorelease();
//        show->retain();
		//return pRet;
	}
	else
	{
		delete show;
		show = NULL;
		//return NULL;
	}
    
}

bool ShowPetBattleWord::init(uint16 wordType, cocos2d::CCPoint worldPos, CCNode *node)
{
    if (!CCSprite::init()) {
        return false;
    }
    CCNode *pNode = NULL;
    //addChild(lbl);
    float scale = 1.0;
    float time = 1.3;
    act = NULL;
    int zorder = 888;
//    CCLabelTTF *lbl = CCLabelTTF::create("被动技能", "", 15);
//    lbl->setColor(ccRED);
    //位置在一定范围内随机}
    CCPoint pos = worldPos;//ccp(worldPos.x + CCRANDOM_MINUS1_1() * 5, worldPos.y + CCRANDOM_0_1() * 15);
    switch (wordType) {
        case E_WORD_TYPE_CRIT_TEXT:
//            pNode = CcbManager::sharedManager()->LoadTextCriticalLayer(this);
//            pNode = TextCriticalLayer::create();
            zorder = 699;
            pNode = CcbManager::sharedManager()->LoadTextCriticalLayer();
            pos = ccp(worldPos.x + CCRANDOM_MINUS1_1() * 5, worldPos.y + CCRANDOM_0_1() * 15);

            break;
        case E_WORD_TYPE_SPARK_TEXT:
            zorder = 699;
            pNode = CcbManager::sharedManager()->LoadTextSparkLayer();
            pos = ccp(worldPos.x + CCRANDOM_MINUS1_1() * 5, worldPos.y + CCRANDOM_0_1() * 15);
            break;
        case E_WORD_TYPE_MISS_TEXT:
            zorder = 699;
            pNode = CcbManager::sharedManager()->LoadTextMissLayer();
            pos = ccp(worldPos.x + CCRANDOM_MINUS1_1() * 5, worldPos.y + CCRANDOM_0_1() * 15);
            break;
        case E_WORD_TYPE_WIN:
            pNode = CcbManager::sharedManager()->LoadCcbWinLayer();
            time = 1.8;
            break;
        case E_WORD_TYPE_FIGHT_START:
            pNode = CcbManager::sharedManager()->LoadCcbFightStart();
            time = 1.0;
            break;
        case E_WORD_TYPE_LOSE:
            pNode = CcbManager::sharedManager()->LoadCcbLostLayer();
            time = 2.5;
            break;
        case E_WORD_TYPE_BOSS_WARNING:
            pNode = CcbManager::sharedManager()->LoadCcbBossWarningLayer();
//            pNode = ArmatureManager::sharedManager()->LoadArmature("armature/ef_gyc_waning_01/eef_gyc_waning_01.ExportJson", "eef_gyc_waning_01");
            time = 3.0;
            break;
        case E_WORD_TYPE_FIGHT_FINISH:
            pNode = CcbManager::sharedManager()->LoadCcbFightFinishLayer();
            time = 3.5;
            break;
//        case E_WORD_TYPE_LIANXIE:
//            pNode = CcbManager::sharedManager()->LoadCcbTextLianXieLayer();
//            time = 0.5;
//            break;
        default:
            
            break;
    }

    if (pNode) {
//        return false;
        pNode->ignoreAnchorPointForPosition(false);
        pNode->setAnchorPoint(ccp(0.5, 0.5));
        pNode->setPosition(CCPointZero);
        addChild(pNode);
    }
    
    this->setScale(scale);
    
    this->setPosition(pos);

    act = CCSequence::create(CCDelayTime::create(time),
                                               CCHide::create(),
                                               CCCallFunc::create(this,callfunc_selector(ShowPetBattleWord::releaseSelf)),
                                               NULL);
    
    if (node) {
        node->addChild(this, zorder);
    }
    else
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(this, zorder);
    }
    return true;
}

bool ShowPetBattleWord::init(std::string word, uint16 wordType, cocos2d::CCPoint worldPos, CCNode *node)
{
    if (!CCSprite::init()) {
        return false;
    }
    act = NULL;
    CCLabelBMFont *lbl = NULL;//CCLabelBMFont::create(word.c_str(), "ui/font/battle_damage_font.fnt");
    //addChild(lbl);
    CCLabelTTF *lblPassive = NULL;
    
    //位置在一定范围内随机}
    CCPoint pos = worldPos;// ccp(worldPos.x + CCRANDOM_MINUS1_1() * 12, worldPos.y);// + CCRANDOM_MINUS1_1() * 13);
    
//    float scale = 1;
    switch (wordType) {
        case E_WORD_TYPE_NORMAL:
            lbl = CCLabelBMFont::create(word.c_str(), "ccbresources/font/bai.fnt");
            break;
        case E_WORD_TYPE_REGULATE_UP:
//            scale = UpSize / NormalSize;
            lbl = CCLabelBMFont::create(word.c_str(), "ccbresources/font/huang.fnt");
            break;
        case E_WORD_TYPE_REGULATE_DOWN:
//            scale = DownSize / NormalSize;
            lbl = CCLabelBMFont::create(word.c_str(), "ccbresources/font/hong.fnt");
            break;
        case E_WORD_TYPE_CRIT_TEXT:
            lbl = NULL;
            break;
        case E_WORD_TYPE_HP:
            lbl = CCLabelBMFont::create(word.c_str(), "ccbresources/font/lue.fnt");
            pos = ccp(worldPos.x + CCRANDOM_MINUS1_1() * 12, worldPos.y + CCRANDOM_MINUS1_1() * 15);
            break;
        case E_WORD_TYPE_SPARK_TEXT:
            lbl = NULL;
            
            break;
        case E_WORD_TYPE_PASSIVE:
            lbl = NULL;
//            lblPassive = CCLabelTTF::create(word.c_str(), "Thonburi-Bold", 14);
//            lblPassive->setColor(ccRED);
//            scale = 1.5;
            break;
        default:
            
            break;
    }
    if (lbl) {
        addChild(lbl);
    }
    if (lblPassive) {
        addChild(lblPassive);
    }
//    this->setScale(scale);
    
    this->setPosition(pos);
    this->setAnchorPoint(ccp(0.5, 0));
    
    act = CCSequence::create(CCMoveBy::create(0.04, ccp(0, 2)),
                             CCSpawn::create(CCScaleTo::create(0.12, 1.1),
                                             CCMoveBy::create(0.08, ccp(0, -4)),
                                             CCMoveBy::create(0.04, ccp(0, 2)),
                                             NULL),
                             CCDelayTime::create(0.2),
                             CCHide::create(),
                             CCCallFunc::create(this,callfunc_selector(ShowPetBattleWord::releaseSelf)),
                             NULL);
//    this->runAction(act);
    if (node) {
        node->addChild(this, 700);
    }
    else
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(this, 700);
    }
    return true;
}
void ShowPetBattleWord::onEnter()
{
    CCSprite::onEnter();
    
    if (act) {
        this->runAction(act);
    }
    
}
void ShowPetBattleWord::releaseSelf()
{
    if (this) {
        this->removeFromParentAndCleanup(true);
        //delete this;
    }
}

void ShowPetBattleWord::onExit()
{
	CCSprite::onExit();
//    CC_SAFE_RELEASE(this);
//    CCLog("ShowPetBattleWord Exit");
}