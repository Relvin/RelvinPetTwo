//
//  Notify.h
//  MyGame
//
//  Created by 朱 俊杰 on 14-9-10.}
//
//

#ifndef __MyGame__Notify__
#define __MyGame__Notify__

#include "DynamicStruct.h"

//#define NOTIFY_PRO_DEF(T, name) \
//T Get##name() { return m_##name; }; \
//void Set##name(T name) { m_##name = name; };  \

class CNotify : public CDynamicStruct {
    
public:
    enum {
        E_NEWS_byNewPet,	// 宠物}
		E_NEWS_byNewEquip,	// 新装备}
		E_NEWS_byNewEmblem,	// 新徽章}
		E_NEWS_byGacha,		// 扭蛋}
		E_NEWS_byMysteryShop,// 神秘商店}
		E_NEWS_byFriendRew,	 // 好友奖励}
    };
    
    CNotify();
    ~CNotify();
    
	void DeSerializeDataClient(ByteBuffer &data);
	void PropertyUpdate(ByteBuffer & data);
    
//    NOTIFY_PRO_DEF(uint8, byNotiNewPet);
//    NOTIFY_PRO_DEF(uint8, byNotiNewEquip);
//    NOTIFY_PRO_DEF(uint8, byNotiNewEmblem);
//    NOTIFY_PRO_DEF(uint8, byNotiGacha);
//    NOTIFY_PRO_DEF(uint8, byNotiMysteryShop);
//    NOTIFY_PRO_DEF(uint8, byNotiFriend);
    
private:
    uint8 m_byNotiNewPet;
    uint8 m_byNotiNewEquip;
    uint8 m_byNotiNewEmblem;
    uint8 m_byNotiGacha;
    uint8 m_byNotiMysteryShop;
    uint8 m_byNotiFriend;

};

#endif /* defined(__MyGame__Notify__) */
