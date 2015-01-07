#ifndef _PET_CTRL_H
#define _PET_CTRL_H

#include "Defines.h"
#include "ByteBuffer.h"
#include <map>
#include "cocos2d.h"
#include "Singleton.h"


USING_NS_CC;


struct STC_PET_BASE_INFO{
    uint32 dwHp;
    uint32 dwCAtk;
    uint32 dwSAtk;
    uint32 dwCDef;
    uint32 dwSDef;
    uint32 dwRev;
    STC_PET_BASE_INFO()
    {
        dwHp = 0;
        dwCAtk = 0;
        dwSAtk = 0;
        dwCDef = 0;
        dwSDef = 0;
        dwRev = 0;
    };
};

class CPet;

class CPetCtrl : public Singleton<CPetCtrl>
{
public:
    
#define ENHANCE_MONEY(exp_base, lv, money_base) (exp_base + lv * 10) * money_base / 1000
#define ENHANCE_EXP(base, lv) (base + lv * 20 )
    
	typedef std::map<uint32, CPet *> MAP_PETS;
	typedef std::vector<uint32> VEC_PETS;

    
    enum E_PET_SORT_TYPE
    {
        E_PET_SORT_TYPE_NULL = 0,
        E_PET_SORT_TYPE_LV,         //等级}
        E_PET_SORT_TYPE_NATURE,     //属性}
        E_PET_SORT_TYPE_BIRTHDAY,   //入手时间}
        E_PET_SORT_TYPE_ATTACK,     //攻击力}
        E_PET_SORT_TYPE_DEFENSE,    //防御}
        E_PET_SORT_TYPE_SDEF,       //特防}
        E_PET_SORT_TYPE_RECOVER,    //回复}
        E_PET_SORT_TYPE_STAR,       //星级}
        E_PET_SORT_TYPE_HP          //生命}
        
    };
    
    enum E_BAG_ENTER_TYPE
    {
        E_BAG_ENTER_TYPE_ALL,
        E_BAG_ENTER_TYPE_LOCK,
        E_BAG_ENTER_TYPE_SALE,
        E_BAG_ENTER_TYPE_PARTY_NORMAL,
        E_BAG_ENTER_TYPE_PARTY_LEADER,
        E_BAG_ENTER_TYPE_INTENSIFY_PRIMARY,
        E_BAG_ENTER_TYPE_INTENSIFY_SUB,
        E_BAG_ENTER_TYPE_EVOLVE,
        E_BAG_ENTER_TYPE_TUJIAN,
        E_BAG_ENTER_TYPE_FUSE,
        E_BAG_ENTER_TYPE_EMBLEM,
        E_BAG_ENTER_TYPE_TEAM,
    };
    
    enum E_PET_SHOW_TAB
    {
        E_PET_SHOW_TAB_ULT,
        E_PET_SHOW_TAB_PASS,
        E_PET_SHOW_TAB_EQUIP,
    };
    
    CPetCtrl();
    
    void SetPetBagType(uint8 type){
        m_byPetBagType = type;
    };
    uint8 GetPetBagType(){return m_byPetBagType;};
    
    void SetSortType(uint8 type){m_bySortType = type;};
    uint8 GetSortType(){return m_bySortType;};
    
    void SetSortUp(bool isUp){m_IsSortUp = isUp;};
    bool GetSortUp(){return m_IsSortUp;};
	//摧毁所有宠物对象}
	void UnInit();
    
    //新增宠物}
	void NewPetAdd(CPet *pPet);
	//删除宠物}
    void DelPet(uint32 dwPetObjId);
    //通过obId获取宠物}
	CPet * GetPetByObjId(uint32 dwPetObjId);
    //更新宠物信息}
	void PetPropertyUpdate(uint32 dwPetObjId, ByteBuffer & data);
    //取头像}
	CCTexture2D * GetPetHeadTexture(uint16 wPetIndex);
    //取原画}
	CCTexture2D * GetPetBodyTexture(uint16 wPetIndex);
    //取战斗界面头像}
    CCTexture2D * GetPetBattleHeadTexture(uint16 wPetIndex);
    //取战斗界面队长技能头像}
    CCTexture2D * GetPetBattleLeaderIconTexture(uint16 wPetIndex);
    
    //取宠物类型名}
    std::string GetPetTypeString(uint16 wPetIndex);
    //取宠物类型图}
    CCSpriteFrame * GetPetTypeSF(uint16 wPetIndex);

    //转换Flcc的坐标（按内框计算）}
    CCPoint ConvertFlccPos(uint16 petIndex, float flccWidth, CCPoint pos, bool isFlexY = false);
	
    std::string GetPetHeadPicName(uint16 wPetIndex);
	std::string GetPetBodyPicName(uint16 wPetIndex);
	std::string GetPetBattleHeadName(uint16 wPetIndex);
    //取战斗中队长技能头像}
    std::string GetPetBattleLeaderIconName(uint16 wPetIndex);
    //获取宠物属性球}
    CCSpriteFrame* GetPetNaturePicSF(uint16 wPetIndex);
    //获取宠物类型图
    CCSpriteFrame* getPetType2SF(uint16 wPetIndex);
    
    //获取宠物详情界面宠物背景图}
    CCSpriteFrame* GetPetShowFramePicSF(uint16 wPetIndex);
    // 获取星空颜色}
    ccColor3B GetStarColrByPetIdx(uint16 wPetIndex);
    // 获取底座颜色}
    ccColor3B GetBaseColrByPetIdx(uint16 wPetIndex);
    // {获取底传送光颜色}
    ccColor3B GetHaloLightColrByPetIdx(uint16 wPetIndex);
    
    // 获取星空Texture}
    CCTexture2D* GetStarTextureByPet(uint16 wPetIdx);
    // 获取底座Texture}
    CCTexture2D* GetBaseTextureByPet(uint16 wPetIdx);
    CCSpriteFrame* GetHaloLightTextureByPet(uint16 wPetIdx);
    
    //取宠物名}
	const char *  GetPetNameByIndex(uint32 wIndex);
    //获取全部宠物数量}
	int GetTotalPetNum();
    //获取某种宠物的数量}
    int getPetNumByIndex(uint16 wIndex);

    //获取宠物等级}
    uint16 GetPetLv(uint32 wObIndex);
    
    MAP_PETS getAllPet(){return m_mapPets;};
    //是否是新宠}
    bool IsNewPet(uint32 wObIndex);
    //是否是保护宠}
    bool IsProtected(uint32 wObIndex);
    //判断锁定}
    bool IsLocked(uint32 wObIndex);
    //判断是否有装备}
    bool IsHasEquip(uint32 wObIndex);
    //判断是否装备了玉}
    bool IsHasGem(uint32 wObIndex);
    //判断是否在队伍中(-1：不在队伍中，0：在队伍中；1：在当前队伍中)}
    int IsInParty(uint32 wObIndex);
    //判断可否强化}
    bool IsCanIntensify(uint32 wObIndex);
    //判断可否出售}
    bool IsCanSale(uint32 wObIndex);
    //判断可否进化}
    bool IsCanEvolve(uint32 wObIndex);
    //判断满级}
    bool IsLvMax(uint32 wObIndex);
    
    bool IsPetIconEnable(uint32 wObIndex);
    
    //根据各种情况过滤宠物背包，并设置宠物能否被选择}
    VEC_PETS GetBagPets();
    //宠物背包排序}
    VEC_PETS SortPetBag();
    //强化时主宠}
    void SetIntensifyPet(uint32 wObIndex){m_wIntensifyPetObjId = wObIndex;};
    uint32 GetIntensifyPet(){return m_wIntensifyPetObjId;};
    //强化时副宠}

    //强化}
    void DoIntensifyPet();
    // 获得被吃的pet Index}
    VEC_PETS GetFoodIndex();
    
    //进化主宠}
    void SetEvolvePet(uint32 wObjIndex){m_wEvolvePetObjId = wObjIndex;};
    uint32 GetEvolvePet(){return m_wEvolvePetObjId;};
    //进化}
    void DoEvolvePet();
    //出售宠物}
    void DoSalePet(std::vector<uint32> arrPetObjId);
    
    //设置要显示详情的PetObjId}
    void SetShowPetObjId(uint16 wObjId){m_wShowPetObjId = wObjId;};
    uint16 GetShowPetObjId(){return m_wShowPetObjId;};
    
    //刷新背包界面所选宠物的编号}
    void ReflashPetBagNum();
    //添加选择宠物}
    void AddSelectedPet(uint32 wObjId);
    //去除选择}
    void UnSelectedPet(uint32 wObjId);
    //获取选中的宠物}
    std::vector<uint32> GetSelectedPet(){return m_arrSelectedPet;};
    //清空选中宠物}
    void ClearSelectedPet()
    {
        m_arrSelectedPet.clear();
    };
    //已选宠物是否达到上限}
    bool IsSeletedFull();
    
    //刷新背包界面}
    void ReflashPetBag();
    
    
    /*
     图鉴相关
     */
    //增加已开图鉴宠物}
    void AddPetTujian(uint16 wPetIndex);
    //获取已开图鉴宠物}
    std::set<uint16> getPetTujian(){return m_setPetsTujian;};
    //图鉴详细显示的宠物id}
    void setPetTujianShowId(uint16 wTujianShowPetId)
    {
        m_wTujianShowPetId = wTujianShowPetId;
        m_wShowPetObjId = 0;
    };
    uint16 getPetTujianShowId(){return m_wTujianShowPetId;};
    
    //设置当前图鉴显示类型
    void setCurTujianType(uint8 type){m_byCurTujianType = type;};
    //获取当前图鉴显示类型
    uint8 getCurTujianType(){return m_byCurTujianType;};
    
    //设置锁定}
    void setPetLocked(uint32 dwObjId, bool isLock);
    //保存锁定}
    void saveLocked();
    //查看好友}
    void setIsFriendLook(bool isFriendLook){m_isFriendLook = isFriendLook;};
    bool getIsFirendLook(){return m_isFriendLook;};
    
    void setPetBagOffSet(CCPoint offset);
    CCPoint getPetBagOffSet();
//    CCPoint m_pPetBagOffSet;
    //自动选择被吃副宠}
    uint16 selectEnhanceElemAuto();
    
    std::string getPassSkillIcon(uint32 dwPassSkillId);
    
    //存取宠物详细界面显示标签}
    void setPetShowTab(uint8 byTab){
        m_byPetShowTab = byTab;
        m_wTujianShowPetId = 0;
    };
    uint8 getPetShowTab(){return m_byPetShowTab;};
    
    //获取当前阶级的宠物index}
//    uint32 getCurPetIndex(uint32 dwObjId);
    //自动添加融合宠}
    void selectFuseElemAuto();
    
    //根据星级获得宠物品质}
    uint8 getPetQuality(uint16 wPetId);
    
    //是否需要刷新宠物属性，用在属性变化飘字用}
    void SetNeedRefreshValue(bool isNeed) { m_isNeedRefreshValue = isNeed; } ;
    bool isNeedRefreshValue() { return m_isNeedRefreshValue; };
    
    void SetPetFirstAttriValue(int index, uint32 value) { m_dwPetFirstAttriValue[index] = value; };
    uint32 GetPetFristAttriValue(int index) { return m_dwPetFirstAttriValue[index]; };
    
    void SetEquipCountOnce(int count) { m_nEquipCountOnce = count; };
    int GetEquipCountOnce() { return m_nEquipCountOnce; } ;
    
    
    //获取属性文字}
    std::string getNatureText(uint8 nature);
    
    //获取宠物等级、进阶 的基础六维值
    STC_PET_BASE_INFO getPetBaseValueByObjId(uint32 petObjId, uint16 lv = 0);
    STC_PET_BASE_INFO getEmblemAddValue(uint32 petObjId, STC_PET_BASE_INFO baseValue);
    
    //进阶前宠物基础六维
    void setEvoPerData(STC_PET_BASE_INFO baseInfo){m_evoPerInfo = baseInfo;};
    STC_PET_BASE_INFO getEvoPerData(){return m_evoPerInfo;};
    
    //判断当前宠物是否能够进化
    bool checkPetCanEvo(uint32 petObjId);
    
    //判断情缘
    std::vector<uint8> checkQingyuan(uint32 qyId);
    //情缘激活状态
    bool checkQingyuanActi(uint32 qyId);
private:
    static bool cmp(const int &p, const int &q);
    static bool cmpLock(const int &p, const int &q);
private:
	MAP_PETS m_mapPets;
    VEC_PETS m_vecFood;
    
	VEC_PETS m_vecPetsNew;
	
	VEC_PETS m_vecPetsProtected;
    VEC_PETS m_vecPetsNormal;
    
    uint8 m_bySortType;
    bool m_IsSortUp;
    uint8 m_byPetBagType;

    uint32 m_wIntensifyPetObjId;
    uint32 m_wEvolvePetObjId;
    uint32 m_wShowPetObjId;
    
    std::vector<uint32>m_arrSelectedPet;
    
    //图鉴宠物}
    std::set<uint16> m_setPetsTujian;
    //图鉴详细的宠物id}
    uint16 m_wTujianShowPetId;
    //当前显示图鉴类型
    uint8 m_byCurTujianType;
    
    //改变了锁定的宠物}
    std::map<uint32, bool> m_mapChgLockedPet;
    
    //查看好友}
    bool m_isFriendLook;
    
    //记录不同情况下，宠物背包界面的tabelview偏移(包括图鉴)}
    std::map<uint8, CCPoint> m_mapPetBagOffSet;
    
    //记录宠物详细界面显示标签}
    uint8 m_byPetShowTab;
    
    //是否需要刷新宠物属性，用在属性变化飘字用}
    bool m_isNeedRefreshValue;
    uint32 m_dwPetFirstAttriValue[14];
    int m_nEquipCountOnce;
    
    STC_PET_BASE_INFO m_evoPerInfo;
};


#endif