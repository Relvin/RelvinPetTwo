//
//  CFuseDadaMgr.h
//  HelloWorld
//
//  Created by long on 14-6-4.
//
//

#ifndef __HelloWorld__CFuseDadaMgr__
#define __HelloWorld__CFuseDadaMgr__

#include <iostream>
#include "Singleton.h"
#include "Defines.h"
#include <vector>
#include "cocos2d.h"

USING_NS_CC;

#define fuseCnt  4

#define g_FuseDada CFuseDadaMgr::Get()

enum E_FUSE_TAB
{
    E_FUSE_TAB_PET = 1,
    E_FUSE_TAB_EQUIP = 2,
};

class CFuseDadaMgr : public Singleton<CFuseDadaMgr>
{
public:
    CFuseDadaMgr()
    {
        m_curTab = 1;
        m_arrSelected.clear();
    };
    
    bool addSelected(uint32 dwId);
    bool delSelected(uint32 dwId);
    bool checkSelected(uint32 dwId);
    void clearSelected(){m_arrSelected.clear();};
    std::vector<uint32> getSelected(){return m_arrSelected;};
    bool isSelectedFull(){return m_arrSelected.size() >= fuseCnt;};
    
    void setFuseTab(uint8 tab);
    uint8 getFuseTab(){return m_curTab;};
    
    void atuoSelecte();
private:
    uint8 m_curTab;
    std::vector<uint32> m_arrSelected;
    
    
private:
    void autoSelectePet();
    void autoSelecteEquip();
    
    void ReflashPetBagNum();
};

#endif /* defined(__HelloWorld__CFuseDadaMgr__) */
