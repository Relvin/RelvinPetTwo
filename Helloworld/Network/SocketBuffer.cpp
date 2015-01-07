


#include <memory.h>
#include <stdlib.h>
#include "SocketBuffer.h"
#include "NetBase.h"

int CSocketBuffer::m_nMaxBufferLen = CSocketBuffer::BUFFER_INIT_LEN;

CSocketBuffer::CSocketBuffer()
{
	m_stcBuffer.buffer = NULL;
	m_stcBuffer.orig_buffer = NULL;
	m_stcBuffer.totallen = 0;
	m_stcBuffer.misalign = 0;
	m_stcBuffer.off = 0;
	m_nBufferInitLen = BUFFER_INIT_LEN;
}

CSocketBuffer::~CSocketBuffer()
{
	//free the memory
	Clear();
}

void CSocketBuffer::Clear()
{
	if( m_stcBuffer.buffer != NULL )
	{
		delete m_stcBuffer.buffer;
		m_stcBuffer.buffer = NULL;
	}
	m_stcBuffer.off = 0;
	m_stcBuffer.buffer = m_stcBuffer.orig_buffer;
}

void CSocketBuffer::Init(char* szBuf, size_t uLen)
{
	m_stcBuffer.buffer = szBuf;
	m_stcBuffer.orig_buffer = szBuf;
	m_stcBuffer.totallen = uLen;
}

void CSocketBuffer::Init()
{
	//use config buffer len
	m_nBufferInitLen = CSocketBuffer::m_nMaxBufferLen;
	char *pTmp = new char [m_nBufferInitLen];
	Init(pTmp,m_nBufferInitLen);
}

int CSocketBuffer::Append(const void * pBuffer, size_t uLen)
{
	if (!uLen)
		return 0;

	size_t need = m_stcBuffer.misalign + m_stcBuffer.off + uLen;

	if (m_stcBuffer.totallen < need)
	{
		if (m_stcBuffer.misalign >= uLen)
		{
			Align();
		}
		else if (Expand(uLen) == -1)
			return (-1);
	}

	memcpy(m_stcBuffer.buffer + m_stcBuffer.off, pBuffer, uLen);
	m_stcBuffer.off += uLen;

	return 0;
}

int CSocketBuffer::Appends(const CSocketBuffer * pBuffer)
{
	if (pBuffer->GetSize() > 0)
	{
		return Append(pBuffer->GetBuffer(), pBuffer->GetSize());
	}
	else
	{
		return 0;
	}
}

void CSocketBuffer::Align()
{
	memmove(m_stcBuffer.orig_buffer, m_stcBuffer.buffer, m_stcBuffer.off);
	m_stcBuffer.buffer = m_stcBuffer.orig_buffer;
	m_stcBuffer.misalign = 0;
}

int CSocketBuffer::Expand(size_t uLen)
{
	size_t need = m_stcBuffer.misalign + m_stcBuffer.off + uLen;

	/* If we can fit all the data, then we don't have to do anything */
	if (m_stcBuffer.totallen >= need)
		return (0);

	/*
	 * If the misalignment fulfills our data needs, we just force an
	 * alignment to happen.  Afterwards, we have enough space.
	 */
	if (m_stcBuffer.misalign >= uLen) {
		Align();
	} else {
		void *newbuf;
		size_t length = m_stcBuffer.totallen;

		if (length < 256)
			length = 256;
		while (length < need)
			length <<= 1;

		if (m_stcBuffer.orig_buffer != m_stcBuffer.buffer)
			Align();
		if ((newbuf = realloc(m_stcBuffer.buffer, length)) == NULL)
			return (-1);

		m_stcBuffer.orig_buffer = m_stcBuffer.buffer = (char *)newbuf;
		m_stcBuffer.totallen = length;
	}

	return 0;
}

void CSocketBuffer::Erase(size_t uLen)
{
	if (uLen >= m_stcBuffer.off)
	{
		m_stcBuffer.off = 0;
		m_stcBuffer.buffer = m_stcBuffer.orig_buffer;
		m_stcBuffer.misalign = 0;
		return;
	}

	m_stcBuffer.buffer += uLen;
	m_stcBuffer.misalign += uLen;

	m_stcBuffer.off -= uLen;
}

void CSocketBuffer::Reset()
{
	Erase(GetSize());
}

const char * CSocketBuffer::GetBuffer() const
{
	return m_stcBuffer.buffer;
}

const char * CSocketBuffer::GetBuffer(size_t & size) const
{
	size = m_stcBuffer.off;
	return m_stcBuffer.buffer;
}

size_t CSocketBuffer::GetSize() const
{
	return m_stcBuffer.off;
}

int CSocketBuffer::BufferRead(char * szBuffer, size_t uLen)
{
	size_t nread = uLen;
	if (nread >= m_stcBuffer.off)
		nread = m_stcBuffer.off;

	memcpy(szBuffer, m_stcBuffer.buffer, nread);
	Erase(nread);

	return nread;
}


#ifdef NET_CURL
int CSocketBuffer::SockRead(CURL * pCurl, int nHowmuch, CURLcode & curlRes)
{
	char *p;
	int n = BUFFER_MAX_READ;

	if (nHowmuch < 0 || nHowmuch > n)
		nHowmuch = n;

	
	size_t need = m_stcBuffer.misalign + m_stcBuffer.off + nHowmuch;
	if (m_stcBuffer.totallen < need)
	{
		if (m_stcBuffer.misalign >= nHowmuch)
		{
			Align();
		}
		else if (Expand(nHowmuch) == -1)
		{
			Reset();
			//realloc 失败！
			//need log
			return -1;
		}
	}

	/* We can append new data at this point */
	p = m_stcBuffer.buffer + m_stcBuffer.off;

	//curl read!
	CURLcode res;
	size_t iolen;
    res = curl_easy_recv(pCurl, p, nHowmuch, &iolen);
	n = iolen;
	curlRes = res;
    if(CURLE_OK != res)
	{
		return 0;
	}
	if (n < 0)
		return -1;
	if (n == 0)
		return 0;

	m_stcBuffer.off += n;

	return n;
}

int CSocketBuffer::Sends(CURL * pCurl, CURLcode & curlRes)
{
	int n;


	CURLcode res;
	size_t iolen;
	res = curl_easy_send(pCurl, m_stcBuffer.buffer, m_stcBuffer.off, &iolen);

	n = iolen;
	curlRes = res;
	if(CURLE_OK != res && CURLE_AGAIN != res)
    {
		//printf("Error: %s\n", curl_easy_strerror(res));
		return -1;
    }

	if (n < 0)
		return -1;
	if (n == 0)
		return 0;
	Erase(n);

	return n;
}

#else
//读到buff，nHowmuch表示一次读到字节数。-1 表示采用默认 4096字节
int CSocketBuffer::SockRead(CNetBase *pNetBase, int nHowmuch)
{
	char *p;
	int n = BUFFER_MAX_READ;

	if (nHowmuch < 0 || nHowmuch > n)
		nHowmuch = n;

	size_t need = m_stcBuffer.misalign + m_stcBuffer.off + nHowmuch;
	if (m_stcBuffer.totallen < need)
	{
		if (m_stcBuffer.misalign >= nHowmuch)
		{
			Align();
		}
		else if (Expand(nHowmuch) == -1)
		{
			Reset();
			//realloc 失败！
			//need log
			return -1;
		}
	}

	/* We can append new data at this point */
	p = m_stcBuffer.buffer + m_stcBuffer.off;

	n = pNetBase->Recv(p,nHowmuch);

	if (n <= 0)
		return n;

	m_stcBuffer.off += n;

	return n;
}

//发送buff  返回发送成功到字节数
int CSocketBuffer::Sends(CNetBase *pNetBase)
{
	int n;
	
	n = pNetBase->Send(m_stcBuffer.buffer,m_stcBuffer.off);

	if (n < 0)
		return -1;
	if (n == 0)
		return 0;
	Erase(n);
	return n;
}

#endif