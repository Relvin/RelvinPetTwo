//
//  ShowPetBattleWord.h
//  HelloWorld
//
//  Created by long on 13-8-7.
//
//

#ifndef __HelloWorld__ShowPetBattleWord__
#define __HelloWorld__ShowPetBattleWord__

#include <iostream>
#include "cocos2d.h"
#include "Defines.h"
#include "PetBattleData.h"
USING_NS_CC;

class ShowPetBattleWord : public CCSprite
{
public:
    ShowPetBattleWord(){};
    ~ShowPetBattleWord(){
//        CCLog("show pet battle delloc");
//        this->release();
    };
    
    static void showWord(std::string word, CCPoint worldPos, CCNode *node = NULL);
    static void showWord(std::string word, uint16 wordType, CCPoint worldPos, CCNode *node = NULL);
    static void showTextWord(uint16 wordType, CCPoint worldPos, CCNode *node = NULL);
    
    bool init(std::string word, uint16 wordType, CCPoint worldPos, CCNode *node = NULL);
    
    bool init(uint16 wordType, CCPoint worldPos, CCNode *node = NULL);
    
    virtual void onEnter();
    virtual void onExit();
private:
    //void show(E_WORD_TYPE wordType);
    void releaseSelf();
    
    CCActionInterval *act;
};

#endif /* defined(__HelloWorld__ShowPetBattleWord__) */
