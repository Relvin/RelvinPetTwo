//
//  CPetMgr.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-2-18.}
//
//

#ifndef __HelloWorld__CPetMgr__
#define __HelloWorld__CPetMgr__

#include <iostream>
#include "Singleton.h"
#include "Defines.h"
#include <vector>
#include "WorldPacket.h"

using namespace std;

class CPetMgr : public Singleton<CPetMgr> {
    
public:
    void setEnhanceExp(uint32 dwExp) {
        dwEnhanceExp = dwExp;
    }
    void setEnhanceCrit(uint8 byCrit) {
        byEnhanceCrit = byCrit;
    }
    uint32 getEnhanceExp() {
        return dwEnhanceExp;
    }
    uint8 getEnhanceCrit() {
        return byEnhanceCrit;
    }
    
    void upgradeNext();     // 升级到下一级，刷新各项数据}
    void upgradeSpeed();    // 触摸加速升级}
    uint32 getCurMaxExp();  // 得到当前等级最大的Exp数值}
    uint32 getRemainEnhanceExp();  // 得到剩余的升级经验（总的升级经验=已经用掉的升级经验+剩余升级经验）}
    // 当剩余的升级经验==当前显示出的经验时，则停止动画}
    
    uint8 getOrgLv() {
        return byOrgLv;
    }
    uint32 getOrgExp() {
        return dwOrgExp;
    }
    uint32 getOrgHp() {
        return dwOrgHp;
    }
    uint32 getOrgAtt() {
        return dwOrgAtt;
    }
    uint32 getOrgDef() {
        return dwOrgDef;
    }
    uint32 getOrgRec() {
        return dwOrgRec;
    }
    string getPetName() {
        return strPetName;
    }
    
    void setPetOrgInfo(uint32 dwObjId, bool bFromOut = true);
    
    uint8 getNxtLv() {
        return byNxtLv;
    }
//    uint32 getNxtExp() {
//        return dwNxtExp;
//    }
    uint32 getNxtHp() {
        return dwNxtHp;
    }
    uint32 getNxtAtt() {
        return dwNxtAtt;
    }
    uint32 getNxtDef() {
        return dwNxtDef;
    }
    uint32 getNxtRec() {
        return dwNxtRec;
    }
    
    void setDataTouched() {
        m_nDataCnt--;;
    }
    int getDataTouched() {
        return m_nDataCnt;
    }
    
    void setAnimTouched() {
        m_nAnimCnt--;
    }
    int getAnimTouched() {
        return m_nAnimCnt;
    }
    void maxLvData();
    uint8 petRealLv();
private:
    uint32  dwEnhanceExp;       // 强化成功后得到的Exp}
    uint8   byEnhanceCrit;      // 强化是否是暴击}
    uint32  dwOrgExp;           // 强化前的Exp}
    uint8   byOrgLv;            // 强化前的Lv}
    uint32  dwOrgHp;            // 强化前的Hp}
    uint32  dwOrgAtt;           // 强化前的Att}
    uint32  dwOrgDef;           // 强化前的Def}
    uint32  dwOrgRec;           // 强化前的回复量}
    
//    uint32  dwNxtExp;           // 下一级的Exp}
    uint8   byNxtLv;            // 下一级等级}
    uint32  dwNxtHp;
    uint32  dwNxtAtt;
    uint32  dwNxtDef;
    uint32  dwNxtRec;
//    uint32  dwOrgLuck;          //
    
    uint32  dwHpFatio;
    uint32  dwAttFatio;
    uint32  dwDefFatio;
    uint32  dwRecFatio;
    
    float fHpFatio;
    float fAttFatio;
    float fDefFatio;
    float fRecFatio;
    float fExpFatio;
    
    uint32  dwCurMaxExp;
    uint32  dwCurObjId;
    
    string  strPetName;
    
    int m_nAnimCnt;
    int m_nDataCnt;
};

#endif /* defined(__HelloWorld__CPetMgr__) */
