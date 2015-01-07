#ifndef _ENCODE_H_
#define _ENCODE_H_
#include "cocos2d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include <arpa/inet.h>
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <windows.h>
#include <winsock2.h>
//#include <arpa/inet.h>

typedef	unsigned char		u_int8_t;
typedef	unsigned short		u_int16_t;
typedef	unsigned int		u_int32_t;
typedef	unsigned long long	u_int64_t;

#endif
namespace MiniConnProxy
{
#define MAX_OP_ID_LENGTH 64
#define MAX_APP_PACK_LENGTH (1024 * 8)

	int EncodeChar( char **pstrEncode, unsigned char ucSrc );
	int DecodeChar( char **pstrDecode, unsigned char *pucDest );
	int EncodeShort16( char **pstrEncode, unsigned short usSrc );
	int DecodeShort16( char **pstrDecode, unsigned short *pusDest );
	int EncodeLong( char **pstrEncode, unsigned long ulSrc );
	int DecodeLong( char **pstrDecode, unsigned long *pulDest );
	int EncodeInt32( char **pstrEncode, unsigned int uiSrc );
	int DecodeInt32( char **pstrDecode, unsigned int *puiDest );
	int EncodeString( char **pstrEncode, char *strSrc, short sMaxStrLength );
	int DecodeString( char **pstrDecode, char *strDest, short sMaxStrLength );
	int EncodeMem( char **pstrEncode, char *pcSrc, short sMemSize );
	int DecodeMem( char **pstrDecode, char *pcDest, short sMemSize );
	int EncodeMemInt( char **pstrEncode, char *pcSrc, int iMemSize );
	int DecodeMemInt( char **pstrDecode, char *pcDest, int iMemSize );
	int EncodeInt64( char **pstrEncode, u_int64_t uiSrc );
	int DecodeInt64( char **pstrDecode, u_int64_t *puiDest );

	int gEncode(char *pcOutBuffer, short& shOutLength);
	
	extern short nVersion;		//协议版本号--默认0x100
	extern char cPackFlag;		//后续数据包是否有开放平台包头.0-无，1-有
	extern int iCpID;			//cp编号
	extern int iGameID;		//cp游戏ID
	extern short nSvrID;		//cp服务器ID
	extern unsigned char cOpenIDLen;				//用户ID长度
	extern char szOpenID[MAX_OP_ID_LENGTH];//用户ID
	extern unsigned char cOptionLen;							//扩展数据长度，0表示无扩展数据
	extern char szOptionData[MAX_OP_ID_LENGTH];		//扩展数据
	extern short nAppPackLen;							//应用协议包体长度
	extern char szAppPackData[MAX_APP_PACK_LENGTH];	//应用协议包体
	 
	#define EncodeInt EncodeInt32
	#define DecodeInt DecodeInt32
	#define EncodeShort EncodeShort16
	#define DecodeShort DecodeShort16
}
#endif

