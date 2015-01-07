//
//  ArmatureManager.h
//  MyGame
//
//  Created by 朱 俊杰 on 14-8-22.}
//
//

#ifndef __MyGame__ArmatureManager__
#define __MyGame__ArmatureManager__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"


USING_NS_CC;
USING_NS_CC_EXT;

enum {
    Arm_ef_boss         = 1,    // boss出现特效}
    Arm_ef_pet_enhance  = 2,    // 宠物强化大招特效}
    Arm_ef_mabi = 3,            // buff效果（麻痹）}
    Arm_ef_hunluan = 4,         // buff效果（混乱）}
    Arm_ef_fengyin = 5,         // buff效果（封印）}
    Arm_ef_bingdong = 6,        // buff效果（冰冻）}
    Arm_ef_zhongdu = 7,         // buff效果（中毒）}
    Arm_ef_zhuoshao = 8,        // buff效果（灼烧）}
    Arm_ef_GemCompoundSucc = 9,    // 宝石合成成功}
    Arm_ef_GemCompoundFail = 10,    // 宝石合成失败}
    
};

#define GET_ARM_PATH(x) ArmatureManager::GetArmaturePath(x).c_str()
#define GET_ARM_NAME(x) ArmatureManager::GetArmatureName(x).c_str()

class ArmatureManager :
public CCLayer
{
    
public:
    static ArmatureManager* sharedManager();
    ArmatureManager();
    ~ArmatureManager();
    
    CCArmature* LoadArmature(std::string path, const char* name, int idx = 0);
    
    static std::string GetArmaturePath(uint16 wArmId);
    static std::string GetArmatureName(uint16 wArmId);
    
private:
    std::string m_path;
    void callBack(CCArmature * armature, MovementEventType meType, const char * name);
};

#endif /* defined(__MyGame__ArmatureManager__) */
