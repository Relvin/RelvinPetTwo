
#include "PetCtrl.h"
#include "Pet.h"
#include "GameSession.h"
#include "ConfigData.h"
#include <assert.h>
#include "ResourcePic.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "UISupport.h"
#include "ConfigUtil.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "ConfigGet.h"
#include "PetLoadingLayer.h"
#include "CcbPetBagSaleLayer.h"
#include "CcbPetBagLayer.h"
#include "PetLoadingLayer.h"
#include "EnumDefines.h"
#include "ResourceDefine.h"
#include "EmblemDataMgr.h"
#include "Emblem.h"
#include "Role.h"
#include "PacketDataMgr.h"
#include <algorithm>

USING_NS_CC;

#define MaxIntensifySubCnt      5
#define MaxSaleCnt              50
#define MaxFuseCnt              4

CPetCtrl::CPetCtrl()
{
    m_bySortType = E_PET_SORT_TYPE_BIRTHDAY;
    m_IsSortUp = false;
    m_byPetBagType = 0;
    m_wIntensifyPetObjId = 0;
    m_wEvolvePetObjId = 0;
    m_wShowPetObjId = 0;
    m_wTujianShowPetId = 0;
    m_isFriendLook = false;
    m_isNeedRefreshValue = false;
    m_nEquipCountOnce = 0;
    
    m_byPetShowTab = 0;
    m_byCurTujianType = 1;
}

//摧毁所有宠物对象}
void CPetCtrl::UnInit()
{
    
	MAP_PETS::iterator ii = m_mapPets.begin();
    
	for(; ii != m_mapPets.end(); ++ii)
	{
        CC_SAFE_DELETE(ii->second);
	}
	m_mapPets.clear();
	m_vecPetsNew.clear();
	m_vecPetsProtected.clear();
    m_vecFood.clear();

    m_bySortType = E_PET_SORT_TYPE_BIRTHDAY;
    m_mapPetBagOffSet.clear();
    m_setPetsTujian.clear();
}

void CPetCtrl::NewPetAdd(CPet *pPet)
{
    if (pPet->GetwIndex() == 0) {
        return;
    }
	MAP_PETS::iterator ii = m_mapPets.find(pPet->GetObjId());
	if (ii != m_mapPets.end())
	{
		//重复？}
		assert(false);

        CC_SAFE_DELETE(ii->second);
		m_mapPets[pPet->GetObjId()] = pPet;
		return ;
	}
	m_mapPets[pPet->GetObjId()] = pPet;
    
    if (IsProtected(pPet->GetObjId())) {
        m_vecPetsProtected.push_back(pPet->GetObjId());
    }
    else
    {
        m_vecPetsNormal.push_back(pPet->GetObjId());
    }
}
void CPetCtrl::DelPet(uint32 dwPetObjId)
{
	MAP_PETS::iterator ii = m_mapPets.find(dwPetObjId);
	if (ii != m_mapPets.end())
	{
		m_mapPets.erase(ii);
		//vector删除。。。}
		VEC_PETS::iterator jj = m_vecPetsNew.begin();
		for(; jj != m_vecPetsNew.end(); ++jj)
		{
			if (dwPetObjId == *jj)
			{
				m_vecPetsNew.erase(jj);
				break;
			}
		}
		return ;
	}
	assert(false);
	//没有找到删除个毛哦}
}

//增加图鉴宠物}
void CPetCtrl::AddPetTujian(uint16 wPetIndex)
{
    std::set<uint16>::iterator it = m_setPetsTujian.find(wPetIndex);
    if (it != m_setPetsTujian.end()) {
        return;
    }
    m_setPetsTujian.insert(wPetIndex);
}

CPet * CPetCtrl::GetPetByObjId(uint32 dwPetObjId)
{
	MAP_PETS::iterator ii = m_mapPets.find(dwPetObjId);
	if (ii != m_mapPets.end())
	{
		return ii->second;
	}
	return NULL;
}

void CPetCtrl::PetPropertyUpdate(uint32 dwPetObjId, ByteBuffer & data)
{
	CPet *pPet = GetPetByObjId(dwPetObjId);
	assert(pPet != NULL);
	pPet->PropertyUpdate(data);
}


CCTexture2D * CPetCtrl::GetPetHeadTexture(uint16 wPetIndex)
{
    std::string path = ConfigGet::GetPetHeadIcon(wPetIndex);//CUtil::StrFormat( PET_HEAD , wPetIndex, FORMAT_PARAM_END ).c_str();

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
	if (pTexture)
	{
		return pTexture;
	}
	//找不到, 用狗头}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(PIC_DEFAULT);
	if (pTexture)
	{
		return pTexture;
	}
	return NULL;
}
CCTexture2D * CPetCtrl::GetPetBodyTexture(uint16 wPetIndex)
{
    std::string path = GetPetBodyPicName(wPetIndex);
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
	if (pTexture)
	{
		return pTexture;
	}
	//找不到}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(PIC_DEFAULT);
	if (pTexture)
	{
		return pTexture;
	}
	return NULL;
}

//取战斗界面头像}
CCTexture2D * CPetCtrl::GetPetBattleHeadTexture(uint16 wPetIndex)
{
    std::string path = GetPetBattleHeadName(wPetIndex);
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
	if (pTexture)
	{
		return pTexture;
	}
	//找不到}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(PIC_DEFAULT);
	if (pTexture)
	{
		return pTexture;
	}
	return NULL;
}

//取战斗界面头像}
CCTexture2D * CPetCtrl::GetPetBattleLeaderIconTexture(uint16 wPetIndex)
{
    std::string path = GetPetBattleLeaderIconName(wPetIndex);
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
	if (pTexture)
	{
		return pTexture;
	}
	//找不到}
	pTexture = CCTextureCache::sharedTextureCache()->addImage(PIC_DEFAULT);
	if (pTexture)
	{
		return pTexture;
	}
	return NULL;
}

std::string CPetCtrl::GetPetHeadPicName(uint16 wPetIndex)
{
    
    std::string path = ConfigGet::GetPetHeadIcon(wPetIndex);//CUtil::StrFormat( PET_HEAD , wPetIndex, FORMAT_PARAM_END ).c_str();

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
	if (pTexture)
	{
		return path;
	}
    
	return PIC_DEFAULT;
}
std::string CPetCtrl::GetPetBodyPicName(uint16 wPetIndex)
{
	std::string path = CUtil::StrFormat( PET_PAINT , wPetIndex, FORMAT_PARAM_END ).c_str();
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
	if (pTexture)
	{
		return path;
	}

	return PIC_DEFAULT;
}

std::string CPetCtrl::GetPetBattleLeaderIconName(uint16 wPetIndex)
{
	CCString* path = CCString::createWithFormat(PET_LEADER_EFF_ICON , wPetIndex);
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(path->getCString());
	if (pTexture)
	{
		return path->getCString();
	}
	return PIC_DEFAULT;
}

std::string CPetCtrl::GetPetBattleHeadName(uint16 wPetIndex)
{
	CCString* path = CCString::createWithFormat(PET_BATTLE_ICON , wPetIndex);
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(path->getCString());
	if (pTexture)
	{
		return path->getCString();
	}
	return PIC_DEFAULT;
}

//获取宠物属性球}
CCSpriteFrame* CPetCtrl::GetPetNaturePicSF(uint16 wPetIndex)
{
    PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, wPetIndex);
    uint8 byNature = 1;
    if (pCfg) {
        byNature = pCfg->byNature1;
    }
    else{
        CCString *str = CCString::createWithFormat("id 为 %d not found", wPetIndex);
        CCMessageBox(str->getCString(), "Error");
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/interplay.plist");
    CCString *str = CCString::createWithFormat(PET_NATURE, byNature);
    CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
    return sf;
}

//获取宠物类型图
CCSpriteFrame* CPetCtrl::getPetType2SF(uint16 wPetIndex)
{
    PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, wPetIndex);
    uint8 byType = 1;
    if (pCfg) {
        byType = pCfg->byType2;
    }
    else{
        CCString *str = CCString::createWithFormat("id 为 %d not found", wPetIndex);
        CCMessageBox(str->getCString(), "Error");
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/petshow/pet_type.plist");
    CCString *str = CCString::createWithFormat("pt2_%d.png", byType);
    CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
    return sf;
}

//获取宠物详情界面宠物背景图}
CCSpriteFrame* CPetCtrl::GetPetShowFramePicSF(uint16 wPetIndex)
{
    PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, wPetIndex);
    if (!pCfg) {
        CCString *str = CCString::createWithFormat("id 为 %d not found", wPetIndex);
        CCMessageBox(str->getCString(), "Error");
        //        CCSprite* img = CCSprite::create(PIC_DEFAULT);
        //        return img->getTexture();
        return NULL;
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/scene/scene_petshow.plist");
    CCString *str = CCString::createWithFormat(PET_SHOW_BG, pCfg->byNature1);
    CCSpriteFrame *sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
    return sf;
}

//取宠物类型名}
std::string CPetCtrl::GetPetTypeString(uint16 wPetIndex)
{
    PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, wPetIndex);
    if (!pCfg) {
        CCString *str = CCString::createWithFormat("id 为 %d not found", wPetIndex);
        CCMessageBox(str->getCString(), "Error");
        return "";
    }
//    1	坦克}
//    2	DPS
//    3	support
    

    return GET_STR(Str_tank + pCfg->byType1 - 1);

    return "";
}
//取宠物类型图}
CCSpriteFrame * CPetCtrl::GetPetTypeSF(uint16 wPetIndex)
{
    PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, wPetIndex);
    if (!pCfg) {
        CCString *str = CCString::createWithFormat("id 为 %d not found", wPetIndex);
        CCMessageBox(str->getCString(), "Error");
        return NULL;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/petshow/pic_property.plist");
    
    string framePath = CCString::createWithFormat("pt_%d.png", pCfg->byType1)->getCString();
    
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framePath.c_str());
}

/*
 6，氛围图RGB值}
 绿色 15 40 0
 黄色 255 250 180
 紫色 30 0 40
 青色 0 70 70
 红色 45 0 0
 蓝色 0 15 50
 
 7，底座转圈RGB值}
 绿色 100 200 20
 黄色 255 220 110
 紫色 160 0 255
 青色 150 250 255
 红色 255 25 0
 蓝色 0 70 185
 */

// 星空图}
static const ccColor3B m_pCcGreenStar={40,100,0};        // 草}
static const ccColor3B m_pCcYellowStar={255,250,180};   // 雷}
static const ccColor3B m_pCcPurpleStar={70,0,90};       // 暗}
static const ccColor3B m_pCcCyanStar={0,70,70};         // 光}
static const ccColor3B m_pCcRedStar={45,0,0};           // 火}
static const ccColor3B m_pCcBlueStar={0,30,100};         // 水}

// 底座}
static const ccColor3B m_pCcGreenBase={100,200,20};
static const ccColor3B m_pCcYellowBase={255,220,110};
static const ccColor3B m_pCcPurpleBase={160,0,255};
static const ccColor3B m_pCcCyanBase={150,250,255};
static const ccColor3B m_pCcRedBase={255,25,0};
static const ccColor3B m_pCcBlueBase={0,70,185};

// {宠物传送光环颜色}
static const ccColor3B m_pCcGreenHaleLight  = {0,249,0};        // 草}
static const ccColor3B m_pCcYellowHaleLight = {254,251,0};   // 雷}
static const ccColor3B m_pCcPurpleHaleLight = {255,64,255};       // 暗}
static const ccColor3B m_pCcCyanHaleLight   = {254,255,255};         // 光}
static const ccColor3B m_pCcRedHaleLight    = {255,38,0};           // 火}
static const ccColor3B m_pCcBlueHaleLight   = {0,252,255};         // 水}

static const string strRoot = "ccbresources/12monthdate/home/";

//static const string BaseBluePath    = strRoot+"pic_magiccircleblue.png";
//static const string BaseGreenPath   = strRoot+"pic_magiccirclegreen.png";
//static const string BasePurplePath  = strRoot+"pic_magiccirclepurple.png";
//static const string BaseRedPath     = strRoot+"pic_magiccirclered.png";
//static const string BaseWhitePath   = strRoot+"pic_magiccirclewhite.png";
//static const string BaseYellowPath  = strRoot+"pic_magiccircleyellow.png";

static const string BaseBluePath    = strRoot+"stage-water.png";
static const string BaseGreenPath   = strRoot+"stage-grass.png";
static const string BasePurplePath  = strRoot+"stage-dark.png";
static const string BaseRedPath     = strRoot+"stage-fire.png";
static const string BaseWhitePath   = strRoot+"stage-light.png";
static const string BaseYellowPath  = strRoot+"stage-lighting.png";


static const string StarBluePath    = strRoot+"pic_starblue.png";
static const string StarGreenPath   = strRoot+"pic_stargreen.png";
static const string StarPurplePath  = strRoot+"pic_starpurple.png";
static const string StarRedPath     = strRoot+"pic_starred.png";
static const string StarWhitePath   = strRoot+"pic_starwhite.png";
static const string StarYellowPath  = strRoot+"pic_staryellow.png";

// {宠物传送光环颜色}
static const string HaleLightGreenPath  = "halo_2.png";        // 草}
static const string HaleLightYellowPath = "halo_5.png";   // 雷}
static const string HaleLightPurplePath = "halo_1.png";       // 暗}
static const string HaleLightCyanPath   = "halo_3.png";         // 光}
static const string HaleLightRedPath    = "halo_4.png";           // 火}
static const string HaleLightBluePath   = "halo_6.png";         // 水}


CCTexture2D* CPetCtrl::GetStarTextureByPet(uint16 wPetIdx)
{
    PetConfig::STC_PET_CONFIG* pCfg = GET_CONFIG_STC(PetConfig, wPetIdx);
    
    CCTexture2D* pTex = CCTextureCache::sharedTextureCache()->addImage(StarWhitePath.c_str());
    if (!pCfg) {
        return pTex;
    }
    switch (pCfg->byNature1) {
        case 1:
            pTex = CCTextureCache::sharedTextureCache()->addImage(StarBluePath.c_str());
            break;
        case 2:
            pTex = CCTextureCache::sharedTextureCache()->addImage(StarRedPath.c_str());
            break;
        case 3:
            pTex = CCTextureCache::sharedTextureCache()->addImage(StarGreenPath.c_str());
            break;
        case 4:
            pTex = CCTextureCache::sharedTextureCache()->addImage(StarYellowPath.c_str());
            break;
        case 5:
            pTex = CCTextureCache::sharedTextureCache()->addImage(StarWhitePath.c_str());
            break;
        case 6:
            pTex = CCTextureCache::sharedTextureCache()->addImage(StarPurplePath.c_str());
            break;
        default:
            break;
    }
    return pTex;
}

CCTexture2D* CPetCtrl::GetBaseTextureByPet(uint16 wPetIdx)
{
    PetConfig::STC_PET_CONFIG* pCfg = GET_CONFIG_STC(PetConfig, wPetIdx);
    
    CCTexture2D* pTex = CCTextureCache::sharedTextureCache()->addImage(BaseWhitePath.c_str());
    if (!pCfg) {
        return pTex;
    }
    switch (pCfg->byNature1) {
        case E_NATURE_WATER:
            pTex = CCTextureCache::sharedTextureCache()->addImage(BaseBluePath.c_str());
            break;
        case E_NATURE_FIRE:
            pTex = CCTextureCache::sharedTextureCache()->addImage(BaseRedPath.c_str());
            break;
        case E_NATURE_GRASS:
            pTex = CCTextureCache::sharedTextureCache()->addImage(BaseGreenPath.c_str());
            break;
        case E_NATURE_THUNDER:
            pTex = CCTextureCache::sharedTextureCache()->addImage(BaseYellowPath.c_str());
            break;
        case E_NATURE_LIGHT:
            pTex = CCTextureCache::sharedTextureCache()->addImage(BaseWhitePath.c_str());
            break;
        case E_NATURE_DARK:
            pTex = CCTextureCache::sharedTextureCache()->addImage(BasePurplePath.c_str());
            break;
        default:
            break;
    }
    return pTex;
}

CCSpriteFrame* CPetCtrl::GetHaloLightTextureByPet(uint16 wPetIndex)
{
    PetConfig::STC_PET_CONFIG* pCfg = GET_CONFIG_STC(PetConfig, wPetIndex);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/cartoon/halo.plist");
    CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(HaleLightCyanPath.c_str());
    if (!pCfg) {
        return pSpriteFrame;
    }
    
    switch (pCfg->byNature1) {
        case E_NATURE_WATER:
            pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(HaleLightBluePath.c_str());
            break;
        case E_NATURE_FIRE:
            pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(HaleLightRedPath.c_str());
            break;
        case E_NATURE_GRASS:
            pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(HaleLightGreenPath.c_str());
            break;
        case E_NATURE_THUNDER:
            pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(HaleLightYellowPath.c_str());
            break;
        case E_NATURE_LIGHT:
            pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(HaleLightCyanPath.c_str());
            break;
        case E_NATURE_DARK:
            pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(HaleLightPurplePath.c_str());
            break;
        default:
            break;
    }
    return pSpriteFrame;
}

ccColor3B CPetCtrl::GetStarColrByPetIdx(uint16 wPetIndex)
{
    PetConfig::STC_PET_CONFIG* pCfg = GET_CONFIG_STC(PetConfig, wPetIndex);
    if (!pCfg) {
        return ccWHITE;
    }
    /*
     1. 水}
     2. 火}
     3. 草}
     4. 雷}
     5. 光}
     6. 暗}
     E_NATURE_WATER, // 水}
     E_NATURE_FIRE, // 火}
     E_NATURE_GRASS, // 草}
     E_NATURE_THUNDER, // 雷}
     E_NATURE_LIGHT, // 光}
     E_NATURE_DARK, // 暗}
     */
    ccColor3B color = ccBLACK;
    switch (pCfg->byNature1) {
        case E_NATURE_WATER:
            color = m_pCcBlueStar;
            break;
        case E_NATURE_FIRE:
            color = m_pCcRedStar;
            break;
        case E_NATURE_GRASS:
            color = m_pCcGreenStar;
            break;
        case E_NATURE_THUNDER:
            color = m_pCcYellowStar;
            break;
        case E_NATURE_LIGHT:
            color = m_pCcCyanStar;
            break;
        case E_NATURE_DARK:
            color = m_pCcPurpleStar;
            break;
        default:
            break;
    }
    return color;
}

ccColor3B CPetCtrl::GetBaseColrByPetIdx(uint16 wPetIndex)
{
    PetConfig::STC_PET_CONFIG* pCfg = GET_CONFIG_STC(PetConfig, wPetIndex);
    if (!pCfg) {
        return ccWHITE;
    }
    /*
     1. 水}
     2. 火}
     3. 草}
     4. 雷}
     5. 光}
     6. 暗}
     */
    ccColor3B color = ccBLACK;
    switch (pCfg->byNature1) {
        case E_NATURE_WATER:
            color = m_pCcBlueBase;
            break;
        case E_NATURE_FIRE:
            color = m_pCcRedBase;
            break;
        case E_NATURE_GRASS:
            color = m_pCcGreenBase;
            break;
        case E_NATURE_THUNDER:
            color = m_pCcYellowBase;
            break;
        case E_NATURE_LIGHT:
            color = m_pCcCyanBase;
            break;
        case E_NATURE_DARK:
            color = m_pCcPurpleBase;
            break;
        default:
            break;
    }
    return color;
}

ccColor3B CPetCtrl::GetHaloLightColrByPetIdx(uint16 wPetIndex)
{
    PetConfig::STC_PET_CONFIG* pCfg = GET_CONFIG_STC(PetConfig, wPetIndex);
    if (!pCfg) {
        return ccWHITE;
    }
    /*
     1. 水}
     2. 火}
     3. 草}
     4. 雷}
     5. 光}
     6. 暗}
     */
    ccColor3B color = ccBLACK;
    switch (pCfg->byNature1) {
        case E_NATURE_WATER:
            color = m_pCcBlueHaleLight;
            break;
        case E_NATURE_FIRE:
            color = m_pCcRedHaleLight;
            break;
        case E_NATURE_GRASS:
            color = m_pCcGreenHaleLight;
            break;
        case E_NATURE_THUNDER:
            color = m_pCcYellowHaleLight;
            break;
        case E_NATURE_LIGHT:
            color = m_pCcCyanHaleLight;
            break;
        case E_NATURE_DARK:
            color = m_pCcPurpleHaleLight;
            break;
        default:
            break;
    }
    return color;
}

//转换Flcc的坐标（按内框计算）}
CCPoint CPetCtrl::ConvertFlccPos(uint16 petIndex, float flccWidth, CCPoint pos, bool isFlexY)
{
    CCPoint p = pos;
    PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, petIndex);
    if (!petCfg) {
		CCLOG("Cannot find pet [id=%d]", petIndex);
        return p;
    }
    std::vector<int > arrStand;
    ResourceStringConverter::StrSplit(petCfg->strStandSize, "_", arrStand);
    CCPoint standPos;
    CCSize standSize;
    //    std::map<uint16, uint16>::iterator it = arrStand.begin();
    standPos.x = arrStand[0] * 0.5;
    //    it++;
    standPos.y = arrStand[1]* 0.5;
    //    it++;
    standSize.width = arrStand[2]* 0.5;
    //    it++;
    standSize.height = arrStand[3]* 0.5;
    
    arrStand.clear();
   
    if (isFlexY) {
        p = ccpSub(pos, ccp(flccWidth * 0.5 - standPos.x - standSize.width * 0.5, standPos.y));
    }
    else{
        p = ccpAdd(pos, ccp(flccWidth * 0.5 - standPos.x - standSize.width * 0.5, -standPos.y));
    }
    return  p;
}
//取宠物名}
const char *CPetCtrl::GetPetNameByIndex(uint32 wObIndex)
{
    CPet *pet = GetPetByObjId(wObIndex);
    if (pet) {
        PetConfig::STC_PET_CONFIG *petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
        if (!petCfg) {
            return "";
        }
        return petCfg->strName.c_str();
    }
    return "";
}

//	static const char *  GetSpellNameByIndex(uint16 wIndex);
//获取宠物数量}
int CPetCtrl::GetTotalPetNum()
{
	return m_mapPets.size();
    
}
//获取某种宠物的数量}
int CPetCtrl::getPetNumByIndex(uint16 wIndex)
{
    int num = 0;
    std::map<uint32, CPet*>::iterator it = m_mapPets.begin();
    for (; it != m_mapPets.end(); it++) {
        if (!it->second) {
            continue;
        }
        if (it->second->GetwIndex() == wIndex) {
            num++;
        }
    }
    
    return num;
}
//设置背包最大数目}
//void CPetCtrl::SetBagTotalSize(uint16 wBagTotalSize)
//{
//    m_wBagTotalSize = wBagTotalSize;
//}

//获取宠物等级}
uint16 CPetCtrl::GetPetLv(uint32 wObIndex)
{
    CPet *pet = GetPetByObjId(wObIndex);
    if (pet) {
        return pet->GetbyLv();
    }
    return 0;
}
bool CPetCtrl::IsNewPet(uint32 wObIndex)
{
    for (int i = 0 ; i < m_vecPetsNew.size(); i++) {
        if (m_vecPetsNew[i] && m_vecPetsNew[i] == wObIndex) {
            return true;
        }
    }
    return false;
}
bool CPetCtrl::IsProtected(uint32 wObIndex)
{
    if (IsInParty(wObIndex) != -1
//        || IsHasEquip(wObIndex)
//        || IsHasGem(wObIndex)
        || IsLocked(wObIndex)) {
        return true;
    }
    return false;
}
//判断锁定}
bool CPetCtrl::IsLocked(uint32 wObIndex)
{
    CPet *pet = GetPetByObjId(wObIndex);
    if (pet) {
        return pet->GetbIsLock();
    }
    return false;
}
//判断是否有装备}
bool CPetCtrl::IsHasEquip(uint32 wObIndex)
{
//    CPet *pet = GetPetByObjId(wObIndex);
//    if (pet) {
//        return pet->GetwEquipId1()
//        ||pet->GetwEquipId2()
//        ||pet->GetwEquipId3()
//        ||pet->GetwEquipId4();
//    }
    return false;
}
//判断是否装备了玉}
bool CPetCtrl::IsHasGem(uint32 wObIndex)
{
    CPet *pet = GetPetByObjId(wObIndex);
    if (pet) {
        return pet->GetwGemId();
    }
    return false;
}
//判断是否在队伍中(-1：不在队伍中，0：在队伍中；1：在当前队伍中)}
int CPetCtrl::IsInParty(uint32 wObIndex)
{
    CPet *pet = GetPetByObjId(wObIndex);
    if (pet) {
        if ((CTeamCtrl::GetCurTeamId() == 0 && pet->GetbyTeamId1())                ) {
            return 1;
        }
//        return 0;
        
    }
    
    return -1;
}
//判断可否强化}
bool CPetCtrl::IsCanIntensify(uint32 wObIndex)
{
    CPet *pet = GetPetByObjId(wObIndex);
    if (pet) {
        PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
        if (pet->GetbyLv() >= pCfg->byLvMax) {
            return false;
        }
        return true;
    }
    return false;
}
//判断可否出售}
bool CPetCtrl::IsCanSale(uint32 wObIndex)
{
    if (IsProtected(wObIndex)) {
        return false;
    }
    return true;
}
//判断可否进化}
bool CPetCtrl::IsCanEvolve(uint32 wObIndex)
{
    CPet *pet = GetPetByObjId(wObIndex);
    if (pet) {
//        int lv = pet->GetbyEvolveLv();
//        if (lv == 0) {
            EvolveConfig::STC_EVOLVE_CONFIG *eConfig = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv()));
            if (eConfig && eConfig->wNextId) {
                return true;
            }
//        }
//        EvolveConfig::STC_EVOLVE_CONFIG *eConfig = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv()));
//        if (eConfig && eConfig->wNextId > 0) {
//            return true;
//        }
//        return false;
    }
    return false;
}

//判断当前宠物是否能够进化
bool CPetCtrl::checkPetCanEvo(uint32 petObjId)
{
    CPet *pet = GetPetByObjId(petObjId);
    if (!pet) {
        return false;
    }
        EvolveConfig::STC_EVOLVE_CONFIG *eConfig = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv()));
        if (!eConfig || !eConfig->wNextId) {
            return false;
        }
        
        eConfig = GET_CONFIG_STC(EvolveConfig, eConfig->wNextId);
        if (!eConfig) {
            return false;
        }
        CRole* role = CGameSession::GetRole();
        //等级
        if (pet->GetbyLv() < eConfig->wPetLv) {
            return false;
        }
        //钱
        if (role->GetdwCoin() < eConfig->dwNeedMoney) {
            return false;
        }
        //材料
        int len = 0;
        GET_ARRAY_LEN(eConfig->wEvoItemId, len);
        for (int i = 0; i < len; i++) {
            uint32 itemId = eConfig->wEvoItemId[i];
            if (!itemId) {
                continue;
            }
            uint32 cnt = 0;
            if (itemId / E_UNITE_BASE_FABIO == E_UNITE_TYPE_PET) {
                cnt = getPetNumByIndex(pet->GetwIndex());
            }
            else{
                cnt = g_PacketDataMgr->GetItemCountByIndex(itemId);
            }
            if (cnt < eConfig->byEvoItemCnt[i]) {
                return false;
            }
        }
    
    return true;
}

//判断满级}
bool CPetCtrl::IsLvMax(uint32 wObIndex)
{
    CPet *pet = GetPetByObjId(wObIndex);
    if (pet) {
        PetConfig::STC_PET_CONFIG *pConfig = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
        if (!pConfig) {
            return false;
        }
        return pet->GetbyLv() >= pConfig->byLvMax;
//        return true;
    }
    return false;
}

bool CPetCtrl::IsPetIconEnable(uint32 wObIndex)
{
    bool ret = true;
    CPet *pet = GetPetByObjId(wObIndex);
    if (!pet) {
        return false;
    }
    switch (GetPetBagType()) {
        case E_BAG_ENTER_TYPE_ALL:
            
            break;
            
        case E_BAG_ENTER_TYPE_INTENSIFY_SUB:
            
            break;
            
        case E_BAG_ENTER_TYPE_INTENSIFY_PRIMARY:
            if (IsLvMax(wObIndex)) {
                return false;
            }
            
            break;
            
        case E_BAG_ENTER_TYPE_EVOLVE:
            
            break;
            
        case E_BAG_ENTER_TYPE_PARTY_LEADER:
            
            break;
            
        case E_BAG_ENTER_TYPE_PARTY_NORMAL:
            
            break;
            
        case E_BAG_ENTER_TYPE_SALE:
            if (IsProtected(wObIndex)) {
                ret = false;
            }
            break;
            
        default:
            break;
    }
    
    return ret;
}
//根据各种情况过滤宠物背包，并设置宠物能否被选择}
CPetCtrl::VEC_PETS CPetCtrl::GetBagPets()
{
    m_vecPetsProtected.clear();
    m_vecPetsNormal.clear();
    std::map<uint32, CPet*>::iterator it = m_mapPets.begin();
    std::vector<uint32> arrCurTeamPets = CTeamCtrl::GetCurTeam()->getarrPetObId();
    
    for (; it != m_mapPets.end(); it++) {
        if (!it->second) {
            continue;
        }
        CPet* pet = it->second;
        
        switch (CPetCtrl::GetPetBagType()) {
            case CPetCtrl::E_BAG_ENTER_TYPE_ALL:    //全部}
            case CPetCtrl::E_BAG_ENTER_TYPE_EMBLEM: //徽章}
                if (CPetCtrl::IsProtected(pet->GetObjId()))
                {
                    m_vecPetsProtected.push_back(pet->GetObjId());
                }
                else{
                    m_vecPetsNormal.push_back(pet->GetObjId());
                }
                break;
                
            case CPetCtrl::E_BAG_ENTER_TYPE_INTENSIFY_SUB:      //强化副宠(不显示主宠)}
                if (!CPetCtrl::IsProtected(pet->GetObjId())
                    && pet->GetObjId() != GetIntensifyPet())
                {
                    m_vecPetsNormal.push_back(pet->GetObjId());
                }
                break;
                
            case CPetCtrl::E_BAG_ENTER_TYPE_INTENSIFY_PRIMARY:  //强化主宠}
                if (CPetCtrl::IsProtected(pet->GetObjId()))
                {
                    m_vecPetsProtected.push_back(pet->GetObjId());
                }
                else{
                    m_vecPetsNormal.push_back(pet->GetObjId());
                }
                break;
                
            case CPetCtrl::E_BAG_ENTER_TYPE_EVOLVE:             //进化}
                if (CPetCtrl::IsProtected(pet->GetObjId()))
                {
                    m_vecPetsProtected.push_back(pet->GetObjId());
                }
                else{
                    m_vecPetsNormal.push_back(pet->GetObjId());
                }
                break;
                
            case CPetCtrl::E_BAG_ENTER_TYPE_PARTY_LEADER:       //队长}
   
            case CPetCtrl::E_BAG_ENTER_TYPE_PARTY_NORMAL:       //队员}
                if (std::find(arrCurTeamPets.begin(), arrCurTeamPets.end(), pet->GetObjId()) != arrCurTeamPets.end()) {
                    continue;
                }
                if (CPetCtrl::IsProtected(pet->GetObjId()))
                {
                    m_vecPetsProtected.push_back(pet->GetObjId());
                }
                else{
                    m_vecPetsNormal.push_back(pet->GetObjId());
                }
                
                break;
                
            case CPetCtrl::E_BAG_ENTER_TYPE_SALE:
                if (CPetCtrl::IsProtected(pet->GetObjId()))
                {
                    m_vecPetsProtected.push_back(pet->GetObjId());
                }
                else{
                    m_vecPetsNormal.push_back(pet->GetObjId());
                }
                break;
                
            case CPetCtrl::E_BAG_ENTER_TYPE_FUSE:
            {
                if (CPetCtrl::IsProtected(pet->GetObjId())) {
                    continue;
                }
                PetFuseConfig::STC_PET_FUSE_CONFIG *fuCfg = GET_CONFIG_STC(PetFuseConfig, pet->GetwIndex());
                if (!fuCfg) {
                    continue;
                }
                m_vecPetsNormal.push_back(pet->GetObjId());
            }

                break;
                
            default:
                break;
        }
        
        
    }
    
    return SortPetBag();
}

CPetCtrl::VEC_PETS CPetCtrl::SortPetBag()
{
    VEC_PETS pets;
    VEC_PETS petsLock;
    VEC_PETS petsPr;
    
    uint32 leaderId = CTeamCtrl::GetCurTeam()->getarrPetObId()[CTeamCtrl::GetCurTeam()->getbyLeaderSite()];
    bool hasLeader = false;
    for (int i = 0; i < m_vecPetsProtected.size(); i++) {
        CPet *pet = GetPetByObjId(m_vecPetsProtected[i]);
        if (!pet) {
            continue;
        }
        if (pet->GetObjId() == leaderId) {
            hasLeader = true;
        }
        else if (pet->GetbIsLock()) {
            petsLock.push_back(m_vecPetsProtected[i]);
        }
        else
        {
            petsPr.push_back(m_vecPetsProtected[i]);
        }
    }
    std::sort(petsLock.begin(), petsLock.end(), cmp);
    std::sort(petsPr.begin(), petsPr.end(), cmp);
    
    std::sort(m_vecPetsNormal.begin(), m_vecPetsNormal.end(), cmp);
    
    
    //当前队伍队长永远在最前面}
    if (hasLeader) {
        pets.push_back(leaderId);
    }
    //现在受保护的就只是在队伍中与被锁定了，锁定延后，队伍在前}
    for (int i = 0; i < petsPr.size(); i++) {
        pets.push_back(petsPr[i]);
    }
    for (int i = 0; i < petsLock.size(); i++) {
        pets.push_back(petsLock[i]);
    }
    
    
    for (int i = 0; i < m_vecPetsNormal.size(); i++) {
        pets.push_back(m_vecPetsNormal[i]);
    }
    
    return pets;
}

bool CPetCtrl::cmp(const int &p, const int &q)
{
    CPet *pPet1 = CPetCtrl::Get()->GetPetByObjId(p);
	CPet *pPet2 = CPetCtrl::Get()->GetPetByObjId(q);
    uint32 pet1 = 0;
    uint32 pet2 = 0;
    if (!pPet1 || !pPet2) {
        return 0;
    }
    switch (CPetCtrl::Get()->GetSortType()) {
        case CPetCtrl::E_PET_SORT_TYPE_LV:
            pet1 = pPet1->GetbyLv();
            pet2 = pPet2->GetbyLv();
            break;
        case CPetCtrl::E_PET_SORT_TYPE_NATURE:
            pet1 = pPet1->GetbyNature1();
            pet2 = pPet2->GetbyNature1();
            break;
        case CPetCtrl::E_PET_SORT_TYPE_BIRTHDAY:
            pet1 = pPet1->GetdwBirthday();
            pet2 = pPet2->GetdwBirthday();
            break;
        case CPetCtrl::E_PET_SORT_TYPE_ATTACK:
            pet1 = pPet1->GetdwAttackValue();
            pet2 = pPet2->GetdwAttackValue();
            break;
        case CPetCtrl::E_PET_SORT_TYPE_DEFENSE:
            pet1 = pPet1->GetdwDefenseValue();
            pet2 = pPet2->GetdwDefenseValue();
            break;
        case CPetCtrl::E_PET_SORT_TYPE_SDEF:
            pet1 = pPet1->GetdwSDefenseValue();
            pet2 = pPet2->GetdwSDefenseValue();
            break;
        case CPetCtrl::E_PET_SORT_TYPE_RECOVER:
            pet1 = pPet1->GetdwRecoverValue();
            pet2 = pPet2->GetdwRecoverValue();
            break;
        case CPetCtrl::E_PET_SORT_TYPE_STAR:
            pet1 = pPet1->GetbyStarLv();
            pet2 = pPet2->GetbyStarLv();
            break;
        case CPetCtrl::E_PET_SORT_TYPE_HP:
            pet1 = pPet1->GetdwHpValue();
            pet2 = pPet2->GetdwHpValue();
            break;
        default:
            pet1 = pPet1->GetdwBirthday();
            pet2 = pPet2->GetdwBirthday();
            break;
    }
    if (pet1 == pet2) {
        return pPet1->GetwIndex() < pPet2->GetwIndex();
    }
    if (CPetCtrl::Get()->GetSortUp()) {
        return pet1 < pet2;
    }
    else
    {
        return pet1 > pet2;
    }
}

//按锁定排序（为把锁定宠放在最前面）}
bool CPetCtrl::cmpLock(const int &p, const int &q)
{
    CPet *pPet1 = CPetCtrl::Get()->GetPetByObjId(p);
	CPet *pPet2 = CPetCtrl::Get()->GetPetByObjId(q);
    if (!pPet1 || !pPet2) {
        return 0;
    }
    return (int)pPet1->GetbIsLock() > (int)pPet2->GetbIsLock();
}

//刷新背包界面所选宠物的编号}
void CPetCtrl::ReflashPetBagNum()
{
    if (m_byPetBagType == E_BAG_ENTER_TYPE_INTENSIFY_SUB
        || m_byPetBagType == E_BAG_ENTER_TYPE_SALE
        || m_byPetBagType == E_BAG_ENTER_TYPE_FUSE)
    {
        CcbPetBagSaleLayer* pPetBag = (CcbPetBagSaleLayer*)CCDirector::sharedDirector()->getNowScene()->getChildByTag(1)->getChildByTag(1);
        if (pPetBag) {
            pPetBag->ReflashPetBagNum();
        }
    }
}

//添加选择宠物}
void CPetCtrl::AddSelectedPet(uint32 wObjId)
{
    if (!IsSeletedFull()) {
        m_arrSelectedPet.push_back(wObjId);
        ReflashPetBagNum();
    }
}

//去除选择}
void CPetCtrl::UnSelectedPet(uint32 wObjId)
{
    if (m_arrSelectedPet.size() == 0)
    {
        return;
    }
    
    std::vector<uint32>::iterator it = std::find(m_arrSelectedPet.begin(), m_arrSelectedPet.end(), wObjId);
    
    if( it != m_arrSelectedPet.end()) {
        m_arrSelectedPet.erase(it);
        ReflashPetBagNum();
    }
}

//自动选择被吃副宠（小于3星的）}
uint16 CPetCtrl::selectEnhanceElemAuto()
{
    int count = 0;//m_arrSelectedPet.size();

    count = m_arrSelectedPet.size();
    if (count >= MaxIntensifySubCnt) {
        return count;
    }
    
    std::vector<uint32> arrDankeDa;
    std::vector<uint32> arrDankeZhong;
    std::vector<uint32> arrDankeXiao;
    std::vector<uint32> arrZhamao;
    std::vector<uint32> arrShuiqiu;
    std::vector<uint32> arrNormal;
    
    std::map<uint32, CPet*>::iterator it = m_mapPets.begin();
    for (; it != m_mapPets.end(); ++it) {
        if (!it->second || IsProtected(it->first)) {
            continue;
        }
        bool flag = false;
        for (int i = 0; i < m_arrSelectedPet.size(); i++) {
            if (it->first == m_arrSelectedPet[i]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            continue;
        }
        
        switch (it->second->GetwIndex()) {
            case 163:
                arrDankeXiao.push_back(it->first);
                continue;
                break;
            case 164:
                arrDankeZhong.push_back(it->first);
                continue;
                break;
            case 165:
                arrDankeDa.push_back(it->first);
                continue;
                break;
            case 166:
                arrZhamao.push_back(it->first);
                continue;
                break;
            case 170:
                arrShuiqiu.push_back(it->first);
                continue;
                break;
                
            default:
                break;
        }
        if (it->first == m_wIntensifyPetObjId
            || it->second->GetwIndex() < 25
            || it->second->GetwIndex() > 66) {
            continue;
        }
        arrNormal.push_back(it->first);
    }
    
    std::vector< std::vector<uint32> > arrAll;
    arrAll.push_back(arrShuiqiu);
    arrAll.push_back(arrDankeDa);
    arrAll.push_back(arrDankeZhong);
    arrAll.push_back(arrDankeXiao);
    arrAll.push_back(arrZhamao);
    arrAll.push_back(arrNormal);
    
    if (count < MaxIntensifySubCnt) {
        
        for (int k = 0; k < arrAll.size(); k++) {
            std::vector<uint32> arrPet = arrAll[k];
            
            for (int i = 0; i < arrPet.size(); i++) {
                m_arrSelectedPet.push_back(arrPet[i]);
                count++;
                if (count >= MaxIntensifySubCnt) {
                    return count;
                }
            }
            
        }
    }
    return count;
}

//自动选择可融合宠}
void CPetCtrl::selectFuseElemAuto()
{
    int count = 0;//m_arrSelectedPet.size();
    m_arrSelectedPet.clear();
    std::vector<uint32> arrPet;
    std::vector<uint32> arrPetLower;
    std::map<uint32, CPet*>::iterator it = m_mapPets.begin();
    for (; it != m_mapPets.end(); ++it) {
        if (!it->second || IsProtected(it->first)) {
            continue;
        }
        PetFuseConfig::STC_PET_FUSE_CONFIG *fuCfg = GET_CONFIG_STC(PetFuseConfig, it->second->GetwIndex());
        if (!fuCfg) {
            continue;
        }
//        if (count >= MaxFuseCnt) {
//            break;
//        }
        if (it->second->GetbyStarLv() < 4) {
            arrPetLower.push_back(it->first);
        }
        else{
            arrPet.push_back(it->first);
        }
//        count++;
        
    }
    
    uint8 sortType = GetSortType();
    bool isup = GetSortUp();
    SetSortType(E_PET_SORT_TYPE_STAR);
    
    SetSortUp(true);
    std::sort(arrPet.begin(), arrPet.end(), cmp);
    
    SetSortUp(false);
    std::sort(arrPetLower.begin(), arrPetLower.end(), cmp);
    
    SetSortType(sortType);
    SetSortUp(isup);
    
    for (int i = 0; i < arrPet.size(); i++) {
        if (count >= MaxFuseCnt) {
            break;
        }
        m_arrSelectedPet.push_back(arrPet[i]);
        count++;
    }
    
    for (int i = 0; i < arrPetLower.size(); i++) {
        if (count >= MaxFuseCnt) {
            break;
        }
        m_arrSelectedPet.push_back(arrPetLower[i]);
        count++;
    }
}

//已选宠物是否达到上限}
bool CPetCtrl::IsSeletedFull()
{
    int size = 0;
    switch (m_byPetBagType) {
        case E_BAG_ENTER_TYPE_INTENSIFY_SUB:
            size = MaxIntensifySubCnt;
            break;
        case E_BAG_ENTER_TYPE_SALE:
            size = MaxSaleCnt;
            break;
        case E_BAG_ENTER_TYPE_FUSE:
            size = MaxFuseCnt;
            break;
        default:
            break;
    }
    
    return m_arrSelectedPet.size() >= size;
}

//刷新背包界面}
void CPetCtrl::ReflashPetBag()
{
    if (m_byPetBagType == E_BAG_ENTER_TYPE_INTENSIFY_SUB
        || m_byPetBagType == E_BAG_ENTER_TYPE_SALE)
    {
        CcbPetBagSaleLayer* pPetBag = (CcbPetBagSaleLayer*)CCDirector::sharedDirector()->getNowScene()->getChildByTag(1)->getChildByTag(1);
        if (pPetBag) {
            pPetBag->RefeashLayer();
        }
    }
    else
    {
        CcbPetBagLayer* pPetBag = (CcbPetBagLayer*)CCDirector::sharedDirector()->getNowScene()->getChildByTag(1)->getChildByTag(1);
        if (pPetBag) {
            pPetBag->RefeashLayer();
        }
    }
}

//强化}
void CPetCtrl::DoIntensifyPet()
{
    m_vecFood.clear();
    for (int i = 0; i < m_arrSelectedPet.size(); i++) {
        if (!m_arrSelectedPet[i]) {
            continue;
        }
        CPet* pPet = GetPetByObjId(m_arrSelectedPet[i]);
        if (!pPet) {
            continue;
        }
        m_vecFood.push_back(pPet->GetwIndex());
    }
    
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendPetEat(m_wIntensifyPetObjId, m_arrSelectedPet.size(), m_arrSelectedPet);
}

CPetCtrl::VEC_PETS CPetCtrl::GetFoodIndex()
{
    return m_vecFood;
}

void CPetCtrl::DoEvolvePet()
{
    CGameSession::SendPetEvolve(m_wEvolvePetObjId);
}

void CPetCtrl::DoSalePet(std::vector<uint32> arrPetObjId)
{
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendPetSell(arrPetObjId.size(), arrPetObjId);
}

//设置锁定}
void CPetCtrl::setPetLocked(uint32 dwObjId, bool isLock)
{
    m_mapChgLockedPet[dwObjId] = isLock;
}
//保存锁定}
void CPetCtrl::saveLocked()
{
    std::map<uint32, bool> toSave;
    std::map<uint32, bool>::iterator it = m_mapChgLockedPet.begin();
    for (; it != m_mapChgLockedPet.end(); it++) {
        CPet *pet = GetPetByObjId(it->first);
        if (!pet) {
            continue;
        }
        if (pet->GetbIsLock() == it->second) {
            continue;
        }
        toSave[it->first] = it->second;
    }
    if (toSave.size() == 0) {
        return;
    }
    CGameSession::SendPetLocked(toSave);
    m_mapChgLockedPet.clear();
    toSave.clear();
}

void CPetCtrl::setPetBagOffSet(CCPoint offset)
{
    if(m_mapPetBagOffSet.find(m_byPetBagType) == m_mapPetBagOffSet.end())
    {
        m_mapPetBagOffSet.insert( std::make_pair(m_byPetBagType, offset));
    }
    else
    {
        m_mapPetBagOffSet[m_byPetBagType] = offset;
    }
}
CCPoint CPetCtrl::getPetBagOffSet()
{
    if(m_mapPetBagOffSet.find(m_byPetBagType) == m_mapPetBagOffSet.end())
    {
        m_mapPetBagOffSet.insert( std::make_pair(m_byPetBagType, ccp(0, 1)));
    }
    return m_mapPetBagOffSet[m_byPetBagType];
}


std::string CPetCtrl::getPassSkillIcon(uint32 dwPassSkillId)
{
    std::string path = PIC_DEFAULT;//"icon/rune/30100007.png";
    if (dwPassSkillId / E_UNITE_BASE_FABIO == E_SKILL_TYPE_PASSIVE) {
        PassiveSkillConfig::STC_PASSIVE_SKILL_CONFIG *pCfg = GET_CONFIG_STC(PassiveSkillConfig, dwPassSkillId);
        if (pCfg) {
            path = ConfigGet::GetSkillIconByIndexID(pCfg->wIcon);
        }
    }
    else if(dwPassSkillId / E_UNITE_BASE_FABIO == E_SKILL_TYPE_TALENT)
    {
        TalentConfig::STC_TALENT_CONFIG *pCfg = GET_CONFIG_STC(TalentConfig, dwPassSkillId);
        if (pCfg) {
            path = ConfigGet::GetSkillIconByIndexID(pCfg->dwIcon);
        }
    }
    CCTexture2D* te = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
    if (!te) {
        path = PIC_DEFAULT;//"icon/rune/30100007.png";
    }
    return path;
}

//根据星级获得宠物品质}
uint8 CPetCtrl::getPetQuality(uint16 wPetId)
{
    uint8 quality = E_GACHA_EGG_TYPE_XIYOU;
    PetConfig::STC_PET_CONFIG* pCfg = GET_CONFIG_STC(PetConfig, wPetId);
    if (pCfg) {
        if (pCfg->byStarLv >= 6) {
            quality = 4;
        }
        else if(pCfg->byStarLv == 5)
        {
            quality = E_GACHA_EGG_TYPE_CHAOJUE_XIYOU;
        }
        else if (pCfg->byStarLv == 4){
            quality = E_GACHA_EGG_TYPE_CHAO_XIYOU;
        }
    }
    return quality;
}

//获取属性文字}
std::string CPetCtrl::getNatureText(uint8 nature)
{
    std::string str = "";
    switch (nature) {
        case E_NATURE_WATER:
            str = GET_STR(Str_attr_water);
            break;
        case E_NATURE_FIRE:
            str = GET_STR(Str_attr_fire);
            break;
        case E_NATURE_GRASS:
            str = GET_STR(Str_attr_grass);
            break;
        case E_NATURE_THUNDER:
            str = GET_STR(Str_attr_thunder);
            break;
        case E_NATURE_LIGHT:
            str = GET_STR(Str_attr_light);
            break;
        case E_NATURE_DARK:
            str = GET_STR(Str_attr_dark);
            break;
        default:
            break;
    }
    
    return str;
}

//获取宠物当前等级、进阶 的基础六维值
STC_PET_BASE_INFO CPetCtrl::getPetBaseValueByObjId(uint32 petObjId, uint16 lv)
{
    STC_PET_BASE_INFO baseInfo;
    CPet* pet = GetPetByObjId(petObjId);
    if (!pet) {
        return baseInfo;
    }
    if (lv == 0) {
        lv = pet->GetbyLv();
    }
    PetConfig::STC_PET_CONFIG* petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
    baseInfo.dwHp = petCfg->dwHpValue + (lv-1)*petCfg->dwHpChg / 1000;
    baseInfo.dwCAtk = petCfg->dwAttackValue + (lv-1)*petCfg->dwAttackChg / 1000;
    baseInfo.dwCDef = petCfg->dwDeffenseValue + (lv-1)*petCfg->dwDeffenseChg / 1000;
    baseInfo.dwSAtk = petCfg->dwSAttackValue + (lv-1)*petCfg->dwSAttackChg / 1000;
    baseInfo.dwSDef = petCfg->dwSDeffenseValue + (lv-1)*petCfg->dwSDeffenseChg / 1000;
    baseInfo.dwRev = petCfg->dwRecoverValue + (lv-1)*petCfg->dwRecoverChg / 1000;
    
    
    
    uint16 eLv = pet->GetbyEvolveLv();
    //2、找到基础index}
    uint16 baseId = 0;
    EvolveConfig::STC_EVOLVE_CONFIG* eCfg = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(pet->GetwIndex(), eLv));
    if (eCfg) {
        baseId = eCfg->wBasePetId;
    }
    //3、从0阶开始查找}
    uint32 nextEvoId = GET_EVOLVE_ID(baseId, 0);
    while (true) {
        EvolveConfig::STC_EVOLVE_CONFIG* eCfg = GET_CONFIG_STC(EvolveConfig, nextEvoId);
        if (!eCfg) {
            break;
        }
        nextEvoId = eCfg->wNextId;
        baseInfo.dwHp += eCfg->dwAddHP;
        baseInfo.dwCAtk += eCfg->dwAddCATK;
        baseInfo.dwCDef += eCfg->dwAddCDEF;
        baseInfo.dwSAtk += eCfg->dwAddSATK;
        baseInfo.dwSDef += eCfg->dwAddSDEF;
        baseInfo.dwRev += eCfg->dwAddREV;
    }
    
    return baseInfo;
}

STC_PET_BASE_INFO CPetCtrl::getEmblemAddValue(uint32 petObjId, STC_PET_BASE_INFO baseValue)
{
    STC_PET_BASE_INFO addInfo;
    CPet* pet = GetPetByObjId(petObjId);
    if (!pet ||
        (!pet->GetdwEmblemId1() && !pet->GetdwEmblemId2())) {
        return addInfo;
    }
    EvolveConfig::STC_EVOLVE_CONFIG *evoCfg = GET_CONFIG_STC(EvolveConfig, GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv()));
    
    std::vector<uint32> arrEmbObjId;
    arrEmbObjId.push_back(pet->GetdwEmblemId1());
    arrEmbObjId.push_back(pet->GetdwEmblemId2());
    std::vector<uint8> arrType;
    std::vector<uint8> arrAddType;
    std::vector<uint32> arrValue;
    for (int i = 0; i < arrEmbObjId.size(); i++) {
        if (!arrEmbObjId[i]) {
            continue;
        }
        
        CEmblem* emb = g_EmblemData->getEmblemByObjId(arrEmbObjId[i]);
        if (!emb) {
            continue;
        }
        EmblemConfig::STC_EMBLEM_CONFIG* embCfg = GET_CONFIG_STC(EmblemConfig, emb->getdwIndexId());
        if (!embCfg) {
            continue;
        }
        
        for (int e = 0; e < 3; e++) {
            if (embCfg->byAttrType[e]) {
                arrType.push_back(embCfg->byAttribute[e]);
                arrAddType.push_back(embCfg->byAttrType[e]);
                float attvalue = embCfg->dwAttrValue[e] + (emb->getbyLv() - 1)*embCfg->dwAttrChg[e];
                arrValue.push_back(attvalue);
            }
        }
        
        for (int e = 0; e < 5; e++) {
            if (embCfg->wExcPetIndex[e] == evoCfg->wBasePetId) {
                arrType.push_back(embCfg->byExcAttr[e]);
                arrAddType.push_back(2);    //专属加成都是百分比
                arrValue.push_back(embCfg->dwExcAttrValue[e]);
            }
        }
    }

    for (int i = 0; i < arrType.size(); i++) {
        switch (arrType[i]) {
            case E_ATTR_ALL_ATT:
                if (arrAddType[i] == 1) {
                    addInfo.dwCAtk += arrValue[i];
                    addInfo.dwSAtk += arrValue[i];
                }
                else{
                    addInfo.dwCAtk += baseValue.dwCAtk*arrValue[i] / 10000;
                    addInfo.dwSAtk += baseValue.dwSAtk*arrValue[i] / 10000;
                }
                break;
            case E_ATTR_HP:
                if (arrAddType[i] == 1) {
                    addInfo.dwHp += arrValue[i];
                }
                else{
                    addInfo.dwHp += baseValue.dwHp*arrValue[i] / 10000;
                }
                break;
            case E_ATTR_CATT:
                if (arrAddType[i] == 1) {
                    addInfo.dwCAtk += arrValue[i];
                }
                else{
                    addInfo.dwCAtk += baseValue.dwCAtk*arrValue[i] / 10000;
                }
                break;
            case E_ATTR_CDEF:
                if (arrAddType[i] == 1) {
                    addInfo.dwCDef += arrValue[i];
                }
                else{
                    addInfo.dwCDef += baseValue.dwCDef*arrValue[i] / 10000;
                }
                break;
            case E_ATTR_SATT:
                if (arrAddType[i] == 1) {
                    addInfo.dwSAtk += arrValue[i];
                }
                else{
                    addInfo.dwSAtk += baseValue.dwSAtk*arrValue[i] / 10000;
                }
                break;
            case E_ATTR_SDEF:
                if (arrAddType[i] == 1) {
                    addInfo.dwSDef += arrValue[i];
                }
                else{
                    addInfo.dwSDef += baseValue.dwSDef*arrValue[i] / 10000;
                }
                break;
            case E_ATTR_REV:
                if (arrAddType[i] == 1) {
                    addInfo.dwRev += arrValue[i];
                }
                else{
                    addInfo.dwRev += baseValue.dwRev*arrValue[i] / 10000;
                }
                break;
                
            default:
                break;
        }
    }
    
    return addInfo;
}

//判断情缘
std::vector<uint8> CPetCtrl::checkQingyuan(uint32 qyId)
{
    std::vector<uint8> arrQy;
    QingYuanConfig::STC_QING_YUAN_CONFIG* qyCfg = GET_CONFIG_STC(QingYuanConfig, qyId);
    if (!qyCfg) {
        return arrQy;
    }
    
    int len = 0;
    GET_ARRAY_LEN(qyCfg->dwQyPetGroup, len);
    CTeam* team = CTeamCtrl::GetCurTeam();
    std::set<uint32> arrPetGroup;
    //将当期队伍中所有成员的groupId加入到set中，方便查找
    for (int i = 1; i < 7; i++) {
        if (!team->getarrPetObId()[i]) {
            continue;
        }
        CPet*pet = GetPetByObjId(team->getarrPetObId()[i]);
        if (!pet) {
            continue;
        }
        PetConfig::STC_PET_CONFIG* pCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
        if (!pCfg) {
            continue;
        }
        arrPetGroup.insert(pCfg->wGroupId);
    }
    
    //遍历情缘中宠物groupId，判断是否在队伍中，只有全部都在队伍中时，才被激活
    for (int i = 0; i < len; i ++) {
        if (!qyCfg->dwQyPetGroup[i]) {
            arrQy.push_back(1);
            continue;
        }
        if (arrPetGroup.find(qyCfg->dwQyPetGroup[i]) != arrPetGroup.end()){
            arrQy.push_back(1);
        }
        else{
            arrQy.push_back(0);
        }
    }
    
    return arrQy;
}

//情缘激活状态
bool CPetCtrl::checkQingyuanActi(uint32 qyId)
{
    std::vector<uint8> arrQy = checkQingyuan(qyId);
    if (arrQy.size() == 0) {
        return false;
    }
    
    for (int i = 0; i < arrQy.size(); i++) {
        if (arrQy[i] == 0) {
            return false;
        }
    }
    return true;
}