#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include "HttpRequest.h"

class HttpClient
{
public:
	static HttpClient* GetInstance();
	static void DestroyInstance();

public:
	HttpClient();
	virtual ~HttpClient();

	void Send( HttpRequest* pRequest );
	void DispatchResponse();

	int GetTimeoutForRead() { return m_dwTimeoutForRead; }
	void SetTimeoutForRead( int value ) { m_dwTimeoutForRead = value; }

	int GetTimeoutForConnect() { return m_dwTimeoutForConnect; }
	void SetTimeoutForConnect( int value ) { m_dwTimeoutForConnect = value; }
    
    int GetProgressByte();
    void SetProgressByte( int value );

    static void SetSemName(const std::string& sem_name);
protected:

	bool InitThreadSemphore();

	int m_dwTimeoutForRead;
	int m_dwTimeoutForConnect;
    
    int m_dwProgressByte;


};

#endif
