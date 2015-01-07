//
//  CPetMgr.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-2-18.}
//
//

#include "CPetMgr.h"
#include "Pet.h"
#include "ConfigData.h"
#include "PetCtrl.h"
#include "game_config.h"
#include "FlyTextLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

void CPetMgr::maxLvData()
{
    CPet* pPet = CPetCtrl::Get()->GetPetByObjId(dwCurObjId);
    if (!pPet) {
        CCMessageBox("Can't find pet", "CPetMgr");
        return;
    }
    PetConfig::STC_PET_CONFIG *pPetCfg = GET_CONFIG_STC(PetConfig, pPet->GetwIndex());
    if (!pPetCfg) {
        return;
    }
    
    byNxtLv = pPet->GetbyLv();  // should equals 80(Max_Lv)
    assert(byNxtLv == Max_Lv);
    
    dwNxtHp = pPet->GetdwHpValue();
    dwNxtAtt = pPet->GetdwAttackValue();
    dwNxtDef = pPet->GetdwDefenseValue();
    dwNxtRec = pPet->GetdwRecoverValue();
    
    byOrgLv = byNxtLv - 1;
    dwNxtHp = dwOrgHp - fHpFatio;
    dwNxtAtt = dwOrgAtt - fAttFatio;
    dwNxtDef = dwOrgDef - fDefFatio;
    dwNxtRec = dwOrgRec - fRecFatio;
    
    ExpConfig::STC_EXP_CONFIG* pExpCfg = GET_CONFIG_STC(ExpConfig, byNxtLv);
    if (!pExpCfg) {
        return;
    }
    
    fExpFatio = pPetCfg->dwExpFatio / 100.0f;
    dwCurMaxExp = pExpCfg->dwPetExp * fExpFatio; // 获取当前最大Max值}
    
    dwOrgExp = dwCurMaxExp;
}

void CPetMgr::setPetOrgInfo(uint32 dwObjId, bool bFromOut)
{
    dwCurObjId = dwObjId;
    CPet * pPet = CPetCtrl::Get()->GetPetByObjId(dwObjId);
    if (!pPet) {
        CCMessageBox("jz", "Error");
        return;
    }
    
    PetConfig::STC_PET_CONFIG *pPetCfg = GET_CONFIG_STC(PetConfig, pPet->GetwIndex());
    if (!pPetCfg) {
        return;
    }
    
    // 将强化前的值保存}
    dwOrgExp = pPet->GetcurExp();
    byOrgLv = pPet->GetbyLv();

    //成长率不能有小数，此处被配成了小数，因此只读取到整数部分}
    dwHpFatio = pPetCfg->dwHpChg;
    dwAttFatio = pPetCfg->dwAttackChg;
    dwDefFatio = pPetCfg->dwDeffenseChg;
    dwRecFatio = pPetCfg->dwRecoverChg;
    
    float EPS = 1000.0;
    fHpFatio = (float)dwHpFatio / EPS;
    fAttFatio = (float)dwAttFatio / EPS;
    fDefFatio = (float)dwDefFatio / EPS;
    fRecFatio = (float)dwRecFatio / EPS;
    
//    CCLog("Fatio Hp:%f, Att:%f, Def:%f, Rec:%f", fHpFatio, fAttFatio, fDefFatio, fRecFatio);

    dwOrgHp = pPet->GetdwHpValue();
    dwOrgAtt = pPet->GetdwAttackValue();
    dwOrgDef = pPet->GetdwDefenseValue();
    dwOrgRec = pPet->GetdwRecoverValue();
    
    byNxtLv = byOrgLv + 1;

    dwNxtHp = dwOrgHp + fHpFatio;
    dwNxtAtt = dwOrgAtt + fAttFatio;
    dwNxtDef = dwOrgDef + fDefFatio;
    dwNxtRec = dwOrgRec + fRecFatio;
    
//    CCLog("Pet[%d]Org Info Exp:%d, Lv:%d, Hp:%d, Att:%d, Def:%d, Rec:%d", pPet->GetwIndex(), dwOrgExp, byOrgLv, dwOrgHp, dwOrgAtt, dwOrgDef, dwOrgRec);
//    CCLog("Pet[%d]Nxt Lv:%d, Hp:%d, Att:%d, Def:%d, Rec:%d", pPet->GetwIndex(), byNxtLv, dwNxtHp, dwNxtAtt, dwNxtDef, dwNxtRec);
    
    ExpConfig::STC_EXP_CONFIG* pExpCfg = GET_CONFIG_STC(ExpConfig, byOrgLv);
    if (!pExpCfg && byOrgLv == Max_Lv) {
        FlyTextLayer::showTips(GET_STR(Str_max_pet_lv));
        return;
    }
    
    fExpFatio = pPetCfg->dwExpFatio / 100.0f;
    dwCurMaxExp = pExpCfg->dwPetExp * fExpFatio; // 获取当前最大Max值}
    
    strPetName = pPetCfg->strName;
    if (bFromOut) {
        m_nDataCnt = 3;
        m_nAnimCnt = 2;
    }
}

uint32 CPetMgr::getCurMaxExp()
{
    return dwCurMaxExp;
}

void CPetMgr::upgradeNext()
{
    byOrgLv = byNxtLv;
    dwOrgExp = 0;
    dwOrgHp = dwNxtHp;
    dwOrgAtt = dwNxtAtt;
    dwOrgDef = dwNxtDef;
    dwOrgRec = dwNxtRec;
    
    byNxtLv += 1;

    dwNxtHp = dwOrgHp + fHpFatio;
    dwNxtAtt = dwOrgAtt + fAttFatio;
    dwNxtDef = dwOrgDef + fDefFatio;
    dwNxtRec = dwOrgRec + fRecFatio;
    
//    CCLog("Cur Lv:%d, Hp:%d, Att:%d, Def:%d, Rec:%d", byOrgLv, dwOrgHp, dwOrgAtt, dwOrgDef, dwOrgRec);
//    CCLog("Nxt Lv:%d, Hp:%d, Att:%d, Def:%d, Rec:%d", byNxtLv, dwNxtHp, dwNxtAtt, dwNxtDef, dwNxtRec);
    
    // 更新ExpMax}
    ExpConfig::STC_EXP_CONFIG* pExpCfg = GET_CONFIG_STC(ExpConfig, byOrgLv);
    if (!pExpCfg && byOrgLv == Max_Lv) {
        FlyTextLayer::showTips(GET_STR(Str_max_pet_lv));
        return;
    }
    
    dwCurMaxExp = pExpCfg->dwPetExp * fExpFatio; // 获取当前最大Max值}
}

void CPetMgr::upgradeSpeed()
{
    setPetOrgInfo(dwCurObjId, false);
}

uint8 CPetMgr::petRealLv()
{
    CPet* pPet = CPetCtrl::Get()->GetPetByObjId(dwCurObjId);
    return pPet->GetbyLv();
}


