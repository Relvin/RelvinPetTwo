
#include "NetBase.h"
#include <errno.h>
#include <signal.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#pragma comment(lib, "wsock32")
#endif


CNetBase::CNetBase(SOCKET sock)
{
	m_sock = sock;
}

CNetBase::~CNetBase()
{
}

int CNetBase::Init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	/*
	http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx

	typedef struct WSAData { 
		WORD wVersion;								//winsock version
		WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
		char szDescription[WSADESCRIPTION_LEN+1]; 
		char szSystemStatus[WSASYSSTATUS_LEN+1]; 
		unsigned short iMaxSockets; 
		unsigned short iMaxUdpDg; 
		char FAR * lpVendorInfo; 
	}WSADATA, *LPWSADATA; 
	*/
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8)) 
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret )
	{
		CCLOG("Initilize winsock error !");
		return -1;
	}
#endif
	
	return 0;
}
//this is just for windows
int CNetBase::Clean()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		return (WSACleanup());
#endif
		return 0;
}

CNetBase& CNetBase::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

CNetBase::operator SOCKET ()
{
	return m_sock;
}
//create a socket object win/lin is the same
// af:
bool CNetBase::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	if ( m_sock == INVALID_SOCKET )
	{
		return false;
	}

	return true;
}

void u_alarm_handler(int n) {
    
}

bool CNetBase::Connect(const char* ip, unsigned short port)
{
    struct hostent* h = gethostbyname( ip );
    if (h == NULL) {
        return false;
    }
    
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
//	svraddr.sin_addr.s_addr = inet_addr(ip);
    svraddr.sin_addr = *(struct in_addr*) h->h_addr;
    svraddr.sin_port = htons(port);
    
    // added by Juniechu, 用于超时判断}
    /** 首先定义一个中断信号处理函数u_alarm_handler，用于超时后的报警处理，然后定义一个}
     5s的定时器，执行connect，当系统connect成功，则系统正常执行下去；如果connect不成功}
     阻塞在这里，则超过定义的5s之后，系统产生一个信号，触发执行u_alarm_handler函数，当}
     执行完u_alarm_handler函数后，程序将继续从connect的下面一行执行下去。}
     */

    //sigset(SIGALRM, u_alarm_handler);}
    //alarm(10);
	int ret = connect(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
    //alarm(0);
    //sigrelse(SIGALRM);
    
	if ( ret == SOCKET_ERROR )
	{
		return false;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	unsigned long ul = 1;
	ret = ioctlsocket(m_sock, FIONBIO, (unsigned long*)&ul);
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
#else
	if(fcntl(m_sock, F_SETFL, O_NONBLOCK) == -1) 
	{
		return false;
	}
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    // set flag SO_NOSIGPIPE, so SIGPIPE won't be raised when write fails
    // @yuxiaofei
    int opt =  1;
    if(setsockopt(m_sock, SOL_SOCKET, SO_NOSIGPIPE, (char*)&opt, sizeof(opt) ) != 0)
    {
        return false;
    }
#endif
    
#endif
	return true;
}

bool CNetBase::Bind(unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);

	int opt =  1;
	if ( setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0 ) 
		return false;

	int ret = bind(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR )
	{
		return false;
	}
	return true;
}
//for server
bool CNetBase::Listen(int backlog)
{
	int ret = listen(m_sock, backlog);
	if ( ret == SOCKET_ERROR )
	{
		return false;
	}
	return true;
}

bool CNetBase::Accept(CNetBase& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR )
	{
		return false;
	}

	s = sock;
	if ( fromip != NULL )
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));

	return true;
}

int CNetBase::Send(const char* buf, int len, int flags)
{
	int bytes;
	int count = 0;

	while ( count < len )
	{

		bytes = send(m_sock, buf + count, len - count, flags);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
	}

	return count;
}

int CNetBase::Recv(char* buf, int len, int flags)
{
	return (recv(m_sock, buf, len, flags));
}

int CNetBase::Close()
{
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}

int CNetBase::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}

bool CNetBase::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
		
	sprintf(ip, 
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0], 
		(unsigned char)p->h_addr_list[0][1], 
		(unsigned char)p->h_addr_list[0][2], 
		(unsigned char)p->h_addr_list[0][3]);
	
	return true;
}
 
 
