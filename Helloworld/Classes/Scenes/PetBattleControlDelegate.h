//
//  PetBattleControlDelegate.h
//  HelloWorld
//
//  Created by long on 13-8-1.
//
//

#ifndef __HelloWorld__PetBattleControlDelegate__
#define __HelloWorld__PetBattleControlDelegate__

#include <iostream>
#include "PetBattleData.h"
#include "Defines.h"
#include "FightTeam.h"
#include "cocos2d.h"
#include <map>
class FightPetSprite;
class PetBattleControlDelegate
{
public:
    //回执，掉血}
    virtual void loseHp(uint16 wBattleIndex, int loseHealth){};
    //回血}
    virtual void addHp(uint16 wIndex, int wValue){};
    //调整主动技能冷却}
    virtual void setPower(uint16 wBattleId, int wValue){};
    //设置icon状态}
    virtual void setPetCtrlSpecial(uint16 wBattleIndex){};
    //掉物品}
    virtual void dropItem(uint16 wBattleIndex, STC_ITEM_DROP item){};
    //一次攻击结束}
    virtual void endBattle(uint16 wBattleIndex, uint32 skillId){};
    //获取精灵的petSprite}
    virtual FightPetSprite* getFightPetSprite(uint16 wBattleIndex){return NULL;};
    //技能攻击}
    virtual void doSomething(uint16 wBattleIndex, uint32 skillId){};

    //获取我方宠物中间位置}
    virtual cocos2d::CCPoint getMyMiddlePos(){return cocos2d::CCPointZero;};
    //获取敌方宠物中间位置}
    virtual cocos2d::CCPoint getEnemyMiddlePos(){return cocos2d::CCPointZero;};
    //掉落箱子}
    virtual void dropBox(uint16 wEnemyIndxe){};
    //打开箱子}
    virtual void openBox(cocos2d::CCLayer *box){};
    //精灵死亡}
    virtual void showDeadEff(uint16 wBattleId){};
    
    //屏幕抖动}
    virtual void doShake(){};
    //显示大招点击时特效}
    virtual void showBattleCtrlTouchEff(uint16 wBattleId){};
    //暂停}
    virtual void pauseAll(){};
    //恢复}
    virtual void remuseAll(){};
};

#endif /* defined(__HelloWorld__PetBattleControlDelegate__) */
