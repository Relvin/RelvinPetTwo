#include "GameSession.h"
#include "NetClient.h"
#include "SocketBuffer.h"

#include "ClientPacketHandler.h"
#include "NetBase.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#endif
#include "Encode.h"
#include "LoginSystem.h"
#include "GlobalData.h"
#include "StartGameLayer.h"

CNetClient::CNetClient()
:m_eConnectState(CONN_STATE_DISCONNECT)
{
#ifdef NET_CURL
	m_curl = NULL;
#else 
	m_pNetBase = NULL;
#endif

	m_pBufferInput = new CSocketBuffer();
	m_pBufferOutput = new CSocketBuffer();

	m_pBufferInput->Init();
	m_pBufferOutput->Init();
	GSvrID = 0;
}
CNetClient::~CNetClient()
{
	delete m_pBufferInput;
	delete m_pBufferOutput;
	if (m_pNetBase)
		delete m_pNetBase;
}
bool CNetClient::Init()
{
#ifdef NET_CURL
	m_curl = curl_easy_init();

	if (!m_curl)
		return false;
	return true;
#else 
	m_pNetBase = new CNetBase;
	if (m_pNetBase->Init() == -1)
		return false;
	return m_pNetBase->Create();
#endif
}
void CNetClient::End()
{
	m_pBufferInput->Erase(m_pBufferInput->GetSize());
	m_pBufferOutput->Erase(m_pBufferOutput->GetSize());
	m_eConnectState = CONN_STATE_DISCONNECT;
    CCLog("CNetClient::End()");
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CNetClient::Tick), this);
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CNetClient::HBeaT), this);

#ifdef NET_CURL
	// always cleanup 
	if (m_curl)
	{
		curl_easy_cleanup(m_curl);
		m_curl = 0;
	}
#else
	if (m_pNetBase)
	{
		m_pNetBase->Close();
		m_pNetBase->Clean();
		delete m_pNetBase;
		m_pNetBase = NULL;
	}
#endif
}
bool CNetClient::Connect(const char * szServerAddr, int nPort)
{

	if (!Init())
	{
		CCLOG("NetClient Init failed!");
		return false;
	}

#ifdef NET_CURL
	CURLcode res;
	m_eConnectState = CONN_STATE_CONNECTING;
	if(m_curl) 
	{
		curl_easy_setopt(m_curl, CURLOPT_URL, szServerAddr);
		curl_easy_setopt(m_curl, CURLOPT_PORT, nPort);
		curl_easy_setopt(m_curl, CURLOPT_TIMEOUT,3);

		/* Do not do the transfer - only connect to host */ 
		curl_easy_setopt(m_curl, CURLOPT_CONNECT_ONLY, 1L);
		res = curl_easy_perform(m_curl);
	 
		if(CURLE_OK != res)
		{
			CCLOG("Error: %s\n",strerror(res));
			m_eConnectState = CONN_STATE_DISCONNECT;
			End();
			return false;
		}
		m_eConnectState = CONN_STATE_CONNECTED;
		
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CNetClient::Tick), this, (float)(1.0 * m_nTickTime / 1000), false);
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CNetClient::HBeaT), this, (float)(1.0 * m_nHBeatTime/ 1000), false);
		OnConnect();

		return true;
	}
#else
	m_eConnectState = CONN_STATE_CONNECTING;
	if (m_pNetBase)
	{
		if (m_pNetBase->Connect(szServerAddr,nPort))
		{
			m_eConnectState = CONN_STATE_CONNECTED;

			CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CNetClient::Tick), this, (float)(1.0 * m_nTickTime / 1000), false);
			CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CNetClient::HBeaT), this, (float)(1.0 * m_nHBeatTime/ 1000), false);
            
			OnConnect();
            GlobalData::bStillAlive = true;
			return true;
		} else {    // 网络连接不成功}
            LoginSystem::Get()->ShowNoServiceLayer();
        }
	}

#endif


	m_eConnectState = CONN_STATE_DISCONNECT;
	End();
	return false;
}
void CNetClient::QQTick()
{
	Tick(100);
}
size_t CNetClient::QQGetBufSize()
{
	return m_pBufferOutput->GetSize();
}
void CNetClient::Tick(float dt)
{
	if (!IsConnect())
	{
        //重连}
        LoginSystem::Get()->ShowNoServiceLayer();
		return;
	}

	//do write
	OnWrite();

	//do read
	OnRead();

	if (!IsConnect())
	{
        if (!StartGameLayer::GetCurLayer()) {
            //重连}
            LoginSystem::Get()->ShowNoServiceLayer();
        }
		return;
	}
	
	return ;
}

void CNetClient::HBeaT(float dt){
//	if (GlobalData::bStillAlive) {
//        GlobalData::bStillAlive = false;
//        CGameSession::SendTest();
////        CGameSession::SendLoginTest();
//    } else {    // 到下次循环，仍旧为false，则说明断开连接了}
//        End();
//        LoginSystem::Get()->ShowNoServiceLayer();
//    }
}

void CNetClient::OnProcessPacket(WorldPacket & packet)
{
    CClientPacketHandler::sharedInstance()->processFuckByPacket(packet);
}	

void CNetClient::OnConnect()
{

}
void CNetClient::OnDisConnect()
{
	End();
}

void CNetClient::SendData(WorldPacket & packet)
{
#ifdef NETQQ
	SendQQData(packet, GSvrID);
#else
	uint16 size = packet.size() + 4;
	uint16 cmd = packet.GetOpcode();
    CCLOG("    Send Cmd is :    CMD_MAKE_CLIENT(0x%04x)", (cmd >> 1) & 0xffff);
	m_pBufferOutput->Append((char *)&size,2);
	m_pBufferOutput->Append((char *)&cmd,2);
	if (packet.size() == 0)
		return ;
	m_pBufferOutput->Append(packet.contents(),packet.size());
#endif
	//OnWrite();
}
void CNetClient::SendQQData(WorldPacket & packet, uint16 SvrID){
	short length;
//	uint8 IDLen ;
	std::string IDData = "";//CCApplication::loginUid();
	uint16 size = packet.size() + 4;
	uint16 cmd = packet.GetOpcode();
	if(SvrID != 101 && SvrID != 102){
		GSvrID = SvrID;
	}
	MiniConnProxy::nSvrID = SvrID;
	MiniConnProxy::cOpenIDLen = IDData.length();
	memcpy(MiniConnProxy::szOpenID,IDData.data(),MiniConnProxy::cOpenIDLen);
	MiniConnProxy::cOptionLen = 0;
	MiniConnProxy::nAppPackLen = size;
	memcpy(MiniConnProxy::szAppPackData, &size, 2);
	memcpy(MiniConnProxy::szAppPackData + 2, &cmd, 2);
	memcpy(MiniConnProxy::szAppPackData + 4, packet.contents(), packet.size());
	char data[1024*8];
	if(MiniConnProxy::gEncode(data, length)!=-1){
		m_pBufferOutput->Append((char *)&data, length);
	}
}
void CNetClient::OnRead()
{
	if (!IsConnect())
		return ;
	int nReads;
#ifdef NET_CURL
	CURLcode curlRes;
	nReads = m_pBufferInput->SockRead(m_curl,-1,curlRes);
	if (curlRes != CURLE_OK && curlRes != CURLE_AGAIN || nReads < 0)
	{
		//error
		m_eConnectState = CONN_STATE_DISCONNECT;
		OnDisConnect();
		return ;
	}
	if (curlRes == CURLE_OK && nReads == 0)
	{
		
		OnDisConnect();
		return ;
	}
#else
	nReads = m_pBufferInput->SockRead(m_pNetBase,-1);
	if (nReads == 0)
	{
        // 远程服务器主动断开}
		OnDisConnect();
		return ;
	}

	if ( nReads < 0 && !IsTryAgain() )
	{
        // 错误}
		OnDisConnect();
		return ;
	}
	
#endif

    // 分发包}
	size_t buffSize = 0;
	int nParsed = 0;

	char* pData = (char*)m_pBufferInput->GetBuffer(buffSize);
#ifdef NETQQ
	if(buffSize < 6)
		return ;

	while( 1 )
	{

		if(buffSize < 6)
			break;

		uint16 wLen = 0;
		uint16 lengh = 0;
		memcpy(&lengh,pData+sizeof(uint16),sizeof(uint16));
		wLen = lengh + 2;
		lengh = wLen +2;
		if(wLen > buffSize)
			break;

		uint16 wCmd = 0;
		memcpy(&wCmd,pData + sizeof(uint16)*2,sizeof(uint16)*2);
		uint16 wRemaining = wLen - 6;

		///- Read the remaining of the packet
        	WorldPacket packet(wCmd, wRemaining); 

		if( wRemaining>0 ) {
			packet.resize(wRemaining);
			memcpy((char *)(packet.contents()),pData + 6,wRemaining);
		}


		//m_pBufferInput->BufferRead((char*)packet.contents(), _remaining);

		OnProcessPacket(packet);
		
		pData += wLen;		
		buffSize -= wLen;		
		nParsed += wLen;	
	}
#else
	if(buffSize < 4) {
		return ;
    }

	while( 1 )
	{

		if(buffSize < 4) {
            break;
        }

		uint16 wLen = 0;
		memcpy(&wLen,pData,sizeof(uint16));

		if(wLen > buffSize)
			break;

		uint16 wCmd = 0;
		memcpy(&wCmd,pData + sizeof(uint16),sizeof(uint16));
		uint16 wRemaining = wLen - 4;

		///- Read the remaining of the packet
        WorldPacket packet(wCmd, wRemaining);

		if( wRemaining>0 ) {
			packet.resize(wRemaining);
			memcpy((char *)(packet.contents()),pData + 4,wRemaining);
		}


		//m_pBufferInput->BufferRead((char*)packet.contents(), _remaining);

		OnProcessPacket(packet);
		
		pData += wLen;		
		buffSize -= wLen;		
		nParsed += wLen;	
	}
#endif
	if( nParsed > 0 )
	{
		m_pBufferInput->Erase(nParsed);	
	}

}
void CNetClient::OnWrite()
{
    if (!IsConnect()) {
        End();
        return;
    }
    
	int nSends;
	if (m_pBufferOutput->GetSize() <= 0)
		return ;
#ifdef NET_CURL
	CURLcode curlRes;
	nSends = m_pBufferOutput->Sends(m_curl,curlRes);
	if (curlRes != CURLE_OK && curlRes != CURLE_AGAIN || nSends < 0)
	{
		//error
		m_eConnectState = CONN_STATE_DISCONNECT;
		OnDisConnect();
		return ;
	}
#else
	nSends = m_pBufferOutput->Sends(m_pNetBase);
	if (nSends < 0)
	{
		//error
		CCLOG("NetBase send error %d",m_pNetBase->GetError());
		m_eConnectState = CONN_STATE_DISCONNECT;
		OnDisConnect();
		return ;
	}
#endif

}

bool CNetClient::IsTryAgain()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return WSAGetLastError() == WSATRY_AGAIN|| WSAGetLastError() == WSAEWOULDBLOCK;
#else
	return EAGAIN == errno || EWOULDBLOCK == errno;
#endif

}