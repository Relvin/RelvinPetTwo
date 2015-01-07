#include "MapScene.h"
#include "CcbManager.h"
#include "GameStateManager.h"
#include "GameSession.h"
#include "Role.h"
#include "BackCtrl.h"
#include "StageScene.h"
#include "GuideData.h"
#include "CcbSystemBootInfoLayer.h"

USING_NS_CC_EXT;

#pragma mark MapCtrl

int MapCtrl::nOpenArea;
MapCtrl::VECTOR_AREA_TYPE MapCtrl::m_vecArea;
MapCtrl::VECTOR_SPECIAL_TYPE MapCtrl::m_vecSpe;
int MapCtrl::nSelectedMapId = 1;
MapCtrl::VEC_MAP_STAR MapCtrl::m_vecMapStar[2];
uint8 MapCtrl::bMapPointClicked = 1;
uint8 MapCtrl::bNeedShowNextMessage = 0;

void MapCtrl::ReloadMapInfo()
{
    CRole* pRole = CGameSession::GetRole();
    uint16 wOpenMap;   // 已经开放的地图点数量，绑定在人物身上，初始为0，所以第一个地图开放，使用时加一}
//    // test!!!
//    wOpenMap = 23;
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
        wOpenMap = pRole->GetwPassMapId() + 1;
    } else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
        wOpenMap = pRole->GetwHeroMap() + 1;
    }
    
    for (int i = 1; i <= wOpenMap; i++) {
        MapConfig::STC_MAP_CONFIG* pMapConfig = GET_CONFIG_STC(MapConfig, i);

        if (!pMapConfig) {
            return;
        }
        
        STC_MAP_POINT t_config;
        t_config.map_config = *pMapConfig;
//        t_config.map_config.wMapId = pMapConfig
//        CCLOG("old:%d,%d \t new:%d,%d",pMapConfig->posX, pMapConfig->posY, t_config.map_config.posX, t_config.map_config.posY);
        
        for (VECTOR_SPECIAL_TYPE::const_iterator it = m_vecSpe.begin(); it != m_vecSpe.end(); it++) {
            if (pMapConfig->wMapId == it->wMapId) {
                t_config.strDes = it->strDes;
                t_config.strTime = it->strTime;
                break;
            }
        }
        
        const uint8 tAreaId = pMapConfig->byAreaId;
        if (nOpenArea < tAreaId) {
            // 新area的地图点，新建一个地图点vector，然后加入到area中}
            nOpenArea = tAreaId;
            VECTOR_POINT_TYPE vecPoint;
            vecPoint.push_back(t_config);
            m_vecArea.push_back(vecPoint);
        } else {
            // 已有area的地图点，直接加入，记得area在配表中是由1开始的}
            m_vecArea[tAreaId-1].push_back(t_config);
        }
    }
}

void MapCtrl::HandlerMapInfoSpecial(WorldPacket &packet)
{
    m_vecSpe.clear();
    m_vecArea.clear();
    nOpenArea = 0;
    nSelectedMapId = 0;
    
    uint8 wSize;
    
    packet >> wSize;
    for (int i = 0; i < wSize; i++) {
        STC_SPECIAL special;
        packet >> special.wMapId;
        packet >> special.strDes;
        packet >> special.strTime;
        m_vecSpe.push_back(special);
    }
    ReloadMapInfo();
    if (BackCtrl::GetCurSceneIdx() == kActivityMapScene || BackCtrl::GetCurSceneIdx() == kMapScene) {
        // 如果从特殊活动界面进入则替换当前scene}
        BackCtrl::ReplaceCurScene(kMapScene, kFadeTrans);
    } else {
        BackCtrl::InsertNextScene(kMapScene, kFadeTrans);
    }
}

uint32 MapCtrl::starCntInMap(int _kind, uint16 _map) {
    for (VEC_MAP_STAR::iterator pIter = m_vecMapStar[_kind].begin(); pIter != m_vecMapStar[_kind].end(); pIter++) {
        if (pIter->wMapId == _map) {
            return pIter->dwStarNum;
        }
    }
    return 0;
}

void MapCtrl::setMapPointClicked(int _kind, uint16 _map) {
    for (VEC_MAP_STAR::iterator pIter = m_vecMapStar[_kind].begin(); pIter != m_vecMapStar[_kind].end(); pIter++) {
        if (pIter->wMapId == _map) {
            bMapPointClicked = pIter->byIsClicked;
            return;
        }
    }
    bMapPointClicked = 0;
}

void MapCtrl::hasNewMapPointOpen() {
    // 判断是否是该Map点通关，如果通关则跳转到下一个地图点
    uint16 wPassMapId = 0;
    uint16 wPassStageId = 0;
    CRole* pRole = CGameSession::GetRole();
    
    if (pRole->GetwPassStageId() < 2005) {
        bNeedShowNextMessage = false;
        return;
    }
    
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
        wPassMapId = pRole->GetwPassMapId() + 1;
        wPassStageId = pRole->GetwPassStageId();
    } else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
        wPassMapId = pRole->GetwHeroMap() + 1;
        wPassStageId = pRole->GetwHeroStage();
    }
    if (wPassStageId / 1000 < wPassMapId) {
        // 地图刚开启 @Ref CcbDropTipFrameLayer.cpp:Line:450
        bNeedShowNextMessage = true;
        return;
    }
    bNeedShowNextMessage = false;
}

void MapCtrl::HandlerMapStarInfo(WorldPacket &packet) {
    uint8 byType;
    uint8 bySize;
    
    m_vecMapStar[0].clear();
    m_vecMapStar[1].clear();
    
    packet >> byType;
    if (byType == kMapStarNormal) {
        packet >> bySize;
        for (int i = 0; i < bySize; i++) {
            STC_MAP_STAR stcStar;
            packet >> stcStar.wMapId >> stcStar.dwStarNum >> stcStar.byIsClicked;
            m_vecMapStar[byType].push_back(stcStar);
            
//            CCLOG("normal mapId:%d, starNum:%d, isClicked:%d", stcStar.wMapId, stcStar.dwStarNum, stcStar.byIsClicked);
        }
    }
    
    packet >> byType;
    if (byType == kMapStarHero) {
        packet >> bySize;
        for (int i = 0; i < bySize; i++) {
            STC_MAP_STAR stcStar;
            packet >> stcStar.wMapId >> stcStar.dwStarNum >> stcStar.byIsClicked;
            m_vecMapStar[byType].push_back(stcStar);
        }
    }
}

void MapCtrl::HandlerMapStarUpdate(WorldPacket &packet) {
    uint8 byType;
    STC_MAP_STAR stcStar;
    
    packet >> byType >> stcStar.wMapId >> stcStar.dwStarNum >> stcStar.byIsClicked;
    
//    CCLOG("update type:%d, mapid:%d, starnum:%d, isclicked:%d", byType, stcStar.wMapId, stcStar.dwStarNum, stcStar.byIsClicked);
    
    for (VEC_MAP_STAR::iterator pIter = m_vecMapStar[byType].begin(); pIter != m_vecMapStar[byType].end(); pIter++) {
        if (pIter->wMapId == stcStar.wMapId) {
            pIter->dwStarNum = stcStar.dwStarNum;
            pIter->byIsClicked = stcStar.byIsClicked;
            return;
        }
    }
    
    // new map point, should add to vec
    m_vecMapStar[byType].push_back(stcStar);
}

#pragma mark MapScene

MapScene::~MapScene()
{
    
}

CCScene* MapScene::scene()
{
    CCScene* scene = CCScene::create();
    MapScene* pLayer = MapScene::create();
    scene->addChild(pLayer);
    return scene;
}

bool MapScene::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    addChild(CcbManager::sharedManager()->LoadMapLayer(this));
	return true;
}

void MapScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CCLOG("map scene stack cnt:%d", CCDirector::sharedDirector()->GetSceneStackCnt());
    // 所有的战斗结束后均跳转到StageLayer界面，此处的判断可以去除}
//    CcbSystemBootInfoLayer::showSystemBootInfo(GuideData::GetInstance()->getSysLockId(), this);
}

void MapScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void MapScene::onExit()
{
	CCLayer::onExit();
}

void MapScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}




