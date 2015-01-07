//
//  FightPetSprite.h
//  HelloWorld
//
//  Created by long on 13-9-2.
//
//

#ifndef __HelloWorld__FightPetSprite__
#define __HelloWorld__FightPetSprite__

#include <iostream>
#include "Defines.h"
#include "cocos2d.h"
#include "PetBattleData.h"
#include "PetBattleControlDelegate.h"
#include "SequencePet.h"
#include "ConfigGet.h"
#include "CcbPetBattleHpBarLayer.h"
#include "CcbTextLianXieLayer.h"
USING_NS_CC;

class SpccMovieClip;
class FlccMovieClip;

class CcbPetBattleLayer;

class FightPetSprite : public CCLayerRGBA
{
public:
    FightPetSprite();
    virtual ~FightPetSprite();
    
    static FightPetSprite* create(uint16 wBattleIndex, PetBattleControlDelegate *delegate);
    
    bool init(uint16 wBattleIndex, PetBattleControlDelegate *delegate);

    virtual void onEnter();
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void setOpacity(GLubyte opacity);
    
    CC_MY_PROPERTY(int, m_CurHP, CurHP);

    //破防值}
    CC_MY_PROPERTY(int, m_DeadValue, DeadValue);
    
    CC_MY_PROPERTY(uint32, m_MaxHP, MaxHp);
    
    CC_MY_PROPERTY(uint16, m_BattleIndex, BattleIndex);
    
    CC_MY_PROPERTY(uint16, m_PetIndex, PetIndex);
    
    CC_MY_PROPERTY(uint8, m_PetNature, PetNature);
    
    CC_MY_PROPERTY(bool, m_isCanDead, IsCanDead);
    
    void setMapBuff(std::map<uint8, std::vector<STC_BUFF> > mapBuff)
    {
        m_mapBuff = mapBuff;
    };
    
    CC_MY_PROPERTY(std::vector<STC_EFFECT>, m_arrEff, ArrEff);
    
    CC_MY_PROPERTY(CCPoint, m_MyPos, MyPos);
    
    CC_MY_PROPERTY(int, m_deadTime, DeadTime);
    
    CcbPetBattleHpBarLayer* getHpBar(){return hpBar;};
    
    std::map<uint16, FightPetSprite*> getMyTeam()
    {
        return m_MyTeam;
    };
    void setMyTeam(std::map<uint16, FightPetSprite*> team)
    {
        m_MyTeam = team;
    };
    
    std::map<uint16, FightPetSprite*> getEnemyTeam()
    {
        return m_EnemyTeam;
    };
    void setEnemyTeam(std::map<uint16, FightPetSprite*> team)
    {
        m_EnemyTeam = team;
    };
    
    void setIsDead(bool isDead);
    
    bool getIsDead(void){return m_isDead;};
    CCPoint getStandPos(){return standPos;};
    CCSize getStandSize(){return standSize;};
    CCSize getAtkSize(){return atkSize;};

    SequencePet *getSequencePet(){return mc;};
    
    std::vector<STC_TRIGGERED_PSKILL> arrDeadTPSkill;
public:
    void chgSelected();
    void showBuff();
    void reflashBuff();
    void hideBuff();
    
    void doBattle();

    void startBattle(CCPoint pos, STC_BATTLE_DATA data);
    void endBattle();
    void showEff();
    
    void buffActive(std::vector<STC_BUFF_VALUE> arrBuffValue);
    
    void beHit();
    void onDodge();
    void dropBox();

    int addHP(int wValue);
    int loseHP(int wValue);

    void afterAttact();
    void afterAtk();
    
    void showHpBar();
    void hideHpBar();
    void showRunIn();
    void showLeaderEff();
    
    bool isHide(){return m_isHide;};
    
    void showPassive(std::vector<STC_TRIGGERED_PSKILL> arrTPSkill, bool flag = false);
    
    void showAltEff(CCObject* object = NULL);
    void hideAltEff();
    
    void showLianXie(uint16 add);
private:
    void showDeadPassive();
    
    CcbTextLianXieLayer* lblLXAdd;

    std::map<uint16, FightPetSprite*> m_MyTeam;
    std::map<uint16, FightPetSprite*> m_EnemyTeam;
    
    PetBattleControlDelegate *m_delegate;

    std::map<uint8, std::vector<STC_BUFF> > m_mapBuff;
    std::map<uint16, uint16> m_mapKeyFrame;
    std::map<uint16, uint16> m_mapAltKeyFrame;
    bool m_isSelected;
    
    std::vector<CCPoint> arrComboOffNorm;
    std::vector<CCPoint> arrComboOffSkill;
    
    CCNode* dustEff;
    CCNode* altEff;
    int allFrame;
    //站立标记（站立时显示buff，其他情况不显示）}
    bool m_isStand;
    bool m_isDead;
    bool m_isFighting;
    int stopFrame;
    SequencePet *mc;
    CcbPetBattleHpBarLayer *hpBar;
    CCPoint standPos;
    CCSize standSize;
    CCPoint atkPos;
    CCSize atkSize;

    std::vector<CCSprite*> arrImgBuff;

    void showHitEff();
    void showHitEff(EffectGroupConfig::STC_EFFECT_GROUP_CONFIG *effGroup, FightPetSprite *pet);
    std::string getEffPath(std::string idx);
	void onParticle(CCObject *pObject);

    void showArmEff();
    
    int itemCnt;
    
    void beforeAttact();
    
    bool is45Fps;// m_dwModelId;

    bool isParitleStop;
    
    bool m_isHide;

    int m_hpBarShowTime;
    bool isHpBarShow;
    typedef struct _STC_CUR_ATT_DATA
    {
        //计数帧}
        uint16 wFrame;
        //伤害帧}
        std::map<uint16, uint16> arrComboFrame;
        //伤害显示类型}
        uint16 wComboType;
        //第几次伤害（用来计算伤害数字显示位置）}
        int wCounter;
        //攻击包}
        STC_BATTLE_DATA bData;
        _STC_CUR_ATT_DATA()
        {
            wFrame = 1;
            wComboType = 0;
            arrComboFrame.clear();
            wCounter = -1;
            bData = *new STC_BATTLE_DATA();
        };
    }STC_CUR_ATT_DATA;
    STC_CUR_ATT_DATA m_CurBattleData;
    
    void update(float time);
    
    std::vector<CCParticleSystemQuad*> arrCurParticle;
    CCPoint getPointOffByType(uint32 skillId, uint16 wNextIndex);
    
    void initSpcc();
    
    void updateForHpBar(float time);
    
    void runStand();

    void showRunIn3();
    
    std::vector<std::string> arrWaitPassiveText;
    std::vector<CCSprite*> arrNowShowPassTextSprite;
    
    void showPassiveInBattle();
    void showPassiveEff();
    void showPassive(std::string strPassName);
    void addPassText(std::string strPassName);
    void updataWaitForShowPass(float time);
    void hidePassText(cocos2d::CCNode *node);
    void showPassSkillLayer();
    
    int waitForDoBattle;
    void updateForDoBattle(float time);
};

#endif /* defined(__HelloWorld__FightPetSprite__) */
