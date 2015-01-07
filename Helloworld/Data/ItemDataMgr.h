//
//  ItemDataMgr.h
//  HelloWorld
//
//  Created by jun on 13-11-26.
//
//

#ifndef __HelloWorld__ItemDataMgr__
#define __HelloWorld__ItemDataMgr__

#include "Singleton.h"
#include "Defines.h"
#include "Item.h"
#include <vector>

USING_NS_CC;
using namespace std;

enum ITEM_SHOW_MODE
{
    MODE_SHOW_NORMAL_ITEM = 1,
    MODE_SHOW_PET_CHIP = 2,
};

class CItemDataMgr : public Singleton<CItemDataMgr>
{
public:

    void AddShowItemIndex(uint32 dwIndex);
    vector<uint32> GetVecShowItemIndex();
    void ClearShowItemIndex();
    void DelIndexFromShowVector(uint32 dwIndex);
    
    void AddPetChipIndex(uint32 dwIndex);
    vector<uint32> GetVecPetChip();
    void ClearPetChipIndex();
    void DelPetChipIndex(uint32 dwIndex);
    
    void SetItemShowMode(ITEM_SHOW_MODE mode) { m_ItemShowMode = mode; };
    ITEM_SHOW_MODE GetItemShowMode() { return m_ItemShowMode; };
    
    void checkAllItem();
private:

    vector<uint32> m_vecShowItemIndex;
    vector<uint32> m_vecPetChipIndex;
    
    ITEM_SHOW_MODE m_ItemShowMode;
};

#define g_ItemData CItemDataMgr::Get()


#endif /* defined(__HelloWorld__ItemDataMgr__) */