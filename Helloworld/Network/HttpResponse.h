#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include <string>


class HttpRequest;
class HttpResponse
{
    
public:
	HttpResponse( HttpRequest* pRequest )
	:m_pRequest( pRequest ), m_bSucceed( false ), m_dwResponseCode(0)
	{
        
	}
    
	~HttpResponse()
	{
        
	}
    
	bool IsSucceed() { return m_bSucceed; }
	void SetSucceed( bool value ) { m_bSucceed = value; }
    
	int GetResponseCode() { return m_dwResponseCode; }
	void SetResponseCode( int value ) { m_dwResponseCode = value; }
    
	HttpRequest* GetRequest() { return m_pRequest; }
    
	// raw response data
	std::string* GetResponseData() { return &m_strResponseData; }
    
	std::string* GetErrorMsg() { return &m_strErrorBuffer; }
	void SetErrorMsg( const char* value )
	{
		m_strErrorBuffer.clear();
		m_strErrorBuffer.assign( value );
	}
    
protected:
    
	HttpRequest*	m_pRequest;			// corresponding request
	bool			m_bSucceed;
	int				m_dwResponseCode;
	std::string		m_strResponseData;	// raw response data
	std::string		m_strErrorBuffer;	// error message if not succeed
    
};

#endif
