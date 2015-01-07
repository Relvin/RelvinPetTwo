


#ifndef _NET_CLIENT_H
#define _NET_CLIENT_H

#include "cocos2d.h"
USING_NS_CC;

#include "curl/curl.h"
#include "WorldPacket.h"

class CSocketBuffer;
class CNetBase;


class CNetClient: public CCObject
{
public:
	typedef enum {
		CONN_STATE_DISCONNECT,
		CONN_STATE_CONNECTING,
		CONN_STATE_CONNECTED
	} eConnectState;


	CNetClient();
	~CNetClient();


	bool Init();

	void End();


	bool Connect(const char * szServerAddr, int nPort);

	bool IsConnect() { return m_eConnectState == CONN_STATE_CONNECTED;}
	eConnectState connectState() { return m_eConnectState; }
    void setConnectStage(eConnectState state) {
        m_eConnectState = state;
    }

	virtual void OnConnect();
	//
	virtual void OnDisConnect();

	void OnProcessPacket(WorldPacket & packet);

	void OnRead();
	void OnWrite();

	void SendData(WorldPacket & packet);
	void SendQQData(WorldPacket & packet, uint16 SvrID);
	bool IsTryAgain();

	void QQTick();
	size_t QQGetBufSize();
private:
	void Tick(float dt);
	void HBeaT(float dt);
private:
#ifdef NET_CURL

	CURL * m_curl;
#else
	CNetBase * m_pNetBase;
#endif
	uint16 GSvrID;

	eConnectState m_eConnectState;

	CSocketBuffer * m_pBufferInput;
	CSocketBuffer * m_pBufferOutput;

	static const int m_nTickTime = 33;
	static const int m_nHBeatTime = 20000;

};

#endif
