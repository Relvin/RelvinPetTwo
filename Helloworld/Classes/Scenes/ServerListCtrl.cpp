//
//  ServerListCtrl.cpp
//  HelloWorld
//
//  Created by junjie zhu on 13-9-27.
//
//

#include "ServerListCtrl.h"
#include "GameSession.h"
#include "LoginSystem.h"
#include "SystemMessage.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "PetLoadingLayer.h"

void ServerListCtrl::setServerList(WorldPacket &packet)
{
    m_vecArea.clear();
    packet >> m_dwVersion;
    packet >> m_strNotice;
    packet >> m_wAreaNum;
    for (int i = 0; i < m_wAreaNum; i++) {
        STC_AREA stcArea;
        packet >> stcArea.wAreaId;
        packet >> stcArea.strAreaName;
        packet >> stcArea.byStatus;
        packet >> stcArea.dwResourceVersion;
        m_vecArea.push_back(stcArea);
    }
    
    if (!m_strNotice.empty() || m_strNotice != "") {
        SystemMessage::showSystemMessage(0, NULL, m_strNotice.c_str(), NULL, true, 0, GET_STR(Str_warning), true);
        PetLoadingLayer::sharedLayer()->End();
    } else {
        CGameSession::NotifyRefeashLayer();
        LoginSystem::Get()->SetServerCallback();
    }
}

const char* ServerListCtrl::getAreaName(int idx) {
    if (m_vecArea.empty() || m_vecArea.size() <= idx) {
        return "null server";
    }
    return m_vecArea[idx].strAreaName.c_str();
}

uint8 ServerListCtrl::getAreaStatus(int idx) {
    if (m_vecArea.empty()) {
        return E_SERVER_STATUS_MAINTAIN;
    }
    return m_vecArea[idx].byStatus;
}

uint32 ServerListCtrl::resourceVersion()
{
    if (m_nSelected >= m_wAreaNum) {
        m_nSelected = m_wAreaNum - 1;
    }
    if (m_nSelected < 0) {
        m_nSelected = 0;
    }
    if (m_vecArea.empty()) {
        return -1;
    }
    return m_vecArea[m_nSelected].dwResourceVersion;
}

uint16 ServerListCtrl::getAreaId(int idx)
{
    if (m_vecArea.empty()) {
        return -1;
    }
    return m_vecArea[idx].wAreaId;
}

const char* ServerListCtrl::selectedServerName() {
    return getAreaName(m_nSelected);
}
