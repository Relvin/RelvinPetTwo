#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <string>

class HttpResponse;
class HttpRequest
{
public:
    
	typedef void (*ResponseCallback)( void* target, HttpResponse* response );
    
	enum HttpRequestType
	{
		E_HTTP_GET,
		E_HTTP_POST
	};
    
public:
    
	HttpRequest( HttpRequestType eType, std::string strUrl, void* pTarget, ResponseCallback fntCallback )
	:m_eType( eType ), m_strUrl( strUrl ), m_pUserData( NULL ), m_pTarget( pTarget ), m_fntCallback( fntCallback ),
    m_dwRetryCnt( 0 )
	{
	}
    
	~HttpRequest()
	{
	}
    
public:
    
	void SetRequestData( const char *pBuffer, unsigned int dwLength )
	{
		m_strRequestData.clear();
		m_strRequestData.append( pBuffer, dwLength );
	}
    
	HttpRequestType GetType() { return m_eType; }
	const char* GetUrl() { return m_strUrl.c_str(); }
    
	const char* GetRequestData() { return m_strRequestData.c_str(); }
	int GetRequestDataSize() { return m_strRequestData.size(); }
    
	void* GetUserData() { return m_pUserData; }
	void SetUserData( void* value ) { m_pUserData = value; }
    
	ResponseCallback GetCallback() { return m_fntCallback; }
    
	void* GetTarget() { return m_pTarget; }
	int GetRetryCnt() { return m_dwRetryCnt; }
	void SetRetryCnt( int v ) { m_dwRetryCnt = v; }
    
protected:
    
    HttpRequestType	m_eType;			// GET, POST
    std::string		m_strUrl;			// Request URL
    
    std::string		m_strRequestData;	// Request Data If Use POST
    
    void*			m_pUserData;		// Customer Data If Needed
    
    ResponseCallback m_fntCallback;		// Callback Function When Response Recieved
    void*			m_pTarget;			// As a Param In Callback Function
    
    int				m_dwRetryCnt;
    
};

#endif
