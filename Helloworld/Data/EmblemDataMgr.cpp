//
//  EmblemDataMgr.cpp
//  MyGame
//
//  Created by long on 14-7-4.
//
//

#include "EmblemDataMgr.h"
#include "ResourceDefine.h"
#include "ConfigGet.h"
#include "GameSession.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "EnumDefines.h"
#include "ResourceStringClient.h"
#include "GuideData.h"


CEmblemDataMgr::CEmblemDataMgr()
{
    m_mapAllEmblem.clear();
    m_emBagOff = ccp(0, 1);
    m_byEmbInType = 0;
}


CEmblemDataMgr::~CEmblemDataMgr()
{
    m_mapAllEmblem.clear();
}



//销毁当前徽章背包}
void CEmblemDataMgr::unInit()
{
    m_mapAllEmblem.clear();
}


//新增}
void CEmblemDataMgr::addNewEmblem(CEmblem *emblem)
{
    MAP_EMBLEM::iterator ii = m_mapAllEmblem.find(emblem->getdwEmlemObjId());
	if (ii != m_mapAllEmblem.end())
	{
        CC_SAFE_DELETE(ii->second);
		m_mapAllEmblem[emblem->getdwEmlemObjId()] = emblem;
		return ;
	}
	m_mapAllEmblem[emblem->getdwEmlemObjId()] = emblem;
}


//删除}
void CEmblemDataMgr::delEmblem(uint32 dwEmblemObjId)
{
    MAP_EMBLEM::iterator ii = m_mapAllEmblem.find(dwEmblemObjId);
	if (ii != m_mapAllEmblem.end())
	{
		m_mapAllEmblem.erase(ii);
		return ;
	}
}


//更新}
void CEmblemDataMgr::updateEmblem(uint32 dwEmblemObjId, ByteBuffer & data)
{
    MAP_EMBLEM::iterator ii = m_mapAllEmblem.find(dwEmblemObjId);
	if (ii != m_mapAllEmblem.end())
	{
        ii->second->PropertyUpdate(data);
    }
}


//更据ObjId获取徽章}
CEmblem* CEmblemDataMgr::getEmblemByObjId(uint32 dwEmblemObjId)
{
    MAP_EMBLEM::iterator ii = m_mapAllEmblem.find(dwEmblemObjId);
	if (ii != m_mapAllEmblem.end())
	{
        return ii->second;
    }
    
    return NULL;
}

//获取icon路径}
std::string CEmblemDataMgr::getIconPath(uint32 wEmbIndex)
{
    EmblemConfig::STC_EMBLEM_CONFIG* cfg = GET_CONFIG_STC(EmblemConfig, wEmbIndex);
    if (cfg) {
        std::string path = GET_EMBLEM_ICON(cfg->wIcon);
        CCTexture2D* t2d = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
        if (t2d) {
            return path;
        }
    }
    
    return PIC_DEFAULT;
}

//验证专属宠物}
bool CEmblemDataMgr::checkExcPet(uint32 dwEmbIndex, uint32 wPetObjId)
{
    bool ret = false;
    
    EmblemConfig::STC_EMBLEM_CONFIG *embCfg = GET_CONFIG_STC(EmblemConfig, dwEmbIndex);
    if (!embCfg) {
        return ret;
    }
    
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(wPetObjId);
    if (!pet) {
        return ret;
    }
    //从当前阶级往前找，找到0阶时对应的Index Id，再与徽章的专属宠匹配}
    uint32 nextId = GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv());
    std::vector<uint32> arrId;
    while (true) {
        if (nextId % 100 == 0) {
            break;
        }
        EvolveConfig::STC_EVOLVE_CONFIG* cfg = GET_CONFIG_STC(EvolveConfig, nextId);
        if (cfg) {
            arrId.push_back(nextId);
        }
        else
        {
            nextId = nextId - 100;
            EvolveConfig::STC_EVOLVE_CONFIG* cfg = GET_CONFIG_STC(EvolveConfig, nextId);
            if (cfg) {
                arrId.push_back(nextId);
            }
            else
            {
                break;
            }
        }
        nextId --;
    }
    
    if (arrId.size() > 0) {
        nextId = arrId[arrId.size() - 1];
    }
    
    nextId = nextId / 100;
    
    for ( int i = 0 ; i < 5; i ++) {
        if (embCfg->wExcPetIndex[i] && embCfg->wExcPetIndex[i] == nextId) {
            ret = true;
            break;
        }
    }
    
    return ret;
}

//自动添加强化素材}
void CEmblemDataMgr::selectElemAuto()
{
//    m_arrSelected.clear();
    if(m_arrSelected.size() >= embSelMax)
    {
        return;
    }
    //自动选择3级以下徽章
    MAP_EMBLEM mapEmb = g_EmblemData->getAllEmblem();
    MAP_EMBLEM::iterator it = mapEmb.begin();
    for (; it != mapEmb.end(); it++) {
        if (!it->second || it->second->getdwPetObjId()
            || it->first == g_EmblemData->getEnhEmbObjId()
            || it->second->getbyLv() >= 3) {
            continue;
        }
        if(m_arrSelected.size() >= embSelMax)
        {
            break;
        }
        m_arrSelected.push_back(it->first);
    }
}

//选中}
bool CEmblemDataMgr::addSelected(uint32 dwEmbObjId)
{
    CEmblem* emb = getEmblemByObjId(dwEmbObjId);
    if (!emb) {
        return false;
    }
    
    if (m_arrSelected.size() >= embSelMax) {
        return false;
    }
    
    m_arrSelected.push_back(dwEmbObjId);
    return true;
    
}

//取消选中}
bool CEmblemDataMgr::delSelected(uint32 dwEmbObjId)
{
    CEmblem* emb = getEmblemByObjId(dwEmbObjId);
    if (!emb) {
        return false;
    }
    
    for (int i = 0; i < m_arrSelected.size(); i++) {
        if (m_arrSelected[i] == dwEmbObjId) {
            m_arrSelected.erase(m_arrSelected.begin() + i);
            return true;
        }
    }
    return false;
}

//判断是否选中}
bool CEmblemDataMgr::isSelected(uint32 dwEmbObjId)
{
    for (int i = 0; i < m_arrSelected.size(); i++) {
        if (m_arrSelected[i] == dwEmbObjId) {
            return true;
        }
    }
    return false;
}

//验证有没有可用徽章
bool CEmblemDataMgr::hasFreeEmblem()
{
    uint32 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        return false;
    }
    
    MAP_EMBLEM mapEmb = g_EmblemData->getAllEmblem();
    MAP_EMBLEM::iterator it = mapEmb.begin();
    for (; it != mapEmb.end(); it++) {
        if (!it->second || it->second->getdwPetObjId()){
            continue;
        }
        
        return true;
    }
    
    return false;
}