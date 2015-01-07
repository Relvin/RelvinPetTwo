/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-08 10:34:56
*/

#ifndef __MAPSCENE__H__
#define __MAPSCENE__H__

#include "cocos2d.h"
#include "game_config.h"
#include "WorldPacket.h"

USING_NS_CC;

class MapCtrl {
    
public:
    MapCtrl() {};
    ~MapCtrl() {};
    
    // 地图点信息}
    typedef struct _STC_MAP_POINT
    {
        MapConfig::STC_MAP_CONFIG map_config;
        std::string strDes;
        std::string strTime;
        _STC_MAP_POINT() {
            strDes = "";
            strTime = "";
        }
    }STC_MAP_POINT;
    
    // 特殊活动信息，更新地图用}
    typedef struct _STC_SPECIAL
    {
        uint16 wMapId;
        std::string strDes;
        std::string strTime;
        _STC_SPECIAL() {
            wMapId = 0;
            strDes = "";
            strTime = "";
        }
    }STC_SPECIAL;
    
    // MapPoint Star Cnt
    typedef struct _STC_MAP_STAR {
        uint16 wMapId;
        uint32 dwStarNum;
        uint8 byIsClicked;
        _STC_MAP_STAR() {
            wMapId = 0;
            dwStarNum = 0;
            byIsClicked = 0;
        }
    }STC_MAP_STAR;
    
    enum {
        kMapStarNormal = 0,
        kMapStarHero = 1,
    };
    
    static uint32 starCntInMap(int _kind, uint16 _map);
    static void setMapPointClicked(int _kind, uint16 _map);
    static void hasNewMapPointOpen();
    
    static uint8 bMapPointClicked;
    static uint8 bNeedShowNextMessage;
public:
    typedef std::vector<STC_MAP_POINT> VECTOR_POINT_TYPE;   // 地图点vector，存有地图所有信息}
    typedef std::vector<STC_SPECIAL> VECTOR_SPECIAL_TYPE;   // 特殊活动地图点vector，只存有地图id}
    typedef std::vector<VECTOR_POINT_TYPE> VECTOR_AREA_TYPE;// area扇形大地图，包含地图点vector}
    typedef std::vector<STC_MAP_STAR> VEC_MAP_STAR; // map star vector
    
    static void HandlerMapInfoSpecial(WorldPacket &packet);
    static void HandlerMapStarInfo(WorldPacket &packet);
    static void HandlerMapStarUpdate(WorldPacket &packet);
    
    static VECTOR_AREA_TYPE m_vecArea; // Area vector，扇形地图，包含地图点vector}
    static int nOpenArea;   // 已经开放的Area数量，扇形大地图开放了几个，最小为1}
    static int nSelectedMapId;  // 选中的地图Id，地图Id最小为1，为了在stage界面可以知道是从哪个地图点进来的！}
    
    static VEC_MAP_STAR m_vecMapStar[2];
private:
    static void ReloadMapInfo();
    static VECTOR_SPECIAL_TYPE m_vecSpe;
};

class MapScene:
	public cocos2d::CCLayer
{
public:
	// Constructor
	MapScene()
	{
	}
	~MapScene();

	// must have
	static cocos2d::CCScene* scene();
    CREATE_FUNC(MapScene);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

};


#endif // __MAPSCENE__H__