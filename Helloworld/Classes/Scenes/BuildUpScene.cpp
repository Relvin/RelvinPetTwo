//
//  BuildUpScene.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-12-20.}
//
//

#include "BuildUpScene.h"
#include "CcbManager.h"
#include "CcbBuildUpLayer.h"
#include "BackCtrl.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"

#pragma mark BuildUpDataMgr
void CBuildUpDataMgr::handlerUpgradeInfo(WorldPacket &packet)
{
    uint8 bySize;
    packet >> bySize;
    
    m_mapBuild.clear();
    for (int i = 0; i < bySize; i++) {
        uint8 byType;
        STC_BUILD_INFO buildInfo;
        
        packet >> byType;
        packet >> buildInfo.wBuildLv >> buildInfo.dwMoney >> buildInfo.dwHun;
        
        m_mapBuild.insert( std::make_pair(byType, buildInfo) );
    }
    
    if (CcbBuildUpLayer::GetCurLayer()) {
        CcbBuildUpLayer::GetCurLayer()->UpdateInfo(m_mapBuild);
    } else {
        BackCtrl::InsertNextScene(kBuildUpScene);
    }
}

CBuildUpDataMgr::STC_BUILD_INFO CBuildUpDataMgr::getBuildingByType(uint8 kType)
{
    STC_BUILD_INFO stcInfo;
    MAP_INFO::iterator iter = m_mapBuild.find(kType);
    if (iter != m_mapBuild.end()) {
        stcInfo = iter->second;
    }
    return stcInfo;
}

#pragma mark BuildUpScene

CCScene* BuildUpScene::scene()
{
    CCScene* pScene = CCScene::create();
    BuildUpScene* pLayer = BuildUpScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool BuildUpScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbBuildUpLayer(this));
    return true;
}

void BuildUpScene::onEnter()
{
    CCLayer::onEnter();
//    m_pLabelTTFName->setStrokeForLabelTTF(ccBLACK, 1.0);
    m_pLabelTTFName->setString(GET_STR(Str_build_up));
}

void BuildUpScene::onExit()
{
    CCLayer::onExit();
}

bool BuildUpScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    return false;
}

