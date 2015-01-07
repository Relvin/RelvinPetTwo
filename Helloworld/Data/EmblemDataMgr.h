//
//  EmblemDataMgr.h
//  MyGame
//
//  Created by long on 14-7-4.
//
//

#ifndef __MyGame__EmblemDataMgr__
#define __MyGame__EmblemDataMgr__

#include <iostream>
#include "Singleton.h"
#include "Emblem.h"
#include "Defines.h"
#include "cocos2d.h"
USING_NS_CC;

#define embSelMax   5

#define g_EmblemData CEmblemDataMgr::Get()
#define MAP_EMBLEM std::map<uint32, CEmblem*>

enum E_EMB_IN_TYPE
{
    E_EMB_IN_TYPE_ALL,
    E_EMB_IN_TYPE_WEAR,
};

struct STC_EXC_PET
{
    uint16 petIndex; //专属宠物Id}
    uint8 byEmbType; //专属属性}
    uint32 dwEmbValue;//专属加成值（万分比）}
};

class CEmblemDataMgr : public Singleton<CEmblemDataMgr>
{
public:
    CEmblemDataMgr();
    ~CEmblemDataMgr();
    
    //销毁当前徽章背包}
    void unInit();
    //新增}
    void addNewEmblem(CEmblem *emblem);
    //删除}
    void delEmblem(uint32 dwEmblemObjId);
    //更新}
    void updateEmblem(uint32 dwEmblemObjId, ByteBuffer & data);
    //获取全部徽章}
    std::map<uint32, CEmblem*> getAllEmblem(){return m_mapAllEmblem;};
    //更据ObjId获取徽章}
    CEmblem* getEmblemByObjId(uint32 dwEmblemObjId);
    //获取icon路径}
    std::string getIconPath(uint32 wEmbIndex);
    
    //验证专属宠物}
    bool checkExcPet(uint32 dwEmbIndex, uint32 wPetObjId);
    
    //取徽章背包进入方式}
    void setEmbInType(uint8 inType){m_byEmbInType = inType;};
    uint8 getEmbInType(){return m_byEmbInType;};

    //验证有没有可用徽章
    bool hasFreeEmblem();
#pragma mark 徽章装备
    //设置装备徽章}
//    void setWearEmbObjId(uint32 embObjId){m_dwWearEmbId = embObjId;};
//    //取装备徽章Id}
//    uint32 getWearEmbObjId(){return m_dwWearEmbId;};

#pragma mark 徽章强化
    
    //自动添加强化素材}
    void selectElemAuto();
    
    //选中}
    bool addSelected(uint32 dwEmbObjId);
    //取消选中}
    bool delSelected(uint32 dwEmbObjId);
    //判断是否选中}
    bool isSelected(uint32 dwEmbObjId);
    //清除选中}
    void clearSelected(){m_arrSelected.clear();};
    //获取选中}
    std::vector<uint32> getSelected(){return m_arrSelected;};
    
    
    //设置强化徽章}
    void setEnhEmbObjId(uint32 embObjId){m_dwEnhEmbId = embObjId;};
    //取强化徽章Id}
    uint32 getEnhEmbObjId(){return m_dwEnhEmbId;};
    
    
    //获取背包table off}
    CCPoint getBagOffSet(){return m_emBagOff;};
    //设置背包table off}
    void setBagOffSet(CCPoint off){m_emBagOff = off;};
    
private:
    
    MAP_EMBLEM m_mapAllEmblem;
    
    CCPoint m_emBagOff;
    
    std::vector<uint32> m_arrSelected;
    
    //强化徽章Id}
    uint32 m_dwEnhEmbId;
    //装备徽章Id}
    uint32 m_dwWearEmbId;
    
    uint8 m_byEmbInType;
};


#endif /* defined(__MyGame__EmblemDataMgr__) */
