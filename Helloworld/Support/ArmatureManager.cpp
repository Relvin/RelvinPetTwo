//
//  ArmatureManager.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14-8-22.}
//
//

#include "ArmatureManager.h"
#include "ConfigData.h"
#include "game_config.h"

static ArmatureManager* m_pInstance = NULL;

ArmatureManager* ArmatureManager::sharedManager() {
    if (!m_pInstance) {
        m_pInstance = new ArmatureManager();
    }
    return m_pInstance;
}

ArmatureManager::ArmatureManager() {
    
}

ArmatureManager::~ArmatureManager() {
    if (m_pInstance) {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

CCArmature* ArmatureManager::LoadArmature(std::string path, const char* name, int idx)
{
    // remove sigle resource
    CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo(path.c_str());
    
    // load resource directly
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(path.c_str());
    m_path = path;
    
    CCArmature *armature = CCArmature::create(name);
    if (armature) {
        armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(ArmatureManager::callBack));
        armature->getAnimation()->playWithIndex(idx);
        
    }

    return armature;
}

#pragma mark Static Method
std::string ArmatureManager::GetArmaturePath(uint16 wArmId)
{
    std::string strPath;
    ArmatureConfig::STC_CONFIG_ARMATURE* pConfig = GET_CONFIG_STC(ArmatureConfig, wArmId);
    if (pConfig) {
        return pConfig->strPath;
    }
    return "";
}

std::string ArmatureManager::GetArmatureName(uint16 wArmId)
{
    std::string strName;
    ArmatureConfig::STC_CONFIG_ARMATURE* pConfig = GET_CONFIG_STC(ArmatureConfig, wArmId);
    if (pConfig) {
        return pConfig->strName;
    }
    return "";
}

void ArmatureManager::callBack(CCArmature * armature, MovementEventType meType, const char * name)
{
    if (meType == COMPLETE) {
        armature->getAnimation()->setMovementEventCallFunc(NULL, NULL);
        CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo(m_path.c_str());
    }
}
