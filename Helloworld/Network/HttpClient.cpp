#include "HttpClient.h"
#include "string.h"
#include "pthread.h"
#include "semaphore.h"
#include "curl/curl.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "fcntl.h"
#include "Log.h"
#include <errno.h>
#include <list>

// IOS doesn't support anonymous semaphore}
#ifdef COCOS2D_VERSION
	#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		#define ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE 1
	#else
		#define ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE 0
	#endif

	#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		typedef int int32_t;
	#endif
#else
	#define ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE 0
#endif

#if ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE
	#define ASYNC_HTTPREQUEST_SEMAPHORE "cc"
#else
	static sem_t s_sem;
#endif

#define SEM_NAME_LEN_MAX    28

static std::string      s_sem_name;

static pthread_t        s_networkThread;
static pthread_mutex_t  s_requestQueueMutex;
static pthread_mutex_t  s_responseQueueMutex;
static pthread_mutex_t  s_progressMutex;
static sem_t*	    	s_pSem = NULL;

static bool need_quit = false;

static std::list< HttpRequest* > 	s_requestQueue;
static std::list< HttpResponse*>	s_responseQueue;

static HttpClient *s_pHttpClient = NULL; // pointer to singleton

static char s_errorBuffer[CURL_ERROR_SIZE];

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

HttpClient* HttpClient::GetInstance()
{
    if (s_pHttpClient == NULL) s_pHttpClient = new HttpClient();
    return s_pHttpClient;
}

void HttpClient::DestroyInstance()
{
	if ( s_pHttpClient )
	{
		delete s_pHttpClient;
		s_pHttpClient = NULL;
	}
}

HttpClient::HttpClient()
:m_dwTimeoutForRead(30), m_dwTimeoutForConnect(10), m_dwProgressByte(0)
{
}

HttpClient::~HttpClient()
{
	need_quit = true;
	if ( s_pSem != NULL ) sem_post( s_pSem );
}

size_t WriteData( void* ptr, size_t size, size_t nmemb, void* stream )
{
	std::string* recvBuffer = (std::string*)stream;
	size_t realSize = size * nmemb;
    
    //IME_LOG( "HttpWriteData - size=%d nmemb=%d", size, nmemb );

    recvBuffer->append( (const char*)ptr, realSize );

    if ( s_pHttpClient )
    {
       s_pHttpClient->SetProgressByte( s_pHttpClient->GetProgressByte() + realSize ); 
    }

	return realSize;
}

bool ConfigureCURL( CURL* handle )
{
	if ( handle == NULL ) return false;

	CURLcode code = CURL_LAST;

	code = curl_easy_setopt( handle, CURLOPT_ERRORBUFFER, s_errorBuffer );
	if ( code != CURLE_OK ) return false;

	code = curl_easy_setopt( handle, CURLOPT_TIMEOUT_MS, 3000L );
	if ( code != CURLE_OK ) return false;

	code = curl_easy_setopt( handle, CURLOPT_CONNECTTIMEOUT, HttpClient::GetInstance()->GetTimeoutForConnect() );
	if ( code != CURLE_OK ) return false;

	//code = curl_easy_setopt( handle, CURLOPT_VERBOSE, 1L );
	//if ( code != CURLE_OK ) return false;

	// prevent crash when dns timeout
	code = curl_easy_setopt( handle, CURLOPT_NOSIGNAL, 1 );
	if ( code != CURLE_OK ) return false;
    
    s_pHttpClient->SetProgressByte( 0 );

	return true;
}

int processGetTask( HttpRequest* request, write_callback callback, void* stream, int* errorCode )
{
	CURLcode code = CURL_LAST;
	CURL* curl = curl_easy_init();

	do
	{
		if ( !ConfigureCURL( curl ) ) break;

		code = curl_easy_setopt( curl, CURLOPT_URL, request->GetUrl() );
		if ( code != CURLE_OK ) break;

		code = curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, callback );
		if ( code != CURLE_OK ) break;

		code = curl_easy_setopt( curl, CURLOPT_WRITEDATA, stream );
		if ( code != CURLE_OK ) break;
        
        int fail = 0;
        
        do
        {
            long pos = (long)((std::string*)stream)->size();
            
            code = curl_easy_setopt( curl, CURLOPT_RESUME_FROM, pos  );
            if ( code != CURLE_OK ) break;
            
            code = curl_easy_perform( curl );
            
            if ( code == CURLE_OPERATION_TIMEDOUT )
            {
                IME_LOG( "libcurl perform timeout before complete, try again, pos=%ld", pos );
                
                if ( (long)((std::string*)stream)->size() == pos )
                {
                    if ( ++fail >= 500 ) break;
                }
                else
                {
                    fail = 0;
                }
            }
            
        } while ( code == CURLE_OPERATION_TIMEDOUT );
        
        
        if ( code != CURLE_OK ) break;
        
        IME_LOG( "libcurl perform complete" );
        

        //IME_LOG( "libcurl GET perform start" );
		//code = curl_easy_perform( curl );
		//if ( code != CURLE_OK ) break;
        //IME_LOG( "libcurl Get perform finish" );

		code = curl_easy_getinfo( curl, CURLINFO_RESPONSE_CODE, errorCode );
		if ( code != CURLE_OK || (*errorCode != 200 && *errorCode != 206 /* part of require */ ) )
		{
			code = CURLE_HTTP_RETURNED_ERROR;
			if ( s_errorBuffer[0] == '\0' ) // empty
			{
				sprintf( s_errorBuffer, "Error Code: %d", *errorCode );
			}
		}
	} while (0);

	if ( curl ) curl_easy_cleanup( curl );

	return ( code == CURLE_OK ? 0 : 1 );
}

int processPostTask( HttpRequest* request, write_callback callback, void* stream, int* errorCode )
{
	CURLcode code = CURL_LAST;
	CURL* curl = curl_easy_init();

	do
	{
		if ( !ConfigureCURL( curl ) ) break;
		code = curl_easy_setopt( curl, CURLOPT_URL, request->GetUrl() );
		if ( code != CURLE_OK ) break;

		code = curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, callback );
		if ( code != CURLE_OK ) break;

		code = curl_easy_setopt( curl, CURLOPT_WRITEDATA, stream );
		if ( code != CURLE_OK ) break;

		code = curl_easy_setopt( curl, CURLOPT_POST, 1L );
		if ( code != CURLE_OK ) break;

		code = curl_easy_setopt( curl, CURLOPT_POSTFIELDS, request->GetRequestData() );
		if ( code != CURLE_OK ) break;

		code = curl_easy_setopt( curl, CURLOPT_POSTFIELDSIZE, request->GetRequestDataSize() );
		if ( code != CURLE_OK ) break;

		code = curl_easy_perform( curl );
		if ( code != CURLE_OK ) break;

		code = curl_easy_getinfo( curl, CURLINFO_RESPONSE_CODE, errorCode );
		if ( code != CURLE_OK || *errorCode != 200 )
		{
			code = CURLE_HTTP_RETURNED_ERROR;
            if ( s_errorBuffer[0] == '\0' ) // empty
            {
                sprintf( s_errorBuffer, "Error Code: %d", *errorCode );
            }
		}
	} while (0);

	if ( curl ) curl_easy_cleanup( curl );

	return ( code == CURLE_OK ? 0 : 1 );
}

static void* NetworkThread( void* data )
{
	HttpRequest* request = NULL;

	while (true)
	{
        //int t;
        //sem_getvalue( s_pSem, &t );
        //IME_LOG( "%d", t );
        
//        sem_wait( s_pSem );
		if ( need_quit ) break;

        request = NULL;
		pthread_mutex_lock( &s_requestQueueMutex );
		if ( s_requestQueue.size() > 0 )
		{
			request = s_requestQueue.front();
			s_requestQueue.pop_front();
		}
		pthread_mutex_unlock( &s_requestQueueMutex );
        
        if( request == NULL ) continue;
		HttpResponse* response = new HttpResponse( request );

		int responseCode = -1, retValue = 0;
        memset( s_errorBuffer, 0, sizeof( s_errorBuffer ) );
        
		switch ( request->GetType() )
		{
			case HttpRequest::E_HTTP_GET:

				retValue = processGetTask(
						request,
						WriteData,
						(void *)response->GetResponseData(),
						&responseCode );
				break;

			case HttpRequest::E_HTTP_POST:

				retValue = processPostTask(
						request,
						WriteData,
						(void *)response->GetResponseData(),
						&responseCode );

				break;

			default:
				IME_ERROR( "HttpClient: Unknown request type[%d]", request->GetType() );
				break;
		}
		response->SetResponseCode( responseCode );

		if ( retValue != 0 )
		{
			response->SetSucceed( false );
			response->SetErrorMsg( s_errorBuffer );
		}
		else
		{
			response->SetSucceed( true );
		}

		pthread_mutex_lock( &s_responseQueueMutex );
		s_responseQueue.push_back( response );
		pthread_mutex_unlock( &s_responseQueueMutex );
	}

	// quit. cleanup here

	pthread_mutex_lock( &s_responseQueueMutex );
	for ( std::list< HttpResponse* >::iterator it = s_responseQueue.begin();
			it != s_responseQueue.end(); ++it )
	{
		delete *it;
	}
	s_responseQueue.clear();
	pthread_mutex_unlock( &s_responseQueueMutex );

	pthread_mutex_lock( &s_requestQueueMutex );
	for ( std::list< HttpRequest* >::iterator it = s_requestQueue.begin();
			it != s_requestQueue.end(); ++it )
	{
		delete *it;
	}
	s_requestQueue.clear();
	pthread_mutex_unlock( &s_requestQueueMutex );

	if ( s_pSem != NULL )
	{
#if ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE
		sem_unlink( ASYNC_HTTPREQUEST_SEMAPHORE );
		sem_close( s_pSem );
#else
		sem_destroy( s_pSem );
#endif
		s_pSem = NULL;

		pthread_mutex_destroy( &s_requestQueueMutex );
		pthread_mutex_destroy( &s_responseQueueMutex );
        pthread_mutex_destroy( &s_progressMutex );
	}

	pthread_exit( NULL );

	return 0;
}

bool HttpClient::InitThreadSemphore()
{
	if ( s_pSem != NULL ) return true;

#if ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE
//	s_pSem = sem_open( ASYNC_HTTPREQUEST_SEMAPHORE, O_CREAT, 0644, 0 );
	s_pSem = sem_open( s_sem_name.c_str(), O_CREAT, 0644, 0 );
	if ( s_pSem == SEM_FAILED )
	{
        IME_ERROR("Sem error code: %d", errno);
		IME_ERROR( "Open HttpRequest Semaphore failed" );
		s_pSem = NULL;
		return false;
	}
#else

	int semRet = sem_init( &s_sem, 0, 0 );
	if ( semRet < 0 )
	{
		IME_ERROR( "Init HttpRequest Semaphore failed" );
		return false;
	}
	s_pSem = &s_sem;
#endif

	pthread_mutex_init( &s_requestQueueMutex	, NULL );
	pthread_mutex_init( &s_responseQueueMutex	, NULL );
    pthread_mutex_init( &s_progressMutex        , NULL );

	pthread_create( &s_networkThread, NULL, NetworkThread, NULL );
	pthread_detach( s_networkThread );

	need_quit = false;

	return true;
}

void HttpClient::Send( HttpRequest* pRequest )
{
	if ( InitThreadSemphore() == false ) return;
	if ( pRequest == NULL ) return;

	pthread_mutex_lock( &s_requestQueueMutex );
	s_requestQueue.push_back( pRequest );
	pthread_mutex_unlock( &s_requestQueueMutex );

	sem_post( s_pSem );
}

// call in another thread
void HttpClient::DispatchResponse()
{
	HttpResponse* response = NULL;
    
    while ( true )
    {
        response = NULL;
        
        pthread_mutex_lock( &s_responseQueueMutex );
        if ( s_responseQueue.size() )
        {
            response = s_responseQueue.front();
            s_responseQueue.pop_front();
        }
        pthread_mutex_unlock( &s_responseQueueMutex );
        
        if ( response )
        {
            HttpRequest* request = response->GetRequest();
            HttpRequest::ResponseCallback fctCallback = request->GetCallback();
            
            (*fctCallback)( request->GetTarget(), response );
            
            delete request;
            delete response;
        }
        else
        {
            break;
        }
    }
}

int HttpClient::GetProgressByte()
{
    int ret = 0;
    pthread_mutex_lock( &s_progressMutex );
    ret = m_dwProgressByte;
	pthread_mutex_unlock( &s_progressMutex );
    return ret;
}

void HttpClient::SetProgressByte( int value )
{
    pthread_mutex_lock( &s_progressMutex );
    m_dwProgressByte = value;
	pthread_mutex_unlock( &s_progressMutex );
}

void HttpClient::SetSemName(const std::string &sem_name)
{
#if ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE
    s_sem_name = ASYNC_HTTPREQUEST_SEMAPHORE + sem_name;
    if (s_sem_name.size() > SEM_NAME_LEN_MAX) {
        s_sem_name = s_sem_name.substr(0, SEM_NAME_LEN_MAX);
    }
#endif
}
