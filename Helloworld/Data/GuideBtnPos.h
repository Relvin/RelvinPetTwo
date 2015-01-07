//
//  GuideBtnPos.h
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/4.
//
//

#ifndef __MyGame__GuideBtnPos__
#define __MyGame__GuideBtnPos__

#include "cocos2d.h"
#include <map>
#include "Singleton.h"

class GuideBtnPos : public Singleton<GuideBtnPos> {
    
public:
    enum kBtnEnum {
        E_BIG_ONE = 1,
        E_BIG_TWO = 2,
        E_BIG_THREE = 3,
        E_BIG_FOUR = 4,
        E_BIG_FIVE = 5,
        E_BIG_SIX = 6,
        E_ADVENTURE = 7,
        E_MAP_ONE = 8,
        E_TALK_150 = 9,
        E_STAGE_TOP = 10,
        E_BOTTOM_PET = 11,
        E_UNIT_TEAM = 12,
        E_TEAM_ONE = 13,
        E_PET_BAG_ONE = 14,
        E_BOTTOM_MAIN = 15,
        E_BOTTOM_GACHA = 16,
        E_GACHA_ADV_FREE = 17,
        E_GACHA_ONCE = 61,
        E_GACHA_BOARD_CLOSE = 62,
        // Spelical
        E_ANY_PLACE = 18,
        E_PET_INFO = 19,
        E_INFO_BACK = 20,
        E_COMMON_BACK = 21,
        E_MAIN_TEAM_TWO = 22,
        E_PET_ENHANCE = 23,
        E_ENHANCE_AUTO = 24,
        E_COMFIRM_ENHANCE = 25,
        E_PET_EVOLVE = 26,
        E_COMFIRM_EVOLVE = 27,
        E_FULL_STAR = 28,
        E_JUMP_NEXT = 29,
        E_MAP_TWO = 30,
        E_MAIN_TEAM_THREE = 31,
        E_UNIT_EQUIP = 32,
        E_EQUIP_PET_TWO = 33,
        E_EQUIP_ON = 34,
        E_EQUIP_AUTO_EHAN = 35,
        E_BOTTOM_TIAOZHAN = 36,
        E_PET_CHANLLENGE = 63,
        E_MONEY_CAT = 37,
        E_CAT_FIGHT = 38,
        E_BOTTOM_JJC = 39,
        E_JJC_START = 40,
        E_JJC_LAST = 60,
        E_JJC_EXTERN_REWARD = 41,
        E_SHENGWANG = 42,
        E_HERO_MAP = 43,
        E_EQUIP_EVOLVE = 44,
        E_TOWER = 45,
        E_GO_TOWER = 46,
        E_UNIT_BAOSHI = 47,
        E_YIJI = 48,
        E_WEATHER = 49,
        E_YIJI_POINT = 50,
        E_WANT_YIJI = 51,
        E_YIJI_BACK = 52,
        E_PET_BADGE = 53,
        E_BADGE_ON = 54,
        E_UNIT_FENJIE = 55,
        E_ADD_PET = 56,
        E_START_FENJIE = 57,
        E_COMFIRM_FENJIE = 58,
        E_MYSTERY = 59,
    };
    
    GuideBtnPos() {
        m_mapRect.clear();
    }
    virtual ~GuideBtnPos() {
        m_mapRect.clear();
    }
    
    void addNodeWorldPos(cocos2d::CCNode* _node, int _enum, bool _forceAdd = false);
    void setWorldRect(int _enum, cocos2d::CCRect _rect);
    cocos2d::CCRect worldRectWithEnum(int _enum);
private:
    typedef std::map<int, cocos2d::CCRect> MAP_RECT;
    MAP_RECT m_mapRect;
    
};

#endif /* defined(__MyGame__GuideBtnPos__) */
